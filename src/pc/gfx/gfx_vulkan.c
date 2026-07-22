#if defined(ENABLE_VULKAN)

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "macros.h"
#include "gfx_vulkan.h"
#include "gfx_vulkan/gfx_vulkan_context.h"
#include "gfx_vulkan/gfx_vulkan_swapchain.h"
#include "gfx_vulkan/gfx_vulkan_frame.h"
#include "gfx_vulkan/gfx_vulkan_memory.h"
#include "gfx_vulkan/gfx_vulkan_texture.h"
#include "gfx_vulkan/gfx_vulkan_shader.h"
#include "gfx_vulkan/gfx_vulkan_pipeline.h"
#include "gfx_vulkan/gfx_vulkan_draw.h"
#include "gfx_window_manager.h"

#include <volk.h>

// Checks whether `device` reports `extensionName` as a supported device extension.
static bool device_has_extension(VkPhysicalDevice device, const char* extensionName) {
    uint32_t count = 0;
    if (vkEnumerateDeviceExtensionProperties(device, NULL, &count, NULL) != VK_SUCCESS || count == 0) {
        return false;
    }

    VkExtensionProperties* props = malloc(count * sizeof(VkExtensionProperties));
    if (!props) {
        return false;
    }

    bool found = false;
    if (vkEnumerateDeviceExtensionProperties(device, NULL, &count, props) == VK_SUCCESS) {
        for (uint32_t i = 0; i < count; i++) {
            if (strcmp(props[i].extensionName, extensionName) == 0) {
                found = true;
                break;
            }
        }
    }

    free(props);
    return found;
}

// Same suitability rules as gfx_vulkan_context.c::pick_physical_device, kept
// in sync even though this probe isn't invoked from ENABLE_VULKAN builds today.
static bool device_is_suitable(VkPhysicalDevice device) {
    VkPhysicalDeviceProperties props;
    vkGetPhysicalDeviceProperties(device, &props);
    if (props.apiVersion < VK_API_VERSION_1_3) {
        return false; // dynamic rendering + synchronization2 are core only from 1.3
    }

    if (!device_has_extension(device, VK_KHR_SWAPCHAIN_EXTENSION_NAME) ||
        !device_has_extension(device, VK_EXT_EXTENDED_DYNAMIC_STATE_3_EXTENSION_NAME) ||
        !device_has_extension(device, VK_KHR_PUSH_DESCRIPTOR_EXTENSION_NAME)) {
        return false;
    }

    VkPhysicalDeviceExtendedDynamicState3FeaturesEXT eds3Features = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_DYNAMIC_STATE_3_FEATURES_EXT,
    };
    VkPhysicalDeviceVulkan12Features vk12Features = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES,
        .pNext = &eds3Features,
    };
    VkPhysicalDeviceVulkan13Features vk13Features = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES,
        .pNext = &vk12Features,
    };
    VkPhysicalDeviceFeatures2 features2 = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
        .pNext = &vk13Features,
    };
    vkGetPhysicalDeviceFeatures2(device, &features2);

    // Only extended_dynamic_state3 capability this backend needs: a dynamic
    // blend-enable toggle (the blend equation itself is fixed).
    return eds3Features.extendedDynamicState3ColorBlendEnable &&
           vk13Features.dynamicRendering && vk13Features.synchronization2 &&
           vk12Features.timelineSemaphore;
}

// Creates a throwaway instance, checks at least one physical device meets
// device_is_suitable(), then destroys everything. No VkDevice/window is
// created.
bool gfx_vulkan_probe_support(void) {
    if (volkInitialize() != VK_SUCCESS) {
        return false;
    }

    VkApplicationInfo appInfo = {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .apiVersion = VK_API_VERSION_1_3,
    };
    VkInstanceCreateInfo createInfo = {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &appInfo,
    };

    VkInstance instance = VK_NULL_HANDLE;
    if (vkCreateInstance(&createInfo, NULL, &instance) != VK_SUCCESS) {
        return false;
    }
    volkLoadInstanceOnly(instance);

    uint32_t deviceCount = 0;
    bool supported = false;
    if (vkEnumeratePhysicalDevices(instance, &deviceCount, NULL) == VK_SUCCESS && deviceCount > 0) {
        VkPhysicalDevice* devices = malloc(deviceCount * sizeof(VkPhysicalDevice));
        if (devices && vkEnumeratePhysicalDevices(instance, &deviceCount, devices) == VK_SUCCESS) {
            for (uint32_t i = 0; i < deviceCount && !supported; i++) {
                supported = device_is_suitable(devices[i]);
            }
        }
        free(devices);
    }

    vkDestroyInstance(instance, NULL);
    return supported;
}

