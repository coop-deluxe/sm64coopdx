#include <string.h>

#include "djui.h"
#include "djui_panel_menu.h"
#include "djui_panel_playerlist.h"
#include "djui_panel_modlist.h"
#include "game/level_info.h"
#include "game/mario_misc.h"
#include "pc/configfile.h"
#include "pc/network/network.h"
#include "pc/utils/misc.h"
#include "pc/network/ban_list.h"

struct DjuiThreePanel* gDjuiPlayerList = NULL;
bool gAttemptingToOpenPlayerlist = false;

static struct DjuiFlowLayout* djuiRow[MAX_PLAYERS] = { 0 };
static struct DjuiImage* djuiImages[MAX_PLAYERS] = { 0 };
static struct DjuiText* djuiTextNames[MAX_PLAYERS] = { 0 };
static struct DjuiText* djuiTextDescriptions[MAX_PLAYERS] = { 0 };
static struct DjuiText* djuiTextLocations[MAX_PLAYERS] = { 0 };
static struct DjuiText* djuiTextAct[MAX_PLAYERS] = { 0 };

static struct DjuiRect* bkButtons[MAX_PLAYERS] = { 0 };
static struct DjuiButton* bkLeftButtons[MAX_PLAYERS] = { 0 };
static struct DjuiButton* bkRightButtons[MAX_PLAYERS] = { 0 };

u8 bki = 0;
struct NetworkPlayer *bknp;

const u8 sPlayerListSize = 16;
u8 sPageIndex = 0;

static u8 bkState = 0;

void ban_kick_buttons_show(u8 i, struct NetworkPlayer *np) {
    djui_base_set_visible(&bkButtons[i]->base, true);
    
    djui_base_set_visible(&djuiTextDescriptions[i]->base, false);
    djui_base_set_visible(&djuiTextLocations[i]->base, false);
    djui_base_set_visible(&djuiTextAct[i]->base, false);

    bknp = np;
    bki = i;
    printf("show #%u\n", i);
}

void ban_kick_buttons_hide(u8 i) {
    djui_base_set_visible(&bkButtons[i]->base, false);
    djui_text_set_text(bkLeftButtons[i]->text, "Kick");
    djui_text_set_text(bkRightButtons[i]->text, "Ban");
    
    djui_base_set_visible(&djuiTextDescriptions[i]->base, true);
    djui_base_set_visible(&djuiTextLocations[i]->base, true);
    djui_base_set_visible(&djuiTextAct[i]->base, true);

    bkState = NONE;
    printf("hide #%u\n", i);
}

void ban_kick_buttons_action(u8 lr) {
    if (!bkState) {
        bkState = lr;

        struct DjuiText *text = ((BK_LEFT) ? bkLeftButtons[bki] : bkRightButtons[bki])->text;
        djui_text_set_text(text, "\\#ffa0a0\\Confirm?");
        if (BK_RIGHT) djui_text_set_text(bkLeftButtons[bki]->text, "Perm Ban");
        return;
    }
    switch (bkState) {
        case KICK:
            if (gNetworkType == NT_SERVER) {
                network_send_kick(bknp->localIndex, EKT_KICKED);
                network_player_disconnected(bknp->localIndex);
            } else {
                network_send_chat_command(bknp->globalIndex, CCC_KICK);
            }
            ban_kick_buttons_hide(bki);
            break;
        case BAN:
            if (BK_RIGHT) {
                if (gNetworkType == NT_SERVER) {
                    network_send_kick(bknp->localIndex, EKT_BANNED);
                    ban_list_add(gNetworkSystem->get_id_str(bknp->localIndex), false);
                    network_player_disconnected(bknp->localIndex);
                } else {
                    network_send_chat_command(bknp->globalIndex, CCC_BAN);
                }
                ban_kick_buttons_hide(bki);
            } else {
                bkState = PERM_BAN;

                djui_text_set_text(bkLeftButtons[bki]->text, "\\#ffa0a0\\Confirm?");
                djui_text_set_text(bkRightButtons[bki]->text, "Go Back");
            }
            break;
        case PERM_BAN:
            if (BK_LEFT) {
                network_send_kick(bknp->localIndex, EKT_BANNED);
                ban_list_add(gNetworkSystem->get_id_str(bknp->localIndex), true);
                network_player_disconnected(bknp->localIndex);
                ban_kick_buttons_hide(bki);
            } else {
                bkState = NONE;

                djui_text_set_text(bkLeftButtons[bki]->text, "Kick");
                djui_text_set_text(bkRightButtons[bki]->text, "Ban");
            }
            break;
    }
}

void left_button_click() { ban_kick_buttons_action(1); };
void right_button_click() { ban_kick_buttons_action(2); };

