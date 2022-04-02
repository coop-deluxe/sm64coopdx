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

  /////////////
 // Writing //
/////////////

void DynOS_Vtx_Write(FILE* aFile, GfxData* aGfxData, DataNode<Vtx> *aNode) {
    if (!aNode->mData) return;

    // Header
    WriteBytes<u8>(aFile, DATA_TYPE_VERTEX);
    aNode->mName.Write(aFile);

    // Data
    WriteBytes<u32>(aFile, aNode->mSize);
    for (u32 i = 0; i != aNode->mSize; ++i) {
        WriteBytes<s16>(aFile, aNode->mData[i].n.ob[0]);
        WriteBytes<s16>(aFile, aNode->mData[i].n.ob[1]);
        WriteBytes<s16>(aFile, aNode->mData[i].n.ob[2]);
        WriteBytes<s16>(aFile, aNode->mData[i].n.flag);
        WriteBytes<s16>(aFile, aNode->mData[i].n.tc[0]);
        WriteBytes<s16>(aFile, aNode->mData[i].n.tc[1]);
        WriteBytes<s8> (aFile, aNode->mData[i].n.n[0]);
        WriteBytes<s8> (aFile, aNode->mData[i].n.n[1]);
        WriteBytes<s8> (aFile, aNode->mData[i].n.n[2]);
        WriteBytes<u8> (aFile, aNode->mData[i].n.a);
    }
}

  /////////////
 // Reading //
/////////////

void DynOS_Vtx_Load(FILE *aFile, GfxData *aGfxData) {
    DataNode<Vtx> *_Node = New<DataNode<Vtx>>();

    // Name
    _Node->mName.Read(aFile);

    // Data
    _Node->mSize = ReadBytes<u32>(aFile);
    _Node->mData = New<Vtx>(_Node->mSize);
    for (u32 i = 0; i != _Node->mSize; ++i) {
        _Node->mData[i].n.ob[0] = ReadBytes<s16>(aFile);
        _Node->mData[i].n.ob[1] = ReadBytes<s16>(aFile);
        _Node->mData[i].n.ob[2] = ReadBytes<s16>(aFile);
        _Node->mData[i].n.flag  = ReadBytes<s16>(aFile);
        _Node->mData[i].n.tc[0] = ReadBytes<s16>(aFile);
        _Node->mData[i].n.tc[1] = ReadBytes<s16>(aFile);
        _Node->mData[i].n.n[0]  = ReadBytes<s8> (aFile);
        _Node->mData[i].n.n[1]  = ReadBytes<s8> (aFile);
        _Node->mData[i].n.n[2]  = ReadBytes<s8> (aFile);
        _Node->mData[i].n.a     = ReadBytes<u8>(aFile);
    }

    // Append
    aGfxData->mVertices.Add(_Node);
}
