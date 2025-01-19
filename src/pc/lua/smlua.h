#ifndef SMLUA_H
#define SMLUA_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <stdbool.h>
#include "types.h"

#include "smlua_cobject.h"
#include "smlua_cobject_autogen.h"
#include "smlua_utils.h"
#include "smlua_functions.h"
#include "smlua_functions_autogen.h"
#include "smlua_hooks.h"
#include "smlua_sync_table.h"

#include "pc/debuglog.h"
#include "pc/djui/djui_console.h"

#define LOG_LUA(...)  { if (!gSmLuaSuppressErrors) { printf("[LUA] "), printf(__VA_ARGS__), printf("\n"), smlua_mod_error(), snprintf(gDjuiConsoleTmpBuffer, CONSOLE_MAX_TMP_BUFFER, __VA_ARGS__), sys_swap_backslashes(gDjuiConsoleTmpBuffer), djui_console_message_create(gDjuiConsoleTmpBuffer, CONSOLE_MESSAGE_ERROR); } }
#define LOG_LUA_LINE(...)  { if (!gSmLuaSuppressErrors) { printf("[LUA] "), printf(__VA_ARGS__), printf("\n"), smlua_mod_error(); snprintf(gDjuiConsoleTmpBuffer, CONSOLE_MAX_TMP_BUFFER, __VA_ARGS__), sys_swap_backslashes(gDjuiConsoleTmpBuffer), djui_console_message_create(gDjuiConsoleTmpBuffer, CONSOLE_MESSAGE_ERROR), smlua_logline(); } }
#define LOG_LUA_LINE_WARNING(...)  { if (!gLuaActiveMod->showedScriptWarning) { gLuaActiveMod->showedScriptWarning = true; smlua_mod_warning(); snprintf(gDjuiConsoleTmpBuffer, CONSOLE_MAX_TMP_BUFFER, __VA_ARGS__), sys_swap_backslashes(gDjuiConsoleTmpBuffer), djui_console_message_create(gDjuiConsoleTmpBuffer, CONSOLE_MESSAGE_WARNING); } }

#ifdef DEVELOPMENT
#define LUA_STACK_CHECK_BEGIN_NUM(n) int __LUA_STACK_TOP = lua_gettop(gLuaState) + (n)
#define LUA_STACK_CHECK_BEGIN() LUA_STACK_CHECK_BEGIN_NUM(0)
#define LUA_STACK_CHECK_END() if ((__LUA_STACK_TOP) != lua_gettop(gLuaState)) { smlua_dump_stack(); fflush(stdout); } assert((__LUA_STACK_TOP) == lua_gettop(gLuaState))
#else
#define LUA_STACK_CHECK_BEGIN_NUM(n)
#define LUA_STACK_CHECK_BEGIN()
#define LUA_STACK_CHECK_END()
#endif

extern lua_State* gLuaState;
extern u8 gLuaInitializingScript;
extern u8 gSmLuaSuppressErrors;
extern struct Mod* gLuaLoadingMod;
extern struct Mod* gLuaActiveMod;
extern struct Mod* gLuaLastHookMod;

void smlua_mod_error(void);
void smlua_mod_warning(void);
int smlua_error_handler(UNUSED lua_State* L);
int smlua_pcall(lua_State* L, int nargs, int nresults, int errfunc);
void smlua_exec_file(const char* path);
void smlua_exec_str(const char* str);

void smlua_init(void);
void smlua_update(void);
void smlua_shutdown(void);

#endif
