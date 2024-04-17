#include "dynos.cpp.h"

extern "C" {
#include "include/level_misc_macros.h"
#include "game/moving_texture.h"
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnarrowing"

  /////////////
 // Parsing //
/////////////

#define movtexqc_constant(x) if (_Arg == #x) { return (Movtex*) (x); }
static Movtex* ParseMovtexQCSymbolArg(GfxData* aGfxData, DataNode<MovtexQC>* aNode, u64 aTokenIndex) {
    const String& _Arg = aNode->mTokens[aTokenIndex];

    // Other constants
    movtexqc_constant(NULL);

    // Movtexs
    for (auto& _Node : aGfxData->mMovtexs) {
        if (_Arg == _Node->mName) {
            return DynOS_Movtex_Parse(aGfxData, _Node, false)->mData;
        }
    }

    // Unknown
    PrintDataError("  ERROR: Unknown movtexqc arg: %s", _Arg.begin());
    return NULL;
}

DataNode<MovtexQC>* DynOS_MovtexQC_Parse(GfxData* aGfxData, DataNode<MovtexQC>* aNode) {
    if (aNode->mData) return aNode;

    // MovtexQC data
    aNode->mSize = (u32) (aNode->mTokens.Count() / 2);
    aNode->mData = New<MovtexQC>(aNode->mSize);
    for (u32 i = 0; i != aNode->mSize; ++i) {
        s16 id = (s16) aNode->mTokens[2 * i + 0].ParseInt();
        Movtex* quadArraySegmented = ParseMovtexQCSymbolArg(aGfxData, aNode, 2 * i + 1);
        aNode->mData[i] = { id, quadArraySegmented };
        aGfxData->mPointerList.Add(aNode->mData[i].quadArraySegmented);
    }
    aNode->mLoadIndex = aGfxData->mLoadIndex++;
    return aNode;
}

#pragma GCC diagnostic pop

  /////////////
 // Writing //
/////////////

void DynOS_MovtexQC_Write(BinFile* aFile, GfxData* aGfxData, DataNode<MovtexQC> *aNode) {
    if (!aNode->mData) return;

    // Name
    aFile->Write<u8>(DATA_TYPE_MOVTEXQC);
    aNode->mName.Write(aFile);

    // Data
    aFile->Write<u32>(aNode->mSize);
    for (u32 i = 0; i != aNode->mSize; ++i) {
        aFile->Write<s16>(aNode->mData[i].id);
        DynOS_Pointer_Write(aFile, (const void *) (aNode->mData[i].quadArraySegmented), aGfxData);
    }
}

  /////////////
 // Reading //
/////////////

DataNode<MovtexQC>* DynOS_MovtexQC_Load(BinFile *aFile, GfxData *aGfxData) {
    DataNode<MovtexQC> *_Node = New<DataNode<MovtexQC>>();

    // Name
    _Node->mName.Read(aFile);

    // Data
    _Node->mSize = aFile->Read<u32>();
    _Node->mData = New<MovtexQC>(_Node->mSize);
    for (u32 i = 0; i != _Node->mSize; ++i) {
        _Node->mData[i].id = aFile->Read<s16>();
        u32 _Value = aFile->Read<u32>();
        void *_Ptr = DynOS_Pointer_Load(aFile, aGfxData, _Value, &_Node->mFlags);
        _Node->mData[i].quadArraySegmented = (Movtex*)_Ptr;
    }

    // Add it
    if (aGfxData != NULL) {
        aGfxData->mMovtexQCs.Add(_Node);
    }

    return _Node;
}
