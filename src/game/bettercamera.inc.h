#include "sm64.h"
#include "game/camera.h"
#include "game/level_update.h"
#include "game/print.h"
#include "engine/math_util.h"
#include "game/segment2.h"
#include "game/save_file.h"
#include "bettercamera.h"
#include "engine/surface_collision.h"
#include "pc/configfile.h"
#include "pc/controller/controller_mouse.h"
#include "pc/lua/utils/smlua_camera_utils.h"

#if defined(__MINGW32__) && !defined(__MINGW64_VERSION_MAJOR)
//quick and dirty fix for some older MinGW.org mingwrt
#else
#include <stdio.h>
#endif

#define NEWCAM_ACCEL                    10
#define NEWCAM_ACCEL_MAX                100
#define NEWCAM_MARIO_HEIGHT             125
#define NEWCAM_SAVED_MODE_NONE          0xFF
#define NEWCAM_DISTANCE_INC             250
#define NEWCAM_YAW_STEP                 0x3000
#define NEWCAM_TILT_CENTERING           3000
#define NEWCAM_TILT_LIMIT               0x3000
#define NEWCAM_COLLISION_CHECK_WIDTH    75
#define NEWCAM_COLLISION_CHECK_HEIGHT   90

static const f32 NEWCAM_DISTANCES[] = {
    750, 1250, 2000
};

static const u32 NEWCAM_NUM_DISTANCES = sizeof(NEWCAM_DISTANCES) / sizeof(*NEWCAM_DISTANCES);

NewCamera gNewCamera = {

    // Status
    .isActive               = false,
    .isSlide                = false,
    .pos                    = { 0, 0, 0 },
    .posTarget              = { 0, 0, 0 },
    .lookAt                 = { 0, 0, 0 },
    .distance               = 750, // NEWCAM_DISTANCES[0]
    .distanceTargetIndex    = 0,
    .yaw                    = 0,
    .yawTarget              = 0,
    .yawAccel               = 0,
    .tilt                   = 1500,
    .tiltAccel              = 0,
    .panX                   = 0,
    .panZ                   = 0,
    .framesSinceCButtons    = { 0, 0 },
    .centering              = false,
    .directionLocked        = false,
    .turnWait               = 0,
    .extStick               = { 0, 0 },
    .savedMode              = NEWCAM_SAVED_MODE_NONE,
    .savedDefMode           = NEWCAM_SAVED_MODE_NONE,

    // Settings
    .sensitivityX           = 0,
    .sensitivityY           = 0,
    .panLevel               = 0,
    .aggression             = 0,
    .deceleration           = 1,
    .invertX                = false,
    .invertY                = false,
    .isMouse                = false,
    .isAnalogue             = false,
    .useDPad                = false,
    .hasCollision           = true,
    .LCentering             = true,
};

extern bool gDjuiInMainMenu;

inline static s16 newcam_clamp(s16 value, s16 a, s16 b) {
    return min(max(a, value), b);
}

inline static s16 newcam_lengthdir_x(f32 length, s16 dir) {
    return (s16) (length * coss(dir));
}

inline static s16 newcam_lengthdir_y(f32 length, s16 dir) {
    return (s16) (length * sins(dir));
}

inline static s16 newcam_adjust_value(f32 var, f32 val, f32 limit) {
    if (val > 0.f) {
        return min(var + val, limit);
    }
    if (val < 0.f) {
        return max(var + val, limit);
    }
    return var;
}

inline static s32 newcam_ivrt(u8 axis) {
    return (
        axis == 0 ?
        (gNewCamera.invertX ? 1 : -1) :
        (gNewCamera.invertY ? -1 : 1)
    );
}

