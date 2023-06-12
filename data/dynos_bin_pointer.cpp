#include "dynos.cpp.h"
extern "C" {
#include "behavior_table.h"
#include "levels/scripts.h"
#include "engine/graph_node.h"
}

  /////////////
 // Writing //
/////////////

typedef Pair<String, u32> PointerData;
static PointerData GetDataFromPointer(const void* aPtr, GfxData* aGfxData) {
    // Lights
    for (auto& _Node : aGfxData->mLights) {
        if (&_Node->mData->l[0] == aPtr) { // Light *, not Lights1 *
            return { _Node->mName, 1 };
        }
        if (&_Node->mData->a == aPtr) { // Ambient *, not Lights1 *
            return { _Node->mName, 2 };
        }
    }

    // Light0s
    for (auto& _Node : aGfxData->mLight0s) {
        if (&_Node->mData->l[0] == aPtr) { // Light *, not Lights1 *
            return { _Node->mName, 1 };
        }
        if (&_Node->mData->a == aPtr) { // Ambient *, not Lights1 *
            return { _Node->mName, 2 };
        }
    }

    // Light_ts
    for (auto& _Node : aGfxData->mLightTs) {
        if (&_Node->mData->col[0] == aPtr) {
            return { _Node->mName, 1 };
        }
        if (&_Node->mData->colc[0] == aPtr) {
            return { _Node->mName, 2 };
        }
        if (&_Node->mData->dir[0] == aPtr) {
            return { _Node->mName, 3 };
        }
    }

    // Ambient_ts
    for (auto& _Node : aGfxData->mAmbientTs) {
        if (&_Node->mData->col[0] == aPtr) {
            return { _Node->mName, 1 };
        }
        if (&_Node->mData->colc[0] == aPtr) {
            return { _Node->mName, 2 };
        }
    }

    // Textures
    for (auto& _Node : aGfxData->mTextures) {
        if (_Node == aPtr) {
            return { _Node->mName, 0 };
        }
    }

    // Texture Lists
    for (auto& _Node : aGfxData->mTextureLists) {
        if (_Node == aPtr) {
            return { _Node->mName, 0 };
        }
    }

    // Display lists
    for (auto& _Node : aGfxData->mDisplayLists) {
        if (_Node == aPtr) {
            return { _Node->mName, 0 };
        }
    }

    // Geo layouts
    for (auto& _Node : aGfxData->mGeoLayouts) {
        if (_Node->mData == aPtr) {
            return { _Node->mName, 0 };
        }
    }
    
    // Collisions
    for (auto& _Node : aGfxData->mCollisions) {
        if (_Node->mData == aPtr) {
            return { _Node->mName, 0 };
        }
    }

    // Macro objects
    for (auto& _Node : aGfxData->mMacroObjects) {
        if (_Node->mData == aPtr) {
            return { _Node->mName, 0 };
        }
    }

    // Trajectories
    for (auto& _Node : aGfxData->mTrajectories) {
        if (_Node->mData == aPtr) {
            return { _Node->mName, 0 };
        }
    }

    // Movtexs
    for (auto& _Node : aGfxData->mMovtexs) {
        if (_Node->mData == aPtr) {
            return { _Node->mName, 0 };
        }
    }

    // MovtexQCs
    for (auto& _Node : aGfxData->mMovtexQCs) {
        if (_Node->mData == aPtr) {
            return { _Node->mName, 0 };
        }
    }

    // Rooms
    for (auto& _Node : aGfxData->mRooms) {
        if (_Node->mData == aPtr) {
            return { _Node->mName, 0 };
        }
    }

    // Behaviors
    enum BehaviorId id = get_id_from_vanilla_behavior((const BehaviorScript*) aPtr);
    if (id >= 0 && id < id_bhv_max_count) {
        return { get_behavior_name_from_id(id), 0 };
    }

    // Built-in Actors
    auto builtinActor = DynOS_Builtin_Actor_GetFromData((const GeoLayout*)aPtr);
    if (builtinActor != NULL) {
        return { builtinActor, 0 };
    }

    // Built-in Lvl Geos
    auto builtinGeo = DynOS_Builtin_LvlGeo_GetFromData((const GeoLayout*)aPtr);
    if (builtinGeo != NULL) {
        return { builtinGeo, 0 };
    }

    // Built-in Cols
    auto builtinCol = DynOS_Builtin_Col_GetFromData((const Collision*)aPtr);
    if (builtinCol != NULL) {
        return { builtinCol, 0 };
    }
    
    // Built-in Animations
    auto builtinAnim = DynOS_Builtin_Anim_GetFromData((const Animation *)aPtr);
    if (builtinAnim != NULL) {
        return { builtinAnim, 0 };
    }

    // Built-in Script Pointers
    auto builtinScriptPtr = DynOS_Builtin_ScriptPtr_GetFromData(aPtr);
    if (builtinScriptPtr != NULL) {
        return { builtinScriptPtr, 0 };
    }

    // Built-in Textures
    auto builtinTex = DynOS_Builtin_Tex_GetFromData((const Texture*)aPtr);
    if (builtinTex != NULL) {
        return { builtinTex, 0 };
    }

    // the ones below use a saved offset

    s32 _Offset = 0;
    for (auto& pair : aGfxData->mPointerOffsetList) {
        if (pair.first == aPtr) {
            _Offset = (s32)((u8*)pair.first - (u8*)pair.second);
            aPtr = pair.second;
            break;
        }
    }

    // Level scripts
    for (auto& _Node : aGfxData->mLevelScripts) {
        if (_Node->mData == aPtr) {
            return { _Node->mName, _Offset };
        }
    }

    // Vertices
    String _VtxArrayName = "";
    uintptr_t _VtxArrayStart = 0;
    for (auto& _Node : aGfxData->mVertices) {
        if (_Node->mData == aPtr) {
            return { _Node->mName, _Offset };
        }
    }

    PrintDataError("Unable to find pointer %x!", aPtr);
    return { "", 0 };
}

