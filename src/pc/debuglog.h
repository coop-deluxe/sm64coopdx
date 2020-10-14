#include <stdio.h>
#include <time.h>
#include "pc/network/network.h"

#if defined(DEBUG) && !defined(DISABLE_MODULE_LOG)
    static void debuglog_print_timestamp(void) {
        time_t ltime = time(NULL);
        char* str = asctime(localtime(&ltime));
        printf("%.*s", (int)strlen(str) - 1, str);
    }

    static void debuglog_print_network_type(void) {
        printf(" [%02d] ", (gNetworkPlayerLocal != NULL) ? gNetworkPlayerLocal->globalIndex : -1);
    }

    static void debuglog_print_log_type(char* logType) {
        printf("[%s] ", logType);
    }

    static void debuglog_print_short_filename(char* filename) {
        char* last = strrchr(filename, '/');
        if (last != NULL) {
            printf("%s: ", last + 1);
        } else {
            printf("???: ");
        }
    }

    static void debuglog_print_log(char* logType, char* filename) {
        debuglog_print_timestamp();
        debuglog_print_network_type();
        debuglog_print_log_type(logType);
        debuglog_print_short_filename(filename);
    }

    #define LOG_INFO(...)  ( debuglog_print_log("INFO ", __FILE__), printf(__VA_ARGS__), printf("\n") )
    #define LOG_ERROR(...) ( debuglog_print_log("ERROR", __FILE__), printf(__VA_ARGS__), printf("\n") )
#else
    #define LOG_INFO(...)
    #define LOG_ERROR(...)
#endif
