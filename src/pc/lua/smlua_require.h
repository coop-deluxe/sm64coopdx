#ifndef SMLUA_REQUIRE_H
#define SMLUA_REQUIRE_H

#include "smlua.h"

void smlua_bind_custom_require(lua_State* L);
void smlua_init_require_system(void);

#endif