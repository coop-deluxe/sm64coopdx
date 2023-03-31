#include <stdio.h>
#include "djui.h"
#include "src/pc/network/network.h"
#include "src/pc/network/discord/discord.h"
#include "src/pc/utils/misc.h"
#include "src/pc/configfile.h"
#include "pc/utils/misc.h"
#include "src/game/level_update.h"
#include "src/game/hardcoded.h"
#include "src/engine/math_util.h"
#include "audio/external.h"
#include "sounds.h"

void djui_panel_do_host(void) {
    stop_demo(NULL);
    djui_panel_shutdown();
    extern s16 gCurrSaveFileNum;
    gCurrSaveFileNum = configHostSaveSlot;
    update_all_mario_stars();

#ifndef DISCORD_SDK
    configNetworkSystem = 1;
    network_set_system(NS_SOCKET);
#else
    if (configNetworkSystem == 0) {
        network_set_system(NS_DISCORD);
    } else {
        network_set_system(NS_SOCKET);
    }
#endif

    network_init(NT_SERVER);
    djui_panel_modlist_create(NULL);
    fake_lvl_init_from_save_file();

    extern s16 gChangeLevelTransition;
    gChangeLevelTransition = gLevelValues.entryLevel;

    if (gMarioState->marioObj) vec3f_copy(gMarioState->marioObj->header.gfx.cameraToObject, gGlobalSoundSource);

    play_character_sound(gMarioState, CHAR_SOUND_OKEY_DOKEY);
    extern void play_transition(s16 transType, s16 time, u8 red, u8 green, u8 blue);
    play_transition(0x09, 0x14, 0x00, 0x00, 0x00);
}

void djui_panel_host_message_do_host(UNUSED struct DjuiBase* caller) {
    network_reset_reconnect_and_rehost();
    djui_panel_do_host();
}

void djui_panel_host_message_create(struct DjuiBase* caller) {
    f32 warningLines = 0;
    char* warningMessage = NULL;
    bool hideHostButton = false;

#ifdef DISCORD_SDK
    if (!configNetworkSystem) {
        warningLines = gDiscordFailed ? 5 : 13;
        warningMessage = gDiscordFailed ? DLANG(HOST_MESSAGE, WARN_DISCORD2) : DLANG(HOST_MESSAGE, WARN_DISCORD);
        hideHostButton = gDiscordFailed;
    } else
#endif
    {
        warningLines = 5;
        warningMessage = calloc(256, sizeof(char));
        sprintf(warningMessage, DLANG(HOST_MESSAGE, WARN_SOCKET), configHostPort);
    }

    f32 textHeight = 32 * 0.8125f * warningLines + 8;

    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(HOST_MESSAGE, INFO_TITLE));
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        struct DjuiText* text1 = djui_text_create(body, warningMessage);
        djui_base_set_size_type(&text1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&text1->base, 1.0f, textHeight);
        djui_base_set_color(&text1->base, 200, 200, 200, 255);

        struct DjuiRect* rect1 = djui_rect_container_create(body, 64);
        {
            struct DjuiButton* btnHost = djui_button_right_create(&rect1->base, DLANG(HOST_MESSAGE, HOST), DJUI_BUTTON_STYLE_NORMAL, djui_panel_host_message_do_host);
            struct DjuiButton* btnBack = djui_button_left_create(&rect1->base, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);

            if (hideHostButton) {
                djui_base_set_size(&btnBack->base, 1.0f, 64);
                djui_base_set_visible(&btnHost->base, false);
                djui_base_set_enabled(&btnHost->base, false);
            }
        }
    }

    djui_panel_add(caller, panel, NULL);
#ifdef DISCORD_SDK
    if (configNetworkSystem)
#endif
    {
        free(warningMessage);
    }
}
