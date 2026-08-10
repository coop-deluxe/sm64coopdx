#pragma once

#include "pc/lua/smlua_utils.h"

/* |description|Reads a file in a given mod, relative to the current lua file if it's the active mod, and returns its content as a bytestring|descriptionEnd|*/
ByteString smlua_fs_utils_mod_file_read(struct Mod *mod, const char *fileName);
/* |description|Checks if a file exists inside of a mod|descriptionEnd| */
bool smlua_fs_utils_mod_file_exists(const char* filename);
/* |description|Gets all files a mod contains|descriptionEnd| */
LuaTable smlua_fs_utils_mod_files_get(struct Mod* mod, OPTIONAL const char* subDirectory, OPTIONAL bool relative);