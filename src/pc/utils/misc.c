#include <stdio.h>
#include <stdlib.h>
#include <PR/ultratypes.h>
#include <stdbool.h>
#include <time.h>

#include "misc.h"

#include "course_table.h"
#include "game/area.h"
#include "game/level_update.h"
#include "game/save_file.h"
#include "engine/math_util.h"

float smoothstep(float edge0, float edge1, float x) {
    float t = (x - edge0) / (edge1 - edge0);
    if (t < 0) { t = 0; }
    if (t > 1) { t = 1; }
    return t * t * (3.0 - 2.0 * t);
}

void update_all_mario_stars(void) {
    s32 numStars = save_file_get_total_star_count(gCurrSaveFileNum - 1, COURSE_MIN - 1, COURSE_MAX - 1);
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        gMarioStates[i].numStars = numStars;
    }
}

static void _clock_gettime(struct timespec* clock_time) {
#if !defined _POSIX_MONOTONIC_CLOCK || _POSIX_MONOTONIC_CLOCK < 0
    clock_gettime(CLOCK_REALTIME, clock_time);
#elif _POSIX_MONOTONIC_CLOCK > 0
    clock_gettime(CLOCK_MONOTONIC, clock_time);
#else
    if (clock_gettime(CLOCK_MONOTONIC, clock_time))
        clock_gettime(CLOCK_REALTIME, clock_time));
#endif

#ifdef DEVELOPMENT
    // give each instance a random offset for testing purposed
    static s32 randomOffset1 = 0;
    static s32 randomOffset2 = 0;
    if (randomOffset1 == 0) {
        time_t t;
        srand((unsigned)time(&t));
        randomOffset1 = rand();
        randomOffset2 = rand();
    }
    clock_time->tv_sec += randomOffset1;
    clock_time->tv_nsec += randomOffset2;
#endif
}

static u64 clock_elapsed_ns(void) {
    static bool sClockInitialized = false;
    static u64 clock_start_ns;
    if (!sClockInitialized) {
        struct timespec clock_start;
        _clock_gettime(&clock_start);
        clock_start_ns = ((u64)clock_start.tv_sec) * 1000000000 + ((u64)clock_start.tv_nsec);
        sClockInitialized = true;
    }

    struct timespec clock_current;
    _clock_gettime(&clock_current);

    u64 clock_current_ns = ((u64)clock_current.tv_sec) * 1000000000 + ((u64)clock_current.tv_nsec);
    return (clock_current_ns - clock_start_ns);
}

f32 clock_elapsed(void) {
    return (clock_elapsed_ns() / 1000000000.0f);
}

f64 clock_elapsed_f64(void) {
    return (clock_elapsed_ns() / 1000000000.0);
}

u32 clock_elapsed_ticks(void) {
    return (clock_elapsed_ns() * 3 / 100000000);
}

void file_get_line(char* buffer, size_t maxLength, FILE* fp) {
    char* initial = buffer;

    char c = fgetc(fp);
    while (!feof(fp) && c != '\n') {
        // make sure it's printable
        if (c < ' ' || c > '~') { goto next_get; }

        // parse new line escape code
        if (c == '\\') {
            c = fgetc(fp);
            if (feof(fp)) { break; }
            if (c == 'n') {
                if ((size_t)(buffer - initial) < (maxLength - 1)) {
                    *buffer++ = '\n';
                }
                goto next_get;
            }
        }

        // found new line
        if (c == '\n') { break; }

        // append to buffer
        if ((size_t)(buffer - initial) < (maxLength - 1)) {
            *buffer++ = c;
        }

next_get:
        c = fgetc(fp);
    }

    *buffer = '\0';
}

/////////////////

static f32 sm64_to_radians(f32 val) {
    return val * M_PI / 0x8000;
}

static f32 radians_to_sm64(f32 val) {
    return val * 0x8000 / M_PI;
}

static f32 asins(f32 val) {
    return radians_to_sm64(asin(sm64_to_radians(val)));
}

f32 delta_interpolate_f32(f32 start, f32 end, f32 delta) {
    return start * (1.0f - delta) + end * delta;
}

s32 delta_interpolate_s32(s32 a, s32 b, f32 delta) {
    return a * (1.0f - delta) + b * delta;
}

