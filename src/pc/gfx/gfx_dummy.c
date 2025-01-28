#ifdef WIN32
#include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
#include <time.h>   // for nanosleep
#else
#include <unistd.h> // for usleep
#endif

#include <errno.h>
#include <stdbool.h>
#include <PR/ultratypes.h>

#include "macros.h"
#include "gfx_window_manager_api.h"
#include "gfx_rendering_api.h"

#include "pc/pc_main.h"
#include "pc/utils/misc.h"
#include "pc/debuglog.h"

// TODO: figure out if this shit even works
#ifdef VERSION_EU
# define FRAMERATE 25
#else
# define FRAMERATE 30
#endif
// time between consequtive game frames
static const f64 sFrameTime = 1.0 / ((double)FRAMERATE);
static f64 sFrameTargetTime = 0;

static void sleep_ms(int milliseconds) { // cross-platform sleep function
    // from StackOverflow user Bernardo Ramos: https://stackoverflow.com/a/28827188
#ifdef WIN32
    Sleep(milliseconds);
#elif _POSIX_C_SOURCE >= 199309L
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
#else
    if (milliseconds >= 1000)
        sleep(milliseconds / 1000);
    usleep((milliseconds % 1000) * 1000);
#endif
}

static void gfx_dummy_wm_init(UNUSED const char *game_name) {
}

static void gfx_dummy_wm_set_keyboard_callbacks(UNUSED kb_callback_t on_key_down, UNUSED kb_callback_t on_key_up, UNUSED void (*on_all_keys_up)(void),
                                                UNUSED void (*on_text_input)(char*), UNUSED void (*on_text_editing)(char*, int)) {
}

static void gfx_dummy_wm_set_fullscreen_changed_callback(UNUSED void (*on_fullscreen_changed)(bool is_now_fullscreen)) {
}

static void gfx_dummy_wm_set_fullscreen(UNUSED bool enable) {
}

static void gfx_dummy_wm_main_loop(void (*run_one_game_iter)(void)) {
    while (1) {
        run_one_game_iter();
    }
}

static void gfx_dummy_wm_get_dimensions(uint32_t *width, uint32_t *height) {
    *width = 320;
    *height = 240;
}

static void gfx_dummy_wm_handle_events(void) {
}

static bool gfx_dummy_wm_start_frame(void) {
    return true;
}

static void gfx_dummy_wm_delay(u32 ms) {
    sleep_ms(ms);
}

static int gfx_dummy_wm_get_max_msaa(void) {
    return 0;
}

static void gfx_dummy_wm_set_window_title(UNUSED const char* title) {
}

static void gfx_dummy_wm_reset_window_title(void) {
}

static void gfx_dummy_wm_swap_buffers_begin(void) {
}

static void gfx_dummy_wm_swap_buffers_end(void) {
}

static double gfx_dummy_wm_get_time(void) {
    return 0.0;
}

static char* gfx_dummy_wm_get_clipboard_text(void) {
    return "";
}

static void gfx_dummy_wm_shutdown(void) {
}

static void gfx_dummy_wm_start_text_input(void) {
}

static void gfx_dummy_wm_stop_text_input(void) {
}

static void gfx_dummy_wm_set_clipboard_text(UNUSED const char* text) {
}

static void gfx_dummy_wm_set_cursor_visible(UNUSED bool visible) {
}

static bool gfx_dummy_wm_has_focus(void) {
    return true;
}

static bool gfx_dummy_renderer_z_is_from_0_to_1(void) {
    return false;
}

static void gfx_dummy_renderer_unload_shader(UNUSED struct ShaderProgram *old_prg) {
}

static void gfx_dummy_renderer_load_shader(UNUSED struct ShaderProgram *new_prg) {
}

static struct ShaderProgram *gfx_dummy_renderer_create_and_load_new_shader(UNUSED struct ColorCombiner* cc) {
    return NULL;
}

static struct ShaderProgram *gfx_dummy_renderer_lookup_shader(UNUSED struct ColorCombiner* cc) {
    return NULL;
}

static void gfx_dummy_renderer_shader_get_info(UNUSED struct ShaderProgram *prg, uint8_t *num_inputs, bool used_textures[2]) {
    *num_inputs = 0;
    used_textures[0] = false;
    used_textures[1] = false;
}

