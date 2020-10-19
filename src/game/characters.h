#ifndef CHARACTERS_H
#define CHARACTERS_H
#include "PR/ultratypes.h"
// NOTE: do not include any additional headers

enum CharacterType {
    CT_MARIO,
    CT_LUIGI,

    // must be last
    CT_MAX
};

struct Character {
    char hudHead;
    u32 cameraHudHead;
    u32 modelId;
    u32 capModelId;
    s32 capKleptoAnimState;
    s32 capUkikiAnimState;
    // sounds
    s32 soundYahWahHoo;
    s32 soundHoohoo;
    s32 soundYahoo;
    s32 soundUh;
    s32 soundHrmm;
    s32 soundWah2;
    s32 soundWhoa;
    s32 soundEeuh;
    s32 soundAttacked;
    s32 soundOoof;
    s32 soundOoof2;
    s32 soundHereWeGo;
    s32 soundYawning;
    s32 soundSnoring1;
    s32 soundSnoring2;
    s32 soundWaaaooow;
    s32 soundHaha;
    s32 soundHaha_2;
    s32 soundUh2;
    s32 soundUh2_2;
    s32 soundOnFire;
    s32 soundDying;
    s32 soundPantingCold;
    s32 soundPanting;
    s32 soundCoughing1;
    s32 soundCoughing2;
    s32 soundCoughing3;
    s32 soundPunchYah;
    s32 soundPunchHoo;
    s32 soundMamaMia;
    s32 soundGroundPoundWah;
    s32 soundDrowning;
    s32 soundPunchWah;
    s32 soundYahooWahaYippee;
    s32 soundDoh;
    s32 soundGameOver;
    s32 soundHello;
    s32 soundPressStartToPlay;
    s32 soundTwirlBounce;
    s32 soundSnoring3;
    s32 soundSoLongaBowser;
    s32 soundImaTired;
};
struct MarioState;
extern struct Character gCharacters[];
struct Character* get_character_sound(struct MarioState* m);

#endif // CHARACTERS_H
