#ifndef VERSION_H
#define VERSION_H

#define VERSION_TEXT "beta"
#define VERSION_NUMBER 33
#define MINOR_VERSION_NUMBER 0
#define PATCH_VERSION_NUMBER 0

#define MAX_VERSION_LENGTH 10
#define MAX_LOCAL_VERSION_LENGTH 12
char* get_version(void);
char* get_version_local(void);

#endif
