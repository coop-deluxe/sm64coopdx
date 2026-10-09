#include "dynos.cpp.h"
extern "C" {
#include "include/moving_texture_macros.h"
}

bool DynOS_Movtex_Validate_CheckCommands(GfxData *aGfxData, const DataNode<Movtex> *aNode) {

    // Moving texture must have at least 1 command
    if (aNode->mSize < 1) {
        PrintDataError("  ERROR: Validation failed for moving texture %s: Not enough commands (%d).", aNode->mName.begin(), aNode->mSize);
        return false;
    }

    return true;
}
