#include <stdio.h>
#include "../network.h"
#include "game/save_file.h"
#include "buffers/buffers.h"
#include "pc/debuglog.h"

extern u8 gSaveFileUsingBackupSlot;

void network_send_save_set_flag(s32 fileIndex, s32 courseIndex, u8 courseStars, u32 flags) {
    struct Packet p = { 0 };
    packet_init(&p, PACKET_SAVE_SET_FLAG, true, PLMT_NONE);
    packet_write(&p, &fileIndex,                sizeof(s32));
    packet_write(&p, &courseIndex,              sizeof(s32));
    packet_write(&p, &courseStars,              sizeof(u8));
    packet_write(&p, &flags,                    sizeof(u32));
    packet_write(&p, &gSaveFileUsingBackupSlot, sizeof(u8));
    network_send(&p);
}

void network_receive_save_set_flag(struct Packet* p) {
    s32 fileIndex;
    s32 courseIndex;
    u8 courseStars;
    u32 flags;
    u8 backupSlot;
    packet_read(p, &fileIndex,   sizeof(s32));
    packet_read(p, &courseIndex, sizeof(s32));
    packet_read(p, &courseStars, sizeof(u8));
    packet_read(p, &flags,       sizeof(u32));
    packet_read(p, &backupSlot,  sizeof(u8));

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