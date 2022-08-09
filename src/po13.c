#include "po13.h"
#include "legacy.h"

#include <stdlib.h>

static struct po13_device *dev_default;

void po13_demo()
{
    legacy_demo();
}

void po13_init()
{
    legacy_init();

    dev_default = malloc(sizeof(struct po13_device));
    dev_default->ctx = malloc(sizeof(struct po13_ctx));
    dev_default->ctx->id = LEGACY_CTX_DEFAULT;
    dev_default->ctx->buffer = malloc((PO13_WIDTH * PO13_HEIGHT) / 8);
    legacy_context_init(LEGACY_CTX_DEFAULT, dev_default->ctx->buffer);
    dev_default->ctx->font = malloc(sizeof(struct po13_font));
    dev_default->ctx->font->id = PO13_FONT_12;
    dev_default->ctx->color_bg = PO13_BLACK;
    dev_default->ctx->color_fg = PO13_WHITE;
    legacy_image_clear(dev_default->ctx->color_bg);
}

struct po13_device *po13_device_default()
{
    return dev_default;
}
struct po13_device *po13_device_create()
{
    return dev_default;
}
struct po13_ctx *po13_context_create(uint16_t width, uint16_t height)
{
    uint16_t width_bytes = width %8 == 0? width /8: width /8 +1;
    uint16_t height_bytes = height %8 == 0? height /8: height /8 +1;
    struct po13_ctx *ctx = malloc(sizeof(struct po13_ctx));
    uint8_t *buffer = malloc(width_bytes * height_bytes);
    ctx->id = legacy_context_new();
    legacy_context_init(ctx->id, buffer);
    return ctx;
}

void po13_display_update(const struct po13_device *dev)
{
    legacy_context_set(dev->ctx->id );
    legacy_display_show_image(dev->ctx->buffer);
}
void po13_display_clear(const struct po13_device *dev)
{
    legacy_context_set(dev->ctx->id);
    legacy_display_clear();
}

void po13_draw_clear(const struct po13_ctx *ctx)
{
    legacy_image_clear(ctx->color_bg);
}
void po13_draw_text(const struct po13_ctx *ctx,
                    struct po13_point2d origin, const uint8_t *text)
{
    legacy_draw_text(origin, text, ctx->font->id, ctx->color_fg, ctx->color_bg);
}
void po13_draw_rect(const struct po13_ctx *ctx,
                    struct po13_point2d origin, struct po13_point2d extent, bool fill)
{
    legacy_draw_rect(origin, extent, ctx->color_fg, ctx->point_size, fill);
}
void po13_draw_line(const struct po13_ctx *ctx, struct po13_point2d origin, struct po13_point2d extent, bool solid)
{
    legacy_draw_line(origin, extent, ctx->color_fg, ctx->point_size, solid);
}
void po13_draw_point(const struct po13_ctx *ctx, struct po13_point2d origin, bool fill_around)
{
    legacy_context_set(ctx->id);
    legacy_draw_point(origin, ctx->color_fg,
                        ctx->point_size, fill_around);
}
