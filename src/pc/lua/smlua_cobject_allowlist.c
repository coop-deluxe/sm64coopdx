#include <stdio.h>
#include "smlua.h"

struct CAllowListNode {
    u64 pointer;
    struct CAllowListNode* next;
};

#define LOT_COUNT (LOT_MAX + (LOT_AUTOGEN_MAX - LOT_AUTOGEN_MIN))
static struct CAllowListNode* sObjectAllowList[LOT_COUNT] = { 0 };
static u16 sCachedObjectAllowed[LOT_COUNT] = { 0 };

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
    for (s32 i = 0; i < LOT_COUNT; i++) {
        sCachedObjectAllowed[i] = 0;
        struct CAllowListNode* node = sObjectAllowList[i];
        while (node != NULL) {
            struct CAllowListNode* nextNode = node->next;
            free(node);
            node = nextNode;
        }
        sObjectAllowList[i] = NULL;
    }
}

void smlua_cobject_allowlist_add(u16 lot, u64 pointer) {
    if (pointer == 0) { return; }
    if (!smlua_valid_lot(lot)) { return; }

    u16 m = smlua_lot_mapping(lot);
    if (sCachedObjectAllowed[m] == pointer) { return; }
    sCachedObjectAllowed[m] = pointer;

    struct CAllowListNode* curNode = sObjectAllowList[m];
    struct CAllowListNode* prevNode = NULL;
    while (curNode != NULL) {
        if (pointer == curNode->pointer) { return; }
        if (pointer < curNode->pointer) { break; }
        prevNode = curNode;
        curNode = curNode->next;
    }

    struct CAllowListNode* node = malloc(sizeof(struct CAllowListNode));
    node->pointer = pointer;
    node->next = curNode;
    if (prevNode == NULL) {
        sObjectAllowList[m] = node;
    } else {
        prevNode->next = node;
    }
}

bool smlua_cobject_allowlist_contains(u16 lot, u64 pointer) {
    if (pointer == 0) { return false; }
    if (!smlua_valid_lot(lot)) { return false; }

    u16 m = smlua_lot_mapping(lot);
    if (sCachedObjectAllowed[m] == pointer) { return true; }

    struct CAllowListNode* node = sObjectAllowList[m];
    while (node != NULL) {
        if (pointer == node->pointer) { return true; }
        if (pointer < node->pointer) { return false; }
        node = node->next;
    }
    return false;
}

/////////////////////////////

static struct CAllowListNode* sPointerAllowList[LVT_MAX] = { 0 };
static u16 sCachedPointerAllowed[LVT_MAX] = { 0 };

void smlua_cpointer_allowlist_init(void) {
    smlua_cpointer_allowlist_shutdown();
}

void smlua_cpointer_allowlist_shutdown(void) {
    for (s32 i = 0; i < LVT_MAX; i++) {
        sCachedPointerAllowed[i] = 0;
        struct CAllowListNode* node = sPointerAllowList[i];
        while (node != NULL) {
            struct CAllowListNode* nextNode = node->next;
            free(node);
            node = nextNode;
        }
        sPointerAllowList[i] = NULL;
    }
}

void smlua_cpointer_allowlist_add(u16 lvt, u64 pointer) {
    if (pointer == 0) { return; }
    if (!smlua_valid_lvt(lvt)) { return; }

    if (sCachedPointerAllowed[lvt] == pointer) { return; }
    sCachedPointerAllowed[lvt] = pointer;

    struct CAllowListNode* curNode = sPointerAllowList[lvt];
    struct CAllowListNode* prevNode = NULL;
    while (curNode != NULL) {
        if (pointer == curNode->pointer) { return; }
        if (pointer < curNode->pointer) { break; }
        prevNode = curNode;
        curNode = curNode->next;
    }

    struct CAllowListNode* node = malloc(sizeof(struct CAllowListNode));
    node->pointer = pointer;
    node->next = curNode;
    if (prevNode == NULL) {
        sPointerAllowList[lvt] = node;
    } else {
        prevNode->next = node;
    }
}

bool smlua_cpointer_allowlist_contains(u16 lvt, u64 pointer) {
    if (pointer == 0) { return false; }
    if (!smlua_valid_lvt(lvt)) { return false; }

    if (sCachedPointerAllowed[lvt] == pointer) { return true; }

    struct CAllowListNode* node = sPointerAllowList[lvt];
    while (node != NULL) {
        if (pointer == node->pointer) { return true; }
        if (pointer < node->pointer) { return false; }
        node = node->next;
    }
    return false;
}