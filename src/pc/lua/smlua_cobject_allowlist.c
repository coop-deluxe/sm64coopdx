#include <stdio.h>
#include "smlua.h"
#define STB_DS_IMPLEMENTATION 1
#include "pc/utils/stb_ds.h"

struct AllowList {
    u64 key;
    u8 value;
};

#define LOT_COUNT (LOT_MAX + (LOT_AUTOGEN_MAX - LOT_AUTOGEN_MIN))
static struct AllowList* sObjectAllowList[LOT_COUNT] = { 0 };
static u64 sCachedObjectAllowed[LOT_COUNT] = { 0 };

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

        while (sObjectAllowList[i] && hmlen(sObjectAllowList[i]) > 0) {
            hmdel(sObjectAllowList[i], sObjectAllowList[i]->key);
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

    if (!hmget(sObjectAllowList[m], pointer)) {
        hmput(sObjectAllowList[m], pointer, 1);
    }
}

bool smlua_cobject_allowlist_contains(u16 lot, u64 pointer) {
    if (pointer == 0) { return false; }
    if (!smlua_valid_lot(lot)) { return false; }

    u16 m = smlua_lot_mapping(lot);
    if (sCachedObjectAllowed[m] == pointer) { return true; }

    return hmget(sObjectAllowList[m], pointer);
}

/////////////////////////////

static struct AllowList* sPointerAllowList[LVT_MAX] = { 0 };
static u64 sCachedPointerAllowed[LVT_MAX] = { 0 };

void smlua_cpointer_allowlist_init(void) {
    smlua_cpointer_allowlist_shutdown();
}

void smlua_cpointer_allowlist_shutdown(void) {
    for (s32 i = 0; i < LVT_MAX; i++) {
        sCachedPointerAllowed[i] = 0;

        while (sPointerAllowList[i] && hmlen(sPointerAllowList[i]) > 0) {
            hmdel(sPointerAllowList[i], sPointerAllowList[i]->key);
        }

        sPointerAllowList[i] = NULL;
    }
}

void smlua_cpointer_allowlist_add(u16 lvt, u64 pointer) {
    if (pointer == 0) { return; }
    if (!smlua_valid_lvt(lvt)) { return; }

    if (sCachedPointerAllowed[lvt] == pointer) { return; }
    sCachedPointerAllowed[lvt] = pointer;

    if (!hmget(sPointerAllowList[lvt], pointer)) {
        hmput(sPointerAllowList[lvt], pointer, 1);
    }
}

bool smlua_cpointer_allowlist_contains(u16 lvt, u64 pointer) {
    if (pointer == 0) { return false; }
    if (!smlua_valid_lvt(lvt)) { return false; }

    if (sCachedPointerAllowed[lvt] == pointer) { return true; }

    return hmget(sPointerAllowList[lvt], pointer);
}