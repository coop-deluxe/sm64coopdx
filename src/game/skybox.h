#ifndef SKYBOX_H
#define SKYBOX_H

#include <PR/ultratypes.h>
#include <PR/gbi.h>

#define SKYBOX_TILES_X 5
#define SKYBOX_TILES_Y 3

extern s8 gReadOnlyBackground;
extern s8 gOverrideBackground;
extern Color gSkyboxColor;

extern Texture* gCustomSkyboxPtrList[];

Gfx *create_skybox_facing_camera(s8 player, s8 background, f32 fov,
                                 f32 posX, f32 posY, f32 posZ,
                                 f32 focX, f32 focY, f32 focZ);

#endif // SKYBOX_H
