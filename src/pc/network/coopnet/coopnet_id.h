#pragma once

#include <PR/ultratypes.h>

void coopnet_save_dest_id(uint64_t userId, uint64_t destId);
void coopnet_clear_dest_id(uint64_t userId);
void coopnet_clear_dest_ids(void);
uint64_t coopnet_get_dest_id(uint64_t userId);

u8 coopnet_user_id_to_local_index(uint64_t userId);
void coopnet_set_user_id(uint8_t localIndex, uint64_t userId);
uint64_t coopnet_get_local_user_id(void);
void coopnet_set_local_user_id(uint64_t userId);

s64 coopnet_raw_get_id(u8 localIndex);
s64 ns_coopnet_get_id(u8 localIndex);
void ns_coopnet_save_id(u8 localIndex, s64 networkId);
void ns_coopnet_clear_id(u8 localIndex);
void* ns_coopnet_dup_addr(u8 localIndex);