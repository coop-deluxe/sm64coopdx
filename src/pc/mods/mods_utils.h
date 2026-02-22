#ifndef MODS_UTILS_H
#define MODS_UTILS_H

#include <PR/ultratypes.h>
#include "types.h"
#include "pc/platform.h"

void mods_size_enforce(struct Mods* mods);
void mods_update_selectable(void);
void mods_delete_tmp(void);

bool mod_file_full_path(char* destination, struct Mod* mod, struct ModFile* modFile);
bool mod_file_create_directories(struct Mod* mod, struct ModFile* modFile);

bool str_starts_with(const char *string, const char *prefix);
bool str_ends_with(const char *string, const char *suffix);

bool path_ends_with(const char* path, const char* suffix);

char* extract_lua_field(char* fieldName, char* buffer);

void normalize_path(char* path);
bool concat_path(char* destination, char* path, char* fname);
char* path_basename(char* path);
void path_get_folder(char* path, char* outpath);
int path_depth(const char* path);
void resolve_relative_path(const char* base, const char* path, char* output);
bool path_is_relative_to(const char* fullPath, const char* baseDir);
bool directory_sanity_check(struct dirent* dir, char* dirPath, char* outPath);

#endif