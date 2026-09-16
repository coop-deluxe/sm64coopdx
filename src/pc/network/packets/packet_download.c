#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "../network.h"
#include "pc/djui/djui.h"
#include "pc/mods/mods.h"
#include "pc/mods/mods_utils.h"
#include "pc/utils/misc.h"
#include "pc/djui/djui_panel_join_message.h"
//#define DISABLE_MODULE_LOG 1
#include "pc/debuglog.h"
#include "pc/fs/fmem.h"

#define CHUNK_SIZE 1400
#define OFFSET_COUNT 50
#define CHUNK_GROUP_TIMEOUT 1.5f
#define GROUP_SIZE (CHUNK_SIZE * OFFSET_COUNT)
#define MAX_ACTIVE_OFFSET_GROUPS 32
#define MAX_QUEUED_CHUNKS (OFFSET_COUNT * MAX_ACTIVE_OFFSET_GROUPS)

struct OffsetGroup {
    u64 offset[OFFSET_COUNT];
    bool rx[OFFSET_COUNT];
    bool active;
    f32 requestTime;
};

struct QueuedChunk {
    u64 chunkOffset;
    u64 chunkFill;
    u8 buffer[CHUNK_SIZE];
};

static struct QueuedChunk sQueuedChunks[MAX_QUEUED_CHUNKS] = { 0 };
static u32 sQueuedChunksHead = 0; // to avoid shifting elements, track using a head and tail
static u32 sQueuedChunksTail = 0;
static u32 sQueuedChunksCount = 0;

static struct OffsetGroup sOffsetGroup[MAX_ACTIVE_OFFSET_GROUPS] = { 0 };
static bool *sOffsetGroupsCompleted = NULL;
static u64 sOffsetGroupCount = 0;

static u8 *sDownloadBuffer = NULL;
static u64 sTotalDownloadBytes = 0;
static f32 sDownloadStartTime = 0;
static u64 sDownloadReceivedBytes = 0;

static u32 sMaxOffsetGroups = 2;
static u32 sSuccessCount = 0;

static bool sIsDownloading = false;

static bool network_start_offset_group(struct OffsetGroup* og);
static void network_update_offset_groups(void);
static void mark_groups_loaded_from_hash(void);

// Cache any mod that doesn't have "(wip)" or "[wip]" in its name (case-insensitive)
static bool should_cache_mod(struct Mod *mod) {
    char modNameLowercase[MOD_NAME_SIZE];
    memcpy(modNameLowercase, mod->name, MOD_NAME_SIZE * sizeof(char));
    sys_strlwr(modNameLowercase);
    bool shouldCache = (
        !strstr(modNameLowercase, "(wip)") &&
        !strstr(modNameLowercase, "[wip]")
    );
    return shouldCache;
}

static void open_mod_file(struct Mod* mod, struct ModFile* file) {
    if (file->fp != NULL) {
        return;
    }

    char fullPath[SYS_MAX_PATH] = { 0 };
    if (!mod_file_full_path(fullPath, mod, file)) {
        LOG_ERROR("unable to concat full path!");
        return;
    }

    file->wroteBytes = 0;
    if (should_cache_mod(mod)) {
        mod_file_create_directories(mod, file);
        file->fp = fopen(fullPath, "wb");
    } else {
        file->fp = f_open_w(fullPath);
    }
    if (file->fp == NULL) {
        LOG_ERROR("unable to open for write: '%s' - '%s'", fullPath, strerror(errno));
        return;
    }
    LOG_INFO("Opened mod file pointer: %s", fullPath);
}

