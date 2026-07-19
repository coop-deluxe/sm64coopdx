#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../network.h"
#include "object_fields.h"
#include "behavior_data.h"
#include "game/behavior_actions.h"
#include "pc/debuglog.h"
#include "pc/configfile.h"
#include "pc/network/moderator_list.h"

#define NETWORK_PLAYERS_CHUNK_HEADER_SIZE \
    (sizeof(u16) + sizeof(u8) + sizeof(u8) + sizeof(u8) + sizeof(u8))

#define NETWORK_PLAYER_ENTRY_SIZE ( \
    sizeof(u8) + \
    sizeof(u8) + \
    sizeof(u16) + \
    sizeof(s16) + \
    sizeof(s16) + \
    sizeof(s16) + \
    sizeof(s16) + \
    sizeof(u8) + \
    sizeof(u8) + \
    sizeof(s64) + \
    sizeof(u8) + \
    sizeof(struct PlayerPalette) + \
    (sizeof(u8) * MAX_CONFIG_STRING) + \
    (sizeof(u8) * 64) \
)

#define NETWORK_PLAYERS_GLOBAL_BITMAP_SIZE ((MAX_PLAYERS + 7) / 8)
#define NETWORK_PLAYERS_CHUNK_BITMAP_SIZE 32

STATIC_ASSERT(
    PACKET_BASE_HEADER_LENGTH
        + NETWORK_PLAYERS_CHUNK_HEADER_SIZE
        + NETWORK_PLAYER_ENTRY_SIZE
        <= PACKET_DATA_LENGTH,
    "network player roster entry must fit inside one packet"
);
STATIC_ASSERT(
    NETWORK_PLAYERS_CHUNK_BITMAP_SIZE * 8 > 254,
    "network player roster chunk bitmap must cover every u8 chunk index"
);

struct NetworkPlayerRosterEntry {
    u8 type;
    u8 globalIndex;
    u16 levelAreaSeqId;
    s16 courseNum;
    s16 actNum;
    s16 levelNum;
    s16 areaIndex;
    u8 levelSyncValid;
    u8 areaSyncValid;
    s64 networkId;
    u8 modelIndex;
    struct PlayerPalette palette;
    char playerName[MAX_CONFIG_STRING];
    char discordId[64];
};

struct NetworkPlayersReceiveState {
    bool active;
    u16 generation;
    u8 connectedCount;
    u8 chunkCount;
    u8 receivedChunkCount;
    u8 seenPlayerCount;
    u8 receivedChunks[NETWORK_PLAYERS_CHUNK_BITMAP_SIZE];
    u8 seenGlobalIndices[NETWORK_PLAYERS_GLOBAL_BITMAP_SIZE];
};

static u16 sNetworkPlayersGeneration = 0;
static struct NetworkPlayersReceiveState sNetworkPlayersReceiveState = { 0 };

static bool network_players_bitmap_contains(const u8* bitmap, u8 index) {
    return (bitmap[index >> 3] & (1u << (index & 7))) != 0;
}

static void network_players_bitmap_add(u8* bitmap, u8 index) {
    bitmap[index >> 3] |= (1u << (index & 7));
}

static u16 network_players_entries_per_chunk(void) {
    u32 headerSize = PACKET_BASE_HEADER_LENGTH
                   + NETWORK_PLAYERS_CHUNK_HEADER_SIZE;
    if (headerSize >= PACKET_DATA_LENGTH) { return 0; }

    return (u16)(
        (PACKET_DATA_LENGTH - headerSize)
        / NETWORK_PLAYER_ENTRY_SIZE
    );
}

static u8 network_players_expected_chunk_count(
    u8 connectedCount,
    u16 entriesPerChunk
) {
    if (entriesPerChunk == 0) { return 0; }
    if (connectedCount == 0) { return 1; }

    return (u8)(
        ((u16)connectedCount + entriesPerChunk - 1)
        / entriesPerChunk
    );
}

static u8 network_players_expected_entry_count(
    u8 connectedCount,
    u8 chunkIndex,
    u16 entriesPerChunk
) {
    u16 firstEntry = (u16)chunkIndex * entriesPerChunk;
    if (firstEntry >= connectedCount) { return 0; }

    return (u8)MIN(
        (u16)connectedCount - firstEntry,
        entriesPerChunk
    );
}

static bool network_players_generation_is_newer(
    u16 candidate,
    u16 current
) {
    return (s16)(candidate - current) > 0;
}

