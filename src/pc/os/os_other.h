#pragma once

#include <dirent.h>

#define os_dirent struct dirent
#define OS_DIR DIR
#define os_opendir(_x) opendir(_x)
#define os_readdir(_x) readdir(_x)
#define os_closedir(_x) closedir(_x)
#define os_get_dir_name(_x) _x->d_name
