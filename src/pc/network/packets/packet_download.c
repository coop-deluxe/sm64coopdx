#include <stdio.h>
#include "../network.h"
#include "pc/mod_list.h"
#include "pc/debuglog.h"

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

    struct Packet p;
    packet_init(&p, PACKET_DOWNLOAD_REQUEST, true, PLMT_NONE);

    packet_write(&p, &index, sizeof(u16));
    packet_write(&p, &offset, sizeof(u64));

    network_send_to((gNetworkPlayerServer != NULL) ? gNetworkPlayerServer->localIndex : 0, &p);
    //LOG_INFO("sending download request packet");
}

void network_receive_download_request(struct Packet* p) {
    SOFT_ASSERT(gNetworkType == NT_SERVER);

    //LOG_INFO("received download request packet");

    u16 index;
    u64 offset;
    packet_read(p, &index, sizeof(u16));
    packet_read(p, &offset, sizeof(u64));

    network_send_download(index, offset);
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

    struct Packet p;
    packet_init(&p, PACKET_DOWNLOAD, true, PLMT_NONE);

    packet_write(&p, &index, sizeof(u16));
    packet_write(&p, &offset, sizeof(u64));
    packet_write(&p, &chunkSize, sizeof(u16));
    packet_write(&p, chunk, chunkSize * sizeof(u8));

    network_send_to(0, &p);
    //LOG_INFO("sending download packet: %u:%llu", index, offset);
}

void network_receive_download(struct Packet* p) {
    SOFT_ASSERT(gNetworkType == NT_CLIENT);

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

    if (entry->curOffset != offset) {
        LOG_ERROR("Received download of unexpected offset %llu != %llu", entry->curOffset, offset);
        return;
    }

    entry->curOffset += chunkSize;

    //u64 told = ftell(entry->fp);
    //if (offset == 0) {
        fseek(entry->fp, offset, SEEK_SET);
    //}
    fwrite(chunk, sizeof(u8) * chunkSize, 1, entry->fp);

    /*u64 told2 = ftell(entry->fp);

    printf("#################################################\n");
    printf("%llu -> %llu -> %llu - %u\n", told, offset, told2, chunkSize);
    printf("%s\n", chunk);
    printf("#################################################\n");*/

    if ((offset + chunkSize) == entry->size) {
        LOG_INFO("Finished download of '%s'", entry->name);
        fclose(entry->fp);
        entry->fp = NULL;
        entry->complete = true;
    }

    network_send_next_download_request();
}
