#include "dynos.cpp.h"

extern "C" {
#include "engine/level_script.h"
#include "game/skybox.h"
}

struct OverrideLevelScript {
    const void* originalScript;
    const void* newScript;
    GfxData* gfxData;
};

static Array<struct OverrideLevelScript>& DynosOverrideLevelScripts() {
    static Array<struct OverrideLevelScript> sDynosOverrideLevelScripts;
    return sDynosOverrideLevelScripts;
}

Array<Pair<const char*, GfxData*>> &DynOS_Lvl_GetArray() {
    static Array<Pair<const char*, GfxData*>> sDynosCustomLevelScripts;
    return sDynosCustomLevelScripts;
}

LevelScript* DynOS_Lvl_GetScript(const char* aScriptEntryName) {
    auto& _CustomLevelScripts = DynOS_Lvl_GetArray();
    for (s32 i = 0; i < _CustomLevelScripts.Count(); ++i) {
        auto& pair = _CustomLevelScripts[i];
        if (!strcmp(pair.first, aScriptEntryName)) {
            auto& newScripts = pair.second->mLevelScripts;
            auto& newScriptNode = newScripts[newScripts.Count() - 1];
            return newScriptNode->mData;
        }
    }
    return NULL;
}

void DynOS_Lvl_ModShutdown() {
    DynOS_Level_Unoverride();

    auto& _CustomLevelScripts = DynOS_Lvl_GetArray();
    while (_CustomLevelScripts.Count() > 0) {
        for (auto& pair : _CustomLevelScripts) {
            DynOS_Tex_Invalid(pair.second);
            Delete(pair.second);
            free((void*)pair.first);
        }
        _CustomLevelScripts.Clear();
    }

    auto& _OverrideLevelScripts = DynosOverrideLevelScripts();
    _OverrideLevelScripts.Clear();
}

void DynOS_Lvl_Activate(s32 modIndex, const SysPath &aFilename, const char *aLevelName) {
    auto& _CustomLevelScripts = DynOS_Lvl_GetArray();
    auto& _OverrideLevelScripts = DynosOverrideLevelScripts();

    // make sure vanilla levels were parsed
    DynOS_Level_Init();

    // check for duplicates
    for (s32 i = 0; i < _CustomLevelScripts.Count(); ++i) {
        if (!strcmp(_CustomLevelScripts[i].first, aLevelName)) {
            return;
        }
    }

    u16 levelLen = strlen(aLevelName);
    char* levelName = (char*)calloc(1, sizeof(char) * (levelLen + 1));
    strcpy(levelName, aLevelName);

    GfxData* _Node = DynOS_Lvl_LoadFromBinary(aFilename, levelName);
    if (!_Node) {
        free(levelName);
        return;
    }

    // remember index
    _Node->mModIndex = modIndex;

    // Add to levels
    _CustomLevelScripts.Add({ levelName, _Node });
    DynOS_Tex_Valid(_Node);

    // Override vanilla script
    auto& newScripts = _Node->mLevelScripts;
    if (newScripts.Count() <= 0) {
        PrintError("Could not find level scripts: '%s'", aLevelName);
        return;
    }

    auto& newScriptNode = newScripts[newScripts.Count() - 1];
    const void* originalScript = DynOS_Builtin_ScriptPtr_GetFromName(newScriptNode->mName.begin());
    if (originalScript == NULL) {
        return;
    }

    DynOS_Level_Override((void*)originalScript, newScriptNode->mData, modIndex);
    _OverrideLevelScripts.Add({ originalScript, newScriptNode->mData, _Node});
}

GfxData* DynOS_Lvl_GetActiveGfx(void) {
    auto& _CustomLevelScripts = DynOS_Lvl_GetArray();
    for (s32 i = 0; i < _CustomLevelScripts.Count(); ++i) {
        auto& gfxData = _CustomLevelScripts[i].second;
        auto& scripts = gfxData->mLevelScripts;
        for (auto& s : scripts) {
            if (gLevelScriptActive == s->mData) {
                return gfxData;
            }
        }
    }
    return NULL;
}

const char* DynOS_Lvl_GetToken(u32 index) {
    GfxData* gfxData = DynOS_Lvl_GetActiveGfx();
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

Trajectory* DynOS_Lvl_GetTrajectory(const char* aName) {
    auto& _CustomLevelScripts = DynOS_Lvl_GetArray();

    for (auto& script : _CustomLevelScripts) {
        for (auto& trajectoryNode : script.second->mTrajectories) {
            if (trajectoryNode->mName == aName) {
                return trajectoryNode->mData;
            }
        }
    }
    return NULL;
}

void DynOS_Lvl_LoadBackground(void *aPtr) {
    auto& _CustomLevelScripts = DynOS_Lvl_GetArray();

    // ensure this texture list exists
    GfxData* foundGfxData = NULL;
    DataNode<TexData*>* foundList = NULL;
    for (auto& script : _CustomLevelScripts) {
        auto &textureLists = script.second->mTextureLists;
        for (auto& textureList : textureLists) {
            if (textureList == aPtr) {
                foundGfxData = script.second;
                foundList = textureList;
                goto double_break;
            }
        }
    }
double_break:

    if (foundList == NULL) {
        PrintError("Could not find custom background");
        return;
    }

    // Load up custom background
    for (s32 i = 0; i < 80; i++) {
        // find texture
        for (auto& tex : foundGfxData->mTextures) {
            if (tex->mData == foundList->mData[i]) {
                gCustomSkyboxPtrList[i] = (Texture*)tex;
                break;
            }
        }
    }
}

void *DynOS_Lvl_Override(void *aCmd) {
    auto& _OverrideLevelScripts = DynosOverrideLevelScripts();
    for (auto& overrideStruct : _OverrideLevelScripts) {
        if (aCmd == overrideStruct.originalScript || aCmd == overrideStruct.newScript) {
            aCmd = (void*)overrideStruct.newScript;
            gLevelScriptModIndex = overrideStruct.gfxData->mModIndex;
            gLevelScriptActive = (LevelScript*)aCmd;
        }
    }

    auto& _CustomLevelScripts = DynOS_Lvl_GetArray();
    for (auto& script : _CustomLevelScripts) {
        auto& scripts = script.second->mLevelScripts;
        for (auto& s : scripts) {
            if (aCmd == s->mData) {
                gLevelScriptModIndex = script.second->mModIndex;
                gLevelScriptActive = (LevelScript*)aCmd;
            }
        }
    }

    return aCmd;
}

