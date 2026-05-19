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
void DynOS_GfxDynCmd_Load(BinFile *aFile, UNUSED GfxData *aGfxData) {
    UNUSED String _DisplayListName; _DisplayListName.Read(aFile);
    aFile->Read<u32>();
    aFile->Read<u8>();
}
