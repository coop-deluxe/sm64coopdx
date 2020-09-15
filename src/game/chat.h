#ifndef CHAT_H
#define CHAT_H

void render_chat(void);
void chat_add_message(char* ascii, u8 isLocal);
void chat_start_input(void);

#endif