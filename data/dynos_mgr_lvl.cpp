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

static Array<Pair<const char*, GfxData*>> sDynosCustomLevelScripts;
static Array<struct OverrideLevelScript> sDynosOverrideLevelScripts;

Array<Pair<const char*, GfxData*>> &DynOS_Lvl_GetArray() {
    return sDynosCustomLevelScripts;
}

void DynOS_Lvl_Activate(s32 modIndex, const SysPath &aFilename, const char *aLevelName) {
    // make sure vanilla levels were parsed
    DynOS_Level_GetCount();

    // check for duplicates
    for (s32 i = 0; i < sDynosCustomLevelScripts.Count(); ++i) {
        if (!strcmp(sDynosCustomLevelScripts[i].first, aLevelName)) {
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
    sDynosCustomLevelScripts.Add({ levelName, _Node });

    // Override vanilla script
    auto& newScripts = _Node->mLevelScripts;
    auto& newScriptNode = newScripts[newScripts.Count() - 1];
    const void* originalScript = DynOS_Builtin_ScriptPtr_GetFromName(newScriptNode->mName.begin());
    if (originalScript == NULL) {
        Print("Could not find level to override: '%s'", newScriptNode->mName.begin());
        return;
    }

    DynOS_Level_Override((void*)originalScript, newScriptNode->mData);
    sDynosOverrideLevelScripts.Add({ originalScript, newScriptNode->mData, _Node});
    DynOS_Tex_Valid(_Node);
}

GfxData* DynOS_Lvl_GetActiveGfx(void) {
    for (s32 i = 0; i < sDynosCustomLevelScripts.Count(); ++i) {
        auto& gfxData = sDynosCustomLevelScripts[i].second;
        auto& scripts = gfxData->mLevelScripts;
        if (gLevelScriptActive == scripts[scripts.Count() - 1]->mData) {
            return gfxData;
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
    for (auto& script : sDynosCustomLevelScripts) {
        for (auto& trajectoryNode : script.second->mTrajectories) {
            if (trajectoryNode->mName == aName) {
                return trajectoryNode->mData;
            }
        }
    }
    return NULL;
}

void DynOS_Lvl_LoadBackground(void *aPtr) {
    // ensure this texture list exists
    GfxData* foundGfxData = NULL;
    DataNode<TexData*>* foundList = NULL;
    for (auto& script : sDynosCustomLevelScripts) {
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
        Print("Could not find custom background");
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
    for (auto& overrideStruct : sDynosOverrideLevelScripts) {
        if (aCmd == overrideStruct.originalScript || aCmd == overrideStruct.newScript) {
            aCmd = (void*)overrideStruct.newScript;
            gLevelScriptModIndex = overrideStruct.gfxData->mModIndex;
            gLevelScriptActive = (LevelScript*)aCmd;
        }
    }
    return aCmd;
}
