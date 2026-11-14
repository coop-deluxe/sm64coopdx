#include <stdio.h>
#include "../network.h"
#include "pc/mods/mods.h"
#include "pc/mods/mods_utils.h"
#include "pc/djui/djui.h"
#include "pc/djui/djui_panel_join_message.h"
#include "pc/debuglog.h"
#include "pc/pc_main.h"
#include "pc/mods/mod_cache.h"

void network_send_mod_list_request(void) {
    SOFT_ASSERT(gNetworkType == NT_CLIENT);
    SOFT_ASSERT(gGameInited);
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
    packet_write_uint16(&p, gActiveMods.entryCount);
    
    network_send_to(0, &p);
    packet_clear(&p);

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
        packet_write_uint16(&p, i);
        packet_write_uint16(&p, nameLength);
        packet_write(&p, mod->name, sizeof(u8) * nameLength);
        if (mod->incompatible) {
            packet_write_uint16(&p, incompatibleLength);
            packet_write(&p, mod->incompatible, sizeof(u8) * incompatibleLength);
        } else {
            packet_write_uint16(&p, 0);
            packet_write(&p, "", 0);
        }
        packet_write_uint16(&p, relativePathLength);
        packet_write(&p, mod->relativePath, sizeof(u8) * relativePathLength);
        packet_write_uint64(&p, modSize);
        packet_write_uint8(&p, mod->isDirectory);
        packet_write_uint8(&p, mod->pausable);
        packet_write_uint8(&p, mod->ignoreScriptWarnings);
        packet_write_uint16(&p, mod->fileCount);
        network_send_to(0, &p);
        packet_clear(&p);
        LOG_INFO("    '%s': %llu", mod->name, (u64)mod->size);

        for (u16 j = 0; j < mod->fileCount; j++) {
            struct Packet p = { 0 };
            packet_init(&p, PACKET_MOD_LIST_FILE, true, PLMT_NONE);
            struct ModFile* file = &mod->files[j];
            u16 relativePathLength = strlen(file->relativePath);
            u64 fileSize = file->size;
            packet_write_uint16(&p, i);
            packet_write_uint16(&p, j);
            packet_write_uint16(&p, relativePathLength);
            packet_write(&p, file->relativePath, sizeof(u8) * relativePathLength);
            packet_write_uint64(&p, fileSize);
            packet_write(&p, &file->dataHash[0], sizeof(u8) * 16);
            network_send_to(0, &p);
            packet_clear(&p);
            LOG_INFO("      '%s': %llu", file->relativePath, (u64)file->size);
        }
    }

    struct Packet p2 = { 0 };
    packet_init(&p2, PACKET_MOD_LIST_DONE, true, PLMT_NONE);
    network_send_to(0, &p2);
    packet_clear(&p2);

    packet_ordered_end();
}

void network_receive_mod_list(struct Packet* p) {
    if (p == NULL) { return; }
    
    // Sanity check for data contents. Read will throw an error anyways,
    // But it's better to catch malformed or maliciously formed packets here.
    SOFT_ASSERT(packet_get_remaining_size(p) >= sizeof(u16) + (sizeof(u8) * MAX_VERSION_LENGTH));

    SOFT_ASSERT(gNetworkType == NT_CLIENT);

    if (p->localIndex != UNKNOWN_LOCAL_INDEX) {
        if (gNetworkPlayerServer == NULL || gNetworkPlayerServer->localIndex != p->localIndex) {
            LOG_ERROR("Received mod list from known local index '%d'", p->localIndex);
            return;
        }
    }

    if (gRemoteMods.entries != NULL) {
        LOG_INFO("Received mod list after allocating");
        return;
    }

    if (gNetworkServerAddr == NULL) {
        gNetworkServerAddr = network_duplicate_address(0);
    }

    char version[MAX_VERSION_LENGTH] = { 0 };
    snprintf(version, MAX_VERSION_LENGTH, "%s", get_version());
    LOG_INFO("Client has version: %s", version);

    // Verify version
    char remoteVersion[MAX_VERSION_LENGTH] = { 0 };
    packet_read(p, &remoteVersion, sizeof(u8) * MAX_VERSION_LENGTH);
    LOG_INFO("Server has version: %s", version);
    if (memcmp(version, remoteVersion, MAX_VERSION_LENGTH) != 0) {
        network_shutdown(true, false, false, false);
        LOG_ERROR("Version mismatch");
        char mismatchMessage[256] = { 0 };
        snprintf(mismatchMessage, 256, "\\#ffa0a0\\Error:\\#\\ Version mismatch.\n\nYour version: \\#a0a0ff\\%s\\#\\\nTheir version: \\#a0a0ff\\%s\\#\\\n\nSomeone is out of date!\n", version, remoteVersion);
        djui_panel_join_message_error(mismatchMessage);
        return;
    }
    
    gRemoteMods.entryCount = packet_read_uint16(p);
    gRemoteMods.entries = calloc(gRemoteMods.entryCount, sizeof(struct Mod*));
    if (gRemoteMods.entries == NULL) {
        LOG_ERROR("Failed to allocate remote mod entries");
        return;
    }

    LOG_INFO("Received mod list (%u):", gRemoteMods.entryCount);
}

