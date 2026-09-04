#pragma once
#include "src/pc/thread.h"

void log_to_terminal(const char* fmt, ...);
void terminal_init();
void terminal_update();
void terminal_clear();
