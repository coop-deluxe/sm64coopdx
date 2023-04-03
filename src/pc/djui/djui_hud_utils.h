#ifndef DJUI_HUD_UTILS_H
#define DJUI_HUD_UTILS_H

enum HudUtilsResolution {
    RESOLUTION_DJUI,
    RESOLUTION_N64,
    RESOLUTION_COUNT,
};

enum DjuiFontType {
    FONT_NORMAL,
    FONT_MENU,
    FONT_HUD,
    FONT_TINY,
    FONT_COUNT,
};

struct GlobalTextures {
    struct TextureInfo camera;
    struct TextureInfo lakitu;
    struct TextureInfo no_camera;
    struct TextureInfo arrow_up;
    struct TextureInfo arrow_down;
    struct TextureInfo coin;
    struct TextureInfo star;
    struct TextureInfo apostrophe;
    struct TextureInfo double_quote;
    struct TextureInfo mario_head;
    struct TextureInfo luigi_head;
    struct TextureInfo toad_head;
    struct TextureInfo waluigi_head;
    struct TextureInfo wario_head;
};

extern struct GlobalTextures gGlobalTextures;
extern f32 gDjuiHudUtilsZ;
extern u8 gDjuiHudLockMouse;

void djui_hud_set_resolution(enum HudUtilsResolution resolutionType);
void djui_hud_set_font(enum DjuiFontType fontType);
void djui_hud_set_color(u8 r, u8 g, u8 b, u8 a);

u32 djui_hud_get_screen_width(void);
u32 djui_hud_get_screen_height(void);

f32 djui_hud_get_mouse_x(void);
f32 djui_hud_get_mouse_y(void);
f32 djui_hud_get_raw_mouse_x(void);
f32 djui_hud_get_raw_mouse_y(void);
void djui_hud_set_mouse_locked(bool locked);

f32 djui_hud_measure_text(const char* message);
void djui_hud_print_text(const char* message, float x, float y, float scale);
void djui_hud_render_texture(struct TextureInfo* texInfo, f32 x, f32 y, f32 scaleW, f32 scaleH);
void djui_hud_render_texture_raw(const u8* texture, u32 bitSize, u32 width, u32 height, f32 x, f32 y, f32 scaleW, f32 scaleH);
void djui_hud_render_texture_tile(struct TextureInfo* texInfo, f32 x, f32 y, f32 scaleW, f32 scaleH, u32 tileX, u32 tileY, u32 tileW, u32 tileH);
void djui_hud_render_texture_tile_raw(const u8* texture, u32 bitSize, u32 width, u32 height, f32 x, f32 y, f32 scaleW, f32 scaleH, u32 tileX, u32 tileY, u32 tileW, u32 tileH);
void djui_hud_render_texture_interpolated(struct TextureInfo* texInfo, f32 prevX, f32 prevY, f32 prevScaleW, f32 prevScaleH, f32 x, f32 y, f32 scaleW, f32 scaleH);
void djui_hud_render_texture_tile_interpolated(struct TextureInfo* texInfo, f32 prevX, f32 prevY, f32 prevScaleW, f32 prevScaleH, f32 x, f32 y, f32 scaleW, f32 scaleH, u32 tileX, u32 tileY, u32 tileW, u32 tileH);
void djui_hud_render_rect(f32 x, f32 y, f32 width, f32 height);
void djui_hud_render_rect_interpolated(f32 prevX, f32 prevY, f32 prevWidth, f32 prevHeight, f32 x, f32 y, f32 width, f32 height);

void djui_hud_world_pos_to_screen_pos(Vec3f pos, Vec3f out);

void djui_hud_set_render_behind_hud(bool enable);

bool djui_hud_is_pause_menu_created(void);

#endif