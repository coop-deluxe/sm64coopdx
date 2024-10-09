#include "dynos.cpp.h"

static Array<Pair<const char*, DataNode<Collision>*>>& DynosCollisions() {
    static Array<Pair<const char*, DataNode<Collision>*>> sDynosCollisions;
    return sDynosCollisions;
}

void DynOS_Col_Activate(const SysPath &aFilename, const char *aCollisionName) {
    auto& _DynosCollisions = DynosCollisions();

    // check for duplicates
    for (s32 i = 0; i < _DynosCollisions.Count(); ++i) {
        if (!strcmp(_DynosCollisions[i].first, aCollisionName)) {
            return;
        }
    }

    // Allocate name
    u16 collisionLen = strlen(aCollisionName);
    char* collisionName = (char*)calloc(1, sizeof(char) * (collisionLen + 1));
    strcpy(collisionName, aCollisionName);

    // Load
    DataNode<Collision>* _Node = DynOS_Col_LoadFromBinary(aFilename, collisionName);
    if (!_Node) {
        free(collisionName);
        return;
    }

    // Add to collisions
    _DynosCollisions.Add({ collisionName, _Node });
}

Collision* DynOS_Col_Get(const char* collisionName) {
    auto& _DynosCollisions = DynosCollisions();

    // check levels
    auto& levelsArray = DynOS_Lvl_GetArray();
    for (auto& lvl : levelsArray) {
        for (auto& col : lvl.second->mCollisions) {
            if (col->mName == collisionName) {
                return col->mData;
            }
        }
    }

    // check mod actor collisions
    for (s32 i = 0; i < _DynosCollisions.Count(); ++i) {
        if (!strcmp(_DynosCollisions[i].first, collisionName)) {
            return _DynosCollisions[i].second->mData;
        }
    }

    // check builtin collisions
    return (Collision*)DynOS_Builtin_Col_GetFromName(collisionName);
}

void DynOS_Col_ModShutdown() {
    auto& _DynosCollisions = DynosCollisions();
    while (_DynosCollisions.Count() > 0) {
        auto& pair = _DynosCollisions[0];
        free((void*)pair.first);
        Delete(pair.second);
        _DynosCollisions.Remove(0);
    }
}
