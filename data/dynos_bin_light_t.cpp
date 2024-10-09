#include "dynos.cpp.h"

  /////////////
 // Parsing //
/////////////

DataNode<Light_t>* DynOS_LightT_Parse(GfxData* aGfxData, DataNode<Light_t>* aNode) {
    if (aNode->mData) return aNode;

    // Check tokens count
    if (aNode->mTokens.Count() < 12) {
        PrintDataError("  ERROR: %s: not enough data", aNode->mName.begin());
        return aNode;
    }

    // Parse data tokens
    u8 cr  = (u8) aNode->mTokens[0].ParseInt();
    u8 cg  = (u8) aNode->mTokens[1].ParseInt();
    u8 cb  = (u8) aNode->mTokens[2].ParseInt();
    u8 c2r = (u8) aNode->mTokens[4].ParseInt();
    u8 c2g = (u8) aNode->mTokens[5].ParseInt();
    u8 c2b = (u8) aNode->mTokens[6].ParseInt();
    s8 dx  = (s8) aNode->mTokens[8].ParseInt();
    s8 dy  = (s8) aNode->mTokens[9].ParseInt();
    s8 dz  = (s8) aNode->mTokens[10].ParseInt();
    aNode->mData = New<Light_t>();
    *aNode->mData = {
            {  cr,  cg,  cb}, 0,
            { c2r, c2g, c2b}, 0,
            {  dx,  dy,  dz}, 0
        };
    aNode->mLoadIndex = aGfxData->mLoadIndex++;
    return aNode;
}

  /////////////
 // Writing //
/////////////

void DynOS_LightT_Write(BinFile* aFile, GfxData* aGfxData, DataNode<Light_t> *aNode) {
    if (!aNode->mData) return;

    // Header
    aFile->Write<u8>(DATA_TYPE_LIGHT_T);
    aNode->mName.Write(aFile);

    // Data
    aFile->Write<Light_t>(*aNode->mData);
}

  /////////////
 // Reading //
/////////////

void DynOS_LightT_Load(BinFile *aFile, GfxData *aGfxData) {
    DataNode<Light_t> *_Node = New<DataNode<Light_t>>();

    // Name
    _Node->mName.Read(aFile);

    // Data
    _Node->mData = New<Light_t>();
    *_Node->mData = aFile->Read<Light_t>();

    // Append
    aGfxData->mLightTs.Add(_Node);
}
