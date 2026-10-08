static int reference_rect(
    uint8_t opcode,
    int x,
    int y,
    int w,
    int h,
    int u,
    int v,
    int clx,
    int cly,
    uint16_t texpage,
    uint32_t command,
    int raw_texture
)
{
    if (
        !g_vram
        ||
        sw_renderer_scale() != 1
        ||
        sw_wide_width() != 0
        ||
        sw_texture_filter() != 0
    )
    {
        ++g_b124_rect_fallbacks;
        return 0;
    }

    /*
     * First B124 intentionally targets only the measured hot family
     * 64h..67h (variable-size textured rectangle).
     */
    if ((opcode & 0xFCu) != 0x64u)
    {
        ++g_b124_rect_fallbacks;
        return 0;
    }

    ++g_b124_rect_hits;

#if FM_PERF_PROFILE
    g_b13543_last_x = x;
    g_b13543_last_y = y;
    g_b13543_last_w = w;
    g_b13543_last_h = h;
    g_b13543_last_off_x = g_offset_x;
    g_b13543_last_off_y = g_offset_y;
    g_b13543_last_area_x1 = g_draw_x1;
    g_b13543_last_area_y1 = g_draw_y1;
    g_b13543_last_area_x2 = g_draw_x2;
    g_b13543_last_area_y2 = g_draw_y2;
#endif

    if (w <= 0 || h <= 0)
    {
        return 1;
    }

    int x0 = x;
    int y0 = y;
    int x1 = x + w;
    int y1 = y + h;

    if (x0 < g_draw_x1) x0 = g_draw_x1;
    if (y0 < g_draw_y1) y0 = g_draw_y1;
    if (x1 > g_draw_x2 + 1) x1 = g_draw_x2 + 1;
    if (y1 > g_draw_y2 + 1) y1 = g_draw_y2 + 1;

    if (x0 < 0) x0 = 0;
    if (y0 < 0) y0 = 0;
    if (x1 > 1024) x1 = 1024;
    if (y1 > 512) y1 = 512;

    if (x0 >= x1 || y0 >= y1)
    {
#if FM_PERF_PROFILE
        ++g_b13543_rect_clip_rejects;
#endif
        return 1;
    }

    int mod_r =
        (command & 0xFFu)
        >>
        3;

    int mod_g =
        ((command >> 8) & 0xFFu)
        >>
        3;

    int mod_b =
        ((command >> 16) & 0xFFu)
        >>
        3;

    int semi =
        (opcode & 0x02u)
        !=
        0;

    int semi_mode =
        (texpage >> 5)
        &
        3u;

    g_b124_rect_pixels +=
        (uint64_t)(x1 - x0)
        *
        (uint64_t)(y1 - y0);

    B13512TexCtx texctx =
        b13512_texctx(
            clx,
            cly,
            texpage
        );

    for (int py = y0; py < y1; ++py)
    {
        int tv =
            (v + (py - y))
            &
            0xFF;

        uint16_t *dst =
            g_vram
            +
            (size_t)py * 1024u
            +
            (size_t)x0;

        int tu =
            (u + (x0 - x))
            &
            0xFF;

        for (int px = x0; px < x1; ++px, ++dst)
        {
            uint16_t texel =
                b13512_fetch_texel_ctx(
                    tu,
                    tv,
                    &texctx
                );

            tu =
                (tu + 1)
                &
                0xFF;

            ++g_b124_rect_texels;

            if (texel == 0u)
            {
                continue;
            }

#if FM_PERF_PROFILE
            ++g_b13543_rect_nonzero_texels;
#endif

            if (
                g_mask_check
                &&
                (*dst & 0x8000u)
            )
            {
                continue;
            }

            uint16_t color;

            if (raw_texture)
            {
                color =
                    texel
                    &
                    0x7FFFu;
            }
            else
            {
                int tr = (texel >> 0) & 31;
                int tg = (texel >> 5) & 31;
                int tb = (texel >> 10) & 31;

                int r = (tr * mod_r) >> 4;
                int g = (tg * mod_g) >> 4;
                int b = (tb * mod_b) >> 4;

                if (r > 31) r = 31;
                if (g > 31) g = 31;
                if (b > 31) b = 31;

                color =
                    (uint16_t)(
                        r
                        |
                        (g << 5)
                        |
                        (b << 10)
                    );
            }

            if (
                semi
                &&
                (texel & 0x8000u)
            )
            {
                color =
                    b124_blend(
                        *dst,
                        color,
                        semi_mode
                    );
            }

            if (g_mask_set)
            {
                color |=
                    0x8000u;
            }

            *dst =
                color;

#if FM_PERF_PROFILE
            ++g_b13543_rect_writes;
#endif
        }
    }

    return 1;
}



/*
 * ============================================================
 * B125 - fixed-point hot-quad rasterizers
 * ============================================================
 *
 * These paths intentionally target native 1x / nearest / no-wide mode only.
 * They replace per-pixel floating-point interpolation with 16.16 fixed-point
 * increments. The generic renderer remains the fallback for every other mode.
 */
