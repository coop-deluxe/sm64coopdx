#include <stdio.h>
#include "../network.h"
#include "pc/mod_list.h"
#include "pc/djui/djui.h"
#include "pc/debuglog.h"

void network_send_mod_list_request(void) {
    SOFT_ASSERT(gNetworkType == NT_CLIENT);
    mod_table_clear(&gModTableRemote);

    struct Packet p = { 0 };
    packet_init(&p, PACKET_MOD_LIST_REQUEST, true, PLMT_NONE);

    network_send_to((gNetworkPlayerServer != NULL) ? gNetworkPlayerServer->localIndex : 0, &p);
    LOG_INFO("sending mod list request");
}

void network_receive_mod_list_request(UNUSED struct Packet* p) {
    SOFT_ASSERT(gNetworkType == NT_SERVER);
    LOG_INFO("received mod list request");

    network_send_mod_list();
}

void network_send_mod_list(void) {
    SOFT_ASSERT(gNetworkType == NT_SERVER);

    struct Packet p = { 0 };
    packet_init(&p, PACKET_MOD_LIST, true, PLMT_NONE);

    char version[MAX_VERSION_LENGTH] = { 0 };
    snprintf(version, MAX_VERSION_LENGTH, "%s", get_version());
    LOG_INFO("sending version: %s", version);
    packet_write(&p, &version, sizeof(u8) * MAX_VERSION_LENGTH);

    u16 activeCount = 0;
    for (u16 i = 0; i < gModTableLocal.entryCount; i++) {
        struct ModListEntry* entry = &gModTableLocal.entries[i];
        if (entry->enabled) { activeCount++; }
    }

    packet_write(&p, &activeCount, sizeof(u16));
    LOG_INFO("sent mod list (%u):", gModTableLocal.entryCount);
    for (u16 i = 0; i < gModTableLocal.entryCount; i++) {
        struct ModListEntry* entry = &gModTableLocal.entries[i];
        if (!entry->enabled) { continue; }
        u16 nameLength = strlen(entry->name);
        packet_write(&p, &i, sizeof(u16));
        packet_write(&p, &nameLength, sizeof(u16));
        packet_write(&p, entry->name, sizeof(u8) * nameLength);
        packet_write(&p, &entry->size, sizeof(u16));
        LOG_INFO("    '%s': %u", entry->name, (u16)entry->size);
    }
    network_send_to(0, &p);
}

void network_receive_mod_list(struct Packet* p) {
    SOFT_ASSERT(gNetworkType == NT_CLIENT);

    if (p->localIndex != UNKNOWN_LOCAL_INDEX) {
        if (gNetworkPlayerServer == NULL || gNetworkPlayerServer->localIndex != p->localIndex) {
            LOG_ERROR("Received download from known local index '%d'", p->localIndex);
            return;
        }
    }

    if (gModTableRemote.entries != NULL) {
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
        network_shutdown(true);
        LOG_ERROR("version mismatch");
        char mismatchMessage[256] = { 0 };
        snprintf(mismatchMessage, 256, "\\#ffa0a0\\Error:\\#c8c8c8\\ Version mismatch.\n\nYour version: \\#a0a0ff\\%s\\#c8c8c8\\\nTheir version: \\#a0a0ff\\%s\\#c8c8c8\\\n\nSomeone is out of date!\n", version, remoteVersion);
        djui_panel_join_message_error(mismatchMessage);
        return;
    }

    u16 modEntryCount = 0;
    gModTableCurrent = &gModTableRemote;

    packet_read(p, &modEntryCount, sizeof(u16));
    mod_list_alloc(&gModTableRemote, modEntryCount);

    LOG_INFO("received mod list (%u):", modEntryCount);
    for (int i = 0; i < modEntryCount; i++) {
        u16 remoteIndex = 0;
        packet_read(p, &remoteIndex, sizeof(u16));

        u16 nameLength = 0;
        packet_read(p, &nameLength, sizeof(u16));

        char* name = (char*)calloc(nameLength + 1, sizeof(u8));
        packet_read(p, name, nameLength * sizeof(u8));

        u16 size = 0;
        packet_read(p, &size, sizeof(u16));

        mod_list_add_tmp(i, remoteIndex, name, size);

        LOG_INFO("    '%s': %u", name, size);
    }

    network_send_next_download_request();
}
