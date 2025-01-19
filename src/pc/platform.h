#ifndef _SM64_PLATFORM_H_
#define _SM64_PLATFORM_H_

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/* platform-specific functions and whatnot */

#define SYS_MAX_PATH 4096

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

#endif // _SM64_PLATFORM_H_
