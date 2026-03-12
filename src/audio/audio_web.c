#ifdef TARGET_WEB

#include <ultra64.h>
#include <string.h>
#include <assert.h>

#include "internal.h"
#include "audio_web.h"

/*
 * 64-bit vs 32-bit struct sizes (non-SH, non-EU, i.e. VERSION_US):
 *
 * AudioBankSound:   64-bit: 16 (ptr8 + f32 + pad4)    32-bit:  8 (ptr4 + f32)
 * AudioBankSample:  64-bit: 40 (2+pad6 + ptr8*3 + u32+pad4)  32-bit: 20 (2+pad2 + ptr4*3 + u32)
 * Drum:             64-bit: 32 (3+pad5 + Sound16 + ptr8)      32-bit: 16 (3+pad1 + Sound8 + ptr4)
 * Instrument:       64-bit: 64 (4+pad4 + ptr8 + Sound16*3)    32-bit: 32 (4 + ptr4 + Sound8*3)
 * AdsrEnvelope:     64-bit:  4 (s16+s16, no ptrs)             32-bit:  4
 * AdpcmLoop:        64-bit: variable (no ptrs)                 32-bit: same
 * AdpcmBook:        64-bit: variable (no ptrs)                 32-bit: same
 *
 * AudioBank header: 64-bit: 8 + 8*numInstruments              32-bit: 4 + 4*numInstruments
 */

/* Sizes of structures in 64-bit layout */
#define SOUND_SIZE_64    16
#define SAMPLE_SIZE_64   40
#define DRUM_SIZE_64     32
#define INST_SIZE_64     64
#define ENVELOPE_SIZE     4  /* same on both */

/* Sizes of structures in 32-bit layout */
#define SOUND_SIZE_32     8
#define SAMPLE_SIZE_32   20
#define DRUM_SIZE_32     16
#define INST_SIZE_32     32

/* Field offsets within 64-bit Drum struct */
#define DRUM64_RELEASE_RATE   0
#define DRUM64_PAN            1
#define DRUM64_LOADED         2
/* pad to 8 */
#define DRUM64_SOUND          8   /* AudioBankSound: sample(8) + tuning(4) + pad(4) */
#define DRUM64_SOUND_SAMPLE   8
#define DRUM64_SOUND_TUNING  16
#define DRUM64_ENVELOPE      24   /* ptr(8) */

/* Field offsets within 32-bit Drum struct */
#define DRUM32_RELEASE_RATE   0
#define DRUM32_PAN            1
#define DRUM32_LOADED         2
/* pad to 4 */
#define DRUM32_SOUND          4   /* AudioBankSound: sample(4) + tuning(4) */
#define DRUM32_SOUND_SAMPLE   4
#define DRUM32_SOUND_TUNING   8
#define DRUM32_ENVELOPE      12   /* ptr(4) */

/* Field offsets within 64-bit Instrument struct */
#define INST64_LOADED            0
#define INST64_NORMAL_RANGE_LO   1
#define INST64_NORMAL_RANGE_HI   2
#define INST64_RELEASE_RATE      3
/* pad to 8 */
#define INST64_ENVELOPE          8   /* ptr(8) */
#define INST64_LOW_SOUND        16   /* AudioBankSound(16) */
#define INST64_NORMAL_SOUND     32
#define INST64_HIGH_SOUND       48

/* Field offsets within 32-bit Instrument struct */
#define INST32_LOADED            0
#define INST32_NORMAL_RANGE_LO   1
#define INST32_NORMAL_RANGE_HI   2
#define INST32_RELEASE_RATE      3
#define INST32_ENVELOPE          4   /* ptr(4) */
#define INST32_LOW_SOUND         8   /* AudioBankSound(8) */
#define INST32_NORMAL_SOUND     16
#define INST32_HIGH_SOUND       24

