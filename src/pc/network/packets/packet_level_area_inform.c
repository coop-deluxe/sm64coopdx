#include <stdio.h>
#include "../network.h"
#include "level_table.h"
//#define DISABLE_MODULE_LOG 1
#include "pc/debuglog.h"

#include "pc/djui/djui.h"
#include "game/level_info.h"
#include "game/mario_misc.h"

void network_send_level_area_inform(void) {
    struct NetworkPlayer* np = gNetworkPlayerLocal;
    if (np == NULL) { return; }
    np->currLevelAreaSeqId++;

    struct Packet p = { 0 };
    packet_init(&p, PACKET_LEVEL_AREA_INFORM, true, PLMT_NONE);
    packet_write_uint16(&p, np->currLevelAreaSeqId);
    packet_write_uint8(&p, np->globalIndex);
    packet_write_int16(&p, np->currCourseNum);
    packet_write_int16(&p, np->currActNum);
    packet_write_int16(&p, np->currLevelNum);
    packet_write_int16(&p, np->currAreaIndex);
    packet_write_uint8(&p, np->currLevelSyncValid);
    packet_write_uint8(&p, np->currAreaSyncValid);
    network_send(&p);
    packet_clear(&p);

    LOG_INFO("tx level area inform for global %d: (%d, %d, %d, %d)", np->globalIndex, np->currCourseNum, np->currActNum, np->currLevelNum, np->currAreaIndex);
}

void network_receive_level_area_inform(struct Packet* p) {
    if (p == NULL) { return; }

    // Sanity check for data contents. Read will throw an error anyways,
    // But it's better to catch malformed or maliciously formed packets here.
    SOFT_ASSERT(packet_get_remaining_size(p) >= (sizeof(u8) * 3) + sizeof(u16) + (sizeof(s16) * 4));

    u16 seq = packet_read_uint16(p);
    u8 globalIndex = packet_read_uint8(p);
    s16 courseNum = packet_read_int16(p);
    s16 actNum = packet_read_int16(p);
    s16 levelNum = packet_read_int16(p);
    s16 areaIndex = packet_read_int16(p);
    u8 levelSyncValid = packet_read_uint8(p);
    u8 areaSyncValid = packet_read_uint8(p);

    LOG_INFO("rx level area inform for global %d: (%d, %d, %d, %d)", globalIndex, courseNum, actNum, levelNum, areaIndex);

    struct NetworkPlayer *np = network_player_from_global_index(globalIndex);
    if (np == NULL || np->localIndex == UNKNOWN_LOCAL_INDEX || !np->connected) {
        LOG_ERROR("Receiving level area inform from inactive player!");
        return;
    }

    if (np == gNetworkPlayerLocal) { return; }

    if (np->currLevelAreaSeqId >= seq && abs(np->currLevelAreaSeqId - seq) < 256) {
        LOG_INFO("Received old level area inform seq: %d vs %d", np->currLevelAreaSeqId, seq);
        return;
    }

    np->currLevelAreaSeqId = seq;
    np->currLevelSyncValid = levelSyncValid;
    np->currAreaSyncValid  = areaSyncValid;
    network_player_update_course_level(np, courseNum, actNum, levelNum, areaIndex);
}
