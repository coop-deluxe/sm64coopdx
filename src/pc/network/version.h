#ifndef VERSION_H
#define VERSION_H

#define SM64COOPDX_VERSION "v1.0"

// sm64ex-coop version, for mod compatibility
#define VERSION_TEXT "beta"
#define VERSION_NUMBER 37
#define MINOR_VERSION_NUMBER 0
#define PATCH_VERSION_NUMBER 0

#if defined(VERSION_JP)
    #define VERSION_REGION "JP"
#elif defined(VERSION_EU)
    #define VERSION_REGION "EU"
#elif defined(VERSION_SH)
    #define VERSION_REGION "SH"
#else
    #define VERSION_REGION "US"
#endif

#ifdef DEVELOPMENT
    #define GAME_NAME "sm64coopdx-dev"
#elif !defined(VERSION_US)
    #define GAME_NAME "sm64coopdx-intl"
#else
    #define GAME_NAME "sm64coopdx"
#endif

#define MAX_VERSION_LENGTH 32

const char* get_version(void);

#endif