/* Field offsets within 64-bit AudioBankSample struct */
#define SAMP64_UNUSED         0
#define SAMP64_LOADED         1
/* pad to 8 */
#define SAMP64_SAMPLE_ADDR    8   /* ptr(8) */
#define SAMP64_LOOP          16   /* ptr(8) */
#define SAMP64_BOOK          24   /* ptr(8) */
#define SAMP64_SAMPLE_SIZE   32   /* u32(4) + pad(4) */

/* Field offsets within 32-bit AudioBankSample struct */
#define SAMP32_UNUSED         0
#define SAMP32_LOADED         1
/* pad to 4 */
#define SAMP32_SAMPLE_ADDR    4   /* ptr(4) */
#define SAMP32_LOOP           8   /* ptr(4) */
#define SAMP32_BOOK          12   /* ptr(4) */
#define SAMP32_SAMPLE_SIZE   16   /* u32(4) */

/*
 * Helper: read a little-endian pointer value from 64-bit data (8 bytes),
 * returning just the low 32 bits (sufficient since offsets are small).
 */
static u32 read_ptr64(const u8 *base, u32 offset) {
    u32 lo;
    memcpy(&lo, base + offset, 4);
    return lo;
}

static u32 read_u32(const u8 *base, u32 offset) {
    u32 val;
    memcpy(&val, base + offset, 4);
    return val;
}

static f32 read_f32(const u8 *base, u32 offset) {
    f32 val;
    memcpy(&val, base + offset, 4);
    return val;
}

static void write_ptr32(u8 *base, u32 offset, u32 val) {
    memcpy(base + offset, &val, 4);
}

static void write_u32(u8 *base, u32 offset, u32 val) {
    memcpy(base + offset, &val, 4);
}

static void write_f32(u8 *base, u32 offset, f32 val) {
    memcpy(base + offset, &val, 4);
}

/*
 * Offset remapping table.  As we copy structs from 64-bit to 32-bit layout
 * at potentially different positions, we record old->new offset mappings so
 * that pointer fields can be fixed up afterwards.
 */
#define MAX_OFFSET_MAP 4096

struct OffsetMapEntry {
    u32 off64;
    u32 off32;
};

struct OffsetMap {
    struct OffsetMapEntry entries[MAX_OFFSET_MAP];
    u32 count;
};

static void omap_add(struct OffsetMap *m, u32 off64, u32 off32) {
    if (m->count < MAX_OFFSET_MAP) {
        m->entries[m->count].off64 = off64;
        m->entries[m->count].off32 = off32;
        m->count++;
    }
}

static u32 omap_lookup(const struct OffsetMap *m, u32 off64) {
    for (u32 i = 0; i < m->count; i++) {
        if (m->entries[i].off64 == off64) {
            return m->entries[i].off32;
        }
    }
    /* Not found — return original (may be a NULL/0 offset) */
    return off64;
}

/*
 * Copy an AudioBankSound from 64-bit layout to 32-bit layout.
 * Returns the sample pointer offset (64-bit value) for later remapping.
 */
static void copy_sound_64to32(const u8 *src, u32 srcOff,
                               u8 *dst, u32 dstOff,
                               struct OffsetMap *map) {
    u32 sampleOff = read_ptr64(src, srcOff);       /* sample ptr */
    f32 tuning    = read_f32(src, srcOff + 8);      /* tuning after 8-byte ptr */
    write_ptr32(dst, dstOff, sampleOff);             /* sample ptr at 4-byte slot */
    write_f32(dst, dstOff + 4, tuning);              /* tuning right after */
    (void)map;
}

/*
 * Copy a Drum from 64-bit to 32-bit layout.
 */
