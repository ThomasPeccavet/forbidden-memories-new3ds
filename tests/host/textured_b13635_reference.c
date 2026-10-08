/* Frozen production B136.35 raster, commit de6637c, for pixel comparison. */
static void reference_textured_triangle(
    int x0, int y0, int u0, int v0, uint32_t c0,
    int x1, int y1, int u1, int v1, uint32_t c1,
    int x2, int y2, int u2, int v2, uint32_t c2,
    int clx,
    int cly,
    uint16_t texpage,
    int raw_texture,
    int semi
)
{
#if FM_PERF_PROFILE
    ++g_b13534_tri_calls;

    uint64_t b13534_begin =
        g_b13534_sample_active
            ? svcGetSystemTick()
            : 0u;
#endif

#define B13511_SWAP_INT(a,b) do { int _t=(a); (a)=(b); (b)=_t; } while (0)
#define B13511_SWAP_U32(a,b) do { uint32_t _t=(a); (a)=(b); (b)=_t; } while (0)

    if (y0 > y1)
    {
        B13511_SWAP_INT(x0,x1); B13511_SWAP_INT(y0,y1);
        B13511_SWAP_INT(u0,u1); B13511_SWAP_INT(v0,v1);
        B13511_SWAP_U32(c0,c1);
    }

    if (y0 > y2)
    {
        B13511_SWAP_INT(x0,x2); B13511_SWAP_INT(y0,y2);
        B13511_SWAP_INT(u0,u2); B13511_SWAP_INT(v0,v2);
        B13511_SWAP_U32(c0,c2);
    }

    if (y1 > y2)
    {
        B13511_SWAP_INT(x1,x2); B13511_SWAP_INT(y1,y2);
        B13511_SWAP_INT(u1,u2); B13511_SWAP_INT(v1,v2);
        B13511_SWAP_U32(c1,c2);
    }

    int dy02 = y2 - y0;
    if (dy02 <= 0) return;

    int32_t det =
        (x1 - x0) * (y2 - y0)
        -
        (x2 - x0) * (y1 - y0);

    if (det == 0) return;

    int r0 = ((int)(c0 & 0xFFu)) >> 3;
    int g0 = ((int)((c0 >> 8) & 0xFFu)) >> 3;
    int b0 = ((int)((c0 >> 16) & 0xFFu)) >> 3;

    int r1 = ((int)(c1 & 0xFFu)) >> 3;
    int g1 = ((int)((c1 >> 8) & 0xFFu)) >> 3;
    int b1 = ((int)((c1 >> 16) & 0xFFu)) >> 3;

    int r2 = ((int)(c2 & 0xFFu)) >> 3;
    int g2 = ((int)((c2 >> 8) & 0xFFu)) >> 3;
    int b2 = ((int)((c2 >> 16) & 0xFFu)) >> 3;

    /*
     * One VFP division replaces the ten 64-bit software divisions used by
     * the UV + RGB plane gradients.
     */
    float inv_det_fp16 =
        65536.0f
        /
        (float)det;

#define B13513_NUM_X(a0,a1,a2) \
    (((int32_t)((a1)-(a0)) * (y2-y0)) - \
     ((int32_t)((a2)-(a0)) * (y1-y0)))

#define B13513_NUM_Y(a0,a1,a2) \
    (((int32_t)(x1-x0) * ((a2)-(a0))) - \
     ((int32_t)(x2-x0) * ((a1)-(a0))))

    int32_t du_dx = b13513_grad_fp16(B13513_NUM_X(u0,u1,u2), inv_det_fp16);
    int32_t du_dy = b13513_grad_fp16(B13513_NUM_Y(u0,u1,u2), inv_det_fp16);
    int32_t dv_dx = b13513_grad_fp16(B13513_NUM_X(v0,v1,v2), inv_det_fp16);
    int32_t dv_dy = b13513_grad_fp16(B13513_NUM_Y(v0,v1,v2), inv_det_fp16);

    int32_t dr_dx = b13513_grad_fp16(B13513_NUM_X(r0,r1,r2), inv_det_fp16);
    int32_t dr_dy = b13513_grad_fp16(B13513_NUM_Y(r0,r1,r2), inv_det_fp16);
    int32_t dg_dx = b13513_grad_fp16(B13513_NUM_X(g0,g1,g2), inv_det_fp16);
    int32_t dg_dy = b13513_grad_fp16(B13513_NUM_Y(g0,g1,g2), inv_det_fp16);
    int32_t db_dx = b13513_grad_fp16(B13513_NUM_X(b0,b1,b2), inv_det_fp16);
    int32_t db_dy = b13513_grad_fp16(B13513_NUM_Y(b0,b1,b2), inv_det_fp16);

#undef B13513_NUM_X
#undef B13513_NUM_Y

    int32_t dx_long = b13513_edge_fp16(x2-x0, dy02);
    int32_t dx_upper = b13513_edge_fp16(x1-x0, y1-y0);
    int32_t dx_lower = b13513_edge_fp16(x2-x1, y2-y1);

    int semi_mode = (texpage >> 5) & 3u;

    B13512TexCtx texctx =
        b13512_texctx(
            clx,
            cly,
            texpage
        );

    /*
     * B135.33 fast case: exact 34h semantics on the measured Palace path.
     * 34h is opaque + modulated, and the current native renderer normally
     * has no mask bits or texture window.  In that case all those branches
     * are invariant and can disappear from the pixel loop.
     */
    int b13533_fast =
        !raw_texture
        &&
        !semi
        &&
        !g_mask_set
        &&
        !g_mask_check
        &&
        (texctx.mask_x | texctx.mask_y) == 0u;

    uint16_t b13533_clut[256];

    if (b13533_fast && texctx.depth == 0u)
    {
        for (unsigned i = 0u; i < 16u; ++i)
        {
            b13533_clut[i] =
                g_vram[
                    ((unsigned)texctx.cly & 511u) * 1024u
                    +
                    (((unsigned)texctx.clx + i) & 1023u)
                ];
        }
    }
    else if (b13533_fast && texctx.depth == 1u)
    {
        for (unsigned i = 0u; i < 256u; ++i)
        {
            b13533_clut[i] =
                g_vram[
                    ((unsigned)texctx.cly & 511u) * 1024u
                    +
                    (((unsigned)texctx.clx + i) & 1023u)
                ];
        }
    }

    if (b13533_fast)
    {
        ++g_b13533_34_fast_hits;

#if FM_PERF_PROFILE
        unsigned d =
            texctx.depth < 2u
                ? texctx.depth
                : 2u;

        ++g_b13535_depth_hits[d];
#endif
    }

    /*
     * B135.37: accumulate debug pixel counters locally and publish once per
     * triangle.  The old path performed two 64-bit global read/modify/writes
     * on every scanline, which is disproportionately expensive for the ~900
     * tiny Palace triangles.
     */
    uint32_t b13537_pixels = 0u;
    uint32_t b13537_fast_pixels = 0u;

    int ys = y0;
    int ye = y2;
    if (ys < g_draw_y1) ys = g_draw_y1;
    if (ye > g_draw_y2 + 1) ye = g_draw_y2 + 1;
    if (ys < 0) ys = 0;
    if (ye > 512) ye = 512;

#if FM_PERF_PROFILE
    uint64_t b13534_raster_begin =
        g_b13534_sample_active
            ? svcGetSystemTick()
            : 0u;
#endif

    for (int y = ys; y < ye; ++y)
    {
        int32_t xl_fp = ((int32_t)x0 << 16) + dx_long * (y-y0);
        int32_t xs_fp =
            y < y1
                ? ((int32_t)x0 << 16) + dx_upper * (y-y0)
                : ((int32_t)x1 << 16) + dx_lower * (y-y1);

        int32_t left_fp = xl_fp < xs_fp ? xl_fp : xs_fp;
        int32_t right_fp = xl_fp < xs_fp ? xs_fp : xl_fp;

        int sx = left_fp >> 16;
        int ex = right_fp >> 16;

        if (sx < g_draw_x1) sx = g_draw_x1;
        if (ex > g_draw_x2 + 1) ex = g_draw_x2 + 1;
        if (sx < 0) sx = 0;
        if (ex > 1024) ex = 1024;
        if (sx >= ex) continue;

        int32_t u_fp =
            (int32_t)(((int64_t)u0 << 16) +
                      (int64_t)du_dx * (sx-x0) +
                      (int64_t)du_dy * (y-y0));
        int32_t v_fp =
            (int32_t)(((int64_t)v0 << 16) +
                      (int64_t)dv_dx * (sx-x0) +
                      (int64_t)dv_dy * (y-y0));

        int32_t r_fp =
            (int32_t)(((int64_t)r0 << 16) +
                      (int64_t)dr_dx * (sx-x0) +
                      (int64_t)dr_dy * (y-y0));
        int32_t g_fp =
            (int32_t)(((int64_t)g0 << 16) +
                      (int64_t)dg_dx * (sx-x0) +
                      (int64_t)dg_dy * (y-y0));
        int32_t b_fp =
            (int32_t)(((int64_t)b0 << 16) +
                      (int64_t)db_dx * (sx-x0) +
                      (int64_t)db_dy * (y-y0));

        uint16_t *dst =
            g_vram + (size_t)y * 1024u + (size_t)sx;

        uint32_t b13537_span =
            (uint32_t)(ex - sx);

        b13537_pixels +=
            b13537_span;

        if (b13533_fast)
        {
            b13537_fast_pixels +=
                b13537_span;

            int last_key = -1;
            uint16_t packed = 0u;

            for (int x = sx; x < ex; ++x, ++dst)
            {
                int tu = (u_fp >> 16) & 0xFF;
                int tv = (v_fp >> 16) & 0xFF;
                uint16_t texel;

                if (texctx.depth == 0u)
                {
                    int key =
                        (tv << 6)
                        |
                        (tu >> 2);

                    if (key != last_key)
                    {
                        packed =
                            g_vram[
                                (size_t)(texctx.tpy + tv) * 1024u
                                +
                                (size_t)((texctx.tpx + (tu >> 2)) & 1023)
                            ];

                        last_key =
                            key;
                    }

                    texel =
                        b13533_clut[
                            (packed >> ((tu & 3) * 4)) & 0x0F
                        ];
                }
                else if (texctx.depth == 1u)
                {
                    int key =
                        (tv << 7)
                        |
                        (tu >> 1);

                    if (key != last_key)
                    {
                        packed =
                            g_vram[
                                (size_t)(texctx.tpy + tv) * 1024u
                                +
                                (size_t)((texctx.tpx + (tu >> 1)) & 1023)
                            ];

                        last_key =
                            key;
                    }

                    texel =
                        b13533_clut[
                            (packed >> ((tu & 1) * 8)) & 0xFF
                        ];
                }
                else
                {
                    texel =
                        g_vram[
                            (size_t)(texctx.tpy + tv) * 1024u
                            +
                            (size_t)((texctx.tpx + tu) & 1023)
                        ];
                }

                if (texel != 0u)
                {
                    int mr = r_fp >> 16;
                    int mg = g_fp >> 16;
                    int mb = b_fp >> 16;

                    if ((unsigned)mr > 31u) mr = mr < 0 ? 0 : 31;
                    if ((unsigned)mg > 31u) mg = mg < 0 ? 0 : 31;
                    if ((unsigned)mb > 31u) mb = mb < 0 ? 0 : 31;

                    int rr =
                        (((int)(texel & 31u)) * mr) >> 4;

                    int gg =
                        (((int)((texel >> 5) & 31u)) * mg) >> 4;

                    int bb =
                        (((int)((texel >> 10) & 31u)) * mb) >> 4;

                    if (rr > 31) rr = 31;
                    if (gg > 31) gg = 31;
                    if (bb > 31) bb = 31;

                    *dst =
                        (uint16_t)(
                            rr
                            |
                            (gg << 5)
                            |
                            (bb << 10)
                        );
                }

                u_fp += du_dx;
                v_fp += dv_dx;
                r_fp += dr_dx;
                g_fp += dg_dx;
                b_fp += db_dx;
            }
        }
        else
        {
            for (int x = sx; x < ex; ++x, ++dst)
            {
                uint16_t texel =
                    b13512_fetch_texel_ctx(
                        (u_fp >> 16) & 0xFF,
                        (v_fp >> 16) & 0xFF,
                        &texctx
                    );

                int mr = r_fp >> 16;
                int mg = g_fp >> 16;
                int mb = b_fp >> 16;

                if (mr < 0) mr = 0; else if (mr > 31) mr = 31;
                if (mg < 0) mg = 0; else if (mg > 31) mg = 31;
                if (mb < 0) mb = 0; else if (mb > 31) mb = 31;

                b125_put_textured(
                    dst,
                    texel,
                    mr,
                    mg,
                    mb,
                    raw_texture,
                    semi,
                    semi_mode
                );

                u_fp += du_dx;
                v_fp += dv_dx;
                r_fp += dr_dx;
                g_fp += dg_dx;
                b_fp += db_dx;
            }
        }
    }

    g_b125_pixels +=
        (uint64_t)b13537_pixels;

    if (b13533_fast)
    {
        g_b13533_34_fast_pixels +=
            (uint64_t)b13537_fast_pixels;
    }

#if FM_PERF_PROFILE
    if (g_b13534_sample_active)
    {
        uint64_t b13534_end =
            svcGetSystemTick();

        g_b13534_setup_ticks +=
            b13534_raster_begin - b13534_begin;

        g_b13534_raster_ticks +=
            b13534_end - b13534_raster_begin;

        ++g_b13534_samples;
    }
#endif

#undef B13511_SWAP_INT
#undef B13511_SWAP_U32
}

