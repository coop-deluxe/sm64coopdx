#include "discord.h"
#include "user.h"
#include "activity.h"
#include "lobby.h"
#include "discord_network.h"
#include "pc/debuglog.h"

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#else
#include <unistd.h>
#define MAX_PATH 1024
#endif

#define MAX_LAUNCH_CMD (MAX_PATH + 12)

static int64_t applicationId = 752700005210390568;
struct DiscordApplication app = { 0 };
bool gDiscordInitialized = false;

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
#if defined(_WIN32) || defined(_WIN64)
    HMODULE hModule = GetModuleHandle(NULL);
    if (hModule == NULL) {
        LOG_ERROR("unable to retrieve absolute path!");
        return;
    }
    GetModuleFileName(hModule, cmd, sizeof(cmd));
#else
    int rc = readlink("/proc/self/exe", cmd, sizeof(MAX_LAUNCH_CMD) - 1);
    if (rc) {
        LOG_ERROR("unable to retrieve absolute path! rc = %d", rc);
        return;
    }
#endif
    strncat(cmd, " --discord 1", MAX_LAUNCH_CMD - 1);
    int rc = app.activities->register_command(app.activities, cmd);
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
        if (rc) {
            LOG_ERROR("DiscordCreate failed: %d", rc);
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
    .update     = ns_discord_update,
    .send       = ns_discord_network_send,
    .shutdown   = ns_discord_shutdown,
};
