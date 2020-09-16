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

#define HASH_LENGTH 8
extern u8* gOverrideEeprom;
static u8 eeprom[512] = { 0 };

void network_send_join_request(void) {
    assert(gNetworkType == NT_CLIENT);

    gOverrideEeprom = eeprom;

    struct Packet p;
    packet_init(&p, PACKET_JOIN_REQUEST, true);
    network_send(&p);
}

void network_receive_join_request(UNUSED struct Packet* p) {
    assert(gNetworkType == NT_SERVER);
    network_send_join();
}

void network_send_join(void) {
    assert(gNetworkType == NT_SERVER);

    fs_file_t* fp = fs_open(SAVE_FILENAME);
    if (fp != NULL) {
        fs_read(fp, eeprom, 512);
        fs_close(fp);
    }

    char hash[HASH_LENGTH] = GIT_HASH;

    struct Packet p;
    packet_init(&p, PACKET_JOIN, true);
    packet_write(&p, &hash, sizeof(u8) * HASH_LENGTH);
    packet_write(&p, &gCurrSaveFileNum, sizeof(s16));
    packet_write(&p, &gServerSettings.playerInteractions, sizeof(u8));
    packet_write(&p, &gServerSettings.playerKnockbackStrength, sizeof(u8));
    packet_write(&p, &gServerSettings.stayInLevelAfterStar, sizeof(u8));
    packet_write(&p, eeprom, sizeof(u8) * 512);
    network_send(&p);
}

void network_receive_join(struct Packet* p) {
    assert(gNetworkType == NT_CLIENT);

    gOverrideEeprom = eeprom;
    char hash[HASH_LENGTH] = GIT_HASH;
    char remoteHash[HASH_LENGTH] = { 0 };

    // find all reserved objects
    packet_read(p, &remoteHash, sizeof(u8) * HASH_LENGTH);
    packet_read(p, &gCurrSaveFileNum, sizeof(s16));
    packet_read(p, &gServerSettings.playerInteractions, sizeof(u8));
    packet_read(p, &gServerSettings.playerKnockbackStrength, sizeof(u8));
    packet_read(p, &gServerSettings.stayInLevelAfterStar, sizeof(u8));
    packet_read(p, eeprom, sizeof(u8) * 512);

    save_file_load_all(TRUE);
    if (memcmp(hash, remoteHash, HASH_LENGTH) != 0) {
        custom_menu_version_mismatch();
        return;
    }
    custom_menu_goto_game(gCurrSaveFileNum);
}
