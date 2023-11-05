#include "first_person_cam.h"

#include "sm64.h"
#include "behavior_data.h"
#include "camera.h"
#include "level_update.h"
#include "object_list_processor.h"
#include "object_helpers.h"

#include "engine/math_util.h"

#include "pc/controller/controller_mouse.h"
#include "pc/djui/djui_hud_utils.h"
#include "pc/lua/utils/smlua_misc_utils.h"
#include "pc/lua/smlua_hooks.h"

#define MARIO_HEAD_POS 120
#define MARIO_HEAD_POS_SHORT MARIO_HEAD_POS / 2

#define CLAMP(_val, _min, _max) MAX(MIN((_val), _max), _min)

bool gFirstPersonEnabled = false;
s16 gFirstPersonYaw = 0;
static s16 sFirstPersonPitch = 0;
static f32 sFirstPersonCrouch = 0;

extern s16 gMenuMode;

/**
 * A mode that implements an first person player camera. (referenced from Gun Mod v3)
 */
void update_first_person_camera(void) {
    struct MarioState *m = &gMarioStates[0];
    f32 sensX = 0.3f * camera_config_get_x_sensitivity();
    f32 sensY = 0.4f * camera_config_get_y_sensitivity();
    u8 invX = camera_config_is_x_inverted() ? 1 : -1;
    u8 invY = camera_config_is_y_inverted() ? 1 : -1;

    if (gMenuMode == -1) {
        // update pitch
        sFirstPersonPitch -= sensY * (invY * m->controller->extStickY - 1.5f * mouse_y);
        sFirstPersonPitch = CLAMP(sFirstPersonPitch, -0x3F00, 0x3F00);

        // update yaw
        if (m->controller->buttonPressed & L_TRIG) {
            gFirstPersonYaw = m->faceAngle[1] + 0x8000;
        } else {
            gFirstPersonYaw += sensX * (invX * m->controller->extStickX - 1.5f * mouse_x);
        }

        gDjuiHudLockMouse = true;
    } else {
        gDjuiHudLockMouse = false;
    }

    // fix yaw for some specific actions
    // if the left stick is held, use Mario's yaw to set the camera's yaw
    // otherwise, set Mario's yaw to the camera's yaw
    u32 actions[] = { ACT_FLYING, ACT_HOLDING_BOWSER, ACT_TORNADO_TWIRLING, ACT_FLAG_ON_POLE, ACT_FLAG_SWIMMING };
    for (s32 i = 0; i < 4; i++) {
        u32 flag = actions[i];
        if ((m->action & flag) == flag) {
            if (ABS(m->controller->stickX) > 4) {
                gFirstPersonYaw = m->faceAngle[1] + 0x8000;
            } else {
                m->faceAngle[1] = gFirstPersonYaw - 0x8000;
            }
            break;
        }
    }
    if (m->action == ACT_LEDGE_GRAB) {
        gFirstPersonYaw = m->faceAngle[1] + 0x8000;
    }

    gLakituState.yaw = gFirstPersonYaw;
    m->area->camera->yaw = gFirstPersonYaw;

    // update crouch
    if (m->action == ACT_START_CROUCHING || m->action == ACT_CROUCHING || m->action == ACT_STOP_CROUCHING ||
       m->action == ACT_START_CRAWLING || m->action == ACT_CRAWLING || m->action == ACT_STOP_CRAWLING ||
       m->action == ACT_CROUCH_SLIDE || m->action == ACT_LEDGE_GRAB) {
        f32 inc = 10 * (m->controller->buttonDown & Z_TRIG) != 0 || m->action == ACT_CROUCH_SLIDE || m->action == ACT_LEDGE_GRAB ? 1 : -1;
        sFirstPersonCrouch = CLAMP(sFirstPersonCrouch + inc, 0, MARIO_HEAD_POS - MARIO_HEAD_POS_SHORT);
    } else {
        sFirstPersonCrouch = CLAMP(sFirstPersonCrouch - 10, 0, MARIO_HEAD_POS - MARIO_HEAD_POS_SHORT);
    }

    if (m->action == ACT_LEDGE_GRAB) {
        sFirstPersonCrouch = MARIO_HEAD_POS - MARIO_HEAD_POS_SHORT;
    }

    // update pos
    gLakituState.pos[0] = m->pos[0] + coss(sFirstPersonPitch) * sins(gFirstPersonYaw);
    gLakituState.pos[1] = m->pos[1] + sins(sFirstPersonPitch) + (MARIO_HEAD_POS - sFirstPersonCrouch);
    gLakituState.pos[2] = m->pos[2] + coss(sFirstPersonPitch) * coss(gFirstPersonYaw);
    vec3f_copy(m->area->camera->pos, gLakituState.pos);
    vec3f_copy(gLakituState.curPos, gLakituState.pos);
    vec3f_copy(gLakituState.goalPos, gLakituState.pos);

    // update focus
    gLakituState.focus[0] = m->pos[0] - 100 * coss(sFirstPersonPitch) * sins(gFirstPersonYaw);
    gLakituState.focus[1] = m->pos[1] - 100 * sins(sFirstPersonPitch) + (MARIO_HEAD_POS - sFirstPersonCrouch);
    gLakituState.focus[2] = m->pos[2] - 100 * coss(sFirstPersonPitch) * coss(gFirstPersonYaw);
    vec3f_copy(m->area->camera->focus, gLakituState.focus);
    vec3f_copy(gLakituState.curFocus, gLakituState.focus);
    vec3f_copy(gLakituState.goalFocus, gLakituState.focus);

    // set other values
    gLakituState.posHSpeed = 0;
    gLakituState.posVSpeed = 0;
    gLakituState.focHSpeed = 0;
    gLakituState.focVSpeed = 0;
    vec3s_set(gLakituState.shakeMagnitude, 0, 0, 0);

    gFOVState.fov = FIRST_PERSON_FOV;
}

bool update_first_person(void) {
    if (gFirstPersonEnabled && !gDjuiInMainMenu) {
        if (gCurrActNum == 99) {
            return false;
        }

        struct MarioState *m = &gMarioStates[0];

        // check cancels
        if (m->action == ACT_FIRST_PERSON || m->action == ACT_IN_CANNON || m->action == ACT_READING_NPC_DIALOG) {
            gFOVState.fov = 45.0f;
            return false;
        }
        if (m->action == ACT_DISAPPEARED) {
            gFOVState.fov = 45.0f;
            return false;
        }
        struct Object *bowser = find_object_with_behavior(bhvBowser);
        if (bowser != NULL && (bowser->oAction == 5 || bowser->oAction == 6)) {
            gFOVState.fov = 45.0f;
            return false;
        }

        if (m->action == ACT_SHOT_FROM_CANNON && m->area->camera->mode == CAMERA_MODE_INSIDE_CANNON) {
            gFirstPersonYaw = m->faceAngle[1] + 0x8000;
            m->area->camera->mode = CAMERA_MODE_FREE_ROAM;
        }

        gDjuiHudLockMouse = gMenuMode == -1;

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

        update_first_person_camera();

        return true;
    } else if (!camera_config_is_mouse_look_enabled()) {
        gDjuiHudLockMouse = false;
    }

    return false;
}
