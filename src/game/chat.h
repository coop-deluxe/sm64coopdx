#ifndef CHAT_H
#define CHAT_H

enum ChatMessageType {
    CMT_LOCAL,
    CMT_REMOTE,
    CMT_SYSTEM,
    CMT_INPUT,
};

void render_chat(void);
void chat_add_message(char* ascii, enum ChatMessageType chatMessageType);
void chat_add_message_ext(char* ascii, enum ChatMessageType chatMessageType, const u8 color[3]);
void chat_start_input(void);

#endif