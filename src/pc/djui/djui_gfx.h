#pragma once
#include "djui.h"
#include "djui_base.h"

#define DJUI_MTX_PUSH   1
#define DJUI_MTX_NOPUSH 2

extern const Gfx dl_djui_simple_rect[];
extern const Gfx dl_djui_ia_text_begin[];
extern const Gfx dl_djui_img_begin[];
extern const Gfx dl_djui_img_end[];

void djui_gfx_render_char(u8 c);
void djui_gfx_render_texture(const u8* texture, u16 w, u16 h);

void djui_gfx_position_translate(f32* x, f32* y);
void djui_gfx_scale_translate(f32* width, f32* height);
void djui_gfx_size_translate(f32* size);

bool djui_gfx_add_clipping_specific(struct DjuiBase* base, bool rotatedUV, f32 dX, f32 dY, f32 dW, f32 dH);
bool djui_gfx_add_clipping(struct DjuiBase* base);