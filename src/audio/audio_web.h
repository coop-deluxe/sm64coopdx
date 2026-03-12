#ifndef AUDIO_WEB_H
#define AUDIO_WEB_H

#ifdef TARGET_WEB

#include "internal.h"

/**
 * Convert a bank body from 64-bit host pointer layout to 32-bit WASM layout.
 *
 * The compiled-in sound bank data (gSoundDataADSR) uses 64-bit struct alignment
 * from the host build tools.  On 32-bit WASM sizeof(void*)==4, so every struct
 * that contains a pointer has a different size/layout.  This function reads the
 * raw 64-bit data and writes properly-laid-out 32-bit structs into the output
 * AudioBank buffer, then performs the standard pointer-offset patching.
 *
 * @param src64       Raw 64-bit bank body data (ctlData + 0x10).
 * @param src64Size   Size of the 64-bit bank body in bytes.
 * @param outBank     Pre-allocated AudioBank buffer (at least src64Size bytes).
 * @param tblOffset   TBL base pointer for sample address patching.
 * @param numInstruments  Number of instruments in the bank.
 * @param numDrums        Number of drums in the bank.
 */
void web_patch_bank_64to32(const u8 *src64, u32 src64Size,
                           struct AudioBank *outBank, u8 *tblOffset,
                           u32 numInstruments, u32 numDrums);

#endif /* TARGET_WEB */
#endif /* AUDIO_WEB_H */