void delta_interpolate_vec3f(Vec3f res, Vec3f a, Vec3f b, f32 delta) {
    f32 antiDelta = 1.0f - delta;
    res[0] = ((a[0] * antiDelta) + (b[0] * delta));
    res[1] = ((a[1] * antiDelta) + (b[1] * delta));
    res[2] = ((a[2] * antiDelta) + (b[2] * delta));
}

void delta_interpolate_vec3s(Vec3s res, Vec3s a, Vec3s b, f32 delta) {
    f32 antiDelta = 1.0f - delta;
    res[0] = ((a[0] * antiDelta) + (b[0] * delta));
    res[1] = ((a[1] * antiDelta) + (b[1] * delta));
    res[2] = ((a[2] * antiDelta) + (b[2] * delta));
}

void delta_interpolate_normal(s8* res, s8* a, s8* b, f32 delta) {
    f32 antiDelta = 1.0f - delta;
    res[0] = ((a[0] * antiDelta) + (b[0] * delta));
    res[1] = ((a[1] * antiDelta) + (b[1] * delta));
    res[2] = ((a[2] * antiDelta) + (b[2] * delta));
}

void delta_interpolate_rgba(u8* res, u8* a, u8* b, f32 delta) {
    f32 antiDelta = 1.0f - delta;
    res[0] = ((a[0] * antiDelta) + (b[0] * delta));
    res[1] = ((a[1] * antiDelta) + (b[1] * delta));
    res[2] = ((a[2] * antiDelta) + (b[2] * delta));
    res[3] = ((a[3] * antiDelta) + (b[3] * delta));
}

static s16 delta_interpolate_angle(s16 a, s16 b, f32 delta) {
    s32 absDiff = b - a;
    if (absDiff < 0) {
        absDiff = -absDiff;
    }
    if (absDiff >= 0x4000 && absDiff <= 0xC000) {
        return b;
    }

    f32 antiDelta = 1.0f - delta;
    if (absDiff <= 0x8000) {
        return (a * antiDelta) + (b * delta);
    } else {
        return (a * antiDelta) + (b * delta) + 0x8000;
    }
}

static void delta_interpolate_angles(Vec3s res, Vec3s a, Vec3s b, f32 delta) {
    res[0] = delta_interpolate_angle(a[0], b[0], delta);
    res[1] = delta_interpolate_angle(a[1], b[1], delta);
    res[2] = delta_interpolate_angle(a[2], b[2], delta);
}

void delta_interpolate_mtx(Mtx* out, Mtx* a, Mtx* b, f32 delta) {
    // this isn't the right way to do things.
    f32 antiDelta = 1.0f - delta;
    for (s32 i = 0; i < 4; i++) {
        for (s32 j = 0; j < 4; j++) {
            out->m[i][j] = (a->m[i][j] * antiDelta) + (b->m[i][j] * delta);
        }
    }
}

void detect_and_skip_mtx_interpolation(Mtx** mtxPrev, Mtx** mtx) {
    // if the matrix has changed "too much", then skip interpolation
    const f32 minDot = sqrt(2.0f) / -2.0f;
    Vec3f prevX; vec3f_copy(prevX, (f32*)(*mtxPrev)->m[0]); vec3f_normalize(prevX);
    Vec3f prevY; vec3f_copy(prevY, (f32*)(*mtxPrev)->m[1]); vec3f_normalize(prevY);
    Vec3f prevZ; vec3f_copy(prevZ, (f32*)(*mtxPrev)->m[2]); vec3f_normalize(prevZ);

    Vec3f nextX; vec3f_copy(nextX, (f32*)(*mtx)->m[0]); vec3f_normalize(nextX);
    Vec3f nextY; vec3f_copy(nextY, (f32*)(*mtx)->m[1]); vec3f_normalize(nextY);
    Vec3f nextZ; vec3f_copy(nextZ, (f32*)(*mtx)->m[2]); vec3f_normalize(nextZ);

    f32 dotX = vec3f_dot(prevX, nextX);
    f32 dotY = vec3f_dot(prevY, nextY);
    f32 dotZ = vec3f_dot(prevZ, nextZ);

    if ((dotX < minDot) | (dotY < minDot) || (dotZ < minDot)) {
        *mtx = *mtxPrev;
    }
}
