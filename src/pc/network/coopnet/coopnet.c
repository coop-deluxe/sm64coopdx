#include <inttypes.h>
#include "libcoopnet.h"
#include "coopnet.h"
#include "coopnet_id.h"
#include "pc/network/network.h"
#include "pc/network/version.h"
#include "pc/djui/djui_language.h"
#include "pc/djui/djui_popup.h"
#include "pc/djui/djui_panel_host_mods.h"
#include "pc/djui/mod_category.h"
#include "pc/mods/mods.h"
#include "pc/utils/misc.h"
#include "pc/debuglog.h"
#ifdef DISCORD_SDK
#include "pc/discord/discord.h"
#endif

#ifdef COOPNET

static struct ModCategory sModCategories[] = {
#define MOD_CATEGORY_DEF(key)
#define MOD_CATEGORY(key, category) { #key, category },
#include "pc/djui/mod_categories.inl"
#undef MOD_CATEGORY_DEF
#undef MOD_CATEGORY
};

uint64_t gCoopNetDesiredLobby = 0;
char gCoopNetPassword[COOPNET_MAX_PASSWORD_LEN] = "";
char sCoopNetDescription[COOPNET_MAX_DESCRIPTION_LEN] = "";

static uint64_t sLocalLobbyId = 0;
static uint64_t sLocalLobbyOwnerId = 0;
static enum NetworkType sNetworkType;
static bool sReconnecting = false;
static u64 *sTimePtr = NULL;
static bool sGotTime = false;

static CoopNetRc coopnet_initialize(void);

bool ns_coopnet_query(QueryCallbackPtr callback, QueryFinishCallbackPtr finishCallback, const char* password) {
    gCoopNetCallbacks.OnLobbyListGot = callback;
    gCoopNetCallbacks.OnLobbyListFinish = finishCallback;
    if (coopnet_initialize() != COOPNET_OK) { return false; }
    if (coopnet_lobby_list_get(GAME_NAME, password) != COOPNET_OK) { return false; }
    return true;
}

static void coopnet_on_got_time(uint64_t time) {
    if (sTimePtr == NULL) { return; }
    *sTimePtr = time;
    sGotTime = true;
}

bool ns_coopnet_get_time(uint64_t *time, float timeout) {
    gCoopNetCallbacks.OnTimeGot = coopnet_on_got_time;
    sTimePtr = time;
    sGotTime = false;
    if (coopnet_initialize() != COOPNET_OK) { return false; }
    if (coopnet_time_get() != COOPNET_OK) { return false; }
    // update and wait to get the time
    float startTime = clock_elapsed();
    float curTime = startTime;
    while (sTimePtr) {
        coopnet_update();
        if (sGotTime) { break; }
        curTime = clock_elapsed();

        // if it's been too long, null out the time ptr and bail
        if (curTime - startTime >= timeout) {
            sTimePtr = NULL;
            return false;
        }
    }
    return true;
}

static void coopnet_on_connected(uint64_t userId) {
    coopnet_set_local_user_id(userId);
}

static void coopnet_on_disconnected(bool intentional) {
    LOG_INFO("coopnet_on_disconnected: Coopnet shutdown!");
    if (!intentional) {
        djui_popup_create(DLANG(NOTIF, COOPNET_DISCONNECTED), 2);
    }
    coopnet_shutdown();
    gCoopNetCallbacks.OnLobbyListGot = NULL;
    gCoopNetCallbacks.OnLobbyListFinish = NULL;
}

static void coopnet_on_peer_disconnected(uint64_t peerId) {
    u8 localIndex = coopnet_user_id_to_local_index(peerId);
    if (localIndex != UNKNOWN_LOCAL_INDEX && gNetworkPlayers[localIndex].connected) {
        network_player_disconnected(gNetworkPlayers[localIndex].globalIndex);
    }
}

static void coopnet_on_load_balance(const char* host, uint32_t port) {
    if (host && strlen(host) > 0) {
        snprintf(configCoopNetIp, MAX_CONFIG_STRING, "%s", host);
    }
    configCoopNetPort = port;
    configfile_save(configfile_name());
}

