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
#include "pc_main.h"
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

#ifdef DISCORD_SDK
#include "pc/discord/discord.h"
#endif

#include "pc/mumble/mumble.h"

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

extern Vp D_8032CF00;

OSMesg D_80339BEC;
OSMesgQueue gSIEventMesgQueue;

s8 gResetTimer;
s8 D_8032C648;
s8 gDebugLevelSelect;
s8 gShowProfiler;
s8 gShowDebugText;

s32 gRumblePakPfs;
u32 gNumVblanks = 0;

u8 gRenderingInterpolated = 0;
f32 gRenderingDelta = 0;

#define FRAMERATE 30
static const f64 sFrameTime = (1.0 / ((double)FRAMERATE));
static f64 sFpsTimeLast = 0;
static f64 sFrameTimeStart = 0;
static u32 sDrawnFrames = 0;

bool gGameInited = false;
bool gGfxInited = false;

u8 gLuaVolumeMaster = 127;
u8 gLuaVolumeLevel = 127;
u8 gLuaVolumeSfx = 127;
u8 gLuaVolumeEnv = 127;

static struct AudioAPI *audio_api;
struct GfxWindowManagerAPI *wm_api = &WAPI;

extern void gfx_run(Gfx *commands);
extern void thread5_game_loop(void *arg);
extern void create_next_audio_buffer(s16 *samples, u32 num_samples);
void game_loop_one_iteration(void);

void dispatch_audio_sptask(UNUSED struct SPTask *spTask) {}
void set_vblank_handler(UNUSED s32 index, UNUSED struct VblankHandler *handler, UNUSED OSMesgQueue *queue, UNUSED OSMesg *msg) {}

void send_display_list(struct SPTask *spTask) {
    if (!gGameInited) { return; }
    gfx_run((Gfx *)spTask->task.t.data_ptr);
}

#ifdef VERSION_EU
#define SAMPLES_HIGH 560 // gAudioBufferParameters.maxAiBufferLength
#define SAMPLES_LOW 528 // gAudioBufferParameters.minAiBufferLength
#else
#define SAMPLES_HIGH 544
#define SAMPLES_LOW 528
#endif

extern void patch_mtx_before(void);
extern void patch_screen_transition_before(void);
extern void patch_title_screen_before(void);
extern void patch_dialog_before(void);
extern void patch_hud_before(void);
extern void patch_paintings_before(void);
extern void patch_bubble_particles_before(void);
extern void patch_snow_particles_before(void);
extern void patch_djui_before(void);
extern void patch_djui_hud_before(void);
extern void patch_scroll_targets_before(void);

extern void patch_mtx_interpolated(f32 delta);
extern void patch_screen_transition_interpolated(f32 delta);
extern void patch_title_screen_interpolated(f32 delta);
extern void patch_dialog_interpolated(f32 delta);
extern void patch_hud_interpolated(f32 delta);
extern void patch_paintings_interpolated(f32 delta);
extern void patch_bubble_particles_interpolated(f32 delta);
extern void patch_snow_particles_interpolated(f32 delta);
extern void patch_djui_interpolated(f32 delta);
extern void patch_djui_hud(f32 delta);
extern void patch_scroll_targets_interpolated(f32 delta);

static void patch_interpolations_before(void) {
    patch_mtx_before();
    patch_screen_transition_before();
    patch_title_screen_before();
    patch_dialog_before();
    patch_hud_before();
    patch_paintings_before();
    patch_bubble_particles_before();
    patch_snow_particles_before();
    patch_djui_before();
    patch_djui_hud_before();
    patch_scroll_targets_before();
}

static inline void patch_interpolations(f32 delta) {
    patch_mtx_interpolated(delta);
    patch_screen_transition_interpolated(delta);
    patch_title_screen_interpolated(delta);
    patch_dialog_interpolated(delta);
    patch_hud_interpolated(delta);
    patch_paintings_interpolated(delta);
    patch_bubble_particles_interpolated(delta);
    patch_snow_particles_interpolated(delta);
    patch_djui_interpolated(delta);
    patch_djui_hud(delta);
    patch_scroll_targets_interpolated(delta);
}