static void network_players_begin_receive(
    u16 generation,
    u8 connectedCount,
    u8 chunkCount
) {
    memset(
        &sNetworkPlayersReceiveState,
        0,
        sizeof(sNetworkPlayersReceiveState)
    );
    sNetworkPlayersReceiveState.active = true;
    sNetworkPlayersReceiveState.generation = generation;
    sNetworkPlayersReceiveState.connectedCount = connectedCount;
    sNetworkPlayersReceiveState.chunkCount = chunkCount;
}

void network_reset_network_players_roster(void) {
    memset(
        &sNetworkPlayersReceiveState,
        0,
        sizeof(sNetworkPlayersReceiveState)
    );
}

static u16 network_players_next_generation(void) {
    sNetworkPlayersGeneration++;
    if (sNetworkPlayersGeneration == 0) {
        sNetworkPlayersGeneration++;
    }
    return sNetworkPlayersGeneration;
}

static void network_players_write_entry(
    struct Packet* p,
    u8 localIndex,
    u8 sendToLocalIndex
) {
    struct NetworkPlayer* np = &gNetworkPlayers[localIndex];

    u8 npType = np->type;
    if (npType == NPT_LOCAL) {
        npType = NPT_SERVER;
    } else if (localIndex == sendToLocalIndex) {
        npType = NPT_LOCAL;
    }

    s64 networkId = gNetworkSystem->get_id(localIndex);
    packet_write(p, &npType,                    sizeof(u8));
    packet_write(p, &np->globalIndex,           sizeof(u8));
    packet_write(p, &np->currLevelAreaSeqId,    sizeof(u16));
    packet_write(p, &np->currCourseNum,         sizeof(s16));
    packet_write(p, &np->currActNum,            sizeof(s16));
    packet_write(p, &np->currLevelNum,          sizeof(s16));
    packet_write(p, &np->currAreaIndex,         sizeof(s16));
    packet_write(p, &np->currLevelSyncValid,    sizeof(u8));
    packet_write(p, &np->currAreaSyncValid,     sizeof(u8));
    packet_write(p, &networkId,                 sizeof(s64));
    packet_write(p, &np->modelIndex,            sizeof(u8));
    packet_write(p, &np->palette,               sizeof(struct PlayerPalette));
    packet_write(p, &np->name,                  sizeof(u8) * MAX_CONFIG_STRING);
    packet_write(p, &np->discordId,             sizeof(u8) * 64);

    LOG_INFO("send network player [%d == %d]", np->globalIndex, npType);
}

static void network_send_to_network_players(
    u8 sendToLocalIndex,
    u16 generation
) {
    SOFT_ASSERT(gNetworkType == NT_SERVER);
    SOFT_ASSERT(sendToLocalIndex != 0);

    u8 connectedLocalIndices[MAX_PLAYERS] = { 0 };
    u8 connectedCount = 0;

    for (u16 i = 0; i < MAX_PLAYERS; i++) {
        if (!gNetworkPlayers[i].connected) { continue; }
        connectedLocalIndices[connectedCount++] = (u8)i;
    }

    u16 entriesPerChunk = network_players_entries_per_chunk();
    if (entriesPerChunk == 0) {
        LOG_ERROR(
            "network player entry is too large: entry=%u capacity=%u",
            (u32)NETWORK_PLAYER_ENTRY_SIZE,
            (u32)PACKET_DATA_LENGTH
        );
        return;
    }

    u8 chunkCount = network_players_expected_chunk_count(
        connectedCount,
        entriesPerChunk
    );
    if (chunkCount == 0) {
        LOG_ERROR("failed to calculate network player chunk count");
        return;
    }

    for (u8 chunkIndex = 0; chunkIndex < chunkCount; chunkIndex++) {
        u16 firstEntry = (u16)chunkIndex * entriesPerChunk;
        u8 entryCount = network_players_expected_entry_count(
            connectedCount,
            chunkIndex,
            entriesPerChunk
        );

        struct Packet p = { 0 };
        packet_init(&p, PACKET_NETWORK_PLAYERS, true, PLMT_NONE);
        packet_write(&p, &generation,     sizeof(u16));
        packet_write(&p, &connectedCount, sizeof(u8));
        packet_write(&p, &chunkIndex,     sizeof(u8));
        packet_write(&p, &chunkCount,     sizeof(u8));
        packet_write(&p, &entryCount,     sizeof(u8));

        for (u8 entryIndex = 0; entryIndex < entryCount; entryIndex++) {
            u8 localIndex = connectedLocalIndices[firstEntry + entryIndex];
            network_players_write_entry(&p, localIndex, sendToLocalIndex);
        }

        if (p.writeError) {
            LOG_ERROR(
                "failed to build network player chunk %u/%u",
                chunkIndex + 1,
                chunkCount
            );
            return;
        }

        network_send_to(sendToLocalIndex, &p);
        LOG_INFO(
            "sent network player chunk %u/%u with %u of %u players to %u",
            chunkIndex + 1,
            chunkCount,
            entryCount,
            connectedCount,
            sendToLocalIndex
        );
    }
}

