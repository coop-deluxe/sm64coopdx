#include <stdio.h>
#include "../network.h"
#include "pc/utils/misc.h"
#include "pc/debuglog.h"

// two-player hack: the localIndex for resending packets can be 0... this means reply to last person received from. THIS WILL NOT WORK with more than two players

#define RELIABLE_RESEND_RATE 0.20f
#define MAX_RESEND_ATTEMPTS 10

struct PacketLinkedList {
    struct Packet p;
    f32 lastSend;
    int sendAttempts;
    struct PacketLinkedList* prev;
    struct PacketLinkedList* next;
};

struct PacketLinkedList* head = NULL;
struct PacketLinkedList* tail = NULL;

static void remove_node_from_list(struct PacketLinkedList* node) {
    if (node == head) {
        head = node->next;
        if (head != NULL) { head->prev = NULL; }
    }
    if (node == tail) {
        tail = node->prev;
        if (tail != NULL) { tail->next = NULL; }
    }

    if (node->prev != NULL) { node->prev->next = node->next; }
    if (node->next != NULL) { node->next->prev = node->prev; }

    if (node->p.addr != NULL) { free(node->p.addr); }
    if (node != NULL) { free(node); }
}

void network_forget_all_reliable(void) {
    while (head != NULL) { remove_node_from_list(head); }
}

void network_forget_all_reliable_from(u8 localIndex) {
    if (localIndex == 0) { return; }
    struct PacketLinkedList* node = head;
    while (node != NULL) {
        struct PacketLinkedList* next = node->next;
        if (node->p.localIndex == localIndex) {
            remove_node_from_list(node);
        }
        node = next;
    }
}

void network_send_ack(struct Packet* p) {
    // grab seq num
    u16 seqId = 0;
    memcpy(&seqId, &p->buffer[1], 2);
    p->seqId = seqId;
    p->reliable = (seqId != 0);
    if (seqId == 0) { return; }

    // send back the ACK
    struct Packet ack = { 0 };
    packet_init(&ack, PACKET_ACK, false, PLMT_NONE);
    packet_write(&ack, &seqId, sizeof(u16));
    network_send_to(0, &ack);
}

void network_receive_ack(struct Packet* p) {
    // grab seq num
    u16 seqId = 0;
    packet_read(p, &seqId, sizeof(u16));

    // find in list and remove
    struct PacketLinkedList* node = head;
    while (node != NULL) {
        if (node->p.seqId == seqId) {
            remove_node_from_list(node);
            break;
        }
        node = node->next;
    }
}

void network_remember_reliable(struct Packet* p) {
    if (!p->reliable) { return; }
    if (p->sent) { return; }
    if (p->writeError) { return; }

    struct PacketLinkedList* node = calloc(1, sizeof(struct PacketLinkedList));
    node->p = *p;
    node->p.addr = network_duplicate_address(p->localIndex);
    node->p.sent = true;
    node->lastSend = clock_elapsed();
    node->sendAttempts = 1;
    node->prev = NULL;
    node->next = NULL;

    if (tail == NULL) {
        // start of the list
        if (head != NULL) {
            free(node);
            SOFT_ASSERT(head == NULL);
        }

        head = node;
        tail = node;
        return;
    }

    // add to end of list
    if (tail->next != NULL) {
        free(node);
        SOFT_ASSERT(tail->next == NULL);
    }
    tail->next = node;
    node->prev = tail;
    tail = node;
}

static float network_adjust_max_elapsed(enum PacketType packetType, float maxElapsed) {
    switch (packetType) {
        case PACKET_DOWNLOAD_REQUEST:
        case PACKET_DOWNLOAD:
        case PACKET_MOD_LIST_REQUEST:
        case PACKET_MOD_LIST:
        case PACKET_MOD_LIST_ENTRY:
        case PACKET_MOD_LIST_FILE:
        case PACKET_MOD_LIST_DONE:
            return 0.2f + maxElapsed * 2.0f;
        default:
            return maxElapsed;
    }
}

void network_update_reliable(void) {
    struct PacketLinkedList* node = head;
    while (node != NULL) {
        float elapsed = (clock_elapsed() - node->lastSend);
        float maxElapsed = (node->sendAttempts * node->sendAttempts * RELIABLE_RESEND_RATE) / ((float)MAX_RESEND_ATTEMPTS);
        maxElapsed = network_adjust_max_elapsed(node->p.packetType, maxElapsed);
        if (elapsed > maxElapsed) {
            if (node->p.packetType == PACKET_JOIN_REQUEST && gNetworkPlayerServer != NULL) {
                node->p.localIndex = gNetworkPlayerServer->localIndex;
            }
            // resend
            node->p.sent = true;
            network_send_to(node->p.localIndex, &node->p);

            node->lastSend = clock_elapsed();
            node->sendAttempts++;
            if (node->sendAttempts >= MAX_RESEND_ATTEMPTS) {
                struct PacketLinkedList* next = node->next;
                remove_node_from_list(node);
                node = next;
                LOG_ERROR("giving up on reliable packet");
                continue;
            }
        }
        node = node->next;
    }
}
