#include <stdio.h>
#include "pc/network/network.h"
#include "pc/utils/misc.h"
#include "sounds.h"
#include "audio/external.h"
#include "game/mario_misc.h"
#include "djui.h"
#include "djui_hud_utils.h"
#include "pc/debuglog.h"
#include "pc/lua/smlua_hooks.h"

#define DJUI_CHAT_LIFE_TIME 10.0f

static bool djui_chat_message_render(struct DjuiBase* base) {
    struct DjuiChatMessage* chatMessage = (struct DjuiChatMessage*)base;
    struct DjuiBase* ctBase = &chatMessage->message->base;

    f32 seconds = clock_elapsed() - chatMessage->createTime;
    f32 f = 1.0f;
    if (seconds >= (DJUI_CHAT_LIFE_TIME - 1)) {
        f = fmax(1.0f - (seconds - (DJUI_CHAT_LIFE_TIME - 1)), 0.0f);
        f *= f;
        f *= f;
    }

    if (gDjuiChatBoxFocus) {
        djui_base_set_color(base, 0, 0, 0, 120);
        djui_base_set_color(ctBase, 255, 255, 255, 255);
        djui_base_set_size_type(base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(base, 1.0f, chatMessage->base.height.value);
    } else if (f <= 0.1f) {
        return false;
    } else {
        djui_base_set_color(base, 0, 0, 0, 180 * f);
        djui_base_set_color(ctBase, 255, 255, 255, 255 * f);
        djui_base_set_size_type(base, DJUI_SVT_ABSOLUTE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(base, chatMessage->messageWidth, chatMessage->base.height.value);
    }

    djui_text_set_font(chatMessage->message, gDjuiFonts[configDjuiThemeFont == 0 ? FONT_NORMAL : FONT_ALIASED]);

    djui_rect_render(base);
    return true;
}

static void djui_chat_message_destroy(struct DjuiBase* base) {
    struct DjuiChatMessage* chatMessage = (struct DjuiChatMessage*)base;
    free(chatMessage);
}

void djui_chat_message_create_from(u8 globalIndex, const char* message) {
    struct NetworkPlayer* np = network_player_from_global_index(globalIndex);
    if (np == NULL) {
        LOG_ERROR("Could not find network player, global index: %u", globalIndex);
        return;
    }

    bool returnValue = true;
    smlua_call_event_hooks_on_chat_message(HOOK_ON_CHAT_MESSAGE, &gMarioStates[np->localIndex], message, &returnValue);
    if (!returnValue) {
        return;
    }

    const char* playerColorString = network_get_player_text_color_string(np->localIndex);
    char chatMsg[MAX_CHAT_MSG_LENGTH] = { 0 };
    snprintf(chatMsg, MAX_CHAT_MSG_LENGTH, "%s%s\\#dcdcdc\\: %s", playerColorString, (np != NULL) ? np->name : "Player", message);

    play_sound((globalIndex == gNetworkPlayerLocal->globalIndex) ? SOUND_MENU_MESSAGE_DISAPPEAR : SOUND_MENU_MESSAGE_APPEAR, gGlobalSoundSource);
    djui_chat_message_create(chatMsg);
}

void djui_chat_message_create(const char* message) {
    if (gDjuiChatBox == NULL || gDjuiChatBox->chatFlow == NULL) { return; }
    struct DjuiChatMessage* chatMessage = calloc(1, sizeof(struct DjuiChatMessage));
    struct DjuiBase* base = &chatMessage->base;
    djui_base_init(&gDjuiChatBox->chatFlow->base, base, djui_chat_message_render, djui_chat_message_destroy);
    djui_base_set_size_type(base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(base, 1.0f, 0);
    djui_base_set_color(base, 0, 0, 0, 64);
    djui_base_set_padding(base, 2, 4, 2, 4);
    djui_base_set_alignment(base, DJUI_HALIGN_LEFT, DJUI_VALIGN_BOTTOM);

    f32 maxTextWidth = gDjuiChatBox->base.width.value - gDjuiChatBox->base.padding.left.value - gDjuiChatBox->base.padding.right.value - base->padding.left.value - base->padding.right.value;

    struct DjuiText* chatText = djui_text_create(base, message);
    struct DjuiBase* ctBase = &chatText->base;
    djui_base_set_size_type(ctBase, DJUI_SVT_ABSOLUTE, DJUI_SVT_RELATIVE);
    djui_base_set_size(ctBase, maxTextWidth, 1.0f);
    djui_base_set_color(ctBase, 255, 255, 255, 255);
    djui_base_set_location(ctBase, 0, 0);
    djui_text_set_alignment(chatText, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
    chatMessage->message = chatText;
    chatMessage->createTime = clock_elapsed();

    // figure out chat message height
    chatText->base.comp.width = maxTextWidth;
    f32 messageHeight = djui_text_count_lines(chatText, 10) * (chatText->font->lineHeight * chatText->font->defaultFontScale) + 8;
    djui_base_set_size(base, 1.0f, messageHeight);
    gDjuiChatBox->chatFlow->base.height.value += messageHeight + gDjuiChatBox->chatFlow->margin.value;
    if (!gDjuiChatBox->scrolling) {
        gDjuiChatBox->chatFlow->base.y.value = gDjuiChatBox->chatContainer->base.elem.height - gDjuiChatBox->chatFlow->base.height.value;
    }

    // figure out chat message width
    f32 messageWidth = djui_text_find_width(chatText, 10);
    chatMessage->messageWidth = messageWidth + 8;
}
