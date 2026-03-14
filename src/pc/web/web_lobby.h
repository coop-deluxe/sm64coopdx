#ifndef WEB_LOBBY_H
#define WEB_LOBBY_H
#ifdef TARGET_WEB

#include <stdint.h>
#include <stdbool.h>

typedef void (*WebLobbyQueryCallbackPtr)(uint64_t aLobbyId, uint64_t aOwnerId, uint16_t aConnections, uint16_t aMaxConnections, const char* aGame, const char* aVersion, const char* aHostName, const char* aMode, const char* aDescription);
typedef void (*WebLobbyQueryFinishCallbackPtr)(void);

bool ns_web_lobby_query(WebLobbyQueryCallbackPtr callback, WebLobbyQueryFinishCallbackPtr finishCallback);
void ns_web_lobby_register(const char* roomId, bool unlisted);
void ns_web_lobby_unregister(void);
void ns_web_lobby_update(void);

#endif
#endif