void network_send_network_players_request(void) {
    SOFT_ASSERT(gNetworkType == NT_CLIENT);
    network_reset_network_players_roster();

    struct Packet p = { 0 };
    packet_init(&p, PACKET_NETWORK_PLAYERS_REQUEST, true, PLMT_NONE);
    network_send_to(
        (gNetworkPlayerServer != NULL)
            ? gNetworkPlayerServer->localIndex
            : 0,
        &p
    );
    LOG_INFO("sending network players request");
}

void network_receive_network_players_request(struct Packet* p) {
    SOFT_ASSERT(gNetworkType == NT_SERVER);
    u8 localIndex = p->localIndex;
    if (localIndex == UNKNOWN_LOCAL_INDEX || localIndex >= MAX_PLAYERS) {
        LOG_ERROR("Received network players request from unknown index");
        return;
    }

    network_send_to_network_players(
        localIndex,
        network_players_next_generation()
    );

    if (moderator_list_contains(gNetworkSystem->get_id_str(p->localIndex))) {
        LOG_INFO("sending moderator packet to localIndex: %d", p->localIndex);
        network_send_moderator(p->localIndex);
    }
}

void network_send_network_players(u8 exceptLocalIndex) {
    SOFT_ASSERT(gNetworkType == NT_SERVER);
    LOG_INFO("sending list of network players to all");

    u16 generation = network_players_next_generation();
    for (s32 i = 1; i < MAX_PLAYERS; i++) {
        if (!gNetworkPlayers[i].connected) { continue; }
        if (i == exceptLocalIndex) { continue; }
        network_send_to_network_players((u8)i, generation);
    }
}

static bool network_players_read_entry(
    struct Packet* p,
    struct NetworkPlayerRosterEntry* entry
) {
    packet_read(p, &entry->type,             sizeof(u8));
    packet_read(p, &entry->globalIndex,      sizeof(u8));
    packet_read(p, &entry->levelAreaSeqId,   sizeof(u16));
    packet_read(p, &entry->courseNum,        sizeof(s16));
    packet_read(p, &entry->actNum,           sizeof(s16));
    packet_read(p, &entry->levelNum,         sizeof(s16));
    packet_read(p, &entry->areaIndex,        sizeof(s16));
    packet_read(p, &entry->levelSyncValid,   sizeof(u8));
    packet_read(p, &entry->areaSyncValid,    sizeof(u8));
    packet_read(p, &entry->networkId,        sizeof(s64));
    packet_read(p, &entry->modelIndex,       sizeof(u8));
    packet_read(p, &entry->palette,          sizeof(struct PlayerPalette));
    packet_read(p, &entry->playerName,       sizeof(u8) * MAX_CONFIG_STRING);
    packet_read(p, &entry->discordId,        sizeof(u8) * 64);

    entry->playerName[MAX_CONFIG_STRING - 1] = '\0';
    entry->discordId[63] = '\0';
    return !p->error;
}

static bool network_players_entry_valid(
    const struct NetworkPlayerRosterEntry* entry
) {
    if (entry->globalIndex >= MAX_PLAYERS) { return false; }
    if (entry->type <= NPT_UNKNOWN || entry->type > NPT_CLIENT) {
        return false;
    }
    if (entry->globalIndex == 0 && entry->type != NPT_SERVER) {
        return false;
    }
    if (entry->globalIndex != 0 && entry->type == NPT_SERVER) {
        return false;
    }
    if (gNetworkPlayerLocal != NULL) {
        bool isLocalGlobalIndex = (
            entry->globalIndex == gNetworkPlayerLocal->globalIndex
        );
        if (isLocalGlobalIndex != (entry->type == NPT_LOCAL)) {
            return false;
        }
    }
    return true;
}

