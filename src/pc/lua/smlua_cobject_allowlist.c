#include <stdio.h>
#include "smlua.h"
#include "data/dynos_cmap.cpp.h"

#define LOT_COUNT (LOT_MAX + (LOT_AUTOGEN_MAX - LOT_AUTOGEN_MIN))
static void* sObjectAllowList[LOT_COUNT] = { NULL };
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

        if (sObjectAllowList[i]) {
            hmap_clear(sObjectAllowList[i]);
        }
    }
}

void smlua_cobject_allowlist_add(u16 lot, u64 pointer) {
    if (pointer == 0) { return; }
    if (!smlua_valid_lot(lot)) { return; }

    u16 m = smlua_lot_mapping(lot);
    if (sCachedObjectAllowed[m] == pointer) { return; }
    sCachedObjectAllowed[m] = pointer;

    if (!sObjectAllowList[m]) {
        sObjectAllowList[m] = hmap_create();
    }

    if (!hmap_get(sObjectAllowList[m], pointer)) {
        hmap_put(sObjectAllowList[m], pointer, (void*)1);
    }
}

bool smlua_cobject_allowlist_contains(u16 lot, u64 pointer) {
    if (pointer == 0) { return false; }
    if (!smlua_valid_lot(lot)) { return false; }

    u16 m = smlua_lot_mapping(lot);
    if (sCachedObjectAllowed[m] == pointer) { return true; }

    if (!sObjectAllowList[m]) { return false; }
    return hmap_get(sObjectAllowList[m], pointer) != 0;
}

/////////////////////////////

static void* sPointerAllowList[LVT_MAX] = { 0 };
static u64 sCachedPointerAllowed[LVT_MAX] = { 0 };

void smlua_cpointer_allowlist_init(void) {
    smlua_cpointer_allowlist_shutdown();
}

void smlua_cpointer_allowlist_shutdown(void) {
    for (s32 i = 0; i < LVT_MAX; i++) {
        sCachedPointerAllowed[i] = 0;

        if (sPointerAllowList[i]) {
            hmap_clear(sPointerAllowList[i]);
        }
    }
}

void smlua_cpointer_allowlist_add(u16 lvt, u64 pointer) {
    if (pointer == 0) { return; }
    if (!smlua_valid_lvt(lvt)) { return; }

    if (sCachedPointerAllowed[lvt] == pointer) { return; }
    sCachedPointerAllowed[lvt] = pointer;

    if (!sPointerAllowList[lvt]) {
        sPointerAllowList[lvt] = hmap_create();
    }

    if (!hmap_get(sPointerAllowList[lvt], pointer)) {
        hmap_put(sPointerAllowList[lvt], pointer, (void*)1);
    }
}

bool smlua_cpointer_allowlist_contains(u16 lvt, u64 pointer) {
    if (pointer == 0) { return false; }
    if (!smlua_valid_lvt(lvt)) { return false; }

    if (sCachedPointerAllowed[lvt] == pointer) { return true; }

    if (!sPointerAllowList[lvt]) { return false; }
    return hmap_get(sPointerAllowList[lvt], pointer) != 0;
}