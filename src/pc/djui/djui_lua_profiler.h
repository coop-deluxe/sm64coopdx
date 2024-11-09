#pragma once
#include "djui.h"
#include "pc/mods/mod.h"

void lua_profiler_start_counter(UNUSED struct Mod *mod);
void lua_profiler_stop_counter(UNUSED struct Mod *mod);

void djui_lua_profiler_update(void);
void djui_lua_profiler_render(void);
void djui_lua_profiler_create(void);
void djui_lua_profiler_destroy(void);