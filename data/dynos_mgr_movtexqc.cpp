#include "dynos.cpp.h"
extern "C" {
#include "game/area.h"
}

struct RegisteredMovtexQC {
    DataNode<MovtexQC>* dataNode;
    s16 level;
    s16 area;
    s16 type;
};

static Array<RegisteredMovtexQC>& DynosRegisteredMovtexQCs() {
    static Array<RegisteredMovtexQC> sDynosRegisteredMovtexQCs;
    return sDynosRegisteredMovtexQCs;
}

void DynOS_MovtexQC_Register(const char* name, s16 level, s16 area, s16 type) {
    auto& _DynosRegisteredMovtexQCs = DynosRegisteredMovtexQCs();

    // check for duplicates
    for (auto& registered : _DynosRegisteredMovtexQCs) {
        if (registered.level == level && registered.area == area && registered.type == type) { return; }
    }

    // find it in the levels
    for (auto& lvlPair : DynOS_Lvl_GetArray()) {
        for (auto& node : lvlPair.second->mMovtexQCs) {
            if (node->mName == name) {
                // add it
                _DynosRegisteredMovtexQCs.Add({
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
    auto& _DynosRegisteredMovtexQCs = DynosRegisteredMovtexQCs();

    // find the datanode
    s16 type = (id & 0xF);
    for (auto& registered : _DynosRegisteredMovtexQCs) {
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

void DynOS_MovtexQC_ModShutdown() {
    auto& _DynosRegisteredMovtexQCs = DynosRegisteredMovtexQCs();
    while (_DynosRegisteredMovtexQCs.Count() > 0) {
        auto& registered = _DynosRegisteredMovtexQCs[0];
        Delete(registered.dataNode);
        _DynosRegisteredMovtexQCs.Remove(0);
    }
}
