#include <stdio.h>
#include <stdlib.h>
#include <PR/ultratypes.h>
#include <stdbool.h>
#include <time.h>
#include <float.h>

#include "misc.h"

#include "course_table.h"
#include "game/area.h"
#include "game/level_update.h"
#include "game/save_file.h"
#include "engine/math_util.h"
#include "pc/configfile.h"

float smooth_step(float edge0, float edge1, float x) {
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
    /*
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
    */
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

bool clock_is_date(u8 month, u8 day) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    return tm_info->tm_mon == month - 1 && tm_info->tm_mday == day;
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

f32 delta_interpolate_f32(f32 a, f32 b, f32 delta) {
    return a * (1.0f - delta) + b * delta;
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

static f32 get_quat_compo_abs(f32 xPiece, f32 yPiece, f32 zPiece) {
    return sqrt((1.0f + xPiece + yPiece + zPiece) * 0.25f);
}

static u8 float_ge_with_nan_check(f32 a, f32 b) {
    return !isnan(a) && (isnan(b) || a >= b);
}

// this function expects an orthonormal rotation matrix
static void rot_mat_to_rot_quat(Vec4f q, Vec3f a[3]) {
    // get absolute value of coefficients
    q[0] = get_quat_compo_abs(a[0][0], a[1][1], a[2][2]);
    q[1] = get_quat_compo_abs(a[0][0], -a[1][1], -a[2][2]);
    q[2] = get_quat_compo_abs(-a[0][0], a[1][1], -a[2][2]);
    q[3] = get_quat_compo_abs(-a[0][0], -a[1][1], a[2][2]);

    // find the coefficient with greatest magnitude
    // NaN checks are because of possible square root of negative number in get_quat_compo_abs
    int maxCompoMagCase = float_ge_with_nan_check(q[0], q[1])
        ? float_ge_with_nan_check(q[0], q[2])
            ? float_ge_with_nan_check(q[0], q[3])
                ? 0
                : 3
            : float_ge_with_nan_check(q[2], q[3])
                ? 2
                : 3
        : float_ge_with_nan_check(q[1], q[2])
            ? float_ge_with_nan_check(q[1], q[3])
                ? 1
                : 3
            : float_ge_with_nan_check(q[2], q[3])
                ? 2
                : 3;

    // adjust signs of coefficients; base on greatest magnitude to improve float accuracy
    f32 divFactor = 0;
    switch (maxCompoMagCase) {
        case 0:
            divFactor = 0.25f / q[0];
            q[1] = (a[1][2] - a[2][1]) * divFactor;
            q[2] = (a[2][0] - a[0][2]) * divFactor;
            q[3] = (a[0][1] - a[1][0]) * divFactor;
            return;

        case 1:
            divFactor = 0.25f / q[1];
            q[0] = (a[1][2] - a[2][1]) * divFactor;
            q[2] = (a[1][0] + a[0][1]) * divFactor;
            q[3] = (a[2][0] + a[0][2]) * divFactor;
            return;

        case 2:
            divFactor = 0.25f / q[2];
            q[0] = (a[2][0] - a[0][2]) * divFactor;
            q[1] = (a[1][0] + a[0][1]) * divFactor;
            q[3] = (a[2][1] + a[1][2]) * divFactor;
            return;

        case 3:
            divFactor = 0.25f / q[3];
            q[0] = (a[0][1] - a[1][0]) * divFactor;
            q[1] = (a[2][0] + a[0][2]) * divFactor;
            q[2] = (a[2][1] + a[1][2]) * divFactor;
            return;
    }
}

static void rot_quat_to_mtx_rot(Vec3f a[3], Vec4f q) {
    f32 dq0s = 2.0f * sqr(q[0]), dq1s = 2.0f * sqr(q[1]), dq2s = 2.0f * sqr(q[2]),
        dq3s = 2.0f * sqr(q[3]), dq12 = 2.0f * q[1] * q[2], dq03 = 2.0f * q[0] * q[3],
        dq13 = 2.0f * q[1] * q[3], dq02 = 2.0f * q[0] * q[2], dq23 = 2.0f * q[2] * q[3],
        dq01 = 2.0f * q[0] * q[1];

    a[0][0] = dq0s + dq1s - 1.0f;
    a[0][1] = dq12 + dq03;
    a[0][2] = dq13 - dq02;
    a[1][0] = dq12 - dq03;
    a[1][1] = dq0s + dq2s - 1.0f;
    a[1][2] = dq23 + dq01;
    a[2][0] = dq13 + dq02;
    a[2][1] = dq23 - dq01;
    a[2][2] = dq0s + dq3s - 1.0f;
}

// rotation quaternion spherical linear interpolation
static void rot_quat_slerp(Vec4f out, Vec4f a, Vec4f b, f32 t) {
    // credit where it's due:
    // Martin John Baker
    // https://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/slerp/index.htm

    f32 halfTh = 0;
    f32 halfSin = 0;
    f32 st = 0;
    f32 sat = 0;
    f32 halfCos = a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];

    memcpy(out, b, sizeof(f32) * 4);

    // if the abs of cos is 1, then there is no rotation
    if (fabs(halfCos) >= 1.0f) {
        return;
    }

    // if cos is negative, rotation takes long path; invert to take short path
    if (halfCos < 0.0f) {
        out[0] *= -1.0f;
        out[1] *= -1.0f;
        out[2] *= -1.0f;
        out[3] *= -1.0f;
        halfCos *= -1.0f;
    }

    halfTh = acos(halfCos);
    halfSin = sqrt(1.0f - sqr(halfCos));

    if (halfSin == 0.0f) {
        // this shouldn't happen, but float imprecision can make it happen anyway
        halfSin = FLT_EPSILON;
    }

    sat = sin((1 - t) * halfTh) / halfSin;
    st = sin(t * halfTh) / halfSin;
    out[0] = a[0] * sat + out[0] * st;
    out[1] = a[1] * sat + out[1] * st;
    out[2] = a[2] * sat + out[2] * st;
    out[3] = a[3] * sat + out[3] * st;
}

// removes scaling from the shear value
inline static f32 unmat_unscale_shear(f32 shear, f32 scale) {
    if (scale == 0.0f) {
        // assume no shear
        return 0.0f;
    }

    return shear / scale;
}

// matrix decomposition code is brought over from "unmatrix.c" from Graphics Gems II
// Author: Spencer W. Thomas of University of Michigan
// additional Graphics Gems II code by Andrew Glassner and Rod G. Bogart
// thanks to fgsfds for informing me of this
// http://www.realtimerendering.com/resources/GraphicsGems/gemsii/unmatrix.c
//
// matrix perspective is not used in SM64, so those indices are stripped from the output parameter
// return value was related to if matrix was non-singular, which was necessary for perspective
// since perspective is not used, the return value is also stripped
//
// additionally, rotation is not converted to euler angles
// instead, it is converted to a quaternion to avoid gimbal lock
//
// tranfs is returned as follows:
// scale(x, y, z), shear(xy, xz, zy), rotation(a, b, c, d), translation(x, y, z)
OPTIMIZE_O3 static void unmatrix(Mtx * mat, f32 tranfs[13]) {
    int i = 0;
    Vec3f axisVecs[3] = { 0 };
    Vec3f yzCross = { 0 };

    Mtx locMat = *mat;

    // matrix normalization skipped since all SM64 matrices are normalized

    // perspective is not used in SM64 matrices, so the steps for it are skipped

    for (i = 0; i < 3; ++i) {
        // translation (position)
        tranfs[10 + i] = locMat.m[3][i];

        // axis vector
        memcpy(axisVecs[i], locMat.m[i], sizeof(f32) * 3);
    }

    // X-scale
    tranfs[0] = vec3f_length(axisVecs[0]);

    // normalize X-axis vector
    if (tranfs[0] == 0.0f) {
        axisVecs[0][0] = 1.0f;
        axisVecs[0][1] = 0.0f;
        axisVecs[0][2] = 0.0f;
    } else {
        for (i = 0; i < 3; ++i) {
            axisVecs[0][i] /= tranfs[0];
        }
    }

    // XY-shear
    tranfs[3] = vec3f_dot(axisVecs[0], axisVecs[1]);

    // orthogonalize Y-axis vector to X-axis vector
    vec3f_combine(axisVecs[1], axisVecs[1], axisVecs[0], 1.0f, -tranfs[3]);

    // Y-scale
    tranfs[1] = vec3f_length(axisVecs[1]);

    // normalize Y-axis vector
    if (tranfs[1] == 0.0f) {
        axisVecs[1][0] = 0.0f;
        axisVecs[1][1] = 1.0f;
        axisVecs[1][2] = 0.0f;
    } else {
        for (i = 0; i < 3; ++i) {
            axisVecs[1][i] /= tranfs[1];
        }
    }

    // unscale XY-shear
    tranfs[3] = unmat_unscale_shear(tranfs[3], tranfs[1]);

    // XZ-shear
    tranfs[4] = vec3f_dot(axisVecs[0], axisVecs[2]);

    // orthogonalize Z-axis vector to X-axis vector
    vec3f_combine(axisVecs[2], axisVecs[2], axisVecs[0], 1.0f, -tranfs[4]);

    // ZY-shear
    tranfs[5] = vec3f_dot(axisVecs[1], axisVecs[2]);

    // orthogonalize Z-axis vector to Y-axis vector
    vec3f_combine(axisVecs[2], axisVecs[2], axisVecs[1], 1.0f, -tranfs[5]);

    // Z-scale
    tranfs[2] = vec3f_length(axisVecs[2]);

    // normalize Z-axis vector
    if (tranfs[2] == 0.0f) {
        axisVecs[2][0] = 0.0f;
        axisVecs[2][1] = 0.0f;
        axisVecs[2][2] = 1.0f;
    } else {
        for (i = 0; i < 3; ++i) {
            axisVecs[2][i] /= tranfs[2];
        }
    }

    // unscale remaining shears
    tranfs[4] = unmat_unscale_shear(tranfs[4], tranfs[2]);
    tranfs[5] = unmat_unscale_shear(tranfs[5], tranfs[2]);

    // check if coordinate system needs to be flipped
    vec3f_cross(yzCross, axisVecs[1], axisVecs[2]);
    if (vec3f_dot(axisVecs[0], yzCross) < 0.0f) {
        for (i = 0; i < 3; ++i) {
            tranfs[i] *= -1.0f;
            vec3f_mul(axisVecs[i], -1.0f);
        }
    }

    // rotation
    rot_mat_to_rot_quat(tranfs + 6, axisVecs);
}

// builds a transformation matrix from a decomposed sequence from unmatrix
// see unmatrix for what tranfs means
static void rematrix(Mtx * mat, f32 tranfs[13]) {
    int i;
    Vec3f rotAxes[3] = { 0 };
    Mat4 rotMat = { 0 };

    // start with the identity matrix
    for (i = 0; i < 4; ++i) {
        int j;

        mat->m[i][i] = 1.0f;
        for (j = 3; j > i; --j) {
            mat->m[i][j] = mat->m[j][i] = 0.0f;
        }
    }

    // scale
    for (i = 0; i < 3; ++i) {
        vec3f_mul(mat->m[i], tranfs[i]);
    }

    // shear
    mat->m[1][0] = mat->m[1][1] * tranfs[3];
    mat->m[2][0] = mat->m[2][2] * tranfs[4];
    mat->m[2][1] = mat->m[2][2] * tranfs[5];

    // rotate
    // get the rotation matrix for the quat
    rot_quat_to_mtx_rot(rotAxes, tranfs + 6);

    // transfer to the Mat4 struct
    for (i = 0; i < 3; ++i) {
        memcpy(rotMat[i], rotAxes[i], sizeof(f32) * 3);
        rotMat[i][3] = rotMat[3][i] = 0.0f;
    }
    rotMat[3][3] = 1.0f;

    // apply the rotation
    // this is technically abuse of Mat4 vs. Mtx, but coop doesn't target N64 anyway
    mtxf_mul(mat->m, mat->m, rotMat);

    // translate
    for (i = 0; i < 3; ++i) {
        mat->m[3][i] = tranfs[10 + i];
    }
}

inline static void delta_interpolate_mtx_accurate(Mtx* out, Mtx* a, Mtx* b, f32 delta) {
    int i = 0;
    f32 matTranfsA[13] = { 0 };
    f32 matTranfsB[13] = { 0 };

    f32 antiDelta = 1.0f - delta;

    unmatrix(a, matTranfsA);
    unmatrix(b, matTranfsB);

    // skip rot quat
    for (i = 0; i < 6; ++i) {
        matTranfsB[i] = matTranfsA[i] * antiDelta + matTranfsB[i] * delta;
    }
    for (i = 10; i < 13; ++i) {
        matTranfsB[i] = matTranfsA[i] * antiDelta + matTranfsB[i] * delta;
    }

    rot_quat_slerp(matTranfsB + 6, matTranfsA + 6, matTranfsB + 6, delta);

    rematrix(out, matTranfsB);
}

void delta_interpolate_mtx(Mtx* out, Mtx* a, Mtx* b, f32 delta) {
    // HACK: Limit accurate interpolation to 64-bit builds
    if (sizeof(void*) > 4) {
        if (configInterpolationMode) {
            delta_interpolate_mtx_accurate(out, a, b, delta);
            return;
        }
    }

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
    const f32 minDot = sqrt(2.0f) / -3.0f;
    Vec3f prevX; vec3f_copy(prevX, (f32*)(*mtxPrev)->m[0]); vec3f_normalize(prevX);
    Vec3f prevY; vec3f_copy(prevY, (f32*)(*mtxPrev)->m[1]); vec3f_normalize(prevY);
    Vec3f prevZ; vec3f_copy(prevZ, (f32*)(*mtxPrev)->m[2]); vec3f_normalize(prevZ);

    Vec3f nextX; vec3f_copy(nextX, (f32*)(*mtx)->m[0]); vec3f_normalize(nextX);
    Vec3f nextY; vec3f_copy(nextY, (f32*)(*mtx)->m[1]); vec3f_normalize(nextY);
    Vec3f nextZ; vec3f_copy(nextZ, (f32*)(*mtx)->m[2]); vec3f_normalize(nextZ);

    f32 dotX = vec3f_dot(prevX, nextX);
    f32 dotY = vec3f_dot(prevY, nextY);
    f32 dotZ = vec3f_dot(prevZ, nextZ);

    if ((dotX < minDot) || (dotY < minDot) || (dotZ < minDot)) {
        *mtx = *mtxPrev;
    }
}

void str_seperator_concat(char *output_buffer, int buffer_size, char** strings, int num_strings, char* seperator) {
    // empty buffer
    memset(output_buffer, 0, buffer_size);
    if (num_strings <= 0) { return; }

    // Calculate the total length of all strings
    int string_length[num_strings];
    int total_length = 0;
    for (int i = 0; i < num_strings; i++) {
        string_length[i] = strlen(strings[i]);
        total_length += string_length[i];
    }

    // get the seperator length
    int seperator_length = strlen(seperator);
    int seperators_length = (num_strings - 1) * seperator_length;
    if (seperators_length + 8 < buffer_size) {
        // Shorten the largest string over and over until we fit
        while (total_length + seperators_length >= buffer_size) {
            int* largest = NULL;
            for (int i = 0; i < num_strings; i++) {
                if (largest == NULL || string_length[i] >= *largest) {
                    largest = &string_length[i];
                }
            }
            if (largest == NULL || *largest == 0) { break; }
            *largest = *largest - 1;
            total_length--;
        }
    }

    // Fill the buffer
    int buffer_index = 0;
    for (int i = 0; i < num_strings; i++) {
        // Concat string
        int amount = MIN(buffer_size - buffer_index, string_length[i] + 1);
        if (amount <= 0) { break; }
        snprintf(&output_buffer[buffer_index], amount, "%s", strings[i]);
        buffer_index += string_length[i];

        // Concat seperator
        if (i != (num_strings - 1)) {
            int amount = MIN(buffer_size - buffer_index, seperator_length + 1);
            if (amount <= 0) { break; }
            snprintf(&output_buffer[buffer_index], amount, "%s", seperator);
            buffer_index += seperator_length;
        }
    }
}

char *str_remove_color_codes(const char *str) {
    char *output = strdup(str);
    char *startColor;
    while ((startColor = strstr(output, "\\#"))) {
        char *endColor = strchr(startColor + 2, '\\');
        if (endColor) {
            memmove(startColor, endColor + 1, strlen(endColor + 1) + 1);
        } else {
            *startColor = 0;
            break;
        }
    }
    return output;
}
