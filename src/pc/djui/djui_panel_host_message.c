#include <stdio.h>
#include "djui.h"
#include "src/pc/network/network.h"
#include "src/pc/network/discord/discord.h"
#include "src/pc/utils/misc.h"
#include "src/pc/configfile.h"
#include "pc/utils/misc.h"
#include "src/game/level_update.h"
#include "audio/external.h"
#include "audio_defines.h"

#ifdef DISCORD_SDK
static char* sWarningDiscord = "\
Invite friends by right clicking their name on Discord and clicking on\n\
'\\#d0d0ff\\Invite to Game\\#c8c8c8\\'.\n\n\
You can invite channels of servers as well by clicking the \\#d0d0ff\\plus\\#c8c8c8\\ button next to the place where you enter chat.\n\n\
Game Activity \\#ffa0a0\\must be\\#c8c8c8\\ enabled in your\nDiscord user settings.\n\n\
Appearing offline \\#ffa0a0\\will prevent\\#c8c8c8\\ invites from being sent.\
";
static char* sWarningDiscord2 = "\\#ffa0a0\\Error:\\#c8c8c8\\ Could not detect Discord.\n\n\\#a0a0a0\\Try closing the game,\nrestarting Discord,\nand opening the game again.";
#endif

static char* sWarningSocket = "\
Direct connections \\#ffa0a0\\require you\\#c8c8c8\\ to configure port forwarding in your router.\n\n\
Forward port '\\#d0d0ff\\%d\\#c8c8c8\\' for UDP.\
";

void djui_panel_host_message_do_host(UNUSED struct DjuiBase* caller) {
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
    gChangeLevelTransition = 16;
    play_sound(SOUND_MENU_STAR_SOUND_OKEY_DOKEY, gDefaultSoundArgs);
    extern void play_transition(s16 transType, s16 time, u8 red, u8 green, u8 blue);
    play_transition(0x09, 0x14, 0x00, 0x00, 0x00);
}

void djui_panel_host_message_create(struct DjuiBase* caller) {
    f32 warningLines = 0;
    char* warningMessage = NULL;
    bool hideHostButton = false;

#ifdef DISCORD_SDK
    if (!configNetworkSystem) {
        warningLines = gDiscordFailed ? 5 : 13;
        warningMessage = gDiscordFailed ? sWarningDiscord2 : sWarningDiscord;
        hideHostButton = gDiscordFailed;
    } else
#endif
    {
        warningLines = 5;
        warningMessage = calloc(256, sizeof(char));
        sprintf(warningMessage, sWarningSocket, configHostPort);
    }

    f32 textHeight = 32 * 0.8125f * warningLines + 8;
    f32 bodyHeight = textHeight + 16 + 64;

    struct DjuiBase* defaultBase = NULL;
    struct DjuiThreePanel* panel = djui_panel_menu_create(bodyHeight, "\\#ff0800\\I\\#1be700\\N\\#00b3ff\\F\\#ffef00\\O");
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);
    {
        struct DjuiText* text1 = djui_text_create(&body->base, warningMessage);
        djui_base_set_size_type(&text1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&text1->base, 1.0f, textHeight);
        djui_base_set_color(&text1->base, 200, 200, 200, 255);

        struct DjuiRect* rect1 = djui_rect_create(&body->base);
        djui_base_set_size_type(&rect1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&rect1->base, 1.0f, 64);
        djui_base_set_color(&rect1->base, 0, 0, 0, 0);
        {
            struct DjuiButton* button1 = djui_button_create(&rect1->base, "Back");
            djui_base_set_size_type(&button1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button1->base, 0.485f, 64);
            djui_base_set_alignment(&button1->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
            djui_button_set_style(button1, 1);
            djui_interactable_hook_click(&button1->base, djui_panel_menu_back);

            struct DjuiButton* button2 = djui_button_create(&rect1->base, "Host");
            djui_base_set_size_type(&button2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button2->base, 0.485f, 64);
            djui_base_set_alignment(&button2->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
            djui_interactable_hook_click(&button2->base, djui_panel_host_message_do_host);
            defaultBase = &button2->base;

            if (hideHostButton) {
                djui_base_set_size_type(&button1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
                djui_base_set_size(&button1->base, 1.0f, 64);
                defaultBase = &button1->base;
                djui_base_set_visible(&button2->base, false);
                djui_base_set_enabled(&button2->base, false);
            }
        }
    }

    djui_panel_add(caller, &panel->base, defaultBase);
#ifdef DISCORD_SDK
    if (configNetworkSystem)
#endif
    {
        free(warningMessage);
    }
}
