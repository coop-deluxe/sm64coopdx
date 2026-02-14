// BungeeCord64 - Fallback Port Packet
// Server sends its fallback port to clients so they know where to reconnect
// if the server crashes unexpectedly.

#include <stdio.h>
#include "../network.h"
#include "pc/debuglog.h"
#include "pc/configfile.h"

// Server-side: configured fallback port (where clients should go if this server dies)
// This can be set via server config or command
static u32 sServerFallbackPort = 0;

void network_set_server_fallback_port(u32 port) {
    sServerFallbackPort = port;
    LOG_INFO("BungeeCord64: Server fallback port set to %u", port);
}

u32 network_get_server_fallback_port(void) {
    return sServerFallbackPort;
}

// Server sends fallback port to a specific client
void network_send_bungee_fallback(u8 toLocalIndex, u32 fallbackPort) {
    if (gNetworkType != NT_SERVER) { return; }

    struct Packet p = { 0 };
    packet_init(&p, PACKET_BUNGEE_FALLBACK, true, PLMT_NONE);
    packet_write(&p, &fallbackPort, sizeof(u32));

    network_send_to(toLocalIndex, &p);
    LOG_INFO("BungeeCord64: Sent fallback port %u to player %d", fallbackPort, toLocalIndex);
}

// Client requests fallback port from server
void network_send_bungee_fallback_request(void) {
    if (gNetworkType != NT_CLIENT) { return; }

    struct Packet p = { 0 };
    packet_init(&p, PACKET_BUNGEE_FALLBACK, true, PLMT_NONE);
    
    // Empty packet = request
    u32 zero = 0;
    packet_write(&p, &zero, sizeof(u32));

    network_send_to(PACKET_DESTINATION_SERVER, &p);
    LOG_INFO("BungeeCord64: Requesting fallback port from server");
}

// Server receives request, Client receives fallback port
void network_receive_bungee_fallback(struct Packet* p) {
    u32 port = 0;
    packet_read(p, &port, sizeof(u32));

    if (gNetworkType == NT_SERVER) {
        // This is a request from a client
        if (sServerFallbackPort != 0) {
            network_send_bungee_fallback(p->localIndex, sServerFallbackPort);
        } else {
            LOG_INFO("BungeeCord64: Client requested fallback port, but none configured on this server");
        }
    } else if (gNetworkType == NT_CLIENT) {
        // This is the server sending us the fallback port
        if (port != 0) {
            network_set_bungee_fallback_port(port);
            LOG_INFO("BungeeCord64: Received fallback port %u from server", port);
        } else {
            LOG_INFO("BungeeCord64: Server has no fallback port configured, keeping previous: %u", 
                     network_get_bungee_fallback_port());
        }
    }
}

// Alias for backwards compatibility
void network_receive_bungee_fallback_request(struct Packet* p) {
    network_receive_bungee_fallback(p);
}
