#include "dynos.cpp.h"
#include <map>
#include <assert.h>
extern "C" {
#include "include/level_commands.h"
#include "include/model_ids.h"
#include "include/behavior_data.h"
#include "include/surface_terrains.h"
#include "include/seq_ids.h"
#include "level_commands.h"
#include "game/level_update.h"
#include "include/dialog_ids.h"
#include "levels/scripts.h"
#include "levels/menu/header.h"
#include "game/area.h"
}

#define POINTER 0xD34DB33F

struct LevelScriptCommand {
    u8 id;
    u8 size;
    u8 ptrIdx[2];
};

static bool sCommandMapFilled = false;
static std::map<u8, struct LevelScriptCommand> sCommandMap;

static u8 sCurCommandId = 0xFF;
static u8 sCurCommandOffset = 0xFF;

#define ADD_COMMAND(_cmd) {               \
    LevelScript _script[] = { _cmd };     \
    size_t _size = ARRAY_COUNT(_script);  \
    LvlCmd_Add(_script, _size);           \
}

static void LvlCmd_Add(LevelScript script[], size_t size) {
    // make sure size isn't crazy
    assert(size < 0xFF);

    // find the single pointer index
    u8 ptrIdx[2] = { 0xFF, 0xFF };
    for (u8 i = 0; i < size; i++) {
        if (script[i] != POINTER) { continue; }
        if (ptrIdx[0] == 0xFF) {
            ptrIdx[0] = i;
        } else {
            assert(ptrIdx[1] == 0xFF);
            ptrIdx[1] = i;
        }
    }

    // extract the id and make sure it's unique
    u8 id = (u8)(script[0] & 0xFF);
    if (sCommandMap.count(id) != 0) { return; }

    // add the command to the map
    sCommandMap[id] = {
        .id = id,
        .size = (u8)size,
        .ptrIdx = { ptrIdx[0], ptrIdx[1] },
    };
}

