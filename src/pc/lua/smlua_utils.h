#ifndef SMLUA_UTILS_H
#define SMLUA_UTILS_H

extern u8 gSmLuaConvertSuccess;

void smlua_bind_function(lua_State* L, const char* name, void* func);

lua_Integer smlua_to_integer(lua_State* L, int index);
lua_Number smlua_to_number(lua_State* L, int index);
void* smlua_to_cobject(lua_State* L, int index, enum LuaObjectType lot);

void smlua_push_object(lua_State* L, enum LuaObjectType lot, void* p);
void smlua_push_integer_field(lua_Integer val, char* name);
void smlua_push_number_field(float val, char* name);

void smlua_get_u8_field(u8* val, char* name);
void smlua_get_u16_field(u16* val, char* name);
void smlua_get_u32_field(u32* val, char* name);
void smlua_get_s8_field(s8* val, char* name);
void smlua_get_s16_field(s16* val, char* name);
void smlua_get_s32_field(s32* val, char* name);
void smlua_get_number_field(float* val, char* name);

void smlua_dump_stack(void);
void smlua_dump_globals(void);

#endif