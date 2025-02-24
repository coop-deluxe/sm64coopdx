#ifndef LOGGING_H
#define LOGGING_H

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

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
 * @param category Log category (e.g. LOG_CATEGORY_GAME).
 * @param type Log type (e.g. LOG_TYPE_INFO).
 * @param format String to be logged. Optionally can include format specifiers.
 * @param ... Values to replace format specifiers.
 */
void log_message(LogType type, const char *format, ...);
void log_message_with_file(LogType type, const char* filename, uint16_t line, const char *format, ...);

void log_context_begin(LogContext ctx);
void log_context_end(LogContext ctx);

#endif // LOGGING_H