// This is called at every level initialisation.
static void newcam_init(struct Camera *c, u8 isSoftReset) {
    gNewCamera.tilt = 1500;
    gNewCamera.yaw = -c->yaw + 0x4000; // Mario and the camera's yaw have this offset between them.
    gNewCamera.isSlide = false;

    // This here will dictate what modes the camera will start in at the beginning of a level. Below are some examples.
    if (gCameraUseCourseSpecificSettings && !isSoftReset) {
        switch (gCurrLevelNum) {
            case LEVEL_BITDW: gNewCamera.yaw = 0x4000; gNewCamera.tilt = 4000; break;
            case LEVEL_BITFS: gNewCamera.yaw = 0x4000; gNewCamera.tilt = 4000; break;
            case LEVEL_BITS: gNewCamera.yaw = 0x4000; gNewCamera.tilt = 4000; break;
            case LEVEL_WF: gNewCamera.yaw = 0x4000; gNewCamera.tilt = 2000; break;
            case LEVEL_RR: gNewCamera.yaw = 0x6000; gNewCamera.tilt = 2000; break;
            case LEVEL_CCM: if (gCurrAreaIndex == 1) { gNewCamera.yaw = -0x4000; gNewCamera.tilt = 2000; } else { gNewCamera.isSlide = true; } break;
            case LEVEL_WDW: gNewCamera.yaw = 0x2000; gNewCamera.tilt = 3000; break;
            case LEVEL_PSS: gNewCamera.isSlide = true; break;
            case LEVEL_TTM: if (gCurrAreaIndex == 2) { gNewCamera.isSlide = true; } break;
        }
    }

    // clear these out when entering a new level to prevent "camera mode buffering"
    gNewCamera.savedDefMode = NEWCAM_SAVED_MODE_NONE;
    gNewCamera.savedMode = NEWCAM_SAVED_MODE_NONE;

    // this will be set in init_settings() if enabled
    gNewCamera.isActive = false;
}

static void newcam_toggle(bool enabled) {

    // force-disable if a demo is being played
    if (gCurrDemoInput) {
        enabled = false;
    }

    if (enabled && !gNewCamera.isActive) {
        gNewCamera.isActive = true;
        gNewCamera.savedMode = gLakituState.mode;
        gNewCamera.savedDefMode = gLakituState.defMode;
        gLakituState.mode = CAMERA_MODE_NEWCAM;
        gLakituState.defMode = CAMERA_MODE_NEWCAM;
    } else if (!enabled && gNewCamera.isActive) {
        if (gNewCamera.savedMode != NEWCAM_SAVED_MODE_NONE) {
            gLakituState.defMode = gNewCamera.savedDefMode;
            gLakituState.mode = gNewCamera.savedMode;
            gNewCamera.savedDefMode = NEWCAM_SAVED_MODE_NONE;
            gNewCamera.savedMode = NEWCAM_SAVED_MODE_NONE;
        }
        gNewCamera.isActive = false;
    }
}

// These are the default settings for Puppycam. You may change them to change how they'll be set for first timers.
void newcam_init_settings(void) {
    gNewCamera.sensitivityX = newcam_clamp(camera_config_get_x_sensitivity(), 1, 100) * 5;
    gNewCamera.sensitivityY = newcam_clamp(camera_config_get_y_sensitivity(), 1, 100) * 5;
    gNewCamera.panLevel     = newcam_clamp(camera_config_get_pan_level(), 0, 100);
    gNewCamera.aggression   = newcam_clamp(camera_config_get_aggression(), 0, 100);
    gNewCamera.deceleration = camera_config_get_deceleration();
    gNewCamera.invertX      = camera_config_is_x_inverted();
    gNewCamera.invertY      = camera_config_is_y_inverted();
    gNewCamera.isMouse      = camera_config_is_mouse_look_enabled();
    gNewCamera.isAnalogue   = camera_config_is_analog_cam_enabled();
    gNewCamera.useDPad      = camera_config_is_dpad_enabled();
    gNewCamera.hasCollision = camera_config_is_collision_enabled();
    gNewCamera.LCentering   = camera_config_get_centering();

    // setup main menu camera
    if (gDjuiInMainMenu) {
        gNewCamera.tilt = 5;
    }

    newcam_toggle(camera_config_is_free_cam_enabled() || gDjuiInMainMenu);
}

