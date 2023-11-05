#ifndef CHAT_COMMAND_MANAGER_H
#define CHAT_COMMAND_MANAGER_H
#include <stdbool.h>
#include "chat_command.h"
#include "pc/djui/djui.h"

void register_chat_command(const char* commandName, bool (*execute)(char* args), const char* description);
bool execute_chat_command(char* commandName, char* args);
void display_all_chat_commands();

#endif
