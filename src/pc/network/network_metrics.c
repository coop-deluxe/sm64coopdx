#include <string.h>
#include "network_metrics.h"
#include "network.h"
#include "network_player.h"
#include "pc/debuglog.h"
#include "pc/utils/misc.h"

#define PACKET_TYPE_COUNT 256
#define TOP_PACKET_COUNT 8

typedef struct NetworkPacketMetrics {
    u64 sendDeliveries;
    u64 sendUncompressedBytes;
    u64 sendCompressedBytes;
    f64 compressionSeconds;
    u64 receivePackets;
    u64 receiveCompressedBytes;
    u64 receiveUncompressedBytes;
    f64 decompressionSeconds;
    u64 broadcastCalls;
    u64 broadcastRecipients;
    u32 maxBroadcastRecipients;
    u64 rateLimitedDrops;
    u64 sendErrors;
} NetworkPacketMetrics;

typedef struct NetworkDestinationMetrics {
    u64 packets;
    u64 compressedBytes;
    u64 uncompressedBytes;
} NetworkDestinationMetrics;

static NetworkPacketMetrics sPackets[PACKET_TYPE_COUNT];
static NetworkDestinationMetrics sDestinations[MAX_PLAYERS];
static f64 sStartedAt = 0.0;
static f64 sLastReportAt = 0.0;
static u64 sReceiveErrors = 0;
static u64 sReceiveErrorBytes = 0;
static f64 sReceiveErrorSeconds = 0.0;

static u64 network_metrics_packet_score(const NetworkPacketMetrics* metrics) {
    return metrics->sendCompressedBytes + metrics->receiveCompressedBytes;
}

const char* network_metrics_packet_name(enum PacketType packetType) {
    switch (packetType) {
        case PACKET_ACK: return "ACK";
        case PACKET_PLAYER: return "PLAYER";
        case PACKET_OBJECT: return "OBJECT";
        case PACKET_SPAWN_OBJECTS: return "SPAWN_OBJECTS";
        case PACKET_SPAWN_STAR: return "SPAWN_STAR";
        case PACKET_SPAWN_STAR_NLE: return "SPAWN_STAR_NLE";
        case PACKET_COLLECT_STAR: return "COLLECT_STAR";
        case PACKET_COLLECT_COIN: return "COLLECT_COIN";
        case PACKET_COLLECT_ITEM: return "COLLECT_ITEM";
        case PACKET_GLOBAL_POPUP: return "GLOBAL_POPUP";
        case PACKET_DEBUG_SYNC: return "DEBUG_SYNC";
        case PACKET_JOIN_REQUEST: return "JOIN_REQUEST";
        case PACKET_JOIN: return "JOIN";
        case PACKET_CHAT: return "CHAT";
        case PACKET_KICK: return "KICK";
        case PACKET_KEEP_ALIVE: return "KEEP_ALIVE";
        case PACKET_LEAVING: return "LEAVING";
        case PACKET_SAVE_FILE: return "SAVE_FILE";
        case PACKET_SAVE_SET_FLAG: return "SAVE_SET_FLAG";
        case PACKET_SAVE_REMOVE_FLAG: return "SAVE_REMOVE_FLAG";
        case PACKET_NETWORK_PLAYERS: return "NETWORK_PLAYERS";
        case PACKET_DEATH: return "DEATH";
        case PACKET_PING: return "PING";
        case PACKET_PONG: return "PONG";
        case PACKET_CHANGE_LEVEL: return "CHANGE_LEVEL";
        case PACKET_CHANGE_AREA: return "CHANGE_AREA";
        case PACKET_LEVEL_AREA_REQUEST: return "LEVEL_AREA_REQUEST";
        case PACKET_LEVEL_REQUEST: return "LEVEL_REQUEST";
        case PACKET_LEVEL: return "LEVEL";
        case PACKET_AREA_REQUEST: return "AREA_REQUEST";
        case PACKET_AREA: return "AREA";
        case PACKET_SYNC_VALID: return "SYNC_VALID";
        case PACKET_LEVEL_SPAWN_INFO: return "LEVEL_SPAWN_INFO";
        case PACKET_LEVEL_MACRO: return "LEVEL_MACRO";
        case PACKET_LEVEL_AREA_INFORM: return "LEVEL_AREA_INFORM";
        case PACKET_LEVEL_RESPAWN_INFO: return "LEVEL_RESPAWN_INFO";
        case PACKET_CHANGE_WATER_LEVEL: return "CHANGE_WATER_LEVEL";
        case PACKET_PLAYER_SETTINGS: return "PLAYER_SETTINGS";
        case PACKET_MOD_LIST_REQUEST: return "MOD_LIST_REQUEST";
        case PACKET_MOD_LIST: return "MOD_LIST";
        case PACKET_DOWNLOAD_REQUEST: return "DOWNLOAD_REQUEST";
        case PACKET_DOWNLOAD: return "DOWNLOAD";
        case PACKET_MOD_LIST_ENTRY: return "MOD_LIST_ENTRY";
        case PACKET_MOD_LIST_FILE: return "MOD_LIST_FILE";
        case PACKET_MOD_LIST_DONE: return "MOD_LIST_DONE";
        case PACKET_LUA_SYNC_TABLE_REQUEST: return "LUA_SYNC_TABLE_REQUEST";
        case PACKET_LUA_SYNC_TABLE: return "LUA_SYNC_TABLE";
        case PACKET_NETWORK_PLAYERS_REQUEST: return "NETWORK_PLAYERS_REQUEST";
        case PACKET_REQUEST_FAILED: return "REQUEST_FAILED";
        case PACKET_LUA_CUSTOM: return "LUA_CUSTOM";
        case PACKET_LUA_CUSTOM_BYTESTRING: return "LUA_CUSTOM_BYTESTRING";
        case PACKET_COMMAND: return "COMMAND";
        case PACKET_MODERATOR: return "MODERATOR";
        case PACKET_CUSTOM: return "CUSTOM";
        default: return "UNKNOWN";
    }
}

