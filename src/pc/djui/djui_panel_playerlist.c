#include <string.h>

#include "pc/network/network.h"
#include "djui.h"
#include "djui_panel_playerlist.h"
#include "src/pc/utils/misc.h"
#include "src/pc/configfile.h"
#include "game/mario_misc.h"

struct DjuiThreePanel* gDjuiPlayerList = NULL;

static struct DjuiFlowLayout* djuiRow[MAX_PLAYERS] = { 0 };
static struct DjuiImage* djuiImages[MAX_PLAYERS] = { 0 };
static struct DjuiText* djuiTextNames[MAX_PLAYERS] = { 0 };
static struct DjuiText* djuiTextLocations[MAX_PLAYERS] = { 0 };

extern u8 seg2_course_name_table[];
extern u8 seg2_act_name_table[];

static char stage[188];
static char act[188];

static const char charset[0xFF + 1] = {
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 7
    ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', // 15
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', // 23
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v', // 31
    'w', 'x', 'y', 'z', ' ', ' ', ' ', ' ', // 39
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 49
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 55
    ' ', ' ', ' ', ' ', ' ', ' ', '\'', ' ', // 63
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 71
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 79
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 87
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 95
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 103
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ',', // 111
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 119
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 127
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 135
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 143
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 151
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', '-', // 159
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 167
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 175
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 183
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 192
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 199
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 207
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 215
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 223
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 231
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // 239
    ' ', ' ', '!', ' ', ' ', ' ', ' ', ' ', // 247
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '  // 255
};

static void convert_string(const u8* str, char* output) {
    s32 strPos = 0;
    bool capitalizeChar = true;

    while (str[strPos] != 0xFF) {
        if (str[strPos] < 0xFF) {
            output[strPos] = charset[str[strPos]];

            // if the char is a letter we can capatalize it
            if (capitalizeChar && 0x0A <= str[strPos] && str[strPos] <= 0x23) {
                output[strPos] -= ('a' - 'A');
                capitalizeChar = false;
            }

        }
        else {
            output[strPos] = ' ';
        }

        // decide if the next character should be capitalized
        switch (output[strPos]) {
        case ' ':
            //if (str[strPos] != 158)
                //fprintf(stdout, "Unknown Character (%i)\n", str[strPos]); // inform that an unknown char was found
        case '-':
            capitalizeChar = true;
            break;
        default:
            capitalizeChar = false;
            break;
        }

        strPos++;
    }

    output[strPos] = '\0';
}

static void set_details(s16 courseNum, s16 levelNum, s16 areaIndex) {
    // overrides for castle locations
    if (courseNum == 0 && levelNum == 16) {
        strcpy(stage, "Castle Grounds");
        return;
    }
    if (courseNum == 0 && levelNum == 6) {
        if (areaIndex == 1) {
            strcpy(stage, "Castle Main Floor");
            return;
        } else if (areaIndex == 2) {
            strcpy(stage, "Castle Upper Floor");
            return;
        } else if (areaIndex == 3) {
            strcpy(stage, "Castle Basement");
            return;
        }
    }
    if (courseNum == 0 && levelNum == 26) {
        strcpy(stage, "Castle Courtyard");
        return;
    }

    // If we are in in Course 0 we are in the castle which doesn't have a string
    if (courseNum) {
        void** courseNameTbl;

#ifndef VERSION_EU
        courseNameTbl = segmented_to_virtual(seg2_course_name_table);
#else
        switch (gInGameLanguage) {
        case LANGUAGE_ENGLISH:
            courseNameTbl = segmented_to_virtual(course_name_table_eu_en);
            break;
        case LANGUAGE_FRENCH:
            courseNameTbl = segmented_to_virtual(course_name_table_eu_fr);
            break;
        case LANGUAGE_GERMAN:
            courseNameTbl = segmented_to_virtual(course_name_table_eu_de);
            break;
        }
#endif
        u8* courseName = segmented_to_virtual(courseNameTbl[courseNum - 1]);

        convert_string(&courseName[3], stage);
    } else {
        strcpy(stage, "Peach's Castle");
    }
}

static void playerlist_update_row(u8 i, struct NetworkPlayer* np) {
    u8 charIndex = np->modelIndex;
    if (charIndex >= CT_MAX) { charIndex = 0; }
    djuiImages[i]->texture = gCharacters[charIndex].hudHeadTexture;

    set_details(np->currCourseNum, np->currLevelNum, np->currAreaIndex);
    djui_base_set_visible(&djuiRow[i]->base, np->connected);

    u8* rgb = get_player_color(np->paletteIndex, 0);
    djui_base_set_color(&djuiTextNames[i]->base, rgb[0], rgb[1], rgb[2], 255);
    djui_text_set_text(djuiTextNames[i], np->name);

    djui_text_set_text(djuiTextLocations[i], stage);
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
