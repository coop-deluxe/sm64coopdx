#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_host.h"
#include "djui_panel_join.h"
#include "djui_panel_options.h"
#include "djui_panel_menu.h"
#include "djui_panel_confirm.h"
#include "pc/controller/controller_sdl.h"
#include "pc/controller/controller_mouse.h"
#include "pc/pc_main.h"
#include "pc/update_checker.h"
#include "sounds.h"
#include "audio/external.h"
#include "game/area.h"

extern ALIGNED8 u8 texture_coopdx_logo[];

bool gDjuiPanelMainCreated = false;
static struct DjuiThreePanel* sPanelMain = NULL;

static void djui_panel_main_quit_yes(UNUSED struct DjuiBase* caller) {
    game_exit();
}

static void djui_panel_main_quit(struct DjuiBase* caller) {
    djui_panel_confirm_create(caller,
                              DLANG(MAIN, QUIT_TITLE),
                              DLANG(MAIN, QUIT_CONFIRM),
                              djui_panel_main_quit_yes);
}

static int sEggCounter;
static u32 sEggLastFired;
static f32 sEggLastY;
static bool sEggHovered = false;
static bool sEggClicked = false;

static void djui_panel_main_egg_end(struct DjuiBase *base, UNUSED bool *noRender) {
    sPanelMain->base.x.value -= gGlobalTimer - sEggLastFired + 60;
    base->color.a = MAX(255.f - ((gGlobalTimer - sEggLastFired + 60) << 3), 0);
    if (gGlobalTimer == sEggLastFired) {
        configExCoopTheme = !configExCoopTheme;
        game_exit();
    }
}

static void djui_panel_main_egg(struct DjuiBase *base, UNUSED bool *noRender) {
    if (sEggCounter && sEggLastY == base->clip.y) {
        bool hovering = djui_cursor_inside_base(base);
        bool clicking = ((gInteractablePad.button & PAD_BUTTON_A) || (mouse_buttons & L_MOUSE_BUTTON));
    
        if (hovering) {
            if (!sEggHovered && sEggLastFired + 20 < gGlobalTimer) {
                play_sound(SOUND_GENERAL_COIN, gGlobalSoundSource);
            }
            sEggLastFired = gGlobalTimer;
    
            if (!sEggClicked && clicking) {
                play_sound(SOUND_MENU_COLLECT_SECRET + ((5 - sEggCounter) << 16), gGlobalSoundSource);
        
                if (!--sEggCounter) {
                    play_transition(WARP_TRANSITION_FADE_INTO_COLOR, 0x1E, 0xFF, 0xFF, 0xFF);
                    fade_volume_scale(SEQ_PLAYER_LEVEL, 0, 40);
                    sound_banks_disable(SEQ_PLAYER_SFX, SOUND_BANKS_ALL & ~(1 << SOUND_BANK_MENU));
                    sEggLastFired = gGlobalTimer + 60;

                    extern struct DjuiImage* sMouseCursor;
                    sMouseCursor->base.on_render_pre = djui_panel_main_egg_end;
                }
            }
        }
    
        sEggHovered = hovering;
        sEggClicked = clicking;
        return;
    }
    sEggLastY = base->clip.y;
}

void djui_panel_main_create(struct DjuiBase* caller) {
    sPanelMain = djui_panel_menu_create(configExCoopTheme ? "\\#ff0800\\SM\\#1be700\\64\\#00b3ff\\EX\n\\#ffef00\\COOP" : "", false);
    if (configExCoopTheme) { djui_three_panel_get_header(sPanelMain)->on_render_pre = djui_panel_main_egg; }
    
    {
        struct DjuiBase* body = djui_three_panel_get_body(sPanelMain);
        {
            if (!configExCoopTheme) {
                struct DjuiImage* logo = djui_image_create(body, texture_coopdx_logo, 2048, 1024, G_IM_FMT_RGBA, G_IM_SIZ_32b);
                if (configDjuiThemeCenter) {
                    djui_base_set_size(&logo->base, 550, 275);
                } else {
                    djui_base_set_size(&logo->base, 480, 240);
                }
                djui_base_set_alignment(&logo->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_TOP);
                djui_base_set_location_type(&logo->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
                djui_base_set_location(&logo->base, 0, -30);
                logo->base.on_render_pre = djui_panel_main_egg;
            }

            struct DjuiButton* button1 = djui_button_create(body, DLANG(MAIN, HOST), DJUI_BUTTON_STYLE_NORMAL, djui_panel_host_create);
            if (!configExCoopTheme) { djui_base_set_location(&button1->base, 0, -30); }
            djui_cursor_input_controlled_center(&button1->base);

            struct DjuiButton* button2 = djui_button_create(body, DLANG(MAIN, JOIN), DJUI_BUTTON_STYLE_NORMAL, djui_panel_join_create);
            if (!configExCoopTheme) { djui_base_set_location(&button2->base, 0, -30); }
            struct DjuiButton* button3 = djui_button_create(body, DLANG(MAIN, OPTIONS), DJUI_BUTTON_STYLE_NORMAL, djui_panel_options_create);
            if (!configExCoopTheme) { djui_base_set_location(&button3->base, 0, -30); }
            struct DjuiButton* button4 = djui_button_create(body, DLANG(MAIN, QUIT), DJUI_BUTTON_STYLE_BACK, djui_panel_main_quit);
            if (!configExCoopTheme) { djui_base_set_location(&button4->base, 0, -30); }
        }

        // these two cannot co-exist for some reason
        if (gUpdateMessage) {
            struct DjuiText* message = djui_text_create(&sPanelMain->base, DLANG(NOTIF, UPDATE_AVAILABLE));
            djui_base_set_size_type(&message->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&message->base, 1.0f, 1.0f);
            djui_base_set_color(&message->base, 255, 255, 160, 255);
            djui_text_set_alignment(message, DJUI_HALIGN_CENTER, DJUI_VALIGN_BOTTOM);
        } else {
            struct DjuiText* version = djui_text_create(
                &sPanelMain->base,
                #ifdef COMPILE_TIME
                    get_version_with_build_date()
                #else
                    get_version()
                #endif
            );
            djui_base_set_size_type(&version->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&version->base, 1.0f, 1.0f);
            djui_base_set_color(&version->base, 50, 50, 50, 255);
            djui_text_set_alignment(version, configExCoopTheme ? DJUI_HALIGN_CENTER : DJUI_HALIGN_RIGHT, DJUI_VALIGN_BOTTOM);
        }
    }

    djui_panel_add(caller, sPanelMain, NULL);
    gInteractableOverridePad = true;
    gDjuiPanelMainCreated = true;
    sEggCounter = 5;
}
