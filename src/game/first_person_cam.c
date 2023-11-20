#include "first_person_cam.h"

#include "sm64.h"
#include "behavior_data.h"
#include "camera.h"
#include "level_update.h"
#include "object_list_processor.h"
#include "object_helpers.h"

#include "engine/math_util.h"

#include "pc/controller/controller_mouse.h"
#include "pc/djui/djui.h"
#include "pc/djui/djui_hud_utils.h"
#include "pc/lua/utils/smlua_misc_utils.h"
#include "pc/lua/smlua_hooks.h"

#define MARIO_HEAD_POS 120
#define MARIO_HEAD_POS_SHORT MARIO_HEAD_POS / 2

#define CLAMP(_val, _min, _max) MAX(MIN((_val), _max), _min)

struct FirstPersonCamera gFirstPersonCamera = {
    .enabled = false,
    .pitch = 0,
    .yaw = 0,
    .crouch = 0,
    .fov = FIRST_PERSON_DEFAULT_FOV
};

extern s16 gMenuMode;

bool first_person_check_cancels(void) {
    struct MarioState *m = &gMarioStates[0];

    if (m->action == ACT_FIRST_PERSON || m->action == ACT_IN_CANNON || m->action == ACT_READING_NPC_DIALOG || m->action == ACT_DISAPPEARED) {
        return true;
    }

    if (gLuaLoadingMod != NULL) { return false; }

    struct Object *bowser = find_object_with_behavior(bhvBowser);
    if (bowser != NULL && (bowser->oAction == 5 || bowser->oAction == 6)) {
        return true;
    }

    return false;
}

bool get_first_person_enabled(void) {
    return gFirstPersonCamera.enabled && !first_person_check_cancels();
}

void set_first_person_enabled(bool enable) {
    if (gFirstPersonCamera.enabled && !enable) { gFOVState.fov = 45.0f; }
    gFirstPersonCamera.enabled = enable;
}

