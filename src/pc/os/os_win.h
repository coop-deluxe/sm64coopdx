#pragma once

#include <wchar.h>
#include <dirent.h>

#define os_dirent struct _wdirent
#define OS_DIR _WDIR

#define os_closedir(_x) _wclosedir(_x)
#define os_readdir(_x) _wreaddir(_x)

OS_DIR* os_opendir(const char* path);
const char* os_get_dir_name(os_dirent* dir);
