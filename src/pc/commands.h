#pragma once

#define MAX_COMMAND_LEN 128
// only applies to builtin commands
#define MAX_COMMAND_DESC_LEN 512

struct Command {
    char command[MAX_COMMAND_LEN];
    char description[MAX_COMMAND_DESC_LEN];
    bool (*action)(const char*);
    bool active;
    bool isChatCommand;
};

struct Command* get_command(const char* name);
void run_command(char* command);
void command_message_create(const char* message, OPTIONAL enum ConsoleMessageLevel level);