#include <stdio.h>
#include "../network.h"
#include "object_fields.h"
#include "object_constants.h"
#include "behavior_table.h"
#include "course_table.h"
#include "src/game/interaction.h"
#include "src/engine/math_util.h"
#include "src/game/save_file.h"
#include "src/game/level_update.h"
#include "src/game/hardcoded.h"
#include "src/pc/fs/fs.h"
#include "PR/os_eeprom.h"
#include "pc/network/version.h"
#include "pc/djui/djui.h"
#include "pc/djui/djui_panel.h"
#include "pc/djui/djui_panel_modlist.h"
#include "pc/djui/djui_panel_playerlist.h"
#include "pc/djui/djui_panel_menu.h"
#include "pc/djui/djui_panel_join_message.h"
#include "pc/cheats.h"
#include "pc/utils/string_builder.h"
//#define DISABLE_MODULE_LOG 1
#include "pc/debuglog.h"
#include "pc/utils/misc.h"
#include "pc/mods/mods.h"
#include "pc/lua/smlua.h"
#include "pc/configfile.h"

extern u8* gOverrideEeprom;
static u8 eeprom[512] = { 0 };

static u8   sJoinRequestPlayerModel;
static struct PlayerPalette sJoinRequestPlayerPalette;
static char sJoinRequestPlayerName[MAX_PLAYER_STRING];
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

    packet_write(&p, &configPlayerModel,   sizeof(u8));
    packet_write(&p, &configPlayerPalette, sizeof(struct PlayerPalette));
    packet_write(&p, &configPlayerName,    sizeof(u8) * MAX_PLAYER_STRING);

    network_send_to((gNetworkPlayerServer != NULL) ? gNetworkPlayerServer->localIndex : 0, &p);
    LOG_INFO("sending join request");
}

void network_receive_join_request(struct Packet* p) {
    SOFT_ASSERT(gNetworkType == NT_SERVER);
    LOG_INFO("received join request");

    if (p->dataLength > 5) {
        char version[MAX_VERSION_LENGTH] = { 0 };
        packet_read(p, &version, sizeof(u8) * MAX_VERSION_LENGTH);
        packet_read(p, &sJoinRequestPlayerModel,   sizeof(u8));
        packet_read(p, &sJoinRequestPlayerPalette, sizeof(struct PlayerPalette));
        packet_read(p, &sJoinRequestPlayerName,    sizeof(u8) * MAX_PLAYER_STRING);
    } else {
        sJoinRequestPlayerModel = 0;
        sJoinRequestPlayerPalette = DEFAULT_MARIO_PALETTE;
        snprintf(sJoinRequestPlayerName, MAX_PLAYER_STRING, "%s", "Player");
    }

    network_send_join(p);
}

void network_send_join(struct Packet* joinRequestPacket) {
    SOFT_ASSERT(gNetworkType == NT_SERVER);

    // figure out id
    u8 globalIndex = joinRequestPacket->localIndex;
    if (globalIndex == UNKNOWN_LOCAL_INDEX) {
        for (u32 i = 1; i < configAmountofPlayers; i++) {
            if (!gNetworkPlayers[i].connected) {
                globalIndex = i;
                break;
            }
        }
        if (globalIndex == UNKNOWN_LOCAL_INDEX) {
            network_send_kick(0, EKT_FULL_PARTY);
            return;
        }
    }
    LOG_INFO("chose globalIndex: %d", globalIndex);

    // do connection event
    network_player_connected(NPT_CLIENT, globalIndex, sJoinRequestPlayerModel, &sJoinRequestPlayerPalette, sJoinRequestPlayerName);

    fs_file_t* fp = fs_open(SAVE_FILENAME);
    if (fp != NULL) {
        fs_read(fp, eeprom, 512);
        fs_close(fp);
    }

    char version[MAX_VERSION_LENGTH] = { 0 };
    snprintf(version, MAX_VERSION_LENGTH, "%s", get_version());
    LOG_INFO("sending version: %s", version);

    struct Packet p = { 0 };
    packet_init(&p, PACKET_JOIN, true, PLMT_NONE);
    packet_write(&p, &version, sizeof(u8) * MAX_VERSION_LENGTH);
    packet_write(&p, &globalIndex, sizeof(u8));
    packet_write(&p, &gCurrSaveFileNum, sizeof(s16));
    packet_write(&p, &gServerSettings.playerInteractions, sizeof(u8));
    packet_write(&p, &gServerSettings.playerKnockbackStrength, sizeof(u8));
    packet_write(&p, &gServerSettings.stayInLevelAfterStar, sizeof(u8));
    packet_write(&p, &gServerSettings.skipIntro, sizeof(u8));
    packet_write(&p, &gServerSettings.shareLives, sizeof(u8));
    packet_write(&p, &gServerSettings.enableCheats, sizeof(u8));
    packet_write(&p, &gServerSettings.bubbleDeath, sizeof(u8));
    packet_write(&p, &gServerSettings.headlessServer, sizeof(u8));
    packet_write(&p, eeprom, sizeof(u8) * 512);

    u8 modCount = string_linked_list_count(&gRegisteredMods);
    packet_write(&p, &modCount, sizeof(u8));

    struct StringLinkedList* node = &gRegisteredMods;
    char nullchar = '\0';
    while (node != NULL && node->string != NULL) {
        s32 length = strlen(node->string);
        packet_write(&p, node->string, sizeof(u8) * length);
        packet_write(&p, &nullchar, sizeof(u8));
        LOG_INFO("sending registered mod: %s", node->string);
        node = node->next;
    }

    network_send_to(globalIndex, &p);
    LOG_INFO("sending join packet");

    network_send_network_players(globalIndex);
}

