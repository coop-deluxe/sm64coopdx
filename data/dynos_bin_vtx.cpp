#include "dynos.cpp.h"

#define F32VTX_SENTINEL_0 0x3346
#define F32VTX_SENTINEL_1 0x5632
#define F32VTX_SENTINEL_2 0x5854

static inline bool ShouldUseF32Vtx(DataNode<Vtx>* aNode) {
    for (u32 i = 0; i != aNode->mSize; ++i) {
        for (u32 j = 0; j != 3; ++j) {
            if (aNode->mData[i].n.ob[j] < -0x7FFF || 
                aNode->mData[i].n.ob[j] > +0x7FFF) {
                return true;
            }
        }
    }
    return false;
}

static inline bool IsUsingF32Vtx(Vec3f ob) {
    return ob[0] == F32VTX_SENTINEL_0 &&
           ob[1] == F32VTX_SENTINEL_1 &&
           ob[2] == F32VTX_SENTINEL_2;
}

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
    bool shouldUseF32Vtx = ShouldUseF32Vtx(aNode);
    if (shouldUseF32Vtx) {
        WriteBytes<u32>(aFile, aNode->mSize + 1);

        // Write sentinel
        WriteBytes<s16>(aFile, F32VTX_SENTINEL_0);
        WriteBytes<s16>(aFile, F32VTX_SENTINEL_1);
        WriteBytes<s16>(aFile, F32VTX_SENTINEL_2);
        WriteBytes<s16>(aFile, 0);
        WriteBytes<s16>(aFile, 0);
        WriteBytes<s16>(aFile, 0);
        WriteBytes<s8> (aFile, 0);
        WriteBytes<s8> (aFile, 0);
        WriteBytes<s8> (aFile, 0);
        WriteBytes<u8> (aFile, 0);
    } else {
        WriteBytes<u32>(aFile, aNode->mSize);
    }
    for (u32 i = 0; i != aNode->mSize; ++i) {
        if (shouldUseF32Vtx) {
            WriteBytes<f32>(aFile, aNode->mData[i].n.ob[0]);
            WriteBytes<f32>(aFile, aNode->mData[i].n.ob[1]);
            WriteBytes<f32>(aFile, aNode->mData[i].n.ob[2]);
        } else {
            WriteBytes<s16>(aFile, aNode->mData[i].n.ob[0]);
            WriteBytes<s16>(aFile, aNode->mData[i].n.ob[1]);
            WriteBytes<s16>(aFile, aNode->mData[i].n.ob[2]);
        }
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
    bool isUsingF32Vtx = false;
    _Node->mSize = ReadBytes<u32>(aFile);
    _Node->mData = New<Vtx>(_Node->mSize);
    for (u32 i = 0; i != _Node->mSize; ++i) {
        if (isUsingF32Vtx) {
            _Node->mData[i].n.ob[0] = ReadBytes<f32>(aFile);
            _Node->mData[i].n.ob[1] = ReadBytes<f32>(aFile);
            _Node->mData[i].n.ob[2] = ReadBytes<f32>(aFile);
        } else {
            _Node->mData[i].n.ob[0] = ReadBytes<s16>(aFile);
            _Node->mData[i].n.ob[1] = ReadBytes<s16>(aFile);
            _Node->mData[i].n.ob[2] = ReadBytes<s16>(aFile);
        }
        _Node->mData[i].n.flag  = ReadBytes<s16>(aFile);
        _Node->mData[i].n.tc[0] = ReadBytes<s16>(aFile);
        _Node->mData[i].n.tc[1] = ReadBytes<s16>(aFile);
        _Node->mData[i].n.n[0]  = ReadBytes<s8> (aFile);
        _Node->mData[i].n.n[1]  = ReadBytes<s8> (aFile);
        _Node->mData[i].n.n[2]  = ReadBytes<s8> (aFile);
        _Node->mData[i].n.a     = ReadBytes<u8> (aFile);

        // Check sentinel on first vertex
        if (!isUsingF32Vtx && i == 0 && IsUsingF32Vtx(_Node->mData[i].n.ob)) {
            _Node->mSize--; i--;
            isUsingF32Vtx = true;
        }
    }

    // Append
    aGfxData->mVertices.Add(_Node);
}
