#include <stdio.h>
#include "../network.h"
#include "pc/mods/mods.h"
#include "pc/mods/mods_utils.h"
#include "pc/djui/djui.h"
#include "pc/djui/djui_panel_join_message.h"
#include "pc/debuglog.h"
#include "pc/mods/mod_cache.h"

void network_send_mod_list_request(void) {
    SOFT_ASSERT(gNetworkType == NT_CLIENT);
    mods_clear(&gActiveMods);
    mods_clear(&gRemoteMods);

    if (!mods_generate_remote_base_path()) {
        LOG_ERROR("Failed to generate remote base path!");
        return;
    }

    struct Packet p = { 0 };
    packet_init(&p, PACKET_MOD_LIST_REQUEST, true, PLMT_NONE);
    char version[MAX_VERSION_LENGTH] = { 0 };
    snprintf(version, MAX_VERSION_LENGTH, "%s", get_version());
    packet_write(&p, &version, sizeof(u8) * MAX_VERSION_LENGTH);

    network_send_to(PACKET_DESTINATION_SERVER, &p);
    LOG_INFO("sending mod list request");
    gAllowOrderedPacketClear = 0;
}

void network_receive_mod_list_request(UNUSED struct Packet* p) {
    if (gNetworkType != NT_SERVER) {
        LOG_ERROR("Network type should be server!");
        return;
    }
    LOG_INFO("received mod list request");

    network_send_mod_list();
}

void network_send_mod_list(void) {
    SOFT_ASSERT(gNetworkType == NT_SERVER);

    packet_ordered_begin();

    struct Packet p = { 0 };
    packet_init(&p, PACKET_MOD_LIST, true, PLMT_NONE);

    char version[MAX_VERSION_LENGTH] = { 0 };
    snprintf(version, MAX_VERSION_LENGTH, "%s", get_version());
    LOG_INFO("sending version: %s", version);
    packet_write(&p, &version, sizeof(u8) * MAX_VERSION_LENGTH);
    packet_write(&p, &gActiveMods.entryCount, sizeof(u16));
    network_send_to(0, &p);

    LOG_INFO("sent mod list (%u):", gActiveMods.entryCount);
    for (u16 i = 0; i < gActiveMods.entryCount; i++) {
        struct Mod* mod = gActiveMods.entries[i];

        u16 nameLength = strlen(mod->name);
        if (nameLength > MOD_NAME_MAX_LENGTH) { nameLength = MOD_NAME_MAX_LENGTH; }

        u16 incompatibleLength = 0;
        if (mod->incompatible) {
            incompatibleLength = strlen(mod->incompatible);
            if (incompatibleLength > MOD_INCOMPATIBLE_MAX_LENGTH) { incompatibleLength = MOD_INCOMPATIBLE_MAX_LENGTH; }
        }

        u16 relativePathLength = strlen(mod->relativePath);
        u64 modSize = mod->size;

        struct Packet p = { 0 };
        packet_init(&p, PACKET_MOD_LIST_ENTRY, true, PLMT_NONE);
        packet_write(&p, &i, sizeof(u16));
        packet_write(&p, &nameLength, sizeof(u16));
        packet_write(&p, mod->name, sizeof(u8) * nameLength);
        packet_write(&p, &incompatibleLength, sizeof(u16));
        if (mod->incompatible) {
            packet_write(&p, mod->incompatible, sizeof(u8) * incompatibleLength);
        } else {
            packet_write(&p, "", 0);
        }
        packet_write(&p, &relativePathLength, sizeof(u16));
        packet_write(&p, mod->relativePath, sizeof(u8) * relativePathLength);
        packet_write(&p, &modSize, sizeof(u64));
        packet_write(&p, &mod->isDirectory, sizeof(u8));
        packet_write(&p, &mod->pausable, sizeof(u8));
        packet_write(&p, &mod->ignoreScriptWarnings, sizeof(u8));
        packet_write(&p, &mod->fileCount, sizeof(u16));
        network_send_to(0, &p);
        LOG_INFO("    '%s': %llu", mod->name, (u64)mod->size);

        for (u16 j = 0; j < mod->fileCount; j++) {
            struct Packet p = { 0 };
            packet_init(&p, PACKET_MOD_LIST_FILE, true, PLMT_NONE);
            struct ModFile* file = &mod->files[j];
            u16 relativePathLength = strlen(file->relativePath);
            u64 fileSize = file->size;
            packet_write(&p, &i, sizeof(u16));
            packet_write(&p, &j, sizeof(u16));
            packet_write(&p, &relativePathLength, sizeof(u16));
            packet_write(&p, file->relativePath, sizeof(u8) * relativePathLength);
            packet_write(&p, &fileSize, sizeof(u64));
            packet_write(&p, &file->dataHash[0], sizeof(u8) * 16);
            network_send_to(0, &p);
            LOG_INFO("      '%s': %llu", file->relativePath, (u64)file->size);
        }
    }

    struct Packet p2 = { 0 };
    packet_init(&p2, PACKET_MOD_LIST_DONE, true, PLMT_NONE);
    network_send_to(0, &p2);

    packet_ordered_end();

}

