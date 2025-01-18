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
    LOG_CATEGORY_SETTINGS,
    LOG_CATEGORY_MODS,
    LOG_CATEGORY_NETWORK,
    LOG_CATEGORY_CLIENT,
    LOG_CATEGORY_SERVER,
    LOG_CATEGORY_COOPNET,
    LOG_CATEGORY_CONSOLE,
    LOG_CATEGORY_CHAT,
    LOG_CATEGORY_DEBUG
} LogCategory;

/**
 * Enum representing the different log types.
 */
typedef enum {
    LOG_TYPE_INFO,
    LOG_TYPE_WARN,
    LOG_TYPE_ERROR,
    LOG_TYPE_CRASH,
    LOG_TYPE_DEBUG
} LogType;

/**
 * Logs a message with optional additional arguments.
 * IMPORTANT: Always terminate the variadic arguments with NULL.
 * If the NULL parameter is omitted, the program will crash.
 * 
 * Examples:
 * log_message(LOG_CATEGORY_CLIENT, LOG_TYPE_INFO, "Test", NULL);
 * log_message(LOG_CATEGORY_CLIENT, LOG_TYPE_INFO, "Hello", " World", "!", NULL);
 *
 * @param category The log category (e.g., LOG_CATEGORY_GAME).
 * @param type The log type (e.g., LOG_TYPE_INFO).
 * @param message The base message string.
 * @param ... Additional strings to concatenate, terminated by NULL.
 */
void log_message(LogCategory category, LogType type, const char *message, ...);

/**
 * Utility functions to convert various basic data types to strings.
 */
char* log_int(int value);
char* log_uint(unsigned int value);
char* log_short(short value);
char* log_ushort(unsigned short value);
char* log_long(long value);
char* log_ulong(unsigned long value);
char* log_longlong(long long value);
char* log_ulonglong(unsigned long long value);
char* log_float(float value);
char* log_double(double value);
char* log_longdouble(long double value);
char* log_bool(bool value);
char* log_char(char value);

#endif // LOGGING_H
