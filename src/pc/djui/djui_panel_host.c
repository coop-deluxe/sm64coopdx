#include <stdio.h>
#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "djui_panel_host_mods.h"
#include "djui_panel_host_settings.h"
#include "djui_panel_host_save.h"
#include "djui_panel_host_message.h"
#include "djui_panel_rules.h"
#include "djui_panel_loading.h"
#include "game/save_file.h"
#include "pc/network/network.h"
#include "pc/utils/misc.h"
#include "pc/configfile.h"
#include "pc/pc_main.h"
#include "pc/update_checker.h"
#include "pc/mods/mods.h"
#include "pc/mods/mods_utils.h"
#include "djui_panel_host.h"

extern const Texture exclamation_box_seg8_texture_08015E28[];

static struct DjuiRect* sRectPort = NULL;
static struct DjuiInputbox* sInputboxPort = NULL;
static struct DjuiText* sBigModText = NULL;
static struct DjuiImage* sBigModIcon = NULL;
static struct DjuiButton* sHostButton = NULL;
static int sBigModState = -1;
#ifdef COOPNET
static struct DjuiRect* sRectPassword = NULL;
static struct DjuiInputbox* sInputboxPassword = NULL;
#endif

bool djui_host_blocked_by_mod_size(void) {
#ifdef COOPNET
    return configNetworkSystem == NS_COOPNET && configAmountOfPlayers != 1 && mods_has_too_large_mod();
#else
    return false;
#endif
}

static void djui_panel_host_set_big_mod_text(const char* message) {
    char pad[24] = { 0 };
    char buffer[512] = { 0 };
    f32 iconSize = sBigModIcon->base.height.value;
    f32 spaceWidth = sBigModText->font->char_width(" ") * sBigModText->fontScale;
    int spaces = (int)((iconSize + 6.0f) / spaceWidth + 0.999f);
    if (spaces > (int)sizeof(pad) - 1) { spaces = (int)sizeof(pad) - 1; }
    for (int i = 0; i < spaces; i++) { pad[i] = ' '; }
    snprintf(buffer, sizeof(buffer), "%s%s", pad, message);
    djui_text_set_text(sBigModText, buffer);
}

static void djui_panel_host_on_render_pre(struct DjuiBase* base, UNUSED bool* skipRender) {
    int state = djui_host_blocked_by_mod_size() ? 2 : (mods_has_too_large_mod() ? 1 : 0);
    if (state == sBigModState) { return; }
    sBigModState = state;

    if (state == 0) {
        djui_text_set_text(sBigModText, "");
    } else {
        djui_panel_host_set_big_mod_text((state == 2) ? DLANG(HOST, BIG_MODS_COOPNET) : DLANG(HOST, BIG_MODS_LOADED));
    }
    djui_base_set_visible(&sBigModText->base, state != 0);
    djui_base_set_enabled(&sHostButton->base, state != 2);

    struct DjuiThreePanel* panel = (struct DjuiThreePanel*)base;
    djui_three_panel_set_body_size(panel, 0);
    djui_three_panel_recalculate_body_size(panel);
}

#ifdef COOPNET
static void djui_panel_host_network_system_change(UNUSED struct DjuiBase* base) {
    djui_base_set_visible(&sRectPort->base, (configNetworkSystem == NS_SOCKET));
    djui_base_set_visible(&sRectPassword->base, (configNetworkSystem == NS_COOPNET));
    djui_base_set_enabled(&sInputboxPort->base, (configNetworkSystem == NS_SOCKET));
    djui_base_set_enabled(&sInputboxPassword->base, (configNetworkSystem == NS_COOPNET));
}
#endif

static bool djui_panel_host_port_valid(void) {
    char* buffer = sInputboxPort->buffer;
    int port = 0;
    while (*buffer != '\0') {
        if (*buffer < '0' || *buffer > '9') { return false; }
        port *= 10;
        port += (*buffer - '0');
        buffer++;
    }
#if __linux__
    return port >= 1024 && port <= 65535;
#else
    return port <= 65535;
#endif
}

static void djui_panel_host_port_text_change(struct DjuiBase* caller) {
    struct DjuiInputbox* sInputboxPort = (struct DjuiInputbox*)caller;
    struct DjuiTheme* theme = gDjuiThemes[configDjuiTheme];
    struct DjuiColor* textColor = &theme->interactables.textColor;
    if (djui_panel_host_port_valid()) {
        djui_inputbox_set_text_color(sInputboxPort, textColor->r, textColor->g, textColor->b, textColor->a);
    } else {
        djui_inputbox_set_text_color(sInputboxPort, 255, 0, 0, 255);
    }
}

