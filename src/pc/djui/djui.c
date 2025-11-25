#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_main.h"
#include "djui_panel_language.h"
#include "djui_panel_pause.h"
#include "djui_panel_join.h"
#include "djui_panel_join_message.h"
#include "djui_ctx_display.h"
#include "djui_fps_display.h"
#include "djui_lua_profiler.h"
#include "../debuglog.h"
#include "pc/cliopts.h"
#include "game/level_update.h"
#include "pc/lua/smlua_hooks.h"
#include "djui_panel_playerlist.h"
#include "djui_hud_utils.h"
#include "engine/math_util.h"
#include "pc/utils/misc.h"

static Gfx* sSavedDisplayListHead = NULL;
static Gfx* sHookHudRenderGfx = NULL;
static size_t sHookHudRenderGfxSize = 0;

struct DjuiRoot* gDjuiRoot = NULL;
struct DjuiText* gDjuiPauseOptions = NULL;
struct DjuiText* gDjuiModReload = NULL;
static struct DjuiText* sDjuiLuaError = NULL;
static u32 sDjuiLuaErrorTimeout = 0;
bool gDjuiInMainMenu = true;
bool gDjuiInPlayerMenu = false;
bool gDjuiDisabled = false;
bool gDjuiShuttingDown = false;
bool gDjuiChangingTheme = false;
static bool sDjuiInited = false;
static struct DjuiRoot* sDjuiRootBehind = NULL;

bool sDjuiRendered60fps = false;

void djui_shutdown(void) {
    gDjuiShuttingDown = true;
    djui_panel_shutdown();

    sSavedDisplayListHead = NULL;
    if (gDjuiPauseOptions) djui_base_destroy(&gDjuiPauseOptions->base);
    if (gDjuiModReload) djui_base_destroy(&gDjuiModReload->base);
    if (sDjuiLuaError) djui_base_destroy(&sDjuiLuaError->base);
    gDjuiPauseOptions = NULL;
    gDjuiModReload = NULL;
    sDjuiLuaError = NULL;
    sDjuiLuaErrorTimeout = 0;

    if (gDjuiConsole) {
        djui_base_destroy(&gDjuiConsole->base);
        gDjuiConsole = NULL;
    }
    extern u32 sDjuiConsoleMessages;
    sDjuiConsoleMessages = 0;

    if (gDjuiRoot) {
        djui_base_destroy(&gDjuiRoot->base);
    }

    djui_fps_display_destroy();
    djui_ctx_display_destroy();
    djui_lua_profiler_destroy();

    gDjuiShuttingDown = false;
    sDjuiInited = false;
}

void patch_djui_before(void) {
    sDjuiRendered60fps = false;
    sSavedDisplayListHead = NULL;
}

void patch_djui_interpolated(UNUSED f32 delta) {
    extern f32 gFramePercentage;
    if (gDjuiInMainMenu || gDjuiPanelPauseCreated) {
        if (gFramePercentage >= 0.5f && !sDjuiRendered60fps) {
            // reset the head and re-render DJUI
            sDjuiRendered60fps = true;
            if (sSavedDisplayListHead == NULL) { return; }
            gDisplayListHead = sSavedDisplayListHead;
            djui_render();
            gDPFullSync(gDisplayListHead++);
            gSPEndDisplayList(gDisplayListHead++);
        } else {
            // patch the display list instead of a full re-render
            // to make some elements on screen be smooth, while keeping things cheap.
            Gfx* displayListHead = gDisplayListHead;
            djui_cursor_interp();
            gDisplayListHead = displayListHead;
        }
    }
}

