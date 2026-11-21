#include "game/area.h"
#include "pc/debuglog.h"
#include "pc/network/network.h"
#include "pc/network/packets/datagram.h"

#define PACKET_TYPE_OFFSET               0
#define PACKET_SEQ_ID_OFFSET             1
#define PACKET_FLAG_OFFSET               3
#define PACKET_DESTINATION_OFFSET        4
#define PACKET_ORDERED_SEQ_ID_OFFSET     8

static u16 sNextSeqNum = 1;

static bool sOrderedPackets = false;
static u16 sCurrentOrderedGroupId = 0;
static u16 sCurrentOrderedSeqId = 0;

OPTIMIZE_O3 void packet_init(struct Packet *packet, enum PacketType packetType, bool reliable, enum PacketLevelMatchType levelAreaMustMatch) {
    datagram_init(&packet->dg);
    packet->packetType = packetType;
    packet->reliable = reliable;
    packet->levelAreaMustMatch = (levelAreaMustMatch == PLMT_AREA);
    packet->levelMustMatch     = (levelAreaMustMatch == PLMT_LEVEL);
    packet->requestBroadcast = false;
    packet->sent = false;
    packet->orderedFromGlobalId = sOrderedPackets ? gNetworkPlayerLocal->globalIndex : 0;
    packet->orderedGroupId      = sOrderedPackets ? sCurrentOrderedGroupId : 0;
    packet->orderedSeqId        = 0;
    packet->keepSendingAfterDisconnect = false;

    datagram_add_uint8(&packet->dg, packetType);

    // Write Seq Id
    if (reliable) {
        datagram_add_uint16(&packet->dg, sNextSeqNum);
        packet->seqId = sNextSeqNum;
        sNextSeqNum++;
        if (sNextSeqNum == 0) { sNextSeqNum++;  }
    } else {
        u16 nullSeqNum = 0;
        datagram_add_uint16(&packet->dg, nullSeqNum);
    }

    // Write packet flags
    u8 flags = 0;
    datagram_add_uint8(&packet->dg, flags); // Fill in the byte
    packet_set_flags(packet);

    // Write destination
    u8 destination = PACKET_DESTINATION_BROADCAST;
    datagram_add_uint8(&packet->dg, destination);

    // Write ordered packet information
    if (sOrderedPackets) {
        datagram_add_uint8(&packet->dg, packet->orderedFromGlobalId);
        datagram_add_uint16(&packet->dg, packet->orderedGroupId);
        datagram_add_uint16(&packet->dg, packet->orderedSeqId);
    }

    // Write game location
    if (packet->levelAreaMustMatch) {
        datagram_add_uint8(&packet->dg, gCurrCourseNum);
        datagram_add_uint8(&packet->dg, gCurrActStarNum);
        datagram_add_int16(&packet->dg, gCurrLevelNum);
        datagram_add_uint8(&packet->dg, gCurrAreaIndex);
        packet->courseNum = gCurrCourseNum;
        packet->actNum    = gCurrActStarNum;
        packet->levelNum  = gCurrLevelNum;
        packet->areaIndex = gCurrAreaIndex;
    } else if (packet->levelMustMatch) {
        datagram_add_uint8(&packet->dg, gCurrCourseNum);
        datagram_add_uint8(&packet->dg, gCurrActStarNum);
        datagram_add_int16(&packet->dg, gCurrLevelNum);
        packet->courseNum = gCurrCourseNum;
        packet->actNum    = gCurrActStarNum;
        packet->levelNum  = gCurrLevelNum;
    }
}

OPTIMIZE_O3 void packet_duplicate(struct Packet *srcPacket, struct Packet *dstPacket) {
    dstPacket->packetType = srcPacket->packetType;
    dstPacket->reliable = srcPacket->reliable;
    dstPacket->levelAreaMustMatch = srcPacket->levelAreaMustMatch;
    dstPacket->levelMustMatch = srcPacket->levelMustMatch;
    dstPacket->requestBroadcast = srcPacket->requestBroadcast;
    dstPacket->destGlobalId = srcPacket->destGlobalId;
    dstPacket->sent = false;
    dstPacket->orderedGroupId = srcPacket->orderedGroupId;
    dstPacket->orderedSeqId = srcPacket->orderedSeqId;
    dstPacket->courseNum = srcPacket->courseNum;
    dstPacket->actNum    = srcPacket->actNum;
    dstPacket->levelNum  = srcPacket->levelNum;
    dstPacket->areaIndex = srcPacket->areaIndex;
    datagram_copy(&srcPacket->dg, &dstPacket->dg);

    if (dstPacket->reliable) {
        dstPacket->seqId = sNextSeqNum;
        sNextSeqNum++;
        if (sNextSeqNum == 0) { sNextSeqNum++; }
    } else {
        dstPacket->seqId = 0;
    }
    // Preserve the old cursor position.
    u32 old_pos = datagram_cursor_position(&dstPacket->dg);
    datagram_seek(&dstPacket->dg, PACKET_SEQ_ID_OFFSET);
    datagram_write_uint16(&dstPacket->dg, dstPacket->seqId);
    datagram_seek(&dstPacket->dg, old_pos);
}

