#ifndef SMLUA_FUNCTIONS_H
#define SMLUA_FUNCTIONS_H

bool smlua_functions_valid_param_count(lua_State* L, int expected);
void smlua_bind_functions(void);

#endif