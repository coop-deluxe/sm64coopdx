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
#include "pc/configfile.h"

#define DJUI_CHAT_LIFE_TIME_DEFAULT 10.0f

static bool djui_chat_message_render(struct DjuiBase* base) {
    struct DjuiChatMessage* chatMessage = (struct DjuiChatMessage*)base;
    struct DjuiBase* ctBase = &chatMessage->message->base;

    f32 lifeTime = (f32)configChatMessageLifetime;
    if (lifeTime < 1.0f)  lifeTime = 1.0f;
    if (lifeTime > 120.0f) lifeTime = 120.0f;

    f32 seconds = clock_elapsed() - chatMessage->createTime;
    f32 f = 1.0f;
    if (seconds >= (lifeTime - 1.0f)) {
        f = fmax(1.0f - (seconds - (lifeTime - 1.0f)), 0.0f);
        f *= f;
        f *= f;
    }

    if (gDjuiChatBoxFocus) {
        djui_base_set_color(base, 0, 0, 0, 0);
        djui_base_set_color(ctBase, 255, 255, 255, 255);
        djui_base_set_size_type(base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(base, 1.0f, chatMessage->base.height.value);
    } else if (configDisableChatWhenClosed) {
        return false;
    } else if (f <= 0.1f) {
        return false;
    } else {
        int bgAlphaI = (int)(configChatOpacity * f * 2.55f);
        if (bgAlphaI > 255) { bgAlphaI = 255; }
        if (bgAlphaI < 0)   { bgAlphaI = 0; }
        u8 bgAlpha = (u8)bgAlphaI;

        // Text-Deckkraft: beim Standardwert (70) bereits voll sichtbar,
        // darunter linear bis 0 herunter, darüber weiterhin voll sichtbar.
        const f32 defaultOpacity = 70.0f;
        f32 textScale = 1.0f;
        if ((f32)configChatOpacity < defaultOpacity) {
            textScale = (f32)configChatOpacity / defaultOpacity;
        }
        u8 textAlpha = (u8)(255.0f * f * textScale);

        djui_base_set_color(base, 0, 0, 0, bgAlpha);
        djui_base_set_color(ctBase, 255, 255, 255, textAlpha);
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

    bool allowMessage = true;
    smlua_call_event_hooks(HOOK_ON_CHAT_MESSAGE, &gMarioStates[np->localIndex], message, &allowMessage);
    if (!allowMessage) {
        return;
    }

    const char* playerColorString = network_get_player_text_color_string(np->localIndex);
    char chatMsg[MAX_CHAT_MSG_LENGTH] = { 0 };
    snprintf(chatMsg, MAX_CHAT_MSG_LENGTH, "%s%s\\#dcdcdc\\: %s", playerColorString, (np != NULL) ? np->name : "Player", message);

    play_sound((globalIndex == gNetworkPlayerLocal->globalIndex) ? SOUND_MENU_MESSAGE_DISAPPEAR : SOUND_MENU_MESSAGE_APPEAR, gGlobalSoundSource);
    djui_chat_message_create(chatMsg);
}

static void djui_chat_message_apply_style_one(struct DjuiChatMessage* chatMessage) {
    struct DjuiBase* base = &chatMessage->base;

    f32 maxTextWidth = gDjuiChatBox->base.width.value
        - gDjuiChatBox->base.padding.left.value - gDjuiChatBox->base.padding.right.value
        - base->padding.left.value - base->padding.right.value;

    struct DjuiText* chatText = chatMessage->message;
    struct DjuiBase* ctBase = &chatText->base;
    djui_base_set_size_type(ctBase, DJUI_SVT_ABSOLUTE, DJUI_SVT_RELATIVE);
    djui_base_set_size(ctBase, maxTextWidth, 1.0f);
    djui_base_set_color(ctBase, 255, 255, 255, 255);
    djui_base_set_location(ctBase, 0, 0);
    djui_text_set_alignment(chatText, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);

    // apply text scale based on config
    f32 scale = ((f32)configChatTextScale) / 100.0f;
    if (scale < 0.5f) { scale = 0.5f; }
    if (scale > 1.5f) { scale = 1.5f; }
    djui_text_set_font_scale(chatText, chatText->font->defaultFontScale * scale);

    // figure out chat message height
    chatText->base.comp.width = maxTextWidth;
    f32 messageHeight = djui_text_count_lines(chatText, 10)
        * (chatText->font->lineHeight * chatText->font->defaultFontScale * scale) + 8;
    djui_base_set_size(base, 1.0f, messageHeight);

    // figure out chat message width
    f32 messageWidth = djui_text_find_width(chatText, 10);
    chatMessage->messageWidth = messageWidth + 8;
}

void djui_chat_messages_apply_style(void) {
    if (gDjuiChatBox == NULL || gDjuiChatBox->chatFlow == NULL) { return; }

    gDjuiChatBox->chatFlow->base.height.value = 0;

    struct DjuiBaseChild* child = gDjuiChatBox->chatFlow->base.child;
    while (child != NULL) {
        struct DjuiChatMessage* msg = (struct DjuiChatMessage*)child->base;
        djui_chat_message_apply_style_one(msg);
        gDjuiChatBox->chatFlow->base.height.value += msg->base.height.value + gDjuiChatBox->chatFlow->margin.value;
        child = child->next;
    }

    if (!gDjuiChatBox->scrolling) {
        f32 containerHeight = gDjuiChatBox->base.height.value - 32.0f - 18.0f;
        gDjuiChatBox->chatFlow->base.y.value = containerHeight - gDjuiChatBox->chatFlow->base.height.value;
    }
}

void djui_chat_message_create(const char* message) {
    if (gDjuiChatBox == NULL || gDjuiChatBox->chatFlow == NULL) { return; }
    struct DjuiChatMessage* chatMessage = calloc(1, sizeof(struct DjuiChatMessage));
    struct DjuiBase* base = &chatMessage->base;
    djui_base_init(&gDjuiChatBox->chatFlow->base, base, djui_chat_message_render, djui_chat_message_destroy);
    djui_base_set_size_type(base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(base, 1.0f, 0);
    djui_base_set_color(base, 0, 0, 0, 0);
    djui_base_set_padding(base, 0, 4, 0, 4);
    djui_base_set_alignment(base, DJUI_HALIGN_LEFT, DJUI_VALIGN_BOTTOM);

    struct DjuiText* chatText = djui_text_create(base, message);
    chatMessage->message = chatText;
    chatMessage->createTime = clock_elapsed();

    djui_chat_message_apply_style_one(chatMessage);

    gDjuiChatBox->chatFlow->base.height.value += chatMessage->base.height.value + gDjuiChatBox->chatFlow->margin.value;
    if (!gDjuiChatBox->scrolling) {
        gDjuiChatBox->chatFlow->base.y.value = gDjuiChatBox->chatContainer->base.elem.height - gDjuiChatBox->chatFlow->base.height.value;
    }
}
