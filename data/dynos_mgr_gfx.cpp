#include "dynos.cpp.h"

extern "C" {
#include "pc/lua/smlua.h"
#include "pc/lua/utils/smlua_gfx_utils.h"
}

struct MapNode {
    void *duplicate;
    size_t size;
    Gfx *gfxCopy;
};

// Maps read-only Gfx and Vtx buffers to their writable duplicates
static std::map<const void *, struct MapNode> sRomToRamGfxVtxMap;

static Vtx *DynOS_Vtx_Duplicate(Vtx *aVtx, u32 vtxCount, bool shouldDuplicate) {
    if (!aVtx) { return NULL; }

    // Return duplicate if it already exists
    auto it = sRomToRamGfxVtxMap.find(aVtx);
    if (it != sRomToRamGfxVtxMap.end()) {
        return (Vtx *) it->second.duplicate;
    }

    // Duplicate vertex buffer and return the copy
    if (shouldDuplicate) {
        size_t vtxSize = vtxCount * sizeof(Vtx);
        Vtx *vtxDuplicate = vtx_allocate_internal(NULL, vtxCount);
        memcpy(vtxDuplicate, aVtx, vtxSize);
        sRomToRamGfxVtxMap[aVtx] = { (void *) vtxDuplicate, vtxSize, NULL };
        return vtxDuplicate;
    }

    return aVtx;
}

static Gfx *DynOS_Gfx_Duplicate(Gfx *aGfx, bool shouldDuplicate) {
    if (!aGfx) { return NULL; }

    // Return duplicate if it already exists
    auto it = sRomToRamGfxVtxMap.find(aGfx);
    if (it != sRomToRamGfxVtxMap.end()) {
        return (Gfx *) it->second.duplicate;
    }

    // Check if it's vanilla
    if (!shouldDuplicate) {
        shouldDuplicate = (DynOS_Builtin_Gfx_GetFromData(aGfx) != NULL);
    }

    // Duplicate display list
    Gfx *gfxDuplicate = aGfx;
    u32 gfxLength = shouldDuplicate ? gfx_get_length_no_sentinel(aGfx) : gfx_get_length(aGfx);
    if (shouldDuplicate) {
        gfxDuplicate = gfx_allocate_internal(NULL, gfxLength);
        memcpy(gfxDuplicate, aGfx, gfxLength * sizeof(Gfx));
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

    // Create a second duplicate for resetting the
    // display list later, and then store it in the map
    if (shouldDuplicate) {
        size_t gfxSize = gfxLength * sizeof(Gfx);
        Gfx *gfxCopy = (Gfx *) malloc(gfxSize);
        memcpy(gfxCopy, gfxDuplicate, gfxSize);
        sRomToRamGfxVtxMap[aGfx] = { (void *) gfxDuplicate, gfxSize, gfxCopy };
    }

    return gfxDuplicate;
}

// Get a writable display list so it can be modified by mods
// If it's a vanilla display list, duplicate it, so it can be restored later
Gfx *DynOS_Gfx_GetWritableDisplayList(Gfx *aGfx) {
    return DynOS_Gfx_Duplicate(aGfx, false);
}

  ///////////////////
 // Display lists //
///////////////////

#define MOD_DATA_MAX_DISPLAY_LISTS          0x400
#define MOD_DATA_DISPLAY_LIST_MAX_LENGTH    0x800

static Gfx *dynos_mod_data_gfx_allocate(u32 length) {
    return gfx_allocate_internal(NULL, length);
}

static void dynos_mod_data_gfx_resize(Gfx *gfx, u32 oldLength, u32 newLength) {
    if (newLength < oldLength) {
        gfx_allocate_internal(gfx + newLength, 0);
    } else {
        gfx_allocate_internal(gfx + oldLength, newLength - oldLength);
    }
}

static void dynos_mod_data_gfx_deallocate(Gfx *gfx, UNUSED u32 length) {
    free(gfx);
}

DEFINE_MODS_DATA(sModsDisplayLists,
    Gfx,
    MOD_DATA_MAX_DISPLAY_LISTS,
    MOD_DATA_DISPLAY_LIST_MAX_LENGTH,
    dynos_mod_data_gfx_allocate,
    dynos_mod_data_gfx_resize,
    dynos_mod_data_gfx_deallocate
);

Gfx *DynOS_Gfx_Get(const char *aName, u32 *outLength) {
    if (!aName) { return NULL; }
    s32 modIndex = (gLuaActiveMod ? gLuaActiveMod->index : -1);

    // Check mod data
    Gfx *gfx = sModsDisplayLists.Get(modIndex, aName, outLength);
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

        *outLength = it->second.size / sizeof(Gfx);
        return (Gfx *) it->second.duplicate;
    }

    return NULL;
}

