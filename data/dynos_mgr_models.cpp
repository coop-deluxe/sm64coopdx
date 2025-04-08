#include <map>
#include <vector>
#include "dynos.cpp.h"

extern "C" {
#include "engine/geo_layout.h"
#include "engine/graph_node.h"
#include "model_ids.h"
#include "pc/lua/utils/smlua_model_utils.h"
#include "pc/lua/utils/smlua_gfx_utils.h"
#include "pc/mods/mod.h"
#include "dynos_mgr_builtin_externs.h"
extern struct Mod *gLuaActiveMod;
}

enum ModelLoadType {
    MLT_GEO,
    MLT_DL,
    MLT_STORE,
};

struct ModelInfo {
    u32 id;
    void* asset;
    struct GraphNode* graphNode;
    enum ModelPool modelPool;
};

static struct DynamicPool* sModelPools[MODEL_POOL_MAX] = { 0 };

static std::map<void*, struct ModelInfo> sAssetMap[MODEL_POOL_MAX];
static std::map<u32, std::vector<struct ModelInfo>> sIdMap;
static std::map<u32, u32> sOverwriteMap;

// Maps read-only Gfx and Vtx buffers to their writable duplicates
static std::map<const void *, std::pair<void *, size_t>> sRomToRamGfxVtxMap;

static u32 find_empty_id(bool aIsPermanent) {
    u32 id = aIsPermanent ? 9999 : VANILLA_ID_END + 1;
    s8 dir = aIsPermanent ? -1 : 1;
    while (true) {
        if (id != 9999) {
            if (sIdMap.count(id) == 0)  { return id; }
            if (sIdMap[id].size() == 0) { return id; }
        }
        id += dir;
    }
}

void DynOS_Model_Dump() {
    for (auto& it : sIdMap) {
        if (it.second.size() == 0 || it.second.empty()) { continue; }
        printf(">> [%03x] ", it.first);
        for (auto& it2 : it.second) {
            switch (it2.modelPool) {
                case MODEL_POOL_PERMANENT: printf("P "); break;
                case MODEL_POOL_SESSION:   printf("S "); break;
                case MODEL_POOL_LEVEL:     printf("L "); break;
                case MODEL_POOL_MAX:       printf("M "); break;
            }
            printf("%p ", it2.graphNode);
        }
        printf("\n");
    }
}

static struct GraphNode* DynOS_Model_LoadCommonInternal(u32* aId, enum ModelPool aModelPool, void* aAsset, u8 aLayer, struct GraphNode* aGraphNode, bool aDeDuplicate, enum ModelLoadType mlt) {
    // sanity check pool
    if (aModelPool >= MODEL_POOL_MAX) { return NULL; }

    // allocate pool
    if (!sModelPools[aModelPool]) {
        sModelPools[aModelPool] = dynamic_pool_init();
    }

    // check perm map
    auto& permMap = sAssetMap[MODEL_POOL_PERMANENT];
    if (aDeDuplicate && permMap.count(aAsset)) {
        auto& found = permMap[aAsset];
        if (*aId && *aId == found.id) {
            return found.graphNode;
        }
        if (*aId == 0) {
            *aId = found.id;
            return found.graphNode;
        }
    }

    // check map
    auto& map = sAssetMap[aModelPool];
    if (aDeDuplicate && map.count(aAsset)) {
        auto& found = map[aAsset];
        if (*aId && *aId != found.id) {
            sOverwriteMap[*aId] = found.id;
        }
        *aId = found.id;
        return found.graphNode;
    }

    // load geo
    struct GraphNode* node = NULL;
    switch (mlt) {
        case MLT_GEO:
            node = process_geo_layout(sModelPools[aModelPool], aAsset);
            break;
        case MLT_DL:
            node = (struct GraphNode *) init_graph_node_display_list(sModelPools[aModelPool], NULL, aLayer, aAsset);
            break;
        case MLT_STORE:
            node = aGraphNode;
            break;
    }
    if (!node) { return NULL; }

    // figure out id
    if (!*aId) { *aId = find_empty_id(aModelPool == MODEL_POOL_PERMANENT); }

    // create model info
    struct ModelInfo info = {
        .id = *aId,
        .asset = aAsset,
        .graphNode = node,
        .modelPool = aModelPool,
    };

    // store in maps
    sIdMap[*aId].push_back(info);
    map[aAsset] = info;

    return node;
}

