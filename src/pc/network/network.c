#include "socket/socket.h"
#include "coopnet/coopnet.h"
#include <stdio.h>
#include "network.h"
#include "object_fields.h"
#include "game/level_update.h"
#include "object_constants.h"
#include "behavior_table.h"
#include "pc/configfile.h"
#include "pc/djui/djui.h"
#include "pc/djui/djui_panel.h"
#include "pc/djui/djui_hud_utils.h"
#include "pc/djui/djui_panel_main.h"
#include "pc/utils/misc.h"
#include "pc/lua/smlua.h"
#include "pc/lua/utils/smlua_model_utils.h"
#include "pc/lua/utils/smlua_misc_utils.h"
#include "pc/lua/utils/smlua_camera_utils.h"
#include "pc/mods/mods.h"
#include "pc/crash_handler.h"
#include "pc/debuglog.h"
#include "pc/pc_main.h"
#include "pc/gfx/gfx_pc.h"
#include "pc/fs/fmem.h"
#include "game/hardcoded.h"
#include "game/scroll_targets.h"
#include "game/camera.h"
#include "game/skybox.h"
#include "game/object_list_processor.h"
#include "game/object_helpers.h"
#include "game/level_geo.h"
#include "menu/intro_geo.h"
#include "game/ingame_menu.h"
#include "game/first_person_cam.h"
#include "game/envfx_snow.h"
#include "game/mario.h"
#include "engine/math_util.h"
#include "engine/lighting_engine.h"

#ifdef DISCORD_SDK
#include "pc/discord/discord.h"
#endif

// fix warnings when including rendering_graph_node
#undef near
#undef far
#include "game/rendering_graph_node.h"

// Mario 64 specific externs
extern s16 sCurrPlayMode;
extern s16 gCurrCourseNum, gCurrActStarNum, gCurrLevelNum, gCurrAreaIndex;

enum NetworkType gNetworkType = NT_NONE;
struct NetworkSystem* gNetworkSystem = &gNetworkSystemSocket;

#define LOADING_LEVEL_THRESHOLD 10
#define MAX_PACKETS_PER_SECOND_PER_PLAYER ((u16)100)

u16 networkLoadingLevel = 0;
bool gNetworkAreaLoaded = false;
bool gNetworkAreaSyncing = true;
u32 gNetworkAreaTimerClock = 0;
u32 gNetworkAreaTimer = 0;
void* gNetworkServerAddr = NULL;
bool gNetworkSentJoin = false;
u16 gNetworkRequestLocationTimer = 0;

u8 gDebugPacketIdBuffer[256] = { 0xFF };
u8 gDebugPacketSentBuffer[256] = { 0 };
u8 gDebugPacketOnBuffer = 0;

u32 gNetworkStartupTimer = 0;
u32 sNetworkReconnectTimer = 0;
u32 sNetworkRehostTimer = 0;
enum NetworkSystemType sNetworkReconnectType = NS_SOCKET;

struct ServerSettings gServerSettings = {
    .playerInteractions = PLAYER_INTERACTIONS_SOLID,
    .bouncyLevelBounds = BOUNCY_LEVEL_BOUNDS_OFF,
    .playerKnockbackStrength = 25,
    .skipIntro = FALSE,
    .bubbleDeath = TRUE,
    .enablePlayersInLevelDisplay = TRUE,
    .enablePlayerList = TRUE,
    .headlessServer = FALSE,
    .nametags = TRUE,
    .maxPlayers = MAX_PLAYERS,
    .pauseAnywhere = FALSE,
    .pvpType = PLAYER_PVP_CLASSIC,
};

struct NametagsSettings gNametagsSettings = {
    .showHealth = false,
    .showSelfTag = false,
};

void network_set_system(enum NetworkSystemType nsType) {
    network_forget_all_reliable();

    switch (nsType) {
        case NS_SOCKET:  gNetworkSystem = &gNetworkSystemSocket; break;
#ifdef COOPNET
        case NS_COOPNET: gNetworkSystem = &gNetworkSystemCoopNet; break;
#endif
        default: gNetworkSystem = &gNetworkSystemSocket; LOG_ERROR("Unknown network system: %d", nsType); break;
    }
}

