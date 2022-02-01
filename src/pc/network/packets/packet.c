#include <stdio.h>
#include "../network.h"
#include "pc/debuglog.h"

void packet_process(struct Packet* p) {
    if (p->levelAreaMustMatch) {
        extern s16 gCurrCourseNum, gCurrActStarNum, gCurrLevelNum, gCurrAreaIndex;
        bool levelAreaMismatch =
            (p->courseNum    != gCurrCourseNum
             || p->actNum    != gCurrActStarNum
             || p->levelNum  != gCurrLevelNum
             || p->areaIndex != gCurrAreaIndex);
        // drop packet
        if (levelAreaMismatch) {
            if (gNetworkType != NT_SERVER) {
                LOG_INFO("dropping level mismatch packet %d", p->packetType);
                LOG_INFO("    (%d, %d, %d, %d) != (%d, %d, %d, %d)", p->courseNum, p->actNum, p->levelNum, p->areaIndex, gCurrCourseNum, gCurrActStarNum, gCurrLevelNum, gCurrAreaIndex);
            }
            return;
        }
    } else if (p->levelMustMatch) {
        extern s16 gCurrCourseNum, gCurrActStarNum, gCurrLevelNum;
        bool levelMismatch =
            (p->courseNum != gCurrCourseNum
                || p->actNum != gCurrActStarNum
                || p->levelNum != gCurrLevelNum);
        // drop packet
        if (levelMismatch) {
            if (gNetworkType != NT_SERVER) {
                LOG_INFO("dropping level mismatch packet %d", p->packetType);
                LOG_INFO("    (%d, %d, %d) != (%d, %d, %d)", p->courseNum, p->actNum, p->levelNum, gCurrCourseNum, gCurrActStarNum, gCurrLevelNum);
            }
            return;
        }
    }

    switch (p->packetType) {
        case PACKET_ACK:                     network_receive_ack(p);                     break;
        case PACKET_PLAYER:                  network_receive_player(p);                  break;
        case PACKET_OBJECT:                  network_receive_object(p);                  break;
        case PACKET_SPAWN_OBJECTS:           network_receive_spawn_objects(p);           break;
        case PACKET_SPAWN_STAR:              network_receive_spawn_star(p);              break;
        case PACKET_SPAWN_STAR_NLE:          network_receive_spawn_star_nle(p);          break;
        case PACKET_COLLECT_STAR:            network_receive_collect_star(p);            break;
        case PACKET_COLLECT_COIN:            network_receive_collect_coin(p);            break;
        case PACKET_COLLECT_ITEM:            network_receive_collect_item(p);            break;
        case PACKET_UNUSED1:                                                             break;
        case PACKET_DEBUG_SYNC:              network_receive_debug_sync(p);              break;
        case PACKET_JOIN_REQUEST:            network_receive_join_request(p);            break;
        case PACKET_JOIN:                    network_receive_join(p);                    break;
        case PACKET_CHAT:                    network_receive_chat(p);                    break;
        case PACKET_KICK:                    network_receive_kick(p);                    break;
        case PACKET_KEEP_ALIVE:              network_receive_keep_alive(p);              break;
        case PACKET_LEAVING:                 network_receive_leaving(p);                 break;
        case PACKET_SAVE_FILE:               network_receive_save_file(p);               break;
        case PACKET_SAVE_SET_FLAG:           network_receive_save_set_flag(p);           break;
        case PACKET_NETWORK_PLAYERS:         network_receive_network_players(p);         break;
        case PACKET_DEATH:                   network_receive_death(p);                   break;

        // reservation area
        case PACKET_RESERVATION_LIST:        network_receive_reservation_list(p);        break;
        case PACKET_RESERVATION_USE:         network_receive_reservation_use(p);         break;
        case PACKET_RESERVATION_RELEASE:     network_receive_reservation_release(p);     break;

        // location
        case PACKET_CHANGE_LEVEL:            network_receive_change_level(p);            break;
        case PACKET_CHANGE_AREA:             network_receive_change_area(p);             break;
        case PACKET_LEVEL_AREA_REQUEST:      network_receive_level_area_request(p);      break;
        case PACKET_LEVEL_REQUEST:           network_receive_level_request(p);           break;
        case PACKET_LEVEL:                   network_receive_level(p);                   break;
        case PACKET_AREA_REQUEST:            network_receive_area_request(p);            break;
        case PACKET_AREA:                    network_receive_area(p);                    break;
        case PACKET_SYNC_VALID:              network_receive_sync_valid(p);              break;
        case PACKET_LEVEL_SPAWN_INFO:        network_receive_level_spawn_info(p);        break;
        case PACKET_LEVEL_MACRO:             network_receive_level_macro(p);             break;
        case PACKET_LEVEL_AREA_INFORM:       network_receive_level_area_inform(p);       break;
        case PACKET_LEVEL_RESPAWN_INFO:      network_receive_level_respawn_info(p);      break;

        case PACKET_PLAYER_SETTINGS:         network_receive_player_settings(p);         break;

        case PACKET_MOD_LIST_REQUEST:        network_receive_mod_list_request(p);        break;
        case PACKET_MOD_LIST:                network_receive_mod_list(p);                break;
        case PACKET_DOWNLOAD_REQUEST:        network_receive_download_request(p);        break;
        case PACKET_DOWNLOAD:                network_receive_download(p);                break;

        case PACKET_LUA_SYNC_TABLE_REQUEST:  network_receive_lua_sync_table_request(p);  break;
        case PACKET_LUA_SYNC_TABLE:          network_receive_lua_sync_table(p);          break;

        case PACKET_NETWORK_PLAYERS_REQUEST: network_receive_network_players_request(p); break;

        // custom
        case PACKET_CUSTOM:                  network_receive_custom(p);                  break;
        default: LOG_ERROR("received unknown packet: %d", p->buffer[0]);
    }
}