static void newcam_rotate_button(void) {

    // Standard camera movement
    // Buzz if the camera can't move due to being locked
    if (gPlayer1Controller->buttonPressed & (L_CBUTTONS | R_CBUTTONS) && gNewCamera.directionLocked) {
        play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
    }

    if (!gNewCamera.isAnalogue) {

        // Yaw (C<, C>)
        if ((gPlayer1Controller->buttonDown & L_CBUTTONS)) {
            gNewCamera.yawAccel = newcam_adjust_value(gNewCamera.yawAccel, -NEWCAM_ACCEL, -NEWCAM_ACCEL_MAX);
        } else if ((gPlayer1Controller->buttonDown & R_CBUTTONS)) {
            gNewCamera.yawAccel = newcam_adjust_value(gNewCamera.yawAccel, NEWCAM_ACCEL, NEWCAM_ACCEL_MAX);
        } else {
            gNewCamera.yawAccel -= (gNewCamera.yawAccel * (gNewCamera.deceleration / NEWCAM_ACCEL_MAX));
        }

        // Tilt (C^, Cv)
        if (gPlayer1Controller->buttonDown & U_CBUTTONS) {
            gNewCamera.tiltAccel = newcam_adjust_value(gNewCamera.tiltAccel, NEWCAM_ACCEL, NEWCAM_ACCEL_MAX);
        } else if (gPlayer1Controller->buttonDown & D_CBUTTONS) {
            gNewCamera.tiltAccel = newcam_adjust_value(gNewCamera.tiltAccel, -NEWCAM_ACCEL, -NEWCAM_ACCEL_MAX);
        } else {
            gNewCamera.tiltAccel -= (gNewCamera.tiltAccel * (gNewCamera.deceleration / NEWCAM_ACCEL_MAX));
        }

        // Double-tap the C-buttons to quickly rotate the camera
        gNewCamera.framesSinceCButtons[0]++;
        gNewCamera.framesSinceCButtons[1]++;
        if (!gNewCamera.directionLocked) {
            if (gPlayer1Controller->buttonPressed & L_CBUTTONS) {
                if (gNewCamera.framesSinceCButtons[0] < 6) {
                    gNewCamera.yawTarget = gNewCamera.yaw + (newcam_ivrt(0) * NEWCAM_YAW_STEP);
                    gNewCamera.centering = true;
                    play_sound(SOUND_MENU_CAMERA_TURN, gGlobalSoundSource);
                }
                gNewCamera.framesSinceCButtons[0] = 0;
            }
            if (gPlayer1Controller->buttonPressed & R_CBUTTONS) {
                if (gNewCamera.framesSinceCButtons[1] < 6) {
                    gNewCamera.yawTarget = gNewCamera.yaw - (newcam_ivrt(0) * NEWCAM_YAW_STEP);
                    gNewCamera.centering = true;
                    play_sound(SOUND_MENU_CAMERA_TURN, gGlobalSoundSource);
                }
                gNewCamera.framesSinceCButtons[1] = 0;
            }
        }
    }

    // Analogue camera
    // The joystick values cap at 80, so divide by 8 to get the same net result at maximum turn as the button
    else {

        // Yaw
        if (ABS(gNewCamera.extStick[0]) > 20) {
            gNewCamera.yawAccel = newcam_adjust_value(gNewCamera.yawAccel, gNewCamera.extStick[0] * 0.125f, gNewCamera.extStick[0] * 1.25f);
        } else {
            gNewCamera.yawAccel -= (gNewCamera.yawAccel * (gNewCamera.deceleration / 100));
        }

        // Tilt
        if (ABS(gNewCamera.extStick[1]) > 20) {
            gNewCamera.tiltAccel = newcam_adjust_value(gNewCamera.tiltAccel, gNewCamera.extStick[1] * 0.125f, gNewCamera.extStick[1] * 1.25f);
        } else {
            gNewCamera.tiltAccel -= (gNewCamera.tiltAccel* (gNewCamera.deceleration / 100));
        }
    }

    // Mouse control
    if (gNewCamera.isMouse && !gDjuiInMainMenu && !gDjuiChatBoxFocus && !gDjuiConsoleFocus) {
        if (!gNewCamera.useDPad || !gNewCamera.directionLocked) {
            gNewCamera.yaw += newcam_ivrt(0) * mouse_x * 16.f * (gNewCamera.sensitivityX / 250.f);
        }
        gNewCamera.tilt += newcam_ivrt(1) * mouse_y * 16.f * (gNewCamera.sensitivityY / 250.f);
    }

    // Dpad behaviors
    if (gNewCamera.useDPad) {

        // Make dpad up head to the nearest cardinal direction
        if (gPlayer1Controller->buttonDown & U_JPAD) {
            gNewCamera.yaw = snap_to_45_degrees(gNewCamera.yaw);
            gNewCamera.yawAccel = snap_to_45_degrees(gNewCamera.yawAccel);
        }

        // Make dpad left/right increment 45 degrees
        else if (gPlayer1Controller->buttonPressed & L_JPAD) {
            gNewCamera.yaw += newcam_ivrt(0) * DEGREES(45);
            play_sound(SOUND_MENU_CAMERA_TURN, gGlobalSoundSource);
        } else if (gPlayer1Controller->buttonPressed & R_JPAD) {
            gNewCamera.yaw -= newcam_ivrt(0) * DEGREES(45);
            play_sound(SOUND_MENU_CAMERA_TURN, gGlobalSoundSource);
        }

        // Make dpad down lock the current camera direction
        else if (gPlayer1Controller->buttonPressed & D_JPAD) {
            gNewCamera.directionLocked = !gNewCamera.directionLocked;
        }
    }

    if (gNewCamera.useDPad && gNewCamera.directionLocked) {
        gNewCamera.yawAccel = 0;
    }
}