bool network_init(enum NetworkType inNetworkType, bool reconnecting) {
    // reset override hide hud
    extern u8 gOverrideHideHud;
    gOverrideHideHud = 0;
    gNetworkStartupTimer = 5 * 30;

    // sanity check network system
    if (gNetworkSystem == NULL) {
        LOG_ERROR("no network system attached");
        return false;
    }

    network_forget_all_reliable();
    crash_handler_init();

    // set server settings
    gServerSettings.playerInteractions = configPlayerInteraction;
    gServerSettings.bouncyLevelBounds = configBouncyLevelBounds;
    gServerSettings.playerKnockbackStrength = configPlayerKnockbackStrength;
    gServerSettings.stayInLevelAfterStar = configStayInLevelAfterStar;
    gServerSettings.skipIntro = gCLIOpts.skipIntro ? TRUE : configSkipIntro;
    gServerSettings.bubbleDeath = configBubbleDeath;
    gServerSettings.enablePlayersInLevelDisplay = TRUE;
    gServerSettings.enablePlayerList = TRUE;
    gServerSettings.nametags = configNametags;
    gServerSettings.maxPlayers = configAmountOfPlayers;
    gServerSettings.pauseAnywhere = configPauseAnywhere;
    gServerSettings.pvpType = configPvpType;
    gServerSettings.headlessServer = gCLIOpts.headless && (inNetworkType == NT_SERVER);

    gNametagsSettings.showHealth = false;
    gNametagsSettings.showSelfTag = false;

    // initialize the network system
    gNetworkSentJoin = false;
    int rc = gNetworkSystem->initialize(inNetworkType, reconnecting);
    if (!rc && inNetworkType != NT_NONE) {
        LOG_ERROR("failed to initialize network system");
        djui_popup_create(DLANG(NOTIF, DISCONNECT_CLOSED), 2);
        return false;
    }
    if (gNetworkServerAddr != NULL) {
        free(gNetworkServerAddr);
        gNetworkServerAddr = NULL;
    }

    // set network type
    gNetworkType = inNetworkType;

    if (gNetworkType == NT_SERVER) {
        extern s16 gCurrSaveFileNum;
        gCurrSaveFileNum = configHostSaveSlot;

        mods_activate(&gLocalMods);
        smlua_init();

        dynos_behavior_hook_all_custom_behaviors();

        network_player_connected(NPT_LOCAL, 0, configPlayerModel, &configPlayerPalette, configPlayerName, get_local_discord_id());
        extern u8* gOverrideEeprom;
        gOverrideEeprom = NULL;

        if (gCurrLevelNum != (s16)gLevelValues.entryLevel) {
            extern s16 gChangeLevelTransition;
            gChangeLevelTransition = gLevelValues.entryLevel;
        }

        djui_chat_box_create();
    }

    configfile_save(configfile_name());

#ifdef DISCORD_SDK
    if (gDiscordInitialized) {
        discord_activity_update();
    }
#endif

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

static void network_remember_debug_packet(u8 id, bool sent) {
    if (id == PACKET_ACK) { return; }
    if (id == PACKET_KEEP_ALIVE) { return; }
    if (id == PACKET_DEBUG_SYNC) { return; }
    if (id == PACKET_PLAYER && id == gDebugPacketIdBuffer[gDebugPacketOnBuffer]) { return; }
    if (id == PACKET_OBJECT && id == gDebugPacketIdBuffer[gDebugPacketOnBuffer]) { return; }
    gDebugPacketOnBuffer++;
    gDebugPacketIdBuffer[gDebugPacketOnBuffer] = id;
    gDebugPacketSentBuffer[gDebugPacketOnBuffer] = sent;
}

bool network_allow_unknown_local_index(enum PacketType packetType) {
    return (packetType == PACKET_JOIN_REQUEST)
        || (packetType == PACKET_KICK)
        || (packetType == PACKET_ACK)
        || (packetType == PACKET_MOD_LIST_REQUEST)
        || (packetType == PACKET_MOD_LIST)
        || (packetType == PACKET_MOD_LIST_ENTRY)
        || (packetType == PACKET_MOD_LIST_FILE)
        || (packetType == PACKET_MOD_LIST_DONE)
        || (packetType == PACKET_DOWNLOAD_REQUEST)
        || (packetType == PACKET_DOWNLOAD)
        || (packetType == PACKET_KEEP_ALIVE)
        || (packetType == PACKET_DEBUG_SYNC)
        || (packetType == PACKET_PING)
        || (packetType == PACKET_PONG);
}

void network_send_to(u8 localIndex, struct Packet* p) {
    if (p == NULL) {
        LOG_ERROR("no data to send");
        return;
    }

    // set destination
    if (localIndex == PACKET_DESTINATION_SERVER) {
        packet_set_destination(p, 0);
        localIndex = (gNetworkPlayerServer != NULL) ? gNetworkPlayerServer->localIndex : 0;
    } else {
        u8 idx = (localIndex == 0) ? p->localIndex : localIndex;
        if (idx >= MAX_PLAYERS) {
            LOG_ERROR("Could not set destination to %u", idx);
            return;
        }
        packet_set_destination(p, p->requestBroadcast
                                ? PACKET_DESTINATION_BROADCAST
                                : gNetworkPlayers[idx].globalIndex);
    }

    // sanity checks
    if (gNetworkType == NT_NONE) { LOG_ERROR("network type error none!"); return; }
    if (p->error) { LOG_ERROR("packet error!"); return; }
    if (gNetworkSystem == NULL) { LOG_ERROR("no network system attached"); return; }
    if (localIndex == 0 && !network_allow_unknown_local_index(p->buffer[0])) {
        LOG_ERROR("\n####################\nsending to myself, packetType: %d\n####################\n", p->packetType);
        // SOFT_ASSERT(false); - Crash?
        return;
    }

    if (gNetworkType == NT_SERVER) {
        if (localIndex >= MAX_PLAYERS) {
            LOG_ERROR("Could not get network player %u", localIndex);
            return;
        }
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
    if (localIndex != 0 && gNetworkType != NT_SERVER && gNetworkSystem->requireServerBroadcast && gNetworkPlayerServer != NULL) {
        localIndex = gNetworkPlayerServer->localIndex;
    }

    SOFT_ASSERT(p->dataLength < PACKET_LENGTH);

    // rate limit packets
    bool tooManyPackets = false;
    s32 maxPacketsPerSecond = (gNetworkType == NT_SERVER) ? (MAX_PACKETS_PER_SECOND_PER_PLAYER * (u16)network_player_connected_count()) : MAX_PACKETS_PER_SECOND_PER_PLAYER;
    static s32 sPacketsPerSecond[MAX_PLAYERS] = { 0 };
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
        if (p->keepSendingAfterDisconnect) {
            localIndex = 0; // Force this type of packet to use the saved addr
        }
        u8* buffer = NULL;
        u32 len = 0;
        packet_compress(p, &buffer, &len);
        if (!buffer || len == 0) {
            LOG_ERROR("Failed to compress!");
        } else {
            int rc = gNetworkSystem->send(localIndex, p->addr, buffer, len);
            if (rc == SOCKET_ERROR) { LOG_ERROR("send error %d", rc); return; }
        }
    }
    p->sent = true;

    network_remember_debug_packet(p->packetType, true);

    if (localIndex < MAX_PLAYERS) {
        gNetworkPlayers[localIndex].lastSent = clock_elapsed();
    }
}

void network_send(struct Packet* p) {
    if (p == NULL) {
        LOG_ERROR("no data to send");
        return;
    }
    // prevent errors during writing from propagating
    if (p->writeError) {
        LOG_ERROR("packet has write error: %u", p->packetType);
        return;
    }

    // set the flags again
    packet_set_flags(p);

    if (gNetworkType != NT_SERVER) {
        p->requestBroadcast = TRUE;
        if (gNetworkSystem != NULL && gNetworkSystem->requireServerBroadcast && gNetworkPlayerServer != NULL) {
            int i = gNetworkPlayerServer->localIndex;
            p->localIndex = i;
            p->sent = false;
            network_send_to(i, p);
            return;
        }
    }

    for (s32 i = 1; i < MAX_PLAYERS; i++) {
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
        p->sent = false;
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
    if (!packet_decompress(&p, data, dataLength)) {
        LOG_ERROR("Failed to decompress!");
        return;
    }

    if (localIndex != UNKNOWN_LOCAL_INDEX && localIndex != 0) {
        gNetworkPlayers[localIndex].lastReceived = clock_elapsed();
    }

    // subtract and check hash
    if (!packet_check_hash(&p)) {
        LOG_ERROR("invalid packet hash!");
        return;
    }

    network_remember_debug_packet(p.buffer[0], false);

    // execute packet
    packet_receive(&p);
}

void* network_duplicate_address(u8 localIndex) {
    assert(localIndex < MAX_PLAYERS);
    return gNetworkSystem->dup_addr(localIndex);
}

void network_reset_reconnect_and_rehost(void) {
    gNetworkStartupTimer = 0;
    sNetworkReconnectTimer = 0;
    sNetworkRehostTimer = 0;
    sNetworkReconnectType = NS_SOCKET;
}

void network_reconnect_begin(void) {
    if (sNetworkReconnectTimer > 0) {
        return;
    }

    sNetworkReconnectTimer = 2 * 30;

#ifdef COOPNET
    sNetworkReconnectType = (gNetworkSystem == &gNetworkSystemCoopNet)
                          ? NS_COOPNET
                          : NS_SOCKET;
#else
    sNetworkReconnectType = NS_SOCKET;
#endif

    network_shutdown(false, false, false, true);

    djui_connect_menu_open();
}

static void network_reconnect_update(void) {
    if (sNetworkReconnectTimer <= 0) { return; }
    if (--sNetworkReconnectTimer != 0) { return; }

    if (sNetworkReconnectType == NS_SOCKET) {
        network_set_system(NS_SOCKET);
    } else if (sNetworkReconnectType == NS_COOPNET) {
        network_set_system(NS_COOPNET);
    }

    network_init(NT_CLIENT, true);

    network_send_mod_list_request();
}

bool network_is_reconnecting(void) {
    return sNetworkReconnectTimer > 0;
}

void network_rehost_begin(void) {
    for (int i = 1; i < MAX_PLAYERS; i++) {
        struct NetworkPlayer* np = &gNetworkPlayers[i];
        if (!np->connected) { continue; }

        network_send_kick(i, EKT_REJOIN);
        network_player_disconnected(i);
    }

    network_shutdown(false, false, false, true);

    sNetworkRehostTimer = 2;
}

extern void djui_panel_do_host(bool reconnecting, bool playSound);
static void network_rehost_update(void) {
    if (sNetworkRehostTimer <= 0) { return; }
    if (--sNetworkRehostTimer != 0) { return; }

    djui_panel_do_host(true, true);
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
        if (network_check_singleplayer_pause()) {
            gNetworkAreaTimerClock++;
        }
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

#ifdef COOPNET
void network_update_coopnet(void) {
    if (gNetworkType != NT_NONE) { return; }
    if (!ns_coopnet_is_connected()) { return; }
    ns_coopnet_update();
}
#endif

void network_update(void) {
    if (gNetworkStartupTimer > 0) {
        gNetworkStartupTimer--;
    }

    network_rehost_update();
    network_reconnect_update();

#ifdef COOPNET
    network_update_coopnet();
#endif

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

    sync_objects_update();

    // update level/area request timers
    /*struct NetworkPlayer* np = gNetworkPlayerLocal;
    if (np != NULL && !np->currLevelSyncValid) {
        gNetworkRequestLocationTimer++;
        if (gNetworkRequestLocationTimer > 30 * 10) {
            // find a NetworkPlayer around that location
            struct NetworkPlayer *npLevelAreaMatch = get_network_player_from_area(np->currCourseNum, np->currActNum, np->currLevelNum, np->currAreaIndex);
            struct NetworkPlayer *npLevelMatch     = get_network_player_from_level(np->currCourseNum, np->currActNum, np->currLevelNum);
            struct NetworkPlayer *npAny = (npLevelAreaMatch == NULL) ? npLevelMatch : npLevelAreaMatch;

            bool inCredits = (np->currActNum == 99);
            if (gNetworkType == NT_SERVER && (npAny == NULL || inCredits)) {
                // no NetworkPlayer in the level
                network_send_sync_valid(np, np->currCourseNum, np->currActNum, np->currLevelNum, np->currAreaIndex);
                return;
            }

            // matching NetworkPlayer is client
            if (npAny == npLevelAreaMatch) {
                network_send_level_area_request(np, npAny);
            } else {
                network_send_level_request(np, npAny);
            }
        }
    }*/

    // Kick the player back to the Main Menu if network init failed
    if ((gNetworkType == NT_NONE) && !gDjuiInMainMenu) {
        network_reset_reconnect_and_rehost();
        network_shutdown(true, false, false, false);
    }
}

static inline void color_set(Color color, u8 r, u8 g, u8 b) {
    color[0] = r;
    color[1] = g;
    color[2] = b;
}

void network_shutdown(bool sendLeaving, bool exiting, bool popup, bool reconnecting) {
    smlua_call_event_hooks(HOOK_ON_EXIT);

    if (gDjuiChatBox != NULL) {
        djui_base_destroy(&gDjuiChatBox->base);
        gDjuiChatBox = NULL;
    }

    gNetworkSentJoin = false;

    network_forget_all_reliable();
    if (gNetworkSystem == NULL) {
        LOG_ERROR("no network system attached");
    } else {
        if (gNetworkPlayerLocal != NULL && sendLeaving) { network_send_leaving(gNetworkPlayerLocal->globalIndex); }
        network_player_shutdown(popup);
        gNetworkSystem->shutdown(reconnecting);
    }
    if (gNetworkServerAddr != NULL) {
        free(gNetworkServerAddr);
        gNetworkServerAddr = NULL;
    }
    gNetworkPlayerServer = NULL;

    if (sNetworkReconnectTimer <= 0 || sNetworkReconnectType != NS_COOPNET) {
        gNetworkType = NT_NONE;
    }

    dynos_model_clear_pool(MODEL_POOL_SESSION);

    if (exiting) { return; }

    // reset other stuff
    extern u8* gOverrideEeprom;
    gOverrideEeprom = NULL;
    extern u8 gOverrideFreezeCamera;
    gOverrideFreezeCamera = false;
    gDjuiHudLockMouse = false;
    gOverrideNear = 0;
    gOverrideFar = 0;
    gOverrideFOV = 0;
    gCurrActStarNum = 0;
    gCurrActNum = 0;
    gCurrCreditsEntry = NULL;
    vec3f_set(gLightingDir, 0, 0, 0);
    color_set(gLightingColor[0], 0xFF, 0xFF, 0xFF);
    color_set(gLightingColor[1], 0xFF, 0xFF, 0xFF);
    color_set(gVertexColor, 0xFF, 0xFF, 0xFF);
    color_set(gSkyboxColor, 0xFF, 0xFF, 0xFF);
    color_set(gFogColor, 0xFF, 0xFF, 0xFF);
    gFogIntensity = 1.0f;
    gOverrideBackground = -1;
    gOverrideEnvFx = ENVFX_MODE_NO_OVERRIDE;
    gRomhackCameraSettings.centering = FALSE;
    gOverrideAllowToxicGasCamera = FALSE;
    gRomhackCameraSettings.dpad = FALSE;
    camera_reset_overrides();
    romhack_camera_reset_settings();
    free_vtx_scroll_targets();
    dynos_mod_shutdown();
    mods_clear(&gActiveMods);
    mods_clear(&gRemoteMods);
    smlua_shutdown();
    extern s16 gChangeLevel;
    gChangeLevel = LEVEL_CASTLE_GROUNDS;
    network_player_init();
    camera_set_use_course_specific_settings(true);
    gMarioStates[0].cap = 0;
    gMarioStates[0].input = 0;
    extern s16 gTTCSpeedSetting;
    gTTCSpeedSetting = 0;
    gOverrideDialogPos = 0;
    gOverrideDialogColor = 0;
    gDialogMinWidth = 0;
    gOverrideAllowToxicGasCamera = FALSE;
    gLuaVolumeMaster = 127;
    gLuaVolumeLevel = 127;
    gLuaVolumeSfx = 127;
    gLuaVolumeEnv = 127;

    struct Controller* cnt = gPlayer1Controller;
    cnt->rawStickX = 0;
    cnt->rawStickY = 0;
    cnt->stickX = 0;
    cnt->stickY = 0;
    cnt->stickMag = 0;
    cnt->buttonDown = 0;
    cnt->buttonPressed = 0;
    cnt->buttonReleased = 0;
    cnt->extStickX = 0;
    cnt->extStickY = 0;

    gFirstPersonCamera.enabled = false;
    gFirstPersonCamera.forcePitch = false;
    gFirstPersonCamera.forceYaw = false;
    gFirstPersonCamera.forceRoll = true;
    gFirstPersonCamera.centerL = true;
    gFirstPersonCamera.fov = FIRST_PERSON_DEFAULT_FOV;
    vec3f_set(gFirstPersonCamera.offset, 0, 0, 0);
    first_person_reset();

    le_shutdown();

    extern void save_file_load_all(UNUSED u8 reload);
    save_file_load_all(TRUE);
    extern void save_file_set_using_backup_slot(bool usingBackupSlot);
    save_file_set_using_backup_slot(false);
    f_shutdown();

    extern s16 gMenuMode;
    gMenuMode = -1;

    reset_window_title();

    init_mario_from_save_file();

    djui_panel_shutdown();
    extern bool gDjuiInMainMenu;
    if (!gDjuiInMainMenu) {
        gDjuiInMainMenu = true;
        djui_panel_main_create(NULL);
    }
    djui_lua_error_clear();

#ifdef DISCORD_SDK
    if (gDiscordInitialized) {
        discord_activity_update();
    }
#endif
    packet_ordered_clear_all();

    djui_reset_popup_disabled_override();
}
