#include "sound_data.h"
#include "pc/rom_assets.h"

#define SAMPLES_SIZE 0x5b8200
#define SEQUENCES_SIZE 0x1ca00

unsigned char gSoundDataADSR[] = {
#embed "sound/sound_data.ctl"
};

unsigned char gSoundDataRaw[SAMPLES_SIZE] = {
#embed "sound/sound_data.tbl"
};

unsigned char gMusicData[SEQUENCES_SIZE] = {
#embed "sound/sequences.bin"
};

#ifndef VERSION_SH
unsigned char gBankSetsData[] = {
#embed "sound/bank_sets"
};
#endif