static void network_sync_mod_files_and_download_buffer(void) {
    SOFT_ASSERT(gNetworkType == NT_CLIENT);

    if (!sDownloadBuffer) { return; }

    u64 fileStartOffset = 0;

    for (u64 modIndex = 0; modIndex < gRemoteMods.entryCount; modIndex++) {
        struct Mod *mod = gRemoteMods.entries[modIndex];
        if (!mod) { continue; }

        for (u64 fileIndex = 0; fileIndex < mod->fileCount; fileIndex++) {
            struct ModFile *modFile = &mod->files[fileIndex];

            // skip if already written to
            if (modFile->cachedPath != NULL || modFile->wroteBytes >= modFile->size) {
                fileStartOffset += modFile->size;
                continue;
            }

            // check if the offset group is finished and if we can write to a file
            u64 startGroup = fileStartOffset / GROUP_SIZE;
            u64 endGroup = (fileStartOffset + modFile->size) / GROUP_SIZE;
            bool writeToFile = true;

            for (u64 g = startGroup; g <= endGroup && g < sOffsetGroupCount; g++) {
                if (!sOffsetGroupsCompleted[g]) {
                    writeToFile = false;
                    break;
                }
            }

            if (writeToFile) {
                open_mod_file(mod, modFile);
                if (modFile->fp != NULL) {
                    // write to the file
                    f_write(&sDownloadBuffer[fileStartOffset], sizeof(u8), modFile->size, modFile->fp);
                    modFile->wroteBytes = modFile->size;

                    // flush and close the file
                    f_flush(modFile->fp);
                    f_close(modFile->fp);
                    modFile->fp = NULL;

                    // configure cachedPath if necessary
                    if (!should_cache_mod(mod)) {
                        char modFilePath[SYS_MAX_PATH] = { 0 };
                        concat_path(modFilePath, mod->basePath, modFile->relativePath);
                        normalize_path(modFilePath);
                        modFile->cachedPath = strdup(modFilePath);
                    }
                }
            }

            fileStartOffset += modFile->size;
        }
    }
}

void network_start_download_requests(void) {
    SOFT_ASSERT(gNetworkType == NT_CLIENT);

    sIsDownloading = true;
    sTotalDownloadBytes = 0;
    gDownloadProgress = 0;
    gDownloadProgressInf = 0;
    sDownloadStartTime = clock_elapsed();
    sDownloadReceivedBytes = 0;
    sMaxOffsetGroups = 2;
    sSuccessCount = 0;
    free(sDownloadBuffer);
    sDownloadBuffer = calloc(1, gRemoteMods.size);
    if (!sDownloadBuffer) {
        LOG_ERROR("Failed to allocate download buffer! Can't start!");
        return;
    }

    sOffsetGroupCount = (gRemoteMods.size / GROUP_SIZE) + 1;

    if (sOffsetGroupsCompleted != NULL) {
        free(sOffsetGroupsCompleted);
    }

    sOffsetGroupsCompleted = calloc(sOffsetGroupCount, sizeof(bool));

    memset(sOffsetGroup, 0, sizeof(sOffsetGroup));

    mark_groups_loaded_from_hash();
    network_update_offset_groups();
}

static void mark_groups_loaded_from_hash(void) {
    u8 *offsetGroupRequired = calloc(sOffsetGroupCount, sizeof(u8));
    if (offsetGroupRequired == NULL) {
        LOG_ERROR("Failed to allocate offsetGroupRequired");
        return;
    }

    sTotalDownloadBytes = 0;
    u64 fileStartOffset = 0;
    for (u64 modIndex = 0; modIndex < gRemoteMods.entryCount; modIndex++) {
        struct Mod* mod = gRemoteMods.entries[modIndex];
        for (u64 fileIndex = 0; fileIndex < mod->fileCount; fileIndex++) {
            struct ModFile* file = &mod->files[fileIndex];
            if (file->cachedPath != NULL) {
                // if we loaded from cache, mark bytes as downloaded
                sTotalDownloadBytes += file->size;
                LOG_INFO("Loaded from cache: %s, %llu", file->cachedPath, (u64)file->size);
            } else {
                // if we haven't loaded from cache, we need this offset group
                u64 ogIndexStart = fileStartOffset / GROUP_SIZE;
                u64 ogIndexEnd = (fileStartOffset + file->size) / GROUP_SIZE;
                do {
                    if (ogIndexStart < sOffsetGroupCount) {
                        LOG_INFO("Marking group as required: %llu (%s)", ogIndexStart, file->relativePath);
                        offsetGroupRequired[ogIndexStart] = 1;
                    }
                    ogIndexStart++;
                } while (ogIndexStart <= ogIndexEnd);
            }
            fileStartOffset += file->size;
        }
    }

    for (u64 ogIndex = 0; ogIndex < sOffsetGroupCount; ogIndex++) {
        if (!offsetGroupRequired[ogIndex]) {
            sOffsetGroupsCompleted[ogIndex] = 1;
        } else {
            sOffsetGroupsCompleted[ogIndex] = 0;
        }
    }

    free(offsetGroupRequired);
}

