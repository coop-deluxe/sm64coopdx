#ifndef DEBUGLOG_H
#define DEBUGLOG_H

#include <stdio.h>
#include <time.h>
#include "pc/network/network.h"
#include "pc/djui/djui_console.h"
#include "pc/terminal.h"

#define MAX_LOG_SIZE 8192

static int _debuglog_print_timestamp(char* buffer, size_t bufferSize) {
    time_t ltime = time(NULL);
#if defined(_WIN32)
    char* str = asctime(localtime(&ltime));
#else
    struct tm ltime2 = { 0 };
    localtime_r(&ltime, &ltime2);
    char* str = asctime(&ltime2);
#endif
    return snprintf(buffer, bufferSize, "%.*s", (int)strlen(str) - 1, str);
}

static int _debuglog_print_network_type(char* buffer, size_t bufferSize) {
    return snprintf(buffer, bufferSize, " [%02d] ", (gNetworkPlayerLocal != NULL) ? gNetworkPlayerLocal->globalIndex : -1);
}

static int _debuglog_print_log_type(const char* logType, char* buffer, size_t bufferSize) {
    return snprintf(buffer, bufferSize, "[%s] ", logType);
}

static int _debuglog_print_short_filename(const char* filename, char* buffer, size_t bufferSize) {
    const char* last = strrchr(filename, '/');
    if (last != NULL) {
        return snprintf(buffer, bufferSize, "%s: ", last + 1);
    }
    else {
        return snprintf(buffer, bufferSize, "???: ");
    }
}

static inline void _debuglog_print_log(const char* color, const char* logType, const char* filename, const char* fmt, ...) {
    char log[MAX_LOG_SIZE];
    size_t capacity = MAX_LOG_SIZE;
    char* buffer = log;

    int len = 0;

    len = snprintf(buffer, capacity, "%s", color);
    if (len < 0 || (size_t)len >= capacity) return;
    buffer += len; capacity -= len;

    len = _debuglog_print_timestamp(buffer, capacity);
    if (len < 0 || (size_t)len >= capacity) return;
    buffer += len; capacity -= len;

    len = _debuglog_print_network_type(buffer, capacity);
    if (len < 0 || (size_t)len >= capacity) return;
    buffer += len; capacity -= len;

    len = _debuglog_print_log_type(logType, buffer, capacity);
    if (len < 0 || (size_t)len >= capacity) return;
    buffer += len; capacity -= len;

    len = _debuglog_print_short_filename(filename, buffer, capacity);
    if (len < 0 || (size_t)len >= capacity) return;
    buffer += len; capacity -= len;

    va_list args;
    va_start(args, fmt);

    len = vsnprintf(buffer, capacity, fmt, args);

    va_end(args);

    if (len < 0) return;

    log_to_terminal("%s\x1b[0m\n", log);
}

#if defined(DISABLE_MODULE_LOG)
#define LOG_DEBUG(...)
#define LOG_INFO(...)
#define LOG_ERROR(...)
#else
#define LOG_DEBUG(...) (configDebugPrint ? ( _debuglog_print_log("", "DEBUG", __FILE__, __VA_ARGS__) ) : 0)
#define LOG_INFO(...)  ((configDebugInfo || gCLIOpts.headless) ? ( _debuglog_print_log("", "INFO",  __FILE__, __VA_ARGS__) ) : 0)
#define LOG_ERROR(...) (configDebugError ? ( _debuglog_print_log("\x1b[31m", "ERROR", __FILE__, __VA_ARGS__) ) : 0)
#endif
#define LOG_CONSOLE(...)  { snprintf(gDjuiConsoleTmpBuffer, CONSOLE_MAX_TMP_BUFFER, __VA_ARGS__), djui_console_message_create(gDjuiConsoleTmpBuffer, CONSOLE_MESSAGE_INFO); }

#endif
