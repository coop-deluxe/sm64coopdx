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

#define CHUNK_SIZE 800
#define OFFSET_COUNT 50
#define GROUP_SIZE (CHUNK_SIZE * OFFSET_COUNT)

struct OffsetGroup {
    u64 offset[OFFSET_COUNT];
    bool rx[OFFSET_COUNT];
    bool active;
};

static struct OffsetGroup sOffsetGroup[2] = { 0 };
static bool* sOffsetGroupsCompleted = NULL;
static u64 sOffsetGroupCount = 0;

static u64 sTotalDownloadBytes = 0;
static f32 sDownloadStartTime = 0;
static u64 sDownloadReceivedBytes = 0;

static bool network_start_offset_group(struct OffsetGroup* og);
static void network_update_offset_groups(void);
static void mark_groups_loaded_from_hash(void);

void network_start_download_requests(void) {
    sTotalDownloadBytes = 0;
    gDownloadProgress = 0;
    gDownloadProgressInf = 0;
    sDownloadStartTime = clock_elapsed();
    sDownloadReceivedBytes = 0;

    sOffsetGroupCount = (gRemoteMods.size / GROUP_SIZE) + 1;

    if (sOffsetGroupsCompleted != NULL) {
        free(sOffsetGroupsCompleted);
    }

    sOffsetGroupsCompleted = calloc(sOffsetGroupCount, sizeof(bool));

    memset(&sOffsetGroup[0], 0, sizeof(struct OffsetGroup));
    memset(&sOffsetGroup[1], 0, sizeof(struct OffsetGroup));

    mark_groups_loaded_from_hash();
    network_update_offset_groups();
}