// --- GfxRenderingAPI --------------------------------------------------------
// The functions below implement struct GfxRenderingAPI (assembled at the
// bottom of this file), most as thin delegates to the specialized module
// that owns the real logic (gfx_vulkan_texture/shader/pipeline/draw.c).

// Tracks the ShaderProgram most recently made current (mirrors gfx_opengl.c's
// `opengl_prg`) - draw_triangles needs it to know which pipeline/textures to bind.
static struct ShaderProgram *sCurrentShader = NULL;
static uint32_t sFrameCount = 0;

// GfxRenderingAPI::z_is_from_0_to_1 - Vulkan's depth range is [0,1].
static bool gfx_vulkan_renderer_z_is_from_0_to_1(void) {
    return true;
}

// GfxRenderingAPI::unload_shader - no-op: vertex input is baked into each
// pipeline, so there's no GL-style attribute state to tear down.
static void gfx_vulkan_renderer_unload_shader(UNUSED struct ShaderProgram *old_prg) {
}

// GfxRenderingAPI::load_shader
static void gfx_vulkan_renderer_load_shader(struct ShaderProgram *new_prg) {
    sCurrentShader = new_prg;
}

// GfxRenderingAPI::create_and_load_new_shader
static struct ShaderProgram *gfx_vulkan_renderer_create_and_load_new_shader(struct ColorCombiner* cc) {
    struct ShaderProgram *prg = gfx_vulkan_shader_create_and_load(cc);
    sCurrentShader = prg; // mirrors gfx_opengl.c: create_and_load also makes it current
    return prg;
}

// GfxRenderingAPI::lookup_shader
static struct ShaderProgram *gfx_vulkan_renderer_lookup_shader(struct ColorCombiner* cc) {
    return gfx_vulkan_shader_lookup(cc);
}

// GfxRenderingAPI::shader_get_info
static void gfx_vulkan_renderer_shader_get_info(struct ShaderProgram *prg, uint8_t *num_inputs, bool used_textures[2]) {
    if (!prg) {
        // Shader compile failure (see gfx_vulkan_shader.c) - degrade to "no
        // textures, no inputs" instead of dereferencing NULL. gfx_opengl.c
        // can't hit this path (it sys_fatal()s on compile failure instead).
        *num_inputs = 0;
        used_textures[0] = false;
        used_textures[1] = false;
        return;
    }
    gfx_vulkan_shader_get_info(prg, num_inputs, used_textures);
}

// GfxRenderingAPI::new_texture
static uint32_t gfx_vulkan_renderer_new_texture(void) {
    return gfx_vulkan_texture_new();
}

// GfxRenderingAPI::select_texture
static void gfx_vulkan_renderer_select_texture(int tile, uint32_t texture_id) {
    gfx_vulkan_texture_select(tile, texture_id);
}

// GfxRenderingAPI::upload_texture
static void gfx_vulkan_renderer_upload_texture(const uint8_t *rgba32_buf, int width, int height) {
    gfx_vulkan_texture_upload(rgba32_buf, width, height);
}

// GfxRenderingAPI::set_sampler_parameters
static void gfx_vulkan_renderer_set_sampler_parameters(int sampler, bool linear_filter, uint32_t cms, uint32_t cmt) {
    gfx_vulkan_texture_set_sampler_parameters(sampler, linear_filter, cms, cmt);
}

// GfxRenderingAPI::set_depth_test
static void gfx_vulkan_renderer_set_depth_test(bool depth_test) {
    gfx_vulkan_draw_set_depth_test(depth_test);
}

