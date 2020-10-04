#ifndef CUSTOM_MENU_H
#define CUSTOM_MENU_H
#include "custom_menu_system.h"

extern u8 gOpenConnectMenu;

void custom_menu_init(struct CustomMenu* head);
void custom_menu_loop(void);
void custom_menu_on_load_save_file(s8 saveFileNum);
void custom_menu_goto_game(s16 saveFileNum);
void custom_menu_connection_error(char* message);

#endif // CUSTOM_MENU_H
