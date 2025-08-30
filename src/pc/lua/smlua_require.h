#ifndef SMLUA_REQUIRE_H
#define SMLUA_REQUIRE_H

#include "smlua.h"

void smlua_require_update(lua_State* L);
void smlua_bind_custom_require(lua_State* L);
void smlua_get_or_create_mod_loaded_table(lua_State* L, struct Mod* mod);
bool smlua_get_cached_file(lua_State* L, struct Mod* mod, struct ModFile* file);
void smlua_cache_module_result(lua_State* L, struct Mod* mod, struct ModFile* file);
void smlua_init_require_system(void);

#endif