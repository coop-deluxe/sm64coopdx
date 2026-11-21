#include <stdio.h>
#include <time.h>
#include "pc/network/network.h"
#include "pc/djui/djui_console.h"
#include "pc/terminal.h"
#include "debuglog.h"

bool log_type_should_print(enum LogType logType) {
    switch (logType) {
        case LOG_TYPE_DEBUG:
            if (!configDebugPrint) { return false; }
            return true;
        case LOG_TYPE_INFO:
            if (!configDebugInfo && !gCLIOpts.headless) { return false; }
            return true;
        case LOG_TYPE_WARNING:
            if (!configDebugWarning) { return false; }
            return true;
        case LOG_TYPE_ERROR:
            if (!configDebugError) { return false; }
            return true;
        default:
            return true;
    }
}

const char *log_type_ansi_color(enum LogType logType) {
    switch (logType) {
        case LOG_TYPE_DEBUG:   return "\x1b[0m";
        case LOG_TYPE_INFO:    return "\x1b[0m";
        case LOG_TYPE_WARNING: return "\x1b[33m";
        case LOG_TYPE_ERROR:   return "\x1b[31m";
        default:               return "\x1b[0m";
    }
}

const char *log_type_hex_color_code(enum LogType logType) {
    switch (logType) {
        case LOG_TYPE_DEBUG:
            return "\\#\\";
        case LOG_TYPE_INFO:
            return "\\#\\";
        case LOG_TYPE_WARNING:
            return "\\#ffffa0\\";
        case LOG_TYPE_ERROR:
            return "\\#ffa0a0\\";
        default:
            return "\\#\\";
    }
}

const char *log_type_name(enum LogType logType) {
    switch (logType) {
        case LOG_TYPE_DEBUG:   return "DEBUG";
        case LOG_TYPE_INFO:    return "INFO";
        case LOG_TYPE_WARNING: return "WARNING";
        case LOG_TYPE_ERROR:   return "ERROR";
        default:               return "UNKNOWN";
    }
}

static int debuglog_print_timestamp(char *buffer, size_t bufferSize) {
    time_t ltime = time(NULL);
#if defined(_WIN32)
    char *str = asctime(localtime(&ltime));
#else
    struct tm ltime2 = { 0 };
    localtime_r(&ltime, &ltime2);
    char *str = asctime(&ltime2);
#endif
    return snprintf(buffer, bufferSize, "%.*s", (int)strlen(str) - 1, str);
}

static int debuglog_print_network_type(char *buffer, size_t bufferSize) {
    return snprintf(buffer, bufferSize, " [%02d] ", (gNetworkPlayerLocal != NULL) ? gNetworkPlayerLocal->globalIndex : -1);
}

static int debuglog_print_log_type(const char *logTypeString, char *buffer, size_t bufferSize) {
    return snprintf(buffer, bufferSize, "[%s] ", logTypeString);
}

static int debuglog_print_short_filename(const char *filename, char *buffer, size_t bufferSize) {
    const char *last = strrchr(filename, '/');
    if (last != NULL) {
        return snprintf(buffer, bufferSize, "%s: ", last + 1);
    }
    else {
        return snprintf(buffer, bufferSize, "???: ");
    }
}

void debuglog_print_log(enum LogType logType, const char *filename, const char *fmt, ...) {
    const char *ansiColor = log_type_ansi_color(logType);
    const char *logTypeString = log_type_name(logType);

    char log[MAX_LOG_SIZE];
    size_t capacity = MAX_LOG_SIZE;
    char *buffer = log;

    int len = 0;

    len = debuglog_print_timestamp(buffer, capacity);
    if (len < 0 || (size_t)len >= capacity) { return; }
    buffer += len; capacity -= len;

    len = debuglog_print_network_type(buffer, capacity);
    if (len < 0 || (size_t)len >= capacity) { return; }
    buffer += len; capacity -= len;

    len = debuglog_print_log_type(logTypeString, buffer, capacity);
    if (len < 0 || (size_t)len >= capacity) { return; }
    buffer += len; capacity -= len;

    len = debuglog_print_short_filename(filename, buffer, capacity);
    if (len < 0 || (size_t)len >= capacity) { return; }
    buffer += len; capacity -= len;

    va_list args;
    va_start(args, fmt);

    len = vsnprintf(buffer, capacity, fmt, args);

    va_end(args);

    if (len < 0) { return; }

    log_to_terminal("%s%s\x1b[0m\n", ansiColor, log);
    djui_console_message_create(log, logType);
}
