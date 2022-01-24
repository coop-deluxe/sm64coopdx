#ifndef SMLUA_COBJECT_ALLOWLIST_H
#define SMLUA_COBJECT_ALLOWLIST_H

void smlua_cobject_allowlist_init(void);
void smlua_cobject_allowlist_shutdown(void);
void smlua_cobject_allowlist_add(enum LuaObjectType objectType, u64 pointer);
bool smlua_cobject_allowlist_contains(enum LuaObjectType objectType, u64 pointer);

#endif