#include <stdio.h>
#include "../network.h"
#include "pc/djui/djui.h"
#include "pc/mods/mods.h"
#include "pc/mods/mods_utils.h"
#include "pc/debuglog.h"

#define CHUNK_SIZE 400
#define OFFSET_COUNT 40

static u64 sOffset[OFFSET_COUNT] = { 0 };
static bool sWaitingForOffset[OFFSET_COUNT] = { 0 };
u64 sTotalDownloadBytes = 0;
extern float gDownloadProgress;

void network_start_download_requests(void) {
    sTotalDownloadBytes = 0;
    gDownloadProgress = 0;
    for (s32 i = 0; i < gRemoteMods.entryCount; i++) {
        struct Mod* mod = gRemoteMods.entries[i];
        mod->enabled = true;
        for (s32 j = 0; j < mod->fileCount; j++) {
            struct ModFile* file = &mod->files[j];
            char fullPath[SYS_MAX_PATH] = { 0 };
            if (!mod_file_full_path(fullPath, mod, file)) {
                LOG_ERROR("unable to concat full path!");
                return;
            }
            mod_file_create_directories(mod, file);
            file->fp = fopen(fullPath, "wb");
            if (file->fp == NULL) {
                LOG_ERROR("unable to open for write: '%s'", fullPath);
                return;
            }
        }
    }
    network_send_next_download_request();
}

void network_send_next_download_request(void) {
    SOFT_ASSERT(gNetworkType == NT_CLIENT);
    for (s32 i = 0; i < gRemoteMods.entryCount; i++) {
        struct Mod* mod = gRemoteMods.entries[i];
        for (s32 j = 0; j < mod->fileCount; j++) {
            struct ModFile* file = &mod->files[j];
            if (file->complete) { continue; }
            //LOG_INFO("sending download request: %d, %d, %lld", i, file->remoteIndex, file->curOffset);
            network_send_download_request(i, j, file->curOffset);
            return;
        }
    }
    network_send_join_request();
}

void network_send_download_request(u16 modIndex, u16 fileIndex, u64 offset) {
    SOFT_ASSERT(gNetworkType == NT_CLIENT);

    struct Packet p = { 0 };
    packet_init(&p, PACKET_DOWNLOAD_REQUEST, true, PLMT_NONE);

    packet_write(&p, &modIndex, sizeof(u16));
    packet_write(&p, &fileIndex, sizeof(u16));
    packet_write(&p, &offset, sizeof(u64));

    struct Mod* mod = gRemoteMods.entries[modIndex];
    struct ModFile* file = &mod->files[fileIndex];
    for (s32 i = 0; i < OFFSET_COUNT; i++) {
        sOffset[i] = offset + CHUNK_SIZE * i;
        sWaitingForOffset[i] = (sOffset[i] < file->size);
    }

    network_send_to((gNetworkPlayerServer != NULL) ? gNetworkPlayerServer->localIndex : 0, &p);
}

void network_receive_download_request(struct Packet* p) {
    SOFT_ASSERT(gNetworkType == NT_SERVER);

    u16 modIndex;
    u16 fileIndex;
    u64 offset;
    packet_read(p, &modIndex, sizeof(u16));
    packet_read(p, &fileIndex, sizeof(u16));
    packet_read(p, &offset, sizeof(u64));

    if (modIndex >= gActiveMods.entryCount) {
        LOG_ERROR("Requested download of invalid mod index %u:%llu", modIndex, offset);
        return;
    }

    struct Mod* mod = gActiveMods.entries[modIndex];

    if (fileIndex >= mod->fileCount) {
        LOG_ERROR("Requested download of invalid file index %u:%llu", fileIndex, offset);
        return;
    }

    struct ModFile* file = &mod->files[fileIndex];

    for (s32 i = 0; i < OFFSET_COUNT; i++) {
        u64 o = offset + CHUNK_SIZE * i;
        if (o >= file->size) { break; }
        network_send_download(modIndex, fileIndex, o);
    }
}

