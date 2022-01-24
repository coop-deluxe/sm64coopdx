#include <stdio.h>
#include "smlua.h"

#pragma pack(1)
struct CObjectAllowListNode {
    u64 pointer;
    struct CObjectAllowListNode* next;
};

static struct CObjectAllowListNode* sAllowList[LOT_MAX] = { 0 };
static u16 sCachedAllowed[LOT_MAX] = { 0 };

void smlua_cobject_allowlist_init(void) {
    smlua_cobject_allowlist_shutdown();
}

void smlua_cobject_allowlist_shutdown(void) {
    for (int i = 0; i < LOT_MAX; i++) {
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

void smlua_cobject_allowlist_add(enum LuaObjectType objectType, u64 pointer) {
    if (pointer == 0) { return; }
    if (objectType == LOT_NONE || objectType >= LOT_MAX) { return; }

    if (sCachedAllowed[objectType] == pointer) { return; }
    sCachedAllowed[objectType] = pointer;
    
    struct CObjectAllowListNode* curNode = sAllowList[objectType];
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
        sAllowList[objectType] = node;
    } else {
        prevNode->next = node;
    }
}

bool smlua_cobject_allowlist_contains(enum LuaObjectType objectType, u64 pointer) {
    if (pointer == 0) { return false; }
    if (objectType == LOT_NONE || objectType >= LOT_MAX) { return false; }
    if (sCachedAllowed[objectType] == pointer) { return true; }

    struct CObjectAllowListNode* node = sAllowList[objectType];
    while (node != NULL) {
        if (pointer == node->pointer) { return true; }
        if (pointer < node->pointer) { return false; }
        node = node->next;
    }
    return false;
}