static struct GraphNode* DynOS_Model_LoadCommon(u32* aId, enum ModelPool aModelPool, void* aAsset, u8 aLayer, struct GraphNode* aGraphNode, bool aDeDuplicate, enum ModelLoadType mlt) {
    struct GraphNode* node = DynOS_Model_LoadCommonInternal(aId, aModelPool, aAsset, aLayer, aGraphNode, aDeDuplicate, mlt);
    smlua_model_util_register_model_id(*aId, aAsset);
    return node;
}

struct GraphNode* DynOS_Model_LoadGeo(u32* aId, enum ModelPool aModelPool, void* aAsset, bool aDeDuplicate) {
    return DynOS_Model_LoadCommon(aId, aModelPool, aAsset, 0, NULL, aDeDuplicate, MLT_GEO);
}

struct GraphNode* DynOS_Model_LoadDl(u32* aId, enum ModelPool aModelPool, u8 aLayer, void* aAsset) {
    return DynOS_Model_LoadCommon(aId, aModelPool, aAsset, aLayer, NULL, true, MLT_DL);
}

struct GraphNode* DynOS_Model_StoreGeo(u32* aId, enum ModelPool aModelPool, void* aAsset, struct GraphNode* aGraphNode) {
    return DynOS_Model_LoadCommon(aId, aModelPool, aAsset, 0, aGraphNode, true, MLT_STORE);
}

struct GraphNode* DynOS_Model_GetErrorGeo() {
    if (!sIdMap.count(MODEL_ERROR_MODEL)) { return NULL; }
    auto& vec = sIdMap[MODEL_ERROR_MODEL];
    if (vec.size() == 0 || vec.empty()) {
        return NULL;
    }
    return vec.back().graphNode;
}

struct GraphNode* DynOS_Model_GetGeo(u32 aId) {
    if (!aId) { return NULL; }

    if (sOverwriteMap.count(aId)) {
        aId = sOverwriteMap[aId];
    }

    if (sIdMap.count(aId) == 0) {
        return DynOS_Model_GetErrorGeo();
    }

    auto& vec = sIdMap[aId];
    if (vec.size() == 0 || vec.empty()) {
        return DynOS_Model_GetErrorGeo();
    }

    return vec.back().graphNode;
}

static u32 DynOS_Model_GetIdFromGeoRef(u32 aIndex, void* aGeoRef) {
    u32 lowest = 9999;
    for (auto& it : sIdMap) {
        u32 id = it.first;
        if (id > lowest) { continue; }
        if (!it.second.size() || it.second.empty()) { continue; }
        auto& node = it.second.back();
        if (aGeoRef == node.graphNode->georef) {
            lowest = id;
        }
    }
    if (lowest < 9999) { return lowest; }
    return aIndex;
}

u32 DynOS_Model_GetIdFromGraphNode(struct GraphNode* aNode) {
    u32 lowest = 9999;
    void* georef = NULL;
    for (auto& it : sIdMap) {
        u32 id = it.first;
        if (id > lowest) { continue; }
        if (!it.second.size() || it.second.empty()) { continue; }
        auto& node = it.second.back();
        if (aNode == node.graphNode) {
            lowest = id;
            georef = (void*)node.graphNode->georef;
        }
    }
    if (georef) {
        lowest = DynOS_Model_GetIdFromGeoRef(lowest, georef);
    }
    if (lowest < 9999) { return lowest; }
    return MODEL_ERROR_MODEL;
}

u32 DynOS_Model_GetIdFromAsset(void* asset) {
    if (!asset) { return MODEL_NONE; }
    u32 lowest = 9999;
    for (int i = 0; i < MODEL_POOL_MAX; i++) {
        if (!sAssetMap[i].count(asset)) { continue; }
        u32 id = sAssetMap[i][asset].id;
        if (id < lowest) { lowest = id; }
        if (sOverwriteMap.count(id)) {
            id = sOverwriteMap[id];
            if (id < lowest) { lowest = id; }
        }
    }
    if (lowest < 9999) { return lowest; }
    return MODEL_ERROR_MODEL;
}

void DynOS_Model_OverwriteSlot(u32 srcSlot, u32 dstSlot) {
    sOverwriteMap[srcSlot] = dstSlot;
}