static bool network_start_offset_group(struct OffsetGroup *og) {
    // sanity check
    if (og->active) {
        for (u32 i = 0; i < OFFSET_COUNT; i++) {
            assert(og->rx[i]);
        }
    }

    // figure out the starting offset
    bool foundIndex = false;
    u64 offset = 0;
    for (u32 i = 0; i < sOffsetGroupCount; i++) {
        u64 targetOffset = i * GROUP_SIZE;

        // skip this offset if it is already in progress
        bool inProgress = false;
        for (u32 group = 0; group < MAX_ACTIVE_OFFSET_GROUPS; group++) {
            if (&sOffsetGroup[group] != og && sOffsetGroup[group].active && sOffsetGroup[group].offset[0] == targetOffset) {
                inProgress = true;
                break;
            }
        }
        if (inProgress) { continue; }

        // set offset group to download if the offset group isn't completed
        if (!sOffsetGroupsCompleted[i]) {
            offset = (i * GROUP_SIZE);
            foundIndex = true;
            break;
        }
    }

    // sanity check
    if (!foundIndex) {
        LOG_INFO("Could not find offset group, may be near the end of the download");
        return false;
    }

    // set up offset group
    for (u64 i = 0; i < OFFSET_COUNT; i++) {
        og->offset[i] = offset + (i * CHUNK_SIZE);
        og->rx[i] = (og->offset[i] >= gRemoteMods.size);
    }
    og->active = true;
    og->requestTime = clock_elapsed();

    // send download request
    network_send_download_request(og->offset[0]);
    return true;
}

