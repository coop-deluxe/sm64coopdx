#include "sound_data.h"
#include "pc/rom_assets.h"

unsigned char gSoundDataADSR[] = {
    #embed "sound/sound_data.ctl"
};

unsigned char gSoundDataRaw[] = {
    #embed "sound/sound_data.tbl"
};

unsigned char gMusicData[] = {
    #embed "sound/sequences.bin"
};

#ifndef VERSION_SH
unsigned char gBankSetsData[] = {
    #embed "sound/bank_sets"
};
#endif
