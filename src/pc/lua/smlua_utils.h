#ifndef SMLUA_UTILS_H
#define SMLUA_UTILS_H

extern u8 gSmLuaConvertSuccess;
typedef int LuaFunction;
struct Packet;
struct LSTNetworkType;

f32* smlua_get_vec3f_from_buffer(void);
s16* smlua_get_vec3s_from_buffer(void);
f32* smlua_get_vec4f_from_buffer(void);
s16* smlua_get_vec4s_from_buffer(void);
u8* smlua_get_color_from_buffer(void);

void smlua_bind_function(lua_State* L, const char* name, void* func);
bool smlua_is_table_empty(int index);

bool smlua_to_boolean(lua_State* L, int index);
lua_Integer smlua_to_integer(lua_State* L, int index);
lua_Number smlua_to_number(lua_State* L, int index);
const char* smlua_to_string(lua_State* L, int index);
LuaFunction smlua_to_lua_function(lua_State* L, int index);
bool smlua_is_cobject(lua_State* L, int index, u16 lot);
void* smlua_to_cobject(lua_State* L, int index, u16 lot);
void* smlua_to_cpointer(lua_State* L, int index, u16 lvt);
struct LSTNetworkType smlua_to_lnt(lua_State* L, int index);

bool packet_write_lnt(struct Packet* p, struct LSTNetworkType* lnt);
bool packet_read_lnt(struct Packet* p, struct LSTNetworkType* lnt);

CObject *smlua_push_object(lua_State* L, u16 lot, void* p, void *extraInfo);
CPointer *smlua_push_pointer(lua_State* L, u16 lvt, void* p, void *extraInfo);
void smlua_push_integer_field(int index, const char* name, lua_Integer val);
void smlua_push_number_field(int index, const char* name, lua_Number val);
void smlua_push_string_field(int index, const char* name, const char* val);
void smlua_push_nil_field(int index, const char* name);
void smlua_push_table_field(int index, const char* name);

void smlua_push_lnt(struct LSTNetworkType* lnt);

lua_Integer smlua_get_integer_field(int index, const char* name);
lua_Number smlua_get_number_field(int index, const char* name);
const char* smlua_get_string_field(int index, const char* name);
LuaFunction smlua_get_function_field(int index, const char *name);

const char* smlua_lnt_to_str(struct LSTNetworkType* lnt);

s64 smlua_get_integer_mod_variable(u16 modIndex, const char* variable);
s64 smlua_get_any_integer_mod_variable(const char* variable);
LuaFunction smlua_get_function_mod_variable(u16 modIndex, const char *variable);
LuaFunction smlua_get_any_function_mod_variable(const char *variable);

void smlua_logline(void);
void smlua_dump_stack(void);
void smlua_dump_globals(void);
void smlua_dump_table(int index);
void smlua_free(void *ptr);

#endif