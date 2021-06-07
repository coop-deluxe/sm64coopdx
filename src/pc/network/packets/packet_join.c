#include <stdio.h>
#include "../network.h"
#include "object_fields.h"
#include "object_constants.h"
#include "behavior_table.h"
#include "course_table.h"
#include "src/game/interaction.h"
#include "src/engine/math_util.h"
#include "src/game/save_file.h"
#include "src/menu/custom_menu.h"
#include "src/pc/fs/fs.h"
#include "PR/os_eeprom.h"
#include "pc/network/version.h"
#define DISABLE_MODULE_LOG 1
#include "pc/debuglog.h"


extern u8* gOverrideEeprom;
static u8 eeprom[512] = { 0 };

void network_send_join_request(void) {
    assert(gNetworkType == NT_CLIENT);

    gOverrideEeprom = eeprom;

    struct Packet p;
    packet_init(&p, PACKET_JOIN_REQUEST, true, false);
    network_send_to(0, &p);
    LOG_INFO("sending join request");
}

void network_receive_join_request(struct Packet* p) {
    assert(gNetworkType == NT_SERVER);
    LOG_INFO("received join request");
    network_send_join(p);
}

void network_send_join(struct Packet* joinRequestPacket) {
    assert(gNetworkType == NT_SERVER);

    fs_file_t* fp = fs_open(SAVE_FILENAME);
    if (fp != NULL) {
        fs_read(fp, eeprom, 512);
        fs_close(fp);
    }

    // do connection event
    joinRequestPacket->localIndex = network_player_connected(NPT_CLIENT, joinRequestPacket->localIndex);
    if (joinRequestPacket->localIndex == UNKNOWN_LOCAL_INDEX) {
        network_send_kick(EKT_FULL_PARTY);
        return;
    }

    char version[MAX_VERSION_LENGTH] = { 0 };
    snprintf(version, MAX_VERSION_LENGTH, "%s", get_version());
    LOG_INFO("sending version: %s", version);

    struct Packet p;
    packet_init(&p, PACKET_JOIN, true, false);
    packet_write(&p, &version, sizeof(u8) * MAX_VERSION_LENGTH);
    packet_write(&p, &joinRequestPacket->localIndex, sizeof(u8));
    packet_write(&p, &gCurrSaveFileNum, sizeof(s16));
    packet_write(&p, &gServerSettings.playerInteractions, sizeof(u8));
    packet_write(&p, &gServerSettings.playerKnockbackStrength, sizeof(u8));
    packet_write(&p, &gServerSettings.stayInLevelAfterStar, sizeof(u8));
    packet_write(&p, &gServerSettings.skipIntro, sizeof(u8));
    packet_write(&p, &gServerSettings.shareLives, sizeof(u8));
    packet_write(&p, eeprom, sizeof(u8) * 512);

    u8 modCount = string_linked_list_count(&gRegisteredMods);
    packet_write(&p, &modCount, sizeof(u8));

    struct StringLinkedList* node = &gRegisteredMods;
    char nullchar = '\0';
    while (node != NULL && node->string != NULL) {
        int length = strlen(node->string);
        packet_write(&p, node->string, sizeof(char) * length);
        packet_write(&p, &nullchar, sizeof(char));
        LOG_INFO("sending registered mod: %s", node->string);
        node = node->next;
    }

    network_send_to(joinRequestPacket->localIndex , &p);
    LOG_INFO("sending join packet");

    network_send_network_players();
}

void network_receive_join(struct Packet* p) {
    assert(gNetworkType == NT_CLIENT);
    LOG_INFO("received join packet");

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
        LOG_ERROR("version mismatch");

        // todo: hack: remove me in the future
        // needed because the old style only had 8 characters for the version
        if (strcmp("beta", remoteVersion) != 0) {
            remoteVersion[8] = '\0';
        }

        char mismatchMessage[128] = { 0 };
        snprintf(mismatchMessage, 128, "Version mismatch.\n\nYour version - %s\nTheir version - %s\n\nSomeone is out of date!\n", version, remoteVersion);
        custom_menu_connection_error(mismatchMessage);
        return;
    }

    packet_read(p, &myGlobalIndex, sizeof(u8));
    packet_read(p, &gCurrSaveFileNum, sizeof(s16));
    packet_read(p, &gServerSettings.playerInteractions, sizeof(u8));
    packet_read(p, &gServerSettings.playerKnockbackStrength, sizeof(u8));
    packet_read(p, &gServerSettings.stayInLevelAfterStar, sizeof(u8));
    packet_read(p, &gServerSettings.skipIntro, sizeof(u8));
    packet_read(p, &gServerSettings.shareLives, sizeof(u8));
    packet_read(p, eeprom, sizeof(u8) * 512);
    packet_read(p, &modCount, sizeof(u8));

    struct StringLinkedList head = { 0 };
    for (int i = 0; i < modCount; i++) {
        char* modName = (char*) &p->buffer[p->cursor];
        int length = strlen(modName);
        LOG_INFO("host has mod: %s", modName);
        string_linked_list_append(&head, modName);
        p->cursor += length + 1;
    }

    if (string_linked_list_mismatch(&gRegisteredMods, &head)) {
        string_linked_list_free(&head);
        custom_menu_connection_error("Your mods don't match!");
        return;
    }
    string_linked_list_free(&head);

    network_player_connected(NPT_SERVER, 0);
    network_player_connected(NPT_LOCAL, myGlobalIndex);

    save_file_load_all(TRUE);
    custom_menu_goto_game(gCurrSaveFileNum);
}
