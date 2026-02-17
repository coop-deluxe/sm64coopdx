#include "smlua_ffi.h"
#include "pc/mods/mods.h"

static struct LuaClosure* sLuaClosures = NULL;

void* smlua_ffi_create_closure(LuaFunction func, void* bridge, ffi_cif* cif) {
    if (func == 0) { return NULL; }

    // Check for existing closure
    struct LuaClosure* lc = sLuaClosures;
    while (lc != NULL) {
        if (lc->luaFunc == func && lc->cif == cif) {
            return lc->boundFunc;
        }
        lc = lc->next;
    }

    void* bound_func;
    ffi_closure* closure = ffi_closure_alloc(sizeof(ffi_closure), &bound_func);
    if (closure == NULL) {
        LOG_ERROR("Failed to allocate ffi_closure");
        return NULL;
    }

    lc = malloc(sizeof(struct LuaClosure));
    lc->closure = closure;
    lc->cif = cif;
    lc->boundFunc = bound_func;
    lc->luaFunc = func;
    lc->mod = gLuaActiveMod;
    lc->next = sLuaClosures;
    sLuaClosures = lc;

    if (ffi_prep_closure_loc(closure, cif, bridge, lc, bound_func) != FFI_OK) {
        LOG_ERROR("Failed to prepare ffi_closure");
        return NULL;
    }

    return bound_func;
}

void smlua_ffi_cleanup(void) {
    struct LuaClosure* lc = sLuaClosures;
    while (lc != NULL) {
        struct LuaClosure* next = lc->next;
        if (gLuaState && lc->luaFunc != 0) {
            luaL_unref(gLuaState, LUA_REGISTRYINDEX, lc->luaFunc);
        }
        ffi_closure_free(lc->closure);
        free(lc);
        lc = next;
    }
    sLuaClosures = NULL;
}
