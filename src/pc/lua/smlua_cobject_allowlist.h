#ifndef SMLUA_COBJECT_ALLOWLIST_H
#define SMLUA_COBJECT_ALLOWLIST_H

void smlua_cobject_allowlist_init(void);
void smlua_cobject_allowlist_shutdown(void);
void smlua_cobject_allowlist_add(u16 lot, u64 pointer);
bool smlua_cobject_allowlist_contains(u16 lot, u64 pointer);

#endif