static Vtx *DynOS_Model_DuplicateVtx(Vtx *aVtx, u32 vtxCount, bool shouldDuplicate) {
    if (!aVtx) { return NULL; }

    // Return duplicate if it already exists
    auto it = sRomToRamGfxVtxMap.find(aVtx);
    if (it != sRomToRamGfxVtxMap.end()) {
        return (Vtx *) it->second.first;
    }

    // Duplicate vertex buffer and return the copy
    if (shouldDuplicate) {
        size_t vtxSize = vtxCount * sizeof(Vtx);
        Vtx *vtxDuplicate = (Vtx *) malloc(vtxSize);
        memcpy(vtxDuplicate, aVtx, vtxSize);
        DynOS_Find_Pending_Scroll_Target(aVtx, vtxDuplicate);
        sRomToRamGfxVtxMap[aVtx] = { (void *) vtxDuplicate, vtxSize };
        return vtxDuplicate;
    }

    return aVtx;
}

static Gfx *DynOS_Model_DuplicateDisplayList(Gfx *aGfx, bool shouldDuplicate) {
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
    u32 gfxLength = gfx_get_length(aGfx);
    if (shouldDuplicate) {
        size_t gfxSize = gfxLength * sizeof(Gfx);
        gfxDuplicate = (Gfx *) malloc(gfxSize);
        memcpy(gfxDuplicate, aGfx, gfxSize);
        sRomToRamGfxVtxMap[aGfx] = { (void *) gfxDuplicate, gfxSize };
    }

    // Look for other display lists or vertices
    for (u32 i = 0; i < gfxLength; i++) {
        Gfx *cmd = gfxDuplicate + i;
        u32 op = cmd->words.w0 >> 24;

        // Duplicate referenced display lists
        if (op == G_DL) {
            cmd->words.w1 = (uintptr_t) DynOS_Model_DuplicateDisplayList((Gfx *) cmd->words.w1, shouldDuplicate);
            if (C0(cmd, 16, 1) == G_DL_NOPUSH) { break; } // This is a branch (jump), end of display list
        }

        // Duplicate referenced vertices
        if (op == G_VTX) {
            cmd->words.w1 = (uintptr_t) DynOS_Model_DuplicateVtx((Vtx *) cmd->words.w1, C0(cmd, 12, 8), shouldDuplicate);
        }
    }

    return gfxDuplicate;
}

// Get a writable display list so it can be modified by mods
// If it's a vanilla display list, duplicate it, so it can be restored later
Gfx *DynOS_Model_GetWritableDisplayList(Gfx *aGfx) {
    return DynOS_Model_DuplicateDisplayList(aGfx, false);
}

void DynOS_Model_RestoreVanillaDisplayLists() {
    for (auto &it : sRomToRamGfxVtxMap) {
        const void *original = it.first;
        void *duplicate = it.second.first;
        size_t size = it.second.second;
        memcpy(duplicate, original, size);
    }
}

void DynOS_Model_ClearPool(enum ModelPool aModelPool) {
    if (!sModelPools[aModelPool]) { return; }

    // schedule pool to be freed
    dynamic_pool_free_pool(sModelPools[aModelPool]);

    // clear overwrite
    if (aModelPool == MODEL_POOL_LEVEL) {
        sOverwriteMap.clear();
    }

    // clear maps
    auto& assetMap = sAssetMap[aModelPool];
    for (auto& asset : assetMap) {
        auto& info = asset.second;
        if (sIdMap.count(info.id) == 0) { continue; }

        // preventing clearing permanent vanilla model slot
        if (info.id <= VANILLA_ID_END && sIdMap.count(info.id) <= 1) {
            if (sAssetMap[MODEL_POOL_PERMANENT].count(info.asset) > 0) {
                continue;
            }
        }

        // erase from id map
        auto& idMap = sIdMap[info.id];
        for (auto info2 = idMap.begin(); info2 != idMap.end(); ) {
            if (info.id == info2->id && info2->modelPool == aModelPool) {
                info2 = idMap.erase(info2);
            } else {
                info2++;
            }
        }
    }

    assetMap.clear();
}

Gfx *DynOS_Model_GetGfx(const char *aName, u32 *outLength) {
    if (!aName) { return NULL; }
    s32 modIndex = (gLuaActiveMod ? gLuaActiveMod->index : -1);

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
            DynOS_Model_DuplicateDisplayList((Gfx *) gfxVanilla, true);
            it = sRomToRamGfxVtxMap.find(gfxVanilla);
        }

        *outLength = it->second.second / sizeof(Gfx);
        return (Gfx *) it->second.first;
    }

    return NULL;
}

Vtx *DynOS_Model_GetVtx(const char *aName, u32 *outCount) {
    if (!aName) { return NULL; }
    s32 modIndex = (gLuaActiveMod ? gLuaActiveMod->index : -1);

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