static void LvlCmd_Init() {
    ADD_COMMAND(EXECUTE(0, 0, 0, POINTER));
    ADD_COMMAND(EXIT_AND_EXECUTE(0, 0, 0, POINTER));
    ADD_COMMAND(EXIT());
    ADD_COMMAND(SLEEP(0));
    ADD_COMMAND(SLEEP_BEFORE_EXIT(0));
    ADD_COMMAND(JUMP(POINTER));
    ADD_COMMAND(JUMP_LINK(POINTER));
    ADD_COMMAND(RETURN());
    ADD_COMMAND(JUMP_LINK_PUSH_ARG(0));
    ADD_COMMAND(JUMP_N_TIMES());
    ADD_COMMAND(LOOP_BEGIN());
    ADD_COMMAND(LOOP_UNTIL(0, 0));
    ADD_COMMAND(JUMP_IF(0, 0, POINTER));
    ADD_COMMAND(JUMP_LINK_IF(0, 0, POINTER));
    ADD_COMMAND(SKIP_IF(0, 0));
    ADD_COMMAND(SKIP());
    ADD_COMMAND(SKIP_NOP());
    ADD_COMMAND(CALL(0, POINTER));
    ADD_COMMAND(CALL_LOOP(0, POINTER));
    ADD_COMMAND(SET_REG(0));
    ADD_COMMAND(PUSH_POOL());
    ADD_COMMAND(POP_POOL());
    ADD_COMMAND(FIXED_LOAD(0, 0, 0));
    ADD_COMMAND(LOAD_RAW(0, 0, 0));
    ADD_COMMAND(LOAD_MIO0(0, 0, 0));
    ADD_COMMAND(LOAD_MARIO_HEAD(0));
    ADD_COMMAND(LOAD_MIO0_TEXTURE(0, 0, 0));
    ADD_COMMAND(INIT_LEVEL());
    ADD_COMMAND(CLEAR_LEVEL());
    ADD_COMMAND(ALLOC_LEVEL_POOL());
    ADD_COMMAND(FREE_LEVEL_POOL());
    ADD_COMMAND(AREA(0, POINTER));
    ADD_COMMAND(END_AREA());
    ADD_COMMAND(LOAD_MODEL_FROM_DL(0, 0, 0));
    ADD_COMMAND(LOAD_MODEL_FROM_GEO(0, POINTER));
    ADD_COMMAND(CMD23(0, 0, 0));
    ADD_COMMAND(OBJECT_WITH_ACTS(0, 0, 0, 0, 0, 0, 0, 0, POINTER, 0));
    ADD_COMMAND(OBJECT(0, 0, 0, 0, 0, 0, 0, 0, POINTER));
    ADD_COMMAND(MARIO(0, 0, POINTER));
    ADD_COMMAND(WARP_NODE(0, 0, 0, 0, 0));
    ADD_COMMAND(PAINTING_WARP_NODE(0, 0, 0, 0, 0));
    ADD_COMMAND(INSTANT_WARP(0, 0, 0, 0, 0));
    ADD_COMMAND(LOAD_AREA(0));
    ADD_COMMAND(CMD2A(0));
    ADD_COMMAND(MARIO_POS(0, 0, 0, 0, 0));
    ADD_COMMAND(CMD2C());
    ADD_COMMAND(CMD2D());
    ADD_COMMAND(TERRAIN(POINTER));
    ADD_COMMAND(ROOMS(POINTER));
    ADD_COMMAND(SHOW_DIALOG(0, 0));
    ADD_COMMAND(TERRAIN_TYPE(0));
    ADD_COMMAND(NOP());
    ADD_COMMAND(TRANSITION(0, 0, 0, 0, 0));
    ADD_COMMAND(BLACKOUT(0));
    ADD_COMMAND(GAMMA(0));
    ADD_COMMAND(SET_BACKGROUND_MUSIC(0, 0));
    ADD_COMMAND(SET_MENU_MUSIC(0));
    ADD_COMMAND(STOP_MUSIC(0));
    ADD_COMMAND(MACRO_OBJECTS(POINTER));
    ADD_COMMAND(CMD3A(0, 0, 0, 0, 0));
    ADD_COMMAND(WHIRLPOOL(0, 0, 0, 0, 0, 0));
    ADD_COMMAND(GET_OR_SET(0, 0));
    ADD_COMMAND(ADV_DEMO());
    ADD_COMMAND(CLEAR_DEMO_PTR());
    ADD_COMMAND(OBJECT_WITH_ACTS_EXT(0, 0, 0, 0, 0, 0, 0, 0, POINTER, 0));
    ADD_COMMAND(OBJECT_WITH_ACTS_EXT2(POINTER, 0, 0, 0, 0, 0, 0, 0, POINTER, 0));
    ADD_COMMAND(OBJECT_EXT(0, 0, 0, 0, 0, 0, 0, 0, POINTER));
    ADD_COMMAND(OBJECT_EXT2(POINTER, 0, 0, 0, 0, 0, 0, 0, POINTER));
    ADD_COMMAND(LOAD_MODEL_FROM_GEO_EXT(0, POINTER));
    ADD_COMMAND(JUMP_AREA_EXT(0, 0, POINTER));
}

void DynOS_Lvl_Validate_Begin() {
    // fill our command map if it hasn't been initialized
    if (!sCommandMapFilled) {
        LvlCmd_Init();
        sCommandMapFilled = true;
    }

    // set current command info to defaults
    sCurCommandId = 0xFF;
    sCurCommandOffset = 0xFF;
}

bool DynOS_Lvl_Validate_RequirePointer(u32 value) {
    // figure out which command we're inside
    if (sCurCommandId == 0xFF || sCurCommandOffset >= sCommandMap[sCurCommandId].size) {
        u8 id = (u8)(value & 0xFF);
        sCurCommandId = id;
        sCurCommandOffset = 0;
    }

    // figure out if we expect a pointer
    bool ret = (
        sCurCommandOffset == sCommandMap[sCurCommandId].ptrIdx[0]
        || sCurCommandOffset == sCommandMap[sCurCommandId].ptrIdx[1]);

    // advance command offset
    sCurCommandOffset++;

    return ret;
}
