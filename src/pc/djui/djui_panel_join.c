#include <stdio.h>
#include "djui.h"
#include "src/pc/network/network.h"
#include "src/pc/network/socket/socket.h"
#include "src/pc/network/socket/domain_res.h"
#include "src/pc/utils/misc.h"
#include "src/pc/configfile.h"
#include "src/pc/debuglog.h"

#ifdef DISCORD_SDK
static char* sJoiningDiscord = "\
To join a \\#d0d0ff\\Discord\\#c8c8c8\\ lobby:\n\n\
Keep the game open and click the join button on the invite.\n\n\
If the invite says that the game has ended, click the name of the person that sent the invite to refresh it.\
";
#endif

static char* sJoiningDirect = "\
Enter \\#d0d0ff\\direct connection\\#c8c8c8\\ IP and port:\
";

static struct DjuiInputbox* sInputboxIp = NULL;

static bool djui_panel_join_ip_parse_numbers(char** msg) {
    int num = 0;
    for (int i = 0; i < 3; i++) {
        char c = **msg;
        if (c >= '0' && c <= '9') {
            // is number
            num *= 10;
            num += (c - '0');
            *msg = *msg + 1;
        } else if (i == 0) {
            return false;
        } else {
            break;
        }
    }

    return num >= 0 && num <= 255;
}

static bool djui_panel_join_ip_parse_period(char** msg) {
    char c = **msg;
    bool isPeriod = (c == '.');
    if (isPeriod) { *msg = *msg + 1; }
    return isPeriod;
}

static bool djui_panel_join_ip_parse_spacer(char** msg) {
    char c = **msg;
    bool isSpacer = (c == ':' || c == ' ');
    if (isSpacer) { *msg = *msg + 1; }
    return isSpacer;
}

static bool djui_panel_join_ip_parse_port(char** msg) {
    int port = 0;
    for (int i = 0; i < 5; i++) {
        char c = **msg;
        if (c >= '0' && c <= '9') {
            // is number
            port *= 10;
            port += (c - '0');
            *msg = *msg + 1;
        } else if (i == 0) {
            return false;
        } else {
            break;
        }
    }

    return port <= 65535;
}

static bool djui_panel_join_ip_valid(char* buffer) {
    char** msg = &buffer;

    if (!djui_panel_join_ip_parse_numbers(msg)) { return false; }
    if (!djui_panel_join_ip_parse_period(msg))  { return false; }
    if (!djui_panel_join_ip_parse_numbers(msg)) { return false; }
    if (!djui_panel_join_ip_parse_period(msg))  { return false; }
    if (!djui_panel_join_ip_parse_numbers(msg)) { return false; }
    if (!djui_panel_join_ip_parse_period(msg))  { return false; }
    if (!djui_panel_join_ip_parse_numbers(msg)) { return false; }
    if (djui_panel_join_ip_parse_spacer(msg)) {
        if (!djui_panel_join_ip_parse_port(msg)) { return false; }
    }

    return (**msg == '\0');
}

static void djui_panel_join_ip_text_change(struct DjuiBase* caller) {
    struct DjuiInputbox* inputbox1 = (struct DjuiInputbox*)caller;
    if (strlen(inputbox1->buffer) > 2) {
        djui_inputbox_set_text_color(inputbox1, 0, 0, 0, 255);
    } else {
        djui_inputbox_set_text_color(inputbox1, 255, 0, 0, 255);
    }
}

static void djui_panel_join_ip_text_set_new(void) {
    char buffer[256] = { 0 };
    if (snprintf(buffer, 256, "%s", sInputboxIp->buffer) < 0) {
        LOG_INFO("truncating IP");
    }

    bool afterSpacer = false;
    int port = 0;
    for (int i = 0; i < 256; i++) {
        if (buffer[i] == ' ' || buffer[i] == ':') {
            buffer[i] = '\0';
            afterSpacer = true;
        } else if (buffer[i] == '\0') {
            break;
        } else if (afterSpacer && buffer[i] >= '0' && buffer[i] <= '9') {
            port *= 10;
            port += buffer[i] - '0';
        }
    }

    snprintf(gGetHostName, MAX_CONFIG_STRING, "%s", buffer);
    if (snprintf(configJoinIp, MAX_CONFIG_STRING, "%s", buffer) < 0) {
        LOG_INFO("truncating IP");
    }
    if (port >= 1 && port <= 65535) {
        configJoinPort = port;
    } else {
        configJoinPort = DEFAULT_PORT;
    }
}