static bool network_players_apply_entry(
    const struct NetworkPlayerRosterEntry* entry
) {
    u8 localIndex = network_player_connected(
        entry->type,
        entry->globalIndex,
        entry->modelIndex,
        &entry->palette,
        entry->playerName,
        entry->discordId
    );
    LOG_INFO(
        "received network player [%d == %d] (%d)",
        entry->globalIndex,
        entry->type,
        localIndex
    );

    if (localIndex == UNKNOWN_LOCAL_INDEX || localIndex >= MAX_PLAYERS) {
        return false;
    }

    struct NetworkPlayer* np = &gNetworkPlayers[localIndex];
    if (localIndex != 0) {
        np->currLevelAreaSeqId = entry->levelAreaSeqId;
        np->currLevelSyncValid = entry->levelSyncValid;
        np->currAreaSyncValid = entry->areaSyncValid;
        network_player_update_course_level(
            np,
            entry->courseNum,
            entry->actNum,
            entry->levelNum,
            entry->areaIndex
        );
        LOG_INFO(
            "received network player location (%d, %d, %d, %d)",
            entry->courseNum,
            entry->actNum,
            entry->levelNum,
            entry->areaIndex
        );
        if (entry->globalIndex != 0) {
            gNetworkSystem->save_id(localIndex, entry->networkId);
        }
    } else {
        np->modelIndex = (entry->modelIndex < CT_MAX)
                       ? entry->modelIndex
                       : 0;
        np->palette = entry->palette;
        network_player_update_model(localIndex);
    }

    return true;
}

static bool network_players_roster_has_required_players(void) {
    if (!network_players_bitmap_contains(
        sNetworkPlayersReceiveState.seenGlobalIndices,
        0
    )) {
        return false;
    }
    if (
        gNetworkPlayerLocal == NULL
        || gNetworkPlayerLocal->globalIndex >= MAX_PLAYERS
    ) {
        return false;
    }
    return network_players_bitmap_contains(
        sNetworkPlayersReceiveState.seenGlobalIndices,
        gNetworkPlayerLocal->globalIndex
    );
}

static void network_players_reconcile_completed_roster(void) {
    u8 staleGlobalIndices[MAX_PLAYERS] = { 0 };
    u8 staleCount = 0;

    for (u16 i = 1; i < MAX_PLAYERS; i++) {
        struct NetworkPlayer* np = &gNetworkPlayers[i];
        if (!np->connected) { continue; }
        if (np == gNetworkPlayerLocal || np == gNetworkPlayerServer) {
            continue;
        }
        if (np->globalIndex >= MAX_PLAYERS) { continue; }
        if (network_players_bitmap_contains(
            sNetworkPlayersReceiveState.seenGlobalIndices,
            np->globalIndex
        )) {
            continue;
        }
        staleGlobalIndices[staleCount++] = np->globalIndex;
    }

    for (u8 i = 0; i < staleCount; i++) {
        network_player_disconnected(staleGlobalIndices[i]);
    }
}

