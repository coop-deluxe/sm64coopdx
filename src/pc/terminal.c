#include <stdio.h>
#include <pthread.h>
#if !defined(_WIN32) && !defined(_WIN64)
#include <sys/select.h>
#include <unistd.h>
#include <termios.h>
#include "linenoise/linenoise.h"
#endif
#include "djui/djui_console.h"
#include "commands.h"
#include "pc_main.h"
#include "terminal.h"

#define TERMINAL_BUFFER_SIZE 1024

#if !defined(_WIN32) && !defined(_WIN64)
static struct linenoiseState sLinenoiseState;
#endif
static char sTerminalInput[TERMINAL_BUFFER_SIZE] = { 0 };
static bool sTerminalInitialized = false;
static bool sTerminalActive = false;
static pthread_mutex_t sTerminalMutex = PTHREAD_MUTEX_INITIALIZER;

void log_to_terminal(const char* fmt, ...) {
    pthread_mutex_lock(&sTerminalMutex);
    va_list args;
    va_start(args, fmt);

#if !defined(_WIN32) && !defined(_WIN64)
    if (sTerminalActive) { linenoiseHide(&sLinenoiseState); }
#endif

    vprintf(fmt, args);

#if !defined(_WIN32) && !defined(_WIN64)
    if (sTerminalActive) { linenoiseShow(&sLinenoiseState); }
#endif

    va_end(args);
    pthread_mutex_unlock(&sTerminalMutex);
}

static void terminal_stop() {
#if !defined(_WIN32) && !defined(_WIN64)
    if (!sTerminalInitialized) { return; }
    linenoiseEditStop(&sLinenoiseState);
    sTerminalActive = false;
#endif
}

void terminal_init() {
#if !defined(_WIN32) && !defined(_WIN64)
    if (!isatty(STDIN_FILENO)) {
        sTerminalActive = false;
        sTerminalInitialized = false;
        return;
    }

    if (tcgetpgrp(STDIN_FILENO) != getpgrp()) {
        sTerminalActive = false;
        sTerminalInitialized = false;
        return;
    }

    if (linenoiseEditStart(&sLinenoiseState, -1, -1, sTerminalInput, sizeof(sTerminalInput), "> ") == -1) {
        sTerminalInitialized = false;
        sTerminalActive = false;
        return;
    }
    sTerminalInitialized = true;
    sTerminalActive = true;
#endif
}

void terminal_update() {
#if !defined(_WIN32) && !defined(_WIN64)
    if (!sTerminalInitialized) { return; }
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);

    if (select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) <= 0) { return; }

    char* input = linenoiseEditFeed(&sLinenoiseState);

    if (input == NULL) {
        linenoiseEditStop(&sLinenoiseState);
        game_exit();
    } else if (input != linenoiseEditMore) {
        terminal_stop();

        if (input[0] != '\0') {
            run_command(input[0] == '/' ? input + 1 : input, true);
            linenoiseHistoryAdd(input);
        }

        free(input);

        terminal_init();
    }
    #endif
}

void terminal_clear() {
#if !defined(_WIN32) && !defined(_WIN64)
    if (!sTerminalInitialized) { return; }
    linenoiseClearScreen();
#endif
}
