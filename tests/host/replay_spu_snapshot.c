/* Private quickstates supply game code; no game bytes are stored in the repo.
 * Reuse the host dependencies and fail if a callback unexpectedly needs GPU/GTE.
 * This replays the native sound path, not the full Azahar game loop. */
#define main memory_test_main
#include "test_spu_dma4.c"
#undef main
#include <stdlib.h>
#include <time.h>

static int g_media_irq_active, g_b33_cb_active, g_cd_tick_active;
static int g_b34_ready_active, g_b35_finalizer_active;
static const uint32_t g_media_irq_sentinel = 0x8000FFD0u;
static uint64_t osGetTime(void) { return (uint64_t)clock() * 1000u / CLOCKS_PER_SEC; }
/* The BIOS timer registration/masking has its own host test. Here the
 * captured SEQ registration points to 4BBC4; retain real I_STAT/I_MASK. */
static int fm_runtime_take_timer_callback(uint32_t *callback) {
    if (!(fm_memory_i_stat() & fm_memory_i_mask() & 0x40u)) return 0;
    fm_memory_write_half(0x1F801070u, (uint16_t)~0x40u);
    *callback = 0x8004BBC4u; return 1;
}
static int fm_bios_try_hle(CPUState *cpu, uint32_t pc) {
    (void)cpu; (void)pc; assert(0); return 0;
}
#include "timer_irq_bridge.inc"

static void bind_cpu(CPUState *cpu)
{
    cpu->read_byte = fm_memory_read_byte; cpu->read_half = fm_memory_read_half;
    cpu->read_word = fm_memory_read_word; cpu->write_byte = fm_memory_write_byte;
    cpu->write_half = fm_memory_write_half; cpu->write_word = fm_memory_write_word;
}

static int run(CPUState *cpu, uint32_t sentinel, unsigned *blocks)
{
    *blocks = 0;
    while (cpu->pc != sentinel && ++*blocks <= 100000) {
        FMInterpResult r = fm_interp_run_block(cpu, 512);
        if (r.reason != FM_INTERP_BLOCK_DONE && r.reason != FM_INTERP_BUDGET)
            break;
    }
    if (cpu->pc == sentinel) return 1;
    fprintf(stderr, "No return: pc=%08X ra=%08X blocks=%u reverb=%08X\n",
        cpu->pc, cpu->gpr[31], *blocks, fm_memory_read_word(REVERB));
    return 0;
}

static int call(CPUState *cpu, uint32_t entry, unsigned *blocks)
{
    cpu->pc = entry; cpu->gpr[29] = 0x801FFF00; cpu->gpr[31] = 0x8000FFD0;
    if (!run(cpu, 0x8000FFD0, blocks)) return 0;
    return cpu->gpr[29] == 0x801FFF00;
}

