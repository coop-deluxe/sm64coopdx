#include <PR/ultratypes.h>
#include <stdbool.h>
#include <time.h>

#include "misc.h"

#include "course_table.h"
#include "game/area.h"
#include "game/level_update.h"
#include "game/save_file.h"

float smoothstep(float edge0, float edge1, float x) {
    float t = (x - edge0) / (edge1 - edge0);
    if (t < 0) { t = 0; }
    if (t > 1) { t = 1; }
    return t * t * (3.0 - 2.0 * t);
}

void update_all_mario_stars(void) {
    s32 numStars = save_file_get_total_star_count(gCurrSaveFileNum - 1, COURSE_MIN - 1, COURSE_MAX - 1);
    for (int i = 0; i < MAX_PLAYERS; i++) {
        gMarioStates[i].numStars = numStars;
    }
}

f32 clock_elapsed(void) {
    static bool sClockInitialized = false;
    static struct timespec clock_start;
    if (!sClockInitialized) {
        clock_gettime(CLOCK_MONOTONIC, &clock_start);
        sClockInitialized = true;
    }

    struct timespec clock_current;
    clock_gettime(CLOCK_MONOTONIC, &clock_current);
    return (clock_current.tv_sec - clock_start.tv_sec)
        + ((clock_current.tv_nsec - clock_start.tv_nsec) / 1000000000.0f);
}