static void coopnet_on_receive(uint64_t userId, const uint8_t* data, uint64_t dataLength) {
    coopnet_set_user_id(0, userId);
    u8 localIndex = coopnet_user_id_to_local_index(userId);
    network_receive(localIndex, &userId, (u8*)data, dataLength);
}

static void coopnet_on_lobby_joined(uint64_t lobbyId, uint64_t userId, uint64_t ownerId, uint64_t destId) {
    LOG_INFO("coopnet_on_lobby_joined!");
    coopnet_set_user_id(0, ownerId);
    sLocalLobbyId = lobbyId;
    sLocalLobbyOwnerId = ownerId;

    if (userId == coopnet_get_local_user_id()) {
        coopnet_clear_dest_ids();
        snprintf(configDestId, MAX_CONFIG_STRING, "%" PRIu64 "", destId);
    }

    coopnet_save_dest_id(userId, destId);

    if (userId == coopnet_get_local_user_id() && gNetworkType == NT_CLIENT) {
        network_send_mod_list_request();
    }
#ifdef DISCORD_SDK
    if (gDiscordInitialized) {
        discord_activity_update();
    }
#endif
}

static void coopnet_on_lobby_left(uint64_t lobbyId, uint64_t userId) {
    LOG_INFO("coopnet_on_lobby_left!");
    coopnet_clear_dest_id(userId);
    if (lobbyId == sLocalLobbyId && userId == coopnet_get_local_user_id()) {
        network_shutdown(false, false, true, false);
    }
}

static void coopnet_on_error(enum MPacketErrorNumber error, uint64_t tag) {
    switch (error) {
        case MERR_COOPNET_VERSION:
            djui_popup_create(DLANG(NOTIF, COOPNET_VERSION), 2);
            network_shutdown(false, false, false, false);
            break;
        case MERR_PEER_FAILED:
            {
                char built[256] = { 0 };
                u8 localIndex = coopnet_user_id_to_local_index(tag);
                char* name = DLANG(NOTIF, UNKNOWN);
                if (localIndex == 0) {
                    name = DLANG(NOTIF, LOBBY_HOST);
                } else if (localIndex != UNKNOWN_LOCAL_INDEX && gNetworkPlayers[localIndex].connected) {
                    name = gNetworkPlayers[localIndex].name;
                }
                djui_language_replace(DLANG(NOTIF, PEER_FAILED), built, 256, '@', name);
                djui_popup_create(built, 2);
            }
            break;
        case MERR_LOBBY_CREATION_FAILED:
            djui_popup_create(DLANG(NOTIF, LOBBY_CREATION_FAILED), 2);
            network_shutdown(false, false, false, false);
            break;
        case MERR_LOBBY_NOT_FOUND:
            djui_popup_create(DLANG(NOTIF, LOBBY_NOT_FOUND), 2);
            network_shutdown(false, false, false, false);
            break;
        case MERR_LOBBY_JOIN_FULL:
            djui_popup_create(DLANG(NOTIF, DISCONNECT_FULL), 2);
            network_shutdown(false, false, false, false);
            break;
        case MERR_LOBBY_JOIN_FAILED:
            djui_popup_create(DLANG(NOTIF, LOBBY_JOIN_FAILED), 2);
            network_shutdown(false, false, false, false);
            break;
        case MERR_LOBBY_PASSWORD_INCORRECT:
            djui_popup_create(DLANG(NOTIF, LOBBY_PASSWORD_INCORRECT), 2);
            network_shutdown(false, false, false, false);
            break;
        case MERR_NONE:
        case MERR_MAX:
            break;
    }
}

static bool ns_coopnet_initialize(enum NetworkType networkType, bool reconnecting) {
    sNetworkType = networkType;
    sReconnecting = reconnecting;
    if (reconnecting) { return true; }
    return coopnet_is_connected()
        ? true
        : (coopnet_initialize() == COOPNET_OK);
}

static char* ns_coopnet_get_id_str(u8 localIndex) {
    static char id_str[32] = { 0 };
    if (localIndex == UNKNOWN_LOCAL_INDEX) {
        snprintf(id_str, 32, "???");
    } else {
        uint64_t userId = ns_coopnet_get_id(localIndex);
        uint64_t destId = coopnet_get_dest_id(userId);
        snprintf(id_str, 32, "%" PRIu64 "", destId);
    }
    return id_str;
}