static f32 newcam_get_distance_target() {
    gNewCamera.distanceTargetIndex = newcam_clamp(gNewCamera.distanceTargetIndex, 0, NEWCAM_NUM_DISTANCES - 1);
    return NEWCAM_DISTANCES[gNewCamera.distanceTargetIndex];
}

static void newcam_zoom_button(void) {
    if (gDjuiInMainMenu) {
        gNewCamera.distance = NEWCAM_DISTANCES[0];
        gNewCamera.distanceTargetIndex = 0;
        return;
    }

    f32 distanceTarget = newcam_get_distance_target();

    // Smoothly move the camera to the new spot.
    if (gNewCamera.distance > distanceTarget) {
        gNewCamera.distance = max(gNewCamera.distance - NEWCAM_DISTANCE_INC, distanceTarget);
    }
    if (gNewCamera.distance < distanceTarget) {
        gNewCamera.distance = min(gNewCamera.distance + NEWCAM_DISTANCE_INC, distanceTarget);
    }

    // When you press L, set the flag for centering the camera. Afterwards, start setting the yaw to the Player's yaw at the time.
    if (gNewCamera.LCentering && (gPlayer1Controller->buttonDown & L_TRIG)) {
        gNewCamera.yawTarget = -gMarioState->faceAngle[1] - 0x4000;
        gNewCamera.centering = true;
    }

    // Each time the player presses R, but NOT L the camera zooms out more, until it hits the limit and resets back to close view.
    else if (gPlayer1Controller->buttonPressed & R_TRIG) {
        play_sound(SOUND_MENU_CLICK_CHANGE_VIEW, gGlobalSoundSource);
        gNewCamera.distanceTargetIndex = (gNewCamera.distanceTargetIndex + 1) % NEWCAM_NUM_DISTANCES;
    }

    if (gNewCamera.centering) {
        gNewCamera.yaw = approach_s16_symmetric(gNewCamera.yaw, gNewCamera.yawTarget, 0x800);
        if (gNewCamera.yaw == gNewCamera.yawTarget) {
            gNewCamera.centering = false;
        }
    } else {
        gNewCamera.yawTarget = gNewCamera.yaw;
    }
}

