#include "discord.h"
#include "pc/pc_main.h"
#include "pc/djui/djui.h"
#include "pc/mods/mods.h"
#include "pc/debuglog.h"
#include "pc/utils/misc.h"
#include "pc/djui/djui_panel_join_message.h"
#ifdef COOPNET
#include "pc/network/coopnet/coopnet.h"
#endif

extern struct DiscordApplication app;
struct DiscordActivity sCurActivity = { 0 };
static int sQueuedLobby = 0;
static uint64_t sQueuedLobbyId = 0;
static char sQueuedLobbyPassword[64] = "";

static void on_activity_update_callback(UNUSED void* data, enum EDiscordResult result) {
    LOG_INFO("> on_activity_update_callback returned %d", result);
    DISCORD_REQUIRE(result);
}

static void on_activity_join(UNUSED void* data, const char* secret) {
    LOG_INFO("> on_activity_join, secret: %s", secret);
    char *token;

    // extract lobby type
    token = strtok((char*)secret, ":");
    if (strcmp(token, "coopnet") != 0) {
        LOG_ERROR("Tried to join unrecognized lobby type: %s", token);
        return;
    }

#ifdef COOPNET
    // extract lobby ID
    token = strtok(NULL, ":");
    char* end;
    u64 lobbyId = strtoull(token, &end, 10);

    // extract lobby password
    token = strtok(NULL, ":");
    if (token == NULL) { token = ""; }

    // join
    if (gNetworkType != NT_NONE) {
        network_shutdown(true, false, false, false);
    }
    sQueuedLobbyId = lobbyId;
    snprintf(sQueuedLobbyPassword, 64, "%s", token);
    sQueuedLobby = 2;
#endif
}

static void on_activity_join_request_callback(UNUSED void* data, enum EDiscordResult result) {
    LOG_INFO("> on_activity_join_request_callback returned %d", (int)result);
    DISCORD_REQUIRE(result);
}

static void on_activity_join_request(UNUSED void* data, struct DiscordUser* user) {
    LOG_INFO("> on_activity_join_request from " DISCORD_ID_FORMAT, user->id);
}

static void strncat_len(char* destination, char* source, size_t destinationLength, size_t sourceLength) {
    char altered[128] = { 0 };
    snprintf(altered, (sourceLength < 127) ? sourceLength : 127, "%s", source);
    strncat(destination, altered, destinationLength);
}

static void discord_populate_details(char* buffer, int bufferLength) {
    // get version
    const char* version = get_version();
    int versionLength = strlen(version);
    snprintf(buffer, bufferLength, "%s", version);
    buffer += versionLength;
    bufferLength -= versionLength;

    // get mod strings
    if (gActiveMods.entryCount <= 0) { return; }
    char* strings[gActiveMods.entryCount];
    for (int i = 0; i < gActiveMods.entryCount; i++) {
        strings[i] = gActiveMods.entries[i]->name;
    }

    // add seperator
    snprintf(buffer, bufferLength, "%s", " - ");
    buffer += 3;
    bufferLength -= 3;

    // concat mod strings
    str_seperator_concat(buffer, bufferLength, strings, gActiveMods.entryCount, ", ");
}

void discord_activity_update(void) {
    sCurActivity.type = DiscordActivityType_Playing;

    snprintf(sCurActivity.assets.large_image, 128, "characters");
    snprintf(sCurActivity.assets.large_text, 128, "sm64coopdx Characters");
    snprintf(sCurActivity.assets.small_image, 128, "icon");
    snprintf(sCurActivity.assets.small_text, 128, "sm64coopdx Icon");

    if (gNetworkType != NT_NONE && gNetworkSystem) {
        gNetworkSystem->get_lobby_id(sCurActivity.party.id, 128);
        gNetworkSystem->get_lobby_secret(sCurActivity.secrets.join, 128);
        sCurActivity.party.size.current_size = network_player_connected_count();
        sCurActivity.party.size.max_size = gServerSettings.maxPlayers;
    } else {
        snprintf(sCurActivity.party.id, 128, "%s", "");
        snprintf(sCurActivity.secrets.join, 128, "%s", "");
        sCurActivity.party.size.current_size = 1;
        sCurActivity.party.size.max_size = 1;
    }

    if ((sCurActivity.party.size.current_size > 1 || configAmountOfPlayers == 1) && !gDjuiInMainMenu) {
        strcpy(sCurActivity.state, "Playing!");
    } else if (gNetworkType == NT_SERVER) {
        strcpy(sCurActivity.state, "Waiting for players...");
    } else {
        strcpy(sCurActivity.state, "In the menus.");
        sCurActivity.party.size.current_size = 1;
        if (sCurActivity.party.size.max_size < 1) { sCurActivity.party.size.max_size = 1; }
    }

    // HACK: give the detail population more space than the Discord details can fit so it gets truncated without cutting off the largest strings
    char details[512] = { 0 };
    discord_populate_details(details, 512);
    char* detailsNoColor = str_remove_color_codes(details);

    snprintf(sCurActivity.details, 128, "%s", detailsNoColor);
    free(detailsNoColor);

    if (!app.activities) {
        LOG_INFO("no activities");
        return;
    }

    if (!app.activities->update_activity) {
        LOG_INFO("no update_activity");
        return;
    }

    app.activities->update_activity(app.activities, &sCurActivity, NULL, on_activity_update_callback);
    LOG_INFO("set activity");
}

void discord_activity_update_check(void) {
#ifdef COOPNET
    if (sQueuedLobby > 0) {
        if (--sQueuedLobby == 0) {
            gCoopNetDesiredLobby = sQueuedLobbyId;
            snprintf(gCoopNetPassword, 64, "%s", sQueuedLobbyPassword);
            network_reset_reconnect_and_rehost();
            network_set_system(NS_COOPNET);
            network_init(NT_CLIENT, false);
            djui_panel_join_message_create(NULL);
        }
    }
#endif

    if (gNetworkType == NT_NONE) { return; }
    bool shouldUpdate = false;
    u8 connectedCount = network_player_connected_count();

    if (connectedCount > 0) {
        if (connectedCount != sCurActivity.party.size.current_size) {
            shouldUpdate = true;
        }
    }

    static int updateTimer = 30 * 60;
    if (--updateTimer <= 0) {
        updateTimer = 30 * 60;
        shouldUpdate = true;
    }

    if (shouldUpdate) {
        discord_activity_update();
    }
}

struct IDiscordActivityEvents* discord_activity_initialize(void) {
    static struct IDiscordActivityEvents events = { 0 };
    events.on_activity_join         = on_activity_join;
    events.on_activity_join_request = on_activity_join_request;
    return &events;
}