static void network_update_offset_groups(void) {
    SOFT_ASSERT(gNetworkType == NT_CLIENT);
    if (!sIsDownloading) { return; }

    // if there is a timeout, resend the download request
    f32 currentTime = clock_elapsed();
    for (u32 i = 0; i < MAX_ACTIVE_OFFSET_GROUPS; i++) {
        struct OffsetGroup *og = &sOffsetGroup[i];
        if (og->active && !sOffsetGroupsCompleted[og->offset[0] / GROUP_SIZE] && (currentTime - og->requestTime) > CHUNK_GROUP_TIMEOUT) {
            LOG_INFO("Offset group %llu timed out. Freeing group...", og->offset[0] / GROUP_SIZE);
            og->requestTime = currentTime;

            if (sMaxOffsetGroups > 2) {
                sMaxOffsetGroups--;
            }
            sSuccessCount = 0;

            network_send_download_request(og->offset[0]);
        }
    }

    // count number of active groups
    u32 activeGroups = 0;
    for (u32 i = 0; i < MAX_ACTIVE_OFFSET_GROUPS; i++) {
        if (sOffsetGroup[i].active) {
            activeGroups++;
        }
    }

    // if a groups is inactive and we can start a new one, start it up
    for (u32 i = 0; i < MAX_ACTIVE_OFFSET_GROUPS; i++) {
        if (!sOffsetGroup[i].active && activeGroups < sMaxOffsetGroups) {
            if (network_start_offset_group(&sOffsetGroup[i])) {
                activeGroups++;
            }
        }
    }

    // figure out group progress
    u32 groupProgress[MAX_ACTIVE_OFFSET_GROUPS] = { 0 };
    for (u32 i = 0; i < MAX_ACTIVE_OFFSET_GROUPS; i++) {
        struct OffsetGroup *og = &sOffsetGroup[i];
        if (!og->active) { continue; }

        for (u32 j = 0; j < OFFSET_COUNT; j++) {
            if (og->rx[j]) { groupProgress[i]++; }
        }

        // mark group finished if all chunks received
        if (groupProgress[i] >= OFFSET_COUNT) {
            u64 groupIndex = (og->offset[0] / GROUP_SIZE);
            if (!sOffsetGroupsCompleted[groupIndex]) {
                LOG_INFO("Completed group: %llu [ %llu <---> %llu ]", groupIndex, og->offset[0], og->offset[0] + GROUP_SIZE);
                sOffsetGroupsCompleted[groupIndex] = true;
            }

            // ramp up speed if we are on a good run of successful finishes
            sSuccessCount++;
            if (sSuccessCount >= 4) {
                if (sMaxOffsetGroups < MAX_ACTIVE_OFFSET_GROUPS) {
                    sMaxOffsetGroups++;
                    LOG_INFO("Increasing active group limit to %u", sMaxOffsetGroups);
                }
                sSuccessCount = 0;
            }

            // deactivate group for later use
            og->active = false;
        }
    }

    // if all chunks were received, we're finished
    bool completedDownload = true;
    for (u64 i = 0; i < sOffsetGroupCount; i++) {
        if (!sOffsetGroupsCompleted[i]) {
            LOG_INFO("Not completed: %llu", i);
            completedDownload = false;
            break;
        }
    }

    if (completedDownload) {
        // sync one last time to make sure we didn't miss anything
        network_sync_mod_files_and_download_buffer();

        // cleanup
        network_download_cleanup();

        // enable remote mods
        for (u64 modIndex = 0; modIndex < gRemoteMods.entryCount; modIndex++) {
            struct Mod *mod = gRemoteMods.entries[modIndex];
            mod->enabled = true;
        }

        LOG_INFO("Download complete!");
        gDownloadProgress = 1.0f;
        snprintf(gDownloadEstimate, DOWNLOAD_ESTIMATE_LENGTH, "Finalizing");
        network_send_join_request();
        return;
    }

    // if a group is 50% complete, attempt to spin up the next group if under capacity
    if (activeGroups < sMaxOffsetGroups) {
        for (u32 i = 0; i < MAX_ACTIVE_OFFSET_GROUPS; i++) {
            struct OffsetGroup *og = &sOffsetGroup[i];
            if (og->active && groupProgress[i] >= (OFFSET_COUNT / 2)) {
                for (u32 j = 0; j < MAX_ACTIVE_OFFSET_GROUPS; j++) {
                    if (!sOffsetGroup[j].active) {
                        if (network_start_offset_group(&sOffsetGroup[j])) {
                            goto end_spinup_group;
                        }
                    }
                }
            }
        }
    }
end_spinup_group:;
}

void network_send_download_request(u64 offset) {
    SOFT_ASSERT(gNetworkType == NT_CLIENT);

    struct Packet p = { 0 };
    packet_init(&p, PACKET_DOWNLOAD_REQUEST, true, PLMT_NONE);
    packet_write(&p, &offset, sizeof(u64));

    network_send_to((gNetworkPlayerServer != NULL) ? gNetworkPlayerServer->localIndex : 0, &p);

    LOG_INFO("Requesting group: %llu [ %llu <---> %llu ]", (offset / GROUP_SIZE), offset, offset + GROUP_SIZE);
}

void network_receive_download_request(struct Packet *p) {
    SOFT_ASSERT(gNetworkType == NT_SERVER);

    // receive requested offset
    u64 requestOffset;
    packet_read(p, &requestOffset, sizeof(u64));

    network_send_download(requestOffset);

    LOG_INFO("Sending group: %llu [ %llu <---> %llu ]", (requestOffset / GROUP_SIZE), requestOffset, requestOffset + GROUP_SIZE);
}

