#ifndef DISCORD_LOBBY_H
#define DISCORD_LOBBY_H
#include "discord.h"

extern DiscordLobbyId gCurLobbyId;

void discord_lobby_create(void);
void discord_lobby_leave(void);
struct IDiscordLobbyEvents* discord_lobby_initialize(void);

#endif