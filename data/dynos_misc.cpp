#include <unordered_map>
#include <string_view>
#include <string>
#include "dynos.cpp.h"
extern "C" {
#include "game/scroll_targets.h"
}

//
// Scroll Targets
//

static void DynOS_Add_Scroll_Target_Match(u32 index, const char* name, u32 offset, u32 size, DataNode<Vtx>* node) {
    if (offset >= node->mSize) { return; }
    u32 finalSize = (size > 0 && size <= (node->mSize - offset)) ? size : (node->mSize - offset);
    add_vtx_scroll_target(
        index,
        &node->mData[offset],
        finalSize,
        offset > 0
    );
}

void DynOS_Add_Scroll_Target(u32 index, const char* name, u32 offset, u32 size) {
    static std::unordered_multimap<std::string_view, DataNode<Vtx>*> sVertexNodesExactMap;
    static std::vector<GfxData*> sLvlGfxDataCache; // cache existing level pointers to know when to rebuild

    auto& lvlArray = DynOS_Lvl_GetArray();

    // Check if cache needs rebuilding
    bool rebuild = (lvlArray.size() != sLvlGfxDataCache.size());
    if (!rebuild) {
        for (size_t i = 0; i < lvlArray.size(); ++i) {
            if (lvlArray[i].second != sLvlGfxDataCache[i]) {
                rebuild = true;
                break;
            }
        }
    }

    if (rebuild) {
        sVertexNodesExactMap.clear();
        sLvlGfxDataCache.clear();
        for (const auto& lvlPair : lvlArray) {
            sLvlGfxDataCache.push_back(lvlPair.second);
            for (const auto& node : lvlPair.second->mVertices) {
                sVertexNodesExactMap.emplace(std::string_view(node->mName.begin(), node->mName.Length()), node);
            }
        }
    }

    // Check exact match
    auto range = sVertexNodesExactMap.equal_range(name);
    if (range.first != range.second) {
        for (auto it = range.first; it != range.second; ++it) {
            DynOS_Add_Scroll_Target_Match(index, name, offset, size, it->second);
        }
        return;
    }

    // Fallback to substring search
    for (const auto& lvlPair : lvlArray) {
        for (const auto& node : lvlPair.second->mVertices) {
            if (node->mName.Find(name) >= 0) {
                DynOS_Add_Scroll_Target_Match(index, name, offset, size, node);
            }
        }
    }
}
