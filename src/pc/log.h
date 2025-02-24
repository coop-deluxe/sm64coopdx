#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

/**
 * Enum representing the different logging contexts.
 */
typedef enum {
    LOG_CTX_RUNTIME,
    LOG_CTX_GAME,
    LOG_CTX_DYNOS,
    LOG_CTX_LUA,
    LOG_CTX_NETWORK,
    LOG_CTX_CHAT
    // MUST BE KEPT IN SYNC WITH sLogContextNames
} LogContext;

/**
 * Enum representing the different log types.
 */
typedef enum {
    LOG_TYPE_INFO,
    LOG_TYPE_WARN,
    LOG_TYPE_ERROR,
    LOG_TYPE_DEBUG,
    LOG_TYPE_CRASH
} LogType;

/**
 * Logs a message with optional additional arguments.
 *
 * Examples:
 * log_message(LOG_CATEGORY_CLIENT, LOG_TYPE_INFO, "Test");
 * log_message(LOG_CATEGORY_CLIENT, LOG_TYPE_INFO, "Hello, %s!", "World");
 *
 * @param type Log type (e.g. LOG_TYPE_INFO).
 * @param format String to be logged. Optionally can include format specifiers.
 * @param ... Values to replace format specifiers.
 */
void log_message(LogType type, const char *format, ...);
void log_message_with_file(LogType type, const char* filename, uint16_t line, const char *format, ...);

void log_context_begin(LogContext ctx);
void log_context_end(LogContext ctx);

#if defined(DISABLE_MODULE_LOG)
#define LOG_INFO(...)
#define LOG_WARN(...)
#define LOG_ERROR(...)
#define LOG_DEBUG(...)
#else
#define LOG_INFO(...) log_message(LOG_TYPE_INFO, __VA_ARGS__)
#define LOG_WARN(...) log_message(LOG_TYPE_WARN, __VA_ARGS__)
#define LOG_ERROR(...) log_message(LOG_TYPE_ERROR, __VA_ARGS__)
#define LOG_DEBUG(...) log_message(LOG_TYPE_DEBUG, __VA_ARGS__)
#define LOG_INFO_FILE(...) log_message_with_file(LOG_TYPE_INFO,  __FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARN_FILE(...) log_message_with_file(LOG_TYPE_WARN, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERROR_FILE(...) log_message_with_file(LOG_TYPE_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_DEBUG_FILE(...) log_message_with_file(LOG_TYPE_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#endif
#define LOG_CRASH(...) log_message(LOG_TYPE_CRASH, __VA_ARGS__)
#define LOG_CONSOLE(...)  snprintf(gDjuiConsoleTmpBuffer, CONSOLE_MAX_TMP_BUFFER, __VA_ARGS__), djui_console_message_create(gDjuiConsoleTmpBuffer, CONSOLE_MESSAGE_INFO)

#endif // LOGGING_H