void packet_receive(struct Packet* p) {
    u8 packetType = (u8)p->buffer[0];

    // send an ACK if requested
    network_send_ack(p);

    // refuse packets from unknown servers
    if (gNetworkServerAddr != NULL && gNetworkType == NT_CLIENT) {
        bool fromServer = (p->localIndex == UNKNOWN_LOCAL_INDEX);
        if (gNetworkPlayerServer != NULL) { fromServer = fromServer || p->localIndex == gNetworkPlayerServer->localIndex; }
        if (fromServer && !gNetworkSystem->match_addr(gNetworkServerAddr, p->addr)) {
            LOG_INFO("refusing packet from unknown server");
            return;
        }
    }

    // refuse packets from unknown players other than join request
    if (gNetworkType == NT_SERVER && p->localIndex == UNKNOWN_LOCAL_INDEX && !network_allow_unknown_local_index(packetType)) {
        if (packetType != PACKET_PLAYER) {
            LOG_INFO("closing connection for packetType: %d", packetType);
            network_send_kick(EKT_CLOSE_CONNECTION);
        }
        LOG_INFO("refusing packet from unknown player, packetType: %d", packetType);
        return;
    }

    // check if we've already seen this packet
    if (p->localIndex != 0 && p->seqId != 0 && gNetworkPlayers[p->localIndex].connected) {
        u32 packetHash = packet_hash(p);
        struct NetworkPlayer* np = &gNetworkPlayers[p->localIndex];
        for (int i = 0; i < MAX_RX_SEQ_IDS; i++) {
            if (np->rxSeqIds[i] == p->seqId && np->rxPacketHash[i] == packetHash) {
                LOG_INFO("received duplicate packet");
                return;
            }
        }
        // remember seq id
        np->rxSeqIds[np->onRxSeqId] = p->seqId;
        np->rxPacketHash[np->onRxSeqId] = packetHash;
        np->onRxSeqId++;
        if (np->onRxSeqId >= MAX_RX_SEQ_IDS) { np->onRxSeqId = 0; }
    }

    // parse the packet without processing the rest
    if (packet_initial_read(p)) {
        if (gNetworkType == NT_SERVER && p->destGlobalId != PACKET_DESTINATION_BROADCAST && p->destGlobalId != 0 && packetType != PACKET_ACK) {
            // this packet is meant for someone else
            struct Packet p2 = { 0 };
            packet_duplicate(p, &p2);
            network_send_to(p->destGlobalId, &p2);
        } else if (p->orderedGroupId != 0) {
            // add the packet to the ordered bucket (may process immediately if it's in order)
            packet_ordered_add(p);
        } else {
            // process the packet
            packet_process(p);
        }
    } else {
        LOG_INFO("packet initial read failed, packetType: %d", packetType);
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
