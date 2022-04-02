#include "dynos.cpp.h"

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

    // Textures
    for (auto& _Node : aGfxData->mTextures) {
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

    // Level scripts
    for (auto& _Node : aGfxData->mLevelScripts) {
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

    // Vertices
    String _VtxArrayName = "";
    uintptr_t _VtxArrayStart = 0;
    for (auto& _Node : aGfxData->mVertices) {
        if (_Node->mData == aPtr) {
            return { _Node->mName, 0 };
        }
        if ((uintptr_t)_Node->mData <= (uintptr_t)aPtr &&
            (uintptr_t)_Node->mData >= _VtxArrayStart) {
            _VtxArrayName = _Node->mName;
            _VtxArrayStart = (uintptr_t)_Node->mData;
        }
    }
    return { _VtxArrayName, (u32)((const Vtx*)aPtr - (const Vtx*)_VtxArrayStart) };
}

void DynOS_Pointer_Write(FILE* aFile, const void* aPtr, GfxData* aGfxData) {

    // NULL
    if (!aPtr) {
        WriteBytes<u32>(aFile, 0);
        return;
    }

    // Geo function
    s32 _GeoFunctionIndex = DynOS_Geo_GetFunctionIndex(aPtr);
    if (_GeoFunctionIndex != -1) {
        WriteBytes<u32>(aFile, FUNCTION_CODE);
        WriteBytes<s32>(aFile, _GeoFunctionIndex);
        return;
    }

    // Pointer
    PointerData _PtrData = GetDataFromPointer(aPtr, aGfxData);
    WriteBytes<u32>(aFile, POINTER_CODE);
    _PtrData.first.Write(aFile);
    WriteBytes<u32>(aFile, _PtrData.second);
}

  /////////////
 // Reading //
/////////////

static void *GetPointerFromData(GfxData *aGfxData, const String &aPtrName, u32 aPtrData) {

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

    // Textures
    for (auto& _Node : aGfxData->mTextures) {
        if (_Node->mName == aPtrName) {
            return (void *) _Node;
        }
    }

    // Display lists
    for (auto &_Node : aGfxData->mDisplayLists) {
        if (_Node->mName == aPtrName) {
            return (void *) _Node->mData;
        }
    }

    // Geo layouts
    for (auto &_Node : aGfxData->mGeoLayouts) {
        if (_Node->mName == aPtrName) {
            return (void *) _Node->mData;
        }
    }

    // Vertices
    for (auto &_Node : aGfxData->mVertices) {
        if (_Node->mName == aPtrName) {
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
            return (void *) _Node->mData;
        }
    }

    // Macro objects
    for (auto &_Node : aGfxData->mMacroObjects) {
        if (_Node->mName == aPtrName) {
            return (void *) _Node->mData;
        }
    }

    // Error
    sys_fatal("Pointer not found: %s", aPtrName.begin());
    return NULL;
}

void *DynOS_Pointer_Load(FILE *aFile, GfxData *aGfxData, u32 aValue) {

    // FUNC
    if (aValue == FUNCTION_CODE) {
        s32 _GeoFunctionIndex = ReadBytes<s32>(aFile);
        return DynOS_Geo_GetFunctionPointerFromIndex(_GeoFunctionIndex);
    }

    // PNTR
    if (aValue == POINTER_CODE) {
        String _PtrName; _PtrName.Read(aFile);
        u32   _PtrData = ReadBytes<u32>(aFile);
        return GetPointerFromData(aGfxData, _PtrName, _PtrData);
    }

    // Not a pointer
    return NULL;
}
