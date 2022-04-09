#include "dynos.cpp.h"
extern "C" {
#include "engine/level_script.h"
#include "game/skybox.h"
}

static Array<Pair<const char*, GfxData*>> sDynosCustomLevelScripts;
static Array<Pair<const void*, const void*>> sDynosOverrideLevelScripts;

Array<Pair<const char*, GfxData*>> &DynOS_Lvl_GetArray() {
    return sDynosCustomLevelScripts;
}

void DynOS_Lvl_Activate(s32 modIndex, const SysPath &aPackFolder, const char *aLevelName) {
    // check for duplicates
    for (s32 i = 0; i < sDynosCustomLevelScripts.Count(); ++i) {
        if (!strcmp(sDynosCustomLevelScripts[i].first, aLevelName)) {
            return;
        }
    }

    u16 levelLen = strlen(aLevelName);
    char* levelName = (char*)calloc(1, sizeof(char) * (levelLen + 1));
    strcpy(levelName, aLevelName);

    GfxData* _Node = DynOS_Lvl_LoadFromBinary(aPackFolder, levelName);
    if (!_Node) {
        free(levelName);
        return;
    }

    // remember index
    _Node->mModIndex = modIndex;

    // Add to levels
    sDynosCustomLevelScripts.Add({ levelName, _Node });

    // Override vanilla script
    auto& newScripts = _Node->mLevelScripts; // DO NOT COMMIT
    auto& newScriptNode = newScripts[newScripts.Count() - 1];
    const void* originalScript = DynOS_Builtin_ScriptPtr_GetFromName(newScriptNode->mName.begin());
    if (originalScript == NULL) {
        Print("Could not find level to override: '%s'", newScriptNode->mName);
        return;
    }

    DynOS_Level_Override((void*)originalScript, newScriptNode->mData);
    sDynosOverrideLevelScripts.Add({ originalScript, newScriptNode->mData});
}

DataNode<TexData> *DynOS_Lvl_GetTexture(void *aPtr) {
    for (s32 i = 0; i < sDynosCustomLevelScripts.Count(); ++i) {
        auto &mTextures = sDynosCustomLevelScripts[i].second->mTextures;
        for (s32 j = 0; j < mTextures.Count(); j++) {
            auto &texture = mTextures[j];
            if (texture == aPtr) {
                return texture;
            }

        }
    }
    return NULL;
}

static GfxData* DynOS_Lvl_GetActiveGfx(void) {
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

DataNode<MovtexQC> *DynOS_Lvl_GetMovtexQuadCollection(s32 index) {
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
    for (auto& overridePair : sDynosOverrideLevelScripts) {
        if (aCmd == overridePair.first || aCmd == overridePair.second) {
            aCmd = (void*)overridePair.second;
            for (auto& customPair : sDynosCustomLevelScripts) {
                gLevelScriptModIndex = customPair.second->mModIndex;
                gLevelScriptActive = (LevelScript*)aCmd;
            }
        }
    }
    return aCmd;
}
