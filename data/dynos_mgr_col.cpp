#include "dynos.cpp.h"

static Array<Pair<const char*, DataNode<Collision>*>> sDynosCollisions;

void DynOS_Col_Activate(const SysPath &aPackFolder, const char *aCollisionName) {
    // check for duplicates
    for (s32 i = 0; i < sDynosCollisions.Count(); ++i) {
        if (!strcmp(sDynosCollisions[i].first, aCollisionName)) {
            return;
        }
    }

    // Allocate name
    u16 collisionLen = strlen(aCollisionName);
    char* collisionName = (char*)calloc(1, sizeof(char) * (collisionLen + 1));
    strcpy(collisionName, aCollisionName);

    // Load
    DataNode<Collision>* _Node = DynOS_Col_LoadFromBinary(aPackFolder, collisionName);
    if (!_Node) {
        free(collisionName);
        return;
    }

    // Add to collisions
    sDynosCollisions.Add({ collisionName, _Node });
}

Collision* DynOS_Col_Get(const char* collisionName) {
    // check levels
    auto& levelsArray = DynOS_Lvl_GetArray();
    for (auto& lvl : levelsArray) {
        for (auto& col : lvl.second->mCollisions) {
            if (col->mName == collisionName) {
                return col->mData;
            }
        }
    }

    // check normal actor collisions
    for (s32 i = 0; i < sDynosCollisions.Count(); ++i) {
        if (!strcmp(sDynosCollisions[i].first, collisionName)) {
            return sDynosCollisions[i].second->mData;
        }
    }
    return NULL;
}