void network_receive_mod_list(struct Packet* p) {
    SOFT_ASSERT(gNetworkType == NT_CLIENT);

    if (p->localIndex != UNKNOWN_LOCAL_INDEX) {
        if (gNetworkPlayerServer == NULL || gNetworkPlayerServer->localIndex != p->localIndex) {
            LOG_ERROR("Received mod list from known local index '%d'", p->localIndex);
            return;
        }
    }

    if (gRemoteMods.entries != NULL) {
        LOG_INFO("received mod list after allocating");
        return;
    }

    if (gNetworkServerAddr == NULL) {
        gNetworkServerAddr = network_duplicate_address(0);
    }

    char version[MAX_VERSION_LENGTH] = { 0 };
    snprintf(version, MAX_VERSION_LENGTH, "%s", get_version());
    LOG_INFO("client has version: %s", version);

    // verify version
    char remoteVersion[MAX_VERSION_LENGTH] = { 0 };
    packet_read(p, &remoteVersion, sizeof(u8) * MAX_VERSION_LENGTH);
    LOG_INFO("server has version: %s", version);
    if (memcmp(version, remoteVersion, MAX_VERSION_LENGTH) != 0) {
        network_shutdown(true, false, false, false);
        LOG_ERROR("version mismatch");
        char mismatchMessage[256] = { 0 };
        snprintf(mismatchMessage, 256, "\\#ffa0a0\\Error:\\#dcdcdc\\ Version mismatch.\n\nYour version: \\#a0a0ff\\%s\\#dcdcdc\\\nTheir version: \\#a0a0ff\\%s\\#dcdcdc\\\n\nSomeone is out of date!\n", version, remoteVersion);
        djui_panel_join_message_error(mismatchMessage);
        return;
    }

    packet_read(p, &gRemoteMods.entryCount, sizeof(u16));
    gRemoteMods.entries = calloc(gRemoteMods.entryCount, sizeof(struct Mod*));
    if (gRemoteMods.entries == NULL) {
        LOG_ERROR("Failed to allocate remote mod entries");
        return;
    }

    LOG_INFO("received mod list (%u):", gRemoteMods.entryCount);
}

void network_receive_mod_list_entry(struct Packet* p) {
    SOFT_ASSERT(gNetworkType == NT_CLIENT);

    // make sure it was sent by the server
    if (p->localIndex != UNKNOWN_LOCAL_INDEX) {
        if (gNetworkPlayerServer == NULL || gNetworkPlayerServer->localIndex != p->localIndex) {
            LOG_ERROR("Received download from known local index '%d'", p->localIndex);
            return;
        }
    }

    // get mod index
    u16 modIndex = 0;
    packet_read(p, &modIndex, sizeof(u16));
    if (modIndex >= gRemoteMods.entryCount) {
        LOG_ERROR("Received mod outside of known range");
        return;
    }

    // allocate mod entry
    gRemoteMods.entries[modIndex] = calloc(1, sizeof(struct Mod));
    struct Mod* mod = gRemoteMods.entries[modIndex];
    if (mod == NULL) {
        LOG_ERROR("Failed to allocate remote mod!");
        return;
    }

    // get name length
    u16 nameLength = 0;
    packet_read(p, &nameLength, sizeof(u16));
    if (nameLength > MOD_NAME_MAX_LENGTH) {
        LOG_ERROR("Received name with invalid length!");
        return;
    }

    // get name
    char name[MOD_NAME_MAX_LENGTH + 1] = { 0 };
    packet_read(p, name, nameLength * sizeof(u8));
    mod->name = strdup(name);

    // get incompatible length
    u16 incompatibleLength = 0;
    packet_read(p, &incompatibleLength, sizeof(u16));
    if (incompatibleLength > MOD_INCOMPATIBLE_MAX_LENGTH) {
        LOG_ERROR("Received name with invalid length!");
        return;
    }

    // get incompatible
    if (incompatibleLength > 0) {
        char incompatible[MOD_INCOMPATIBLE_MAX_LENGTH + 1] = { 0 };
        packet_read(p, incompatible, incompatibleLength * sizeof(u8));
        mod->incompatible = strdup(incompatible);
    } else {
        packet_read(p, 0, 0);
    }

    // get other fields
    u16 relativePathLength = 0;
    packet_read(p, &relativePathLength, sizeof(u16));
    packet_read(p, mod->relativePath, relativePathLength * sizeof(u8));
    packet_read(p, &mod->size, sizeof(u64));
    packet_read(p, &mod->isDirectory, sizeof(u8));
    packet_read(p, &mod->pausable, sizeof(u8));
    packet_read(p, &mod->ignoreScriptWarnings, sizeof(u8));
    normalize_path(mod->relativePath);
    LOG_INFO("    '%s': %llu", mod->name, (u64)mod->size);

    // figure out base path
    if (mod->isDirectory) {
        if (snprintf(mod->basePath, SYS_MAX_PATH - 1, "%s/%s", gRemoteModsBasePath, mod->relativePath) < 0) {
            LOG_ERROR("Failed save remote base path!");
            return;
        }
        normalize_path(mod->basePath);
    } else {
        if (snprintf(mod->basePath, SYS_MAX_PATH - 1, "%s", gRemoteModsBasePath) < 0) {
            LOG_ERROR("Failed save remote base path!");
            return;
        }
    }

    // sanity check mod size
    if (mod->size >= MAX_MOD_SIZE) {
        djui_popup_create(DLANG(NOTIF, DISCONNECT_BIG_MOD), 4);
        network_shutdown(false, false, false, false);
        return;
    }

    // get file count and allocate them
    packet_read(p, &mod->fileCount, sizeof(u16));
    mod->files = calloc(mod->fileCount, sizeof(struct ModFile));
    if (mod->files == NULL) {
        LOG_ERROR("Failed to allocate mod files!");
        return;
    }
}

