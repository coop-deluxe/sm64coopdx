#ifndef CHARACTERS_H
#define CHARACTERS_H
#include "PR/ultratypes.h"
// NOTE: do not include any additional headers

enum CharacterType {
    CT_MARIO,
    CT_LUIGI,
    CT_TOAD,
    CT_WALUIGI,

    // must be last
    CT_MAX
};

struct Character {
    enum CharacterType type;
    char* name;
    char hudHead;
    const u8* hudHeadTexture;
    u32 cameraHudHead;
    u32 modelId;
    u32 capModelId;
    u32 capMetalModelId;
    u32 capWingModelId;
    u32 capMetalWingModelId;
    u8 capEnemyLayer;
    Gfx* capEnemyGfx;
    Gfx* capEnemyDecalGfx;
    // anim
    u8 animOffsetEnabled;
    f32 animOffsetLowYPoint;
    f32 animOffsetFeet;
    f32 animOffsetHand;
    // sounds
    f32 soundFreqScale;
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

enum CharacterSound {
    CHAR_SOUND_YAH_WAH_HOO,
    CHAR_SOUND_HOOHOO,
    CHAR_SOUND_YAHOO,
    CHAR_SOUND_UH,
    CHAR_SOUND_HRMM,
    CHAR_SOUND_WAH2,
    CHAR_SOUND_WHOA,
    CHAR_SOUND_EEUH,
    CHAR_SOUND_ATTACKED,
    CHAR_SOUND_OOOF,
    CHAR_SOUND_OOOF2,
    CHAR_SOUND_HERE_WE_GO,
    CHAR_SOUND_YAWNING,
    CHAR_SOUND_SNORING1,
    CHAR_SOUND_SNORING2,
    CHAR_SOUND_WAAAOOOW,
    CHAR_SOUND_HAHA,
    CHAR_SOUND_HAHA_2,
    CHAR_SOUND_UH2,
    CHAR_SOUND_UH2_2,
    CHAR_SOUND_ON_FIRE,
    CHAR_SOUND_DYING,
    CHAR_SOUND_PANTING_COLD,
    CHAR_SOUND_PANTING,
    CHAR_SOUND_COUGHING1,
    CHAR_SOUND_COUGHING2,
    CHAR_SOUND_COUGHING3,
    CHAR_SOUND_PUNCH_YAH,
    CHAR_SOUND_PUNCH_HOO,
    CHAR_SOUND_MAMA_MIA,
    CHAR_SOUND_GROUND_POUND_WAH,
    CHAR_SOUND_DROWNING,
    CHAR_SOUND_PUNCH_WAH,
    CHAR_SOUND_YAHOO_WAHA_YIPPEE,
    CHAR_SOUND_DOH,
    CHAR_SOUND_GAME_OVER,
    CHAR_SOUND_HELLO,
    CHAR_SOUND_PRESS_START_TO_PLAY,
    CHAR_SOUND_TWIRL_BOUNCE,
    CHAR_SOUND_SNORING3,
    CHAR_SOUND_SO_LONGA_BOWSER,
    CHAR_SOUND_IMA_TIRED,
    CHAR_SOUND_MAX // MUST BE LAST
};

struct MarioState;
extern struct Character gCharacters[];
struct Character* get_character(struct MarioState* m);

void play_character_sound(struct MarioState* m, enum CharacterSound characterSound);
void play_character_sound_offset(struct MarioState* m, enum CharacterSound characterSound, u32 offset);
void play_character_sound_if_no_flag(struct MarioState* m, enum CharacterSound characterSound, u32 flags);

f32 get_character_anim_offset(struct MarioState* m);
void update_character_anim_offset(struct MarioState* m);

#endif // CHARACTERS_H