void network_send_download(u16 modIndex, u16 fileIndex, u64 offset) {
    SOFT_ASSERT(gNetworkType == NT_SERVER);

    if (modIndex >= gActiveMods.entryCount) {
        LOG_ERROR("Requested download of invalid mod index %u:%llu", modIndex, offset);
        return;
    }

    struct Mod* mod = gActiveMods.entries[modIndex];

    if (fileIndex >= mod->fileCount) {
        LOG_ERROR("Requested download of invalid file index %u:%llu", fileIndex, offset);
        return;
    }

    struct ModFile* file = &mod->files[fileIndex];

    if (offset >= file->size) {
        LOG_ERROR("Requested download of invalid offset %u:%llu", modIndex, offset);
        return;
    }

    if (file->fp == NULL) {
        LOG_ERROR("Requested download of invalid file pointer %u:%llu", modIndex, offset);
        return;
    }

    u16 chunkSize = 400;
    if ((offset + chunkSize) > file->size) {
        chunkSize = file->size - offset;
    }

    u8 chunk[400] = { 0 };
    fseek(file->fp, offset, SEEK_SET);
    fread(chunk, chunkSize, 1, file->fp);

    struct Packet p = { 0 };
    packet_init(&p, PACKET_DOWNLOAD, true, PLMT_NONE);

    packet_write(&p, &modIndex, sizeof(u16));
    packet_write(&p, &fileIndex, sizeof(u16));
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

    u16 modIndex;
    u16 fileIndex;
    u64 offset;
    u16 chunkSize;
    u8 chunk[400] = { 0 };

    packet_read(p, &modIndex, sizeof(u16));
    packet_read(p, &fileIndex, sizeof(u16));
    packet_read(p, &offset, sizeof(u64));
    packet_read(p, &chunkSize, sizeof(u16));
    packet_read(p, chunk, chunkSize * sizeof(u8));

    //LOG_INFO("Received download %u:%llu", clientIndex, offset);

    if (modIndex >= gRemoteMods.entryCount) {
        LOG_ERROR("Received download of invalid mod index %u:%llu", modIndex, offset);
        return;
    }

    struct Mod* mod = gRemoteMods.entries[modIndex];

    if (fileIndex >= mod->fileCount) {
        LOG_ERROR("Received download of invalid file index %u:%llu", modIndex, offset);
        return;
    }

    struct ModFile* file = &mod->files[fileIndex];

    if (offset >= file->size) {
        LOG_ERROR("Received download of invalid offset %u:%llu", modIndex, offset);
        return;
    }

    if (file->fp == NULL) {
        LOG_ERROR("Received download of invalid file pointer %u:%llu", modIndex, offset);
        return;
    }

    if ((offset + chunkSize) > file->size) {
        LOG_ERROR("Received download of invalid chunk size %u:%llu:%u -- %llu", modIndex, (u64)offset, chunkSize, (u64)file->size);
        return;
    }

    // check if we're still waiting for chunks
    bool found = false;
    bool waiting = false;
    for (s32 i = 0; i < OFFSET_COUNT; i++) {
        if (sOffset[i] == offset) {
            found = sWaitingForOffset[i];
            sWaitingForOffset[i] = false;
        }
        waiting = waiting || sWaitingForOffset[i];
    }

    if (!found) {
        LOG_ERROR("Received download of unexpected offset [ %llu <-> %llu ] != %llu", file->curOffset, file->curOffset + CHUNK_SIZE * OFFSET_COUNT, offset);
        return;
    }

    // write to the file
    fseek(file->fp, offset, SEEK_SET);
    fwrite(chunk, sizeof(u8) * chunkSize, 1, file->fp);

    // update progress
    sTotalDownloadBytes += chunkSize;
    gDownloadProgress = (float)sTotalDownloadBytes / (float)gRemoteMods.size;

    if (!waiting) {
        // check if we're finished with this file
        //LOG_INFO("Checking download of '%s': %lld, %lld", file->name, sOffset[OFFSET_COUNT - 1] + CHUNK_SIZE, file->size);
        if (sOffset[OFFSET_COUNT - 1] + CHUNK_SIZE >= file->size) {
            LOG_INFO("Finished download of '%s'", file->relativePath);
            fclose(file->fp);
            file->fp = NULL;
            file->complete = true;
        }

        file->curOffset += (u64)CHUNK_SIZE * OFFSET_COUNT;
        network_send_next_download_request();
    }
}
