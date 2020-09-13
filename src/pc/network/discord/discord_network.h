#ifndef DISCORD_NETWORK_H
#define DISCORD_NETWORK_H
#include "discord.h"

int ns_discord_network_send(u8* data, u16 dataLength);
void discord_network_on_message(UNUSED void* eventData, int64_t lobbyId, int64_t userId, uint8_t channelId, uint8_t* data, uint32_t dataLength);
void discord_network_flush(void);
void discord_network_init(int64_t lobbyId);
void discord_network_shutdown(void);

#endif