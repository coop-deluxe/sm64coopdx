#include <stdio.h>
#include "../network.h"
#include "game/save_file.h"
#include "pc/debuglog.h"

extern u8 gSaveFileUsingBackupSlot;

void network_send_save_file(s32 fileIndex) {
    if (gNetworkPlayerServer == NULL) { return; }
    SOFT_ASSERT(gNetworkType == NT_CLIENT);
    struct Packet p = { 0 };
    packet_init(&p, PACKET_SAVE_FILE, true, PLMT_NONE);
    packet_write_int32(&p, fileIndex);
    packet_write_uint8(&p, gSaveFileUsingBackupSlot);
    network_send_to(gNetworkPlayerServer->localIndex, &p);
    packet_clear(&p);
}

void network_receive_save_file(struct Packet* p) {
    if (p == NULL) { return; }
    
    // Sanity check for data contents. Read will throw an error anyways,
    // But it's better to catch malformed or maliciously formed packets here.
    SOFT_ASSERT(packet_get_remaining_size(p) >= sizeof(u8) + sizeof(s32));
    
    if (gNetworkType != NT_SERVER) { return; }

    u8 lastBackupSlot = gSaveFileUsingBackupSlot;

    s32 fileIndex = packet_read_int32(p);
    gSaveFileUsingBackupSlot = packet_read_uint8(p);

    if (gSaveFileUsingBackupSlot != 0) { gSaveFileUsingBackupSlot = 1; }

    save_file_do_save(fileIndex, FALSE);

    gSaveFileUsingBackupSlot = lastBackupSlot;
}
