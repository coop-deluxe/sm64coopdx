#include <unistd.h>
#include <sys/stat.h>
#include "mods_utils.h"
#include "pc/debuglog.h"

bool str_ends_with(char* string, char* suffix) {
    if (string == NULL || suffix == NULL) { return false; }

    size_t stringLength = strlen(string);
    size_t suffixLength = strlen(suffix);

    if (suffixLength > stringLength) { return false; }

    return !strcmp(&string[stringLength - suffixLength], suffix);
}


char* extract_lua_field(char* fieldName, char* buffer) {
    size_t length = strlen(fieldName);
    if (strncmp(fieldName, buffer, length) == 0) {
        char* s = &buffer[length];
        while (*s == ' ' || *s == '\t') { s++; }
        return s;
    }
    return NULL;
}

bool path_exists(char* path) {
    struct stat sb = { 0 };
    return (stat(path, &sb) == 0);
}

bool is_directory(char* path) {
    struct stat sb = { 0 };
    return (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode));
}

void normalize_path(char* path) {
    // replace slashes
    char* p = path;
    while (*p) {
#if defined(_WIN32)
        if (*p == '/') { *p = '\\'; }
#else
        if (*p == '\\') { *p = '/'; }
#endif
        p++;
    }
}

bool concat_path(char* destination, char* path, char* fname) {
    return (snprintf(destination, SYS_MAX_PATH - 1, "%s/%s", path, fname) >= 0);
}

char* path_basename(char* path) {
    char* base = path;
    while (*path != '\0') {
        if (*(path + 1) != '\0') {
            if (*path == '\\' || *path == '/') {
                base = path + 1;
            }
        }
        path++;
    }
    return base;
}

bool directory_sanity_check(struct dirent* dir, char* dirPath, char* outPath) {
    // skip anything that contains \ or /
    if (strchr(dir->d_name, '/') != NULL)  { return false; }
    if (strchr(dir->d_name, '\\') != NULL) { return false; }

    // skip anything that starts with .
    if (dir->d_name == NULL || dir->d_name[0] == '.') { return false; }

    // build path
    if (!concat_path(outPath, dirPath, dir->d_name)) {
        LOG_ERROR("Failed to concat path '%s' + '%s'", dirPath, dir->d_name);
        return false;
    }
    normalize_path(outPath);

    // sanity check
    if (!path_exists(outPath)) {
        LOG_ERROR("Path doesn't exist: '%s'", outPath);
        return false;
    }

    return true;
}