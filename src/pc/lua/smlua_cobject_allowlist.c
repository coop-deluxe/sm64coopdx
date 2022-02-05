#include <stdio.h>
#include "smlua.h"

struct CObjectAllowListNode {
    u64 pointer;
    struct CObjectAllowListNode* next;
};

#define LOT_COUNT (LOT_MAX + (LOT_AUTOGEN_MAX - LOT_AUTOGEN_MIN))
static struct CObjectAllowListNode* sAllowList[LOT_COUNT] = { 0 };
static u16 sCachedAllowed[LOT_COUNT] = { 0 };

static u16 smlua_lot_mapping(u16 lot) {
    if (lot >= LOT_MAX) {
        return LOT_MAX + (lot - LOT_AUTOGEN_MIN);
    } else {
        return lot;
    }
}

void smlua_cobject_allowlist_init(void) {
    smlua_cobject_allowlist_shutdown();
}

void smlua_cobject_allowlist_shutdown(void) {
    for (int i = 0; i < LOT_COUNT; i++) {
        sCachedAllowed[i] = 0;
        struct CObjectAllowListNode* node = sAllowList[i];
        while (node != NULL) {
            struct CObjectAllowListNode* nextNode = node->next;
            free(node);
            node = nextNode;
        }
        sAllowList[i] = NULL;
    }
}

void smlua_cobject_allowlist_add(u16 lot, u64 pointer) {
    if (pointer == 0) { return; }
    if (!smlua_valid_lot(lot)) { return; }

    u16 m = smlua_lot_mapping(lot);
    if (sCachedAllowed[m] == pointer) { return; }
    sCachedAllowed[m] = pointer;
    
    struct CObjectAllowListNode* curNode = sAllowList[m];
    struct CObjectAllowListNode* prevNode = NULL;
    while (curNode != NULL) {
        if (pointer == curNode->pointer) { return; }
        if (pointer < curNode->pointer) { break; }
        prevNode = curNode;
        curNode = curNode->next;
    }

    struct CObjectAllowListNode* node = malloc(sizeof(struct CObjectAllowListNode));
    node->pointer = pointer;
    node->next = curNode;
    if (prevNode == NULL) {
        sAllowList[m] = node;
    } else {
        prevNode->next = node;
    }
}

bool smlua_cobject_allowlist_contains(u16 lot, u64 pointer) {
    if (pointer == 0) { return false; }
    if (!smlua_valid_lot(lot)) { return false; }

    u16 m = smlua_lot_mapping(lot);
    if (sCachedAllowed[m] == pointer) { return true; }

    struct CObjectAllowListNode* node = sAllowList[m];
    while (node != NULL) {
        if (pointer == node->pointer) { return true; }
        if (pointer < node->pointer) { return false; }
        node = node->next;
    }
    return false;
}