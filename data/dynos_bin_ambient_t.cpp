#include "dynos.cpp.h"

  /////////////
 // Parsing //
/////////////

DataNode<Ambient_t>* DynOS_AmbientT_Parse(GfxData* aGfxData, DataNode<Ambient_t>* aNode) {
    if (aNode->mData) return aNode;

    // Check tokens count
    if (aNode->mTokens.Count() < 8) {
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
    aNode->mData = New<Ambient_t>();
    *aNode->mData = {
            {  cr,  cg,  cb}, 0,
            { c2r, c2g, c2b}, 0
        };
    aNode->mLoadIndex = aGfxData->mLoadIndex++;
    return aNode;
}

  /////////////
 // Writing //
/////////////

void DynOS_AmbientT_Write(BinFile* aFile, GfxData* aGfxData, DataNode<Ambient_t> *aNode) {
    if (!aNode->mData) return;

    // Header
    aFile->Write<u8>(DATA_TYPE_AMBIENT_T);
    aNode->mName.Write(aFile);

    // Data
    aFile->Write<Ambient_t>(*aNode->mData);
}

  /////////////
 // Reading //
/////////////

void DynOS_AmbientT_Load(BinFile *aFile, GfxData *aGfxData) {
    DataNode<Ambient_t> *_Node = New<DataNode<Ambient_t>>();

    // Name
    _Node->mName.Read(aFile);

    // Data
    // HACK: allocate for Light_t size due to PC port rendering all ambients as lights
    _Node->mData = (Ambient_t*)New<Light_t>();
    *_Node->mData = aFile->Read<Ambient_t>();

    // Append
    aGfxData->mAmbientTs.Add(_Node);
}