void network_receive_mod_list_entry(struct Packet* p) {
    if (p == NULL) { return; }
    
    SOFT_ASSERT(gNetworkType == NT_CLIENT);

    // make sure it was sent by the server
    if (p->localIndex != UNKNOWN_LOCAL_INDEX) {
        if (gNetworkPlayerServer == NULL || gNetworkPlayerServer->localIndex != p->localIndex) {
            LOG_ERROR("Received download from known local index '%d'", p->localIndex);
            return;
        }
    }

    // Get mod index
    u16 modIndex = packet_read_uint16(p);
    if (modIndex >= gRemoteMods.entryCount) {
        LOG_ERROR("Received mod outside of known range");
        return;
    }

    // Allocate mod entry
    gRemoteMods.entries[modIndex] = calloc(1, sizeof(struct Mod));
    struct Mod* mod = gRemoteMods.entries[modIndex];
    if (mod == NULL) {
        LOG_ERROR("Failed to allocate remote mod!");
        return;
    }

    // Get name length
    u16 nameLength = packet_read_uint16(p);
    if (nameLength > MOD_NAME_MAX_LENGTH) {
        LOG_ERROR("Received name with invalid length!");
        return;
    }

    // Get name
    packet_read(p, mod->name, nameLength * sizeof(u8));
    mod->name[nameLength] = 0;

    // Get incompatible length
    u16 incompatibleLength = packet_read_uint16(p);
    if (incompatibleLength > MOD_INCOMPATIBLE_MAX_LENGTH) {
        LOG_ERROR("Received name with invalid length!");
        return;
    }

    // Get incompatible
    if (incompatibleLength > 0) {
        char incompatible[MOD_INCOMPATIBLE_SIZE] = { 0 };
        packet_read(p, incompatible, incompatibleLength * sizeof(u8));
        mod->incompatible = strdup(incompatible);
    } else {
        packet_read(p, 0, 0);
    }

    // Get relative path length
    u16 relativePathLength = packet_read_uint16(p);
    if (relativePathLength == 0 || relativePathLength >= SYS_MAX_PATH) {
        LOG_ERROR("Relative path length is invalid!");
        return;
    }

    // Get relative path
    packet_read(p, mod->relativePath, relativePathLength * sizeof(u8));
    if (path_has_traversal(mod->relativePath)) {
        LOG_ERROR("Received an invalid relative path!");
        mod->relativePath[0] = '\0'; // clear relative path so it isn't incorrectly used elsewhere
        return;
    }

    // Get other fields
    mod->size = packet_read_uint64(p);
    mod->isDirectory = packet_read_uint8(p);
    mod->pausable = packet_read_uint8(p);
    mod->ignoreScriptWarnings = packet_read_uint8(p);
    normalize_path(mod->relativePath);
    LOG_INFO("    '%s': %llu", mod->name, (u64)mod->size);

    // Figure out base path
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

    // Sanity check mod size
    if (mod->size >= MAX_MOD_SIZE) {
        djui_popup_create(DLANG(NOTIF, DISCONNECT_BIG_MOD), 4);
        network_shutdown(false, false, false, false);
        return;
    }

    // Get file count and allocate them
    mod->fileCount = packet_read_uint16(p);
    mod->files = calloc(mod->fileCount, sizeof(struct ModFile));
    if (mod->files == NULL) {
        LOG_ERROR("Failed to allocate mod files!");
        return;
    }
}

void network_receive_mod_list_file(struct Packet* p) {
    if (p == NULL) { return; }
    
    SOFT_ASSERT(gNetworkType == NT_CLIENT);

    if (p->localIndex != UNKNOWN_LOCAL_INDEX) {
        if (gNetworkPlayerServer == NULL || gNetworkPlayerServer->localIndex != p->localIndex) {
            LOG_ERROR("Received download from known local index '%d'", p->localIndex);
            return;
        }
    }

    // Get mod index
    u16 modIndex = packet_read_uint16(p);
    if (modIndex >= gRemoteMods.entryCount) {
        LOG_ERROR("Received mod outside of known range");
        return;
    }
    struct Mod* mod = gRemoteMods.entries[modIndex];
    if (mod == NULL) {
        LOG_ERROR("Received mod file for null mod");
        return;
    }

    // Get file index
    u16 fileIndex = packet_read_uint16(p);
    if (fileIndex >= mod->fileCount) {
        LOG_ERROR("Received mod file outside of known range");
        return;
    }
    struct ModFile* file = &mod->files[fileIndex];
    if (mod == NULL) {
        LOG_ERROR("Received null mod file");
        return;
    }

    // Read relative path len
    u16 relativePathLength = packet_read_uint16(p);
    if (relativePathLength == 0 || relativePathLength >= SYS_MAX_PATH) {
        LOG_ERROR("Relative path length is invalid!");
        return;
    }

    // Read relative path
    packet_read(p, file->relativePath, relativePathLength * sizeof(u8));
    if (path_has_traversal(file->relativePath)) {
        LOG_ERROR("Received an invalid relative path!");
        file->relativePath[0] = '\0';
        return;
    }

    // Read other fields
    file->size = packet_read_uint64(p);
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
    if (p == NULL) { return; }

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
