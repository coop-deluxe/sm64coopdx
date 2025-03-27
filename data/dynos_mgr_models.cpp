#include <map>
#include <vector>
#include "dynos.cpp.h"

extern "C" {
#include "engine/geo_layout.h"
#include "engine/graph_node.h"
#include "model_ids.h"
#include "pc/lua/utils/smlua_model_utils.h"
#include "engine/display_list.h"
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
    std::vector<void*> *duplicates;
};

static struct DynamicPool* sModelPools[MODEL_POOL_MAX] = { 0 };

static std::map<void*, struct ModelInfo> sAssetMap[MODEL_POOL_MAX];
static std::map<u32, std::vector<struct ModelInfo>> sIdMap;
static std::map<u32, u32> sOverwriteMap;

// An array of display list and/or vertex buffer duplicates for the current model processed in process_geo_layout
static std::vector<void*> *sCurrModelDuplicates = nullptr;
static std::vector<void*> sScheduledFree[MODEL_POOL_MAX];

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

    sCurrModelDuplicates = new std::vector<void*>();

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
    if (!node) {
        for (auto &duplicate : *sCurrModelDuplicates) {
            free(duplicate);
        }
        delete sCurrModelDuplicates;
        sCurrModelDuplicates = nullptr;
        return NULL;
    }

    // figure out id
    if (!*aId) { *aId = find_empty_id(aModelPool == MODEL_POOL_PERMANENT); }

    // create model info
    struct ModelInfo info = {
        .id = *aId,
        .asset = aAsset,
        .graphNode = node,
        .modelPool = aModelPool,
        .duplicates = sCurrModelDuplicates,
    };
    sCurrModelDuplicates = nullptr;

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

// Display lists need to be duplicated so they can be modified by mods
// also to prevent trying to write to read only memory for vanilla display lists
Gfx *DynOS_Model_Duplicate_DisplayList(Gfx* aGfx) {
    if (!aGfx) { return nullptr; }

    u32 size = gfx_get_size(aGfx) * sizeof(Gfx);
    Gfx *gfxDuplicate = (Gfx *) malloc(size);
    memcpy(gfxDuplicate, aGfx, size);

    // Look for other display lists or vertices
    for (u32 i = 0; i < size / sizeof(Gfx); i++) {
        Gfx *cmd = gfxDuplicate + i;
        u32 op = cmd->words.w0 >> 24;

        // Duplicate referenced display lists
        if (op == G_DL) {
            cmd->words.w1 = (uintptr_t) DynOS_Model_Duplicate_DisplayList((Gfx *) cmd->words.w1);
            if (C0(cmd, 16, 1) == G_DL_NOPUSH) { break; } // This is a branch (jump), end of display list
        }

        // Duplicate referenced vertices
        if (op == G_VTX) {
            u32 size = C0(cmd, 12, 8) * sizeof(Vtx);
            Vtx *vtxDuplicate = (Vtx *) malloc(size);
            memcpy(vtxDuplicate, (Vtx *) cmd->words.w1, size);
            cmd->words.w1 = (uintptr_t) vtxDuplicate;
            sCurrModelDuplicates->push_back(vtxDuplicate);
        }
    }

    sCurrModelDuplicates->push_back(gfxDuplicate);

    return gfxDuplicate;
}

void DynOS_Model_ClearPool(enum ModelPool aModelPool) {
    if (!sModelPools[aModelPool]) { return; }

    // schedule pool to be freed
    dynamic_pool_free_pool(sModelPools[aModelPool]);

    // free scheduled duplicates
    for (auto &duplicate : sScheduledFree[aModelPool]) {
        free(duplicate);
    }
    sScheduledFree[aModelPool].clear();

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

        // schedule duplicates to be freed
        if (info.duplicates) {
            for (auto &duplicate : *info.duplicates) {
                sScheduledFree[aModelPool].push_back(duplicate);
            }
            delete info.duplicates;
            info.duplicates = nullptr;
        }
    }

    assetMap.clear();
}
