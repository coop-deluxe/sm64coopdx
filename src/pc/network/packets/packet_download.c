#include <stdio.h>
#include "../network.h"
#include "pc/djui/djui.h"
#include "pc/mod_list.h"
#include "pc/debuglog.h"

#define CHUNK_SIZE 400
#define OFFSET_COUNT 5

static u64 sOffset[OFFSET_COUNT] = { 0 };
static bool sWaitingForOffset[OFFSET_COUNT] = { 0 };
u64 sTotalDownloadBytes = 0;
extern float gDownloadProgress;

void network_send_next_download_request(void) {
    SOFT_ASSERT(gNetworkType == NT_CLIENT);
    for (int i = 0; i < gModTableRemote.entryCount; i++) {
        struct ModListEntry* entry = &gModTableRemote.entries[i];
        if (entry->complete) { continue; }
        //LOG_INFO("sending download request: %d, %d, %lld", i, entry->remoteIndex, entry->curOffset);
        network_send_download_request(i, entry->remoteIndex, entry->curOffset);
        return;
    }
    //LOG_INFO("sending join request");
    network_send_join_request();
    djui_panel_modlist_create(NULL);
}

void network_send_download_request(u16 clientIndex, u16 serverIndex, u64 offset) {
    SOFT_ASSERT(gNetworkType == NT_CLIENT);

    struct Packet p = { 0 };
    packet_init(&p, PACKET_DOWNLOAD_REQUEST, true, PLMT_NONE);

    packet_write(&p, &clientIndex, sizeof(u16));
    packet_write(&p, &serverIndex, sizeof(u16));
    packet_write(&p, &offset, sizeof(u64));

    if (clientIndex == 0 && offset == 0) {
        sTotalDownloadBytes = 0;
        gDownloadProgress = 0;
    }

    struct ModListEntry* entry = &gModTableRemote.entries[clientIndex];
    for (int i = 0; i < OFFSET_COUNT; i++) {
        sOffset[i] = offset + CHUNK_SIZE * i;
        sWaitingForOffset[i] = (sOffset[i] < entry->size);
    }

    network_send_to((gNetworkPlayerServer != NULL) ? gNetworkPlayerServer->localIndex : 0, &p);
}

void network_receive_download_request(struct Packet* p) {
    SOFT_ASSERT(gNetworkType == NT_SERVER);

    u16 clientIndex;
    u16 serverIndex;
    u64 offset;
    packet_read(p, &clientIndex, sizeof(u16));
    packet_read(p, &serverIndex, sizeof(u16));
    packet_read(p, &offset, sizeof(u64));

    struct ModListEntry* entry = &gModTableLocal.entries[serverIndex];
    if (serverIndex >= gModTableLocal.entryCount) {
        LOG_ERROR("Requested download of invalid index %u:%llu", serverIndex, offset);
        return;
    }

    for (int i = 0; i < OFFSET_COUNT; i++) {
        u64 o = offset + CHUNK_SIZE * i;
        if (o >= entry->size) { break; }
        network_send_download(clientIndex, serverIndex, o);
    }
}

void network_send_download(u16 clientIndex, u16 serverIndex, u64 offset) {
    SOFT_ASSERT(gNetworkType == NT_SERVER);

    if (serverIndex >= gModTableLocal.entryCount) {
        LOG_ERROR("Requested download of invalid index %u:%llu", serverIndex, offset);
        return;
    }

    struct ModListEntry* entry = &gModTableLocal.entries[serverIndex];
    if (offset >= entry->size) {
        LOG_ERROR("Requested download of invalid offset %u:%llu", serverIndex, offset);
        return;
    }

    if (entry->fp == NULL) {
        LOG_ERROR("Requested download of invalid file pointer %u:%llu", serverIndex, offset);
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

    packet_write(&p, &clientIndex, sizeof(u16));
    packet_write(&p, &serverIndex, sizeof(u16));
    packet_write(&p, &offset, sizeof(u64));
    packet_write(&p, &chunkSize, sizeof(u16));
    packet_write(&p, chunk, chunkSize * sizeof(u8));

    network_send_to(0, &p);
}

void network_receive_download(struct Packet* p) {
    SOFT_ASSERT(gNetworkType == NT_CLIENT);
    if (p->localIndex != UNKNOWN_LOCAL_INDEX) {
        if (gNetworkPlayerServer == NULL || gNetworkPlayerServer->localIndex != p->localIndex) {
            LOG_ERROR("Received download from known local index '%d'", p->localIndex);
            return;
        }
    }

    u16 clientIndex;
    u16 serverIndex;
    u64 offset;
    u16 chunkSize;
    u8 chunk[400] = { 0 };

    packet_read(p, &clientIndex, sizeof(u16));
    packet_read(p, &serverIndex, sizeof(u16));
    packet_read(p, &offset, sizeof(u64));
    packet_read(p, &chunkSize, sizeof(u16));
    packet_read(p, chunk, chunkSize * sizeof(u8));

    //LOG_ERROR("Received download %u:%llu", clientIndex, offset);

    if (clientIndex >= gModTableRemote.entryCount) {
        LOG_ERROR("Received download of invalid index %u:%llu", clientIndex, offset);
        return;
    }

    struct ModListEntry* entry = &gModTableRemote.entries[clientIndex];
    if (offset >= entry->size) {
        LOG_ERROR("Received download of invalid offset %u:%llu", clientIndex, offset);
        return;
    }

    if (entry->fp == NULL) {
        LOG_ERROR("Received download of invalid file pointer %u:%llu", clientIndex, offset);
        return;
    }

    if ((offset + chunkSize) > entry->size) {
        LOG_ERROR("Received download of invalid chunk size %u:%llu:%u", clientIndex, offset, chunkSize);
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
        LOG_ERROR("Received download of unexpected offset [ %llu <-> %llu ] != %llu", entry->curOffset, entry->curOffset + CHUNK_SIZE * OFFSET_COUNT, offset);
        return;
    }

    // write to the file
    fseek(entry->fp, offset, SEEK_SET);
    fwrite(chunk, sizeof(u8) * chunkSize, 1, entry->fp);

    // update progress
    sTotalDownloadBytes += chunkSize;
    gDownloadProgress = (float)sTotalDownloadBytes / (float)gModTableRemote.totalSize;

    if (!waiting) {
        // check if we're finished with this file
        //LOG_INFO("Checking download of '%s': %lld, %lld", entry->name, sOffset[OFFSET_COUNT - 1] + CHUNK_SIZE, entry->size);
        if (sOffset[OFFSET_COUNT - 1] + CHUNK_SIZE >= entry->size) {
            LOG_INFO("Finished download of '%s'", entry->name);
            fclose(entry->fp);

            // parse mod header
            entry->fp = fopen(entry->path, "rb");
            mod_list_extract_lua_fields(entry);
            fclose(entry->fp);

            entry->fp = NULL;
            entry->complete = true;
        }

        entry->curOffset += CHUNK_SIZE * OFFSET_COUNT;
        network_send_next_download_request();
    }
}