#ifdef COOPNET
static void djui_panel_host_password_text_change(UNUSED struct DjuiBase* caller) {
    snprintf(configPassword, 64, "%s", sInputboxPassword->buffer);
    if (strlen(sInputboxPassword->buffer) >= 64) {
        djui_inputbox_set_text(sInputboxPassword, configPassword);
    }
}
#endif

extern void djui_panel_do_host(bool reconnecting, bool playSound);
static void djui_panel_host_do_host(struct DjuiBase* caller) {
    if (!gGameInited) {
        djui_panel_loading_create(caller, djui_panel_host_do_host);
        return;
    }

    if (!djui_panel_host_port_valid()) {
        djui_interactable_set_input_focus(&sInputboxPort->base);
        djui_inputbox_select_all(sInputboxPort);
        return;
    }

    // Doesn't let you host if the player limit is not good
    if (configAmountOfPlayers < 1 || configAmountOfPlayers > MAX_PLAYERS) {
        return;
    }

    configHostPort = atoi(sInputboxPort->buffer);

    if (gNetworkType == NT_SERVER) {
        network_rehost_begin();
    } else if (configNetworkSystem == NS_COOPNET || configAmountOfPlayers == 1 || configHideSocketWarning) {
        network_reset_reconnect_and_rehost();
        djui_panel_do_host(false, true);
    } else {
        djui_panel_host_message_create(caller);
    }
}