static void compute_fps(f64 curTime) {
    u32 fps = round((f64) sDrawnFrames / MAX(0.001, curTime - sFpsTimeLast));
    djui_fps_display_update(fps);
    sFpsTimeLast = curTime;
    sDrawnFrames = 0;
}

static s32 get_num_frames_to_draw(f64 t) {
    if (configFrameLimit % FRAMERATE == 0) {
        return configFrameLimit / FRAMERATE;
    }
    s64 numFramesCurr = (s64) (t * (f64) configFrameLimit);
    s64 numFramesNext = (s64) ((t + sFrameTime) * (f64) configFrameLimit);
    return (s32) MAX(1, numFramesNext - numFramesCurr);
}

void produce_interpolation_frames_and_delay(void) {
    bool is30Fps = (!configUncappedFramerate && configFrameLimit == FRAMERATE);

    gRenderingInterpolated = true;

    f64 curTime = clock_elapsed_f64();
    f64 targetTime = sFrameTimeStart + sFrameTime;
    s32 numFramesToDraw = get_num_frames_to_draw(sFrameTimeStart);

    f64 loopStartTime = curTime;
    f64 expectedTime = 0;

    // interpolate and render
    // make sure to draw at least one frame to prevent the game from freezing completely
    // (including inputs and window events) if the game update duration is greater than 33ms
    do {
        f32 delta = (
            is30Fps ?
            1.0f :
            MIN(MAX((curTime - sFrameTimeStart) / sFrameTime, 0.f), 1.f)
        );
        gRenderingDelta = delta;

        gfx_start_frame();
        if (!gSkipInterpolationTitleScreen) { patch_interpolations(delta); }
        send_display_list(gGfxSPTask);
        gfx_end_frame();

        sDrawnFrames++;

        if (!is30Fps && configUncappedFramerate) { continue; }

        // delay if our framerate is capped
        f64 now = clock_elapsed_f64();
        f64 elapsedTime = now - loopStartTime;
        expectedTime += (targetTime - curTime) / (f64) numFramesToDraw;
        f64 delay = (expectedTime - elapsedTime) * 1000.0;
        if (delay > 0.0) {
            WAPI.delay((u32)delay);
        }
        numFramesToDraw--;
    } while ((curTime = clock_elapsed_f64()) < targetTime && numFramesToDraw > 0);

    // compute and update the frame rate every second
    if ((curTime = clock_elapsed_f64()) >= sFpsTimeLast + 1.0) {
        compute_fps(curTime);
    }

    // advance frame start time
    if (curTime > sFrameTimeStart + 2 * sFrameTime) {
        sFrameTimeStart = curTime;
    } else {
        sFrameTimeStart += sFrameTime;
    }

    gRenderingInterpolated = false;
}

// It's just better to have this off the stack, Because the size isn't small.
// It also may help static analysis and bug catching.
static s16 sAudioBuffer[SAMPLES_HIGH * 2 * 2] = { 0 };

inline static void buffer_audio(void) {
    bool shouldMute = configMuteFocusLoss && !WAPI.has_focus();
    const f32 masterMod = (f32)configMasterVolume / 127.0f * (f32)gLuaVolumeMaster / 127.0f;
    set_sequence_player_volume(SEQ_PLAYER_LEVEL, shouldMute ? 0 : (f32)configMusicVolume / 127.0f * (f32)gLuaVolumeLevel / 127.0f * masterMod);
    set_sequence_player_volume(SEQ_PLAYER_SFX,   shouldMute ? 0 : (f32)configSfxVolume / 127.0f * (f32)gLuaVolumeSfx / 127.0f * masterMod);
    set_sequence_player_volume(SEQ_PLAYER_ENV,   shouldMute ? 0 : (f32)configEnvVolume / 127.0f * (f32)gLuaVolumeEnv / 127.0f * masterMod);

    int samplesLeft = audio_api->buffered();
    u32 numAudioSamples = samplesLeft < audio_api->get_desired_buffered() ? SAMPLES_HIGH : SAMPLES_LOW;
    for (s32 i = 0; i < 2; i++) {
        create_next_audio_buffer(sAudioBuffer + i * (numAudioSamples * 2), numAudioSamples);
    }
    audio_api->play((u8 *)sAudioBuffer, 2 * numAudioSamples * 4);
}

