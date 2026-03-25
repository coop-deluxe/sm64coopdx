#pragma once
#include "src/pc/thread.h"

extern struct ThreadHandle gTerminalThread;

void log_to_terminal(const char* fmt, ...);
//void* terminal_update(UNUSED void* dummy);
void terminal_init();
void terminal_update();
void terminal_clear();