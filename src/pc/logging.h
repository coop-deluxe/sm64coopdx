#ifndef LOGGING_H
#define LOGGING_H

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

/**
 * Enum representing the different logging categories.
 */
typedef enum {
    LOG_CATEGORY_RUNTIME,
    LOG_CATEGORY_GAME,
    LOG_CATEGORY_DYNOS,
    LOG_CATEGORY_LUA,
    LOG_CATEGORY_NETWORK,
    LOG_CATEGORY_CHAT
} LogCategory;

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
 * log_message(LOG_CATEGORY_CLIENT, LOG_TYPE_INFO, "Test", NULL);
 * log_message(LOG_CATEGORY_CLIENT, LOG_TYPE_INFO, "Hello", " World", "!", NULL);
 *
 * @param category Log category (e.g. LOG_CATEGORY_GAME).
 * @param type Log type (e.g. LOG_TYPE_INFO).
 * @param format String to be logged. Optionally can include format specifiers.
 * @param ... Values to replace format specifiers.
 */
void log_message(LogCategory category, LogType type, const char *format, ...);

#endif // LOGGING_H
