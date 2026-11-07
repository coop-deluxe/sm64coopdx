#include <stdio.h>
#include "../network.h"
#include "object_fields.h"
#include "object_constants.h"
#include "behavior_table.h"
#include "course_table.h"
#include "game/interaction.h"
#include "engine/math_util.h"
#include "game/save_file.h"
#include "game/level_update.h"
#include "game/hardcoded.h"
#include "pc/fs/fs.h"
#include "PR/os_eeprom.h"
#include "pc/network/version.h"
#include "pc/djui/djui.h"
#include "pc/djui/djui_panel.h"
#include "pc/djui/djui_panel_modlist.h"
#include "pc/djui/djui_panel_playerlist.h"
#include "pc/djui/djui_panel_menu.h"
#include "pc/djui/djui_panel_join_message.h"
#include "pc/utils/string_builder.h"
//#define DISABLE_MODULE_LOG 1
#include "pc/debuglog.h"
#include "pc/utils/misc.h"
#include "pc/mods/mods.h"
#include "pc/lua/smlua.h"
#include "pc/configfile.h"
#include "pc/lua/utils/smlua_misc_utils.h"

extern u8* gOverrideEeprom;
static u8 eeprom[512] = { 0 };

static u8   sJoinRequestPlayerModel = 0;
static struct PlayerPalette sJoinRequestPlayerPalette = { 0 };
static char sJoinRequestPlayerName[MAX_CONFIG_STRING] = { 0 };
static char sJoinRequestDiscordId[64] = { 0 };
bool gCurrentlyJoining = false;

void network_send_join_request(void) {
    SOFT_ASSERT(gNetworkType == NT_CLIENT);

    gNetworkSentJoin = true;
    gOverrideEeprom = eeprom;

    struct Packet p = { 0 };
    packet_init(&p, PACKET_JOIN_REQUEST, true, PLMT_NONE);
    
    char version[MAX_VERSION_LENGTH] = { 0 };
    snprintf(version, MAX_VERSION_LENGTH, "%s", get_version());
    packet_write(&p, &version, sizeof(u8) * MAX_VERSION_LENGTH);
    
    packet_write_uint8(&p, configPlayerModel);
    packet_write(&p, &configPlayerPalette, sizeof(struct PlayerPalette));
    packet_write(&p, &configPlayerName,    sizeof(u8) * MAX_CONFIG_STRING);

    network_send_to((gNetworkPlayerServer != NULL) ? gNetworkPlayerServer->localIndex : 0, &p);
    
    packet_clear(&p);
    
    LOG_INFO("sending join request");
}

void network_receive_join_request(struct Packet* p) {
    SOFT_ASSERT(gNetworkType == NT_SERVER);
    LOG_INFO("received join request");
    
    // Sanity check for data contents. Read will throw an error anyways,
    // But it's better to catch malformed or maliciously formed packets here.
    SOFT_ASSERT(packet_get_remaining_size(p) >= MAX_VERSION_LENGTH);
    
    char version[MAX_VERSION_LENGTH] = { 0 };
    packet_read(p, &version, sizeof(u8) * MAX_VERSION_LENGTH);

    if (packet_get_remaining_size(p) >= sizeof(u8) + sizeof(struct PlayerPalette) + (sizeof(u8) * MAX_CONFIG_STRING)) {
        sJoinRequestPlayerModel = packet_read_uint8(p);
        packet_read(p, &sJoinRequestPlayerPalette, sizeof(struct PlayerPalette));
        packet_read(p, &sJoinRequestPlayerName,    sizeof(u8) * MAX_CONFIG_STRING);
    } else {
        sJoinRequestPlayerModel = 0;
        sJoinRequestPlayerPalette = DEFAULT_MARIO_PALETTE;
        snprintf(sJoinRequestPlayerName, MAX_CONFIG_STRING, "%s", "Player");
    }

    network_send_join(p);
}

