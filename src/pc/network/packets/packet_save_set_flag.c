#include <stdio.h>
#include "../network.h"
#include "game/save_file.h"
#include "buffers/buffers.h"
#include "pc/debuglog.h"

extern u8 gSaveFileUsingBackupSlot;

void network_send_save_set_flag(s32 fileIndex, s32 courseIndex, u8 courseStars, u32 flags) {
    struct Packet p = { 0 };
    packet_init(&p, PACKET_SAVE_SET_FLAG, true, PLMT_NONE);
    packet_write_int32(&p, fileIndex);
    packet_write_int32(&p, courseIndex);
    packet_write_uint8(&p, courseStars);
    packet_write_uint32(&p, flags);
    packet_write_uint8(&p, gSaveFileUsingBackupSlot);
    network_send(&p);
    packet_clear(&p);
}

void network_receive_save_set_flag(struct Packet* p) {
    if (p == NULL) { return; }
    
    // Sanity check for data contents. Read will throw an error anyways,
    // But it's better to catch malformed or maliciously formed packets here.
    SOFT_ASSERT(packet_get_remaining_size(p) >= (sizeof(u8) * 2) + sizeof(u32) + (sizeof(s32) * 2));
  
    s32 fileIndex = packet_read_int32(p);
    s32 courseIndex = packet_read_int32(p);
    u8 courseStars = packet_read_uint8(p);
    u32 flags = packet_read_uint32(p);
    u8 backupSlot = packet_read_uint8(p);

    if (fileIndex < 0 || fileIndex >= NUM_SAVE_FILES) {
        LOG_ERROR("Invalid fileIndex: %d", fileIndex);
        return;
    }

    if (courseIndex < 0 || courseIndex >= COURSE_COUNT) {
        LOG_ERROR("Invalid courseIndex: %d", courseIndex);
        return;
    }

    if (backupSlot > 1) {
        LOG_ERROR("Invalid backupSlot: %d", backupSlot);
        return;
    }

    gSaveBuffer.files[fileIndex][backupSlot].courseStars[courseIndex] |= courseStars;
    gSaveBuffer.files[fileIndex][backupSlot].flags |= flags;
    gSaveFileModified = TRUE;
}