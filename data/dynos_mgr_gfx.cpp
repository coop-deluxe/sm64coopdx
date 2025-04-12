#include "dynos.cpp.h"

extern "C" {
#include "pc/lua/smlua.h"
#include "pc/lua/utils/smlua_gfx_utils.h"
}

static ModData<Gfx> sModDisplayLists;
static ModData<Vtx> sModVertexBuffers;

// Maps read-only Gfx and Vtx buffers to their writable duplicates
static std::map<const void *, std::pair<void *, size_t>> sRomToRamGfxVtxMap;

static Vtx *DynOS_Vtx_Duplicate(Vtx *aVtx, u32 vtxCount, bool shouldDuplicate) {
    if (!aVtx) { return NULL; }

    // Return duplicate if it already exists
    auto it = sRomToRamGfxVtxMap.find(aVtx);
    if (it != sRomToRamGfxVtxMap.end()) {
        return (Vtx *) it->second.first;
    }

    // Duplicate vertex buffer and return the copy
    if (shouldDuplicate) {
        size_t vtxSize = vtxCount * sizeof(Vtx);
        Vtx *vtxDuplicate = vtx_allocate_internal(vtxCount);
        memcpy(vtxDuplicate, aVtx, vtxSize);
        DynOS_Find_Pending_Scroll_Target(aVtx, vtxDuplicate);
        sRomToRamGfxVtxMap[aVtx] = { (void *) vtxDuplicate, vtxSize };
        return vtxDuplicate;
    }

    return aVtx;
}

static Gfx *DynOS_Gfx_Duplicate(Gfx *aGfx, bool shouldDuplicate) {
    if (!aGfx) { return NULL; }

    // Return duplicate if it already exists
    auto it = sRomToRamGfxVtxMap.find(aGfx);
    if (it != sRomToRamGfxVtxMap.end()) {
        return (Gfx *) it->second.first;
    }

    // Check if it's vanilla
    if (!shouldDuplicate) {
        shouldDuplicate = (DynOS_Builtin_Gfx_GetFromData(aGfx) != NULL);
    }

    // Duplicate display list
    Gfx *gfxDuplicate = aGfx;
    u32 gfxLength = shouldDuplicate ? gfx_get_length_no_sentinel(aGfx) : gfx_get_length(aGfx);
    if (shouldDuplicate) {
        size_t gfxSize = gfxLength * sizeof(Gfx);
        gfxDuplicate = gfx_allocate_internal(gfxLength);
        memcpy(gfxDuplicate, aGfx, gfxSize);
        sRomToRamGfxVtxMap[aGfx] = { (void *) gfxDuplicate, gfxSize };
    }

    // Look for other display lists or vertices
    for (u32 i = 0; i < gfxLength; i++) {
        Gfx *cmd = gfxDuplicate + i;
        u32 op = GFX_OP(cmd);

        // Duplicate referenced display lists
        if (op == G_DL) {
            cmd->words.w1 = (uintptr_t) DynOS_Gfx_Duplicate((Gfx *) cmd->words.w1, shouldDuplicate);
            if (C0(cmd, 16, 1) == G_DL_NOPUSH) { break; } // This is a branch (jump), end of display list
        }

        // Duplicate referenced vertices
        if (op == G_VTX) {
            cmd->words.w1 = (uintptr_t) DynOS_Vtx_Duplicate((Vtx *) cmd->words.w1, C0(cmd, 12, 8), shouldDuplicate);
        }
    }

    return gfxDuplicate;
}

// Get a writable display list so it can be modified by mods
// If it's a vanilla display list, duplicate it, so it can be restored later
Gfx *DynOS_Gfx_GetWritableDisplayList(Gfx *aGfx) {
    return DynOS_Gfx_Duplicate(aGfx, false);
}

Gfx *DynOS_Gfx_Get(const char *aName, u32 *outLength) {
    if (!aName) { return NULL; }
    s32 modIndex = (gLuaActiveMod ? gLuaActiveMod->index : -1);

    // Check mod data
    Gfx *gfx = DynOS_ModData_Get<Gfx>(sModDisplayLists, modIndex, aName, outLength);
    if (gfx) {
        return gfx;
    }

    // Check levels
    for (auto &lvl : DynOS_Lvl_GetArray()) {
        if (modIndex == -1 || lvl.second->mModIndex == modIndex) {
            for (auto &gfx : lvl.second->mDisplayLists) {
                if (gfx->mName == aName) {
                    *outLength = gfx->mSize;
                    return gfx->mData;
                }
            }
        }
    }

    // Check loaded actors
    for (auto &actor : DynOS_Actor_GetValidActors()) {
        if (modIndex == -1 || actor.second.mGfxData->mModIndex == modIndex) {
            for (auto &gfx : actor.second.mGfxData->mDisplayLists) {
                if (gfx->mName == aName) {
                    *outLength = gfx->mSize;
                    return gfx->mData;
                }
            }
        }
    }

    // Check vanilla display lists
    const Gfx *gfxVanilla = DynOS_Builtin_Gfx_GetFromName(aName);
    if (gfxVanilla) {
        auto it = sRomToRamGfxVtxMap.find(gfxVanilla);

        // If not found, duplicate the display list now
        if (it == sRomToRamGfxVtxMap.end()) {
            DynOS_Gfx_Duplicate((Gfx *) gfxVanilla, true);
            it = sRomToRamGfxVtxMap.find(gfxVanilla);
        }

        *outLength = it->second.second / sizeof(Gfx);
        return (Gfx *) it->second.first;
    }

    return NULL;
}

