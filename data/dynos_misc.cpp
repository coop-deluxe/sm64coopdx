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

static std::unordered_multimap<std::string_view, DataNode<Vtx>*> sVertexNodesExactMap;
static std::vector<GfxData*> sVertexNodesCacheLvls;

void DynOS_Add_Scroll_Target(u32 index, const char* name, u32 offset, u32 size) {
    auto& lvlArray = DynOS_Lvl_GetArray();

    // Check if cache needs rebuilding
    bool rebuild = (lvlArray.size() != sVertexNodesCacheLvls.size());
    if (!rebuild) {
        for (size_t i = 0; i < lvlArray.size(); ++i) {
            if (lvlArray[i].second != sVertexNodesCacheLvls[i]) {
                rebuild = true;
                break;
            }
        }
    }

    if (rebuild) {
        sVertexNodesExactMap.clear();
        sVertexNodesCacheLvls.clear();
        for (const auto& lvlPair : lvlArray) {
            sVertexNodesCacheLvls.push_back(lvlPair.second);
            for (const auto& node : lvlPair.second->mVertices) {
                sVertexNodesExactMap.emplace(std::string_view(node->mName.begin(), node->mName.Length()), node);
            }
        }
    }

    // Check exact match
    auto range = sVertexNodesExactMap.equal_range(name);
    if (range.first != range.second) {
        for (auto it = range.first; it != range.second; ++it) {
            DataNode<Vtx>* node = it->second;
            if (offset >= node->mSize) { continue; }
            u32 finalSize = (size > 0 && size <= (node->mSize - offset)) ? size : (node->mSize - offset);
            add_vtx_scroll_target(
                index,
                &node->mData[offset],
                finalSize,
                offset > 0
            );
        }
        return;
    }

    // Fallback to substring search
    for (const auto& lvlPair : lvlArray) {
        for (const auto& node : lvlPair.second->mVertices) {
            if (node->mName.Find(name) >= 0) {
                if (offset >= node->mSize) { continue; }
                u32 finalSize = (size > 0 && size <= (node->mSize - offset)) ? size : (node->mSize - offset);
                add_vtx_scroll_target(
                    index,
                    &node->mData[offset],
                    finalSize,
                    offset > 0
                );
            }
        }
    }
}
