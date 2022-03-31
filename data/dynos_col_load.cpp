#include "dynos.cpp.h"

//
// Load collision from binary
//

static DataNode<Collision>* LoadCollisionData(FILE *aFile) {
    DataNode<Collision> *_Node = New<DataNode<Collision>>();

    // Name
    _Node->mName.Read(aFile);

    // Data
    _Node->mSize = ReadBytes<u32>(aFile);
    _Node->mData = New<Collision>(_Node->mSize);
    for (u32 i = 0; i != _Node->mSize; ++i) {
        _Node->mData[i] = ReadBytes<Collision>(aFile);
    }

    return _Node;
}

DataNode<Collision>* DynOS_Col_LoadFromBinary(const SysPath &aPackFolder, const char *aCollisionName) {
    // Load data from binary file
    DataNode<Collision>* collisionNode = NULL;
    SysPath _Filename = fstring("%s/%s.col", aPackFolder.begin(), aCollisionName);
    FILE *_File = fopen(_Filename.c_str(), "rb");
    if (_File) {
        collisionNode = LoadCollisionData(_File);
        fclose(_File);
    }

    return collisionNode;
}
