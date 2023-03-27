#include "controller_keyboard_debug.h"
#include "game/level_update.h"
#include "game/camera.h"
#include "pc/network/network.h"
#include "game/mario.h"
#include "sm64.h"

#include "object_fields.h"
#include "object_constants.h"
#include "src/game/object_helpers.h"
#include "behavior_data.h"
#include "behavior_table.h"

#ifdef DEVELOPMENT
#include "pc/lua/smlua.h"
#include "pc/network/socket/socket.h"

static bool sHoldingAlt = false;
static bool sHoldingShift = false;

#define SCANCODE_0 0x0B
#define SCANCODE_1 0x02
#define SCANCODE_2 0x03
#define SCANCODE_3 0x04
#define SCANCODE_4 0x05
#define SCANCODE_5 0x06
#define SCANCODE_6 0x07
#define SCANCODE_7 0x08
#define SCANCODE_8 0x09
#define SCANCODE_9 0x0A
#define SCANCODE_F5 0x3f
#define SCANCODE_ALT 0x38
#define SCANCODE_SHIFT 0x2A

extern void print_sync_object_table(void);

static void debug_breakpoint_here(void) {
    // create easy breakpoint position for debugging
}

extern bool dynos_warp_to_level(s32 aLevel, s32 aArea, s32 aAct);

static void debug_warp_level1() {
    // warp to credits
    //set_mario_action(&gMarioStates[0], ACT_JUMBO_STAR_CUTSCENE, 0);
    //return;

    dynos_warp_to_level(LEVEL_BOB, 1, 1);
}

static void debug_warp_level2() {
    extern f64 gGameSpeed;
    gGameSpeed = MAX(gGameSpeed - 0.1f, 0.1f);
    printf("GAME SPEED: %f\n", gGameSpeed);
    //dynos_warp_to_level(gCurrLevelNum, gCurrAreaIndex^3, 1);
}

static void debug_warp_level3() {
    extern f64 gGameSpeed;
    gGameSpeed = MIN(gGameSpeed + 0.1f, 10.0f);
    printf("GAME SPEED: %f\n", gGameSpeed);
    //dynos_warp_to_level(LEVEL_CASTLE_GROUNDS, 1, 1);
}

static void debug_grand_star(void) {
    set_mario_action(&gMarioStates[0], ACT_JUMBO_STAR_CUTSCENE, 0);
}

static void debug_warp_to(void) {
    gMarioStates[0].pos[0] = gMarioStates[1].pos[0];
    gMarioStates[0].pos[1] = gMarioStates[1].pos[1];
    gMarioStates[0].pos[2] = gMarioStates[1].pos[2];
    gMarioStates[0].marioObj->oRoom = gMarioStates[1].marioObj->oRoom;
}

static void debug_suicide(void) {
    gMarioStates[0].hurtCounter = 31;
}

static void debug_reload_lua(void) {
    smlua_shutdown();
    smlua_init();
}

static void debug_spawn_object(void) {
    for (int i = 0; i < 1; i++) {
        struct Object* box = spawn_object(gMarioStates[0].marioObj, MODEL_BREAKABLE_BOX_SMALL, bhvBreakableBoxSmall);
        if (box == NULL) { return; }
        //box->oPosX += (random_float() - 0.5f) * 1000.0f;
        //box->oPosZ += (random_float() - 0.5f) * 1000.0f;
        if (!sync_object_set_id(box)) {
            box->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            return;
        }

        struct Object* spawn_objects[] = { box };
        u32 models[] = { MODEL_BREAKABLE_BOX_SMALL };
        network_send_spawn_objects(spawn_objects, models, 1);
    }
}

void debug_keyboard_on_key_down(int scancode) {
    if (gNetworkSystem == &gNetworkSystemSocket) {
        switch (scancode & 0xFF) {
            case SCANCODE_ALT: sHoldingAlt = true; break;
            case SCANCODE_SHIFT: sHoldingShift = true; break;
            case SCANCODE_3: debug_breakpoint_here(); break;
            case SCANCODE_1:  if (sHoldingAlt) { debug_warp_level1();       } break;
            case SCANCODE_2:  if (sHoldingAlt) { debug_warp_level2();       } break;
            case SCANCODE_4:  if (sHoldingAlt) { debug_warp_level3();       } break;
            case SCANCODE_5:  if (sHoldingAlt) { print_sync_object_table(); } break;
            case SCANCODE_8:  if (sHoldingAlt) { debug_spawn_object();      } break;
            case SCANCODE_9:  if (sHoldingAlt) { debug_warp_to();           } break;
            case SCANCODE_0:  if (sHoldingAlt) { debug_suicide();           } break;
            case SCANCODE_F5: debug_reload_lua(); break;
        }
    }
}

void debug_keyboard_on_key_up(int scancode) {
    if (gNetworkSystem == &gNetworkSystemSocket) {
        switch (scancode & 0xFF) {
            case SCANCODE_ALT: sHoldingAlt = false; break;
            case SCANCODE_SHIFT: sHoldingShift = false; break;
        }
    }
}

#endif
