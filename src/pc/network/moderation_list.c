#include <stdlib.h>
#include <string.h>
#include <PR/ultratypes.h>
#include "moderation.h"
#include "pc/debuglog.h"
#include "pc/ini.h"

struct ModerationLists gModerationLists = {
    .banList = {
        .actions = {
            [MODERATION_ACTION_UNBAN] = true
        }
    },
    .moderatorList = {
        .actions = {
            [MODERATION_ACTION_UNMOD] = true
        }
    }
};

static const char* safe_ini_get(ini_t* ini, const char* section, const char* key) {
    const char* str = ini_get(ini, section, key);
    return str ? str : "";
}

struct ModerationList* moderation_list_get_list_by_type(enum ModerationListType type) {
    if (type == MODERATION_LIST_TYPE_BAN) return &gModerationLists.banList;
    if (type == MODERATION_LIST_TYPE_MODERATOR) return &gModerationLists.moderatorList;
    LOG_ERROR("Type %u is not a valid type", type);
    return NULL;
}

void moderation_list_save() {
    FILE* file = fopen(fs_get_write_path(MODERATION_LIST_FILEPATH), "w");
    if (!file) return;

    for (u8 type = 0; type < MODERATION_LIST_TYPE_COUNT; type++) {
        struct ModerationList* list = moderation_list_get_list_by_type(type);
        if (!list) continue;

        fprintf(file, "[Type %u]\n", type);
        fprintf(file, "count = %u\n\n", list->count);

        for (u16 i = 0; i < list->count; i++) {
            struct ModerationEntry* entry = list->list[i];
            if (!entry) continue;
            fprintf(file, "[Entry %u for %u]\n", i, type);
            // windows <3
            fprintf(file, "time = %lld\n", (long long)entry->time);
            fprintf(file, "playerName = %s\n", entry->playerName);
            fprintf(file, "playerColorR = %d\n", entry->playerColor[0]);
            fprintf(file, "playerColorG = %d\n", entry->playerColor[1]);
            fprintf(file, "playerColorB = %d\n", entry->playerColor[2]);
            fprintf(file, "address = %s\n", entry->address);
            fprintf(file, "discordId = %s\n", entry->discordId);
            fprintf(file, "reason = %s\n", entry->reason);
            fprintf(file, "permanent = %d\n\n", entry->permanent ? 1 : 0);
        }
    }
    fclose(file);
}

void moderation_list_load() {
    ini_t* iniFile = ini_load(fs_get_write_path(MODERATION_LIST_FILEPATH));
    if (!iniFile) return;

    for (u8 type = 0; type < MODERATION_LIST_TYPE_COUNT; type++) {
        struct ModerationList* list = moderation_list_get_list_by_type(type);
        if (!list) continue;

        char typeSection[16];
        snprintf(typeSection, 16, "Type %u", type);
        u16 totalInIni = strtol(safe_ini_get(iniFile, typeSection, "count"), NULL, 0);

        for (u16 i = 0; i < totalInIni && list->count < MAX_MODERATION_LIST_ENTRIES; i++) {
            char entrySection[32];
            snprintf(entrySection, 32, "Entry %u for %u", i, type);

            struct ModerationEntry* entry = malloc(sizeof(struct ModerationEntry));
            if (!entry) continue;

            entry->permanent = (strtol(safe_ini_get(iniFile, entrySection, "permanent"), NULL, 0) != 0);

            if (!entry->permanent) {
                free(entry);
                continue;
            }

            entry->time = strtol(safe_ini_get(iniFile, entrySection, "time"), NULL, 0);
            entry->playerName = strdup(safe_ini_get(iniFile, entrySection, "playerName"));
            entry->playerColor[0] = strtol(safe_ini_get(iniFile, entrySection, "playerColorR"), NULL, 0);
            entry->playerColor[1] = strtol(safe_ini_get(iniFile, entrySection, "playerColorG"), NULL, 0);
            entry->playerColor[2] = strtol(safe_ini_get(iniFile, entrySection, "playerColorB"), NULL, 0);
            entry->address = strdup(safe_ini_get(iniFile, entrySection, "address"));
            entry->discordId = strdup(safe_ini_get(iniFile, entrySection, "discordId"));
            snprintf(entry->reason, MAX_REASON_LENGTH, "%s", safe_ini_get(iniFile, entrySection, "reason"));

            list->list[list->count++] = entry;
        }
    }
    ini_free(iniFile);
    // wipe non-permanent players from list
    moderation_list_save();
}

void moderation_list_add(enum ModerationListType type, u8 localIndex, char* reason, bool permanent) {
    struct ModerationList* list = moderation_list_get_list_by_type(type);
    if (!list || list->count >= MAX_MODERATION_LIST_ENTRIES) return;

    struct NetworkPlayer* np = &gNetworkPlayers[localIndex];
    struct ModerationEntry* entry = malloc(sizeof(struct ModerationEntry));
    if (!entry) return;

    entry->playerName = strdup(np->name);
    memcpy(entry->playerColor, network_get_player_text_color(np->localIndex), 3);
    entry->address = strdup(gNetworkSystem->get_id_str(localIndex));
    entry->discordId = strdup(network_discord_id_from_local_index(localIndex));
    snprintf(entry->reason, MAX_REASON_LENGTH, "%s", reason ? reason : "");
    entry->permanent = permanent;
    time(&entry->time);

    list->list[list->count++] = entry;
    moderation_list_save();
}

void moderation_list_remove(enum ModerationListType type, char* address) {
    struct ModerationList* list = moderation_list_get_list_by_type(type);
    if (!list || !address) return;

    for (u16 i = 0; i < list->count; i++) {
        if (list->list[i] && strcmp(list->list[i]->address, address) == 0) {
            free(list->list[i]->playerName);
            free(list->list[i]->address);
            free(list->list[i]->discordId);
            free(list->list[i]);

            for (u16 j = i; j < list->count - 1; j++) {
                list->list[j] = list->list[j + 1];
            }

            list->count--;
            list->list[list->count] = NULL;

            moderation_list_save();
            return;
        }
    }
    LOG_ERROR("Address %s not found in list %u", address, type);
}

bool moderation_list_contains(enum ModerationListType type, char* address) {
    struct ModerationList* list = moderation_list_get_list_by_type(type);
    if (!list || !address) return false;

    for (u16 i = 0; i < list->count; i++) {
        if (list->list[i] && strcmp(list->list[i]->address, address) == 0) {
            return true;
        }
    }
    return false;
}