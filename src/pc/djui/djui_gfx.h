#pragma once
#include "djui.h"
#include "djui_base.h"

#define DJUI_MTX_PUSH   1
#define DJUI_MTX_NOPUSH 2

extern const Gfx dl_djui_menu_rect[];
extern const Gfx dl_djui_simple_rect[];
extern const Gfx dl_djui_img_begin[];
extern const Gfx dl_djui_img_end[];

void djui_gfx_displaylist_begin(void);
void djui_gfx_displaylist_end(void);

enum CombinerSource {
    CS_0,
    CS_1,
    CS_TEXTURE,        // TEXEL0
    CS_COLOR,          // ENVIRONMENT
    CS_TEXT,           // PRIMITIVE
    CS_COMBINED,       // COMBINED
    CS_NOISE,          // NOISE
    CS_TEXTURE_ALPHA,  // TEXEL0_ALPHA
    CS_COLOR_ALPHA,    // ENV_ALPHA
    CS_TEXT_ALPHA,     // PRIMITIVE_ALPHA
    CS_COMBINED_ALPHA, // COMBINED_ALPHA
};

struct CombinerPart {
    enum CombinerSource a, b, c, d;
};

enum CombinerChannel {
    CC_COLOR,
    CC_ALPHA,
};

struct CombinerCycle {
    struct CombinerPart channel[2];
};

struct CombinerState {
    struct CombinerCycle cycle[2];
    u8 cycles;
};

extern struct CombinerState gCombinerState;
extern bool gCombinerUpdated;
extern bool gCombinerOverride;
void djui_gfx_update_combine_mode(enum CombinerSource mode);

f32 djui_gfx_get_scale(void);

void djui_gfx_render_texture(const Texture* texture, u32 w, u32 h, u8 fmt, u8 siz, bool filter);
void djui_gfx_render_texture_tile(const Texture* texture, u32 w, u32 h, u8 fmt, u8 siz, u32 tileX, u32 tileY, u32 tileW, u32 tileH, bool filter);

void djui_gfx_render_texture_font_begin();
void djui_gfx_render_texture_font(const Texture* texture, u32 w, u32 h, u8 fmt, u8 siz);
void djui_gfx_render_texture_font_end();

void djui_gfx_render_texture_tile_font_begin();
void djui_gfx_render_texture_tile_font(const Texture* texture, u32 w, u32 h, u8 fmt, u8 siz, u32 tileX, u32 tileY, u32 tileW, u32 tileH);
void djui_gfx_render_texture_tile_font_end();

void gfx_get_dimensions(u32* width, u32* height);

void djui_gfx_position_translate(f32* x, f32* y);
void djui_gfx_scale_translate(f32* width, f32* height);
void djui_gfx_size_translate(f32* size);

bool djui_gfx_add_clipping_specific(struct DjuiBase* base, f32 dX, f32 dY, f32 dW, f32 dH);
bool djui_gfx_add_clipping(struct DjuiBase* base);