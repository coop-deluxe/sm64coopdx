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

    // send an ACK if requested
    network_send_ack(p);

    // check if we've already seen this packet
    if (p->localIndex != 0 && p->seqId != 0 && gNetworkPlayers[p->localIndex].connected) {
        struct NetworkPlayer* np = &gNetworkPlayers[p->localIndex];
        for (int i = 0; i < MAX_RX_SEQ_IDS; i++) {
            if (np->rxSeqIds[i] == p->seqId) {
                LOG_INFO("received duplicate packet");
                return;
            }
        }
        // remember seq id
        np->rxSeqIds[np->onRxSeqId] = p->seqId;
        np->onRxSeqId++;
        if (np->onRxSeqId >= MAX_RX_SEQ_IDS) { np->onRxSeqId = 0; }
    }

    // check if we should process the packet
    if (packet_initial_read(p)) {
        if (gNetworkType == NT_SERVER && p->destGlobalId != PACKET_DESTINATION_BROADCAST && p->destGlobalId != 0 && packetType != PACKET_ACK) {
            // this packet is meant for someone else
            struct Packet p2 = { 0 };
            packet_duplicate(p, &p2);
            network_send_to(p->destGlobalId, &p2);
        } else {
            // process the packet
            switch (packetType) {
                case PACKET_ACK:                     network_receive_ack(p);                     break;
                case PACKET_PLAYER:                  network_receive_player(p);                  break;
                case PACKET_OBJECT:                  network_receive_object(p);                  break;
                case PACKET_SPAWN_OBJECTS:           network_receive_spawn_objects(p);           break;
                case PACKET_SPAWN_STAR:              network_receive_spawn_star(p);              break;
                case PACKET_SPAWN_STAR_NLE:          network_receive_spawn_star_nle(p);          break;
                case PACKET_COLLECT_STAR:            network_receive_collect_star(p);            break;
                case PACKET_COLLECT_COIN:            network_receive_collect_coin(p);            break;
                case PACKET_COLLECT_ITEM:            network_receive_collect_item(p);            break;
                case PACKET_RESERVATION_REQUEST:     network_receive_reservation_request(p);     break;
                case PACKET_RESERVATION:             network_receive_reservation(p);             break;
                case PACKET_JOIN_REQUEST:            network_receive_join_request(p);            break;
                case PACKET_JOIN:                    network_receive_join(p);                    break;
                case PACKET_CHAT:                    network_receive_chat(p);                    break;
                case PACKET_KICK:                    network_receive_kick(p);                    break;
                case PACKET_KEEP_ALIVE:              network_receive_keep_alive(p);              break;
                case PACKET_LEAVING:                 network_receive_leaving(p);                 break;
                case PACKET_SAVE_FILE:               network_receive_save_file(p);               break;
                case PACKET_NETWORK_PLAYERS:         network_receive_network_players(p);         break;
                case PACKET_DEATH:                   network_receive_death(p);                   break;
                case PACKET_LEVEL_AREA:              network_receive_level_area(p);              break;
                case PACKET_LEVEL_AREA_VALID:        network_receive_level_area_valid(p);        break;
                case PACKET_LOCATION_REQUEST:        network_receive_location_request(p);        break;
                case PACKET_CLIENT_LOCATION_REQUEST: network_receive_client_location_request(p); break;
                case PACKET_LOCATION_RESPONSE:       network_receive_location_response(p);       break;
                    ///
                case PACKET_CUSTOM:                  network_receive_custom(p);                  break;
                default: LOG_ERROR("received unknown packet: %d", p->buffer[0]);
            }
        }
    }

    // broadcast packet
    if (p->requestBroadcast) {
        if (gNetworkType == NT_SERVER && gNetworkSystem->requireServerBroadcast) {
            for (int i = 1; i < MAX_PLAYERS; i++) {
                if (!gNetworkPlayers[i].connected) { continue; }
                if (i == p->localIndex) { continue; }
                struct Packet p2 = { 0 };
                packet_duplicate(p, &p2);
                network_send_to(i, &p2);
            }
        }
    }
}
