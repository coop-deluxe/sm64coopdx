#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "custom_menu.h"
#include "custom_menu_system.h"
#include "pc/network/network.h"

#include "pc/configfile.h"
#include "pc/controller/controller_keyboard.h"
#include "game/object_list_processor.h"
#include "game/object_helpers.h"
#include "game/ingame_menu.h"
#include "game/game_init.h"
#include "game/segment2.h"
#include "object_fields.h"
#include "model_ids.h"
#include "behavior_data.h"

#define MAIN_MENU_HEADER_TEXT "SM64 COOP"

char gConnectionJoinError[128] = { 0 };
char gConnectionText[128] = { 0 };
struct CustomMenu* sConnectMenu = NULL;
u8 gOpenConnectMenu = FALSE;
s8 sGotoGame = 0;

static void menu_main_draw_strings(void) {
    print_generic_ascii_string(98, 150, "Still in early development.");
    u8 red = (gGlobalTimer % 20 > 10) ? 0 : 222;
    if (gGlobalTimer > 200) { red = 222; }
    gDPSetEnvColor(gDisplayListHead++, 222, red, red, gMenuStringAlpha);
    print_generic_ascii_string(50, 55, "Levels after Bowser 1 don't synchronize yet.");
}

static void host_menu_draw_strings(void) {
    // set up server setting strings
    char* buttonText[4];
    buttonText[0] = (configNetworkSystem == 0) ? "Host through Discord." : "Host direct connection.";
    switch (configPlayerInteraction) {
        case 0:  buttonText[1] = "Non-solid players."; break;
        case 1:  buttonText[1] = "Solid players.";     break;
        case 2:  buttonText[1] = "Friendly fire.";     break;
        default: buttonText[1] = "UNKNOWN";            break;
    }
    if (configPlayerKnockbackStrength <= 20) {
        buttonText[2] = "Weak knockback.";
    } else if (configPlayerKnockbackStrength <= 40) {
        buttonText[2] = "Normal knockback.";
    } else {
        buttonText[2] = "Too much knockback.";
    }

    buttonText[3] = configStayInLevelAfterStar ? "Stay in level after star." : "Leave level after star.";

    // display server setting strings
    for (int i = 0; i < 4; i++) {
        print_generic_ascii_string(95, 158 + -35 * i, buttonText[i]);
    }

    // display direct connection warning
    if (configNetworkSystem != 0) {
        print_generic_ascii_string(0, 30, "For direct connections -");
        f32 red = (f32)fabs(sin(gGlobalTimer / 20.0f));
        gDPSetEnvColor(gDisplayListHead++, 222, 222 * red, 222 * red, gMenuStringAlpha);
        char warning[128];
        snprintf(warning, 127, "You must forward port '%d' in your router or use Hamachi.", configHostPort);
        print_generic_ascii_string(0, 15, warning);

    }
}

static void host_menu_do_host(void) {
    if (configNetworkSystem == 0) {
        network_set_system(NS_DISCORD);
    }
    else {
        network_set_system(NS_SOCKET);
    }
    custom_menu_close_system();
}

static void host_menu_setting_network_system(void) {
    configNetworkSystem = (configNetworkSystem == 0) ? 1 : 0;
}

static void host_menu_setting_interaction(void) {
    switch (configPlayerInteraction) {
        case 0: configPlayerInteraction = 1; break;
        case 1: configPlayerInteraction = 2; break;
        default: configPlayerInteraction = 0; break;
    }
}

static void host_menu_setting_knockback(void) {
    if (configPlayerKnockbackStrength <= 20) {
        configPlayerKnockbackStrength = 25;
    } else if (configPlayerKnockbackStrength <= 40) {
        configPlayerKnockbackStrength = 75;
    } else {
        configPlayerKnockbackStrength = 10;
    }
}

static void host_menu_setting_stay_in_level(void) {
    configStayInLevelAfterStar = (configStayInLevelAfterStar == 0) ? 1 : 0;
}

static void join_menu_draw_strings(void) {
    print_generic_ascii_string(30, 155, "Accept a Discord game invite in order to join.");
    print_generic_ascii_string(30, 130, "For direct connections, click connect to type in an IP.");
}

static void connect_menu_draw_strings(void) {
    if (gNetworkType == NT_CLIENT) {
        f32 alpha = (f32)fabs(sin(gGlobalTimer / 20.0f));
        gDPSetEnvColor(gDisplayListHead++, 222, 222, 222, gMenuStringAlpha * alpha);
        print_generic_ascii_string(130, 130, "Connecting...");
        return;
    }

    if (*gConnectionJoinError) {
        f32 red = (f32)fabs(sin(gGlobalTimer / 20.0f));
        gDPSetEnvColor(gDisplayListHead++, 222, 222 * red, 222 * red, gMenuStringAlpha);
        print_generic_ascii_string(30, 130, gConnectionJoinError);
        return;
    }

    print_generic_ascii_string(30, 175, "Type in or paste the host's IP.");
    print_generic_ascii_string(30, 160, "Note - the host must forward a port on their router.");

    if (keyboard_in_text_input()) {
        if (strlen(gTextInput) >= 7) {
            print_generic_ascii_string(30, 100, "Press (ENTER) to connect.");
        } else {
            print_generic_ascii_string(30, 100, "Press (ESC) to cancel.");
        }
    }

    gDPSetEnvColor(gDisplayListHead++, 130, 222, 140, gMenuStringAlpha);
    print_generic_ascii_string(30, 130, gTextInput);
}