void network_metrics_reset(void) {
#if DENSE_NETWORK_METRICS
    memset(sPackets, 0, sizeof(sPackets));
    memset(sDestinations, 0, sizeof(sDestinations));
    sReceiveErrors = 0;
    sReceiveErrorBytes = 0;
    sReceiveErrorSeconds = 0.0;
    sStartedAt = clock_elapsed_f64();
    sLastReportAt = sStartedAt;
#endif
}

void network_metrics_record_broadcast(enum PacketType packetType, u32 recipients) {
#if DENSE_NETWORK_METRICS
    NetworkPacketMetrics* metrics = &sPackets[(u8)packetType];
    metrics->broadcastCalls++;
    metrics->broadcastRecipients += recipients;
    if (recipients > metrics->maxBroadcastRecipients) {
        metrics->maxBroadcastRecipients = recipients;
    }
#else
    (void)packetType;
    (void)recipients;
#endif
}

void network_metrics_record_send(
    enum PacketType packetType,
    u8 localIndex,
    u32 uncompressedBytes,
    u32 compressedBytes,
    f64 compressionSeconds
) {
#if DENSE_NETWORK_METRICS
    NetworkPacketMetrics* metrics = &sPackets[(u8)packetType];
    metrics->sendDeliveries++;
    metrics->sendUncompressedBytes += uncompressedBytes;
    metrics->sendCompressedBytes += compressedBytes;
    metrics->compressionSeconds += compressionSeconds;

    if (localIndex < MAX_PLAYERS) {
        sDestinations[localIndex].packets++;
        sDestinations[localIndex].compressedBytes += compressedBytes;
        sDestinations[localIndex].uncompressedBytes += uncompressedBytes;
    }
#else
    (void)packetType;
    (void)localIndex;
    (void)uncompressedBytes;
    (void)compressedBytes;
    (void)compressionSeconds;
#endif
}

void network_metrics_record_send_drop(enum PacketType packetType, bool rateLimited) {
#if DENSE_NETWORK_METRICS
    if (rateLimited) {
        sPackets[(u8)packetType].rateLimitedDrops++;
    }
#else
    (void)packetType;
    (void)rateLimited;
#endif
}

