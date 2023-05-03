#ifndef VERSION_H
#define VERSION_H

#define VERSION_TEXT "beta"
#define VERSION_NUMBER 34
#define MINOR_VERSION_NUMBER 1
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

#define MAX_VERSION_LENGTH 32
#define MAX_LOCAL_VERSION_LENGTH 36
char* get_version(void);
char* get_version_local(void);

#endif
