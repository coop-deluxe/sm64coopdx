#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

#include "cliopts.h"
#include "fs/fs.h"
#include "configfile.h"

/* these are not available on some platforms, so might as well */

char *sys_strlwr(char *src) {
  for (unsigned char *p = (unsigned char *)src; *p; p++)
     *p = tolower(*p);
  return src;
}

char *sys_strdup(const char *src) {
    const unsigned len = strlen(src) + 1;
    char *newstr = malloc(len);
    if (newstr) memcpy(newstr, src, len);
    return newstr;
}

int sys_strcasecmp(const char *s1, const char *s2) {
    const unsigned char *p1 = (const unsigned char *) s1;
    const unsigned char *p2 = (const unsigned char *) s2;
    int result;
    if (p1 == p2)
        return 0;
    while ((result = tolower(*p1) - tolower(*p2++)) == 0)
        if (*p1++ == '\0')
            break;
    return result;
}

const char *sys_file_extension(const char *fpath) {
    const char *fname = sys_file_name(fpath);
    const char *dot = strrchr(fname, '.');
    if (!dot || !dot[1]) return NULL; // no dot
    if (dot == fname) return NULL; // dot is the first char (e.g. .local)
    return dot + 1;
}

const char *sys_file_name(const char *fpath) {
    const char *sep1 = strrchr(fpath, '/');
    const char *sep2 = strrchr(fpath, '\\');
    const char *sep = sep1 > sep2 ? sep1 : sep2;
    if (!sep) return fpath;
    return sep + 1;
}

void sys_swap_backslashes(char* buffer) {
    size_t length = strlen(buffer);
    bool inColor = false;
    for (u32 i = 0; i < length; i++) {
        if (buffer[i] == '\\' && buffer[MIN(i + 1, length)] == '#') { inColor = true; }
        if (buffer[i] == '\\' && !inColor) { buffer[i] = '/'; }
        if (buffer[i] == '\\' && inColor && buffer[MIN( i + 1, length)] != '#') { inColor = false; }
    }
}

/* this calls a platform-specific impl function after forming the error message */

static void sys_fatal_impl(const char *msg) __attribute__ ((noreturn));

void sys_fatal(const char *fmt, ...) {
    static char msg[2048];
    va_list args;
    va_start(args, fmt);
    vsnprintf(msg, sizeof(msg), fmt, args);
    va_end(args);
    fflush(stdout); // push all crap out
    sys_fatal_impl(msg);
}

#ifdef HAVE_SDL2

// we can just ask SDL for most of this shit if we have it
#include <SDL2/SDL.h>

static const char *sys_old_user_path(void) {
    static char path[SYS_MAX_PATH] = { 0 };

    // get the new pref path from SDL
    char *sdlPath = SDL_GetPrefPath("", "sm64ex-coop");
    if (sdlPath) {
        const unsigned int len = strlen(sdlPath);
        strncpy(path, sdlPath, sizeof(path));
        path[sizeof(path)-1] = 0;

        SDL_free(sdlPath);

        // strip the trailing separator
        if (path[len-1] == '/' || path[len-1] == '\\') { path[len-1] = 0; }
    }

    return path;
}

const char *sys_user_path(void) {
    static char path[SYS_MAX_PATH] = { 0 };

    // get the new pref path from SDL
    char *sdlPath = SDL_GetPrefPath("", "sm64coopdx");
    if (sdlPath) {
        // redirect to the old user path if the current one is empty (likely just created from SDL_GetPrefPath)
        if (fs_sys_dir_is_empty(sdlPath)) {
            SDL_free(sdlPath);
            return sys_old_user_path();
        }

        const unsigned int len = strlen(sdlPath);
        strncpy(path, sdlPath, sizeof(path));
        path[sizeof(path)-1] = 0;

        SDL_free(sdlPath);

        // strip the trailing separator
        if (path[len-1] == '/' || path[len-1] == '\\') { path[len-1] = 0; }
    }

    return path;
}

const char *sys_exe_path(void) {
    static char path[SYS_MAX_PATH] = { 0 };
    char *sdlPath = SDL_GetBasePath();
    if (sdlPath && sdlPath[0]) {
        // use the SDL path if it exists
        const unsigned int len = strlen(sdlPath);
        strncpy(path, sdlPath, sizeof(path));
        path[sizeof(path)-1] = 0;
        SDL_free(sdlPath);
        if (path[len-1] == '/' || path[len-1] == '\\')
            path[len-1] = 0; // strip the trailing separator
    }
    return path;
}

static void sys_fatal_impl(const char *msg) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR , "Fatal error", msg, NULL);
    fprintf(stderr, "FATAL ERROR:\n%s\n", msg);
    fflush(stderr);
    exit(1);
}

#else

#ifndef WAPI_DUMMY
#warning "You might want to implement these functions for your platform"
#endif

const char *sys_user_path(void) {
    return ".";
}

const char *sys_exe_path(void) {
    return ".";
}

static void sys_fatal_impl(const char *msg) {
    fprintf(stderr, "FATAL ERROR:\n%s\n", msg);
    fflush(stderr);
    exit(1);
}

#endif // platform switch
