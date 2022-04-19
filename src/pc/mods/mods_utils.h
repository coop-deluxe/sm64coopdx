#ifndef MODS_UTILS_H
#define MODS_UTILS_H

#include "PR/ultratypes.h"
#include <types.h>
#include "src/pc/platform.h"

void mods_size_enforce(struct Mods* mods);
void mods_update_selectable(void);
void mods_delete_tmp(void);

bool mod_file_full_path(char* destination, struct Mod* mod, struct ModFile* modFile);
bool mod_file_create_directories(struct Mod* mod, struct ModFile* modFile);

bool str_ends_with(char* string, char* suffix);

char* extract_lua_field(char* fieldName, char* buffer);

const char* path_to_executable(void);
bool path_is_portable_filename(char* string);
bool path_exists(char* path);
bool is_directory(char* path);
void normalize_path(char* path);
bool concat_path(char* destination, char* path, char* fname);
char* path_basename(char* path);
void path_get_folder(char* path, char* outpath);
bool directory_sanity_check(struct dirent* dir, char* dirPath, char* outPath);

#endif