static void playerlist_update_row(u8 i, struct NetworkPlayer *np) {
    u8 charIndex = np->overrideModelIndex;
    static u8 sPlayer;
    char sActNum[7];

    if (!np->localIndex) sPlayer = 0;
    if (np->currActNum != 99 && np->currActNum != 0) {
        snprintf(sActNum, 7, "# %d", np->currActNum);
    } else if (np->currActNum == 0) {
        snprintf(sActNum, 7, " ");
    } else {
        snprintf(sActNum, 7, "Done");
    }
    if (charIndex >= CT_MAX) { charIndex = 0; }
    djuiImages[i]->texture = gCharacters[charIndex].hudHeadTexture.texture;

    u8 visible = np->connected;
    if (np == gNetworkPlayerServer && gServerSettings.headlessServer) {
        visible = false;
    } else if (sPlayer < sPlayerListSize * sPageIndex) {
        visible = false;
        sPlayer++;
    }

    djui_base_set_visible(&djuiRow[i]->base, visible);
    
    if (np->localIndex && np->globalIndex // don't ban/kick yourself or the host
       && (gNetworkType == NT_SERVER || gNetworkPlayerLocal->moderator) // privilege check
       && visible) { // skip if hidden
        if (djui_cursor_inside_base(&djuiRow[i]->base)) {
            ban_kick_buttons_show(i, np);
        } else if (bkButtons[i]->base.visible) ban_kick_buttons_hide(i);
    }

    u8* rgb = network_get_player_text_color(np->localIndex);
    djui_base_set_color(&djuiTextNames[i]->base, rgb[0], rgb[1], rgb[2], 255);
    djui_text_set_text(djuiTextNames[i], np->name);

    djui_base_set_color(&djuiTextDescriptions[i]->base, np->descriptionR, np->descriptionG, np->descriptionB, np->descriptionA);
    djui_text_set_text(djuiTextDescriptions[i], np->description);

    djui_text_set_text(djuiTextLocations[i], get_level_name(np->currCourseNum, np->currLevelNum, np->currAreaIndex));
    djui_text_set_text(djuiTextAct[i], sActNum);
}

void djui_panel_playerlist_on_render_pre(UNUSED struct DjuiBase* base, UNUSED bool* skipRender) {
    if (gDjuiInMainMenu || gNetworkType == NT_NONE) {
        djui_base_set_visible(&gDjuiPlayerList->base, false);
        djui_base_set_visible(&gDjuiModList->base, false);
        return;
    }

    s32 j = 0;

    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        struct NetworkPlayer *np = &gNetworkPlayers[i];
        if (np->connected) playerlist_update_row(j++, np);
    }

    while (j < MAX_PLAYERS) {
        djui_base_set_visible(&djuiRow[j]->base, false);
        j++;
    }
}

void djui_panel_playerlist_create(UNUSED struct DjuiBase* caller) {
    f32 bodyHeight = (sPlayerListSize * 32) + (sPlayerListSize - 1) * 4;

    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(PLAYER_LIST, PLAYERS), false);
    djui_three_panel_set_body_size(panel, bodyHeight);
    gDjuiPlayerList = panel;
    panel->base.on_render_pre = djui_panel_playerlist_on_render_pre;
    djui_base_set_alignment(&panel->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
    djui_base_set_size_type(&panel->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(&panel->base, 710, bodyHeight + (32 + 16) + 32 + 32);
    djui_base_set_visible(&panel->base, false);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    djui_flow_layout_set_margin((struct DjuiFlowLayout*)body, 4);

    for (u8 i = 0; i < MAX_PLAYERS; i++) {
        struct DjuiFlowLayout* row = djui_flow_layout_create(body);
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
        struct DjuiText* t2 = djui_text_create(&row->base, DLANG(PLAYER_LIST, NAME));
        djui_base_set_size_type(&t2->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&t2->base, 180, 32.0f);
        djui_base_set_color(&t2->base, t, t, t, 255);
        djuiTextNames[i] = t2;

        struct DjuiText* t3 = djui_text_create(&row->base, "");
        djui_base_set_size_type(&t3->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&t3->base, 100, 32.0f);
        djui_base_set_color(&t3->base, 220, 220, 220, 255);
        djui_text_set_alignment(t3, DJUI_HALIGN_CENTER, DJUI_VALIGN_TOP);
        djuiTextDescriptions[i] = t3;

        struct DjuiText* t4 = djui_text_create(&row->base, DLANG(PLAYER_LIST, LOCATION));
        djui_base_set_size_type(&t4->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&t4->base, 300 - 100, 32.0f);
        djui_base_set_color(&t4->base, t, t, t, 255);
        djui_text_set_alignment(t4, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
        djuiTextLocations[i] = t4;

        struct DjuiText* t5 = djui_text_create(&row->base, DLANG(PLAYER_LIST, ACT));
        djui_base_set_size_type(&t5->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&t5->base, 100, 32.0f);
        djui_base_set_color(&t5->base, t, t, t, 255);
        djui_text_set_alignment(t5, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
        djuiTextAct[i] = t5;
        
        struct DjuiRect* t6 = djui_rect_container_create(&row->base, 32);
        struct DjuiButton* l = djui_button_left_create(&t6->base, "Kick", DJUI_BUTTON_STYLE_NORMAL, left_button_click);
        struct DjuiButton* r = djui_button_right_create(&t6->base, "Ban", DJUI_BUTTON_STYLE_NORMAL, right_button_click);
        l->base.height.value = 32.f;
        r->base.height.value = 32.f;
        djui_base_set_visible(&t6->base, false);
        bkButtons[i] = t6;
        bkLeftButtons[i] = l;
        bkRightButtons[i] = r;
    }
}
