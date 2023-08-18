#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)

#include <stdio.h>
#include <stringapiset.h>
#include "os_win.h"
#include "pc/platform.h"

OS_DIR* os_opendir(const char* path) {
    wchar_t wpath[SYS_MAX_PATH] = { 0 };
    MultiByteToWideChar(CP_UTF8, 0, path, -1, wpath, SYS_MAX_PATH);
    return _wopendir(wpath);
}

const char* os_get_dir_name(os_dirent* dir) {
    static char path[SYS_MAX_PATH] = { 0 };
    snprintf(path, SYS_MAX_PATH, "%ls", dir->d_name);
    return path;
}

#endif