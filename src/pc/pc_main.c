#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "sm64.h"

#include "pc/lua/smlua.h"

#include "game/memory.h"
#include "audio/external.h"

#include "network/network.h"
#include "lua/smlua.h"

#include "audio/audio_api.h"
#include "audio/audio_sdl.h"
#include "audio/audio_null.h"

#include "pc_main.h"
#include "cliopts.h"
#include "configfile.h"
#include "controller/controller_api.h"
#include "controller/controller_keyboard.h"
#include "fs/fs.h"

#include "game/display.h" // for gGlobalTimer
#include "game/game_init.h"
#include "game/main.h"
#include "game/rumble_init.h"

#include "include/bass/bass.h"
#include "include/bass/bass_fx.h"
#include "src/bass_audio/bass_audio_helpers.h"
#include "pc/lua/utils/smlua_audio_utils.h"

#include "pc/network/version.h"
#include "pc/network/socket/domain_res.h"
#include "pc/network/network_player.h"
#include "pc/djui/djui.h"
#include "pc/djui/djui_unicode.h"
#include "pc/djui/djui_panel.h"
#include "pc/djui/djui_panel_modlist.h"
#include "pc/debuglog.h"
#include "pc/utils/misc.h"

#include "pc/mods/mods.h"

#include "debug_context.h"
#include "menu/intro_geo.h"

#ifdef DISCORD_SDK
#include "pc/discord/discord.h"
#endif

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

f64 gGameSpeed = 1.0f; // TODO: should probably remove

#define FRAMERATE 30
static const f64 sFrameTime = (1.0 / ((double)FRAMERATE));
static f64 sFrameTargetTime = 0;
static f64 sFrameTimeStart;
static f64 sLastFrameTimeStart;
static f32 sAvgFrames = 1;
static f32 sAvgFps = 0;

bool gGameInited = false;
bool gGfxInited = false;

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
}

void produce_interpolation_frames_and_delay(void) {
    u64 frames = 0;
    f64 curTime = clock_elapsed_f64();

    gRenderingInterpolated = true;

    // sanity check target time to deal with hangs and such
    if (fabs(sFrameTargetTime - curTime) > 1) { sFrameTargetTime = curTime - 0.01f; }

    // interpolate and render
    while ((curTime = clock_elapsed_f64()) < sFrameTargetTime) {
        gfx_start_frame();
        f32 delta = MIN((curTime - sFrameTimeStart) / (sFrameTargetTime - sFrameTimeStart), 1);
        gRenderingDelta = delta;
        if (!gSkipInterpolationTitleScreen && (configFrameLimit > 30 || configUncappedFramerate)) { patch_interpolations(delta); }
        send_display_list(gGfxSPTask);
        gfx_end_frame();

        // delay
        if (!configUncappedFramerate) {
            f64 targetDelta = 1.0 / (f64) configFrameLimit;
            f64 now = clock_elapsed_f64();
            f64 actualDelta = now - curTime;
            if (actualDelta < targetDelta) {
                f64 delay = ((targetDelta - actualDelta) * 1000.0);
                WAPI.delay((u32) delay);
            }
        }

        frames++;
    }

    f32 fps = frames / (clock_elapsed_f64() - sFrameTimeStart);
    sAvgFps = sAvgFps * 0.95 + fps * 0.05;
    sAvgFrames = sAvgFrames * 0.9 + frames * 0.1;
    sFrameTimeStart = sFrameTargetTime;
    sFrameTargetTime += sFrameTime * gGameSpeed;
    gRenderingInterpolated = false;

    //printf(">>> fpt: %llu, fps: %f :: %f\n", frames, sAvgFps, fps);
}

inline static void buffer_audio(void) {
    int samples_left = audio_api->buffered();
    u32 num_audio_samples = samples_left < audio_api->get_desired_buffered() ? SAMPLES_HIGH : SAMPLES_LOW;
    s16 audio_buffer[SAMPLES_HIGH * 2 * 2];
    for (s32 i = 0; i < 2; i++) {
        create_next_audio_buffer(audio_buffer + i * (num_audio_samples * 2), num_audio_samples);
    }
    audio_api->play((u8 *)audio_buffer, 2 * num_audio_samples * 4);
}

void produce_one_frame(void) {
    CTX_EXTENT(CTX_NETWORK, network_update);

    CTX_EXTENT(CTX_INTERP, patch_interpolations_before);

    const f32 master_mod = (f32)configMasterVolume / 127.0f;
    set_sequence_player_volume(SEQ_PLAYER_LEVEL, (f32)configMusicVolume / 127.0f * master_mod);
    set_sequence_player_volume(SEQ_PLAYER_SFX, (f32)configSfxVolume / 127.0f * master_mod);
    set_sequence_player_volume(SEQ_PLAYER_ENV, (f32)configEnvVolume / 127.0f * master_mod);

    CTX_EXTENT(CTX_GAME_LOOP, game_loop_one_iteration);

    CTX_EXTENT(CTX_SMLUA, smlua_update);

    thread6_rumble_loop(NULL);

    CTX_EXTENT(CTX_AUDIO, buffer_audio);

    CTX_EXTENT(CTX_RENDER, produce_interpolation_frames_and_delay);
}