static void newcam_update_values(void) {
    bool centering = false;
    bool ycentering = true;

    // Update yaw and tilt
    gNewCamera.yaw -= gNewCamera.yawAccel * newcam_ivrt(0) * (gNewCamera.sensitivityX / 10);
    gNewCamera.tilt = newcam_clamp(gNewCamera.tilt + gNewCamera.tiltAccel * newcam_ivrt(1) * (gNewCamera.sensitivityY / 10), -NEWCAM_TILT_LIMIT, +NEWCAM_TILT_LIMIT);

    // 10 frames after landing, progressively center the camera behind Mario when he's moving
    // This effect can be negated by setting `aggression` to 0
    if (gNewCamera.turnWait > 0 && gMarioState->vel[1] == 0) {
        gNewCamera.turnWait--;
    } else if (gMarioState->intendedMag > 0 && gMarioState->vel[1] == 0) {
        gNewCamera.yaw = approach_s16_symmetric(gNewCamera.yaw, -gMarioState->faceAngle[1] - 0x4000, ((gNewCamera.aggression * (ABS(gPlayer1Controller->rawStickX / 10.f))) * (gMarioState->forwardVel / 32.f)));
    } else {
        gNewCamera.turnWait = 10;
    }

    // During slide actions in slide levels, force centering
    if (gNewCamera.isSlide && (
        gMarioState->action == ACT_BUTT_SLIDE ||
        gMarioState->action == ACT_STOMACH_SLIDE ||
        gMarioState->action == ACT_HOLD_BUTT_SLIDE ||
        gMarioState->action == ACT_HOLD_STOMACH_SLIDE)
    ) {
        centering = (gMarioState->forwardVel > 8);
        ycentering = false;
    }

    // Force centering when flying
    if ((gMarioState->action & ACT_FLAG_FLYING) == ACT_FLAG_FLYING) {
        centering = true;
    }

    // Force centering when changing action
    // Place the camera behind Mario during the ACT_SHOT_FROM_CANNON action
    static u32 sLastAction = 0;
    static bool sForceCentering = false;
    if (sLastAction != gMarioState->action) {
        sLastAction = gMarioState->action;
        sForceCentering = true;
        switch (gMarioState->action) {
            case ACT_SHOT_FROM_CANNON:
                gNewCamera.yaw = -gMarioState->faceAngle[1] - 0x4000;
                break;
        }
    }

    // WTF is this
    if (centering) {
        if (fabs(gNewCamera.yawAccel) > 32 || fabs(gNewCamera.tiltAccel) > 32) {
            sForceCentering = false;
        }
        if (!sForceCentering) {
            centering = false;
        }
    }

    // Force centering during non-still swimming actions
    if (gMarioState->action & ACT_FLAG_SWIMMING && gMarioState->forwardVel > 2) {
        centering = true;
    }

    if (centering) {
        gNewCamera.yaw = approach_s16_symmetric(gNewCamera.yaw, -gMarioState->faceAngle[1] - 0x4000, gMarioState->forwardVel * 128);
        if (gMarioState->forwardVel > 1 && ycentering) {
            gNewCamera.tilt = approach_s16_symmetric(gNewCamera.tilt, (-gMarioState->faceAngle[0] * 0.8f) + NEWCAM_TILT_CENTERING, gMarioState->forwardVel * 32);
        } else {
            gNewCamera.tilt = approach_s16_symmetric(gNewCamera.tilt, NEWCAM_TILT_CENTERING, 32);
        }
    }
}