static bool ns_coopnet_match_addr(void* addr1, void* addr2) {
    return !memcmp(addr1, addr2, sizeof(u64));
}

bool ns_coopnet_is_connected(void) {
    return coopnet_is_connected();
}

static void coopnet_generate_coopnet_description(struct CoopnetDescription *coopnetDesc) {
    coopnetDesc->majorVer = VERSION_NUMBER;
    coopnetDesc->minorVer = MINOR_VERSION_NUMBER;
    coopnetDesc->modSize = gActiveMods.size;

    if (!ns_coopnet_get_time(&coopnetDesc->timestamp, 1.0f)) {
        djui_popup_create(DLANG(NOTIF, LOBBY_CREATION_FAILED), 2);
        network_shutdown(false, false, false, false);
        return;
    }

    if (gActiveMods.entryCount <= 0) { return; }

    // iterate through mod categories
    for (size_t i = 0; i < ARRAY_COUNT(sModCategories); i++) {
        struct ModCategory *category = &sModCategories[i];

        // get the name of each mod in that category
        char *modNames[gActiveMods.entryCount];
        u32 modCount = 0;
        for (int j = 0; j < gActiveMods.entryCount; j++) {
            struct Mod *mod = gActiveMods.entries[j];
            char *modCategory = mod->category != NULL ? mod->category : mod->incompatible;
            if (modCategory && strstr_lowercased(modCategory, category->category)) {
                modNames[modCount++] = mod->name;
            }
        }

        if (modCount == 0) { continue; }

        // increment category count
        coopnetDesc->modCategoryCount++;

        // realloc category array with new required size
        struct CoopnetModCategory *newCategoryArray = realloc(coopnetDesc->modCategories, coopnetDesc->modCategoryCount * sizeof(struct CoopnetModCategory));
        if (newCategoryArray == NULL) {
            LOG_ERROR("Failed to allocate category array for coopnet description");
            coopnetDesc->modCategoryCount--; // revert count increment
            return;
        }
        coopnetDesc->modCategories = newCategoryArray;

        struct CoopnetModCategory *coopnetModCategory = &coopnetDesc->modCategories[coopnetDesc->modCategoryCount - 1];

        // add category entry to coopnet desc
        snprintf(coopnetModCategory->name, MOD_CATEGORY_SIZE, "%s", category->langKey);

        // add each mod to the coopnet desc
        for (u16 j = 0; j < modCount; j++) {
            // increment mod count
            coopnetModCategory->modCount++;

            // realloc mod with new required size
            struct CoopnetMod *newModArray = realloc(coopnetModCategory->mod, coopnetModCategory->modCount * sizeof(struct CoopnetMod));
            if (newModArray == NULL) {
                LOG_ERROR("Failed to reallocate mods for coopnet description");
                coopnetModCategory->modCount--; // revert count increment
                return;
            }
            coopnetModCategory->mod = newModArray;

            struct CoopnetMod *mod = &coopnetModCategory->mod[coopnetModCategory->modCount - 1];
            snprintf(mod->name, MOD_NAME_SIZE, "%s", modNames[j]);
        }
    }

    // add mods that are not in a category, labeled as MISC
    char *modNames[gActiveMods.entryCount];
    u32 modCount = 0;
    for (u16 j = 0; j < gActiveMods.entryCount; j++) {
        struct Mod *mod = gActiveMods.entries[j];
        char *modCategory = mod->category != NULL ? mod->category : mod->incompatible;
        bool doContinue = false;
        if (modCategory) {
            // make sure we are NOT in a valid category
            for (size_t i = 0; i < ARRAY_COUNT(sModCategories); i++) {
                if (strstr_lowercased(modCategory, sModCategories[i].category)) {
                    doContinue = true;
                    break;
                }
            }
        }
        if (doContinue) { continue; }
        modNames[modCount++] = mod->name;
    }

    if (modCount == 0) { return; }

    // increment category count
    coopnetDesc->modCategoryCount++;

    // realloc category array with new required size
    struct CoopnetModCategory *newCategoryArray = realloc(coopnetDesc->modCategories, coopnetDesc->modCategoryCount * sizeof(struct CoopnetModCategory));
    if (newCategoryArray == NULL) {
        LOG_ERROR("Failed to allocate category array for coopnet description");
        coopnetDesc->modCategoryCount--; // revert count increment
        return;
    }
    coopnetDesc->modCategories = newCategoryArray;

    struct CoopnetModCategory *coopnetModCategory = &coopnetDesc->modCategories[coopnetDesc->modCategoryCount - 1];

    snprintf(coopnetModCategory->name, MOD_CATEGORY_SIZE, "MISC");

    // add each mod to the coopnet desc
    for (u16 j = 0; j < modCount; j++) {
        // increment mod count
        coopnetModCategory->modCount++;

        // realloc mod with new required size
        struct CoopnetMod *newModArray = realloc(coopnetModCategory->mod, coopnetModCategory->modCount * sizeof(struct CoopnetMod));
        if (newModArray == NULL) {
            LOG_ERROR("Failed to reallocate mods for coopnet description");
            return;
        }
        coopnetModCategory->mod = newModArray;

        struct CoopnetMod *mod = &coopnetModCategory->mod[coopnetModCategory->modCount - 1];
        snprintf(mod->name, MOD_NAME_SIZE, "%s", modNames[j]);
    }
}

