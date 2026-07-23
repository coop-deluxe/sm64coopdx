#ifndef NETWORK_METRICS_H
#define NETWORK_METRICS_H

#include <PR/ultratypes.h>
#include <stdbool.h>
#include "types.h"
#include "packets/packet.h"

#ifndef DENSE_NETWORK_METRICS
#define DENSE_NETWORK_METRICS 1
#endif

#ifndef DENSE_NETWORK_METRICS_INTERVAL_SEC
#define DENSE_NETWORK_METRICS_INTERVAL_SEC 10.0
#endif

void network_metrics_reset(void);
void network_metrics_update(void);
void network_metrics_report(bool finalReport);

void network_metrics_record_broadcast(enum PacketType packetType, u32 recipients);
void network_metrics_record_send(
    enum PacketType packetType,
    u8 localIndex,
    u32 uncompressedBytes,
    u32 compressedBytes,
    f64 compressionSeconds
);
void network_metrics_record_send_drop(enum PacketType packetType, bool rateLimited);
void network_metrics_record_send_error(enum PacketType packetType);
void network_metrics_record_receive(
    enum PacketType packetType,
    u8 localIndex,
    u32 compressedBytes,
    u32 uncompressedBytes,
    f64 decompressionSeconds
);
void network_metrics_record_receive_error(u32 compressedBytes, f64 decompressionSeconds);

const char* network_metrics_packet_name(enum PacketType packetType);

#endif
