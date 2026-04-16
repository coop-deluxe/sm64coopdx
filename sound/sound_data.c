#include "sound_data.h"

#if defined(__i386__) || (defined(_WIN32) && !defined(_WIN64))
unsigned char gSoundDataADSR[] = {
#include "sound/sound_data.ctl.inc.c"
};

unsigned char gSoundDataRaw[] = {
#include "sound/sound_data.tbl.inc.c"
};

unsigned char gMusicData[] = {
#include "sound/sequences.bin.inc.c"
};
#else
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
#endif

#ifndef VERSION_SH
unsigned char gBankSetsData[] = {
#include "sound/bank_sets.inc.c"
};
#endif
