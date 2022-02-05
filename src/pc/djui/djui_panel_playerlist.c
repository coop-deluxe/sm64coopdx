#include <string.h>

#include "djui.h"
#include "djui_panel_playerlist.h"
#include "game/level_info.h"
#include "game/mario_misc.h"
#include "pc/configfile.h"
#include "pc/network/network.h"
#include "pc/utils/misc.h"

struct DjuiThreePanel* gDjuiPlayerList = NULL;

static struct DjuiFlowLayout* djuiRow[MAX_PLAYERS] = { 0 };
static struct DjuiImage* djuiImages[MAX_PLAYERS] = { 0 };
static struct DjuiText* djuiTextNames[MAX_PLAYERS] = { 0 };
static struct DjuiText* djuiTextLocations[MAX_PLAYERS] = { 0 };

static void playerlist_update_row(u8 i, struct NetworkPlayer* np) {
    u8 charIndex = np->modelIndex;
    if (charIndex >= CT_MAX) { charIndex = 0; }
    djuiImages[i]->texture = gCharacters[charIndex].hudHeadTexture;

    u8 visible = np->connected;
    if (np == gNetworkPlayerServer && gServerSettings.headlessServer) {
        visible = false;
    }

    djui_base_set_visible(&djuiRow[i]->base, visible);

    u8* rgb = network_get_player_text_color(np->localIndex);
    djui_base_set_color(&djuiTextNames[i]->base, rgb[0], rgb[1], rgb[2], 255);
    djui_text_set_text(djuiTextNames[i], np->name);

    djui_text_set_text(djuiTextLocations[i], get_level_name(np->currCourseNum, np->currLevelNum, np->currAreaIndex));
}

void djui_panel_playerlist_on_render_pre(UNUSED struct DjuiBase* base, UNUSED bool* skipRender) {
    int j = 0;
    for (int i = 0; i < MAX_PLAYERS; i++) {
        struct NetworkPlayer* np = &gNetworkPlayers[i];
        if (!np->connected) { continue; }
        playerlist_update_row(j++, np);
    }

    while (j < MAX_PLAYERS) {
        djui_base_set_visible(&djuiRow[j]->base, false);
        j++;
    }
}

void djui_panel_playerlist_create(UNUSED struct DjuiBase* caller) {
    f32 bodyHeight = (MAX_PLAYERS * 32) + (MAX_PLAYERS - 1) * 4;

    struct DjuiThreePanel* panel = djui_panel_menu_create(bodyHeight, "\\#ff0800\\P\\#1be700\\L\\#00b3ff\\A\\#ffef00\\Y\\#ff0800\\E\\#1be700\\R\\#00b3ff\\S");
    gDjuiPlayerList = panel;
    panel->base.on_render_pre = djui_panel_playerlist_on_render_pre;
    djui_base_set_alignment(&panel->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
    djui_base_set_size_type(&panel->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(&panel->base, 580, bodyHeight + (32 + 16) + 32 + 32);
    djui_base_set_visible(&panel->base, false);
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);
    djui_flow_layout_set_margin(body, 4);

    for (int i = 0; i < MAX_PLAYERS; i++) {
        struct DjuiFlowLayout* row = djui_flow_layout_create(&body->base);
        djui_base_set_size_type(&row->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&row->base, 1.0f, 32.0f);
        int v = (i % 2) ? 16 : 32;
        djui_base_set_color(&row->base, v, v, v, 128);
        djui_flow_layout_set_flow_direction(row, DJUI_FLOW_DIR_RIGHT);
        djui_flow_layout_set_margin(row, 8);
        djui_base_set_visible(&row->base, false);
        djuiRow[i] = row;

        extern ALIGNED8 const u8 texture_hud_char_mario_head[];
        struct DjuiImage* i1 = djui_image_create(&row->base, texture_hud_char_mario_head, 16, 16, 8);
        djui_base_set_size(&i1->base, 32, 32);
        djuiImages[i] = i1;

        int t = 220;
        struct DjuiText* t2 = djui_text_create(&row->base, "name");
        djui_base_set_size_type(&t2->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&t2->base, 180, 32.0f);
        djui_base_set_color(&t2->base, t, t, t, 255);
        djuiTextNames[i] = t2;

        struct DjuiText* t3 = djui_text_create(&row->base, "location");
        djui_base_set_size_type(&t3->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&t3->base, 300, 32.0f);
        djui_base_set_color(&t3->base, t, t, t, 255);
        djui_text_set_alignment(t3, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
        djuiTextLocations[i] = t3;
    }
}
