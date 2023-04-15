#include "activity.h"
#include "lobby.h"
#include "discord_network.h"
#include "pc/network/network.h"
#include "pc/network/version.h"
#include "pc/djui/djui.h"
#include "pc/mods/mods.h"
#include "pc/logfile.h"

#define HASH_LENGTH 8
struct DiscordActivity gCurActivity = { 0 };
bool gActivityLock = false;

static void on_activity_update_callback(UNUSED void* data, enum EDiscordResult result) {
    LOGFILE_INFO(LFT_DISCORD, "> on_activity_update_callback returned %d", result);
    DISCORD_REQUIRE(result);
}

static void on_activity_join_callback(UNUSED void* data, enum EDiscordResult result, struct DiscordLobby* lobby) {
    gActivityLock = false;
    LOGFILE_INFO(LFT_DISCORD, "> on_activity_join_callback returned %d, lobby " DISCORD_ID_FORMAT ", owner " DISCORD_ID_FORMAT, result, lobby->id, lobby->owner_id);
    DISCORD_REQUIRE(result);
    if (gNetworkType != NT_NONE) {
        LOGFILE_ERROR(LFT_DISCORD, "Joined lobby when already connected somewhere!");
        return;
    }
    network_reset_reconnect_and_rehost();
    network_init(NT_CLIENT, false);

    gCurActivity.type = DiscordActivityType_Playing;
    if (snprintf(gCurActivity.party.id, 128, DISCORD_ID_FORMAT, lobby->id) < 0) {
        LOGFILE_ERROR(LFT_DISCORD, "Truncating party id");
    }
    gCurActivity.party.size.current_size = 2;
    gCurActivity.party.size.max_size = lobby->capacity;

    gCurLobbyId = lobby->id;

    discord_network_init(lobby->id);
    discord_activity_update(false);

    if (gNetworkPlayerServer == NULL) {
        network_player_connected(NPT_SERVER, 0, 0, &DEFAULT_MARIO_PALETTE, "Player");
    }
    ns_discord_save_id(gNetworkPlayerServer->localIndex, lobby->owner_id);
    network_send_mod_list_request();

    gNetworkUserIds[0] = lobby->owner_id;
}

static void on_activity_join(UNUSED void* data, const char* secret) {
    LOGFILE_INFO(LFT_DISCORD, "> on_activity_join, secret: %s", secret);
    if (gActivityLock) { return; }
    gActivityLock = true;
    djui_connect_menu_open();
    app.lobbies->connect_lobby_with_activity_secret(app.lobbies, (char*)secret, NULL, on_activity_join_callback);
}

static void on_activity_join_request_callback(UNUSED void* data, enum EDiscordResult result) {
    LOGFILE_INFO(LFT_DISCORD, "> on_activity_join_request_callback returned %d", (int)result);
    DISCORD_REQUIRE(result);
}

static void on_activity_join_request(UNUSED void* data, struct DiscordUser* user) {
    LOGFILE_INFO(LFT_DISCORD, "> on_activity_join_request from " DISCORD_ID_FORMAT, user->id);
    //app.activities->send_request_reply(app.activities, user->id, DiscordActivityJoinRequestReply_Yes, NULL, on_activity_join_request_callback);
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

    if (gRegisteredMods.string != NULL) {
        strncat_len(details, " - ", 127, catLength);
        displayDash = false;

        // add patches to activity
        struct StringLinkedList* node = &gRegisteredMods;
        while (node != NULL && node->string != NULL) {
            if (displayComma) { strncat_len(details, ", ", 127, catLength); }
            strncat_len(details, node->string, 127, catLength);
            displayComma = true;
            node = node->next;
        }
    }

    if (gActiveMods.entryCount > 0) {
        // add mods to activity
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

void discord_activity_update(bool hosting) {
    gCurActivity.type = DiscordActivityType_Playing;
    if (gCurActivity.party.size.current_size > 1) {
        strcpy(gCurActivity.state, "Playing!");
    } else if (hosting) {
        strcpy(gCurActivity.state, "Waiting for players...");
    } else {
        strcpy(gCurActivity.state, "In-game.");
        gCurActivity.party.size.current_size = 1;
        if (gCurActivity.party.size.max_size < 1) { gCurActivity.party.size.max_size = 1; }
    }

    char details[256] = { 0 };
    bool overrun = discord_populate_details(details, false);
    if (overrun) {
        discord_populate_details(details, true);
    }

    if (snprintf(gCurActivity.details, 125, "%s", details) < 0) {
        LOGFILE_INFO(LFT_DISCORD, "truncating details");
    }

    if (!app.activities) {
        LOGFILE_INFO(LFT_DISCORD, "no activities");
        return;
    }

    if (!app.activities->update_activity) {
        LOGFILE_INFO(LFT_DISCORD, "no update_activity");
        return;
    }

    app.activities->update_activity(app.activities, &gCurActivity, NULL, on_activity_update_callback);
    LOGFILE_INFO(LFT_DISCORD, "set activity");
}

void discord_activity_update_check(void) {
    if (gNetworkType == NT_NONE) { return; }
    bool shouldUpdate = false;
    u8 connectedCount = network_player_connected_count();

    if (connectedCount > 0) {
        if (connectedCount != gCurActivity.party.size.current_size) {
            gCurActivity.party.size.current_size = connectedCount;
            shouldUpdate = true;
        }
    }

    if (shouldUpdate) {
        discord_activity_update(gNetworkType == NT_SERVER);
    }
}

struct IDiscordActivityEvents* discord_activity_initialize(void) {
    static struct IDiscordActivityEvents events = { 0 };
    events.on_activity_join         = on_activity_join;
    events.on_activity_join_request = on_activity_join_request;
    return &events;
}