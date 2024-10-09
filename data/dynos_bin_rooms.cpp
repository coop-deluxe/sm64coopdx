#include "dynos.cpp.h"

extern "C" {
}

  /////////////
 // Parsing //
/////////////

DataNode<u8>* DynOS_Rooms_Parse(GfxData* aGfxData, DataNode<u8>* aNode) {
    if (aNode->mData) return aNode;

    // U8 data
    aNode->mSize = (u32) (aNode->mTokens.Count());
    aNode->mData = New<u8>(aNode->mSize);
    for (u32 i = 0; i != aNode->mSize; ++i) {
        aNode->mData[i] = (u8) aNode->mTokens[i].ParseInt();
    }
    aNode->mLoadIndex = aGfxData->mLoadIndex++;
    return aNode;
}

  /////////////
 // Writing //
/////////////

void DynOS_Rooms_Write(BinFile* aFile, GfxData* aGfxData, DataNode<u8> *aNode) {
    if (!aNode->mData) return;

    // Name
    aFile->Write<u8>(DATA_TYPE_ROOMS);
    aNode->mName.Write(aFile);

    // Data
    aFile->Write<u32>(aNode->mSize);
    for (u32 i = 0; i != aNode->mSize; ++i) {
        aFile->Write<u8>(aNode->mData[i]);
    }
}

  /////////////
 // Reading //
/////////////

DataNode<u8>* DynOS_Rooms_Load(BinFile *aFile, GfxData *aGfxData) {
    DataNode<u8> *_Node = New<DataNode<u8>>();

    // Name
    _Node->mName.Read(aFile);

    // Data
    _Node->mSize = aFile->Read<u32>();
    _Node->mData = New<u8>(_Node->mSize);
    for (u32 i = 0; i != _Node->mSize; ++i) {
        _Node->mData[i] = aFile->Read<u8>();
    }

    // Add it
    if (aGfxData != NULL) {
        aGfxData->mRooms.Add(_Node);
    }

    return _Node;
}
