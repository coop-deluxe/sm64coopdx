#include <stdio.h>
#include "smlua.h"
#include "data/dynos_cmap.cpp.h"

static void* sPointers = NULL;

void smlua_pointer_user_data_shutdown(void) {
    hmap_clear(sPointers);
}

void smlua_pointer_user_data_init(void) {
    smlua_pointer_user_data_shutdown();
}

void smlua_pointer_user_data_add(uintptr_t pointer, CObject *obj) {
    if (pointer == 0) { return; }

    if (!sPointers) {
        sPointers = hmap_create();
    }

    if (!hmap_get(sPointers, pointer)) {
        hmap_put(sPointers, pointer, obj);
    }
}

void smlua_pointer_user_data_delete(uintptr_t pointer) {
    if (pointer == 0) { return; }
    hmap_del(sPointers, pointer);
}

CObject *smlua_pointer_user_data_get(uintptr_t pointer) {
    if (pointer == 0) { return NULL; }
    return hmap_get(sPointers, pointer);
}
