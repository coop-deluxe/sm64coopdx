#ifndef DISCORD_H
#define DISCORD_H
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#pragma pack(push, 8)
#include "discord_game_sdk.h"
#pragma pack(pop)
#ifdef _WIN32
#define DISCORD_ID_FORMAT "%lld"
#include <Windows.h>
#else
#define DISCORD_ID_FORMAT "%ld"
#include <unistd.h>
#include <string.h>
#endif
#include "../network.h"

void discord_fatal(int rc);

// disgusting but descriptive
#define DISCORD_REQUIRE(x) {                      \
    enum EDiscordResult DISCORD_REQUIRE_RC = x;   \
    if (DISCORD_REQUIRE_RC != DiscordResult_Ok) { \
        discord_fatal(DISCORD_REQUIRE_RC);        \
    }                                             \
}

extern struct NetworkSystem gNetworkSystemDiscord;
extern bool gDiscordInitialized;
extern bool gDiscordFailed;

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

extern struct DiscordApplication app;

#endif