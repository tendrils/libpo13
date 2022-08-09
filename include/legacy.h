#ifndef _LEGACY_H
#define _LEGACY_H

#include "po13.h"

#include <stdint.h>
#include <stdbool.h>

#define LEGACY_CTX_MAX      16
#define LEGACY_CTX_DEFAULT  LEGACY_CTX_MAX

void legacy_demo();
void legacy_init();

void legacy_display_show_image(uint8_t *img);
void legacy_display_clear();

uint8_t legacy_context_new();
void legacy_context_set(uint8_t ctx_id);
void legacy_context_init(uint8_t ctx_id, uint8_t *buffer);
void legacy_context_update();

//  Draw API
void legacy_image_clear(uint8_t color);
void legacy_draw_text(struct po13_point2d origin,
                    const uint8_t *text, uint8_t font,
                    uint16_t color_fg, uint16_t color_bg);
void legacy_draw_rect(struct po13_point2d origin,
                      struct po13_point2d extent,
                      uint16_t color, uint8_t line_size, bool fill);
void legacy_draw_line(struct po13_point2d origin,
                      struct po13_point2d extent,
                      uint16_t color, uint8_t line_size, bool solid);
void legacy_draw_point(struct po13_point2d origin, uint16_t color,
                        uint8_t size, bool fill_around);
#endif
