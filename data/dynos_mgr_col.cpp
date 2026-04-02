#include "dynos.cpp.h"

extern "C" {
#include "pc/mods/mod_fs.h"
}

static std::vector<std::pair<std::string, DataNode<Collision>*>> &DynosCollisions() {
    static std::vector<std::pair<std::string, DataNode<Collision>*>> sDynosCollisions;
    return sDynosCollisions;
}

bool DynOS_Col_Activate(const SysPath &aFilename, const char *aCollisionName) {
    auto& _DynosCollisions = DynosCollisions();

    // check for duplicates
    for (auto &collision : _DynosCollisions) {
        if (collision.first == aCollisionName) {
            return true;
        }
    }

    // Load
    DataNode<Collision>* _Node = DynOS_Col_LoadFromBinary(aFilename, aCollisionName);
    if (!_Node) { return false; }

    // Add to collisions
    _DynosCollisions.emplace_back(aCollisionName, _Node);
    return true;
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
    for (auto &collision : _DynosCollisions) {
        if (collision.first == collisionName) {
            return collision.second->mData;
        }
    }

    // check modfs file
    if (is_mod_fs_file(collisionName)) {
        if (DynOS_Col_Activate(collisionName, collisionName)) {
            return DynOS_Col_Get(collisionName);
        }
    }

    // check builtin collisions
    return (Collision*)DynOS_Builtin_Col_GetFromName(collisionName);
}

void DynOS_Col_ModShutdown() {
    auto& _DynosCollisions = DynosCollisions();
    for (auto &pair : _DynosCollisions) {
        Delete(pair.second);
    }
    _DynosCollisions.clear();
}
