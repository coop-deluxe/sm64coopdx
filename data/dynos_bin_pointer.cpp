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
static PointerData GetDataFromPointer(const void* aPtr, GfxData* aGfxData, u32 aPtrType) {
    // Lights
    if (aPtrType & PTYPE_PNTR_LIGHT) {
        for (auto& _Node : aGfxData->mLights) {
            if (!_Node->mData) { continue; }
            if (&_Node->mData->l[0] == aPtr) { // Light *, not Lights1 *
                return { _Node->mName, 1 };
            }
            if (&_Node->mData->a == aPtr) { // Ambient *, not Lights1 *
                return { _Node->mName, 2 };
            }
        }
    }

    // Light0s
    if (aPtrType & PTYPE_PNTR_LIGHT0) {
        for (auto& _Node : aGfxData->mLight0s) {
            if (!_Node->mData) { continue; }
            if (&_Node->mData->l[0] == aPtr) { // Light *, not Lights1 *
                return { _Node->mName, 1 };
            }
            if (&_Node->mData->a == aPtr) { // Ambient *, not Lights1 *
                return { _Node->mName, 2 };
            }
        }
    }

    // Light_ts
    if (aPtrType & PTYPE_PNTR_LIGHTT) {
        for (auto& _Node : aGfxData->mLightTs) {
            if (!_Node->mData) { continue; }
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
    }

    // Ambient_ts
    if (aPtrType & PTYPE_PNTR_AMBIENTT) {
        for (auto& _Node : aGfxData->mAmbientTs) {
            if (!_Node->mData) { continue; }
            if (&_Node->mData->col[0] == aPtr) {
                return { _Node->mName, 1 };
            }
            if (&_Node->mData->colc[0] == aPtr) {
                return { _Node->mName, 2 };
            }
        }
    }

    // Textures
    if (aPtrType & PTYPE_PNTR_TEX) {
        for (auto& _Node : aGfxData->mTextures) {
            if (_Node == aPtr) {
                return { _Node->mName, 0 };
            }
        }
    }

    // Texture Lists
    if (aPtrType & PTYPE_PNTR_TEXLIST) {
        for (auto& _Node : aGfxData->mTextureLists) {
            if (_Node == aPtr) {
                return { _Node->mName, 0 };
            }
        }
    }

    // Display lists
    if (aPtrType & PTYPE_PNTR_GFX) {
        for (auto& _Node : aGfxData->mDisplayLists) {
            if (_Node == aPtr) {
                return { _Node->mName, 0 };
            }
        }
    }

    // Geo layouts
    if (aPtrType & PTYPE_PNTR_GEO) {
        for (auto& _Node : aGfxData->mGeoLayouts) {
            if (_Node->mData == aPtr) {
                return { _Node->mName, 0 };
            }
        }
    }

    // Collisions
    if (aPtrType & PTYPE_PNTR_COL) {
        for (auto& _Node : aGfxData->mCollisions) {
            if (_Node->mData == aPtr) {
                return { _Node->mName, 0 };
            }
        }
    }

    // Macro objects
    if (aPtrType & PTYPE_PNTR_MACRO) {
        for (auto& _Node : aGfxData->mMacroObjects) {
            if (_Node->mData == aPtr) {
                return { _Node->mName, 0 };
            }
        }
    }

    // Trajectories
    if (aPtrType & PTYPE_PNTR_TRAJ) {
        for (auto& _Node : aGfxData->mTrajectories) {
            if (_Node->mData == aPtr) {
                return { _Node->mName, 0 };
            }
        }
    }

    // Movtexs
    if (aPtrType & PTYPE_PNTR_MOVTEX) {
        for (auto& _Node : aGfxData->mMovtexs) {
            if (_Node->mData == aPtr) {
                return { _Node->mName, 0 };
            }
        }
    }

    // MovtexQCs
    if (aPtrType & PTYPE_PNTR_MOVTEXQC) {
        for (auto& _Node : aGfxData->mMovtexQCs) {
            if (_Node->mData == aPtr) {
                return { _Node->mName, 0 };
            }
        }
    }

    // Rooms
    if (aPtrType & PTYPE_PNTR_ROOM) {
        for (auto& _Node : aGfxData->mRooms) {
            if (_Node->mData == aPtr) {
                return { _Node->mName, 0 };
            }
        }
    }

    // Behaviors
    if (aPtrType & PTYPE_PNTR_BHV) {
        enum BehaviorId id = get_id_from_vanilla_behavior((const BehaviorScript*) aPtr);
        if (id >= 0 && id < id_bhv_max_count) {
            return { get_behavior_name_from_id(id), 0 };
        }
    }

    // Built-in Actors
    if (aPtrType & PTYPE_PNTR_GEO) {
        auto builtinActor = DynOS_Builtin_Actor_GetFromData((const GeoLayout*)aPtr);
        if (builtinActor != NULL) {
            return { builtinActor, 0 };
        }
    }

    // Built-in Level Macros
    if (aPtrType & PTYPE_PNTR_MACRO) {
        auto builtinLvlMacro = DynOS_Builtin_LvlMacro_GetFromData((const MacroObject*)aPtr);
        if (builtinLvlMacro != NULL) {
            return { builtinLvlMacro, 0 };
        }
    }

    // Built-in Lvl Geos
    if (aPtrType & PTYPE_PNTR_GEO) {
        auto builtinGeo = DynOS_Builtin_LvlGeo_GetFromData((const GeoLayout*)aPtr);
        if (builtinGeo != NULL) {
            return { builtinGeo, 0 };
        }
    }

    // Built-in Cols
    if (aPtrType & PTYPE_PNTR_COL) {
        auto builtinCol = DynOS_Builtin_Col_GetFromData((const Collision*)aPtr);
        if (builtinCol != NULL) {
            return { builtinCol, 0 };
        }
    }

    // Built-in Animations
    if (aPtrType & PTYPE_PNTR_ANIM) {
        auto builtinAnim = DynOS_Builtin_Anim_GetFromData((const Animation *)aPtr);
        if (builtinAnim != NULL) {
            return { builtinAnim, 0 };
        }
    }

    // Built-in Script Pointers
    if (aPtrType & PTYPE_PNTR_LVL) {
        auto builtinScriptPtr = DynOS_Builtin_ScriptPtr_GetFromData(aPtr);
        if (builtinScriptPtr != NULL) {
            return { builtinScriptPtr, 0 };
        }
    }

    // Built-in Textures
    if (aPtrType & PTYPE_PNTR_TEX) {
        auto builtinTex = DynOS_Builtin_Tex_GetFromData((const Texture*)aPtr);
        if (builtinTex != NULL) {
            return { builtinTex, 0 };
        }
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
    if (aPtrType & PTYPE_PNTR_LVL) {
        for (auto& _Node : aGfxData->mLevelScripts) {
            if (_Node->mData == aPtr) {
                return { _Node->mName, _Offset };
            }
        }
    }

    // Vertices
    if (aPtrType & PTYPE_PNTR_VTX) {
        for (auto& _Node : aGfxData->mVertices) {
            if (_Node->mData == aPtr) {
                return { _Node->mName, _Offset };
            }
        }
    }

    PrintDataError("  ERROR: Unable to find pointer: %x", aPtr);
    return { "", 0 };
}

void DynOS_Pointer_Lua_Write(BinFile* aFile, u32 index, GfxData* aGfxData) {
    String& token = aGfxData->mLuaTokenList[index];
    aFile->Write<u32>(LUA_VAR_CODE);
    token.Write(aFile);
}

void DynOS_Pointer_Write(BinFile* aFile, const void* aPtr, GfxData* aGfxData, u32 aPtrType) {

    // NULL
    if (!aPtr) {
        aFile->Write<u32>(0);
        return;
    }

    // Lua variable
    if (aPtrType & PTYPE_LUAV) {
        for (s32 i = 0; i < aGfxData->mLuaPointerList.Count(); i++) {
            if (aPtr == aGfxData->mLuaPointerList[i]) {
                u32 index = *((u32*)aPtr);
                String& token = aGfxData->mLuaTokenList[index];
                aFile->Write<u32>(LUA_VAR_CODE);
                token.Write(aFile);
                return;
            }
        }
    }

    // Built-in functions
    if (aPtrType & PTYPE_FUNC) {
        s32 _FunctionIndex = DynOS_Builtin_Func_GetIndexFromData(aPtr, aPtrType);
        if (_FunctionIndex != -1) {
            aFile->Write<u32>(FUNCTION_CODE);
            aFile->Write<s32>(_FunctionIndex);
            return;
        }
        String error = DynOS_Builtin_Func_CheckMisuse(aPtr, aPtrType);
        if (!error.Empty()) {
            PrintDataError("  ERROR: %s", error.begin());
            return;
        }
    }

    // Pointer
    if (aPtrType & PTYPE_PNTR) {
        PointerData _PtrData = GetDataFromPointer(aPtr, aGfxData, aPtrType);
        aFile->Write<u32>(POINTER_CODE);
        _PtrData.first.Write(aFile);
        aFile->Write<u32>(_PtrData.second);
        return;
    }

    // No valid pointer
    PrintDataError("  ERROR: Not a valid pointer: %x", aPtr);
}

  /////////////
 // Reading //
/////////////

static void *GetPointerFromData(GfxData *aGfxData, const String &aPtrName, u32 aPtrData, u32 aPtrTypes, u8* outFlags) {

    // Lights
    if (aPtrTypes & PTYPE_PNTR_LIGHT) {
        auto _Node = aGfxData->mLights.Find(aPtrName);
        if (_Node) {
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
    if (aPtrTypes & PTYPE_PNTR_LIGHT0) {
        auto _Node = aGfxData->mLight0s.Find(aPtrName);
        if (_Node) {
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
    if (aPtrTypes & PTYPE_PNTR_LIGHTT) {
        auto _Node = aGfxData->mLightTs.Find(aPtrName);
        if (_Node) {
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
    if (aPtrTypes & PTYPE_PNTR_AMBIENTT) {
        auto _Node = aGfxData->mAmbientTs.Find(aPtrName);
        if (_Node) {
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
    if (aPtrTypes & PTYPE_PNTR_TEX) {
        auto _Node = aGfxData->mTextures.Find(aPtrName);
        if (_Node) {
            return (void *) _Node;
        }
    }

    // Texture Lists
    if (aPtrTypes & PTYPE_PNTR_TEXLIST) {
        auto _Node = aGfxData->mTextureLists.Find(aPtrName);
        if (_Node) {
            return (void *) _Node;
        }
    }

    // Display lists
    if (aPtrTypes & PTYPE_PNTR_GFX) {
        auto _Node = aGfxData->mDisplayLists.Find(aPtrName);
        if (_Node) {
            *outFlags |= _Node->mFlags;
            return (void *) _Node->mData;
        }
    }

    // Geo layouts
    if (aPtrTypes & PTYPE_PNTR_GEO) {
        auto _Node = aGfxData->mGeoLayouts.Find(aPtrName);
        if (_Node) {
            *outFlags |= _Node->mFlags;
            return (void *) _Node->mData;
        }
    }

    // Vertices
    if (aPtrTypes & PTYPE_PNTR_VTX) {
        auto _Node = aGfxData->mVertices.Find(aPtrName);
        if (_Node) {
            if (aPtrData >= _Node->mSize) {
                sys_fatal("Vertices offset %u larger than buffer size %u", aPtrData, _Node->mSize);
            }
            *outFlags |= _Node->mFlags;
            return (void *) (_Node->mData + aPtrData);
        }
    }

    // Collisions
    if (aPtrTypes & PTYPE_PNTR_COL) {
        auto _Node = aGfxData->mCollisions.Find(aPtrName);
        if (_Node) {
            return (void *) _Node->mData;
        }
    }

    // Level scripts
    if (aPtrTypes & PTYPE_PNTR_LVL) {
        auto _Node = aGfxData->mLevelScripts.Find(aPtrName);
        if (_Node) {
            if (aPtrData >= _Node->mSize) {
                sys_fatal("Level script offset %u larger than buffer size %u", aPtrData, _Node->mSize);
            }
            return (void *) (_Node->mData + aPtrData);
        }
    }

    // Behavior scripts
    if (aPtrTypes & PTYPE_PNTR_BHV) {
        auto _Node = aGfxData->mBehaviorScripts.Find(aPtrName);
        if (_Node) {
            return (void *) _Node->mData;
        }
    }

    // Macro objects
    if (aPtrTypes & PTYPE_PNTR_MACRO) {
        auto _Node = aGfxData->mMacroObjects.Find(aPtrName);
        if (_Node) {
            return (void *) _Node->mData;
        }
    }

    // Trajectories
    if (aPtrTypes & PTYPE_PNTR_TRAJ) {
        auto _Node = aGfxData->mTrajectories.Find(aPtrName);
        if (_Node) {
            return (void *) _Node->mData;
        }
    }

    // Movtexs
    if (aPtrTypes & PTYPE_PNTR_MOVTEX) {
        auto _Node = aGfxData->mMovtexs.Find(aPtrName);
        if (_Node) {
            return (void *) _Node->mData;
        }
    }

    // MovtexQCs
    if (aPtrTypes & PTYPE_PNTR_MOVTEXQC) {
        auto _Node = aGfxData->mMovtexQCs.Find(aPtrName);
        if (_Node) {
            return (void *) _Node->mData;
        }
    }

    // Rooms
    if (aPtrTypes & PTYPE_PNTR_ROOM) {
        auto _Node = aGfxData->mRooms.Find(aPtrName);
        if (_Node) {
            return (void *) _Node->mData;
        }
    }

    // Lua Behaviors
    if (aPtrTypes & PTYPE_PNTR_BHV) {
        enum BehaviorId id = get_id_from_behavior_name(aPtrName.begin());
        if (id >= 0 && id < id_bhv_max_count) {
            return (void*)get_behavior_from_id(id);
        }
    }

    // Built-in Actors
    if (aPtrTypes & PTYPE_PNTR_GEO) {
        auto builtinActor = DynOS_Builtin_Actor_GetFromName(aPtrName.begin());
        if (builtinActor != NULL) {
            return (void*)builtinActor;
        }
    }

    // Built-in Lvl Macros
    if (aPtrTypes & PTYPE_PNTR_MACRO) {
        auto builtinLvlMacro = DynOS_Builtin_LvlMacro_GetFromName(aPtrName.begin());
        if (builtinLvlMacro != NULL) {
            return (void*)builtinLvlMacro;
        }
    }

    // Built-in Lvl Geos
    if (aPtrTypes & PTYPE_PNTR_GEO) {
        auto builtinGeo = DynOS_Builtin_LvlGeo_GetFromName(aPtrName.begin());
        if (builtinGeo != NULL) {
            return (void*)builtinGeo;
        }
    }

    // Built-in Cols
    if (aPtrTypes & PTYPE_PNTR_COL) {
        auto builtinCol = DynOS_Builtin_Col_GetFromName(aPtrName.begin());
        if (builtinCol != NULL) {
            return (void*)builtinCol;
        }
    }

    // Built-in Animations
    if (aPtrTypes & PTYPE_PNTR_ANIM) {
        auto builtinAnim = DynOS_Builtin_Anim_GetFromName(aPtrName.begin());
        if (builtinAnim != NULL) {
            return (void *)builtinAnim;
        }
    }

    // Built-in Script Pointers
    if (aPtrTypes & PTYPE_PNTR_LVL) {
        auto builtinScriptPtr = DynOS_Builtin_ScriptPtr_GetFromName(aPtrName.begin());
        if (builtinScriptPtr != NULL) {
            return (void*)builtinScriptPtr;
        }
    }

    // Built-in Textures
    if (aPtrTypes & PTYPE_PNTR_TEX) {
        auto builtinTex = DynOS_Builtin_Tex_GetFromName(aPtrName.begin());
        if (builtinTex != NULL) {
            return (void*)builtinTex;
        }
    }

    // Error
    sys_fatal("Pointer not found: %s", aPtrName.begin());
    return NULL;
}

void *DynOS_Pointer_Load(BinFile *aFile, GfxData *aGfxData, u32 aValue, u32 aPtrTypes, u8* outFlags) {

    // LUAV
    if (aValue == LUA_VAR_CODE) {
        if (!(aPtrTypes & PTYPE_LUAV)) {
            PrintDataError("  ERROR: Invalid use of a LUAV pointer");
            return NULL;
        }
        String token; token.Read(aFile);
        if (aGfxData->mModIndex == PACK_MOD_INDEX) {
            PrintDataError("  ERROR: Invalid use of Lua function in DynOS pack: %s", token.begin());
            return NULL;
        }
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
        if (!(aPtrTypes & PTYPE_FUNC)) {
            PrintDataError("  ERROR: Invalid use of a FUNC pointer");
            return NULL;
        }
        s32 _FunctionIndex = aFile->Read<s32>();
        void *_FunctionPtr = (void*) DynOS_Builtin_Func_GetFromIndex(_FunctionIndex, aPtrTypes & PTYPE_FUNC);
        if (_FunctionPtr) {
            return _FunctionPtr;
        }
        String error = DynOS_Builtin_Func_CheckMisuse(_FunctionIndex, aPtrTypes & PTYPE_FUNC);
        if (!error.Empty()) {
            sys_fatal(error.begin());
            return NULL;
        }
        sys_fatal("Invalid function index: %d", _FunctionIndex);
        return NULL;
    }

    // PNTR
    if (aValue == POINTER_CODE) {
        if (!(aPtrTypes & PTYPE_PNTR)) {
            PrintDataError("  ERROR: Invalid use of a PNTR pointer");
            return NULL;
        }
        String _PtrName; _PtrName.Read(aFile);
        u32 _PtrData = aFile->Read<u32>();
        return GetPointerFromData(aGfxData, _PtrName, _PtrData, aPtrTypes, outFlags);
    }

    // Not a pointer
    return NULL;
}
