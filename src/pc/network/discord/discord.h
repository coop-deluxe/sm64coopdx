#ifndef DISCORD_H
#define DISCORD_H
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#pragma pack(push, 8)
#include "discord_game_sdk.h"
#pragma pack(pop)
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#include <string.h>
#endif
#include "../network.h"

// disgusting but descriptive
#define DISCORD_REQUIRE(x) {                                                         \
    enum EDiscordResult DISCORD_REQUIRE_RC = x;                                      \
    if (DISCORD_REQUIRE_RC != DiscordResult_Ok) {                                    \
        assert(DISCORD_REQUIRE_RC != DiscordResult_ServiceUnavailable);              \
        assert(DISCORD_REQUIRE_RC != DiscordResult_InvalidVersion);                  \
        assert(DISCORD_REQUIRE_RC != DiscordResult_LockFailed);                      \
        assert(DISCORD_REQUIRE_RC != DiscordResult_InternalError);                   \
        assert(DISCORD_REQUIRE_RC != DiscordResult_InvalidPayload);                  \
        assert(DISCORD_REQUIRE_RC != DiscordResult_InvalidCommand);                  \
        assert(DISCORD_REQUIRE_RC != DiscordResult_InvalidPermissions);              \
        assert(DISCORD_REQUIRE_RC != DiscordResult_NotFetched);                      \
        assert(DISCORD_REQUIRE_RC != DiscordResult_NotFound);                        \
        assert(DISCORD_REQUIRE_RC != DiscordResult_Conflict);                        \
        assert(DISCORD_REQUIRE_RC != DiscordResult_InvalidSecret);                   \
        assert(DISCORD_REQUIRE_RC != DiscordResult_InvalidJoinSecret);               \
        assert(DISCORD_REQUIRE_RC != DiscordResult_NoEligibleActivity);              \
        assert(DISCORD_REQUIRE_RC != DiscordResult_InvalidInvite);                   \
        assert(DISCORD_REQUIRE_RC != DiscordResult_NotAuthenticated);                \
        assert(DISCORD_REQUIRE_RC != DiscordResult_InvalidAccessToken);              \
        assert(DISCORD_REQUIRE_RC != DiscordResult_ApplicationMismatch);             \
        assert(DISCORD_REQUIRE_RC != DiscordResult_InvalidDataUrl);                  \
        assert(DISCORD_REQUIRE_RC != DiscordResult_InvalidBase64);                   \
        assert(DISCORD_REQUIRE_RC != DiscordResult_NotFiltered);                     \
        assert(DISCORD_REQUIRE_RC != DiscordResult_LobbyFull);                       \
        assert(DISCORD_REQUIRE_RC != DiscordResult_InvalidFilename);                 \
        assert(DISCORD_REQUIRE_RC != DiscordResult_InvalidFileSize);                 \
        assert(DISCORD_REQUIRE_RC != DiscordResult_InvalidEntitlement);              \
        assert(DISCORD_REQUIRE_RC != DiscordResult_NotInstalled);                    \
        assert(DISCORD_REQUIRE_RC != DiscordResult_NotRunning);                      \
        assert(DISCORD_REQUIRE_RC != DiscordResult_InsufficientBuffer);              \
        assert(DISCORD_REQUIRE_RC != DiscordResult_PurchaseCanceled);                \
        assert(DISCORD_REQUIRE_RC != DiscordResult_InvalidGuild);                    \
        assert(DISCORD_REQUIRE_RC != DiscordResult_InvalidEvent);                    \
        assert(DISCORD_REQUIRE_RC != DiscordResult_InvalidChannel);                  \
        assert(DISCORD_REQUIRE_RC != DiscordResult_InvalidOrigin);                   \
        assert(DISCORD_REQUIRE_RC != DiscordResult_RateLimited);                     \
        assert(DISCORD_REQUIRE_RC != DiscordResult_OAuth2Error);                     \
        assert(DISCORD_REQUIRE_RC != DiscordResult_SelectChannelTimeout);            \
        assert(DISCORD_REQUIRE_RC != DiscordResult_SelectVoiceForceRequired);        \
        assert(DISCORD_REQUIRE_RC != DiscordResult_CaptureShortcutAlreadyListening); \
        assert(DISCORD_REQUIRE_RC != DiscordResult_UnauthorizedForAchievement);      \
        assert(DISCORD_REQUIRE_RC != DiscordResult_InvalidGiftCode);                 \
        assert(DISCORD_REQUIRE_RC != DiscordResult_PurchaseError);                   \
        assert(DISCORD_REQUIRE_RC != DiscordResult_TransactionAborted);              \
        assert(DISCORD_REQUIRE_RC == DiscordResult_Ok);                              \
    }                                                                                \
}

extern struct NetworkSystem gNetworkSystemDiscord;
extern bool gDiscordInitialized;

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