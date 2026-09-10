#include "dynos.cpp.h"
#include <map>
extern "C" {
#include "include/PR/gbi.h"
#include "pc/gfx/gfx.h"
#include "pc/lua/utils/smlua_gfx_utils.h"
}

#define MAX_VERTICES_WITH_RECT (MAX_VERTICES + 4)

static std::map<u8, u32> sGfxCommands = {
#define GFX_OPCODE(_symb_, _ptrTypes_) { (u8) _symb_, (u32) _ptrTypes_ },
#include "dynos_bin_gfx_opcodes.inl"
#undef GFX_OPCODE
};

bool DynOS_Gfx_Validate_GetPointerTypes(u32 aWordsW0, u8 &outCommandId, u32 &outPtrTypes) {
    outCommandId = (u8) (aWordsW0 >> 24);

    // verify id
    if (sGfxCommands.count(outCommandId) == 0) {
        return false;
    }

    outPtrTypes = sGfxCommands[outCommandId];

    return true;
}

bool DynOS_Gfx_Validate_CheckCommands(GfxData *aGfxData, const DataNode<Gfx> *aNode) {

    // Display list must have at least 1 command
    if (aNode->mSize < 1) {
        PrintDataError("  ERROR: Validation failed for display list %s: Not enough commands (%d).", aNode->mName.begin(), aNode->mSize);
        return false;
    }

    // Last command must be a terminating command
    static const Array<uintptr_t> sGfxEndCommands = {
        Gfx(gsSPBranchList(0)).words.w0,
        Gfx(gsSPEndDisplayList()).words.w0,
    };
    if (sGfxEndCommands.Find(aNode->mData[aNode->mSize - 1].words.w0) == -1) {
        PrintDataError("  ERROR: Validation failed for display list %s: Last command must be one of:\n    gsSPBranchList, gsSPEndDisplayList", aNode->mName.begin());
        return false;
    }

    // Validate some specific commands
    for (u32 i = 0; i < aNode->mSize; ++i) {
        const Gfx *gfx = aNode->mData + i;
        u8 cmdId = (u8) (gfx->words.w0 >> 24);

        switch (cmdId) {

            // Vertex commands
            case G_VTX:
            case G_VTX_EXT: {
                const Vtx *vtxPtr = (const Vtx *) gfx->words.w1;
                if (vtxPtr == NULL) {
                    break;
                }

                // Check bounds for loaded vertices
                size_t numVertices = C0(gfx, 12, 8);
                size_t endIndex = C0(gfx, 1, 7);
                if (endIndex < numVertices) {
                    PrintDataError("  ERROR: Validation failed for display list %s: Invalid end vertex, must be greater than or equal to num vertices (endIndex: %llu, numVertices: %llu)", aNode->mName.begin(), endIndex, numVertices);
                    return false;
                }
                if (endIndex > MAX_VERTICES_WITH_RECT) {
                    PrintDataError("  ERROR: Validation failed for display list %s: Vertices exceed the maximum allowed, must be lower than or equal to %u (endIndex: %llu, numVertices: %llu)", aNode->mName.begin(), MAX_VERTICES_WITH_RECT, endIndex, numVertices);
                    return false;
                }

                // Find vertex node
                const Vtx *vtxEnd = NULL;
                for (const auto &_Node : aGfxData->mVertices) {
                    if (_Node->mData <= vtxPtr && vtxPtr < _Node->mData + _Node->mSize) {
                        vtxEnd = _Node->mData + _Node->mSize;
                        break;
                    }
                }
                if (!vtxEnd) {
                    PrintDataError("  ERROR: Validation failed for display list %s: Vertex buffer not found", aNode->mName.begin());
                    return false;
                }

                // Check bounds for vertex buffer
                if (vtxPtr + numVertices > vtxEnd) {
                    PrintDataError("  ERROR: Validation failed for display list %s: Invalid number of vertices to load (%llu > %llu)", aNode->mName.begin(), numVertices, (vtxEnd - vtxPtr));
                    return false;
                }
            } break;

            // Triangle commands
            case G_TRI1:
            case G_TRI2:
            case G_TRI2_EXT: {
                size_t vtx1 = C0(gfx, 16, 8) / 2, vtx2 = C0(gfx, 8, 8) / 2, vtx3 = C0(gfx, 0, 8) / 2;
                size_t vtx4 = C1(gfx, 16, 8) / 2, vtx5 = C1(gfx, 8, 8) / 2, vtx6 = C1(gfx, 0, 8) / 2;

                if (vtx1 >= MAX_VERTICES_WITH_RECT) {
                    PrintDataError("  ERROR: Validation failed for display list %s: Invalid triangle vertex index 1 (%llu)", aNode->mName.begin(), vtx1);
                    return false;
                }
                if (vtx2 >= MAX_VERTICES_WITH_RECT) {
                    PrintDataError("  ERROR: Validation failed for display list %s: Invalid triangle vertex index 2 (%llu)", aNode->mName.begin(), vtx2);
                    return false;
                }
                if (vtx3 >= MAX_VERTICES_WITH_RECT) {
                    PrintDataError("  ERROR: Validation failed for display list %s: Invalid triangle vertex index 3 (%llu)", aNode->mName.begin(), vtx3);
                    return false;
                }
                if (cmdId == G_TRI2 || cmdId == G_TRI2_EXT) {
                    if (vtx4 >= MAX_VERTICES_WITH_RECT) {
                        PrintDataError("  ERROR: Validation failed for display list %s: Invalid triangle vertex index 4 (%llu)", aNode->mName.begin(), vtx4);
                        return false;
                    }
                    if (vtx5 >= MAX_VERTICES_WITH_RECT) {
                        PrintDataError("  ERROR: Validation failed for display list %s: Invalid triangle vertex index 5 (%llu)", aNode->mName.begin(), vtx5);
                        return false;
                    }
                    if (vtx6 >= MAX_VERTICES_WITH_RECT) {
                        PrintDataError("  ERROR: Validation failed for display list %s: Invalid triangle vertex index 6 (%llu)", aNode->mName.begin(), vtx6);
                        return false;
                    }
                }
            } break;
        }
    }

    return true;
}
