// logfile.c - handles opening and closing of the log file

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "pc/fs/fs.h"
#include "pc/debuglog.h"
#include "logfile.h"

struct LogFile gLogFiles[LFT_MAX] = {
    { .fileName = "hanglog.txt",    .active = false, .firstOpen = true, .file = NULL },
    { .fileName = "discordlog.txt", .active = false, .firstOpen = true, .file = NULL }
};

FILE* logfile_open(enum LogFileType logFileType) {
    struct LogFile* logfile = &gLogFiles[logFileType];
    if (logfile->active) {
        return logfile->file;
    }

    LOG_INFO("opening log file '%s'", logfile->fileName);
    logfile->file = fopen(fs_get_write_path(logfile->fileName), logfile->firstOpen ? "w+" : "a");
    logfile->firstOpen = false;

    if (logfile->file == NULL) { return NULL; }

    logfile->active = true;
    return logfile->file;
}

void logfile_close(enum LogFileType logFileType) {
    struct LogFile* logfile = &gLogFiles[logFileType];
    if (!logfile->active) { return; }

    fflush(logfile->file);
    fclose(logfile->file);

    logfile->file = NULL;
    logfile->active = false;
}
