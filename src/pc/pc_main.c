#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "sm64.h"

#include "pc/lua/smlua.h"

#include "game/memory.h"
#include "audio/external.h"

#include "network/network.h"
#include "lua/smlua.h"

#include "gfx/gfx_pc.h"

#include "gfx/gfx_opengl.h"
#include "gfx/gfx_direct3d11.h"
#include "gfx/gfx_direct3d12.h"

#include "gfx/gfx_dxgi.h"
#include "gfx/gfx_sdl.h"
#include "gfx/gfx_dummy.h"

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

#ifdef DISCORDRPC
#include "pc/discord/discordrpc.h"
#endif
#include "pc/network/version.h"
#include "pc/network/socket/domain_res.h"
#include "pc/network/network_player.h"
#include "pc/djui/djui.h"
#include "pc/debuglog.h"
#include "pc/utils/misc.h"

#include "pc/mods/mods.h"

#include "menu/intro_geo.h"

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

static struct AudioAPI *audio_api;
struct GfxWindowManagerAPI *wm_api;
static struct GfxRenderingAPI *rendering_api;

extern void gfx_run(Gfx *commands);
extern void thread5_game_loop(void *arg);
extern void create_next_audio_buffer(s16 *samples, u32 num_samples);
void game_loop_one_iteration(void);

void dispatch_audio_sptask(UNUSED struct SPTask *spTask) {
}

void set_vblank_handler(UNUSED s32 index, UNUSED struct VblankHandler *handler, UNUSED OSMesgQueue *queue, UNUSED OSMesg *msg) {
}

static bool inited = false;

void send_display_list(struct SPTask *spTask) {
    if (!inited) return;
    gfx_run((Gfx *)spTask->task.t.data_ptr);
}

#ifdef VERSION_EU
#define SAMPLES_HIGH 656
#define SAMPLES_LOW 640
#else
#define SAMPLES_HIGH 544
#define SAMPLES_LOW 528
#endif

static void patch_interpolations_before(void) {
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
    gRenderingInterpolated = true;

    // sanity check target time to deal with hangs and such
    f64 curTime = clock_elapsed_f64();
    if (fabs(sFrameTargetTime - curTime) > 1) {
        sFrameTargetTime = curTime - 0.01f;
    }

    u64 frames = 0;
    while ((curTime = clock_elapsed_f64()) < sFrameTargetTime) {
        // interpolate and render
        gfx_start_frame();
        f32 delta = MIN((curTime - sFrameTimeStart) / (sFrameTargetTime - sFrameTimeStart), 1);
        gRenderingDelta = delta;
        if (!gSkipInterpolationTitleScreen && (configFrameLimit > 30 || configUncappedFramerate)) { patch_interpolations(delta); }
        send_display_list(gGfxSPTask);
        gfx_end_frame();

        // delay
        if (!configUncappedFramerate) {
            f64 targetDelta = 1.0 / (f64)configFrameLimit;
            f64 now = clock_elapsed_f64();
            f64 actualDelta = now - curTime;
            if (actualDelta < targetDelta) {
                f64 delay = ((targetDelta - actualDelta) * 1000.0);
                wm_api->delay((u32)delay);
            }
        }

        frames++;
    }

    f32 fps = frames / (clock_elapsed_f64() - sFrameTimeStart);
    sAvgFps = sAvgFps * 0.6 + fps * 0.4;
    sAvgFrames = sAvgFrames * 0.9 + frames * 0.1;
    sFrameTimeStart = sFrameTargetTime;
    sFrameTargetTime += sFrameTime * gGameSpeed;
    gRenderingInterpolated = false;

    //printf(">>> fpt: %llu, fps: %f :: %f\n", frames, sAvgFps, fps);
}

void produce_one_frame(void) {
    network_update();

    patch_interpolations_before();

    const f32 master_mod = (f32)configMasterVolume / 127.0f;
    set_sequence_player_volume(SEQ_PLAYER_LEVEL, (f32)configMusicVolume / 127.0f * master_mod);
    set_sequence_player_volume(SEQ_PLAYER_SFX, (f32)configSfxVolume / 127.0f * master_mod);
    set_sequence_player_volume(SEQ_PLAYER_ENV, (f32)configEnvVolume / 127.0f * master_mod);

    game_loop_one_iteration();
    smlua_update();
    thread6_rumble_loop(NULL);

    int samples_left = audio_api->buffered();
    u32 num_audio_samples = samples_left < audio_api->get_desired_buffered() ? SAMPLES_HIGH : SAMPLES_LOW;
    //printf("Audio samples: %d %u\n", samples_left, num_audio_samples);
    s16 audio_buffer[SAMPLES_HIGH * 2 * 2];
    for (s32 i = 0; i < 2; i++) {
        /*if (audio_cnt-- == 0) {
            audio_cnt = 2;
        }
        u32 num_audio_samples = audio_cnt < 2 ? 528 : 544;*/
        create_next_audio_buffer(audio_buffer + i * (num_audio_samples * 2), num_audio_samples);
    }
    //printf("Audio samples before submitting: %d\n", audio_api->buffered());

    audio_api->play((u8 *)audio_buffer, 2 * num_audio_samples * 4);

    produce_interpolation_frames_and_delay();
}

