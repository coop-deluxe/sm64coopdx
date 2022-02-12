#ifndef DISCORD_NETWORK_H
#define DISCORD_NETWORK_H
#include "discord.h"

extern int64_t gNetworkUserIds[MAX_PLAYERS];

u8 discord_user_id_to_local_index(int64_t userId);
int ns_discord_network_send(u8 localIndex, void* addr, u8* data, u16 dataLength);
void discord_network_on_message(UNUSED void* eventData, int64_t lobbyId, int64_t userId, uint8_t channelId, uint8_t* data, uint32_t dataLength);
void discord_network_flush(void);
s64 ns_discord_get_id(u8 localId);
char* ns_discord_get_id_str(u8 localId);
void ns_discord_save_id(u8 localId, s64 networkId);
void ns_discord_clear_id(u8 localId);
void discord_network_init(int64_t lobbyId);
void discord_network_shutdown(void);

#endif