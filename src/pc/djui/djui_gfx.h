#pragma once
#include "djui.h"
#include "djui_base.h"

#define DJUI_MTX_PUSH   1
#define DJUI_MTX_NOPUSH 2

extern const Gfx dl_djui_simple_rect[];
extern const Gfx dl_djui_img_begin[];
extern const Gfx dl_djui_img_end[];

void djui_gfx_displaylist_begin(void);
void djui_gfx_displaylist_end(void);

f32 djui_gfx_get_scale(void);

void djui_gfx_render_texture(const u8* texture, u32 w, u32 h, u32 bitSize, bool filter);
void djui_gfx_render_texture_tile(const u8* texture, u32 w, u32 h, u32 bitSize, u32 tileX, u32 tileY, u32 tileW, u32 tileH, bool filter, bool font);

void djui_gfx_position_translate(f32* x, f32* y);
void djui_gfx_scale_translate(f32* width, f32* height);
void djui_gfx_size_translate(f32* size);

bool djui_gfx_add_clipping_specific(struct DjuiBase* base, f32 dX, f32 dY, f32 dW, f32 dH);
bool djui_gfx_add_clipping(struct DjuiBase* base);