/*
rom_offsets.h

Small header expected by generated code. If you prefer a different API, you can replace this.
This file is also safe to keep in the repo; codegen will generate rom_offsets.c implementing rom_addr().

Include rom_offsets.h in code that needs ROM symbol addresses.
*/
#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uintptr_t rom_addr(const char *symbol);
#define ROM_FUNC(sym) ((void(*)())rom_addr(sym))
#define ROM_PTR(sym, type) (*(type*)rom_addr(sym))

#ifdef __cplusplus
}
#endif
