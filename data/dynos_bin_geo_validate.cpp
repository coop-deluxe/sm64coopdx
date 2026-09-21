#include "dynos.cpp.h"
#include <map>
extern "C" {
#include "include/sm64.h"
#include "include/geo_commands.h"
}

struct GeoLayoutCommand {
    u16 id; // id + modifier, because sm64 devs thought it was a good idea to create 8 different commands with the same id
    u8 size;
    GeoLayout command[16];
};

#define GEO_COMMAND_ID(...) \
    (u16) (((GeoLayout[]){ __VA_ARGS__ })[0])

static std::map<u16, struct GeoLayoutCommand> sGeoLayoutCommands = {

// Preprocessor magic
// Construct the command and repeat it for each modifier (layer, type, op...) in range.

#define GEO_COMMAND_ID_WITH_MOD(_mod_, ...) \
    (u16) (((GeoLayout[]){ __VA_ARGS__ })[0] | ((_mod_ - 1) << 8))

#define GEO_SYMBOL_WITH_MOD(_mod_, _symb_, _numArgs_, _ptrOff_, _ptrType_, ...) { \
    GEO_COMMAND_ID_WITH_MOD(_mod_, _symb_(__VA_ARGS__) ), { \
        .id = GEO_COMMAND_ID_WITH_MOD(_mod_, _symb_(__VA_ARGS__)), \
        .size = 4 * (u8) (sizeof((GeoLayout[]){ _symb_(__VA_ARGS__) }) / sizeof(GeoLayout)), \
        .command = { _symb_(__VA_ARGS__) } \
    } \
},

#define GEO_SYMBOL(_cat_, _symb_, _numArgs_, _ptrOff_, _ptrType_, _modRange_, ...) \
    REPEAT_WITH_ARGS(GEO_SYMBOL_WITH_MOD, _modRange_, _symb_, _numArgs_, _ptrOff_, _ptrType_, __VA_ARGS__)

#include "dynos_bin_geo_symbols.inl"

#undef GEO_COMMAND_ID_WITH_MOD
#undef GEO_SYMBOL_WITH_MOD
#undef GEO_SYMBOL
};

static u16 sCurCommandId = 0xFFFF;
static u8 sCurCommandIndex = 0;

void DynOS_Geo_Validate_Begin() {
    sCurCommandId = 0xFFFF;
    sCurCommandIndex = 0;
}

bool DynOS_Geo_Validate_GetPointerTypes(u32 aValue, u16 &outCommandId, u32 &outPtrTypes) {
    // figure out which command we're inside
    if (sCurCommandId == 0xFFFF || sCurCommandIndex >= sGeoLayoutCommands[sCurCommandId].size / 4) {
        u16 id = (u16) aValue;

        // verify id
        if (sGeoLayoutCommands.count(id) == 0) {
            outCommandId = sCurCommandId;
            return false;
        }

        // set current
        sCurCommandId = id;
        sCurCommandIndex = 0;
    }

    // figure out if we expect a pointer
    // index 0 contains the id and modifier, it's never a pointer
    if (sCurCommandIndex == 0) {
        outPtrTypes = 0;
    } else {
        outPtrTypes = sGeoLayoutCommands[sCurCommandId].command[sCurCommandIndex];
    }

    // advance command index
    sCurCommandIndex++;

    outCommandId = sCurCommandId;
    return true;
}

bool DynOS_Geo_Validate_CheckCommands(GfxData *aGfxData, const DataNode<GeoLayout> *aNode, bool isLoad) {

    // Check unterminated command (Load only)
    if (isLoad && sCurCommandId != 0xFFFF && sCurCommandIndex < sGeoLayoutCommands[sCurCommandId].size / 4) {
        PrintDataError("  ERROR: Validation failed for geo layout %s: Unterminated command: %04X", aNode->mName.begin(), sCurCommandId);
        return false;
    }

    // Check commands
    Array<u16> geoCommandIds;
    if (!DynOS_Bin_Validate_GetCommandIds<u16, 0>(aGfxData, aNode, sGeoLayoutCommands, geoCommandIds)) {
        return false;
    }

    // Geo layout must have at least 1 command
    if (geoCommandIds.Count() < 1) {
        PrintDataError("  ERROR: Validation failed for geo layout %s: Not enough commands (%d).", aNode->mName.begin(), geoCommandIds.Count());
        return false;
    }

    // Last command must be a terminating command
    static const Array<u16> sGeoEndCommands = {
        GEO_COMMAND_ID(GEO_BRANCH(0, 0)),
        GEO_COMMAND_ID(GEO_RETURN()),
        GEO_COMMAND_ID(GEO_END()),
    };
    if (sGeoEndCommands.Find(geoCommandIds[geoCommandIds.Count() - 1]) == -1) {
        PrintDataError("  ERROR: Validation failed for geo layout %s: Last command of the script must be one of:\n    GEO_BRANCH(0), GEO_RETURN, GEO_END", aNode->mName.begin());
        return false;
    }

    return true;
}
