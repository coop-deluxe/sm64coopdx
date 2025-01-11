#ifndef VERSION_H
#define VERSION_H

#define SM64COOPDX_VERSION "v1.1.1"

// internal version
#define VERSION_TEXT "v"
#define VERSION_NUMBER 38
#define MINOR_VERSION_NUMBER 1

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
#define GAME_NAME   "sm64coopdx-dev"
#define WINDOW_NAME "Super Mario 64 Coop Deluxe (DEV)"
#elif !defined(VERSION_US)
#define GAME_NAME "sm64coopdx-intl"
#define WINDOW_NAME "Super Mario 64 Coop Deluxe (INTL)"
#else
#define GAME_NAME "sm64coopdx"
#define WINDOW_NAME "Super Mario 64 Coop Deluxe"
#endif

#define MAX_VERSION_LENGTH 32

const char* get_version(void);

#endif
