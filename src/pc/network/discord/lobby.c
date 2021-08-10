#include "lobby.h"
#include "activity.h"
#include "discord_network.h"
#include "pc/logfile.h"
#include "pc/utils/misc.h"

#define MAX_LOBBY_RETRY 5
#define MAX_LOBBY_RETRY_WAIT_TIME 6

static bool isHosting = false;
DiscordLobbyId gCurLobbyId = 0;

bool gLobbyCreateRetry = false;
u8 gLobbyCreateAttempts = 0;
f32 gLobbyCreateAttemptElapsed = 0;

void discord_lobby_update(void) {
    if (gCurLobbyId != 0) { return; }
    if (!gLobbyCreateRetry) { return; }
    f32 timeUntilRetry = (clock_elapsed() - gLobbyCreateAttemptElapsed);
    if (timeUntilRetry < MAX_LOBBY_RETRY_WAIT_TIME) { return; }
    gLobbyCreateRetry = false;
    discord_lobby_create();
}

static void on_lobby_create_callback(UNUSED void* data, enum EDiscordResult result, struct DiscordLobby* lobby) {
    LOGFILE_INFO(LFT_DISCORD, "> on_lobby_create returned %d", (int)result);

    if (result != DiscordResult_Ok && gLobbyCreateAttempts < MAX_LOBBY_RETRY) {
        LOGFILE_INFO(LFT_DISCORD, "rescheduling lobby creation");
        gLobbyCreateRetry = true;
        gLobbyCreateAttempts++;
        gLobbyCreateAttemptElapsed = clock_elapsed();
        return;
    }

    DISCORD_REQUIRE(result);
    LOGFILE_INFO(LFT_DISCORD, "Lobby id: %lld", lobby->id);
    LOGFILE_INFO(LFT_DISCORD, "Lobby type: %u", lobby->type);
    LOGFILE_INFO(LFT_DISCORD, "Lobby owner id: %lld", lobby->owner_id);
    LOGFILE_INFO(LFT_DISCORD, "Lobby secret: %s", lobby->secret);
    LOGFILE_INFO(LFT_DISCORD, "Lobby capacity: %u", lobby->capacity);
    LOGFILE_INFO(LFT_DISCORD, "Lobby locked: %d", lobby->locked);

    gCurActivity.type = DiscordActivityType_Playing;
    snprintf(gCurActivity.party.id, 128, "%lld", lobby->id);
    gCurActivity.party.size.current_size = 1;
    gCurActivity.party.size.max_size = MAX_PLAYERS;

    char secretJoin[128] = "";
    snprintf(secretJoin, 128, "%lld:%s", lobby->id, lobby->secret);
    strcpy(gCurActivity.secrets.join, secretJoin);

    isHosting = true;
    gCurLobbyId = lobby->id;

    discord_network_init(lobby->id);
    discord_activity_update(true);
}

static void on_lobby_update(UNUSED void* data, int64_t lobbyId) {
    LOGFILE_INFO(LFT_DISCORD, "> on_lobby_update id: %lld", lobbyId);
}

static void on_member_connect(UNUSED void* data, int64_t lobbyId, int64_t userId) {
    LOGFILE_INFO(LFT_DISCORD, "> on_member_connect lobby: %lld, user: %lld", lobbyId, userId);
    gCurActivity.party.size.current_size++;
    discord_activity_update(true);
}

static void on_member_update(UNUSED void* data, int64_t lobbyId, int64_t userId) {
    LOGFILE_INFO(LFT_DISCORD, "> on_member_update lobby: %lld, user: %lld", lobbyId, userId);
}

static void on_member_disconnect(UNUSED void* data, int64_t lobbyId, int64_t userId) {
    LOGFILE_INFO(LFT_DISCORD, "> on_member_disconnect lobby: %lld, user: %lld", lobbyId, userId);
    u8 localIndex = discord_user_id_to_local_index(userId);
    if (localIndex != UNKNOWN_LOCAL_INDEX && gNetworkPlayers[localIndex].connected) {
        network_player_disconnected(gNetworkPlayers[localIndex].globalIndex);
    }
    gCurActivity.party.size.current_size--;
    discord_activity_update(isHosting);
}

void discord_lobby_create(void) {
    struct IDiscordLobbyTransaction* txn = { 0 };

    DISCORD_REQUIRE(app.lobbies->get_lobby_create_transaction(app.lobbies, &txn));
    txn->set_capacity(txn, MAX_PLAYERS);
    txn->set_type(txn, DiscordLobbyType_Public);
    //txn->set_metadata(txn, "a", "123");

    app.lobbies->create_lobby(app.lobbies, txn, NULL, on_lobby_create_callback);
}

static void on_lobby_leave_callback(UNUSED void* data, enum EDiscordResult result) {
    LOGFILE_INFO(LFT_DISCORD, "> on_lobby_leave returned %d", result);
    DISCORD_REQUIRE(result);
}

void discord_lobby_leave(void) {
    if (gCurLobbyId == 0) { return; }

    discord_network_shutdown();
    if (isHosting) {
        app.lobbies->delete_lobby(app.lobbies, gCurLobbyId, NULL, on_lobby_leave_callback);
    } else {
        app.lobbies->disconnect_lobby(app.lobbies, gCurLobbyId, NULL, on_lobby_leave_callback);
    }

    LOGFILE_INFO(LFT_DISCORD, "left lobby %lld", gCurLobbyId);

    isHosting = false;
    gCurLobbyId = 0;
}

struct IDiscordLobbyEvents* discord_lobby_initialize(void) {
    static struct IDiscordLobbyEvents events = { 0 };
    events.on_lobby_update      = on_lobby_update;
    events.on_member_connect    = on_member_connect;
    events.on_member_update     = on_member_update;
    events.on_member_disconnect = on_member_disconnect;
    events.on_network_message   = discord_network_on_message;
    return &events;
}
