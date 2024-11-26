#ifndef DJUI_HUD_UTILS_H
#define DJUI_HUD_UTILS_H

enum HudUtilsResolution {
    RESOLUTION_DJUI,
    RESOLUTION_N64,
    RESOLUTION_COUNT,
};

enum HudUtilsFilter {
    FILTER_NEAREST,
    FILTER_LINEAR,
    FILTER_COUNT,
};

enum DjuiFontType {
    FONT_NORMAL,
    FONT_MENU,
    FONT_HUD,
    FONT_ALIASED,
    FONT_CUSTOM_HUD,
    FONT_RECOLOR_HUD,
    FONT_COUNT,
};

struct HudUtilsRotation {
    f32 rotation;
    f32 rotationDiff;
    f32 prevPivotX;
    f32 prevPivotY;
    f32 pivotX;
    f32 pivotY;
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

u8 djui_hud_get_resolution(void);
void djui_hud_set_resolution(enum HudUtilsResolution resolutionType);
u8 djui_hud_get_filter(void);
void djui_hud_set_filter(enum HudUtilsFilter filterType);
u8 djui_hud_get_font(void);
void djui_hud_set_font(s8 fontType);
struct DjuiColor* djui_hud_get_color(void);
void djui_hud_set_color(u8 r, u8 g, u8 b, u8 a);
void djui_hud_reset_color(void);
struct HudUtilsRotation* djui_hud_get_rotation(void);
void djui_hud_set_rotation(s16 rotation, f32 pivotX, f32 pivotY);
void djui_hud_set_rotation_interpolated(s32 prevRotation, f32 prevPivotX, f32 prevPivotY, s32 rotation, f32 pivotX, f32 pivotY);

u32 djui_hud_get_screen_width(void);
u32 djui_hud_get_screen_height(void);

f32 djui_hud_get_mouse_x(void);
f32 djui_hud_get_mouse_y(void);
f32 djui_hud_get_raw_mouse_x(void);
f32 djui_hud_get_raw_mouse_y(void);
void djui_hud_set_mouse_locked(bool locked);

f32 djui_hud_measure_text(const char* message);
void djui_hud_print_text(const char* message, f32 x, f32 y, f32 scale);
void djui_hud_print_text_interpolated(const char* message, f32 prevX, f32 prevY, f32 prevScale, f32 x, f32 y, f32 scale);
void djui_hud_render_texture(struct TextureInfo* texInfo, f32 x, f32 y, f32 scaleW, f32 scaleH);
void djui_hud_render_texture_raw(const u8* texture, u32 bitSize, u32 width, u32 height, f32 x, f32 y, f32 scaleW, f32 scaleH);
void djui_hud_render_texture_tile(struct TextureInfo* texInfo, f32 x, f32 y, f32 scaleW, f32 scaleH, u32 tileX, u32 tileY, u32 tileW, u32 tileH);
void djui_hud_render_texture_tile_raw(const u8* texture, u32 bitSize, u32 width, u32 height, f32 x, f32 y, f32 scaleW, f32 scaleH, u32 tileX, u32 tileY, u32 tileW, u32 tileH);
void djui_hud_render_texture_interpolated(struct TextureInfo* texInfo, f32 prevX, f32 prevY, f32 prevScaleW, f32 prevScaleH, f32 x, f32 y, f32 scaleW, f32 scaleH);
void djui_hud_render_texture_tile_interpolated(struct TextureInfo* texInfo, f32 prevX, f32 prevY, f32 prevScaleW, f32 prevScaleH, f32 x, f32 y, f32 scaleW, f32 scaleH, u32 tileX, u32 tileY, u32 tileW, u32 tileH);
void djui_hud_render_rect(f32 x, f32 y, f32 width, f32 height);
void djui_hud_render_rect_interpolated(f32 prevX, f32 prevY, f32 prevWidth, f32 prevHeight, f32 x, f32 y, f32 width, f32 height);

f32 get_current_fov();
f32 djui_hud_get_fov_coeff();
bool djui_hud_world_pos_to_screen_pos(Vec3f pos, Vec3f out);
bool djui_hud_is_pause_menu_created(void);

void djui_open_pause_menu(void);

#endif