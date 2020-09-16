#include <stdio.h>
#include "network.h"
#include "object_fields.h"
#include "object_constants.h"
#include "socket/socket.h"
#include "discord/discord.h"
#include "pc/configfile.h"
#include "pc/debuglog.h"

// Mario 64 specific externs
extern s16 sCurrPlayMode;

enum NetworkType gNetworkType = NT_NONE;
struct NetworkSystem* gNetworkSystem = &gNetworkSystemDiscord;

#define LOADING_LEVEL_THRESHOLD 10
u8 networkLoadingLevel = 0;
bool gNetworkLevelLoaded = false;

struct ServerSettings gServerSettings = {
    .playerInteractions = PLAYER_INTERACTIONS_SOLID,
    .playerKnockbackStrength = 25,
};


void network_set_system(enum NetworkSystemType nsType) {
    switch (nsType) {
        case NS_SOCKET:  gNetworkSystem = &gNetworkSystemSocket; break;
        case NS_DISCORD: gNetworkSystem = &gNetworkSystemDiscord; break;
        default: LOG_ERROR("Unknown network system: %d", nsType);
    }
}

bool network_init(enum NetworkType inNetworkType) {
    // sanity check network system
    if (gNetworkSystem == NULL) {
        LOG_ERROR("no network system attached");
        return false;
    }

    // set server settings
    gServerSettings.playerInteractions = configPlayerInteraction;
    gServerSettings.playerKnockbackStrength = configPlayerKnockbackStrength;
    gServerSettings.stayInLevelAfterStar = configStayInLevelAfterStar;

    // initialize the network system
    int rc = gNetworkSystem->initialize(inNetworkType);
    if (!rc) {
        LOG_ERROR("failed to initialize network system");
        return false;
    }

    // set network type
    gNetworkType = inNetworkType;

    LOG_INFO("initialized");

    return true;
}

void network_on_init_level(void) {
    // reset loading timer
    networkLoadingLevel = 0;
    gNetworkLevelLoaded = false;
}

void network_on_loaded_level(void) {
    // request my chunk of reserved sync ids
    if (gNetworkType == NT_CLIENT) {
        network_send_reservation_request();
    }
}

void network_send(struct Packet* p) {
    // sanity checks
    if (gNetworkType == NT_NONE) { return; }
    if (p->error) { LOG_ERROR("packet error!"); return; }
    if (gNetworkSystem == NULL) { LOG_ERROR("no network system attached"); return; }

    // remember reliable packets
    network_remember_reliable(p);

    // save inside packet buffer
    u32 hash = packet_hash(p);
    memcpy(&p->buffer[p->dataLength], &hash, sizeof(u32));

    // send
    int rc = gNetworkSystem->send(p->buffer, p->cursor + sizeof(u32));
    if (rc != NO_ERROR) { return; }
    p->sent = true;
}

void network_receive(u8* data, u16 dataLength) {
    // receive packet
    struct Packet p = {
        .cursor = 3,
        .buffer = { 0 },
        .dataLength = dataLength,
    };
    memcpy(p.buffer, data, dataLength);

    // subtract and check hash
    p.dataLength -= sizeof(u32);
    if (!packet_check_hash(&p)) {
        LOG_ERROR("invalid packet hash!");
        return;
    }

    // execute packet
    packet_receive(&p);
}

void network_update(void) {

    // check for level loaded event
    if (!gNetworkLevelLoaded) {
        if (networkLoadingLevel++ >= LOADING_LEVEL_THRESHOLD) {
            gNetworkLevelLoaded = true;
            network_on_loaded_level();
        }
    }

    // send out update packets
    if (gNetworkType != NT_NONE) {
        if (sCurrPlayMode == PLAY_MODE_NORMAL || sCurrPlayMode == PLAY_MODE_PAUSED) {
            network_update_player();
            network_update_objects();
        }
    }

    // receive packets
    if (gNetworkSystem != NULL) {
        gNetworkSystem->update();
    }

    // update reliable packets
    if (gNetworkType != NT_NONE) {
        network_update_reliable();
    }
}

void network_shutdown(void) {
    if (gNetworkType == NT_NONE) { return; }

    if (gNetworkSystem == NULL) { LOG_ERROR("no network system attached"); return; }
    gNetworkSystem->shutdown();

    gNetworkType = NT_NONE;
}
