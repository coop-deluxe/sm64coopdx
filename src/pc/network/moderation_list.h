#pragma once
#include <stdbool.h>
#include <PR/ultratypes.h>
#include "moderation.h"

#define MODERATION_LIST_FILEPATH "moderation_list.ini"
#define MAX_MODERATION_LIST_ENTRIES 1024

enum ModerationListType {
    MODERATION_LIST_TYPE_BAN,
    MODERATION_LIST_TYPE_MODERATOR,
    MODERATION_LIST_TYPE_COUNT
};

struct ModerationEntry {
    time_t time;
    char* playerName;
    u8 playerColor[3];
    char* address;
    char* discordId;
    char* reason;
    bool permanent;
};

struct ModerationList {
    struct ModerationEntry* list[MAX_MODERATION_LIST_ENTRIES];
    u16 count;
    bool actions[MODERATION_ACTION_COUNT];
};

struct ModerationLists {
    struct ModerationList banList;
    struct ModerationList moderatorList;
};

extern struct ModerationLists gModerationLists;

struct ModerationList* moderation_list_get_list_by_type(enum ModerationListType type);
void moderation_list_save();
void moderation_list_load();
void moderation_list_add(enum ModerationListType type, u8 localIndex, char* reason, bool permanent);
void moderation_list_remove(enum ModerationListType type, char* address);
bool moderation_list_contains(enum ModerationListType type, char* address);