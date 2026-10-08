#include "dynos.cpp.h"
#include <map>
extern "C" {
#include "include/level_commands.h"
}

struct LevelScriptCommand {
    u8 id;
    u8 size;
    LevelScript command[16];
};

#define LVL_COMMAND_ID(...) \
    (u8) (((LevelScript[]){ __VA_ARGS__ })[0])

#define LVL_COMMAND(cmd) { \
    LVL_COMMAND_ID(cmd), { \
        .id = LVL_COMMAND_ID(cmd), \
        .size = 4 * (u8) (sizeof((LevelScript[]){ cmd }) / sizeof(LevelScript)), \
        .command = { cmd } \
    } \
}

static std::map<u8, struct LevelScriptCommand> sLevelScriptCommands = {
#define LVL_SYMBOL(_cat_, _symb_, _numArgs_, _ptrOff_, _ptrType_, ...) LVL_COMMAND(CALL_MACRO(_symb_, __VA_ARGS__)),
#include "dynos_bin_lvl_symbols.inl"
#undef LVL_SYMBOL
};

static u8 sCurCommandId = 0xFF;
static u8 sCurCommandIndex = 0;

void DynOS_Lvl_Validate_Begin() {
    sCurCommandId = 0xFF;
    sCurCommandIndex = 0;
}

bool DynOS_Lvl_Validate_GetPointerTypes(u32 aValue, u8 &outCommandId, u32 &outPtrTypes) {
    // figure out which command we're inside
    if (sCurCommandId == 0xFF || sCurCommandIndex >= sLevelScriptCommands[sCurCommandId].size / 4) {
        u8 id = (u8) aValue;

        // verify id
        if (sLevelScriptCommands.count(id) == 0) {
            outCommandId = sCurCommandId;
            return false;
        }

        // set current
        sCurCommandId = id;
        sCurCommandIndex = 0;
    }

    // figure out if we expect a pointer
    // index 0 contains the id and size, it's never a pointer
    if (sCurCommandIndex == 0) {
        outPtrTypes = 0;
    } else {
        outPtrTypes = sLevelScriptCommands[sCurCommandId].command[sCurCommandIndex];
    }

    // advance command index
    sCurCommandIndex++;

    outCommandId = sCurCommandId;
    return true;
}

bool DynOS_Lvl_Validate_CheckCommands(GfxData *aGfxData, const DataNode<LevelScript> *aNode, bool isLoad) {

    // Check unterminated command (Load only)
    if (isLoad && sCurCommandId != 0xFF && sCurCommandIndex < sLevelScriptCommands[sCurCommandId].size / 4) {
        PrintDataError("  ERROR: Validation failed for level %s: Unterminated command: %02X", aNode->mName.begin(), sCurCommandId);
        return false;
    }

    // Check commands
    Array<u8> lvlCommandIds;
    if (!DynOS_Bin_Validate_GetCommandIds<u8, 0>(aGfxData, aNode, sLevelScriptCommands, lvlCommandIds)) {
        return false;
    }

    // Level script must have at least 1 command
    if (lvlCommandIds.Count() < 1) {
        PrintDataError("  ERROR: Validation failed for level %s: Not enough commands (%d).", aNode->mName.begin(), lvlCommandIds.Count());
        return false;
    }

    // Penultimate command cannot be a SKIP command
    static const Array<u8> sLvlSkipCommands = {
        LVL_COMMAND_ID(SKIP()),
        LVL_COMMAND_ID(SKIP_IF(0, 0)),
        LVL_COMMAND_ID(SKIP_NOP()),
    };
    if (lvlCommandIds.Count() >= 2 && sLvlSkipCommands.Find(lvlCommandIds[lvlCommandIds.Count() - 2]) != -1) {
        PrintDataError("  ERROR: Validation failed for level %s: Penultimate command of the script cannot be one of:\n    SKIP, SKIP_IF, SKIP_NOP", aNode->mName.begin());
        return false;
    }

    // Last command must be a terminating command
    static const Array<u8> sLvlEndCommands = {
        LVL_COMMAND_ID(EXIT()),
        LVL_COMMAND_ID(EXIT_AND_EXECUTE(0, 0, 0, 0)),
        LVL_COMMAND_ID(JUMP(0)),
        LVL_COMMAND_ID(RETURN()),
    };
    if (sLvlEndCommands.Find(lvlCommandIds[lvlCommandIds.Count() - 1]) == -1) {
        PrintDataError("  ERROR: Validation failed for level %s: Last command of the script must be one of:\n    EXIT, EXIT_AND_EXECUTE, JUMP, RETURN", aNode->mName.begin());
        return false;
    }

    return true;
}

u8 DynOS_Lvl_GetCommandSize(u8 aCmdType) {
    if (sLevelScriptCommands.count(aCmdType) != 0) {
        return sLevelScriptCommands[aCmdType].size;
    }
    return 0;
}