void *audio_thread(UNUSED void *arg) {
    // As long as we have an audio api and that we're threaded, Loop.
    while (audio_api) {
        f64 curTime = clock_elapsed_f64();

        // Buffer the audio.
        lock_mutex(&gAudioThread);
        buffer_audio();
        unlock_mutex(&gAudioThread);

        // Delay till the next frame for smooth audio at the correct speed.
        // delay
        f64 targetDelta = 1.0 / (f64)FRAMERATE;
        f64 now = clock_elapsed_f64();
        f64 actualDelta = now - curTime;
        if (actualDelta < targetDelta) {
            f64 delay = ((targetDelta - actualDelta) * 1000.0);
            WAPI.delay((u32)delay);
        }
    }

    // Exit the thread if our loop breaks.
    exit_thread();

    return NULL;
}

void produce_one_frame(void) {
    CTX_EXTENT(CTX_NETWORK, network_update);

    CTX_EXTENT(CTX_INTERP, patch_interpolations_before);

    CTX_EXTENT(CTX_GAME_LOOP, game_loop_one_iteration);

    CTX_EXTENT(CTX_SMLUA, smlua_update);

    // If we aren't threaded
    if (gAudioThread.state == INVALID) {
        CTX_EXTENT(CTX_AUDIO, buffer_audio);
    }

    CTX_EXTENT(CTX_RENDER, produce_interpolation_frames_and_delay);
}

// used for rendering 2D scenes fullscreen like the loading or crash screens
void produce_one_dummy_frame(void (*callback)(), u8 clearColorR, u8 clearColorG, u8 clearColorB) {
    // start frame
    gfx_start_frame();
    config_gfx_pool();
    init_render_image();
    create_dl_ortho_matrix();
    djui_gfx_displaylist_begin();

    // fix scaling issues
    gSPViewport(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(&D_8032CF00));
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, BORDER_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT - BORDER_HEIGHT);

    // clear screen
    create_dl_translation_matrix(MENU_MTX_PUSH, GFX_DIMENSIONS_FROM_LEFT_EDGE(0), 240.f, 0.f);
    create_dl_scale_matrix(MENU_MTX_NOPUSH, (GFX_DIMENSIONS_ASPECT_RATIO * SCREEN_HEIGHT) / 130.f, 3.f, 1.f);
    gDPSetEnvColor(gDisplayListHead++, clearColorR, clearColorG, clearColorB, 0xFF);
    gSPDisplayList(gDisplayListHead++, dl_draw_text_bg_box);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

    // call the callback
    callback();

    // render frame
    djui_gfx_displaylist_end();
    end_master_display_list();
    alloc_display_list(0);
    gfx_run((Gfx*) gGfxSPTask->task.t.data_ptr); // send_display_list
    display_and_vsync();
    gfx_end_frame();
}

void audio_shutdown(void) {
    audio_custom_shutdown();
    if (audio_api) {
        if (audio_api->shutdown) audio_api->shutdown();
        audio_api = NULL;
    }
}

void game_deinit(void) {
    if (gGameInited) { configfile_save(configfile_name()); }
    controller_shutdown();
    audio_custom_shutdown();
    audio_shutdown();
    network_shutdown(true, true, false, false);
    smlua_text_utils_shutdown();
    smlua_shutdown();
    smlua_audio_custom_deinit();
    mods_shutdown();
    djui_shutdown();
    gfx_shutdown();
    gGameInited = false;
}

void game_exit(void) {
    LOG_INFO("exiting cleanly");
    game_deinit();
    exit(0);
}

