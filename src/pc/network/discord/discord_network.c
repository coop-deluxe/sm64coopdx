#include "discord_network.h"
#include "lobby.h"
#include "pc/logfile.h"

int64_t gNetworkUserIds[MAX_PLAYERS] = { 0 };

u8 discord_user_id_to_local_index(int64_t userId) {
    for (int i = 1; i < MAX_PLAYERS; i++) {
        if (gNetworkPlayers[i].connected && gNetworkUserIds[i] == userId) {
            return i;
        }
    }
    return UNKNOWN_LOCAL_INDEX;
}

int ns_discord_network_send(u8 localIndex, void* address, u8* data, u16 dataLength) {
    if (!gDiscordInitialized) { return 1; }
    if (gCurLobbyId == 0) { return 2; }
    DiscordUserId userId = gNetworkUserIds[localIndex];
    if (localIndex == 0 && address != NULL) { userId = *(DiscordUserId*)address; }
    DISCORD_REQUIRE(app.lobbies->send_network_message(app.lobbies, gCurLobbyId, userId, 0, data, dataLength));
    return 0;
}

void discord_network_on_message(UNUSED void* eventData, UNUSED int64_t lobbyId, int64_t userId, UNUSED uint8_t channelId, uint8_t* data, uint32_t dataLength) {
    gNetworkUserIds[0] = userId;

    u8 localIndex = UNKNOWN_LOCAL_INDEX;
    for (int i = 1; i < MAX_PLAYERS; i++) {
        if (gNetworkUserIds[i] == userId) {
            localIndex = i;
            break;
        }
    }

    network_receive(localIndex, &userId, (u8*)data, (u16)dataLength);
}

void discord_network_flush(void) {
    app.lobbies->flush_network(app.lobbies);
}

s64 ns_discord_get_id(u8 localId) {
    if (localId == 0) { return app.userId; }
    return gNetworkUserIds[localId];
}

char* ns_discord_get_id_str(u8 localId) {
    static char id_str[22] = { 0 };
    if (localId == UNKNOWN_LOCAL_INDEX) {
        snprintf(id_str, 22, "???");
    } else {
        snprintf(id_str, 22, "%lld", (long long int)ns_discord_get_id(localId));
    }
    return id_str;
}

void ns_discord_save_id(u8 localId, s64 networkId) {
    SOFT_ASSERT(localId > 0);
    SOFT_ASSERT(localId < MAX_PLAYERS);
    gNetworkUserIds[localId] = (networkId == 0) ? gNetworkUserIds[0] : networkId;
    LOGFILE_INFO(LFT_DISCORD, "saved user id %d == " DISCORD_ID_FORMAT, localId, gNetworkUserIds[localId]);
}

void ns_discord_clear_id(u8 localId) {
    if (localId == 0) { return; }
    SOFT_ASSERT(localId < MAX_PLAYERS);
    gNetworkUserIds[localId] = 0;
    LOGFILE_INFO(LFT_DISCORD, "cleared user id %d == " DISCORD_ID_FORMAT, localId, gNetworkUserIds[localId]);
}

void discord_network_init(int64_t lobbyId) {
    DISCORD_REQUIRE(app.lobbies->connect_network(app.lobbies, lobbyId));
    DISCORD_REQUIRE(app.lobbies->open_network_channel(app.lobbies, lobbyId, 0, false));
    LOGFILE_INFO(LFT_DISCORD, "network initialized");
}

void discord_network_shutdown(void) {
    if (gCurLobbyId == 0) { return; }
    app.lobbies->flush_network(app.lobbies);
    app.lobbies->disconnect_network(app.lobbies, gCurLobbyId);
    app.lobbies->flush_network(app.lobbies);
    LOGFILE_INFO(LFT_DISCORD, "shutdown network, lobby = " DISCORD_ID_FORMAT, gCurLobbyId);
}