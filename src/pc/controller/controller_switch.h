#ifndef CONTROLLER_SWITCH_H
#define CONTROLLER_SWITCH_H

#include "controller_api.h"

extern struct ControllerAPI controller_switch;

void show_swkb(char *text);
void hide_swkb(void);
void poll_swkb(void);

#endif