static void mark_groups_loaded_from_hash(void) {
    u8* offsetGroupRequired = calloc(sOffsetGroupCount, sizeof(u8));
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
                u64 ogIndexEnd = (fileStartOffset + mod->size) / GROUP_SIZE;
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

static bool network_start_offset_group(struct OffsetGroup* og) {

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
        // skip this offset if its in progress
        struct OffsetGroup* otherOg = (og == &sOffsetGroup[0])
            ? &sOffsetGroup[1]
            : &sOffsetGroup[0];
        if (otherOg->active && otherOg->offset[0] == (i * GROUP_SIZE)) {
            continue;
        }

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

    // send download request
    network_send_download_request(og->offset[0]);
    return true;
}

static void network_update_offset_groups(void) {
    SOFT_ASSERT(gNetworkType == NT_CLIENT);

    // if no groups are active, start one
    if (!sOffsetGroup[0].active && !sOffsetGroup[1].active) {
        if (network_start_offset_group(&sOffsetGroup[0])) {
            return;
        }
    }

    // figure out group progress
    u32 groupProgress[2] = { 0 };
    for (u32 i = 0; i < 2; i++) {
        struct OffsetGroup* og = &sOffsetGroup[i];

        // count how many chunks were received
        for (u32 j = 0; j < OFFSET_COUNT; j++) {
            if (og->rx[j]) { groupProgress[i]++; }
        }

        // mark finished if finished
        if (groupProgress[i] >= OFFSET_COUNT) {
            u64 groupIndex = (og->offset[0] / GROUP_SIZE);
            if (!sOffsetGroupsCompleted[groupIndex]) {
                LOG_INFO("Completed group: %llu [ %llu <---> %llu ]", groupIndex, og->offset[0], og->offset[0] + GROUP_SIZE);
                sOffsetGroupsCompleted[groupIndex] = true;
            }
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
        // close and flush all file pointers
        for (u64 modIndex = 0; modIndex < gRemoteMods.entryCount; modIndex++) {
            struct Mod* mod = gRemoteMods.entries[modIndex];
            for (u64 fileIndex = 0; fileIndex < mod->fileCount; fileIndex++) {
                struct ModFile* modFile = &mod->files[fileIndex];
                if (modFile->fp == NULL) { continue; }
                f_flush(modFile->fp);
                f_close(modFile->fp);
                modFile->fp = NULL;
            }
            mod->enabled = true;
        }
        LOG_INFO("Download complete!");
        network_send_join_request();
        return;
    }

    // if one group is more than half complete, and the other group is complete, start the other group
    for (u32 i = 0; i < 2; i++) {
        u32 o = (i + 1) % 2;
        struct OffsetGroup* otherOg = &sOffsetGroup[o];
        if ((groupProgress[i] >= (OFFSET_COUNT/2)) && ((groupProgress[o] >= OFFSET_COUNT) || !otherOg->active)) {
            network_start_offset_group(otherOg);
            return;
        }
    }
}

void network_send_download_request(u64 offset) {
    SOFT_ASSERT(gNetworkType == NT_CLIENT);

    struct Packet p = { 0 };
    packet_init(&p, PACKET_DOWNLOAD_REQUEST, true, PLMT_NONE);
    packet_write(&p, &offset, sizeof(u64));

    network_send_to((gNetworkPlayerServer != NULL) ? gNetworkPlayerServer->localIndex : 0, &p);

    LOG_INFO("Requesting group: %llu [ %llu <---> %llu ]", (offset / GROUP_SIZE), offset, offset + GROUP_SIZE);
}

void network_receive_download_request(struct Packet* p) {
    SOFT_ASSERT(gNetworkType == NT_SERVER);

    // receive requested offset
    u64 requestOffset;
    packet_read(p, &requestOffset, sizeof(u64));

    for (u64 i = 0; i < OFFSET_COUNT; i++) {
        u64 sendOffset = requestOffset + (i * CHUNK_SIZE);
        if (sendOffset >= gActiveMods.size) {
            break;
        }
        network_send_download(sendOffset);
    }

    LOG_INFO("Sending group: %llu [ %llu <---> %llu ]", (requestOffset / GROUP_SIZE), requestOffset, requestOffset + GROUP_SIZE);
}

void network_send_download(u64 requestOffset) {
    u8 chunk[CHUNK_SIZE] = { 0 };
    u64 chunkFill = 0;
    u64 fileStartOffset = 0;

    // fill up chunk
    for (u64 modIndex = 0; modIndex < gActiveMods.entryCount; modIndex++) {
        struct Mod* mod = gActiveMods.entries[modIndex];

        // skip past mods to get to the right offset
        if ((fileStartOffset + mod->size) < requestOffset) {
            fileStartOffset += mod->size;
            continue;
        }

        for (u64 fileIndex = 0; fileIndex < mod->fileCount; fileIndex++) {
            struct ModFile* modFile = &mod->files[fileIndex];

            // skip past mod files to get to the right offset
            if ((fileStartOffset + modFile->size) < requestOffset) {
                fileStartOffset += modFile->size;
                continue;
            }

            // calculate file offset and read length
            u64 fileReadOffset = MAX(((s64)requestOffset - (s64)fileStartOffset), 0);
            u64 fileReadLength = MIN((modFile->size - fileReadOffset), (CHUNK_SIZE - chunkFill));

            // open file pointer
            bool opened = false;
            if (modFile->fp == NULL) {
                modFile->fp = fopen(modFile->cachedPath, "rb");
                if (modFile->fp == NULL) {
                    LOG_ERROR("Failed to open mod file during download: %s", modFile->cachedPath);
                    return;
                }
                opened = true;
            }

            // read from file, filling chunk
            fseek(modFile->fp, fileReadOffset, SEEK_SET);
            fread(&chunk[chunkFill], sizeof(u8), fileReadLength, modFile->fp);

            // close file pointer
            if (opened) {
                fclose(modFile->fp);
                modFile->fp = NULL;
            }

            // increment counters
            chunkFill += fileReadLength;
            fileStartOffset += modFile->size;

            // check if we've filled the chunk
            if (chunkFill >= CHUNK_SIZE) {
                goto after_filled;
            }
        }
    }
after_filled:;

    // send the packet
    struct Packet p = { 0 };
    packet_init(&p, PACKET_DOWNLOAD, true, PLMT_NONE);
    packet_write(&p, &requestOffset, sizeof(u64));
    packet_write(&p, &chunkFill,    sizeof(u64));
    packet_write(&p, &chunk,        sizeof(u8) * chunkFill);
    network_send_to(0, &p);

    //LOG_INFO("Sent chunk: offset %llu, length %llu", requestOffset, chunkFill);
}

// Cache any mod that doesn't have "(wip)" or "[wip]" in its name (case-insensitive)
static bool should_cache_mod(struct Mod *mod) {
    char *modName = sys_strdup(mod->name);
    sys_strlwr(modName);
    bool shouldCache = (
        !strstr(modName, "(wip)") &&
        !strstr(modName, "[wip]")
    );
    free(modName);
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

void network_receive_download(struct Packet* p) {
    if (!p) {
        LOG_ERROR("Received null packet");
        return;
    }

    SOFT_ASSERT(gNetworkType == NT_CLIENT);
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
    for (u64 i = 0; i < 2; i++) {
        struct OffsetGroup* og = &sOffsetGroup[i];
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

    // write the chunk
    u64 wroteBytes = 0;
    u64 chunkPour = 0;
    u64 fileStartOffset = 0;
    for (u64 modIndex = 0; modIndex < gRemoteMods.entryCount; modIndex++) {
        struct Mod* mod = gRemoteMods.entries[modIndex];
        if (!mod) {
            LOG_ERROR("Null mod");
            continue;
        }

        // skip past mods to get to the right offset
        if ((fileStartOffset + mod->size) < receiveOffset) {
            fileStartOffset += mod->size;
            continue;
        }

        if (mod->fileCount > 0 && !mod->files) {
            LOG_ERROR("Null mod files");
            continue;
        }

        for (u64 fileIndex = 0; fileIndex < mod->fileCount; fileIndex++) {
            struct ModFile* modFile = &mod->files[fileIndex];

            // skip past mod files to get to the right offset
            if ((fileStartOffset + modFile->size) < receiveOffset) {
                fileStartOffset += modFile->size;
                continue;
            }

            // calculate file offset and read length
            u64 fileWriteOffset = MAX(((s64)receiveOffset - (s64)fileStartOffset), 0);
            u64 fileWriteLength = MIN((modFile->size - fileWriteOffset), (chunkLength - chunkPour));

            // read from file, filling chunk
            if (!modFile->cachedPath && (modFile->wroteBytes < modFile->size)) {
                open_mod_file(mod, modFile);
                if (modFile->fp == NULL) {
                    LOG_ERROR("Failed to open file for download write: %s", modFile->cachedPath);
                    return;
                }
                f_seek(modFile->fp, fileWriteOffset, SEEK_SET);
                f_write(&chunk[chunkPour], sizeof(u8), fileWriteLength, modFile->fp);
                modFile->wroteBytes += fileWriteLength;

                if (modFile->wroteBytes >= modFile->size) {
                    f_flush(modFile->fp);
                    f_close(modFile->fp);
                    modFile->fp = NULL;

                    // Write cachedPath here so the file doesn't end up in mod.cache
                    if (!should_cache_mod(mod)) {
                        char modFilePath[SYS_MAX_PATH] = { 0 };
                        concat_path(modFilePath, mod->basePath, modFile->relativePath);
                        normalize_path(modFilePath);
                        modFile->cachedPath = strdup(modFilePath);
                    }
                }

                wroteBytes += fileWriteLength;
            }

            // increment counters
            chunkPour       += fileWriteLength;
            fileStartOffset += modFile->size;

            // check if we've filled the chunk
            if (chunkPour >= CHUNK_SIZE) {
                goto after_poured;
            }
        }
    }
after_poured:;

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
        if (hours) {
            snprintf(gDownloadEstimate, DOWNLOAD_ESTIMATE_LENGTH, "%uh %um %us", hours, minutes, seconds);
        } else if (minutes) {
            snprintf(gDownloadEstimate, DOWNLOAD_ESTIMATE_LENGTH, "%um %us", minutes, seconds);
        } else {
            snprintf(gDownloadEstimate, DOWNLOAD_ESTIMATE_LENGTH, "%us", seconds);
        }
    }

    network_update_offset_groups();
}