int main(int argc, char **argv)
{
    if (argc != 3 || (strcmp(argv[2], "menu") && strcmp(argv[2], "sequence")
        && strcmp(argv[2], "timed-sequence") && strcmp(argv[2], "host-timer") && strcmp(argv[2], "host-once")))
        return 2;
    FILE *f = fopen(argv[1], "rb");
    if (!f) return 2;
    uint32_t prefix[13];
    if (fread(prefix, sizeof(prefix), 1, f) != 1 || prefix[0] != 0x35333142
        || (prefix[1] != 2 && prefix[1] != 3) || prefix[3] != sizeof(ram)
        || prefix[2] < 0xB48 || prefix[2] > 0x10000) { fclose(f); return 2; }
    CPUState cpu = {0};
    /* ARM EABI: uint64-aligned CPU state at 56; memory state at 0x280. */
    fseek(f, 56, SEEK_SET);
    if (fread(cpu.gpr, 4, 32, f) != 32 || fread(&cpu.pc, 4, 1, f) != 1
        || fread(&cpu.hi, 4, 1, f) != 1 || fread(&cpu.lo, 4, 1, f) != 1
        || fread(cpu.cop0, 4, 32, f) != 32) { fclose(f); return 2; }
    FMMemoryQuickState memory = {0};
    size_t memory_bytes = prefix[1] == 2 ? 1104 : sizeof(memory);
    fseek(f, 0x280, SEEK_SET);
    if (fread(&memory, 1, memory_bytes, f) != memory_bytes) { fclose(f); return 2; }
    fseek(f, prefix[2], SEEK_SET);
    if (fread(ram, 1, sizeof(ram), f) != sizeof(ram)) { fclose(f); return 2; }
    fclose(f);
    fm_memory_init(ram, sizeof(ram)); fm_memory_quick_load(&memory);
    fm_interp_bind_ram(ram, sizeof(ram)); bind_cpu(&cpu);
    unsigned blocks;
    if (!strcmp(argv[2], "menu")) {
        /* B136.24/25 snapshots were taken inside the active sound callback. */
        if (!run(&cpu, 0x8000FFD0, &blocks)) return 1;
        printf("Menu IRQ returned in %u blocks; reverb=%08X\n", blocks,
            fm_memory_read_word(REVERB));
        return 0;
    }
    uint32_t sound = fm_memory_read_word(0x8009C7D8);
    uint32_t engine = fm_memory_read_word(0x8009C7E0);
    if (sound < 0x80000000 || sound > 0x801FF000
        || engine < 0x80000000 || engine > 0x801FE000) return 2;
    int once = !strcmp(argv[2], "host-once");
    int host = once || !strcmp(argv[2], "host-timer");
    int timed = host || !strcmp(argv[2], "timed-sequence");
    unsigned irqs = 0;
    if (timed) {
        /* Enable timer2 at this controlled scheduler boundary. The capture
         * can have I_MASK=0 while the interrupted main thread is in DrawSync.
         * Timer mode/count/target remain the actual captured configuration. */
        fm_memory_write_half(0x1F801074u, fm_memory_i_mask() | 0x40u);
        fm_memory_write_half(0x1F801070u, (uint16_t)~0x40u);
    }
    for (unsigned tick = 1; tick <= (timed ? 30000u : 2000u); ++tick) {
        if (timed) {
            fm_memory_vblank_tick();
            if (!(fm_memory_i_stat() & fm_memory_i_mask() & 0x40u)) continue;
            if (!host) fm_memory_write_half(0x1F801070u, (uint16_t)~0x40u);
        }
        ++irqs;
        if (host) {
            CPUState interrupted = cpu;
            unsigned char stack_before[0x300];
            memcpy(stack_before, ram + 0x1FFD00, sizeof(stack_before));
            if (fm_execute_guest_timer_callback(&cpu) != 1) return 1;
            assert(!memcmp(&cpu, &interrupted, sizeof(cpu)));
            assert(!memcmp(stack_before, ram + 0x1FFD00, sizeof(stack_before)));
            if (irqs == 1) printf("Captured main PC %08X preserved; ISR completed in %u blocks\n",
                cpu.pc, g_seq_irq_blocks);
        } else if (!call(&cpu, 0x8004BBC4, &blocks)) return 1;
        if (once) {
            printf("Production ISR returned; serviced=%u skipped=%u max_ms=%u\n",
                g_seq_irq_serviced, g_seq_irq_skipped, g_seq_irq_max_ms);
            return 0;
        }
        CPUState service = cpu;
        if (!call(&service, 0x8004A3E0, &blocks)) return 1;
        if (service.gpr[2] != 3) continue;
        if (!call(&service, 0x800463F8, &blocks)) return 1;
        unsigned flags = fm_memory_read_half(engine + 0x40);
        printf("SEQ finished after %u IRQs; channel=%u sound_flags=%04X\n",
            irqs, fm_memory_read_byte(sound + 0x53C), flags);
        if (host) printf("Production delivery: %u serviced, %u skipped; main context preserved\n",
            g_seq_irq_serviced, g_seq_irq_skipped);
        if (timed) printf("Timer-paced replay: %u host intervals, %.2fs at 60 Hz\n",
            tick, tick / 60.0);
        return (flags & 0x80) ? 1 : 0;
    }
    fprintf(stderr, "SEQ did not finish within replay budget\n");
    return 1;
}