OPTIMIZE_O3 void packet_set_flags(struct Packet *packet) {
    u8 flags = 0;
    flags |= SET_BIT(packet->levelAreaMustMatch,  0);
    flags |= SET_BIT(packet->requestBroadcast,    1);
    flags |= SET_BIT(packet->orderedGroupId != 0, 2);
    flags |= SET_BIT(packet->levelMustMatch,      3);

    // Preserve the old cursor position.
    u32 old_pos = datagram_cursor_position(&packet->dg);
    datagram_seek(&packet->dg, PACKET_FLAG_OFFSET);
    datagram_write_uint8(&packet->dg, flags);
    datagram_seek(&packet->dg, old_pos);
}

OPTIMIZE_O3 void packet_set_destination(struct Packet *packet, u8 destGlobalId) {
    // Preserve the old cursor position.
    u32 old_pos = datagram_cursor_position(&packet->dg);
    datagram_seek(&packet->dg, PACKET_DESTINATION_OFFSET);
    datagram_write_uint8(&packet->dg, destGlobalId);
    datagram_seek(&packet->dg, old_pos);
}

OPTIMIZE_O3 u8 packet_initial_read(struct Packet *packet) {
    datagram_seek_start(&packet->dg);
    
    // Read packet type
    packet->packetType = datagram_read_uint8(&packet->dg);
    
    // Read sequence ID
    packet->seqId = datagram_read_uint16(&packet->dg);

    // Read packet flags
    u8 flags = datagram_read_uint8(&packet->dg);
    packet->levelAreaMustMatch = GET_BIT(flags, 0);
    packet->requestBroadcast   = GET_BIT(flags, 1);
    bool packetIsOrdered       = GET_BIT(flags, 2);
    packet->levelMustMatch     = GET_BIT(flags, 3);

    // Read destination
    packet->destGlobalId = datagram_read_uint8(&packet->dg);

    // Read ordered packet information
    if (packetIsOrdered) {
        packet->orderedFromGlobalId = datagram_read_uint8(&packet->dg);
        packet->orderedGroupId = datagram_read_uint16(&packet->dg);
        packet->orderedSeqId = datagram_read_uint16(&packet->dg);
    }

    // Read game location
    if (packet->levelAreaMustMatch) {
        packet->courseNum = datagram_read_uint8(&packet->dg);
        packet->actNum = datagram_read_uint8(&packet->dg);
        packet->levelNum = datagram_read_int16(&packet->dg);
        packet->areaIndex = datagram_read_uint8(&packet->dg);
    } else if (packet->levelMustMatch) {
        packet->courseNum = datagram_read_uint8(&packet->dg);
        packet->actNum = datagram_read_uint8(&packet->dg);
        packet->levelNum = datagram_read_int16(&packet->dg);
    }

    // Don't drop packet
    return TRUE;
}

OPTIMIZE_O3 bool packet_check_hash(struct Packet *packet) {
    if (!packet) { return FALSE; }
    
    u32 length = datagram_length(&packet->dg);
    if (length < 4) { return FALSE; }
    u32 localHash = datagram_hash(&packet->dg, length - 4);
    
    u32 old_pos = datagram_cursor_position(&packet->dg);
    datagram_seek(&packet->dg, length - 4);
    if (datagram_has_seek_error(&packet->dg)) { return FALSE; }
    u32 packetHash = datagram_read_uint32(&packet->dg);
    if (datagram_has_read_error(&packet->dg)) { return FALSE; }
    datagram_seek(&packet->dg, old_pos);
    return localHash == packetHash;
}

OPTIMIZE_O3 void packet_ordered_begin(void) {
    if (sOrderedPackets) { return; }
    sOrderedPackets = true;

    sCurrentOrderedGroupId++;
    if (sCurrentOrderedGroupId == 0) { sCurrentOrderedGroupId++; }
    sCurrentOrderedSeqId = 1;
}

OPTIMIZE_O3 void packet_ordered_end(void) {
    sOrderedPackets = false;
    sCurrentOrderedSeqId = 0;
}

OPTIMIZE_O3 void packet_set_ordered_data(struct Packet *packet) {
    if (packet->orderedGroupId == 0) { return; }
    if (packet->orderedSeqId != 0) { return; }
    packet->orderedSeqId = sCurrentOrderedSeqId++;
    
    // Preserve the old cursor position.
    u32 old_pos = datagram_cursor_position(&packet->dg);
    datagram_seek(&packet->dg, PACKET_ORDERED_SEQ_ID_OFFSET);
    datagram_write_uint16(&packet->dg, packet->orderedSeqId);
    datagram_seek(&packet->dg, old_pos);
}