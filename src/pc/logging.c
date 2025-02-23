#include "logging.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <stdbool.h>
#include "fs/fs.h"

#define LOG_FOLDER "logs"
#define LOG_EXTENSION ".log"
#define MAX_LOG_LINE 512
#define LOG_FORMAT "[%s %s] (%s/%s) %s\n"

static FILE *logFile = NULL;

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
        strncpy(date_buffer, "unknown_date", date_size);
        strncpy(time_buffer, "unknown_time", time_size);
        return;
    }

    strftime(date_buffer, date_size, "%Y-%m-%d", t);

    char time_format[16];
    snprintf(time_format, sizeof(time_format), "%s", for_filename ? "%H-%M-%S" : "%H:%M:%S");

    char time_part[64];
    strftime(time_part, sizeof(time_part), time_format, t);
    snprintf(time_buffer, time_size, "%s_%03ld", time_part, ts.tv_nsec / 1000000);
}

// Returns a string representation of the log category
static const char* get_category_string(LogCategory category) {
    switch (category) {
        case LOG_CATEGORY_RUNTIME: return "Runtime";
        case LOG_CATEGORY_GAME: return "Game";
        case LOG_CATEGORY_DYNOS: return "DynOS";
        case LOG_CATEGORY_LUA: return "Lua";
        case LOG_CATEGORY_NETWORK: return "Network";
        case LOG_CATEGORY_CHAT: return "Chat";
        default: return "Unknown";
    }
}

// Returns a string representation of the log type
static const char* get_type_string(LogType type) {
    switch (type) {
        case LOG_TYPE_INFO: return "INFO";
        case LOG_TYPE_WARN: return "WARN";
        case LOG_TYPE_ERROR: return "ERROR";
        case LOG_TYPE_CRASH: return "CRASH";
        case LOG_TYPE_DEBUG: return "DEBUG";
        default: return "UNKNOWN";
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
static void write_log(LogCategory category, LogType type, const char *message) {
    if (logFile == NULL) {
        fprintf(stderr, "Error: Log file is not open. Cannot write log message.\n");
        return;
    }

    char date_buffer[64], time_buffer[64];
    generate_timestamp(date_buffer, sizeof(date_buffer), time_buffer, sizeof(time_buffer), 0);

    printf(LOG_FORMAT, date_buffer, time_buffer, get_category_string(category), get_type_string(type), message);

    fprintf(logFile, LOG_FORMAT, date_buffer, time_buffer, get_category_string(category), get_type_string(type), message);
    fflush(logFile);
}

void log_message(LogCategory category, LogType type, const char *format, ...) {
    ensure_log_file_open();

    static char message[MAX_LOG_LINE];
    va_list args;
    va_start(args, format);
    vsnprintf(message, MAX_LOG_LINE, format, args);
    va_end(args);

    write_log(category, type, message);
}

// Closes the log file when the program exits
__attribute__((destructor)) static void close_log_file() {
    if (logFile) {
        fclose(logFile);
        logFile = NULL;
    }
}
