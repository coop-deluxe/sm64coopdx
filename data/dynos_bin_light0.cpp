#include "dynos.cpp.h"

  /////////////
 // Parsing //
/////////////

DataNode<Lights0>* DynOS_Light0_Parse(GfxData* aGfxData, DataNode<Lights0>* aNode) {
    if (aNode->mData) return aNode;

    // Check tokens count
    if (aNode->mTokens.Count() < 4) {
        PrintDataError("  ERROR: %s: not enough data", aNode->mName.begin());
        return aNode;
    }

    // Parse def token
    if (aNode->mTokens[0] != "gdSPDefLights0") {
        PrintDataError("  ERROR: Invalid def token: should be gdSPDefLights0, is %s", aNode->mTokens[0].begin());
        return aNode;
    }

    // Parse data tokens
    u8 ar = (u8) aNode->mTokens[1].ParseInt();
    u8 ag = (u8) aNode->mTokens[2].ParseInt();
    u8 ab = (u8) aNode->mTokens[3].ParseInt();
    aNode->mData = New<Lights0>();
    *aNode->mData = gdSPDefLights0(ar, ag, ab);
    aNode->mLoadIndex = aGfxData->mLoadIndex++;
    return aNode;
}

  /////////////
 // Writing //
/////////////

void DynOS_Light0_Write(BinFile* aFile, GfxData* aGfxData, DataNode<Lights0> *aNode) {
    if (!aNode->mData) return;

    // Header
    aFile->Write<u8>(DATA_TYPE_LIGHT_0);
    aNode->mName.Write(aFile);

    // Data
    aFile->Write<Lights0>(*aNode->mData);
}

  /////////////
 // Reading //
/////////////

void DynOS_Light0_Load(BinFile *aFile, GfxData *aGfxData) {
    DataNode<Lights0> *_Node = New<DataNode<Lights0>>();

    // Name
    _Node->mName.Read(aFile);

    // Data
    _Node->mData = New<Lights0>();
    *_Node->mData = aFile->Read<Lights0>();

    // Append
    aGfxData->mLight0s.Add(_Node);
}