static void write_to_desc(char *dest, size_t destMaxLength, const char *fmt, ...) {
    size_t destLength = strlen(dest);

    // check we can write data
    if (destLength >= destMaxLength - 1) { return; }

    // get the write buffer pointer loc, and get the amount of data we can write
    char *writeBuffer = dest + destLength;
    size_t writeLength = destMaxLength - destLength;

    // set write buffer
    va_list args;
    va_start(args, fmt);
    vsnprintf(writeBuffer, writeLength, fmt, args);
    va_end(args);
}

static void coopnet_activate_coopnet_description(struct CoopnetDescription *coopnetDesc) {
    memset(sCoopNetDescription, 0, sizeof(sCoopNetDescription));

    // write version info
    write_to_desc(sCoopNetDescription, COOPNET_MAX_DESCRIPTION_LEN, "%u,", coopnetDesc->majorVer);
    write_to_desc(sCoopNetDescription, COOPNET_MAX_DESCRIPTION_LEN, "%u,", coopnetDesc->minorVer);

    // write mod size
    write_to_desc(sCoopNetDescription, COOPNET_MAX_DESCRIPTION_LEN, "%zu,", coopnetDesc->modSize);

    // write timestamp
    write_to_desc(sCoopNetDescription, COOPNET_MAX_DESCRIPTION_LEN, "%llu,", coopnetDesc->timestamp);

    // write mod categories
    write_to_desc(sCoopNetDescription, COOPNET_MAX_DESCRIPTION_LEN, "%u,", coopnetDesc->modCategoryCount);

    for (u16 i = 0; i < coopnetDesc->modCategoryCount; i++) {
        struct CoopnetModCategory *category = &coopnetDesc->modCategories[i];

        size_t categoryNameLength = strlen(category->name);

        // write category info
        write_to_desc(sCoopNetDescription, COOPNET_MAX_DESCRIPTION_LEN, "%zu,%s", categoryNameLength, category->name);
        write_to_desc(sCoopNetDescription, COOPNET_MAX_DESCRIPTION_LEN, "%u,", category->modCount);

        // write mods in category
        for (u16 j = 0; j < category->modCount; j++) {
            struct CoopnetMod *mod = &category->mod[j];

            size_t modNameLength = strlen(mod->name);

            write_to_desc(sCoopNetDescription, COOPNET_MAX_DESCRIPTION_LEN, "%zu,%s", modNameLength, mod->name);
        }
    }
}

