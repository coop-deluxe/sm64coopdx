#include <map>
#include <vector>
#include "dynos.cpp.h"

extern "C" {
#include "engine/geo_layout.h"
#include "engine/graph_node.h"
}

struct ScheduledFreePool {
    struct DynamicPool* pool;
    u32 timeout;
};

static struct DynamicPool* sModelPools[MODEL_POOL_MAX] = { 0 };
static std::map<void*, struct GraphNode*> sModelMap[MODEL_POOL_MAX];
static std::vector<struct ScheduledFreePool> sPoolsToFree;

struct GraphNode* DynOS_Model_LoadGeo(enum ModelPool aModelPool, void* aAsset) {
    // sanity check pool
    if (aModelPool >= MODEL_POOL_MAX) { return NULL; }

    // allocate pool
    if (!sModelPools[aModelPool]) {
        sModelPools[aModelPool] = dynamic_pool_init();
    }

    // check map
    auto& map = sModelMap[aModelPool];
    if (map.count(aAsset)) {
        return map[aAsset];
    }

    // load geo
    struct GraphNode* node = process_geo_layout(sModelPools[aModelPool], aAsset);

    // store and return geo
    map[aAsset] = node;
    return node;
}

struct GraphNode* DynOS_Model_LoadDl(enum ModelPool aModelPool, u8 aLayer, void* aAsset) {
    // sanity check pool
    if (aModelPool >= MODEL_POOL_MAX) { return NULL; }

    // allocate pool
    if (!sModelPools[aModelPool]) {
        sModelPools[aModelPool] = dynamic_pool_init();
    }

    // check map
    auto& map = sModelMap[aModelPool];
    if (map.count(aAsset)) {
        return map[aAsset];
    }

    // load geo
    struct GraphNode* node = (struct GraphNode *) init_graph_node_display_list(sModelPools[aModelPool], NULL, aLayer, aAsset);

    // store and return geo
    map[aAsset] = node;
    return node;
}

void DynOS_Model_ClearPool(enum ModelPool aModelPool) {
    if (!sModelPools[aModelPool]) { return; }

    // schedule pool to be freed
    sPoolsToFree.push_back({
        .pool = sModelPools[aModelPool],
        .timeout = 30
    });

    // clear pointer
    sModelPools[aModelPool] = NULL;

    // clear map
    auto& map = sModelMap[aModelPool];
    map.clear();
}

void DynOS_Model_Update() {
    for (auto it = sPoolsToFree.begin(); it != sPoolsToFree.end(); ) {
        if (--it->timeout <= 0) {
            dynamic_pool_free_pool(it->pool);
            it = sPoolsToFree.erase(it);
        } else {
            it++;
        }
    }
}