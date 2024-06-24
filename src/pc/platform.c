#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    #include <shlobj.h>
    #include <shlwapi.h>
#endif

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

#if defined(_WIN32) || defined(_WIN64)

static BOOL sys_windows_short_path(LPSTR destPath, SIZE_T destSize, LPWSTR wideLongPath)
{
    WCHAR wideShortPath[SYS_MAX_PATH];

    // Convert the Long Path in Wide Format to the alternate short form.
    // It will still point to already existing directory.
    if (0 == GetShortPathNameW(wideLongPath, wideShortPath, SYS_MAX_PATH)) { return FALSE; }

    // Short Path can be safely represented by the US-ASCII Charset.
    return (WideCharToMultiByte(CP_ACP, 0, wideShortPath, (-1), destPath, destSize, NULL, NULL) > 0);
}

const char *sys_user_path(void)
{
    static char shortPath[SYS_MAX_PATH] = { 0 };
    if ('\0' != shortPath[0]) { return shortPath; }

    WCHAR widePath[SYS_MAX_PATH];

    // "%USERPROFILE%\AppData\Roaming"
    WCHAR *wcsAppDataPath = NULL;
    HRESULT res = SHGetKnownFolderPath(
        &(FOLDERID_RoamingAppData),
        (KF_FLAG_CREATE  | KF_FLAG_DONT_UNEXPAND),
        NULL, &(wcsAppDataPath));

    if (S_OK != res)
    {
        if (NULL != wcsAppDataPath) { CoTaskMemFree(wcsAppDataPath); }
        return NULL;
    }

    LPCWSTR subdirs[] = { L"sm64coopdx", L"sm64ex-coop", NULL };

    for (int i = 0; NULL != subdirs[i]; i++)
    {
        if (_snwprintf(widePath, SYS_MAX_PATH, L"%s\\%s", wcsAppDataPath, subdirs[i]) <= 0) { return NULL; }

        // Directory already exists.
        if (FALSE != PathIsDirectoryW(widePath))
        {
            // Directory is not empty, so choose this name.
            if (FALSE == PathIsDirectoryEmptyW(widePath)) { break; }
        }

        // 'widePath' will hold the last checked subdir name.
    }

    // System resource can be safely released now.
    if (NULL != wcsAppDataPath) { CoTaskMemFree(wcsAppDataPath); }

    // Always try to create the directory pointed to by User Path,
    // but ignore errors if the destination already exists.
    if (FALSE == CreateDirectoryW(widePath, NULL))
    {
        if (ERROR_ALREADY_EXISTS != GetLastError()) { return NULL; }
    }

    return sys_windows_short_path(shortPath, SYS_MAX_PATH, widePath) ? shortPath : NULL;
}

const char *sys_exe_path(void)
{
    static char shortPath[SYS_MAX_PATH] = { 0 };
    if ('\0' != shortPath[0]) { return shortPath; }

    WCHAR widePath[SYS_MAX_PATH];
    if (0 == GetModuleFileNameW(NULL, widePath, SYS_MAX_PATH)) { return NULL; }

    WCHAR *lastBackslash = wcsrchr(widePath, L'\\');
    if (NULL != lastBackslash) { *lastBackslash = L'\0'; }
    else { return NULL; }

    return sys_windows_short_path(shortPath, SYS_MAX_PATH, widePath) ? shortPath : NULL;
}

static void sys_fatal_impl(const char *msg) {
    MessageBoxA(NULL, msg, "Fatal error", MB_ICONERROR);
    fprintf(stderr, "FATAL ERROR:\n%s\n", msg);
    fflush(stderr);
    exit(1);
}

#elif defined(HAVE_SDL2)

// we can just ask SDL for most of this shit if we have it
#include <SDL2/SDL.h>

const char *sys_user_path(void) {
    static char path[SYS_MAX_PATH] = { 0 };
    if ('\0' != path[0]) { return path; }

    char const *subdirs[] = { "sm64coopdx", "sm64ex-coop", NULL };

    char *sdlPath = NULL;
    for (int i = 0; NULL != subdirs[i]; i++)
    {
        if (sdlPath) {
            // Previous dir likely just created with SDL_GetPrefPath.
            fs_sys_rmdir(sdlPath);
            SDL_free(sdlPath);
        }

        sdlPath = SDL_GetPrefPath("", subdirs[i]);

        // Choose this directory if it already exists and is not empty.
        if (sdlPath && !fs_sys_dir_is_empty(sdlPath)) { break; }
    }

    if (NULL == sdlPath) { return NULL; }

    strncpy(path, sdlPath, SYS_MAX_PATH - 1);
    SDL_free(sdlPath);

    // strip the trailing separator
    const unsigned int len = strlen(path);
    if (path[len-1] == '/' || path[len-1] == '\\') { path[len-1] = 0; }

    return path;
}

const char *sys_exe_path(void) {
    static char path[SYS_MAX_PATH] = { 0 };
    if ('\0' != path[0]) { return path; }

    char *sdlPath = SDL_GetBasePath();
    if (sdlPath && sdlPath[0]) {
        // use the SDL path if it exists
        const unsigned int len = strlen(sdlPath);
        snprintf(path, sizeof(path), "%s", sdlPath);
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