static void newcam_collision(void) {

    // check if we can see player
    Vec3f up = { 0, 1, 0 };
    Vec3f mainRay = {
        gNewCamera.pos[0] - gNewCamera.lookAt[0],
        gNewCamera.pos[1] - gNewCamera.lookAt[1],
        gNewCamera.pos[2] - gNewCamera.lookAt[2],
    };
    Vec3f sideway;
    vec3f_normalize(mainRay);
    vec3f_cross(sideway, mainRay, up);

    // Checks collision with left, up and right direction vectors
    bool allhit = true;
    for (s32 i = 0; i != 3; ++i) {
        f32 x = (f32) (-1 + i); // -1, 0, 1
        f32 y = (f32) (i % 2);  //  0, 1, 0
        Vec3f offset = {
            sideway[0] * x * NEWCAM_COLLISION_CHECK_WIDTH,
            -NEWCAM_COLLISION_CHECK_HEIGHT / 2 + y * NEWCAM_COLLISION_CHECK_HEIGHT,
            sideway[2] * x * NEWCAM_COLLISION_CHECK_WIDTH,
        };

        if (x != 0) {
            struct Surface *surf = NULL;
            Vec3f hitpos;
            Vec3f move = {
                offset[0] * 1.2f,
                offset[1],
                offset[2] * 1.2f,
            };
            find_surface_on_ray(gNewCamera.posTarget, move, &surf, hitpos, 3.f);
            vec3f_copy(offset, hitpos);
            vec3f_sub(offset, gNewCamera.posTarget);
            if (surf) {
                offset[0] = 0;
                offset[2] = 0;
            }
        }

        Vec3f camray = {
            gNewCamera.pos[0] - gNewCamera.lookAt[0] - offset[0],
            gNewCamera.pos[1] - gNewCamera.lookAt[1] - offset[1],
            gNewCamera.pos[2] - gNewCamera.lookAt[2] - offset[2],
        };

        Vec3f camorig = {
            gNewCamera.posTarget[0] + offset[0],
            gNewCamera.posTarget[1] + offset[1],
            gNewCamera.posTarget[2] + offset[2],
        };

        struct Surface *surf = NULL;
        Vec3f hitpos;
        find_surface_on_ray(camorig, camray, &surf, hitpos, 3.f);
        if (surf == NULL) {
            allhit = false;
        }
    }

    Vec3f camdir = {
        gNewCamera.pos[0] - gNewCamera.lookAt[0],
        gNewCamera.pos[1] - gNewCamera.lookAt[1],
        gNewCamera.pos[2] - gNewCamera.lookAt[2],
    };

    if (allhit) {
        struct Surface *surf = NULL;
        Vec3f hitpos;
        find_surface_on_ray(gNewCamera.lookAt, camdir, &surf, hitpos, 3.f);

        if (surf) {
            // offset the hit pos by the hit normal
            Vec3f offset = { 0 };
            offset[0] = surf->normal.x;
            offset[1] = surf->normal.y;
            offset[2] = surf->normal.z;
            vec3f_mul(offset, 5.f);
            vec3f_add(hitpos, offset);

            gNewCamera.pos[0] = hitpos[0];
            gNewCamera.pos[1] = hitpos[1];
            gNewCamera.pos[2] = hitpos[2];
            gNewCamera.panX = 0;
            gNewCamera.panZ = 0;
        }
    } else {
        gNewCamera.pos[0] = gNewCamera.lookAt[0] + camdir[0];
        gNewCamera.pos[1] = gNewCamera.lookAt[1] + camdir[1];
        gNewCamera.pos[2] = gNewCamera.lookAt[2] + camdir[2];
    }
}

static void newcam_set_pan(void) {
    if (gDjuiInMainMenu) {
        gNewCamera.panX = 0;
        gNewCamera.panZ = 0;
        return;
    }

    // Apply panning values based on Mario's direction.
    if (gMarioState->action != ACT_HOLDING_BOWSER &&
        gMarioState->action != ACT_SLEEPING &&
        gMarioState->action != ACT_START_SLEEPING
    ) {
        approach_f32_asymptotic_bool(&gNewCamera.panX, newcam_lengthdir_x((160.f * gNewCamera.panLevel) / 100.f, -gMarioState->faceAngle[1] - 0x4000), 0.05f);
        approach_f32_asymptotic_bool(&gNewCamera.panZ, newcam_lengthdir_y((160.f * gNewCamera.panLevel) / 100.f, -gMarioState->faceAngle[1] - 0x4000), 0.05f);
    } else {
        approach_f32_asymptotic_bool(&gNewCamera.panX, 0, 0.05f);
        approach_f32_asymptotic_bool(&gNewCamera.panZ, 0, 0.05f);
    }

    f32 distanceTarget = newcam_get_distance_target();
    gNewCamera.panX = gNewCamera.panX * min(gNewCamera.distance / distanceTarget, 1);
    gNewCamera.panZ = gNewCamera.panZ * min(gNewCamera.distance / distanceTarget, 1);
}

static void newcam_level_bounds(void) {
    if (gCameraUseCourseSpecificSettings) {
        u8 hasMinY = FALSE;
        f32 minY = 0;
        get_area_minimum_y(&hasMinY, &minY);
        if (hasMinY) {
            gNewCamera.pos[1] = max(gNewCamera.pos[1], minY);
        }
    }
}