void DynOS_Pointer_Lua_Write(BinFile* aFile, u32 index, GfxData* aGfxData) {
    String& token = aGfxData->mLuaTokenList[index];
    aFile->Write<u32>(LUA_VAR_CODE);
    token.Write(aFile);
}

void DynOS_Pointer_Write(BinFile* aFile, const void* aPtr, GfxData* aGfxData) {

    // NULL
    if (!aPtr) {
        aFile->Write<u32>(0);
        return;
    }

    // Lua variable
    for (s32 i = 0; i < aGfxData->mLuaPointerList.Count(); i++) {
        if (aPtr == aGfxData->mLuaPointerList[i]) {
            u32 index = *((u32*)aPtr);
            String& token = aGfxData->mLuaTokenList[index];
            aFile->Write<u32>(LUA_VAR_CODE);
            token.Write(aFile);
            return;
        }
    }

    // Built-in functions
    s32 _GeoFunctionIndex = DynOS_Builtin_Func_GetIndexFromData(aPtr);
    if (_GeoFunctionIndex != -1) {
        aFile->Write<u32>(FUNCTION_CODE);
        aFile->Write<s32>(_GeoFunctionIndex);
        return;
    }

    // Pointer
    PointerData _PtrData = GetDataFromPointer(aPtr, aGfxData);
    aFile->Write<u32>(POINTER_CODE);
    _PtrData.first.Write(aFile);
    aFile->Write<u32>(_PtrData.second);
}

  /////////////
 // Reading //
/////////////

