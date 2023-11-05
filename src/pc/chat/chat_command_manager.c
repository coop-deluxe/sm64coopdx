#include "chat_command_manager.h"
#include <string.h>

#define MAX_COMMANDS 512

typedef struct {
    const char* name;
    bool (*execute)(char* args);
    const char* description;
} CommandEntry;

static CommandEntry sCommands[MAX_COMMANDS];
static s32 sNumCommands = 0;

void register_chat_command(const char* commandName, bool (*execute)(char* args), const char* description) {
    if (sNumCommands < MAX_COMMANDS) {
        sCommands[sNumCommands].name = commandName;
        sCommands[sNumCommands].execute = execute;
        sCommands[sNumCommands].description = description;
        sNumCommands++;
    }
}

bool execute_chat_command(char* commandName, char* args) {
    for (s32 i = 0; i < sNumCommands; i++) {
        if (strcmp(sCommands[i].name, commandName) == 0) {
            return sCommands[i].execute(args);
        }
    }
    return false;
}

void display_all_chat_commands() {
    for (s32 i = 0; i < sNumCommands; i++) {
        djui_chat_message_create(sCommands[i].description);
    }
}
