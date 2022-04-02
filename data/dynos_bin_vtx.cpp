#include "dynos.cpp.h"

  /////////////
 // Parsing //
/////////////

DataNode<Vtx>* DynOS_Vtx_Parse(GfxData* aGfxData, DataNode<Vtx>* aNode) {
    if (aNode->mData) return aNode;

    // Vertex data
    aNode->mSize = (u32) (aNode->mTokens.Count() / 10);
    aNode->mData = New<Vtx>(aNode->mSize);
    for (u32 i = 0; i != aNode->mSize; ++i) {
        f32 px = (f32) aNode->mTokens[10 * i + 0].ParseFloat();
        f32 py = (f32) aNode->mTokens[10 * i + 1].ParseFloat();
        f32 pz = (f32) aNode->mTokens[10 * i + 2].ParseFloat();
        u8 fl = (u8) aNode->mTokens[10 * i + 3].ParseInt();
        s16 tu = (s16) aNode->mTokens[10 * i + 4].ParseInt();
        s16 tv = (s16) aNode->mTokens[10 * i + 5].ParseInt();
        u8 nx = (u8) aNode->mTokens[10 * i + 6].ParseInt();
        u8 ny = (u8) aNode->mTokens[10 * i + 7].ParseInt();
        u8 nz = (u8) aNode->mTokens[10 * i + 8].ParseInt();
        u8 a  = (u8) aNode->mTokens[10 * i + 9].ParseInt();
        aNode->mData[i] = { { { px, py, pz }, fl, { tu, tv }, { nx, ny, nz, a } } };
    }
    aNode->mLoadIndex = aGfxData->mLoadIndex++;
    return aNode;
}
