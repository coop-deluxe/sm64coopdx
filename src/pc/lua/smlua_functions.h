#ifndef SMLUA_FUNCTIONS_H
#define SMLUA_FUNCTIONS_H

bool smlua_functions_valid_param_count(lua_State* L, int expected);
bool smlua_functions_valid_param_range(lua_State* L, int min, int max);
void smlua_bind_functions(void);

#endif