#include "discord.h"
#include "pc/djui/djui.h"
#include "pc/mods/mods.h"
#include "pc/debuglog.h"
#include "pc/djui/djui_panel_join_message.h"
#ifdef COOPNET
#include "pc/network/coopnet/coopnet.h"
#endif

extern struct DiscordApplication app;
struct DiscordActivity sCurActivity = { 0 };

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
    u64 lobbyId = atoi(token);

    // extract lobby password
    token = strtok(NULL, ":");

    // join
    gCoopNetDesiredLobby = lobbyId;
    snprintf(gCoopNetPassword, 64, "%s", token);
    network_reset_reconnect_and_rehost();
    network_set_system(NS_COOPNET);
    network_init(NT_CLIENT, false);
    djui_panel_join_message_create(NULL);
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

static bool discord_populate_details(char* details, bool shorten) {
    snprintf(details, 127, "%s", get_version());

    bool displayDash = true;
    bool displayComma = false;
    size_t catLength = shorten ? 14 : 64;

    // add mods to activity
    if (gActiveMods.entryCount > 0) {
        for (int i = 0; i < gActiveMods.entryCount; i++) {
            struct Mod* mod = gActiveMods.entries[i];
            if (displayDash) { strncat_len(details, " - ", 127, catLength); }
            if (displayComma) { strncat_len(details, ", ", 127, catLength); }

            strncat_len(details, mod->name, 127, catLength);

            displayDash = false;
            displayComma = true;
        }
    }

    return (strlen(details) >= 125);
}

void discord_activity_update(void) {
    sCurActivity.type = DiscordActivityType_Playing;

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

    if (sCurActivity.party.size.current_size > 1) {
        strcpy(sCurActivity.state, "Playing!");
    } else if (gNetworkType == NT_SERVER) {
        strcpy(sCurActivity.state, "Waiting for players...");
    } else {
        strcpy(sCurActivity.state, "In-game.");
        sCurActivity.party.size.current_size = 1;
        if (sCurActivity.party.size.max_size < 1) { sCurActivity.party.size.max_size = 1; }
    }

    char details[256] = { 0 };
    bool overrun = discord_populate_details(details, false);
    if (overrun) {
        discord_populate_details(details, true);
    }

    if (snprintf(sCurActivity.details, 125, "%s", details) < 0) {
        LOG_INFO("truncating details");
    }

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