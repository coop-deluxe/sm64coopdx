#include "discord_network.h"
#include "lobby.h"
#include "pc/debuglog.h"

int ns_discord_network_send(u8* data, u16 dataLength) {
    if (!gDiscordInitialized) { return 1; }
    if (gCurLobbyId == 0) { return 2; }
    int32_t memberCount = 0;
    DISCORD_REQUIRE(app.lobbies->member_count(app.lobbies, gCurLobbyId, &memberCount));
    if (memberCount <= 1) { return 3; }

    for (int i = 0; i < memberCount; i++) {
        DiscordUserId userId;
        DISCORD_REQUIRE(app.lobbies->get_member_user_id(app.lobbies, gCurLobbyId, i, &userId));
        if (userId == app.userId) { continue; }
        DISCORD_REQUIRE(app.lobbies->send_network_message(app.lobbies, gCurLobbyId, userId, 0, data, dataLength));
    }
    return 0;
}

void discord_network_on_message(UNUSED void* eventData, int64_t lobbyId, int64_t userId, uint8_t channelId, uint8_t* data, uint32_t dataLength) {
    network_receive((u8*)data, (u16)dataLength);
}

void discord_network_flush(void) {
    app.lobbies->flush_network(app.lobbies);
}

void discord_network_init(int64_t lobbyId) {
    DISCORD_REQUIRE(app.lobbies->connect_network(app.lobbies, lobbyId));
    DISCORD_REQUIRE(app.lobbies->open_network_channel(app.lobbies, lobbyId, 0, false));
}

void discord_network_shutdown(void) {
    app.lobbies->flush_network(app.lobbies);
    if (gCurLobbyId == 0) { return; }
    app.lobbies->disconnect_network(app.lobbies, gCurLobbyId);
    LOG_INFO("shutdown network, lobby = %lld", gCurLobbyId);
}