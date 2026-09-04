#pragma once

#include <stdbool.h>
#include "types.h"

/* platform-specific functions and whatnot */

#ifdef _WIN32
#define PATH_SEPARATOR      "\\"
#define PATH_SEPARATOR_ALT  "/"
#else
#define PATH_SEPARATOR      "/"
#define PATH_SEPARATOR_ALT  "\\"
#endif

#define SYS_MAX_PATH 4096

// casting a float to a s16 is actually undefined behavior! What happens on Arm vs
// Intel differs. Arm has different behavior from Intel, which it and the N64 wraps X around.
// We can replicate the n64s behavior by modulating the float to within bounds and then
// casting from there. Don't alter intel's behavior since the fmodf is slower
static inline s16 n64_float_to_s16(f32 x) {
#ifdef __arm64__
    // modulate to be inside the range of a u16
    f32 wrapped = fmodf(x, 65536.0f);
    // cast into a s32 and then to an s16. s32 can hold this number in any sign, and from
    // there, casting to a s16 is defined to wrap, which is what we are looking for
    return (s16)(s32)wrapped;
#else
    return (s16)x;
#endif
}
#define N64_FLOAT_TO_S16(x) n64_float_to_s16(x)

// crossplatform impls of misc stuff
char *sys_strdup(const char *src);
char *sys_strlwr(char *src);
int sys_strcasecmp(const char *s1, const char *s2);

// path stuff
#ifdef _WIN32
bool sys_windows_short_path_from_wcs(char *destPath, size_t destSize, const wchar_t *wcsLongPath);
bool sys_windows_short_path_from_mbs(char* destPath, size_t destSize, const char *mbsLongPath);
#endif
const char *sys_user_path(void);
const char *sys_resource_path(void);
const char *sys_exe_path_dir(void);
const char *sys_exe_path_file(void);
const char *sys_file_extension(const char *fpath);
const char *sys_file_name(const char *fpath);
void sys_swap_backslashes(char* buffer);

// shows an error message in some way and terminates the game
void sys_fatal(const char *fmt, ...) __attribute__ ((noreturn));
