#ifndef SMLUA_COBJECT_MAP_H
#define SMLUA_COBJECT_MAP_H

void smlua_pointer_user_data_init(void);
void smlua_pointer_user_data_shutdown(void);
void smlua_pointer_user_data_add(u64 pointer, CObject *obj);
void smlua_pointer_user_data_delete(u64 pointer);
CObject *smlua_pointer_user_data_get(u64 pointer);

#endif
