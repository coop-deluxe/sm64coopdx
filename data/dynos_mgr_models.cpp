#include <vector>
#include "dynos.cpp.h"

extern "C" {
#include "engine/geo_layout.h"
#include "engine/graph_node.h"
#include "model_ids.h"
#include "pc/lua/utils/smlua_model_utils.h"
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

static struct GraphNode *DynOS_Model_CheckMap(int index, u32* aId, void* aAsset, bool aDeDuplicate) {
    auto& map = sAssetMap[index];
    if (aDeDuplicate) {
        auto it = map.find(aAsset);
        if (it != map.end()) {
            auto& found = it->second;

            if (index != MODEL_POOL_PERMANENT) {
                if (*aId && *aId != found.id) {
                    sOverwriteMap[*aId] = found.id;
                }
                *aId = found.id;
                return found.graphNode;
            }

            if (!*aId || *aId == found.id) {
                if (!*aId) { *aId = found.id; }
                return found.graphNode;
            }
        }
    }
    return NULL;
}

static struct GraphNode* DynOS_Model_LoadCommonInternal(u32* aId, enum ModelPool aModelPool, void* aAsset, u8 aLayer, struct GraphNode* aGraphNode, bool aDeDuplicate, enum ModelLoadType mlt) {
    // sanity check pool
    if (aModelPool >= MODEL_POOL_MAX) { return NULL; }

    // allocate pool
    if (!sModelPools[aModelPool]) {
        sModelPools[aModelPool] = dynamic_pool_init();
    }

    // check maps, permanent pool is always checked
    struct GraphNode *node = NULL;
    #define CHECK_POOL(pool) if (node = DynOS_Model_CheckMap(pool, aId, aAsset, aDeDuplicate)) { return node; }
    CHECK_POOL(MODEL_POOL_PERMANENT);
    if (aModelPool == MODEL_POOL_SESSION) {
        CHECK_POOL(MODEL_POOL_SESSION);
        CHECK_POOL(MODEL_POOL_LEVEL);
    }
    if (aModelPool == MODEL_POOL_LEVEL) {
        CHECK_POOL(MODEL_POOL_LEVEL);
    }

    // load geo
    auto& map = sAssetMap[aModelPool];
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
    auto it = sIdMap.find(MODEL_ERROR_MODEL);
    if (it == sIdMap.end()) { return NULL; }
    auto& vec = it->second;
    if (vec.size() == 0 || vec.empty()) {
        return NULL;
    }
    return vec.back().graphNode;
}

struct GraphNode* DynOS_Model_GetGeo(u32 aId) {
    if (!aId) { return NULL; }

    auto overwriteIt = sOverwriteMap.find(aId);
    if (overwriteIt != sOverwriteMap.end()) {
        aId = overwriteIt->second;
    }

    auto idIt = sIdMap.find(aId);
    if (idIt == sIdMap.end()) {
        return DynOS_Model_GetErrorGeo();
    }

    auto& vec = idIt->second;
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
        auto& map = sAssetMap[i];
        auto assetIt = map.find(asset);
        if (assetIt == map.end()) { continue; }
        u32 id = assetIt->second.id;
        if (id < lowest) { lowest = id; }
        auto idIt = sOverwriteMap.find(id);
        if (idIt != sOverwriteMap.end()) {
            id = idIt->second;
            if (id < lowest) { lowest = id; }
        }
    }
    if (lowest < 9999) { return lowest; }
    return MODEL_ERROR_MODEL;
}

void DynOS_Model_OverwriteSlot(u32 srcSlot, u32 dstSlot) {
    sOverwriteMap[srcSlot] = dstSlot;
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
        auto idIt = sIdMap.find(info.id);
        if (idIt == sIdMap.end()) { continue; }
        auto& idMap = idIt->second;

        // preventing clearing permanent vanilla model slot
        if (info.id <= VANILLA_ID_END && idMap.size() <= 1) {
            if (sAssetMap[MODEL_POOL_PERMANENT].count(info.asset) > 0) {
                continue;
            }
        }

        // erase from id map
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