static void *GetPointerFromData(GfxData *aGfxData, const String &aPtrName, u32 aPtrData, u8* outFlags) {

    // Lights
    for (auto& _Node : aGfxData->mLights) {
        if (_Node->mName == aPtrName) {
            if (aPtrData == 1) {
                return (void *) &_Node->mData->l[0];
            }
            if (aPtrData == 2) {
                return (void *) &_Node->mData->a;
            }
            sys_fatal("Unknown Light type: %u", aPtrData);
        }
    }

    // Light0s
    for (auto& _Node : aGfxData->mLight0s) {
        if (_Node->mName == aPtrName) {
            if (aPtrData == 1) {
                return (void *) &_Node->mData->l[0];
            }
            if (aPtrData == 2) {
                return (void *) &_Node->mData->a;
            }
            sys_fatal("Unknown Light type: %u", aPtrData);
        }
    }

    // Light_ts
    for (auto& _Node : aGfxData->mLightTs) {
        if (_Node->mName == aPtrName) {
            if (aPtrData == 1) {
                return (void *) &_Node->mData->col[0];
            }
            if (aPtrData == 2) {
                return (void *) &_Node->mData->colc[0];
            }
            if (aPtrData == 3) {
                return (void *) &_Node->mData->dir[0];
            }
            sys_fatal("Unknown Light type: %u", aPtrData);
        }
    }

    // Ambient_ts
    for (auto& _Node : aGfxData->mAmbientTs) {
        if (_Node->mName == aPtrName) {
            if (aPtrData == 1) {
                return (void *) &_Node->mData->col[0];
            }
            if (aPtrData == 2) {
                return (void *) &_Node->mData->colc[0];
            }
            sys_fatal("Unknown Light type: %u", aPtrData);
        }
    }

    // Textures
    for (auto& _Node : aGfxData->mTextures) {
        if (_Node->mName == aPtrName) {
            return (void *) _Node;
        }
    }

    // Texture Lists
    for (auto& _Node : aGfxData->mTextureLists) {
        if (_Node->mName == aPtrName) {
            return (void *) _Node;
        }
    }

    // Display lists
    for (auto &_Node : aGfxData->mDisplayLists) {
        if (_Node->mName == aPtrName) {
            *outFlags |= _Node->mFlags;
            return (void *) _Node->mData;
        }
    }

    // Geo layouts
    for (auto &_Node : aGfxData->mGeoLayouts) {
        if (_Node->mName == aPtrName) {
            *outFlags |= _Node->mFlags;
            return (void *) _Node->mData;
        }
    }

    // Vertices
    for (auto &_Node : aGfxData->mVertices) {
        if (_Node->mName == aPtrName) {
            *outFlags |= _Node->mFlags;
            return (void *) (_Node->mData + aPtrData);
        }
    }

    // Collisions
    for (auto &_Node : aGfxData->mCollisions) {
        if (_Node->mName == aPtrName) {
            return (void *) _Node->mData;
        }
    }

    // Level scripts
    for (auto &_Node : aGfxData->mLevelScripts) {
        if (_Node->mName == aPtrName) {
            return (void *) (_Node->mData + aPtrData);
        }
    }
    
    // Behavior scripts
    for (auto &_Node : aGfxData->mBehaviorScripts) {
        if (_Node->mName == aPtrName) {
            return (void *) _Node->mData;
        }
    }

    // Macro objects
    for (auto &_Node : aGfxData->mMacroObjects) {
        if (_Node->mName == aPtrName) {
            return (void *) _Node->mData;
        }
    }

    // Trajectories
    for (auto &_Node : aGfxData->mTrajectories) {
        if (_Node->mName == aPtrName) {
            return (void *) _Node->mData;
        }
    }

    // Movtexs
    for (auto &_Node : aGfxData->mMovtexs) {
        if (_Node->mName == aPtrName) {
            return (void *) _Node->mData;
        }
    }

    // MovtexQCs
    for (auto &_Node : aGfxData->mMovtexQCs) {
        if (_Node->mName == aPtrName) {
            return (void *) _Node->mData;
        }
    }

    // Rooms
    for (auto &_Node : aGfxData->mRooms) {
        if (_Node->mName == aPtrName) {
            return (void *) _Node->mData;
        }
    }

    // Lua Behaviors
    enum BehaviorId id = get_id_from_behavior_name(aPtrName.begin());
    if (id >= 0 && id < id_bhv_max_count) {
        return (void*)get_behavior_from_id(id);
    }

    // Built-in Actors
    auto builtinActor = DynOS_Builtin_Actor_GetFromName(aPtrName.begin());
    if (builtinActor != NULL) {
        return (void*)builtinActor;
    }

    // Built-in Lvl Geos
    auto builtinGeo = DynOS_Builtin_LvlGeo_GetFromName(aPtrName.begin());
    if (builtinGeo != NULL) {
        return (void*)builtinGeo;
    }

    // Built-in Cols
    auto builtinCol = DynOS_Builtin_Col_GetFromName(aPtrName.begin());
    if (builtinCol != NULL) {
        return (void*)builtinCol;
    }
    
    // Built-in Animations
    auto builtinAnim = DynOS_Builtin_Anim_GetFromName(aPtrName.begin());
    if (builtinAnim != NULL) {
        return (void *)builtinAnim;
    }

    // Built-in Script Pointers
    auto builtinScriptPtr = DynOS_Builtin_ScriptPtr_GetFromName(aPtrName.begin());
    if (builtinScriptPtr != NULL) {
        return (void*)builtinScriptPtr;
    }

    // Built-in Textures
    auto builtinTex = DynOS_Builtin_Tex_GetFromName(aPtrName.begin());
    if (builtinTex != NULL) {
        return (void*)builtinTex;
    }

    // Error
    sys_fatal("Pointer not found: %s", aPtrName.begin());
    return NULL;
}

void *DynOS_Pointer_Load(BinFile *aFile, GfxData *aGfxData, u32 aValue, u8* outFlags) {

    // LUAV
    if (aValue == LUA_VAR_CODE) {
        String token; token.Read(aFile);
        for (s32 i = 0; i < aGfxData->mLuaTokenList.Count(); i++) {
            if (token == aGfxData->mLuaTokenList[i]) {
                return (void*)(uintptr_t)(i+1);
            }
        }
        u32 index = aGfxData->mLuaTokenList.Count();
        aGfxData->mLuaTokenList.Add(token);
        return (void*)(uintptr_t)(index+1);
    }

    // FUNC
    if (aValue == FUNCTION_CODE) {
        s32 _FunctionIndex = aFile->Read<s32>();
        return (void*) DynOS_Builtin_Func_GetFromIndex(_FunctionIndex);
    }

    // PNTR
    if (aValue == POINTER_CODE) {
        String _PtrName; _PtrName.Read(aFile);
        u32   _PtrData = aFile->Read<u32>();
        return GetPointerFromData(aGfxData, _PtrName, _PtrData, outFlags);
    }

    // Not a pointer
    return NULL;
}
