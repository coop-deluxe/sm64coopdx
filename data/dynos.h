#ifndef DYNOS_H
#define DYNOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <dirent.h>
#ifdef HAVE_SDL2
#include <SDL2/SDL.h>
#endif
#ifdef __cplusplus
#include <new>
#include <utility>
#include <string>
#include <map>
extern "C" {
#endif
#include "config.h"
#include "pc/fs/fs.h"
#include "sounds.h"
#undef STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#ifdef __cplusplus
}
#endif

#define DYNOS_VERSION           "1.0"
#define DYNOS_EXE_FOLDER        sys_resource_path()
#define DYNOS_USER_FOLDER       fs_get_write_path("")
#define DYNOS_RES_FOLDER        "dynos"
#define DYNOS_PACKS_FOLDER      DYNOS_RES_FOLDER "/packs"
#define DYNOS_CONFIG_FILENAME   "DynOS." DYNOS_VERSION ".config.txt"
#define DYNOS_AT_STARTUP		__attribute__((constructor))
#define DYNOS_AT_EXIT			__attribute__((destructor))

enum ModelPool {
    MODEL_POOL_PERMANENT,
    MODEL_POOL_SESSION,
    MODEL_POOL_LEVEL,
    MODEL_POOL_MAX,
};

enum {
    DYNOS_MOD_DATA_ERROR_NAME_IS_NULL = 1,
    DYNOS_MOD_DATA_ERROR_NAME_IS_EMPTY,
    DYNOS_MOD_DATA_ERROR_NAME_NOT_FOUND,
    DYNOS_MOD_DATA_ERROR_POINTER_IS_NULL,
    DYNOS_MOD_DATA_ERROR_POINTER_NOT_FOUND,
    DYNOS_MOD_DATA_ERROR_SIZE_IS_ZERO,
    DYNOS_MOD_DATA_ERROR_SIZE_IS_ABOVE_MAX,
    DYNOS_MOD_DATA_ERROR_ALREADY_EXISTS,
    DYNOS_MOD_DATA_ERROR_POOL_IS_FULL,
};

#endif