static uint32_t gfx_dummy_renderer_new_texture(void) {
    return 0;
}

static void gfx_dummy_renderer_select_texture(UNUSED int tile, UNUSED uint32_t texture_id) {
}

static void gfx_dummy_renderer_upload_texture(UNUSED const uint8_t *rgba32_buf, UNUSED int width, UNUSED int height) {
}

static void gfx_dummy_renderer_set_sampler_parameters(UNUSED int tile, UNUSED bool linear_filter, UNUSED uint32_t cms, UNUSED uint32_t cmt) {
}

static void gfx_dummy_renderer_set_depth_test(UNUSED bool depth_test) {
}

static void gfx_dummy_renderer_set_depth_mask(UNUSED bool z_upd) {
}

static void gfx_dummy_renderer_set_zmode_decal(UNUSED bool zmode_decal) {
}

static void gfx_dummy_renderer_set_viewport(UNUSED int x, UNUSED int y, UNUSED int width, UNUSED int height) {
}

static void gfx_dummy_renderer_set_scissor(UNUSED int x, UNUSED int y, UNUSED int width, UNUSED int height) {
}

static void gfx_dummy_renderer_set_use_alpha(UNUSED bool use_alpha) {
}

static void gfx_dummy_renderer_draw_triangles(UNUSED float buf_vbo[], UNUSED size_t buf_vbo_len, UNUSED size_t buf_vbo_num_tris) {
}

static void gfx_dummy_renderer_init(void) {
}

static void gfx_dummy_renderer_on_resize(void) {
}

static void gfx_dummy_renderer_start_frame(void) {
}

static void gfx_dummy_renderer_end_frame(void) {
}

static void gfx_dummy_renderer_finish_render(void) {
}

static void gfx_dummy_renderer_shutdown(void) {
}

struct GfxWindowManagerAPI gfx_dummy_wm_api = {
    gfx_dummy_wm_init,
    gfx_dummy_wm_set_keyboard_callbacks,
    gfx_dummy_wm_main_loop,
    gfx_dummy_wm_get_dimensions,
    gfx_dummy_wm_handle_events,
    gfx_dummy_wm_start_frame,
    gfx_dummy_wm_swap_buffers_begin,
    gfx_dummy_wm_swap_buffers_end,
    gfx_dummy_wm_get_time,
    gfx_dummy_wm_shutdown,
    gfx_dummy_wm_start_text_input,
    gfx_dummy_wm_stop_text_input,
    gfx_dummy_wm_get_clipboard_text,
    gfx_dummy_wm_set_clipboard_text,
    gfx_dummy_wm_set_cursor_visible,
    gfx_dummy_wm_delay,
    gfx_dummy_wm_get_max_msaa,
    gfx_dummy_wm_set_window_title,
    gfx_dummy_wm_reset_window_title,
    gfx_dummy_wm_has_focus
};

struct GfxRenderingAPI gfx_dummy_renderer_api = {
    gfx_dummy_renderer_z_is_from_0_to_1,
    gfx_dummy_renderer_unload_shader,
    gfx_dummy_renderer_load_shader,
    gfx_dummy_renderer_create_and_load_new_shader,
    gfx_dummy_renderer_lookup_shader,
    gfx_dummy_renderer_shader_get_info,
    gfx_dummy_renderer_new_texture,
    gfx_dummy_renderer_select_texture,
    gfx_dummy_renderer_upload_texture,
    gfx_dummy_renderer_set_sampler_parameters,
    gfx_dummy_renderer_set_depth_test,
    gfx_dummy_renderer_set_depth_mask,
    gfx_dummy_renderer_set_zmode_decal,
    gfx_dummy_renderer_set_viewport,
    gfx_dummy_renderer_set_scissor,
    gfx_dummy_renderer_set_use_alpha,
    gfx_dummy_renderer_draw_triangles,
    gfx_dummy_renderer_init,
    gfx_dummy_renderer_on_resize,
    gfx_dummy_renderer_start_frame,
    gfx_dummy_renderer_end_frame,
    gfx_dummy_renderer_finish_render,
    gfx_dummy_renderer_shutdown
};