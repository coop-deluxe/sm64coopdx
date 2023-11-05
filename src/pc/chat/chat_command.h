#ifndef CHAT_COMMAND_H
#define CHAT_COMMAND_H
#include <stdbool.h>
#include "pc/djui/djui.h"

typedef struct ChatCommand {
    char* commandName;
    bool (*execute)(char* command);
    void (*display)();
} ChatCommand;

#endif
