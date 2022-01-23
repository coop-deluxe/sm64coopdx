#include <stdio.h>
#include "../network.h"
#include "pc/mod_list.h"
#include "pc/debuglog.h"

void network_send_mod_list_request(void) {
    SOFT_ASSERT(gNetworkType == NT_CLIENT);
    mod_list_shutdown();

    struct Packet p = { 0 };
    packet_init(&p, PACKET_MOD_LIST_REQUEST, true, PLMT_NONE);

    char version[MAX_VERSION_LENGTH] = { 0 };
    snprintf(version, MAX_VERSION_LENGTH, "%s", get_version());
    packet_write(&p, &version, sizeof(u8) * MAX_VERSION_LENGTH);

    network_send_to((gNetworkPlayerServer != NULL) ? gNetworkPlayerServer->localIndex : 0, &p);
    LOG_INFO("sending mod list request");
}

void network_receive_mod_list_request(struct Packet* p) {
    SOFT_ASSERT(gNetworkType == NT_SERVER);
    LOG_INFO("received mod list request");

    char version[MAX_VERSION_LENGTH] = { 0 };
    snprintf(version, MAX_VERSION_LENGTH, "%s", get_version());

    char remoteVersion[MAX_VERSION_LENGTH] = { 0 };
    packet_read(p, &remoteVersion, sizeof(u8) * MAX_VERSION_LENGTH);
    LOG_INFO("client has version: %s", remoteVersion);

    if (memcmp(version, remoteVersion, MAX_VERSION_LENGTH) != 0) {
        LOG_INFO("client version mismatch: %s != %s", remoteVersion, version);
        // TODO: send version mismatch packet
        return;
    }

    network_send_mod_list();
}

void network_send_mod_list(void) {
    SOFT_ASSERT(gNetworkType == NT_SERVER);

    struct Packet p = { 0 };
    packet_init(&p, PACKET_MOD_LIST, true, PLMT_NONE);

    packet_write(&p, &gModEntryCount, sizeof(u16));
    LOG_INFO("sent mod list (%u):", gModEntryCount);
    for (int i = 0; i < gModEntryCount; i++) {
        struct ModListEntry* entry = &gModEntries[i];
        u16 nameLength = strlen(entry->name);
        packet_write(&p, &nameLength, sizeof(u16));
        packet_write(&p, entry->name, sizeof(u8) * nameLength);
        packet_write(&p, &entry->size, sizeof(u16));
        LOG_INFO("    '%s': %u", entry->name, (u16)entry->size);
    }
    network_send_to(0, &p);
}

void network_receive_mod_list(struct Packet* p) {
    SOFT_ASSERT(gNetworkType == NT_CLIENT);
    SOFT_ASSERT(p->localIndex == UNKNOWN_LOCAL_INDEX);
    if (gModEntries != NULL) {
        LOG_INFO("received mod list after allocating");
        return;
    }

    if (gNetworkServerAddr == NULL) {
        gNetworkServerAddr = network_duplicate_address(0);
    }

    u16 modEntryCount = 0;
    packet_read(p, &modEntryCount, sizeof(u16));
    mod_list_alloc(modEntryCount);

    LOG_INFO("received mod list (%u):", modEntryCount);
    gModTotalSize = 0;
    for (int i = 0; i < modEntryCount; i++) {
        u16 nameLength = 0;
        packet_read(p, &nameLength, sizeof(u16));

        char* name = (char*)calloc(nameLength + 1, sizeof(u8));
        packet_read(p, name, nameLength * sizeof(u8));

        u16 size = 0;
        packet_read(p, &size, sizeof(u16));

        mod_list_add(i, name, size, true);
        LOG_INFO("    '%s': %u", name, size);
    }

    if (modEntryCount <= 0) {
        network_send_join_request();
    } else {
        network_send_download_request(0, 0);
    }
}
