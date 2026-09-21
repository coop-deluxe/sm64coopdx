#include "dynos.cpp.h"
#include <map>
extern "C" {
#include "include/behavior_commands.h"
}

struct BehaviorScriptCommand {
    u8 id;
    u8 size;
    BehaviorScript command[16];
};

#define BHV_COMMAND_ID(...) \
    (u8) (((BehaviorScript[]){ __VA_ARGS__ })[0] >> 24)

#define BHV_COMMAND(cmd) { \
    BHV_COMMAND_ID(cmd), { \
        .id = BHV_COMMAND_ID(cmd), \
        .size = 4 * (u8) (sizeof((BehaviorScript[]){ cmd }) / sizeof(BehaviorScript)), \
        .command = { cmd } \
    } \
}

static std::map<u8, struct BehaviorScriptCommand> sBehaviorScriptCommands = {
#define BHV_SYMBOL(_cat_, _symb_, _numArgs_, ...) BHV_COMMAND(CALL_MACRO(_symb_, __VA_ARGS__)),
#include "dynos_bin_behavior_symbols.inl"
#undef BHV_SYMBOL
};

static u8 sCurCommandId = 0xFF;
static u8 sCurCommandIndex = 0;

void DynOS_Bhv_Validate_Begin() {
    sCurCommandId = 0xFF;
    sCurCommandIndex = 0;
}

bool DynOS_Bhv_Validate_GetPointerTypes(u32 aValue, u8 &outCommandId, u32 &outPtrTypes) {
    // figure out which command we're inside
    if (sCurCommandId == 0xFF || sCurCommandIndex >= sBehaviorScriptCommands[sCurCommandId].size / 4) {
        u8 id = (u8) (aValue >> 24);

        // verify id
        if (sBehaviorScriptCommands.count(id) == 0) {
            outCommandId = sCurCommandId;
            return false;
        }

        // set current
        sCurCommandId = id;
        sCurCommandIndex = 0;
    }

    // figure out if we expect a pointer
    // index 0 contains the id, it's never a pointer
    if (sCurCommandIndex == 0) {
        outPtrTypes = 0;
    } else {
        outPtrTypes = sBehaviorScriptCommands[sCurCommandId].command[sCurCommandIndex];
    }

    // advance command index
    sCurCommandIndex++;

    outCommandId = sCurCommandId;
    return true;
}

bool DynOS_Bhv_Validate_CheckCommands(GfxData *aGfxData, const DataNode<BehaviorScript> *aNode, bool isLoad) {

    // Check unterminated command (Load only)
    if (isLoad && sCurCommandId != 0xFF && sCurCommandIndex < sBehaviorScriptCommands[sCurCommandId].size / 4) {
        PrintDataError("  ERROR: Validation failed for behavior %s: Unterminated command: %02X", aNode->mName.begin(), sCurCommandId);
        return false;
    }

    // Check commands
    Array<u8> bhvCommandIds;
    if (!DynOS_Bin_Validate_GetCommandIds<u8, 24>(aGfxData, aNode, sBehaviorScriptCommands, bhvCommandIds)) {
        return false;
    }

    // Behavior must have at least 2 commands
    if (bhvCommandIds.Count() < 2) {
        PrintDataError("  ERROR: Validation failed for behavior %s: Not enough commands (%d).", aNode->mName.begin(), bhvCommandIds.Count());
        return false;
    }

    // 1st command must be BEGIN
    if (bhvCommandIds[0] != BHV_COMMAND_ID(BEGIN(0))) {
        PrintDataError("  ERROR: Validation failed for behavior %s: First command of the script must be BEGIN.", aNode->mName.begin());
        return false;
    }

    // 2nd command must be ID
    if (bhvCommandIds[1] != BHV_COMMAND_ID(ID(0))) {
        PrintDataError("  ERROR: Validation failed for behavior %s: Second command of the script must be ID.", aNode->mName.begin());
        return false;
    }

    // Last command must be a terminating command
    static const Array<u8> sBhvEndCommands = {
        BHV_COMMAND_ID(CALL(0)),
        BHV_COMMAND_ID(RETURN()),
        BHV_COMMAND_ID(GOTO(0)),
        BHV_COMMAND_ID(END_LOOP()),
        BHV_COMMAND_ID(BREAK()),
        BHV_COMMAND_ID(DEACTIVATE()),
        BHV_COMMAND_ID(CALL_EXT(0)),
        BHV_COMMAND_ID(GOTO_EXT(0)),
    };
    if (sBhvEndCommands.Find(bhvCommandIds[bhvCommandIds.Count() - 1]) == -1) {
        PrintDataError("  ERROR: Validation failed for behavior %s: Last command of the script must be one of:\n    CALL, RETURN, GOTO, END_LOOP, BREAK, DEACTIVATE", aNode->mName.begin());
        return false;
    }

    return true;
}