void network_send_download(u64 requestOffset) {
    u8 groupBuffer[GROUP_SIZE];
    u64 groupFill = 0;
    u64 fileStartOffset = 0;

    // iterate through mods
    for (u64 modIndex = 0; modIndex < gActiveMods.entryCount; modIndex++) {
        struct Mod *mod = gActiveMods.entries[modIndex];

        // if we are not at the file start offset, increment and continue
        if ((fileStartOffset + mod->size) < requestOffset) {
            fileStartOffset += mod->size;
            continue;
        }

        // iterate through each file in the mod
        for (u64 fileIndex = 0; fileIndex < mod->fileCount; fileIndex++) {
            struct ModFile *modFile = &mod->files[fileIndex];

            u64 currentTargetOffset = requestOffset + groupFill;
            if (fileStartOffset + modFile->size < currentTargetOffset) {
                fileStartOffset += modFile->size;
                continue;
            }

            u64 fileReadOffset = currentTargetOffset - fileStartOffset;
            u64 fileReadLength = MIN(modFile->size - fileReadOffset, GROUP_SIZE - groupFill);

            // read file
            FILE *fp = fopen(modFile->cachedPath, "rb");
            if (fp != NULL) {
                fseek(fp, fileReadOffset, SEEK_SET);
                fread(&groupBuffer[groupFill], sizeof(u8), fileReadLength, fp);
                fclose(fp);
            } else {
                LOG_ERROR("Failed to open mod file: %s", modFile->cachedPath);
            }

            groupFill += fileReadLength;
            fileStartOffset += modFile->size;

            // if we have filled the group, exit
            if (groupFill >= GROUP_SIZE) {
                goto after_filled;
            }
        }
    }
after_filled:;

    // queue up packets
    u64 bytesQueued = 0;
    while (bytesQueued < groupFill) {
        if (sQueuedChunksCount >= MAX_QUEUED_CHUNKS) {
            LOG_ERROR("No space in the queue! Not sending download packet");
            break;
        }

        u64 chunkOffset = requestOffset + bytesQueued;
        u64 chunkFill = MIN(CHUNK_SIZE, groupFill - bytesQueued);

        struct QueuedChunk *queuedChunk = &sQueuedChunks[sQueuedChunksTail];
        queuedChunk->chunkOffset = chunkOffset;
        queuedChunk->chunkFill = chunkFill;
        memcpy(queuedChunk->buffer, &groupBuffer[bytesQueued], chunkFill);

        sQueuedChunksTail = (sQueuedChunksTail + 1) % MAX_QUEUED_CHUNKS;
        sQueuedChunksHead++;

        bytesQueued += chunkFill;
    }
}

