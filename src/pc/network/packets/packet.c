#include <stdio.h>
#include "../network.h"
#include "pc/debuglog.h"

void packet_receive(struct Packet* p) {
    u8 packetType = (u8)p->buffer[0];

    // refuse packets from unknown players other than join request
    if (gNetworkType == NT_SERVER && p->localIndex == UNKNOWN_LOCAL_INDEX && packetType != PACKET_JOIN_REQUEST) {
        network_send_kick(EKT_CLOSE_CONNECTION);
        return;
    }

    switch (packetType) {
        case PACKET_ACK:                 network_receive_ack(p);                 break;
        case PACKET_PLAYER:              network_receive_player(p);              break;
        case PACKET_OBJECT:              network_receive_object(p);              break;
        case PACKET_SPAWN_OBJECTS:       network_receive_spawn_objects(p);       break;
        case PACKET_SPAWN_STAR:          network_receive_spawn_star(p);          break;
        case PACKET_LEVEL_WARP:          network_receive_level_warp(p);          break;
        case PACKET_INSIDE_PAINTING:     network_receive_inside_painting(p);     break;
        case PACKET_COLLECT_STAR:        network_receive_collect_star(p);        break;
        case PACKET_COLLECT_COIN:        network_receive_collect_coin(p);        break;
        case PACKET_COLLECT_ITEM:        network_receive_collect_item(p);        break;
        case PACKET_RESERVATION_REQUEST: network_receive_reservation_request(p); break;
        case PACKET_RESERVATION:         network_receive_reservation(p);         break;
        case PACKET_JOIN_REQUEST:        network_receive_join_request(p);        break;
        case PACKET_JOIN:                network_receive_join(p);                break;
        case PACKET_CHAT:                network_receive_chat(p);                break;
        case PACKET_KICK:                network_receive_kick(p);                break;
        case PACKET_KEEP_ALIVE:          network_receive_keep_alive(p);          break;
        case PACKET_LEAVING:             network_receive_leaving(p);             break;
        case PACKET_SAVE_FILE:           network_receive_save_file(p);           break;
        ///
        case PACKET_CUSTOM:              network_receive_custom(p);              break;
        default: LOG_ERROR("received unknown packet: %d", p->buffer[0]);
    }

    // send an ACK if requested
    network_send_ack(p);
}