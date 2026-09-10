#include "dynos.cpp.h"
extern "C" {
#include "include/level_misc_macros.h"
}

bool DynOS_Trajectory_Validate_CheckCommands(GfxData *aGfxData, const DataNode<Trajectory> *aNode) {

    // Should be of fixed size (N * 4 + 1)
    if (aNode->mSize % 4 != 1) {
        PrintDataError("  ERROR: Validation failed for trajectory %s: Invalid size: %d", aNode->mName.begin(), aNode->mSize);
        return false;
    }

    // Last command must be TRAJECTORY_END
    if (aNode->mData[aNode->mSize - 1] != TRAJECTORY_END()) {
        PrintDataError("  ERROR: Validation failed for trajectory %s: Last command must be TRAJECTORY_END", aNode->mName.begin());
        return false;
    }

    return true;
}
