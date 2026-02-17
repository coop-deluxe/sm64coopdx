#ifndef SMLUA_FFI_H
#define SMLUA_FFI_H

#include <ffi.h>
#include "smlua.h"

struct LuaClosure {
    ffi_closure* closure;
    ffi_cif* cif;
    void* boundFunc;
    LuaFunction luaFunc;
    struct Mod* mod;
    struct LuaClosure* next;
};

void* smlua_ffi_create_closure(LuaFunction func, void* bridge, ffi_cif* cif);
void smlua_ffi_cleanup(void);

#endif