static void copy_drum_64to32(const u8 *src, u32 srcOff,
                              u8 *dst, u32 dstOff,
                              struct OffsetMap *map) {
    /* Scalar fields: releaseRate, pan, loaded */
    dst[dstOff + DRUM32_RELEASE_RATE] = src[srcOff + DRUM64_RELEASE_RATE];
    dst[dstOff + DRUM32_PAN]          = src[srcOff + DRUM64_PAN];
    dst[dstOff + DRUM32_LOADED]       = src[srcOff + DRUM64_LOADED];
    dst[dstOff + 3]                   = 0; /* padding */

    /* Sound */
    copy_sound_64to32(src, srcOff + DRUM64_SOUND, dst, dstOff + DRUM32_SOUND, map);

    /* Envelope pointer */
    u32 envOff = read_ptr64(src, srcOff + DRUM64_ENVELOPE);
    write_ptr32(dst, dstOff + DRUM32_ENVELOPE, envOff);

    omap_add(map, srcOff, dstOff);
}

/*
 * Copy an Instrument from 64-bit to 32-bit layout.
 */
static void copy_inst_64to32(const u8 *src, u32 srcOff,
                              u8 *dst, u32 dstOff,
                              struct OffsetMap *map) {
    /* Scalar fields */
    dst[dstOff + INST32_LOADED]           = src[srcOff + INST64_LOADED];
    dst[dstOff + INST32_NORMAL_RANGE_LO]  = src[srcOff + INST64_NORMAL_RANGE_LO];
    dst[dstOff + INST32_NORMAL_RANGE_HI]  = src[srcOff + INST64_NORMAL_RANGE_HI];
    dst[dstOff + INST32_RELEASE_RATE]     = src[srcOff + INST64_RELEASE_RATE];

    /* Envelope pointer */
    u32 envOff = read_ptr64(src, srcOff + INST64_ENVELOPE);
    write_ptr32(dst, dstOff + INST32_ENVELOPE, envOff);

    /* Three AudioBankSounds */
    copy_sound_64to32(src, srcOff + INST64_LOW_SOUND,    dst, dstOff + INST32_LOW_SOUND, map);
    copy_sound_64to32(src, srcOff + INST64_NORMAL_SOUND, dst, dstOff + INST32_NORMAL_SOUND, map);
    copy_sound_64to32(src, srcOff + INST64_HIGH_SOUND,   dst, dstOff + INST32_HIGH_SOUND, map);

    omap_add(map, srcOff, dstOff);
}

/*
 * Copy an AudioBankSample from 64-bit to 32-bit layout.
 */
static void copy_sample_64to32(const u8 *src, u32 srcOff,
                                u8 *dst, u32 dstOff,
                                struct OffsetMap *map) {
    dst[dstOff + SAMP32_UNUSED] = src[srcOff + SAMP64_UNUSED];
    dst[dstOff + SAMP32_LOADED] = src[srcOff + SAMP64_LOADED];
    dst[dstOff + 2] = 0;
    dst[dstOff + 3] = 0;

    u32 sampleAddr = read_ptr64(src, srcOff + SAMP64_SAMPLE_ADDR);
    u32 loopOff    = read_ptr64(src, srcOff + SAMP64_LOOP);
    u32 bookOff    = read_ptr64(src, srcOff + SAMP64_BOOK);
    u32 sampleSize = read_u32(src, srcOff + SAMP64_SAMPLE_SIZE);

    write_ptr32(dst, dstOff + SAMP32_SAMPLE_ADDR, sampleAddr);
    write_ptr32(dst, dstOff + SAMP32_LOOP, loopOff);
    write_ptr32(dst, dstOff + SAMP32_BOOK, bookOff);
    write_u32(dst, dstOff + SAMP32_SAMPLE_SIZE, sampleSize);

    omap_add(map, srcOff, dstOff);
}