static void connect_menu_on_connection_attempt(void) {
    keyboard_stop_text_input();
    if (gNetworkType != NT_NONE) { return; }

    char delims[2] = " ";

    // copy input
    char buffer[MAX_TEXT_INPUT] = { 0 };
    strncpy(buffer, gTextInput, MAX_TEXT_INPUT);
    char* text = buffer;

    // trim whitespace
    while (*text == ' ') { text++; }

    // grab IP
    char* ip = strtok(text, delims);
    if (ip == NULL) { custom_menu_close(); return; }
    strncpy(configJoinIp, ip, MAX_CONFIG_STRING);

    // grab port
    char* port = strtok(NULL, delims);
    if (port != NULL) {
        unsigned int intPort = atoi(port);
        if (intPort == 0) { custom_menu_close(); return; }
        configJoinPort = intPort;
    }
    else {
        configJoinPort = DEFAULT_PORT;
    }

    network_set_system(NS_SOCKET);
    network_init(NT_CLIENT);

}

static void connect_menu_on_click(void) {
    gConnectionJoinError[0] = '\0';

    keyboard_start_text_input(TIM_IP, custom_menu_close, connect_menu_on_connection_attempt);

    // fill in our last attempt
    if (configJoinPort == 0) { configJoinPort = DEFAULT_PORT; }
    sprintf(gTextInput, "%s %d", configJoinIp, configJoinPort);

}

static void connect_menu_on_close(void) {
    keyboard_stop_text_input();
    network_shutdown();
}

void custom_menu_init(struct CustomMenu* head) {

    // set the header text
    head->me->label = calloc(strlen(MAIN_MENU_HEADER_TEXT) + 1, sizeof(char));
    strcpy(head->me->label, MAIN_MENU_HEADER_TEXT);

    // set main menu settings
    head->headerY = 55;
    head->draw_strings = menu_main_draw_strings;

    // create sub menus and buttons
    struct CustomMenu* hostMenu = custom_menu_create(head, "HOST", -266, 0);
    hostMenu->draw_strings = host_menu_draw_strings;
    custom_menu_create_button(hostMenu, "CANCEL", 700, -400 + (250 * 3), custom_menu_close);
    custom_menu_create_button(hostMenu, "HOST", 700, -400, host_menu_do_host);
    custom_menu_create_button(hostMenu, "", -700, -400 + (250 * 3), host_menu_setting_network_system);
    custom_menu_create_button(hostMenu, "", -700, -400 + (250 * 2), host_menu_setting_interaction);
    custom_menu_create_button(hostMenu, "", -700, -400 + (250 * 1), host_menu_setting_knockback);
    custom_menu_create_button(hostMenu, "", -700, -400 + (250 * 0), host_menu_setting_stay_in_level);

    struct CustomMenu* joinMenu = custom_menu_create(head, "JOIN", 266, 0);
    custom_menu_create_button(joinMenu, "CANCEL", -266, -320, custom_menu_close);
    joinMenu->draw_strings = join_menu_draw_strings;

    struct CustomMenu* connectMenu = custom_menu_create(joinMenu, "CONNECT", 266, -320);
    connectMenu->me->on_click = connect_menu_on_click;
    connectMenu->on_close = connect_menu_on_close;
    connectMenu->draw_strings = connect_menu_draw_strings;
    custom_menu_create_button(connectMenu, "CANCEL", 0, -400, custom_menu_close);
    sConnectMenu = connectMenu;
}

void custom_menu_loop(void) {
    // we've received an event that makes us exit the menus
    if (sGotoGame) { sSelectedFileNum = sGotoGame; }

    // force-start the load when command-line server hosting
    if (gNetworkType == NT_SERVER && sSelectedFileNum == 0) {
        sSelectedFileNum = 1;
    }

    if (gOpenConnectMenu && sConnectMenu != NULL) {
        gOpenConnectMenu = FALSE;
        custom_menu_open(sConnectMenu);
    }
}

void custom_menu_on_load_save_file(s8 saveFileNum) {
    if (gNetworkType != NT_CLIENT && saveFileNum != 0) {
        configHostSaveSlot = saveFileNum;
        network_init(NT_SERVER);
    }
}

void custom_menu_goto_game(s16 saveFileNum) {
    sGotoGame = saveFileNum;
}