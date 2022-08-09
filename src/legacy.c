/*****************************************************************************
* | File      	:   OLED_1in3_test.c
* | Author      :   
* | Function    :   
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2021-03-16
* | Info        :
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
******************************************************************************/
#include "legacy.h"
#include "po13.h"

#include "stdlib.h"
#include "ImageData.h"
#include "EPD_Test.h"
#include "OLED_1in3_c.h"
#include "GUI_Paint.h"

#define N_FONTS 5

static PAINT ctx_default;
static uint8_t ctx_active;

// private function decls
PAINT *_context_obj_get(uint8_t id);

static uint8_t context_id_next = 0;
static PAINT *context_table[LEGACY_CTX_MAX + 1];
static sFONT *font_table[N_FONTS] = {
    &Font8,
    &Font12,
    &Font16,
    &Font20,
    &Font24
};

void legacy_init()
{
    DEV_Module_Init();
    OLED_1in3_C_Init();
    OLED_1in3_C_Clear();

    context_table[LEGACY_CTX_DEFAULT] = &ctx_default;
    ctx_active = LEGACY_CTX_DEFAULT;
}

void legacy_demo()
{
    OLED_1in3_C_test();
}

uint8_t legacy_context_new()
{
    uint8_t id = context_id_next++;
    context_table[id] = malloc(sizeof(PAINT));
    return id;
}
// save and switch active context to context_table[id]
void legacy_context_set(uint8_t id)
{
    if(ctx_active != id) {
        *context_table[ctx_active] = Paint;
        Paint = *context_table[id];
        ctx_active = id;
    }
}
// saves and restores active context because init routines
// require context to be active
void legacy_context_init(uint8_t ctx_id, uint8_t *buffer)
{
    uint8_t ctx_old = ctx_active;
    legacy_context_set(ctx_id);
    Paint_NewImage(buffer, OLED_1in3_C_WIDTH, OLED_1in3_C_HEIGHT, 0, WHITE);
    legacy_context_set(ctx_old);
}
void legacy_context_update()
{
    Paint = *context_table[ctx_active];
}

void legacy_display_show_image(uint8_t *img)
{
    OLED_1in3_C_Display(img);
}
void legacy_display_clear()
{
    OLED_1in3_C_Clear();
}

void legacy_image_clear(uint8_t color)
{
    Paint_Clear(color);
}

// legacy draw API
void legacy_draw_text(struct po13_point2d origin,
                    const uint8_t *text, uint8_t font,
                    uint16_t color_fg, uint16_t color_bg)
{
    Paint_DrawString_EN(origin.x, origin.y, text,
                        font_table[font], color_fg, color_bg);
}
void legacy_draw_rect(struct po13_point2d origin,
                      struct po13_point2d extent,
                      uint16_t color, uint8_t line_size, bool fill)
{
    Paint_DrawRectangle(origin.x, origin.y, extent.x, extent.y,
        color, line_size, fill? DRAW_FILL_FULL: DRAW_FILL_EMPTY);
}
void legacy_draw_line(struct po13_point2d origin,
                      struct po13_point2d extent,
                      uint16_t color, uint8_t line_size, bool solid)
{
    Paint_DrawLine(origin.x, origin.y,
                    extent.x, extent.y, color, line_size, solid);
}
void legacy_draw_point(struct po13_point2d origin, uint16_t color,
                        uint8_t size, bool fill_around)
{
    Paint_DrawPoint(origin.x, origin.y, color, size,
                    fill_around? DOT_FILL_AROUND: DOT_FILL_RIGHTUP);
}
