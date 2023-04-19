#ifndef VERSION_H
#define VERSION_H

#define PATCH_VERSION_NUMBER 0

#define MAX_VERSION_LENGTH 28
#define MAX_LOCAL_VERSION_LENGTH 32

char* get_version(void);
char* get_version_local(void);

#endif
