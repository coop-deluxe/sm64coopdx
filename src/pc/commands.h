#pragma once

#include <stdbool.h>
#include "src/pc/lua/smlua_autogen.h"
#include "src/pc/djui/djui_console.h"

#define MAX_COMMAND_LEN 128
// only applies to builtin commands
#define MAX_COMMAND_DESC_LEN 512

struct Command {
    char command[MAX_COMMAND_LEN];
    char description[MAX_COMMAND_DESC_LEN];
    bool (*action)(const char *);
    bool active;
    bool isChatCommand;
};

struct Command *get_command(const char *name);
void run_command(char *command, bool onConsole);
void command_message_create(const char *message, OPTIONAL enum ConsoleMessageLevel level);

extern enum ChatConfirmCommand gConfirmingCommandType;
extern u8 gConfirmPlayerIndex;
