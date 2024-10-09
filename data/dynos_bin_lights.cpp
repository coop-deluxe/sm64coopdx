#include "dynos.cpp.h"

  /////////////
 // Parsing //
/////////////

DataNode<Lights1>* DynOS_Lights_Parse(GfxData* aGfxData, DataNode<Lights1>* aNode) {
    if (aNode->mData) return aNode;

    // Check tokens count
    if (aNode->mTokens.Count() < 10) {
        PrintDataError("  ERROR: %s: not enough data", aNode->mName.begin());
        return aNode;
    }

    // Parse def token
    if (aNode->mTokens[0] != "gdSPDefLights1") {
        PrintDataError("  ERROR: Invalid def token: should be gdSPDefLights1, is %s", aNode->mTokens[0].begin());
        return aNode;
    }

    // Parse data tokens
    u8 ar = (u8) aNode->mTokens[1].ParseInt();
    u8 ag = (u8) aNode->mTokens[2].ParseInt();
    u8 ab = (u8) aNode->mTokens[3].ParseInt();
    u8 r1 = (u8) aNode->mTokens[4].ParseInt();
    u8 g1 = (u8) aNode->mTokens[5].ParseInt();
    u8 b1 = (u8) aNode->mTokens[6].ParseInt();
    s8  x1 = (s8)  aNode->mTokens[7].ParseInt();
    s8  y1 = (s8)  aNode->mTokens[8].ParseInt();
    s8  z1 = (s8)  aNode->mTokens[9].ParseInt();
    aNode->mData = New<Lights1>();
    *aNode->mData = gdSPDefLights1(ar, ag, ab, r1, g1, b1, x1, y1, z1);
    aNode->mLoadIndex = aGfxData->mLoadIndex++;
    return aNode;
}

  /////////////
 // Writing //
/////////////

void DynOS_Lights_Write(BinFile* aFile, GfxData* aGfxData, DataNode<Lights1> *aNode) {
    if (!aNode->mData) return;

    // Header
    aFile->Write<u8>(DATA_TYPE_LIGHT);
    aNode->mName.Write(aFile);

    // Data
    aFile->Write<Lights1>(*aNode->mData);
}

  /////////////
 // Reading //
/////////////

void DynOS_Lights_Load(BinFile *aFile, GfxData *aGfxData) {
    DataNode<Lights1> *_Node = New<DataNode<Lights1>>();

    // Name
    _Node->mName.Read(aFile);

    // Data
    _Node->mData = New<Lights1>();
    *_Node->mData = aFile->Read<Lights1>();

    // Append
    aGfxData->mLights.Add(_Node);
}
