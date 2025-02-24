#include "log.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include "fs/fs.h"

#define LOG_FOLDER "logs"
#define LOG_EXTENSION ".log"

#define LOG_CONTEXT_STACK_SIZE 32

#define MAX_LOG_LINE 512
// [DATE TIME] (CTX/TYPE) MESSAGE
#define LOG_FORMAT "[%s %s] (%s/%s) %s\n"

static FILE *logFile = NULL;

static const char* sLogContextNames[] = {
    "Runtime",
    "Game",
    "DynOS",
    "Lua",
    "Network",
    "Chat"
};

typedef struct {
    LogContext ctx;
    uint16_t depth;
} LogContextItem;

LogContextItem contextStack[LOG_CONTEXT_STACK_SIZE];
uint16_t contextStackTop = 0;
LogContext currentContext;

// Generates a timestamp for filenames or log entries
static void generate_timestamp(char *date_buffer, size_t date_size, char *time_buffer, size_t time_size, int for_filename) {
    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts) != 0) {
        fprintf(stderr, "Error: Failed to get current time.\n");
        strncpy(date_buffer, "unknown_date", date_size);
        strncpy(time_buffer, "unknown_time", time_size);
        return;
    }

    struct tm *t = localtime(&ts.tv_sec);
    if (t == NULL) {
        fprintf(stderr, "Error: Failed to convert time to localtime.\n");
        strncpy(date_buffer, "???", date_size);
        strncpy(time_buffer, "???", time_size);
        return;
    }

    strftime(date_buffer, date_size, "%Y-%m-%d", t);

    char time_format[16];
    snprintf(time_format, sizeof(time_format), "%s", for_filename ? "%H-%M-%S" : "%H:%M:%S");

    char time_part[64];
    strftime(time_part, sizeof(time_part), time_format, t);
    snprintf(time_buffer, time_size, "%s_%03ld", time_part, ts.tv_nsec / 1000000);
}

// Returns a string representation of the log type
static const char* get_type_string(LogType type) {
    switch (type) {
        case LOG_TYPE_INFO: return "INFO";
        case LOG_TYPE_WARN: return "WARN";
        case LOG_TYPE_ERROR: return "ERROR";
        case LOG_TYPE_CRASH: return "CRASH";
        case LOG_TYPE_DEBUG: return "DEBUG";
        default: return "INFO";
    }
}

// Ensures the log file is open and ready for writing
static void ensure_log_file_open() {
    if (logFile != NULL) {
        return;
    }

    const char *base_path = fs_get_write_path("");
    if (!base_path) {
        fprintf(stderr, "Error: Could not determine write path.\n");
        return;
    }

    char log_folder_path[SYS_MAX_PATH];
    snprintf(log_folder_path, sizeof(log_folder_path), "%s/%s", base_path, LOG_FOLDER);

    // Check if the directory exists, create it if it doesn't
    if (!fs_sys_dir_exists(log_folder_path) && !fs_sys_mkdir(log_folder_path)) {
        fprintf(stderr, "Error: Could not create log directory at %s\n", log_folder_path);
        return;
    }

    char date_buffer[64], time_buffer[64];
    generate_timestamp(date_buffer, sizeof(date_buffer), time_buffer, sizeof(time_buffer), 1);

    char log_file_path[SYS_MAX_PATH];
    int count = 1;
    do {
        if (count == 1) {
            snprintf(log_file_path, sizeof(log_file_path), "%s/%s__%s%s", log_folder_path, date_buffer, time_buffer, LOG_EXTENSION);
        } else {
            snprintf(log_file_path, sizeof(log_file_path), "%s/%s__%s__%03d%s", log_folder_path, date_buffer, time_buffer, count, LOG_EXTENSION);
        }
        count++;
    } while (fs_sys_file_exists(log_file_path));

    logFile = fopen(log_file_path, "w");
    if (logFile == NULL) {
        fprintf(stderr, "Error: Could not open log file at %s\n", log_file_path);
    }
}

// Writes a log message to the file
static void write_to_log(LogContext ctx, LogType type, const char *message) {
    if (logFile == NULL) {
        fprintf(stderr, "Error: Log file is not open. Cannot write log message.\n");
        return;
    }

    char date_buffer[64], time_buffer[64];
    generate_timestamp(date_buffer, sizeof(date_buffer), time_buffer, sizeof(time_buffer), 0);

    const char* ctx_str = sLogContextNames[ctx];
    const char* type_str = get_type_string(type);

    switch(type)
    {
        case LOG_TYPE_ERROR:
        case LOG_TYPE_CRASH: fprintf(stderr, LOG_FORMAT, date_buffer, time_buffer, ctx_str, type_str, message); break;
        default: printf(LOG_FORMAT, date_buffer, time_buffer, ctx_str, type_str, message); break;
    }

    fprintf(logFile, LOG_FORMAT, date_buffer, time_buffer, ctx_str, type_str, message);
    fflush(logFile);
}



void log_message(LogType type, const char *format, ...) {
    static char message[MAX_LOG_LINE];
    va_list args;
    va_start(args, format);
    vsnprintf(message, MAX_LOG_LINE, format, args);
    va_end(args);
    
    ensure_log_file_open();
    write_to_log(currentContext, type, message);
}

void log_message_with_file(LogType type, const char* filename, uint16_t line, const char *format, ...) {
    static char message[MAX_LOG_LINE];
    va_list args;
    va_start(args, format);
    vsnprintf(message, MAX_LOG_LINE, format, args);
    va_end(args);
    
    static char full_message[MAX_LOG_LINE];
    snprintf(full_message, MAX_LOG_LINE, "<%s:%i> %s", filename, line, message);

    ensure_log_file_open();
    write_to_log(currentContext, type, full_message);
}

void log_context_begin(LogContext ctx) {
    currentContext = ctx;

    LogContextItem top = contextStack[contextStackTop];
    if (ctx == top.ctx) {
        top.depth++;
        return;
    }

    if (contextStackTop == LOG_CONTEXT_STACK_SIZE - 1) {
        LOG_ERROR("Filled log context stack! Log context may not persist correctly.");
        top.depth++; // Prevent errors when closing context
        return;
    }

    top = contextStack[contextStackTop++];
    top.ctx = ctx;
    top.depth++;
}

void log_context_end(LogContext ctx) {
    if (ctx != currentContext) LOG_ERROR("Closing log context is not the same as current log context.");
;
    LogContextItem top = contextStack[contextStackTop];
    currentContext = top.ctx;

    if (contextStackTop == 0 && top.depth == 0) {
        LOG_ERROR("Log context was closed too many times!");
        return;
    }

    if (top.depth-- == 0) {
        currentContext = contextStack[contextStackTop--].ctx;
    }
}

// Closes the log file when the program exits
__attribute__((destructor)) static void close_log_file() {
    if (logFile) {
        fclose(logFile);
        logFile = NULL;
    }
}
