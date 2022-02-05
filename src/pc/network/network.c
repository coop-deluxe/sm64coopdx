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
#include "pc/cheats.h"
#include "pc/djui/djui.h"
#include "pc/utils/misc.h"
#include "pc/lua/smlua.h"
#include "pc/mod_list.h"
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
#define MAX_PACKETS_PER_SECOND_PER_PLAYER ((u16)70)

u16 networkLoadingLevel = 0;
bool gNetworkAreaLoaded = false;
bool gNetworkAreaSyncing = true;
u32 gNetworkAreaTimerClock = 0;
u32 gNetworkAreaTimer = 0;
void* gNetworkServerAddr = NULL;
bool gNetworkSentJoin = false;

struct StringLinkedList gRegisteredMods = { 0 };

struct ServerSettings gServerSettings = {
    .playerInteractions = PLAYER_INTERACTIONS_SOLID,
    .playerKnockbackStrength = 25,
    .skipIntro = 0,
    .shareLives = 0,
    .enableCheats = 0,
    .bubbleDeath = 1,
    .headlessServer = 0,
};

void network_set_system(enum NetworkSystemType nsType) {
    network_forget_all_reliable();
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
    gServerSettings.enableCheats = configEnableCheats;
    gServerSettings.bubbleDeath = configBubbleDeath;
#if defined(RAPI_DUMMY) || defined(WAPI_DUMMY)
    gServerSettings.headlessServer = (inNetworkType == NT_SERVER);
#else
    gServerSettings.headlessServer = 0;
#endif
    Cheats.EnableCheats = gServerSettings.enableCheats;

    // initialize the network system
    gNetworkSentJoin = false;
    int rc = gNetworkSystem->initialize(inNetworkType);
    if (!rc) {
        LOG_ERROR("failed to initialize network system");
        return false;
    }
    if (gNetworkServerAddr != NULL) {
        free(gNetworkServerAddr);
        gNetworkServerAddr = NULL;
    }

    // set network type
    gNetworkType = inNetworkType;

    if (gNetworkType == NT_SERVER) {
        smlua_init();

        network_player_connected(NPT_LOCAL, 0, configPlayerModel, configPlayerPalette, configPlayerName);
        extern u8* gOverrideEeprom;
        gOverrideEeprom = NULL;

        djui_chat_box_create();
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
    gNetworkAreaTimerClock = clock_elapsed_ticks();
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

bool network_allow_unknown_local_index(enum PacketType packetType) {
    return (packetType == PACKET_JOIN_REQUEST)
        || (packetType == PACKET_KICK)
        || (packetType == PACKET_ACK)
        || (packetType == PACKET_MOD_LIST_REQUEST)
        || (packetType == PACKET_MOD_LIST)
        || (packetType == PACKET_DOWNLOAD_REQUEST)
        || (packetType == PACKET_DOWNLOAD)
        || (packetType == PACKET_KEEP_ALIVE)
        || (packetType == PACKET_DEBUG_SYNC);
}

void network_send_to(u8 localIndex, struct Packet* p) {
    // sanity checks
    if (gNetworkType == NT_NONE) { LOG_ERROR("network type error none!"); return; }
    if (p->error) { LOG_ERROR("packet error!"); return; }
    if (gNetworkSystem == NULL) { LOG_ERROR("no network system attached"); return; }
    if (localIndex == 0 && !network_allow_unknown_local_index(p->buffer[0])) {
        LOG_ERROR("\n####################\nsending to myself, packetType: %d\n####################\n", p->packetType);
        SOFT_ASSERT(false);
        return;
    }

    if (gNetworkType == NT_SERVER) {
        struct NetworkPlayer* np = &gNetworkPlayers[localIndex];
        // don't send a packet to a player that can't receive it
        if (p->levelAreaMustMatch) {
            if (p->courseNum != np->currCourseNum) { return; }
            if (p->actNum    != np->currActNum)    { return; }
            if (p->levelNum  != np->currLevelNum)  { return; }
            if (p->areaIndex != np->currAreaIndex) { return; }
        } else if (p->levelMustMatch) {
            if (p->courseNum != np->currCourseNum) { return; }
            if (p->actNum    != np->currActNum)    { return; }
            if (p->levelNum  != np->currLevelNum)  { return; }
        }
    }

    // set the flags again
    packet_set_flags(p);

    // set destination
    packet_set_destination(p, p->requestBroadcast
                              ? PACKET_DESTINATION_BROADCAST
                              : gNetworkPlayers[(localIndex == 0) ? p->localIndex : localIndex].globalIndex);

    p->localIndex = localIndex;

    // set ordered data (MUST BE IMMEDITAELY BEFORE network_remember_reliable())
    if (p->orderedGroupId != 0 && !p->sent) {
        packet_set_ordered_data(p);
    }

    // remember reliable packets
    network_remember_reliable(p);

    // save inside packet buffer
    u32 hash = packet_hash(p);
    memcpy(&p->buffer[p->dataLength], &hash, sizeof(u32));

    // redirect to server if required
    if (localIndex != 0 && gNetworkType != NT_SERVER && gNetworkSystem->requireServerBroadcast) {
        localIndex = gNetworkPlayerServer->localIndex;
    }

    SOFT_ASSERT(p->dataLength < PACKET_LENGTH);

    // rate limit packets
    bool tooManyPackets = false;
    int maxPacketsPerSecond = (gNetworkType == NT_SERVER) ? (MAX_PACKETS_PER_SECOND_PER_PLAYER * (u16)network_player_connected_count()) : MAX_PACKETS_PER_SECOND_PER_PLAYER;
    static int sPacketsPerSecond[MAX_PLAYERS] = { 0 };
    static f32 sPacketsPerSecondTime[MAX_PLAYERS] = { 0 };
    f32 currentTime = clock_elapsed();
    if ((currentTime - sPacketsPerSecondTime[localIndex]) > 0) {
        if (sPacketsPerSecond[localIndex] > maxPacketsPerSecond) {
            LOG_ERROR("Too many packets sent to localIndex %d! Attempted %d. Connected count %d.", localIndex, sPacketsPerSecond[localIndex], network_player_connected_count());
        }
        sPacketsPerSecondTime[localIndex] = currentTime;
        sPacketsPerSecond[localIndex] = 1;
    } else {
        sPacketsPerSecond[localIndex]++;
        if (sPacketsPerSecond[localIndex] > maxPacketsPerSecond) {
            tooManyPackets = true;
        }
    }

    // send
    if (!tooManyPackets) {
        int rc = gNetworkSystem->send(localIndex, p->addr, p->buffer, p->cursor + sizeof(u32));
        if (rc == SOCKET_ERROR) { LOG_ERROR("send error %d", rc); return; }
    }
    p->sent = true;

    gNetworkPlayers[localIndex].lastSent = clock_elapsed();
}

void network_send(struct Packet* p) {
    // prevent errors during writing from propagating
    if (p->writeError) { return; }

    // set the flags again
    packet_set_flags(p);

    if (gNetworkType != NT_SERVER) {
        p->requestBroadcast = TRUE;
        if (gNetworkSystem != NULL && gNetworkSystem->requireServerBroadcast && gNetworkPlayerServer != NULL) {
            int i = gNetworkPlayerServer->localIndex;
            p->localIndex = i;
            network_send_to(i, p);
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
        } else if (p->levelMustMatch) {
            if (p->courseNum != np->currCourseNum) { continue; }
            if (p->actNum    != np->currActNum)    { continue; }
            if (p->levelNum  != np->currLevelNum)  { continue; }
        }

        p->localIndex = i;
        network_send_to(i, p);
    }
}

void network_receive(u8 localIndex, void* addr, u8* data, u16 dataLength) {
    // receive packet
    struct Packet p = {
        .localIndex = localIndex,
        .cursor = 3,
        .addr = addr,
        .buffer = { 0 },
        .dataLength = dataLength,
    };
    memcpy(p.buffer, data, dataLength);

    if (localIndex != UNKNOWN_LOCAL_INDEX && localIndex != 0) {
        gNetworkPlayers[localIndex].lastReceived = clock_elapsed();
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

void* network_duplicate_address(u8 localIndex) {
    assert(localIndex < MAX_PLAYERS);
    return gNetworkSystem->dup_addr(localIndex);
}

static void network_update_area_timer(void) {
    bool brokenClock = false;
#ifdef DEVELOPMENT
    static u16 skipClockCount = 0;
    static u16 updateClockCount = 1;
    if (updateClockCount > 0) {
        updateClockCount--;
        if (updateClockCount <= 0 || updateClockCount > 120) {
            skipClockCount = rand() % 30;
        }
    }
    else {
        skipClockCount--;
        if (skipClockCount <= 0 || skipClockCount > 60) {
            updateClockCount = rand() % 120;
        }
    }
    //brokenClock = (skipClockCount > 0);
#endif
    if (!brokenClock) {
        // update network area timer
        u32 desiredNAT = gNetworkAreaTimer + 1;
        gNetworkAreaTimer = (clock_elapsed_ticks() - gNetworkAreaTimerClock);
        if (gNetworkAreaTimer < desiredNAT) {
            gNetworkAreaTimer++;
        }
        else if (gNetworkAreaTimer > desiredNAT) {
            gNetworkAreaTimer--;
        }
    }
}

void network_update(void) {
    // check for level loaded event
    if (networkLoadingLevel < LOADING_LEVEL_THRESHOLD) {
        networkLoadingLevel++;
        if (!gNetworkAreaLoaded && networkLoadingLevel >= LOADING_LEVEL_THRESHOLD) {
            gNetworkAreaLoaded = true;
            network_on_loaded_area();
        }
    }

    // update network area timer
    network_update_area_timer();

    // send out update packets
    if (gNetworkType != NT_NONE) {
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

void network_shutdown(bool sendLeaving) {
    if (gDjuiChatBox != NULL) {
        djui_base_destroy(&gDjuiChatBox->base);
        gDjuiChatBox = NULL;
    }

    gNetworkSentJoin = false;

    network_forget_all_reliable();
    if (gNetworkType == NT_NONE) { return; }
    if (gNetworkSystem == NULL) { LOG_ERROR("no network system attached"); return; }

    if (gNetworkPlayerLocal != NULL && sendLeaving) { network_send_leaving(gNetworkPlayerLocal->globalIndex); }
    network_player_shutdown();
    gNetworkSystem->shutdown();

    if (gNetworkServerAddr != NULL) {
        free(gNetworkServerAddr);
        gNetworkServerAddr = NULL;
    }

    gNetworkType = NT_NONE;
}
