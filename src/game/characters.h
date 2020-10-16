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
};

extern struct Character gCharacters[];

#endif // CHARACTERS_H
