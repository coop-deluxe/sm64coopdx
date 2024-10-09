#ifndef RNG_POSITION_H
#define RNG_POSITION_H

#include "types.h"

struct RngPosition {
    Vec3f position;
    u16 seed;
    u8 life;
};

extern struct RngPosition* gOverrideRngPosition;

void rng_position_init(f32 x, f32 y, f32 z);
void rng_position_finish(void);
void rng_position_update(void);

#endif