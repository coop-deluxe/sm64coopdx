#include "dynos.cpp.h"

  /////////////
 // Parsing //
/////////////

  /////////////
 // Writing //
/////////////

  /////////////
 // Reading //
/////////////

// For retro-compatibility
void DynOS_GfxDynCmd_Load(BinFile *aFile, GfxData *aGfxData) {
    Gfx *_Data = NULL;
    String _DisplayListName; _DisplayListName.Read(aFile);
    for (auto& _DisplayList : aGfxData->mDisplayLists) {
        if (_DisplayList->mName == _DisplayListName) {
            _Data = _DisplayList->mData;
            break;
        }
    }
    if (!_Data) {
        sys_fatal("Display list not found: %s", _DisplayListName.begin());
    }
    aFile->Read<u32>();
    aFile->Read<u8>();
}
