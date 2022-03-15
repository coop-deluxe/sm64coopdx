#ifndef MODS_UTILS_H
#define MODS_UTILS_H

#include "PR/ultratypes.h"
#include <types.h>
#include "src/pc/platform.h"

bool str_ends_with(char* string, char* suffix);

char* extract_lua_field(char* fieldName, char* buffer);

bool path_exists(char* path);
bool is_directory(char* path);
void normalize_path(char* path);
bool concat_path(char* destination, char* path, char* fname);
char* path_basename(char* path);
bool directory_sanity_check(struct dirent* dir, char* dirPath, char* outPath);

#endif