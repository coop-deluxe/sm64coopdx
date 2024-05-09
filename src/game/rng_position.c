#include "rng_position.h"
#include "engine/math_util.h"

#define RNG_POSITION_MAX 16
#define RNG_POSITION_MATCH_DIST 300
#define RNG_POSITION_LIFE 30

struct RngPosition sRngPosition[RNG_POSITION_MAX] = { 0 };
struct RngPosition* gOverrideRngPosition = NULL;

void rng_position_init(f32 x, f32 y, f32 z) {
    Vec3f position = { x, y, z };
    // try to find and update past rng position
    for (u8 i = 0; i < RNG_POSITION_MAX; i++) {
        if (sRngPosition[i].life == 0) { continue; }
        Vec3f difference = { 0 };
        vec3f_dif(difference, position, sRngPosition[i].position);
        f32 length = vec3f_length(difference);
        if (length >= RNG_POSITION_MATCH_DIST) { continue; }
        sRngPosition[i].life = RNG_POSITION_LIFE;
        gOverrideRngPosition = &sRngPosition[i];
        return;
    }

    // try to store new rng position
    for (u8 i = 0; i < RNG_POSITION_MAX; i++) {
        if (sRngPosition[i].life != 0) { continue; }
        sRngPosition[i].life = RNG_POSITION_LIFE;
        sRngPosition[i].seed = (u16)((position[0] / 3) + (position[1] / 3));
        vec3f_copy(sRngPosition[i].position, position);
        gOverrideRngPosition = &sRngPosition[i];
        return;
    }
}

void rng_position_finish(void) {
    gOverrideRngPosition = NULL;
}

void rng_position_update(void) {
    // decrease life of all rng positions
    for (u8 i = 0; i < RNG_POSITION_MAX; i++) {
        if (sRngPosition[i].life == 0) { continue; }
        sRngPosition[i].life--;
        if (sRngPosition[i].life > 0) { continue; }
        if (&sRngPosition[i] == gOverrideRngPosition) {
            gOverrideRngPosition = NULL;
        }
    }
}