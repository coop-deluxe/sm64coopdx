#ifndef SMLUA_UTILS_H
#define SMLUA_UTILS_H

void smlua_dump_stack(void);
void smlua_dump_globals(void);

void smlua_push_integer_field(lua_Integer val, char* name);
void smlua_push_number_field(float val, char* name);

void smlua_get_u8_field(u8* val, char* name);
void smlua_get_u16_field(u16* val, char* name);
void smlua_get_u32_field(u32* val, char* name);
void smlua_get_s8_field(s8* val, char* name);
void smlua_get_s16_field(s16* val, char* name);
void smlua_get_s32_field(s32* val, char* name);
void smlua_get_number_field(float* val, char* name);

#endif