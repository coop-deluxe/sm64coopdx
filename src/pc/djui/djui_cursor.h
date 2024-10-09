#pragma once
#include "djui.h"
#include "djui_base.h"

extern f32 gCursorX;
extern f32 gCursorY;

void djui_cursor_set_visible(bool visible);
bool djui_cursor_inside_base(struct DjuiBase* base);
void djui_cursor_input_controlled_center(struct DjuiBase* base);
void djui_cursor_move(s8 xDir, s8 yDir);
void djui_cursor_update(void);
void djui_cursor_create(void);
