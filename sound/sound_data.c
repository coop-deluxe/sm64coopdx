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

// 0x2e0 is the offset to the first sample
// header is not extracted because it uses pointers that are 32 bits
// in size in the rom, where in coop, the size of a pointer may be larger
ROM_ASSET_LOAD_SAMPLE(sample_body_data, &gSoundDataRaw[0x2e0], 0x005936a0, 2123556, 0x00000000, 2123556);

// 0x41c0 is the offset to the first sequence
// 00_sound_player is modified in coop, so only overwrite the music data
ROM_ASSET_LOAD_SEQUENCE(sequence_body_data, &gMusicData[0x41c0], 0x007b3e10, 100368, 0x00000000, 100368);
