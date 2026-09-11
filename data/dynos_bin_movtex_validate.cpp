#include "dynos.cpp.h"
extern "C" {
#include "include/moving_texture_macros.h"
}

bool DynOS_Movtex_Validate_CheckCommands(GfxData *aGfxData, const DataNode<Movtex> *aNode) {

    // Behavior must have at least 1 command
    if (aNode->mSize < 1) {
        PrintDataError("  ERROR: Validation failed for moving texture %s: Not enough commands (%d).", aNode->mName.begin(), aNode->mSize);
        return false;
    }

    // Last command must be MOV_TEX_END
    if (aNode->mData[aNode->mSize - 1] != MOV_TEX_END()) {
        PrintDataError("  ERROR: Validation failed for moving texture %s: Last command must be MOV_TEX_END", aNode->mName.begin());
        return false;
    }

    return true;
}
