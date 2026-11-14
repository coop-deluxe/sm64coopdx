#ifndef PACKET_READ_WRITE_H
#define PACKET_READ_WRITE_H

#include "pc/network/packets/packet_defs.h"

OPTIMIZE_O3 void packet_init(struct Packet *packet, enum PacketType packetType, bool reliable, enum PacketLevelMatchType levelAreaMustMatch);
OPTIMIZE_O3 void packet_duplicate(struct Packet *srcPacket, struct Packet *dstPacket);
OPTIMIZE_O3 void packet_set_flags(struct Packet *packet);
OPTIMIZE_O3 void packet_set_destination(struct Packet *packet, u8 destGlobalId);
OPTIMIZE_O3 u8 packet_initial_read(struct Packet *packet);
OPTIMIZE_O3 bool packet_check_hash(struct Packet *packet);
OPTIMIZE_O3 void packet_ordered_begin(void);
OPTIMIZE_O3 void packet_ordered_end(void);
OPTIMIZE_O3 void packet_ordered_clear_all(void);
OPTIMIZE_O3 void packet_set_ordered_data(struct Packet *packet);

#include "pc/network/packets/packet_read_write.inl"

#endif // PACKET_READ_WRITE_H