void djui_init(void) {
    gDjuiRoot = djui_root_create();
    sDjuiRootBehind = djui_root_create();

    gDjuiPauseOptions = djui_text_create(&sDjuiRootBehind->base, DLANG(MISC, R_BUTTON));
    djui_base_set_size_type(&gDjuiPauseOptions->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(&gDjuiPauseOptions->base, 1.0f, 32);
    djui_base_set_location(&gDjuiPauseOptions->base, 0, 16);
    djui_text_set_alignment(gDjuiPauseOptions, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);

    gDjuiModReload = djui_text_create(&sDjuiRootBehind->base, DLANG(MISC, L_BUTTON));
    djui_text_set_drop_shadow(gDjuiModReload, 0, 0, 0, 255);
    djui_base_set_color(&gDjuiModReload->base, 255, 32, 32, 255);
    djui_base_set_size_type(&gDjuiModReload->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(&gDjuiModReload->base, 1.0f, 32);
    djui_base_set_location(&gDjuiModReload->base, 0, 64);
    djui_text_set_alignment(gDjuiModReload, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
    djui_base_set_visible(&gDjuiModReload->base, false);

    sDjuiLuaError = djui_text_create(&gDjuiRoot->base, "");
    djui_base_set_size_type(&sDjuiLuaError->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(&sDjuiLuaError->base, 1.0f, 32);
    djui_base_set_location(&sDjuiLuaError->base, 0, 64);
    djui_text_set_drop_shadow(sDjuiLuaError, 0, 0, 0, 255);
    djui_text_set_alignment(sDjuiLuaError, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
    djui_base_set_visible(&sDjuiLuaError->base, false);
    djui_base_set_color(&sDjuiLuaError->base, 255, 0, 0, 255);

    djui_panel_playerlist_create(NULL);

    djui_console_create();

    djui_fps_display_create();
    djui_ctx_display_create();
    djui_lua_profiler_create();

    sDjuiInited = true;
}

void djui_init_late(void) {
    djui_panel_main_create(NULL);
    if (configLanguage[0] == '\0') {
        gPanelLanguageOnStartup = true;
        djui_panel_language_create(NULL);
    }

    // djui_panel_debug_create();
    djui_cursor_create();
}

void djui_connect_menu_open(void) {
    djui_panel_shutdown();
    gDjuiInMainMenu = true;
    djui_panel_main_create(NULL);
    djui_panel_join_create(NULL);
    djui_panel_join_message_create(NULL);
}

void djui_lua_error(char* text, struct DjuiColor color) {
    if (!sDjuiLuaError) { return; }
    djui_base_set_color(&sDjuiLuaError->base, color.r, color.g, color.b, color.a);
    djui_text_set_text(sDjuiLuaError, text);
    djui_base_set_visible(&sDjuiLuaError->base, true);
    sDjuiLuaErrorTimeout = 30 * 5;
}

void djui_lua_error_clear(void) {
    sDjuiLuaErrorTimeout = 0;
    djui_base_set_visible(&sDjuiLuaError->base, false);
}

void djui_reset_hud_params(void) {
    djui_hud_set_resolution(RESOLUTION_DJUI);
    djui_hud_set_font(FONT_NORMAL);
    djui_hud_set_rotation(0, 0, 0);
    djui_hud_reset_color();
    djui_hud_set_filter(FILTER_NEAREST);
    djui_hud_reset_viewport();
    djui_hud_reset_scissor();
}

void djui_render(void) {
    if (!sDjuiInited || gDjuiDisabled) { return; }

    sSavedDisplayListHead = gDisplayListHead;
    gDjuiHudUtilsZ = 0;
    djui_reset_hud_params();

    create_dl_ortho_matrix();
    djui_gfx_displaylist_begin();

    if (sDjuiRootBehind != NULL && (sCurrPlayMode == PLAY_MODE_PAUSED) && !gDjuiPanelPauseCreated) {
        djui_base_render(&sDjuiRootBehind->base);
    }

    // To maintain consistency with other hooks, HOOK_ON_HUD_RENDER must run at 30 fps
    // During interpolated frames, copy the generated display list without running the hook again
    if (!sDjuiRendered60fps) {
        Gfx *hookHudRenderStart = gDisplayListHead;
        smlua_call_event_hooks(HOOK_ON_HUD_RENDER, djui_reset_hud_params);
        size_t gfxSize = sizeof(Gfx) * (gDisplayListHead - hookHudRenderStart);
        if (gfxSize > 0) {
            if (gfxSize > sHookHudRenderGfxSize) {
                sHookHudRenderGfx = realloc(sHookHudRenderGfx, gfxSize);
            }
            memcpy(sHookHudRenderGfx, hookHudRenderStart, gfxSize);
        }
        sHookHudRenderGfxSize = gfxSize;
    } else if (sHookHudRenderGfx != NULL && sHookHudRenderGfxSize > 0) {
        memcpy(gDisplayListHead, sHookHudRenderGfx, sHookHudRenderGfxSize);
        gDisplayListHead += sHookHudRenderGfxSize / sizeof(Gfx);
    }

    djui_panel_update();
    djui_popup_update();

    djui_lua_profiler_render();

    if (gDjuiRoot != NULL) {
        djui_base_render(&gDjuiRoot->base);
    }

    djui_fps_display_render();
    djui_ctx_display_render();

    if (sDjuiLuaErrorTimeout > 0) {
        sDjuiLuaErrorTimeout--;
        if (sDjuiLuaErrorTimeout == 0) {
            djui_base_set_visible(&sDjuiLuaError->base, false);
        }
    }

    djui_cursor_update();
    djui_base_render(&gDjuiConsole->base);

    // Be careful! Djui interactables update at 30hz to avoid display list corruption.
    if (!sDjuiRendered60fps) {
        djui_interactable_update();
    }

    djui_gfx_displaylist_end();
}
