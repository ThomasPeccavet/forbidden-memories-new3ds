/* Frozen production B136.34 raster (03705ef), for pixel differential tests. */
static void reference_gouraud_triangle(
    int x0, int y0, uint16_t c0,
    int x1, int y1, uint16_t c1,
    int x2, int y2, uint16_t c2,
    int semi,
    int semi_mode
)
{
#define B128_SWAP_INT2(a,b) do { int _t=(a); (a)=(b); (b)=_t; } while (0)
#define B128_SWAP_U16(a,b) do { uint16_t _t=(a); (a)=(b); (b)=_t; } while (0)

    if (y0 > y1)
    {
        B128_SWAP_INT2(x0,x1);
        B128_SWAP_INT2(y0,y1);
        B128_SWAP_U16(c0,c1);
    }

    if (y0 > y2)
    {
        B128_SWAP_INT2(x0,x2);
        B128_SWAP_INT2(y0,y2);
        B128_SWAP_U16(c0,c2);
    }

    if (y1 > y2)
    {
        B128_SWAP_INT2(x1,x2);
        B128_SWAP_INT2(y1,y2);
        B128_SWAP_U16(c1,c2);
    }

    int dy02 = y2 - y0;

    if (dy02 <= 0)
    {
        return;
    }

    int64_t det =
        (int64_t)(x1 - x0) * (int64_t)(y2 - y0)
        -
        (int64_t)(x2 - x0) * (int64_t)(y1 - y0);

    if (det == 0)
    {
        return;
    }

    int r0 = (c0 >> 0) & 31;
    int g0 = (c0 >> 5) & 31;
    int b0 = (c0 >> 10) & 31;

    int r1 = (c1 >> 0) & 31;
    int g1 = (c1 >> 5) & 31;
    int b1 = (c1 >> 10) & 31;

    int r2 = (c2 >> 0) & 31;
    int g2 = (c2 >> 5) & 31;
    int b2 = (c2 >> 10) & 31;

#define B128_GRAD_X(a0,a1,a2) \
    ((int32_t)(((((int64_t)((a1)-(a0)) * (y2-y0)) - \
                  ((int64_t)((a2)-(a0)) * (y1-y0))) << 16) / det))

#define B128_GRAD_Y(a0,a1,a2) \
    ((int32_t)(((((int64_t)(x1-x0) * ((a2)-(a0))) - \
                  ((int64_t)(x2-x0) * ((a1)-(a0)))) << 16) / det))

    int32_t dr_dx = B128_GRAD_X(r0,r1,r2);
    int32_t dr_dy = B128_GRAD_Y(r0,r1,r2);
    int32_t dg_dx = B128_GRAD_X(g0,g1,g2);
    int32_t dg_dy = B128_GRAD_Y(g0,g1,g2);
    int32_t db_dx = B128_GRAD_X(b0,b1,b2);
    int32_t db_dy = B128_GRAD_Y(b0,b1,b2);

#undef B128_GRAD_X
#undef B128_GRAD_Y

    int32_t dx_long =
        b128_div_fp16(
            (int64_t)(x2 - x0),
            dy02
        );

    int32_t dx_upper =
        b128_div_fp16(
            (int64_t)(x1 - x0),
            y1 - y0
        );

    int32_t dx_lower =
        b128_div_fp16(
            (int64_t)(x2 - x1),
            y2 - y1
        );

    int ys = y0;
    int ye = y2;

    if (ys < g_draw_y1) ys = g_draw_y1;
    if (ye > g_draw_y2 + 1) ye = g_draw_y2 + 1;
    if (ys < 0) ys = 0;
    if (ye > 512) ye = 512;

    for (int y = ys; y < ye; ++y)
    {
        int32_t xl_fp =
            ((int32_t)x0 << 16)
            +
            dx_long * (y - y0);

        int32_t xs_fp;

        if (y < y1)
        {
            xs_fp =
                ((int32_t)x0 << 16)
                +
                dx_upper * (y - y0);
        }
        else
        {
            xs_fp =
                ((int32_t)x1 << 16)
                +
                dx_lower * (y - y1);
        }

        int32_t left_fp =
            xl_fp < xs_fp
                ? xl_fp
                : xs_fp;

        int32_t right_fp =
            xl_fp < xs_fp
                ? xs_fp
                : xl_fp;

        int sx = left_fp >> 16;
        int ex = right_fp >> 16;

        if (sx < g_draw_x1) sx = g_draw_x1;
        if (ex > g_draw_x2 + 1) ex = g_draw_x2 + 1;
        if (sx < 0) sx = 0;
        if (ex > 1024) ex = 1024;

        if (sx >= ex)
        {
            continue;
        }

        int32_t r_fp =
            (int32_t)(
                ((int64_t)r0 << 16)
                +
                (int64_t)dr_dx * (sx - x0)
                +
                (int64_t)dr_dy * (y - y0)
            );

        int32_t g_fp =
            (int32_t)(
                ((int64_t)g0 << 16)
                +
                (int64_t)dg_dx * (sx - x0)
                +
                (int64_t)dg_dy * (y - y0)
            );

        int32_t b_fp =
            (int32_t)(
                ((int64_t)b0 << 16)
                +
                (int64_t)db_dx * (sx - x0)
                +
                (int64_t)db_dy * (y - y0)
            );

        uint16_t *dst =
            g_vram
            +
            (size_t)y * 1024u
            +
            (size_t)sx;

        g_b125_pixels +=
            (uint64_t)(ex - sx);

        for (int x = sx; x < ex; ++x, ++dst)
        {
            int r = r_fp >> 16;
            int g = g_fp >> 16;
            int b = b_fp >> 16;

            if (r < 0) r = 0; else if (r > 31) r = 31;
            if (g < 0) g = 0; else if (g > 31) g = 31;
            if (b < 0) b = 0; else if (b > 31) b = 31;

            uint16_t color =
                (uint16_t)(
                    r
                    |
                    (g << 5)
                    |
                    (b << 10)
                );

            b125_put_gouraud(
                dst,
                color,
                semi,
                semi_mode
            );

            r_fp += dr_dx;
            g_fp += dg_dx;
            b_fp += db_dx;
        }
    }

#undef B128_SWAP_INT2
#undef B128_SWAP_U16
}

