#include "dynos.cpp.h"

extern "C" {
#include "engine/behavior_script.h"
#include "pc/network/packets/packet.h"
#include "pc/lua/smlua_hooks.h"
}

Array<Pair<const char *, GfxData *>> &DynOS_Bhv_GetArray() {
    static Array<Pair<const char *, GfxData *>> sDynosCustomBehaviorScripts;
    return sDynosCustomBehaviorScripts;
}

void DynOS_Bhv_Activate(s32 modIndex, const SysPath &aFilename, const char *aBehaviorName) {
    auto &_CustomBehaviorScripts = DynOS_Bhv_GetArray();

    // check for duplicates
    for (s32 i = 0; i < _CustomBehaviorScripts.Count(); ++i) {
        if (!strcmp(_CustomBehaviorScripts[i].first, aBehaviorName)) {
            return;
        }
    }

    u16 behaviorLen = strlen(aBehaviorName);
    char *behaviorName = (char *)calloc(1, sizeof(char) * (behaviorLen + 1));
    strcpy(behaviorName, aBehaviorName);

    GfxData *_Node = DynOS_Bhv_LoadFromBinary(aFilename, behaviorName);
    if (!_Node) {
        free(behaviorName);
        return;
    }

    // Remember index
    _Node->mModIndex = modIndex;

    // Add to behaviors
    _CustomBehaviorScripts.Add({ behaviorName, _Node });
}

void DynOS_Bhv_ModShutdown() {
    auto &_CustomBehaviorScripts = DynOS_Bhv_GetArray();
    while (_CustomBehaviorScripts.Count() > 0) {
        auto &pair = _CustomBehaviorScripts[0];
        Delete(pair.second);
        free((void *)pair.first);
        _CustomBehaviorScripts.Remove(0);
    }
}

GfxData *DynOS_Bhv_GetActiveGfx(BehaviorScript *bhvScript) {
    auto &_CustomBehaviorScripts = DynOS_Bhv_GetArray();

    for (s32 i = 0; i < _CustomBehaviorScripts.Count(); ++i) {
        auto &gfxData = _CustomBehaviorScripts[i].second;
        auto &scripts = gfxData->mBehaviorScripts;
        if (scripts.Count() == 0) { continue; }
        if (bhvScript == scripts[scripts.Count() - 1]->mData) {
            return gfxData;
        }
    }
    return NULL;
}

s32 DynOS_Bhv_GetActiveModIndex(BehaviorScript *bhvScript) {
    auto &_CustomBehaviorScripts = DynOS_Bhv_GetArray();

    for (s32 i = 0; i < _CustomBehaviorScripts.Count(); ++i) {
        auto &gfxData = _CustomBehaviorScripts[i].second;
        auto &scripts = gfxData->mBehaviorScripts;
        if (scripts.Count() == 0) { continue; }
        if (bhvScript == scripts[scripts.Count() - 1]->mData) {
            return gfxData->mModIndex;
        }
    }
    return -1;
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

    for (s32 i = 0; i < _CustomBehaviorScripts.Count(); ++i) {
        auto &scriptName = _CustomBehaviorScripts[i].first;
        auto &aGfxData = _CustomBehaviorScripts[i].second;
        if (aGfxData->mBehaviorScripts.Count() == 0) { continue; }
        auto *node = aGfxData->mBehaviorScripts[aGfxData->mBehaviorScripts.Count() - 1];
        if (node == nullptr) { continue; }
        auto &script = node->mData;

        // Theres currently no better place but to do this here.
        if (smlua_hook_custom_bhv(script, scriptName) == 0) {
            PrintDataError("  ERROR: Failed to add custom behavior '%s'!", scriptName);
        }
    }
}