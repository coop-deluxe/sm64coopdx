#ifndef _CHEATS_H
#define _CHEATS_H

#include <stdbool.h>

struct CheatList {
    bool enabled;
    bool moonJump;
    bool godMode;
    bool infiniteLives;
    bool superSpeed;
    bool responsive;
};

extern struct CheatList Cheats;

#endif // _CHEATS_H