Gfx *DynOS_Gfx_New(const char *aName, u32 aLength) {
    if (!aName || !aLength) { return NULL; }
    s32 modIndex = (gLuaActiveMod ? gLuaActiveMod->index : -1);

    return DynOS_ModData_New(sModDisplayLists, modIndex, aName, aLength, gfx_allocate_internal);
}

Gfx *DynOS_Gfx_Realloc(Gfx *aGfx, u32 aNewLength) {
    if (!aGfx || !aNewLength) { return NULL; }
    s32 modIndex = (gLuaActiveMod ? gLuaActiveMod->index : -1);

    return DynOS_ModData_Realloc(sModDisplayLists, modIndex, aGfx, aNewLength, gfx_allocate_internal, free);
}

bool DynOS_Gfx_Delete(Gfx *aGfx) {
    if (!aGfx) { return false; }
    s32 modIndex = (gLuaActiveMod ? gLuaActiveMod->index : -1);

    return DynOS_ModData_Delete(sModDisplayLists, modIndex, aGfx, free);
}

Vtx *DynOS_Vtx_Get(const char *aName, u32 *outCount) {
    if (!aName) { return NULL; }
    s32 modIndex = (gLuaActiveMod ? gLuaActiveMod->index : -1);

    // Check mod data
    Vtx *vtx = DynOS_ModData_Get<Vtx>(sModVertexBuffers, modIndex, aName, outCount);
    if (vtx) {
        return vtx;
    }

    // Check levels
    for (auto &lvl : DynOS_Lvl_GetArray()) {
        if (modIndex == -1 || lvl.second->mModIndex == modIndex) {
            for (auto &vtx : lvl.second->mVertices) {
                if (vtx->mName == aName) {
                    *outCount = vtx->mSize;
                    return vtx->mData;
                }
            }
        }
    }

    // Check loaded actors
    for (auto &actor : DynOS_Actor_GetValidActors()) {
        if (modIndex == -1 || actor.second.mGfxData->mModIndex == modIndex) {
            for (auto &vtx : actor.second.mGfxData->mVertices) {
                if (vtx->mName == aName) {
                    *outCount = vtx->mSize;
                    return vtx->mData;
                }
            }
        }
    }

    return NULL;
}

Vtx *DynOS_Vtx_New(const char *aName, u32 aCount) {
    if (!aName || !aCount) { return NULL; }
    s32 modIndex = (gLuaActiveMod ? gLuaActiveMod->index : -1);

    return DynOS_ModData_New(sModVertexBuffers, modIndex, aName, aCount, vtx_allocate_internal);
}

Vtx *DynOS_Vtx_Realloc(Vtx *aVtx, u32 aNewCount) {
    if (!aVtx || !aNewCount) { return NULL; }
    s32 modIndex = (gLuaActiveMod ? gLuaActiveMod->index : -1);

    return DynOS_ModData_Realloc(sModVertexBuffers, modIndex, aVtx, aNewCount, vtx_allocate_internal, free);
}

bool DynOS_Vtx_Delete(Vtx *aVtx) {
    if (!aVtx) { return false; }
    s32 modIndex = (gLuaActiveMod ? gLuaActiveMod->index : -1);

    return DynOS_ModData_Delete(sModVertexBuffers, modIndex, aVtx, free);
}

void DynOS_Gfx_ModShutdown() {

    // Delete all allocated display lists and vertex buffers
    DynOS_ModData_DeleteAll(sModDisplayLists, free);
    DynOS_ModData_DeleteAll(sModVertexBuffers, free);

    // Restore vanilla display lists
    for (auto &it : sRomToRamGfxVtxMap) {
        const void *original = it.first;
        void *duplicate = it.second.first;
        size_t size = it.second.second;
        memcpy(duplicate, original, size);
    }
}
