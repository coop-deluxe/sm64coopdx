#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

#if defined(_WIN32)
#include <windows.h>
#include <shlobj.h>
#include <shlwapi.h>
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#else
#include <unistd.h>
#endif

#include "cliopts.h"
#include "fs/fs.h"
#include "debuglog.h"
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

#ifdef _WIN32

static bool sys_windows_pathname_is_portable(const wchar_t *name, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        wchar_t c = name[i];

        // character outside the ASCII printable range
        if ((c < L' ') || (c > L'~')) { return false; }

        // characters unallowed in filenames
        switch (c) {
            // skipping ':', as it will appear with the drive specifier
            case L'<': case L'>': case L'/': case L'\\':
            case L'"': case L'|': case L'?': case L'*':
                return false;
        }
    }
    return true;
}

static wchar_t *sys_windows_pathname_get_delim(const wchar_t *name)
{
    const wchar_t *sep1 = wcschr(name, L'/');
    const wchar_t *sep2 = wcschr(name, L'\\');

    if (NULL == sep1) { return (wchar_t*)sep2; }
    if (NULL == sep2) { return (wchar_t*)sep1; }

    return (sep1 < sep2) ? (wchar_t*)sep1 : (wchar_t*)sep2;
}

bool sys_windows_short_path_from_wcs(char *destPath, size_t destSize, const wchar_t *wcsLongPath)
{
    wchar_t wcsShortPath[SYS_MAX_PATH]; // converted with WinAPI
    wchar_t wcsPortablePath[SYS_MAX_PATH]; // non-unicode parts replaced back with long forms

    // Convert the Long Path in Wide Format to the alternate short form.
    // It will still point to already existing directory or file.
    if (0 == GetShortPathNameW(wcsLongPath, wcsShortPath, SYS_MAX_PATH)) { return FALSE; }

    // Scanning the paths side-by-side, to keep the portable (ASCII)
    // parts of the absolute path unchanged (in the long form)
    wcsPortablePath[0] = L'\0';
    const wchar_t *longPart = wcsLongPath;
    wchar_t *shortPart = wcsShortPath;

    while (true) {
        int longLength;
        int shortLength;
        const wchar_t *sourcePart;
        int sourceLength;
        int bufferLength;

        const wchar_t *longDelim = sys_windows_pathname_get_delim(longPart);
        wchar_t *shortDelim = sys_windows_pathname_get_delim(shortPart);

        if (NULL == longDelim) {
            longLength = wcslen(longPart); // final part of the scanned path
        } else {
            longLength = longDelim - longPart; // ptr diff measured in WCHARs
        }

        if (NULL == shortDelim) {
            shortLength = wcslen(shortPart); // final part of the scanned path
        } else {
            shortLength = shortDelim - shortPart; // ptr diff measured in WCHARs
        }

        if (sys_windows_pathname_is_portable(longPart, longLength)) {
            // take the original name (subdir or filename)
            sourcePart = longPart;
            sourceLength = longLength;
        } else {
            // take the converted alternate (short) name
            sourcePart = shortPart;
            sourceLength = shortLength;
        }

        // take into account the slash-or-backslash separator
        if (L'\0' != sourcePart[sourceLength]) { sourceLength++; }

        // how many WCHARs are still left in the buffer
        bufferLength = (SYS_MAX_PATH - 1) - wcslen(wcsPortablePath);
        if (sourceLength > bufferLength) { return false; }

        wcsncat(wcsPortablePath, sourcePart, sourceLength);

        // path end reached?
        if ((NULL == longDelim) || (NULL == shortDelim)) { break; }

        // compare the next name
        longPart = longDelim + 1;
        shortPart = shortDelim + 1;
    }

    // Short Path can be safely represented by the US-ASCII Charset.
    return (WideCharToMultiByte(CP_ACP, 0, wcsPortablePath, (-1), destPath, destSize, NULL, NULL) > 0);
}

bool sys_windows_short_path_from_mbs(char *destPath, size_t destSize, const char *mbsLongPath)
{
    // Converting the absolute path in UTF-8 format (MultiByte String)
    // to an alternate (portable) format usable on Windows.
    // Assuming the given paths points to an already existing file or folder.

    wchar_t wcsWidePath[SYS_MAX_PATH];

    if (MultiByteToWideChar(CP_UTF8, 0, mbsLongPath, (-1), wcsWidePath, SYS_MAX_PATH) > 0)
    {
        return sys_windows_short_path_from_wcs(destPath, destSize, wcsWidePath);
    }

    return false;
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

    LPCWSTR subdirs[] = { L"sm64coopdx", L"sm64ex-coop", L"sm64coopdx", NULL };

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

    return sys_windows_short_path_from_wcs(shortPath, SYS_MAX_PATH, widePath) ? shortPath : NULL;
}

const char *sys_resource_path(void) {
    return sys_exe_path_dir();
}

const char *sys_exe_path_dir(void)
{
    static char path[SYS_MAX_PATH];
    if ('\0' != path[0]) { return path; }

    const char *exeFilepath = sys_exe_path_file();
    char *lastSeparator = strrchr(exeFilepath, '\\');
    if (lastSeparator != NULL) {
        size_t count = (size_t)(lastSeparator - exeFilepath);
        strncpy(path, exeFilepath, count);
    }

    return path;
}

const char *sys_exe_path_file(void)
{
    static char shortPath[SYS_MAX_PATH] = { 0 };
    if ('\0' != shortPath[0]) { return shortPath; }

    WCHAR widePath[SYS_MAX_PATH];
    if (0 == GetModuleFileNameW(NULL, widePath, SYS_MAX_PATH)) {
        LOG_ERROR("unable to retrieve absolute path.");
        return shortPath;
    }

    return sys_windows_short_path_from_wcs(shortPath, SYS_MAX_PATH, widePath) ? shortPath : NULL;
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

    char const *subdirs[] = { "sm64coopdx", "sm64ex-coop", "sm64coopdx", NULL };

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

const char *sys_resource_path(void)
{
#ifdef __APPLE__ // Kinda lazy, but I don't know how to add CoreFoundation.framework
    static char path[SYS_MAX_PATH];
    if ('\0' != path[0]) { return path; }

    const char *exeDir = sys_exe_path_dir();
    char *lastSeparator = strrchr(exeDir, '/');
    if (lastSeparator != NULL) {
        const char folder[] = "/Resources";
        size_t count = (size_t)(lastSeparator - exeDir);
        strncpy(path, exeDir, count);
        return strncat(path, folder, sizeof(path) - 1 - count);
    }
#endif

    return sys_exe_path_dir();
}

const char *sys_exe_path_dir(void) {
    static char path[SYS_MAX_PATH];
    if ('\0' != path[0]) { return path; }

    const char *exeFilepath = sys_exe_path_file();
    char *lastSeparator = strrchr(exeFilepath, '/');
    if (lastSeparator != NULL) {
        size_t count = (size_t)(lastSeparator - exeFilepath);
        strncpy(path, exeFilepath, count);
    }

    return path;
}

const char *sys_exe_path_file(void) {
    static char path[SYS_MAX_PATH];
    if ('\0' != path[0]) { return path; }

#if defined(__APPLE__)
    uint32_t bufsize = SYS_MAX_PATH;
    int res = _NSGetExecutablePath(path, &bufsize);

#else
    char procPath[SYS_MAX_PATH];
    snprintf(procPath, SYS_MAX_PATH, "/proc/%d/exe", getpid());
    ssize_t res = readlink(procPath, path, SYS_MAX_PATH);

#endif
    if (res <= 0) {
        LOG_ERROR("unable to retrieve absolute path.");
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
