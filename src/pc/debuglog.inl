#ifndef DEBUGLOG_INL
#define DEBUGLOG_INL

#include <stdio.h>
#include <time.h>

#include "pc/djui/djui_console.h"
#include "pc/terminal.h"
#include "pc/network/network.h"

OPTIMIZE_O3 INLINE int _debuglog_print_timestamp(char* buffer, size_t bufferSize) {
    time_t ltime = time(NULL);
#if defined(_WIN32)
    struct tm* lctime = localtime(&ltime);
    if (lctime == NULL) { return 0; }
    char* str = asctime(lctime);
    if (str == NULL) { return 0; }
#else
    struct tm ltime2 = { 0 };
    localtime_r(&ltime, &ltime2);
    char* str = asctime(&ltime2);
#endif
    return snprintf(buffer, bufferSize, "%.*s", (int)strlen(str) - 1, str);
}

OPTIMIZE_O3 INLINE int _debuglog_print_network_type(char* buffer, size_t bufferSize) {
    extern struct NetworkPlayer *gNetworkPlayerLocal;
    return snprintf(buffer, bufferSize, " [%02d] ", (gNetworkPlayerLocal != NULL) ? gNetworkPlayerLocal->globalIndex : -1);
}

OPTIMIZE_O3 INLINE int _debuglog_print_log_type(const char* logType, char* buffer, size_t bufferSize) {
    return snprintf(buffer, bufferSize, "[%s] ", logType);
}

OPTIMIZE_O3 INLINE int _debuglog_print_short_filename(const char* filename, char* buffer, size_t bufferSize) {
    const char* last = strrchr(filename, '/');
    if (last != NULL) {
        return snprintf(buffer, bufferSize, "%s: ", last + 1);
    }
    return snprintf(buffer, bufferSize, "???: ");
}

#endif // DEBUGLOG_INL