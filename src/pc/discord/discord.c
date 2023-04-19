#include "discord.h"
#include "pc/djui/djui.h"
#include "pc/debuglog.h"

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
static bool sFatalShown = false;
static bool sDiscordInitialized = false;
static bool sDiscordFailed = false;

static void discord_sdk_log_callback(UNUSED void* hook_data, enum EDiscordLogLevel level, const char* message) {
    LOG_INFO("callback (%d): %s", level, message);
}

void discord_fatal_message(int rc) { // Discord usually does this because of loss of connection to Discord
    LOG_ERROR("Discord fatal: %d", rc);
    /*char errorMessage[132] = { 0 };
    snprintf(errorMessage, 132, "%s\nRC: %d", DLANG(NOTIF, DISCORD_ERROR), rc);
    djui_popup_create(errorMessage, 6);*/
}

void discord_fatal(int rc) {
    if (!sFatalShown) {
        discord_fatal_message(rc);
        sFatalShown = true;
    }

    if (rc != DiscordResult_Ok) {
        LOG_ERROR("Discord threw an error. RC: %d", rc);
    }
}

static void get_oauth2_token_callback(UNUSED void* data, enum EDiscordResult result, struct DiscordOAuth2Token* token) {
    LOG_INFO("> get_oauth2_token_callback returned %d", result);
    if (result != DiscordResult_Ok) { return; }
    LOG_INFO("OAuth2 token: %s", token->access_token);
}

static void register_launch_command(void) {
    char cmd[MAX_LAUNCH_CMD] = { 0 };
    int rc;
#if defined(_WIN32) || defined(_WIN64)
    HMODULE hModule = GetModuleHandle(NULL);
    if (hModule == NULL) {
        LOG_ERROR("unable to retrieve absolute path!");
        return;
    }
    GetModuleFileName(hModule, cmd, sizeof(cmd));
#else
    char pidpath[MAX_LAUNCH_CMD] = { 0 };
    char fullpath[MAX_LAUNCH_CMD] = { 0 };
    snprintf(pidpath, MAX_LAUNCH_CMD - 1, "/proc/%d/exe", getpid());
    rc = readlink(pidpath, fullpath, MAX_LAUNCH_CMD - 1);
    if (rc <= 0) {
        LOG_ERROR("unable to retrieve absolute path! rc = %d", rc);
        return;
    }
    snprintf(cmd, MAX_LAUNCH_CMD, "%s", fullpath);
#endif
    rc = app.activities->register_command(app.activities, cmd);
    if (rc != DiscordResult_Ok) {
        LOG_ERROR("register command failed %d", rc);
        return;
    }
    LOG_INFO("cmd: %s", cmd);
}

static void on_current_user_update(UNUSED void* data) {
    LOG_INFO("> on_current_user_update");
    struct DiscordUser user = { 0 };
    app.users->get_current_user(app.users, &user);

    // remember user id
    app.userId = user.id;

    // copy over discord username if we haven't set one yet
    if (configPlayerName[0] == '\0' && strlen(user.username) > 0) {
        char* cname = configPlayerName;
        char* dname = user.username;
        for (int i = 0; i < MAX_PLAYER_STRING - 1; i++) {
            if (*dname >= '!' && *dname <= '~') {
                *cname = *dname;
                cname++;
            }
            dname++;
        }
    }
}

struct IDiscordUserEvents* discord_user_initialize(void) {
    LOG_INFO("> discord_user_intitialize");
    static struct IDiscordUserEvents events = { 0 };
    events.on_current_user_update = on_current_user_update;
    return &events;
}

static void discord_initialize(void) {
    if (sDiscordInitialized) { return; }
    sDiscordInitialized = true;

    if (app.core != NULL) {
        app.core->set_log_hook(app.core, DiscordLogLevel_Debug, NULL, discord_sdk_log_callback);
    }

    // set up discord params
    struct DiscordCreateParams params = { 0 };
    DiscordCreateParamsSetDefault(&params);
    params.client_id = applicationId;
    params.flags = DiscordCreateFlags_NoRequireDiscord;
    params.event_data = &app;
    params.user_events = discord_user_initialize();
    params.activity_events = discord_activity_initialize();

    int rc = DiscordCreate(DISCORD_VERSION, &params, &app.core);
    if (app.core != NULL) {
        app.core->set_log_hook(app.core, DiscordLogLevel_Debug, NULL, discord_sdk_log_callback);
    }

    if (rc) {
        LOG_ERROR("DiscordCreate failed: %d", rc);
        //djui_popup_create(DLANG(NOTIF, DISCORD_DETECT), 3);
        sDiscordFailed = true;
        return;
    }

    // set up manager pointers
    if (app.core != NULL) {
        app.users = app.core->get_user_manager(app.core);
        app.achievements = app.core->get_achievement_manager(app.core);
        app.activities = app.core->get_activity_manager(app.core);
        app.application = app.core->get_application_manager(app.core);
    }

    // get oath2 token
    app.application->get_oauth2_token(app.application, NULL, get_oauth2_token_callback);

    // set activity
    discord_activity_update();
    sDiscordFailed = false;

    // register launch params
    register_launch_command();

    LOG_INFO("initialized");
}

u64 discord_get_user_id(void) {
    return app.userId;
}

void discord_update(void) {
    if (sDiscordFailed) { return; }
    if (!sDiscordInitialized) { discord_initialize(); }
    if (sDiscordFailed) { return; }

    discord_activity_update_check();
    DISCORD_REQUIRE(app.core->run_callbacks(app.core));
}
