#include "libcoopnet.h"
#include "coopnet.h"
#include "pc/network/network.h"
#include "pc/debuglog.h"

static uint64_t sLocalUserId = 0;
static uint64_t sNetworkUserIds[MAX_PLAYERS] = { 0 };

u8 coopnet_user_id_to_local_index(uint64_t userId) {
    for (int i = 1; i < MAX_PLAYERS; i++) {
        if (gNetworkPlayers[i].connected && sNetworkUserIds[i] == userId) {
            return i;
        }
    }
    return UNKNOWN_LOCAL_INDEX;
}

void coopnet_set_user_id(uint8_t localIndex, uint64_t userId) {
    sNetworkUserIds[localIndex] = userId;
}

uint64_t coopnet_get_local_user_id(void) {
    return sLocalUserId;
}

void coopnet_set_local_user_id(uint64_t userId) {
    sLocalUserId = userId;
}

s64 ns_coopnet_get_id(u8 localIndex) {
    if (localIndex == 0) { return (s64)sLocalUserId; }
    return (s64)sNetworkUserIds[localIndex];
}

void ns_coopnet_save_id(u8 localIndex, s64 networkId) {
    SOFT_ASSERT(localIndex > 0);
    SOFT_ASSERT(localIndex < MAX_PLAYERS);
    sNetworkUserIds[localIndex] = (networkId == 0) ? sNetworkUserIds[0] : (u64)networkId;
}

void ns_coopnet_clear_id(u8 localIndex) {
    if (localIndex == 0) { return; }
    SOFT_ASSERT(localIndex < MAX_PLAYERS);
    sNetworkUserIds[localIndex] = 0;
}

void* ns_coopnet_dup_addr(u8 localIndex) {
    void* address = malloc(sizeof(u64));
    memcpy(address, &sNetworkUserIds[localIndex], sizeof(u64));
    return address;
}
