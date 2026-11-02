#include <stdio.h>
#include "local.h"
#include "pc/debuglog.h"

static bool ns_local_initialize(enum NetworkType networkType, UNUSED bool reconnecting) {
    if (networkType == NT_CLIENT) {
        LOG_ERROR("cannot join a server without a network connection");
        return false;
    }
    LOG_INFO("initialized");
    return true;
}

static s64 ns_local_get_id(UNUSED u8 localIndex) {
    return 0;
}

static char* ns_local_get_id_str(UNUSED u8 localIndex) {
    static char sIdStr[] = "local";
    return sIdStr;
}

static void ns_local_save_id(UNUSED u8 localIndex, UNUSED s64 networkId) {
}

static void ns_local_clear_id(UNUSED u8 localIndex) {
}

static void* ns_local_dup_addr(UNUSED u8 localIndex) {
    return NULL;
}

static bool ns_local_match_addr(UNUSED void* addr1, UNUSED void* addr2) {
    return false;
}

static void ns_local_update(void) {
}

static int ns_local_send(UNUSED u8 localIndex, UNUSED void* address, UNUSED u8* data, UNUSED u16 dataLength) {
    return 0;
}

static void ns_local_get_lobby_id(char* destination, u32 destLength) {
    snprintf(destination, destLength, "%s", "");
}

static void ns_local_get_lobby_secret(char* destination, u32 destLength) {
    snprintf(destination, destLength, "%s", "");
}

static void ns_local_shutdown(UNUSED bool reconnecting) {
    LOG_INFO("shutdown");
}

struct NetworkSystem gNetworkSystemLocal = {
    .initialize       = ns_local_initialize,
    .get_id           = ns_local_get_id,
    .get_id_str       = ns_local_get_id_str,
    .save_id          = ns_local_save_id,
    .clear_id         = ns_local_clear_id,
    .dup_addr         = ns_local_dup_addr,
    .match_addr       = ns_local_match_addr,
    .update           = ns_local_update,
    .send             = ns_local_send,
    .get_lobby_id     = ns_local_get_lobby_id,
    .get_lobby_secret = ns_local_get_lobby_secret,
    .shutdown         = ns_local_shutdown,
    .requireServerBroadcast = true,
    .name             = "Local",
};
