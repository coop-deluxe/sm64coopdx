#include "pc/debuglog.h"

OPTIMIZE_O3 void _debuglog_print_log(const char* color, const char* logType, const char* filename, const char* fmt, ...) {
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