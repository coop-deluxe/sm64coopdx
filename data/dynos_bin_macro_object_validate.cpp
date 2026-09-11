#include "dynos.cpp.h"
extern "C" {
#include "include/level_misc_macros.h"
#include "include/macro_presets.h"
}

bool DynOS_MacroObject_Validate_CheckCommands(GfxData *aGfxData, const DataNode<MacroObject> *aNode) {

    // Should be of fixed size (N * 5 + 1)
    if (aNode->mSize % 5 != 1) {
        PrintDataError("  ERROR: Validation failed for macro objects %s: Invalid size: %d", aNode->mName.begin(), aNode->mSize);
        return false;
    }

    // Check presets
    for (s32 i = 0; i < (aNode->mSize - 1); i += 5) {
        s16 presetId = (s16) ((aNode->mData[i] & 0x1FF) - 0x1F);
        if (presetId < 0 || presetId >= MACRO_OBJECT_PRESET_COUNT) {
            PrintDataError("  ERROR: Validation failed for macro objects %s: Invalid preset ID: %d", aNode->mName.begin(), presetId);
            return false;
        }
    }

    // Last command must be MACRO_OBJECT_END
    if (aNode->mData[aNode->mSize - 1] != MACRO_OBJECT_END()) {
        PrintDataError("  ERROR: Validation failed for macro objects %s: Last command must be MACRO_OBJECT_END", aNode->mName.begin());
        return false;
    }

    return true;
}
