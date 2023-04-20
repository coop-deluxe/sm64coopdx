#ifndef VERSION_H
#define VERSION_H

#define VERSION_TEXT "beta"
#define VERSION_NUMBER 34
#define MINOR_VERSION_NUMBER 0
#define PATCH_VERSION_NUMBER 0

#define MAX_VERSION_LENGTH 28
#define MAX_LOCAL_VERSION_LENGTH 32
char* get_version(void);
char* get_version_local(void);

#endif
