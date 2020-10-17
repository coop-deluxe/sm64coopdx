#ifndef LUIGI_AUDIO_DEFINES_H
#define LUIGI_AUDIO_DEFINES_H

/* Mario Sound Effects */
// A random number 0-2 is added to the sound ID before playing, producing Yah/Wah/Hoo
#define SOUND_LUIGI_YAH_WAH_HOO      SOUND_ARG_LOAD(0x0A, 4, 0x00, 0x80, 8)
#define SOUND_LUIGI_HOOHOO           SOUND_ARG_LOAD(0x0A, 4, 0x03, 0x80, 8)
#define SOUND_LUIGI_YAHOO            SOUND_ARG_LOAD(0x0A, 4, 0x04, 0x80, 8)
#define SOUND_LUIGI_UH               SOUND_ARG_LOAD(0x0A, 4, 0x05, 0x80, 8)
#define SOUND_LUIGI_HRMM             SOUND_ARG_LOAD(0x0A, 4, 0x06, 0x80, 8)
#define SOUND_LUIGI_WAH2             SOUND_ARG_LOAD(0x0A, 4, 0x07, 0x80, 8)
#define SOUND_LUIGI_WHOA             SOUND_ARG_LOAD(0x0A, 4, 0x08, 0xC0, 8)
#define SOUND_LUIGI_EEUH             SOUND_ARG_LOAD(0x0A, 4, 0x09, 0x80, 8)
#define SOUND_LUIGI_ATTACKED         SOUND_ARG_LOAD(0x0A, 4, 0x0A, 0xFF, 8)
#define SOUND_LUIGI_OOOF             SOUND_ARG_LOAD(0x0A, 4, 0x0B, 0x80, 8)
#define SOUND_LUIGI_OOOF2            SOUND_ARG_LOAD(0x0A, 4, 0x0B, 0xD0, 8)
#define SOUND_LUIGI_HERE_WE_GO       SOUND_ARG_LOAD(0x0A, 4, 0x0C, 0x80, 8)
#define SOUND_LUIGI_YAWNING          SOUND_ARG_LOAD(0x0A, 4, 0x0D, 0x80, 8)
#define SOUND_LUIGI_SNORING1         SOUND_ARG_LOAD(0x0A, 4, 0x0E, 0x80, 8)
#define SOUND_LUIGI_SNORING2         SOUND_ARG_LOAD(0x0A, 4, 0x0F, 0x80, 8)
#define SOUND_LUIGI_WAAAOOOW         SOUND_ARG_LOAD(0x0A, 4, 0x10, 0xC0, 8)
#define SOUND_LUIGI_HAHA             SOUND_ARG_LOAD(0x0A, 4, 0x11, 0x80, 8)
#define SOUND_LUIGI_HAHA_2           SOUND_ARG_LOAD(0x0A, 4, 0x11, 0xF0, 8)
#define SOUND_LUIGI_UH2              SOUND_ARG_LOAD(0x0A, 4, 0x13, 0xD0, 8)
#define SOUND_LUIGI_UH2_2            SOUND_ARG_LOAD(0x0A, 4, 0x13, 0x80, 8)
#define SOUND_LUIGI_ON_FIRE          SOUND_ARG_LOAD(0x0A, 4, 0x14, 0xA0, 8)
#define SOUND_LUIGI_DYING            SOUND_ARG_LOAD(0x0A, 4, 0x15, 0xFF, 8)
#define SOUND_LUIGI_PANTING_COLD     SOUND_ARG_LOAD(0x0A, 4, 0x16, 0x80, 8)

// A random number 0-2 is added to the sound ID before playing
#define SOUND_LUIGI_PANTING                     SOUND_ARG_LOAD(0x0A, 4, 0x18, 0x80, 8)

#define SOUND_LUIGI_COUGHING1                   SOUND_ARG_LOAD(0x0A, 4, 0x1B, 0x80, 8)
#define SOUND_LUIGI_COUGHING2                   SOUND_ARG_LOAD(0x0A, 4, 0x1C, 0x80, 8)
#define SOUND_LUIGI_COUGHING3                   SOUND_ARG_LOAD(0x0A, 4, 0x1D, 0x80, 8)
#define SOUND_LUIGI_PUNCH_YAH                   SOUND_ARG_LOAD(0x0A, 4, 0x1E, 0x80, 8)
#define SOUND_LUIGI_PUNCH_HOO                   SOUND_ARG_LOAD(0x0A, 4, 0x1F, 0x80, 8)
#define SOUND_LUIGI_MAMA_MIA                    SOUND_ARG_LOAD(0x0A, 4, 0x20, 0x80, 8)
//#define SOUND_LUIGI_OKEY_DOKEY                  0x2021
#define SOUND_LUIGI_GROUND_POUND_WAH            SOUND_ARG_LOAD(0x0A, 4, 0x22, 0x80, 8)
#define SOUND_LUIGI_DROWNING                    SOUND_ARG_LOAD(0x0A, 4, 0x23, 0xF0, 8)
#define SOUND_LUIGI_PUNCH_WAH                   SOUND_ARG_LOAD(0x0A, 4, 0x24, 0x80, 8)

// A random number 0-4 is added to the sound ID before playing, producing one of
// Yahoo! (60% chance), Waha! (20%), or Yippee! (20%).
#define SOUND_LUIGI_YAHOO_WAHA_YIPPEE           SOUND_ARG_LOAD(0x0A, 4, 0x2B, 0x80, 8)

#define SOUND_LUIGI_DOH                         SOUND_ARG_LOAD(0x0A, 4, 0x30, 0x80, 8)
#define SOUND_LUIGI_GAME_OVER                   SOUND_ARG_LOAD(0x0A, 4, 0x31, 0xFF, 8)
#define SOUND_LUIGI_HELLO                       SOUND_ARG_LOAD(0x0A, 4, 0x32, 0xFF, 8)
#define SOUND_LUIGI_PRESS_START_TO_PLAY         SOUND_ARG_LOAD(0x0A, 4, 0x33, 0xFF, 0xA)
#define SOUND_LUIGI_TWIRL_BOUNCE                SOUND_ARG_LOAD(0x0A, 4, 0x34, 0x80, 8)
#define SOUND_LUIGI_SNORING3                    SOUND_ARG_LOAD(0x0A, 4, 0x35, 0xFF, 8)
#define SOUND_LUIGI_SO_LONGA_BOWSER             SOUND_ARG_LOAD(0x0A, 4, 0x36, 0x80, 8)
#define SOUND_LUIGI_IMA_TIRED                   SOUND_ARG_LOAD(0x0A, 4, 0x37, 0x80, 8)

#endif // LUIGI_AUDIO_DEFINES_H