#ifndef DEBUGLOG_H
#define DEBUGLOG_H

#include "macros.h"

#define MAX_LOG_SIZE 8192

OPTIMIZE_O3 void _debuglog_print_log(const char* color, const char* logType, const char* filename, const char* fmt, ...);

#define LOG_CONSOLE(...)  { snprintf(gDjuiConsoleTmpBuffer, CONSOLE_MAX_TMP_BUFFER, __VA_ARGS__), djui_console_message_create(gDjuiConsoleTmpBuffer, CONSOLE_MESSAGE_INFO); }
#if defined(DISABLE_MODULE_LOG)
#define LOG_DEBUG(...)
#define LOG_INFO(...)
#define LOG_ERROR(...)
#else
#define LOG_DEBUG(...) { if (configDebugPrint) { _debuglog_print_log("", "DEBUG", __FILE__, __VA_ARGS__); } }
#define LOG_INFO(...)  { if (configDebugInfo || gCLIOpts.headless) { _debuglog_print_log("", "INFO",  __FILE__, __VA_ARGS__); } }
#define LOG_ERROR(...) { if (configDebugError) { _debuglog_print_log("\x1b[31m", "ERROR", __FILE__, __VA_ARGS__); } }
#endif // DISABLE_MODULE_LOG

#include "pc/debuglog.inl"

#endif // DEBUGLOG_H
