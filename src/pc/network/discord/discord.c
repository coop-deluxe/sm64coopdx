#include "discord.h"
#include "user.h"
#include "activity.h"
#include "lobby.h"
#include "discord_network.h"
#include "pc/debuglog.h"
#include "menu/custom_menu_system.h"
#include "pc/network/version.h"

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <winuser.h>
#else
#include <unistd.h>
#define MAX_PATH 1024
#endif

#define MAX_LAUNCH_CMD (MAX_PATH + 12)

static int64_t applicationId = 752700005210390568;
struct DiscordApplication app = { 0 };
bool gDiscordInitialized = false;
bool gDiscordFailed = false;

void discord_fatal(int rc) {
#if defined(_WIN32) || defined(_WIN64)
    char errorMessage[132] = { 0 };
    snprintf(errorMessage, 132, "Discord threw an error.\r\n\r\nTo fix: \r\n1. Close the game.\r\n2. Restart Discord.\r\n3. Start the game.\r\n\r\nRC: %d", rc);
    int msgboxID = MessageBox(NULL,
        errorMessage,
        "Fatal Discord Error",
        MB_ICONERROR | MB_OK | MB_DEFBUTTON1
    );
    exit(1);
#else
    assert(rc != DiscordResult_ServiceUnavailable);
    assert(rc != DiscordResult_InvalidVersion);
    assert(rc != DiscordResult_LockFailed);
    assert(rc != DiscordResult_InternalError);
    assert(rc != DiscordResult_InvalidPayload);
    assert(rc != DiscordResult_InvalidCommand);
    assert(rc != DiscordResult_InvalidPermissions);
    assert(rc != DiscordResult_NotFetched);
    assert(rc != DiscordResult_NotFound);
    assert(rc != DiscordResult_Conflict);
    assert(rc != DiscordResult_InvalidSecret);
    assert(rc != DiscordResult_InvalidJoinSecret);
    assert(rc != DiscordResult_NoEligibleActivity);
    assert(rc != DiscordResult_InvalidInvite);
    assert(rc != DiscordResult_NotAuthenticated);
    assert(rc != DiscordResult_InvalidAccessToken);
    assert(rc != DiscordResult_ApplicationMismatch);
    assert(rc != DiscordResult_InvalidDataUrl);
    assert(rc != DiscordResult_InvalidBase64);
    assert(rc != DiscordResult_NotFiltered);
    assert(rc != DiscordResult_LobbyFull);
    assert(rc != DiscordResult_InvalidFilename);
    assert(rc != DiscordResult_InvalidFileSize);
    assert(rc != DiscordResult_InvalidEntitlement);
    assert(rc != DiscordResult_NotInstalled);
    assert(rc != DiscordResult_NotRunning);
    assert(rc != DiscordResult_InsufficientBuffer);
    assert(rc != DiscordResult_PurchaseCanceled);
    assert(rc != DiscordResult_InvalidGuild);
    assert(rc != DiscordResult_InvalidEvent);
    assert(rc != DiscordResult_InvalidChannel);
    assert(rc != DiscordResult_InvalidOrigin);
    assert(rc != DiscordResult_RateLimited);
    assert(rc != DiscordResult_OAuth2Error);
    assert(rc != DiscordResult_SelectChannelTimeout);
    assert(rc != DiscordResult_SelectVoiceForceRequired);
    assert(rc != DiscordResult_CaptureShortcutAlreadyListening);
    assert(rc != DiscordResult_UnauthorizedForAchievement);
    assert(rc != DiscordResult_InvalidGiftCode);
    assert(rc != DiscordResult_PurchaseError);
    assert(rc != DiscordResult_TransactionAborted);
    assert(rc == DiscordResult_Ok);
#endif
}

static void set_instance_env_variable(void) {
    // set local instance id
    char environmentVariables[64] = { 0 };
    int instance = (gCLIOpts.Discord == 0) ? 0 : (gCLIOpts.Discord - 1);
    sprintf(environmentVariables, "DISCORD_INSTANCE_ID=%d", instance);
    putenv(environmentVariables);
    LOG_INFO("set environment variables: %s", environmentVariables);
}

