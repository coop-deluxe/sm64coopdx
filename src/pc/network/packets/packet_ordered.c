#include <stdio.h>
#include "../network.h"
#include "pc/utils/misc.h"
//#define DISABLE_MODULE_LOG 1
#include "pc/debuglog.h"

#define PACKET_ORDERED_TIMEOUT 30

struct OrderedPacketList {
    struct Packet p;
    struct OrderedPacketList* next;
};

struct OrderedPacketTable {
    u8 fromGlobalId;
    u16 groupId;
    u16 processSeqId;
    f32 lastReceived;
    struct OrderedPacketList* packets;
    struct OrderedPacketTable* next;
};

static struct OrderedPacketTable* orderedPacketTable[MAX_PLAYERS] = { 0 };
u8 gAllowOrderedPacketClear = 1;

static void packet_ordered_check_for_processing(struct OrderedPacketTable* opt) {
    if (!opt) { return; }

    struct OrderedPacketList* opl = opt->packets;
    struct OrderedPacketList* oplLast = opl;
    struct Packet* p = NULL;

    while (opl != NULL) {
        if (opt->processSeqId == opl->p.orderedSeqId) {
            // we found the packet we're supposed to process!
            p = &opl->p;
            break;
        }
        oplLast = opl;
        opl = opl->next;
    }

    // make sure we found the packet
    if (p == NULL) { return; }

    // process it
    packet_process(p);
    LOG_INFO("processed ordered packet (%d, %d, %d)", p->orderedFromGlobalId, p->orderedGroupId, p->orderedSeqId);

    // remove from linked list
    if (oplLast == opl) {
        // we processed the head of the list
        opt->packets = opl->next;
    } else if (oplLast) {
        // we processed from after the head
        oplLast->next = opl->next;
    }

    // deallocate
    free(opl);

    // find the next one we have to process.
    opt->processSeqId++;
    packet_ordered_check_for_processing(opt);
}

static void packet_ordered_add_to_table(struct OrderedPacketTable* opt, struct Packet* p) {
    // sanity check
    SOFT_ASSERT(opt != NULL);
    SOFT_ASSERT(opt->fromGlobalId == p->orderedFromGlobalId);
    SOFT_ASSERT(opt->groupId == p->orderedGroupId);

    if (p->orderedSeqId < opt->processSeqId) {
        // this packet has already been processed!
        LOG_INFO("this packet has already been processed!");
        return;
    }

    if (p->orderedSeqId == opt->processSeqId) {
        // this is the packet that the table is waiting on, process it!
        packet_process(p);

        // find the next one we have to process.
        opt->processSeqId++;
        packet_ordered_check_for_processing(opt);
        return;
    }

    struct OrderedPacketList* opl = opt->packets;
    struct OrderedPacketList* oplLast = opl;

    // make sure this packet isn't currently in the list
    while (opl != NULL) {
        if (opl->p.orderedSeqId == p->orderedSeqId) {
            // this packet is already in the list!
            LOG_INFO("this packet is already in the list!");
            return;
        }
        // iterate
        oplLast = opl;
        opl = opl->next;
    }

    // allocate the packet list
    opl = calloc(1, sizeof(struct OrderedPacketList));
    if (oplLast == NULL) {
        opt->packets = opl;
    } else {
        oplLast->next = opl;
    }

    // copy the packet over to the list
    memcpy(&opl->p, p, sizeof(struct Packet));
    opl->next = NULL;

    LOG_INFO("added to list for (%d, %d, %d)", opt->fromGlobalId, opt->groupId, p->orderedSeqId);
    opt->lastReceived = clock_elapsed();

    packet_ordered_check_for_processing(opt);
}