void* main_game_init(UNUSED void* dummy) {
    // load language
    if (!djui_language_init(configLanguage)) { snprintf(configLanguage, MAX_CONFIG_STRING, "%s", ""); }

    LOADING_SCREEN_MUTEX(loading_screen_set_segment_text("Loading"));
    dynos_gfx_init();
    enable_queued_dynos_packs();
    sync_objects_init_system();

    if (gCLIOpts.network != NT_SERVER && !gCLIOpts.skipUpdateCheck) {
        check_for_updates();
    }

    LOADING_SCREEN_MUTEX(loading_screen_set_segment_text("Loading ROM Assets"));
    rom_assets_load();
    smlua_text_utils_init();

    mods_init();
    enable_queued_mods();
    LOADING_SCREEN_MUTEX(
        gCurrLoadingSegment.percentage = 0;
        loading_screen_set_segment_text("Starting Game");
    );

    audio_init();
    sound_init();
    network_player_init();
    mumble_init();

    gGameInited = true;
}

int main(int argc, char *argv[]) {
    // handle terminal arguments
    if (!parse_cli_opts(argc, argv)) { return 0; }

#if defined(RAPI_DUMMY) || defined(WAPI_DUMMY)
    gCLIOpts.headless = true;
#endif

#ifdef _WIN32
    // handle Windows console
    if (gCLIOpts.console || gCLIOpts.headless) {
        SetConsoleOutputCP(CP_UTF8);
    } else {
        FreeConsole();
        freopen("NUL", "w", stdout);
    }
#endif

#ifdef _WIN32
    if (gCLIOpts.savePath[0]) {
        char portable_path[SYS_MAX_PATH] = {};
        sys_windows_short_path_from_mbs(portable_path, SYS_MAX_PATH, gCLIOpts.savePath);
        fs_init(portable_path);
    } else {
        fs_init(sys_user_path());
    }
#else
    fs_init(gCLIOpts.savePath[0] ? gCLIOpts.savePath : sys_user_path());
#endif

#if !defined(RAPI_DUMMY) && !defined(WAPI_DUMMY)
    if (gCLIOpts.headless) {
        memcpy(&WAPI, &gfx_dummy_wm_api, sizeof(struct GfxWindowManagerAPI));
        memcpy(&RAPI, &gfx_dummy_renderer_api, sizeof(struct GfxRenderingAPI));
    }
#endif

    configfile_load();

    legacy_folder_handler();

    // create the window almost straight away
    if (!gGfxInited) {
        gfx_init(&WAPI, &RAPI, TITLE);
        WAPI.set_keyboard_callbacks(keyboard_on_key_down, keyboard_on_key_up, keyboard_on_all_keys_up,
            keyboard_on_text_input, keyboard_on_text_editing);
    }

    // render the rom setup screen
    if (!main_rom_handler()) {
#ifdef LOADING_SCREEN_SUPPORTED
        if (!gCLIOpts.hideLoadingScreen) {
            render_rom_setup_screen(); // holds the game load until a valid rom is provided
        } else
#endif
        {
            printf("ERROR: could not find valid vanilla us sm64 rom in game's user folder\n");
            return 0;
        }
    }

    // start the thread for setting up the game
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

    // initialize sound outside threads
    if (gCLIOpts.headless) audio_api = &audio_null;
#if defined(AAPI_SDL1) || defined(AAPI_SDL2)
    if (!audio_api && audio_sdl.init()) audio_api = &audio_sdl;
#endif
    if (!audio_api) audio_api = &audio_null;

    // Initialize the audio thread if possible.
    // init_thread_handle(&gAudioThread, audio_thread, NULL, NULL, 0);

#ifdef LOADING_SCREEN_SUPPORTED
    loading_screen_reset();
#endif

    // initialize djui
    djui_init();
    djui_unicode_init();
    djui_init_late();
    djui_console_message_dequeue();

    show_update_popup();

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

    // main loop
    while (true) {
        debug_context_reset();
        CTX_BEGIN(CTX_TOTAL);
        WAPI.main_loop(produce_one_frame);
#ifdef DISCORD_SDK
        discord_update();
#endif
        mumble_update();
#ifdef DEBUG
        fflush(stdout);
        fflush(stderr);
#endif
        CTX_END(CTX_TOTAL);

#ifdef DEVELOPMENT
        djui_ctx_display_update();
#endif
        djui_lua_profiler_update();
    }

    return 0;
}
