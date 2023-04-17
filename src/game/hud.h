#ifndef HUD_H
#define HUD_H

#include <PR/ultratypes.h>
#include <PR/gbi.h>

enum PowerMeterAnimation {
    POWER_METER_HIDDEN,
    POWER_METER_EMPHASIZED,
    POWER_METER_DEEMPHASIZING,
    POWER_METER_HIDING,
    POWER_METER_VISIBLE
};

enum CameraHUDLut {
    GLYPH_CAM_CAMERA,
    GLYPH_CAM_MARIO_HEAD,
    GLYPH_CAM_LAKITU_HEAD,
    GLYPH_CAM_FIXED,
    GLYPH_CAM_ARROW_UP,
    GLYPH_CAM_ARROW_DOWN,
    GLYPH_CAM_LUIGI_HEAD,
    GLYPH_CAM_TOAD_HEAD,
    GLYPH_CAM_WALUIGI_HEAD,
    GLYPH_CAM_WARIO_HEAD,
};

extern u8 gOverrideHideHud;

bool use_forced_4by3(void);
extern s32 gfx_dimensions_rect_from_left_edge(s32 v);
extern s32 gfx_dimensions_rect_from_right_edge(s32 v);

void set_hud_camera_status(s16 status);
void render_hud(void);

#endif // HUD_H