void ns_coopnet_update(void) {
    if (!coopnet_is_connected()) { return; }

    coopnet_update();
    if (gNetworkType != NT_NONE && sNetworkType != NT_NONE) {
        if (sNetworkType == NT_SERVER) {
            char mode[MOD_NAME_SIZE] = "";
            mods_get_main_mod_name(mode, MOD_NAME_SIZE);

            struct CoopnetDescription coopnetDesc = { 0 };
            coopnet_generate_coopnet_description(&coopnetDesc);
            coopnet_activate_coopnet_description(&coopnetDesc);
            ns_coopnet_free_coopnet_description(&coopnetDesc);

            if (sReconnecting) {
                LOG_INFO("Update lobby");
                if (gNetworkType != NT_SERVER) {
                    sNetworkType = NT_NONE;
                    return;
                }
                coopnet_lobby_update(sLocalLobbyId, GAME_NAME, get_version(), configPlayerName, mode, sCoopNetDescription);
            } else {
                LOG_INFO("Create lobby");
                snprintf(gCoopNetPassword, COOPNET_MAX_PASSWORD_LEN, "%s", configPassword);
                if (gNetworkType != NT_SERVER) {
                    sNetworkType = NT_NONE;
                    return;
                }
                coopnet_lobby_create(GAME_NAME, get_version(), configPlayerName, mode, (uint16_t)configAmountOfPlayers, gCoopNetPassword, sCoopNetDescription);
            }
        } else if (sNetworkType == NT_CLIENT) {
            LOG_INFO("Join lobby");
            coopnet_lobby_join(gCoopNetDesiredLobby, gCoopNetPassword);
        }
        sNetworkType = NT_NONE;
    }
}

void ns_coopnet_parse_coopnet_description(const char *descStr, struct CoopnetDescription *coopnetDesc) {
    if (descStr == NULL || coopnetDesc == NULL) { return; } // sanity check

    // clear out old data if it exists
    ns_coopnet_free_coopnet_description(coopnetDesc);

    const char *buffer = descStr;
    size_t descLen = strlen(descStr);
    int offsetBy = 0;

    u32 majorVer = 0;
    u32 minorVer = 0;
    u32 modCategoryCount = 0;

    // read metadata
    if (sscanf(buffer, "%u,%u,%zu,%llu,%u,%n", &majorVer, &minorVer, &coopnetDesc->modSize, &coopnetDesc->timestamp, &modCategoryCount, &offsetBy) != 5) {
        LOG_ERROR("Failed to parse coopnet description");
        return;
    }

    // sanity check max categories size
    if (modCategoryCount > ARRAY_COUNT(sModCategories)) {
        LOG_ERROR("Failed to parse coopnet description");
        return;
    }

    coopnetDesc->majorVer = (u8)majorVer;
    coopnetDesc->minorVer = (u8)minorVer;
    coopnetDesc->modCategoryCount = (u16)modCategoryCount;

    buffer += offsetBy;

    // allocate mod categories
    if (coopnetDesc->modCategoryCount > 0) {
        coopnetDesc->modCategories = calloc(coopnetDesc->modCategoryCount, sizeof(struct CoopnetModCategory));
        if (coopnetDesc->modCategories == NULL) {
            LOG_ERROR("Failed to parse coopnet description");
            return;
        }
    }

    // read mod categories
    for (u16 i = 0; i < coopnetDesc->modCategoryCount; i++) {
        struct CoopnetModCategory *category = &coopnetDesc->modCategories[i];
        size_t categoryNameLen = 0;

        // read category name length
        if (sscanf(buffer, "%zu,%n", &categoryNameLen, &offsetBy) != 1) {
            LOG_ERROR("Failed to parse coopnet description");
            return;
        }

        buffer += offsetBy;

        // sanity check buffer size for category name
        size_t remainingBytes = descLen - (buffer - descStr);
        if (categoryNameLen > remainingBytes) {
            LOG_ERROR("Failed to parse coopnet description");
            return;
        }

        // write the category name safely
        size_t copyNameLen = (categoryNameLen < MOD_CATEGORY_SIZE - 1) ? categoryNameLen : (MOD_CATEGORY_SIZE - 1);
        memcpy(category->name, buffer, copyNameLen);
        category->name[copyNameLen] = '\0'; // null terminate!

        // advance buffer past the incoming raw string size
        buffer += categoryNameLen;

        // read the amount of mods inside the category
        u32 modCount = 0;
        if (sscanf(buffer, "%u,%n", &modCount, &offsetBy) != 1) {
            LOG_ERROR("Failed to parse coopnet description");
            return;
        }
        category->modCount = (u16)modCount;
        buffer += offsetBy;

        if (category->modCount > 0) {
            // allocate mod array
            category->mod = calloc(category->modCount, sizeof(struct CoopnetMod));
            if (category->mod == NULL) {
                LOG_ERROR("Failed to parse coopnet description");
                return;
            }

            // read each mod
            for (u16 j = 0; j < category->modCount; j++) {
                struct CoopnetMod *mod = &category->mod[j];
                size_t modNameLen = 0;

                // read the mod name length
                if (sscanf(buffer, "%zu,%n", &modNameLen, &offsetBy) != 1) {
                    LOG_ERROR("Failed to parse coopnet description");
                    return;
                }

                buffer += offsetBy;

                // sanity check buffer size for mod name
                remainingBytes = descLen - (buffer - descStr);
                if (modNameLen > remainingBytes) {
                    LOG_ERROR("Failed to parse coopnet description");
                    return;
                }

                // read the mod name safely
                size_t copyModLen = (modNameLen < MOD_NAME_SIZE - 1) ? modNameLen : (MOD_NAME_SIZE - 1);
                memcpy(mod->name, buffer, copyModLen);
                mod->name[copyModLen] = '\0'; // null terminate!

                // advance buffer past the incoming raw string size
                buffer += modNameLen;
            }
        }
    }
}

