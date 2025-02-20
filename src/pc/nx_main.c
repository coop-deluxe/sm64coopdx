#ifdef __SWITCH__
#include <switch.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#include "sm64.h"

#include "pc/lua/smlua.h"
#include "pc/lua/utils/smlua_text_utils.h"
#include "game/memory.h"
#include "audio/data.h"
#include "audio/external.h"

#include "network/network.h"
#include "lua/smlua.h"

#include "audio/audio_api.h"
#include "audio/audio_sdl.h"
#include "audio/audio_null.h"

#include "rom_assets.h"
#include "rom_checker.h"
#include "nx_main.h"
#include "loading.h"
#include "cliopts.h"
#include "configfile.h"
#include "thread.h"
#include "controller/controller_api.h"
#include "controller/controller_keyboard.h"
#include "fs/fs.h"

#include "game/display.h" // for gGlobalTimer
#include "game/game_init.h"
#include "game/main.h"
#include "game/rumble_init.h"

#include "pc/lua/utils/smlua_audio_utils.h"

#include "pc/network/version.h"
#include "pc/network/socket/socket.h"
#include "pc/network/network_player.h"
#include "pc/update_checker.h"
#include "pc/djui/djui.h"
#include "pc/djui/djui_unicode.h"
#include "pc/djui/djui_panel.h"
#include "pc/djui/djui_panel_modlist.h"
#include "pc/djui/djui_ctx_display.h"
#include "pc/djui/djui_fps_display.h"
#include "pc/djui/djui_lua_profiler.h"
#include "pc/debuglog.h"
#include "pc/utils/misc.h"

#include "pc/mods/mods.h"

#include "debug_context.h"
#include "menu/intro_geo.h"

#include "gfx_dimensions.h"
#include "game/segment2.h"

struct AudioAPI *audio_api = NULL;
struct GfxWindowManagerAPI *wm_api = &WAPI;

void nx_init(void) {
    //accountInitialize(AccountServiceType_Application);
    socketInitializeDefault();
    //nifmInitialize(NifmServiceType_User);
    //plInitialize(PlServiceType_User);
    romfsInit();
    nxlinkStdio();

    NWindow* win = nwindowGetDefault();
    nwindowSetDimensions(win, 1920, 1080);
}

void nx_cleanup(void) {
    //accountExit();
    socketExit();
    //nifmExit();
    //plExit();
    romfsExit();
}

int main(int argc, char *argv[]) {
    nx_init();
    
    // Initialize our filesystem, If it fails.
    // We can't continue.
    if (!fs_init("sdmc:/switch")) {
        nx_cleanup();
        return 0;
    }
    
    printf("Loading game config.\n");
    
    // Load our config.
    configfile_load();
    
    printf("Loading gfx for game.\n");

    // Create the window as soon as possible.
    if (!gGfxInited) {
        gfx_init(&WAPI, &RAPI, "Super Mario 64 Coop Deluxe");
    }
    
    printf("Checking for game ROM.\n");

    // Render the ROM setup screen
    if (!main_rom_handler()) {
#ifdef LOADING_SCREEN_SUPPORTED
        if (!gCLIOpts.hideLoadingScreen) {
            render_rom_setup_screen(); // holds the game load until a valid rom is provided
        } else
#endif
        {
            printf("ERROR: Could not find a valid vanilla US SM64 rom in the game user folder.\n");
            nx_cleanup();
            return 0;
        }
    }
    
    printf("Loading game data.\n");

    // Start the thread for setting up the game
#ifdef LOADING_SCREEN_SUPPORTED
    bool threadSuccess = false;
    if (!gCLIOpts.hideLoadingScreen && !gCLIOpts.headless) {
        if (init_thread_handle(&gLoadingThread, main_game_init, NULL, NULL, 0) == 0) {
            render_loading_screen(); // render the loading screen while the game is setup
            threadSuccess = true;
            destroy_mutex(&gLoadingThread);
        }
    }
    if (!threadSuccess)
#endif
    {
        main_game_init(NULL); // failsafe incase threading doesn't work
    }

    // initialize sm64 data and controllers
    thread5_game_loop(NULL);
    
    printf("Initializing audio.\n");

    // initialize sound outside threads
    if (audio_sdl.init()) audio_api = &audio_sdl;
    if (!audio_api) audio_api = &audio_null;

    // Initialize the audio thread if possible.
    // init_thread_handle(&gAudioThread, audio_thread, NULL, NULL, 0);

#ifdef LOADING_SCREEN_SUPPORTED
    loading_screen_reset();
#endif

    printf("Initializing DJUI.\n");

    // initialize djui
    djui_init();
    djui_unicode_init();
    djui_init_late();
    djui_console_message_dequeue();

    show_update_popup();
    
    printf("Initializing networking.\n");

    // initialize network
    if (gCLIOpts.network == NT_CLIENT) {
        network_set_system(NS_SOCKET);
        snprintf(gGetHostName, MAX_CONFIG_STRING, "%s", gCLIOpts.joinIp);
        snprintf(configJoinIp, MAX_CONFIG_STRING, "%s", gCLIOpts.joinIp);
        configJoinPort = gCLIOpts.networkPort;
        network_init(NT_CLIENT, false);
    } else if (gCLIOpts.network == NT_SERVER || gCLIOpts.coopnet) {
        if (gCLIOpts.network == NT_SERVER) {
            configNetworkSystem = NS_SOCKET;
            configHostPort = gCLIOpts.networkPort;
        } else {
            configNetworkSystem = NS_COOPNET;
            snprintf(configPassword, MAX_CONFIG_STRING, "%s", gCLIOpts.coopnetPassword);
        }

        // horrible, hacky fix for mods that access marioObj straight away
        // best fix: host with the standard main menu method
        static struct Object sHackyObject = { 0 };
        gMarioStates[0].marioObj = &sHackyObject;

        extern void djui_panel_do_host(bool reconnecting, bool playSound);
        djui_panel_do_host(NULL, false);
    } else {
        network_init(NT_NONE, false);
    }
    
    printf("Starting main loop.\n");

    // main loop
    while (appletMainLoop()) {
        debug_context_reset();
        
        CTX_BEGIN(CTX_TOTAL);
        WAPI.main_loop(produce_one_frame);
        CTX_END(CTX_TOTAL);

#ifdef DEVELOPMENT
        djui_ctx_display_update();
#endif
        djui_lua_profiler_update();
    }
  
    nx_cleanup();
    return 0;
}

#endif // __SWITCH__