void audio_shutdown(void) {
    audio_custom_shutdown();
    if (audio_api) {
        if (audio_api->shutdown) audio_api->shutdown();
        audio_api = NULL;
    }
}

void game_deinit(void) {
#ifdef DISCORDRPC
    discord_shutdown();
#endif
    configfile_save(configfile_name());
    controller_shutdown();
    audio_custom_shutdown();
    audio_shutdown();
    gfx_shutdown();
    network_shutdown(true, true, false);
    smlua_shutdown();
    mods_shutdown();
    inited = false;
}

void game_exit(void) {
    LOG_INFO("exiting cleanly");
    game_deinit();
    exit(0);
}

void inthand(UNUSED int signum) {
    game_exit();
}

void main_func(void) {
    const char *gamedir = gCLIOpts.GameDir[0] ? gCLIOpts.GameDir : FS_BASEDIR;
    const char *userpath = gCLIOpts.SavePath[0] ? gCLIOpts.SavePath : sys_user_path();
    fs_init(sys_ropaths, gamedir, userpath);

    sync_objects_init_system();
    mods_init();
    configfile_load(configfile_name());
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

    if (gCLIOpts.FullScreen == 1)
        configWindow.fullscreen = true;
    else if (gCLIOpts.FullScreen == 2)
        configWindow.fullscreen = false;

    const size_t poolsize = gCLIOpts.PoolSize ? gCLIOpts.PoolSize : DEFAULT_POOL_SIZE;
    u64 *pool = calloc(poolsize, 1);
    if (!pool) sys_fatal("Could not alloc %u bytes for main pool.\n", poolsize);
    main_pool_init(pool, pool + poolsize / sizeof(pool[0]));
    gEffectsMemoryPool = mem_pool_init(0x4000, MEMORY_POOL_LEFT);

    #if defined(WAPI_SDL1) || defined(WAPI_SDL2)
    wm_api = &gfx_sdl;
    #elif defined(WAPI_DXGI)
    wm_api = &gfx_dxgi;
    #elif defined(WAPI_DUMMY)
    wm_api = &gfx_dummy_wm_api;
    #else
    #error No window API!
    #endif

    #if defined(RAPI_D3D11)
    rendering_api = &gfx_direct3d11_api;
    # define RAPI_NAME "DirectX 11"
    #elif defined(RAPI_D3D12)
    rendering_api = &gfx_direct3d12_api;
    # define RAPI_NAME "DirectX 12"
    #elif defined(RAPI_GL) || defined(RAPI_GL_LEGACY)
    rendering_api = &gfx_opengl_api;
    # ifdef USE_GLES
    #  define RAPI_NAME "OpenGL ES"
    # else
    #  define RAPI_NAME "OpenGL"
    # endif
    #elif defined(RAPI_DUMMY)
    rendering_api = &gfx_dummy_renderer_api;
    #else
    #error No rendering API!
    #endif

    char* version = get_version_local();
    char window_title[96] = { 0 };
#ifdef GIT_HASH
    snprintf(window_title, 96, "sm64ex-coop: %s [%s]", version, GIT_HASH);
#else
    snprintf(window_title, 96, "sm64ex-coop: %s", version);
#endif

    gfx_init(wm_api, rendering_api, window_title);
    wm_api->set_keyboard_callbacks(keyboard_on_key_down, keyboard_on_key_up, keyboard_on_all_keys_up, keyboard_on_text_input);

    #if defined(AAPI_SDL1) || defined(AAPI_SDL2)
    if (audio_api == NULL && audio_sdl.init())
        audio_api = &audio_sdl;
    #endif

    if (audio_api == NULL) {
        audio_api = &audio_null;
    }

    djui_init();

    if (gCLIOpts.Network == NT_CLIENT) {
        network_set_system(NS_SOCKET);
        snprintf(gGetHostName, MAX_CONFIG_STRING, "%s", gCLIOpts.JoinIp);
        snprintf(configJoinIp, MAX_CONFIG_STRING, "%s", gCLIOpts.JoinIp);
        configJoinPort = gCLIOpts.NetworkPort;
        network_init(NT_CLIENT);
    } else if (gCLIOpts.Network == NT_SERVER) {
        network_set_system(NS_SOCKET);
        configHostPort = gCLIOpts.NetworkPort;
        network_init(NT_SERVER);
        djui_panel_shutdown();
        djui_panel_modlist_create(NULL);
    } else {
        network_init(NT_NONE);
    }

    audio_init();
    sound_init();
    bassh_init();
    network_player_init();

    thread5_game_loop(NULL);

    inited = true;

#ifdef EXTERNAL_DATA
    // precache data if needed
    if (configPrecacheRes) {
        fprintf(stdout, "precaching data\n");
        fflush(stdout);
        gfx_precache_textures();
    }
#endif

#ifdef DISCORDRPC
    discord_init();
#endif

    while (true) {
        wm_api->main_loop(produce_one_frame);
#ifdef DISCORDRPC
        discord_update_rich_presence();
#endif
#ifdef DEBUG
        fflush(stdout);
        fflush(stderr);
#endif
    }

    bassh_deinit();
}

int main(int argc, char *argv[]) {
    parse_cli_opts(argc, argv);
    main_func();
    return 0;
}