void ns_coopnet_get_pretty_desc(char *dest, size_t destMaxLength, struct CoopnetDescription *coopnetDesc) {
    // write current version string
    write_to_desc(dest, destMaxLength, "%s\n\n", SM64COOPDX_VERSION);

    // write total mod size
    write_to_desc(dest, destMaxLength, "Total Mod Size: %s\n", get_size_string(coopnetDesc->modSize));

    // get total number of mods
    u16 totalModCount = 0;
    for (u16 i = 0; i < coopnetDesc->modCategoryCount; i++) {
        struct CoopnetModCategory *category = &coopnetDesc->modCategories[i];

        totalModCount += category->modCount;
    }

    // write mod header
    write_to_desc(dest, destMaxLength, "Mods (%u):\n\n", totalModCount);

    // write categories and mods
    for (u16 i = 0; i < coopnetDesc->modCategoryCount; i++) {
        struct CoopnetModCategory *category = &coopnetDesc->modCategories[i];

        // write category header
        write_to_desc(dest, destMaxLength, "%s (%u):\n", djui_language_get("HOST_MOD_CATEGORIES", category->name), category->modCount);

        // write all mods inside category
        for (u16 j = 0; j < category->modCount; j++) {
            struct CoopnetMod *mod = &category->mod[j];

            write_to_desc(dest, destMaxLength, "%s\\#dcdcdc\\", mod->name);

            // write extra newline if we need to
            if (i < coopnetDesc->modCategoryCount) {
                write_to_desc(dest, destMaxLength, "\n");
            }
        }

        // write extra newline if needed
        if (i < coopnetDesc->modCategoryCount) {
            write_to_desc(dest, destMaxLength, "\n");
        }
    }
}

void ns_coopnet_free_coopnet_description(struct CoopnetDescription *coopnetDesc) {
    if (coopnetDesc == NULL) { return; }

    // free all mods allocated first
    if (coopnetDesc->modCategories != NULL) {
        for (u16 i = 0; i < coopnetDesc->modCategoryCount; i++) {
            struct CoopnetModCategory *category = &coopnetDesc->modCategories[i];
            free(category->mod);
        }
        free(coopnetDesc->modCategories);
    }

    // zero out struct
    memset(coopnetDesc, 0, sizeof(struct CoopnetDescription));
}

static int ns_coopnet_network_send(u8 localIndex, void* address, u8* data, u16 dataLength) {
    if (!coopnet_is_connected()) { return 1; }
    //if (gCurLobbyId == 0) { return 2; }
    u64 userId = coopnet_raw_get_id(localIndex);
    if (localIndex == 0 && address != NULL) { userId = *(u64*)address; }
    coopnet_send_to(userId, data, dataLength);

    return 0;
}