Gfx *DynOS_Gfx_Create(const char *aName, u32 aLength) {
    s32 modIndex = (gLuaActiveMod ? gLuaActiveMod->index : -1);
    return sModsDisplayLists.Create(modIndex, aName, aLength);
}

bool DynOS_Gfx_Resize(Gfx *aGfx, u32 aNewLength) {
    s32 modIndex = (gLuaActiveMod ? gLuaActiveMod->index : -1);
    return sModsDisplayLists.Resize(modIndex, aGfx, aNewLength);
}

bool DynOS_Gfx_Delete(Gfx *aGfx) {
    s32 modIndex = (gLuaActiveMod ? gLuaActiveMod->index : -1);
    return sModsDisplayLists.Delete(modIndex, aGfx);
}

void DynOS_Gfx_DeleteAll() {
    s32 modIndex = (gLuaActiveMod ? gLuaActiveMod->index : -1);
    sModsDisplayLists.DeleteAll(modIndex);
}

  ////////////////////
 // Vertex buffers //
////////////////////

#define MOD_DATA_MAX_VERTEX_BUFFERS         0x400
#define MOD_DATA_VERTEX_BUFFER_MAX_COUNT    0x1000

static Vtx *dynos_mod_data_vtx_allocate(u32 count) {
    return vtx_allocate_internal(NULL, count);
}

static void dynos_mod_data_vtx_resize(Vtx *vtx, u32 oldCount, u32 newCount) {
    if (newCount < oldCount) {
        vtx_allocate_internal(vtx + newCount, 0);
    } else {
        vtx_allocate_internal(vtx + oldCount, newCount - oldCount);
    }
}

static void dynos_mod_data_vtx_deallocate(Vtx *vtx, UNUSED u32 count) {
    free(vtx);
}

DEFINE_MODS_DATA(sModsVertexBuffers,
    Vtx,
    MOD_DATA_MAX_VERTEX_BUFFERS,
    MOD_DATA_VERTEX_BUFFER_MAX_COUNT,
    dynos_mod_data_vtx_allocate,
    dynos_mod_data_vtx_resize,
    dynos_mod_data_vtx_deallocate
);

Vtx *DynOS_Vtx_Get(const char *aName, u32 *outCount) {
    if (!aName) { return NULL; }
    s32 modIndex = (gLuaActiveMod ? gLuaActiveMod->index : -1);

    // Check mod data
    Vtx *vtx = sModsVertexBuffers.Get(modIndex, aName, outCount);
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

Vtx *DynOS_Vtx_Create(const char *aName, u32 aCount) {
    s32 modIndex = (gLuaActiveMod ? gLuaActiveMod->index : -1);
    return sModsVertexBuffers.Create(modIndex, aName, aCount);
}

bool DynOS_Vtx_Resize(Vtx *aVtx, u32 aNewCount) {
    s32 modIndex = (gLuaActiveMod ? gLuaActiveMod->index : -1);
    return sModsVertexBuffers.Resize(modIndex, aVtx, aNewCount);
}

bool DynOS_Vtx_Delete(Vtx *aVtx) {
    s32 modIndex = (gLuaActiveMod ? gLuaActiveMod->index : -1);
    return sModsVertexBuffers.Delete(modIndex, aVtx);
}

void DynOS_Vtx_DeleteAll() {
    s32 modIndex = (gLuaActiveMod ? gLuaActiveMod->index : -1);
    sModsVertexBuffers.DeleteAll(modIndex);
}

void DynOS_Gfx_ModShutdown() {

    // Delete all allocated display lists and vertex buffers
    sModsDisplayLists.Clear();
    sModsVertexBuffers.Clear();

    // Restore vanilla display lists
    for (auto &it : sRomToRamGfxVtxMap) {
        const void *original = it.second.gfxCopy ? it.second.gfxCopy : it.first;
        void *duplicate = it.second.duplicate;
        size_t size = it.second.size;
        memcpy(duplicate, original, size);
    }
}