void network_receive_mod_list_file(struct Packet* p) {
    SOFT_ASSERT(gNetworkType == NT_CLIENT);

    if (p->localIndex != UNKNOWN_LOCAL_INDEX) {
        if (gNetworkPlayerServer == NULL || gNetworkPlayerServer->localIndex != p->localIndex) {
            LOG_ERROR("Received download from known local index '%d'", p->localIndex);
            return;
        }
    }

    // get mod index
    u16 modIndex = 0;
    packet_read(p, &modIndex, sizeof(u16));
    if (modIndex >= gRemoteMods.entryCount) {
        LOG_ERROR("Received mod outside of known range");
        return;
    }
    struct Mod* mod = gRemoteMods.entries[modIndex];
    if (mod == NULL) {
        LOG_ERROR("Received mod file for null mod");
        return;
    }

    // get file index
    u16 fileIndex = 0;
    packet_read(p, &fileIndex, sizeof(u16));
    if (fileIndex >= mod->fileCount) {
        LOG_ERROR("Received mod file outside of known range");
        return;
    }
    struct ModFile* file = &mod->files[fileIndex];
    if (mod == NULL) {
        LOG_ERROR("Received null mod file");
        return;
    }

    u16 relativePathLength = 0;
    packet_read(p, &relativePathLength, sizeof(u16));
    packet_read(p, file->relativePath, relativePathLength * sizeof(u8));
    packet_read(p, &file->size, sizeof(u64));
    packet_read(p, &file->dataHash, sizeof(u8) * 16);
    file->fp = NULL;
    LOG_INFO("      '%s': %llu", file->relativePath, (u64)file->size);

    struct ModCacheEntry* cache = mod_cache_get_from_hash(file->dataHash);
    if (cache != NULL) {
        LOG_INFO("Found file in cache: %s -> %s", file->relativePath, cache->path);
        if (file->cachedPath != NULL) {
            free((char*)file->cachedPath);
        }
        file->cachedPath = strdup(cache->path);
        normalize_path(file->cachedPath);
    }
}

void network_receive_mod_list_done(struct Packet* p) {
    SOFT_ASSERT(gNetworkType == NT_CLIENT);

    if (p->localIndex != UNKNOWN_LOCAL_INDEX) {
        if (gNetworkPlayerServer == NULL || gNetworkPlayerServer->localIndex != p->localIndex) {
            LOG_ERROR("Received download from known local index '%d'", p->localIndex);
            return;
        }
    }

    size_t totalSize = 0;
    for (u16 i = 0; i < gRemoteMods.entryCount; i++) {
        struct Mod* mod = gRemoteMods.entries[i];
        totalSize += mod->size;
    }
    gRemoteMods.size = totalSize;

    network_start_download_requests();
}