static bool coopnet_allow_invite(void) {
    if (sLocalLobbyId == 0) { return false; }
    return (sLocalLobbyOwnerId == coopnet_get_local_user_id()) || (strlen(gCoopNetPassword) == 0);
}

static void ns_coopnet_get_lobby_id(UNUSED char* destination, UNUSED u32 destLength) {
    if (sLocalLobbyId == 0) {
        snprintf(destination, destLength, "%s", "");
    } else {
        snprintf(destination, destLength, "coopnet:%" PRIu64 "", sLocalLobbyId);
    }
}

static void ns_coopnet_get_lobby_secret(UNUSED char* destination, UNUSED u32 destLength) {
    if (sLocalLobbyId == 0 || !coopnet_allow_invite()) {
        snprintf(destination, destLength, "%s", "");
    } else {
        snprintf(destination, destLength, "coopnet:%" PRIu64":%s", sLocalLobbyId, gCoopNetPassword);
    }
}

static void ns_coopnet_shutdown(bool reconnecting) {
    if (reconnecting) { return; }
    LOG_INFO("ns_coopnet_shutdown: Coopnet shutdown!");
    coopnet_shutdown();
    gCoopNetCallbacks.OnLobbyListGot = NULL;
    gCoopNetCallbacks.OnLobbyListFinish = NULL;

    gCoopNetCallbacks.OnConnected = NULL;
    gCoopNetCallbacks.OnDisconnected = NULL;
    gCoopNetCallbacks.OnReceive = NULL;
    gCoopNetCallbacks.OnLobbyJoined = NULL;
    gCoopNetCallbacks.OnLobbyLeft = NULL;
    gCoopNetCallbacks.OnError = NULL;
    gCoopNetCallbacks.OnPeerDisconnected = NULL;
    gCoopNetCallbacks.OnLoadBalance = NULL;

    sLocalLobbyId = 0;
    sLocalLobbyOwnerId = 0;
}

static CoopNetRc coopnet_initialize(void) {
    gCoopNetCallbacks.OnConnected = coopnet_on_connected;
    gCoopNetCallbacks.OnDisconnected = coopnet_on_disconnected;
    gCoopNetCallbacks.OnReceive = coopnet_on_receive;
    gCoopNetCallbacks.OnLobbyJoined = coopnet_on_lobby_joined;
    gCoopNetCallbacks.OnLobbyLeft = coopnet_on_lobby_left;
    gCoopNetCallbacks.OnError = coopnet_on_error;
    gCoopNetCallbacks.OnPeerDisconnected = coopnet_on_peer_disconnected;
    gCoopNetCallbacks.OnLoadBalance = coopnet_on_load_balance;

    if (coopnet_is_connected()) { return COOPNET_OK; }

    char* endptr = NULL;
    uint64_t destId = strtoull(configDestId, &endptr, 10);

    CoopNetRc rc = coopnet_begin(configCoopNetIp, configCoopNetPort, configPlayerName, destId);
    if (rc == COOPNET_FAILED) {
        djui_popup_create(DLANG(NOTIF, COOPNET_CONNECTION_FAILED), 2);
    }
    return rc;
}

struct NetworkSystem gNetworkSystemCoopNet = {
    .initialize       = ns_coopnet_initialize,
    .get_id           = ns_coopnet_get_id,
    .get_id_str       = ns_coopnet_get_id_str,
    .save_id          = ns_coopnet_save_id,
    .clear_id         = ns_coopnet_clear_id,
    .dup_addr         = ns_coopnet_dup_addr,
    .match_addr       = ns_coopnet_match_addr,
    .update           = ns_coopnet_update,
    .send             = ns_coopnet_network_send,
    .get_lobby_id     = ns_coopnet_get_lobby_id,
    .get_lobby_secret = ns_coopnet_get_lobby_secret,
    .shutdown         = ns_coopnet_shutdown,
    .requireServerBroadcast = false,
    .name             = "CoopNet",
};

#endif
