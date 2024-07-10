#ifndef COOPNET_H
#define COOPNET_H
#ifdef COOPNET

#define MAX_COOPNET_DESCRIPTION_LENGTH 1024

typedef void (*QueryCallbackPtr)(uint64_t aLobbyId, uint64_t aOwnerId, uint16_t aConnections, uint16_t aMaxConnections, const char* aGame, const char* aVersion, const char* aHostName, const char* aMode, const char* aDescription);
typedef void (*QueryFinishCallbackPtr)(void);

extern struct NetworkSystem gNetworkSystemCoopNet;
extern uint64_t gCoopNetDesiredLobby;
extern char gCoopNetPassword[];

bool ns_coopnet_query(QueryCallbackPtr callback, QueryFinishCallbackPtr finishCallback, const char* password);
bool ns_coopnet_is_connected(void);
void ns_coopnet_update(void);

#endif
#endif