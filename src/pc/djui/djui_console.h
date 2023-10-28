#pragma once
#include "djui.h"

struct DjuiConsole {
    struct DjuiThreePanel* panel;
    struct DjuiFlowLayout* flow;
    bool scrolling;
};

#define CONSOLE_MAX_TMP_BUFFER 256
extern struct DjuiConsole* gDjuiConsole;
extern bool gDjuiConsoleFocus;
extern char gDjuiConsoleTmpBuffer[];

void djui_console_message_create(char* message);
void djui_console_toggle(void);
struct DjuiConsole* djui_console_create(void);
