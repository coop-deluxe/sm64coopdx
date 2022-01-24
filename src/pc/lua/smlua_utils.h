#ifndef SMLUA_UTILS_H
#define SMLUA_UTILS_H

extern u8 gSmLuaConvertSuccess;

f32* smlua_get_vec3f_from_buffer(void);
s16* smlua_get_vec3s_from_buffer(void);

void smlua_bind_function(lua_State* L, const char* name, void* func);
void smlua_logline(void);

lua_Integer smlua_to_integer(lua_State* L, int index);
lua_Number smlua_to_number(lua_State* L, int index);
const char* smlua_to_string(lua_State* L, int index);
void* smlua_to_cobject(lua_State* L, int index, enum LuaObjectType lot);

void smlua_push_object(lua_State* L, enum LuaObjectType lot, void* p);
void smlua_push_integer_field(int index, char* name, lua_Integer val);
void smlua_push_number_field(int index, char* name, lua_Number val);

lua_Integer smlua_get_integer_field(int index, char* name);
lua_Number smlua_get_number_field(int index, char* name);

void smlua_dump_stack(void);
void smlua_dump_globals(void);
void smlua_dump_table(int index);

#endif