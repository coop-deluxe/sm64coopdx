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

void render_hud_icon(Vtx *vtx, const u8 *texture, u32 fmt, u32 siz, s32 texW, s32 texH, s32 x, s32 y, s32 w, s32 h, s32 tileX, s32 tileY, s32 tileW, s32 tileH);

s16 get_hud_camera_status(void);
void set_hud_camera_status(s16 status);
void render_hud(void);

#endif // HUD_H
