#ifndef _PO13_H
#define _PO13_H

#include <stdint.h>
#include <stdbool.h>

#define PO13_WIDTH      128
#define PO13_HEIGHT     64

#define PO13_BLACK      (uint16_t)0x0000
#define PO13_WHITE      (uint16_t)0xFFFF

#define PO13_FONT_8   0
#define PO13_FONT_12  1
#define PO13_FONT_16  2
#define PO13_FONT_20  3
#define PO13_FONT_24  4

#define PO13_POINT_1    1
#define PO13_POINT_2    2
#define PO13_POINT_3    3
#define PO13_POINT_4    4
#define PO13_POINT_5    5
#define PO13_POINT_6    6
#define PO13_POINT_7    7
#define PO13_POINT_8    8

struct po13_device {
    // device id
    // transport type
    // spi/i2c pins
    struct po13_ctx *ctx;
};

struct po13_ctx {
    uint8_t id;
    uint8_t *buffer;
    uint8_t point_size;
    uint16_t color_fg;
    uint16_t color_bg;
    struct po13_font *font;
};

struct po13_font {
    uint8_t id;
};

struct po13_point2d {
    uint16_t x;
    uint16_t y;
};

void po13_init();
void po13_demo();

struct po13_device *po13_device_default();
struct po13_device *po13_device_create();
struct po13_ctx *po13_context_create(uint16_t width, uint16_t height);

void po13_display_set_context(const struct po13_device *dev, struct po13_ctx *ctx);
void po13_display_update(const struct po13_device *dev);
void po13_display_clear(const struct po13_device *dev);

void po13_draw_clear(const struct po13_ctx *ctx);
void po13_draw_text(const struct po13_ctx *ctx,
                    const struct po13_point2d origin, const uint8_t *text);
void po13_draw_rect(const struct po13_ctx *ctx,
                    struct po13_point2d origin, struct po13_point2d extent, bool fill);
void po13_draw_line(const struct po13_ctx *ctx, struct po13_point2d origin, struct po13_point2d extent, bool solid);
void po13_draw_point(const struct po13_ctx *img, struct po13_point2d point, bool fill_around);

#endif