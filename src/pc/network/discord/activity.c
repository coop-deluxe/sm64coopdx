#include "activity.h"
#include "lobby.h"
#include "discord_network.h"
#include "pc/network/network.h"
#include "pc/network/version.h"
#include "pc/djui/djui.h"
#include "pc/logfile.h"

#define HASH_LENGTH 8
struct DiscordActivity gCurActivity = { 0 };

static void on_activity_update_callback(UNUSED void* data, enum EDiscordResult result) {
    LOGFILE_INFO(LFT_DISCORD, "> on_activity_update_callback returned %d", result);
    DISCORD_REQUIRE(result);
}

static void on_activity_join_callback(UNUSED void* data, enum EDiscordResult result, struct DiscordLobby* lobby) {
    LOGFILE_INFO(LFT_DISCORD, "> on_activity_join_callback returned %d, lobby %lld, owner %lld", result, lobby->id, lobby->owner_id);
    DISCORD_REQUIRE(result);
    if (gNetworkType != NT_NONE) {
        LOGFILE_ERROR(LFT_DISCORD, "Joined lobby when already connected somewhere!");
        exit(0);
        return;
    }
    network_init(NT_CLIENT);

    gCurActivity.type = DiscordActivityType_Playing;
    snprintf(gCurActivity.party.id, 128, "%lld", lobby->id);
    gCurActivity.party.size.current_size = 2;
    gCurActivity.party.size.max_size = lobby->capacity;

    gCurLobbyId = lobby->id;

    discord_network_init(lobby->id);
    discord_activity_update(false);

    if (gNetworkType == NT_CLIENT) {
        if (gNetworkPlayerServer == NULL) {
            network_player_connected(NPT_SERVER, 0, 0, 0, "Player");
        }
        ns_discord_save_id(gNetworkPlayerServer->localIndex, lobby->owner_id);
        network_send_join_request();
    }

    gNetworkUserIds[0] = lobby->owner_id;
}

static void on_activity_join(UNUSED void* data, const char* secret) {
    LOGFILE_INFO(LFT_DISCORD, "> on_activity_join, secret: %s", secret);
    djui_connect_menu_open();
    app.lobbies->connect_lobby_with_activity_secret(app.lobbies, (char*)secret, NULL, on_activity_join_callback);
}

static void on_activity_join_request_callback(UNUSED void* data, enum EDiscordResult result) {
    LOGFILE_INFO(LFT_DISCORD, "> on_activity_join_request_callback returned %d", (int)result);
    DISCORD_REQUIRE(result);
}

static void on_activity_join_request(UNUSED void* data, struct DiscordUser* user) {
    LOGFILE_INFO(LFT_DISCORD, "> on_activity_join_request from %lld", user->id);
    //app.activities->send_request_reply(app.activities, user->id, DiscordActivityJoinRequestReply_Yes, NULL, on_activity_join_request_callback);
}

void discord_activity_update(bool hosting) {
    gCurActivity.type = DiscordActivityType_Playing;
    if (gCurActivity.party.size.current_size > 1) {
        strcpy(gCurActivity.state, "Playing!");
    } else if (hosting) {
        strcpy(gCurActivity.state, "Waiting for player...");
    } else {
        strcpy(gCurActivity.state, "In-game.");
        gCurActivity.party.size.current_size = 1;
        gCurActivity.party.size.max_size = 1;
    }

    if (gCurActivity.details[0] == '\0') {
        snprintf(gCurActivity.details, 128, "%s", get_version());
        if (gRegisteredMods.string != NULL) {
            strncat(gCurActivity.details, " - ", 127);
            struct StringLinkedList* node = &gRegisteredMods;
            while (node != NULL && node->string != NULL) {
                strncat(gCurActivity.details, node->string, 127);
                node = node->next;
                if (node != NULL && node->string != NULL) {
                    strncat(gCurActivity.details, ", ", 127);
                }
            }
        }
    }

    app.activities->update_activity(app.activities, &gCurActivity, NULL, on_activity_update_callback);
    LOGFILE_INFO(LFT_DISCORD, "set activity");
}

struct IDiscordActivityEvents* discord_activity_initialize(void) {
    static struct IDiscordActivityEvents events = { 0 };
    events.on_activity_join         = on_activity_join;
    events.on_activity_join_request = on_activity_join_request;
    return &events;
}