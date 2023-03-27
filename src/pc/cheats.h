#ifndef _CHEATS_H
#define _CHEATS_H

#include <stdbool.h>
#include "network/network.h"

#define SUPER_SPEED_MULTIPLIER 4

struct Cheats {
    bool moonJump;
    bool godMode;
    bool infiniteLives;
    bool superSpeed;
    bool responsiveControls;
    bool rapidFireA;
    bool alwaysTripleJump;
    bool bljAnywhere;
};

extern struct Cheats gCheats;

#endif // _CHEATS_H
