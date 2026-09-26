#pragma once

#include "pc/djui/mod_category.h"
#include "pc/mods/mods.h"
#include "pc/utils/misc.h"

#ifdef COOPNET

struct CoopnetMod {
    char name[MOD_NAME_SIZE];
};

struct CoopnetModCategory {
    char name[MOD_CATEGORY_SIZE];
    u16 modCount;
    struct CoopnetMod *mod;
};

struct CoopnetDescription {
    u8 majorVer;
    u8 minorVer;
    size_t modSize;
    u64 timestamp;
    u16 modCategoryCount;
    struct CoopnetModCategory *modCategories;
};

typedef void (*QueryCallbackPtr)(uint64_t aLobbyId, uint64_t aOwnerId, uint16_t aConnections, uint16_t aMaxConnections, const char* aGame, const char* aVersion, const char* aHostName, const char* aMode, const char* aDescription);
typedef void (*QueryFinishCallbackPtr)(void);

extern struct NetworkSystem gNetworkSystemCoopNet;
extern uint64_t gCoopNetDesiredLobby;
extern char gCoopNetPassword[];

bool ns_coopnet_query(QueryCallbackPtr callback, QueryFinishCallbackPtr finishCallback, const char* password);
bool ns_coopnet_get_time(uint64_t *time, float timeout);
bool ns_coopnet_is_connected(void);
void ns_coopnet_update(void);
void ns_coopnet_parse_coopnet_description(const char *descStr, struct CoopnetDescription *coopnetDesc);
void ns_coopnet_get_pretty_desc(char *dest, size_t destMaxLength, struct CoopnetDescription *coopnetDesc);
void ns_coopnet_free_coopnet_description(struct CoopnetDescription *coopnetDesc);

#endif
