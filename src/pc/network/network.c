#include <stdio.h>
#include "network.h"
#include "object_fields.h"
#include "object_constants.h"
#include "game/object_list_processor.h"
#include "behavior_table.h"
#include "socket/socket.h"
#ifdef DISCORD_SDK
#include "discord/discord.h"
#endif
#include "pc/configfile.h"
#include "pc/debuglog.h"

// Mario 64 specific externs
extern s16 sCurrPlayMode;
extern s16 gCurrCourseNum, gCurrActStarNum, gCurrLevelNum, gCurrAreaIndex;

enum NetworkType gNetworkType = NT_NONE;
#ifdef DISCORD_SDK
struct NetworkSystem* gNetworkSystem = &gNetworkSystemDiscord;
#else
struct NetworkSystem* gNetworkSystem = &gNetworkSystemSocket;
#endif

#define LOADING_LEVEL_THRESHOLD 10

u16 networkLoadingLevel = 0;
bool gNetworkAreaLoaded = false;
bool gNetworkAreaSyncing = true;
u32  gNetworkAreaTimer = 0;

clock_t gLastNetworkSend = 0;
struct StringLinkedList gRegisteredMods = { 0 };

struct ServerSettings gServerSettings = {
    .playerInteractions = PLAYER_INTERACTIONS_SOLID,
    .playerKnockbackStrength = 25,
    .skipIntro = 0,
    .shareLives = 0,
};

