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
};

extern struct Character gCharacters[];

#endif // CHARACTERS_H
