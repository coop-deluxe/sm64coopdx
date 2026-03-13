#include "djui.h"
#include "djui_playerlist_display.h"
#include "pc/network/network.h"
#include "pc/network/network_player.h"
#include "game/level_info.h"

#define PLAYERLIST_MAX_ROWS MAX_PLAYERS
#define PLAYERLIST_ROW_HEIGHT 16
#define PLAYERLIST_WIDTH 200
#define PLAYERLIST_PADDING 4

struct DjuiPlayerlistDisplay {
    struct DjuiText *rows[PLAYERLIST_MAX_ROWS];
    u8 rowCount;
    struct DjuiBase base;
};

static struct DjuiPlayerlistDisplay *sPlayerlistDisplay = NULL;

void djui_playerlist_display_render(void) {
    if (sPlayerlistDisplay == NULL) return;
    if (gNetworkType == NT_NONE) return;

    // Build text for each connected player
    u8 count = 0;
    for (s32 i = 0; i < MAX_PLAYERS && count < PLAYERLIST_MAX_ROWS; i++) {
        struct NetworkPlayer *np = &gNetworkPlayers[i];
        if (!np->connected) continue;

        char buf[128];
        const char *loc = (np->overrideLocation[0] != '\0')
            ? np->overrideLocation
            : get_level_name(np->currCourseNum, np->currLevelNum, np->currAreaIndex);

        // Color: local player in blue, others in white
        bool isSelf = (gNetworkPlayerLocal && np->localIndex == gNetworkPlayerLocal->localIndex);
        if (isSelf) {
            snprintf(buf, sizeof(buf), "\\#55bbff\\%s \\#888888\\%s", np->name, loc);
        } else {
            snprintf(buf, sizeof(buf), "\\#dcdcdc\\%s \\#888888\\%s", np->name, loc);
        }

        djui_text_set_text(sPlayerlistDisplay->rows[count], buf);
        djui_base_set_visible(&sPlayerlistDisplay->rows[count]->base, true);
        count++;
    }

    // Hide unused rows
    for (u8 j = count; j < PLAYERLIST_MAX_ROWS; j++) {
        djui_base_set_visible(&sPlayerlistDisplay->rows[j]->base, false);
    }

    // Resize background to fit visible rows
    f32 totalHeight = count * PLAYERLIST_ROW_HEIGHT + PLAYERLIST_PADDING * 2;
    djui_base_set_size(&sPlayerlistDisplay->base, PLAYERLIST_WIDTH, totalHeight);
    // Position at bottom-left: y = SCREEN_HEIGHT - totalHeight
    djui_base_set_location(&sPlayerlistDisplay->base, 0, 240.0f - totalHeight);

    if (count > 0) {
        djui_rect_render(&sPlayerlistDisplay->base);
        djui_base_render(&sPlayerlistDisplay->base);
    }
}

static void djui_playerlist_display_on_destroy(UNUSED struct DjuiBase *base) {
    free(sPlayerlistDisplay);
    sPlayerlistDisplay = NULL;
}

void djui_playerlist_display_create(void) {
    struct DjuiPlayerlistDisplay *pld = calloc(1, sizeof(struct DjuiPlayerlistDisplay));
    struct DjuiBase *base = &pld->base;
    djui_base_init(NULL, base, NULL, djui_playerlist_display_on_destroy);
    djui_base_set_size(base, PLAYERLIST_WIDTH, PLAYERLIST_ROW_HEIGHT + PLAYERLIST_PADDING * 2);
    djui_base_set_color(base, 0, 0, 0, 200);
    djui_base_set_border_color(base, 0, 0, 0, 160);
    djui_base_set_border_width(base, 4);
    djui_base_set_padding(base, PLAYERLIST_PADDING, PLAYERLIST_PADDING + 4, PLAYERLIST_PADDING, PLAYERLIST_PADDING + 4);

    for (u8 i = 0; i < PLAYERLIST_MAX_ROWS; i++) {
        struct DjuiText *text = djui_text_create(base, "");
        djui_text_set_alignment(text, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
        djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&text->base, 1.0f, PLAYERLIST_ROW_HEIGHT);
        djui_base_set_location(&text->base, 0, i * PLAYERLIST_ROW_HEIGHT);
        djui_text_set_font_scale(text, 0.6f);
        djui_base_set_visible(&text->base, false);
        pld->rows[i] = text;
    }

    sPlayerlistDisplay = pld;
}

void djui_playerlist_display_destroy(void) {
    if (sPlayerlistDisplay) {
        djui_base_destroy(&sPlayerlistDisplay->base);
    }
}