void network_receive_join(struct Packet* p) {
    SOFT_ASSERT(gNetworkType == NT_CLIENT);
    if (gNetworkPlayerLocal != NULL) { return; }
    LOG_INFO("received join packet");
    gCurrentlyJoining = true;

    gOverrideEeprom = eeprom;

    char version[MAX_VERSION_LENGTH] = { 0 };
    snprintf(version, MAX_VERSION_LENGTH, "%s", get_version());
    LOG_INFO("client has version: %s", version);

    char remoteVersion[MAX_VERSION_LENGTH] = { 0 };
    u8 myGlobalIndex = UNKNOWN_GLOBAL_INDEX;
    u8 modCount = 0;

    if (gNetworkPlayerLocal != NULL && gNetworkPlayerLocal->connected) {
        LOG_ERROR("Received join packet, but already in-game!");
        return;
    }

    // verify version
    packet_read(p, &remoteVersion, sizeof(u8) * MAX_VERSION_LENGTH);
    LOG_INFO("server has version: %s", version);
    if (memcmp(version, remoteVersion, MAX_VERSION_LENGTH) != 0) {
        network_shutdown(true, false, false);
        LOG_ERROR("version mismatch");
        char mismatchMessage[256] = { 0 };
        snprintf(mismatchMessage, 256, "\\#ffa0a0\\Error:\\#c8c8c8\\ Version mismatch.\n\nYour version: \\#a0a0ff\\%s\\#c8c8c8\\\nTheir version: \\#a0a0ff\\%s\\#c8c8c8\\\n\nSomeone is out of date!\n", version, remoteVersion);
        djui_panel_join_message_error(mismatchMessage);
        return;
    }

    packet_read(p, &myGlobalIndex, sizeof(u8));
    packet_read(p, &gCurrSaveFileNum, sizeof(s16));
    packet_read(p, &gServerSettings.playerInteractions, sizeof(u8));
    packet_read(p, &gServerSettings.playerKnockbackStrength, sizeof(u8));
    packet_read(p, &gServerSettings.stayInLevelAfterStar, sizeof(u8));
    packet_read(p, &gServerSettings.skipIntro, sizeof(u8));
    packet_read(p, &gServerSettings.shareLives, sizeof(u8));
    packet_read(p, &gServerSettings.enableCheats, sizeof(u8));
    packet_read(p, &gServerSettings.bubbleDeath, sizeof(u8));
    packet_read(p, &gServerSettings.headlessServer, sizeof(u8));
    packet_read(p, eeprom, sizeof(u8) * 512);
    packet_read(p, &modCount, sizeof(u8));

    struct StringLinkedList head = { 0 };
    for (s32 i = 0; i < modCount; i++) {
        char* modName = (char*) &p->buffer[p->cursor];
        s32 length = strlen(modName);
        LOG_INFO("host has mod: %s", modName);
        string_linked_list_append(&head, modName);
        p->cursor += length + 1;
    }

    if (string_linked_list_mismatch(&gRegisteredMods, &head)) {
        network_shutdown(true, false, false);

        struct StringBuilder* builder = string_builder_create(512);
        string_builder_append(builder, "\\#ffa0a0\\Error:\\#c8c8c8\\ mods don't match.\n\n");

        string_builder_append(builder, "\\#c8c8c8\\Yours: ");
        struct StringLinkedList* node = &gRegisteredMods;
        bool first = true;
        while (node != NULL && node->string != NULL) {
            string_builder_append(builder, first ? "\\#%s\\%s" : ", \\#%s\\%s",
                string_linked_list_contains(&head, node->string) ? "a0ffa0" : "ffa0a0"
                , node->string);
            first = false;
            node = node->next;
        }

        string_builder_append(builder, "\n\n\\#c8c8c8\\Theirs: ");
        node = &head;
        first = true;
        while (node != NULL && node->string != NULL) {
            string_builder_append(builder, first ? "\\#%s\\%s" : ", \\#%s\\%s",
                string_linked_list_contains(&gRegisteredMods, node->string) ? "a0ffa0" : "ffa0a0"
                , node->string);
            first = false;
            node = node->next;
        }

        djui_panel_join_message_error(builder->string);
        string_builder_destroy(builder);
        string_linked_list_free(&head);
        return;
    }
    string_linked_list_free(&head);

    network_player_connected(NPT_SERVER, 0, 0, &DEFAULT_MARIO_PALETTE, "Player");
    network_player_connected(NPT_LOCAL, myGlobalIndex, configPlayerModel, &configPlayerPalette, configPlayerName);
    djui_chat_box_create();

    save_file_load_all(TRUE);

    djui_panel_shutdown();
    update_all_mario_stars();

    fake_lvl_init_from_save_file();

    mods_activate(&gRemoteMods);
    djui_panel_modlist_create(NULL);
    smlua_init();
    dynos_behavior_hook_all_custom_behaviors();

    network_send_network_players_request();
    network_send_lua_sync_table_request();

    gCurrentlyJoining = false;
    smlua_call_event_hooks(HOOK_JOINED_GAME);
    extern s16 gChangeLevel;
    gChangeLevel = gLevelValues.entryLevel;
}
