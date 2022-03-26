#ifndef DISCORD_ACTIVITY_H
#define DISCORD_ACTIVITY_H
#include "discord.h"

extern struct DiscordActivity gCurActivity;

void discord_activity_update(bool hosting);
void discord_activity_update_check(void);
struct IDiscordActivityEvents* discord_activity_initialize(void);
extern bool gActivityLock;

#endif