void web_patch_bank_64to32(const u8 *src64, u32 src64Size,
                           struct AudioBank *outBank, u8 *tblOffset,
                           u32 numInstruments, u32 numDrums) {
    static struct OffsetMap map;
    map.count = 0;

    u8 *dst = (u8 *)outBank;
    memset(dst, 0, src64Size); /* Clear output; src64Size >= 32-bit size */

    /*
     * Phase 1: Copy the AudioBank header.
     *
     * 64-bit layout: drums(8) + instruments[numInstruments](8 each)
     * 32-bit layout: drums(4) + instruments[numInstruments](4 each)
     */
    u32 hdr64Size = 8 + 8 * numInstruments;
    u32 hdr32Size = 4 + 4 * numInstruments;

    /* Drums pointer */
    u32 drumsOff = read_ptr64(src64, 0);
    write_ptr32(dst, 0, drumsOff);  /* Will be remapped later */

    /* Instruments pointers */
    for (u32 i = 0; i < numInstruments; i++) {
        u32 instOff = read_ptr64(src64, 8 + i * 8);
        write_ptr32(dst, 4 + i * 4, instOff);
    }

    omap_add(&map, 0, 0);  /* Bank header starts at 0 in both */

    /*
     * Phase 2: Discover and copy all sub-structures.
     *
     * We walk the pointer graph starting from the AudioBank header.
     * The drums pointer points to an array of Drum* (pointers, numDrums entries).
     * Each valid Drum* points to a Drum struct.
     * Each Instrument* points to an Instrument struct.
     * Within Drums/Instruments, Sound.sample points to AudioBankSample.
     * Within AudioBankSample, loop/book point to AdpcmLoop/AdpcmBook (no ptr fields).
     * Envelope pointers point to AdsrEnvelope arrays (no ptr fields).
     *
     * Strategy: we'll pack the 32-bit structs contiguously starting after
     * the 32-bit header.  For data that has no pointers (envelopes, loops,
     * books), we just need to remap the offset.
     */

    u32 writePos = hdr32Size;

    /* Align writePos to 4 bytes */
    writePos = (writePos + 3) & ~3;

    /*
     * Copy drums pointer array (Drum*[numDrums]).
     * 64-bit: each entry is 8 bytes.  32-bit: each entry is 4 bytes.
     */
    u32 drumsArr64 = drumsOff;  /* offset of Drum*[] in 64-bit data */
    u32 drumsArr32 = 0;
    if (drumsOff != 0 && numDrums > 0) {
        drumsArr32 = writePos;
        omap_add(&map, drumsArr64, drumsArr32);

        for (u32 i = 0; i < numDrums; i++) {
            u32 drumPtr = read_ptr64(src64, drumsArr64 + i * 8);
            write_ptr32(dst, drumsArr32 + i * 4, drumPtr);
        }
        writePos = drumsArr32 + numDrums * 4;
        writePos = (writePos + 3) & ~3;

        /* Now remap the drums pointer in the header */
        write_ptr32(dst, 0, drumsArr32);
    }

    /*
     * Copy each Drum struct.
     */
    if (drumsOff != 0 && numDrums > 0) {
        for (u32 i = 0; i < numDrums; i++) {
            u32 drumOff64 = read_ptr64(src64, drumsArr64 + i * 8);
            if (drumOff64 == 0) continue;
            if (drumOff64 >= src64Size) continue;

            u32 drumOff32 = writePos;
            copy_drum_64to32(src64, drumOff64, dst, drumOff32, &map);
            /* Update the drum pointer in the array */
            write_ptr32(dst, drumsArr32 + i * 4, drumOff32);
            writePos = drumOff32 + DRUM_SIZE_32;
            writePos = (writePos + 3) & ~3;
        }
    }

    /*
     * Copy each Instrument struct.
     */
    for (u32 i = 0; i < numInstruments; i++) {
        u32 instOff64 = read_ptr64(src64, 8 + i * 8);
        if (instOff64 == 0) continue;
        if (instOff64 >= src64Size) continue;

        u32 instOff32 = writePos;
        copy_inst_64to32(src64, instOff64, dst, instOff32, &map);
        /* Update the instrument pointer in the header */
        write_ptr32(dst, 4 + i * 4, instOff32);
        writePos = instOff32 + INST_SIZE_32;
        writePos = (writePos + 3) & ~3;
    }

    /*
     * Phase 3: Copy AudioBankSample structs.
     *
     * Samples are referenced from Sound.sample fields inside Drums and
     * Instruments.  We need to find all unique sample offsets, copy them,
     * and remap the sound.sample fields.
     *
     * Collect all sample offsets from the already-written 32-bit structs.
     */
    u32 sampleOffs64[512];
    u32 sampleSlots[512]; /* position of the ptr32 field that references this sample */
    u32 numSamples = 0;

    /* Scan drums for sample offsets */
    if (drumsOff != 0 && numDrums > 0) {
        for (u32 i = 0; i < numDrums; i++) {
            u32 drumOff64 = read_ptr64(src64, drumsArr64 + i * 8);
            if (drumOff64 == 0) continue;
            if (drumOff64 >= src64Size) continue;

            u32 sampOff64 = read_ptr64(src64, drumOff64 + DRUM64_SOUND_SAMPLE);
            if (sampOff64 != 0 && sampOff64 < src64Size && numSamples < 512) {
                u32 drumOff32 = omap_lookup(&map, drumOff64);
                sampleOffs64[numSamples] = sampOff64;
                sampleSlots[numSamples] = drumOff32 + DRUM32_SOUND_SAMPLE;
                numSamples++;
            }
        }
    }

    /* Scan instruments for sample offsets (3 sounds each) */
    for (u32 i = 0; i < numInstruments; i++) {
        u32 instOff64 = read_ptr64(src64, 8 + i * 8);
        if (instOff64 == 0) continue;
        if (instOff64 >= src64Size) continue;

        u32 instOff32 = omap_lookup(&map, instOff64);

        static const u32 soundOffsets64[] = { INST64_LOW_SOUND, INST64_NORMAL_SOUND, INST64_HIGH_SOUND };
        static const u32 soundOffsets32[] = { INST32_LOW_SOUND, INST32_NORMAL_SOUND, INST32_HIGH_SOUND };

        for (int s = 0; s < 3; s++) {
            u32 sampOff64 = read_ptr64(src64, instOff64 + soundOffsets64[s]);
            if (sampOff64 != 0 && sampOff64 < src64Size && numSamples < 512) {
                sampleOffs64[numSamples] = sampOff64;
                sampleSlots[numSamples] = instOff32 + soundOffsets32[s];
                numSamples++;
            }
        }
    }

    /* Copy unique samples and remap */
    for (u32 i = 0; i < numSamples; i++) {
        u32 off64 = sampleOffs64[i];

        /* Check if we already copied this sample */
        u32 existing = omap_lookup(&map, off64);
        if (existing != off64) {
            /* Already copied, just update the pointer */
            write_ptr32(dst, sampleSlots[i], existing);
            continue;
        }

        u32 off32 = writePos;
        copy_sample_64to32(src64, off64, dst, off32, &map);
        write_ptr32(dst, sampleSlots[i], off32);
        writePos = off32 + SAMPLE_SIZE_32;
        writePos = (writePos + 3) & ~3;
    }

    /*
     * Phase 4: Copy envelope, loop, and book data.
     *
     * These structs have NO pointer fields, so their binary layout is
     * identical on 32-bit and 64-bit.  We just need to copy the bytes
     * and remap the offsets that reference them.
     *
     * Envelopes: referenced from Drum.envelope and Instrument.envelope.
     * Loops: referenced from AudioBankSample.loop.
     * Books: referenced from AudioBankSample.book.
     *
     * For envelopes, we don't know the exact size (they're variable-length
     * arrays terminated by a sentinel).  We'll scan for the sentinel.
     *
     * For loops/books, we also need to figure out sizes.
     */

    /* Helper: collect all non-pointer-struct offsets and copy them.
     * Since these are raw data with no pointer fields, we can just
     * copy the bytes from the 64-bit source at the same offsets.
     *
     * HOWEVER, the 64-bit offsets point into the 64-bit data, and we need
     * to remap them in the 32-bit output.
     */

    /* Collect envelope offsets from drums */
    u32 envOffs64[256];
    u32 envSlots[256]; /* where in dst the envelope ptr field lives */
    u32 numEnvs = 0;

    if (drumsOff != 0 && numDrums > 0) {
        for (u32 i = 0; i < numDrums; i++) {
            u32 drumOff64 = read_ptr64(src64, drumsArr64 + i * 8);
            if (drumOff64 == 0 || drumOff64 >= src64Size) continue;
            u32 envOff64 = read_ptr64(src64, drumOff64 + DRUM64_ENVELOPE);
            if (envOff64 != 0 && envOff64 < src64Size && numEnvs < 256) {
                u32 drumOff32 = omap_lookup(&map, drumOff64);
                envOffs64[numEnvs] = envOff64;
                envSlots[numEnvs] = drumOff32 + DRUM32_ENVELOPE;
                numEnvs++;
            }
        }
    }

    /* Collect envelope offsets from instruments */
    for (u32 i = 0; i < numInstruments; i++) {
        u32 instOff64 = read_ptr64(src64, 8 + i * 8);
        if (instOff64 == 0 || instOff64 >= src64Size) continue;
        u32 envOff64 = read_ptr64(src64, instOff64 + INST64_ENVELOPE);
        if (envOff64 != 0 && envOff64 < src64Size && numEnvs < 256) {
            u32 instOff32 = omap_lookup(&map, instOff64);
            envOffs64[numEnvs] = envOff64;
            envSlots[numEnvs] = instOff32 + INST32_ENVELOPE;
            numEnvs++;
        }
    }

    /* Copy envelopes.  Each is an array of AdsrEnvelope (4 bytes each),
     * terminated when delay < 0 (or some other condition; the code in
     * patch_audio_bank doesn't inspect them, just patches the pointer).
     * We'll copy up to 128 bytes per envelope as a safe upper bound,
     * or until we hit the end of the source data.
     *
     * Actually, envelopes are at the SAME byte offsets in both layouts
     * because AdsrEnvelope has no pointers.  But we need to copy them
     * to the output buffer and remap the offset.
     */
    for (u32 i = 0; i < numEnvs; i++) {
        u32 off64 = envOffs64[i];
        u32 existing = omap_lookup(&map, off64);
        if (existing != off64) {
            write_ptr32(dst, envSlots[i], existing);
            continue;
        }

        /* Determine envelope size: scan for terminator (delay == 0 with special arg,
         * or negative delay).  The ADSR format: each entry is {s16 delay, s16 arg}.
         * Terminated by delay <= 0 (with the entry itself included). */
        u32 envSize = 0;
        for (u32 j = 0; j < 64; j++) { /* max 64 entries */
            s16 delay;
            memcpy(&delay, src64 + off64 + j * 4, 2);
            envSize += 4;
            if (delay <= 0) break; /* This is the last entry (or final release marker) */
        }

        u32 off32 = writePos;
        omap_add(&map, off64, off32);
        memcpy(dst + off32, src64 + off64, envSize);
        write_ptr32(dst, envSlots[i], off32);
        writePos = off32 + envSize;
        writePos = (writePos + 3) & ~3;
    }

    /* Collect loop and book offsets from samples */
    u32 loopOffs64[256], loopSlots[256];
    u32 bookOffs64[256], bookSlots[256];
    u32 numLoops = 0, numBooks = 0;

    for (u32 i = 0; i < numSamples; i++) {
        u32 sampOff64 = sampleOffs64[i];
        u32 sampOff32 = omap_lookup(&map, sampOff64);

        u32 loopOff64 = read_ptr64(src64, sampOff64 + SAMP64_LOOP);
        if (loopOff64 != 0 && loopOff64 < src64Size && numLoops < 256) {
            loopOffs64[numLoops] = loopOff64;
            loopSlots[numLoops] = sampOff32 + SAMP32_LOOP;
            numLoops++;
        }

        u32 bookOff64 = read_ptr64(src64, sampOff64 + SAMP64_BOOK);
        if (bookOff64 != 0 && bookOff64 < src64Size && numBooks < 256) {
            bookOffs64[numBooks] = bookOff64;
            bookSlots[numBooks] = sampOff32 + SAMP32_BOOK;
            numBooks++;
        }
    }

    /* Copy loops.  AdpcmLoop: {u32 start, u32 end, u32 count, u32 pad,
     * s16 state[16] (only if count != 0)}.  Base size = 16, with state = 48. */
    for (u32 i = 0; i < numLoops; i++) {
        u32 off64 = loopOffs64[i];
        u32 existing = omap_lookup(&map, off64);
        if (existing != off64) {
            write_ptr32(dst, loopSlots[i], existing);
            continue;
        }

        u32 count;
        memcpy(&count, src64 + off64 + 8, 4);
        u32 loopSize = 16 + (count != 0 ? 32 : 0);

        u32 off32 = writePos;
        omap_add(&map, off64, off32);
        memcpy(dst + off32, src64 + off64, loopSize);
        write_ptr32(dst, loopSlots[i], off32);
        writePos = off32 + loopSize;
        writePos = (writePos + 7) & ~7; /* 8-byte align as original */
    }

    /* Copy books.  AdpcmBook: {s32 order, s32 npredictors, s16 book[]}.
     * book size = 8 * order * npredictors (in bytes of s16, so
     * 8 * order * npredictors * sizeof(s16) = 16 * order * npredictors). */
    for (u32 i = 0; i < numBooks; i++) {
        u32 off64 = bookOffs64[i];
        u32 existing = omap_lookup(&map, off64);
        if (existing != off64) {
            write_ptr32(dst, bookSlots[i], existing);
            continue;
        }

        s32 order, npredictors;
        memcpy(&order, src64 + off64, 4);
        memcpy(&npredictors, src64 + off64 + 4, 4);
        u32 bookDataSize = 8 * order * npredictors * sizeof(s16);
        u32 bookTotalSize = 8 + bookDataSize;

        u32 off32 = writePos;
        omap_add(&map, off64, off32);
        memcpy(dst + off32, src64 + off64, bookTotalSize);
        write_ptr32(dst, bookSlots[i], off32);
        writePos = off32 + bookTotalSize;
        writePos = (writePos + 7) & ~7;
    }

    /*
     * Phase 5: Now perform standard pointer patching — convert offsets to
     * real pointers.  This is what patch_audio_bank normally does, but we
     * do it here on the already-remapped 32-bit data.
     *
     * All "pointer" fields currently contain offsets from the start of dst
     * (the 32-bit bank).  We add the bank base address to make them real
     * pointers.
     */
    uintptr_t base = (uintptr_t)dst;

    /* Patch AudioBank header: drums pointer */
    {
        u32 off = read_u32(dst, 0);
        if (off != 0) {
            write_ptr32(dst, 0, off + base);
        }
    }

    /* Patch AudioBank header: instruments pointers */
    for (u32 i = 0; i < numInstruments; i++) {
        u32 off = read_u32(dst, 4 + i * 4);
        if (off != 0) {
            write_ptr32(dst, 4 + i * 4, off + base);
        }
    }

    /* Patch drums pointer array */
    struct Drum **drumsArr = outBank->drums;
    if (drumsArr != NULL) {
        for (u32 i = 0; i < numDrums; i++) {
            uintptr_t off = (uintptr_t)drumsArr[i];
            if (off != 0) {
                drumsArr[i] = (struct Drum *)(off + base);
                struct Drum *drum = drumsArr[i];
                if (drum->loaded == 0) {
                    /* Patch sound.sample */
                    if (drum->sound.sample != NULL) {
                        drum->sound.sample = (struct AudioBankSample *)
                            ((uintptr_t)drum->sound.sample + base);
                        struct AudioBankSample *sample = drum->sound.sample;
                        if (sample->loaded == 0) {
                            /* sampleAddr is offset into TBL */
                            sample->sampleAddr = (u8 *)
                                ((uintptr_t)sample->sampleAddr + (uintptr_t)tblOffset);
                            if (sample->loop != NULL) {
                                sample->loop = (struct AdpcmLoop *)
                                    ((uintptr_t)sample->loop + base);
                            }
                            if (sample->book != NULL) {
                                sample->book = (struct AdpcmBook *)
                                    ((uintptr_t)sample->book + base);
                            }
                            sample->loaded = 1;
                        }
                    }
                    /* Patch envelope */
                    if (drum->envelope != NULL) {
                        drum->envelope = (struct AdsrEnvelope *)
                            ((uintptr_t)drum->envelope + base);
                    }
                    drum->loaded = 1;
                }
            }
        }
    }

    /* Patch instruments */
    for (u32 i = 0; i < numInstruments; i++) {
        struct Instrument *inst = outBank->instruments[i];
        if (inst == NULL) continue;
        if (inst->loaded != 0) continue;

        /* Patch envelope */
        if (inst->envelope != NULL) {
            inst->envelope = (struct AdsrEnvelope *)
                ((uintptr_t)inst->envelope + base);
        }

        /* Patch lowNotesSound */
        if (inst->lowNotesSound.sample != NULL) {
            inst->lowNotesSound.sample = (struct AudioBankSample *)
                ((uintptr_t)inst->lowNotesSound.sample + base);
            struct AudioBankSample *sample = inst->lowNotesSound.sample;
            if (sample->loaded == 0) {
                sample->sampleAddr = (u8 *)
                    ((uintptr_t)sample->sampleAddr + (uintptr_t)tblOffset);
                if (sample->loop != NULL)
                    sample->loop = (struct AdpcmLoop *)((uintptr_t)sample->loop + base);
                if (sample->book != NULL)
                    sample->book = (struct AdpcmBook *)((uintptr_t)sample->book + base);
                sample->loaded = 1;
            }
        }

        /* Patch normalNotesSound */
        if (inst->normalNotesSound.sample != NULL) {
            inst->normalNotesSound.sample = (struct AudioBankSample *)
                ((uintptr_t)inst->normalNotesSound.sample + base);
            struct AudioBankSample *sample = inst->normalNotesSound.sample;
            if (sample->loaded == 0) {
                sample->sampleAddr = (u8 *)
                    ((uintptr_t)sample->sampleAddr + (uintptr_t)tblOffset);
                if (sample->loop != NULL)
                    sample->loop = (struct AdpcmLoop *)((uintptr_t)sample->loop + base);
                if (sample->book != NULL)
                    sample->book = (struct AdpcmBook *)((uintptr_t)sample->book + base);
                sample->loaded = 1;
            }
        }

        /* Patch highNotesSound */
        if (inst->highNotesSound.sample != NULL) {
            inst->highNotesSound.sample = (struct AudioBankSample *)
                ((uintptr_t)inst->highNotesSound.sample + base);
            struct AudioBankSample *sample = inst->highNotesSound.sample;
            if (sample->loaded == 0) {
                sample->sampleAddr = (u8 *)
                    ((uintptr_t)sample->sampleAddr + (uintptr_t)tblOffset);
                if (sample->loop != NULL)
                    sample->loop = (struct AdpcmLoop *)((uintptr_t)sample->loop + base);
                if (sample->book != NULL)
                    sample->book = (struct AdpcmBook *)((uintptr_t)sample->book + base);
                sample->loaded = 1;
            }
        }

        inst->loaded = 1;
    }
}

#endif /* TARGET_WEB */
