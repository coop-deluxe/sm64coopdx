#pragma once

#include <PR/ultratypes.h>
#include "discord_game_sdk.h"

#ifdef _WIN32
#define DISCORD_ID_FORMAT "%lld"
#else
#define DISCORD_ID_FORMAT "%ld"
#endif

// disgusting but descriptive
#define DISCORD_REQUIRE(x) {                      \
    enum EDiscordResult DISCORD_REQUIRE_RC = x;   \
    if (DISCORD_REQUIRE_RC != DiscordResult_Ok) { \
        discord_fatal(DISCORD_REQUIRE_RC);        \
    }                                             \
}

struct DiscordApplication {
    struct IDiscordCore* core;
    struct IDiscordUserManager* users;
    struct IDiscordAchievementManager* achievements;
    struct IDiscordActivityManager* activities;
    struct IDiscordRelationshipManager* relationships;
    struct IDiscordApplicationManager* application;
    struct IDiscordLobbyManager* lobbies;
    DiscordUserId userId;
};

extern bool gDiscordInitialized;

void discord_update(void);
void discord_fatal(int rc);
void discord_activity_update_check(void);
void discord_activity_update(void);
struct IDiscordActivityEvents* discord_activity_initialize(void);
u64 discord_get_user_id(void);
