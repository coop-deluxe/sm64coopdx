#include "../network.h"
#include "game/area.h"

#define PACKET_FLAG_BUFFER_OFFSET 3

static u16 nextSeqNum = 1;
void packet_init(struct Packet* packet, enum PacketType packetType, bool reliable, bool levelAreaMustMatch) {
    memset(packet->buffer, 0, PACKET_LENGTH);
    packet->buffer[0] = (char)packetType;
    if (reliable) {
        memcpy(&packet->buffer[1], &nextSeqNum, 2);
        packet->seqId = nextSeqNum;
        nextSeqNum++;
        if (nextSeqNum == 0) { nextSeqNum++;  }
    }
    packet->dataLength = 3;
    packet->cursor = 3;
    packet->error = false;
    packet->reliable = reliable;
    packet->levelAreaMustMatch = levelAreaMustMatch;
    packet->requestBroadcast = false;
    packet->sent = false;

    // write packet flags
    u8 flags = 0;
    packet_write(packet, &flags, sizeof(u8)); // fill in the byte
    packet_set_flags(packet);

    if (levelAreaMustMatch) {
        packet_write(packet, &gCurrLevelNum, sizeof(s16));
        packet_write(packet, &gCurrAreaIndex, sizeof(s16));
    }
}

void packet_set_flags(struct Packet* packet) {
    u8 flags = 0;
    flags |= SET_BIT(packet->levelAreaMustMatch, 0);
    flags |= SET_BIT(packet->requestBroadcast, 1);
    packet->buffer[PACKET_FLAG_BUFFER_OFFSET] = flags;
}

void packet_write(struct Packet* packet, void* data, u16 length) {
    if (data == NULL) { packet->error = true; return; }
    memcpy(&packet->buffer[packet->cursor], data, length);
    packet->dataLength += length;
    packet->cursor += length;
}

u8 packet_initial_read(struct Packet* packet) {
    // read packet flags
    u8 flags = 0;
    packet_read(packet, &flags, sizeof(u8));
    packet->levelAreaMustMatch = GET_BIT(flags, 0);
    packet->requestBroadcast = GET_BIT(flags, 1);

    if (packet->levelAreaMustMatch) {
        s16 currLevelNum;
        s16 currAreaIndex;
        packet_read(packet, &currLevelNum, sizeof(s16));
        packet_read(packet, &currAreaIndex, sizeof(s16));
        if (currLevelNum != gCurrLevelNum || currAreaIndex != gCurrAreaIndex) {
            // drop packet
            return FALSE;
        }
    }

    // don't drop packet
    return TRUE;
}

void packet_read(struct Packet* packet, void* data, u16 length) {
    if (data == NULL) { packet->error = true; return; }
    u16 cursor = packet->cursor;
    memcpy(data, &packet->buffer[cursor], length);
    packet->cursor = cursor + length;
}

u32 packet_hash(struct Packet* packet) {
    u32 hash = 0;
    u16 byte = 0;
    for (u16 i = 0; i < packet->dataLength; i++) {
        hash ^= ((u32)packet->buffer[i]) << (8 * byte);
        byte = (byte + 1) % sizeof(u32);
    }
    return hash;
}

bool packet_check_hash(struct Packet* packet) {
    u32 localHash = packet_hash(packet);
    u32 packetHash = 0;
    memcpy(&packetHash, &packet->buffer[packet->dataLength], sizeof(u32));
    return localHash == packetHash;
}