void djui_panel_host_create(struct DjuiBase* caller) {
    struct DjuiBase* defaultBase = NULL;
    struct DjuiThreePanel* panel = djui_panel_menu_create(
        (gNetworkType == NT_SERVER) ? DLANG(HOST, SERVER_TITLE) : DLANG(HOST, HOST_TITLE),
        false);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        #ifdef COOPNET
        char* nChoices[] = { DLANG(HOST, DIRECT_CONNECTION), DLANG(HOST, COOPNET) };
        struct DjuiSelectionbox* selectionbox1 = djui_selectionbox_create(body, DLANG(HOST, NETWORK_SYSTEM), nChoices, 2, &configNetworkSystem, djui_panel_host_network_system_change);
        if (gNetworkType == NT_SERVER) {
            djui_base_set_enabled(&selectionbox1->base, false);
        }
        #endif

        struct DjuiRect* rect1 = djui_rect_container_create(body, 32);
        {
            sRectPort = djui_rect_container_create(&rect1->base, 32);
            djui_base_set_location(&sRectPort->base, 0, 0);
            djui_base_set_visible(&sRectPort->base, (configNetworkSystem == NS_SOCKET));
            {
                struct DjuiText* text1 = djui_text_create(&sRectPort->base, DLANG(HOST, PORT));
                djui_base_set_size_type(&text1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
                djui_base_set_color(&text1->base, 220, 220, 220, 255);
                djui_base_set_size(&text1->base, 0.585f, 64);
                djui_base_set_alignment(&text1->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
                djui_text_set_drop_shadow(text1, 64, 64, 64, 100);
                if (gNetworkType == NT_SERVER) {
                    djui_base_set_enabled(&text1->base, false);
                }

                sInputboxPort = djui_inputbox_create(&sRectPort->base, 32);
                djui_base_set_size_type(&sInputboxPort->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
                djui_base_set_size(&sInputboxPort->base, 0.45f, 32);
                djui_base_set_alignment(&sInputboxPort->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
                char portString[32] = { 0 };
                snprintf(portString, 32, "%d", configHostPort);
                djui_inputbox_set_text(sInputboxPort, portString);
                djui_interactable_hook_value_change(&sInputboxPort->base, djui_panel_host_port_text_change);
                if (gNetworkType == NT_SERVER) {
                    djui_base_set_enabled(&sInputboxPort->base, false);
                } else {
                    djui_base_set_enabled(&sInputboxPort->base, (configNetworkSystem == NS_SOCKET));
                }
            }
#ifdef COOPNET
            sRectPassword = djui_rect_container_create(&rect1->base, 32);
            djui_base_set_location(&sRectPassword->base, 0, 0);
            djui_base_set_visible(&sRectPassword->base, (configNetworkSystem == NS_COOPNET));
            {
                struct DjuiText* text1 = djui_text_create(&sRectPassword->base, DLANG(HOST, PASSWORD));
                djui_base_set_size_type(&text1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
                djui_base_set_color(&text1->base, 220, 220, 220, 255);
                djui_base_set_size(&text1->base, 0.585f, 64);
                djui_base_set_alignment(&text1->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
                if (gNetworkType == NT_SERVER) {
                    djui_base_set_enabled(&text1->base, false);
                }

                sInputboxPassword = djui_inputbox_create(&sRectPassword->base, 32);
                sInputboxPassword->passwordChar[0] = '#';
                djui_base_set_size_type(&sInputboxPassword->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
                djui_base_set_size(&sInputboxPassword->base, 0.45f, 32);
                djui_base_set_alignment(&sInputboxPassword->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
                char portPassword[64] = { 0 };
                snprintf(portPassword, 64, "%s", configPassword);
                djui_inputbox_set_text(sInputboxPassword, portPassword);
                djui_interactable_hook_value_change(&sInputboxPassword->base, djui_panel_host_password_text_change);
                if (gNetworkType == NT_SERVER) {
                    djui_base_set_enabled(&sInputboxPassword->base, false);
                } else {
                    djui_base_set_enabled(&sInputboxPassword->base, (configNetworkSystem == NS_COOPNET));
                }
            }
#endif
        }

        struct DjuiRect* rect2 = djui_rect_container_create(body, 32);
        {
            struct DjuiText* text1 = djui_text_create(&rect2->base, DLANG(HOST, SAVE_SLOT));
            djui_base_set_size_type(&text1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_color(&text1->base, 220, 220, 220, 255);
            djui_base_set_size(&text1->base, 0.585f, 64);
            djui_base_set_alignment(&text1->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
            djui_text_set_drop_shadow(text1, 64, 64, 64, 100);

            char starString[64] = { 0 };
            snprintf(starString, 64, "%c x%d - %s", '~' + 1, save_file_get_total_star_count(configHostSaveSlot - 1, 0, 24), configSaveNames[configHostSaveSlot - 1]);
            struct DjuiButton* button1 = djui_button_create(&rect2->base, starString, DJUI_BUTTON_STYLE_NORMAL, djui_panel_host_save_create);
            djui_base_set_size(&button1->base, 0.45f, 32);
            djui_base_set_alignment(&button1->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
        }

        djui_button_create(body, DLANG(HOST, SETTINGS), DJUI_BUTTON_STYLE_NORMAL, djui_panel_host_settings_create);
        djui_button_create(body, DLANG(HOST, MODS), DJUI_BUTTON_STYLE_NORMAL, djui_panel_host_mods_create);

        sBigModText = djui_text_create(body, "");
        djui_base_set_size_type(&sBigModText->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&sBigModText->base, 1.0f, 100);
        djui_base_set_color(&sBigModText->base, 220, 220, 220, 255);
        djui_text_set_drop_shadow(sBigModText, 64, 64, 64, 100);

        sBigModIcon = djui_image_create(&sBigModText->base, exclamation_box_seg8_texture_08015E28, 32, 32, G_IM_FMT_RGBA, G_IM_SIZ_16b);
        f32 cellHeight = sBigModText->font->charHeight * sBigModText->fontScale;
        f32 iconSize = cellHeight * (10.0f / 16.0f);
        djui_base_set_size(&sBigModIcon->base, iconSize, iconSize);
        djui_base_set_alignment(&sBigModIcon->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
        djui_base_set_location(&sBigModIcon->base, 0, (cellHeight - iconSize) / 2.0f);

        struct DjuiRect* rect3 = djui_rect_container_create(body, 64);
        {
            struct DjuiButton* button1 = djui_button_create(&rect3->base, (gNetworkType == NT_SERVER) ? DLANG(MENU, CANCEL) : DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
            djui_base_set_size(&button1->base, 0.485f, 64);
            djui_base_set_alignment(&button1->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);

            struct DjuiButton* button2 = djui_button_create(&rect3->base, (gNetworkType == NT_SERVER) ? DLANG(HOST, APPLY) : DLANG(HOST, HOST), DJUI_BUTTON_STYLE_NORMAL, djui_panel_host_do_host);
            djui_base_set_size(&button2->base, 0.485f, 64);
            djui_base_set_alignment(&button2->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
            sHostButton = button2;

            defaultBase = (gNetworkType == NT_SERVER || djui_host_blocked_by_mod_size())
                        ? &button1->base
                        : &button2->base;
        }
    }

    sBigModState = -1;
    panel->base.on_render_pre = djui_panel_host_on_render_pre;

    djui_panel_add(caller, panel, defaultBase);
}