void network_metrics_record_send_error(enum PacketType packetType) {
#if DENSE_NETWORK_METRICS
    sPackets[(u8)packetType].sendErrors++;
#else
    (void)packetType;
#endif
}

void network_metrics_record_receive(
    enum PacketType packetType,
    u8 localIndex,
    u32 compressedBytes,
    u32 uncompressedBytes,
    f64 decompressionSeconds
) {
#if DENSE_NETWORK_METRICS
    NetworkPacketMetrics* metrics = &sPackets[(u8)packetType];
    metrics->receivePackets++;
    metrics->receiveCompressedBytes += compressedBytes;
    metrics->receiveUncompressedBytes += uncompressedBytes;
    metrics->decompressionSeconds += decompressionSeconds;
    (void)localIndex;
#else
    (void)packetType;
    (void)localIndex;
    (void)compressedBytes;
    (void)uncompressedBytes;
    (void)decompressionSeconds;
#endif
}

void network_metrics_record_receive_error(u32 compressedBytes, f64 decompressionSeconds) {
#if DENSE_NETWORK_METRICS
    sReceiveErrors++;
    sReceiveErrorBytes += compressedBytes;
    sReceiveErrorSeconds += decompressionSeconds;
#else
    (void)compressedBytes;
    (void)decompressionSeconds;
#endif
}

static void network_metrics_find_top_packets(u8 output[TOP_PACKET_COUNT]) {
    bool selected[PACKET_TYPE_COUNT] = { false };
    for (u32 rank = 0; rank < TOP_PACKET_COUNT; rank++) {
        u8 bestType = 0;
        u64 bestScore = 0;
        bool found = false;
        for (u32 packetType = 0; packetType < PACKET_TYPE_COUNT; packetType++) {
            if (selected[packetType]) { continue; }
            u64 score = network_metrics_packet_score(&sPackets[packetType]);
            if (!found || score > bestScore) {
                found = true;
                bestType = (u8)packetType;
                bestScore = score;
            }
        }
        output[rank] = bestType;
        selected[bestType] = true;
    }
}

