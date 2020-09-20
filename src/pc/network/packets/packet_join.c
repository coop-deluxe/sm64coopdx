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
#include "pc/debuglog.h"

#define HASH_LENGTH 8
extern u8* gOverrideEeprom;
static u8 eeprom[512] = { 0 };

void network_send_join_request(void) {
    assert(gNetworkType == NT_CLIENT);

    gOverrideEeprom = eeprom;

    struct Packet p;
    packet_init(&p, PACKET_JOIN_REQUEST, true);
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

    char hash[HASH_LENGTH] = GIT_HASH;

    struct Packet p;
    packet_init(&p, PACKET_JOIN, true);
    packet_write(&p, &hash, sizeof(u8) * HASH_LENGTH);
    packet_write(&p, &joinRequestPacket->localIndex, sizeof(u8));
    packet_write(&p, &gCurrSaveFileNum, sizeof(s16));
    packet_write(&p, &gServerSettings.playerInteractions, sizeof(u8));
    packet_write(&p, &gServerSettings.playerKnockbackStrength, sizeof(u8));
    packet_write(&p, &gServerSettings.stayInLevelAfterStar, sizeof(u8));
    packet_write(&p, eeprom, sizeof(u8) * 512);
    network_send_to(joinRequestPacket->localIndex , &p);

    LOG_INFO("sending join packet");
}

void network_receive_join(struct Packet* p) {
    assert(gNetworkType == NT_CLIENT);
    LOG_INFO("received join packet");

    gOverrideEeprom = eeprom;
    char hash[HASH_LENGTH] = GIT_HASH;
    char remoteHash[HASH_LENGTH] = { 0 };
    u8 myGlobalIndex = UNKNOWN_GLOBAL_INDEX;

    if (gNetworkPlayerLocal != NULL && gNetworkPlayerLocal->connected) {
        LOG_ERROR("Received join packet, but already in-game!");
        return;
    }

    // verify version
    packet_read(p, &remoteHash, sizeof(u8) * HASH_LENGTH);
    if (memcmp(hash, remoteHash, HASH_LENGTH) != 0) {
        custom_menu_version_mismatch();
        return;
    }

    packet_read(p, &myGlobalIndex, sizeof(u8));
    packet_read(p, &gCurrSaveFileNum, sizeof(s16));
    packet_read(p, &gServerSettings.playerInteractions, sizeof(u8));
    packet_read(p, &gServerSettings.playerKnockbackStrength, sizeof(u8));
    packet_read(p, &gServerSettings.stayInLevelAfterStar, sizeof(u8));
    packet_read(p, eeprom, sizeof(u8) * 512);

    network_player_connected(NPT_SERVER, 0);
    network_player_connected(NPT_LOCAL, myGlobalIndex);

    save_file_load_all(TRUE);
    custom_menu_goto_game(gCurrSaveFileNum);
}