// GfxRenderingAPI::set_depth_mask
static void gfx_vulkan_renderer_set_depth_mask(bool z_upd) {
    gfx_vulkan_draw_set_depth_mask(z_upd);
}

// GfxRenderingAPI::set_zmode_decal
static void gfx_vulkan_renderer_set_zmode_decal(bool zmode_decal) {
    gfx_vulkan_draw_set_zmode_decal(zmode_decal);
}

// GfxRenderingAPI::set_viewport
static void gfx_vulkan_renderer_set_viewport(int x, int y, int width, int height) {
    gfx_vulkan_draw_set_viewport(x, y, width, height);
}

// GfxRenderingAPI::set_scissor
static void gfx_vulkan_renderer_set_scissor(int x, int y, int width, int height) {
    gfx_vulkan_draw_set_scissor(x, y, width, height);
}

// GfxRenderingAPI::set_use_alpha
static void gfx_vulkan_renderer_set_use_alpha(bool use_alpha) {
    gfx_vulkan_draw_set_use_alpha(use_alpha);
}

// GfxRenderingAPI::draw_triangles
static void gfx_vulkan_renderer_draw_triangles(float buf_vbo[], size_t buf_vbo_len, size_t buf_vbo_num_tris) {
    gfx_vulkan_draw_triangles(sCurrentShader, buf_vbo, buf_vbo_len, buf_vbo_num_tris);
}

// Set once gfx_vulkan_renderer_init() completes every step successfully.
// GfxRenderingAPI::init() returns void, so a failure partway through can't be
// reported back to select_graphics_backend for a fallback to another backend
// - a known, unresolved gap in the shared contract. Every other lifecycle
// function below guards on this flag so a failed init degrades to "black,
// unresponsive Vulkan window" instead of crashing on uninitialized handles.
static bool sInitOk = false;

// GfxWindowBackendAPI glue for gfx_window_vulkan.c (see gfx_vulkan.h) -
// drops the frame if init failed or the swapchain acquire itself fails.
bool gfx_vulkan_start_frame(void) {
    if (!sInitOk) { return false; }
    return gfx_vulkan_frame_start();
}

// GfxRenderingAPI::init - brings up every backend subsystem in dependency
// order (context -> VMA -> swapchain -> frame resources -> textures ->
// shaders -> pipeline layout -> vertex streaming). Aborts on the first
// failure and unwinds only the subsystems that finished initializing, via
// the fail_* labels below.
//
// Every destroy_* function used in that unwind is safe to call on an
// already-torn-down or never-initialized subsystem, EXCEPT
// gfx_vulkan_shader_destroy(): it calls glslang_finalize_process(), which
// asserts if called without a matching glslang_initialize_process(), so the
// labels are ordered to only reach it when gfx_vulkan_shader_init() is known
// to have succeeded (unwinding from fail_pipeline or later, never fail_shader).
static void gfx_vulkan_renderer_init(void) {
    struct SDL_Window *window = gfx_wm_get_window();

    if (!gfx_vulkan_context_init(window)) {
        fprintf(stderr, "[vulkan] failed to initialize instance/device\n");
        return;
    }
    // VMA must exist before the first swapchain_create call: the swapchain
    // also allocates a depth image through it.
    if (!gfx_vulkan_memory_init()) {
        fprintf(stderr, "[vulkan] failed to initialize VMA\n");
        goto fail_memory;
    }
    if (!gfx_vulkan_swapchain_create(window)) {
        fprintf(stderr, "[vulkan] failed to create swapchain\n");
        goto fail_swapchain;
    }
    if (!gfx_vulkan_frame_init(window)) {
        fprintf(stderr, "[vulkan] failed to initialize frame resources\n");
        goto fail_frame;
    }
    if (!gfx_vulkan_texture_init()) {
        fprintf(stderr, "[vulkan] failed to initialize texture subsystem\n");
        goto fail_texture;
    }
    if (!gfx_vulkan_shader_init()) {
        fprintf(stderr, "[vulkan] failed to initialize glslang\n");
        goto fail_shader;
    }
    if (!gfx_vulkan_pipeline_init()) {
        fprintf(stderr, "[vulkan] failed to initialize shared pipeline layout/frame UBO\n");
        goto fail_pipeline;
    }
    if (!gfx_vulkan_draw_init()) {
        fprintf(stderr, "[vulkan] failed to initialize vertex streaming arenas\n");
        goto fail_draw;
    }

    sInitOk = true;
    return;

fail_draw:
    gfx_vulkan_pipeline_destroy();
fail_pipeline:
    gfx_vulkan_shader_destroy();
fail_shader:
    gfx_vulkan_texture_destroy();
fail_texture:
    gfx_vulkan_frame_destroy();
fail_frame:
    gfx_vulkan_swapchain_destroy();
fail_swapchain:
    gfx_vulkan_memory_destroy();
fail_memory:
    gfx_vulkan_context_destroy();
}

