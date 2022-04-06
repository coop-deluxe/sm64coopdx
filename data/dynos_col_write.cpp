#include "dynos.cpp.h"

//
// Collisions
//

static void WriteCollisionData(FILE* aFile, GfxData* aGfxData, DataNode<Collision> *aNode) {
    if (!aNode->mData) return;

    // Name
    WriteBytes<u8>(aFile, DATA_TYPE_COLLISION);
    aNode->mName.Write(aFile);

    // Data
    WriteBytes<u32>(aFile, aNode->mSize);
    for (u32 i = 0; i != aNode->mSize; ++i) {
        WriteBytes<Collision>(aFile, aNode->mData[i]);
    }
}

bool DynOS_Col_WriteBinary(const SysPath &aOutputFilename, GfxData *aGfxData, DataNode<Collision>* _Node) {
    FILE *_File = fopen(aOutputFilename.c_str(), "wb");
    if (!_File) {
        PrintError("  ERROR: Unable to create file \"%s\"", aOutputFilename.c_str());
        return false;
    }

    WriteCollisionData(_File, aGfxData, _Node);

    fclose(_File);
    return true;
}
