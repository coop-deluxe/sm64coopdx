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
    FONT_SPECIAL,
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
extern bool gDjuiHudLockMouse;

/* |description|Gets the current DJUI HUD resolution|descriptionEnd| */
u8 djui_hud_get_resolution(void);
/* |description|Sets the current DJUI HUD resolution|descriptionEnd| */
void djui_hud_set_resolution(enum HudUtilsResolution resolutionType);
/* |description|Gets the current DJUI HUD texture filter|descriptionEnd| */
u8 djui_hud_get_filter(void);
/* |description|Sets the current DJUI HUD texture filter|descriptionEnd| */
void djui_hud_set_filter(enum HudUtilsFilter filterType);
/* |description|Gets the current DJUI HUD font|descriptionEnd| */
u8 djui_hud_get_font(void);
/* |description|Sets the current DJUI HUD font|descriptionEnd| */
void djui_hud_set_font(s8 fontType);
/* |description|Gets the current DJUI HUD color|descriptionEnd| */
struct DjuiColor* djui_hud_get_color(void);
/* |description|Sets the current DJUI HUD color|descriptionEnd| */
void djui_hud_set_color(u8 r, u8 g, u8 b, u8 a);
/* |description|Resets the current DJUI HUD color|descriptionEnd| */
void djui_hud_reset_color(void);
/* |description|Gets the current DJUI HUD rotation|descriptionEnd| */
struct HudUtilsRotation* djui_hud_get_rotation(void);
/* |description|Sets the current DJUI HUD rotation|descriptionEnd| */
void djui_hud_set_rotation(s16 rotation, f32 pivotX, f32 pivotY);
/* |description|Sets the current DJUI HUD rotation interpolated|descriptionEnd| */
void djui_hud_set_rotation_interpolated(s32 prevRotation, f32 prevPivotX, f32 prevPivotY, s32 rotation, f32 pivotX, f32 pivotY);

/* |description|Gets the screen width in the current DJUI HUD resolution|descriptionEnd| */
u32 djui_hud_get_screen_width(void);
/* |description|Gets the screen height in the current DJUI HUD resolution|descriptionEnd| */
u32 djui_hud_get_screen_height(void);

/* |description|Returns the x coordinate of the mouse relative to the window|descriptionEnd| */
f32 djui_hud_get_mouse_x(void);
/* |description|Returns the y coordinate of the mouse relative to the window|descriptionEnd| */
f32 djui_hud_get_mouse_y(void);
/* |description|Returns the x coordinate of the mouse relative to the screen|descriptionEnd| */
f32 djui_hud_get_raw_mouse_x(void);
/* |description|Returns the y coordinate of the mouse relative to the screen|descriptionEnd| */
f32 djui_hud_get_raw_mouse_y(void);
/* |description|Checks if the cursor is locked to the window|descriptionEnd| */
bool djui_hud_is_mouse_locked(void);
/* |description|Locks (or unlocks) the cursor to the window|descriptionEnd| */
void djui_hud_set_mouse_locked(bool locked);
/* |description|Returns the flags of the mouse buttons held down|descriptionEnd| */
u8 djui_hud_get_mouse_buttons_down(void);
/* |description|Returns the flags of the mouse buttons clicked|descriptionEnd| */
u8 djui_hud_get_mouse_buttons_pressed(void);
/* |description|Returns the flags of the mouse buttons released|descriptionEnd| */
u8 djui_hud_get_mouse_buttons_released(void);
/* |description|Returns the amount scrolled horizontally (-left/right+)|descriptionEnd| */
f32 djui_hud_get_mouse_scroll_x(void);
/* |description|Returns the amount scrolled vertically (-down/up+)|descriptionEnd| */
f32 djui_hud_get_mouse_scroll_y(void);
/* |description|Sets the viewport to the specified position and size, this will resize any subsequent DJUI graphics|descriptionEnd| */
void djui_hud_set_viewport(f32 x, f32 y, f32 width, f32 height);
/* |description|Resets the viewport to a fullscreen state|descriptionEnd| */
void djui_hud_reset_viewport(void);
/* |description|Sets the scissor rectangle to the specified position and size, this will cut off any subsequent DJUI graphics not within the rectangle|descriptionEnd| */
void djui_hud_set_scissor(f32 x, f32 y, f32 width, f32 height);
/* |description|Resets the scissor rectangle to a fullscreen state|descriptionEnd| */
void djui_hud_reset_scissor(void);

/* |description|Measures the length of `message` in the current font|descriptionEnd| */
f32 djui_hud_measure_text(const char* message);
/* |description|Prints DJUI HUD text onto the screen|descriptionEnd| */
void djui_hud_print_text(const char* message, f32 x, f32 y, f32 scale);
/* |description|Prints interpolated DJUI HUD text onto the screen|descriptionEnd| */
void djui_hud_print_text_interpolated(const char* message, f32 prevX, f32 prevY, f32 prevScale, f32 x, f32 y, f32 scale);
/* |description|Renders a DJUI HUD texture onto the screen|descriptionEnd| */
void djui_hud_render_texture(struct TextureInfo* texInfo, f32 x, f32 y, f32 scaleW, f32 scaleH);
/* |description|Renders a DJUI HUD texture tile onto the screen|descriptionEnd| */
void djui_hud_render_texture_tile(struct TextureInfo* texInfo, f32 x, f32 y, f32 scaleW, f32 scaleH, u32 tileX, u32 tileY, u32 tileW, u32 tileH);
/* |description|Renders an interpolated DJUI HUD texture onto the screen|descriptionEnd| */
void djui_hud_render_texture_interpolated(struct TextureInfo* texInfo, f32 prevX, f32 prevY, f32 prevScaleW, f32 prevScaleH, f32 x, f32 y, f32 scaleW, f32 scaleH);
/* |description|Renders an interpolated DJUI HUD texture tile onto the screen|descriptionEnd| */
void djui_hud_render_texture_tile_interpolated(struct TextureInfo* texInfo, f32 prevX, f32 prevY, f32 prevScaleW, f32 prevScaleH, f32 x, f32 y, f32 scaleW, f32 scaleH, u32 tileX, u32 tileY, u32 tileW, u32 tileH);
/* |description|Renders a DJUI HUD rect onto the screen|descriptionEnd| */
void djui_hud_render_rect(f32 x, f32 y, f32 width, f32 height);
/* |description|Renders an interpolated DJUI HUD rect onto the screen|descriptionEnd| */
void djui_hud_render_rect_interpolated(f32 prevX, f32 prevY, f32 prevWidth, f32 prevHeight, f32 x, f32 y, f32 width, f32 height);
/* |description|Renders an DJUI HUD line onto the screen|descriptionEnd| */
void djui_hud_render_line(f32 p1X, f32 p1Y, f32 p2X, f32 p2Y, f32 size);

/* |description|Gets the current camera FOV|descriptionEnd| */
f32 get_current_fov();
/* |description|Gets the camera FOV coefficient|descriptionEnd| */
f32 djui_hud_get_fov_coeff();
/* |description|Converts a world position to screen position|descriptionEnd| */
bool djui_hud_world_pos_to_screen_pos(Vec3f pos, OUT Vec3f out);
/* |description|Checks if the DJUI pause menu is created|descriptionEnd| */
bool djui_hud_is_pause_menu_created(void);

/* |description|Opens the DJUI pause menu|descriptionEnd| */
void djui_open_pause_menu(void);

#endif