static void djui_panel_join_ip_text_set(struct DjuiInputbox* inputbox1) {
    char buffer[256] = { 0 };
    if (strlen(configJoinIp) > 0 && configJoinPort != DEFAULT_PORT) {
        if (snprintf(buffer, 256, "%s:%d", configJoinIp, configJoinPort) < 0) { LOG_INFO("truncating IP"); }
    } else if (strlen(configJoinIp) > 0) {
        if (snprintf(buffer, 256, "%s", configJoinIp) < 0) { LOG_INFO("truncating IP"); }
    } else {
        if (snprintf(buffer, 256, "localhost") < 0) { LOG_INFO("truncating IP"); }
    }

    djui_inputbox_set_text(inputbox1, buffer);
}

void djui_panel_join_do_join(struct DjuiBase* caller) {
    if (!(strlen(sInputboxIp->buffer) > 2)) {
        djui_interactable_set_input_focus(&sInputboxIp->base);
        djui_inputbox_select_all(sInputboxIp);
        return;
    }
    network_reset_reconnect_and_rehost();
    djui_panel_join_ip_text_set_new();
    network_set_system(NS_SOCKET);
    network_init(NT_CLIENT);
    djui_panel_join_message_create(caller);
}

void djui_panel_join_create(struct DjuiBase* caller) {
    f32 bodyHeight = 2 + 32 + 16 * 2 + 64;

    u16 directLines = 1;
    f32 directTextHeight = 32 * 0.8125f * directLines + 8;
    bodyHeight += directTextHeight + 16;

#ifdef DISCORD_SDK
    u16 discordLines = 8;
    f32 discordTextHeight = 32 * 0.8125f * discordLines + 8;
    bodyHeight += discordTextHeight + 16;
#endif

    struct DjuiBase* defaultBase = NULL;
    struct DjuiThreePanel* panel = djui_panel_menu_create(bodyHeight, "\\#ff0800\\J\\#1be700\\O\\#00b3ff\\I\\#ffef00\\N");
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);
    {
#ifdef DISCORD_SDK
        struct DjuiText* text1 = djui_text_create(&body->base, sJoiningDiscord);
        djui_base_set_size_type(&text1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&text1->base, 1.0f, discordTextHeight);
        djui_base_set_color(&text1->base, 200, 200, 200, 255);
#endif
        struct DjuiRect* rect1 = djui_rect_create(&body->base);
        djui_base_set_size_type(&rect1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&rect1->base, 1.0f, 2);
        djui_base_set_color(&rect1->base, 150, 150, 150, 255);

        struct DjuiText* text2 = djui_text_create(&body->base, sJoiningDirect);
        djui_base_set_size_type(&text2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&text2->base, 1.0f, directTextHeight);
        djui_base_set_color(&text2->base, 200, 200, 200, 255);

        struct DjuiInputbox* inputbox1 = djui_inputbox_create(&body->base, 256);
        djui_base_set_size_type(&inputbox1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&inputbox1->base, 1.0f, 32.0f);
        djui_interactable_hook_value_change(&inputbox1->base, djui_panel_join_ip_text_change);
        sInputboxIp = inputbox1;
        djui_panel_join_ip_text_set(inputbox1);

        struct DjuiRect* rect2 = djui_rect_create(&body->base);
        djui_base_set_size_type(&rect2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&rect2->base, 1.0f, 64);
        djui_base_set_color(&rect2->base, 0, 0, 0, 0);
        {
            struct DjuiButton* button1 = djui_button_create(&rect2->base, "Back");
            djui_base_set_size_type(&button1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button1->base, 0.485f, 64);
            djui_base_set_alignment(&button1->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
            djui_button_set_style(button1, 1);
            djui_interactable_hook_click(&button1->base, djui_panel_menu_back);

            struct DjuiButton* button2 = djui_button_create(&rect2->base, "Join");
            djui_base_set_size_type(&button2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button2->base, 0.485f, 64);
            djui_base_set_alignment(&button2->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
            djui_interactable_hook_click(&button2->base, djui_panel_join_do_join);
            defaultBase = &button2->base;
        }
    }

    djui_panel_add(caller, &panel->base, defaultBase);
}