void network_metrics_report(bool finalReport) {
#if DENSE_NETWORK_METRICS
    f64 now = clock_elapsed_f64();
    f64 elapsed = now - sStartedAt;
    if (elapsed <= 0.0) { return; }

    u64 sendPackets = 0;
    u64 sendRaw = 0;
    u64 sendWire = 0;
    u64 receivePackets = 0;
    u64 receiveRaw = 0;
    u64 receiveWire = 0;
    u64 broadcastCalls = 0;
    u64 broadcastRecipients = 0;
    u64 rateDrops = 0;
    u64 sendErrors = 0;
    f64 compressionSeconds = 0.0;
    f64 decompressionSeconds = 0.0;

    for (u32 packetType = 0; packetType < PACKET_TYPE_COUNT; packetType++) {
        NetworkPacketMetrics* metrics = &sPackets[packetType];
        sendPackets += metrics->sendDeliveries;
        sendRaw += metrics->sendUncompressedBytes;
        sendWire += metrics->sendCompressedBytes;
        receivePackets += metrics->receivePackets;
        receiveRaw += metrics->receiveUncompressedBytes;
        receiveWire += metrics->receiveCompressedBytes;
        broadcastCalls += metrics->broadcastCalls;
        broadcastRecipients += metrics->broadcastRecipients;
        rateDrops += metrics->rateLimitedDrops;
        sendErrors += metrics->sendErrors;
        compressionSeconds += metrics->compressionSeconds;
        decompressionSeconds += metrics->decompressionSeconds;
    }

    if (!finalReport && sendPackets == 0 && receivePackets == 0 && sReceiveErrors == 0) {
        sLastReportAt = now;
        return;
    }

    f64 ratio = (sendRaw > 0) ? ((f64)sendWire / (f64)sendRaw) : 0.0;
    f64 averageFanout = (broadcastCalls > 0)
        ? ((f64)broadcastRecipients / (f64)broadcastCalls)
        : 0.0;

    LOG_INFO(
        "[dense-net] %s %.1fs peers=%u tx=%llu packets %.2f MiB wire %.2f MiB raw ratio=%.3f %.1f KiB/s compress=%.3f ms",
        finalReport ? "final" : "report",
        elapsed,
        network_player_connected_count(),
        (unsigned long long)sendPackets,
        (double)sendWire / (1024.0 * 1024.0),
        (double)sendRaw / (1024.0 * 1024.0),
        ratio,
        ((double)sendWire / 1024.0) / elapsed,
        compressionSeconds * 1000.0
    );
    LOG_INFO(
        "[dense-net] rx=%llu packets %.2f MiB wire %.2f MiB raw %.1f KiB/s decompress=%.3f ms broadcast=%llu avg-fanout=%.2f drops=%llu send-errors=%llu rx-errors=%llu",
        (unsigned long long)receivePackets,
        (double)receiveWire / (1024.0 * 1024.0),
        (double)receiveRaw / (1024.0 * 1024.0),
        ((double)receiveWire / 1024.0) / elapsed,
        decompressionSeconds * 1000.0,
        (unsigned long long)broadcastCalls,
        averageFanout,
        (unsigned long long)rateDrops,
        (unsigned long long)sendErrors,
        (unsigned long long)sReceiveErrors
    );

    u8 topPackets[TOP_PACKET_COUNT];
    network_metrics_find_top_packets(topPackets);
    for (u32 rank = 0; rank < TOP_PACKET_COUNT; rank++) {
        u8 packetType = topPackets[rank];
        NetworkPacketMetrics* metrics = &sPackets[packetType];
        if (network_metrics_packet_score(metrics) == 0) { break; }
        f64 packetRatio = (metrics->sendUncompressedBytes > 0)
            ? ((f64)metrics->sendCompressedBytes / (f64)metrics->sendUncompressedBytes)
            : 0.0;
        f64 packetFanout = (metrics->broadcastCalls > 0)
            ? ((f64)metrics->broadcastRecipients / (f64)metrics->broadcastCalls)
            : 0.0;
        LOG_INFO(
            "[dense-net] top%u type=%u/%s tx=%llu wire=%.1f KiB raw=%.1f KiB ratio=%.3f fanout=%.2f max=%u rx=%llu wire=%.1f KiB",
            rank + 1,
            packetType,
            network_metrics_packet_name((enum PacketType)packetType),
            (unsigned long long)metrics->sendDeliveries,
            (double)metrics->sendCompressedBytes / 1024.0,
            (double)metrics->sendUncompressedBytes / 1024.0,
            packetRatio,
            packetFanout,
            metrics->maxBroadcastRecipients,
            (unsigned long long)metrics->receivePackets,
            (double)metrics->receiveCompressedBytes / 1024.0
        );
    }

    for (u32 i = 1; i < MAX_PLAYERS; i++) {
        if (sDestinations[i].packets == 0) { continue; }
        LOG_INFO(
            "[dense-net] peer local=%u global=%u connected=%u tx=%llu wire=%.1f KiB raw=%.1f KiB",
            i,
            gNetworkPlayers[i].globalIndex,
            gNetworkPlayers[i].connected,
            (unsigned long long)sDestinations[i].packets,
            (double)sDestinations[i].compressedBytes / 1024.0,
            (double)sDestinations[i].uncompressedBytes / 1024.0
        );
    }

    if (sReceiveErrors > 0) {
        LOG_INFO(
            "[dense-net] rx-errors=%llu rejected-wire=%.1f KiB failed-decompress=%.3f ms",
            (unsigned long long)sReceiveErrors,
            (double)sReceiveErrorBytes / 1024.0,
            sReceiveErrorSeconds * 1000.0
        );
    }
    sLastReportAt = now;
#else
    (void)finalReport;
#endif
}

void network_metrics_update(void) {
#if DENSE_NETWORK_METRICS
    f64 now = clock_elapsed_f64();
    if ((now - sLastReportAt) >= DENSE_NETWORK_METRICS_INTERVAL_SEC) {
        network_metrics_report(false);
    }
#endif
}
