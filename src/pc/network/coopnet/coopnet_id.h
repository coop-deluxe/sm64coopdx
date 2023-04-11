#pragma once

#include "PR/ultratypes.h"

u8 coopnet_user_id_to_local_index(uint64_t userId);
void coopnet_set_user_id(uint8_t localIndex, uint64_t userId);
uint64_t coopnet_get_local_user_id(void);
void coopnet_set_local_user_id(uint64_t userId);

s64 ns_coopnet_get_id(u8 localIndex);
void ns_coopnet_save_id(u8 localIndex, s64 networkId);
void ns_coopnet_clear_id(u8 localIndex);
void* ns_coopnet_dup_addr(u8 localIndex);