void network_set_system(enum NetworkSystemType nsType) {
    switch (nsType) {
        case NS_SOCKET:  gNetworkSystem = &gNetworkSystemSocket; break;
#ifdef DISCORD_SDK
        case NS_DISCORD: gNetworkSystem = &gNetworkSystemDiscord; break;
#endif
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
    gServerSettings.skipIntro = configSkipIntro;
    gServerSettings.shareLives = configShareLives;

    // initialize the network system
    int rc = gNetworkSystem->initialize(inNetworkType);
    if (!rc) {
        LOG_ERROR("failed to initialize network system");
        return false;
    }

    // set network type
    gNetworkType = inNetworkType;

    if (gNetworkType == NT_SERVER) {
        network_player_connected(NPT_LOCAL, 0);
        extern u8* gOverrideEeprom;
        gOverrideEeprom = NULL;
    } else if (gNetworkType == NT_CLIENT) {
        network_player_connected(NPT_SERVER, 0);
    }

    LOG_INFO("initialized");

    return true;
}

void network_on_init_area(void) {
    // reset loading timer
    networkLoadingLevel = 0;
    gNetworkAreaLoaded = false;
    gNetworkAreaSyncing = true;
    gNetworkAreaTimer = 0;
}

void network_on_loaded_area(void) {
    area_remove_sync_ids_clear();
    struct NetworkPlayer* np = gNetworkPlayerLocal;
    if (np != NULL) {
        bool levelMatch = (np->currCourseNum == gCurrCourseNum
                           && np->currActNum == gCurrActStarNum
                           && np->currLevelNum == gCurrLevelNum);
        if (np->currLevelSyncValid && levelMatch && np->currAreaIndex != gCurrAreaIndex) {
            network_send_change_area();
        } else {
            network_send_change_level();
        }
    }
}

void network_send_to(u8 localIndex, struct Packet* p) {
    // sanity checks
    if (gNetworkType == NT_NONE) { LOG_ERROR("network type error none!"); return; }
    if (p->error) { LOG_ERROR("packet error!"); return; }
    if (gNetworkSystem == NULL) { LOG_ERROR("no network system attached"); return; }
    if (p->buffer[0] != PACKET_JOIN_REQUEST && p->buffer[0] != PACKET_KICK && p->buffer[0] != PACKET_ACK && gNetworkPlayerLocal != NULL && gNetworkPlayerServer->localIndex != gNetworkPlayerLocal->localIndex) {
        assert(localIndex != gNetworkPlayerLocal->localIndex);
    }

    if (gNetworkType == NT_SERVER) {
        struct NetworkPlayer* np = &gNetworkPlayers[localIndex];
        // don't send a packet to a player that can't receive it
        if (p->levelAreaMustMatch) {
            if (p->courseNum != np->currCourseNum) { return; }
            if (p->actNum    != np->currActNum)    { return; }
            if (p->levelNum  != np->currLevelNum)  { return; }
            if (p->areaIndex != np->currAreaIndex) { return; }
        }
    }

    // set the flags again
    packet_set_flags(p);

    // set destination
    packet_set_destination(p, p->requestBroadcast
                              ? PACKET_DESTINATION_BROADCAST
                              : gNetworkPlayers[(localIndex == 0) ? p->localIndex : localIndex].globalIndex);

    p->localIndex = localIndex;

    // remember reliable packets
    network_remember_reliable(p);

    // set ordered data (MUST BE IMMEDITAELY BEFORE HASING+SENDING)
    if (p->orderedGroupId != 0) {
        packet_set_ordered_data(p);
    }

    // save inside packet buffer
    u32 hash = packet_hash(p);
    memcpy(&p->buffer[p->dataLength], &hash, sizeof(u32));

    // redirect to server if required
    if (localIndex != 0 && gNetworkType != NT_SERVER && gNetworkSystem->requireServerBroadcast) {
        localIndex = gNetworkPlayerServer->localIndex;
    }

    // send
    int rc = gNetworkSystem->send(localIndex, p->buffer, p->cursor + sizeof(u32));
    if (rc == SOCKET_ERROR) { LOG_ERROR("send error %d", rc); return; }
    p->sent = true;

    gLastNetworkSend = clock();
}

void network_send(struct Packet* p) {
    // set the flags again
    packet_set_flags(p);

    if (gNetworkType != NT_SERVER) {
        p->requestBroadcast = TRUE;
        if (gNetworkSystem != NULL && gNetworkSystem->requireServerBroadcast && gNetworkPlayerServer != NULL) {
            int i = gNetworkPlayerServer->localIndex;
            p->localIndex = i;
            network_send_to(i, p);
            gLastNetworkSend = clock();
            return;
        }
    }

    for (int i = 1; i < MAX_PLAYERS; i++) {
        struct NetworkPlayer* np = &gNetworkPlayers[i];
        if (!np->connected) { continue; }

        // don't send a packet to a player that can't receive it
        if (p->levelAreaMustMatch) {
            if (p->courseNum != np->currCourseNum) { continue; }
            if (p->actNum    != np->currActNum)    { continue; }
            if (p->levelNum  != np->currLevelNum)  { continue; }
            if (p->areaIndex != np->currAreaIndex) { continue; }
        }

        p->localIndex = i;
        network_send_to(i, p);
    }
    gLastNetworkSend = clock();
}

void network_receive(u8 localIndex, u8* data, u16 dataLength) {
    // receive packet
    struct Packet p = {
        .localIndex = localIndex,
        .cursor = 3,
        .buffer = { 0 },
        .dataLength = dataLength,
    };
    memcpy(p.buffer, data, dataLength);

    if (localIndex != UNKNOWN_LOCAL_INDEX && localIndex != 0) {
        gNetworkPlayers[localIndex].lastReceived = clock();
    }

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
    if (networkLoadingLevel < LOADING_LEVEL_THRESHOLD) {
        networkLoadingLevel++;
        if (!gNetworkAreaLoaded && networkLoadingLevel >= LOADING_LEVEL_THRESHOLD) {
            gNetworkAreaLoaded = true;
            gNetworkAreaTimer = 0;
            network_on_loaded_area();
        }
    } else if (gNetworkAreaLoaded) {
        gNetworkAreaTimer++;
    }

    // send out update packets
    if (gNetworkType != NT_NONE && network_player_any_connected()) {
        network_player_update();
        if (sCurrPlayMode == PLAY_MODE_NORMAL || sCurrPlayMode == PLAY_MODE_PAUSED) {
            network_update_player();
            network_update_objects();
        }
    }

    // receive packets
    if (gNetworkSystem != NULL) {
        gNetworkSystem->update();
    }

    // update reliable and ordered packets
    if (gNetworkType != NT_NONE) {
        network_update_reliable();
        packet_ordered_update();
    }
}

void network_register_mod(char* modName) {
    if (string_linked_list_contains(&gRegisteredMods, modName)) { return; }
    string_linked_list_append(&gRegisteredMods, modName);
}

void network_shutdown(void) {
    network_forget_all_reliable();
    if (gNetworkType == NT_NONE) { return; }
    if (gNetworkSystem == NULL) { LOG_ERROR("no network system attached"); return; }

    if (gNetworkPlayerLocal != NULL) { network_send_leaving(gNetworkPlayerLocal->globalIndex); }
    network_player_shutdown();
    gNetworkSystem->shutdown();

    gNetworkType = NT_NONE;
}
