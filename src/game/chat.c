#include <stdio.h>
#include <ultra64.h>
#include <string.h>

#include "chat.h"
#include "game_init.h"
#include "ingame_menu.h"
#include "mario_misc.h"
#include "segment2.h"
#include "gfx_dimensions.h"
#include "config.h"
#include "PR/gbi.h"
#include "pc/controller/controller_keyboard.h"
#include "pc/network/network.h"
#include "audio_defines.h"
#include "audio/external.h"
#include "menu/file_select.h"

#define CHAT_DIALOG_MAX 96
#define CHAT_MESSAGES_MAX 16
#define CHAT_LIFE_MAX 400

struct ChatMessage {
    u8 dialog[CHAT_DIALOG_MAX];
    enum ChatMessageType type;
    u16 life;
    u8 color[3];
};

static char inputMessage[CHAT_DIALOG_MAX] = { 0 };
static struct ChatMessage message[CHAT_MESSAGES_MAX] = { 0 };
static u8 onMessageIndex = 0;
static u8 sInChatInput = FALSE;

#define CHAT_SCALE       0.5f
#define CHAT_SPACE      10.0f
#define CHATBOX_PAD_X    0.0215f
#define CHATBOX_SCALE_X  0.00385f
#define CHATBOX_SCALE_Y  0.115f
#define CHATBOX_X        2.0f
#define CHATBOX_Y       11.0f
#define CHAT_X           4.0f
#define CHAT_Y         -18.0f

static void render_chat_message(struct ChatMessage* chatMessage, u8 index) {
    f32 textWidth = get_generic_dialog_width(chatMessage->dialog);
    f32 alphaScale = ((f32)chatMessage->life / (f32)(CHAT_LIFE_MAX / 20.0f));
    alphaScale *= alphaScale;
    if (alphaScale > 1) { alphaScale = 1; }

    f32 chatBoxWidth = CHATBOX_SCALE_X * textWidth + CHATBOX_PAD_X;
    create_dl_translation_matrix(MENU_MTX_PUSH, GFX_DIMENSIONS_FROM_LEFT_EDGE(CHATBOX_X), CHATBOX_Y + index * CHAT_SPACE, 0);
    create_dl_scale_matrix(MENU_MTX_NOPUSH, chatBoxWidth, CHATBOX_SCALE_Y, 1.0f);

    u8 boxR, boxG, boxB;
    if (chatMessage->type == CMT_INPUT) {
        boxR = 150;
        boxG = 150;
        boxB = 255;
    } else {
        f32 rgbScale = (((f32)chatMessage->life - ((f32)CHAT_LIFE_MAX * 0.98f)) / ((f32)CHAT_LIFE_MAX * 0.02f));
        if (chatMessage->type == CMT_LOCAL || rgbScale < 0) { rgbScale = 0; }
        boxR = 255 * rgbScale;
        boxG = 255 * rgbScale;
        boxB = 255 * rgbScale;
    }

    gDPSetEnvColor(gDisplayListHead++, boxR, boxG, boxB, 110 * alphaScale);
    gSPDisplayList(gDisplayListHead++, dl_draw_text_bg_box);

    create_dl_scale_matrix(MENU_MTX_NOPUSH, CHAT_SCALE / chatBoxWidth, CHAT_SCALE / CHATBOX_SCALE_Y, 1.0f);

    u8 textR, textG, textB;
    switch (chatMessage->type) {
        case CMT_LOCAL:  textR =  200; textG =  200; textB =  255; break;
        case CMT_INPUT:  textR =    0; textG =    0; textB =    0; break;
        case CMT_SYSTEM: textR =  255; textG =  255; textB =  190; break;
        default:         textR =  255; textG =  255; textB =  255; break;
    }

    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);

    gDPSetEnvColor(gDisplayListHead++, textR, textG, textB, 255 * alphaScale);
    print_generic_string(CHAT_X, CHAT_Y, chatMessage->dialog);

    if (chatMessage->type == CMT_REMOTE || chatMessage->type == CMT_SYSTEM) {
        // if it's someone else's message, highlight the icon with their color
        u8 starR = chatMessage->color[0];
        u8 starG = chatMessage->color[1];
        u8 starB = chatMessage->color[2];
        gDPSetEnvColor(gDisplayListHead++, starR, starG, starB, 255 * alphaScale);
        create_dl_translation_matrix(MENU_MTX_PUSH, CHAT_X, CHAT_Y, 0.0f);
        render_generic_char(chatMessage->dialog[0]);
        gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
    }

    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);

    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

void chat_add_message_ext(char* ascii, enum ChatMessageType chatMessageType, const u8 color[3]) {
    u8 character = '?';
    switch (chatMessageType) {
        case CMT_INPUT:
        case CMT_LOCAL: character = 0xFD; break;
        case CMT_REMOTE: character = 0xFA; break;
        case CMT_SYSTEM: character = 0xF9; break;
    }
    struct ChatMessage* msg = &message[onMessageIndex];
    msg->dialog[0] = character;
    msg->dialog[1] = 0x9E;
    str_ascii_to_dialog(ascii, &msg->dialog[2], MIN(strlen(ascii), CHAT_DIALOG_MAX - 3));
    msg->life = (sSelectedFileNum != 0) ? CHAT_LIFE_MAX : CHAT_LIFE_MAX / 3;
    msg->type = chatMessageType;
    msg->color[0] = color[0];
    msg->color[1] = color[1];
    msg->color[2] = color[2];
    onMessageIndex = (onMessageIndex + 1) % CHAT_MESSAGES_MAX;
    play_sound((msg->type == CMT_LOCAL) ? SOUND_MENU_MESSAGE_DISAPPEAR : SOUND_MENU_MESSAGE_APPEAR, gDefaultSoundArgs);
}

void chat_add_message(char* ascii, enum ChatMessageType chatMessageType) {
    const u8 defaultColor[3] = { 255, 255, 255 };
    chat_add_message_ext(ascii, chatMessageType, defaultColor);
}

static void chat_stop_input(void) {
    sInChatInput = FALSE;
    keyboard_stop_text_input();
}

static void chat_send_input(void) {
    sInChatInput = FALSE;
    keyboard_stop_text_input();
    if (strlen(gTextInput) == 0) { return; }
    chat_add_message(gTextInput, CMT_LOCAL);
    // our message has the same color as our shirt
    network_send_chat(gTextInput, get_player_color(gNetworkPlayerLocal->globalIndex, 0));
}

void chat_start_input(void) {
    sInChatInput = TRUE;
    keyboard_start_text_input(TIM_SINGLE_LINE, CHAT_DIALOG_MAX - 3, chat_stop_input, chat_send_input);
}

void render_chat(void) {
    u8 count = 0;
    if (sInChatInput) {
        struct ChatMessage inputMessage = { 0 };
        inputMessage.type = CMT_INPUT;
        inputMessage.dialog[0] = 0xFD;
        inputMessage.dialog[1] = 0x9E;
        str_ascii_to_dialog(gTextInput, &inputMessage.dialog[2], MIN(strlen(gTextInput), CHAT_DIALOG_MAX - 3));
        inputMessage.life = CHAT_LIFE_MAX;
        render_chat_message(&inputMessage, count++);
    }

    u8 index = onMessageIndex;
    for (int i = 0; i < CHAT_MESSAGES_MAX; i++) {
        if (--index >= CHAT_MESSAGES_MAX) { index = CHAT_MESSAGES_MAX - 1; }
        if (message[index].life == 0) { continue; }
        render_chat_message(&message[index], count++);
        message[index].life--;
    }
}