void first_person_camera_update(void) {
    struct MarioState *m = &gMarioStates[0];
    f32 sensX = 0.3f * camera_config_get_x_sensitivity();
    f32 sensY = 0.4f * camera_config_get_y_sensitivity();
    u8 invX = camera_config_is_x_inverted() ? 1 : -1;
    u8 invY = camera_config_is_y_inverted() ? 1 : -1;

    if (gMenuMode == -1 && !gDjuiChatBoxFocus && !gDjuiConsoleFocus) {
        // update pitch
        gFirstPersonCamera.pitch -= sensY * (invY * m->controller->extStickY - 1.5f * mouse_y);
        gFirstPersonCamera.pitch = CLAMP(gFirstPersonCamera.pitch, -0x3F00, 0x3F00);

        // update yaw
        if (m->controller->buttonPressed & L_TRIG) {
            gFirstPersonCamera.yaw = m->faceAngle[1] + 0x8000;
        } else {
            gFirstPersonCamera.yaw += sensX * (invX * m->controller->extStickX - 1.5f * mouse_x);
        }

        gDjuiHudLockMouse = true;
    } else {
        gDjuiHudLockMouse = false;
    }

    // fix yaw for some specific actions
    // if the left stick is held, use Mario's yaw to set the camera's yaw
    // otherwise, set Mario's yaw to the camera's yaw
    u32 actions[] = { ACT_FLYING, ACT_HOLDING_BOWSER, ACT_TORNADO_TWIRLING, ACT_FLAG_ON_POLE, ACT_FLAG_SWIMMING, ACT_FLAG_SWIMMING_OR_FLYING };
    for (s32 i = 0; i < 6; i++) {
        u32 flag = actions[i];
        if ((m->action & flag) == flag) {
            if (ABS(m->controller->stickX) > 4) {
                gFirstPersonCamera.yaw = m->faceAngle[1] + 0x8000;
            } else {
                m->faceAngle[1] = gFirstPersonCamera.yaw - 0x8000;
            }
            break;
        }
    }
    if (m->action == ACT_LEDGE_GRAB) {
        gFirstPersonCamera.yaw = m->faceAngle[1] + 0x8000;
    }

    gLakituState.yaw = gFirstPersonCamera.yaw;
    m->area->camera->yaw = gFirstPersonCamera.yaw;

    // update crouch
    if (m->action == ACT_START_CROUCHING || m->action == ACT_CROUCHING || m->action == ACT_STOP_CROUCHING ||
       m->action == ACT_START_CRAWLING || m->action == ACT_CRAWLING || m->action == ACT_STOP_CRAWLING ||
       m->action == ACT_CROUCH_SLIDE || m->action == ACT_LEDGE_GRAB) {
        f32 inc = 10 * (m->controller->buttonDown & Z_TRIG) != 0 || m->action == ACT_CROUCH_SLIDE || m->action == ACT_LEDGE_GRAB ? 1 : -1;
        gFirstPersonCamera.crouch = CLAMP(gFirstPersonCamera.crouch + inc, 0, MARIO_HEAD_POS - MARIO_HEAD_POS_SHORT);
    } else {
        gFirstPersonCamera.crouch = CLAMP(gFirstPersonCamera.crouch - 10, 0, MARIO_HEAD_POS - MARIO_HEAD_POS_SHORT);
    }

    if (m->action == ACT_LEDGE_GRAB) {
        gFirstPersonCamera.crouch = MARIO_HEAD_POS - MARIO_HEAD_POS_SHORT;
    }

    // update pos
    gLakituState.pos[0] = m->pos[0] + coss(gFirstPersonCamera.pitch) * sins(gFirstPersonCamera.yaw);
    gLakituState.pos[1] = m->pos[1] + sins(gFirstPersonCamera.pitch) + (MARIO_HEAD_POS - gFirstPersonCamera.crouch);
    gLakituState.pos[2] = m->pos[2] + coss(gFirstPersonCamera.pitch) * coss(gFirstPersonCamera.yaw);
    vec3f_copy(m->area->camera->pos, gLakituState.pos);
    vec3f_copy(gLakituState.curPos, gLakituState.pos);
    vec3f_copy(gLakituState.goalPos, gLakituState.pos);

    // update focus
    gLakituState.focus[0] = m->pos[0] - 100 * coss(gFirstPersonCamera.pitch) * sins(gFirstPersonCamera.yaw);
    gLakituState.focus[1] = m->pos[1] - 100 * sins(gFirstPersonCamera.pitch) + (MARIO_HEAD_POS - gFirstPersonCamera.crouch);
    gLakituState.focus[2] = m->pos[2] - 100 * coss(gFirstPersonCamera.pitch) * coss(gFirstPersonCamera.yaw);
    vec3f_copy(m->area->camera->focus, gLakituState.focus);
    vec3f_copy(gLakituState.curFocus, gLakituState.focus);
    vec3f_copy(gLakituState.goalFocus, gLakituState.focus);

    // set other values
    gLakituState.posHSpeed = 0;
    gLakituState.posVSpeed = 0;
    gLakituState.focHSpeed = 0;
    gLakituState.focVSpeed = 0;
    vec3s_set(gLakituState.shakeMagnitude, 0, 0, 0);

    gFOVState.fov = gFirstPersonCamera.fov;
}

void first_person_update(void) {
    if (gFirstPersonCamera.enabled && !gDjuiInMainMenu) {
        // check cancels
        bool cancel = first_person_check_cancels();
        if (cancel) { return; }

        struct MarioState *m = &gMarioStates[0];

        if (m->action == ACT_SHOT_FROM_CANNON && m->area->camera->mode == CAMERA_MODE_INSIDE_CANNON) {
            gFirstPersonCamera.yaw = m->faceAngle[1] + 0x8000;
            m->area->camera->mode = CAMERA_MODE_FREE_ROAM;
        }

        m->marioBodyState->modelState = 0x100;
        if (m->heldObj) {
            Vec3f camDir = {
                m->area->camera->focus[0] - m->area->camera->pos[0],
                m->area->camera->focus[1] - m->area->camera->pos[1],
                m->area->camera->focus[2] - m->area->camera->pos[2],
            };
            vec3f_normalize(camDir);
            vec3f_mul(camDir, 100);
            vec3f_sum(m->marioObj->header.gfx.pos, m->pos, camDir);
        }

        first_person_camera_update();
    } else if (!camera_config_is_mouse_look_enabled()) {
        gDjuiHudLockMouse = false;
    }
}

void first_person_reset(void) {
    gFirstPersonCamera.pitch = 0;
    gFirstPersonCamera.yaw = 0;
    gFirstPersonCamera.crouch = 0;
}
