#pragma once
#include "djui.h"

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
void djui_console_message_create(const char* message);
void djui_console_toggle(void);
struct DjuiConsole* djui_console_create(void);
