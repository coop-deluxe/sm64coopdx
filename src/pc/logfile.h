#ifndef LOGFILE_H
#define LOGFILE_H

#include <stdio.h>
#include "pc/debuglog.h"

#pragma pack(1)
struct LogFile {
    const char* fileName;
    bool active;
    bool firstOpen;
    FILE* file;
};
#pragma pack()

enum LogFileType {
    LFT_HANG,
    LFT_DISCORD,
    LFT_MAX
};

extern struct LogFile gLogFiles[];

FILE* logfile_open(enum LogFileType logFileType);
void logfile_close(enum LogFileType logFileType);

static void _logfile_print_timestamp(enum LogFileType logFileType) {
    FILE* f = gLogFiles[logFileType].file;
    time_t ltime = time(NULL);
#if defined(_WIN32)
    char* str = asctime(localtime(&ltime));
#else
    struct tm ltime2 = { 0 };
    localtime_r(&ltime, &ltime2);
    char* str = asctime(&ltime2);
#endif
    fprintf(f, "%.*s", (int)strlen(str) - 1, str);
}

static void _logfile_print_log_type(enum LogFileType logFileType, char* logType) {
    FILE* f = gLogFiles[logFileType].file;
    fprintf(f, "\t[%s]\t", logType);
}

static void _logfile_print_short_filename(enum LogFileType logFileType, char* filename, int fileLine) {
    FILE* f = gLogFiles[logFileType].file;
    char* last = strrchr(filename, '/');
    if (last != NULL) {
        fprintf(f, "%s:%d\t\t", last + 1, fileLine);
    } else {
        fprintf(f, "???:%d\t\t", fileLine);
    }
}

static void _logfile_print_log(enum LogFileType logFileType, char* logType, char* filename, int fileLine) {
    logfile_open(logFileType);
    _logfile_print_timestamp(logFileType);
    _logfile_print_log_type(logFileType, logType);
    _logfile_print_short_filename(logFileType, filename, fileLine);
}

#if defined(DEBUG) && defined(DISABLE_MODULE_LOG)
    #define LOGFILE_DEBUG(_LFT, ...)
    #define LOGFILE_INFO(_LFT,  ...)
    #define LOGFILE_ERROR(_LFT, ...)
#elif defined(DEBUG) && !defined(DISABLE_MODULE_LOG)
    #define LOGFILE_DEBUG(_LFT, ...) ( _logfile_print_log(_LFT, "DEBUG", __FILE__, __LINE__), fprintf(gLogFiles[_LFT].file, __VA_ARGS__), fprintf(gLogFiles[_LFT].file, "\n"), LOG_DEBUG(__VA_ARGS__))
    #define LOGFILE_INFO(_LFT,  ...) ( _logfile_print_log(_LFT, "INFO",  __FILE__, __LINE__), fprintf(gLogFiles[_LFT].file, __VA_ARGS__), fprintf(gLogFiles[_LFT].file, "\n"), LOG_INFO (__VA_ARGS__))
    #define LOGFILE_ERROR(_LFT, ...) ( _logfile_print_log(_LFT, "ERROR", __FILE__, __LINE__), fprintf(gLogFiles[_LFT].file, __VA_ARGS__), fprintf(gLogFiles[_LFT].file, "\n"), LOG_ERROR(__VA_ARGS__))
#else
    #define LOGFILE_DEBUG(_LFT, ...) ( _logfile_print_log(_LFT, "DEBUG", __FILE__, __LINE__), fprintf(gLogFiles[_LFT].file, __VA_ARGS__), fprintf(gLogFiles[_LFT].file, "\n"))
    #define LOGFILE_INFO(_LFT,  ...) ( _logfile_print_log(_LFT, "INFO",  __FILE__, __LINE__), fprintf(gLogFiles[_LFT].file, __VA_ARGS__), fprintf(gLogFiles[_LFT].file, "\n"))
    #define LOGFILE_ERROR(_LFT, ...) ( _logfile_print_log(_LFT, "ERROR", __FILE__, __LINE__), fprintf(gLogFiles[_LFT].file, __VA_ARGS__), fprintf(gLogFiles[_LFT].file, "\n"))
#endif

#endif
