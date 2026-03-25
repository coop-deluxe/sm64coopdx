#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>
#include <termios.h>
#include "linenoise/linenoise.h"
#include "djui/djui_console.h"
#include "commands.h"
#include "pc_main.h"
#include "terminal.h"

#define TERMINAL_BUFFER_SIZE 1024

static struct linenoiseState sLinenoiseState;
static char sTerminalInput[TERMINAL_BUFFER_SIZE] = { 0 };
static bool sTerminalInitialized = false;
static bool sTerminalActive = false;

void log_to_terminal(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    if (sTerminalActive) linenoiseHide(&sLinenoiseState);

    vprintf(fmt, args);

    if (sTerminalActive) linenoiseShow(&sLinenoiseState);

    va_end(args);
}

static void terminal_stop() {
    if (!sTerminalInitialized) return;
    linenoiseEditStop(&sLinenoiseState);
    sTerminalActive = false;
}

void terminal_init() {
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

    linenoiseEditStart(&sLinenoiseState, -1, -1, sTerminalInput, sizeof(sTerminalInput), "> ");
    sTerminalInitialized = true;
    sTerminalActive = true;
}

void terminal_update() {
    if (!sTerminalInitialized) return;
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);

    if (select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) <= 0) return;

    char* input = linenoiseEditFeed(&sLinenoiseState);

    if (input == NULL) {
        linenoiseEditStop(&sLinenoiseState);
        game_exit();
    } else if (input != linenoiseEditMore) {
        terminal_stop();

        if (input[0] != '\0') {
            run_command(input);
            linenoiseHistoryAdd(input);
        }

        free(input);

        terminal_init();
    }
}

void terminal_clear() {
    if (!sTerminalInitialized) return;
    linenoiseClearScreen();
}