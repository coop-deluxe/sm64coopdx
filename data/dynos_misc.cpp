#include "dynos.cpp.h"
extern "C" {
#include "game/scroll_targets.h"
}

//
// Scroll Targets
//

void DynOS_Add_Scroll_Target(u32 index, const char* name, u32 offset, u32 size) {
    for (auto& lvlPair : DynOS_Lvl_GetArray()) {
        for (auto& node : lvlPair.second->mVertices) {
            if (node->mName.Find(name) >= 0) {
                add_vtx_scroll_target(
                    index,
                    &node->mData[offset],
                    (size > 0 && size < node->mSize) ? size : node->mSize,
                    offset > 0
                );
            }
        }
    }
}