void audio_shutdown(void) {
    audio_custom_shutdown();
    if (audio_api) {
        if (audio_api->shutdown) audio_api->shutdown();
        audio_api = NULL;
    }
}

void game_deinit(void) {
    configfile_save(configfile_name());
    controller_shutdown();
    audio_custom_shutdown();
    audio_shutdown();
    gfx_shutdown();
    network_shutdown(true, true, false, false);
    smlua_shutdown();
    mods_shutdown();
    gGameInited = false;
}

void game_exit(void) {
    LOG_INFO("exiting cleanly");
    game_deinit();
    exit(0);
}

void main_func(void) {
    const char *gamedir = gCLIOpts.GameDir[0] ? gCLIOpts.GameDir : FS_BASEDIR;
    const char *userpath = gCLIOpts.SavePath[0] ? gCLIOpts.SavePath : sys_user_path();
    fs_init(sys_ropaths, gamedir, userpath);

    sync_objects_init_system();
    djui_unicode_init();
    djui_init();
    dynos_packs_init();
    mods_init();

    // load config
    configfile_load();
    if (!djui_language_init(configLanguage)) {
        snprintf(configLanguage, MAX_CONFIG_STRING, "%s", "");
    }

    dynos_pack_init();

    // If coop_custom_palette_* values are not found in sm64config.txt, the custom palette config will use the default values (Mario's palette)
    // But if no preset is found, that means the current palette is a custom palette
    for (int i = 0; i <= PALETTE_PRESET_MAX; i++) {
        if (i == PALETTE_PRESET_MAX) {
            configCustomPalette = configPlayerPalette;
            configfile_save(configfile_name());
        } else if (memcmp(&configPlayerPalette, &gPalettePresets[i], sizeof(struct PlayerPalette)) == 0) {
            break;
        }
    }

    if (configPlayerModel >= CT_MAX) { configPlayerModel = 0; }

    if (gCLIOpts.FullScreen == 1) { configWindow.fullscreen = true; }
    else if (gCLIOpts.FullScreen == 2) { configWindow.fullscreen = false; }

    // incase the loading screen failed, or is disabled
    if (!gGfxInited) {
        gfx_init(&WAPI, &RAPI, TITLE);
        WAPI.set_keyboard_callbacks(keyboard_on_key_down, keyboard_on_key_up, keyboard_on_all_keys_up, keyboard_on_text_input);
    }

#if defined(AAPI_SDL1) || defined(AAPI_SDL2)
    if (audio_api == NULL && audio_sdl.init()) { audio_api = &audio_sdl; }
#endif
    if (audio_api == NULL) { audio_api = &audio_null; }

    audio_init();
    sound_init();
    bassh_init();
    network_player_init();

    thread5_game_loop(NULL);

    djui_init_late();

    // init network
    if (gCLIOpts.Network == NT_CLIENT) {
        network_set_system(NS_SOCKET);
        snprintf(gGetHostName, MAX_CONFIG_STRING, "%s", gCLIOpts.JoinIp);
        snprintf(configJoinIp, MAX_CONFIG_STRING, "%s", gCLIOpts.JoinIp);
        configJoinPort = gCLIOpts.NetworkPort;
        network_init(NT_CLIENT, false);
    } else if (gCLIOpts.Network == NT_SERVER) {
        network_set_system(NS_SOCKET);
        configHostPort = gCLIOpts.NetworkPort;
        network_init(NT_SERVER, false);
        djui_panel_shutdown();
        djui_panel_modlist_create(NULL);
    } else {
        network_init(NT_NONE, false);
    }

#ifdef EXTERNAL_DATA
    // precache data if needed
    if (configPrecacheRes) {
        fprintf(stdout, "precaching data\n");
        fflush(stdout);
        gfx_precache_textures();
    }
#endif

    gGameInited = true;

    while (true) {
        debug_context_reset();
        CTX_BEGIN(CTX_FRAME);
        WAPI.main_loop(produce_one_frame);
#ifdef DISCORD_SDK
        discord_update();
#endif
#ifdef DEBUG
        fflush(stdout);
        fflush(stderr);
#endif
        CTX_END(CTX_FRAME);
    }

    bassh_deinit();
}

int main(int argc, char *argv[]) {
    parse_cli_opts(argc, argv);
    main_func();
    return 0;
}
