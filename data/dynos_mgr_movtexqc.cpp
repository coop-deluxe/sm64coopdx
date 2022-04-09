#include "dynos.cpp.h"
extern "C" {
#include "src/game/area.h"
}

struct RegisteredMovtexQC {
    DataNode<MovtexQC>* dataNode;
    s16 level;
    s16 area;
    s16 type;
};

static Array<RegisteredMovtexQC> sDynosRegisteredMovtexQCs;

void DynOS_MovtexQC_Register(const char* name, s16 level, s16 area, s16 type) {
    // check for duplicates
    for (auto& registered : sDynosRegisteredMovtexQCs) {
        if (registered.level == level && registered.area == area && registered.type == type) { return; }
    }

    // find it in the levels
    for (auto& lvlPair : DynOS_Lvl_GetArray()) {
        for (auto& node : lvlPair.second->mMovtexQCs) {
            if (node->mName == name) {
                // add it
                sDynosRegisteredMovtexQCs.Add({
                    .dataNode = node,
                    .level    = level,
                    .area     = area,
                    .type     = type
                });
            }
        }
    }
}

DataNode<MovtexQC>* DynOS_MovtexQC_GetFromId(u32 id) {
    // find the datanode
    s16 type = (id & 0xF);
    for (auto& registered : sDynosRegisteredMovtexQCs) {
        if (registered.level == gCurrLevelNum && registered.area == gCurrAreaIndex && registered.type == type) {
            return registered.dataNode;
        }
    }
    return NULL;
}

DataNode<MovtexQC>* DynOS_MovtexQC_GetFromIndex(s32 index) {
    GfxData* gfxData = DynOS_Lvl_GetActiveGfx();
    if (gfxData == NULL) {
        return NULL;
    }

    auto &mMovtexQCs = gfxData->mMovtexQCs;

    // Sanity check the index we passed.
    if (index < 0 || index >= mMovtexQCs.Count()) {
        return NULL;
    }

    return mMovtexQCs[index];
}
