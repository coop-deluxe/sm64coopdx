#include "dynos.cpp.h"

extern "C" {
#include "engine/behavior_script.h"
#include "pc/network/packets/packet.h"
#include "pc/lua/smlua_hooks.h"
}

std::vector<std::pair<std::string, GfxData *>> &DynOS_Bhv_GetArray() {
    static std::vector<std::pair<std::string, GfxData *>> sDynosCustomBehaviorScripts;
    return sDynosCustomBehaviorScripts;
}

void DynOS_Bhv_Activate(s32 modIndex, const SysPath &aFilename, const char *aBehaviorName) {
    auto &_CustomBehaviorScripts = DynOS_Bhv_GetArray();

    // check for duplicates
    for (auto &behavior : _CustomBehaviorScripts) {
        if (behavior.first == aBehaviorName) {
            return;
        }
    }

    std::string behaviorName = aBehaviorName;

    GfxData *_Node = DynOS_Bhv_LoadFromBinary(aFilename, behaviorName.c_str());
    if (!_Node) { return; }

    // Remember index
    _Node->mModIndex = modIndex;

    // Add to behaviors
    _CustomBehaviorScripts.emplace_back(behaviorName, _Node);
}

void DynOS_Bhv_ModShutdown() {
    auto &_CustomBehaviorScripts = DynOS_Bhv_GetArray();
    for (auto &pair : _CustomBehaviorScripts) {
        Delete(pair.second);
    }
    _CustomBehaviorScripts.clear();
}

GfxData *DynOS_Bhv_GetActiveGfx(BehaviorScript *bhvScript) {
    auto &_CustomBehaviorScripts = DynOS_Bhv_GetArray();

    for (auto &behavior : _CustomBehaviorScripts) {
        auto &gfxData = behavior.second;
        auto &scripts = gfxData->mBehaviorScripts;
        if (scripts.Count() == 0) { continue; }
        if (bhvScript == scripts[scripts.Count() - 1]->mData) {
            return gfxData;
        }
    }
    return NULL;
}

bool DynOS_Bhv_GetActiveModIndex(BehaviorScript *bhvScript, s32 *modIndex, s32 *modFileIndex) {
    auto &_CustomBehaviorScripts = DynOS_Bhv_GetArray();

    for (auto &behavior : _CustomBehaviorScripts) {
        auto &gfxData = behavior.second;
        auto &scripts = gfxData->mBehaviorScripts;
        if (scripts.Count() == 0) { continue; }
        if (bhvScript == scripts[scripts.Count() - 1]->mData) {
            *modIndex = gfxData->mModIndex;
            *modFileIndex = gfxData->mModFileIndex;
            return true;
        }
    }
    return false;
}

const char *DynOS_Bhv_GetToken(BehaviorScript *bhvScript, u32 index) {
    GfxData *gfxData = DynOS_Bhv_GetActiveGfx(bhvScript);
    if (gfxData == NULL) {
        return NULL;
    }

    // have to 1-index due to to pointer read code
    index = index - 1;

    if (index >= gfxData->mLuaTokenList.Count()) {
        return NULL;
    }

    return gfxData->mLuaTokenList[index].begin();
}

void DynOS_Bhv_HookAllCustomBehaviors() {
    auto &_CustomBehaviorScripts = DynOS_Bhv_GetArray();

    for (auto &behavior : _CustomBehaviorScripts) {
        auto &scriptName = behavior.first;
        auto &aGfxData = behavior.second;
        if (aGfxData->mBehaviorScripts.Count() == 0) { continue; }
        auto *node = aGfxData->mBehaviorScripts[aGfxData->mBehaviorScripts.Count() - 1];
        if (node == nullptr) { continue; }
        auto &script = node->mData;

        // Theres currently no better place but to do this here.
        if (smlua_hook_custom_bhv(script, scriptName.c_str()) == 0) {
            PrintDataError("  ERROR: Failed to add custom behavior '%s'!", scriptName.c_str());
        }
    }
}