void packet_ordered_add(struct Packet* p) {
    u8 globalId = p->orderedFromGlobalId;
    if (globalId > MAX_PLAYERS) { return; }
    struct OrderedPacketTable* opt = orderedPacketTable[globalId];

    // try to find a ordered packet table for the packet's group
    struct OrderedPacketTable* optLast = opt;
    while (opt != NULL) {
        if (opt->groupId == p->orderedGroupId) {
            // found a matching group
            packet_ordered_add_to_table(opt, p);
            return;
        }
        // iterate
        optLast = opt;
        opt = opt->next;
    }

    // could not find a matching group, allocate a ordered packet table
    opt = malloc(sizeof(struct OrderedPacketTable));

    // put the opt in the right place
    if (optLast == NULL) {
        orderedPacketTable[globalId] = opt;
    } else {
        optLast->next = opt;
    }

    // set opt params
    opt->fromGlobalId = p->orderedFromGlobalId;
    opt->groupId      = p->orderedGroupId;
    opt->processSeqId = 1;
    opt->packets      = NULL;
    opt->next         = NULL;
    opt->lastReceived = clock_elapsed();
    LOG_INFO("created table for (%d, %d)", opt->fromGlobalId, opt->groupId);

    // add the packet to the table
    packet_ordered_add_to_table(opt, p);
}

void packet_ordered_clear_table(u8 globalIndex, u16 groupId) {
    LOG_INFO("clearing out ordered packet table for %d (%d)", globalIndex, groupId);
    if (globalIndex > MAX_PLAYERS) { return; }

    struct OrderedPacketTable* opt = orderedPacketTable[globalIndex];
    struct OrderedPacketTable* optLast = opt;

    while (opt != NULL) {
        if (opt->groupId == groupId) {
            // clear opl of table
            struct OrderedPacketList* opl = opt->packets;
            while (opl != NULL) {
                struct OrderedPacketList* oplNext = opl->next;
                free(opl);
                opl = oplNext;
                LOG_INFO("cleared out opl");
            }

            // remove from linked list
            if (optLast == opt) {
                orderedPacketTable[globalIndex] = opt->next;
            } else {
                optLast->next = opt->next;
            }

            // deallocate table
            free(opt);
            LOG_INFO("cleared out opt");
            return;
        }

        // goto the next table
        optLast = opt;
        opt = opt->next;
    }
}

void packet_ordered_clear(u8 globalIndex) {
    if (globalIndex > MAX_PLAYERS) { return; }
    if (!gAllowOrderedPacketClear) {
        LOG_INFO("disallowed ordered packets to be cleared");
        return;
    }

    LOG_INFO("clearing out all ordered packet tables for %d", globalIndex);
    struct OrderedPacketTable* opt = orderedPacketTable[globalIndex];

    while (opt != NULL) {
        // clear opl of table
        struct OrderedPacketList* opl = opt->packets;
        while (opl != NULL) {
            struct OrderedPacketList* oplNext = opl->next;
            free(opl);
            opl = oplNext;
            LOG_INFO("cleared out opl");
        }

        // goto next table and free the current one
        struct OrderedPacketTable* optNext = opt->next;
        free(opt);
        opt = optNext;
        LOG_INFO("cleared out opt");
    }

    orderedPacketTable[globalIndex] = NULL;
}


void packet_ordered_clear_all(void) {
    gAllowOrderedPacketClear = 1;
    for (int i = 0; i < MAX_PLAYERS; i++) {
        packet_ordered_clear(i);
    }
}

void packet_ordered_update(void) {
    f32 currentClock = clock_elapsed();
    // check all ordered tables for a time out
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        struct OrderedPacketTable* opt = orderedPacketTable[i];
        while (opt != NULL) {
            struct OrderedPacketTable* optNext = opt->next;
            float elapsed = (currentClock - opt->lastReceived);

            if (elapsed > PACKET_ORDERED_TIMEOUT) {
                // too much time has elapsed since we last received a packet for this group, forget the table!
                packet_ordered_clear_table(i, opt->groupId);
            }

            opt = optNext;
        }
    }
}
