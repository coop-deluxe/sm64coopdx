#ifndef SMLUA_UTILS_H
#define SMLUA_UTILS_H

extern u8 gSmLuaConvertSuccess;

f32* smlua_get_vec3f_from_buffer(void);
s16* smlua_get_vec3s_from_buffer(void);

void smlua_bind_function(lua_State* L, const char* name, void* func);
bool smlua_is_table_empty(int index);

bool smlua_to_boolean(lua_State* L, int index);
lua_Integer smlua_to_integer(lua_State* L, int index);
lua_Number smlua_to_number(lua_State* L, int index);
const char* smlua_to_string(lua_State* L, int index);
void* smlua_to_cobject(lua_State* L, int index, u16 lot);
struct LSTNetworkType smlua_to_lnt(lua_State* L, int index);

void smlua_push_object(lua_State* L, u16 lot, void* p);
void smlua_push_integer_field(int index, char* name, lua_Integer val);
void smlua_push_number_field(int index, char* name, lua_Number val);
void smlua_push_string_field(int index, char* name, const char* val);
void smlua_push_nil_field(int index, char* name);
void smlua_push_table_field(int index, char* name);

void smlua_push_lnt(struct LSTNetworkType* lnt);

lua_Integer smlua_get_integer_field(int index, char* name);
lua_Number smlua_get_number_field(int index, char* name);

char* smlua_lnt_to_str(struct LSTNetworkType* lnt);
void smlua_logline(void);
void smlua_dump_stack(void);
void smlua_dump_globals(void);
void smlua_dump_table(int index);

#endif