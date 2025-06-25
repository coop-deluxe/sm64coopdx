#ifndef SMLUA_REQUIRE_H
#define SMLUA_REQUIRE_H

#include "smlua.h"

void smlua_require_update(lua_State* L);
void smlua_bind_custom_require(lua_State* L);
void smlua_reload_module(lua_State *L, struct Mod* mod, struct ModFile *file);
void smlua_init_require_system(void);

#endif