static void get_oauth2_token_callback(UNUSED void* data, enum EDiscordResult result, struct DiscordOAuth2Token* token) {
    LOG_INFO("> get_oauth2_token_callback returned %d", result);
    if (result != DiscordResult_Ok) { return; }
    LOG_INFO("OAuth2 token: %s", token->access_token);
}

static void register_launch_command(void) {
    char cmd[MAX_LAUNCH_CMD];
    int rc;
#if defined(_WIN32) || defined(_WIN64)
    HMODULE hModule = GetModuleHandle(NULL);
    if (hModule == NULL) {
        LOG_ERROR("unable to retrieve absolute path!");
        return;
    }
    GetModuleFileName(hModule, cmd, sizeof(cmd));
#else
    char path[MAX_LAUNCH_CMD] = { 0 };
    snprintf(path, MAX_LAUNCH_CMD - 1, "/proc/%d/exe", getpid());
    rc = readlink(path, cmd, MAX_LAUNCH_CMD - 1);
    if (rc <= 0) {
        LOG_ERROR("unable to retrieve absolute path! rc = %d", rc);
        return;
    }
#endif
    strncat(cmd, " --discord 1", MAX_LAUNCH_CMD - 1);
    rc = app.activities->register_command(app.activities, cmd);
    if (rc != DiscordResult_Ok) {
        LOG_ERROR("register command failed %d", rc);
        return;
    }
    LOG_INFO("cmd: %s", cmd);
}

static void ns_discord_update(void) {
    if (!gDiscordInitialized) { return; }
    DISCORD_REQUIRE(app.core->run_callbacks(app.core));
    discord_network_flush();
}

static bool ns_discord_initialize(enum NetworkType networkType) {
#ifdef DEBUG
    set_instance_env_variable();
#endif
#ifdef UNSTABLE_BRANCH
    if (networkType != NT_NONE) {
        // refuse to host on discord for unstable branch
        exit(1);
    }
#endif

    if (!gDiscordInitialized) {
        // set up discord params
        struct DiscordCreateParams params;
        DiscordCreateParamsSetDefault(&params);
        params.client_id = applicationId;
        params.flags = DiscordCreateFlags_NoRequireDiscord;
        params.event_data = &app;
        params.user_events = discord_user_initialize();
        params.activity_events = discord_activity_initialize();
        params.lobby_events = discord_lobby_initialize();

        int rc = DiscordCreate(DISCORD_VERSION, &params, &app.core);
        gDiscordFailed = false;
        if (networkType != NT_NONE) {
            DISCORD_REQUIRE(rc);
        } else if (rc) {
            LOG_ERROR("DiscordCreate failed: %d", rc);
            custom_menu_error("Could not detect Discord.\n\nTry closing the game,\nrestarting Discord,\nand opening the game again.");
            gDiscordFailed = true;
            return false;
        }

        // set up manager pointers
        app.users = app.core->get_user_manager(app.core);
        app.achievements = app.core->get_achievement_manager(app.core);
        app.activities = app.core->get_activity_manager(app.core);
        app.application = app.core->get_application_manager(app.core);
        app.lobbies = app.core->get_lobby_manager(app.core);

        // register launch params
        register_launch_command();

        // get oath2 token
        app.application->get_oauth2_token(app.application, NULL, get_oauth2_token_callback);

        // set activity
        discord_activity_update(false);
    }

    // create lobby
    if (networkType == NT_SERVER) { discord_lobby_create(); }

    gDiscordInitialized = true;
    LOG_INFO("initialized");

    return true;
}

static void ns_discord_shutdown(void) {
    if (!gDiscordInitialized) { return; }
    discord_lobby_leave();
    LOG_INFO("shutdown");
}

struct NetworkSystem gNetworkSystemDiscord = {
    .initialize = ns_discord_initialize,
    .get_id     = ns_discord_get_id,
    .save_id    = ns_discord_save_id,
    .clear_id   = ns_discord_clear_id,
    .update     = ns_discord_update,
    .send       = ns_discord_network_send,
    .shutdown   = ns_discord_shutdown,
    .requireServerBroadcast = false,
};