void network_send_join(struct Packet* joinRequestPacket) {
    SOFT_ASSERT(gNetworkType == NT_SERVER);

    // figure out id
    u8 globalIndex = joinRequestPacket->localIndex;
    u8 connectedCount = 1;
    if (globalIndex == UNKNOWN_LOCAL_INDEX) {
        for (u32 i = 1; i < MAX_PLAYERS; i++) {
            if (!gNetworkPlayers[i].connected) {
                globalIndex = i;
                break;
            } else {
                connectedCount++;
            }
        }
        if (globalIndex == UNKNOWN_LOCAL_INDEX || connectedCount >= gServerSettings.maxPlayers) {
            network_send_kick(0, EKT_FULL_PARTY);
            return;
        }
    }
    LOG_INFO("Chose globalIndex: %d", globalIndex);

    // do connection event
    network_player_connected(NPT_CLIENT, globalIndex, sJoinRequestPlayerModel, &sJoinRequestPlayerPalette, sJoinRequestPlayerName, sJoinRequestDiscordId);

    fs_file_t* fp = fs_open(SAVE_FILENAME);
    if (fp != NULL) {
        fs_read(fp, eeprom, 512);
        fs_close(fp);
    }

    char version[MAX_VERSION_LENGTH] = { 0 };
    snprintf(version, MAX_VERSION_LENGTH, "%s", get_version());
    LOG_INFO("Sending version: %s", version);

    struct Packet p = { 0 };
    packet_init(&p, PACKET_JOIN, true, PLMT_NONE);
    packet_write(&p, &version, sizeof(u8) * MAX_VERSION_LENGTH);
    packet_write_uint8(&p, globalIndex);
    packet_write_int16(&p, gCurrSaveFileNum);
    packet_write_uint8(&p, gServerSettings.playerInteractions);
    packet_write_uint8(&p, gServerSettings.bouncyLevelBounds);
    packet_write_uint8(&p, gServerSettings.playerKnockbackStrength);
    packet_write_uint8(&p, gServerSettings.stayInLevelAfterStar);
    packet_write_uint8(&p, gServerSettings.skipIntro);
    packet_write_uint8(&p, gServerSettings.bubbleDeath);
    packet_write_uint8(&p, gServerSettings.headlessServer);
    packet_write_uint8(&p, gServerSettings.nametags);
    packet_write_uint8(&p, gServerSettings.maxPlayers);
    packet_write_uint8(&p, gServerSettings.pauseAnywhere);
    packet_write_uint8(&p, gServerSettings.pvpType);
    packet_write(&p, eeprom, sizeof(u8) * 512);

    network_send_to(globalIndex, &p);
    LOG_INFO("Sending join packet");
    
    packet_clear(&p);

    network_send_network_players(globalIndex);
}

void network_receive_join(struct Packet* p) {
    SOFT_ASSERT(gNetworkType == NT_CLIENT);
    if (gNetworkPlayerLocal != NULL) { return; }
    LOG_INFO("Received join packet");
    gCurrentlyJoining = true;

    gOverrideEeprom = eeprom;

    char version[MAX_VERSION_LENGTH] = { 0 };
    snprintf(version, MAX_VERSION_LENGTH, "%s", get_version());
    LOG_INFO("Client has version: %s", version);

    char remoteVersion[MAX_VERSION_LENGTH] = { 0 };
    u8 myGlobalIndex = UNKNOWN_GLOBAL_INDEX;

    if (gNetworkPlayerLocal != NULL && gNetworkPlayerLocal->connected) {
        LOG_ERROR("Received join packet, but already in-game!");
        return;
    }
    
    // Sanity check for data contents. Read will throw an error anyways,
    // But it's better to catch malformed or maliciously formed packets here.
    SOFT_ASSERT(packet_get_remaining_size(p) >= (sizeof(u8) * MAX_VERSION_LENGTH) + (sizeof(u8) * 12) + sizeof(s16) + (sizeof(u8) * 512));

    // Verify version
    packet_read(p, &remoteVersion, sizeof(u8) * MAX_VERSION_LENGTH);
    LOG_INFO("Server has version: %s", version);
    if (memcmp(version, remoteVersion, MAX_VERSION_LENGTH) != 0) {
        network_shutdown(true, false, false, false);
        LOG_ERROR("Version mismatch");
        char mismatchMessage[256] = { 0 };
        snprintf(mismatchMessage, 256, "\\#ffa0a0\\Error:\\#\\ Version mismatch.\n\nYour version: \\#a0a0ff\\%s\\#\\\nTheir version: \\#a0a0ff\\%s\\#\\\n\nSomeone is out of date!\n", version, remoteVersion);
        djui_panel_join_message_error(mismatchMessage);
        return;
    }
    
    myGlobalIndex = packet_read_uint8(p);
    gCurrSaveFileNum = packet_read_int16(p);
    gServerSettings.playerInteractions = packet_read_uint8(p);
    gServerSettings.bouncyLevelBounds = packet_read_uint8(p);
    gServerSettings.playerKnockbackStrength = packet_read_uint8(p);
    gServerSettings.stayInLevelAfterStar = packet_read_uint8(p);
    gServerSettings.skipIntro = packet_read_uint8(p);
    gServerSettings.bubbleDeath = packet_read_uint8(p);
    gServerSettings.headlessServer = packet_read_uint8(p);
    gServerSettings.nametags = packet_read_uint8(p);
    gServerSettings.maxPlayers = packet_read_uint8(p);
    gServerSettings.pauseAnywhere = packet_read_uint8(p);
    gServerSettings.pvpType = packet_read_uint8(p);
    packet_read(p, eeprom, sizeof(u8) * 512);

    network_player_connected(NPT_SERVER, 0, 0, &DEFAULT_MARIO_PALETTE, "Player", "0");
    network_player_connected(NPT_LOCAL, myGlobalIndex, configPlayerModel, &configPlayerPalette, configPlayerName, get_local_discord_id());
    djui_chat_box_create();

    save_file_load_all(TRUE);

    djui_panel_shutdown();
    update_all_mario_stars();

    fake_lvl_init_from_save_file();

    mods_activate(&gRemoteMods);
    djui_panel_modlist_create(NULL);
    smlua_init();

    network_send_network_players_request();
    network_send_lua_sync_table_request();

    gCurrentlyJoining = false;
    smlua_call_event_hooks(HOOK_JOINED_GAME);
    extern s16 gChangeLevel;
    gChangeLevel = gLevelValues.entryLevel;

    gAllowOrderedPacketClear = 1;
}
