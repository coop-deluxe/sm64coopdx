#pragma once
#include "djui.h"

enum ConsoleMessageLevel {
    CONSOLE_MESSAGE_INFO,
    CONSOLE_MESSAGE_WARNING,
    CONSOLE_MESSAGE_ERROR
};

struct DjuiConsole {
    struct DjuiBase base;
    struct DjuiFlowLayout* flow;
    bool scrolling;
};

#define CONSOLE_MAX_TMP_BUFFER 512
extern struct DjuiConsole* gDjuiConsole;
extern bool gDjuiConsoleFocus;
extern char gDjuiConsoleTmpBuffer[];

void djui_console_message_dequeue(void);
void djui_console_message_create(const char* message, enum ConsoleMessageLevel level);
/* |description|Toggles the visibility of the DJUI console|descriptionEnd| */
void djui_console_toggle(void);
struct DjuiConsole* djui_console_create(void);