static void newcam_position_cam(void) {
    f32 floorY = 0;
    f32 floorY2 = 0;
    if (!(gMarioState->action & ACT_FLAG_SWIMMING)) {
        calc_y_to_curr_floor(&floorY, 1.f, 200.f, &floorY2, 0.9f, 200.f);
    }

    newcam_update_values();
    s16 shakeX = gLakituState.shakeMagnitude[1];
    s16 shakeY = gLakituState.shakeMagnitude[0];

    // Fetch Mario's current position.
    // Not hardcoded just for the sake of flexibility, though this specific bit is temp,
    // because it won't always want to be focusing on Mario.
    gNewCamera.posTarget[0] = gMarioState->pos[0];
    gNewCamera.posTarget[1] = gMarioState->pos[1] + NEWCAM_MARIO_HEIGHT;
    gNewCamera.posTarget[2] = gMarioState->pos[2];

    // These will set the position of the camera to where Mario is supposed to be,
    // minus adjustments for where the camera should be, on top of.
    gNewCamera.pos[0] = gNewCamera.posTarget[0] + newcam_lengthdir_x(newcam_lengthdir_x(gNewCamera.distance, gNewCamera.tilt + shakeX), gNewCamera.yaw + shakeY);
    gNewCamera.pos[2] = gNewCamera.posTarget[2] + newcam_lengthdir_y(newcam_lengthdir_x(gNewCamera.distance, gNewCamera.tilt + shakeX), gNewCamera.yaw + shakeY);
    gNewCamera.pos[1] = gNewCamera.posTarget[1] + newcam_lengthdir_y(gNewCamera.distance, gNewCamera.tilt + shakeY) + floorY;
    newcam_set_pan();

    // Set where the camera wants to be looking at.
    // This is almost always the place it's based off, too.
    gNewCamera.lookAt[0] = gNewCamera.posTarget[0] - gNewCamera.panX;
    gNewCamera.lookAt[1] = gNewCamera.posTarget[1] + floorY2;
    gNewCamera.lookAt[2] = gNewCamera.posTarget[2] - gNewCamera.panZ;

    newcam_level_bounds();
    if (gNewCamera.hasCollision) {
        newcam_collision();
    }
}

static void newcam_apply_values(struct Camera *c) {
    c->pos[0] = gNewCamera.pos[0];
    c->pos[1] = gNewCamera.pos[1];
    c->pos[2] = gNewCamera.pos[2];

    c->focus[0] = gNewCamera.lookAt[0];
    c->focus[1] = gNewCamera.lookAt[1];
    c->focus[2] = gNewCamera.lookAt[2];

    gLakituState.pos[0] = gNewCamera.pos[0];
    gLakituState.pos[1] = gNewCamera.pos[1];
    gLakituState.pos[2] = gNewCamera.pos[2];

    gLakituState.focus[0] = gNewCamera.lookAt[0];
    gLakituState.focus[1] = gNewCamera.lookAt[1];
    gLakituState.focus[2] = gNewCamera.lookAt[2];

    c->yaw = -gNewCamera.yaw + 0x4000;
    gLakituState.yaw = -gNewCamera.yaw + 0x4000;

    // Adds support for wing mario tower
    if (gNewCamera.tilt < -8000 &&
        sCurrPlayMode != PLAY_MODE_PAUSED &&
        gMarioState->floor != NULL &&
        gMarioState->floor->type == SURFACE_LOOK_UP_WARP &&
        gMarioState->forwardVel == 0 &&
        save_file_get_total_star_count(gCurrSaveFileNum - 1, 0, COURSE_COUNT - 1) >= gLevelValues.wingCapLookUpReq)
    {
        level_trigger_warp(gMarioState, 1);
    }
}

// The ingame cutscene system is such a spaghetti mess I actually have to resort to something as stupid as this to cover every base.
static void newcam_update_camera_yaw(struct Camera *c, bool useMarioYaw) {
    if (useMarioYaw) {
        gNewCamera.yaw = -gMarioState->faceAngle[1] - 0x4000;
    } else {
        gNewCamera.yaw = -c->yaw + 0x4000;
    }
}

static void newcam_stick_input(void) {
    gNewCamera.extStick[0] = gPlayer1Controller->extStickX;
    gNewCamera.extStick[1] = gPlayer1Controller->extStickY;
}

// Main loop.
static void newcam_loop(struct Camera *c) {
    if (sCurrPlayMode != PLAY_MODE_PAUSED) {
        newcam_stick_input();
        newcam_rotate_button();
        newcam_zoom_button();
    } else {
        gNewCamera.yawAccel *= 0.6f;
        gNewCamera.tiltAccel *= 0.6f;
    }
    newcam_position_cam();
    if (gMarioObject) {
        newcam_apply_values(c);
    }
}