void network_receive_network_players(struct Packet* p) {
    LOG_INFO("receiving network player chunk");
    if (gNetworkType != NT_CLIENT) {
        LOG_ERROR("received list of clients as a non-client");
        return;
    }
    if (network_player_any_connected()) {
        if (
            p->localIndex >= MAX_PLAYERS
            || gNetworkPlayers[p->localIndex].type != NPT_SERVER
        ) {
            LOG_ERROR("list of clients came from non-server... refuse!");
            return;
        }
    }

    u16 generation = 0;
    u8 connectedCount = 0;
    u8 chunkIndex = 0;
    u8 chunkCount = 0;
    u8 entryCount = 0;

    packet_read(p, &generation,     sizeof(u16));
    packet_read(p, &connectedCount, sizeof(u8));
    packet_read(p, &chunkIndex,     sizeof(u8));
    packet_read(p, &chunkCount,     sizeof(u8));
    packet_read(p, &entryCount,     sizeof(u8));

    if (p->error) {
        LOG_ERROR("malformed network player chunk header");
        return;
    }

    u16 entriesPerChunk = network_players_entries_per_chunk();
    u8 expectedChunkCount = network_players_expected_chunk_count(
        connectedCount,
        entriesPerChunk
    );
    u8 expectedEntryCount = network_players_expected_entry_count(
        connectedCount,
        chunkIndex,
        entriesPerChunk
    );

    if (
        generation == 0
        || connectedCount == 0
        || connectedCount > MAX_PLAYERS
        || entriesPerChunk == 0
        || chunkCount == 0
        || chunkCount != expectedChunkCount
        || chunkIndex >= chunkCount
        || entryCount != expectedEntryCount
    ) {
        LOG_ERROR(
            "invalid network player chunk metadata: generation=%u total=%u chunk=%u/%u entries=%u",
            generation,
            connectedCount,
            chunkIndex + 1,
            chunkCount,
            entryCount
        );
        return;
    }

    u32 requiredBytes = (u32)entryCount * (u32)NETWORK_PLAYER_ENTRY_SIZE;
    if ((u32)packet_read_remaining(p) != requiredBytes) {
        LOG_ERROR(
            "invalid network player chunk length: need=%u remaining=%u",
            requiredBytes,
            packet_read_remaining(p)
        );
        return;
    }

    if (!sNetworkPlayersReceiveState.active) {
        network_players_begin_receive(
            generation,
            connectedCount,
            chunkCount
        );
    } else if (generation != sNetworkPlayersReceiveState.generation) {
        if (!network_players_generation_is_newer(
            generation,
            sNetworkPlayersReceiveState.generation
        )) {
            LOG_INFO(
                "ignoring stale network player generation %u; current=%u",
                generation,
                sNetworkPlayersReceiveState.generation
            );
            return;
        }
        network_players_begin_receive(
            generation,
            connectedCount,
            chunkCount
        );
    } else if (
        connectedCount != sNetworkPlayersReceiveState.connectedCount
        || chunkCount != sNetworkPlayersReceiveState.chunkCount
    ) {
        LOG_ERROR("network player generation metadata changed mid-stream");
        return;
    }

    if (network_players_bitmap_contains(
        sNetworkPlayersReceiveState.receivedChunks,
        chunkIndex
    )) {
        LOG_INFO(
            "ignoring duplicate network player chunk %u/%u for generation %u",
            chunkIndex + 1,
            chunkCount,
            generation
        );
        return;
    }

    struct NetworkPlayerRosterEntry* entries = calloc(
        entryCount,
        sizeof(struct NetworkPlayerRosterEntry)
    );
    if (entries == NULL) {
        LOG_ERROR("failed to allocate network player roster chunk");
        return;
    }

    u8 prospectiveSeenGlobalIndices[NETWORK_PLAYERS_GLOBAL_BITMAP_SIZE];
    memcpy(
        prospectiveSeenGlobalIndices,
        sNetworkPlayersReceiveState.seenGlobalIndices,
        sizeof(prospectiveSeenGlobalIndices)
    );

    bool valid = true;
    for (u8 i = 0; i < entryCount; i++) {
        if (!network_players_read_entry(p, &entries[i])) {
            LOG_ERROR("malformed network player entry %u", i);
            valid = false;
            break;
        }
        if (!network_players_entry_valid(&entries[i])) {
            LOG_ERROR(
                "invalid network player entry: type=%u global=%u",
                entries[i].type,
                entries[i].globalIndex
            );
            valid = false;
            break;
        }
        if (network_players_bitmap_contains(
            prospectiveSeenGlobalIndices,
            entries[i].globalIndex
        )) {
            LOG_ERROR(
                "duplicate global player index %u in roster generation %u",
                entries[i].globalIndex,
                generation
            );
            valid = false;
            break;
        }
        network_players_bitmap_add(
            prospectiveSeenGlobalIndices,
            entries[i].globalIndex
        );
    }

    if (valid) {
        for (u8 i = 0; i < entryCount; i++) {
            if (!network_players_apply_entry(&entries[i])) {
                LOG_ERROR(
                    "failed to apply network player entry %u",
                    entries[i].globalIndex
                );
                valid = false;
                break;
            }
        }
    }

    free(entries);
    if (!valid) { return; }

    memcpy(
        sNetworkPlayersReceiveState.seenGlobalIndices,
        prospectiveSeenGlobalIndices,
        sizeof(prospectiveSeenGlobalIndices)
    );
    network_players_bitmap_add(
        sNetworkPlayersReceiveState.receivedChunks,
        chunkIndex
    );
    sNetworkPlayersReceiveState.receivedChunkCount++;
    sNetworkPlayersReceiveState.seenPlayerCount += entryCount;

    LOG_INFO(
        "received network player chunk %u/%u for generation %u (%u total)",
        chunkIndex + 1,
        chunkCount,
        generation,
        connectedCount
    );

    if (
        sNetworkPlayersReceiveState.receivedChunkCount
        != sNetworkPlayersReceiveState.chunkCount
    ) {
        return;
    }

    if (
        sNetworkPlayersReceiveState.seenPlayerCount
        != sNetworkPlayersReceiveState.connectedCount
        || !network_players_roster_has_required_players()
    ) {
        LOG_ERROR(
            "incomplete network player roster generation %u: seen=%u expected=%u",
            generation,
            sNetworkPlayersReceiveState.seenPlayerCount,
            sNetworkPlayersReceiveState.connectedCount
        );
        network_reset_network_players_roster();
        return;
    }

    network_players_reconcile_completed_roster();
    LOG_INFO(
        "completed network player roster generation %u with %u players",
        generation,
        connectedCount
    );
}
