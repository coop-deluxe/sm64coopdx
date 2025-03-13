#include "sound_data.h"
#include "pc/rom_assets.h"

#define SAMPLES_SIZE 0x5b8200
#define SEQUENCES_SIZE 0x1ca00

unsigned char gSoundDataADSR[] = {
#include "sound/sound_data.ctl.inc.c"
};

unsigned char gSoundDataRaw[SAMPLES_SIZE] = {
#include "sound/sound_data.tbl.inc.c"
};

unsigned char gMusicData[SEQUENCES_SIZE] = {
#include "sound/sequences.bin.inc.c"
};

#ifndef VERSION_SH
unsigned char gBankSetsData[] = {
#include "sound/bank_sets.inc.c"
};
#endif
