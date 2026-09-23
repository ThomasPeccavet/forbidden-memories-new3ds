#include <3ds.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fm_platform.h"
#include "fm_cpu.h"
#include "fm_memory.h"
#include "fm_runtime_shim.h"
#include "fm_interp.h"
#include "fm_gpu.h"

#include "gpu_sw_renderer.h"

/* B28 helpers exported by source/fm_gpu.c. */
extern uint64_t fm_gpu_fill_suppressed_count(void);
extern void fm_gpu_last_fill_info(
    int *x, int *y, int *w, int *h, uint16_t *color
);


/* B42 - active/desactive le vieux hack de preservation du background. */
extern void fm_gpu_b42_set_preserve_background_clears(int enabled);
extern int fm_gpu_b42_get_preserve_background_clears(void);

/* Generated PSXRecomp dispatch introspection (B135.27 diagnostic). */
extern int psx_game_is_function_entry(uint32_t addr);


/*
 * B100 - diagnostic leger de l'environnement de dessin PS1.
 * Aucun scan VRAM supplementaire : on lit uniquement les registres
 * E3/E4/E5 deja suivis par fm_gpu.c.
 */
extern uint32_t fm_gpu_b101_offset_draw_packets(void);

extern uint32_t fm_gpu_display_mode_raw(void);
extern int fm_gpu_display_24bit(void);
extern unsigned fm_gpu_display_width(void);

extern void fm_gpu_b100_env_get(
    int *off_x, int *off_y,
    int *area_x1, int *area_y1,
    int *area_x2, int *area_y2,
    uint32_t *e3_count,
    uint32_t *e4_count,
    uint32_t *e5_count,
    uint32_t *gp1_05_count,
    uint32_t *last_e3,
    uint32_t *last_e4,
    uint32_t *last_e5,
    uint32_t *last_gp1_05
);


/* B29 - API de trace ajoutee proprement au GPU B28. */
extern unsigned fm_gpu_b29_draw_trace_count(void);
extern int fm_gpu_b29_draw_trace_get(
    unsigned back,
    uint8_t *opcode,
    unsigned *words,
    uint16_t *texpage,
    int *off_x,
    int *off_y,
    int *area_x1,
    int *area_y1,
    int *area_x2,
    int *area_y2,
    uint32_t out_cmd[8]
);


/* B38 - dernier gros rectangle/sprite GP0. */
extern int fm_gpu_b38_bigrect_get(
    uint32_t *count,
    uint8_t *opcode,
    int *textured,
    int *raw,
    int *x, int *y, int *w, int *h,
    int *u, int *v,
    int *clut_x_out, int *clut_y_out,
    uint16_t *texpage,
    uint32_t out_cmd[4]
);


extern int fm_gpu_b39_texture_probe_get(
    uint32_t *texwindow,
    int *depth,
    int *base_x,
    int *base_y,
    uint32_t *texel_count,
    uint32_t *index_nonzero,
    uint32_t *color_nonzero,
    uint32_t *unique_indices,
    uint16_t clut16[16],
    uint8_t sample_idx[8],
    uint16_t sample_col[8]
);


extern void fm_gpu_b44_watch_get(
    uint32_t *fill_hits,
    uint32_t *draw_hits,
    uint32_t *copy_hits,
    uint32_t *upload_hits,
    uint32_t *last_serial,
    uint8_t *last_type,
    uint8_t *last_opcode,
    int *x, int *y, int *w, int *h,
    uint32_t cmd[4]
);


extern int fm_gpu_b46_sprite_provenance_get(
    uint32_t *hits,
    uint32_t *serial,
    uint16_t *last_e1,
    uint32_t *e1_age,
    uint32_t *fill_age,
    uint16_t *texpage,
    int *off_x,
    int *off_y,
    uint32_t cmd[4]
);


int g_ws_bd_stretch_on = 0;
int g_ws_bd_stretch_pct = 100;


int psx_ws_prim_in_backdrop(void)
{
    return 0;
}


/*
 * ============================================================
 * CD-ROM HLE bring-up state
 * ============================================================
 */

static uint8_t g_cd_sector[2048];

static uint32_t g_cd_lba = 0;
static uint32_t g_cd_pos = 2048;
static uint32_t g_cd_last_cmd = 0;
static uint32_t g_cd_sector_count = 0;

static int g_cd_reading = 0;
static int g_cd_error = 0;


/*
 * Dernière recherche ISO9660 effectuée par DsSearchFile.
 */
static char g_cd_search_path[256];

static uint32_t g_cd_search_lba = 0;
static uint32_t g_cd_search_size = 0;

static int g_cd_search_ok = 0;


/*
 * Dernier appel BIOS observé.
 *
 * result:
 *  -1 = aucun appel
 *   0 = non traité par fm_bios_try_hle()
 *   1 = traité par fm_bios_try_hle()
 *   2 = traité directement par main.c (bring-up)
 */
static uint32_t g_bios_debug_addr = 0;
static uint32_t g_bios_debug_fn = 0;
static int g_bios_debug_result = -1;


/*
 * Dernier message texte que le jeu essaie d'envoyer à sa console
 * de debug via FUN_80090CF8.
 *
 * Cette fonction n'a pas d'effet gameplay : elle écrit seulement
 * le texte caractère par caractère via FUN_800901A8. L'intercepter
 * évite de perdre énormément de temps dans cette sortie et nous
 * donne directement le message d'erreur/timeout réel.
 */
static char g_game_log[128];
static uint32_t g_game_log_ptr = 0;
static uint32_t g_game_log_count = 0;


/*
 * ============================================================
 * VSync HLE
 * ============================================================
 *
 * FUN_800746B8 est la VSync Psy-Q de Forbidden Memories.
 *
 * La version native du jeu attend que DAT_80093EE8 soit incrémenté
 * par l'IRQ VBlank. Tant que notre chaîne d'exception R3000A/BIOS
 * n'est pas complète, la fonction finit dans "VSync: timeout".
 *
 * On la synchronise directement sur les VBlank de la boucle 3DS.
 */
static int g_vsync_wait_active = 0;
static uint32_t g_vsync_wait_until_frame = 0;
static int32_t g_vsync_wait_mode = 0;

static uint32_t g_vsync_hle_calls = 0;
static uint32_t g_vsync_hle_wait_calls = 0;
static uint32_t g_vsync_hle_query_calls = 0;
static uint32_t g_vsync_hle_mode1_calls = 0;
static uint32_t g_vsync_hle_mode1_nonzero = 0;
static uint32_t g_vsync_hle_mode1_last = 0;
static uint32_t g_vsync_hle_mode1_max = 0;
static uint64_t g_vsync_host_epoch_ms = 0;
static int32_t g_vsync_hle_last_mode = 0;


/*
 * ============================================================
 * B108 - correct Psy-Q VSync(n>=2) scheduling
 * ============================================================
 *
 * Real Psy-Q semantics:
 *   VSync(0)  -> next VBlank from NOW
 *   VSync(n)  -> wait until LAST_SYNCED_VBLANK + n, n >= 2
 *
 * The old HLE incorrectly used NOW + n for every VSync(n), which
 * adds extra VBlanks whenever some time has already elapsed since
 * the previous synchronized VSync. This can make gameplay/menu
 * cadence visibly too slow.
 */
static uint32_t g_b108_vsync_last_sync_frame = 0u;
static uint32_t g_b108_vsync_sync_valid = 0u;
static uint32_t g_b108_vsync_mode0 = 0u;
static uint32_t g_b108_vsync_modeN = 0u;
static uint32_t g_b108_vsync_immediate = 0u;
static uint32_t g_b108_vsync_waited = 0u;
static uint32_t g_b108_vsync_last_target = 0u;


/*
 * ============================================================
 * B110 - profiler du vrai code ARM recompile
 * ============================================================
 *
 * B109 a montre qu'on ne doit plus deviner : on mesure maintenant
 * directement chaque fm_runtime_probe() du dispatcher principal.
 *
 * Pour chaque gros appel on garde :
 *   start = PC avec lequel le probe a ete lance
 *   end   = PC de reprise/retour du probe
 *   hits
 *   temps cumule
 *   pire duree
 *
 * On conserve les 12 entrees ayant le plus de temps cumule.
 */
#define B110_PROF_SLOTS 12u

typedef struct
{
    uint32_t start_pc;
    uint32_t end_pc;
    uint32_t hits;
    uint32_t max_us;
    uint64_t total_us;
} B110ProbeStat;

static B110ProbeStat g_b110_prof[B110_PROF_SLOTS];

static uint64_t g_b110_probe_total_us = 0u;
static uint32_t g_b110_probe_calls = 0u;
static uint32_t g_b110_probe_max_us = 0u;
static uint32_t g_b110_probe_max_start = 0u;
static uint32_t g_b110_probe_max_end = 0u;

static uint64_t g_b110_loop_sum_ms = 0u;
static uint32_t g_b110_loop_samples = 0u;
static uint32_t g_b110_loop_max_ms = 0u;
static uint32_t g_b110_loop_over20 = 0u;
static uint32_t g_b110_loop_over33 = 0u;

/*
 * B111 - guest cadence probe.
 * Updated only by the 2-second debug refresh, so it has no hot-path cost.
 * It tells us whether the host really runs near 60 Hz while the guest
 * completes far fewer logical frames.
 */
static uint32_t g_b111_prev_host_frame = 0u;
static uint32_t g_b111_prev_guest_frame = 0u;
static uint32_t g_b111_host_delta = 0u;
static uint32_t g_b111_guest_delta = 0u;
static uint32_t g_b111_guest_per_100_host = 0u;


/*
 * ============================================================
 * B115 - GsSortOt phase profiler
 * ============================================================
 *
 * B113/B114 mixed two independent changes: OT merge acceleration and
 * early source-OT submission. B115 keeps the current rendering behavior
 * unchanged and times the three phases independently:
 *
 *   R = OT sentinel repair
 *   P = early source OT traversal + GP0 submission/rasterization
 *   M = native GsSortOt merge
 *
 * Stats are bucketed in real one-second windows, independent of host FPS,
 * so a 180-270 ms stall cannot be hidden by many short loops.
 */
static uint64_t g_b115_window_start_ms = 0u;

static uint32_t g_b115_cur_calls = 0u;
static uint64_t g_b115_cur_repair_ms = 0u;
static uint64_t g_b115_cur_submit_ms = 0u;
static uint64_t g_b115_cur_merge_ms = 0u;
static uint32_t g_b115_cur_repair_max_ms = 0u;
static uint32_t g_b115_cur_submit_max_ms = 0u;
static uint32_t g_b115_cur_merge_max_ms = 0u;

static uint32_t g_b115_last_calls = 0u;
static uint64_t g_b115_last_repair_ms = 0u;
static uint64_t g_b115_last_submit_ms = 0u;
static uint64_t g_b115_last_merge_ms = 0u;
static uint32_t g_b115_last_repair_max_ms = 0u;
static uint32_t g_b115_last_submit_max_ms = 0u;
static uint32_t g_b115_last_merge_max_ms = 0u;

static uint32_t g_b115_slow_total_ms = 0u;
static uint32_t g_b115_slow_repair_ms = 0u;
static uint32_t g_b115_slow_submit_ms = 0u;
static uint32_t g_b115_slow_merge_ms = 0u;
static uint32_t g_b115_slow_src = 0u;
static uint32_t g_b115_slow_dst = 0u;
static uint32_t g_b115_slow_nodes = 0u;
static uint32_t g_b115_slow_packets = 0u;
static uint32_t g_b115_slow_words = 0u;
static uint32_t g_b115_slow_draw = 0u;
static uint32_t g_b115_slow_env = 0u;
static uint32_t g_b115_slow_other = 0u;
static int32_t g_b115_slow_native_code = 0;


static void b115_roll_window(uint64_t now_ms)
{
    if (g_b115_window_start_ms == 0u)
    {
        g_b115_window_start_ms = now_ms;
        return;
    }

    if ((now_ms - g_b115_window_start_ms) < 1000u)
    {
        return;
    }

    g_b115_last_calls = g_b115_cur_calls;
    g_b115_last_repair_ms = g_b115_cur_repair_ms;
    g_b115_last_submit_ms = g_b115_cur_submit_ms;
    g_b115_last_merge_ms = g_b115_cur_merge_ms;
    g_b115_last_repair_max_ms = g_b115_cur_repair_max_ms;
    g_b115_last_submit_max_ms = g_b115_cur_submit_max_ms;
    g_b115_last_merge_max_ms = g_b115_cur_merge_max_ms;

    g_b115_cur_calls = 0u;
    g_b115_cur_repair_ms = 0u;
    g_b115_cur_submit_ms = 0u;
    g_b115_cur_merge_ms = 0u;
    g_b115_cur_repair_max_ms = 0u;
    g_b115_cur_submit_max_ms = 0u;
    g_b115_cur_merge_max_ms = 0u;

    g_b115_window_start_ms = now_ms;
}


static void b115_record_sort(
    uint64_t end_ms,
    uint32_t repair_ms,
    uint32_t submit_ms,
    uint32_t merge_ms,
    uint32_t src,
    uint32_t dst,
    uint32_t nodes,
    uint32_t packets,
    uint32_t words,
    uint32_t draw_packets,
    uint32_t env_packets,
    uint32_t other_packets,
    int32_t native_code
)
{
    b115_roll_window(end_ms);

    ++g_b115_cur_calls;
    g_b115_cur_repair_ms += repair_ms;
    g_b115_cur_submit_ms += submit_ms;
    g_b115_cur_merge_ms += merge_ms;

    if (repair_ms > g_b115_cur_repair_max_ms)
    {
        g_b115_cur_repair_max_ms = repair_ms;
    }

    if (submit_ms > g_b115_cur_submit_max_ms)
    {
        g_b115_cur_submit_max_ms = submit_ms;
    }

    if (merge_ms > g_b115_cur_merge_max_ms)
    {
        g_b115_cur_merge_max_ms = merge_ms;
    }

    uint32_t total_ms = repair_ms + submit_ms + merge_ms;

    if (total_ms > g_b115_slow_total_ms)
    {
        g_b115_slow_total_ms = total_ms;
        g_b115_slow_repair_ms = repair_ms;
        g_b115_slow_submit_ms = submit_ms;
        g_b115_slow_merge_ms = merge_ms;
        g_b115_slow_src = src;
        g_b115_slow_dst = dst;
        g_b115_slow_nodes = nodes;
        g_b115_slow_packets = packets;
        g_b115_slow_words = words;
        g_b115_slow_draw = draw_packets;
        g_b115_slow_env = env_packets;
        g_b115_slow_other = other_packets;
        g_b115_slow_native_code = native_code;
    }
}


static void b110_profile_probe(
    uint32_t start_pc,
    uint32_t end_pc,
    uint32_t elapsed_us
)
{
    ++g_b110_probe_calls;
    g_b110_probe_total_us += elapsed_us;

    if (elapsed_us > g_b110_probe_max_us)
    {
        g_b110_probe_max_us = elapsed_us;
        g_b110_probe_max_start = start_pc;
        g_b110_probe_max_end = end_pc;
    }

    int slot = -1;

    for (unsigned i = 0u; i < B110_PROF_SLOTS; ++i)
    {
        if (g_b110_prof[i].hits != 0u
            && g_b110_prof[i].start_pc == start_pc)
        {
            slot = (int)i;
            break;
        }
    }

    if (slot < 0)
    {
        for (unsigned i = 0u; i < B110_PROF_SLOTS; ++i)
        {
            if (g_b110_prof[i].hits == 0u)
            {
                slot = (int)i;
                break;
            }
        }
    }

    if (slot < 0)
    {
        unsigned smallest = 0u;

        for (unsigned i = 1u; i < B110_PROF_SLOTS; ++i)
        {
            if (g_b110_prof[i].total_us
                < g_b110_prof[smallest].total_us)
            {
                smallest = i;
            }
        }

        /*
         * Une nouvelle entree ne remplace une entree chaude que si
         * ce probe individuel est deja significatif.
         */
        if ((uint64_t)elapsed_us <= g_b110_prof[smallest].total_us)
        {
            return;
        }

        slot = (int)smallest;
        memset(&g_b110_prof[slot], 0, sizeof(g_b110_prof[slot]));
    }

    B110ProbeStat *s = &g_b110_prof[slot];

    if (s->hits == 0u)
    {
        s->start_pc = start_pc;
    }

    s->end_pc = end_pc;
    ++s->hits;
    s->total_us += elapsed_us;

    if (elapsed_us > s->max_us)
    {
        s->max_us = elapsed_us;
    }
}


static int b110_get_rank(
    unsigned rank,
    B110ProbeStat *out
)
{
    uint8_t used[B110_PROF_SLOTS];
    memset(used, 0, sizeof(used));

    for (unsigned r = 0u; r <= rank; ++r)
    {
        int best = -1;

        for (unsigned i = 0u; i < B110_PROF_SLOTS; ++i)
        {
            if (used[i] || g_b110_prof[i].hits == 0u)
            {
                continue;
            }

            if (best < 0
                || g_b110_prof[i].total_us
                    > g_b110_prof[(unsigned)best].total_us)
            {
                best = (int)i;
            }
        }

        if (best < 0)
        {
            return 0;
        }

        used[(unsigned)best] = 1u;

        if (r == rank)
        {
            if (out)
            {
                *out = g_b110_prof[(unsigned)best];
            }

            return 1;
        }
    }

    return 0;
}


/*
 * ============================================================
 * STR intro skip - bring-up temporaire
 * ============================================================
 *
 * Le runtime PC validé montre que le boot reste longtemps dans
 * FUN_8006A4D8 en attendant des secteurs STR, puis que l'appui
 * Start permet d'atteindre le titre/menu.
 *
 * Sur 3DS, notre chaîne CD streaming STR n'alimente pas encore
 * FUN_80078B58. Pour débloquer le jalon graphique sans afficher
 * d'image artificielle, on force UNE SEULE FOIS la fin du premier
 * flux vidéo. Les écrans suivants restent entièrement produits
 * par le code du jeu.
 */
static int g_str_intro_skip_pending = 1;
static uint32_t g_str_intro_skip_count = 0;

static uint32_t g_str_intro_last_base = 0;
static uint8_t g_str_intro_last_done = 0;


/*
 * ============================================================
 * Main state-machine diagnostics
 * ============================================================
 *
 * DAT_8009C60A est l'état principal dispatché par FUN_8002DF60.
 * Le bit 7 est le flag "initialisé"; les 5 bits bas choisissent
 * l'entrée de la jump-table du jeu.
 */
static uint8_t g_main_state = 0;
static uint8_t g_main_state_last = 0xFFu;
static uint32_t g_main_state_changes = 0;
static uint32_t g_main_state_stable_frames = 0;

static uint8_t g_main_state_60c = 0;
static uint8_t g_main_state_60d = 0;
static uint8_t g_main_state_60e = 0;

static uint32_t g_main_render_ctx = 0;
static uint8_t g_main_frame_target = 0;
static int32_t g_main_frame_done = 0;

static uint32_t g_main_flags_6a0 = 0;
static uint32_t g_main_flags_710 = 0;
static uint32_t g_main_flags_72c = 0;


/*
 * ============================================================
 * Startup / dispatcher trace
 * ============================================================
 *
 * Le boot est encore avant la machine d'etat principale
 * (DAT_8009C60A reste a 0). Ces compteurs permettent de voir
 * quelles fonctions importantes repassent par le dispatcher et
 * quelles images dynamiques sont deja presentes en RAM.
 */
static uint32_t g_trace_pc[6];
static uint32_t g_trace_count = 0;
static uint32_t g_trace_last_phys = 0xFFFFFFFFu;

static uint32_t g_hit_startup = 0;
static uint32_t g_hit_service = 0;
static uint32_t g_hit_load_wait = 0;

/* B31: snapshot exact de la requete asynchrone au premier passage dans 80013700. */
static uint32_t g_b31_req_snap = 0;
static uint32_t g_b31_req_10 = 0;
static uint32_t g_b31_req_18 = 0;
static uint32_t g_b31_req_1c = 0;
static uint32_t g_b31_req_20 = 0;
static uint32_t g_b31_req_24 = 0;
static uint32_t g_b31_req_2c = 0;
static uint32_t g_b31_req_34 = 0;
static uint32_t g_b31_req_40 = 0;
static uint16_t g_b31_req_44 = 0;
static uint8_t  g_b31_req_46 = 0;
static uint8_t  g_b31_req_47 = 0;
static uint32_t g_b31_r137_ra = 0;
static uint32_t g_b31_r137_gp = 0;
static uint32_t g_b31_r137_a0 = 0;
static uint32_t g_b31_r137_a1 = 0;
static uint32_t g_b31_r137_a2 = 0;
static uint32_t g_b31_r137_a3 = 0;
static uint32_t g_b31_c460 = 0;
static uint32_t g_b31_c484 = 0;
static uint32_t g_b31_tbl0 = 0;

/*
 * B32 - pont CdGetSector (FUN_8007E968).
 *
 * B31 montre une requete active dans DAT_800EB1B8 avec un secteur
 * restant, alors que notre backend host n'a lu aucun secteur. Le code
 * original appelle FUN_8007E968(dest, 512) lorsqu'un secteur CD est
 * pret. Cette fonction pilote directement le DMA3 PS1, materiel que
 * notre bring-up ne reproduit pas encore completement.
 *
 * B32 intercepte donc uniquement ce point de copie : le LBA courant
 * vient de la requete du jeu (+0x24), le secteur est lu depuis disc.bin
 * puis copie dans le buffer guest demande. Toute la logique au-dessus
 * (decompte, callbacks, chainage, flags de fin) reste le vrai code PS1.
 */
static uint32_t g_b32_getsec_calls = 0;
static uint32_t g_b32_getsec_ok = 0;
static uint32_t g_b32_getsec_fail = 0;
static uint32_t g_b32_last_req = 0;
static uint32_t g_b32_last_lba = 0;
static uint32_t g_b32_last_dst = 0;
static uint32_t g_b32_last_bytes = 0;
static uint32_t g_b32_last_remaining = 0;
static uint32_t g_b32_last_rc = 0;

/*
 * B56 - vrai curseur de flux CD.
 *
 * B55 a revele 0x11111111 partout dans la zone overlay.
 * Le pont B32 relisait req+0x24 a CHAQUE CdlDataReady, alors que
 * sur une vraie PS1 le lecteur CD avance automatiquement d'un secteur
 * pendant CdlReadN. Le curseur hardware emule est g_cd_lba.
 */
static uint32_t g_b56_stream_reads = 0u;
static uint32_t g_b56_stream_first_lba = 0u;
static uint32_t g_b56_stream_last_lba = 0u;


/*
 * ============================================================
 * B57 - curseur par requete LibCD
 * ============================================================
 *
 * B56 a prouve que l'avance sectorielle etait indispensable, mais
 * g_cd_lba n'etait pas encore initialise au LBA logique de la
 * requete : le stream est parti de 0.
 *
 * FUN_8001385C place le LBA de depart dans req+0x24. Ce champ reste
 * fixe pendant la requete, tandis que le lecteur CD physique avance.
 *
 * On maintient donc un curseur host par requete :
 *   premier secteur = req+0x24
 *   suivants        = +1, +2, ...
 *
 * Le curseur est reinitialise si :
 *   - le pointeur de requete change ;
 *   - le LBA de base change ;
 *   - remaining remonte (nouvelle requete sur la meme structure).
 */
static uint32_t g_b57_req = 0u;
static uint32_t g_b57_base_lba = 0u;
static uint32_t g_b57_next_lba = 0u;
static uint32_t g_b57_last_remaining = 0u;
static uint32_t g_b57_resets = 0u;
static uint32_t g_b57_read_index = 0u;


/*
 * ============================================================
 * B59 - pont BIOS PAL pour l'overlay charge a 801680F4
 * ============================================================
 *
 * B57 a enfin charge le vrai ecran KONAMI.
 * B58 montre ensuite une boucle dans l'overlay 801681xx.
 *
 * Les quatre premiers mots de l'overlay charges depuis le CD sont :
 *
 *   801680F4  3C03BFC8   lui   v1,0xBFC8
 *   801680F8  9063FF52   lbu   v1,-0xAE(v1) -> 0xBFC7FF52
 *   801680FC  24020045   addiu v0,zero,0x45
 *   80168100  1062001A   beq   v1,v0,8016816C
 *
 * Le code teste donc explicitement un octet du BIOS PS1 contre 0x45
 * ('E', region Europe). Notre runtime 3DS n'a pas encore de ROM BIOS
 * mappee : fm_memory_read_byte(0xBFC7FF52) renvoie 0.
 *
 * Pour valider ce verrou sans ajouter encore une ROM BIOS complete,
 * on remplace UNIQUEMENT l'instruction LBU ci-dessus par :
 *
 *   addiu v1,zero,0x45
 *
 * La modification n'est appliquee que si les 4 mots correspondent
 * exactement a la signature observee, donc aucun autre overlay n'est
 * modifie par erreur.
 */
static uint32_t g_b59_pal_patch_count = 0u;
static uint32_t g_b59_pal_patch_before = 0u;
static uint32_t g_b59_pal_patch_after = 0u;


/*
 * ============================================================
 * B60 - trace exacte de FUN_80168160
 * ============================================================
 *
 * B59 a prouve que le vrai verrou est maintenant :
 *
 *   80043F44 -> 80168160()
 *   80043F4C <- v0 != 0
 *
 * plusieurs milliers de fois.
 *
 * On capture les registres d'entree/sortie et le code machine
 * reellement charge autour du hot path 801681DC/801681F4.
 */
static uint32_t g_b60_ent_a0 = 0u;
static uint32_t g_b60_ent_a1 = 0u;
static uint32_t g_b60_ent_a2 = 0u;
static uint32_t g_b60_ent_a3 = 0u;
static uint32_t g_b60_ent_s0 = 0u;
static uint32_t g_b60_ent_s1 = 0u;
static uint32_t g_b60_ent_s2 = 0u;
static uint32_t g_b60_ent_s3 = 0u;
static uint32_t g_b60_ent_sp = 0u;
static uint32_t g_b60_ent_ra = 0u;

static uint32_t g_b60_ret_v0 = 0u;
static uint32_t g_b60_ret_s0 = 0u;
static uint32_t g_b60_ret_s1 = 0u;
static uint32_t g_b60_ret_s2 = 0u;
static uint32_t g_b60_ret_s3 = 0u;


/*
 * ============================================================
 * B61 - sortie controlee de l'attente 80168160
 * ============================================================
 *
 * B60 a confirme que FUN_80168160(1) revient des milliers de fois
 * avec v0 == 2, et que 80043E3C boucle tant que v0 != 0.
 *
 * Le code charge montre une table de statuts autour de 801681D0.
 * Le statut 2 est donc un etat de travail/attente, pas un crash.
 *
 * Pendant le bring-up 3DS, START demande une seule fois au pont host
 * de convertir ce retour 2 en 0 AU POINT DE RETOUR 80043F4C.
 *
 * Important :
 *   - on ne saute pas la fonction ;
 *   - elle s'execute normalement une derniere fois ;
 *   - seul son statut de retour est transforme ;
 *   - tout le cleanup original de 80043E3C apres la boucle s'execute.
 *
 * Ce pont n'est actif que pour le tout premier verrou de boot.
 */
static uint32_t g_b61_skip_request = 0u;
static uint32_t g_b61_bridge_count = 0u;
static uint32_t g_b61_old_v0 = 0u;
static uint32_t g_b61_at_return = 0u;


/*
 * ============================================================
 * B62 - HLE ciblé des wrappers libgte Psy-Q
 * ============================================================
 *
 * B61 a franchi la boucle 80168160 puis s'est arrêté dans :
 *
 *   FUN_80087958 -> GTE RTPT
 *
 * L'analyse Psy-Q identifie cette fonction comme RotTransPers4.
 * Le GTE générique n'est pas encore implémenté dans fm_interp /
 * fm_runtime_shim, donc on HLE seulement les wrappers libgte les
 * plus immédiats en conservant leur interface exacte.
 *
 * Pris en charge ici :
 *   80087928  NormalClip
 *   80087958  RotTransPers4
 *   800879D8  RotAverage3
 *   80087A38  RotAverage4
 */
static uint32_t g_b62_hle_nclip = 0u;
static uint32_t g_b62_hle_rtp4 = 0u;
static uint32_t g_b62_hle_ra3 = 0u;
static uint32_t g_b62_hle_ra4 = 0u;
static uint32_t g_b62_last_helper = 0u;
static uint32_t g_b62_last_otz = 0u;


/*
 * ============================================================
 * B65 - latch de la vraie cause d'arret
 * ============================================================
 *
 * La capture B64 finale est revenue a :
 *   RUN:N / CPU:800128CC / RA:0
 * avec tous les compteurs remis a zero.
 *
 * Ce motif correspond a un RESET debug, pas a la fin normale du
 * chargement. On protege donc le reset par une combinaison beaucoup
 * plus stricte et on memorise toute vraie cause d'arret runtime.
 *
 * stop_code :
 *   0 = aucune
 *   1 = saut bas inattendu
 *   2 = BIOS/HLE non gere
 *   3 = retour statique avec PC=0
 *   4 = instruction R3000A non supportee
 *   5 = autre arret runtime natif
 *   9 = reset debug explicite
 */
static uint32_t g_b65_stop_code = 0u;
static uint32_t g_b65_stop_pc = 0u;
static uint32_t g_b65_stop_detail = 0u;
static uint32_t g_b65_stop_ra = 0u;
static uint32_t g_b65_reset_count = 0u;


/*
 * ============================================================
 * B66 - publication de CdlComplete dans l'etat LibCD
 * ============================================================
 *
 * B65 a prouve :
 *   - le dernier chargement est termine ;
 *   - 406C == 1 : FUN_80043E3C est sortie ;
 *   - le runtime reste vivant ;
 *   - le PC boucle dans FUN_80079C8C (CdSync), via VSync
 *     avec RA = 80079D14.
 *
 * Le pont B33 appelait directement le callback utilisateur avec
 * l'evenement 2 (CdlComplete), mais sautait l'etape interne LibCD
 * qui met normalement DAT_80094BEC a 2 et copie le resultat dans
 * DAT_800F7130. CdSync attend donc un evenement qui a deja eu lieu.
 *
 * B66 publie cet etat AVANT d'appeler le vrai callback guest.
 */
static uint32_t g_b66_complete_publish = 0u;
static uint32_t g_b66_last_cmd = 0u;
static uint32_t g_b66_last_sync_before = 0u;
static uint32_t g_b66_last_sync_after = 0u;


/*
 * ============================================================
 * B67 - completion de la file async haut niveau
 * ============================================================
 *
 * B66 a libere CdSync, puis le jeu s'est mis a tourner autour de :
 *
 *   8007ED88
 *      -> 8007B78C(...)   // enqueue async, retourne un request id
 *      -> 8007BDD4(id, out)
 *           -> 8007E888(0)
 *                -> CdSync
 *
 * Notre HLE de 8007B78C court-circuite la vraie file du jeu :
 * la commande hardware se termine bien, MAIS aucun element n'est
 * inscrit dans l'historique 800F7278 consulte par 8007BDD4.
 *
 * Resultat : 8007BDD4 ne voit jamais le statut CdlComplete (2).
 *
 * B67 conserve notre HLE hardware, mais recrée l'API observable :
 *   - genere un request id non nul ;
 *   - le rend "ready" apres retour du vrai callback guest ;
 *   - 8007BDD4 renvoie 2 et recopie les 8 octets de resultat.
 */
static uint32_t g_b67_req_seq = 0u;
static uint32_t g_b67_req_id = 0u;
static uint32_t g_b67_req_pending = 0u;
static uint32_t g_b67_req_ready = 0u;
static uint32_t g_b67_req_status = 0u;

static uint32_t g_b67_poll_calls = 0u;
static uint32_t g_b67_poll_complete = 0u;
static uint32_t g_b67_poll_miss = 0u;
static uint32_t g_b67_last_poll_id = 0u;
static uint32_t g_b67_last_out = 0u;


/*
 * ============================================================
 * B68 - historique des requetes async
 * ============================================================
 *
 * B67 ne conservait qu'UNE requete :
 *   Q id:6 ...
 * alors que 8007BDD4 continuait a sonder l'id 1.
 *
 * Le vrai LibCD garde un historique circulaire (le code guest
 * parcourt jusqu'a 8 entrees). On conserve donc plusieurs IDs,
 * leur statut et leurs 8 octets de resultat.
 */
#define B68_REQ_SLOTS 16u

static uint32_t g_b68_ids[B68_REQ_SLOTS];
static uint8_t  g_b68_status[B68_REQ_SLOTS];
static uint8_t  g_b68_result[B68_REQ_SLOTS][8];

static uint32_t g_b68_return_req_id = 0u;
static uint32_t g_b68_alloc_count = 0u;
static uint32_t g_b68_poll_wait = 0u;
static uint32_t g_b68_last_poll_status = 0u;
static uint32_t g_b68_last_slot = 0u;


/*
 * ============================================================
 * B69 - trace du verrou graphique post-async
 * ============================================================
 *
 * B68 a repare la file async :
 *   POLL all/ok/wait/miss = 3/3/0/0
 *
 * Le CPU est maintenant observe dans FUN_80046750 avec
 * RA=80049600, donc appelee depuis FUN_800495C8.
 *
 * On determine si 80046750 est reellement bloquee dans sa liste
 * de commandes ou si elle revient normalement et est rappelee.
 */
static uint32_t g_b69_495c8_enter = 0u;
static uint32_t g_b69_495c8_ra = 0u;
static uint32_t g_b69_46750_enter = 0u;
static uint32_t g_b69_46750_ra = 0u;
static uint32_t g_b69_after_46750 = 0u;
static uint32_t g_b69_after_494a0 = 0u;
static uint32_t g_b69_after_78588 = 0u;
static uint32_t g_b69_after_47660 = 0u;


/*
 * ============================================================
 * B70 - completion host de la commande graphique type 0x20
 * ============================================================
 *
 * B69 prouve que FUN_80046750 est REELLEMENT bloquee :
 *
 *   46750 ent/ret = 1/0
 *   queue count   = 2
 *   head type     = 0x20
 *
 * Le pseudo-C de FUN_80046750 est sans ambiguite :
 *
 *   case 0x20:
 *       if (*(ctx + entry + 0x90) == 0x20) {
 *           retire l'entree;
 *       }
 *       // sinon la boucle recommence sur LA MEME entree
 *
 * Sur PS1, ce champ est termine de facon asynchrone par le pipeline
 * GPU/DMA. Notre runtime rend bien la VRAM, mais ne publie pas encore
 * cette completion dans la file haut niveau du jeu.
 *
 * Le bridge ne touche QUE :
 *   - FUN_80046750 active;
 *   - tete de file type 0x20;
 *   - marqueur +0x10 de l'entree different de 0x20.
 *
 * Il transforme alors ce marqueur en 0x20, equivalent au signal de
 * completion attendu par le code original. FUN_80046750 retire elle-
 * meme l'entree et poursuit son cleanup normal.
 */
static uint32_t g_b70_ready_bridge = 0u;
static uint32_t g_b70_last_ctx = 0u;
static uint32_t g_b70_last_count = 0u;
static uint32_t g_b70_last_type = 0u;
static uint32_t g_b70_last_marker_before = 0u;
static uint32_t g_b70_last_marker_after = 0u;
static uint32_t g_b70_entry1_type = 0u;
static uint32_t g_b70_entry1_marker = 0u;

static uint32_t g_b32_43e_returned = 0;
static uint32_t g_b32_43e_return_frame = 0;

/*
 * B33 - pont des callbacks asynchrones LibCD.
 *
 * B32 a confirme que FUN_8007E968 n'est jamais atteinte. Le chemin
 * reel passe d'abord par FUN_8007B78C / FUN_8007BA00 qui mettent une
 * commande CD en file et attendent un callback. Notre backend host ne
 * livre pas encore cet evenement. On execute donc le vrai callback
 * guest avec l'evenement CdlComplete (2), puis on reprend exactement
 * au RA du caller de la fonction d'enqueue.
 */
static const uint32_t g_b33_cb_sentinel = 0x8000FFC0u;
static const uint32_t g_b33_result_scratch = 0x8009C4B4u;
static uint32_t g_b33_cb_active = 0;
static uint32_t g_b33_cb_resume = 0;
static uint32_t g_b33_cb_addr = 0;
static uint32_t g_b33_cb_cmd = 0;
static uint32_t g_b33_async_calls = 0;
static uint32_t g_b33_raw_calls = 0;
static uint32_t g_b33_cb_started = 0;
static uint32_t g_b33_cb_done = 0;
static uint32_t g_b33_cb_skipped = 0;
static uint32_t g_b33_last_params = 0;
static uint32_t g_b33_last_ctx = 0;

/* B36: les callbacks LibCD sont asynchrones sur PS1. Leur execution ne
 * doit donc pas detruire le contexte CPU interrompu. */
static uint32_t g_b33_saved_gpr[32];
static uint32_t g_b33_ctx_saved = 0;
static uint32_t g_b33_ctx_restored = 0;

/*
 * B34 - correction de la signature de FUN_8007BA00 et livraison
 * du vrai evenement CdlDataReady au callback 80013B44.
 *
 * L'analyse du SLES PAL montre l'appel exact :
 *   a0 = 0xA0 (mode/flags)
 *   a1 = params
 *   a2 = commande CD (0x06 = ReadN)
 *   a3 = callback de completion (80013FBC)
 *
 * B33 prenait a0 pour la commande, d'ou cmd=A0 et aucun ReadN host.
 */
static const uint32_t g_b34_ready_cb = 0x80013B44u;
static const uint32_t g_b34_ready_sentinel = 0x8000FFB0u;
static uint32_t g_b34_last_mode = 0;
static uint32_t g_b34_last_command = 0;
static uint32_t g_b34_ready_pending = 0;
static uint32_t g_b34_ready_active = 0;
static uint32_t g_b34_ready_resume = 0;
static uint32_t g_b34_ready_started = 0;
static uint32_t g_b34_ready_done = 0;
static uint32_t g_b34_ready_arm_frame = 0;
static uint32_t g_b34_ready_req = 0;
static uint32_t g_b34_ready_before = 0;
static uint32_t g_b34_ready_after = 0;

/* B36: contexte exact interrompu par CdlDataReady. */
static uint32_t g_b34_ready_saved_gpr[32];
static uint32_t g_b34_ready_saved_pc = 0;
static uint32_t g_b34_ready_saved_ra = 0;
static uint32_t g_b34_ready_ctx_saved = 0;
static uint32_t g_b34_ready_ctx_restored = 0;

/*
 * B35 - finalisation CD via le vrai cleanup guest FUN_800143D4.
 *
 * B34 livre correctement CdlDataReady, FUN_8007E968 lit le dernier
 * secteur depuis disc.bin et la requete passe de 0x800 a 0 octet.
 * Pourtant 80013700 reste bloque parce que C460 conserve le bit 0x10.
 * Sur le SLES PAL, FUN_800143D4 est le cleanup du service CD qui
 * conserve seulement les bits 0x20/0x40 de C460. On execute donc
 * cette VRAIE routine guest apres le dernier DataReady, au lieu de
 * modifier C460 a la main.
 */
static const uint32_t g_b35_finalizer_addr = 0x800143D4u;
static const uint32_t g_b35_finalizer_sentinel = 0x8000FFA0u;
static uint32_t g_b35_finalizer_active = 0;
static uint32_t g_b35_finalizer_resume = 0;
static uint32_t g_b35_finalizer_started = 0;
static uint32_t g_b35_finalizer_done = 0;
static uint32_t g_b35_c460_before = 0;
static uint32_t g_b35_c460_after = 0;

/* B36: le cleanup guest est appele comme une pseudo-interruption.
 * Conserver/restaurer tout le contexte afin de reprendre exactement
 * l'instruction qui tournait avant CdlDataReady. */
static uint32_t g_b35_saved_gpr[32];
static uint32_t g_b35_saved_pc = 0;
static uint32_t g_b35_saved_ra = 0;
static uint32_t g_b35_ctx_saved = 0;
static uint32_t g_b35_ctx_restored = 0;

/*
 * B37 - GPU DMA2 sync bridge.
 *
 * Le host traite DMA2 de facon synchrone. Si le guest arrive dans
 * FUN_800819E0 et voit encore CHCR.START/BUSY (bit 24), ce bit est
 * stale pour notre modele : le transfert GP0 a deja ete consomme.
 * On le relache donc comme le ferait le hardware en fin de DMA.
 *
 * 80081A90 lit 0x1F8010A8 (DMA2 CHCR) et attend bit24 == 0.
 * 80081AC0 attend ensuite GPUSTAT bit26 == 1.
 */
static uint32_t g_b37_dma_wait_hits = 0;
static uint32_t g_b37_dma_forced_clear = 0;
static uint32_t g_b37_last_chcr_before = 0;
static uint32_t g_b37_last_chcr_after = 0;
static uint32_t g_b37_last_gpustat = 0;
static uint32_t g_b37_ring_write = 0;
static uint32_t g_b37_ring_read = 0;

/*
 * B71 - sortie robuste de la boucle DMA2 observee apres START
 * sur l'ecran titre.
 *
 * B37 savait deja relacher CHCR.START/BUSY. Mais lorsque le CPU
 * revient comme bloc interprete directement sur 80081A90, il peut
 * rester sur le basic-block de polling sans repasser par le chemin
 * normal assez vite. Une fois CHCR effectivement relache, B71 place
 * le PC au debut du polling GPUSTAT suivant (80081AC0), ce qui est
 * exactement le chemin "DMA termine" de FUN_800819E0.
 */
static uint32_t g_b71_dma_loop_escape = 0u;
static uint32_t g_b71_last_escape_from = 0u;
static uint32_t g_b71_last_escape_to = 0u;


/*
 * ============================================================
 * B72 - START titre : impulsion 10 frames + traces latchees
 * ============================================================
 *
 * Le probe PC valide envoie START actif-bas 0xFFF7 pendant
 * exactement 10 frames. Sur 3DS un appui bref peut ne durer qu'une
 * frame hote et etre manque par la chaine input/VBlank guest.
 *
 * Une fois le titre reel atteint (bridge G20 + retour 46750 + STR
 * termine), tout front physique START est donc etire a 10 frames
 * PS1 : psx_pressed bit 3 == 0x0008.
 *
 * Les valeurs sont aussi latchees pour rester visibles APRES que
 * l'utilisateur a relache START.
 */
static uint32_t g_b72_start_down_count = 0u;
static uint32_t g_b72_start_hold_frames = 0u;
static uint32_t g_b72_start_last_frame = 0u;
static uint32_t g_b72_start_last_host_held = 0u;
static uint32_t g_b72_start_last_host_down = 0u;
static uint32_t g_b72_start_last_psx = 0u;

static uint32_t g_b72_guest_raw_latched = 0u;
static uint32_t g_b72_guest_held_latched = 0u;
static uint32_t g_b72_guest_edge_latched = 0u;
static uint32_t g_b72_guest_rep_latched = 0u;
static uint32_t g_b72_guest_nonzero_frame = 0u;
static uint32_t g_b72_edge8_hits = 0u;
static uint32_t g_b72_edge8_last_frame = 0u;

/*
 * Reference du runtime PC quand le menu FR est visible :
 *   PC ~= 80041C88
 *   RA ~= 80040BE0
 *
 * 80040B48 est la routine de rendu qui conduit a ce chemin.
 */
static uint32_t g_b72_hit_40b48 = 0u;
static uint32_t g_b72_hit_41c88 = 0u;
static uint32_t g_b72_last_40b48_ra = 0u;


/*
 * ============================================================
 * B73 - pont de transition titre -> etat 8 (menu SU)
 * ============================================================
 *
 * B72 prouve que START arrive bien jusqu'au guest :
 *   8009C710 contient 0x0008
 *   et l'edge START est observe.
 *
 * La reference PC/Ghidra montre ensuite que l'etat resident 8
 * (FUN_8002D75C) charge M:\mrg\SU\SU.mrg puis appelle l'overlay
 * de menu a 0x8018001C / 0x80180390.
 *
 * B73 ne remplace pas ce code : il force uniquement la selection
 * de l'etat 8 apres l'impulsion START, afin que le vrai chargeur
 * CD et le vrai overlay prennent ensuite la main.
 */
static uint32_t g_b73_menu_force_request = 0u;
static uint32_t g_b73_menu_force_count = 0u;
static uint32_t g_b73_menu_force_frame = 0u;

static uint32_t g_b73_state60a_before = 0u;
static uint32_t g_b73_state60a_after = 0u;
static uint32_t g_b73_state60d_before = 0u;
static uint32_t g_b73_state60d_after = 0u;

static uint32_t g_b73_hit_state8 = 0u;
static uint32_t g_b73_hit_load_su = 0u;
static uint32_t g_b73_hit_menu_init = 0u;
static uint32_t g_b73_hit_menu_update = 0u;
static uint32_t g_b73_hit_menu_destroy = 0u;


/*
 * ============================================================
 * B74 - trace du rendu reel du menu SU
 * ============================================================
 *
 * B73 prouve que :
 *   - SU.mrg est charge ;
 *   - 8018001C (init) est execute ;
 *   - 80180390 (update) tourne en continu.
 *
 * Pourtant l'ecran affiche encore le titre.
 *
 * Le menu installe DAT_8009C898 = 0x80180B4C. Cette fonction
 * doit etre appelee par FUN_80012F70 a chaque tick de service.
 * B74 verifie donc ce chemin et expose aussi l'etat des objets
 * UI crees par 8018001C.
 */
static uint32_t g_b74_hit_12f70 = 0u;
static uint32_t g_b74_hit_menu_draw_cb = 0u;
static uint32_t g_b74_last_menu_draw_ra = 0u;
static uint32_t g_b74_last_12f70_ra = 0u;


/*
 * ============================================================
 * B75 - completion de l'animation d'entree du menu SU
 * ============================================================
 *
 * B74 prouve que le menu est reellement charge ET dessine :
 *
 *   C898 = 80180B4C
 *   callback draw appele des centaines de fois
 *   objets menu valides en RAM
 *
 * Mais les objets restent figes dans l'etat initial :
 *
 *   OBJ0 x=-160  from=-160  to=160  timer=16  flags=0x0088
 *   OBJ5 x= 480  from= 480  to=160  timer=16
 *
 * Le pseudo-C de 80180390 montre que l'animation normale doit :
 *   - decrementer +0x60 de 16 vers 0 ;
 *   - amener +0x30 vers +0x38 ;
 *   - poser le bit 0x40 sur le groupe visible ;
 *   - remettre DAT_801847C5 a 0 a la fin.
 *
 * Cette branche ne progresse pas dans notre runtime actuel.
 * B75 ne dessine rien artificiellement : il finalise uniquement
 * l'animation d'entree, puis rend la main au VRAI callback menu.
 */
static uint32_t g_b75_menu_entrance_bridge = 0u;
static uint32_t g_b75_menu_entrance_frame = 0u;
static uint32_t g_b75_last_c0 = 0u;
static uint32_t g_b75_last_c5_before = 0u;
static uint32_t g_b75_last_c5_after = 0u;
static uint32_t g_b75_objects_settled = 0u;


/*
 * ============================================================
 * B76 - ressource graphique SU a 0x801AF800
 * ============================================================
 *
 * FUN_8006B350 charge 0x73 secteurs (0x39800 octets) de SU.MRG :
 *
 *   +0x00000 : 0x20000 -> tampon
 *   +0x20000 : 0x10000 -> tampon
 *   +0x30000 : 0x01000 -> 0x801DD000
 *   +0x31000 : 0x08000 -> 0x80180000 (code overlay)
 *   +0x39000 : 0x00800 -> 0x801AF800 (ressource sprites)
 *
 * Le code du menu utilise 0x801AF800 comme ressource de tous ses
 * objets. Si cette derniere etape n'a pas ete publiee par notre
 * chemin CD asynchrone, FUN_800418C0 voit un bloc sprite vide et
 * retourne avant d'emettre les primitives du menu.
 *
 * B76 ne force le secteur que si les 64 premiers octets de
 * 0x801AF800 sont TOUS nuls.
 */
static uint32_t g_b76_resource_bridge = 0u;
static uint32_t g_b76_resource_attempt = 0u;
static int32_t  g_b76_resource_rc = 0;
static uint32_t g_b76_su_lba = 0u;
static uint32_t g_b76_su_size = 0u;
static uint32_t g_b76_pre_nonzero = 0u;
static uint32_t g_b76_post_nonzero = 0u;
static uint32_t g_b76_objects_rearmed = 0u;
static uint32_t g_b76_bridge_frame = 0u;

static uint32_t g_b76_418c0_menu_hits = 0u;
static uint32_t g_b76_last_menu_obj = 0u;

static uint8_t g_b76_sector[2048];


/*
 * ============================================================
 * B77 - prouver ce que produit UN objet menu dans le GPU
 * ============================================================
 *
 * B76 montre :
 *   - 0x801AF800 est DEJA rempli (32/64 octets non nuls) ;
 *   - O0 a un pointeur sprite valide 0x801AF8AA, count=1 ;
 *   - FUN_800418C0 est appelee pour les objets menu ;
 *   - 80041BB4 est atteint.
 *
 * Donc la ressource SU n'est pas le verrou.
 *
 * B77 associe maintenant chaque appel 800418C0 d'un objet SU au
 * serial GPU avant/apres le call. On saura directement :
 *
 *   delta = 0  -> renderer objet ne produit aucune commande GPU
 *   delta > 0  -> primitives bien envoyees au GPU
 *
 * On memorise aussi les 3 dernieres primitives DRAW apres le call.
 */
static uint32_t g_b77_menu_call_pending = 0u;
static uint32_t g_b77_menu_call_obj = 0u;
static uint32_t g_b77_menu_call_index = 0xFFFFFFFFu;

static uint32_t g_b77_menu_calls = 0u;
static uint32_t g_b77_menu_returns = 0u;
static uint32_t g_b77_gpu_before = 0u;
static uint32_t g_b77_gpu_after = 0u;
static uint32_t g_b77_gpu_delta = 0u;
static uint32_t g_b77_gpu_delta_nonzero = 0u;
static uint32_t g_b77_gpu_delta_zero = 0u;
static uint32_t g_b77_gpu_delta_max = 0u;

static uint8_t  g_b77_op[3];
static uint32_t g_b77_cmd0[3];
static uint32_t g_b77_cmd1[3];
static uint32_t g_b77_cmd2[3];
static uint16_t g_b77_tp[3];
static int32_t  g_b77_offx[3];
static int32_t  g_b77_offy[3];


/*
 * ============================================================
 * B78 - menu -> packet allocator -> Ordering Table
 * ============================================================
 *
 * Correction importante de l'interpretation B77 :
 *
 * FUN_800418C0 ne pousse PAS directement ses primitives dans GP0.
 * Elle construit des paquets dans le buffer courant DAT_800FF5C4
 * puis FUN_80084018 les insere dans l'Ordering Table.
 *
 * Le "GPU delta = 0" de B77 n'etait donc pas une preuve d'absence
 * de rendu. De plus le serial B44 est un watcher cible et non un
 * compteur global.
 *
 * B78 suit le vrai chemin :
 *
 *   objet SU
 *     -> FUN_800418C0
 *     -> FUN_800424B8
 *     -> FUN_80084018
 *     -> packet buffer DAT_800FF5C4
 *     -> bucket OT
 *     -> DrawOTag / DMA2 plus tard
 */
static uint32_t g_b78_pending = 0u;
static uint32_t g_b78_obj = 0u;
static uint32_t g_b78_obj_index = 0xFFFFFFFFu;

static uint32_t g_b78_layer = 0u;
static uint32_t g_b78_ctx = 0u;
static uint32_t g_b78_z = 0u;
static int32_t  g_b78_zbase = 0;
static int32_t  g_b78_bucket_index = -1;
static uint32_t g_b78_ot_base = 0u;
static uint32_t g_b78_bucket = 0u;

static uint32_t g_b78_alloc_before = 0u;
static uint32_t g_b78_alloc_after = 0u;
static uint32_t g_b78_alloc_delta = 0u;

static uint32_t g_b78_bucket_before = 0u;
static uint32_t g_b78_bucket_after = 0u;

static uint32_t g_b78_calls = 0u;
static uint32_t g_b78_returns = 0u;
static uint32_t g_b78_alloc_advanced = 0u;
static uint32_t g_b78_bucket_changed = 0u;
static uint32_t g_b78_bucket_points_packet = 0u;

static uint32_t g_b78_addprim_hits = 0u;
static uint32_t g_b78_addprim_packet = 0u;
static uint32_t g_b78_addprim_ctx = 0u;
static uint32_t g_b78_addprim_z = 0u;
static uint32_t g_b78_addprim_words = 0u;

static uint32_t g_b78_packet[8];

static uint32_t g_b78_drawotag_hits = 0u;
static uint32_t g_b78_drawotag_last_a0 = 0u;
static uint32_t g_b78_drawotagenv_hits = 0u;

static uint32_t g_b78_dma_wait_samples = 0u;
static uint32_t g_b78_dma_madr = 0u;
static uint32_t g_b78_dma_bcr = 0u;
static uint32_t g_b78_dma_chcr = 0u;


/*
 * ============================================================
 * B79 - soumission directe des packets produits par le menu
 * ============================================================
 *
 * B78 a prouve que chaque objet SU :
 *   - alloue un packet GPU valide dans DAT_800FF5C4 ;
 *   - avance le packet allocator ;
 *   - modifie son bucket dans l'Ordering Table.
 *
 * Exemple observe :
 *   header : 0509CA58
 *   GP0    : E1000228
 *            64808080
 *            002A006C
 *            3428A060
 *            00200068
 *
 * Le verrou est donc apres la construction du packet.
 *
 * B79 prend UNIQUEMENT les packets nouvellement alloues par les
 * 11 objets menu et envoie leurs mots GP0 directement au parser
 * GPU, sans attendre GsSortOt / DrawOTag / DMA2.
 *
 * Aucun packet n'est fabrique : ce sont exactement les mots
 * produits par le code original.
 *
 * Si le menu devient visible, le bug est confirme dans :
 *      OT -> DrawOTag -> DMA2
 * Si rien ne change, on investiguera texture/CLUT/VRAM.
 */
static uint32_t g_b79_direct_calls = 0u;
static uint32_t g_b79_direct_packets = 0u;
static uint32_t g_b79_direct_words = 0u;
static uint32_t g_b79_direct_bad = 0u;

static uint32_t g_b79_last_header = 0u;
static uint32_t g_b79_last_packet = 0u;
static uint32_t g_b79_last_count = 0u;
static uint32_t g_b79_last_opcode = 0u;

static uint32_t g_b79_last_cmd0 = 0u;
static uint32_t g_b79_last_cmd1 = 0u;
static uint32_t g_b79_last_cmd2 = 0u;
static uint32_t g_b79_last_cmd3 = 0u;
static uint32_t g_b79_last_cmd4 = 0u;


/*
 * ============================================================
 * B80 - corriger l'ordre des deux octets du pad PS1
 * ============================================================
 *
 * FUN_8003CE34 du jeu ne depose pas le mot boutons dans l'ordre
 * "conventionnel" d'un uint16_t PS1.
 *
 * Le vrai chemin fait :
 *
 *   CONCAT11(button_byte_0, button_byte_1) ^ 0xFFFF
 *
 * Ce qui revient, vu depuis DAT_8009C70C, a inverser les deux
 * octets du masque 16 bits :
 *
 *   PS1 logique       DAT_8009C70C
 *   UP    0x0010  ->  0x1000
 *   RIGHT 0x0020  ->  0x2000
 *   DOWN  0x0040  ->  0x4000
 *   LEFT  0x0080  ->  0x8000
 *
 *   TRI   0x1000  ->  0x0010
 *   CIRC  0x2000  ->  0x0020
 *   CROSS 0x4000  ->  0x0040
 *   SQUARE0x8000  ->  0x0080
 *
 * Cela explique exactement les masques du menu SU :
 *
 *   DAT_8009C728 & 0x5000  -> UP/DOWN
 *   DAT_8009C72C & 0x8E0   -> boutons d'action
 *
 * B58 injectait jusqu'ici le mot non-swappe.
 */
static uint32_t g_b80_down_hits = 0u;
static uint32_t g_b80_up_hits = 0u;
static uint32_t g_b80_cross_hits = 0u;
static uint32_t g_b80_circle_hits = 0u;

static uint16_t g_b80_last_native = 0u;
static uint16_t g_b80_last_guest = 0u;

static uint32_t g_b80_sel_changes = 0u;
static uint32_t g_b80_last_sel = 0xFFFFFFFFu;
static uint32_t g_b80_last_sel_frame = 0u;


/*
 * ============================================================
 * B81 - latch entree exactement a l'entree de 80180390
 * ============================================================
 *
 * B80 prouve que les boutons 3DS arrivent bien cote hote, mais
 * le menu n'observe aucun changement de selection.
 *
 * Le menu SU n'est execute qu'environ une fois toutes les
 * plusieurs frames hote. Une impulsion pad tres courte peut donc
 * etre calculee puis effacee entre deux passages dans 80180390.
 *
 * B81 conserve chaque front hote, puis injecte son masque guest
 * EXACTEMENT au moment ou le vrai update menu 80180390 commence.
 * L'impulsion reste visible pendant un update menu complet puis
 * est nettoyee au passage suivant.
 *
 * Ce bridge ne remplace aucune logique de menu : il corrige
 * uniquement le probleme de cadence/latch d'entree du bring-up.
 */
static uint32_t g_b81_pending_mask = 0u;
static uint32_t g_b81_cleanup_mask = 0u;

static uint32_t g_b81_armed = 0u;
static uint32_t g_b81_injected = 0u;
static uint32_t g_b81_cleaned = 0u;

static uint32_t g_b81_last_mask = 0u;
static uint32_t g_b81_last_update = 0u;
static uint32_t g_b81_last_frame = 0u;

static uint32_t g_b81_edge_before = 0u;
static uint32_t g_b81_repeat_before = 0u;
static uint32_t g_b81_held_before = 0u;

static uint32_t g_b81_edge_after = 0u;
static uint32_t g_b81_repeat_after = 0u;
static uint32_t g_b81_held_after = 0u;

static uint32_t g_b81_sel_before = 0u;


/*
 * ============================================================
 * B82 - identifier le garde qui bloque 80180390
 * ============================================================
 *
 * B81 a prouve :
 *   - le front DOWN est capture ;
 *   - 0x4000 est present dans H/E/R a l'entree de 80180390 ;
 *   - la selection reste pourtant a 0.
 *
 * Le pseudo-C du menu montre quatre familles de gardes AVANT la
 * navigation :
 *
 *   C7/C8/C9/C6 != 0         -> sous-dialogue actif
 *   C4 != 0                  -> transition interne
 *   FX=DAT_8018478C actif    -> animation overlay prioritaire
 *   C5 != 0                  -> animation d'entree/sortie
 *
 * B82 photographie ces gardes au moment exact de l'injection et
 * mesure la selection au passage menu suivant.
 */
static uint32_t g_b82_gate_samples = 0u;

static uint32_t g_b82_c0 = 0u;
static uint32_t g_b82_c1 = 0u;
static uint32_t g_b82_c2 = 0u;
static int32_t  g_b82_c3 = 0;
static int32_t  g_b82_c4 = 0;
static uint32_t g_b82_c5 = 0u;
static uint32_t g_b82_c6 = 0u;
static uint32_t g_b82_c7 = 0u;
static uint32_t g_b82_c8 = 0u;
static uint32_t g_b82_c9 = 0u;

static uint32_t g_b82_fx_ptr = 0u;
static uint32_t g_b82_fx_flags = 0u;
static int32_t  g_b82_fx_timer = 0;
static int32_t  g_b82_fx_pos = 0;
static uint32_t g_b82_fx_wait = 0u;
static uint32_t g_b82_fx_rgb = 0u;

static uint32_t g_b82_block_dialog = 0u;
static uint32_t g_b82_block_c4 = 0u;
static uint32_t g_b82_block_fx = 0u;
static uint32_t g_b82_block_c5 = 0u;

static uint32_t g_b82_nav_seen = 0u;
static uint32_t g_b82_action_seen = 0u;

static uint32_t g_b82_result_samples = 0u;
static uint32_t g_b82_sel_after = 0u;
static int32_t  g_b82_sel_delta = 0;
static uint32_t g_b82_last_result_update = 0u;


/*
 * ============================================================
 * B83 - START exact au menu pour liberer l'objet FX
 * ============================================================
 *
 * B82 a identifie le verrou :
 *
 *   BLOCK D/C4/FX/C5 = 0/0/1/0
 *   FX flags          = 0x00F8
 *
 * Dans seed_80180390, tant que FX.flags & 0x40 != 0 :
 *   - UP/DOWN et les boutons menu sont ignores ;
 *   - seul DAT_8009C72C & 0x0800 est accepte ;
 *   - ce bit correspond a START dans le format guest byte-swap.
 *
 * Le START titre B72 etait etire sur 10 frames hote, mais le menu
 * ne tourne qu'environ toutes les 20-30 frames hote. Il peut donc
 * rater l'impulsion.
 *
 * B83 ajoute START au latch B81 : un front START hote est conserve
 * jusqu'a l'entree exacte de 80180390.
 */
static uint32_t g_b83_start_armed = 0u;
static uint32_t g_b83_start_injected = 0u;
static uint32_t g_b83_fx_cleared = 0u;
static uint32_t g_b83_fx_flags_after = 0u;
static uint32_t g_b83_c4_after = 0u;
static uint32_t g_b83_c5_after = 0u;


/*
 * ============================================================
 * B84 - vitesse guest + affichage stable
 * ============================================================
 *
 * Deux causes distinctes expliquent le comportement actuel :
 *
 * 1) R3000A fallback volontairement bride par B16 :
 *      128 instructions max par passage
 *      ~5 ms de tranche guest
 *      break immediat sur FM_INTERP_BUDGET
 *
 *    Les overlays 0x801xxxxx (dont SU) sont presque entierement
 *    interpretes. Le jeu avance donc beaucoup plus lentement que
 *    l'ecran 3DS : un seul update guest peut demander 10-20 frames.
 *
 * 2) La VRAM est presentee a CHAQUE frame 3DS pendant que le guest
 *    construit encore son image. Avec le bridge direct B79, on voit
 *    donc parfois une frame partiellement dessinee -> clignotement.
 *
 * B84 :
 *   - augmente le budget de l'interpreteur ;
 *   - continue apres FM_INTERP_BUDGET tant que la tranche temps
 *     n'est pas consommee ;
 *   - autorise ~12 ms de guest par frame 3DS ;
 *   - latch le framebuffer uniquement apres une nouvelle transaction
 *     DMA2 observee, puis affiche cette copie stable entre deux DMA.
 */
static uint32_t g_b84_latch_valid = 0u;
static uint32_t g_b84_latch_count = 0u;
static uint32_t g_b84_last_dma_sample = 0u;
static uint32_t g_b84_latch_x = 0u;
static uint32_t g_b84_latch_y = 0u;

static uint32_t g_b84_budget_yields = 0u;
static uint32_t g_b84_budget_continues = 0u;


/*
 * ============================================================
 * B85 - vraie frontière de frame guest
 * ============================================================
 *
 * B84 avait encore deux défauts :
 *
 * 1) Le code ARM recompilé s'arrêtait à FM_STOP_BUDGET et attendait
 *    la frame hôte suivante. C'était encore un énorme multiplicateur
 *    de lenteur, même si l'interpréteur R3000A avait été accéléré.
 *
 * 2) Le framebuffer était latché sur les attentes DMA2. Or plusieurs
 *    DMA peuvent appartenir à UNE SEULE image : on capturait parfois
 *    une image incomplète -> clignotement.
 *
 * En DIRECT-2DF, le retour à g_direct2df_sentinel marque au contraire
 * la fin complète d'une itération de la vraie machine d'état.
 *
 * B85 :
 *   - reprend immédiatement après FM_STOP_BUDGET ;
 *   - augmente le budget natif direct ;
 *   - garde une tranche temps bornée ;
 *   - ne publie une nouvelle image qu'après un retour complet à la
 *     sentinelle DIRECT-2DF.
 */
static uint32_t g_b85_probe_budget_continues = 0u;
static uint32_t g_b85_guest_frames = 0u;
static uint32_t g_b85_last_latched_guest_frame = 0u;
static uint32_t g_b85_sentinel_hits = 0u;


/*
 * ============================================================
 * B86 - presentation stable et moins couteuse
 * ============================================================
 *
 * La capture B85 montre :
 *
 *   GFRAME done:0 / sentinel:0
 *   LATCH n:105
 *   DMA:186
 *
 * Donc, au logo Konami, DIRECT-2DF n'est PAS encore actif.
 * B85 latchait encore l'image sur les DMA2 : plusieurs captures
 * pouvaient donc avoir lieu pendant UNE seule image PS1.
 *
 * B86 change la politique :
 *
 *   AVANT DIRECT-2DF :
 *      latch seulement quand GP1(05h) change la page affichee
 *      (display_x / display_y), jamais sur chaque DMA.
 *
 *   APRES DIRECT-2DF :
 *      latch uniquement a la fin d'une frame guest complete
 *      (retour sentinelle B85).
 *
 * En plus, on ne reconvertit plus les 320x240 pixels vers le
 * framebuffer 3DS a chaque VBlank. On ne fait le present que
 * lorsqu'une nouvelle image stable a ete latchée.
 *
 * Le buffer composite contient bien 256 lignes, car le presenter
 * historique peut lire y+8..247 en mode crop.
 */
static uint32_t g_b86_last_display_x = 0xFFFFFFFFu;
static uint32_t g_b86_last_display_y = 0xFFFFFFFFu;
static uint32_t g_b86_display_changes = 0u;
static uint32_t g_b86_present_dirty = 0u;
static uint32_t g_b86_present_count = 0u;
static uint32_t g_b86_skipped_presents = 0u;

/*
 * ============================================================
 * B131 - dirty-frame pacing
 * ============================================================
 *
 * B130 showed far more host presents than real menu draws. Re-presenting
 * the same latched PS1 image wastes RGB555 conversion + cache flush + swap
 * and can worsen frame pacing. B131 swaps only when a new image has been
 * latched; otherwise the current frontbuffer simply remains visible.
 */
static uint32_t g_b131_swap_count = 0u;
static uint32_t g_b131_skip_count = 0u;
static uint32_t g_b131_dirty_present_count = 0u;

/*
 * ============================================================
 * B135.7 - VSync-boundary latch for DIRECT-2DF gameplay
 * ============================================================
 *
 * 8002DF60 is the game's persistent main state-machine loop; it is not
 * a normal once-per-frame function. The old B85/B131 rule waited for the
 * artificial DIRECT-2DF sentinel before latching a new host frame. On the
 * Palace map that sentinel is reached only rarely, so Azahar reports ~1-2
 * App FPS even though the guest itself keeps running near full speed.
 *
 * A VSync wait is the natural stable boundary: by the time the game asks
 * for the next VBlank, all GP0 work submitted since the previous latch is
 * already in software VRAM. Latch once there when GP0 actually changed.
 */
static uint64_t g_b1357_last_latched_gp0 = 0u;
static uint32_t g_b1357_vsync_latches = 0u;
static uint32_t g_b1357_display_latches = 0u;

/*
 * B135.8 - one-loop pulse emitted when the VSync HLE actually RETURNS.
 * B135.7 looked at g_vsync_wait_active during presentation, but that flag is
 * cleared inside the HLE before main.c reaches the latch stage. Therefore
 * VSL stayed at zero even though gameplay was synchronizing correctly.
 */
static uint32_t g_b1358_vsync_completed = 0u;
static uint32_t g_b1358_vsync_completions = 0u;

/*
 * B135.9 - compact performance deltas over the 120-loop debug interval.
 * These counters are deliberately host-side and are not part of quick-state.
 */
static uint32_t g_b1359_prev_swap = 0u;
static uint32_t g_b1359_prev_vsc = 0u;
static uint64_t g_b1359_prev_gp0 = 0u;
static uint64_t g_b13513_prev_pixels = 0u;

/* B135.19 - interval counters for the continuous map interpreter. */
static uint64_t g_b13519_prev_region_chunks = 0u;
static uint64_t g_b13519_prev_region_instructions = 0u;

/*
 * B135.14 - resident dispatch chaining for the Pharaoh map renderer
 * 800342B0..80034D2F.
 */
static uint32_t g_b13514_chain_entries = 0u;
static uint64_t g_b13514_chain_dispatches = 0u;
static uint32_t g_b13514_chain_max = 0u;

/*
 * B135.16 - sampled heavy hitters for the PC that immediately BREAKS the
 * chain. B135.15 still reports max=1, so the next PC after almost every
 * map dispatch lives outside our two chained regions.
 *
 * Sample only 1/16 exits to keep the diagnostic overhead negligible.
 */
static uint32_t g_b13516_exit_pc[4] = {0u};
static uint32_t g_b13516_exit_weight[4] = {0u};
static uint32_t g_b13516_exit_samples = 0u;
static uint32_t g_b13516_exit_seen = 0u;

/*
 * B135.17 - fast R3000A block chaining for the resident Pharaoh-map code.
 *
 * B135.16 proved the dominant chain exits are 034A14 / 034BE4 / 035988:
 * all are INSIDE the map region, but they are labels/basic blocks that the
 * static PSXRecomp dispatcher does not expose as function entries.
 *
 * Returning to main.c after every interpreted basic block is therefore pure
 * overhead. Chain those blocks locally until the PC leaves the map region or
 * the host 12 ms slice expires.
 */
static uint32_t g_b13517_interp_entries = 0u;
static uint64_t g_b13517_interp_blocks = 0u;
static uint32_t g_b13517_interp_max = 0u;
static uint32_t g_b13517_interp_time_yields = 0u;

/*
 * B135.18 - when a host loop already consumed a full 60 Hz frame budget,
 * waiting for the NEXT 3DS VBlank only throws away more CPU time.
 */
static uint32_t g_b13518_late_vblank_skips = 0u;

/*
 * B135.19 - total MIPS instructions retired by the continuous resident-map
 * interpreter. Existing B135.17 "blocks" counter is reused as region chunks.
 */
static uint64_t g_b13519_region_instructions = 0u;

/*
 * B135.25 - profile which internal map continuations still fall back to the
 * R3000A interpreter.  Weight by retired instructions, not only hit count,
 * so one rare but very expensive continuation is visible immediately.
 */
static uint32_t g_b13525_interp_pc[8] = {0u};
static uint32_t g_b13525_interp_hits[8] = {0u};
static uint64_t g_b13525_interp_ins[8] = {0u};

static void b13525_note_interp_entry(
    uint32_t pc,
    uint64_t instructions
)
{
    pc &= 0x1FFFFFFFu;

    unsigned empty = 8u;
    unsigned lightest = 0u;

    for (unsigned i = 0u; i < 8u; ++i)
    {
        if (g_b13525_interp_pc[i] == pc)
        {
            ++g_b13525_interp_hits[i];
            g_b13525_interp_ins[i] += instructions;
            return;
        }

        if (g_b13525_interp_pc[i] == 0u && empty == 8u)
        {
            empty = i;
        }

        if (g_b13525_interp_ins[i] < g_b13525_interp_ins[lightest])
        {
            lightest = i;
        }
    }

    unsigned slot = empty != 8u ? empty : lightest;

    g_b13525_interp_pc[slot] = pc;
    g_b13525_interp_hits[slot] = 1u;
    g_b13525_interp_ins[slot] = instructions;
}


static int b13517_is_map_interp_pc(uint32_t pc)
{
    uint32_t phys = pc & 0x1FFFFFFFu;

    /*
     * 34D30 is a real compiled function entry. Hand it back to the native
     * dispatcher instead of interpreting the whole function from its entry.
     * Internal labels inside it (e.g. 35988) remain eligible.
     */
    if (phys == 0x00034D30u)
    {
        return 0;
    }

    return
        phys >= 0x000342B0u
        &&
        phys < 0x00035AC8u;
}


static void b13516_note_chain_exit(uint32_t pc)
{
    ++g_b13516_exit_seen;

    if ((g_b13516_exit_seen & 15u) != 0u)
    {
        return;
    }

    ++g_b13516_exit_samples;

    pc &= 0x1FFFFFFFu;

    for (unsigned i = 0u; i < 4u; ++i)
    {
        if (
            g_b13516_exit_weight[i] != 0u
            &&
            g_b13516_exit_pc[i] == pc
        )
        {
            ++g_b13516_exit_weight[i];
            return;
        }
    }

    for (unsigned i = 0u; i < 4u; ++i)
    {
        if (g_b13516_exit_weight[i] == 0u)
        {
            g_b13516_exit_pc[i] = pc;
            g_b13516_exit_weight[i] = 1u;
            return;
        }
    }

    /*
     * Misra-Gries: preserve the recurring destinations without a large
     * hash table in the hot scheduler.
     */
    for (unsigned i = 0u; i < 4u; ++i)
    {
        --g_b13516_exit_weight[i];
    }
}


/*
 * ============================================================
 * B87 - vitesse + double-buffer stable
 * ============================================================
 *
 * B86 montre :
 *   SCHED ~3 ms avec hand=256 -> plafond artificiel atteint.
 *   DISPLAY x=0/320 change souvent -> double buffer PS1.
 *
 * B87 :
 *   - porte la limite de handoffs a 4096 ; la vraie borne devient
 *     la tranche temps de 14 ms ;
 *   - avant DIRECT-2DF, capture la page qui vient d'ETRE QUITTEE
 *     au lieu de la nouvelle page au moment du GP1(05) ;
 *   - evite le scan complet VRAM du debug.
 */
static uint32_t g_b87_delayed_latches = 0u;
static uint32_t g_b87_first_flip_waits = 0u;
static uint32_t g_b87_last_source_x = 0u;
static uint32_t g_b87_last_source_y = 0u;

/*
 * ============================================================
 * B97 - diagnostic framebuffer NON INVASIF
 * ============================================================
 *
 * B95/B96 ont modifie le moment/la page de capture et ont degrade
 * le menu. B97 revient strictement au rendu B94 et ne change plus
 * la logique video. On observe seulement, a chaque GP1(05), un
 * echantillon des pages x=0 et x=320 afin d'identifier laquelle
 * contient reellement l'image complete/stable.
 */
static uint32_t g_b97_p0_nonzero = 0u;
static uint32_t g_b97_p320_nonzero = 0u;
static uint32_t g_b97_p0_hash = 0u;
static uint32_t g_b97_p320_hash = 0u;
static uint32_t g_b97_flip_samples = 0u;

/*
 * ============================================================
 * B98 - selection anti-page-vide
 * ============================================================
 *
 * B97 a montre que le jeu alterne GP1(05) entre x=0 et x=320
 * alors qu'une des deux pages peut etre totalement vide dans
 * notre VRAM logicielle. Dans ce cas uniquement, on refuse de
 * latcher la page vide et on conserve la page framebuffer qui
 * contient reellement l'image.
 *
 * Si les deux pages contiennent une image significative, on
 * retombe strictement sur le comportement B94/B97 (page quittee).
 */
static uint32_t g_b98_force_p0 = 0u;
static uint32_t g_b98_force_p320 = 0u;
static uint32_t g_b98_normal_latch = 0u;

/*
 * ============================================================
 * B102 - presenter le VRAI frontbuffer GP1
 * ============================================================
 *
 * B101 a corrige GP0(E5): les deux pages x=0/x=320 sont enfin
 * reellement dessinees. Le vieux comportement B87/B98, qui
 * presentait la page PRECEDENTE, affiche maintenant le backbuffer
 * pendant qu'il est en train d'etre redessine.
 *
 * B102 prend donc fm_gpu_display_x/y comme source normale.
 * Un fallback n'est utilise que si la page demandee par GP1 est
 * pratiquement vide alors que l'autre contient clairement l'image.
 */
static uint32_t g_b102_front_latches = 0u;
static uint32_t g_b102_fallback_latches = 0u;

/*
 * B102 - etat reel du bridge menu B81.
 * L'ancien test "menu init deja vu" restait vrai pour toujours,
 * meme apres avoir quitte SU. On borne maintenant le bridge a la
 * duree de vie reelle du menu.
 */
static uint32_t g_b102_menu_bridge_active = 0u;
static uint32_t g_b102_menu_bridge_cleanup = 0u;


/*
 * ============================================================
 * B103 - reconstruire l'image depuis les 2 pages VRAM
 * ============================================================
 *
 * B101/B102 ont montre un cas tres clair :
 *   - une page porte surtout le decor (beaucoup de pixels non noirs)
 *   - l'autre porte surtout les elements de premier plan / UI
 *
 * Quand les densites sont tres differentes, on prend la page la
 * plus dense comme fond et on superpose les pixels non noirs de la
 * page la plus sparse. Si les deux pages ont une densite voisine,
 * on garde le vrai frontbuffer GP1 de B102.
 */
static uint32_t g_b103_merge_count = 0u;
static uint32_t g_b103_plain_count = 0u;
static uint32_t g_b103_last_base_x = 0u;
static uint32_t g_b103_last_overlay_x = 0u;
static uint32_t g_b103_last_base_nz = 0u;
static uint32_t g_b103_last_overlay_nz = 0u;

/*
 * ============================================================
 * B103 - bridge clavier de saisie du nom
 * ============================================================
 *
 * FUN_800304D0 est la routine de navigation du clavier de nom dans
 * l'EXE FR. Elle consomme DAT_8009C728 / DAT_8009C72C.
 *
 * Le pad brut 70C continue d'etre injecte normalement, mais si le
 * timing guest rate le front hote, on conserve aussi une impulsion
 * jusqu'a l'entree de 800304D0, comme B81 le faisait pour le menu SU.
 */
static uint32_t g_b103_name_hits = 0u;
static uint32_t g_b103_name_active_frames = 0u;
static uint32_t g_b103_name_pending_mask = 0u;
static uint32_t g_b103_name_cleanup_mask = 0u;
static uint32_t g_b103_name_injected = 0u;
static uint32_t g_b103_name_cleanups = 0u;


/*
 * ============================================================
 * B104 - diagnostic / support affichage cine
 * ============================================================
 */
static uint32_t g_b104_mdec_reset = 0u;
static uint32_t g_b104_mdec_in = 0u;
static uint32_t g_b104_mdec_out = 0u;
static uint32_t g_b104_mdec_in_sync = 0u;
static uint32_t g_b104_mdec_out_sync = 0u;

static uint64_t g_b104_last_gp0 = 0u;
static uint32_t g_b104_last_mode = 0xFFFFFFFFu;
static uint32_t g_b104_rgb24_latches = 0u;


/*
 * ============================================================
 * B105 - performance / cadence
 * ============================================================
 *
 * Objectif :
 *   - empecher une grosse tranche native de monopoliser une frame ;
 *   - laisser davantage de marge au present 3DS ;
 *   - mesurer le cout hors scheduler.
 */
static uint32_t g_b105_render_ms = 0u;
static uint32_t g_b105_vblank_ms = 0u;
static uint32_t g_b105_work_ms = 0u;
static uint32_t g_b105_loop_ms = 0u;
/*
 * B135.21 - B135.20 moved most Pharaoh-map work from the interpreter to
 * native generated ARM code. A 64K checkpoint quantum can now keep a single
 * fm_runtime_probe() alive for ~40 ms before main.c gets a chance to enforce
 * the 12 ms host slice. Use an 8K quantum so the outer scheduler can recover
 * control roughly every ~5 ms on the measured map workload.
 */
static uint32_t g_b105_probe_budget = 8192u;
static uint32_t g_b105_slice_budget_ms = 12u;

static uint32_t g_b106_pre_gfx_ms = 0u;
static uint32_t g_b106_gfx_ms = 0u;
static uint32_t g_b106_wait_ms = 0u;


/*
 * ============================================================
 * B91 - fast path d'execution des overlays SU
 * ============================================================
 *
 * B90 confirme que l'affichage B87 est revenu, mais le scheduler
 * peut encore depasser largement le budget pendant le menu SU.
 *
 * Jusqu'ici chaque basic block dynamique 0x801xxxxx faisait :
 *
 *   fm_runtime_probe() -> miss -> fm_interp_run_block()
 *
 * puis revenait au dispatcher principal au premier branchement.
 * L'overlay SU contient beaucoup de petits basic blocks : on paye
 * donc le cout du probe/dispatcher encore et encore.
 *
 * B91 execute directement une rafale de basic blocks tant que le PC
 * reste dans la fenetre overlay 0x80100000..0x801FFFFF. Des qu'un
 * JAL/JR ressort vers le resident 0x800xxxxx, on rend immediatement
 * la main au dispatcher natif. Aucun pixel ni etat de menu n'est
 * fabrique ici : c'est toujours le vrai code MIPS de SU qui tourne.
 */
static uint32_t g_b91_fast_entries = 0u;
static uint32_t g_b91_fast_blocks = 0u;
static uint64_t g_b91_fast_instructions = 0u;
static uint32_t g_b91_fast_time_yields = 0u;
static uint32_t g_b91_fast_block_cap = 0u;
static uint32_t g_b91_fast_exits_resident = 0u;
static uint32_t g_b91_last_block_ms = 0u;
static uint32_t g_b91_max_block_ms = 0u;
static uint32_t g_b91_last_entry_pc = 0u;
static uint32_t g_b91_last_exit_pc = 0u;

/* Petit profiler du handoff qui depasse le plus. */
static uint32_t g_b91_slow_handoff_ms = 0u;
static uint32_t g_b91_slow_handoff_pc = 0u;


/*
 * ============================================================
 * B93 - HLE natif du decodeur resident 800917F8
 * ============================================================
 *
 * Le profiler B91/B92 a isole 800917F8 comme le plus gros handoff
 * resident (79-90 ms). Le pseudo-C Ghidra montre un decodeur LZ
 * tres simple suivi d'un filtre XOR sur 0x8800 demi-mots.
 *
 * B93 execute exactement cette routine directement sur les 2 Mio
 * de RAM PS1 host, sans passer par des dizaines de milliers de
 * load/store du code MIPS recompile.
 */
static uint32_t g_b93_917f8_hle_calls = 0u;
static uint32_t g_b93_917f8_fallbacks = 0u;
static uint32_t g_b93_917f8_last_ms = 0u;
static uint32_t g_b93_917f8_max_ms = 0u;
static uint32_t g_b93_917f8_last_out = 0u;


static void fm_b79_submit_new_menu_packets(
    uint32_t begin,
    uint32_t end
)
{
    ++g_b79_direct_calls;

    if (
        begin < 0x80000000u
        ||
        begin >= 0x80200000u
        ||
        end <= begin
        ||
        end > 0x80200000u
        ||
        (begin & 3u) != 0u
        ||
        (end & 3u) != 0u
    )
    {
        ++g_b79_direct_bad;
        return;
    }

    uint32_t p = begin;

    while (p < end)
    {
        if (p + 4u > end)
        {
            ++g_b79_direct_bad;
            break;
        }

        uint32_t header =
            fm_memory_read_word(p);

        uint32_t count =
            header >> 24;

        uint32_t bytes =
            4u + count * 4u;

        /*
         * Les packets observes ici sont petits.
         * Garde-fou contre une RAM corrompue.
         */
        if (
            count == 0u
            ||
            count > 32u
            ||
            p + bytes > end
        )
        {
            ++g_b79_direct_bad;
            break;
        }

        g_b79_last_header = header;
        g_b79_last_packet = p;
        g_b79_last_count = count;

        g_b79_last_cmd0 =
            count > 0u
                ? fm_memory_read_word(p + 4u)
                : 0u;

        g_b79_last_cmd1 =
            count > 1u
                ? fm_memory_read_word(p + 8u)
                : 0u;

        g_b79_last_cmd2 =
            count > 2u
                ? fm_memory_read_word(p + 12u)
                : 0u;

        g_b79_last_cmd3 =
            count > 3u
                ? fm_memory_read_word(p + 16u)
                : 0u;

        g_b79_last_cmd4 =
            count > 4u
                ? fm_memory_read_word(p + 20u)
                : 0u;

        /*
         * Le premier mot peut etre une commande d'environnement
         * E1 suivie de la primitive sprite. On conserve exactement
         * l'ordre produit par le guest.
         */
        for (uint32_t i = 0u; i < count; ++i)
        {
            uint32_t word =
                fm_memory_read_word(
                    p + 4u + i * 4u
                );

            fm_gpu_gp0_write(word);
            ++g_b79_direct_words;

            if (i == 0u)
            {
                g_b79_last_opcode =
                    word >> 24;
            }
        }

        ++g_b79_direct_packets;

        p += bytes;
    }
}
static uint32_t g_hit_delay_wait = 0;
static uint32_t g_hit_intro_init = 0;
static uint32_t g_hit_boot_loop = 0;
static uint32_t g_hit_fade_wait = 0;
static uint32_t g_hit_main_loop = 0;
static uint32_t g_hit_str = 0;
static uint32_t g_hit_ov16 = 0;
static uint32_t g_hit_ov18 = 0;


/*
 * ============================================================
 * B47 - progression exacte de FUN_80043E3C / overlay 80168xxx
 * ============================================================
 *
 * Le sprite marron est maintenant explique : le jeu selectionne bien
 * E1=0x204 juste avant. On arrete donc de le traiter comme verrou.
 *
 * Cette trace cherche le vrai point ou le boot reste dans 43E3C.
 * 43E3C appelle:
 *   80013700
 *   ...
 *   801680F4
 *   puis boucle sur 80168160 tant que v0 != 0
 *   ...
 *   jusqu'au second 80013700 et au retour.
 */
static uint32_t g_b47_m_43eb8 = 0u;
static uint32_t g_b47_m_43f3c = 0u;
static uint32_t g_b47_m_43f44 = 0u;
static uint32_t g_b47_m_43f4c = 0u;
static uint32_t g_b47_m_43f54 = 0u;
static uint32_t g_b47_m_43ff8 = 0u;
static uint32_t g_b47_m_44054 = 0u;
static uint32_t g_b47_m_44064 = 0u;
static uint32_t g_b47_m_4406c = 0u;

static uint32_t g_b47_680f4_enter = 0u;
static uint32_t g_b47_68160_enter = 0u;
static uint32_t g_b47_68160_return = 0u;
static uint32_t g_b47_68160_v0_zero = 0u;
static uint32_t g_b47_68160_v0_nonzero = 0u;
static uint32_t g_b47_68160_last_v0 = 0u;
static uint32_t g_b47_68160_last_ra = 0u;

static uint32_t g_b47_last_milestone = 0u;
static uint32_t g_b47_last_milestone_frame = 0u;


/*
 * ============================================================
 * B49 - chemin exact entre 43EB8 et 43F3C
 * ============================================================
 *
 * B48 a prouve :
 *   - 43EB8 est atteint une fois ;
 *   - 43F3C n'est jamais atteint ;
 *   - le runtime ne s'arrete PAS sur le GTE (PROBE=RETURN).
 *
 * On trace donc chaque appel intermediaire de FUN_80043E3C :
 *
 *   43EB8 -> 8001569C
 *   43EC0 -> 80040350
 *   43ECC -> 800403D0
 *   43F08 -> 80042BD8
 *   43F20 -> 80043A78
 *   43F2C -> 80043CD4
 *   43F34 -> 8007E8E8
 *   43F3C -> 801680F4
 *
 * Les compteurs "fn" confirment aussi l'entree effective dans les
 * fonctions ciblees. Aucun comportement du jeu n'est modifie.
 */
static uint32_t g_b49_m_43ec0 = 0u;
static uint32_t g_b49_m_43ecc = 0u;
static uint32_t g_b49_m_43f08 = 0u;
static uint32_t g_b49_m_43f20 = 0u;
static uint32_t g_b49_m_43f2c = 0u;
static uint32_t g_b49_m_43f34 = 0u;

static uint32_t g_b49_fn_1569c = 0u;
static uint32_t g_b49_fn_40350 = 0u;
static uint32_t g_b49_fn_403d0 = 0u;
static uint32_t g_b49_fn_42bd8 = 0u;
static uint32_t g_b49_fn_43a78 = 0u;
static uint32_t g_b49_fn_7e8e8 = 0u;

static uint32_t g_b49_ra_1569c = 0u;
static uint32_t g_b49_ra_40350 = 0u;
static uint32_t g_b49_ra_403d0 = 0u;
static uint32_t g_b49_ra_42bd8 = 0u;
static uint32_t g_b49_ra_43a78 = 0u;
static uint32_t g_b49_ra_7e8e8 = 0u;


/*
 * ============================================================
 * B50 - cleanup CD manquant avant FUN_80043CD4
 * ============================================================
 *
 * B49 a isole le verrou :
 *   43A78 est atteint
 *   43CD4 est atteint
 *   7E8E8 n'est jamais atteint
 *
 * FUN_80043CD4 boucle jusqu'a ce que :
 *   (C460 & 0x02000030) == 0
 *   et C484 == 0
 *
 * La capture B49 montre C460=01C00054, donc bit 0x10 encore actif
 * alors que le dernier secteur est deja consomme (remaining == 0).
 *
 * Au premier passage dans 43CD4 avec une requete CD terminee, on
 * appelle le VRAI cleanup guest FUN_800143D4 en pseudo-interruption,
 * avec sauvegarde/restauration complete du contexte comme B35/B36.
 */
static uint32_t g_b50_cleanup_triggered = 0u;
static uint32_t g_b50_cleanup_done = 0u;
static uint32_t g_b50_cleanup_active = 0u;
static uint32_t g_b50_c460_before = 0u;
static uint32_t g_b50_c460_after = 0u;
static uint32_t g_b50_c484_before = 0u;
static uint32_t g_b50_c484_after = 0u;
static uint32_t g_b50_remaining = 0u;


/*
 * ============================================================
 * B51 - relance du dernier CdlDataReady partiel
 * ============================================================
 *
 * B50 confirme que FUN_80043CD4 est le verrou, mais le cleanup
 * n'a pas ete declenche. Le moteur CD est arrive a une queue de
 * requete inferieure a un secteur. Sur PS1, le controleur continue
 * a livrer CdlDataReady jusqu'au dernier fragment.
 *
 * Si notre pseudo-IRQ a perdu cette derniere livraison, on ne
 * touche PAS a la RAM de la requete : on rearme simplement le
 * callback CdlDataReady deja implemente en B34.
 */
static uint32_t g_b51_rearm_count = 0u;
static uint32_t g_b51_last_rem = 0u;
static uint32_t g_b51_last_type = 0u;
static uint32_t g_b51_last_c460 = 0u;
static uint32_t g_b51_last_c484 = 0u;


/*
 * ============================================================
 * B52 - trace du renderer FUN_800418C0
 * ============================================================
 *
 * B51 montre que le CD est maintenant propre :
 *   C460 = 0
 *   C484 = 0
 *   finalizer 3/3
 *
 * mais FUN_80043CD4 ne revient toujours pas vers 8007E8E8.
 * Le PC echantillonne se trouve dans FUN_800418C0 (80041Dxx),
 * appelee depuis le service frame 80012C50.
 *
 * On verifie si ce renderer :
 *   - est entre une seule fois ou se repete ;
 *   - revient bien vers 80040BE0 ;
 *   - parcourt un nombre coherent d'elements ;
 *   - tourne en boucle dans 41BB4/41D38/41F64/41F74.
 */
static uint32_t g_b52_418c0_hits = 0u;
static uint32_t g_b52_418c0_returns = 0u;
static uint32_t g_b52_41bb4_hits = 0u;
static uint32_t g_b52_41d38_hits = 0u;
static uint32_t g_b52_41f64_hits = 0u;
static uint32_t g_b52_41f74_hits = 0u;

static uint32_t g_b52_ra = 0u;
static uint32_t g_b52_a0 = 0u;
static uint32_t g_b52_a1 = 0u;
static uint32_t g_b52_a2 = 0u;

static uint32_t g_b52_data_ptr = 0u;
static uint32_t g_b52_data_w0 = 0u;
static uint32_t g_b52_data_w1 = 0u;
static uint32_t g_b52_data_w2 = 0u;
static uint32_t g_b52_obj_flags = 0u;
static uint32_t g_b52_item_count = 0u;
static uint32_t g_b52_obj_type = 0u;

static uint32_t g_b52_cd4_a0 = 0u;
static uint32_t g_b52_last_hot_pc = 0u;


/*
 * ============================================================
 * B53 - raccourci fidele de FUN_80043CD4
 * ============================================================
 *
 * B52 montre exactement 181 entrees renderer pour a0=0xB4.
 * C'est coherent avec le delai volontaire de 180 iterations de
 * FUN_80043CD4. Ce delai ralentit fortement le bring-up sur 3DS,
 * car chaque FUN_80012C50 est time-slicee sur plusieurs frames host.
 *
 * On raccourcit UNIQUEMENT le compteur minimal 0xB4 -> 2.
 * La condition de sortie CD de la vraie fonction reste intacte :
 * si C460/C484 sont encore busy, 43CD4 continuera quand meme a
 * boucler jusqu'a ce que le vrai code PS1 les libere.
 *
 * Donc :
 *   - aucun flag CD n'est forge ;
 *   - aucun retour de fonction n'est force ;
 *   - le vrai 80012C50 tourne encore ;
 *   - on supprime seulement ~178 iterations d'attente visuelle.
 */
static uint32_t g_b53_fast43cd4_hits = 0u;
static uint32_t g_b53_fast43cd4_last_in = 0u;
static uint32_t g_b53_fast43cd4_last_out = 0u;

/*
 * Trace cible du petit cycle observe dans le dernier build :
 *
 *   80082158 -> 8007FCBC -> 80012CD4 -> VSync
 *
 * On conserve le nombre de passages et le RA vu lors de ces
 * handoffs. Cela permet de remonter le vrai appelant sans
 * modifier le comportement du jeu.
 */
static uint32_t g_hit_7fcbc = 0;
static uint32_t g_hit_82158 = 0;
static uint32_t g_hit_12cd4 = 0;

static uint32_t g_ra_7fcbc = 0;
static uint32_t g_ra_82158 = 0;
static uint32_t g_ra_12cd4 = 0;

/*
 * Trace cible du verrou actuel.
 *
 * La pile observee au VSync remonte jusqu'a 80012B48, qui est
 * le retour du JAL de startup_candidate_fr vers FUN_800401A4.
 *
 * On verifie donc explicitement :
 *   startup -> 800401A4 -> ... -> service frame -> VSync
 * ainsi que l'enregistrement / execution du callback VBlank
 * LAB_80012BD8.
 */
static uint32_t g_hit_401a4 = 0;
static uint32_t g_hit_74968 = 0;
static uint32_t g_hit_vblank_cb = 0;

static uint32_t g_ra_401a4 = 0;
static uint32_t g_sp_401a4 = 0;
static uint32_t g_ra_74968 = 0;
static uint32_t g_ra_vblank_cb = 0;

/*
 * B13 FASTBOOT : FUN_800401A4 effectue correctement son setup,
 * puis reste dans une boucle de service qui n'est pas necessaire
 * pour atteindre le prochain jalon graphique sur notre bring-up.
 * On memorise le contexte d'entree et on sort proprement de cette
 * fonction apres quelques vrais VBlank callbacks executes avec succes.
 */
static uint32_t g_fast401_forced = 0;
static uint32_t g_fast401_frame = 0;

/*
 * B14 FASTBOOT : apres avoir quitte 401A4, le boot entre bien dans
 * FUN_80043E3C mais reste dans son attente de chargement asynchrone.
 * Notre couche CD bas niveau trouve l'ISO, mais la machine Psy-Q
 * asynchrone n'alimente toujours aucun secteur. Pour atteindre le
 * prochain jalon graphique rapidement, on laisse 43E3C effectuer son
 * setup initial, puis on la fait retourner proprement depuis son
 * contexte d'entree si elle tombe dans l'attente 80013700.
 */
static uint32_t g_ra_43e3c = 0;
static uint32_t g_sp_43e3c = 0;
static uint32_t g_fast43e_forced = 0;
static uint32_t g_fast43e_frame = 0;

/*
 * B15 DIRECT-2DF : au lieu d'attendre que le startup atteigne
 * naturellement FUN_8002DF60, on pilote directement la vraie
 * machine d'etat une fois par frame hote apres les deux fastboot.
 *
 * Le code de 8002DF60 reste le vrai code du jeu : on ne fabrique
 * pas d'image. On lui donne seulement un RA sentinelle afin de
 * reprendre la main quand une iteration est terminee.
 */
static uint32_t g_direct2df_active = 0;
static uint32_t g_direct2df_start_frame = 0;
static uint32_t g_direct2df_calls = 0;
static uint32_t g_direct2df_returns = 0;
static uint32_t g_direct2df_last_pc = 0;
static const uint32_t g_direct2df_sentinel = 0x8000FFE0u;

/*
 * B16 - time slicing + trace cible 80085DDC.
 *
 * B15 a prouve que le direct-2DF entre bien dans la machine d'etat,
 * mais une seule tranche a 250000 operations fait chuter Azahar a ~4 FPS.
 * On limite maintenant agressivement le travail guest par frame hote et
 * on capture le nouveau point chaud 80085DDC sans modifier son etat.
 */
static uint32_t g_b16_slice_yields = 0;
static uint32_t g_b16_slice_last_ms = 0;
static uint32_t g_b16_slice_max_ms = 0;
static uint32_t g_b16_last_handoffs = 0;

static uint32_t g_hit_85ddc = 0;
static uint32_t g_hit_85_range = 0;
static uint32_t g_85_last_phys = 0;
static uint32_t g_85_ra = 0;
static uint32_t g_85_sp = 0;
static uint32_t g_85_a0 = 0;
static uint32_t g_85_a1 = 0;
static uint32_t g_85_a2 = 0;
static uint32_t g_85_a3 = 0;
static uint32_t g_85_v0 = 0;
static uint32_t g_85_t0 = 0;
static uint32_t g_85_t1 = 0;
static uint32_t g_85_s0 = 0;
static uint32_t g_85_s1 = 0;
static uint32_t g_85_ops[12] = {0};
static uint32_t g_12e_ops[6] = {0};


/*
 * ============================================================
 * B18 - HLE fidele de FUN_80085D98 (GsSortOt)
 * ============================================================
 *
 * Le trace B16 a identifie la boucle de FUN_80085D98 comme le parcours
 * d'une ordering table PS1. B17 a confirme l'hypothese : le bypass
 * supprime la boucle et fait passer STATE a C0, mais il jette aussi
 * les primitives de l'OT source, donc aucun Draw n'arrive au GPU.
 *
 * B18 implemente le vrai principe de GsSortOt :
 *   OTZ = src->point - dst->offset
 * puis splice de la chaine source dans l'entree OTZ de destination.
 * Le parcours est borne et detecte le marqueur 00FFFFFF pour eviter
 * toute nouvelle boucle infinie.
 */
static uint32_t g_hle_85d98_calls = 0;
static uint32_t g_hle_85d98_last_src = 0;
static uint32_t g_hle_85d98_last_dst = 0;
static uint32_t g_hle_85d98_src_length = 0;
static uint32_t g_hle_85d98_src_org = 0;
static uint32_t g_hle_85d98_src_offset = 0;
static uint32_t g_hle_85d98_src_point = 0;
static uint32_t g_hle_85d98_src_tag = 0;
static uint32_t g_hle_85d98_dst_length = 0;
static uint32_t g_hle_85d98_dst_org = 0;
static uint32_t g_hle_85d98_dst_offset = 0;
static uint32_t g_hle_85d98_dst_point = 0;
static uint32_t g_hle_85d98_dst_tag = 0;
static uint32_t g_hle_85d98_bad_desc = 0;

/*
 * ============================================================
 * B19 - GsSortOt natif borne + soumission directe de l'OT source
 * ============================================================
 *
 * B18 a prouve que notre splice manuel n'etait pas assez fidele :
 * certaines chaines sont cycliques et finissent par alimenter le GPU
 * avec des centaines de milliers de faux mots.
 *
 * B19 ne reecrit plus GsSortOt a la main. Il essaie d'abord d'executer
 * le VRAI FUN_80085D98 dans un CPU temporaire, avec un budget strict.
 * Si l'appel ne revient pas, le jeu continue comme dans B17, mais on
 * parcourt l'OT source de maniere BORNEE et on envoie directement les
 * paquets GP0 valides au GPU. Cela permet de viser une premiere image
 * sans corrompre l'OT destination.
 */
static uint32_t g_sort_native_calls = 0;
static uint32_t g_sort_native_ok = 0;
static uint32_t g_sort_native_fail = 0;
static uint32_t g_sort_native_last_pc = 0;
static int32_t  g_sort_native_last_code = 0;
static uint32_t g_sort_native_last_handoffs = 0;

/*
 * B119 - direct C implementation of Psy-Q GsSortOt.
 * Independently verified against the matching US Forbidden Memories
 * LIBGS routine (GsSortOt, size 0xB4) and its MIPS instruction flow.
 */
static uint32_t g_b119_csort_calls = 0u;
static uint32_t g_b119_csort_ok = 0u;
static uint32_t g_b119_csort_fallbacks = 0u;
static uint32_t g_b119_csort_last_nodes = 0u;
static uint32_t g_b119_csort_max_nodes = 0u;
static int32_t g_b119_csort_last_code = 0;

static uint32_t g_ot_direct_calls = 0;
static uint32_t g_ot_direct_ok = 0;
static uint32_t g_ot_direct_bad = 0;
static uint32_t g_ot_direct_cycles = 0;
static uint32_t g_ot_direct_last_nodes = 0;
static uint32_t g_ot_direct_last_packets = 0;
static uint32_t g_ot_direct_last_words = 0;
static uint32_t g_ot_direct_last_start = 0;
static uint32_t g_ot_direct_last_stop = 0;
static uint32_t g_ot_direct_last_first_word = 0;
static uint32_t g_ot_direct_last_draw_packets = 0;
static uint32_t g_ot_direct_last_env_packets = 0;
static uint32_t g_ot_direct_last_other_packets = 0;


/*
 * ============================================================
 * B45 - provenance OT du sprite 72x72
 * ============================================================
 *
 * B44 a montre que la zone texture VRAM (290,64 18x72) n'est
 * touchee que par des clears 320x256. On capture maintenant le
 * paquet OT exact du sprite 0x64 et l'environnement E1/clear qui
 * le precede, afin de verifier si TP=0x204 est reellement demande
 * par le jeu ou s'il s'agit d'un etat GPU stale.
 */
static uint32_t g_b45_sprite_hits = 0u;
static uint32_t g_b45_last_ot = 0u;
static uint32_t g_b45_last_node = 0u;
static uint32_t g_b45_last_header = 0u;
static uint32_t g_b45_last_next24 = 0u;
static uint32_t g_b45_last_packet_index = 0u;

static uint32_t g_b45_last_e1 = 0xFFFFFFFFu;
static uint32_t g_b45_last_e1_node = 0u;
static uint32_t g_b45_last_e1_age = 0xFFFFFFFFu;

static uint32_t g_b45_clear_before_age = 0xFFFFFFFFu;
static uint32_t g_b45_clear_after_age = 0xFFFFFFFFu;

static uint32_t g_b45_prev1_node = 0u;
static uint32_t g_b45_prev1_word = 0u;
static uint32_t g_b45_prev2_node = 0u;
static uint32_t g_b45_prev2_word = 0u;

/*
 * B20 - correction minimale des OTs effacees par DMA6/OTC.
 * Une OT Psy-Q de longueur N utilise org[0] comme fin de chaine :
 * son lien 24 bits doit etre 00FFFFFF. Les traces B19 montraient
 * au contraire une chaine qui continuait sous org pendant des milliers
 * de mots. On repare UNIQUEMENT cette sentinelle, sans toucher aux
 * autres buckets ni aux primitives inserees par le jeu.
 */
static uint32_t g_ot_fix_calls = 0;
static uint32_t g_ot_fix_ok = 0;
static uint32_t g_ot_fix_changed = 0;
static uint32_t g_ot_fix_bad = 0;
static uint32_t g_ot_fix_last_ot = 0;
static uint32_t g_ot_fix_last_org = 0;
static uint32_t g_ot_fix_last_tag = 0;
static uint32_t g_ot_fix_last_before = 0;
static uint32_t g_ot_fix_last_after = 0;

/*
 * Vue VRAM automatique pour le bring-up graphique.
 * Si le DISPLAY PS1 reste pointe vers une zone vide mais que le jeu
 * ecrit ailleurs dans la VRAM (framebuffer double-buffer ou textures),
 * on choisit temporairement la fenetre 320x240 la plus peuplee afin
 * d'afficher la premiere image utile le plus vite possible.
 */
static uint32_t g_vram_view_x = 0;
static uint32_t g_vram_view_y = 0;
static uint32_t g_vram_view_nonzero = 0;

/*
 * Callback VBlank enregistre par FUN_80074968.
 *
 * Le build precedent a prouve :
 *   - FUN_80074968 est bien appelee une fois ;
 *   - LAB_80012BD8 contient du vrai code MIPS ;
 *   - le callback n'est jamais execute par notre chaine IRQ/HLE.
 *
 * On conserve donc le pointeur et le GP observes lors de
 * l'enregistrement afin de pouvoir reproduire, de facon minimale,
 * le premier effet certain du callback.
 */
static uint32_t g_vblank_registered_cb = 0;
static uint32_t g_vblank_registered_gp = 0;

static uint32_t g_vblank_bridge_ticks = 0;
static uint32_t g_vblank_bridge_target = 0;
static uint32_t g_vblank_bridge_target_41c = 0;
static uint32_t g_vblank_bridge_target_428 = 0;
static uint32_t g_vblank_bridge_before = 0;
static uint32_t g_vblank_bridge_after = 0;
static uint32_t g_vblank_bridge_41c_before = 0;
static uint32_t g_vblank_bridge_41c_after = 0;
static uint32_t g_vblank_bridge_428_before = 0;
static uint32_t g_vblank_bridge_428_after = 0;
static uint32_t g_vblank_bridge_sig_ok = 0;
static uint32_t g_vblank_sig_words[4] = {0, 0, 0, 0};

/*
 * ============================================================
 * B12 - execution REELLE du callback VBlank guest
 * ============================================================
 *
 * Plutot que de continuer a recopier a la main les effets de
 * LAB_80012BD8, B12 execute le vrai code MIPS du callback dans
 * une copie du CPUState. Les ecritures RAM/MMIO restent globales,
 * mais les registres du thread principal sont preserves.
 */
static uint32_t g_irq_exec_calls = 0;
static uint32_t g_irq_exec_ok = 0;
static uint32_t g_irq_exec_fail = 0;
static uint32_t g_irq_exec_last_pc = 0;
static uint32_t g_irq_exec_last_phys = 0;
static uint32_t g_irq_exec_last_handoffs = 0;
static uint32_t g_irq_exec_hit_3ce34 = 0;
static uint32_t g_irq_exec_hit_vsync = 0;
static int32_t g_irq_exec_last_code = 0;
static int32_t g_irq_exec_last_probe_reason = 0;
static int32_t g_irq_exec_last_interp_reason = 0;


/*
 * ============================================================
 * Nouveau verrou apres deblocage VBlank : 80082168
 * ============================================================
 *
 * Le bridge VBlank fonctionne maintenant et le PC a quitte
 * l'ancienne boucle autour de 800746B8. Le nouveau point chaud
 * observe est :
 *
 *   8008111C -> 80082168
 *
 * On ne force rien ici. On capture le contexte d'entree, les
 * premiers mots MIPS de 80082168 et les registres DMA6 afin de
 * savoir si cette routine attend une fin OTC/DMA.
 */
static uint32_t g_hit_8111c = 0;
static uint32_t g_hit_82168 = 0;
static uint32_t g_hit_8219c = 0;

static uint32_t g_ra_8111c = 0;
static uint32_t g_ra_82168 = 0;
static uint32_t g_ra_8219c = 0;

static uint32_t g_82168_a0 = 0;
static uint32_t g_82168_a1 = 0;
static uint32_t g_82168_a2 = 0;
static uint32_t g_82168_a3 = 0;
static uint32_t g_82168_v0 = 0;
static uint32_t g_82168_t0 = 0;
static uint32_t g_82168_t1 = 0;
static uint32_t g_82168_sp = 0;
static uint32_t g_82168_ops[8] = {0,0,0,0,0,0,0,0};


/*
 * Decode uniquement J/JAL MIPS pour les diagnostics.
 * Retourne 0 pour une autre instruction.
 */
static uint32_t fm_mips_jump_target(
    uint32_t pc,
    uint32_t instruction
)
{
    uint32_t opcode =
        instruction
        >>
        26;

    if (
        opcode != 2u
        &&
        opcode != 3u
    )
    {
        return 0;
    }

    return
        (
            (pc + 4u)
            &
            0xF0000000u
        )
        |
        (
            (
                instruction
                &
                0x03FFFFFFu
            )
            <<
            2
        );
}


/*
 * Snapshot de pile pris a l'entree de VSync.
 * On ne garde que les mots qui ressemblent a des adresses de
 * retour dans le code resident du SLES.
 */
static uint32_t g_vsync_stack_sp = 0;
static uint32_t g_vsync_stack_ra[4];
static uint32_t g_vsync_stack_count = 0;
static uint32_t g_vsync_s0 = 0;
static uint32_t g_vsync_s1 = 0;


static void fm_capture_vsync_stack(
    CPUState *cpu
)
{
    if (!cpu)
    {
        return;
    }

    uint32_t sp =
        cpu->gpr[29];

    g_vsync_stack_sp =
        sp;

    g_vsync_s0 =
        cpu->gpr[16];

    g_vsync_s1 =
        cpu->gpr[17];

    memset(
        g_vsync_stack_ra,
        0,
        sizeof(g_vsync_stack_ra)
    );

    g_vsync_stack_count = 0;

    /*
     * 0x100 octets suffisent pour voir les RA des quelques
     * niveaux qui entourent FUN_80012C50 / VSync.
     */
    for (uint32_t off = 0; off < 0x100u; off += 4u)
    {
        uint32_t value =
            cpu->read_word(
                sp + off
            );

        if (
            value >= 0x80010000u
            && value < 0x800A0000u
            && (value & 3u) == 0u
        )
        {
            int duplicate = 0;

            for (uint32_t i = 0; i < g_vsync_stack_count; ++i)
            {
                if (g_vsync_stack_ra[i] == value)
                {
                    duplicate = 1;
                    break;
                }
            }

            if (!duplicate)
            {
                g_vsync_stack_ra[g_vsync_stack_count] =
                    value;

                ++g_vsync_stack_count;

                if (g_vsync_stack_count >= 4u)
                {
                    break;
                }
            }
        }
    }
}



static uint32_t fm_b77_gpu_serial_now(void)
{
    uint32_t fill_hits = 0u;
    uint32_t draw_hits = 0u;
    uint32_t copy_hits = 0u;
    uint32_t upload_hits = 0u;
    uint32_t last_serial = 0u;
    uint8_t last_type = 0u;
    uint8_t last_opcode = 0u;
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;
    uint32_t cmd[4] = {0u, 0u, 0u, 0u};

    fm_gpu_b44_watch_get(
        &fill_hits,
        &draw_hits,
        &copy_hits,
        &upload_hits,
        &last_serial,
        &last_type,
        &last_opcode,
        &x,
        &y,
        &w,
        &h,
        cmd
    );

    return last_serial;
}


static void fm_b77_capture_draw_tail(void)
{
    for (unsigned back = 0u; back < 3u; ++back)
    {
        uint8_t op = 0u;
        unsigned words = 0u;
        uint16_t tp = 0u;
        int ox = 0;
        int oy = 0;
        int ax1 = 0;
        int ay1 = 0;
        int ax2 = 0;
        int ay2 = 0;
        uint32_t cmd[8] =
        {
            0u,0u,0u,0u,0u,0u,0u,0u
        };

        if (
            fm_gpu_b29_draw_trace_get(
                back,
                &op,
                &words,
                &tp,
                &ox,
                &oy,
                &ax1,
                &ay1,
                &ax2,
                &ay2,
                cmd
            )
        )
        {
            g_b77_op[back] = op;
            g_b77_tp[back] = tp;
            g_b77_offx[back] = ox;
            g_b77_offy[back] = oy;
            g_b77_cmd0[back] = cmd[0];
            g_b77_cmd1[back] = cmd[1];
            g_b77_cmd2[back] = cmd[2];
        }
    }
}


static void fm_trace_dispatch(
    CPUState *cpu,
    uint32_t dispatch_address,
    uint32_t phys
)
{
    if (phys != g_trace_last_phys)
    {
        g_trace_last_phys =
            phys;

        g_trace_pc[
            g_trace_count % 6u
        ] =
            dispatch_address;

        ++g_trace_count;
    }

    switch (phys)
    {
        case 0x00012A44u:
            ++g_hit_startup;
            break;

        case 0x00012C50u:
            ++g_hit_service;
            break;

        case 0x00013700u:
            ++g_hit_load_wait;

            if (!g_b31_req_snap)
            {
                const uint32_t req = 0x800EB1B8u;

                g_b31_req_10 = fm_memory_read_word(req + 0x10u);
                g_b31_req_18 = fm_memory_read_word(req + 0x18u);
                g_b31_req_1c = fm_memory_read_word(req + 0x1Cu);
                g_b31_req_20 = fm_memory_read_word(req + 0x20u);
                g_b31_req_24 = fm_memory_read_word(req + 0x24u);
                g_b31_req_2c = fm_memory_read_word(req + 0x2Cu);
                g_b31_req_34 = fm_memory_read_word(req + 0x34u);
                g_b31_req_40 = fm_memory_read_word(req + 0x40u);
                g_b31_req_44 = fm_memory_read_half(req + 0x44u);
                g_b31_req_46 = fm_memory_read_byte(req + 0x46u);
                g_b31_req_47 = fm_memory_read_byte(req + 0x47u);

                g_b31_c460 = fm_memory_read_word(0x8009C460u);
                g_b31_c484 = fm_memory_read_word(0x8009C484u);
                g_b31_tbl0 = fm_memory_read_word(0x800FB198u);

                if (cpu)
                {
                    g_b31_r137_ra = cpu->gpr[31];
                    g_b31_r137_gp = cpu->gpr[28];
                    g_b31_r137_a0 = cpu->gpr[4];
                    g_b31_r137_a1 = cpu->gpr[5];
                    g_b31_r137_a2 = cpu->gpr[6];
                    g_b31_r137_a3 = cpu->gpr[7];
                }

                g_b31_req_snap = 1u;
            }
            break;

        case 0x00043CD4u:
            ++g_hit_delay_wait;
            if (cpu)
            {
                g_b52_cd4_a0 = cpu->gpr[4];
            }
            break;

        /*
         * B52 - entree et jalons internes du renderer 800418C0.
         */
        case 0x000418C0u:
            ++g_b52_418c0_hits;
            if (cpu)
            {
                g_b52_ra = cpu->gpr[31];
                g_b52_a0 = cpu->gpr[4];
                g_b52_a1 = cpu->gpr[5];
                g_b52_a2 = cpu->gpr[6];

                /*
                 * B76 - combien d'appels 418C0 concernent reellement
                 * les 11 objets du menu SU ?
                 */
                for (unsigned i = 0u; i < 11u; ++i)
                {
                    if (
                        g_b52_a0
                        ==
                        fm_memory_read_word(
                            0x80184794u + i * 4u
                        )
                    )
                    {
                        ++g_b76_418c0_menu_hits;
                        g_b76_last_menu_obj = g_b52_a0;

                        /*
                         * B78 : photographier l'etat du packet buffer
                         * et du bucket OT AVANT FUN_800418C0.
                         */
                        g_b78_pending = 1u;
                        g_b78_obj = g_b52_a0;
                        g_b78_obj_index = i;
                        ++g_b78_calls;

                        g_b78_layer =
                            fm_memory_read_byte(
                                g_b52_a0 + 0x17u
                            );

                        g_b78_ctx =
                            fm_memory_read_word(
                                0x8009C858u
                                +
                                (
                                    g_b78_layer
                                    * 4u
                                )
                            );

                        g_b78_z =
                            fm_memory_read_half(
                                g_b52_a0 + 0x14u
                            );

                        g_b78_ot_base = 0u;
                        g_b78_zbase = 0;
                        g_b78_bucket_index = -1;
                        g_b78_bucket = 0u;
                        g_b78_bucket_before = 0u;

                        if (
                            g_b78_ctx >= 0x80000000u
                            &&
                            g_b78_ctx < 0x80200000u
                        )
                        {
                            g_b78_ot_base =
                                fm_memory_read_word(
                                    g_b78_ctx + 0x04u
                                );

                            g_b78_zbase =
                                (int32_t)fm_memory_read_word(
                                    g_b78_ctx + 0x08u
                                );

                            g_b78_bucket_index =
                                (int32_t)(
                                    g_b78_z & 0xFFFFu
                                )
                                -
                                g_b78_zbase;

                            if (
                                g_b78_ot_base >= 0x80000000u
                                &&
                                g_b78_ot_base < 0x80200000u
                                &&
                                g_b78_bucket_index >= 0
                                &&
                                g_b78_bucket_index < 0x10000
                            )
                            {
                                g_b78_bucket =
                                    g_b78_ot_base
                                    +
                                    (
                                        (uint32_t)g_b78_bucket_index
                                        * 4u
                                    );

                                if (
                                    g_b78_bucket >= 0x80000000u
                                    &&
                                    g_b78_bucket < 0x80200000u
                                )
                                {
                                    g_b78_bucket_before =
                                        fm_memory_read_word(
                                            g_b78_bucket
                                        );
                                }
                            }
                        }

                        g_b78_alloc_before =
                            fm_memory_read_word(
                                0x800FF5C4u
                            );

                        break;
                    }
                }

                if (
                    g_b52_a0 >= 0x80000000u
                    && g_b52_a0 < 0x80200000u
                )
                {
                    g_b52_obj_flags =
                        cpu->read_word(g_b52_a0 + 0x04u);

                    g_b52_obj_type =
                        cpu->read_byte(g_b52_a0 + 0x22u);

                    g_b52_data_ptr =
                        cpu->read_word(g_b52_a0 + 0x4Cu);

                    if (
                        g_b52_data_ptr >= 0x80000000u
                        && g_b52_data_ptr < 0x80200000u
                    )
                    {
                        g_b52_item_count =
                            cpu->read_byte(g_b52_data_ptr);

                        g_b52_data_w0 =
                            cpu->read_word(g_b52_data_ptr + 0u);

                        g_b52_data_w1 =
                            cpu->read_word(g_b52_data_ptr + 4u);

                        g_b52_data_w2 =
                            cpu->read_word(g_b52_data_ptr + 8u);
                    }
                }
            }
            break;

        /*
         * 80040BE0 est l'instruction qui suit le JAL 800418C0
         * dans FUN_80040B48 : elle compte donc les retours effectifs.
         */
        case 0x00040BE0u:
            ++g_b52_418c0_returns;

            if (g_b78_pending)
            {
                g_b78_alloc_after =
                    fm_memory_read_word(
                        0x800FF5C4u
                    );

                g_b78_alloc_delta = 0u;

                if (
                    g_b78_alloc_after >= g_b78_alloc_before
                    &&
                    g_b78_alloc_before >= 0x80000000u
                    &&
                    g_b78_alloc_after < 0x80200000u
                )
                {
                    g_b78_alloc_delta =
                        g_b78_alloc_after
                        -
                        g_b78_alloc_before;
                }

                if (g_b78_alloc_delta != 0u)
                {
                    ++g_b78_alloc_advanced;

                    for (unsigned j = 0u; j < 8u; ++j)
                    {
                        uint32_t a =
                            g_b78_alloc_before
                            +
                            j * 4u;

                        if (
                            a >= 0x80000000u
                            &&
                            a < 0x80200000u
                        )
                        {
                            g_b78_packet[j] =
                                fm_memory_read_word(a);
                        }
                        else
                        {
                            g_b78_packet[j] = 0u;
                        }
                    }
                }

                /*
                 * B79 - test decisif :
                 * les mots GP0 crees par CE rendu d'objet sont
                 * envoyes directement au GPU.
                 */
                if (
                    g_b78_alloc_delta != 0u
                    &&
                    g_b75_menu_entrance_bridge != 0u
                    &&
                    g_b73_hit_menu_destroy == 0u
                )
                {
                    fm_b79_submit_new_menu_packets(
                        g_b78_alloc_before,
                        g_b78_alloc_after
                    );
                }


                g_b78_bucket_after =
                    g_b78_bucket_before;

                if (
                    g_b78_bucket >= 0x80000000u
                    &&
                    g_b78_bucket < 0x80200000u
                )
                {
                    g_b78_bucket_after =
                        fm_memory_read_word(
                            g_b78_bucket
                        );
                }

                if (
                    g_b78_bucket_after
                    !=
                    g_b78_bucket_before
                )
                {
                    ++g_b78_bucket_changed;
                }

                /*
                 * Les pointeurs DMA PS1 sont sur 24 bits.
                 * FUN_80084018 doit normalement placer l'adresse
                 * du packet nouvellement alloue dans le bucket.
                 */
                if (
                    g_b78_alloc_delta != 0u
                    &&
                    (
                        g_b78_bucket_after
                        &
                        0x00FFFFFFu
                    )
                    ==
                    (
                        g_b78_alloc_before
                        &
                        0x00FFFFFFu
                    )
                )
                {
                    ++g_b78_bucket_points_packet;
                }

                ++g_b78_returns;
                g_b78_pending = 0u;
            }

            break;

        case 0x00041BB4u:
            ++g_b52_41bb4_hits;
            g_b52_last_hot_pc = 0x80041BB4u;
            break;

        case 0x00041D38u:
            ++g_b52_41d38_hits;
            g_b52_last_hot_pc = 0x80041D38u;
            break;

        case 0x00041F64u:
            ++g_b52_41f64_hits;
            g_b52_last_hot_pc = 0x80041F64u;
            break;

        case 0x00041F74u:
            ++g_b52_41f74_hits;
            g_b52_last_hot_pc = 0x80041F74u;
            break;

        /*
         * B78 - insertion primitive dans l'Ordering Table.
         */
        case 0x00084018u:
            if (g_b78_pending && cpu)
            {
                ++g_b78_addprim_hits;
                g_b78_addprim_packet = cpu->gpr[4];
                g_b78_addprim_ctx = cpu->gpr[5];
                g_b78_addprim_z = cpu->gpr[6];
                g_b78_addprim_words = cpu->gpr[7];
            }
            break;

        /*
         * Psy-Q DrawOTag / DrawOTagEnv.
         */
        case 0x00080258u:
            ++g_b78_drawotag_hits;
            if (cpu)
            {
                g_b78_drawotag_last_a0 = cpu->gpr[4];
            }
            break;

        case 0x00080388u:
            ++g_b78_drawotagenv_hits;
            break;


        case 0x00043E3Cu:
            ++g_hit_intro_init;
            if (cpu)
            {
                if (g_ra_43e3c == 0u)
                {
                    g_ra_43e3c = cpu->gpr[31];
                    g_sp_43e3c = cpu->gpr[29];
                }
            }
            break;

        /*
         * B49 - fonctions appelees avant l'overlay.
         * On conserve RA pour connaitre le callsite exact observe.
         */
        case 0x0001569Cu:
            ++g_b49_fn_1569c;
            if (cpu) g_b49_ra_1569c = cpu->gpr[31];
            break;

        case 0x00040350u:
            ++g_b49_fn_40350;
            if (cpu) g_b49_ra_40350 = cpu->gpr[31];
            break;

        case 0x000403D0u:
            ++g_b49_fn_403d0;
            if (cpu) g_b49_ra_403d0 = cpu->gpr[31];
            break;

        case 0x00042BD8u:
            ++g_b49_fn_42bd8;
            if (cpu) g_b49_ra_42bd8 = cpu->gpr[31];
            break;

        case 0x00043A78u:
            ++g_b49_fn_43a78;
            if (cpu) g_b49_ra_43a78 = cpu->gpr[31];
            break;

        case 0x0007E8E8u:
            ++g_b49_fn_7e8e8;
            if (cpu) g_b49_ra_7e8e8 = cpu->gpr[31];
            break;

        /* B47 - 43E3C milestones */
        case 0x00043EB8u:
            ++g_b47_m_43eb8;
            g_b47_last_milestone = 0x43EB8u;
            break;


        /* B49 - retour de 8001569C / appel 80040350 */
        case 0x00043EC0u:
            ++g_b49_m_43ec0;
            g_b47_last_milestone = 0x43EC0u;
            break;

        /* B49 - appel 800403D0 */
        case 0x00043ECCu:
            ++g_b49_m_43ecc;
            g_b47_last_milestone = 0x43ECCu;
            break;

        /* B49 - appel 80042BD8 */
        case 0x00043F08u:
            ++g_b49_m_43f08;
            g_b47_last_milestone = 0x43F08u;
            break;

        /* B49 - appel 80043A78 */
        case 0x00043F20u:
            ++g_b49_m_43f20;
            g_b47_last_milestone = 0x43F20u;
            break;

        /* B49 - appel 80043CD4 */
        case 0x00043F2Cu:
            ++g_b49_m_43f2c;
            g_b47_last_milestone = 0x43F2Cu;
            break;

        /* B49 - appel 8007E8E8 */
        case 0x00043F34u:
            ++g_b49_m_43f34;
            g_b47_last_milestone = 0x43F34u;
            break;

        case 0x00043F3Cu:
            ++g_b47_m_43f3c;
            g_b47_last_milestone = 0x43F3Cu;
            break;

        case 0x00043F44u:
            ++g_b47_m_43f44;
            g_b47_last_milestone = 0x43F44u;
            break;

        case 0x00043F4Cu:
            ++g_b47_m_43f4c;
            ++g_b47_68160_return;
            ++g_b61_at_return;
            if (cpu)
            {
                /*
                 * B61 : l'utilisateur a appuye sur START alors que
                 * l'overlay renvoie encore le statut d'attente 2.
                 * Faire sortir proprement la boucle du caller.
                 */
                if (
                    g_b61_skip_request
                    &&
                    g_b61_bridge_count == 0u
                    &&
                    cpu->gpr[2] == 2u
                )
                {
                    g_b61_old_v0 = cpu->gpr[2];
                    cpu->gpr[2] = 0u;
                    g_b61_skip_request = 0u;
                    ++g_b61_bridge_count;
                }

                g_b47_68160_last_v0 = cpu->gpr[2];

                g_b60_ret_v0 = cpu->gpr[2];
                g_b60_ret_s0 = cpu->gpr[16];
                g_b60_ret_s1 = cpu->gpr[17];
                g_b60_ret_s2 = cpu->gpr[18];
                g_b60_ret_s3 = cpu->gpr[19];

                if (cpu->gpr[2] == 0u)
                {
                    ++g_b47_68160_v0_zero;
                }
                else
                {
                    ++g_b47_68160_v0_nonzero;
                }
            }
            g_b47_last_milestone = 0x43F4Cu;
            break;

        case 0x00043F54u:
            ++g_b47_m_43f54;
            g_b47_last_milestone = 0x43F54u;
            break;

        case 0x00043FF8u:
            ++g_b47_m_43ff8;
            g_b47_last_milestone = 0x43FF8u;
            break;

        case 0x00044054u:
            ++g_b47_m_44054;
            g_b47_last_milestone = 0x44054u;
            break;

        case 0x00044064u:
            ++g_b47_m_44064;
            g_b47_last_milestone = 0x44064u;
            break;

        case 0x0004406Cu:
            ++g_b47_m_4406c;
            g_b47_last_milestone = 0x4406Cu;
            break;

        case 0x001680F4u:
            ++g_hit_ov16;
            ++g_b47_680f4_enter;
            if (cpu)
            {
                g_b47_68160_last_ra = cpu->gpr[31];
            }
            break;

        case 0x00168160u:
            ++g_hit_ov16;
            ++g_b47_68160_enter;
            if (cpu)
            {
                g_b47_68160_last_ra = cpu->gpr[31];

                g_b60_ent_a0 = cpu->gpr[4];
                g_b60_ent_a1 = cpu->gpr[5];
                g_b60_ent_a2 = cpu->gpr[6];
                g_b60_ent_a3 = cpu->gpr[7];

                g_b60_ent_s0 = cpu->gpr[16];
                g_b60_ent_s1 = cpu->gpr[17];
                g_b60_ent_s2 = cpu->gpr[18];
                g_b60_ent_s3 = cpu->gpr[19];

                g_b60_ent_sp = cpu->gpr[29];
                g_b60_ent_ra = cpu->gpr[31];
            }
            break;

        /*
         * B69 - chemin FUN_800495C8 -> FUN_80046750.
         */
        case 0x000495C8u:
            ++g_b69_495c8_enter;
            if (cpu)
            {
                g_b69_495c8_ra = cpu->gpr[31];
            }
            break;

        case 0x00046750u:
            ++g_b69_46750_enter;
            if (cpu)
            {
                g_b69_46750_ra = cpu->gpr[31];
            }
            break;

        /*
         * Les JAL de 800495C8 sont a :
         *   495F8 -> 46750  ; retour 49600
         *   49600 -> 494A0  ; retour 49608
         *   49608 -> 78588  ; retour 49610
         *   4965C -> 47660  ; retour 49664
         *
         * Les adresses de retour sont les meilleurs marqueurs pour
         * prouver que chaque sous-appel a réellement fini.
         */
        case 0x00049600u:
            ++g_b69_after_46750;
            break;

        case 0x00049608u:
            ++g_b69_after_494a0;
            break;

        case 0x00049610u:
            ++g_b69_after_78588;
            break;

        case 0x00049664u:
            ++g_b69_after_47660;
            break;

        /*
         * B74 - service frame + callback de rendu du menu.
         */
        case 0x00012F70u:
            ++g_b74_hit_12f70;
            if (cpu)
            {
                g_b74_last_12f70_ra = cpu->gpr[31];
            }
            break;

        case 0x00180B4Cu:
            ++g_b74_hit_menu_draw_cb;
            if (cpu)
            {
                g_b74_last_menu_draw_ra = cpu->gpr[31];
            }
            break;


        /*
         * B73 - chemin exact du menu SU.
         */
        /*
         * B104 - fonctions MDEC du PsyQ presentes dans l'EXE FR.
         * On ne modifie rien ici : on compte uniquement les passages.
         */
        case 0x000910A8u:
            ++g_b104_mdec_reset;
            break;

        case 0x00091198u:
            ++g_b104_mdec_in;
            break;

        case 0x00091228u:
            ++g_b104_mdec_out;
            break;

        case 0x000912B4u:
            ++g_b104_mdec_in_sync;
            break;

        case 0x00091348u:
            ++g_b104_mdec_out_sync;
            break;


        case 0x000304D0u:
            /*
             * B103 - entree de la routine de navigation du clavier.
             * Nettoyer l'impulsion precedente, puis injecter celle
             * capturee cote 3DS.
             */
            ++g_b103_name_hits;
            g_b103_name_active_frames = 12u;

            if (g_b103_name_cleanup_mask != 0u)
            {
                uint32_t mask = g_b103_name_cleanup_mask;

                fm_memory_write_word(
                    0x8009C710u,
                    fm_memory_read_word(0x8009C710u) & ~mask
                );

                fm_memory_write_word(
                    0x8009C72Cu,
                    fm_memory_read_word(0x8009C72Cu) & ~mask
                );

                fm_memory_write_word(
                    0x8009C728u,
                    fm_memory_read_word(0x8009C728u) & ~mask
                );

                g_b103_name_cleanup_mask = 0u;
                ++g_b103_name_cleanups;
            }

            if (g_b103_name_pending_mask != 0u)
            {
                uint32_t mask = g_b103_name_pending_mask;

                fm_memory_write_word(
                    0x8009C710u,
                    fm_memory_read_word(0x8009C710u) | mask
                );

                fm_memory_write_word(
                    0x8009C72Cu,
                    fm_memory_read_word(0x8009C72Cu) | mask
                );

                fm_memory_write_word(
                    0x8009C728u,
                    fm_memory_read_word(0x8009C728u) | mask
                );

                g_b103_name_cleanup_mask = mask;
                g_b103_name_pending_mask = 0u;
                ++g_b103_name_injected;
            }
            break;

        case 0x0002D75Cu:
            ++g_b73_hit_state8;
            break;

        case 0x0006B560u:
            ++g_b73_hit_load_su;
            break;

        case 0x0018001Cu:
            ++g_b73_hit_menu_init;
            ++g_hit_ov18;
            g_b102_menu_bridge_active = 1u;
            break;

        case 0x00180390u:
            /*
             * B82 - le prochain passage marque la fin du menu update
             * qui avait recu notre impulsion precedente.
             */
            if (g_b81_cleanup_mask != 0u)
            {
                uint32_t sel_now =
                    fm_memory_read_byte(
                        0x801847C0u
                    );

                g_b82_sel_after = sel_now;
                g_b82_sel_delta =
                    (int32_t)sel_now
                    -
                    (int32_t)g_b81_sel_before;

                g_b82_last_result_update =
                    g_b73_hit_menu_update;

                ++g_b82_result_samples;

                /*
                 * B83 - resultat du START injecte au passage
                 * precedent.
                 */
                if ((g_b81_cleanup_mask & 0x0800u) != 0u)
                {
                    uint32_t fx =
                        fm_memory_read_word(
                            0x8018478Cu
                        );

                    g_b83_fx_flags_after = 0u;

                    if (
                        fx >= 0x80000000u
                        &&
                        fx < 0x80200000u
                    )
                    {
                        g_b83_fx_flags_after =
                            fm_memory_read_half(
                                fx + 0x08u
                            );
                    }

                    g_b83_c4_after =
                        fm_memory_read_byte(
                            0x801847C4u
                        );

                    g_b83_c5_after =
                        fm_memory_read_byte(
                            0x801847C5u
                        );

                    if (
                        (
                            g_b83_fx_flags_after
                            &
                            0x0040u
                        )
                        == 0u
                    )
                    {
                        ++g_b83_fx_cleared;
                    }
                }
            }

            /*
             * B81 - nettoyage de l'impulsion precedente.
             */
            if (g_b81_cleanup_mask != 0u)
            {
                uint32_t mask =
                    g_b81_cleanup_mask;

                fm_memory_write_word(
                    0x8009C710u,
                    fm_memory_read_word(0x8009C710u)
                    &
                    ~mask
                );

                fm_memory_write_word(
                    0x8009C72Cu,
                    fm_memory_read_word(0x8009C72Cu)
                    &
                    ~mask
                );

                fm_memory_write_word(
                    0x8009C728u,
                    fm_memory_read_word(0x8009C728u)
                    &
                    ~mask
                );

                g_b81_cleanup_mask = 0u;
                ++g_b81_cleaned;
            }

            /*
             * B81 - injecter le front conserve EXACTEMENT ici,
             * avant que le vrai seed_80180390 lise H/E/R.
             */
            if (g_b81_pending_mask != 0u)
            {
                uint32_t mask =
                    g_b81_pending_mask;

                /*
                 * B82 - snapshot des gardes du pseudo-C 80180390.
                 */
                g_b82_c0 = fm_memory_read_byte(0x801847C0u);
                g_b82_c1 = fm_memory_read_byte(0x801847C1u);
                g_b82_c2 = fm_memory_read_byte(0x801847C2u);
                g_b82_c3 = (int8_t)fm_memory_read_byte(0x801847C3u);
                g_b82_c4 = (int8_t)fm_memory_read_byte(0x801847C4u);
                g_b82_c5 = fm_memory_read_byte(0x801847C5u);
                g_b82_c6 = fm_memory_read_byte(0x801847C6u);
                g_b82_c7 = fm_memory_read_byte(0x801847C7u);
                g_b82_c8 = fm_memory_read_byte(0x801847C8u);
                g_b82_c9 = fm_memory_read_byte(0x801847C9u);

                g_b82_fx_ptr =
                    fm_memory_read_word(
                        0x8018478Cu
                    );

                g_b82_fx_flags = 0u;
                g_b82_fx_timer = 0;
                g_b82_fx_pos = 0;
                g_b82_fx_wait = 0u;
                g_b82_fx_rgb = 0u;

                if (
                    g_b82_fx_ptr >= 0x80000000u
                    &&
                    g_b82_fx_ptr < 0x80200000u
                )
                {
                    g_b82_fx_flags =
                        fm_memory_read_half(
                            g_b82_fx_ptr + 0x08u
                        );

                    g_b82_fx_timer =
                        (int16_t)fm_memory_read_half(
                            g_b82_fx_ptr + 0x60u
                        );

                    g_b82_fx_pos =
                        (int16_t)fm_memory_read_half(
                            g_b82_fx_ptr + 0x36u
                        );

                    g_b82_fx_wait =
                        fm_memory_read_byte(
                            g_b82_fx_ptr + 0x6Cu
                        );

                    g_b82_fx_rgb =
                        (
                            (uint32_t)fm_memory_read_byte(
                                g_b82_fx_ptr + 0x0Cu
                            )
                            |
                            (
                                (uint32_t)fm_memory_read_byte(
                                    g_b82_fx_ptr + 0x0Du
                                )
                                << 8
                            )
                            |
                            (
                                (uint32_t)fm_memory_read_byte(
                                    g_b82_fx_ptr + 0x0Eu
                                )
                                << 16
                            )
                        );
                }

                g_b82_block_dialog =
                    (
                        g_b82_c6 != 0u
                        ||
                        g_b82_c7 != 0u
                        ||
                        g_b82_c8 != 0u
                        ||
                        g_b82_c9 != 0u
                    );

                g_b82_block_c4 =
                    (g_b82_c4 != 0);

                g_b82_block_fx =
                    (
                        g_b82_fx_ptr != 0u
                        &&
                        (
                            g_b82_fx_flags
                            &
                            0x0040u
                        )
                        != 0u
                    );

                g_b82_block_c5 =
                    (g_b82_c5 != 0u);

                g_b82_nav_seen =
                    (
                        (
                            fm_memory_read_word(
                                0x8009C728u
                            )
                            |
                            mask
                        )
                        &
                        0x5000u
                    );

                g_b82_action_seen =
                    (
                        (
                            fm_memory_read_word(
                                0x8009C72Cu
                            )
                            |
                            mask
                        )
                        &
                        0x08E0u
                    );

                ++g_b82_gate_samples;

                g_b81_held_before =
                    fm_memory_read_word(
                        0x8009C710u
                    );

                g_b81_edge_before =
                    fm_memory_read_word(
                        0x8009C72Cu
                    );

                g_b81_repeat_before =
                    fm_memory_read_word(
                        0x8009C728u
                    );

                g_b81_sel_before =
                    fm_memory_read_byte(
                        0x801847C0u
                    );

                fm_memory_write_word(
                    0x8009C710u,
                    g_b81_held_before
                    |
                    mask
                );

                fm_memory_write_word(
                    0x8009C72Cu,
                    g_b81_edge_before
                    |
                    mask
                );

                fm_memory_write_word(
                    0x8009C728u,
                    g_b81_repeat_before
                    |
                    mask
                );

                g_b81_held_after =
                    fm_memory_read_word(
                        0x8009C710u
                    );

                g_b81_edge_after =
                    fm_memory_read_word(
                        0x8009C72Cu
                    );

                g_b81_repeat_after =
                    fm_memory_read_word(
                        0x8009C728u
                    );

                g_b81_last_mask = mask;
                g_b81_last_update =
                    g_b73_hit_menu_update + 1u;

                if ((mask & 0x0800u) != 0u)
                {
                    ++g_b83_start_injected;
                }

                g_b81_cleanup_mask = mask;
                g_b81_pending_mask = 0u;
                ++g_b81_injected;
            }

            ++g_b73_hit_menu_update;
            ++g_hit_ov18;
            break;

        case 0x00180E48u:
            ++g_b73_hit_menu_destroy;
            ++g_hit_ov18;

            /*
             * B102 : le bridge B81 etait specifique au menu SU.
             * Ne laisser ni impulsion en attente ni bit injecte
             * apres la destruction de l'overlay menu.
             */
            g_b102_menu_bridge_active = 0u;
            g_b81_pending_mask = 0u;

            if (g_b81_cleanup_mask != 0u)
            {
                uint32_t mask = g_b81_cleanup_mask;

                fm_memory_write_word(
                    0x8009C710u,
                    fm_memory_read_word(0x8009C710u) & ~mask
                );

                fm_memory_write_word(
                    0x8009C72Cu,
                    fm_memory_read_word(0x8009C72Cu) & ~mask
                );

                fm_memory_write_word(
                    0x8009C728u,
                    fm_memory_read_word(0x8009C728u) & ~mask
                );

                g_b81_cleanup_mask = 0u;
                ++g_b102_menu_bridge_cleanup;
            }

            break;


        /*
         * B72 - jalons du rendu menu vus dans le runtime PC valide.
         */
        case 0x00040B48u:
            ++g_b72_hit_40b48;
            if (cpu)
            {
                g_b72_last_40b48_ra = cpu->gpr[31];
            }
            break;

        case 0x00041C88u:
            ++g_b72_hit_41c88;
            break;

        case 0x00044084u:
            ++g_hit_boot_loop;
            break;

        case 0x000158B4u:
            ++g_hit_fade_wait;
            break;

        case 0x0002DF60u:
            ++g_hit_main_loop;
            break;

        case 0x0006A4D8u:
            ++g_hit_str;
            break;

        case 0x0007FCBCu:
            ++g_hit_7fcbc;
            if (cpu)
            {
                g_ra_7fcbc = cpu->gpr[31];
            }
            break;

        case 0x00082158u:
            ++g_hit_82158;
            if (cpu)
            {
                g_ra_82158 = cpu->gpr[31];
            }
            break;

        case 0x00012CD4u:
            ++g_hit_12cd4;
            if (cpu)
            {
                g_ra_12cd4 = cpu->gpr[31];
            }
            break;

        case 0x0008111Cu:
            ++g_hit_8111c;
            if (cpu)
            {
                g_ra_8111c = cpu->gpr[31];
            }
            break;

        case 0x00082168u:
            ++g_hit_82168;
            if (cpu)
            {
                g_ra_82168 = cpu->gpr[31];
                g_82168_a0 = cpu->gpr[4];
                g_82168_a1 = cpu->gpr[5];
                g_82168_a2 = cpu->gpr[6];
                g_82168_a3 = cpu->gpr[7];
                g_82168_v0 = cpu->gpr[2];
                g_82168_t0 = cpu->gpr[8];
                g_82168_t1 = cpu->gpr[9];
                g_82168_sp = cpu->gpr[29];

                for (unsigned i = 0; i < 8u; ++i)
                {
                    g_82168_ops[i] =
                        cpu->read_word(0x80082168u + i * 4u);
                }
            }
            break;

        case 0x0008219Cu:
            ++g_hit_8219c;
            if (cpu)
            {
                g_ra_8219c = cpu->gpr[31];
            }
            break;

        case 0x00085DDCu:
            ++g_hit_85ddc;
            /* fall through vers la capture de la fenetre 85Dxx */
        default:
            if (
                phys >= 0x00085D80u
                && phys < 0x00085E80u
            )
            {
                ++g_hit_85_range;
                g_85_last_phys = phys;

                if (cpu)
                {
                    g_85_ra = cpu->gpr[31];
                    g_85_sp = cpu->gpr[29];
                    g_85_a0 = cpu->gpr[4];
                    g_85_a1 = cpu->gpr[5];
                    g_85_a2 = cpu->gpr[6];
                    g_85_a3 = cpu->gpr[7];
                    g_85_v0 = cpu->gpr[2];
                    g_85_t0 = cpu->gpr[8];
                    g_85_t1 = cpu->gpr[9];
                    g_85_s0 = cpu->gpr[16];
                    g_85_s1 = cpu->gpr[17];

                    /* 4 instructions avant + 8 a partir de 85DDC. */
                    for (unsigned i = 0; i < 12u; ++i)
                    {
                        g_85_ops[i] =
                            cpu->read_word(0x80085DCCu + i * 4u);
                    }

                    /* Appelant autour de RA=80012E70 observe en B15. */
                    for (unsigned i = 0; i < 6u; ++i)
                    {
                        g_12e_ops[i] =
                            cpu->read_word(0x80012E5Cu + i * 4u);
                    }
                }

                break;
            }
            break;

        case 0x000401A4u:
            ++g_hit_401a4;
            if (cpu)
            {
                g_ra_401a4 = cpu->gpr[31];
                g_sp_401a4 = cpu->gpr[29];
            }
            break;

        case 0x00074968u:
            ++g_hit_74968;
            if (cpu)
            {
                g_ra_74968 = cpu->gpr[31];

                /*
                 * FUN_80074968(callback) : conserver le dernier
                 * callback demande. Un appel ulterieur avec NULL
                 * desactivera naturellement le bridge.
                 */
                g_vblank_registered_cb =
                    cpu->gpr[4];

                g_vblank_registered_gp =
                    cpu->gpr[28];

                /*
                 * Valider le callback avec le meme chemin de lecture
                 * que celui utilise par le CPU guest. Le build precedent
                 * montrait une signature correcte via cpu->read_word(),
                 * alors que le bridge restait a zero : on fige donc ici
                 * le resultat de cette validation au moment exact de
                 * l'enregistrement.
                 */
                /*
                 * Valider depuis la RAM PS1 brute. Le build precedent
                 * a montre que cpu->read_word() au moment exact de
                 * l'enregistrement pouvait laisser SIG=0 alors que
                 * les quatre mots visibles en RAM etaient corrects.
                 */
                g_vblank_bridge_sig_ok =
                    (
                        g_vblank_registered_cb == 0x80012BD8u
                        && fm_memory_read_word(0x80012BD8u) == 0x8F8201ACu
                        && fm_memory_read_word(0x80012BDCu) == 0x00000000u
                        && fm_memory_read_word(0x80012BE0u) == 0x24420001u
                        && fm_memory_read_word(0x80012BE4u) == 0xAF8201ACu
                    )
                    ? 1u
                    : 0u;

                g_vblank_bridge_target =
                    g_vblank_registered_gp
                    +
                    0x1ACu;

                g_vblank_bridge_target_41c =
                    g_vblank_registered_gp
                    +
                    0x184u;

                g_vblank_bridge_target_428 =
                    g_vblank_registered_gp
                    +
                    0x190u;
            }
            break;

        case 0x00012BD8u:
            ++g_hit_vblank_cb;
            if (cpu)
            {
                g_ra_vblank_cb = cpu->gpr[31];
            }
            break;

    }
}


/*
 * Ecriture little-endian 32 bits via l'API byte publique.
 * Cela evite de dependre d'un helper write_word qui n'est pas
 * necessairement expose par fm_memory.h.
 */
static void fm_memory_write_word_le(
    uint32_t address,
    uint32_t value
)
{
    fm_memory_write_byte(
        address + 0u,
        (uint8_t)(value >> 0)
    );

    fm_memory_write_byte(
        address + 1u,
        (uint8_t)(value >> 8)
    );

    fm_memory_write_byte(
        address + 2u,
        (uint8_t)(value >> 16)
    );

    fm_memory_write_byte(
        address + 3u,
        (uint8_t)(value >> 24)
    );
}


/*
 * ============================================================
 * VBlank callback bridge - effets confirmes du callback
 * ============================================================
 *
 * Le dump B10 a maintenant confirme les 15 premiers mots utiles
 * de LAB_80012BD8 :
 *
 *   lw    v0, 0x1AC(gp)
 *   addiu v0, v0, 1
 *   sw    v0, 0x1AC(gp)      -> 8009C444++
 *
 *   lw    v0, 0x184(gp)
 *   addiu v0, v0, 1
 *   sw    v0, 0x184(gp)      -> 8009C41C++
 *
 *   lw    v0, 0x190(gp)
 *   ...
 *   addiu v0, v0, 1
 *   sw    v0, 0x190(gp)      -> 8009C428++
 *
 * Le callback appelle ensuite 8003CE34. On NE simule PAS encore
 * cet appel : B11 reproduit uniquement les trois increments dont
 * les instructions ont ete directement observees. Cela permet de
 * tester si le verrou du scheduler vient simplement des compteurs
 * temporels absents sans inventer le reste de l'IRQ.
 */
static void fm_service_vblank_callback_bridge(
    CPUState *cpu
)
{
    if (!cpu)
    {
        g_vblank_bridge_sig_ok = 0u;
        return;
    }

    g_vblank_sig_words[0] =
        cpu->read_word(0x80012BD8u);

    g_vblank_sig_words[1] =
        cpu->read_word(0x80012BDCu);

    g_vblank_sig_words[2] =
        cpu->read_word(0x80012BE0u);

    g_vblank_sig_words[3] =
        cpu->read_word(0x80012BE4u);

    g_vblank_bridge_sig_ok =
        (
            g_vblank_registered_cb == 0x80012BD8u
            && g_vblank_sig_words[0] == 0x8F8201ACu
            && g_vblank_sig_words[1] == 0x00000000u
            && g_vblank_sig_words[2] == 0x24420001u
            && g_vblank_sig_words[3] == 0xAF8201ACu
        )
        ? 1u
        : 0u;

    if (
        g_vblank_registered_cb != 0x80012BD8u
        || g_vblank_registered_gp == 0u
        || g_hit_vblank_cb != 0u
        || g_vblank_bridge_sig_ok == 0u
    )
    {
        return;
    }

    uint32_t target444 =
        g_vblank_bridge_target;

    uint32_t target41c =
        g_vblank_bridge_target_41c;

    uint32_t target428 =
        g_vblank_bridge_target_428;

    if (
        target444 < 0x80000000u
        || target444 >= 0x80200000u
        || target41c < 0x80000000u
        || target41c >= 0x80200000u
        || target428 < 0x80000000u
        || target428 >= 0x80200000u
    )
    {
        return;
    }

    uint32_t before444 =
        fm_memory_read_word(target444);

    uint32_t before41c =
        fm_memory_read_word(target41c);

    uint32_t before428 =
        fm_memory_read_word(target428);

    uint32_t after444 =
        before444 + 1u;

    uint32_t after41c =
        before41c + 1u;

    uint32_t after428 =
        before428 + 1u;

    fm_memory_write_word_le(
        target444,
        after444
    );

    fm_memory_write_word_le(
        target41c,
        after41c
    );

    fm_memory_write_word_le(
        target428,
        after428
    );

    g_vblank_bridge_before =
        before444;

    g_vblank_bridge_after =
        after444;

    g_vblank_bridge_41c_before =
        before41c;

    g_vblank_bridge_41c_after =
        after41c;

    g_vblank_bridge_428_before =
        before428;

    g_vblank_bridge_428_after =
        after428;

    ++g_vblank_bridge_ticks;
}


/*
 * Execute un appel guest isole jusqu'a son retour.
 *
 * Sentinel RA : une adresse residentielle volontairement non
 * utilisee. On s'arrete AVANT de tenter de l'executer.
 */
static int fm_execute_guest_vblank_callback(
    CPUState *cpu,
    uint32_t frame
)
{
    const uint32_t sentinel = 0x8000FFF0u;

    if (!cpu)
    {
        return 0;
    }

    g_vblank_sig_words[0] = cpu->read_word(0x80012BD8u);
    g_vblank_sig_words[1] = cpu->read_word(0x80012BDCu);
    g_vblank_sig_words[2] = cpu->read_word(0x80012BE0u);
    g_vblank_sig_words[3] = cpu->read_word(0x80012BE4u);

    g_vblank_bridge_sig_ok =
        (
            g_vblank_registered_cb == 0x80012BD8u
            && g_vblank_registered_gp != 0u
            && g_vblank_sig_words[0] == 0x8F8201ACu
            && g_vblank_sig_words[1] == 0x00000000u
            && g_vblank_sig_words[2] == 0x24420001u
            && g_vblank_sig_words[3] == 0xAF8201ACu
        )
        ? 1u
        : 0u;

    if (!g_vblank_bridge_sig_ok)
    {
        return 0;
    }

    /*
     * Si la vraie chaine IRQ commence un jour a livrer elle-meme
     * le callback, ne surtout pas le doubler.
     */
    if (g_hit_vblank_cb != 0u)
    {
        return 0;
    }

    CPUState irq_cpu = *cpu;

    irq_cpu.pc = g_vblank_registered_cb;
    irq_cpu.gpr[28] = g_vblank_registered_gp;

    /*
     * Pile IRQ separee, dans le haut de la RAM PS1. Le thread
     * principal tourne deja autour de 801FFFxx : 801FF000 laisse
     * suffisamment de marge aux appels imbriques du callback.
     */
    irq_cpu.gpr[29] = 0x801FF000u;
    irq_cpu.gpr[31] = sentinel;
    irq_cpu.gpr[0] = 0u;

    ++g_irq_exec_calls;
    g_irq_exec_last_code = 0;
    g_irq_exec_last_probe_reason = 0;
    g_irq_exec_last_interp_reason = 0;
    g_irq_exec_last_handoffs = 0;

    for (uint32_t handoff = 0; handoff < 128u; ++handoff)
    {
        g_irq_exec_last_handoffs = handoff + 1u;
        g_irq_exec_last_pc = irq_cpu.pc;
        g_irq_exec_last_phys = irq_cpu.pc & 0x1FFFFFFFu;

        if (irq_cpu.pc == sentinel)
        {
            ++g_irq_exec_ok;
            g_irq_exec_last_code = 1;
            return 1;
        }

        if (irq_cpu.pc == 0u && irq_cpu.gpr[31] == sentinel)
        {
            ++g_irq_exec_ok;
            g_irq_exec_last_code = 1;
            return 1;
        }

        uint32_t phys = irq_cpu.pc & 0x1FFFFFFFu;

        if (phys == 0x0003CE34u)
        {
            ++g_irq_exec_hit_3ce34;
        }

        /*
         * Si une sous-routine du callback interroge VSync, ne pas
         * lancer une attente hote depuis l'IRQ : on renvoie l'horloge
         * VBlank courante, ce qui est le comportement utile ici.
         */
        if (phys == 0x000746B8u)
        {
            ++g_irq_exec_hit_vsync;

            int32_t mode = (int32_t)irq_cpu.gpr[4];

            if (mode < 0)
            {
                irq_cpu.gpr[2] = frame;
            }
            else
            {
                irq_cpu.gpr[2] = 0u;
            }

            irq_cpu.pc = irq_cpu.gpr[31];
            irq_cpu.gpr[0] = 0u;
            continue;
        }

        /* BIOS appele depuis une sous-routine du callback. */
        if (
            phys == 0x000000A0u
            || phys == 0x000000B0u
            || phys == 0x000000C0u
            || phys == 0x00000884u
            || phys == 0x00000894u
        )
        {
            if (fm_bios_try_hle(&irq_cpu, irq_cpu.pc))
            {
                continue;
            }

            ++g_irq_exec_fail;
            g_irq_exec_last_code = -10;
            return 0;
        }

        /* Console debug guest : aucun effet gameplay. */
        if (phys == 0x00090CF8u)
        {
            irq_cpu.pc = irq_cpu.gpr[31];
            irq_cpu.gpr[0] = 0u;
            continue;
        }

        FMRuntimeProbeResult local_probe =
            fm_runtime_probe(
                &irq_cpu,
                irq_cpu.pc,
                100000
            );

        g_irq_exec_last_probe_reason =
            (int32_t)local_probe.reason;

        if (local_probe.reason == FM_STOP_BUDGET)
        {
            continue;
        }

        if (local_probe.reason != FM_STOP_RETURNED)
        {
            ++g_irq_exec_fail;
            g_irq_exec_last_code = -20;
            return 0;
        }

        if (local_probe.dispatch_result == 1)
        {
            if (irq_cpu.pc == 0u && irq_cpu.gpr[31] != 0u)
            {
                irq_cpu.pc = irq_cpu.gpr[31];
            }

            continue;
        }

        FMInterpResult local_interp =
            fm_interp_run_block(
                &irq_cpu,
                2048
            );

        g_irq_exec_last_interp_reason =
            (int32_t)local_interp.reason;

        if (
            local_interp.reason == FM_INTERP_BLOCK_DONE
            || local_interp.reason == FM_INTERP_BUDGET
        )
        {
            continue;
        }

        ++g_irq_exec_fail;
        g_irq_exec_last_code = -30;
        g_irq_exec_last_pc = local_interp.pc;
        g_irq_exec_last_phys = local_interp.pc & 0x1FFFFFFFu;
        return 0;
    }

    ++g_irq_exec_fail;
    g_irq_exec_last_code = -40;
    return 0;
}



/*
 * B119 - exact fast-path translation of GsSortOt.
 *
 * Cross-check:
 *   French SLES-03948 Ghidra FUN_80085D98: size 0xB4
 *   US SLUS matching decomp GsSortOt:       size 0xB4
 *
 * The US assembly confirms the exact register/pointer order, including the
 * slightly non-obvious t0/a3 progression used to select the source link that
 * is spliced into the destination bucket.
 *
 * This function changes only guest RAM exactly as GsSortOt does. The old
 * temporary-CPU implementation remains the fallback if validation fails.
 */
static int fm_try_c_gssortot(
    CPUState *cpu,
    uint32_t src_ot,
    uint32_t dst_ot,
    uint32_t *result_v0
)
{
    const uint32_t link_mask = 0x00FFFFFFu;
    const uint32_t header_mask = 0xFF000000u;
    const uint32_t max_steps = 8192u;

    ++g_b119_csort_calls;
    g_b119_csort_last_nodes = 0u;
    g_b119_csort_last_code = 0;

    if (!cpu || src_ot == 0u || dst_ot == 0u)
    {
        g_b119_csort_last_code = -10;
        ++g_b119_csort_fallbacks;
        return 0;
    }

    uint32_t src_phys = src_ot & 0x1FFFFFFFu;
    uint32_t dst_phys = dst_ot & 0x1FFFFFFFu;

    if (
        src_phys >= 0x00200000u
        || dst_phys >= 0x00200000u
        || (src_phys & 3u) != 0u
        || (dst_phys & 3u) != 0u
        || src_phys + 0x10u >= 0x00200000u
        || dst_phys + 0x08u >= 0x00200000u
    )
    {
        g_b119_csort_last_code = -11;
        ++g_b119_csort_fallbacks;
        return 0;
    }

    /*
     * MIPS reference:
     *   a2 = src->org
     *   a0 = src->point
     *   v1 = dst->offset
     *   t3 = dst->org
     *   a3 = a2
     *   t0 = a2
     */
    uint32_t a2 = cpu->read_word(src_ot + 4u);
    uint32_t a0 = cpu->read_word(src_ot + 0x0Cu);
    uint32_t dst_offset = cpu->read_word(dst_ot + 8u);
    uint32_t t3 = cpu->read_word(dst_ot + 4u);
    uint32_t src_tag = cpu->read_word(src_ot + 0x10u);

    uint32_t a2_phys = a2 & 0x1FFFFFFFu;
    uint32_t t3_phys = t3 & 0x1FFFFFFFu;

    if (
        a2_phys >= 0x00200000u
        || t3_phys >= 0x00200000u
        || (a2_phys & 3u) != 0u
        || (t3_phys & 3u) != 0u
    )
    {
        g_b119_csort_last_code = -12;
        ++g_b119_csort_fallbacks;
        return 0;
    }

    uint32_t a3 = a2;
    uint32_t t0 = a2;
    uint32_t v0 = cpu->read_word(a2);

    /*
     * The subtraction occurs in the branch delay slot in the original,
     * therefore it happens regardless of whether the source starts at
     * the terminating bucket.
     */
    uint32_t otz = a0 - dst_offset;

    if ((v0 & link_mask) != link_mask)
    {
        int found_end = 0;

        for (uint32_t step = 0u; step < max_steps; ++step)
        {
            /*
             * Exact 0x80085E54..0x80085E6C register order:
             *   t0 = a3;
             *   v0 = *a2;
             *   a3 = a2;
             *   a2 = v0 & 00FFFFFF;
             *   v0 = *a2;
             */
            t0 = a3;
            v0 = cpu->read_word(a2);
            a3 = a2;
            a2 = v0 & link_mask;

            uint32_t next_phys = a2 & 0x1FFFFFFFu;

            if (
                next_phys >= 0x00200000u
                || (next_phys & 3u) != 0u
            )
            {
                g_b119_csort_last_code = -13;
                ++g_b119_csort_fallbacks;
                return 0;
            }

            v0 = cpu->read_word(a2);
            g_b119_csort_last_nodes = step + 1u;

            if ((v0 & link_mask) == link_mask)
            {
                found_end = 1;
                break;
            }
        }

        if (!found_end)
        {
            g_b119_csort_last_code = -14;
            ++g_b119_csort_fallbacks;
            return 0;
        }
    }

    if (g_b119_csort_last_nodes > g_b119_csort_max_nodes)
    {
        g_b119_csort_max_nodes = g_b119_csort_last_nodes;
    }

    /*
     * MIPS: bucket = dst->org + ((src->point - dst->offset) << 2)
     * with normal 32-bit wraparound.
     */
    uint32_t bucket =
        t3
        +
        (otz << 2);

    uint32_t bucket_phys = bucket & 0x1FFFFFFFu;
    uint32_t t0_phys = t0 & 0x1FFFFFFFu;

    if (
        bucket_phys >= 0x00200000u
        || t0_phys >= 0x00200000u
        || (bucket_phys & 3u) != 0u
        || (t0_phys & 3u) != 0u
    )
    {
        g_b119_csort_last_code = -15;
        ++g_b119_csort_fallbacks;
        return 0;
    }

    /*
     * Exact two splices from the reference assembly. Re-read the
     * destination bucket before the second write because the original does.
     */
    uint32_t src_link_word = cpu->read_word(t0);
    uint32_t dst_bucket_word = cpu->read_word(bucket);

    cpu->write_word(
        t0,
        (src_link_word & header_mask)
        |
        (dst_bucket_word & link_mask)
    );

    dst_bucket_word = cpu->read_word(bucket);

    cpu->write_word(
        bucket,
        (dst_bucket_word & header_mask)
        |
        (src_tag & link_mask)
    );

    if (result_v0)
    {
        *result_v0 = dst_ot;
    }

    ++g_b119_csort_ok;
    g_b119_csort_last_code = 1;
    return 1;
}


/*
 * Execute le vrai GsSortOt dans un CPU temporaire.
 *
 * La pile est separee afin de ne pas polluer le thread principal.
 * Les ecritures dans les structures OT restent, elles, dans la vraie
 * RAM guest : si la fonction retourne, on a exactement le comportement
 * du code original.
 */
static int fm_try_native_gssortot(
    CPUState *cpu,
    uint32_t src_ot,
    uint32_t dst_ot,
    uint32_t *result_v0
)
{
    const uint32_t sentinel = 0x8000FFE0u;

    if (!cpu || src_ot == 0u || dst_ot == 0u)
    {
        return 0;
    }

    CPUState ot_cpu = *cpu;

    ot_cpu.pc = 0x80085D98u;
    ot_cpu.gpr[4] = src_ot;
    ot_cpu.gpr[5] = dst_ot;
    ot_cpu.gpr[29] = 0x801FD000u;
    ot_cpu.gpr[31] = sentinel;
    ot_cpu.gpr[0] = 0u;

    ++g_sort_native_calls;
    g_sort_native_last_code = 0;
    g_sort_native_last_handoffs = 0;

    for (uint32_t handoff = 0u; handoff < 8u; ++handoff)
    {
        g_sort_native_last_handoffs = handoff + 1u;
        g_sort_native_last_pc = ot_cpu.pc;

        if (ot_cpu.pc == sentinel)
        {
            if (result_v0)
            {
                *result_v0 = ot_cpu.gpr[2];
            }

            ++g_sort_native_ok;
            g_sort_native_last_code = 1;
            return 1;
        }

        FMRuntimeProbeResult local_probe =
            fm_runtime_probe(
                &ot_cpu,
                ot_cpu.pc,
                4096u
            );

        if (local_probe.reason == FM_STOP_BUDGET)
        {
            /*
             * Un GsSortOt sain est tres court. Deux tranches consecutives
             * dans sa boucle de chainage signifient pratiquement toujours
             * que l'OT est cyclique dans notre bring-up.
             */
            if (handoff >= 1u)
            {
                ++g_sort_native_fail;
                g_sort_native_last_code = -1;
                return 0;
            }

            continue;
        }

        if (local_probe.reason != FM_STOP_RETURNED)
        {
            ++g_sort_native_fail;
            g_sort_native_last_code = -2;
            return 0;
        }

        if (local_probe.dispatch_result == 1)
        {
            if (ot_cpu.pc == 0u && ot_cpu.gpr[31] != 0u)
            {
                ot_cpu.pc = ot_cpu.gpr[31];
            }

            continue;
        }

        FMInterpResult local_interp =
            fm_interp_run_block(
                &ot_cpu,
                512u
            );

        if (
            local_interp.reason == FM_INTERP_BLOCK_DONE
            || local_interp.reason == FM_INTERP_BUDGET
        )
        {
            continue;
        }

        ++g_sort_native_fail;
        g_sort_native_last_code = -3;
        g_sort_native_last_pc = local_interp.pc;
        return 0;
    }

    ++g_sort_native_fail;
    g_sort_native_last_code = -4;
    return 0;
}


/*
 * Repare uniquement la sentinelle du premier bucket d'une GsOT.
 *
 * GsOT :
 *   +0  length (log2 du nombre de buckets)
 *   +4  org    (premier bucket)
 *   +16 tag    (bucket de tete)
 *
 * Pour une OT vide/valide, tag == org + ((1<<length)-1)*4 et
 * org[0] termine la linked-list avec 00FFFFFF. Si ce dernier lien
 * pointe encore vers org-4, le DMA2/GsSortOt peut parcourir la RAM
 * indefiniment. On ne modifie rien d'autre.
 */
static int fm_repair_ot_sentinel(
    CPUState *cpu,
    uint32_t ot
)
{
    ++g_ot_fix_calls;
    g_ot_fix_last_ot = ot;

    if (!cpu || ot == 0u)
    {
        ++g_ot_fix_bad;
        return 0;
    }

    uint32_t length = cpu->read_word(ot + 0u);
    uint32_t org = cpu->read_word(ot + 4u);
    uint32_t tag = cpu->read_word(ot + 16u);

    g_ot_fix_last_org = org;
    g_ot_fix_last_tag = tag;

    if (length > 15u || org == 0u || tag == 0u)
    {
        ++g_ot_fix_bad;
        return 0;
    }

    uint32_t count = 1u << length;
    uint32_t org_phys = org & 0x1FFFFFFFu;
    uint32_t tag_phys = tag & 0x1FFFFFFFu;
    uint32_t expected_tag_phys = org_phys + (count - 1u) * 4u;

    if (
        org_phys >= 0x00200000u
        || expected_tag_phys >= 0x00200000u
        || (org_phys & 3u) != 0u
        || tag_phys != expected_tag_phys
    )
    {
        ++g_ot_fix_bad;
        return 0;
    }

    uint32_t before = cpu->read_word(org);
    uint32_t after = before;

    g_ot_fix_last_before = before;

    /*
     * B116 - IMPORTANT: do not erase a valid bucket-0 primitive chain.
     *
     * The old bring-up repair replaced ANY org[0] != 00FFFFFF with the
     * terminator. That is destructive: after AddPrim(), bucket 0 may
     * legitimately point at a packet and must survive GsSortOt.
     *
     * The corruption originally observed was much narrower: the OTC
     * chain continued one word below the OT, i.e. org[0] pointed to
     * org-4 instead of terminating. Repair ONLY that exact stale OTC
     * link, and only when the header byte is zero (pure OT bucket).
     */
    uint32_t before_count = before >> 24;
    uint32_t before_next24 = before & 0x00FFFFFFu;
    uint32_t stale_next24 =
        (org_phys - 4u) & 0x00FFFFFFu;

    if (
        before_count == 0u
        &&
        before_next24 == stale_next24
    )
    {
        after =
            (before & 0xFF000000u)
            |
            0x00FFFFFFu;

        cpu->write_word(org, after);
        ++g_ot_fix_changed;
    }

    g_ot_fix_last_after = after;
    ++g_ot_fix_ok;
    return 1;
}

/*
 * Soumet directement une OT au parser GP0 sans passer par DMA2.
 *
 * Le format est exactement celui d'une linked-list GPU :
 *   bits 31..24 = nombre de mots GP0 dans le noeud
 *   bits 23..0  = adresse du noeud suivant, FFFFFF = fin
 *
 * Le parcours est volontairement borne et surveille les cycles.
 * On ne modifie AUCUN lien de l'OT guest.
 */
static int fm_submit_ot_safe(
    CPUState *cpu,
    uint32_t start_tag
)
{
    enum
    {
        OT_MAX_NODES = 4096,
        OT_MAX_WORDS = 65536,
        OT_RECENT = 256
    };

    uint32_t recent[OT_RECENT];
    uint32_t recent_count = 0u;
    uint32_t node = start_tag;
    uint32_t nodes = 0u;
    uint32_t packets = 0u;
    uint32_t words = 0u;
    int ended = 0;


    /* B45 local state for this OT traversal. */
    uint32_t b45_e1 = 0xFFFFFFFFu;
    uint32_t b45_e1_node = 0u;
    uint32_t b45_e1_packet = 0u;
    uint32_t b45_last_clear_packet = 0xFFFFFFFFu;
    uint32_t b45_target_packet = 0xFFFFFFFFu;
    int b45_target_seen = 0;

    uint32_t b45_prev1_node = 0u;
    uint32_t b45_prev1_word = 0u;
    uint32_t b45_prev2_node = 0u;
    uint32_t b45_prev2_word = 0u;

    ++g_ot_direct_calls;
    g_ot_direct_last_nodes = 0u;
    g_ot_direct_last_packets = 0u;
    g_ot_direct_last_words = 0u;
    g_ot_direct_last_start = start_tag;
    g_ot_direct_last_stop = start_tag;
    g_ot_direct_last_first_word = 0u;
    g_ot_direct_last_draw_packets = 0u;
    g_ot_direct_last_env_packets = 0u;
    g_ot_direct_last_other_packets = 0u;

    if (!cpu || start_tag == 0u)
    {
        ++g_ot_direct_bad;
        return 0;
    }

    for (nodes = 0u; nodes < OT_MAX_NODES; ++nodes)
    {
        uint32_t phys = node & 0x1FFFFFFFu;

        if (phys >= 0x00200000u || (phys & 3u) != 0u)
        {
            ++g_ot_direct_bad;
            break;
        }

        /* Cycle court : largement suffisant pour les OTs observees. */
        uint32_t check_count =
            recent_count < OT_RECENT
                ? recent_count
                : OT_RECENT;

        for (uint32_t i = 0u; i < check_count; ++i)
        {
            uint32_t index =
                (recent_count - 1u - i)
                & (OT_RECENT - 1u);

            if (recent[index] == phys)
            {
                ++g_ot_direct_cycles;
                g_ot_direct_last_stop = node;
                goto ot_done;
            }
        }

        recent[recent_count & (OT_RECENT - 1u)] = phys;
        ++recent_count;

        uint32_t guest_node = 0x80000000u | phys;
        uint32_t header = cpu->read_word(guest_node);
        uint32_t count = header >> 24;
        uint32_t next24 = header & 0x00FFFFFFu;

        if (count != 0u)
        {
            uint32_t end_phys =
                phys
                + 4u
                + count * 4u;

            if (end_phys > 0x00200000u)
            {
                ++g_ot_direct_bad;
                g_ot_direct_last_stop = node;
                break;
            }

            if (words + count > OT_MAX_WORDS)
            {
                ++g_ot_direct_bad;
                g_ot_direct_last_stop = node;
                break;
            }

            uint32_t first_word =
                cpu->read_word(guest_node + 4u);

            if (packets == 0u)
            {
                g_ot_direct_last_first_word = first_word;
            }

            uint32_t opcode = first_word >> 24;

            /*
             * B45 - suivre les commandes E1 et les clears dans l'ordre
             * exact de la linked-list GP0.
             */
            if (opcode == 0xE1u)
            {
                b45_e1 = first_word & 0x7FFu;
                b45_e1_node = guest_node;
                b45_e1_packet = packets;
            }

            if (
                opcode == 0x02u
                && count >= 3u
            )
            {
                uint32_t pos =
                    cpu->read_word(guest_node + 8u);

                uint32_t size =
                    cpu->read_word(guest_node + 12u);

                uint32_t fx = pos & 0x3FFu;
                uint32_t fy = (pos >> 16) & 0x1FFu;
                uint32_t fw = size & 0x3FFu;
                uint32_t fh = (size >> 16) & 0x1FFu;

                if (
                    fx == 0u
                    && fy == 0u
                    && fw == 320u
                    && fh == 256u
                )
                {
                    if (!b45_target_seen)
                    {
                        b45_last_clear_packet = packets;
                    }
                    else if (
                        g_b45_clear_after_age == 0xFFFFFFFFu
                        && packets >= b45_target_packet
                    )
                    {
                        g_b45_clear_after_age =
                            packets - b45_target_packet;
                    }
                }
            }

            /*
             * Le sprite observe depuis B38:
             *   64808080
             *   00110011       xy = 17,17
             *   38694088       uv = 136,64 / CLUT = 656,225
             *   00480048       72x72
             */
            if (
                opcode == 0x64u
                && count >= 4u
            )
            {
                uint32_t c1 =
                    cpu->read_word(guest_node + 8u);

                uint32_t c2 =
                    cpu->read_word(guest_node + 12u);

                uint32_t c3 =
                    cpu->read_word(guest_node + 16u);

                if (
                    (c1 & 0xFFFFFFFFu) == 0x00110011u
                    && (c2 & 0x0000FFFFu) == 0x00004088u
                    && c3 == 0x00480048u
                )
                {
                    ++g_b45_sprite_hits;

                    g_b45_last_ot = start_tag;
                    g_b45_last_node = guest_node;
                    g_b45_last_header = header;
                    g_b45_last_next24 = next24;
                    g_b45_last_packet_index = packets;

                    g_b45_last_e1 = b45_e1;
                    g_b45_last_e1_node = b45_e1_node;

                    if (
                        b45_e1 != 0xFFFFFFFFu
                        && packets >= b45_e1_packet
                    )
                    {
                        g_b45_last_e1_age =
                            packets - b45_e1_packet;
                    }
                    else
                    {
                        g_b45_last_e1_age =
                            0xFFFFFFFFu;
                    }

                    if (
                        b45_last_clear_packet != 0xFFFFFFFFu
                        && packets >= b45_last_clear_packet
                    )
                    {
                        g_b45_clear_before_age =
                            packets - b45_last_clear_packet;
                    }
                    else
                    {
                        g_b45_clear_before_age =
                            0xFFFFFFFFu;
                    }

                    /* Reinitialise le "clear apres" pour ce sprite. */
                    g_b45_clear_after_age = 0xFFFFFFFFu;

                    g_b45_prev1_node = b45_prev1_node;
                    g_b45_prev1_word = b45_prev1_word;
                    g_b45_prev2_node = b45_prev2_node;
                    g_b45_prev2_word = b45_prev2_word;

                    b45_target_seen = 1;
                    b45_target_packet = packets;
                }
            }

            if (opcode >= 0x20u && opcode <= 0x7Fu)
            {
                ++g_ot_direct_last_draw_packets;
            }
            else if (opcode >= 0xE1u && opcode <= 0xE6u)
            {
                ++g_ot_direct_last_env_packets;
            }
            else
            {
                ++g_ot_direct_last_other_packets;
            }

            for (uint32_t i = 0u; i < count; ++i)
            {
                fm_gpu_gp0_write(
                    cpu->read_word(guest_node + 4u + i * 4u)
                );
            }

            b45_prev2_node = b45_prev1_node;
            b45_prev2_word = b45_prev1_word;
            b45_prev1_node = guest_node;
            b45_prev1_word = first_word;

            ++packets;
            words += count;
        }

        g_ot_direct_last_stop = guest_node;

        if (next24 == 0x00FFFFFFu)
        {
            ended = 1;
            ++nodes;
            break;
        }

        if (next24 >= 0x00200000u || (next24 & 3u) != 0u)
        {
            ++g_ot_direct_bad;
            break;
        }

        node = 0x80000000u | next24;
    }

ot_done:
    g_ot_direct_last_nodes = nodes;
    g_ot_direct_last_packets = packets;
    g_ot_direct_last_words = words;

    if (ended || packets != 0u)
    {
        ++g_ot_direct_ok;
        return 1;
    }

    return 0;
}


/*
 * ============================================================
 * Fade / transition bridge
 * ============================================================
 *
 * Le boot est actuellement bloqué avant FUN_8002DF60 :
 *
 *   FUN_80044084
 *     -> FUN_800158F4
 *       -> FUN_8001569C
 *         EB24D = FF
 *         EB24E = 80
 *       -> FUN_800158B4
 *          attend tant que (EB24E & 80) != 0
 *
 * Sur PS1, FUN_80015400 -> FUN_8001522C fait progresser EB24C
 * vers EB24D à chaque service de frame, puis efface bit7.
 *
 * Notre bring-up 3DS ne livre pas encore toute la chaîne
 * d'événements/IRQ de façon identique. On reproduit uniquement
 * cette machine de transition en RAM, sans fabriquer d'image.
 */

static uint8_t g_fade_current = 0;
static uint8_t g_fade_target = 0;
static uint8_t g_fade_flags = 0;
static uint8_t g_fade_step = 0;
static uint32_t g_fade_scale = 0;

static uint32_t g_fade_bridge_ticks = 0;
static uint32_t g_fade_bridge_completions = 0;


static void fm_service_fade_bridge(void)
{
    uint8_t current =
        fm_memory_read_byte(
            0x800EB24Cu
        );

    uint8_t target =
        fm_memory_read_byte(
            0x800EB24Du
        );

    uint8_t flags =
        fm_memory_read_byte(
            0x800EB24Eu
        );

    uint8_t step =
        fm_memory_read_byte(
            0x800EB24Fu
        );

    uint32_t scale =
        fm_memory_read_word(
            0x8009C43Cu
        );


    g_fade_current =
        current;

    g_fade_target =
        target;

    g_fade_flags =
        flags;

    g_fade_step =
        step;

    g_fade_scale =
        scale;


    /*
     * Rien à faire si aucune transition n'est active.
     */
    if (
        (
            flags
            &
            0x80u
        )
        ==
        0
    )
    {
        return;
    }


    /*
     * Le bit0 sélectionne un autre chemin (FUN_800150F4).
     * Ne pas l'émuler ici : le bridge cible uniquement la
     * transition linéaire qui bloque le boot.
     */
    if (
        flags
        &
        0x01u
    )
    {
        return;
    }


    uint32_t delta =
        (uint32_t)step
        *
        scale;


    /*
     * Si le multiplicateur vaut zéro, ne pas inventer de vitesse.
     * Le diagnostic l'affichera directement.
     */
    if (delta == 0u)
    {
        return;
    }


    ++g_fade_bridge_ticks;


    if (current != target)
    {
        uint32_t next;


        if (current < target)
        {
            next =
                (uint32_t)current
                +
                delta;


            if (next > target)
            {
                next =
                    target;
            }
        }
        else
        {
            if (delta >= current)
            {
                next =
                    0;
            }
            else
            {
                next =
                    (uint32_t)current
                    -
                    delta;
            }


            if (next < target)
            {
                next =
                    target;
            }
        }


        fm_memory_write_byte(
            0x800EB24Cu,
            (uint8_t)next
        );


        g_fade_current =
            (uint8_t)next;


        return;
    }


    /*
     * Reproduire le cas de fin de transition observé dans
     * FUN_8001522C.
     */
    uint8_t result_flags =
        flags
        &
        0x7Fu;


    /*
     * La fonction originale nettoie d'abord 0x86.
     */
    uint8_t cleaned_flags =
        flags
        &
        0x79u;


    fm_memory_write_byte(
        0x800EB24Eu,
        cleaned_flags
    );


    if (current == 0xFFu)
    {
        /*
         * FUN_80015C18()
         */
        fm_memory_write_byte(
            0x8009C4B8u,
            1u
        );


        fm_memory_write_byte(
            0x8009C4C4u,
            0u
        );

        fm_memory_write_byte(
            0x8009C4C5u,
            0u
        );


        /*
         * Couleurs/états cibles -> courants.
         */
        fm_memory_write_byte(
            0x8009C4BBu,
            fm_memory_read_byte(
                0x8009C4BEu
            )
        );

        fm_memory_write_byte(
            0x8009C4BAu,
            fm_memory_read_byte(
                0x8009C4BDu
            )
        );

        fm_memory_write_byte(
            0x8009C4B9u,
            fm_memory_read_byte(
                0x8009C4BCu
            )
        );


        result_flags =
            cleaned_flags;
    }


    /*
     * Cas courant du boot :
     * 80 -> 00 lorsque C atteint D=FF.
     */
    fm_memory_write_byte(
        0x800EB24Eu,
        result_flags
    );


    g_fade_flags =
        result_flags;


    ++g_fade_bridge_completions;
}


static void fm_update_game_state_debug(void)
{
    uint8_t state =
        fm_memory_read_byte(
            0x8009C60Au
        );


    if (state != g_main_state_last)
    {
        ++g_main_state_changes;

        g_main_state_last =
            state;

        g_main_state_stable_frames =
            0;
    }
    else
    {
        ++g_main_state_stable_frames;
    }


    g_main_state =
        state;


    g_main_state_60c =
        fm_memory_read_byte(
            0x8009C60Cu
        );

    g_main_state_60d =
        fm_memory_read_byte(
            0x8009C60Du
        );

    g_main_state_60e =
        fm_memory_read_byte(
            0x8009C60Eu
        );


    g_main_render_ctx =
        fm_memory_read_word(
            0x8009C414u
        );


    g_main_frame_target =
        fm_memory_read_byte(
            0x8009C424u
        );


    g_main_frame_done =
        (int32_t)
            fm_memory_read_word(
                0x8009C428u
            );


    g_main_flags_6a0 =
        fm_memory_read_word(
            0x8009C6A0u
        );


    g_main_flags_710 =
        fm_memory_read_word(
            0x8009C710u
        );


    g_main_flags_72c =
        fm_memory_read_word(
            0x8009C72Cu
        );


    /*
     * STR context seulement observé ici.
     * On ne force plus rien : la capture précédente a prouvé que
     * le lecteur STR n'est même pas encore initialisé.
     */
    g_str_intro_last_base =
        fm_memory_read_word(
            0x8009C818u
        );


    g_str_intro_last_done =
        fm_memory_read_byte(
            0x8009C3EBu
        );
}


/*
 * Force la fin du premier flux STR depuis la boucle hôte.
 *
 * Pourquoi ici et pas uniquement dans le dispatcher ?
 *
 * FUN_8006A4D8 peut être appelée directement par du code statiquement
 * recompilé. Dans ce cas, le dispatcher principal ne voit jamais son
 * adresse exacte et l'interception par "phys == 0x0006A4D8" ne peut
 * pas se déclencher.
 *
 * En revanche, les variables de contexte STR sont en RAM PS1 et sont
 * observables depuis la boucle 3DS :
 *
 *   8009C818 = base/workspace du lecteur vidéo
 *   8009C3EB = drapeau "stream finished"
 *
 * On attend que le workspace soit réellement initialisé, que l'ISO
 * soit trouvé et que VSync tourne déjà, puis on positionne une seule
 * fois le drapeau de fin.
 */
static void fm_try_force_intro_stream_end(
    int game_running
)
{
    g_str_intro_last_base =
        fm_memory_read_word(
            0x8009C818u
        );


    g_str_intro_last_done =
        fm_memory_read_byte(
            0x8009C3EBu
        );


    if (
        !g_str_intro_skip_pending
        ||
        !game_running
        ||
        !g_cd_search_ok
        ||
        g_vsync_hle_calls < 120u
        ||
        g_str_intro_last_base == 0u
    )
    {
        return;
    }


    /*
     * Si le jeu l'a déjà terminé naturellement, considérer le skip
     * comme consommé sans modifier la RAM.
     */
    if (g_str_intro_last_done != 0u)
    {
        g_str_intro_skip_pending =
            0;


        return;
    }


    fm_memory_write_byte(
        0x8009C3EBu,
        1u
    );


    g_str_intro_last_done =
        1u;


    g_str_intro_skip_pending =
        0;


    ++g_str_intro_skip_count;
}


static void fm_capture_guest_string(
    CPUState *cpu,
    uint32_t guest_ptr
)
{
    g_game_log_ptr =
        guest_ptr;

    ++g_game_log_count;


    if (
        !cpu
        ||
        guest_ptr == 0
    )
    {
        strncpy(
            g_game_log,
            "<NULL>",
            sizeof(g_game_log) - 1
        );

        g_game_log[
            sizeof(g_game_log) - 1
        ] =
            '\0';

        return;
    }


    unsigned i = 0;


    while (
        i < sizeof(g_game_log) - 1
    )
    {
        uint8_t c =
            cpu->read_byte(
                guest_ptr + i
            );


        /*
         * Conserver uniquement quelque chose d'affichable sur la
         * console 3DS. Les CR/LF deviennent des espaces.
         */
        if (
            c == '\r'
            ||
            c == '\n'
            ||
            c == '\t'
        )
        {
            c =
                ' ';
        }


        g_game_log[i] =
            (char)c;


        if (c == 0)
        {
            break;
        }


        ++i;
    }


    g_game_log[
        sizeof(g_game_log) - 1
    ] =
        '\0';
}


static uint32_t fm_bcd_to_u32(uint8_t value)
{
    return
        ((value >> 4) * 10u)
        +
        (value & 0x0Fu);
}


static void fm_cd_hle_reset(void)
{
    memset(
        g_cd_sector,
        0,
        sizeof(g_cd_sector)
    );

    g_cd_lba = 0;
    g_cd_pos = 2048;
    g_cd_last_cmd = 0;
    g_cd_sector_count = 0;
    g_cd_reading = 0;
    g_cd_error = 0;

    g_cd_search_path[0] = '\0';
    g_cd_search_lba = 0;
    g_cd_search_size = 0;
    g_cd_search_ok = 0;

    g_bios_debug_addr = 0;
    g_bios_debug_fn = 0;
    g_bios_debug_result = -1;

    g_game_log[0] = '\0';
    g_game_log_ptr = 0;
    g_game_log_count = 0;

    g_vsync_wait_active = 0;
    g_vsync_wait_until_frame = 0;
    g_vsync_wait_mode = 0;

    g_vsync_hle_calls = 0;
    g_vsync_hle_wait_calls = 0;
    g_vsync_hle_query_calls = 0;
    g_vsync_hle_mode1_calls = 0;
    g_vsync_hle_mode1_nonzero = 0;
    g_vsync_hle_mode1_last = 0;
    g_vsync_hle_mode1_max = 0;
    g_vsync_host_epoch_ms = osGetTime();
    g_vsync_hle_last_mode = 0;

    g_b108_vsync_last_sync_frame = 0u;
    g_b108_vsync_sync_valid = 0u;
    g_b108_vsync_mode0 = 0u;
    g_b108_vsync_modeN = 0u;
    g_b108_vsync_immediate = 0u;
    g_b108_vsync_waited = 0u;
    g_b108_vsync_last_target = 0u;

    g_str_intro_skip_pending = 1;
    g_str_intro_skip_count = 0;

    g_str_intro_last_base = 0;
    g_str_intro_last_done = 0;

    g_main_state = 0;
    g_main_state_last = 0xFFu;
    g_main_state_changes = 0;
    g_main_state_stable_frames = 0;

    g_main_state_60c = 0;
    g_main_state_60d = 0;
    g_main_state_60e = 0;

    g_main_render_ctx = 0;
    g_main_frame_target = 0;
    g_main_frame_done = 0;

    g_main_flags_6a0 = 0;
    g_main_flags_710 = 0;
    g_main_flags_72c = 0;

    memset(
        g_trace_pc,
        0,
        sizeof(g_trace_pc)
    );

    g_trace_count = 0;
    g_trace_last_phys = 0xFFFFFFFFu;

    g_hit_startup = 0;
    g_hit_service = 0;
    g_hit_load_wait = 0;
    g_b31_req_snap = 0;
    g_b31_req_10 = g_b31_req_18 = g_b31_req_1c = g_b31_req_20 = 0;
    g_b31_req_24 = g_b31_req_2c = g_b31_req_34 = g_b31_req_40 = 0;
    g_b31_req_44 = 0;
    g_b31_req_46 = g_b31_req_47 = 0;
    g_b31_r137_ra = g_b31_r137_gp = 0;
    g_b31_r137_a0 = g_b31_r137_a1 = g_b31_r137_a2 = g_b31_r137_a3 = 0;
    g_b31_c460 = g_b31_c484 = g_b31_tbl0 = 0;
    g_b32_getsec_calls = 0;
    g_b32_getsec_ok = 0;
    g_b32_getsec_fail = 0;
    g_b32_last_req = 0;
    g_b32_last_lba = 0;
    g_b32_last_dst = 0;
    g_b32_last_bytes = 0;
    g_b32_last_remaining = 0;
    g_b32_last_rc = 0;

    g_b56_stream_reads = 0u;
    g_b56_stream_first_lba = 0u;
    g_b56_stream_last_lba = 0u;


    g_b57_req = 0u;
    g_b57_base_lba = 0u;
    g_b57_next_lba = 0u;
    g_b57_last_remaining = 0u;
    g_b57_resets = 0u;
    g_b57_read_index = 0u;


    g_b59_pal_patch_count = 0u;
    g_b59_pal_patch_before = 0u;
    g_b59_pal_patch_after = 0u;


    g_b60_ent_a0 = 0u;
    g_b60_ent_a1 = 0u;
    g_b60_ent_a2 = 0u;
    g_b60_ent_a3 = 0u;
    g_b60_ent_s0 = 0u;
    g_b60_ent_s1 = 0u;
    g_b60_ent_s2 = 0u;
    g_b60_ent_s3 = 0u;
    g_b60_ent_sp = 0u;
    g_b60_ent_ra = 0u;

    g_b60_ret_v0 = 0u;
    g_b60_ret_s0 = 0u;
    g_b60_ret_s1 = 0u;
    g_b60_ret_s2 = 0u;
    g_b60_ret_s3 = 0u;


    g_b61_skip_request = 0u;
    g_b61_bridge_count = 0u;
    g_b61_old_v0 = 0u;
    g_b61_at_return = 0u;


    g_b62_hle_nclip = 0u;
    g_b62_hle_rtp4 = 0u;
    g_b62_hle_ra3 = 0u;
    g_b62_hle_ra4 = 0u;
    g_b62_last_helper = 0u;
    g_b62_last_otz = 0u;
    g_b32_43e_returned = 0;
    g_b32_43e_return_frame = 0;
    g_b35_finalizer_active = 0;
    g_b35_finalizer_resume = 0;
    g_b35_finalizer_started = 0;
    g_b35_finalizer_done = 0;
    g_b35_c460_before = 0;
    g_b35_c460_after = 0;
    g_hit_delay_wait = 0;
    g_hit_intro_init = 0;
    g_hit_boot_loop = 0;
    g_hit_fade_wait = 0;
    g_hit_main_loop = 0;
    g_hit_str = 0;
    g_hit_ov16 = 0;
    g_hit_ov18 = 0;


    g_b47_m_43eb8 = 0u;
    g_b47_m_43f3c = 0u;
    g_b47_m_43f44 = 0u;
    g_b47_m_43f4c = 0u;
    g_b47_m_43f54 = 0u;
    g_b47_m_43ff8 = 0u;
    g_b47_m_44054 = 0u;
    g_b47_m_44064 = 0u;
    g_b47_m_4406c = 0u;
    g_b47_680f4_enter = 0u;
    g_b47_68160_enter = 0u;
    g_b47_68160_return = 0u;
    g_b47_68160_v0_zero = 0u;
    g_b47_68160_v0_nonzero = 0u;
    g_b47_68160_last_v0 = 0u;
    g_b47_68160_last_ra = 0u;
    g_b47_last_milestone = 0u;
    g_b47_last_milestone_frame = 0u;


    g_b49_m_43ec0 = 0u;
    g_b49_m_43ecc = 0u;
    g_b49_m_43f08 = 0u;
    g_b49_m_43f20 = 0u;
    g_b49_m_43f2c = 0u;
    g_b49_m_43f34 = 0u;

    g_b49_fn_1569c = 0u;
    g_b49_fn_40350 = 0u;
    g_b49_fn_403d0 = 0u;
    g_b49_fn_42bd8 = 0u;
    g_b49_fn_43a78 = 0u;
    g_b49_fn_7e8e8 = 0u;

    g_b49_ra_1569c = 0u;
    g_b49_ra_40350 = 0u;
    g_b49_ra_403d0 = 0u;
    g_b49_ra_42bd8 = 0u;
    g_b49_ra_43a78 = 0u;
    g_b49_ra_7e8e8 = 0u;


    g_b50_cleanup_triggered = 0u;
    g_b50_cleanup_done = 0u;
    g_b50_cleanup_active = 0u;
    g_b50_c460_before = 0u;
    g_b50_c460_after = 0u;
    g_b50_c484_before = 0u;
    g_b50_c484_after = 0u;
    g_b50_remaining = 0u;


    g_b51_rearm_count = 0u;
    g_b51_last_rem = 0u;
    g_b51_last_type = 0u;
    g_b51_last_c460 = 0u;
    g_b51_last_c484 = 0u;


    g_b52_418c0_hits = 0u;
    g_b52_418c0_returns = 0u;
    g_b52_41bb4_hits = 0u;
    g_b52_41d38_hits = 0u;
    g_b52_41f64_hits = 0u;
    g_b52_41f74_hits = 0u;

    g_b52_ra = 0u;
    g_b52_a0 = 0u;
    g_b52_a1 = 0u;
    g_b52_a2 = 0u;

    g_b52_data_ptr = 0u;
    g_b52_data_w0 = 0u;
    g_b52_data_w1 = 0u;
    g_b52_data_w2 = 0u;
    g_b52_obj_flags = 0u;
    g_b52_item_count = 0u;
    g_b52_obj_type = 0u;

    g_b52_cd4_a0 = 0u;
    g_b52_last_hot_pc = 0u;


    g_b53_fast43cd4_hits = 0u;
    g_b53_fast43cd4_last_in = 0u;
    g_b53_fast43cd4_last_out = 0u;

    g_hit_7fcbc = 0;
    g_hit_82158 = 0;
    g_hit_12cd4 = 0;

    g_ra_7fcbc = 0;
    g_ra_82158 = 0;
    g_ra_12cd4 = 0;

    g_hit_401a4 = 0;
    g_hit_74968 = 0;
    g_hit_vblank_cb = 0;

    g_ra_401a4 = 0;
    g_sp_401a4 = 0;
    g_ra_74968 = 0;
    g_ra_vblank_cb = 0;
    g_fast401_forced = 0;
    g_fast401_frame = 0;
    g_ra_43e3c = 0;
    g_sp_43e3c = 0;
    g_fast43e_forced = 0;
    g_fast43e_frame = 0;

    g_direct2df_active = 0;
    g_direct2df_start_frame = 0;
    g_direct2df_calls = 0;
    g_direct2df_returns = 0;
    g_direct2df_last_pc = 0;

    g_b16_slice_yields = 0;
    g_b16_slice_last_ms = 0;
    g_b16_slice_max_ms = 0;
    g_b16_last_handoffs = 0;

    g_hit_85ddc = 0;
    g_hit_85_range = 0;
    g_85_last_phys = 0;
    g_85_ra = 0;
    g_85_sp = 0;
    g_85_a0 = 0;
    g_85_a1 = 0;
    g_85_a2 = 0;
    g_85_a3 = 0;
    g_85_v0 = 0;
    g_85_t0 = 0;
    g_85_t1 = 0;
    g_85_s0 = 0;
    g_85_s1 = 0;
    memset(g_85_ops, 0, sizeof(g_85_ops));
    memset(g_12e_ops, 0, sizeof(g_12e_ops));


    g_hle_85d98_calls = 0;
    g_hle_85d98_last_src = 0;
    g_hle_85d98_last_dst = 0;
    g_hle_85d98_src_length = 0;
    g_hle_85d98_src_org = 0;
    g_hle_85d98_src_offset = 0;
    g_hle_85d98_src_point = 0;
    g_hle_85d98_src_tag = 0;
    g_hle_85d98_dst_length = 0;
    g_hle_85d98_dst_org = 0;
    g_hle_85d98_dst_offset = 0;
    g_hle_85d98_dst_point = 0;
    g_hle_85d98_dst_tag = 0;
    g_hle_85d98_bad_desc = 0;

    g_vram_view_x = 0;
    g_vram_view_y = 0;
    g_vram_view_nonzero = 0;

    g_vblank_registered_cb = 0;
    g_vblank_registered_gp = 0;
    g_vblank_bridge_ticks = 0;
    g_vblank_bridge_target = 0;
    g_vblank_bridge_target_41c = 0;
    g_vblank_bridge_target_428 = 0;
    g_vblank_bridge_before = 0;
    g_vblank_bridge_after = 0;
    g_vblank_bridge_41c_before = 0;
    g_vblank_bridge_41c_after = 0;
    g_vblank_bridge_428_before = 0;
    g_vblank_bridge_428_after = 0;
    g_vblank_bridge_sig_ok = 0;

    g_vblank_sig_words[0] = 0;
    g_vblank_sig_words[1] = 0;
    g_vblank_sig_words[2] = 0;
    g_vblank_sig_words[3] = 0;

    g_irq_exec_calls = 0;
    g_irq_exec_ok = 0;
    g_irq_exec_fail = 0;
    g_irq_exec_last_pc = 0;
    g_irq_exec_last_phys = 0;
    g_irq_exec_last_handoffs = 0;
    g_irq_exec_hit_3ce34 = 0;
    g_irq_exec_hit_vsync = 0;
    g_irq_exec_last_code = 0;
    g_irq_exec_last_probe_reason = 0;
    g_irq_exec_last_interp_reason = 0;

    g_hit_8111c = 0;
    g_hit_82168 = 0;
    g_hit_8219c = 0;

    g_ra_8111c = 0;
    g_ra_82168 = 0;
    g_ra_8219c = 0;

    g_82168_a0 = 0;
    g_82168_a1 = 0;
    g_82168_a2 = 0;
    g_82168_a3 = 0;
    g_82168_v0 = 0;
    g_82168_t0 = 0;
    g_82168_t1 = 0;
    g_82168_sp = 0;

    for (unsigned i = 0; i < 8u; ++i)
    {
        g_82168_ops[i] = 0;
    }

    g_vsync_stack_sp = 0;
    memset(
        g_vsync_stack_ra,
        0,
        sizeof(g_vsync_stack_ra)
    );
    g_vsync_stack_count = 0;
    g_vsync_s0 = 0;
    g_vsync_s1 = 0;

    g_fade_current = 0;
    g_fade_target = 0;
    g_fade_flags = 0;
    g_fade_step = 0;
    g_fade_scale = 0;

    g_fade_bridge_ticks = 0;
    g_fade_bridge_completions = 0;
}



/*
 * ============================================================
 * B21 - TIM asset probe
 * ============================================================
 *
 * Objectif court terme : obtenir de VRAIS pixels du jeu sur la 3DS
 * sans attendre que tout le pipeline de boot/OT soit parfait.
 *
 * On cherche directement les images TIM PS1 presentes sur le disque,
 * on les decode en RGB555, puis on les affiche sur l'ecran superieur.
 *
 * Ce mode ne remplace pas le rendu du jeu : il sert a valider rapidement
 * la chaine disque -> ressource graphique -> decode TIM -> affichage 3DS.
 * Le runtime du jeu continue en parallele et reste visible avec Y.
 */

typedef struct FMTimProbe
{
    int active;
    int found;
    int show;
    int using_named_file;
    int error;

    uint32_t start_lba;
    uint32_t end_lba;
    uint32_t scan_lba;
    uint32_t scan_byte_offset;

    uint32_t scanned_sectors;
    uint32_t read_errors;
    uint32_t candidates;
    uint32_t images_found;

    uint64_t found_abs_byte;
    uint32_t found_lba;
    uint32_t found_in_sector;

    uint32_t mode;
    uint32_t flags;
    uint32_t width;
    uint32_t height;
    uint32_t clut_colors;

    char target[64];
} FMTimProbe;

static FMTimProbe g_tim_probe;

static uint8_t g_tim_sector_cache[2048];
static uint32_t g_tim_sector_cache_lba = 0xFFFFFFFFu;
static int g_tim_sector_cache_valid = 0;


/*
 * Lit des octets a une position absolue du data track 2048-byte/sector.
 */
static int fm_tim_read_abs(
    uint64_t absolute_byte,
    void *dst,
    uint32_t size
)
{
    uint8_t *out = (uint8_t *)dst;

    while (size != 0u)
    {
        uint32_t lba =
            (uint32_t)(absolute_byte / 2048u);

        uint32_t in_sector =
            (uint32_t)(absolute_byte % 2048u);

        if (
            !g_tim_sector_cache_valid
            || g_tim_sector_cache_lba != lba
        )
        {
            if (
                fm_disc_read_sector(
                    lba,
                    g_tim_sector_cache
                )
                != 0
            )
            {
                g_tim_sector_cache_valid = 0;
                return 0;
            }

            g_tim_sector_cache_lba = lba;
            g_tim_sector_cache_valid = 1;
        }

        uint32_t chunk =
            2048u - in_sector;

        if (chunk > size)
        {
            chunk = size;
        }

        memcpy(
            out,
            g_tim_sector_cache + in_sector,
            chunk
        );

        out += chunk;
        absolute_byte += chunk;
        size -= chunk;
    }

    return 1;
}


static int fm_tim_read_u16(
    uint64_t absolute_byte,
    uint16_t *value
)
{
    uint8_t b[2];

    if (!fm_tim_read_abs(absolute_byte, b, sizeof(b)))
    {
        return 0;
    }

    *value =
        (uint16_t)b[0]
        |
        ((uint16_t)b[1] << 8);

    return 1;
}


static int fm_tim_read_u32(
    uint64_t absolute_byte,
    uint32_t *value
)
{
    uint8_t b[4];

    if (!fm_tim_read_abs(absolute_byte, b, sizeof(b)))
    {
        return 0;
    }

    *value =
        (uint32_t)b[0]
        |
        ((uint32_t)b[1] << 8)
        |
        ((uint32_t)b[2] << 16)
        |
        ((uint32_t)b[3] << 24);

    return 1;
}


/*
 * Decode un TIM candidate directement depuis disc.bin.
 * Retourne 1 uniquement si la structure est suffisamment coherente
 * et qu'une image a effectivement ete produite dans "pixels".
 */
static int fm_tim_decode_at(
    uint64_t base,
    uint16_t *pixels
)
{
    uint32_t magic = 0;
    uint32_t flags = 0;

    if (
        !fm_tim_read_u32(base + 0u, &magic)
        || !fm_tim_read_u32(base + 4u, &flags)
    )
    {
        return 0;
    }

    if (magic != 0x00000010u)
    {
        return 0;
    }

    /*
     * TIM standard : bits 0..2 = profondeur, bit3 = CLUT.
     * Refuser les autres bits permet d'eliminer presque tous les
     * faux positifs trouves en scannant des donnees compressees.
     */
    if ((flags & 0xFFFFFFF0u) != 0u)
    {
        return 0;
    }

    uint32_t mode = flags & 0x07u;
    int has_clut = (flags & 0x08u) != 0u;

    if (mode > 3u)
    {
        return 0;
    }

    if ((mode == 0u || mode == 1u) && !has_clut)
    {
        return 0;
    }

    uint64_t pos = base + 8u;

    uint16_t palette[256];
    uint32_t palette_count = 0u;

    memset(
        palette,
        0,
        sizeof(palette)
    );

    if (has_clut)
    {
        uint32_t block_size = 0;
        uint16_t clut_x = 0;
        uint16_t clut_y = 0;
        uint16_t clut_w = 0;
        uint16_t clut_h = 0;

        if (
            !fm_tim_read_u32(pos + 0u, &block_size)
            || !fm_tim_read_u16(pos + 4u, &clut_x)
            || !fm_tim_read_u16(pos + 6u, &clut_y)
            || !fm_tim_read_u16(pos + 8u, &clut_w)
            || !fm_tim_read_u16(pos + 10u, &clut_h)
        )
        {
            return 0;
        }

        (void)clut_x;
        (void)clut_y;

        uint32_t expected_colors =
            (uint32_t)clut_w
            * (uint32_t)clut_h;

        if (
            block_size < 12u
            || block_size > 0x00040000u
            || clut_w == 0u
            || clut_h == 0u
            || expected_colors == 0u
            || expected_colors > 4096u
            || 12u + expected_colors * 2u > block_size
        )
        {
            return 0;
        }

        /*
         * Pour les TIM a plusieurs palettes, utiliser la premiere.
         * C'est suffisant pour obtenir une vraie image visible.
         */
        palette_count = clut_w;

        if (palette_count > 256u)
        {
            palette_count = 256u;
        }

        for (uint32_t i = 0u; i < palette_count; ++i)
        {
            if (
                !fm_tim_read_u16(
                    pos + 12u + i * 2u,
                    &palette[i]
                )
            )
            {
                return 0;
            }
        }

        pos += block_size;
    }

    uint32_t image_block_size = 0;
    uint16_t image_x = 0;
    uint16_t image_y = 0;
    uint16_t width_words = 0;
    uint16_t src_h16 = 0;

    if (
        !fm_tim_read_u32(pos + 0u, &image_block_size)
        || !fm_tim_read_u16(pos + 4u, &image_x)
        || !fm_tim_read_u16(pos + 6u, &image_y)
        || !fm_tim_read_u16(pos + 8u, &width_words)
        || !fm_tim_read_u16(pos + 10u, &src_h16)
    )
    {
        return 0;
    }

    (void)image_x;
    (void)image_y;

    if (
        image_block_size < 12u
        || image_block_size > 0x00800000u
        || width_words == 0u
        || src_h16 == 0u
    )
    {
        return 0;
    }

    uint32_t row_bytes =
        (uint32_t)width_words * 2u;

    uint32_t src_w = 0u;

    switch (mode)
    {
        case 0u:
            src_w = (uint32_t)width_words * 4u;
            break;

        case 1u:
            src_w = (uint32_t)width_words * 2u;
            break;

        case 2u:
            src_w = (uint32_t)width_words;
            break;

        case 3u:
            src_w = row_bytes / 3u;
            break;

        default:
            return 0;
    }

    uint32_t src_h =
        (uint32_t)src_h16;

    if (
        src_w < 4u
        || src_h < 4u
        || src_w > 2048u
        || src_h > 1024u
        || row_bytes > 16384u
        || 12u + row_bytes * src_h > image_block_size
    )
    {
        return 0;
    }

    if (
        mode == 0u
        && palette_count < 16u
    )
    {
        return 0;
    }

    if (
        mode == 1u
        && palette_count < 256u
    )
    {
        return 0;
    }

    uint8_t *row =
        malloc(
            row_bytes
        );

    uint16_t *decoded_row =
        malloc(
            src_w
            * sizeof(uint16_t)
        );

    if (!row || !decoded_row)
    {
        free(row);
        free(decoded_row);
        return 0;
    }

    memset(
        pixels,
        0,
        320u * 256u * sizeof(uint16_t)
    );

    uint32_t out_w = src_w;
    uint32_t out_h = src_h;

    if (out_w > 320u)
    {
        out_h =
            (uint32_t)(
                ((uint64_t)out_h * 320u)
                /
                out_w
            );

        out_w = 320u;
    }

    if (out_h > 256u)
    {
        out_w =
            (uint32_t)(
                ((uint64_t)out_w * 256u)
                /
                out_h
            );

        out_h = 256u;
    }

    if (out_w == 0u)
        out_w = 1u;

    if (out_h == 0u)
        out_h = 1u;

    uint32_t dst_x =
        (320u - out_w) / 2u;

    uint32_t dst_y =
        (256u - out_h) / 2u;

    uint32_t last_src_y = 0xFFFFFFFFu;

    for (uint32_t dy = 0u; dy < out_h; ++dy)
    {
        uint32_t src_y =
            (uint32_t)(
                ((uint64_t)dy * src_h)
                /
                out_h
            );

        if (src_y >= src_h)
        {
            src_y = src_h - 1u;
        }

        if (src_y != last_src_y)
        {
            uint64_t row_abs =
                pos
                + 12u
                + (uint64_t)src_y * row_bytes;

            if (
                !fm_tim_read_abs(
                    row_abs,
                    row,
                    row_bytes
                )
            )
            {
                free(row);
                free(decoded_row);
                return 0;
            }

            if (mode == 0u)
            {
                for (uint32_t x = 0u; x < src_w; ++x)
                {
                    uint8_t packed =
                        row[x >> 1];

                    uint8_t index =
                        (x & 1u)
                            ? (packed >> 4)
                            : (packed & 0x0Fu);

                    decoded_row[x] =
                        palette[index];
                }
            }
            else if (mode == 1u)
            {
                for (uint32_t x = 0u; x < src_w; ++x)
                {
                    decoded_row[x] =
                        palette[row[x]];
                }
            }
            else if (mode == 2u)
            {
                for (uint32_t x = 0u; x < src_w; ++x)
                {
                    decoded_row[x] =
                        (uint16_t)row[x * 2u]
                        |
                        ((uint16_t)row[x * 2u + 1u] << 8);
                }
            }
            else
            {
                for (uint32_t x = 0u; x < src_w; ++x)
                {
                    uint32_t o = x * 3u;

                    uint8_t r = row[o + 0u];
                    uint8_t g = row[o + 1u];
                    uint8_t b = row[o + 2u];

                    decoded_row[x] =
                        (uint16_t)(
                            (r >> 3)
                            |
                            ((uint16_t)(g >> 3) << 5)
                            |
                            ((uint16_t)(b >> 3) << 10)
                        );
                }
            }

            last_src_y = src_y;
        }

        uint16_t *dst =
            pixels
            + (dst_y + dy) * 320u
            + dst_x;

        for (uint32_t dx = 0u; dx < out_w; ++dx)
        {
            uint32_t src_x =
                (uint32_t)(
                    ((uint64_t)dx * src_w)
                    /
                    out_w
                );

            if (src_x >= src_w)
            {
                src_x = src_w - 1u;
            }

            dst[dx] =
                decoded_row[src_x];
        }
    }

    free(row);
    free(decoded_row);

    g_tim_probe.mode = mode;
    g_tim_probe.flags = flags;
    g_tim_probe.width = src_w;
    g_tim_probe.height = src_h;
    g_tim_probe.clut_colors = palette_count;

    return 1;
}


static void fm_tim_probe_begin_full_disc(void)
{
    memset(
        &g_tim_probe,
        0,
        sizeof(g_tim_probe)
    );

    g_tim_probe.active = 1;
    g_tim_probe.start_lba = 0u;

    /*
     * Valeur volontairement large. Le scan s'arrete egalement si
     * plusieurs lectures consecutives echouent.
     */
    g_tim_probe.end_lba = 400000u;
    g_tim_probe.scan_lba = 0u;
    g_tim_probe.scan_byte_offset = 0u;

    strncpy(
        g_tim_probe.target,
        "DISC FULL SCAN",
        sizeof(g_tim_probe.target) - 1u
    );
}


static void fm_tim_probe_begin(void)
{
    static const char *paths[] =
    {
        "\\M\\MRG\\SU\\SU.MRG;1",
        "\\M\\MRG\\SU\\SU.MRG",
        "\\MRG\\SU\\SU.MRG;1",
        "\\DATA\\SU.MRG;1",
        "\\SU.MRG;1"
    };

    memset(
        &g_tim_probe,
        0,
        sizeof(g_tim_probe)
    );

    uint32_t lba = 0u;
    uint32_t size = 0u;

    for (
        unsigned i = 0u;
        i < sizeof(paths) / sizeof(paths[0]);
        ++i
    )
    {
        if (
            fm_disc_find_file(
                paths[i],
                &lba,
                &size
            )
        )
        {
            g_tim_probe.active = 1;
            g_tim_probe.using_named_file = 1;
            g_tim_probe.start_lba = lba;
            g_tim_probe.end_lba =
                lba
                +
                (size + 2047u) / 2048u;

            g_tim_probe.scan_lba = lba;
            g_tim_probe.scan_byte_offset = 0u;

            strncpy(
                g_tim_probe.target,
                paths[i],
                sizeof(g_tim_probe.target) - 1u
            );

            return;
        }
    }

    fm_tim_probe_begin_full_disc();
}


static void fm_tim_probe_next(void)
{
    if (!g_tim_probe.found)
    {
        return;
    }

    uint64_t resume =
        g_tim_probe.found_abs_byte
        + 4u;

    g_tim_probe.scan_lba =
        (uint32_t)(resume / 2048u);

    g_tim_probe.scan_byte_offset =
        (uint32_t)(resume % 2048u);

    g_tim_probe.active = 1;
    g_tim_probe.found = 0;
    g_tim_probe.show = 0;
    g_tim_probe.error = 0;
}


/*
 * Scanner incrementiel : aucun blocage de plusieurs secondes.
 * "sector_budget" peut etre eleve tant que le jeu est en pause.
 */
static void fm_tim_probe_step(
    uint16_t *pixels,
    uint32_t sector_budget
)
{
    if (
        !g_tim_probe.active
        || g_tim_probe.found
        || !pixels
    )
    {
        return;
    }

    uint32_t consecutive_errors = 0u;

    while (
        sector_budget-- != 0u
        && g_tim_probe.active
    )
    {
        if (
            g_tim_probe.scan_lba
            >=
            g_tim_probe.end_lba
        )
        {
            /*
             * Si la cible SU.MRG ne contenait aucun TIM, continuer
             * automatiquement sur le disque complet.
             */
            if (g_tim_probe.using_named_file)
            {
                fm_tim_probe_begin_full_disc();
                continue;
            }

            g_tim_probe.active = 0;
            g_tim_probe.error = 2;
            break;
        }

        uint8_t sector[2048];

        if (
            fm_disc_read_sector(
                g_tim_probe.scan_lba,
                sector
            )
            != 0
        )
        {
            ++g_tim_probe.read_errors;
            ++consecutive_errors;
            ++g_tim_probe.scan_lba;
            g_tim_probe.scan_byte_offset = 0u;

            if (consecutive_errors >= 16u)
            {
                g_tim_probe.active = 0;
                g_tim_probe.error = 1;
            }

            continue;
        }

        consecutive_errors = 0u;

        uint32_t start =
            g_tim_probe.scan_byte_offset;

        if (start > 2040u)
        {
            start = 0u;
        }

        /*
         * TIM est normalement aligne, mais scanner octet par octet
         * rend le probe robuste aux conteneurs MRG.
         */
        for (uint32_t p = start; p + 8u <= 2048u; ++p)
        {
            if (
                sector[p + 0u] != 0x10u
                || sector[p + 1u] != 0x00u
                || sector[p + 2u] != 0x00u
                || sector[p + 3u] != 0x00u
            )
            {
                continue;
            }

            ++g_tim_probe.candidates;

            uint64_t absolute =
                (uint64_t)g_tim_probe.scan_lba
                * 2048u
                +
                p;

            if (
                fm_tim_decode_at(
                    absolute,
                    pixels
                )
            )
            {
                g_tim_probe.found = 1;
                g_tim_probe.show = 1;
                g_tim_probe.active = 0;
                ++g_tim_probe.images_found;

                g_tim_probe.found_abs_byte =
                    absolute;

                g_tim_probe.found_lba =
                    g_tim_probe.scan_lba;

                g_tim_probe.found_in_sector =
                    p;

                return;
            }
        }

        ++g_tim_probe.scanned_sectors;
        ++g_tim_probe.scan_lba;
        g_tim_probe.scan_byte_offset = 0u;
    }
}



/*
 * ============================================================
 * B23 - PAL-FR WA_MRG campaign background viewer
 * ============================================================
 *
 * Le jeu stocke ses backgrounds de campagne dans DATA/WA_MRG.MRG.
 * On demande d'abord AU CODE DU JEU (FUN_8002DF2C) de calculer
 * l'LBA relatif, la taille et le type pour l'index choisi. Cela evite
 * de figer les constantes de la version US sur notre executable PAL.
 *
 * En cas d'echec du petit appel guest isole, on conserve les constantes
 * connues comme fallback de diagnostic.
 */

typedef struct FMBgViewer
{
    int ready;
    int loaded;
    int error;
    int guest_calc_ok;

    uint32_t wa_lba;
    uint32_t wa_size;

    uint32_t group;
    uint32_t ordinal;
    uint32_t game_index;

    uint32_t rel_lba;
    uint32_t lba_sectors;
    uint32_t type;

    uint32_t width;
    uint32_t height;
    uint32_t nonzero;

    uint32_t calc_pc0;
    uint32_t calc_pc1;
    uint32_t calc_v0;
} FMBgViewer;

static FMBgViewer g_bg;

/*
 * B24 - pont runtime -> background PAL.
 *
 * 0x8002E11C est la vraie routine PAL qui transforme l'index de
 * background puis programme une lecture asynchrone dans WA_MRG.MRG.
 * Tant que la couche CD asynchrone PS1 n'est pas complete, on satisfait
 * cette requete synchronement depuis disc.bin et on laisse le jeu
 * poursuivre son etat. L'image affichee est donc choisie PAR LE JEU.
 */
static uint32_t g_bg_hle_calls = 0u;
static uint32_t g_bg_hle_ok = 0u;
static uint32_t g_bg_hle_fail = 0u;
static uint32_t g_bg_hle_raw = 0u;
static uint32_t g_bg_hle_resolved = 0u;
static uint32_t g_bg_hle_object = 0u;

/*
 * B25 - HLE du vrai LoadImage GPU utilise par les loaders du jeu.
 *
 * FUN_80082380 finit normalement par programmer le DMA2 GPU puis
 * attendre sa fin. Notre DMA de bring-up n'achemine pas encore toujours
 * ces transferts jusqu'au software renderer. On reproduit donc ici le
 * transfert GPU CPU->VRAM avec la commande GP0 A0h, en lisant le RECT
 * et les pixels directement dans la RAM guest.
 */
static uint32_t g_loadimg_hle_calls = 0u;
static uint32_t g_loadimg_hle_ok = 0u;
static uint32_t g_loadimg_hle_fail = 0u;
static uint32_t g_loadimg_hle_rect = 0u;
static uint32_t g_loadimg_hle_src = 0u;
static uint32_t g_loadimg_hle_pixels = 0u;
static uint32_t g_loadimg_hle_first = 0u;


/*
 * ============================================================
 * B40 - provenance des uploads de palette/CLUT
 * ============================================================
 *
 * B39 montre que le sprite est bien texturé et que ses indices 4 bpp
 * varient, mais que les 16 entrées de CLUT lues en VRAM valent toutes
 * 0x1111. On mémorise donc les petits LoadImage (palettes probables)
 * avec une copie des pixels AU MOMENT DE L'UPLOAD.
 */
#define B40_UPLOAD_RING 64u
#define B40_UPLOAD_SNAPSHOT 1024u

typedef struct FMB40UploadTrace
{
    uint32_t serial;
    uint32_t src;
    uint16_t x;
    uint16_t y;
    uint16_t w;
    uint16_t h;
    uint16_t snap_count;
    uint16_t pixels[B40_UPLOAD_SNAPSHOT];
} FMB40UploadTrace;

static FMB40UploadTrace g_b40_uploads[B40_UPLOAD_RING];
static uint32_t g_b40_upload_head = 0u;
static uint32_t g_b40_upload_count = 0u;


/*
 * ============================================================
 * B43 - provenance de toutes les zones texture LoadImage
 * ============================================================
 */
#define B43_LOAD_RING 64u

typedef struct FMB43LoadTrace
{
    uint32_t serial;
    uint32_t src;
    uint16_t x;
    uint16_t y;
    uint16_t w;
    uint16_t h;
    uint32_t first;
} FMB43LoadTrace;

static FMB43LoadTrace g_b43_loads[B43_LOAD_RING];
static uint32_t g_b43_load_head = 0u;
static uint32_t g_b43_load_count = 0u;


/*
 * B41 - provenance CD des buffers envoyes a LoadImage.
 * 64 transferts suffisent ici : le boot observe en fait ~39 secteurs.
 */
#define B41_CD_RING 64u

typedef struct FMB41CdTrace
{
    uint32_t serial;
    uint32_t lba;
    uint32_t dst;
    uint32_t bytes;
} FMB41CdTrace;

static FMB41CdTrace g_b41_cd[B41_CD_RING];
static uint32_t g_b41_cd_head = 0u;
static uint32_t g_b41_cd_count = 0u;

static int fm_hle_gpu_load_image(CPUState *cpu)
{
    if (!cpu)
    {
        return 0;
    }

    uint32_t rect = cpu->gpr[4];
    uint32_t srcp = cpu->gpr[5];

    ++g_loadimg_hle_calls;
    g_loadimg_hle_rect = rect;
    g_loadimg_hle_src = srcp;
    g_loadimg_hle_pixels = 0u;
    g_loadimg_hle_first = 0u;

    if (rect == 0u || srcp == 0u)
    {
        ++g_loadimg_hle_fail;
        return 0;
    }

    uint32_t x = cpu->read_half(rect + 0u) & 0x3FFu;
    uint32_t y = cpu->read_half(rect + 2u) & 0x1FFu;
    uint32_t w = cpu->read_half(rect + 4u);
    uint32_t h = cpu->read_half(rect + 6u);

    if (
        w == 0u
        || h == 0u
        || w > 1024u
        || h > 512u
        || ((uint64_t)w * h) > (1024u * 512u)
    )
    {
        ++g_loadimg_hle_fail;
        return 0;
    }

    uint32_t pixels = w * h;
    g_loadimg_hle_pixels = pixels;
    g_loadimg_hle_first = cpu->read_word(srcp);

    {
        FMB43LoadTrace *lt =
            &g_b43_loads[g_b43_load_head % B43_LOAD_RING];

        lt->serial = g_loadimg_hle_calls;
        lt->src = srcp;
        lt->x = (uint16_t)x;
        lt->y = (uint16_t)y;
        lt->w = (uint16_t)w;
        lt->h = (uint16_t)h;
        lt->first = g_loadimg_hle_first;

        g_b43_load_head =
            (g_b43_load_head + 1u)
            % B43_LOAD_RING;

        if (g_b43_load_count < B43_LOAD_RING)
        {
            ++g_b43_load_count;
        }
    }

    /*
     * B40 : les CLUT PS1 arrivent typiquement sous forme de lignes
     * 16x1 (4 bpp) ou 256x1 (8 bpp). On garde aussi quelques petits
     * blocs afin de ne pas rater une palette empaquetée différemment.
     */
    if (h <= 4u && w <= 256u)
    {
        FMB40UploadTrace *t =
            &g_b40_uploads[g_b40_upload_head % B40_UPLOAD_RING];

        memset(t, 0, sizeof(*t));

        t->serial = g_loadimg_hle_calls;
        t->src = srcp;
        t->x = (uint16_t)x;
        t->y = (uint16_t)y;
        t->w = (uint16_t)w;
        t->h = (uint16_t)h;

        uint32_t n = pixels;
        if (n > B40_UPLOAD_SNAPSHOT)
        {
            n = B40_UPLOAD_SNAPSHOT;
        }

        t->snap_count = (uint16_t)n;

        for (uint32_t i = 0u; i < n; ++i)
        {
            t->pixels[i] = cpu->read_half(srcp + i * 2u);
        }

        g_b40_upload_head =
            (g_b40_upload_head + 1u)
            % B40_UPLOAD_RING;

        if (g_b40_upload_count < B40_UPLOAD_RING)
        {
            ++g_b40_upload_count;
        }
    }

    /* GP0 A0h : CPU -> VRAM. */
    fm_gpu_gp0_write(0xA0000000u);
    fm_gpu_gp0_write((y << 16) | x);
    fm_gpu_gp0_write((h << 16) | w);

    for (uint32_t i = 0u; i < pixels; i += 2u)
    {
        uint32_t lo = cpu->read_half(srcp + i * 2u);
        uint32_t hi = 0u;

        if (i + 1u < pixels)
        {
            hi = cpu->read_half(srcp + (i + 1u) * 2u);
        }

        fm_gpu_gp0_write(lo | (hi << 16));
    }

    ++g_loadimg_hle_ok;
    return 1;
}



/*
 * ============================================================
 * B26 - WA_MRG -> VRAM bridge
 * ============================================================
 *
 * B25 a confirme que le runtime actuel n'appelle pas encore LoadImage2.
 * Pour connecter quand meme une vraie ressource du disque au pipeline
 * GPU PS1, on injecte le background PAL decode par B23/B24 dans les
 * deux pages framebuffer (x=0 et x=320) via la vraie commande
 * GP0 A0h CPU->VRAM.
 *
 * Ce n'est plus un simple "preview" 3DS : les pixels passent par le
 * parser GP0 et vivent dans la VRAM emulee, donc les primitives du jeu
 * peuvent ensuite dessiner par-dessus.
 */
static uint32_t g_bg_vram_pending = 0u;
static uint32_t g_bg_vram_calls = 0u;
static uint32_t g_bg_vram_ok = 0u;
static uint32_t g_bg_vram_pixels = 0u;
static uint32_t g_bg_vram_words = 0u;
static uint32_t g_bg_vram_after_upload_nz = 0u;

/*
 * B42 : 1 = framebuffer reel du jeu, 0 = ancien mode diagnostic
 * avec background WA_MRG force et clears noirs bloques.
 */
static int g_b42_native_video = 1;

static void fm_bg_upload_rect_gp0(
    const uint16_t *pixels,
    uint32_t page_x
)
{
    uint32_t src_x = 0u;
    uint32_t src_y = 48u;
    uint32_t w = 320u;
    uint32_t h = 160u;

    if (!pixels)
    {
        return;
    }

    if (g_bg.type == 2u)
    {
        src_x = 32u;
        src_y = 0u;
        w = 256u;
        h = 256u;
    }

    uint32_t dst_x = page_x + src_x;
    uint32_t dst_y = src_y;

    fm_gpu_gp0_write(0xA0000000u);
    fm_gpu_gp0_write((dst_y << 16) | dst_x);
    fm_gpu_gp0_write((h << 16) | w);

    uint32_t packed = 0u;
    uint32_t half = 0u;

    for (uint32_t y = 0u; y < h; ++y)
    {
        const uint16_t *row =
            pixels + (src_y + y) * 320u + src_x;

        for (uint32_t x = 0u; x < w; ++x)
        {
            uint32_t c = row[x];

            if (half == 0u)
            {
                packed = c;
                half = 1u;
            }
            else
            {
                packed |= c << 16;
                fm_gpu_gp0_write(packed);
                packed = 0u;
                half = 0u;
                ++g_bg_vram_words;
            }

            ++g_bg_vram_pixels;
        }
    }

    if (half != 0u)
    {
        fm_gpu_gp0_write(packed);
        ++g_bg_vram_words;
    }
}


static void fm_bg_upload_preview_to_vram(
    const uint16_t *pixels
)
{
    if (!pixels || !g_bg.loaded)
    {
        return;
    }

    ++g_bg_vram_calls;
    g_bg_vram_pixels = 0u;
    g_bg_vram_words = 0u;

    fm_bg_upload_rect_gp0(pixels, 0u);
    fm_bg_upload_rect_gp0(pixels, 320u);

    /* Snapshot immediat : prouve si l'upload a reellement rempli la VRAM. */
    FMGpuDebugStats snap;
    memset(&snap, 0, sizeof(snap));
    fm_gpu_debug_stats(&snap);
    g_bg_vram_after_upload_nz = snap.nonzero_vram;

    ++g_bg_vram_ok;
}


static uint32_t fm_bg_bcd_index(uint32_t group, uint32_t ordinal)
{
    ordinal %= 100u;

    return
        ((group & 0xFFu) << 8)
        |
        (((ordinal / 10u) & 0x0Fu) << 4)
        |
        (ordinal % 10u);
}


static int fm_bg_calc_lba_guest(
    CPUState *cpu,
    uint32_t game_index,
    uint32_t *out_lba,
    uint32_t *out_size,
    uint32_t *out_type
)
{
    const uint32_t sentinel = 0x8000FFD0u;
    const uint32_t scratch = 0x801FC800u;

    if (!cpu || !out_lba || !out_size || !out_type)
    {
        return 0;
    }

    cpu->write_word(scratch + 0u, 0u);
    cpu->write_word(scratch + 4u, 0u);

    CPUState t = *cpu;

    t.pc = 0x8002DF2Cu;
    t.gpr[4] = game_index;
    t.gpr[5] = scratch + 0u;
    t.gpr[6] = scratch + 4u;
    t.gpr[29] = 0x801FC700u;
    t.gpr[31] = sentinel;
    t.gpr[0] = 0u;

    g_bg.calc_pc0 = t.pc;
    g_bg.calc_pc1 = 0u;
    g_bg.calc_v0 = 0u;

    for (uint32_t handoff = 0u; handoff < 16u; ++handoff)
    {
        g_bg.calc_pc1 = t.pc;

        if (t.pc == sentinel)
        {
            uint32_t lba = t.gpr[2];
            uint32_t sz = cpu->read_word(scratch + 0u);
            uint32_t ty = cpu->read_word(scratch + 4u);

            g_bg.calc_v0 = lba;

            if (
                ty <= 2u
                &&
                (
                    sz == 0x21u
                    || sz == 0x51u
                    || sz == 0x71u
                )
                && lba < 0x20000u
            )
            {
                *out_lba = lba;
                *out_size = sz;
                *out_type = ty;
                return 1;
            }

            return 0;
        }

        FMRuntimeProbeResult p =
            fm_runtime_probe(
                &t,
                t.pc,
                8192u
            );

        if (p.reason == FM_STOP_BUDGET)
        {
            continue;
        }

        if (p.reason == FM_STOP_RETURNED)
        {
            if (p.dispatch_result == 1)
            {
                continue;
            }

            FMInterpResult ir =
                fm_interp_run_block(
                    &t,
                    512u
                );

            if (
                ir.reason == FM_INTERP_BLOCK_DONE
                || ir.reason == FM_INTERP_BUDGET
            )
            {
                continue;
            }
        }

        return 0;
    }

    return 0;
}


static void fm_bg_calc_lba_fallback(
    uint32_t game_index,
    uint32_t *out_lba,
    uint32_t *out_size,
    uint32_t *out_type
)
{
    uint32_t group = game_index >> 8;
    uint32_t low = game_index & 0xFFu;
    uint32_t ordinal =
        10u * ((low >> 4) & 0x0Fu)
        + (low & 0x0Fu);

    uint32_t start = 0u;
    uint32_t size = 0x21u;

    if (group == 1u)
    {
        start = 0x672u;
        size = 0x51u;
    }
    else if (group == 2u)
    {
        start = 0x13BCu;
        size = 0x71u;
    }

    *out_lba = 0x29E8u + start + ordinal * size;
    *out_size = size;
    *out_type = group <= 2u ? group : 0u;
}


static int fm_bg_read_block(
    uint32_t absolute_lba,
    uint8_t *dst,
    uint32_t sectors
)
{
    for (uint32_t s = 0u; s < sectors; ++s)
    {
        if (
            fm_disc_read_sector(
                absolute_lba + s,
                dst + s * 2048u
            )
            != 0
        )
        {
            return 0;
        }
    }

    return 1;
}


static void fm_bg_clear_preview(uint16_t *pixels)
{
    if (pixels)
    {
        memset(
            pixels,
            0,
            320u * 256u * sizeof(uint16_t)
        );
    }
}


static int fm_bg_decode_main0(
    const uint8_t *block,
    uint32_t block_bytes,
    uint32_t type,
    uint16_t *pixels
)
{
    if (!block || !pixels || type > 2u)
    {
        return 0;
    }

    const uint32_t img_size = 128u * 512u;
    const uint32_t simg_half = (256u * 256u) / 2u;

    uint32_t img_count = 1u;
    uint32_t simg_count = 0u;

    if (type == 1u)
    {
        img_count = 2u;
        simg_count = 1u;
    }
    else if (type == 2u)
    {
        img_count = 3u;
        simg_count = 1u;
    }

    uint32_t palette_off =
        img_size * img_count
        + simg_half * simg_count;

    if (palette_off + 512u > block_bytes)
    {
        return 0;
    }

    const uint8_t *indices = block;
    const uint16_t *palette =
        (const uint16_t *)(block + palette_off);

    fm_bg_clear_preview(pixels);

    uint32_t nz = 0u;

    if (type == 2u)
    {
        /*
         * Type 2, image principale 0 : 128x512 -> 256x256.
         * Les deux moities 128x256 deviennent gauche / droite.
         */
        const uint32_t dst_x0 = 32u;

        for (uint32_t y = 0u; y < 256u; ++y)
        {
            for (uint32_t x = 0u; x < 256u; ++x)
            {
                uint32_t src_index;

                if (x < 128u)
                {
                    src_index = y * 128u + x;
                }
                else
                {
                    src_index =
                        32768u
                        + y * 128u
                        + (x - 128u);
                }

                uint16_t c = palette[indices[src_index]];
                pixels[y * 320u + dst_x0 + x] = c;

                if ((c & 0x7FFFu) != 0u)
                {
                    ++nz;
                }
            }
        }

        g_bg.width = 256u;
        g_bg.height = 256u;
    }
    else
    {
        /*
         * Type 0/1, image principale 0 : untile 128x512 -> 320x160.
         * Mapping equivalent au viewer public BGEx, mais directement
         * en RGB555 pour notre framebuffer 3DS.
         */
        const uint32_t dst_y0 = 48u;
        const uint32_t part2_start = img_size / 2u;          /* 32768 */
        const uint32_t part2_size = 128u * 160u;             /* 20480 */
        const uint32_t part34_start = part2_start + part2_size; /* 53248 */

        for (uint32_t y = 0u; y < 160u; ++y)
        {
            for (uint32_t x = 0u; x < 320u; ++x)
            {
                uint32_t src_index;

                if (x < 128u)
                {
                    src_index = y * 128u + x;
                }
                else if (x < 256u)
                {
                    src_index =
                        part2_start
                        + y * 128u
                        + (x - 128u);
                }
                else if (y < 80u)
                {
                    src_index =
                        part34_start
                        + y * 128u
                        + (x - 256u);
                }
                else
                {
                    src_index =
                        part34_start
                        + (y - 80u) * 128u
                        + 64u
                        + (x - 256u);
                }

                if (src_index >= img_size)
                {
                    return 0;
                }

                uint16_t c = palette[indices[src_index]];
                pixels[(dst_y0 + y) * 320u + x] = c;

                if ((c & 0x7FFFu) != 0u)
                {
                    ++nz;
                }
            }
        }

        g_bg.width = 320u;
        g_bg.height = 160u;
    }

    g_bg.nonzero = nz;
    return nz != 0u;
}


static int fm_bg_load(
    CPUState *cpu,
    uint16_t *pixels
)
{
    if (!cpu || !pixels || !g_bg.ready)
    {
        return 0;
    }

    g_bg.loaded = 0;
    g_bg.error = 0;
    g_bg.game_index =
        fm_bg_bcd_index(
            g_bg.group,
            g_bg.ordinal
        );

    uint32_t rel = 0u;
    uint32_t sectors = 0u;
    uint32_t type = 0u;

    /*
     * PAL-FR (SLES_039.48): the background loader uses 0x29E8
     * as the WA_MRG-relative base. The old 0x8002DF2C probe was
     * from the US layout and is not the PAL calculator entry point.
     * Use the constants recovered from this executable directly.
     */
    g_bg.guest_calc_ok = 0;

    fm_bg_calc_lba_fallback(
        g_bg.game_index,
        &rel,
        &sectors,
        &type
    );

    g_bg.rel_lba = rel;
    g_bg.lba_sectors = sectors;
    g_bg.type = type;

    if (
        sectors == 0u
        || sectors > 0x80u
        || type > 2u
        || ((uint64_t)rel + sectors) * 2048u > g_bg.wa_size
    )
    {
        g_bg.error = 3;
        fm_bg_clear_preview(pixels);
        return 0;
    }

    uint32_t bytes = sectors * 2048u;
    uint8_t *block = (uint8_t *)malloc(bytes);

    if (!block)
    {
        g_bg.error = 4;
        return 0;
    }

    int ok =
        fm_bg_read_block(
            g_bg.wa_lba + rel,
            block,
            sectors
        );

    if (!ok)
    {
        free(block);
        g_bg.error = 5;
        return 0;
    }

    ok =
        fm_bg_decode_main0(
            block,
            bytes,
            type,
            pixels
        );

    free(block);

    if (!ok)
    {
        g_bg.error = 6;
        return 0;
    }

    g_bg.loaded = 1;
    g_bg_vram_pending = 1u;
    return 1;
}


static void fm_bg_begin(
    CPUState *cpu,
    uint16_t *pixels
)
{
    memset(&g_bg, 0, sizeof(g_bg));

    uint32_t lba = 0u;
    uint32_t size = 0u;

    static const char *paths[] =
    {
        "\\DATA\\WA_MRG.MRG;1",
        "\\DATA\\WA_MRG.MRG",
        "\\WA_MRG.MRG;1"
    };

    for (unsigned i = 0u; i < sizeof(paths) / sizeof(paths[0]); ++i)
    {
        if (fm_disc_find_file(paths[i], &lba, &size))
        {
            g_bg.wa_lba = lba;
            g_bg.wa_size = size;
            g_bg.ready = 1;
            break;
        }
    }

    if (!g_bg.ready)
    {
        g_bg.error = 1;
        return;
    }

    g_bg.group = 0u;
    g_bg.ordinal = 1u;

    fm_bg_load(cpu, pixels);
}


static void fm_bg_change(
    CPUState *cpu,
    uint16_t *pixels,
    int delta_ordinal,
    int delta_group
)
{
    int group = (int)g_bg.group + delta_group;

    while (group < 0)
        group += 3;
    while (group > 2)
        group -= 3;

    int ordinal = (int)g_bg.ordinal + delta_ordinal;

    while (ordinal < 0)
        ordinal += 100;
    while (ordinal >= 100)
        ordinal -= 100;

    g_bg.group = (uint32_t)group;
    g_bg.ordinal = (uint32_t)ordinal;

    fm_bg_load(cpu, pixels);
}

/*
 * Resout les deux indices speciaux 0x10/0x11 exactement comme la
 * routine PAL 0x8002E11C. Le choix depend de DAT_8009C44B.
 */
static uint32_t fm_bg_resolve_runtime_index(
    CPUState *cpu,
    uint32_t raw_index
)
{
    uint32_t idx = raw_index & 0xFFFFu;

    if (!cpu)
    {
        return idx;
    }

    if (idx == 0x10u || idx == 0x11u)
    {
        uint8_t variant = cpu->read_byte(0x8009C44Bu);

        if (variant >= 1u && variant <= 4u)
        {
            uint32_t base =
                idx == 0x10u
                    ? 0x42u
                    : 0x43u;

            idx = base + (uint32_t)(variant - 1u) * 2u;
        }
    }

    return idx;
}


static int fm_bg_load_game_index(
    CPUState *cpu,
    uint16_t *pixels,
    uint32_t game_index
)
{
    uint32_t group = (game_index >> 8) & 0xFFu;
    uint32_t low = game_index & 0xFFu;
    uint32_t tens = (low >> 4) & 0x0Fu;
    uint32_t ones = low & 0x0Fu;

    if (group > 2u || tens > 9u || ones > 9u)
    {
        return 0;
    }

    uint32_t ordinal = tens * 10u + ones;

    /* Eviter de relire 0x21..0x71 secteurs si le jeu redemande
       exactement le background deja affiche. */
    if (
        g_bg.loaded
        && g_bg.group == group
        && g_bg.ordinal == ordinal
    )
    {
        return 1;
    }

    g_bg.group = group;
    g_bg.ordinal = ordinal;

    return fm_bg_load(cpu, pixels);
}


/*
 * ============================================================
 * Preview
 * ============================================================
 */

static int load_preview(uint16_t *pixels)
{
    FILE *f =
        fopen(
            "sdmc:/3ds/fm-new3ds/preview.rgb555",
            "rb"
        );

    if (!f)
    {
        return 0;
    }

    int ok =
        fread(
            pixels,
            sizeof(uint16_t),
            320 * 256,
            f
        )
        ==
        320 * 256;

    fclose(f);

    return ok;
}


/*
 * ============================================================
 * Main
 * ============================================================
 */


/*
 * ============================================================
 * B33 - immediate LibCD callback bridge
 * ============================================================
 */
static void fm_b33_fill_cd_result(CPUState *cpu, uint32_t command)
{
    if (!cpu)
    {
        return;
    }

    for (unsigned i = 0; i < 16u; ++i)
    {
        cpu->write_byte(g_b33_result_scratch + i, 0u);
    }

    /* Status "OK/ready" utilise par nos autres HLE LibCD. */
    cpu->write_byte(g_b33_result_scratch + 0u, 0x02u);

    /*
     * CdlGetlocL (0x10) : FUN_800142AC convertit les 3 premiers
     * octets BCD en LBA. Fournir la position host courante permet
     * au vrai callback de conserver un etat coherent.
     */
    if (command == 0x10u)
    {
        uint32_t abs_sector = g_cd_lba + 150u;
        uint32_t minute = abs_sector / (60u * 75u);
        uint32_t rem = abs_sector % (60u * 75u);
        uint32_t second = rem / 75u;
        uint32_t frame_cd = rem % 75u;

        cpu->write_byte(
            g_b33_result_scratch + 0u,
            (uint8_t)(((minute / 10u) << 4) | (minute % 10u))
        );
        cpu->write_byte(
            g_b33_result_scratch + 1u,
            (uint8_t)(((second / 10u) << 4) | (second % 10u))
        );
        cpu->write_byte(
            g_b33_result_scratch + 2u,
            (uint8_t)(((frame_cd / 10u) << 4) | (frame_cd % 10u))
        );
    }
}


static int fm_b33_schedule_cd_callback(
    CPUState *cpu,
    uint32_t command,
    uint32_t callback,
    uint32_t resume_pc,
    uint32_t params,
    uint32_t context
)
{
    if (!cpu)
    {
        return 0;
    }

    g_b33_cb_cmd = command & 0xFFu;
    g_b33_cb_addr = callback;
    g_b33_cb_resume = resume_pc;
    g_b33_last_params = params;
    g_b33_last_ctx = context;

    fm_b33_fill_cd_result(cpu, command);

    /*
     * B66 - reproduire la partie INTERNE de LibCD que notre HLE B33
     * court-circuitait.
     *
     * FUN_80079728 fait ceci lors d'un interrupt type 2 :
     *   DAT_80094BEC = 2;
     *   copie des 8 octets de resultat vers DAT_800F7130.
     *
     * Le callback utilisateur est appele seulement APRES cet update.
     */
    g_b66_last_cmd = command & 0xFFu;
    g_b66_last_sync_before =
        cpu->read_byte(0x80094BECu);

    cpu->write_byte(
        0x80094BECu,
        2u
    );

    cpu->write_byte(
        0x8009492Du,
        (uint8_t)(command & 0xFFu)
    );

    for (unsigned i = 0; i < 8u; ++i)
    {
        cpu->write_byte(
            0x800F7130u + i,
            cpu->read_byte(
                g_b33_result_scratch + i
            )
        );
    }

    g_b66_last_sync_after =
        cpu->read_byte(0x80094BECu);

    ++g_b66_complete_publish;

    /* Pas de callback : la commande est simplement acceptee. */
    if (
        callback < 0x80010000u
        || callback >= 0x801E0000u
    )
    {
        ++g_b33_cb_skipped;
        cpu->gpr[2] = 1u;
        cpu->pc = resume_pc;
        cpu->gpr[31] = resume_pc;
        cpu->gpr[0] = 0u;
        return 1;
    }

    /* Une seule profondeur suffit pour le chemin succes (event 2). */
    if (g_b33_cb_active)
    {
        ++g_b33_cb_skipped;
        cpu->gpr[2] = 1u;
        cpu->pc = resume_pc;
        cpu->gpr[31] = resume_pc;
        cpu->gpr[0] = 0u;
        return 1;
    }

    for (unsigned i = 0; i < 32u; ++i)
    {
        g_b33_saved_gpr[i] = cpu->gpr[i];
    }
    ++g_b33_ctx_saved;

    g_b33_cb_active = 1u;
    ++g_b33_cb_started;

    /*
     * Les callbacks du moteur testent a0 == 2 pour CdlComplete
     * et a0 == 5 pour l'erreur/retry. a1 pointe sur le resultat.
     */
    cpu->gpr[4] = 2u;
    cpu->gpr[5] = g_b33_result_scratch;
    cpu->pc = callback;
    cpu->gpr[31] = g_b33_cb_sentinel;
    cpu->gpr[0] = 0u;

    return 1;
}


/*
 * ============================================================
 * B62 - mini moteur de projection GTE pour wrappers Psy-Q
 * ============================================================
 *
 * Ce n'est pas encore un GTE cycle-exact. Le but est d'émuler les
 * résultats architecturaux utilisés par les wrappers libgte ci-dessus
 * afin de poursuivre le bring-up.
 */

typedef struct FMB62Projected
{
    uint32_t sxy;
    uint16_t sz;
    uint32_t p;
    uint32_t flag;
} FMB62Projected;


static int32_t fm_b62_s16_lo(uint32_t v)
{
    return (int32_t)(int16_t)(v & 0xFFFFu);
}


static int32_t fm_b62_s16_hi(uint32_t v)
{
    return (int32_t)(int16_t)((v >> 16) & 0xFFFFu);
}


static int32_t fm_b62_clamp_sxy(int64_t v)
{
    if (v < -1024)
    {
        return -1024;
    }

    if (v > 1023)
    {
        return 1023;
    }

    return (int32_t)v;
}


static uint16_t fm_b62_clamp_sz(int64_t v)
{
    if (v < 0)
    {
        return 0;
    }

    if (v > 0xFFFF)
    {
        return 0xFFFFu;
    }

    return (uint16_t)v;
}


static uint32_t fm_b62_clamp_ir0(int64_t v)
{
    if (v < 0)
    {
        return 0u;
    }

    if (v > 0x1000)
    {
        return 0x1000u;
    }

    return (uint32_t)v;
}


static FMB62Projected fm_b62_project_vertex(
    CPUState *cpu,
    uint32_t vptr
)
{
    FMB62Projected out;
    out.sxy = 0u;
    out.sz = 0u;
    out.p = 0u;
    out.flag = 0u;

    int32_t vx =
        (int32_t)(int16_t)cpu->read_half(vptr + 0u);

    int32_t vy =
        (int32_t)(int16_t)cpu->read_half(vptr + 2u);

    int32_t vz =
        (int32_t)(int16_t)cpu->read_half(vptr + 4u);

    /*
     * Matrice de rotation GTE, format 1.3.12.
     */
    int32_t r11 = fm_b62_s16_lo(cpu->gte_ctrl[0]);
    int32_t r12 = fm_b62_s16_hi(cpu->gte_ctrl[0]);
    int32_t r13 = fm_b62_s16_lo(cpu->gte_ctrl[1]);

    int32_t r21 = fm_b62_s16_hi(cpu->gte_ctrl[1]);
    int32_t r22 = fm_b62_s16_lo(cpu->gte_ctrl[2]);
    int32_t r23 = fm_b62_s16_hi(cpu->gte_ctrl[2]);

    int32_t r31 = fm_b62_s16_lo(cpu->gte_ctrl[3]);
    int32_t r32 = fm_b62_s16_hi(cpu->gte_ctrl[3]);
    int32_t r33 = fm_b62_s16_lo(cpu->gte_ctrl[4]);

    int64_t mac1 =
        ((int64_t)(int32_t)cpu->gte_ctrl[5] << 12)
        + (int64_t)r11 * vx
        + (int64_t)r12 * vy
        + (int64_t)r13 * vz;

    int64_t mac2 =
        ((int64_t)(int32_t)cpu->gte_ctrl[6] << 12)
        + (int64_t)r21 * vx
        + (int64_t)r22 * vy
        + (int64_t)r23 * vz;

    int64_t mac3 =
        ((int64_t)(int32_t)cpu->gte_ctrl[7] << 12)
        + (int64_t)r31 * vx
        + (int64_t)r32 * vy
        + (int64_t)r33 * vz;

    int32_t ir1 =
        (int32_t)(mac1 >> 12);

    int32_t ir2 =
        (int32_t)(mac2 >> 12);

    int64_t z =
        mac3 >> 12;

    out.sz =
        fm_b62_clamp_sz(z);

    /*
     * Division perspective GTE :
     * quotient ~= H / SZ3 en 16.16, saturé à 0x1FFFF.
     */
    uint32_t h =
        cpu->gte_ctrl[26] & 0xFFFFu;

    uint32_t q;

    if (out.sz == 0u)
    {
        q = 0x1FFFFu;
        out.flag |= 0x00020000u;
    }
    else
    {
        uint64_t div =
            ((uint64_t)h << 16) / out.sz;

        if (div > 0x1FFFFu)
        {
            q = 0x1FFFFu;
            out.flag |= 0x00020000u;
        }
        else
        {
            q = (uint32_t)div;
        }
    }

    int64_t sx_fp =
        (int64_t)(int32_t)cpu->gte_ctrl[24]
        + (int64_t)ir1 * q;

    int64_t sy_fp =
        (int64_t)(int32_t)cpu->gte_ctrl[25]
        + (int64_t)ir2 * q;

    int32_t sx =
        fm_b62_clamp_sxy(
            sx_fp >> 16
        );

    int32_t sy =
        fm_b62_clamp_sxy(
            sy_fp >> 16
        );

    out.sxy =
        ((uint32_t)(uint16_t)sy << 16)
        |
        (uint32_t)(uint16_t)sx;

    /*
     * Depth cue P / IR0.
     */
    int32_t dqa =
        (int32_t)(int16_t)(
            cpu->gte_ctrl[27] & 0xFFFFu
        );

    int64_t ir0 =
        (
            (int64_t)(int32_t)cpu->gte_ctrl[28]
            +
            (int64_t)dqa * q
        )
        >> 12;

    out.p =
        fm_b62_clamp_ir0(ir0);

    return out;
}


static void fm_b62_commit_fifo4(
    CPUState *cpu,
    const FMB62Projected *p0,
    const FMB62Projected *p1,
    const FMB62Projected *p2,
    const FMB62Projected *p3,
    uint32_t flag
)
{
    /*
     * Etat final après RTPT(v0,v1,v2) + RTPS(v3).
     */
    cpu->gte_data[12] = p1->sxy;
    cpu->gte_data[13] = p2->sxy;
    cpu->gte_data[14] = p3->sxy;
    cpu->gte_data[15] = p3->sxy;

    cpu->gte_data[16] = p0->sz;
    cpu->gte_data[17] = p1->sz;
    cpu->gte_data[18] = p2->sz;
    cpu->gte_data[19] = p3->sz;

    cpu->gte_data[8] = p3->p;

    cpu->gte_ctrl[31] = flag;
}


static uint32_t fm_b62_average_z(
    CPUState *cpu,
    uint32_t sum,
    int count
)
{
    int32_t zsf;

    if (count == 3)
    {
        zsf =
            (int32_t)(int16_t)(
                cpu->gte_ctrl[29]
                &
                0xFFFFu
            );
    }
    else
    {
        zsf =
            (int32_t)(int16_t)(
                cpu->gte_ctrl[30]
                &
                0xFFFFu
            );
    }

    int64_t otz =
        ((int64_t)sum * zsf) >> 12;

    if (otz < 0)
    {
        otz = 0;
    }
    else if (otz > 0xFFFF)
    {
        otz = 0xFFFF;
    }

    return (uint32_t)otz;
}


static int fm_b62_hle_normal_clip(
    CPUState *cpu
)
{
    uint32_t a = cpu->gpr[4];
    uint32_t b = cpu->gpr[5];
    uint32_t c = cpu->gpr[6];

    int32_t ax = (int16_t)(a & 0xFFFFu);
    int32_t ay = (int16_t)(a >> 16);
    int32_t bx = (int16_t)(b & 0xFFFFu);
    int32_t by = (int16_t)(b >> 16);
    int32_t cx = (int16_t)(c & 0xFFFFu);
    int32_t cy = (int16_t)(c >> 16);

    int64_t area =
        (int64_t)ax * by
        + (int64_t)bx * cy
        + (int64_t)cx * ay
        - (int64_t)ax * cy
        - (int64_t)bx * ay
        - (int64_t)cx * by;

    cpu->gte_data[24] = (uint32_t)area;
    cpu->gpr[2] = (uint32_t)area;
    cpu->pc = cpu->gpr[31];
    cpu->gpr[0] = 0u;

    ++g_b62_hle_nclip;
    g_b62_last_helper = 0x80087928u;

    return 1;
}


static int fm_b62_hle_rot_trans_pers4(
    CPUState *cpu
)
{
    uint32_t sp = cpu->gpr[29];

    uint32_t v0 = cpu->gpr[4];
    uint32_t v1 = cpu->gpr[5];
    uint32_t v2 = cpu->gpr[6];
    uint32_t v3 = cpu->gpr[7];

    uint32_t sxy0 = cpu->read_word(sp + 16u);
    uint32_t sxy1 = cpu->read_word(sp + 20u);
    uint32_t sxy2 = cpu->read_word(sp + 24u);
    uint32_t sxy3 = cpu->read_word(sp + 28u);
    uint32_t p_out = cpu->read_word(sp + 32u);
    uint32_t flag_out = cpu->read_word(sp + 36u);

    FMB62Projected p0 = fm_b62_project_vertex(cpu, v0);
    FMB62Projected p1 = fm_b62_project_vertex(cpu, v1);
    FMB62Projected p2 = fm_b62_project_vertex(cpu, v2);
    FMB62Projected p3 = fm_b62_project_vertex(cpu, v3);

    uint32_t flag =
        p0.flag
        |
        p1.flag
        |
        p2.flag
        |
        p3.flag;

    cpu->write_word(sxy0, p0.sxy);
    cpu->write_word(sxy1, p1.sxy);
    cpu->write_word(sxy2, p2.sxy);
    cpu->write_word(sxy3, p3.sxy);
    cpu->write_word(p_out, p3.p);
    cpu->write_word(flag_out, flag);

    fm_b62_commit_fifo4(
        cpu,
        &p0,
        &p1,
        &p2,
        &p3,
        flag
    );

    /*
     * Psy-Q RotTransPers4 retourne SZ3 / 4.
     */
    cpu->gpr[2] =
        ((uint32_t)p3.sz) >> 2;

    g_b62_last_otz = cpu->gpr[2];

    cpu->pc = cpu->gpr[31];
    cpu->gpr[0] = 0u;

    ++g_b62_hle_rtp4;
    g_b62_last_helper = 0x80087958u;

    return 1;
}


static int fm_b62_hle_rot_average3(
    CPUState *cpu
)
{
    uint32_t sp = cpu->gpr[29];

    uint32_t v0 = cpu->gpr[4];
    uint32_t v1 = cpu->gpr[5];
    uint32_t v2 = cpu->gpr[6];

    uint32_t sxy0 = cpu->gpr[7];
    uint32_t sxy1 = cpu->read_word(sp + 16u);
    uint32_t sxy2 = cpu->read_word(sp + 20u);
    uint32_t p_out = cpu->read_word(sp + 24u);
    uint32_t flag_out = cpu->read_word(sp + 28u);

    FMB62Projected p0 = fm_b62_project_vertex(cpu, v0);
    FMB62Projected p1 = fm_b62_project_vertex(cpu, v1);
    FMB62Projected p2 = fm_b62_project_vertex(cpu, v2);

    uint32_t flag =
        p0.flag | p1.flag | p2.flag;

    cpu->write_word(sxy0, p0.sxy);
    cpu->write_word(sxy1, p1.sxy);
    cpu->write_word(sxy2, p2.sxy);
    cpu->write_word(p_out, p2.p);
    cpu->write_word(flag_out, flag);

    cpu->gte_data[12] = p0.sxy;
    cpu->gte_data[13] = p1.sxy;
    cpu->gte_data[14] = p2.sxy;
    cpu->gte_data[15] = p2.sxy;

    cpu->gte_data[17] = p0.sz;
    cpu->gte_data[18] = p1.sz;
    cpu->gte_data[19] = p2.sz;
    cpu->gte_data[8] = p2.p;
    cpu->gte_ctrl[31] = flag;

    uint32_t sum =
        (uint32_t)p0.sz
        +
        (uint32_t)p1.sz
        +
        (uint32_t)p2.sz;

    cpu->gpr[2] =
        fm_b62_average_z(
            cpu,
            sum,
            3
        );

    cpu->gte_data[7] = cpu->gpr[2];

    g_b62_last_otz = cpu->gpr[2];

    cpu->pc = cpu->gpr[31];
    cpu->gpr[0] = 0u;

    ++g_b62_hle_ra3;
    g_b62_last_helper = 0x800879D8u;

    return 1;
}


static int fm_b62_hle_rot_average4(
    CPUState *cpu
)
{
    uint32_t sp = cpu->gpr[29];

    uint32_t v0 = cpu->gpr[4];
    uint32_t v1 = cpu->gpr[5];
    uint32_t v2 = cpu->gpr[6];
    uint32_t v3 = cpu->gpr[7];

    uint32_t sxy0 = cpu->read_word(sp + 16u);
    uint32_t sxy1 = cpu->read_word(sp + 20u);
    uint32_t sxy2 = cpu->read_word(sp + 24u);
    uint32_t sxy3 = cpu->read_word(sp + 28u);
    uint32_t p_out = cpu->read_word(sp + 32u);
    uint32_t flag_out = cpu->read_word(sp + 36u);

    FMB62Projected p0 = fm_b62_project_vertex(cpu, v0);
    FMB62Projected p1 = fm_b62_project_vertex(cpu, v1);
    FMB62Projected p2 = fm_b62_project_vertex(cpu, v2);
    FMB62Projected p3 = fm_b62_project_vertex(cpu, v3);

    uint32_t flag =
        p0.flag
        |
        p1.flag
        |
        p2.flag
        |
        p3.flag;

    cpu->write_word(sxy0, p0.sxy);
    cpu->write_word(sxy1, p1.sxy);
    cpu->write_word(sxy2, p2.sxy);
    cpu->write_word(sxy3, p3.sxy);
    cpu->write_word(p_out, p3.p);
    cpu->write_word(flag_out, flag);

    fm_b62_commit_fifo4(
        cpu,
        &p0,
        &p1,
        &p2,
        &p3,
        flag
    );

    uint32_t sum =
        (uint32_t)p0.sz
        +
        (uint32_t)p1.sz
        +
        (uint32_t)p2.sz
        +
        (uint32_t)p3.sz;

    cpu->gpr[2] =
        fm_b62_average_z(
            cpu,
            sum,
            4
        );

    cpu->gte_data[7] = cpu->gpr[2];

    g_b62_last_otz = cpu->gpr[2];

    cpu->pc = cpu->gpr[31];
    cpu->gpr[0] = 0u;

    ++g_b62_hle_ra4;
    g_b62_last_helper = 0x80087A38u;

    return 1;
}


static int fm_b62_try_gte_helper(
    CPUState *cpu,
    uint32_t phys
)
{
    switch (phys)
    {
        case 0x00087928u:
            return fm_b62_hle_normal_clip(cpu);

        case 0x00087958u:
            return fm_b62_hle_rot_trans_pers4(cpu);

        case 0x000879D8u:
            return fm_b62_hle_rot_average3(cpu);

        case 0x00087A38u:
            return fm_b62_hle_rot_average4(cpu);

        default:
            return 0;
    }
}


/*
 * ============================================================
 * B93 - traduction native exacte de FUN_800917F8
 * ============================================================
 *
 * Ghidra :
 *   - source compressee fixe : DAT_8009B488
 *   - a0 = buffer destination
 *   - commandes 00..EF : longueur = opcode + 1
 *       distance == 0 -> litteraux
 *       distance != 0 -> copie LZ depuis dst[-distance]
 *   - F0 : repasse en mode litteral
 *   - F1..FF + octet : distance = word - F0FF
 *   - distance F00 : fin du flux
 *   - puis dst16[i] ^= dst16[i - 4], i=4..87FF
 *
 * Retour 1 si le HLE a ete applique. En cas de garde invalide,
 * retour 0 et le code ARM recompile original reste disponible.
 */
static int fm_b93_hle_800917f8(
    CPUState *cpu,
    uint8_t *ram,
    size_t ram_size,
    uint32_t *out_bytes
)
{
    if (!cpu || !ram || ram_size < (2u * 1024u * 1024u))
    {
        return 0;
    }

    const uint32_t src_off = 0x0009B488u;
    const uint32_t dst_off = cpu->gpr[4] & 0x001FFFFFu;
    const size_t post_size = 0x11000u;

    if (
        src_off >= ram_size
        ||
        dst_off > ram_size
        ||
        post_size > ram_size - dst_off
    )
    {
        return 0;
    }

    const uint8_t *src0 = ram + src_off;
    const uint8_t *src_end = ram + ram_size;
    const uint8_t *src = src0;

    size_t produced = 0u;
    uint32_t distance = 0u;

    /*
     * Premier passage : valider le flux sans modifier la RAM.
     * Cela permet de retomber proprement sur le code original si
     * le buffer source n'est pas celui attendu.
     */
    for (;;)
    {
        if (src >= src_end)
        {
            return 0;
        }

        uint32_t code = *src++;

        if (code < 0xF0u)
        {
            size_t count = (size_t)code + 1u;

            if (produced + count > post_size)
            {
                return 0;
            }

            if (distance == 0u)
            {
                if ((size_t)(src_end - src) < count)
                {
                    return 0;
                }

                src += count;
            }
            else
            {
                if ((size_t)distance > produced)
                {
                    return 0;
                }
            }

            produced += count;
        }
        else
        {
            distance = 0u;

            if (code != 0xF0u)
            {
                if (src >= src_end)
                {
                    return 0;
                }

                uint32_t packed =
                    (code << 8)
                    |
                    (uint32_t)(*src++);

                distance =
                    packed
                    -
                    0xF0FFu;
            }
        }

        if (distance == 0x0F00u)
        {
            break;
        }
    }

    const uint8_t *src_after = src;
    uint8_t *dst0 = ram + dst_off;
    uint8_t *dst_end = dst0 + post_size;

    /*
     * Le flux compresse et la destination ne doivent pas se recouvrir.
     * Ce n'est pas le cas normal du jeu ; si cela arrivait, garder le
     * chemin original plutot que de risquer de changer la semantique.
     */
    if (
        dst0 < src_after
        &&
        src0 < dst_end
    )
    {
        return 0;
    }

    /* Deuxieme passage : decode natif. */
    src = src0;
    uint8_t *dst = dst0;
    distance = 0u;

    for (;;)
    {
        uint32_t code = *src++;

        if (code < 0xF0u)
        {
            uint32_t count = code + 1u;

            if (distance == 0u)
            {
                /*
                 * Pas de recouvrement source/destination d'apres la
                 * validation ci-dessus : memcpy est correct et rapide.
                 */
                memcpy(
                    dst,
                    src,
                    count
                );

                src += count;
                dst += count;
            }
            else
            {
                /*
                 * Copie volontairement en avant : les backrefs LZ
                 * peuvent reutiliser les octets tout juste produits.
                 */
                for (uint32_t i = 0u; i < count; ++i)
                {
                    *dst = dst[-(int32_t)distance];
                    ++dst;
                }
            }
        }
        else
        {
            distance = 0u;

            if (code != 0xF0u)
            {
                uint32_t packed =
                    (code << 8)
                    |
                    (uint32_t)(*src++);

                distance =
                    packed
                    -
                    0xF0FFu;
            }
        }

        if (distance == 0x0F00u)
        {
            break;
        }
    }

    /*
     * Filtre XOR final exact du pseudo-C : 0x8800 demi-mots,
     * avec dependance sur la valeur deja reconstruite 4 mots avant.
     */
    if ((dst_off & 1u) == 0u)
    {
        uint16_t *p16 =
            (uint16_t *)dst0;

        for (uint32_t i = 4u; i < 0x8800u; ++i)
        {
            p16[i] =
                (uint16_t)(
                    p16[i]
                    ^
                    p16[i - 4u]
                );
        }
    }
    else
    {
        for (uint32_t i = 4u; i < 0x8800u; ++i)
        {
            size_t o = (size_t)i * 2u;
            size_t p = (size_t)(i - 4u) * 2u;

            uint16_t cur =
                (uint16_t)dst0[o]
                |
                ((uint16_t)dst0[o + 1u] << 8);

            uint16_t prev =
                (uint16_t)dst0[p]
                |
                ((uint16_t)dst0[p + 1u] << 8);

            cur ^= prev;

            dst0[o] = (uint8_t)cur;
            dst0[o + 1u] = (uint8_t)(cur >> 8);
        }
    }

    if (out_bytes)
    {
        *out_bytes = (uint32_t)(dst - dst0);
    }

    /* Equivalent du JR $ra. */
    cpu->pc = cpu->gpr[31];
    cpu->gpr[0] = 0u;

    return 1;
}



/*
 * ============================================================
 * B135 - quick-state de debug persistant
 * ============================================================
 *
 * Objectif : atteindre Simon une seule fois, sauvegarder l'etat sur SD,
 * puis le recharger directement apres chaque nouveau build.
 *
 * Raccourcis :
 *   SELECT + X : sauvegarde
 *   SELECT + Y : recharge et reprend l'execution
 *
 * Le snapshot ne serialise jamais les pointeurs de fonctions CPU.
 */
#define FM_B135_QS_MAGIC       0x35333142u /* "B135" little-endian */
#define FM_B135_QS_VERSION     2u
#define FM_B135_QS_RAM_SIZE    (2u * 1024u * 1024u)
#define FM_B135_QS_VRAM_WORDS  (1024u * 512u)
#define FM_B135_QS_PATH        "sdmc:/3ds/fm-new3ds/quickstate-b135.bin"

typedef struct FMB135CpuQuickState
{
    uint32_t gpr[32];
    uint32_t pc;
    uint32_t hi;
    uint32_t lo;
    uint32_t cop0[32];
    uint32_t gte_data[32];
    uint32_t gte_ctrl[32];

    uint64_t muldiv_ts_done;
    uint64_t gte_ts_done;

    uint8_t read_absorb[33];
    uint8_t read_absorb_which;
    uint8_t read_fudge;
    uint8_t ld_which_t;
    uint32_t ld_absorb;
} FMB135CpuQuickState;

typedef struct FMB135QuickStateHeader
{
    uint32_t magic;
    uint32_t version;
    uint32_t header_size;
    uint32_t ram_size;
    uint32_t vram_words;

    uint32_t frame;
    uint32_t last_dispatch_address;

    uint32_t direct2df_active;
    uint32_t menu_bridge_active;
    uint32_t str_intro_skip_pending;
    uint32_t native_video;

    uint32_t guest_frames;
    uint32_t last_latched_guest_frame;

    FMB135CpuQuickState cpu;
    FMMemoryQuickState memory;
    FMGpuQuickState gpu;
    FMRuntimeQuickState runtime;
} FMB135QuickStateHeader;

static int32_t g_b135_qs_last_result = 0;
static uint32_t g_b135_qs_save_count = 0u;
static uint32_t g_b135_qs_load_count = 0u;


static void fm_b135_cpu_quick_save(
    FMB135CpuQuickState *out,
    const CPUState *cpu
)
{
    memset(out, 0, sizeof(*out));

    memcpy(out->gpr, cpu->gpr, sizeof(out->gpr));
    out->pc = cpu->pc;
    out->hi = cpu->hi;
    out->lo = cpu->lo;
    memcpy(out->cop0, cpu->cop0, sizeof(out->cop0));
    memcpy(out->gte_data, cpu->gte_data, sizeof(out->gte_data));
    memcpy(out->gte_ctrl, cpu->gte_ctrl, sizeof(out->gte_ctrl));

    out->muldiv_ts_done = cpu->muldiv_ts_done;
    out->gte_ts_done = cpu->gte_ts_done;

    memcpy(out->read_absorb, cpu->read_absorb, sizeof(out->read_absorb));
    out->read_absorb_which = cpu->read_absorb_which;
    out->read_fudge = cpu->read_fudge;
    out->ld_which_t = cpu->ld_which_t;
    out->ld_absorb = cpu->ld_absorb;
}


static void fm_b135_cpu_quick_load(
    CPUState *cpu,
    const FMB135CpuQuickState *in
)
{
    memcpy(cpu->gpr, in->gpr, sizeof(in->gpr));
    cpu->pc = in->pc;
    cpu->hi = in->hi;
    cpu->lo = in->lo;
    memcpy(cpu->cop0, in->cop0, sizeof(in->cop0));
    memcpy(cpu->gte_data, in->gte_data, sizeof(in->gte_data));
    memcpy(cpu->gte_ctrl, in->gte_ctrl, sizeof(in->gte_ctrl));

    cpu->muldiv_ts_done = in->muldiv_ts_done;
    cpu->gte_ts_done = in->gte_ts_done;

    memcpy(cpu->read_absorb, in->read_absorb, sizeof(in->read_absorb));
    cpu->read_absorb_which = in->read_absorb_which;
    cpu->read_fudge = in->read_fudge;
    cpu->ld_which_t = in->ld_which_t;
    cpu->ld_absorb = in->ld_absorb;

    cpu->gpr[0] = 0u;
}


static int fm_b135_quick_save(
    CPUState *cpu,
    const uint8_t *ram,
    const uint16_t *vram,
    uint32_t frame,
    uint32_t last_dispatch_address
)
{
    if (!cpu || !ram || !vram)
    {
        return -1;
    }

    FMB135QuickStateHeader state;
    memset(&state, 0, sizeof(state));

    state.magic = FM_B135_QS_MAGIC;
    state.version = FM_B135_QS_VERSION;
    state.header_size = (uint32_t)sizeof(state);
    state.ram_size = FM_B135_QS_RAM_SIZE;
    state.vram_words = FM_B135_QS_VRAM_WORDS;

    state.frame = frame;
    state.last_dispatch_address = last_dispatch_address;

    state.direct2df_active = g_direct2df_active;
    state.menu_bridge_active = g_b102_menu_bridge_active;
    state.str_intro_skip_pending = g_str_intro_skip_pending;
    state.native_video = (uint32_t)g_b42_native_video;

    state.guest_frames = g_b85_guest_frames;
    state.last_latched_guest_frame = g_b85_last_latched_guest_frame;

    fm_b135_cpu_quick_save(
        &state.cpu,
        cpu
    );

    fm_memory_quick_save(
        &state.memory
    );

    fm_gpu_quick_save(
        &state.gpu
    );

    fm_runtime_quick_save(
        &state.runtime
    );

    FILE *fp = fopen(FM_B135_QS_PATH, "wb");

    if (!fp)
    {
        return -2;
    }

    int ok =
        fwrite(&state, sizeof(state), 1u, fp) == 1u
        &&
        fwrite(ram, FM_B135_QS_RAM_SIZE, 1u, fp) == 1u
        &&
        fwrite(
            vram,
            sizeof(uint16_t) * FM_B135_QS_VRAM_WORDS,
            1u,
            fp
        ) == 1u;

    if (fclose(fp) != 0)
    {
        ok = 0;
    }

    return ok ? 0 : -3;
}


static int fm_b135_quick_load(
    CPUState *cpu,
    uint8_t *ram,
    uint16_t *vram,
    unsigned *frame,
    uint32_t *last_dispatch_address
)
{
    if (!cpu || !ram || !vram || !frame || !last_dispatch_address)
    {
        return -1;
    }

    FILE *fp = fopen(FM_B135_QS_PATH, "rb");

    if (!fp)
    {
        return -2;
    }

    const long expected_size =
        (long)sizeof(FMB135QuickStateHeader)
        +
        (long)FM_B135_QS_RAM_SIZE
        +
        (long)(sizeof(uint16_t) * FM_B135_QS_VRAM_WORDS);

    if (
        fseek(fp, 0, SEEK_END) != 0
        ||
        ftell(fp) != expected_size
        ||
        fseek(fp, 0, SEEK_SET) != 0
    )
    {
        fclose(fp);
        return -3;
    }

    FMB135QuickStateHeader state;

    if (
        fread(&state, sizeof(state), 1u, fp) != 1u
        ||
        state.magic != FM_B135_QS_MAGIC
        ||
        state.version != FM_B135_QS_VERSION
        ||
        state.header_size != sizeof(state)
        ||
        state.ram_size != FM_B135_QS_RAM_SIZE
        ||
        state.vram_words != FM_B135_QS_VRAM_WORDS
    )
    {
        fclose(fp);
        return -4;
    }

    if (
        fread(ram, FM_B135_QS_RAM_SIZE, 1u, fp) != 1u
        ||
        fread(
            vram,
            sizeof(uint16_t) * FM_B135_QS_VRAM_WORDS,
            1u,
            fp
        ) != 1u
    )
    {
        fclose(fp);
        return -5;
    }

    fclose(fp);

    fm_memory_quick_load(
        &state.memory
    );

    fm_gpu_quick_load(
        &state.gpu
    );

    fm_runtime_quick_load(
        &state.runtime
    );

    fm_b135_cpu_quick_load(
        cpu,
        &state.cpu
    );

    *frame = state.frame;
    *last_dispatch_address = state.last_dispatch_address;

    g_direct2df_active = state.direct2df_active ? 1u : 0u;
    g_b102_menu_bridge_active = state.menu_bridge_active ? 1u : 0u;
    g_str_intro_skip_pending = state.str_intro_skip_pending;
    g_b42_native_video = state.native_video ? 1 : 0;

    g_b85_guest_frames = state.guest_frames;
    g_b85_last_latched_guest_frame = state.last_latched_guest_frame;

    /*
     * Un snapshot est pris entre deux tranches host : aucune attente HLE
     * ne doit rester armee apres un redemarrage de l'application.
     */
    g_vsync_wait_active = 0u;
    g_vsync_wait_until_frame = 0u;
    g_b108_vsync_sync_valid = 0u;

    /*
     * Forcer un nouveau latch/present depuis la VRAM restauree.
     */
    g_b84_latch_valid = 0u;
    g_b86_present_dirty = 1u;

    g_b65_stop_code = 0u;
    g_b65_stop_pc = 0u;
    g_b65_stop_ra = 0u;
    g_b65_stop_detail = 0u;

    return 0;
}

int main(void)
{
    gfxInitDefault();
    gfxSet3D(false);

    consoleInit(
        GFX_BOTTOM,
        NULL
    );

    bool is_new = false;

    APT_CheckNew3DS(
        &is_new
    );

    if (is_new)
    {
        osSetSpeedupEnable(
            true
        );
    }


    /*
     * ========================================================
     * Memory
     * ========================================================
     */

    uint16_t *vram =
        calloc(
            1024 * 512,
            sizeof(uint16_t)
        );

    uint16_t *preview =
        malloc(
            320
            * 256
            * sizeof(uint16_t)
        );

    /* B24 : fond WA_MRG + primitives GPU du runtime superposees. */
    uint16_t *composite =
        malloc(
            320
            * 256
            * sizeof(uint16_t)
        );

    uint8_t *ram =
        malloc(
            2
            * 1024
            * 1024
        );

    if (
        !vram
        || !preview
        || !composite
        || !ram
    )
    {
        printf(
            "Memoire insuffisante.\n"
        );

        while (aptMainLoop())
        {
            hidScanInput();

            if (
                hidKeysDown()
                & KEY_START
            )
            {
                break;
            }

            gspWaitForVBlank();
        }

        free(vram);
        free(preview);
        free(composite);
        free(ram);

        gfxExit();
        return 1;
    }

    memset(
        ram,
        0,
        2 * 1024 * 1024
    );


    /*
     * ========================================================
     * Renderer / GPU
     * ========================================================
     */

    sw_renderer_init(
        vram
    );

    sw_renderer_set_scale(
        1
    );

    fm_gpu_init(
        vram
    );


    /*
     * ========================================================
     * Preview prototype
     * ========================================================
     */

    int have_preview =
        load_preview(
            preview
        );

    /*
     * B15 : pas de preview artificielle pendant le bring-up.
     * On veut voir la VRAM du vrai jeu des qu'un seul pixel apparait.
     */
    int show_preview = 0;

    int crop = 0;
    int x = 160;
    int y = 128;


    /*
     * ========================================================
     * Disc / EXE
     * ========================================================
     */

    uint32_t entry = 0;

    int disc_status =
        fm_disc_open(
            "sdmc:/3ds/fm-new3ds/disc.bin"
        );

    int exe_status =
        disc_status
            ? -99
            : fm_disc_load_exe(
                ram,
                &entry
            );

    /* B24 : WA_MRG PAL-FR + pont vers les requetes du runtime. */


    /*
     * ========================================================
     * PS1 CPU
     * ========================================================
     */

    int memory_status = -1;

    CPUState *cpu = NULL;

    uint32_t first_instruction = 0;

    if (exe_status == 0)
    {
        fm_memory_init(
            ram,
            2 * 1024 * 1024
        );

        fm_interp_bind_ram(
            ram,
            2u * 1024u * 1024u
        );

        fm_cpu_init(
            entry
        );

        memory_status =
            fm_memory_self_test();

        cpu =
            fm_cpu_get();

        first_instruction =
            cpu->read_word(
                cpu->pc
            );
    }


    /*
     * B24 : garder un background de reference immediat, puis le runtime
     * remplacera automatiquement cet index via le hook 8002E11C.
     */
    if (disc_status == 0 && cpu && memory_status == 0)
    {
        fm_bg_begin(cpu, preview);
    }


    /*
     * ========================================================
     * Runtime state
     * ========================================================
     */

    int probe_ran = 0;
    int game_running = 0;
    int static_miss = 0;

    uint32_t last_dispatch_address = 0;

    uint32_t low_jump_from = 0;
    uint32_t low_jump_target = 0;
    uint32_t low_jump_ra = 0;
    uint32_t low_jump_t1 = 0;
    uint32_t low_jump_opcode = 0;

    FMRuntimeProbeResult probe;

    memset(
        &probe,
        0,
        sizeof(probe)
    );

    int interp_ran = 0;

    FMInterpResult interp;

    memset(
        &interp,
        0,
        sizeof(interp)
    );

    unsigned frame = 0;
    uint16_t old_pad = 0;
    uint64_t render_ticks = 0;
    unsigned render_count = 0;

    /*
     * GP0 par frame :
     *
     * fm_gpu_gp0_count() est cumulatif. Cette valeur permet de
     * distinguer un jeu réellement actif d'un compteur simplement
     * très élevé depuis le boot.
     */
    uint64_t gp0_prev_frame =
        fm_gpu_gp0_count();

    uint64_t gp0_last_frame =
        0;

    fm_cd_hle_reset();


    /*
     * ========================================================
     * Main loop
     * ========================================================
     */

    while (aptMainLoop())
    {
        uint64_t b105_loop_start_ms = osGetTime();

        int b131_presented_this_loop = 0;

        /*
         * B93 : le vieux maximum B91 masquait les hotspots recurrents
         * avec une grosse fonction de chargement vue une seule fois.
         * Une fois le menu atteint, afficher un maximum glissant simple
         * en remettant la valeur a zero toutes les ~4 secondes.
         */
        if (
            frame != 0u
            &&
            (frame % 240u) == 0u
            &&
            g_b73_hit_menu_update != 0u
        )
        {
            g_b91_slow_handoff_ms = 0u;
            g_b91_slow_handoff_pc = 0u;
        }

        hidScanInput();

        uint32_t held =
            hidKeysHeld();

        uint32_t down =
            hidKeysDown();


        /*
         * B58 - Etat manette PS1 correspondant aux boutons 3DS.
         *
         * fm_pad_bits() produit le format pad PS1 actif-bas.
         * Le moteur de Forbidden Memories utilise ensuite, dans
         * DAT_8009C70C, le masque actif-haut avant de calculer
         * held / pressed / repeat via FUN_8003CEA4.
         */
        uint16_t pad =
            fm_pad_bits(
                held
            );

        /*
         * fm_pad_bits() expose les bits dans l'ordre PS1 habituel.
         * Le jeu, lui, reconstruit les deux octets avec CONCAT11()
         * dans l'ordre oppose. Reproduire exactement ce format ici.
         */
        uint16_t psx_native =
            (uint16_t)(
                ~pad
            );

        uint16_t psx_pressed =
            (uint16_t)(
                (psx_native << 8)
                |
                (psx_native >> 8)
            );

        g_b80_last_native = psx_native;
        g_b80_last_guest = psx_pressed;

        if (down & KEY_DDOWN)
        {
            ++g_b80_down_hits;
        }

        if (down & KEY_DUP)
        {
            ++g_b80_up_hits;
        }

        if (down & KEY_B)
        {
            ++g_b80_cross_hits;
        }

        if (down & KEY_A)
        {
            ++g_b80_circle_hits;
        }


        /*
         * B81 - convertir les fronts hote en format guest, puis
         * les conserver jusqu'au prochain vrai 80180390.
         *
         * Format guest :
         *   UP/DOWN/LEFT/RIGHT = 1000/4000/8000/2000
         *   Cross/Circle       = 0040/0020
         *   Triangle/Square    = 0010/0080
         */
        if (g_b102_menu_bridge_active != 0u)
        {
            uint32_t b81_mask = 0u;

            if (down & KEY_DUP)
            {
                b81_mask |= 0x1000u;
            }

            if (down & KEY_DRIGHT)
            {
                b81_mask |= 0x2000u;
            }

            if (down & KEY_DDOWN)
            {
                b81_mask |= 0x4000u;
            }

            if (down & KEY_DLEFT)
            {
                b81_mask |= 0x8000u;
            }

            /*
             * Mapping 3DS -> PS1 deja utilise par fm_pad_bits :
             * B = Cross, A = Circle, X = Triangle, Y = Square.
             */
            if (down & KEY_B)
            {
                b81_mask |= 0x0040u;
            }

            if (down & KEY_A)
            {
                b81_mask |= 0x0020u;
            }

            if (down & KEY_X)
            {
                b81_mask |= 0x0010u;
            }

            if (down & KEY_Y)
            {
                b81_mask |= 0x0080u;
            }

            /*
             * B83 : START guest = 0x0800.
             * C'est exactement le bit teste par le garde FX de
             * seed_80180390.
             */
            if (down & KEY_START)
            {
                b81_mask |= 0x0800u;
                ++g_b83_start_armed;
            }

            if (b81_mask != 0u)
            {
                g_b81_pending_mask |= b81_mask;
                ++g_b81_armed;
            }
        }



        /*
         * ====================================================
         * B103 - fronts hote pour le clavier du nom
         * ====================================================
         *
         * FUN_800304D0 rafraichit g_b103_name_active_frames a
         * chaque passage. Hors de cet ecran, ce bridge s'eteint
         * tout seul et ne pollue pas le reste du jeu.
         */
        if (g_b103_name_active_frames != 0u)
        {
            uint32_t b103_mask = 0u;

            if (down & KEY_DUP)    b103_mask |= 0x1000u;
            if (down & KEY_DRIGHT) b103_mask |= 0x2000u;
            if (down & KEY_DDOWN)  b103_mask |= 0x4000u;
            if (down & KEY_DLEFT)  b103_mask |= 0x8000u;

            if (down & KEY_B) b103_mask |= 0x0040u; /* Cross */
            if (down & KEY_A) b103_mask |= 0x0020u; /* Circle */
            if (down & KEY_X) b103_mask |= 0x0010u; /* Triangle */
            if (down & KEY_Y) b103_mask |= 0x0080u; /* Square */

            if (b103_mask != 0u)
            {
                g_b103_name_pending_mask |= b103_mask;
            }

            --g_b103_name_active_frames;
        }
        else
        {
            /*
             * Aucun passage recent par le clavier : jeter une
             * eventuelle impulsion jamais consommee.
             */
            g_b103_name_pending_mask = 0u;
        }


        /*
         * ====================================================
         * B72 - START titre identique au probe PC : 10 frames
         * ====================================================
         *
         * Ne pas activer pendant le START de bring-up B61.
         * Le gate ci-dessous n'est vrai qu'apres :
         *   - l'intro STR,
         *   - la file graphique B70,
         *   - le retour propre de FUN_80046750.
         */
        int b72_title_stage =
            (
                g_str_intro_last_done != 0u
                &&
                g_b70_ready_bridge != 0u
                &&
                g_b69_after_46750 != 0u
            );

        if (
            (down & KEY_START)
            &&
            b72_title_stage
        )
        {
            ++g_b72_start_down_count;

            g_b72_start_hold_frames = 10u;
            g_b72_start_last_frame = frame;
            g_b72_start_last_host_held = held;
            g_b72_start_last_host_down = down;

            if (g_b73_menu_force_count == 0u)
            {
                g_b73_menu_force_request = 1u;
            }
        }

        if (
            b72_title_stage
            &&
            g_b72_start_hold_frames != 0u
        )
        {
            /*
             * Dans DAT_8009C70C, START est dans l'octet haut :
             * bit PS1 0x0008 -> format guest 0x0800.
             */
            psx_pressed |= 0x0800u;

            g_b72_start_last_psx =
                psx_pressed;

            --g_b72_start_hold_frames;
        }


        /*
         * ====================================================
         * B73 - transition controlee vers l'etat resident 8
         * ====================================================
         *
         * Table 80091F7C :
         *   index 8 -> FUN_8002D75C
         *
         * Ce handler appelle le vrai chargeur SU puis l'overlay
         * 8018001C/80180390. On ne forge donc ni image, ni menu.
         */
        if (
            b72_title_stage
            &&
            g_b73_menu_force_request
            &&
            g_b73_menu_force_count == 0u
            &&
            g_b72_start_hold_frames == 0u
            &&
            frame >= (g_b72_start_last_frame + 10u)
        )
        {
            g_b73_state60a_before =
                fm_memory_read_byte(
                    0x8009C60Au
                );

            g_b73_state60d_before =
                fm_memory_read_byte(
                    0x8009C60Du
                );

            /*
             * 60E devient l'index initial du menu dans 8018001C.
             * 0 = premiere entree.
             *
             * 60C n'est pas exploite par le pseudo-C de 8018001C,
             * mais 1 correspond a la convention d'entree normale.
             */
            fm_memory_write_byte(
                0x8009C60Cu,
                1u
            );

            fm_memory_write_byte(
                0x8009C60Eu,
                0u
            );

            /*
             * Conserver la destination "menu" puis selectionner
             * directement l'etat 8. Le dispatcher 8002DF60 ajoutera
             * lui-meme ses bits de service 0x80/0x40.
             */
            fm_memory_write_byte(
                0x8009C60Du,
                8u
            );

            fm_memory_write_byte(
                0x8009C60Au,
                8u
            );

            g_b73_state60a_after =
                fm_memory_read_byte(
                    0x8009C60Au
                );

            g_b73_state60d_after =
                fm_memory_read_byte(
                    0x8009C60Du
                );

            g_b73_menu_force_frame = frame;
            g_b73_menu_force_request = 0u;
            ++g_b73_menu_force_count;
        }


        /*
         * B61 - START garde son usage normal cote PS1, mais pendant
         * le verrou de boot 80168160 il demande aussi une sortie
         * controlee de la boucle asynchrone.
         */
        if (
            (down & KEY_START)
            &&
            g_b47_68160_return != 0u
            &&
            g_b47_m_43f54 == 0u
            &&
            g_b61_bridge_count == 0u
        )
        {
            g_b61_skip_request = 1u;
        }


        /*
         * Exit
         */
        if (
            (
                held
                &
                (
                    KEY_START
                    |
                    KEY_SELECT
                )
            )
            ==
            (
                KEY_START
                |
                KEY_SELECT
            )
        )
        {
            break;
        }


        /*
         * ====================================================
         * RUN / PAUSE
         * ====================================================
         */

        /*
         * A sert uniquement a DEMARRER le runtime s'il est arrete.
         * Une fois le jeu lance, A redevient un vrai bouton PS1.
         *
         * Le tactile 3DS devient notre pause/reprise de debug.
         */
        if (
            (down & KEY_A)
            && !game_running
            && exe_status == 0
            && memory_status == 0
        )
        {
            game_running = 1;
            static_miss = 0;

            if (!probe_ran)
            {
                fm_cpu_init(
                    entry
                );

                cpu =
                    fm_cpu_get();
            }
        }

        if (
            (down & KEY_TOUCH)
            && exe_status == 0
            && memory_status == 0
        )
        {
            game_running =
                !game_running;

            static_miss = 0;
        }


        /*
         * ====================================================
         * RESET
         * ====================================================
         */

        /*
         * RESET debug : SELECT + B.
         * B seul est maintenant transmis au jeu comme bouton Cross.
         */
        if (
            (
                held
                &
                (
                    KEY_L
                    |
                    KEY_R
                    |
                    KEY_SELECT
                )
            )
            ==
            (
                KEY_L
                |
                KEY_R
                |
                KEY_SELECT
            )
            &&
            (down & KEY_B)
        )
        {
            ++g_b65_reset_count;
            g_b65_stop_code = 9u;
            g_b65_stop_pc = cpu ? cpu->pc : 0u;
            g_b65_stop_ra = cpu ? cpu->gpr[31] : 0u;
            g_b65_stop_detail = 0u;

            game_running = 0;
            static_miss = 0;
            last_dispatch_address = 0;

            low_jump_from = 0;
            low_jump_target = 0;
            low_jump_ra = 0;
            low_jump_t1 = 0;
            low_jump_opcode = 0;

            fm_cd_hle_reset();

            if (exe_status == 0)
            {
                /*
                 * Réinitialise les registres IRQ / scratchpad
                 * tout en conservant le contenu RAM du jeu.
                 */
                fm_memory_init(
                    ram,
                    2 * 1024 * 1024
                );

                fm_interp_bind_ram(
                    ram,
                    2u * 1024u * 1024u
                );

                fm_cpu_init(
                    entry
                );

                cpu =
                    fm_cpu_get();
            }

            fm_gpu_init(
                vram
            );

            memset(
                &probe,
                0,
                sizeof(probe)
            );

            memset(
                &interp,
                0,
                sizeof(interp)
            );

            probe_ran = 0;
            interp_ran = 0;
        }


        /*
         * ====================================================
         * B135 - QUICK-STATE SELECT+X / SELECT+Y
         * ====================================================
         */
        int b135_qs_chord = 0;

        if (
            (held & KEY_SELECT)
            &&
            (down & KEY_X)
            &&
            cpu
            &&
            memory_status == 0
        )
        {
            b135_qs_chord = 1;

            g_b135_qs_last_result =
                fm_b135_quick_save(
                    cpu,
                    ram,
                    vram,
                    frame,
                    last_dispatch_address
                );

            if (g_b135_qs_last_result == 0)
            {
                ++g_b135_qs_save_count;
            }
        }

        if (
            (held & KEY_SELECT)
            &&
            (down & KEY_Y)
            &&
            cpu
            &&
            memory_status == 0
        )
        {
            b135_qs_chord = 1;

            /*
             * Nettoyer d'abord l'etat HLE host. Le quick-load restaure
             * ensuite les quelques flags de phase qui doivent survivre.
             */
            fm_cd_hle_reset();

            g_b135_qs_last_result =
                fm_b135_quick_load(
                    cpu,
                    ram,
                    vram,
                    &frame,
                    &last_dispatch_address
                );

            if (g_b135_qs_last_result == 0)
            {
                ++g_b135_qs_load_count;

                game_running = 1;
                probe_ran = 1;
                interp_ran = 0;
                static_miss = 0;

                low_jump_from = 0u;
                low_jump_target = 0u;
                low_jump_ra = 0u;
                low_jump_t1 = 0u;
                low_jump_opcode = 0u;

                memset(&probe, 0, sizeof(probe));
                memset(&interp, 0, sizeof(interp));

                old_pad = 0u;
            }
        }

        /*
         * Ne jamais transmettre la combinaison de debug au pad PS1.
         */
        if (b135_qs_chord)
        {
            psx_pressed = 0u;
        }


        /*
         * ====================================================
         * B58 - INJECTION PAD VERS LE JEU
         * ====================================================
         *
         * DAT_8009C70C est l'entree brute 32 bits consommee par
         * FUN_8003CEA4. Lower 16 bits = pad joueur 1, avec les
         * deux octets dans l'ordre reconstruit par FUN_8003CE34.
         *
         * Cela laisse le vrai code du jeu fabriquer :
         *   8009C710 = boutons maintenus
         *   8009C72C = nouveaux appuis
         *   8009C728 = repetitions
         */
        if (
            game_running
            &&
            memory_status == 0
        )
        {
            fm_memory_write_word(
                0x8009C70Cu,
                (uint32_t)psx_pressed
            );
        }


        /*
         * ====================================================
         * B59 - BIOS PAL region bridge
         * ====================================================
         *
         * Appliquer une seule fois, seulement quand le vrai overlay
         * attendu est present en RAM.
         */
        if (
            memory_status == 0
            &&
            g_b59_pal_patch_count == 0u
        )
        {
            uint32_t ov0 =
                fm_memory_read_word(
                    0x801680F4u
                );

            uint32_t ov1 =
                fm_memory_read_word(
                    0x801680F8u
                );

            uint32_t ov2 =
                fm_memory_read_word(
                    0x801680FCu
                );

            uint32_t ov3 =
                fm_memory_read_word(
                    0x80168100u
                );

            if (
                ov0 == 0x3C03BFC8u
                &&
                ov1 == 0x9063FF52u
                &&
                ov2 == 0x24020045u
                &&
                ov3 == 0x1062001Au
            )
            {
                g_b59_pal_patch_before =
                    ov1;

                /*
                 * addiu v1,zero,0x45
                 */
                fm_memory_write_word(
                    0x801680F8u,
                    0x24030045u
                );

                g_b59_pal_patch_after =
                    fm_memory_read_word(
                        0x801680F8u
                    );

                ++g_b59_pal_patch_count;
            }
        }


        /*
         * ====================================================
         * B70 - GPU queue type-0x20 completion bridge
         * ====================================================
         */
        if (
            game_running
            &&
            cpu
            &&
            cpu->pc >= 0x80046750u
            &&
            cpu->pc < 0x800469ACu
        )
        {
            uint32_t gfx_ctx =
                fm_memory_read_word(
                    0x8009C7E0u
                );

            if (
                gfx_ctx >= 0x80000000u
                &&
                gfx_ctx < 0x80200000u
            )
            {
                uint32_t count =
                    fm_memory_read_half(
                        gfx_ctx + 0x4Cu
                    );

                uint32_t type0 =
                    fm_memory_read_byte(
                        gfx_ctx + 0x80u
                    );

                uint32_t marker0 =
                    fm_memory_read_word(
                        gfx_ctx + 0x90u
                    );

                g_b70_last_ctx = gfx_ctx;
                g_b70_last_count = count;
                g_b70_last_type = type0;
                g_b70_last_marker_before = marker0;

                if (count > 1u)
                {
                    g_b70_entry1_type =
                        fm_memory_read_byte(
                            gfx_ctx + 0xB0u
                        );

                    g_b70_entry1_marker =
                        fm_memory_read_word(
                            gfx_ctx + 0xC0u
                        );
                }
                else
                {
                    g_b70_entry1_type = 0u;
                    g_b70_entry1_marker = 0u;
                }

                if (
                    count != 0u
                    &&
                    type0 == 0x20u
                    &&
                    marker0 != 0x20u
                )
                {
                    /*
                     * Publier uniquement la completion manquante.
                     */
                    fm_memory_write_word(
                        gfx_ctx + 0x90u,
                        0x20u
                    );

                    ++g_b70_ready_bridge;
                }

                g_b70_last_marker_after =
                    fm_memory_read_word(
                        gfx_ctx + 0x90u
                    );
            }
        }


        /*
         * ====================================================
         * B75 - settle de l'animation d'entree du menu
         * ====================================================
         */
        if (
            game_running
            &&
            g_b73_hit_menu_init != 0u
            &&
            g_b73_hit_menu_update > 24u
            &&
            g_b75_menu_entrance_bridge == 0u
            &&
            fm_memory_read_word(0x8009C898u) == 0x80180B4Cu
        )
        {
            uint32_t p0 =
                fm_memory_read_word(0x80184794u);

            uint32_t c0 =
                fm_memory_read_byte(0x801847C0u);

            uint32_t c5 =
                fm_memory_read_byte(0x801847C5u);

            /*
             * Signature exacte vue en B74 :
             * objet 0 hors ecran + timer d'entree encore a 16.
             */
            if (
                p0 >= 0x80000000u
                &&
                p0 < 0x80200000u
                &&
                fm_memory_read_half(p0 + 0x60u) == 0x0010u
                &&
                (int16_t)fm_memory_read_half(p0 + 0x30u)
                    ==
                    (int16_t)fm_memory_read_half(p0 + 0x36u)
            )
            {
                uint32_t settled = 0u;

                g_b75_last_c0 = c0;
                g_b75_last_c5_before = c5;

                for (unsigned i = 0; i < 11u; ++i)
                {
                    uint32_t obj =
                        fm_memory_read_word(
                            0x80184794u
                            +
                            i * 4u
                        );

                    if (
                        obj < 0x80000000u
                        ||
                        obj >= 0x80200000u
                    )
                    {
                        continue;
                    }

                    uint16_t flags =
                        fm_memory_read_half(
                            obj + 0x08u
                        );

                    int visible_group;

                    if (c0 < 5u)
                    {
                        visible_group =
                            i < 5u;
                    }
                    else
                    {
                        visible_group =
                            i >= 5u;
                    }

                    if (visible_group)
                    {
                        flags |= 0x0040u;
                    }
                    else
                    {
                        flags &= (uint16_t)~0x0040u;
                    }

                    /*
                     * Little-endian halfword writes using the byte
                     * primitive already used throughout main.c.
                     */
                    fm_memory_write_byte(
                        obj + 0x08u,
                        (uint8_t)(flags & 0xFFu)
                    );
                    fm_memory_write_byte(
                        obj + 0x09u,
                        (uint8_t)(flags >> 8)
                    );

                    uint16_t target =
                        fm_memory_read_half(
                            obj + 0x38u
                        );

                    fm_memory_write_byte(
                        obj + 0x30u,
                        (uint8_t)(target & 0xFFu)
                    );
                    fm_memory_write_byte(
                        obj + 0x31u,
                        (uint8_t)(target >> 8)
                    );

                    fm_memory_write_byte(
                        obj + 0x60u,
                        0u
                    );
                    fm_memory_write_byte(
                        obj + 0x61u,
                        0u
                    );

                    ++settled;
                }

                /*
                 * L'animation est maintenant terminee.
                 * Le vrai 80180390 peut reprendre directement sa
                 * branche interactive (navigation / validation).
                 */
                fm_memory_write_byte(
                    0x801847C5u,
                    0u
                );

                g_b75_last_c5_after =
                    fm_memory_read_byte(
                        0x801847C5u
                    );

                g_b75_objects_settled =
                    settled;

                g_b75_menu_entrance_frame =
                    frame;

                ++g_b75_menu_entrance_bridge;
            }
        }


        /*
         * ====================================================
         * B76 - charger le tail graphique SU manquant
         * ====================================================
         */
        if (
            game_running
            &&
            g_b73_hit_menu_init != 0u
            &&
            g_b75_menu_entrance_bridge != 0u
            &&
            g_b76_resource_attempt == 0u
        )
        {
            ++g_b76_resource_attempt;

            g_b76_pre_nonzero = 0u;

            for (unsigned i = 0u; i < 64u; ++i)
            {
                if (
                    fm_memory_read_byte(
                        0x801AF800u + i
                    )
                    != 0u
                )
                {
                    ++g_b76_pre_nonzero;
                }
            }

            /*
             * Ne rien toucher si la ressource est deja presente.
             */
            if (g_b76_pre_nonzero == 0u)
            {
                uint32_t su_lba = 0u;
                uint32_t su_size = 0u;

                int found =
                    fm_disc_find_file(
                        "\\DATA\\SU.MRG;1",
                        &su_lba,
                        &su_size
                    );

                if (!found)
                {
                    found =
                        fm_disc_find_file(
                            "\\SU.MRG;1",
                            &su_lba,
                            &su_size
                        );
                }

                g_b76_su_lba = su_lba;
                g_b76_su_size = su_size;

                if (
                    found
                    &&
                    su_size >= 0x39800u
                )
                {
                    /*
                     * 0x39000 / 0x800 = secteur relatif 0x72.
                     */
                    int rc =
                        fm_disc_read_sector(
                            su_lba + 0x72u,
                            g_b76_sector
                        );

                    g_b76_resource_rc = rc;

                    if (rc == 0)
                    {
                        for (unsigned i = 0u; i < 2048u; ++i)
                        {
                            fm_memory_write_byte(
                                0x801AF800u + i,
                                g_b76_sector[i]
                            );
                        }

                        /*
                         * Les objets ont ete initialises avant que la
                         * ressource soit disponible. Enlever seulement
                         * le bit 0x10 force le vrai FUN_80042090 puis
                         * FUN_80041FBC a recalculer +0x50/+0x4C.
                         */
                        for (unsigned i = 0u; i < 11u; ++i)
                        {
                            uint32_t obj =
                                fm_memory_read_word(
                                    0x80184794u + i * 4u
                                );

                            if (
                                obj < 0x80000000u
                                ||
                                obj >= 0x80200000u
                            )
                            {
                                continue;
                            }

                            uint16_t flags =
                                fm_memory_read_half(
                                    obj + 0x08u
                                );

                            flags &=
                                (uint16_t)~0x0010u;

                            fm_memory_write_byte(
                                obj + 0x08u,
                                (uint8_t)(flags & 0xFFu)
                            );

                            fm_memory_write_byte(
                                obj + 0x09u,
                                (uint8_t)(flags >> 8)
                            );

                            ++g_b76_objects_rearmed;
                        }

                        g_b76_bridge_frame = frame;
                        ++g_b76_resource_bridge;
                    }
                }
                else
                {
                    g_b76_resource_rc = -2;
                }
            }

            g_b76_post_nonzero = 0u;

            for (unsigned i = 0u; i < 64u; ++i)
            {
                if (
                    fm_memory_read_byte(
                        0x801AF800u + i
                    )
                    != 0u
                )
                {
                    ++g_b76_post_nonzero;
                }
            }
        }


        /*
         * B80 - memoriser les changements reels de selection du menu.
         */
        if (
            g_b73_hit_menu_init != 0u
            &&
            memory_status == 0
        )
        {
            uint32_t sel =
                fm_memory_read_byte(
                    0x801847C0u
                );

            if (g_b80_last_sel == 0xFFFFFFFFu)
            {
                g_b80_last_sel = sel;
            }
            else if (sel != g_b80_last_sel)
            {
                g_b80_last_sel = sel;
                g_b80_last_sel_frame = frame;
                ++g_b80_sel_changes;
            }

            if (
                g_b81_injected != 0u
                &&
                g_b81_last_frame == 0u
            )
            {
                g_b81_last_frame = frame;
            }
        }


        /*
         * ====================================================
         * EXECUTION
         * ====================================================
         */

        if (
            game_running
            && cpu
            && exe_status == 0
            && memory_status == 0
        )
        {
            /*
             * B15 : une fois en mode DIRECT-2DF, chaque retour a la
             * sentinelle declenche exactement une nouvelle iteration de
             * la vraie machine d'etat au debut de la frame suivante.
             */
            if (
                g_direct2df_active
                && cpu->pc == g_direct2df_sentinel
            )
            {
                cpu->pc = 0x8002DF60u;
                cpu->gpr[31] = g_direct2df_sentinel;
                cpu->gpr[0] = 0u;

                ++g_direct2df_calls;
            }

            /*
             * Plusieurs passages ARM / BIOS / R3000A dans la meme frame.
             *
             * B16 : en DIRECT-2DF on vise une tranche courte (~5 ms max)
             * afin de rendre la main a Azahar/3DS et retrouver ~60 FPS.
             */
            uint64_t b16_slice_start_ms = osGetTime();
            unsigned b16_handoff_count = 0u;
            /*
             * B84 : beaucoup plus de handoffs possibles.
             * La vraie limite devient surtout la tranche temps de 12 ms.
             */
            /*
             * B87 : B86 atteignait 256 handoffs en ~3 ms.
             * Le plafond n'est plus le limiteur principal.
             */
            unsigned b16_handoff_limit =
                4096u;

            for (
                unsigned handoff = 0;
                handoff < b16_handoff_limit
                && game_running;
                ++handoff
            )
            {
                b16_handoff_count = handoff + 1u;

                /*
                 * B84 : borne temps pour TOUS les modes.
                 *
                 * 12 ms laisse encore quelques ms au rendu/present avant
                 * le VBlank 60 Hz, tout en donnant au fallback R3000A
                 * assez de temps pour terminer un vrai update guest.
                 */
                if (
                    handoff != 0u
                    && (osGetTime() - b16_slice_start_ms) >= g_b105_slice_budget_ms
                )
                {
                    ++g_b16_slice_yields;
                    ++g_b84_budget_yields;
                    break;
                }
                uint32_t dispatch_address =
                    cpu->pc;

                uint32_t phys =
                    dispatch_address
                    & 0x1FFFFFFFu;

                /*
                 * B130: diagnostic handoff timer is disabled in release.
                 */
#if !defined(NDEBUG)
                uint64_t b91_handoff_start_ms = osGetTime();
#endif


                /*
                 * ============================================
                 * B37 - DMA2/GPU sync
                 * ============================================
                 *
                 * FUN_800819E0:
                 *   80081A90 -> poll DMA2 CHCR bit24
                 *   80081AC0 -> poll GPUSTAT bit26
                 *
                 * Notre DMA host est immediat : si bit24 reste leve
                 * quand le jeu entre dans cette attente, on termine le
                 * handshake en relachant START/BUSY + manual trigger.
                 */
                if (
                    phys >= 0x00081A90u
                    &&
                    phys <= 0x00081ABCu
                )
                {
                    uint32_t chcr =
                        fm_memory_read_word(0x1F8010A8u);

                    g_b37_last_chcr_before = chcr;

                    g_b78_dma_madr =
                        fm_memory_read_word(0x1F8010A0u);

                    g_b78_dma_bcr =
                        fm_memory_read_word(0x1F8010A4u);

                    g_b78_dma_chcr = chcr;
                    ++g_b78_dma_wait_samples;

                    g_b37_last_gpustat =
                        fm_memory_read_word(0x1F801814u);
                    g_b37_ring_write =
                        fm_memory_read_word(0x80095BC0u);
                    g_b37_ring_read =
                        fm_memory_read_word(0x80095BC4u);

                    ++g_b37_dma_wait_hits;

                    if (chcr & 0x01000000u)
                    {
                        uint32_t done_chcr =
                            chcr
                            &
                            ~(
                                0x01000000u
                                |
                                0x10000000u
                            );

                        fm_memory_write_word(
                            0x1F8010A8u,
                            done_chcr
                        );

                        g_b37_last_chcr_after =
                            fm_memory_read_word(0x1F8010A8u);

                        ++g_b37_dma_forced_clear;
                    }
                    else
                    {
                        g_b37_last_chcr_after = chcr;
                    }

                    /*
                     * B71 - si START/BUSY est bien retombe, la condition
                     * du do/while PS1 est satisfaite. Sortir explicitement
                     * du basic-block de polling et laisser le vrai code
                     * enchainer sur l'attente GPUSTAT.
                     */
                    if (
                        (
                            g_b37_last_chcr_after
                            &
                            0x01000000u
                        )
                        ==
                        0u
                    )
                    {
                        g_b71_last_escape_from =
                            dispatch_address;

                        cpu->pc =
                            0x80081AC0u;

                        dispatch_address =
                            cpu->pc;

                        phys =
                            dispatch_address
                            &
                            0x1FFFFFFFu;

                        g_b71_last_escape_to =
                            dispatch_address;

                        ++g_b71_dma_loop_escape;
                    }
                }

                if (
                    phys >= 0x00081AC0u
                    &&
                    phys <= 0x00081ADCu
                )
                {
                    g_b37_last_gpustat =
                        fm_memory_read_word(0x1F801814u);
                    g_b37_ring_write =
                        fm_memory_read_word(0x80095BC0u);
                    g_b37_ring_read =
                        fm_memory_read_word(0x80095BC4u);
                }


                /*
                 * Retour normal d'une iteration DIRECT-2DF.
                 * Ne pas tenter de dispatcher la sentinelle.
                 */
                if (
                    g_direct2df_active
                    && dispatch_address == g_direct2df_sentinel
                )
                {
                    ++g_direct2df_returns;
                    ++g_b85_sentinel_hits;
                    ++g_b85_guest_frames;

                    g_direct2df_last_pc = dispatch_address;
                    static_miss = 0;

                    /*
                     * Une frame logique guest vient d'etre terminee.
                     * On rend la main au host : la presentation B85
                     * publiera alors cette image complete.
                     */
                    break;
                }

                /* Retour du vrai callback LibCD guest lance par B33/B34. */
                if (
                    g_b33_cb_active
                    && dispatch_address == g_b33_cb_sentinel
                )
                {
                    uint32_t resume_pc = g_b33_cb_resume;
                    uint32_t completed_cmd = g_b33_cb_cmd & 0xFFu;

                    g_b33_cb_active = 0u;
                    ++g_b33_cb_done;

                    /* B36: le callback est une interruption logique.
                     * Restaurer les registres du caller de la commande,
                     * puis seulement poser la valeur de retour de l'enqueue. */
                    for (unsigned i = 0; i < 32u; ++i)
                    {
                        cpu->gpr[i] = g_b33_saved_gpr[i];
                    }
                    ++g_b33_ctx_restored;

                    if (g_b68_return_req_id != 0u)
                    {
                        /*
                         * Retour d'un vrai 8007B78C HLE.
                         * L'ID est associe au callback qui vient de finir,
                         * donc il ne peut plus etre ecrase par une requete
                         * plus recente.
                         */
                        cpu->gpr[2] = g_b68_return_req_id;
                        g_b68_return_req_id = 0u;
                    }
                    else
                    {
                        /*
                         * Appel raw 8007BA00 : API booleenne classique.
                         */
                        cpu->gpr[2] = 1u;
                    }

                    cpu->pc = resume_pc;
                    cpu->gpr[0] = 0u;

                    /*
                     * ReadN accepte : le vrai controleur PS1 livrerait
                     * ensuite CdlDataReady (event 1). On l'arme pour la
                     * frame suivante, afin de ne pas faire completion et
                     * data-ready dans la meme pseudo-interruption.
                     */
                    if (completed_cmd == 0x06u)
                    {
                        g_b34_ready_pending = 1u;
                        g_b34_ready_arm_frame = frame + 1u;
                    }

                    static_miss = 0;
                    continue;
                }

                /*
                 * B35 : retour du vrai cleanup CD FUN_800143D4.
                 * Reprendre exactement le PC suspendu avant le
                 * DataReady une fois les flags CD nettoyes par le jeu.
                 */
                if (
                    g_b35_finalizer_active
                    && dispatch_address == g_b35_finalizer_sentinel
                )
                {
                    uint32_t resume_pc = g_b35_saved_pc;

                    g_b35_finalizer_active = 0u;
                    ++g_b35_finalizer_done;
                    g_b35_c460_after = cpu->read_word(0x8009C460u);


                    if (g_b50_cleanup_active)
                    {
                        g_b50_cleanup_active = 0u;
                        ++g_b50_cleanup_done;
                        g_b50_c460_after =
                            cpu->read_word(0x8009C460u);
                        g_b50_c484_after =
                            cpu->read_word(0x8009C484u);
                    }

                    /* B36: ne surtout pas remplacer RA par PC.
                     * Sur B35 cela pouvait transformer VSync en boucle
                     * auto-referente (PC=RA=800746B8). */
                    for (unsigned i = 0; i < 32u; ++i)
                    {
                        cpu->gpr[i] = g_b35_saved_gpr[i];
                    }
                    ++g_b35_ctx_restored;

                    cpu->pc = resume_pc;
                    cpu->gpr[0] = 0u;

                    static_miss = 0;
                    continue;
                }

                /* Retour du callback CdlDataReady (80013B44). */
                if (
                    g_b34_ready_active
                    && dispatch_address == g_b34_ready_sentinel
                )
                {
                    uint32_t resume_pc = g_b34_ready_saved_pc;

                    g_b34_ready_active = 0u;
                    ++g_b34_ready_done;

                    /* Le callback peut librement modifier a/t/v/ra. Pour
                     * retrouver la requete, utiliser le GP sauvegarde du
                     * contexte interrompu, pas celui de fin de callback. */
                    uint32_t req = 0u;
                    if (g_b34_ready_saved_gpr[28] != 0u)
                    {
                        req = cpu->read_word(g_b34_ready_saved_gpr[28] + 0x10u);
                    }
                    if (req < 0x80000000u || req >= 0x80200000u)
                    {
                        req = 0x800EB1B8u;
                    }

                    g_b34_ready_req = req;
                    g_b34_ready_after = cpu->read_word(req + 0x10u);

                    /* B36 : restaurer le vrai contexte interrompu AVANT
                     * de reprendre ou d'appeler le cleanup final. */
                    for (unsigned i = 0; i < 32u; ++i)
                    {
                        cpu->gpr[i] = g_b34_ready_saved_gpr[i];
                    }
                    ++g_b34_ready_ctx_restored;
                    cpu->pc = resume_pc;
                    cpu->gpr[0] = 0u;

                    if ((int32_t)g_b34_ready_after > 0)
                    {
                        g_b34_ready_pending = 1u;
                        g_b34_ready_arm_frame = frame + 1u;
                    }
                    else
                    {
                        g_b34_ready_pending = 0u;
                        g_cd_reading = 0;

                        /* Dernier secteur consomme : appeler le vrai
                         * cleanup depuis le contexte restaure, puis remettre
                         * CE MEME contexte apres son retour. */
                        g_b35_finalizer_resume = resume_pc;
                        g_b35_saved_pc = resume_pc;
                        g_b35_saved_ra = cpu->gpr[31];
                        for (unsigned i = 0; i < 32u; ++i)
                        {
                            g_b35_saved_gpr[i] = cpu->gpr[i];
                        }
                        ++g_b35_ctx_saved;

                        g_b35_c460_before = cpu->read_word(0x8009C460u);
                        g_b35_finalizer_active = 1u;
                        ++g_b35_finalizer_started;

                        cpu->pc = g_b35_finalizer_addr;
                        cpu->gpr[31] = g_b35_finalizer_sentinel;
                        cpu->gpr[0] = 0u;
                    }

                    static_miss = 0;
                    continue;
                }

                /*
                 * =================================================
                 * B51 - queue de secteur partielle dans 43CD4
                 * =================================================
                 *
                 * Ne rien inventer dans la structure CD. Si 43CD4 est
                 * deja entre, que des secteurs ont ete livres et qu'il
                 * reste entre 1 et 0x800 octets sans evenement DataReady
                 * arme, rearmer exactement le callback B34.
                 */
                if (
                    g_hit_delay_wait != 0u
                    &&
                    g_b47_m_43f3c == 0u
                    &&
                    g_b32_getsec_ok != 0u
                    &&
                    !g_b34_ready_pending
                    &&
                    !g_b34_ready_active
                    &&
                    !g_b33_cb_active
                    &&
                    !g_b35_finalizer_active
                )
                {
                    const uint32_t req =
                        0x800EB1B8u;

                    uint32_t remaining =
                        cpu->read_word(req + 0x10u);

                    uint32_t type =
                        cpu->read_byte(req + 0x46u);

                    uint32_t c460 =
                        cpu->read_word(0x8009C460u);

                    uint32_t c484 =
                        cpu->read_word(0x8009C484u);

                    g_b51_last_rem = remaining;
                    g_b51_last_type = type;
                    g_b51_last_c460 = c460;
                    g_b51_last_c484 = c484;

                    if (
                        remaining > 0u
                        &&
                        remaining <= 0x800u
                        &&
                        (
                            (c460 & 0x02000030u) != 0u
                            ||
                            c484 != 0u
                        )
                    )
                    {
                        g_b34_ready_pending = 1u;
                        g_b34_ready_arm_frame = frame + 1u;
                        ++g_b51_rearm_count;
                    }
                }


                /*
                 * B34 : livraison d'un vrai CdlDataReady au callback
                 * moteur 80013B44. Ce callback appelle ensuite
                 * FUN_8007E968, qui est deja ponte par B32 vers disc.bin.
                 */
                if (
                    g_b34_ready_pending
                    && !g_b34_ready_active
                    && !g_b33_cb_active
                    && frame >= g_b34_ready_arm_frame
                )
                {
                    uint32_t req = 0u;
                    if (cpu->gpr[28] != 0u)
                    {
                        req = cpu->read_word(cpu->gpr[28] + 0x10u);
                    }
                    if (req < 0x80000000u || req >= 0x80200000u)
                    {
                        req = 0x800EB1B8u;
                    }

                    uint32_t remaining = cpu->read_word(req + 0x10u);
                    g_b34_ready_req = req;
                    g_b34_ready_before = remaining;

                    if ((int32_t)remaining > 0)
                    {
                        g_b34_ready_pending = 0u;
                        g_b34_ready_active = 1u;
                        g_b34_ready_resume = dispatch_address;
                        g_b34_ready_saved_pc = dispatch_address;
                        g_b34_ready_saved_ra = cpu->gpr[31];
                        for (unsigned i = 0; i < 32u; ++i)
                        {
                            g_b34_ready_saved_gpr[i] = cpu->gpr[i];
                        }
                        ++g_b34_ready_ctx_saved;
                        ++g_b34_ready_started;

                        cpu->gpr[4] = 1u; /* CdlDataReady */
                        cpu->gpr[5] = g_b33_result_scratch;
                        cpu->pc = g_b34_ready_cb;
                        cpu->gpr[31] = g_b34_ready_sentinel;
                        cpu->gpr[0] = 0u;

                        static_miss = 0;
                        continue;
                    }

                    g_b34_ready_pending = 0u;
                }


                if (g_direct2df_active)
                {
                    g_direct2df_last_pc = dispatch_address;
                }


                /*
                 * ============================================
                 * B50 - debloque l'attente 43CD4 avec le VRAI
                 * cleanup guest 800143D4.
                 * ============================================
                 *
                 * On ne le fait qu'une seule fois, uniquement si :
                 *   - on entre reellement dans FUN_80043CD4 ;
                 *   - au moins un secteur CD a ete livre ;
                 *   - la requete courante n'a plus d'octets ;
                 *   - C460/C484 portent encore un etat "busy".
                 *
                 * Aucun flag n'est modifie a la main : 800143D4 fait
                 * exactement le nettoyage du code PS1 original.
                 */
                if (
                    phys == 0x00043CD4u
                    &&
                    !g_b50_cleanup_triggered
                    &&
                    !g_b35_finalizer_active
                    &&
                    g_b32_getsec_ok != 0u
                )
                {
                    const uint32_t req =
                        0x800EB1B8u;

                    uint32_t remaining =
                        cpu->read_word(req + 0x10u);

                    uint32_t c460 =
                        cpu->read_word(0x8009C460u);

                    uint32_t c484 =
                        cpu->read_word(0x8009C484u);

                    g_b50_remaining =
                        remaining;

                    g_b50_c460_before =
                        c460;

                    g_b50_c484_before =
                        c484;

                    if (
                        (int32_t)remaining <= 0
                        &&
                        (
                            (c460 & 0x02000030u) != 0u
                            ||
                            c484 != 0u
                        )
                    )
                    {
                        ++g_b50_cleanup_triggered;
                        g_b50_cleanup_active = 1u;

                        /*
                         * Reutiliser le mecanisme B35/B36 deja valide :
                         * sauvegarder le contexte courant, executer le
                         * vrai cleanup, puis reprendre exactement 43CD4.
                         */
                        g_b35_finalizer_resume =
                            dispatch_address;

                        g_b35_saved_pc =
                            dispatch_address;

                        g_b35_saved_ra =
                            cpu->gpr[31];

                        for (unsigned i = 0; i < 32u; ++i)
                        {
                            g_b35_saved_gpr[i] =
                                cpu->gpr[i];
                        }

                        ++g_b35_ctx_saved;

                        g_b35_c460_before =
                            c460;

                        g_b35_finalizer_active =
                            1u;

                        ++g_b35_finalizer_started;

                        cpu->pc =
                            g_b35_finalizer_addr;

                        cpu->gpr[31] =
                            g_b35_finalizer_sentinel;

                        cpu->gpr[0] =
                            0u;

                        static_miss =
                            0;

                        continue;
                    }
                }


                /*
                 * ============================================
                 * B53 - FAST 43CD4
                 * ============================================
                 *
                 * 43CD4(0xB4) garde sa vraie condition de sortie
                 * C460/C484. On ne reduit que son compteur de delai.
                 */
                if (
                    phys == 0x00043CD4u
                    &&
                    cpu->gpr[4] == 0x000000B4u
                )
                {
                    g_b53_fast43cd4_last_in =
                        cpu->gpr[4];

                    cpu->gpr[4] =
                        2u;

                    g_b53_fast43cd4_last_out =
                        cpu->gpr[4];

                    ++g_b53_fast43cd4_hits;
                }


                /*
                 * ============================================
                 * B62 - wrappers libgte HLE
                 * ============================================
                 *
                 * Intercepter avant le code recompilé : sinon
                 * gte_execute() stoppe encore le runtime.
                 */
                if (
                    fm_b62_try_gte_helper(
                        cpu,
                        phys
                    )
                )
                {
                    static_miss = 0;
                    continue;
                }


                fm_trace_dispatch(
                    cpu,
                    dispatch_address,
                    phys
                );


                /*
                 * ============================================
                 * Diagnostic LOW RAM
                 * ============================================
                 *
                 * Capture la première entrée inattendue dans
                 * la zone kernel BIOS RAM.
                 *
                 * 0x884 / 0x894 sont des helpers PAD Psy-Q
                 * désormais gérés en HLE.
                 */
                if (
                    low_jump_target == 0
                    && phys >= 0x00000500u
                    && phys < 0x00008500u
                    && phys != 0x00000884u
                    && phys != 0x00000894u
                    &&
                    (
                        last_dispatch_address
                        & 0x1FFFFFFFu
                    )
                    >= 0x00008500u
                )
                {
                    low_jump_from =
                        last_dispatch_address;

                    low_jump_target =
                        dispatch_address;

                    low_jump_ra =
                        cpu->gpr[31];

                    low_jump_t1 =
                        cpu->gpr[9];

                    low_jump_opcode =
                        cpu->read_word(
                            dispatch_address
                        );

                    last_dispatch_address =
                        dispatch_address;

                    g_b65_stop_code = 1u;
                    g_b65_stop_pc = dispatch_address;
                    g_b65_stop_ra = cpu->gpr[31];
                    g_b65_stop_detail = low_jump_opcode;

                    static_miss = 0;
                    game_running = 0;

                    break;
                }

                last_dispatch_address =
                    dispatch_address;


                /*
                 * ============================================
                 * TEMP HLE - B0:18 ResetEntryInt
                 *
                 * Le handler existe déjà dans
                 * fm_runtime_shim.c, mais sur le bring-up actuel
                 * fm_bios_try_hle() retourne malgré tout 0 pour
                 * cet appel. On le court-circuite ici afin de
                 * poursuivre le boot et d'exposer le prochain
                 * vrai verrou.
                 * ============================================
                 */
                if (
                    phys == 0x000000B0u
                    &&
                    (
                        cpu->gpr[9]
                        &
                        0xFFu
                    )
                    ==
                    0x18u
                )
                {
                    /*
                     * ResetEntryInt : pour le bring-up,
                     * considérer l'ancien hook comme NULL.
                     */
                    cpu->gpr[2] =
                        0;

                    cpu->pc =
                        cpu->gpr[31];

                    cpu->gpr[0] =
                        0;

                    g_bios_debug_addr =
                        0x000000B0u;

                    g_bios_debug_fn =
                        0x18u;

                    /*
                     * 2 = HLE temporaire réalisé par main.c.
                     */
                    g_bios_debug_result =
                        2;

                    static_miss =
                        0;

                    continue;
                }


                /*
                 * ============================================
                 * STR intro - fin de flux forcée UNE FOIS
                 *
                 * FUN_8006A4D8()
                 * ============================================
                 *
                 * Cette fonction renvoie 1 lorsque DAT_8009C3EB
                 * indique que le flux vidéo est terminé.
                 *
                 * Le streaming STR/CD asynchrone n'est pas encore
                 * porté sur 3DS. On reproduit donc cet état de fin
                 * uniquement pour le premier flux du boot afin de
                 * passer à l'écran titre/menu réellement rendu par
                 * Forbidden Memories.
                 */
                if (
                    phys == 0x0006A4D8u
                    &&
                    g_str_intro_skip_pending
                )
                {
                    /*
                     * DAT_8009C3EB = "stream finished".
                     */
                    cpu->write_byte(
                        0x8009C3EBu,
                        1
                    );


                    /*
                     * La fonction originale renvoie 1 dans cet état.
                     */
                    cpu->gpr[2] =
                        1;


                    cpu->pc =
                        cpu->gpr[31];


                    cpu->gpr[0] =
                        0;


                    g_str_intro_skip_pending =
                        0;


                    ++g_str_intro_skip_count;


                    static_miss =
                        0;


                    continue;
                }


                /*
                 * ============================================
                 * VSync HLE - FUN_800746B8
                 * ============================================
                 *
                 * Psy-Q:
                 *
                 *   VSync(-1) -> compteur VBlank courant
                 *   VSync(1)  -> temps depuis le dernier VSync
                 *                 en unités HSync
                 *   VSync(0)  -> attend le prochain VBlank
                 *   VSync(n)  -> attend n VBlanks
                 *
                 * Ici l'attente est réellement étalée sur la
                 * boucle GSP 3DS : pas de busy-loop, pas de timeout,
                 * et le jeu reste cadencé par le VBlank hôte.
                 */
                if (phys == 0x000746B8u)
                {
                    /*
                     * Snapshot de la pile avant de toucher aux
                     * registres de retour. Le dernier build montre
                     * que le boot repasse constamment ici.
                     */
                    fm_capture_vsync_stack(
                        cpu
                    );

                    int32_t mode =
                        (int32_t)cpu->gpr[4];


                    ++g_vsync_hle_calls;

                    g_vsync_hle_last_mode =
                        mode;


                    uint32_t timer_now =
                        cpu->read_half(
                            0x1F801110u
                        );


                    uint32_t timer_last =
                        cpu->read_word(
                            0x80092DB8u
                        )
                        &
                        0xFFFFu;


                    uint32_t timer_delta =
                        (
                            timer_now
                            -
                            timer_last
                        )
                        &
                        0xFFFFu;


                    /*
                     * VSync(-1) :
                     *
                     * Le compteur de frame 3DS est notre horloge
                     * VBlank monotone pour le bring-up.
                     */
                    if (mode < 0)
                    {
                        ++g_vsync_hle_query_calls;


                        cpu->write_word(
                            0x80093EE8u,
                            frame
                        );


                        cpu->gpr[2] =
                            frame;


                        cpu->pc =
                            cpu->gpr[31];


                        cpu->gpr[0] =
                            0;


                        static_miss =
                            0;


                        continue;
                    }


                    /*
                     * VSync(1) : temps depuis le dernier VBlank
                     * en unites HSync.
                     *
                     * Le Timer1 PS1 n'est pas encore suffisamment
                     * cadence pendant le bring-up. Utiliser directement
                     * sa valeur ici peut donc renvoyer 0 indefiniment et
                     * enfermer le jeu dans ses boucles de timeout.
                     *
                     * On derive temporairement ce temps de l'horloge hote.
                     * Forbidden Memories PAL utilise environ 15.625 kHz
                     * d'HSync, soit 15.625 lignes par milliseconde.
                     */
                    if (mode == 1)
                    {
                        ++g_vsync_hle_mode1_calls;


                        uint64_t host_now_ms =
                            osGetTime();


                        if (g_vsync_host_epoch_ms == 0)
                        {
                            g_vsync_host_epoch_ms =
                                host_now_ms;
                        }


                        uint64_t elapsed_ms =
                            host_now_ms
                            -
                            g_vsync_host_epoch_ms;


                        uint64_t host_hsync64 =
                            (
                                elapsed_ms
                                *
                                15625ull
                            )
                            /
                            1000ull;


                        if (host_hsync64 > 0xFFFFu)
                        {
                            host_hsync64 =
                                0xFFFFu;
                        }


                        uint32_t host_hsync =
                            (uint32_t)host_hsync64;


                        g_vsync_hle_mode1_last =
                            host_hsync;


                        if (host_hsync != 0u)
                        {
                            ++g_vsync_hle_mode1_nonzero;
                        }


                        if (
                            host_hsync
                            >
                            g_vsync_hle_mode1_max
                        )
                        {
                            g_vsync_hle_mode1_max =
                                host_hsync;
                        }


                        cpu->gpr[2] =
                            host_hsync;


                        cpu->pc =
                            cpu->gpr[31];


                        cpu->gpr[0] =
                            0;


                        static_miss =
                            0;


                        continue;
                    }


                    /*
                     * B108 - Psy-Q VSync timing exact.
                     *
                     * VSync(0):
                     *   target = current_vblank + 1
                     *
                     * VSync(n>=2):
                     *   target = last_synchronized_vblank + n
                     *
                     * C'est une difference importante : l'ancien code
                     * faisait toujours "frame + n", donc rajoutait des
                     * VBlanks deja ecoules et ralentissait le jeu.
                     */
                    if (!g_vsync_wait_active)
                    {
                        uint32_t target_frame;

                        if (mode <= 0)
                        {
                            ++g_b108_vsync_mode0;

                            target_frame =
                                frame
                                +
                                1u;
                        }
                        else
                        {
                            ++g_b108_vsync_modeN;

                            /*
                             * Premier VSync(n) observe : aligner le
                             * compteur logiciel sur le VBlank courant,
                             * comme apres l'initialisation Psy-Q.
                             */
                            if (!g_b108_vsync_sync_valid)
                            {
                                g_b108_vsync_last_sync_frame =
                                    frame;

                                g_b108_vsync_sync_valid =
                                    1u;
                            }

                            target_frame =
                                g_b108_vsync_last_sync_frame
                                +
                                (uint32_t)mode;
                        }

                        g_b108_vsync_last_target =
                            target_frame;

                        /*
                         * Si le target est deja passe, le vrai Psy-Q
                         * ne dort pas : la boucle while est deja finie.
                         */
                        if (frame >= target_frame)
                        {
                            ++g_b108_vsync_immediate;
                        }
                        else
                        {
                            g_vsync_wait_active =
                                1;

                            g_vsync_wait_mode =
                                mode;

                            g_vsync_wait_until_frame =
                                target_frame;

                            ++g_vsync_hle_wait_calls;
                            ++g_b108_vsync_waited;
                        }
                    }


                    /*
                     * Ne pas exécuter une boucle guest d'attente.
                     *
                     * On garde PC sur FUN_800746B8 et on rend la
                     * main à la boucle principale 3DS. Au VBlank
                     * suivant, la même entrée sera retestée.
                     */
                    if (
                        g_vsync_wait_active
                        &&
                        frame
                        <
                        g_vsync_wait_until_frame
                    )
                    {
                        static_miss =
                            0;


                        break;
                    }


                    /*
                     * Attente terminée.
                     *
                     * Reproduire les globals principaux vus dans
                     * FUN_800746B8 :
                     *
                     * 80093EE8 = compteur VBlank
                     * 80092DBC = dernier VBlank synchronisé
                     * 80092DB8 = cache Timer1
                     */
                    cpu->write_word(
                        0x80093EE8u,
                        frame
                    );


                    cpu->write_word(
                        0x80092DBCu,
                        frame
                    );


                    cpu->write_word(
                        0x80092DB8u,
                        timer_now
                    );

                    g_b108_vsync_last_sync_frame =
                        frame;

                    g_b108_vsync_sync_valid =
                        1u;


                    /*
                     * Nouveau point de depart pour VSync(1).
                     */
                    g_vsync_host_epoch_ms =
                        osGetTime();


                    cpu->gpr[2] =
                        timer_delta;


                    cpu->pc =
                        cpu->gpr[31];


                    cpu->gpr[0] =
                        0;


                    g_vsync_wait_active =
                        0;


                    g_vsync_wait_until_frame =
                        0;

                    /*
                     * B135.8: pulse survives until the presentation stage of
                     * this same host loop. This is the real stable guest-frame
                     * boundary that B135.7 was trying to observe.
                     */
                    g_b1358_vsync_completed = 1u;
                    ++g_b1358_vsync_completions;


                    static_miss =
                        0;


                    continue;
                }


                /*
                 * ============================================
                 * Jeu : console debug
                 *
                 * FUN_80090CF8(char *message)
                 *
                 * Le code original parcourt toute la chaîne puis
                 * appelle FUN_800901A8 pour chaque caractère.
                 *
                 * Sur notre bring-up cela peut coûter beaucoup de
                 * temps, surtout lorsqu'un timeout est répété.
                 *
                 * Aucun état gameplay n'est modifié par cette
                 * fonction : on capture le texte puis on retourne.
                 * ============================================
                 */
                if (phys == 0x00090CF8u)
                {
                    fm_capture_guest_string(
                        cpu,
                        cpu->gpr[4]
                    );


                    cpu->pc =
                        cpu->gpr[31];

                    cpu->gpr[0] =
                        0;

                    static_miss =
                        0;

                    continue;
                }


                /*
                 * ============================================
                 * BIOS vectors / internal PAD helpers
                 * ============================================
                 */
                if (
                    phys == 0x000000A0u
                    || phys == 0x000000B0u
                    || phys == 0x000000C0u
                    || phys == 0x00000884u
                    || phys == 0x00000894u
                )
                {
                    g_bios_debug_addr =
                        dispatch_address;

                    g_bios_debug_fn =
                        cpu->gpr[9]
                        &
                        0xFFu;

                    g_bios_debug_result =
                        fm_bios_try_hle(
                            cpu,
                            dispatch_address
                        );

                    if (g_bios_debug_result)
                    {
                        static_miss = 0;
                        continue;
                    }

                    g_b65_stop_code = 2u;
                    g_b65_stop_pc = dispatch_address;
                    g_b65_stop_ra = cpu->gpr[31];
                    g_b65_stop_detail =
                        (
                            (g_bios_debug_addr & 0xFFFFu)
                            << 8
                        )
                        |
                        (
                            g_bios_debug_fn & 0xFFu
                        );

                    static_miss = 1;
                    game_running = 0;
                    break;
                }


                /*
                 * ============================================
                 * B68 - FUN_8007BDD4(request_id, result)
                 * ============================================
                 *
                 * Le vrai code cherche l'ID dans un historique
                 * circulaire. Notre HLE fait maintenant pareil.
                 */
                if (phys == 0x0007BDD4u)
                {
                    uint32_t req_id = cpu->gpr[4];
                    uint32_t out = cpu->gpr[5];
                    uint32_t slot =
                        req_id
                        &
                        (B68_REQ_SLOTS - 1u);

                    ++g_b67_poll_calls;
                    g_b67_last_poll_id = req_id;
                    g_b67_last_out = out;
                    g_b68_last_slot = slot;
                    g_b68_last_poll_status = 0u;

                    if (g_b68_ids[slot] == req_id)
                    {
                        uint32_t status =
                            g_b68_status[slot];

                        g_b68_last_poll_status =
                            status;

                        if (status != 0u)
                        {
                            if (out != 0u)
                            {
                                for (unsigned i = 0; i < 8u; ++i)
                                {
                                    cpu->write_byte(
                                        out + i,
                                        g_b68_result[slot][i]
                                    );
                                }
                            }

                            cpu->gpr[2] = status;
                            ++g_b67_poll_complete;
                        }
                        else
                        {
                            cpu->gpr[2] = 0u;
                            ++g_b68_poll_wait;
                        }

                        cpu->pc = cpu->gpr[31];
                        cpu->gpr[0] = 0u;

                        static_miss = 0;
                        continue;
                    }

                    /*
                     * Ce n'est pas une requete creee par notre HLE :
                     * laisser le vrai guest verifier sa propre file.
                     */
                    ++g_b67_poll_miss;
                }


                /*
                 * ============================================
                 * B33 - LibCD async command callback bridge
                 *
                 * FUN_8007B78C(command, params, callback, context)
                 *
                 * La PS1 place la commande en file puis livre le callback
                 * plus tard. Sur notre backend host la commande peut etre
                 * consideree terminee immediatement : on execute toutefois
                 * le VRAI callback du jeu (event 2) afin que sa machine
                 * d'etat avance sans inventer ses effets internes.
                 * ============================================
                 */
                if (phys == 0x0007B78Cu)
                {
                    uint32_t command = cpu->gpr[4] & 0xFFu;
                    uint32_t params = cpu->gpr[5];
                    uint32_t callback = cpu->gpr[6];
                    uint32_t context = cpu->gpr[7];
                    uint32_t resume_pc = cpu->gpr[31];

                    /*
                     * B68 : request id + slot historique.
                     */
                    ++g_b67_req_seq;
                    if (g_b67_req_seq == 0u)
                    {
                        ++g_b67_req_seq;
                    }

                    g_b67_req_id = g_b67_req_seq;

                    uint32_t b68_slot =
                        g_b67_req_id
                        &
                        (B68_REQ_SLOTS - 1u);

                    g_b68_ids[b68_slot] =
                        g_b67_req_id;

                    g_b68_status[b68_slot] =
                        0u;

                    for (unsigned i = 0; i < 8u; ++i)
                    {
                        g_b68_result[b68_slot][i] = 0u;
                    }

                    ++g_b68_alloc_count;

                    /*
                     * Le callback prend-il vraiment le CPU ?
                     * Si oui, la sentinelle devra rendre l'ID au caller.
                     * Si non, on rendra l'ID directement apres schedule.
                     */
                    int b68_callback_will_run =
                        (
                            !g_b33_cb_active
                            &&
                            callback >= 0x80010000u
                            &&
                            callback < 0x801E0000u
                        );

                    if (b68_callback_will_run)
                    {
                        g_b68_return_req_id =
                            g_b67_req_id;
                    }

                    ++g_b33_async_calls;
                    g_cd_last_cmd = command;

                    if (command == 0x02u && params != 0u)
                    {
                        uint32_t minute = fm_bcd_to_u32(cpu->read_byte(params + 0u));
                        uint32_t second = fm_bcd_to_u32(cpu->read_byte(params + 1u));
                        uint32_t frame_cd = fm_bcd_to_u32(cpu->read_byte(params + 2u));
                        uint32_t absolute_sector = ((minute * 60u + second) * 75u) + frame_cd;
                        g_cd_lba = absolute_sector >= 150u ? absolute_sector - 150u : 0u;
                        g_cd_pos = 2048u;
                    }

                    if (command == 0x06u)
                    {
                        g_cd_reading = 1;
                        g_cd_pos = 2048u;
                        g_cd_error = 0;
                    }
                    else if (command == 0x09u)
                    {
                        g_cd_reading = 0;
                    }

                    fm_b33_schedule_cd_callback(
                        cpu,
                        command,
                        callback,
                        resume_pc,
                        params,
                        context
                    );

                    /*
                     * Le backend host a deja termine la commande et B66
                     * a publie CdlComplete. Le caller ne pourra observer
                     * ce slot qu'apres le retour du callback guest.
                     */
                    for (unsigned i = 0; i < 8u; ++i)
                    {
                        g_b68_result[b68_slot][i] =
                            cpu->read_byte(
                                g_b33_result_scratch + i
                            );
                    }

                    g_b68_status[b68_slot] = 2u;

                    g_b67_req_pending = 0u;
                    g_b67_req_ready = 1u;
                    g_b67_req_status = 2u;

                    /*
                     * Callback absent ou deja occupe : schedule a rendu
                     * directement la main au caller. Lui rendre alors
                     * l'ID haut niveau au lieu du bool raw.
                     */
                    if (!b68_callback_will_run)
                    {
                        cpu->gpr[2] =
                            g_b67_req_id;
                    }

                    static_miss = 0;
                    continue;
                }

                /*
                 * FUN_8007BA00(mode, params, command, callback, ctx)
                 *
                 * IMPORTANT B34 : le SLES PAL prouve que la commande est
                 * dans a2, pas dans a0. Exemple observe a 80014928 :
                 *   a0=A0, a1=gp+21C, a2=06(ReadN), a3=80013FBC.
                 */
                if (phys == 0x0007BA00u)
                {
                    uint32_t mode = cpu->gpr[4] & 0xFFu;
                    uint32_t params = cpu->gpr[5];
                    uint32_t command = cpu->gpr[6] & 0xFFu;
                    uint32_t callback = cpu->gpr[7];
                    uint32_t resume_pc = cpu->gpr[31];
                    uint32_t context = cpu->read_word(cpu->gpr[29] + 16u);

                    ++g_b33_raw_calls;
                    g_b34_last_mode = mode;
                    g_b34_last_command = command;
                    g_cd_last_cmd = command;

                    if (command == 0x02u && params != 0u)
                    {
                        uint32_t minute = fm_bcd_to_u32(cpu->read_byte(params + 0u));
                        uint32_t second = fm_bcd_to_u32(cpu->read_byte(params + 1u));
                        uint32_t frame_cd = fm_bcd_to_u32(cpu->read_byte(params + 2u));
                        uint32_t absolute_sector = ((minute * 60u + second) * 75u) + frame_cd;
                        g_cd_lba = absolute_sector >= 150u ? absolute_sector - 150u : 0u;
                        g_cd_pos = 2048u;
                    }

                    if (command == 0x06u)
                    {
                        g_cd_reading = 1;
                        g_cd_pos = 2048u;
                        g_cd_error = 0;
                    }
                    else if (command == 0x09u)
                    {
                        g_cd_reading = 0;
                    }

                    fm_b33_schedule_cd_callback(
                        cpu,
                        command,
                        callback,
                        resume_pc,
                        params,
                        context
                    );

                    static_miss = 0;
                    continue;
                }


                /*
                 * ============================================
                 * B32 - CdGetSector bridge
                 *
                 * FUN_8007E968(dest, words)
                 *
                 * Le vrai jeu arrive ici depuis son callback CD quand
                 * un secteur est pret. Sur PS1, cette routine lance le
                 * DMA3 depuis le controleur CD vers la RAM. Sur 3DS on
                 * remplace seulement ce DMA materiel par une lecture du
                 * meme LBA dans disc.bin.
                 *
                 * Le pointeur de requete courant est conserve par le
                 * moteur CD en gp+0x10. +0x24 contient le LBA logique
                 * courant de la sous-requete. Le code guest qui suit
                 * garde la responsabilite de decrementer +0x10, avancer
                 * les buffers et appeler les callbacks de completion.
                 * ============================================
                 */
                if (phys == 0x0007E968u)
                {
                    uint32_t destination = cpu->gpr[4];
                    uint32_t words = cpu->gpr[5];
                    uint32_t bytes = words * 4u;

                    if (bytes > 2048u)
                    {
                        bytes = 2048u;
                    }

                    uint32_t req = 0u;

                    if (cpu->gpr[28] != 0u)
                    {
                        req = cpu->read_word(
                            cpu->gpr[28] + 0x10u
                        );
                    }

                    if (
                        req < 0x80000000u
                        || req >= 0x80200000u
                    )
                    {
                        req = 0x800EB1B8u;
                    }

                    /*
                     * B57 IMPORTANT:
                     *
                     * req+0x24 = LBA logique de DEPART de la requete.
                     * Il reste fixe pendant que la tete CD avance.
                     */
                    uint32_t remaining =
                        cpu->read_word(req + 0x10u);

                    uint32_t base_lba =
                        cpu->read_word(req + 0x24u);

                    int new_request =
                        (
                            g_b57_req != req
                            ||
                            g_b57_base_lba != base_lba
                            ||
                            (
                                g_b57_last_remaining != 0u
                                &&
                                remaining > g_b57_last_remaining
                            )
                        );

                    if (new_request)
                    {
                        g_b57_req = req;
                        g_b57_base_lba = base_lba;
                        g_b57_next_lba = base_lba;
                        g_b57_read_index = 0u;
                        ++g_b57_resets;
                    }

                    uint32_t lba =
                        g_b57_next_lba;

                    ++g_b32_getsec_calls;
                    ++g_b56_stream_reads;

                    if (g_b56_stream_reads == 1u)
                    {
                        g_b56_stream_first_lba = lba;
                    }

                    g_b56_stream_last_lba = lba;

                    g_b32_last_req = req;
                    g_b32_last_lba = lba;
                    g_b32_last_dst = destination;
                    g_b32_last_bytes = bytes;
                    g_b32_last_remaining = remaining;

                    int rc = -1;

                    if (
                        bytes != 0u
                        && destination >= 0x80000000u
                        && destination < 0x80200000u
                    )
                    {
                        rc = fm_disc_read_sector(
                            lba,
                            g_cd_sector
                        );
                    }

                    g_b32_last_rc = (uint32_t)rc;

                    if (rc == 0)
                    {
                        for (
                            uint32_t i = 0;
                            i < bytes;
                            ++i
                        )
                        {
                            cpu->write_byte(
                                destination + i,
                                g_cd_sector[i]
                            );
                        }

                        {
                            FMB41CdTrace *ct =
                                &g_b41_cd[g_b41_cd_head % B41_CD_RING];

                            ct->serial = g_b32_getsec_calls;
                            ct->lba = lba;
                            ct->dst = destination;
                            ct->bytes = bytes;

                            g_b41_cd_head =
                                (g_b41_cd_head + 1u)
                                % B41_CD_RING;

                            if (g_b41_cd_count < B41_CD_RING)
                            {
                                ++g_b41_cd_count;
                            }
                        }

                        ++g_b32_getsec_ok;
                        ++g_cd_sector_count;
                        g_cd_error = 0;

                        /*
                         * Une CdlDataReady consomme exactement le secteur
                         * courant. Avancer le curseur de CETTE requete.
                         */
                        ++g_b57_next_lba;
                        ++g_b57_read_index;

                        /*
                         * Garder g_cd_lba coherent pour CdlGetlocL et les
                         * autres HLE qui consultent la tete CD courante.
                         */
                        g_cd_lba = g_b57_next_lba;

                        /*
                         * FUN_8007E968 renvoie 1 lorsque le transfert DMA
                         * s'est termine correctement.
                         */
                        cpu->gpr[2] = 1u;
                    }
                    else
                    {
                        ++g_b32_getsec_fail;
                        g_cd_error = rc;

                        cpu->gpr[2] = 0u;
                    }

                    g_b57_last_remaining =
                        remaining;

                    cpu->pc = cpu->gpr[31];
                    cpu->gpr[0] = 0u;

                    static_miss = 0;
                    continue;
                }


                /*
                 * ============================================
                 * B25 - GPU LoadImage HLE
                 *
                 * FUN_80082380(RECT *rect, uint16_t *pixels)
                 *
                 * C'est le point commun utilise par le streaming du jeu
                 * pour envoyer palettes, textures et blocs d'image vers
                 * la VRAM PS1. On effectue le meme transfert via GP0 A0h
                 * puis on retourne immediatement comme la routine native
                 * apres DMA termine.
                 * ============================================
                 */
                if (phys == 0x00082380u)
                {
                    if (fm_hle_gpu_load_image(cpu))
                    {
                        cpu->gpr[2] = 0u;
                        cpu->pc = cpu->gpr[31];
                        cpu->gpr[0] = 0u;
                        static_miss = 0;
                        continue;
                    }
                }


                /*
                 * ============================================
                 * B25 - Background loader PAL HLE
                 *
                 * FUN_8002E11C (SLES_039.48 FR)
                 *
                 * Le code original calcule :
                 *   sector = 0x29E8 + group_offset + ordinal * size
                 * puis demarre FUN_80014E08() en asynchrone.
                 *
                 * Notre CD bas niveau n'achemine pas encore ce flux
                 * completement. On lit donc le meme bloc depuis disc.bin,
                 * on le decode avec le format natif WA_MRG valide en B23,
                 * puis on retourne synchronement. Ainsi, c'est bien
                 * l'index demande par le runtime qui choisit le decor.
                 * ============================================
                 */
                if (phys == 0x0002E11Cu)
                {
                    uint32_t object = cpu->gpr[4];
                    uint32_t raw_index = cpu->gpr[5] & 0xFFFFu;
                    uint32_t resolved =
                        fm_bg_resolve_runtime_index(cpu, raw_index);

                    ++g_bg_hle_calls;
                    g_bg_hle_raw = raw_index;
                    g_bg_hle_resolved = resolved;
                    g_bg_hle_object = object;

                    /* La routine native memorise l'index final en +0x3C. */
                    if (object != 0u)
                    {
                        cpu->write_half(
                            object + 0x3Cu,
                            (uint16_t)resolved
                        );
                    }

                    if (
                        fm_bg_load_game_index(
                            cpu,
                            preview,
                            resolved
                        )
                    )
                    {
                        ++g_bg_hle_ok;
                    }
                    else
                    {
                        ++g_bg_hle_fail;
                    }

                    /* Completion synchrone : ne pas poser le busy flag
                       0x10 de DAT_8009C460. L'attente 80013700 verra le
                       chargeur idle et le state machine peut continuer. */
                    cpu->pc = cpu->gpr[31];
                    cpu->gpr[0] = 0u;
                    static_miss = 0;
                    continue;
                }


                /*
                 * ============================================
                 * LibCD initialization HLE
                 *
                 * FUN_8007B53C
                 *
                 * Le code original initialise le contrôleur CD,
                 * ses callbacks et la couche IRQ Psy-Q.
                 *
                 * Notre backend CD est HLE : on expose donc
                 * directement l'état final attendu.
                 * ============================================
                 */
                if (phys == 0x0007B53Cu)
                {
                    /*
                     * DAT_80094CB0 = CD subsystem initialized.
                     */
                    cpu->write_word(
                        0x80094CB0u,
                        1
                    );


                    /*
                     * DAT_80094930 = CD interrupt layer ready.
                     */
                    cpu->write_word(
                        0x80094930u,
                        1
                    );


                    /*
                     * Callbacks internes Psy-Q.
                     */
                    cpu->write_word(
                        0x80094910u,
                        0x8007CA78u
                    );


                    cpu->write_word(
                        0x80094914u,
                        0x8007D0E0u
                    );


                    /*
                     * Callbacks utilisateur initialement NULL.
                     */
                    cpu->write_word(
                        0x800F7308u,
                        0
                    );


                    cpu->write_word(
                        0x800F730Cu,
                        0
                    );


                    cpu->write_word(
                        0x800F7310u,
                        0
                    );


                    /*
                     * Retour succès.
                     */
                    cpu->gpr[2] = 1;

                    cpu->pc =
                        cpu->gpr[31];

                    cpu->gpr[0] = 0;

                    static_miss = 0;

                    continue;
                }


                /*
                 * ============================================
                 * DsSearchFile HLE
                 *
                 * FUN_8007D988
                 *
                 * Cherche un chemin dans l'ISO9660 puis remplit
                 * le CdlFILE de sortie.
                 * ============================================
                 */
                if (phys == 0x0007D988u)
                {
                    uint32_t output =
                        cpu->gpr[4];

                    uint32_t guest_path =
                        cpu->gpr[5];

                    char path[256];

                    unsigned i = 0;


                    while (
                        i < sizeof(path) - 1
                    )
                    {
                        uint8_t c =
                            cpu->read_byte(
                                guest_path + i
                            );

                        path[i] =
                            (char)c;

                        ++i;

                        if (c == 0)
                        {
                            break;
                        }
                    }


                    path[
                        sizeof(path) - 1
                    ] =
                        '\0';


                    strncpy(
                        g_cd_search_path,
                        path,
                        sizeof(g_cd_search_path) - 1
                    );

                    g_cd_search_path[
                        sizeof(g_cd_search_path) - 1
                    ] =
                        '\0';


                    uint32_t file_lba = 0;
                    uint32_t file_size = 0;


                    g_cd_search_ok =
                        fm_disc_find_file(
                            path,
                            &file_lba,
                            &file_size
                        );


                    g_cd_search_lba =
                        file_lba;

                    g_cd_search_size =
                        file_size;


                    if (
                        g_cd_search_ok
                        &&
                        output != 0
                    )
                    {
                        /*
                         * CdlLOC attendu en MSF BCD.
                         */
                        uint32_t absolute =
                            file_lba
                            +
                            150u;

                        uint32_t minute =
                            absolute
                            /
                            (60u * 75u);

                        uint32_t second =
                            (
                                absolute
                                /
                                75u
                            )
                            %
                            60u;

                        uint32_t sector =
                            absolute
                            %
                            75u;


                        uint8_t minute_bcd =
                            (uint8_t)(
                                ((minute / 10u) << 4)
                                |
                                (minute % 10u)
                            );

                        uint8_t second_bcd =
                            (uint8_t)(
                                ((second / 10u) << 4)
                                |
                                (second % 10u)
                            );

                        uint8_t sector_bcd =
                            (uint8_t)(
                                ((sector / 10u) << 4)
                                |
                                (sector % 10u)
                            );


                        /*
                         * CdlFILE minimal :
                         *
                         * +0  CdlLOC
                         * +4  taille
                         * +8  nom[16]
                         */
                        cpu->write_byte(
                            output + 0,
                            minute_bcd
                        );

                        cpu->write_byte(
                            output + 1,
                            second_bcd
                        );

                        cpu->write_byte(
                            output + 2,
                            sector_bcd
                        );

                        cpu->write_byte(
                            output + 3,
                            0
                        );


                        cpu->write_word(
                            output + 4,
                            file_size
                        );


                        for (
                            unsigned n = 0;
                            n < 16;
                            ++n
                        )
                        {
                            cpu->write_byte(
                                output + 8 + n,
                                0
                            );
                        }


                        /*
                         * DsSearchFile retourne un pointeur non NULL.
                         */
                        cpu->gpr[2] =
                            output;
                    }
                    else
                    {
                        cpu->gpr[2] =
                            0;
                    }


                    cpu->pc =
                        cpu->gpr[31];

                    cpu->gpr[0] =
                        0;

                    static_miss =
                        0;

                    continue;
                }


                /*
                 * ============================================
                 * LibCD command HLE
                 *
                 * FUN_8007A1D4
                 * ============================================
                 */
                if (phys == 0x0007A1D4u)
                {
                    uint32_t command =
                        cpu->gpr[4]
                        &
                        0xFFu;

                    uint32_t params =
                        cpu->gpr[5];

                    uint32_t result =
                        cpu->gpr[6];

                    g_cd_last_cmd =
                        command;


                    /*
                     * CdlSetloc = 02
                     */
                    if (
                        command == 0x02u
                        && params != 0
                    )
                    {
                        uint32_t minute =
                            fm_bcd_to_u32(
                                cpu->read_byte(
                                    params + 0
                                )
                            );

                        uint32_t second =
                            fm_bcd_to_u32(
                                cpu->read_byte(
                                    params + 1
                                )
                            );

                        uint32_t frame_cd =
                            fm_bcd_to_u32(
                                cpu->read_byte(
                                    params + 2
                                )
                            );

                        uint32_t absolute_sector =
                            (
                                (
                                    minute * 60u
                                    + second
                                )
                                * 75u
                            )
                            + frame_cd;

                        if (absolute_sector >= 150u)
                        {
                            g_cd_lba =
                                absolute_sector - 150u;
                        }
                        else
                        {
                            g_cd_lba = 0;
                        }

                        g_cd_pos = 2048;
                    }


                    /*
                     * CdlReadN = 06
                     */
                    if (command == 0x06u)
                    {
                        g_cd_reading = 1;
                        g_cd_pos = 2048;
                        g_cd_error = 0;
                    }


                    /*
                     * CdlPause = 09
                     */
                    if (command == 0x09u)
                    {
                        g_cd_reading = 0;
                    }


                    /*
                     * Commandes temporairement traitées en HLE.
                     */
                    if (
                        command == 0x01u
                        || command == 0x02u
                        || command == 0x06u
                        || command == 0x09u
                        || command == 0x0Au
                        || command == 0x0Cu
                        || command == 0x0Eu
                        || command == 0x15u
                        || command == 0x16u
                    )
                    {
                        if (result != 0)
                        {
                            cpu->write_byte(
                                result + 0,
                                0x02
                            );

                            for (
                                unsigned i = 1;
                                i < 8;
                                ++i
                            )
                            {
                                cpu->write_byte(
                                    result + i,
                                    0
                                );
                            }
                        }

                        /*
                         * Etat interne Psy-Q LibCD :
                         * Sync = Complete.
                         */
                        cpu->write_byte(
                            0x80094BECu,
                            2
                        );

                        cpu->write_byte(
                            0x80094BEDu,
                            0
                        );

                        cpu->write_byte(
                            0x80094BEEu,
                            0
                        );

                        cpu->write_byte(
                            0x8009491Cu,
                            0x02
                        );

                        cpu->gpr[2] = 0;
                        cpu->pc = cpu->gpr[31];
                        cpu->gpr[0] = 0;

                        static_miss = 0;
                        continue;
                    }
                }


                /*
                 * ============================================
                 * DMA3 CD-ROM HLE
                 *
                 * FUN_80079580
                 * ============================================
                 */
                if (
                    phys == 0x00079580u
                    && cpu->gpr[4] == 3u
                    && g_cd_reading
                )
                {
                    uint32_t destination =
                        cpu->gpr[5];

                    uint32_t words =
                        cpu->gpr[7];

                    uint32_t bytes =
                        words * 4u;

                    /*
                     * Protection bring-up.
                     * Les transferts vus ici doivent rester
                     * dans un secteur de 2048 octets.
                     */
                    if (bytes > 2048u)
                    {
                        bytes = 2048u;
                    }

                    for (
                        uint32_t i = 0;
                        i < bytes;
                        ++i
                    )
                    {
                        if (g_cd_pos >= 2048u)
                        {
                            int rc =
                                fm_disc_read_sector(
                                    g_cd_lba,
                                    g_cd_sector
                                );

                            if (rc != 0)
                            {
                                g_cd_error = rc;

                                memset(
                                    g_cd_sector,
                                    0,
                                    sizeof(g_cd_sector)
                                );
                            }
                            else
                            {
                                g_cd_error = 0;
                                ++g_cd_sector_count;
                            }

                            g_cd_pos = 0;
                        }

                        cpu->write_byte(
                            destination + i,
                            g_cd_sector[g_cd_pos]
                        );

                        ++g_cd_pos;

                        if (g_cd_pos >= 2048u)
                        {
                            ++g_cd_lba;
                        }
                    }

                    /*
                     * FUN_80079580 est void.
                     */
                    cpu->pc =
                        cpu->gpr[31];

                    cpu->gpr[0] = 0;
                    static_miss = 0;

                    continue;
                }


                /*
                 * ============================================
                 * B19 - GsSortOt natif borne + direct OT
                 * ============================================
                 *
                 * 1) Essayer le VRAI FUN_80085D98 dans un CPU temporaire.
                 *    S'il revient, ses modifications RAM sont conservees.
                 *
                 * 2) S'il boucle sur une OT corrompue, ne rien splicer a la
                 *    main. On rend la main au jeu comme B17 et on soumet
                 *    directement l'OT source au GPU avec un walker borne.
                 *    Les primitives peuvent etre mal ordonnees, mais ce
                 *    chemin maximise nos chances d'obtenir les premiers
                 *    vrais pixels sans fabriquer d'image.
                 */
                if (phys == 0x00085D98u)
                {
                    uint32_t src_ot = cpu->gpr[4];
                    uint32_t dst_ot = cpu->gpr[5];
                    uint32_t native_result = dst_ot;

                    ++g_hle_85d98_calls;
                    g_hle_85d98_last_src = src_ot;
                    g_hle_85d98_last_dst = dst_ot;

                    if (src_ot != 0u)
                    {
                        g_hle_85d98_src_length = cpu->read_word(src_ot + 0u);
                        g_hle_85d98_src_org    = cpu->read_word(src_ot + 4u);
                        g_hle_85d98_src_offset = cpu->read_word(src_ot + 8u);
                        g_hle_85d98_src_point  = cpu->read_word(src_ot + 12u);
                        g_hle_85d98_src_tag    = cpu->read_word(src_ot + 16u);
                    }

                    if (dst_ot != 0u)
                    {
                        g_hle_85d98_dst_length = cpu->read_word(dst_ot + 0u);
                        g_hle_85d98_dst_org    = cpu->read_word(dst_ot + 4u);
                        g_hle_85d98_dst_offset = cpu->read_word(dst_ot + 8u);
                        g_hle_85d98_dst_point  = cpu->read_word(dst_ot + 12u);
                        g_hle_85d98_dst_tag    = cpu->read_word(dst_ot + 16u);
                    }

                    /*
                     * B20 : avant tout traitement, remettre seulement la
                     * sentinelle de fin des deux OTs. La trace B19 montrait
                     * une chaine de buckets vides qui descendait bien au-dela
                     * de src->org, ce qui explique les boucles de GsSortOt.
                     */
                    /*
                     * B130 PERF CLEAN:
                     * keep the corrected OT repair and verified C GsSortOt,
                     * but do not time every phase.
                     */
                    fm_repair_ot_sentinel(cpu, src_ot);
                    fm_repair_ot_sentinel(cpu, dst_ot);

                    int b115_native_ok =
                        fm_try_c_gssortot(
                            cpu,
                            src_ot,
                            dst_ot,
                            &native_result
                        );

                    if (!b115_native_ok)
                    {
                        b115_native_ok =
                            fm_try_native_gssortot(
                                cpu,
                                src_ot,
                                dst_ot,
                                &native_result
                            );
                    }

                    if (b115_native_ok)
                    {
                        cpu->gpr[2] = native_result;
                    }
                    else
                    {
                        /*
                         * Same B114 fallback: source OT was already submitted
                         * safely, then the guest continues without manual splice.
                         */
                        cpu->gpr[2] = dst_ot;
                    }

                    cpu->pc = cpu->gpr[31];
                    cpu->gpr[0] = 0u;

                    static_miss = 0;
                    continue;
                }

                /*
                 * ============================================
                 * B91 - SU OVERLAY FAST PATH
                 * ============================================
                 *
                 * Les overlays charges en 0x801xxxxx ne font pas
                 * partie du gros objet ARM resident. Eviter le probe
                 * natif rate pour chaque basic block et enchainer
                 * directement plusieurs blocks MIPS.
                 *
                 * Des que le PC ressort de 0x801xxxxx (appel d'une
                 * fonction residente, BIOS, etc.), on revient au
                 * dispatcher normal afin de reutiliser le code ARM/HLE.
                 */
                if (
                    phys >= 0x00100000u
                    &&
                    phys < 0x00200000u
                )
                {
                    const uint32_t b91_block_limit = 512u;
                    uint32_t b91_blocks = 0u;
                    int b91_time_yield = 0;

                    ++g_b91_fast_entries;
                    g_b91_last_entry_pc = dispatch_address;

                    while (
                        game_running
                        &&
                        b91_blocks < b91_block_limit
                    )
                    {
                        uint32_t fast_phys =
                            cpu->pc & 0x1FFFFFFFu;

                        if (
                            fast_phys < 0x00100000u
                            ||
                            fast_phys >= 0x00200000u
                        )
                        {
                            ++g_b91_fast_exits_resident;
                            break;
                        }

                        /*
                         * Meme budget global de 14 ms que B87, mais
                         * verifie entre basic blocks de l'overlay.
                         */
                        /*
                         * B111 - le test temporel par basic block etait
                         * inutilement couteux dans le fast path. Les
                         * blocks overlay sont courts; en release on ne
                         * relit l'horloge qu'une fois tous les 16 blocks.
                         * Les builds de diagnostic gardent la mesure fine.
                         */
#if defined(NDEBUG)
                        if (
                            b91_blocks != 0u
                            &&
                            (b91_blocks & 15u) == 0u
                            &&
                            (osGetTime() - b16_slice_start_ms) >= g_b105_slice_budget_ms
                        )
                        {
                            ++g_b91_fast_time_yields;
                            b91_time_yield = 1;
                            break;
                        }

                        interp =
                            fm_interp_run_block(
                                cpu,
                                8192u
                            );

                        g_b91_last_block_ms = 0u;
#else
                        if (
                            b91_blocks != 0u
                            &&
                            (osGetTime() - b16_slice_start_ms) >= g_b105_slice_budget_ms
                        )
                        {
                            ++g_b91_fast_time_yields;
                            b91_time_yield = 1;
                            break;
                        }

                        uint64_t b91_block_start_ms = osGetTime();

                        interp =
                            fm_interp_run_block(
                                cpu,
                                8192u
                            );

                        uint32_t b91_block_ms =
                            (uint32_t)(
                                osGetTime() - b91_block_start_ms
                            );

                        g_b91_last_block_ms = b91_block_ms;
                        if (b91_block_ms > g_b91_max_block_ms)
                        {
                            g_b91_max_block_ms = b91_block_ms;
                        }
#endif

                        interp_ran = 1;
                        ++b91_blocks;
                        ++g_b91_fast_blocks;
                        g_b91_fast_instructions +=
                            (uint64_t)interp.instructions;

                        if (
                            interp.reason == FM_INTERP_BLOCK_DONE
                        )
                        {
                            static_miss = 0;
                            continue;
                        }

                        if (
                            interp.reason == FM_INTERP_BUDGET
                        )
                        {
                            static_miss = 0;
                            ++g_b84_budget_continues;
                            continue;
                        }

                        /* Meme politique d'erreur que le fallback B84. */
                        g_b65_stop_code = 4u;
                        g_b65_stop_pc = interp.pc;
                        g_b65_stop_ra = cpu->gpr[31];
                        g_b65_stop_detail = interp.instruction;

                        static_miss = 0;
                        game_running = 0;
                        break;
                    }

                    g_b91_last_exit_pc = cpu->pc;

                    if (
                        b91_blocks >= b91_block_limit
                        &&
                        (cpu->pc & 0x1FFFFFFFu) >= 0x00100000u
                        &&
                        (cpu->pc & 0x1FFFFFFFu) < 0x00200000u
                    )
                    {
                        ++g_b91_fast_block_cap;
                    }

#if !defined(NDEBUG)
                    {
                        uint32_t b91_handoff_ms =
                            (uint32_t)(osGetTime() - b91_handoff_start_ms);

                        if (b91_handoff_ms > g_b91_slow_handoff_ms)
                        {
                            g_b91_slow_handoff_ms = b91_handoff_ms;
                            g_b91_slow_handoff_pc = dispatch_address;
                        }
                    }
#endif

                    if (!game_running)
                    {
                        break;
                    }

                    if (b91_time_yield)
                    {
                        ++g_b16_slice_yields;
                        ++g_b84_budget_yields;
                        break;
                    }

                    continue;
                }


                /*
                 * ============================================
                 * B93 - 800917F8 natif
                 * ============================================
                 *
                 * B92 descendait le scheduler moyen, mais le profil
                 * montrait encore ~79 ms dans cette routine precise.
                 * Elle est maintenant remplacee par sa traduction C
                 * directe sur la RAM PS1.
                 */
                if (phys == 0x000917F8u)
                {
                    uint64_t b93_start_ms =
                        osGetTime();

                    uint32_t b93_out = 0u;

                    if (
                        fm_b93_hle_800917f8(
                            cpu,
                            ram,
                            2u * 1024u * 1024u,
                            &b93_out
                        )
                    )
                    {
                        uint32_t elapsed =
                            (uint32_t)(
                                osGetTime()
                                -
                                b93_start_ms
                            );

                        ++g_b93_917f8_hle_calls;
                        g_b93_917f8_last_ms = elapsed;
                        g_b93_917f8_last_out = b93_out;

                        if (elapsed > g_b93_917f8_max_ms)
                        {
                            g_b93_917f8_max_ms = elapsed;
                        }

                        static_miss = 0;
                        continue;
                    }

                    ++g_b93_917f8_fallbacks;
                }


                /*
                 * ============================================
                 * ARM recompiled code
                 * ============================================
                 */
                /*
                 * B111 - release hot path.
                 *
                 * B110 etait encore actif meme avec -DNDEBUG : chaque
                 * passage natif lisait le timer deux fois et mettait a
                 * jour le classement du profiler. Sur un dispatcher qui
                 * peut faire des milliers de handoffs, le diagnostic
                 * devenait lui-meme une charge permanente.
                 *
                 * En release on execute donc directement le probe.
                 * Le profiler complet reste disponible dans un build
                 * sans NDEBUG.
                 */
                uint32_t b13514_chain_count = 0u;
                int b13514_chain_region =
                    (
                        phys >= 0x000342B0u
                        &&
                        phys < 0x00035AC8u
                    )
                    ||
                    (
                        phys >= 0x0004D260u
                        &&
                        phys < 0x0004D5B8u
                    )
                    ||
                    (
                        phys >= 0x00089D60u
                        &&
                        phys < 0x0008A204u
                    )
                    ||
                    (
                        phys >= 0x0005721Cu
                        &&
                        phys < 0x00058860u
                    );

#if defined(NDEBUG)
                if (b13514_chain_region)
                {
                    probe =
                        fm_runtime_probe_chain(
                            cpu,
                            dispatch_address,
                            g_b105_probe_budget,
                            0x000342B0u,
                            0x00035AC8u,
                            0x0004D260u,
                            0x0004D5B8u,
                            0x00089D60u,
                            0x0008A204u,
                            0x0005721Cu,
                            0x00058860u,
                            /*
                             * B135.24 - B135.23 reached chains as deep as
                             * 123 dispatches and a single host slice grew to
                             * ~39 ms.  Bound the native chain so main.c gets
                             * frequent chances to enforce the 12 ms scheduler
                             * budget while still amortizing setjmp/dispatcher
                             * overhead versus the old max=4 behavior.
                             */
                            16u,
                            &b13514_chain_count
                        );
                }
                else
                {
                    probe =
                        fm_runtime_probe(
                            cpu,
                            dispatch_address,
                            g_b105_probe_budget
                        );
                }
#else
                {
                    uint64_t b110_probe_start_tick =
                        svcGetSystemTick();

                    if (b13514_chain_region)
                    {
                        probe =
                            fm_runtime_probe_chain(
                                cpu,
                                dispatch_address,
                                g_b105_probe_budget,
                                0x000342B0u,
                                0x00035AC8u,
                                0x0004D260u,
                                0x0004D5B8u,
                                0x00089D60u,
                                0x0008A204u,
                                0x0005721Cu,
                                0x00058860u,
                                16u,
                                &b13514_chain_count
                            );
                    }
                    else
                    {
                        probe =
                            fm_runtime_probe(
                                cpu,
                                dispatch_address,
                                g_b105_probe_budget
                            );
                    }

                    uint64_t b110_probe_ticks =
                        svcGetSystemTick()
                        -
                        b110_probe_start_tick;

                    uint32_t b110_probe_us =
                        (uint32_t)(
                            b110_probe_ticks
                            /
                            (SYSCLOCK_ARM11 / 1000000u)
                        );

                    b110_profile_probe(
                        dispatch_address,
                        probe.pc,
                        b110_probe_us
                    );
                }
#endif

                if (b13514_chain_count != 0u)
                {
                    ++g_b13514_chain_entries;
                    g_b13514_chain_dispatches +=
                        b13514_chain_count;

                    if (b13514_chain_count > g_b13514_chain_max)
                    {
                        g_b13514_chain_max =
                            b13514_chain_count;
                    }

                    if (
                        probe.reason == FM_STOP_RETURNED
                        &&
                        probe.pc != 0u
                    )
                    {
                        b13516_note_chain_exit(
                            probe.pc
                        );
                    }
                }

                probe_ran = 1;

#if !defined(NDEBUG)
                {
                    uint32_t b91_handoff_ms =
                        (uint32_t)(osGetTime() - b91_handoff_start_ms);

                    if (b91_handoff_ms > g_b91_slow_handoff_ms)
                    {
                        g_b91_slow_handoff_ms = b91_handoff_ms;
                        g_b91_slow_handoff_pc = dispatch_address;
                    }
                }
#endif


                /*
                 * Time slice.
                 */
                if (
                    probe.reason
                    == FM_STOP_BUDGET
                )
                {
                    /*
                     * B85 : psx_check_interrupts_at() a deja place
                     * cpu->pc sur le resume_pc exact avant le longjmp.
                     * On peut donc reprendre immediatement dans la meme
                     * tranche host au lieu de perdre une frame 3DS.
                     */
                    static_miss = 0;
                    ++g_b85_probe_budget_continues;
                    continue;
                }


                /*
                 * Normal dispatcher return.
                 */
                if (
                    probe.reason
                    == FM_STOP_RETURNED
                )
                {
                    /*
                     * Static ARM code found.
                     */
                    if (
                        probe.dispatch_result
                        == 1
                    )
                    {
                        if (
                            cpu->pc == 0
                            && cpu->gpr[31] != 0
                        )
                        {
                            cpu->pc =
                                cpu->gpr[31];
                        }

                        if (cpu->pc == 0)
                        {
                            g_b65_stop_code = 3u;
                            g_b65_stop_pc = 0u;
                            g_b65_stop_ra = cpu->gpr[31];
                            g_b65_stop_detail = probe.pc;

                            game_running = 0;
                            static_miss = 0;
                            break;
                        }

                        static_miss = 0;
                        continue;
                    }


                    /*
                     * ========================================
                     * R3000A fallback
                     * ========================================
                     */
                    /*
                     * B84 : les overlays dynamiques 0x801xxxxx passent
                     * par cet interpreteur. 128 instructions/frame etait
                     * la principale cause du ralenti massif.
                     */
                    /*
                     * B135.17:
                     * The hot map PCs reported by B135.16 are internal
                     * labels unknown to psx_dispatch_game_compiled(). Run
                     * consecutive R3000A basic blocks here instead of
                     * bouncing through main.c hundreds of times per slice.
                     */
                    if (b13517_is_map_interp_pc(cpu->pc))
                    {
                        uint32_t b13519_chunks = 0u;
                        int b13517_time_yield = 0;
                        uint32_t b13525_entry_pc =
                            cpu->pc & 0x1FFFFFFFu;
                        uint64_t b13525_entry_instructions = 0u;

                        ++g_b13517_interp_entries;

                        /*
                         * B135.19:
                         * Execute across internal MIPS branch boundaries inside
                         * fm_interp.c. A 256-instruction chunk amortizes the
                         * block-return/dispatcher overhead while still letting
                         * main.c enforce the 12 ms host slice accurately.
                         */
                        while (
                            game_running
                            &&
                            b13517_is_map_interp_pc(cpu->pc)
                            &&
                            b13519_chunks < 256u
                        )
                        {
                            interp =
                                fm_interp_run_region(
                                    cpu,
                                    256u,
                                    0x000342B0u,
                                    0x00035AC8u,
                                    0x00034D30u
                                );

                            interp_ran = 1;
                            ++b13519_chunks;
                            ++g_b13517_interp_blocks;
                            g_b13519_region_instructions +=
                                interp.instructions;
                            b13525_entry_instructions +=
                                interp.instructions;

                            if (
                                interp.reason
                                ==
                                FM_INTERP_BUDGET
                            )
                            {
                                ++g_b84_budget_continues;

                                if (
                                    (osGetTime() - b16_slice_start_ms)
                                        >= g_b105_slice_budget_ms
                                )
                                {
                                    b13517_time_yield = 1;
                                    ++g_b13517_interp_time_yields;
                                    break;
                                }

                                continue;
                            }

                            /*
                             * BLOCK_DONE now means the chained interpreter
                             * deliberately reached a PC outside the region or
                             * the native 0x34D30 entry. Give it back to the
                             * normal dispatcher immediately.
                             */
                            break;
                        }

                        if (b13519_chunks > g_b13517_interp_max)
                        {
                            g_b13517_interp_max = b13519_chunks;
                        }

                        b13525_note_interp_entry(
                            b13525_entry_pc,
                            b13525_entry_instructions
                        );

                        if (b13517_time_yield)
                        {
                            static_miss = 0;
                            ++g_b84_budget_yields;
                            break;
                        }

                        if (
                            interp.reason == FM_INTERP_BLOCK_DONE
                            ||
                            interp.reason == FM_INTERP_BUDGET
                        )
                        {
                            static_miss = 0;
                            continue;
                        }
                    }
                    else
                    {
                        interp =
                            fm_interp_run_block(
                                cpu,
                                8192u
                            );

                        interp_ran = 1;

                        if (
                            interp.reason
                            == FM_INTERP_BLOCK_DONE
                        )
                        {
                            static_miss = 0;
                            continue;
                        }

                        if (
                            interp.reason
                            == FM_INTERP_BUDGET
                        )
                        {
                            /*
                             * B84 : le PC de l'interpreteur est deja avance.
                             * Reprendre une nouvelle tranche au lieu d'attendre
                             * obligatoirement la frame 3DS suivante.
                             */
                            static_miss = 0;
                            ++g_b84_budget_continues;
                            continue;
                        }
                    }

                    /*
                     * Instruction actuellement non supportée.
                     */
                    g_b65_stop_code = 4u;
                    g_b65_stop_pc = interp.pc;
                    g_b65_stop_ra = cpu->gpr[31];
                    g_b65_stop_detail = interp.instruction;

                    static_miss = 0;
                    game_running = 0;
                    break;
                }


                /*
                 * Native runtime stop.
                 */
                g_b65_stop_code = 5u;
                g_b65_stop_pc = probe.pc;
                g_b65_stop_ra = cpu ? cpu->gpr[31] : 0u;
                /*
                 * B135 : conserver le DETAIL reel (commande GTE, syscall,
                 * etc.) plutot que seulement l'enum du motif.
                 */
                g_b65_stop_detail = probe.detail;

                game_running = 0;
                break;
            }

            /*
             * B86 : mesurer aussi le boot PRE-DIRECT-2DF.
             * B85 affichait artificiellement 0 ms / 0 handoff avant
             * l'activation de DIRECT-2DF, ce qui masquait le vrai cout.
             */
            {
                uint32_t elapsed_ms =
                    (uint32_t)(osGetTime() - b16_slice_start_ms);

                g_b16_slice_last_ms = elapsed_ms;
                g_b16_last_handoffs = b16_handoff_count;

                if (elapsed_ms > g_b16_slice_max_ms)
                {
                    g_b16_slice_max_ms = elapsed_ms;
                }
            }
        }


        /*
         * ====================================================
         * B22 WA_MRG background controls
         * ====================================================
         * X/Y : background suivant / precedent dans le groupe
         * R/L : groupe 0/1/2 suivant / precedent
         * A   : runtime PS1 run/pause (inchange)
         */
        if ((down & KEY_X) && cpu)
        {
            fm_bg_change(cpu, preview, +1, 0);
        }

        if ((down & KEY_Y) && cpu)
        {
            fm_bg_change(cpu, preview, -1, 0);
        }

        if ((down & KEY_R) && cpu)
        {
            fm_bg_change(cpu, preview, 0, +1);
        }

        if ((down & KEY_L) && cpu)
        {
            fm_bg_change(cpu, preview, 0, -1);
        }

        /*
         * ====================================================
         * B42 - ZL : bascule NATIF / ancien mode diagnostic
         * ====================================================
         *
         * NATIF  : aucun WA_MRG force, clears du jeu autorises.
         * LEGACY : comportement B28/B41 pour comparaison.
         */
        if (down & KEY_ZL)
        {
            g_b42_native_video = !g_b42_native_video;

            fm_gpu_b42_set_preserve_background_clears(
                g_b42_native_video ? 0 : 1
            );

            if (!g_b42_native_video && g_bg.loaded)
            {
                g_bg_vram_pending = 1u;
            }
        }

        /*
         * ====================================================
         * B26 - push du vrai background dans la VRAM PS1
         * ====================================================
         */
        if (
            !g_b42_native_video
            && g_bg_vram_pending
            && g_bg.loaded
        )
        {
            fm_bg_upload_preview_to_vram(preview);
            g_bg_vram_pending = 0u;
        }

        /*
         * ====================================================
         * TOP SCREEN
         * ====================================================
         */

        uint64_t render_start =
            svcGetSystemTick();

        uint64_t b105_render_start_ms =
            osGetTime();

        /*
         * B15 FIRST IMAGE :
         * scanner periodiquement plusieurs pages VRAM et afficher la
         * fenetre 320x240 contenant le plus de pixels non nuls.
         *
         * Cela ne cree aucun pixel : c'est uniquement une vue de la VRAM
         * produite par Forbidden Memories. Des que le jeu place une
         * image, un framebuffer ou meme un atlas de textures quelque part
         * dans la VRAM, on doit pouvoir le voir.
         */
        if (!g_b42_native_video && (frame % 120u) == 0u)
        {
            static const unsigned xs[] = { 0u, 320u, 640u };
            static const unsigned ys[] = { 0u, 256u };

            uint32_t best_nz = 0u;
            unsigned best_x = fm_gpu_display_x();
            unsigned best_y = fm_gpu_display_y();

            if (best_x > 704u)
                best_x = 0u;
            if (best_y > 272u)
                best_y = 0u;

            for (unsigned yi = 0; yi < 2u; ++yi)
            {
                for (unsigned xi = 0; xi < 3u; ++xi)
                {
                    unsigned vx = xs[xi];
                    unsigned vy = ys[yi];
                    uint32_t nz = 0u;

                    /*
                     * Echantillonnage 1 pixel sur 2 pour limiter le cout.
                     */
                    for (unsigned py = 0; py < 240u; py += 2u)
                    {
                        const uint16_t *row =
                            vram
                            + (vy + py) * 1024u
                            + vx;

                        for (unsigned px = 0; px < 320u; px += 2u)
                        {
                            if (row[px] != 0u)
                            {
                                ++nz;
                            }
                        }
                    }

                    if (nz > best_nz)
                    {
                        best_nz = nz;
                        best_x = vx;
                        best_y = vy;
                    }
                }
            }

            g_vram_view_x = best_x;
            g_vram_view_y = best_y;
            g_vram_view_nonzero = best_nz;
        }

        /*
         * ====================================================
         * B84 - framebuffer stable
         * ====================================================
         *
         * B78/B79 ont deja un compteur de transactions DMA2. Une
         * nouvelle transaction est un bien meilleur point de capture
         * qu'une frame 3DS arbitraire : on evite de montrer une VRAM
         * en plein milieu de la construction d'image.
         */
        /*
         * ====================================================
         * B87 - double-buffer PS1 avec une image de retard
         * ====================================================
         *
         * PRE-DIRECT :
         *   quand GP1(05) change de page, on capture l'ANCIENNE
         *   page. Elle vient de rester affichee pendant toute une
         *   frame et doit donc etre stable.
         *
         * DIRECT-2DF :
         *   on conserve la frontiere "frame guest terminee" de B85.
         */
        if (
            g_b42_native_video
            &&
            fm_gpu_has_frame()
        )
        {
            unsigned current_x = fm_gpu_display_x();
            unsigned current_y = fm_gpu_display_y();

            uint32_t b104_mode = fm_gpu_display_mode_raw();
            int b104_24bit = fm_gpu_display_24bit();
            uint64_t b104_gp0 = fm_gpu_gp0_count();

            if (current_x > 704u)
            {
                current_x = 0u;
            }

            if (current_y > 256u)
            {
                current_y = 0u;
            }

            unsigned previous_x = g_b86_last_display_x;
            unsigned previous_y = g_b86_last_display_y;

            int have_previous =
                previous_x != 0xFFFFFFFFu
                &&
                previous_y != 0xFFFFFFFFu;

            int display_changed =
                !have_previous
                ||
                current_x != previous_x
                ||
                current_y != previous_y;

            int complete_guest_frame =
                g_direct2df_active
                &&
                g_b85_guest_frames
                    !=
                    g_b85_last_latched_guest_frame;

            /*
             * B98 : mesurer les deux pages AU MOMENT OU main.c
             * observe un changement GP1(05). B97 a montre un cas
             * tres net : P0 presque pleine, P320 totalement vide.
             *
             * On garde aussi les hashes B97 pour le diagnostic.
             */
            uint32_t p0_nz = g_b97_p0_nonzero;
            uint32_t p320_nz = g_b97_p320_nonzero;

            if (display_changed)
            {
                p0_nz = 0u;
                p320_nz = 0u;

                uint32_t p0_hash = 2166136261u;
                uint32_t p320_hash = 2166136261u;

                for (unsigned py = 0u; py < 240u; py += 4u)
                {
                    const uint16_t *row0 = vram + py * 1024u;
                    const uint16_t *row320 = row0 + 320u;

                    for (unsigned px = 0u; px < 320u; px += 4u)
                    {
                        uint16_t a = row0[px];
                        uint16_t b = row320[px];

                        if ((a & 0x7FFFu) != 0u) ++p0_nz;
                        if ((b & 0x7FFFu) != 0u) ++p320_nz;

                        p0_hash ^= (uint32_t)a;
                        p0_hash *= 16777619u;

                        p320_hash ^= (uint32_t)b;
                        p320_hash *= 16777619u;
                    }
                }

                g_b97_p0_nonzero = p0_nz;
                g_b97_p320_nonzero = p320_nz;
                g_b97_p0_hash = p0_hash;
                g_b97_p320_hash = p320_hash;
                ++g_b97_flip_samples;
            }

            unsigned latch_x = current_x;
            unsigned latch_y = current_y;
            int need_latch = 0;

            int b103_merge = 0;
            unsigned b103_base_x = current_x;
            unsigned b103_overlay_x = current_x;

            int b104_decode24 = 0;

            /*
             * B104 : GP1(08) bit4 = affichage 24-bit.
             * Dans ce mode le framebuffer est un flux RGB888 compact
             * de 3 octets/pixel dans la VRAM, pas du BGR555.
             *
             * Refaire un latch lorsque le flux GP0 bouge, le mode change,
             * la page change, ou au premier affichage.
             */
            if (
                b104_24bit
                &&
                (
                    !g_b84_latch_valid
                    ||
                    display_changed
                    ||
                    b104_gp0 != g_b104_last_gp0
                    ||
                    b104_mode != g_b104_last_mode
                )
            )
            {
                latch_x = current_x;
                latch_y = current_y;
                need_latch = 1;
                b104_decode24 = 1;
            }
            else if (g_direct2df_active)
            {
                int b1357_vsync_boundary =
                    g_b1358_vsync_completed
                    &&
                    b104_gp0 != g_b1357_last_latched_gp0;

                /*
                 * B135.7:
                 * - VSync wait = stable end-of-frame boundary for gameplay;
                 * - GP1 page change is also inherently safe;
                 * - keep the historical sentinel path as a fallback.
                 *
                 * The GP0 comparison is against the LAST LATCH, not merely
                 * the previous host loop. A complex PS1 frame can span
                 * several 12 ms scheduler slices before it reaches VSync.
                 */
                if (
                    !g_b84_latch_valid
                    ||
                    b1357_vsync_boundary
                    ||
                    display_changed
                    ||
                    complete_guest_frame
                )
                {
                    need_latch = 1;

                    if (b1357_vsync_boundary)
                    {
                        ++g_b1357_vsync_latches;
                    }

                    if (display_changed)
                    {
                        ++g_b1357_display_latches;
                    }
                }
            }
            else if (display_changed)
            {
                uint32_t current_nz =
                    current_x == 320u
                        ? p320_nz
                        : p0_nz;

                uint32_t other_nz =
                    current_x == 320u
                        ? p0_nz
                        : p320_nz;

                /*
                 * B103 :
                 * si une page est beaucoup plus dense que l'autre,
                 * le jeu se retrouve actuellement separe en deux
                 * "couches" dans notre VRAM :
                 *
                 *   dense  = decor / fond
                 *   sparse = UI / texte / curseur
                 *
                 * On reconstruit temporairement l'image complete.
                 *
                 * Le seuil 3/4 evite le merge quand les deux pages
                 * sont de vrais framebuffers complets.
                 */
                if (
                    p0_nz >= 512u
                    &&
                    p320_nz >= 64u
                    &&
                    (
                        p0_nz * 4u < p320_nz * 3u
                        ||
                        p320_nz * 4u < p0_nz * 3u
                    )
                )
                {
                    if (p0_nz > p320_nz)
                    {
                        b103_base_x = 0u;
                        b103_overlay_x = 320u;
                        g_b103_last_base_nz = p0_nz;
                        g_b103_last_overlay_nz = p320_nz;
                    }
                    else
                    {
                        b103_base_x = 320u;
                        b103_overlay_x = 0u;
                        g_b103_last_base_nz = p320_nz;
                        g_b103_last_overlay_nz = p0_nz;
                    }

                    b103_merge = 1;
                    latch_x = b103_base_x;
                    latch_y = current_y;
                    need_latch = 1;

                    g_b103_last_base_x = b103_base_x;
                    g_b103_last_overlay_x = b103_overlay_x;
                    ++g_b103_merge_count;
                }
                else
                {
                    /*
                     * Vrai double-buffer classique : presenter GP1.
                     */
                    latch_x = current_x;
                    latch_y = current_y;

                    if (current_nz > 64u)
                    {
                        need_latch = 1;
                        ++g_b102_front_latches;
                    }
                    else if (other_nz >= 512u)
                    {
                        latch_x =
                            current_x == 320u
                                ? 0u
                                : 320u;

                        latch_y = 0u;
                        need_latch = 1;
                        ++g_b102_fallback_latches;
                    }
                    else if (!g_b84_latch_valid)
                    {
                        need_latch = 1;
                        ++g_b102_front_latches;
                    }

                    if (need_latch)
                    {
                        ++g_b103_plain_count;
                    }
                }
            }

            if (display_changed)
            {
                g_b86_last_display_x = current_x;
                g_b86_last_display_y = current_y;
                ++g_b86_display_changes;
            }

            if (need_latch)
            {
                for (unsigned py = 0u; py < 256u; ++py)
                {
                    unsigned sy =
                        (latch_y + py) & 511u;

                    const uint16_t *src_row =
                        vram
                        +
                        sy * 1024u
                        +
                        latch_x;

                    uint16_t *dst_row =
                        composite
                        +
                        py * 320u;

                    if (b104_decode24)
                    {
                        /*
                         * PS1 24-bit display :
                         * R,G,B bytes packed back-to-back, 3 bytes/pixel.
                         * X is still expressed in 16-bit VRAM words.
                         */
                        unsigned safe_x = latch_x;
                        if (safe_x > 544u)
                        {
                            safe_x = 0u;
                        }

                        const uint8_t *row_bytes =
                            ((const uint8_t *)vram)
                            +
                            sy * 2048u
                            +
                            safe_x * 2u;

                        for (unsigned px = 0u; px < 320u; ++px)
                        {
                            const uint8_t *p =
                                row_bytes
                                +
                                px * 3u;

                            uint16_t r5 = (uint16_t)(p[0] >> 3);
                            uint16_t g5 = (uint16_t)(p[1] >> 3);
                            uint16_t b5 = (uint16_t)(p[2] >> 3);

                            dst_row[px] =
                                r5
                                |
                                (uint16_t)(g5 << 5)
                                |
                                (uint16_t)(b5 << 10);
                        }
                    }
                    else if (!b103_merge)
                    {
                        memcpy(
                            dst_row,
                            src_row,
                            320u * sizeof(uint16_t)
                        );
                    }
                    else
                    {
                        const uint16_t *base_row =
                            vram
                            +
                            sy * 1024u
                            +
                            b103_base_x;

                        const uint16_t *overlay_row =
                            vram
                            +
                            sy * 1024u
                            +
                            b103_overlay_x;

                        /*
                         * Noir = transparent uniquement pour ce merge
                         * de bring-up. Les elements utiles vus en B101
                         * (texte, cadres, curseur) sont non noirs.
                         */
                        for (unsigned px = 0u; px < 320u; ++px)
                        {
                            uint16_t over = overlay_row[px];

                            dst_row[px] =
                                (over & 0x7FFFu) != 0u
                                    ? over
                                    : base_row[px];
                        }
                    }
                }

                g_b84_latch_x = latch_x;
                g_b84_latch_y = latch_y;

                g_b87_last_source_x = latch_x;
                g_b87_last_source_y = latch_y;

                g_b84_last_dma_sample =
                    g_b78_dma_wait_samples;

                g_b85_last_latched_guest_frame =
                    g_b85_guest_frames;

                g_b84_latch_valid = 1u;
                g_b86_present_dirty = 1u;
                g_b1357_last_latched_gp0 = b104_gp0;
                ++g_b84_latch_count;

                if (b104_decode24)
                {
                    ++g_b104_rgb24_latches;
                }
            }

            g_b104_last_gp0 = b104_gp0;
            g_b104_last_mode = b104_mode;

            /*
             * B135.8: VSync completion is an edge, not a level.
             */
            g_b1358_vsync_completed = 0u;
        }


        if (
            g_b42_native_video
            && fm_gpu_has_frame()
        )
        {
            /*
             * B42 : montrer le framebuffer choisi par le vrai GP1 du jeu.
             * Aucun background artificiel n'est melange ici.
             */
            unsigned display_x = fm_gpu_display_x();
            unsigned display_y = fm_gpu_display_y();

            if (display_x > 704u)
            {
                display_x = 0u;
            }

            if (display_y > 272u)
            {
                display_y = 0u;
            }

            /*
             * ========================================================
             * B94 - coherence du double-buffer 3DS
             * ========================================================
             *
             * B86/B87 sautait fm_present_rgb555() lorsque l'image PS1
             * n'avait pas change, MAIS la boucle fait quand meme ensuite
             * gfxSwapBuffers(). Sur 3DS cela alterne alors entre deux
             * framebuffers host, dont un seul vient d'etre rafraichi :
             * resultat = image correcte / ancienne image / correcte / ...
             * donc clignotement visible.
             *
             * Tant que nous utilisons gfxSwapBuffers() a chaque VBlank,
             * il faut alimenter LE backbuffer courant a chaque frame host.
             * On reutilise le composite PS1 deja latche : aucune logique
             * du jeu n'est rejouee, on ne fait que recopier l'image stable
             * dans le framebuffer 3DS qui va devenir visible.
             */
            if (g_b84_latch_valid)
            {
                /*
                 * B131: only copy/swap when the guest produced a new
                 * stable image. If nothing changed, keep the current
                 * 3DS frontbuffer visible and just wait for VBlank.
                 */
                if (g_b86_present_dirty)
                {
                    fm_present_rgb555(
                        composite,
                        320,
                        crop
                    );

                    g_b86_present_dirty = 0u;

                    ++g_b86_present_count;
                    ++g_b131_dirty_present_count;
                    b131_presented_this_loop = 1;
                }
                else
                {
                    ++g_b86_skipped_presents;
                    ++g_b131_skip_count;
                }
            }
            else
            {
                /*
                 * Before the first stable latch, keep the historical
                 * behavior so boot progress remains visible.
                 */
                fm_present_rgb555(
                    vram + display_y * 1024u + display_x,
                    1024,
                    crop
                );

                ++g_b86_present_count;
                b131_presented_this_loop = 1;
            }
        }
        else if (
            !g_b42_native_video
            && g_bg.loaded
            && g_bg_vram_ok != 0u
        )
        {
            /*
             * Ancien mode B26/B28 conserve pour comparaison avec ZL.
             */
            unsigned vx = fm_gpu_display_x();
            unsigned vy = fm_gpu_display_y();

            if (vx != 0u && vx != 320u)
            {
                vx = 320u;
            }

            if (vy > 256u)
            {
                vy = 0u;
            }

            fm_present_rgb555(
                vram + vy * 1024u + vx,
                1024,
                0
            );

            b131_presented_this_loop = 1;
        }
        else if (
            !g_b42_native_video
            && g_bg.loaded
        )
        {
            fm_present_rgb555(
                preview,
                320,
                0
            );

            b131_presented_this_loop = 1;
        }
        else if (
            fm_gpu_has_frame()
            || g_vram_view_nonzero != 0u
        )
        {
            unsigned display_x =
                g_vram_view_nonzero != 0u
                    ? (unsigned)g_vram_view_x
                    : fm_gpu_display_x();

            unsigned display_y =
                g_vram_view_nonzero != 0u
                    ? (unsigned)g_vram_view_y
                    : fm_gpu_display_y();

            const uint16_t *game_frame =
                vram
                + display_y * 1024u
                + display_x;

            fm_present_rgb555(
                game_frame,
                1024,
                crop
            );

            b131_presented_this_loop = 1;
        }
        else if (show_preview)
        {
            fm_present_rgb555(
                preview,
                320,
                crop
            );

            b131_presented_this_loop = 1;
        }
        else
        {
            /*
             * Noir volontaire : pas de triangle/prototype artificiel.
             */
            sw_fill_rect(
                0,
                0,
                320,
                256,
                0
            );

            fm_present_rgb555(
                vram,
                1024,
                crop
            );

            b131_presented_this_loop = 1;
        }

        render_ticks +=
            svcGetSystemTick()
            - render_start;

        g_b105_render_ms =
            (uint32_t)(osGetTime() - b105_render_start_ms);

        ++render_count;


        /*
         * ====================================================
         * Controller
         * ====================================================
         */

        /*
         * B58.2 : pad est deja calcule au debut de la frame.
         */


        /*
         * ====================================================
         * Debug console
         * ====================================================
         */

        if (
            frame % 120u == 0u
        )
        {
            printf(
                "\x1b[2J"
                "\x1b[H"
            );


            /*
             * =================================================
             * BUILD B12 - vrai callback VBlank guest
             * =================================================
             *
             * On n'imite plus le callback : on execute son vrai code
             * MIPS avec le runtime ARM + fallback R3000A dans un CPU
             * temporaire. Les effets RAM/MMIO sont donc ceux du jeu.
             */

            uint32_t clk440 = fm_memory_read_word(0x8009C440u);
            uint32_t clk444 = fm_memory_read_word(0x8009C444u);
            uint32_t clk41c = fm_memory_read_word(0x8009C41Cu);
            uint32_t clk428 = fm_memory_read_word(0x8009C428u);
            uint32_t clk44c = fm_memory_read_word(0x8009C44Cu);
            uint32_t clk438 = fm_memory_read_word(0x8009C438u);
            uint8_t clk425 = fm_memory_read_byte(0x8009C425u);

            /*
             * B87 : ne pas scanner les 1024x512 pixels pour le debug.
             */
            FMGpuDebugStats gpu_debug;
            memset(&gpu_debug, 0, sizeof(gpu_debug));
            gpu_debug.gp0_words =
                fm_gpu_gp0_count();

            /*
             * B127: B124/B125/B126 counters previously displayed zeros
             * because the compact debug path never populated gpu_debug.
             * Use a lightweight getter that does not scan the whole VRAM.
             */
            fm_gpu_b127_perf_snapshot(
                &gpu_debug
            );

            /*
             * =================================================
             * B130 - PERF CLEAN
             * =================================================
             */
            FMDmaDebugStats b130_dma = {0};
            fm_memory_dma_debug(&b130_dma);

            printf("BUILD B135.33-FAST-GT34 (BASE B131)\n");

            printf(
                "RUN:%c F:%lu CPU:%08lX MENU:%u\n",
                game_running ? 'Y' : 'N',
                (unsigned long)frame,
                cpu ? (unsigned long)cpu->pc : 0ul,
                (unsigned)fm_memory_read_byte(0x801847C0u)
            );

            printf(
                "QS rc:%ld S/L:%lu/%lu STOP:%lu D:%08lX\n",
                (long)g_b135_qs_last_result,
                (unsigned long)g_b135_qs_save_count,
                (unsigned long)g_b135_qs_load_count,
                (unsigned long)g_b65_stop_code,
                (unsigned long)g_b65_stop_detail
            );

            printf(
                "LOOP avg/max/>20/>33:%llu/%lu/%lu/%lu ms\n",
                (unsigned long long)(
                    g_b110_loop_samples
                        ? g_b110_loop_sum_ms / g_b110_loop_samples
                        : 0u
                ),
                (unsigned long)g_b110_loop_max_ms,
                (unsigned long)g_b110_loop_over20,
                (unsigned long)g_b110_loop_over33
            );

            printf(
                "SCHED slice/max:%lu/%lu hand:%lu yields:%lu pb:%lu\n",
                (unsigned long)g_b16_slice_last_ms,
                (unsigned long)g_b16_slice_max_ms,
                (unsigned long)g_b16_last_handoffs,
                (unsigned long)g_b84_budget_yields,
                (unsigned long)g_b105_probe_budget
            );

            printf(
                "GPU words:%llu present:%lu draw:%lu\n",
                (unsigned long long)gpu_debug.gp0_words,
                (unsigned long)g_b86_present_count,
                (unsigned long)g_b74_hit_menu_draw_cb
            );

            {
                uint32_t d_swap =
                    g_b131_swap_count - g_b1359_prev_swap;

                uint32_t d_vsc =
                    g_b1358_vsync_completions - g_b1359_prev_vsc;

                uint64_t d_gp0 =
                    gpu_debug.gp0_words - g_b1359_prev_gp0;

                uint64_t d_pixels =
                    gpu_debug.b125_pixels - g_b13513_prev_pixels;

                uint64_t d_region_chunks =
                    g_b13517_interp_blocks
                    -
                    g_b13519_prev_region_chunks;

                uint64_t d_region_instructions =
                    g_b13519_region_instructions
                    -
                    g_b13519_prev_region_instructions;

                printf(
                    "PERF pre/rend/vb/gfx/wait:%lu/%lu/%lu/%lu/%lu late:%lu\n",
                    (unsigned long)g_b106_pre_gfx_ms,
                    (unsigned long)g_b105_render_ms,
                    (unsigned long)g_b105_vblank_ms,
                    (unsigned long)g_b106_gfx_ms,
                    (unsigned long)g_b106_wait_ms,
                    (unsigned long)g_b13518_late_vblank_skips
                );

                printf(
                    "D120 swap/vsc/gp0/pix:%lu/%lu/%llu/%llu\n",
                    (unsigned long)d_swap,
                    (unsigned long)d_vsc,
                    (unsigned long long)d_gp0,
                    (unsigned long long)d_pixels
                );

                printf(
                    "D120 rgch/ins:%llu/%llu\n",
                    (unsigned long long)d_region_chunks,
                    (unsigned long long)d_region_instructions
                );

                printf(
                    "CHAIN4 e/d/m:%lu/%llu/%lu samples:%lu\n",
                    (unsigned long)g_b13514_chain_entries,
                    (unsigned long long)g_b13514_chain_dispatches,
                    (unsigned long)g_b13514_chain_max,
                    (unsigned long)g_b13516_exit_samples
                );

                printf(
                    "IRGN ent/ch/max/y:%lu/%llu/%lu/%lu\n",
                    (unsigned long)g_b13517_interp_entries,
                    (unsigned long long)g_b13517_interp_blocks,
                    (unsigned long)g_b13517_interp_max,
                    (unsigned long)g_b13517_interp_time_yields
                );

                printf(
                    "IRGN ins:%llu\n",
                    (unsigned long long)g_b13519_region_instructions
                );

                {
                    unsigned top1 = 8u;
                    unsigned top2 = 8u;

                    for (unsigned i = 0u; i < 8u; ++i)
                    {
                        if (
                            g_b13525_interp_pc[i] == 0u
                            ||
                            g_b13525_interp_ins[i] == 0u
                        )
                        {
                            continue;
                        }

                        if (
                            top1 == 8u
                            ||
                            g_b13525_interp_ins[i]
                                > g_b13525_interp_ins[top1]
                        )
                        {
                            top2 = top1;
                            top1 = i;
                        }
                        else if (
                            top2 == 8u
                            ||
                            g_b13525_interp_ins[i]
                                > g_b13525_interp_ins[top2]
                        )
                        {
                            top2 = i;
                        }
                    }

                    printf(
                        "IRPC top:%06lX/%lu/%llu %06lX/%lu/%llu\n",
                        (unsigned long)(
                            top1 < 8u ? g_b13525_interp_pc[top1] : 0u
                        ),
                        (unsigned long)(
                            top1 < 8u ? g_b13525_interp_hits[top1] : 0u
                        ),
                        (unsigned long long)(
                            top1 < 8u ? g_b13525_interp_ins[top1] : 0u
                        ),
                        (unsigned long)(
                            top2 < 8u ? g_b13525_interp_pc[top2] : 0u
                        ),
                        (unsigned long)(
                            top2 < 8u ? g_b13525_interp_hits[top2] : 0u
                        ),
                        (unsigned long long)(
                            top2 < 8u ? g_b13525_interp_ins[top2] : 0u
                        )
                    );
                }

                printf(
                    "EXIT top:%06lX/%lu %06lX/%lu\n",
                    (unsigned long)g_b13516_exit_pc[0],
                    (unsigned long)g_b13516_exit_weight[0],
                    (unsigned long)g_b13516_exit_pc[1],
                    (unsigned long)g_b13516_exit_weight[1]
                );

                printf(
                    "ENTRY 34D7C/D30/A14/57B80:%d/%d/%d/%d\n",
                    psx_game_is_function_entry(0x80034D7Cu),
                    psx_game_is_function_entry(0x80034D30u),
                    psx_game_is_function_entry(0x80034A14u),
                    psx_game_is_function_entry(0x80057B80u)
                );

                g_b1359_prev_swap = g_b131_swap_count;
                g_b1359_prev_vsc = g_b1358_vsync_completions;
                g_b1359_prev_gp0 = gpu_debug.gp0_words;
                g_b13513_prev_pixels = gpu_debug.b125_pixels;
                g_b13519_prev_region_chunks = g_b13517_interp_blocks;
                g_b13519_prev_region_instructions =
                    g_b13519_region_instructions;
            }

            printf(
                "PACING swap/dirty/skip:%lu/%lu/%lu VSL:%lu VSC:%lu\n",
                (unsigned long)g_b131_swap_count,
                (unsigned long)g_b131_dirty_present_count,
                (unsigned long)g_b131_skip_count,
                (unsigned long)g_b1357_vsync_latches,
                (unsigned long)g_b1358_vsync_completions
            );

            printf(
                "FAST rect:%lu quadT/G:%lu/%lu fill:%lu/%lu\n",
                (unsigned long)gpu_debug.b124_rect_hits,
                (unsigned long)gpu_debug.b125_texquad_hits,
                (unsigned long)gpu_debug.b125_gouraud_hits,
                (unsigned long)gpu_debug.b129_fill_hits,
                (unsigned long)gpu_debug.b129_fill_fallbacks
            );

            printf(
                "SEEN 2C/2E/3A:%lu/%lu/%lu mode:%d/%d/%d\n",
                (unsigned long)gpu_debug.b126_seen_2c,
                (unsigned long)gpu_debug.b126_seen_2e,
                (unsigned long)gpu_debug.b126_seen_3a,
                gpu_debug.b126_scale,
                gpu_debug.b126_wide,
                gpu_debug.b126_filter
            );

            printf(
                "FILL px:%llu zero:%llu max:%lu\n",
                (unsigned long long)gpu_debug.b129_fill_pixels,
                (unsigned long long)gpu_debug.b129_fill_zero_pixels,
                (unsigned long)gpu_debug.b129_fill_max_pixels
            );

            printf(
                "DMA2 LL:%lu N/W:%lu/%lu ms:%lu/%lu\n",
                (unsigned long)b130_dma.dma2_linked_transfer_count,
                (unsigned long)b130_dma.dma2_last_nodes,
                (unsigned long)b130_dma.dma2_last_words,
                (unsigned long)b130_dma.dma2_linked_last_ms,
                (unsigned long)b130_dma.dma2_linked_max_ms
            );

            printf(
                "DMA2 >20/33:%lu/%lu cyc:%lu OT:%lu skip:%lu\n",
                (unsigned long)b130_dma.dma2_linked_over20,
                (unsigned long)b130_dma.dma2_linked_over33,
                (unsigned long)b130_dma.dma2_cycle_abort_count,
                (unsigned long)b130_dma.dma2_last_empty_ot_nodes,
                (unsigned long)b130_dma.dma2_empty_fast_max
            );

            {
                FMGpuOpcodePerf hot0 = {0};
                FMGpuOpcodePerf hot1 = {0};

                fm_gpu_b122_rank(0u, &hot0);
                fm_gpu_b122_rank(1u, &hot1);

                printf(
                    "GHOT %02X c/t/m:%lu/%llu/%lu\n",
                    (unsigned)hot0.opcode,
                    (unsigned long)hot0.calls,
                    (unsigned long long)hot0.total_us,
                    (unsigned long)hot0.max_us
                );

                printf(
                    "GHOT2 %02X c/t/m:%lu/%llu/%lu\n",
                    (unsigned)hot1.opcode,
                    (unsigned long)hot1.calls,
                    (unsigned long long)hot1.total_us,
                    (unsigned long)hot1.max_us
                );
            }

            /*
             * Les anciens diagnostics restent dans le fichier pour
             * pouvoir les reactiver, mais sont masques dans B87.
             */
            if (0)
            {

            printf(
                "BG:%s err:%d layout:PAL idx:%03lX\n",
                g_bg.loaded ? "OK" : "NO",
                g_bg.error,
                (unsigned long)g_bg.game_index
            );

            printf(
                "WA LBA:%lu size:%lu\n",
                (unsigned long)g_bg.wa_lba,
                (unsigned long)g_bg.wa_size
            );

            printf(
                "REL:%05lX sec:%lX type:%lu abs:%lu\n",
                (unsigned long)g_bg.rel_lba,
                (unsigned long)g_bg.lba_sectors,
                (unsigned long)g_bg.type,
                (unsigned long)(g_bg.wa_lba + g_bg.rel_lba)
            );

            printf(
                "IMG:%lux%lu nz:%lu grp:%lu n:%02lu\n",
                (unsigned long)g_bg.width,
                (unsigned long)g_bg.height,
                (unsigned long)g_bg.nonzero,
                (unsigned long)g_bg.group,
                (unsigned long)g_bg.ordinal
            );

            printf(
                "PAL base:29E8  +G1:0672 +G2:13BC\n"
            );

            printf(
                "BGREQ C/OK/F:%lu/%lu/%lu raw:%04lX\n",
                (unsigned long)g_bg_hle_calls,
                (unsigned long)g_bg_hle_ok,
                (unsigned long)g_bg_hle_fail,
                (unsigned long)g_bg_hle_raw
            );

            printf(
                "BGREQ idx:%04lX obj:%08lX\n",
                (unsigned long)g_bg_hle_resolved,
                (unsigned long)g_bg_hle_object
            );

            printf(
                "LOADIMG C/OK/F:%lu/%lu/%lu pix:%lu\n",
                (unsigned long)g_loadimg_hle_calls,
                (unsigned long)g_loadimg_hle_ok,
                (unsigned long)g_loadimg_hle_fail,
                (unsigned long)g_loadimg_hle_pixels
            );

            printf(
                "BGVRAM C/OK:%lu/%lu pix:%lu words:%lu\n",
                (unsigned long)g_bg_vram_calls,
                (unsigned long)g_bg_vram_ok,
                (unsigned long)g_bg_vram_pixels,
                (unsigned long)g_bg_vram_words
            );

            printf(
                "B42 VIDEO:%s CLRKEEP:%d DXY:%u,%u ZL=MODE\n",
                g_b42_native_video ? "NATIVE" : "LEGACY",
                fm_gpu_b42_get_preserve_background_clears(),
                fm_gpu_display_x(),
                fm_gpu_display_y()
            );

            printf(
                "A=RUN  X/Y BG  L/R TYPE  (VRAM)\n"
            );

            printf(
                "RUN:%s PC:%08lX STATE:%02X 425:%02X\n",
                game_running ? "Y" : "N",
                cpu ? (unsigned long)cpu->pc : 0ul,
                (unsigned)g_main_state,
                (unsigned)clk425
            );

            printf(
                "FAST:%lu/%lu D2DF:%lu C/R:%lu/%lu\n",
                (unsigned long)g_fast401_forced,
                (unsigned long)g_fast43e_forced,
                (unsigned long)g_direct2df_active,
                (unsigned long)g_direct2df_calls,
                (unsigned long)g_direct2df_returns
            );

            printf(
                "SORT C/OK/F:%lu/%lu/%lu OTFIX:%lu\n",
                (unsigned long)g_sort_native_calls,
                (unsigned long)g_sort_native_ok,
                (unsigned long)g_sort_native_fail,
                (unsigned long)g_ot_fix_changed
            );

            printf(
                "CD sec:%lu cmd:%02lX OV:%lu/%lu  R137:%lu\n",
                (unsigned long)g_cd_sector_count,
                (unsigned long)g_cd_last_cmd,
                (unsigned long)g_hit_ov16,
                (unsigned long)g_hit_ov18,
                (unsigned long)g_hit_load_wait
            );

            printf(
                "ACMD/R:%lu/%lu CB:%lu/%lu skip:%lu cmd:%02lX\n",
                (unsigned long)g_b33_async_calls,
                (unsigned long)g_b33_raw_calls,
                (unsigned long)g_b33_cb_started,
                (unsigned long)g_b33_cb_done,
                (unsigned long)g_b33_cb_skipped,
                (unsigned long)g_b33_cb_cmd
            );

            printf(
                "B34 mode/cmd:%02lX/%02lX READY:%lu/%lu p:%lu\n",
                (unsigned long)g_b34_last_mode,
                (unsigned long)g_b34_last_command,
                (unsigned long)g_b34_ready_started,
                (unsigned long)g_b34_ready_done,
                (unsigned long)g_b34_ready_pending
            );

            printf(
                "RD req:%08lX rem:%08lX>%08lX\n",
                (unsigned long)g_b34_ready_req,
                (unsigned long)g_b34_ready_before,
                (unsigned long)g_b34_ready_after
            );

            printf(
                "B36 FIN S/D:%lu/%lu C460:%08lX>%08lX\n",
                (unsigned long)g_b35_finalizer_started,
                (unsigned long)g_b35_finalizer_done,
                (unsigned long)g_b35_c460_before,
                (unsigned long)g_b35_c460_after
            );
            printf(
                "CTX C:%lu/%lu R:%lu/%lu F:%lu/%lu RA:%08lX\n",
                (unsigned long)g_b33_ctx_saved,
                (unsigned long)g_b33_ctx_restored,
                (unsigned long)g_b34_ready_ctx_saved,
                (unsigned long)g_b34_ready_ctx_restored,
                (unsigned long)g_b35_ctx_saved,
                (unsigned long)g_b35_ctx_restored,
                (unsigned long)g_b34_ready_saved_ra
            );

            printf(
                "B37 DMA wait/fix:%lu/%lu CH:%08lX>%08lX\n",
                (unsigned long)g_b37_dma_wait_hits,
                (unsigned long)g_b37_dma_forced_clear,
                (unsigned long)g_b37_last_chcr_before,
                (unsigned long)g_b37_last_chcr_after
            );

            {
                uint32_t br_count = 0u;
                uint8_t br_op = 0u;
                int br_tex = 0, br_raw = 0;
                int br_x = 0, br_y = 0, br_w = 0, br_h = 0;
                int br_u = 0, br_v = 0, br_cx = 0, br_cy = 0;
                uint16_t br_tp = 0u;
                uint32_t br_cmd[4] = {0u,0u,0u,0u};

                if (fm_gpu_b38_bigrect_get(
                        &br_count, &br_op, &br_tex, &br_raw,
                        &br_x, &br_y, &br_w, &br_h,
                        &br_u, &br_v, &br_cx, &br_cy,
                        &br_tp, br_cmd))
                {
                    printf(
                        "BIG:%lu op:%02X T/R:%d/%d xy:%d,%d wh:%d,%d\n",
                        (unsigned long)br_count,
                        (unsigned)br_op,
                        br_tex,
                        br_raw,
                        br_x, br_y, br_w, br_h
                    );

                    printf(
                        "BIG uv:%d,%d CL:%d,%d TP:%03X c:%08lX\n",
                        br_u, br_v, br_cx, br_cy,
                        (unsigned)br_tp,
                        (unsigned long)br_cmd[0]
                    );

                    printf(
                        "BIG cmd:%08lX %08lX %08lX %08lX\n",
                        (unsigned long)br_cmd[0],
                        (unsigned long)br_cmd[1],
                        (unsigned long)br_cmd[2],
                        (unsigned long)br_cmd[3]
                    );

                    {
                        uint32_t tw = 0u;
                        int dep = 0, tbx = 0, tby = 0;
                        uint32_t texels = 0u, inz = 0u, cnz = 0u, uniq = 0u;
                        uint16_t pal[16] = {0};
                        uint8_t si[8] = {0};
                        uint16_t sc[8] = {0};

                        if (fm_gpu_b39_texture_probe_get(
                                &tw, &dep, &tbx, &tby,
                                &texels, &inz, &cnz, &uniq,
                                pal, si, sc))
                        {
                            printf(
                                "TEX d:%d base:%d,%d TW:%05lX uniq:%lu\n",
                                dep, tbx, tby,
                                (unsigned long)tw,
                                (unsigned long)uniq
                            );

                            printf(
                                "TEX nz i/c:%lu/%lu of:%lu idx:%X%X%X%X%X%X%X%X\n",
                                (unsigned long)inz,
                                (unsigned long)cnz,
                                (unsigned long)texels,
                                si[0], si[1], si[2], si[3],
                                si[4], si[5], si[6], si[7]
                            );

                            /*
                             * B43 : quel LoadImage a réellement alimenté
                             * la zone VRAM échantillonnée par ce sprite ?
                             *
                             * Pour le cas courant TW=0, la boite est exacte.
                             * Si une texture window est active, on garde une
                             * boite conservative et on l'indique via TW.
                             */
                            {
                                unsigned ppw =
                                    dep == 0 ? 4u :
                                    dep == 1 ? 2u : 1u;

                                unsigned u0 = (unsigned)br_u & 0xFFu;
                                unsigned v0 = (unsigned)br_v & 0xFFu;

                                unsigned tx =
                                    (unsigned)tbx
                                    +
                                    (u0 / ppw);

                                unsigned ty =
                                    (unsigned)tby
                                    +
                                    v0;

                                unsigned tw_words =
                                    (
                                        (u0 % ppw)
                                        +
                                        (unsigned)br_w
                                        +
                                        ppw
                                        - 1u
                                    )
                                    /
                                    ppw;

                                unsigned th_words =
                                    (unsigned)br_h;

                                unsigned tex_hits = 0u;
                                const FMB43LoadTrace *tex_best = NULL;

                                for (
                                    uint32_t k = 0u;
                                    k < g_b43_load_count;
                                    ++k
                                )
                                {
                                    uint32_t li =
                                        (
                                            g_b43_load_head
                                            + B43_LOAD_RING
                                            - 1u
                                            - k
                                        )
                                        % B43_LOAD_RING;

                                    const FMB43LoadTrace *lt =
                                        &g_b43_loads[li];

                                    uint32_t ax0 = lt->x;
                                    uint32_t ay0 = lt->y;
                                    uint32_t ax1 = ax0 + lt->w;
                                    uint32_t ay1 = ay0 + lt->h;

                                    uint32_t bx0 = tx;
                                    uint32_t by0 = ty;
                                    uint32_t bx1 = bx0 + tw_words;
                                    uint32_t by1 = by0 + th_words;

                                    if (
                                        ax0 < bx1
                                        && bx0 < ax1
                                        && ay0 < by1
                                        && by0 < ay1
                                    )
                                    {
                                        ++tex_hits;

                                        if (!tex_best)
                                        {
                                            tex_best = lt;
                                        }
                                    }
                                }

                                printf(
                                    "TBOX:%u,%u %ux%u hits:%u TW:%05lX\\n",
                                    tx, ty,
                                    tw_words, th_words,
                                    tex_hits,
                                    (unsigned long)tw
                                );

                                if (tex_best)
                                {
                                    printf(
                                        "TUP #%lu xy:%u,%u wh:%u,%u src:%08lX\\n",
                                        (unsigned long)tex_best->serial,
                                        (unsigned)tex_best->x,
                                        (unsigned)tex_best->y,
                                        (unsigned)tex_best->w,
                                        (unsigned)tex_best->h,
                                        (unsigned long)tex_best->src
                                    );

                                    unsigned tcd_hits = 0u;
                                    const FMB41CdTrace *tcd_best = NULL;

                                    uint32_t src_begin = tex_best->src;
                                    uint32_t src_end =
                                        tex_best->src
                                        +
                                        (uint32_t)tex_best->w
                                        *
                                        (uint32_t)tex_best->h
                                        *
                                        2u;

                                    for (
                                        uint32_t k = 0u;
                                        k < g_b41_cd_count;
                                        ++k
                                    )
                                    {
                                        uint32_t ci =
                                            (
                                                g_b41_cd_head
                                                + B41_CD_RING
                                                - 1u
                                                - k
                                            )
                                            % B41_CD_RING;

                                        const FMB41CdTrace *ct =
                                            &g_b41_cd[ci];

                                        uint32_t cd0 = ct->dst;
                                        uint32_t cd1 = ct->dst + ct->bytes;

                                        if (
                                            src_begin < cd1
                                            && cd0 < src_end
                                        )
                                        {
                                            ++tcd_hits;

                                            if (!tcd_best)
                                            {
                                                tcd_best = ct;
                                            }
                                        }
                                    }

                                    if (tcd_best)
                                    {
                                        printf(
                                            "TCD hits:%u LBA:%08lX dst:%08lX\\n",
                                            tcd_hits,
                                            (unsigned long)tcd_best->lba,
                                            (unsigned long)tcd_best->dst
                                        );
                                    }
                                    else
                                    {
                                        printf("TCD hits:0\\n");
                                    }
                                }
                                else
                                {
                                    const FMB43LoadTrace *last = NULL;

                                    if (g_b43_load_count != 0u)
                                    {
                                        uint32_t li =
                                            (
                                                g_b43_load_head
                                                + B43_LOAD_RING
                                                - 1u
                                            )
                                            % B43_LOAD_RING;

                                        last = &g_b43_loads[li];
                                    }

                                    if (last)
                                    {
                                        printf(
                                            "TUP NONE last#%lu xy:%u,%u wh:%u,%u\\n",
                                            (unsigned long)last->serial,
                                            (unsigned)last->x,
                                            (unsigned)last->y,
                                            (unsigned)last->w,
                                            (unsigned)last->h
                                        );
                                    }
                                    else
                                    {
                                        printf("TUP NONE no LoadImage\\n");
                                    }
                                }
                            }

                            printf(
                                "PAL:%04X %04X %04X %04X %04X %04X %04X %04X\n",
                                pal[0], pal[1], pal[2], pal[3],
                                pal[4], pal[5], pal[6], pal[7]
                            );

                            printf(
                                "COL:%04X %04X %04X %04X\n",
                                sc[0], sc[1], sc[2], sc[3]
                            );


                            /*
                             * B40 : retrouver le dernier petit LoadImage qui
                             * a couvert le pixel de départ de cette CLUT.
                             */
                            {
                                unsigned cl_hits = 0u;
                                const FMB40UploadTrace *best = NULL;
                                uint32_t best_offset = 0u;

                                for (uint32_t k = 0u; k < g_b40_upload_count; ++k)
                                {
                                    uint32_t idx =
                                        (
                                            g_b40_upload_head
                                            + B40_UPLOAD_RING
                                            - 1u
                                            - k
                                        )
                                        % B40_UPLOAD_RING;

                                    const FMB40UploadTrace *t =
                                        &g_b40_uploads[idx];

                                    uint32_t x0 = t->x;
                                    uint32_t y0 = t->y;
                                    uint32_t x1 = x0 + t->w;
                                    uint32_t y1 = y0 + t->h;

                                    if (
                                        (uint32_t)br_cx >= x0
                                        && (uint32_t)br_cx < x1
                                        && (uint32_t)br_cy >= y0
                                        && (uint32_t)br_cy < y1
                                    )
                                    {
                                        ++cl_hits;

                                        if (!best)
                                        {
                                            best = t;
                                            best_offset =
                                                ((uint32_t)br_cy - y0) * t->w
                                                + ((uint32_t)br_cx - x0);
                                        }
                                    }
                                }

                                if (best)
                                {
                                    printf(
                                        "CLUP hits:%u #%lu xy:%u,%u wh:%u,%u\n",
                                        cl_hits,
                                        (unsigned long)best->serial,
                                        (unsigned)best->x,
                                        (unsigned)best->y,
                                        (unsigned)best->w,
                                        (unsigned)best->h
                                    );

                                    printf(
                                        "CLUP src:%08lX off:%lu snap:%u\n",
                                        (unsigned long)best->src,
                                        (unsigned long)best_offset,
                                        (unsigned)best->snap_count
                                    );

                                    uint16_t at_upload[8] = {0};
                                    uint16_t now_ram[8] = {0};

                                    for (unsigned q = 0u; q < 8u; ++q)
                                    {
                                        uint32_t p = best_offset + q;

                                        if (p < best->snap_count)
                                        {
                                            at_upload[q] = best->pixels[p];
                                        }

                                        if (
                                            p
                                            <
                                            (uint32_t)best->w * best->h
                                        )
                                        {
                                            now_ram[q] = cpu->read_half(
                                                best->src + p * 2u
                                            );
                                        }
                                    }

                                    printf(
                                        "CLAT:%04X %04X %04X %04X %04X %04X %04X %04X\n",
                                        at_upload[0], at_upload[1],
                                        at_upload[2], at_upload[3],
                                        at_upload[4], at_upload[5],
                                        at_upload[6], at_upload[7]
                                    );

                                    printf(
                                        "CLNOW:%04X %04X %04X %04X %04X %04X %04X %04X\n",
                                        now_ram[0], now_ram[1],
                                        now_ram[2], now_ram[3],
                                        now_ram[4], now_ram[5],
                                        now_ram[6], now_ram[7]
                                    );

                                    /*
                                     * Chercher si un vrai secteur CD a
                                     * directement rempli la zone source de
                                     * ce LoadImage.
                                     */
                                    unsigned cd_hits = 0u;
                                    const FMB41CdTrace *cd_best = NULL;

                                    uint32_t src_begin = best->src;
                                    uint32_t src_end =
                                        best->src
                                        +
                                        (uint32_t)best->w
                                        *
                                        (uint32_t)best->h
                                        *
                                        2u;

                                    for (
                                        uint32_t k = 0u;
                                        k < g_b41_cd_count;
                                        ++k
                                    )
                                    {
                                        uint32_t ci =
                                            (
                                                g_b41_cd_head
                                                + B41_CD_RING
                                                - 1u
                                                - k
                                            )
                                            % B41_CD_RING;

                                        const FMB41CdTrace *ct =
                                            &g_b41_cd[ci];

                                        uint32_t cd_begin = ct->dst;
                                        uint32_t cd_end =
                                            ct->dst + ct->bytes;

                                        if (
                                            src_begin < cd_end
                                            &&
                                            cd_begin < src_end
                                        )
                                        {
                                            ++cd_hits;

                                            if (!cd_best)
                                            {
                                                cd_best = ct;
                                            }
                                        }
                                    }

                                    if (cd_best)
                                    {
                                        printf(
                                            "CDSRC hits:%u #%lu LBA:%08lX\n",
                                            cd_hits,
                                            (unsigned long)cd_best->serial,
                                            (unsigned long)cd_best->lba
                                        );

                                        printf(
                                            "CDSRC dst:%08lX bytes:%lu\n",
                                            (unsigned long)cd_best->dst,
                                            (unsigned long)cd_best->bytes
                                        );
                                    }
                                    else
                                    {
                                        printf(
                                            "CDSRC hits:0 src not direct-CD\n"
                                        );
                                    }
                                }
                                else
                                {
                                    printf(
                                        "CLUP hits:0 smallUploads:%lu\n",
                                        (unsigned long)g_b40_upload_count
                                    );
                                }
                            }
                        }
                        else
                        {
                            printf("TEX probe:none\n");
                        }
                    }
                }
                else
                {
                    printf("BIG:none\n");
                }
            }

            {
                uint32_t wf=0u, wd=0u, wc=0u, wu=0u, ws=0u;
                uint8_t wt=0u, wo=0u;
                int wx=0, wy=0, ww=0, wh=0;
                uint32_t wcmd[4] = {0u,0u,0u,0u};

                fm_gpu_b44_watch_get(
                    &wf, &wd, &wc, &wu,
                    &ws, &wt, &wo,
                    &wx, &wy, &ww, &wh,
                    wcmd
                );

                printf(
                    "W290,64 18x72 F/D/C/U:%lu/%lu/%lu/%lu\\n",
                    (unsigned long)wf,
                    (unsigned long)wd,
                    (unsigned long)wc,
                    (unsigned long)wu
                );

                if (ws != 0u)
                {
                    printf(
                        "WLAST #%lu %c op:%02X xy:%d,%d wh:%d,%d\\n",
                        (unsigned long)ws,
                        wt ? (char)wt : '?',
                        (unsigned)wo,
                        wx, wy, ww, wh
                    );

                    printf(
                        "WCMD:%08lX %08lX %08lX %08lX\\n",
                        (unsigned long)wcmd[0],
                        (unsigned long)wcmd[1],
                        (unsigned long)wcmd[2],
                        (unsigned long)wcmd[3]
                    );
                }
                else
                {
                    printf("WLAST:none\\n");
                }
            }

            {
                uint32_t ph=0u, ps=0u, pea=0u, pfa=0u;
                uint16_t pe1=0u, ptp=0u;
                int pox=0, poy=0;
                uint32_t pcmd[4] = {0u,0u,0u,0u};

                if (fm_gpu_b46_sprite_provenance_get(
                        &ph, &ps, &pe1, &pea, &pfa,
                        &ptp, &pox, &poy, pcmd))
                {
                    printf(
                        "GPU64 hits:%lu serial:%lu E1:%03X age:%lu\n",
                        (unsigned long)ph,
                        (unsigned long)ps,
                        (unsigned)pe1,
                        (unsigned long)pea
                    );

                    printf(
                        "GPU64 fillAge:%lu TP:%03X off:%d,%d\n",
                        (unsigned long)pfa,
                        (unsigned)ptp,
                        pox, poy
                    );

                    printf(
                        "GPU64 cmd:%08lX %08lX %08lX %08lX\n",
                        (unsigned long)pcmd[0],
                        (unsigned long)pcmd[1],
                        (unsigned long)pcmd[2],
                        (unsigned long)pcmd[3]
                    );
                }
                else
                {
                    printf("GPU64:none\n");
                }
            }

            printf(
                "43PATH EB8/F3C/F54/FF8:%lu/%lu/%lu/%lu\n",
                (unsigned long)g_b47_m_43eb8,
                (unsigned long)g_b47_m_43f3c,
                (unsigned long)g_b47_m_43f54,
                (unsigned long)g_b47_m_43ff8
            );

            printf(
                "43PATH 4054/4064/406C:%lu/%lu/%lu last:%05lX\n",
                (unsigned long)g_b47_m_44054,
                (unsigned long)g_b47_m_44064,
                (unsigned long)g_b47_m_4406c,
                (unsigned long)g_b47_last_milestone
            );

            printf(
                "OV16 F4/160/R:%lu/%lu/%lu V0:%08lX\n",
                (unsigned long)g_b47_680f4_enter,
                (unsigned long)g_b47_68160_enter,
                (unsigned long)g_b47_68160_return,
                (unsigned long)g_b47_68160_last_v0
            );

            printf(
                "OV160 zero/nonzero:%lu/%lu RA:%08lX\n",
                (unsigned long)g_b47_68160_v0_zero,
                (unsigned long)g_b47_68160_v0_nonzero,
                (unsigned long)g_b47_68160_last_ra
            );

            printf(
                "B38 STAT:%08lX ring:%lu/%lu PC:%08lX\n",
                (unsigned long)g_b37_last_gpustat,
                (unsigned long)g_b37_ring_write,
                (unsigned long)g_b37_ring_read,
                cpu ? (unsigned long)cpu->pc : 0ul
            );

            printf(
                "GETSEC C/O/F:%lu/%lu/%lu rc:%ld\n",
                (unsigned long)g_b32_getsec_calls,
                (unsigned long)g_b32_getsec_ok,
                (unsigned long)g_b32_getsec_fail,
                (long)(int32_t)g_b32_last_rc
            );

            printf(
                "GET req/lba:%08lX/%08lX rem:%08lX\n",
                (unsigned long)g_b32_last_req,
                (unsigned long)g_b32_last_lba,
                (unsigned long)g_b32_last_remaining
            );

            printf(
                "GET dst/bytes:%08lX/%lu 43N:%lu\n",
                (unsigned long)g_b32_last_dst,
                (unsigned long)g_b32_last_bytes,
                (unsigned long)g_b32_43e_returned
            );

            printf(
                "REQ snap:%lu 10:%08lX 18:%08lX\n",
                (unsigned long)g_b31_req_snap,
                (unsigned long)g_b31_req_10,
                (unsigned long)g_b31_req_18
            );

            printf(
                "REQ 1C:%08lX 20:%08lX 24:%08lX\n",
                (unsigned long)g_b31_req_1c,
                (unsigned long)g_b31_req_20,
                (unsigned long)g_b31_req_24
            );

            printf(
                "REQ 2C:%08lX 34:%08lX 40:%08lX\n",
                (unsigned long)g_b31_req_2c,
                (unsigned long)g_b31_req_34,
                (unsigned long)g_b31_req_40
            );

            printf(
                "REQ 44:%04X 46/47:%02X/%02X\n",
                (unsigned)g_b31_req_44,
                (unsigned)g_b31_req_46,
                (unsigned)g_b31_req_47
            );

            printf(
                "137 RA/GP:%08lX/%08lX\n",
                (unsigned long)g_b31_r137_ra,
                (unsigned long)g_b31_r137_gp
            );

            printf(
                "137 A0/A1:%08lX/%08lX A2/A3:%08lX/%08lX\n",
                (unsigned long)g_b31_r137_a0,
                (unsigned long)g_b31_r137_a1,
                (unsigned long)g_b31_r137_a2,
                (unsigned long)g_b31_r137_a3
            );

            printf(
                "C460/C484/T0:%08lX/%08lX/%08lX\n",
                (unsigned long)g_b31_c460,
                (unsigned long)g_b31_c484,
                (unsigned long)g_b31_tbl0
            );

            printf(
                "ST:%02X stable:%lu 60C/D/E:%02X/%02X/%02X\n",
                (unsigned)g_main_state,
                (unsigned long)g_main_state_stable_frames,
                (unsigned)g_main_state_60c,
                (unsigned)g_main_state_60d,
                (unsigned)g_main_state_60e
            );

            printf(
                "FADE:%02X/%02X/%02X done:%lu  GPU:%llu/%llu/%llu/%llu\n",
                (unsigned)g_fade_current,
                (unsigned)g_fade_target,
                (unsigned)g_fade_flags,
                (unsigned long)g_fade_bridge_completions,
                (unsigned long long)gpu_debug.packets_fill,
                (unsigned long long)gpu_debug.packets_draw,
                (unsigned long long)gpu_debug.packets_copy,
                (unsigned long long)gpu_debug.packets_upload
            );

            printf(
                "GP0:%llu VRAM:%lu VIEW:%lu,%lu nz:%lu\n",
                (unsigned long long)gpu_debug.gp0_words,
                (unsigned long)gpu_debug.nonzero_vram,
                (unsigned long)g_vram_view_x,
                (unsigned long)g_vram_view_y,
                (unsigned long)g_vram_view_nonzero
            );

            /*
             * =================================================
             * B48 - diagnostic du verrou 80042ADC / GTE
             * =================================================
             *
             * La capture B47 termine autour de 80042ADC, juste
             * apres l'appel de FUN_800891E8. Cette chaine appelle
             * les helpers GTE (notamment 80087B48).
             *
             * On affiche volontairement ces lignes EN DERNIER afin
             * qu'elles restent visibles même lorsque la console
             * inférieure défile.
             */
            printf(
                "B54 P:%s CPU:%08lX I:%s frame:%lu\n",
                probe_ran
                    ? fm_runtime_stop_name(probe.reason)
                    : "NONE",
                cpu ? (unsigned long)cpu->pc : 0ul,
                interp_ran
                    ? fm_interp_stop_name(interp.reason)
                    : "NONE",
                (unsigned long)frame
            );

            printf(
                "B54 IP:%08lX INS:%08lX op:%02lX fn:%02lX\n",
                interp_ran
                    ? (unsigned long)interp.pc
                    : 0ul,
                interp_ran
                    ? (unsigned long)interp.instruction
                    : 0ul,
                interp_ran
                    ? (unsigned long)(interp.instruction >> 26)
                    : 0ul,
                interp_ran
                    ? (unsigned long)(interp.instruction & 0x3Fu)
                    : 0ul
            );

            printf(
                "B54 F4:%08lX %08lX %08lX %08lX\n",
                (unsigned long)fm_memory_read_word(0x801680F4u),
                (unsigned long)fm_memory_read_word(0x801680F8u),
                (unsigned long)fm_memory_read_word(0x801680FCu),
                (unsigned long)fm_memory_read_word(0x80168100u)
            );

            printf(
                "B54 160:%08lX %08lX %08lX %08lX\n",
                (unsigned long)fm_memory_read_word(0x80168160u),
                (unsigned long)fm_memory_read_word(0x80168164u),
                (unsigned long)fm_memory_read_word(0x80168168u),
                (unsigned long)fm_memory_read_word(0x8016816Cu)
            );

            printf(
                "B54 FAST43:%lu a0:%lu>%lu CD:%08lX/%08lX\n",
                (unsigned long)g_b53_fast43cd4_hits,
                (unsigned long)g_b53_fast43cd4_last_in,
                (unsigned long)g_b53_fast43cd4_last_out,
                (unsigned long)fm_memory_read_word(0x8009C460u),
                (unsigned long)fm_memory_read_word(0x8009C484u)
            );

            printf(
                "B54 PATH 7E8/F3C/F54/FF8:%lu/%lu/%lu/%lu\n",
                (unsigned long)g_b49_fn_7e8e8,
                (unsigned long)g_b47_m_43f3c,
                (unsigned long)g_b47_m_43f54,
                (unsigned long)g_b47_m_43ff8
            );

            printf(
                "B54 OV F4/160/R ZN:%lu/%lu/%lu %lu/%lu\n",
                (unsigned long)g_b47_680f4_enter,
                (unsigned long)g_b47_68160_enter,
                (unsigned long)g_b47_68160_return,
                (unsigned long)g_b47_68160_v0_zero,
                (unsigned long)g_b47_68160_v0_nonzero
            );

            }

            /*
             * Reset des compteurs de mesure de rendu sans
             * consommer une ligne supplémentaire à l'écran.
             */
            if (
                frame % 30 == 0
                && frame != 0
                && render_count != 0
            )
            {
                render_ticks = 0;
                render_count = 0;
            }
        }

        old_pad =
            pad;


        /*
         * GP0 émis pendant cette frame 3DS.
         */
        {
            uint64_t gp0_now =
                fm_gpu_gp0_count();


            gp0_last_frame =
                gp0_now
                -
                gp0_prev_frame;


            gp0_prev_frame =
                gp0_now;
        }


        ++frame;


        /*
         * Latch VBlank PS1 une fois par frame 3DS.
         */
        if (memory_status == 0)
        {
            fm_memory_vblank_tick();

            /*
             * B12 : executer le vrai callback VBlank du jeu dans un
             * contexte CPU isole, sans detruire les registres du
             * thread principal.
             */
            if (game_running)
            {
                {
                    uint64_t b105_vblank_start_ms =
                        osGetTime();

                    fm_execute_guest_vblank_callback(
                        cpu,
                        frame
                    );

                    g_b105_vblank_ms =
                        (uint32_t)(
                            osGetTime()
                            -
                            b105_vblank_start_ms
                        );
                }

                /*
                 * B72 - conserver le dernier etat input guest non nul.
                 * FUN_8003CEA4, executee par le callback VBlank,
                 * transforme 70C en held/edge/repeat.
                 */
                {
                    uint32_t b72_raw =
                        fm_memory_read_word(0x8009C70Cu)
                        &
                        0xFFFFu;

                    uint32_t b72_held =
                        fm_memory_read_word(0x8009C710u)
                        &
                        0xFFFFu;

                    uint32_t b72_edge =
                        fm_memory_read_word(0x8009C72Cu)
                        &
                        0xFFFFu;

                    uint32_t b72_rep =
                        fm_memory_read_word(0x8009C728u)
                        &
                        0xFFFFu;

                    if (
                        b72_raw != 0u
                        ||
                        b72_held != 0u
                        ||
                        b72_edge != 0u
                        ||
                        b72_rep != 0u
                    )
                    {
                        g_b72_guest_raw_latched = b72_raw;
                        g_b72_guest_held_latched = b72_held;
                        g_b72_guest_edge_latched = b72_edge;
                        g_b72_guest_rep_latched = b72_rep;
                        g_b72_guest_nonzero_frame = frame;
                    }

                    if ((b72_edge & 0x0008u) != 0u)
                    {
                        ++g_b72_edge8_hits;
                        g_b72_edge8_last_frame = frame;
                    }
                }

                /*
                 * =====================================================
                 * B13 FASTBOOT 401A4
                 * =====================================================
                 *
                 * B12 a prouve que le vrai callback VBlank s'execute
                 * correctement (retour propre + 8003CE34 traverse),
                 * mais le startup reste dans la boucle interne de
                 * FUN_800401A4.
                 *
                 * On laisse d'abord la fonction faire son setup et au
                 * moins quatre vrais callbacks VBlank. Quand le thread
                 * principal est de nouveau dans le VSync de cette boucle,
                 * on restaure le SP d'entree et on reprend exactement au
                 * RA du JAL appelant (80012B48 sur notre build FR).
                 *
                 * Cela evite de sauter le setup de 401A4 tout en supprimant
                 * uniquement son attente infinie dans notre environnement.
                 */
                if (
                    !g_fast401_forced
                    && g_hit_401a4 != 0u
                    && g_sp_401a4 != 0u
                    && g_ra_401a4 != 0u
                    && g_irq_exec_ok >= 4u
                    && ((cpu->pc & 0x1FFFFFFFu) == 0x000746B8u)
                    && cpu->gpr[31] == 0x80012D48u
                )
                {
                    cpu->pc = g_ra_401a4;
                    cpu->gpr[29] = g_sp_401a4;
                    cpu->gpr[31] = g_ra_401a4;
                    cpu->gpr[2] = 0u;
                    cpu->gpr[0] = 0u;

                    /* Annuler l'attente VSync HLE devenue obsolete. */
                    g_vsync_wait_active = 0;
                    g_vsync_wait_until_frame = 0;

                    g_fast401_forced = 1u;
                    g_fast401_frame = frame;
                }

                /*
                 * B32 : si FUN_80043E3C revient d'elle-meme apres que
                 * le pont CD a effectivement livre des secteurs, noter
                 * ce retour naturel. On ne saute plus sa sequence
                 * d'initialisation.
                 */
                if (
                    !g_b32_43e_returned
                    && g_b32_getsec_ok != 0u
                    && g_ra_43e3c != 0u
                    && cpu->pc == g_ra_43e3c
                )
                {
                    g_b32_43e_returned = 1u;
                    g_b32_43e_return_frame = frame;
                }


                /*
                 * =====================================================
                 * B14 FASTBOOT 43E3C
                 * =====================================================
                 *
                 * B13 a prouve que le retour force de 401A4 nous fait
                 * bien entrer dans FUN_80043E3C. Le nouveau verrou est
                 * son attente de chargement asynchrone : 80013700 est
                 * atteint, mais aucun secteur CD n'est jamais transfere.
                 *
                 * On ne saute pas 43E3C a son entree. On attend qu'elle
                 * ait initialise sa requete et soit effectivement entree
                 * dans 80013700, puis on restaure le contexte d'entree
                 * de 43E3C et on reprend au vrai RA du startup.
                 *
                 * C'est volontairement un FASTBOOT de bring-up : le but
                 * est d'atteindre 8002DF60 et de provoquer enfin les
                 * premieres commandes graphiques utiles du jeu.
                 */
                if (
                    !g_fast43e_forced
                    && !g_b32_43e_returned
                    && g_fast401_forced
                    && g_hit_intro_init != 0u
                    && g_hit_load_wait != 0u
                    && g_ra_43e3c != 0u
                    && g_sp_43e3c != 0u
                    && g_irq_exec_ok >= 8u
                    /*
                     * B32 laisse maintenant la vraie requete CD se
                     * terminer. L'ancien fastboot n'est conserve qu'en
                     * filet de securite si le bridge n'a jamais reussi
                     * a fournir un secteur apres plusieurs secondes.
                     */
                    && g_b32_getsec_ok == 0u
                    && frame >= (g_fast401_frame + 300u)
                )
                {
                    cpu->pc = g_ra_43e3c;
                    cpu->gpr[29] = g_sp_43e3c;
                    cpu->gpr[31] = g_ra_43e3c;
                    cpu->gpr[2] = 0u;
                    cpu->gpr[0] = 0u;

                    /* Sortir proprement de toute attente HLE en cours. */
                    g_vsync_wait_active = 0;
                    g_vsync_wait_until_frame = 0;

                    g_fast43e_forced = 1u;
                    g_fast43e_frame = frame;
                }

                /*
                 * =====================================================
                 * B15 DIRECT MAIN STATE MACHINE
                 * =====================================================
                 *
                 * B14 a enfin fait apparaitre de vraies commandes DRAW
                 * et COPY GPU, mais le startup n'appelle toujours pas
                 * naturellement 8002DF60. On cesse d'attendre : apres
                 * 43E3C, on initialise le flag attendu par le startup et
                 * on pilote directement la vraie fonction 8002DF60.
                 */
                if (
                    !g_direct2df_active
                    &&
                    (
                        (
                            g_fast43e_forced
                            && frame >= (g_fast43e_frame + 2u)
                        )
                        ||
                        (
                            /*
                             * En chemin naturel, laisser le startup
                             * poursuivre seul. Direct-2DF ne redevient
                             * qu'un fallback si 8002DF60 n'est toujours
                             * jamais atteint deux secondes plus tard.
                             */
                            g_b32_43e_returned
                            && g_hit_main_loop == 0u
                            && frame >= (g_b32_43e_return_frame + 120u)
                        )
                    )
                )
                {
                    fm_memory_write_byte(
                        0x8009C60Du,
                        8u
                    );

                    g_direct2df_active = 1u;
                    g_direct2df_start_frame = frame;

                    /*
                     * Forcer le premier scheduling a la frame suivante.
                     */
                    cpu->pc = g_direct2df_sentinel;
                    cpu->gpr[31] = g_direct2df_sentinel;
                    cpu->gpr[0] = 0u;

                    g_vsync_wait_active = 0;
                    g_vsync_wait_until_frame = 0;
                }
            }
        }


        /*
         * Observer l'état réel du jeu.
         *
         * On ne force plus la fin STR ici : la capture précédente
         * a montré que DAT_8009C818 vaut encore zéro, donc le boot
         * n'a même pas atteint l'initialisation du lecteur vidéo.
         */
        if (memory_status == 0)
        {
            fm_service_fade_bridge();

            fm_update_game_state_debug();

            /*
             * Des que le vrai boot atteint le lecteur STR, sauter
             * uniquement la premiere video pour viser directement
             * l'ecran titre/menu et obtenir une image jouable.
             */
            fm_try_force_intro_stream_end(
                game_running
            );
        }


        /*
         * ====================================================
         * B106 - PRESENT TOP ONLY
         * ====================================================
         *
         * consoleInit(GFX_BOTTOM) met l'ecran bas en simple-buffer.
         * Il n'a donc aucune raison d'etre flush + presente a chaque
         * frame de jeu. L'ancien gfxFlushBuffers()/gfxSwapBuffers()
         * traitait TOP + BOTTOM systematiquement.
         *
         * On ne flush/presente maintenant que le framebuffer TOP.
         * Les printf de la console continuent a flush le bottom quand
         * le texte change.
         */
        g_b106_pre_gfx_ms =
            (uint32_t)(
                osGetTime()
                -
                b105_loop_start_ms
            );

        {
            uint64_t b106_gfx_start_ms =
                osGetTime();

            if (b131_presented_this_loop)
            {
                uint8_t *top_fb =
                    gfxGetFramebuffer(
                        GFX_TOP,
                        GFX_LEFT,
                        NULL,
                        NULL
                    );

                unsigned top_bpp =
                    gspGetBytesPerPixel(
                        gfxGetScreenFormat(
                            GFX_TOP
                        )
                    );

                GSPGPU_FlushDataCache(
                    top_fb,
                    (u32)(
                        GSP_SCREEN_WIDTH
                        *
                        GSP_SCREEN_HEIGHT_TOP
                        *
                        top_bpp
                    )
                );

                gfxScreenSwapBuffers(
                    GFX_TOP,
                    false
                );

                ++g_b131_swap_count;
            }

            g_b106_gfx_ms =
                (uint32_t)(
                    osGetTime()
                    -
                    b106_gfx_start_ms
                );
        }

        g_b105_work_ms =
            (uint32_t)(
                osGetTime()
                -
                b105_loop_start_ms
            );

        {
            /*
             * B135.18:
             * If the guest work already took >= 16 ms, we have missed the
             * current 60 Hz budget. Do not idle until another VBlank; start
             * the next guest slice immediately.
             */
            if (g_b105_work_ms < 16u)
            {
                uint64_t b106_wait_start_ms =
                    osGetTime();

                gspWaitForVBlank();

                g_b106_wait_ms =
                    (uint32_t)(
                        osGetTime()
                        -
                        b106_wait_start_ms
                    );
            }
            else
            {
                g_b106_wait_ms = 0u;
                ++g_b13518_late_vblank_skips;
            }
        }

        g_b105_loop_ms =
            (uint32_t)(
                osGetTime()
                -
                b105_loop_start_ms
            );


        g_b110_loop_sum_ms +=
            g_b105_loop_ms;

        ++g_b110_loop_samples;

        if (g_b105_loop_ms > g_b110_loop_max_ms)
        {
            g_b110_loop_max_ms =
                g_b105_loop_ms;
        }

        if (g_b105_loop_ms > 20u)
        {
            ++g_b110_loop_over20;
        }

        if (g_b105_loop_ms > 33u)
        {
            ++g_b110_loop_over33;
        }
    }


    /*
     * ========================================================
     * Exit
     * ========================================================
     */

    fm_disc_close();

    free(vram);
    free(preview);
    free(composite);
    free(ram);

    gfxExit();

    return 0;
}
