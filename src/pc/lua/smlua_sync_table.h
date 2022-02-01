#ifndef SMLUA_SYNC_TABLE_H
#define SMLUA_SYNC_TABLE_H

enum LuaSyncTableType {
    LST_GLOBAL,
    LST_PLAYER,
    LST_MAX,
};

union LSTNetworkUnion;

void smlua_set_sync_table_field_from_network(u64 seq, u16 remoteIndex, u16 lst, u16 index, const char* key, u16 lUnionType, union LSTNetworkUnion lUnion);
void smlua_sync_table_init_globals(char* path, u16 remoteIndex);
void smlua_bind_sync_table(void);
void smlua_sync_table_send_all(u8 toLocalIndex);

#endif