// GfxRenderingAPI::on_resize
static void gfx_vulkan_renderer_on_resize(void) {
    if (!sInitOk) { return; }
    gfx_vulkan_frame_notify_resize();
}

// GfxRenderingAPI::start_frame - begins the rendering pass and refreshes the
// per-frame UBO/dynamic state before any draw_triangles call this frame.
static void gfx_vulkan_renderer_start_frame(void) {
    if (!sInitOk) { return; }
    sFrameCount++;
    gfx_vulkan_frame_begin_rendering();
    gfx_vulkan_draw_begin_frame();
    gfx_vulkan_pipeline_update_frame_ubo(sFrameCount);
}

// GfxRenderingAPI::end_frame
static void gfx_vulkan_renderer_end_frame(void) {
    if (!sInitOk) { return; }
    gfx_vulkan_frame_end_and_submit();
}

// GfxRenderingAPI::finish_render
static void gfx_vulkan_renderer_finish_render(void) {
    if (!sInitOk) { return; }
    gfx_vulkan_frame_present();
}

// GfxRenderingAPI::get_name
static const char* gfx_vulkan_renderer_get_name(void) {
    return "Vulkan";
}

// GfxRenderingAPI::shutdown - tears down every subsystem in reverse
// dependency order to the one gfx_vulkan_renderer_init() built.
static void gfx_vulkan_renderer_shutdown(void) {
    if (!sInitOk) { return; }
    sInitOk = false;

    if (gfxVkDevice != VK_NULL_HANDLE) {
        vkDeviceWaitIdle(gfxVkDevice);
    }
    sCurrentShader = NULL;
    gfx_vulkan_draw_destroy();
    gfx_vulkan_pipeline_destroy();
    gfx_vulkan_shader_destroy();
    gfx_vulkan_texture_destroy();
    gfx_vulkan_frame_destroy();
    // The swapchain owns a VMA-backed depth image, so it must be torn down
    // before the VMA allocator itself.
    gfx_vulkan_swapchain_destroy();
    gfx_vulkan_memory_destroy();
    gfx_vulkan_context_destroy();
}

struct GfxRenderingAPI gfx_vulkan_api = {
    gfx_vulkan_renderer_z_is_from_0_to_1,
    gfx_vulkan_renderer_unload_shader,
    gfx_vulkan_renderer_load_shader,
    gfx_vulkan_renderer_create_and_load_new_shader,
    gfx_vulkan_renderer_lookup_shader,
    gfx_vulkan_renderer_shader_get_info,
    gfx_vulkan_renderer_new_texture,
    gfx_vulkan_renderer_select_texture,
    gfx_vulkan_renderer_upload_texture,
    gfx_vulkan_renderer_set_sampler_parameters,
    gfx_vulkan_renderer_set_depth_test,
    gfx_vulkan_renderer_set_depth_mask,
    gfx_vulkan_renderer_set_zmode_decal,
    gfx_vulkan_renderer_set_viewport,
    gfx_vulkan_renderer_set_scissor,
    gfx_vulkan_renderer_set_use_alpha,
    gfx_vulkan_renderer_draw_triangles,
    gfx_vulkan_renderer_init,
    gfx_vulkan_renderer_on_resize,
    gfx_vulkan_renderer_start_frame,
    gfx_vulkan_renderer_end_frame,
    gfx_vulkan_renderer_finish_render,
    gfx_vulkan_renderer_get_name,
    gfx_vulkan_renderer_shutdown
};

#endif // ENABLE_VULKAN
