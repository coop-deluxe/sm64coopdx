#ifndef LIBCOOPNET_H
#define LIBCOOPNET_H

#if defined(__cplusplus) 
#include <cstdint>
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    COOPNET_OK,
    COOPNET_FAILED,
    COOPNET_DISCONNECTED,
} CoopNetRc;

enum MPacketErrorNumber {
    MERR_NONE,
    MERR_LOBBY_NOT_FOUND,
    MERR_LOBBY_JOIN_FULL,
    MERR_LOBBY_JOIN_FAILED,
    MERR_LOBBY_PASSWORD_INCORRECT,
    MERR_COOPNET_VERSION,
    MERR_PEER_FAILED,
    MERR_MAX,
};

typedef struct {
    void (*OnConnected)(uint64_t aUserId);
    void (*OnDisconnected)(bool aIntentional);
    void (*OnLobbyCreated)(uint64_t aLobbyId, const char* aGame, const char* aVersion, const char* aHostName, const char* aMode, uint16_t aMaxConnections);
    void (*OnLobbyJoined)(uint64_t aLobbyId, uint64_t aUserId, uint64_t aOwnerId, uint64_t aDestId);
    void (*OnLobbyLeft)(uint64_t aLobbyId, uint64_t aUserId);
    void (*OnLobbyListGot)(uint64_t aLobbyId, uint64_t aOwnerId, uint16_t aConnections, uint16_t aMaxConnections, const char* aGame, const char* aVersion, const char* aHostName, const char* aMode, const char* aDescription);
    void (*OnLobbyListFinish)(void);
    void (*OnReceive)(uint64_t aFromUserId, const uint8_t* aData, uint64_t aSize);
    void (*OnError)(enum MPacketErrorNumber aErrorNumber, uint64_t tag);
    void (*OnPeerConnected)(uint64_t aPeerId);
    void (*OnPeerDisconnected)(uint64_t aPeerId);
} CoopNetCallbacks;

typedef struct {
    bool SkipWinsockInit;
} CoopNetSettings;

extern CoopNetCallbacks gCoopNetCallbacks;
extern CoopNetSettings gCoopNetSettings;

bool coopnet_is_connected(void);
CoopNetRc coopnet_begin(const char* aHost, uint32_t aPort);
CoopNetRc coopnet_shutdown(void);
CoopNetRc coopnet_update(void);
CoopNetRc coopnet_lobby_create(const char* aGame, const char* aVersion, const char* aHostName, const char* aMode, uint16_t aMaxConnections, const char* aPassword, const char* aDescription);
CoopNetRc coopnet_lobby_update(uint64_t aLobbyId, const char* aGame, const char* aVersion, const char* aHostName, const char* aMode, const char* aDescription);
CoopNetRc coopnet_lobby_join(uint64_t aLobbyId, const char* aPassword);
CoopNetRc coopnet_lobby_leave(uint64_t aLobbyId);
CoopNetRc coopnet_lobby_list_get(const char* aGame, const char* aPassword);
CoopNetRc coopnet_send(const uint8_t* aData, uint64_t aDataLength);
CoopNetRc coopnet_send_to(uint64_t aPeerId, const uint8_t* aData, uint64_t aDataLength);
CoopNetRc coopnet_unpeer(uint64_t aPeerId);

#if defined(__cplusplus) 
}
#endif
#endif