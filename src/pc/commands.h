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
/* |description|
Creates a message that goes into either the chat, console, or terminal.
It decides by checking where you entered the command, and will output to that source directly.

It should be used in any function that is ran from `hook_chat_command` or `hook_console_command`.
If ran independently of any hook, it decides on where to output by checking if the chat box is open. If so, log there, otherwise, log to the console and terminal
|descriptionEnd| */
void command_message_create(const char *message, OPTIONAL enum ConsoleMessageLevel level);

extern enum ChatConfirmCommand gConfirmingCommandType;
extern u8 gConfirmPlayerIndex;