void network_receive_download(struct Packet* p) {
    if (!p) {
        LOG_ERROR("Received null packet");
        return;
    }

    SOFT_ASSERT(gNetworkType == NT_CLIENT);
    if (gNetworkSentJoin) {
        LOG_ERROR("Received download packet when we already finished downloading!");
        return;
    }
    if (p->localIndex != UNKNOWN_LOCAL_INDEX) {
        if (gNetworkPlayerServer == NULL || gNetworkPlayerServer->localIndex != p->localIndex) {
            LOG_ERROR("Received download from known local index '%d'", p->localIndex);
            return;
        }
    }

    // read the chunk
    u64 receiveOffset     = 0;
    u64 chunkLength       = 0;
    u8  chunk[CHUNK_SIZE+1] = { 0 };
    packet_read(p, &receiveOffset, sizeof(u64));
    packet_read(p, &chunkLength,   sizeof(u64));
    if (chunkLength > CHUNK_SIZE) {
        LOG_ERROR("Received improper chunk length");
        return;
    }
    packet_read(p, &chunk,         sizeof(u8) * chunkLength);

    // mark the offset group as received
    bool foundGroup = false;
    for (u64 i = 0; i < MAX_ACTIVE_OFFSET_GROUPS; i++) {
        struct OffsetGroup *og = &sOffsetGroup[i];
        if (!og->active) { continue; }
        for (u64 j = 0; j < OFFSET_COUNT; j++) {
            if (og->offset[j] != receiveOffset) {
                continue;
            }
            if (og->rx[j]) {
                LOG_INFO("Received duplicate chunk: %llu", receiveOffset);
                return;
            }
            og->rx[j] = true;
            foundGroup = true;
            goto after_group;
        }
    }
after_group:;

    if (!foundGroup) {
        LOG_INFO("Received chunk from an inactive offset group");
        return;
    }

    // write chunk to the download buffer
    u64 wroteBytes = 0;
    if (sDownloadBuffer && (receiveOffset + chunkLength <= gRemoteMods.size)) {
        memcpy(&sDownloadBuffer[receiveOffset], chunk, chunkLength);
        wroteBytes = chunkLength;
    }

    LOG_INFO("Received chunk: offset %llu, size %llu", receiveOffset, chunkLength);

    // update progress
    sTotalDownloadBytes += wroteBytes;
    gDownloadProgress = (f32)sTotalDownloadBytes / (f32)gRemoteMods.size;
    gDownloadProgressInf += 0.01f * ((f32)wroteBytes / (f32)CHUNK_SIZE);

    // update speed
    f32 elapsed = clock_elapsed() - sDownloadStartTime;
    sDownloadReceivedBytes += wroteBytes;
    f32 bytesPerSecond = (f32)sDownloadReceivedBytes / elapsed;

    // update estimated time
    u64 remaining = gRemoteMods.size - sTotalDownloadBytes;
    if (sTotalDownloadBytes > 0 && remaining > 0) {
        u32 seconds = (remaining / bytesPerSecond) + 1;
        u32 minutes = seconds / 60;
        u32 hours = minutes / 60;

        seconds = seconds % 60;
        minutes = minutes % 60;
        f32 downloadedMB = (f32)sTotalDownloadBytes / (1024.0f * 1024.0f);
        f32 totalMB = (f32)gRemoteMods.size / (1024.0f * 1024.0f);

        if (hours) {
            snprintf(gDownloadEstimate, DOWNLOAD_ESTIMATE_LENGTH, "%uh %um %us (%.2fMB/%.2fMB)", hours, minutes, seconds, downloadedMB, totalMB);
        } else if (minutes) {
            snprintf(gDownloadEstimate, DOWNLOAD_ESTIMATE_LENGTH, "%um %us (%.2fMB/%.2fMB)", minutes, seconds, downloadedMB, totalMB);
        } else {
            snprintf(gDownloadEstimate, DOWNLOAD_ESTIMATE_LENGTH, "%us (%.2fMB/%.2fMB)", seconds, downloadedMB, totalMB);
        }
    }
}

void network_download_update() {
    if (gNetworkType == NT_SERVER) {
        // process queued download packets
        if (sQueuedChunksCount == 0) { return; }

        f64 startTime = clock_elapsed_f64();
        f64 currentTime = clock_elapsed_f64();

        while (sQueuedChunksCount > 0 && currentTime - startTime < 0.008) {
            struct QueuedChunk *queuedChunk = &sQueuedChunks[sQueuedChunksHead];

            struct Packet p = { 0 };
            packet_init(&p, PACKET_DOWNLOAD, false, PLMT_NONE);
            packet_write(&p, &queuedChunk->chunkOffset, sizeof(u64));
            packet_write(&p, &queuedChunk->chunkFill, sizeof(u64));
            packet_write(&p, &queuedChunk->buffer, sizeof(u8) * queuedChunk->chunkFill);

            network_send_to(0, &p);

            sQueuedChunksHead = (sQueuedChunksHead + 1) % MAX_QUEUED_CHUNKS;
            sQueuedChunksCount--;
            currentTime = clock_elapsed_f64();
        }
    }

    if (!sIsDownloading) { return; }
    network_sync_mod_files_and_download_buffer();
    network_update_offset_groups();
}

void network_download_cleanup(void) {
    sIsDownloading = false;

    memset(sQueuedChunks, 0, sizeof(sQueuedChunks));
    sQueuedChunksHead = 0;
    sQueuedChunksTail = 0;
    sQueuedChunksCount = 0;

    free(sDownloadBuffer);
    sDownloadBuffer = NULL;
    free(sOffsetGroupsCompleted);
    sOffsetGroupsCompleted = NULL;

    sTotalDownloadBytes = 0;
    sDownloadReceivedBytes = 0;
    sDownloadStartTime = 0;
    sOffsetGroupCount = 0;
    sMaxOffsetGroups = 2;
    sSuccessCount = 0;

    memset(sOffsetGroup, 0, sizeof(sOffsetGroup));
}
