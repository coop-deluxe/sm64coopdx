#include <stdio.h>
#include "../network.h"
#include "pc/mod_list.h"
#include "pc/debuglog.h"

#define CHUNK_SIZE 400
#define OFFSET_COUNT 5

static u64 sOffset[OFFSET_COUNT] = { 0 };
static bool sWaitingForOffset[OFFSET_COUNT] = { 0 };

static void network_send_next_download_request(void) {
    SOFT_ASSERT(gNetworkType == NT_CLIENT);
    for (int i = 0; i < sModEntryCount; i++) {
        struct ModListEntry* entry = &gModEntries[i];
        if (entry->complete) { continue; }
        network_send_download_request(i, entry->curOffset);
        return;
    }
    network_send_join_request();
}

void network_send_download_request(u16 index, u64 offset) {
    SOFT_ASSERT(gNetworkType == NT_CLIENT);

    struct Packet p = { 0 };
    packet_init(&p, PACKET_DOWNLOAD_REQUEST, true, PLMT_NONE);

    packet_write(&p, &index, sizeof(u16));
    packet_write(&p, &offset, sizeof(u64));

    struct ModListEntry* entry = &gModEntries[index];
    for (int i = 0; i < OFFSET_COUNT; i++) {
        sOffset[i] = offset + CHUNK_SIZE * i;
        sWaitingForOffset[i] = (sOffset[i] < entry->size);
    }

    network_send_to((gNetworkPlayerServer != NULL) ? gNetworkPlayerServer->localIndex : 0, &p);
}

void network_receive_download_request(struct Packet* p) {
    SOFT_ASSERT(gNetworkType == NT_SERVER);

    u16 index;
    u64 offset;
    packet_read(p, &index, sizeof(u16));
    packet_read(p, &offset, sizeof(u64));

    struct ModListEntry* entry = &gModEntries[index];
    if (index >= sModEntryCount) {
        LOG_ERROR("Requested download of invalid index %u:%llu", index, offset);
        return;
    }

    for (int i = 0; i < OFFSET_COUNT; i++) {
        u64 o = offset + CHUNK_SIZE * i;
        if (o >= entry->size) { break; }
        network_send_download(index, o);
    }
}

void network_send_download(u16 index, u64 offset) {
    SOFT_ASSERT(gNetworkType == NT_SERVER);

    if (index >= sModEntryCount) {
        LOG_ERROR("Requested download of invalid index %u:%llu", index, offset);
        return;
    }

    struct ModListEntry* entry = &gModEntries[index];
    if (offset >= entry->size) {
        LOG_ERROR("Requested download of invalid offset %u:%llu", index, offset);
        return;
    }

    if (entry->fp == NULL) {
        LOG_ERROR("Requested download of invalid file pointer %u:%llu", index, offset);
        return;
    }

    u16 chunkSize = 400;
    if ((offset + chunkSize) > entry->size) {
        chunkSize = entry->size - offset;
    }

    u8 chunk[400] = { 0 };
    fseek(entry->fp, offset, SEEK_SET);
    fread(chunk, chunkSize, 1, entry->fp);

    struct Packet p = { 0 };
    packet_init(&p, PACKET_DOWNLOAD, true, PLMT_NONE);

    packet_write(&p, &index, sizeof(u16));
    packet_write(&p, &offset, sizeof(u64));
    packet_write(&p, &chunkSize, sizeof(u16));
    packet_write(&p, chunk, chunkSize * sizeof(u8));

    network_send_to(0, &p);
}

void network_receive_download(struct Packet* p) {
    SOFT_ASSERT(gNetworkType == NT_CLIENT);
    if (p->localIndex != UNKNOWN_LOCAL_INDEX) {
        LOG_ERROR("Received download from known local index");
        return;
    }

    u16 index;
    u64 offset;
    u16 chunkSize;
    u8 chunk[400] = { 0 };

    packet_read(p, &index, sizeof(u16));
    packet_read(p, &offset, sizeof(u64));
    packet_read(p, &chunkSize, sizeof(u16));
    packet_read(p, chunk, chunkSize * sizeof(u8));

    if (index >= sModEntryCount) {
        LOG_ERROR("Received download of invalid index %u:%llu", index, offset);
        return;
    }

    struct ModListEntry* entry = &gModEntries[index];
    if (offset >= entry->size) {
        LOG_ERROR("Received download of invalid offset %u:%llu", index, offset);
        return;
    }

    if (entry->fp == NULL) {
        LOG_ERROR("Received download of invalid file pointer %u:%llu", index, offset);
        return;
    }

    if ((offset + chunkSize) > entry->size) {
        LOG_ERROR("Received download of invalid chunk size %u:%llu:%u", index, offset, chunkSize);
        return;
    }

    // check if we're still waiting for chunks
    bool found = false;
    bool waiting = false;
    for (int i = 0; i < OFFSET_COUNT; i++) {
        if (sOffset[i] == offset) {
            found = sWaitingForOffset[i];
            sWaitingForOffset[i] = false;
        }
        waiting = waiting || sWaitingForOffset[i];
    }

    if (!found) {
        LOG_ERROR("Received download of unexpected offset %llu != %llu", entry->curOffset, offset);
        return;
    }

    // write to the file
    fseek(entry->fp, offset, SEEK_SET);
    fwrite(chunk, sizeof(u8) * chunkSize, 1, entry->fp);

    if (!waiting) {
        // check if we're finished with this file
        if (sOffset[OFFSET_COUNT - 1] >= entry->size) {
            LOG_INFO("Finished download of '%s'", entry->name);
            fclose(entry->fp);
            entry->fp = NULL;
            entry->complete = true;
        }

        entry->curOffset += CHUNK_SIZE * OFFSET_COUNT;
        network_send_next_download_request();
    }
}
