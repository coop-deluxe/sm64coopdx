// Vulkan backend for GfxRenderingAPI/GfxWindowBackendAPI, in one translation
// unit (see gfx_window_vulkan.c for the window/event side).
//
// Hard requirements enforced at physical-device selection (pick_physical_device
// below): Vulkan 1.3 (dynamic rendering + synchronization2 are core only from
// there), plus three things that are NOT part of the 1.3 core feature struct
// and have to be requested explicitly even on a 1.3-capable device:
// VK_EXT_extended_dynamic_state3's colorBlendEnable (the only per-draw
// pipeline toggle this backend uses, to avoid a pipeline-variant explosion),
// VK_KHR_push_descriptor (per-draw texture binding without descriptor pools),
// and timelineSemaphore (a Vulkan 1.2 feature bit, used for frame-in-flight
// sync - 1.3 support doesn't imply it's enabled).
//
// This backend never creates a VkRenderPass/VkFramebuffer (core 1.3 dynamic
// rendering only), and builds one VkPipeline per distinct Color Combiner the
// game encounters, exactly like gfx_opengl.c compiles one GLSL program per CC
// - gfx_vulkan_shader_create_and_load() below generates the GLSL text (ported
// formula-for-formula from gfx_opengl.c's generator), compiles it to SPIR-V
// via glslang (chosen over shaderc specifically to avoid also pulling in
// SPIRV-Tools), and bakes a VkPipeline around it, cached by CC hash.
//
// Dependencies: volk (<volk.h>, loads Vulkan entry points at runtime - no
// libvulkan link dependency beyond dlopen, hence -ldl on Linux, see the
// Makefile) and VMA (<vk_mem_alloc.h>, buffer/image suballocation - only its
// implementation TU, gfx_vulkan_vma.cpp, still lives in this repo) now both
// come from system packages (libvulkan-volk-dev / libvulkan-memory-allocator-dev
// on Debian - watch out, "libvolk-dev" without "vulkan-" in the name is an
// unrelated GNU Radio package) instead of being vendored. glslang stays
// vendored under gfx_vulkan/ pending upstream changes.

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

#ifndef _LANGUAGE_C
# define _LANGUAGE_C
#endif
#include <PR/gbi.h>

#include "macros.h"
#include "gfx_vulkan.h"
#include <volk.h>
#include <vk_mem_alloc.h>
#include "gfx_cc.h"
#include "gfx_pc.h"
#include "gfx_window_manager.h"
#include "../configfile.h"
#include "../fs/fs.h"
#include "../platform.h"
#include "../terminal.h"

#include "glslang/Include/glslang_c_interface.h"
#include "glslang/Public/resource_limits_c.h"

//////////////////////////////////////////////////////////////////////////////
// Shared types - used across more than one section below. struct ShaderProgram
// in particular has to be a complete type before the pipeline section (it
// dereferences prg->pipeline/num_floats/attrib_sizes etc. when building a
// VkPipeline), even though shader creation itself is defined further down and
// calls into the pipeline section - the two are mutually dependent, so their
// shared type comes first and both sections rely on ordinary top-down
// function ordering after that.
//////////////////////////////////////////////////////////////////////////////

// Number of frame-in-flight slots (command pool/buffer, semaphores, and one
// slice each of the per-frame UBO and the vertex streaming arena). Anything
// sized per-slot and only written while that slot is "current" is
// automatically safe from the CPU overwriting data the GPU hasn't read yet,
// since gfx_vulkan_frame_start() already waits on a slot's previous
// submission before reusing it.
#define GFX_VULKAN_FRAMES_IN_FLIGHT 2

// Vertex attribute count upper bound: 1 (position) + 2 (texcoords) + 1 (fog)
// + 1 (light map) + 2 (up to 2 CC inputs, gfx_cc.c never generates more - see
// gfx_opengl.c's identically-sized attrib_sizes array).
#define GFX_VULKAN_MAX_ATTRIBS 7

// Thin wrapper over VMA (gfx_vulkan_vma.cpp/.h) - the only functions allowed
// to call vma* directly are in the "Memory" section below. Callers get plain
// Vk handles plus an opaque allocation handle, so gfx_vulkan_vma.h never needs
// to be included anywhere else.
typedef struct {
    VkBuffer buffer;
    void *allocation; // VmaAllocation, kept opaque here on purpose
} GfxVulkanBuffer;

typedef struct {
    VkImage image;
    VkImageView view;
    void *allocation; // VmaAllocation, kept opaque here on purpose
} GfxVulkanImage;

// Concrete definition of the opaque `struct ShaderProgram*` the
// GfxRenderingAPI contract passes around. Mirrors gfx_opengl.c's own struct
// ShaderProgram field-for-field where the concept carries over, swapping GL
// program/attrib-location state for the VkPipeline this ColorCombiner
// compiled to.
struct ShaderProgram {
    uint64_t hash;
    VkPipeline pipeline; // owned by the "Pipeline" section below

    uint8_t num_inputs;
    bool used_textures[2];
    bool opt_alpha;
    bool used_noise;
    bool used_lightmap;
    bool world_geometry;

    uint8_t num_floats; // vertex stride, in floats
    uint8_t num_attribs;
    uint8_t attrib_sizes[GFX_VULKAN_MAX_ATTRIBS]; // in floats, cumulative offset = running sum
};

// Pushed once per draw_triangles call: size/filter of whichever of the up to
// 2 textures the active ColorCombiner samples. Layout must match
// `PushConstants` in the generated fragment shader (see the "Shader" section
// below) - push_constant blocks use std430 rules implicitly, hence the
// explicit pad.
typedef struct {
    float tex0Size[2];
    int32_t tex0Filter;
    float _pad0;
    float tex1Size[2];
    int32_t tex1Filter;
} GfxVulkanDrawPushConstants;

//////////////////////////////////////////////////////////////////////////////
// Debug labels (VK_EXT_debug_utils) - DEVELOPMENT-only labels for GPU
// debuggers such as RenderDoc. Defined unconditionally so call sites never
// need their own #ifdef DEVELOPMENT: outside DEVELOPMENT builds these compile
// to no-ops. Callers that build a label string (snprintf etc.) should still
// guard that construction with #ifdef DEVELOPMENT to avoid the cost in
// release builds.
//
// VK_EXT_debug_utils itself is only requested when the validation layer is
// also present (see create_instance below), so these labels are silent no-ops
// on machines without VK_LAYER_KHRONOS_validation installed, same as the
// debug messenger.
//////////////////////////////////////////////////////////////////////////////

#if defined(DEVELOPMENT)

// Opens a named debug label region on cmd, visible in GPU debugger event browsers.
static void gfx_vulkan_debug_begin_label(VkCommandBuffer cmd, const char *name) {
    if (!vkCmdBeginDebugUtilsLabelEXT) {
        return; // VK_EXT_debug_utils wasn't enabled (no validation layer available)
    }
    VkDebugUtilsLabelEXT label = {
        .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT,
        .pLabelName = name,
    };
    vkCmdBeginDebugUtilsLabelEXT(cmd, &label);
}

// Closes the label region opened by gfx_vulkan_debug_begin_label.
static void gfx_vulkan_debug_end_label(VkCommandBuffer cmd) {
    if (!vkCmdEndDebugUtilsLabelEXT) {
        return;
    }
    vkCmdEndDebugUtilsLabelEXT(cmd);
}

#else

// No-op outside DEVELOPMENT builds - see the comment above this section.
static void gfx_vulkan_debug_begin_label(UNUSED VkCommandBuffer cmd, UNUSED const char *name) {
}

static void gfx_vulkan_debug_end_label(UNUSED VkCommandBuffer cmd) {
}

#endif // DEVELOPMENT

//////////////////////////////////////////////////////////////////////////////
// Context - owns VkInstance/VkSurfaceKHR/VkPhysicalDevice/VkDevice/VkQueue for
// the lifetime of the Vulkan backend. The surface is created here (not in the
// "Swapchain" section) because physical device selection needs it to verify
// presentation support before a VkDevice exists; the swapchain section only
// owns the VkSwapchainKHR/VkImageView[] built on top of it.
//////////////////////////////////////////////////////////////////////////////

static VkInstance gfxVkInstance = VK_NULL_HANDLE;
static VkSurfaceKHR gfxVkSurface = VK_NULL_HANDLE;
static VkPhysicalDevice gfxVkPhysicalDevice = VK_NULL_HANDLE;
static VkDevice gfxVkDevice = VK_NULL_HANDLE;
static VkQueue gfxVkQueue = VK_NULL_HANDLE;
static uint32_t gfxVkQueueFamily = UINT32_MAX;

#ifdef DEVELOPMENT
static VkDebugUtilsMessengerEXT sDebugMessenger = VK_NULL_HANDLE;

// Forwards validation layer warnings/errors to stderr, prefixed "[vulkan]".
static VKAPI_ATTR VkBool32 VKAPI_CALL gfx_vulkan_debug_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT severity,
    UNUSED VkDebugUtilsMessageTypeFlagsEXT type,
    const VkDebugUtilsMessengerCallbackDataEXT *data,
    UNUSED void *userData) {
    if (severity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
        log_to_terminal("[vulkan] %s\n", data->pMessage);
    }
    return VK_FALSE;
}

// Checks whether VK_LAYER_KHRONOS_validation is installed on this system.
static bool has_validation_layer(void) {
    uint32_t count = 0;
    if (vkEnumerateInstanceLayerProperties(&count, NULL) != VK_SUCCESS || count == 0) {
        return false;
    }

    VkLayerProperties *layers = malloc(count * sizeof(VkLayerProperties));
    if (!layers) {
        return false;
    }

    bool found = false;
    if (vkEnumerateInstanceLayerProperties(&count, layers) == VK_SUCCESS) {
        for (uint32_t i = 0; i < count; i++) {
            if (strcmp(layers[i].layerName, "VK_LAYER_KHRONOS_validation") == 0) {
                found = true;
                break;
            }
        }
    }

    free(layers);
    return found;
}
#endif

// Checks whether `device` reports `extensionName` as a supported device
// extension. Shared by pick_physical_device() below and device_is_suitable()
// (gfx_vulkan_probe_support's throwaway-instance capability check, at the
// bottom of this file) - both apply the exact same suitability rule.
static bool device_has_extension(VkPhysicalDevice device, const char *extensionName) {
    uint32_t count = 0;
    if (vkEnumerateDeviceExtensionProperties(device, NULL, &count, NULL) != VK_SUCCESS || count == 0) {
        return false;
    }

    VkExtensionProperties *props = malloc(count * sizeof(VkExtensionProperties));
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

// Creates gfxVkInstance, requesting the SDL-required surface extensions plus
// debug utils (DEVELOPMENT builds, if the validation layer is present) and
// the macOS portability extensions.
static bool create_instance(struct SDL_Window *window) {
    unsigned int sdlExtCount = 0;
    if (!SDL_Vulkan_GetInstanceExtensions((SDL_Window *)window, &sdlExtCount, NULL)) {
        return false;
    }

    unsigned int extCount = sdlExtCount;
#ifdef DEVELOPMENT
    bool useValidation = has_validation_layer();
    if (useValidation) { extCount += 1; }
#endif
#ifdef OSX_BUILD
    extCount += 2;
#endif

    const char **extensions = malloc(extCount * sizeof(const char *));
    if (!extensions) {
        return false;
    }

    if (!SDL_Vulkan_GetInstanceExtensions((SDL_Window *)window, &sdlExtCount, extensions)) {
        free(extensions);
        return false;
    }

#if defined(DEVELOPMENT) || defined(OSX_BUILD)
    unsigned int idx = sdlExtCount;
#endif
#ifdef DEVELOPMENT
    if (useValidation) {
        extensions[idx++] = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;
    }
#endif
#ifdef OSX_BUILD
    // MoltenVK (Vulkan-over-Metal) requires both of these instance extensions
    // plus VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR below.
    extensions[idx++] = VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME;
    extensions[idx++] = VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME;
#endif

    VkApplicationInfo appInfo = {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = "sm64coopdx",
        .apiVersion = VK_API_VERSION_1_3,
    };

    VkInstanceCreateInfo createInfo = {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &appInfo,
        .enabledExtensionCount = extCount,
        .ppEnabledExtensionNames = extensions,
    };
#ifdef OSX_BUILD
    createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
#endif

    const char *validationLayerName = "VK_LAYER_KHRONOS_validation";
#ifdef DEVELOPMENT
    if (useValidation) {
        createInfo.enabledLayerCount = 1;
        createInfo.ppEnabledLayerNames = &validationLayerName;
    }
#else
    (void)validationLayerName;
#endif

    VkResult res = vkCreateInstance(&createInfo, NULL, &gfxVkInstance);
    free(extensions);
    if (res != VK_SUCCESS) {
        return false;
    }

    volkLoadInstance(gfxVkInstance);
    return true;
}

#ifdef DEVELOPMENT
// Best-effort: a failure here doesn't fail the whole backend.
static void create_debug_messenger(void) {
    if (!vkCreateDebugUtilsMessengerEXT) {
        return; // VK_EXT_debug_utils wasn't enabled (no validation layer available)
    }

    VkDebugUtilsMessengerCreateInfoEXT createInfo = {
        .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
        .messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                            VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
        .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                        VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                        VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
        .pfnUserCallback = gfx_vulkan_debug_callback,
    };

    vkCreateDebugUtilsMessengerEXT(gfxVkInstance, &createInfo, NULL, &sDebugMessenger);
}
#endif

// Finds a queue family on `device` that supports both graphics and
// presentation to `surface`.
static bool find_graphics_present_queue_family(VkPhysicalDevice device, VkSurfaceKHR surface, uint32_t *outFamily) {
    uint32_t count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &count, NULL);
    if (count == 0) {
        return false;
    }

    VkQueueFamilyProperties *props = malloc(count * sizeof(VkQueueFamilyProperties));
    if (!props) {
        return false;
    }
    vkGetPhysicalDeviceQueueFamilyProperties(device, &count, props);

    bool found = false;
    for (uint32_t i = 0; i < count; i++) {
        if (!(props[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)) {
            continue;
        }
        VkBool32 presentSupport = VK_FALSE;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
        if (presentSupport) {
            *outFamily = i;
            found = true;
            break;
        }
    }

    free(props);
    return found;
}

// Picks the best suitable physical device (discrete > integrated > other),
// requiring Vulkan 1.3, VK_KHR_swapchain/extended_dynamic_state3/
// push_descriptor, the extended_dynamic_state3 blend-enable feature, dynamic
// rendering, synchronization2, timeline semaphores, and a combined
// graphics+present queue family.
static bool pick_physical_device(VkSurfaceKHR surface) {
    uint32_t count = 0;
    if (vkEnumeratePhysicalDevices(gfxVkInstance, &count, NULL) != VK_SUCCESS || count == 0) {
        return false;
    }

    VkPhysicalDevice *devices = malloc(count * sizeof(VkPhysicalDevice));
    if (!devices) {
        return false;
    }
    vkEnumeratePhysicalDevices(gfxVkInstance, &count, devices);

    VkPhysicalDevice best = VK_NULL_HANDLE;
    uint32_t bestFamily = UINT32_MAX;
    int bestScore = -1;

    for (uint32_t i = 0; i < count; i++) {
        VkPhysicalDevice device = devices[i];

        VkPhysicalDeviceProperties props;
        vkGetPhysicalDeviceProperties(device, &props);
        if (props.apiVersion < VK_API_VERSION_1_3) {
            continue; // dynamic rendering + synchronization2 are core only from 1.3
        }

        if (!device_has_extension(device, VK_KHR_SWAPCHAIN_EXTENSION_NAME) ||
            !device_has_extension(device, VK_EXT_EXTENDED_DYNAMIC_STATE_3_EXTENSION_NAME) ||
            !device_has_extension(device, VK_KHR_PUSH_DESCRIPTOR_EXTENSION_NAME)) {
            continue;
        }

        VkPhysicalDeviceExtendedDynamicState3FeaturesEXT eds3Features = {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_DYNAMIC_STATE_3_FEATURES_EXT,
        };
        // timelineSemaphore is a Vulkan 1.2 feature (VkPhysicalDeviceVulkan12Features),
        // not folded into VkPhysicalDeviceVulkan13Features - apiVersion >= 1.3
        // alone doesn't enable it, it's still opt-in like any other feature
        // bit. The frame section below relies on it for the frame timeline
        // semaphore (VK_SEMAPHORE_TYPE_TIMELINE).
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
        if (!eds3Features.extendedDynamicState3ColorBlendEnable ||
            !vk13Features.dynamicRendering || !vk13Features.synchronization2 ||
            !vk12Features.timelineSemaphore) {
            continue;
        }

        uint32_t family;
        if (!find_graphics_present_queue_family(device, surface, &family)) {
            continue;
        }

        int score = (props.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) ? 2 :
                    (props.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU) ? 1 : 0;

        if (score > bestScore) {
            bestScore = score;
            best = device;
            bestFamily = family;
        }
    }

    free(devices);

    if (best == VK_NULL_HANDLE) {
        return false;
    }

    gfxVkPhysicalDevice = best;
    gfxVkQueueFamily = bestFamily;
    return true;
}

// Creates the logical device and its single graphics+present queue, enabling
// the feature bits pick_physical_device() already confirmed are supported.
static bool create_device(void) {
    float priority = 1.0f;
    VkDeviceQueueCreateInfo queueInfo = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .queueFamilyIndex = gfxVkQueueFamily,
        .queueCount = 1,
        .pQueuePriorities = &priority,
    };

    const char *deviceExtensions[] = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME,
        VK_EXT_EXTENDED_DYNAMIC_STATE_3_EXTENSION_NAME,
        VK_KHR_PUSH_DESCRIPTOR_EXTENSION_NAME,
    };

    VkPhysicalDeviceExtendedDynamicState3FeaturesEXT eds3Features = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_DYNAMIC_STATE_3_FEATURES_EXT,
        .extendedDynamicState3ColorBlendEnable = VK_TRUE,
    };
    VkPhysicalDeviceVulkan12Features vk12Features = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES,
        .pNext = &eds3Features,
        .timelineSemaphore = VK_TRUE,
    };
    VkPhysicalDeviceVulkan13Features vk13Features = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES,
        .pNext = &vk12Features,
        .dynamicRendering = VK_TRUE,
        .synchronization2 = VK_TRUE,
    };
    VkPhysicalDeviceFeatures2 features2 = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
        .pNext = &vk13Features,
    };

    VkDeviceCreateInfo createInfo = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .pNext = &features2,
        .queueCreateInfoCount = 1,
        .pQueueCreateInfos = &queueInfo,
        .enabledExtensionCount = (uint32_t)(sizeof(deviceExtensions) / sizeof(deviceExtensions[0])),
        .ppEnabledExtensionNames = deviceExtensions,
    };

    if (vkCreateDevice(gfxVkPhysicalDevice, &createInfo, NULL, &gfxVkDevice) != VK_SUCCESS) {
        return false;
    }

    volkLoadDevice(gfxVkDevice);
    vkGetDeviceQueue(gfxVkDevice, gfxVkQueueFamily, 0, &gfxVkQueue);
    return true;
}

// Full bring-up: loader -> instance -> surface -> debug messenger (dev builds
// only) -> physical device -> logical device. Returns false on the first
// failed step; gfx_vulkan_context_destroy() is safe to call regardless of how
// far this got (every handle is checked against VK_NULL_HANDLE before being
// destroyed).
static bool gfx_vulkan_context_init(struct SDL_Window *window) {
    if (volkInitialize() != VK_SUCCESS) {
        return false;
    }

    if (!create_instance(window)) {
        return false;
    }

    if (!SDL_Vulkan_CreateSurface((SDL_Window *)window, gfxVkInstance, &gfxVkSurface)) {
        return false;
    }

#ifdef DEVELOPMENT
    create_debug_messenger();
#endif

    if (!pick_physical_device(gfxVkSurface)) {
        return false;
    }

    if (!create_device()) {
        return false;
    }

    return true;
}

// Destroys whatever gfx_vulkan_context_init() built, in reverse order. Safe
// to call regardless of how far init got (every handle is checked against
// VK_NULL_HANDLE first).
static void gfx_vulkan_context_destroy(void) {
    if (gfxVkDevice != VK_NULL_HANDLE) {
        vkDestroyDevice(gfxVkDevice, NULL);
        gfxVkDevice = VK_NULL_HANDLE;
    }

#ifdef DEVELOPMENT
    if (sDebugMessenger != VK_NULL_HANDLE && vkDestroyDebugUtilsMessengerEXT) {
        vkDestroyDebugUtilsMessengerEXT(gfxVkInstance, sDebugMessenger, NULL);
        sDebugMessenger = VK_NULL_HANDLE;
    }
#endif

    if (gfxVkSurface != VK_NULL_HANDLE) {
        vkDestroySurfaceKHR(gfxVkInstance, gfxVkSurface, NULL);
        gfxVkSurface = VK_NULL_HANDLE;
    }

    if (gfxVkInstance != VK_NULL_HANDLE) {
        vkDestroyInstance(gfxVkInstance, NULL);
        gfxVkInstance = VK_NULL_HANDLE;
    }

    gfxVkPhysicalDevice = VK_NULL_HANDLE;
    gfxVkQueue = VK_NULL_HANDLE;
    gfxVkQueueFamily = UINT32_MAX;
}

//////////////////////////////////////////////////////////////////////////////
// Memory - thin wrapper over VMA (gfx_vulkan_vma.cpp/.h). The only functions
// in this file allowed to call vma* directly.
//////////////////////////////////////////////////////////////////////////////

static VmaAllocator sAllocator = VK_NULL_HANDLE;

// Creates the VMA allocator, loading Vulkan entry points through volk instead
// of linking libvulkan directly (VMA_DYNAMIC_VULKAN_FUNCTIONS).
static bool gfx_vulkan_memory_init(void) {
    VmaVulkanFunctions vulkanFunctions = { 0 };
    vulkanFunctions.vkGetInstanceProcAddr = vkGetInstanceProcAddr;
    vulkanFunctions.vkGetDeviceProcAddr = vkGetDeviceProcAddr;

    VmaAllocatorCreateInfo createInfo = { 0 };
    createInfo.vulkanApiVersion = VK_API_VERSION_1_3;
    createInfo.physicalDevice = gfxVkPhysicalDevice;
    createInfo.device = gfxVkDevice;
    createInfo.instance = gfxVkInstance;
    createInfo.pVulkanFunctions = &vulkanFunctions;

    return vmaCreateAllocator(&createInfo, &sAllocator) == VK_SUCCESS;
}

// Safe to call even if gfx_vulkan_memory_init() was never called (no-op).
static void gfx_vulkan_memory_destroy(void) {
    if (sAllocator != VK_NULL_HANDLE) {
        vmaDestroyAllocator(sAllocator);
        sAllocator = VK_NULL_HANDLE;
    }
}

// Shared implementation behind the two public create_*_buffer helpers below.
static bool create_buffer(VkDeviceSize size, VkBufferUsageFlags usage, VmaAllocationCreateFlags allocFlags,
                           VmaMemoryUsage memUsage, GfxVulkanBuffer *out, void **outMappedPtr) {
    VkBufferCreateInfo bufferInfo = {
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .size = size,
        .usage = usage,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
    };
    VmaAllocationCreateInfo allocInfo = { 0 };
    allocInfo.usage = memUsage;
    allocInfo.flags = allocFlags;

    VkBuffer buffer = VK_NULL_HANDLE;
    VmaAllocation allocation = VK_NULL_HANDLE;
    VmaAllocationInfo allocationInfo;
    if (vmaCreateBuffer(sAllocator, &bufferInfo, &allocInfo, &buffer, &allocation, &allocationInfo) != VK_SUCCESS) {
        return false;
    }

    out->buffer = buffer;
    out->allocation = (void *)allocation;
    if (outMappedPtr) {
        *outMappedPtr = allocationInfo.pMappedData;
    }
    return true;
}

// Device-local, no CPU access - data written once via a staging buffer and
// read many times by the GPU.
static bool gfx_vulkan_memory_create_device_local_buffer(VkDeviceSize size, VkBufferUsageFlags usage, GfxVulkanBuffer *out) {
    return create_buffer(size, usage, 0, VMA_MEMORY_USAGE_AUTO_PREFER_DEVICE, out, NULL);
}

// Host-visible, persistently mapped - for data the CPU writes often (texture
// staging uploads, per-frame vertex streaming). *outMappedPtr stays valid for
// the buffer's lifetime; pass NULL if not needed.
static bool gfx_vulkan_memory_create_streaming_buffer(VkDeviceSize size, VkBufferUsageFlags usage, GfxVulkanBuffer *out, void **outMappedPtr) {
    VmaAllocationCreateFlags flags = VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT | VMA_ALLOCATION_CREATE_MAPPED_BIT;
    return create_buffer(size, usage, flags, VMA_MEMORY_USAGE_AUTO, out, outMappedPtr);
}

// Safe to call on an already-empty/zeroed GfxVulkanBuffer (no-op).
static void gfx_vulkan_memory_destroy_buffer(GfxVulkanBuffer *buf) {
    if (!buf || buf->buffer == VK_NULL_HANDLE) {
        return;
    }
    vmaDestroyBuffer(sAllocator, buf->buffer, (VmaAllocation)buf->allocation);
    buf->buffer = VK_NULL_HANDLE;
    buf->allocation = NULL;
}

// Device-local 2D image + a matching VK_IMAGE_VIEW_TYPE_2D view (aspect mask
// given by `aspect` - COLOR_BIT for textures/color images, DEPTH_BIT for the
// depth buffer) over its full extent, one mip level, one array layer. Starts
// in VK_IMAGE_LAYOUT_UNDEFINED; the caller is responsible for any layout
// transitions.
static bool gfx_vulkan_memory_create_image(uint32_t width, uint32_t height, VkFormat format, VkImageUsageFlags usage, VkImageAspectFlags aspect, GfxVulkanImage *out) {
    VkImageCreateInfo imageInfo = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        .imageType = VK_IMAGE_TYPE_2D,
        .format = format,
        .extent = { width, height, 1 },
        .mipLevels = 1,
        .arrayLayers = 1,
        .samples = VK_SAMPLE_COUNT_1_BIT,
        .tiling = VK_IMAGE_TILING_OPTIMAL,
        .usage = usage,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
        .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
    };
    VmaAllocationCreateInfo allocInfo = { 0 };
    allocInfo.usage = VMA_MEMORY_USAGE_AUTO_PREFER_DEVICE;

    VkImage image = VK_NULL_HANDLE;
    VmaAllocation allocation = VK_NULL_HANDLE;
    if (vmaCreateImage(sAllocator, &imageInfo, &allocInfo, &image, &allocation, NULL) != VK_SUCCESS) {
        return false;
    }

    VkImageViewCreateInfo viewInfo = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        .image = image,
        .viewType = VK_IMAGE_VIEW_TYPE_2D,
        .format = format,
        .subresourceRange = { aspect, 0, 1, 0, 1 },
    };
    VkImageView view = VK_NULL_HANDLE;
    if (vkCreateImageView(gfxVkDevice, &viewInfo, NULL, &view) != VK_SUCCESS) {
        vmaDestroyImage(sAllocator, image, allocation);
        return false;
    }

    out->image = image;
    out->view = view;
    out->allocation = (void *)allocation;
    return true;
}

// Safe to call on an already-empty/zeroed GfxVulkanImage (no-op).
static void gfx_vulkan_memory_destroy_image(GfxVulkanImage *img) {
    if (!img || img->image == VK_NULL_HANDLE) {
        return;
    }
    if (img->view != VK_NULL_HANDLE) {
        vkDestroyImageView(gfxVkDevice, img->view, NULL);
    }
    vmaDestroyImage(sAllocator, img->image, (VmaAllocation)img->allocation);
    memset(img, 0, sizeof(*img));
}

//////////////////////////////////////////////////////////////////////////////
// Swapchain - VkSwapchainKHR + color image views + depth image, built on top
// of the surface/device owned by the Context section above. Safe to
// (re)create on an existing swapchain (e.g. on resize) - destroys the
// previous one first.
//
// NOTE: gfx_vulkan_swapchain_create can fail after the previous swapchain has
// already been torn down (vkCreateSwapchainKHR itself failing leaves
// gfxVkSwapchain == VK_NULL_HANDLE; a VkImageView/depth image failing to
// create instead leaves gfxVkSwapchain valid but
// gfxVkSwapchainImageViews/gfxVkDepthImage incomplete). Callers must not
// assume a false return leaves the previous state untouched - see
// recreate_swapchain() in the Frame section below, which re-arms its dirty
// flag on failure so the next frame retries instead of using this half-built
// state.
//////////////////////////////////////////////////////////////////////////////

static VkSwapchainKHR gfxVkSwapchain = VK_NULL_HANDLE;
static VkFormat gfxVkSwapchainFormat = VK_FORMAT_UNDEFINED;
static VkExtent2D gfxVkSwapchainExtent = { 0, 0 };
static VkImage *gfxVkSwapchainImages = NULL;
static VkImageView *gfxVkSwapchainImageViews = NULL;
static uint32_t gfxVkSwapchainImageCount = 0;

// Depth buffer, recreated alongside the color swapchain images on every
// gfx_vulkan_swapchain_create() call (same extent, same lifetime).
// gfxVkDepthFormat is a pure-depth (no stencil) format - VK_FORMAT_D32_SFLOAT
// or VK_FORMAT_X8_D24_UNORM_PACK32, at least one of which the Vulkan spec
// mandates DEPTH_STENCIL_ATTACHMENT_BIT support for with optimal tiling on
// every conformant device - so the Pipeline section below can bake it into
// every pipeline's VkPipelineRenderingCreateInfo unconditionally.
static VkImage gfxVkDepthImage = VK_NULL_HANDLE;
static VkImageView gfxVkDepthImageView = VK_NULL_HANDLE;
static VkFormat gfxVkDepthFormat = VK_FORMAT_UNDEFINED;
static GfxVulkanImage sDepthImage;

// Picks a supported pure-depth format, preferring the highest precision.
static VkFormat choose_depth_format(void) {
    VkFormat candidates[] = { VK_FORMAT_D32_SFLOAT, VK_FORMAT_X8_D24_UNORM_PACK32 };
    for (size_t i = 0; i < sizeof(candidates) / sizeof(candidates[0]); i++) {
        VkFormatProperties props;
        vkGetPhysicalDeviceFormatProperties(gfxVkPhysicalDevice, candidates[i], &props);
        if (props.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) {
            return candidates[i];
        }
    }
    return VK_FORMAT_D32_SFLOAT; // one of the two above is spec-mandatory on any conformant device
}

// Safe to call even if no depth image exists yet (no-op).
static void destroy_depth_image(void) {
    gfx_vulkan_memory_destroy_image(&sDepthImage);
    gfxVkDepthImage = VK_NULL_HANDLE;
    gfxVkDepthImageView = VK_NULL_HANDLE;
}

// Allocates the depth image/view at `extent`, picking gfxVkDepthFormat once
// and reusing it on every later call.
static bool create_depth_image(VkExtent2D extent) {
    if (gfxVkDepthFormat == VK_FORMAT_UNDEFINED) {
        gfxVkDepthFormat = choose_depth_format();
    }
    if (!gfx_vulkan_memory_create_image(extent.width, extent.height, gfxVkDepthFormat,
                                         VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
                                         VK_IMAGE_ASPECT_DEPTH_BIT, &sDepthImage)) {
        return false;
    }
    gfxVkDepthImage = sDepthImage.image;
    gfxVkDepthImageView = sDepthImage.view;
    return true;
}

// Picks BGRA8_UNORM/SRGB_NONLINEAR if the surface supports it, else the
// surface's first reported format.
static VkSurfaceFormatKHR choose_surface_format(void) {
    uint32_t count = 0;
    vkGetPhysicalDeviceSurfaceFormatsKHR(gfxVkPhysicalDevice, gfxVkSurface, &count, NULL);

    VkSurfaceFormatKHR chosen = { VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };
    if (count == 0) {
        return chosen;
    }

    VkSurfaceFormatKHR *formats = malloc(count * sizeof(VkSurfaceFormatKHR));
    if (!formats) {
        return chosen;
    }
    vkGetPhysicalDeviceSurfaceFormatsKHR(gfxVkPhysicalDevice, gfxVkSurface, &count, formats);

    chosen = formats[0];
    for (uint32_t i = 0; i < count; i++) {
        if (formats[i].format == VK_FORMAT_B8G8R8A8_UNORM &&
            formats[i].colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            chosen = formats[i];
            break;
        }
    }

    free(formats);
    return chosen;
}

// FIFO when vsync is on (always available, blocks like classic double
// buffering). Otherwise prefers MAILBOX, falls back to IMMEDIATE, and
// defaults to FIFO if neither is reported.
static VkPresentModeKHR choose_present_mode(void) {
    if (configWindow.vsync) {
        return VK_PRESENT_MODE_FIFO_KHR; // always guaranteed to be available
    }

    uint32_t count = 0;
    vkGetPhysicalDeviceSurfacePresentModesKHR(gfxVkPhysicalDevice, gfxVkSurface, &count, NULL);
    if (count == 0) {
        return VK_PRESENT_MODE_FIFO_KHR;
    }

    VkPresentModeKHR *modes = malloc(count * sizeof(VkPresentModeKHR));
    if (!modes) {
        return VK_PRESENT_MODE_FIFO_KHR;
    }
    vkGetPhysicalDeviceSurfacePresentModesKHR(gfxVkPhysicalDevice, gfxVkSurface, &count, modes);

    VkPresentModeKHR chosen = VK_PRESENT_MODE_FIFO_KHR;
    for (uint32_t i = 0; i < count; i++) {
        if (modes[i] == VK_PRESENT_MODE_MAILBOX_KHR) {
            chosen = VK_PRESENT_MODE_MAILBOX_KHR;
            break;
        }
        if (modes[i] == VK_PRESENT_MODE_IMMEDIATE_KHR) {
            chosen = VK_PRESENT_MODE_IMMEDIATE_KHR;
        }
    }

    free(modes);
    return chosen;
}

// Resolves the swapchain extent from surface capabilities, falling back to
// the drawable size (clamped to the surface's min/max) when the surface
// doesn't dictate a fixed extent.
static VkExtent2D choose_extent(struct SDL_Window *window, const VkSurfaceCapabilitiesKHR *caps) {
    if (caps->currentExtent.width != UINT32_MAX) {
        return caps->currentExtent;
    }

    int w = 0, h = 0;
    SDL_Vulkan_GetDrawableSize((SDL_Window *)window, &w, &h);

    VkExtent2D extent = { (uint32_t)w, (uint32_t)h };
    if (extent.width < caps->minImageExtent.width) { extent.width = caps->minImageExtent.width; }
    if (extent.width > caps->maxImageExtent.width) { extent.width = caps->maxImageExtent.width; }
    if (extent.height < caps->minImageExtent.height) { extent.height = caps->minImageExtent.height; }
    if (extent.height > caps->maxImageExtent.height) { extent.height = caps->maxImageExtent.height; }
    return extent;
}

// Frees gfxVkSwapchainImageViews/gfxVkSwapchainImages. Safe to call when
// they're already NULL (no-op).
static void destroy_image_views(void) {
    if (gfxVkSwapchainImageViews) {
        for (uint32_t i = 0; i < gfxVkSwapchainImageCount; i++) {
            if (gfxVkSwapchainImageViews[i] != VK_NULL_HANDLE) {
                vkDestroyImageView(gfxVkDevice, gfxVkSwapchainImageViews[i], NULL);
            }
        }
        free(gfxVkSwapchainImageViews);
        gfxVkSwapchainImageViews = NULL;
    }
    if (gfxVkSwapchainImages) {
        free(gfxVkSwapchainImages);
        gfxVkSwapchainImages = NULL;
    }
    gfxVkSwapchainImageCount = 0;
}

// Destroys the depth image, image views, and swapchain itself, in that order.
static void gfx_vulkan_swapchain_destroy(void) {
    destroy_depth_image();
    destroy_image_views();
    if (gfxVkSwapchain != VK_NULL_HANDLE) {
        vkDestroySwapchainKHR(gfxVkDevice, gfxVkSwapchain, NULL);
        gfxVkSwapchain = VK_NULL_HANDLE;
    }
}

// Queries surface capabilities/format/present mode, then (re)builds the
// swapchain, its color image views, and the depth image at the resolved
// extent. See the failure-mode note at the top of this section.
static bool gfx_vulkan_swapchain_create(struct SDL_Window *window) {
    VkSurfaceCapabilitiesKHR caps;
    if (vkGetPhysicalDeviceSurfaceCapabilitiesKHR(gfxVkPhysicalDevice, gfxVkSurface, &caps) != VK_SUCCESS) {
        return false;
    }

    VkSurfaceFormatKHR surfaceFormat = choose_surface_format();
    VkPresentModeKHR presentMode = choose_present_mode();
    VkExtent2D extent = choose_extent(window, &caps);

    if (extent.width == 0 || extent.height == 0) {
        return false; // minimized: nothing to present yet
    }

    // FIFO never drops a queued frame, so every extra image beyond
    // minImageCount is an extra frame of input latency the CPU can race ahead
    // by before anything reaches the screen. Stay at minImageCount for FIFO
    // (typically 2, true double buffering) to match GL's roughly-one-frame-
    // deep blocking swap. MAILBOX/IMMEDIATE (vsync off) do need the extra
    // image - MAILBOX in particular degrades toward FIFO-like blocking
    // without a spare image to render into while one is displayed and one
    // sits in the mailbox slot.
    uint32_t imageCount = caps.minImageCount;
    if (presentMode != VK_PRESENT_MODE_FIFO_KHR) {
        imageCount += 1;
    }
    if (caps.maxImageCount > 0 && imageCount > caps.maxImageCount) {
        imageCount = caps.maxImageCount;
    }

    VkSwapchainKHR oldSwapchain = gfxVkSwapchain;

    VkSwapchainCreateInfoKHR createInfo = {
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .surface = gfxVkSurface,
        .minImageCount = imageCount,
        .imageFormat = surfaceFormat.format,
        .imageColorSpace = surfaceFormat.colorSpace,
        .imageExtent = extent,
        .imageArrayLayers = 1,
        .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
        .imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
        .preTransform = caps.currentTransform,
        .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
        .presentMode = presentMode,
        .clipped = VK_TRUE,
        .oldSwapchain = oldSwapchain,
    };

    VkSwapchainKHR newSwapchain = VK_NULL_HANDLE;
    VkResult res = vkCreateSwapchainKHR(gfxVkDevice, &createInfo, NULL, &newSwapchain);

#ifdef VULKAN_DEBUG
    log_to_terminal("[vulkan] swapchain_create: extent=%ux%u imageCount=%u presentMode=%d oldSwapchain=%p result=%d\n",
            extent.width, extent.height, imageCount, presentMode, (void *)oldSwapchain, res);
#endif

    if (oldSwapchain != VK_NULL_HANDLE) {
        destroy_image_views();
        vkDestroySwapchainKHR(gfxVkDevice, oldSwapchain, NULL);
    }

    if (res != VK_SUCCESS) {
        gfxVkSwapchain = VK_NULL_HANDLE;
        return false;
    }

    gfxVkSwapchain = newSwapchain;
    gfxVkSwapchainFormat = surfaceFormat.format;
    gfxVkSwapchainExtent = extent;

    vkGetSwapchainImagesKHR(gfxVkDevice, gfxVkSwapchain, &gfxVkSwapchainImageCount, NULL);
    gfxVkSwapchainImages = malloc(gfxVkSwapchainImageCount * sizeof(VkImage));
    if (!gfxVkSwapchainImages) {
        return false;
    }
    vkGetSwapchainImagesKHR(gfxVkDevice, gfxVkSwapchain, &gfxVkSwapchainImageCount, gfxVkSwapchainImages);

    gfxVkSwapchainImageViews = calloc(gfxVkSwapchainImageCount, sizeof(VkImageView));
    if (!gfxVkSwapchainImageViews) {
        return false;
    }

    for (uint32_t i = 0; i < gfxVkSwapchainImageCount; i++) {
        VkImageViewCreateInfo viewInfo = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
            .image = gfxVkSwapchainImages[i],
            .viewType = VK_IMAGE_VIEW_TYPE_2D,
            .format = gfxVkSwapchainFormat,
            .subresourceRange = {
                .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                .levelCount = 1,
                .layerCount = 1,
            },
        };
        if (vkCreateImageView(gfxVkDevice, &viewInfo, NULL, &gfxVkSwapchainImageViews[i]) != VK_SUCCESS) {
            return false;
        }
    }

    // sDepthImage/gfxVkDepthImage* still describe the *previous* extent (if
    // any) at this point - drop them before building the new one, same
    // "destroy old, then create new" order as the color image views.
    destroy_depth_image();
    if (!create_depth_image(extent)) {
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////
// Texture - backs the texture-related GfxRenderingAPI functions (new_texture/
// select_texture/upload_texture/set_sampler_parameters). texture_id is an
// index into an internal growable table, the same convention gfx_opengl.c
// uses for its GLuint-indexed texture cache.
//////////////////////////////////////////////////////////////////////////////

// Exact combinatorial max of (linear_filter x cms x cmt): G_TX_CLAMP/
// G_TX_MIRROR are two independent bits per axis, so 2 * 4 * 4 = 32 possible
// VkSamplers can ever be requested - the cache never needs to grow.
#define GFX_VULKAN_SAMPLER_CACHE_MAX 32
#define GFX_VULKAN_TEX_CACHE_STEP 256

typedef struct {
    GfxVulkanImage image;
    VkSampler sampler; // VK_NULL_HANDLE until set_sampler_parameters is called
    uint32_t width, height;
    bool linearFilter; // last value passed to set_sampler_parameters
} GfxVulkanTextureEntry;

typedef struct {
    bool linearFilter;
    uint32_t cms, cmt;
    VkSampler sampler;
} GfxVulkanSamplerCacheEntry;

static GfxVulkanTextureEntry *sTextures = NULL;
static uint32_t sTextureCount = 0;
static uint32_t sTextureCapacity = 0;

static uint32_t sBoundTexture[2] = { UINT32_MAX, UINT32_MAX };
static int sCurrentTile = 0;

static GfxVulkanSamplerCacheEntry sSamplerCache[GFX_VULKAN_SAMPLER_CACHE_MAX];
static uint32_t sSamplerCacheCount = 0;

static VkCommandPool sTransferPool = VK_NULL_HANDLE;

// Creates the transient command pool used for one-shot texture upload commands.
static bool gfx_vulkan_texture_init(void) {
    VkCommandPoolCreateInfo poolInfo = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
        .flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT,
        .queueFamilyIndex = gfxVkQueueFamily,
    };
    return vkCreateCommandPool(gfxVkDevice, &poolInfo, NULL, &sTransferPool) == VK_SUCCESS;
}

// Frees every texture image, every cached sampler, and the transfer pool.
static void gfx_vulkan_texture_destroy(void) {
    for (uint32_t i = 0; i < sTextureCount; i++) {
        gfx_vulkan_memory_destroy_image(&sTextures[i].image);
    }
    free(sTextures);
    sTextures = NULL;
    sTextureCount = 0;
    sTextureCapacity = 0;
    sBoundTexture[0] = sBoundTexture[1] = UINT32_MAX;

    for (uint32_t i = 0; i < sSamplerCacheCount; i++) {
        vkDestroySampler(gfxVkDevice, sSamplerCache[i].sampler, NULL);
    }
    sSamplerCacheCount = 0;

    if (sTransferPool != VK_NULL_HANDLE) {
        vkDestroyCommandPool(gfxVkDevice, sTransferPool, NULL);
        sTransferPool = VK_NULL_HANDLE;
    }
}

// Reserves a new, empty texture slot and returns its id.
static uint32_t gfx_vulkan_texture_new(void) {
    if (sTextureCount >= sTextureCapacity) {
        sTextureCapacity += GFX_VULKAN_TEX_CACHE_STEP;
        GfxVulkanTextureEntry *grown = realloc(sTextures, sTextureCapacity * sizeof(GfxVulkanTextureEntry));
        if (!grown) {
            sys_fatal("out of memory allocating vulkan texture cache");
        }
        sTextures = grown;
    }
    memset(&sTextures[sTextureCount], 0, sizeof(GfxVulkanTextureEntry));
    return sTextureCount++;
}

// Binds texture_id to the given RDP tile (0 or 1) for subsequent upload/draw calls.
static void gfx_vulkan_texture_select(int tile, uint32_t texture_id) {
    sBoundTexture[tile] = texture_id;
    sCurrentTile = tile;
}

// Allocates and begins a one-time-submit command buffer from sTransferPool.
static VkCommandBuffer begin_immediate_commands(void) {
    VkCommandBufferAllocateInfo allocInfo = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        .commandPool = sTransferPool,
        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .commandBufferCount = 1,
    };
    VkCommandBuffer cmd = VK_NULL_HANDLE;
    if (vkAllocateCommandBuffers(gfxVkDevice, &allocInfo, &cmd) != VK_SUCCESS) {
        return VK_NULL_HANDLE;
    }

    VkCommandBufferBeginInfo beginInfo = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
    };
    vkBeginCommandBuffer(cmd, &beginInfo);
    return cmd;
}

// Submits cmd and blocks until the GPU finishes. Fine for the once-per-
// texture-load pattern this backend uses today; would need to become
// asynchronous if uploads ever had to happen every frame.
static void end_immediate_commands(VkCommandBuffer cmd) {
    vkEndCommandBuffer(cmd);

    VkCommandBufferSubmitInfo cmdInfo = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO,
        .commandBuffer = cmd,
    };
    VkSubmitInfo2 submitInfo = {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2,
        .commandBufferInfoCount = 1,
        .pCommandBufferInfos = &cmdInfo,
    };

    VkFenceCreateInfo fenceInfo = { .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO };
    VkFence fence = VK_NULL_HANDLE;
    if (vkCreateFence(gfxVkDevice, &fenceInfo, NULL, &fence) == VK_SUCCESS) {
        if (vkQueueSubmit2(gfxVkQueue, 1, &submitInfo, fence) == VK_SUCCESS) {
            vkWaitForFences(gfxVkDevice, 1, &fence, VK_TRUE, UINT64_MAX);
        }
        vkDestroyFence(gfxVkDevice, fence, NULL);
    }
    vkFreeCommandBuffers(gfxVkDevice, sTransferPool, 1, &cmd);
}

// Uploads RGBA8 pixels to the texture currently bound on the current tile:
// staging buffer -> vkCmdCopyBufferToImage2, with UNDEFINED -> TRANSFER_DST ->
// SHADER_READ_ONLY layout transitions around the copy.
static void gfx_vulkan_texture_upload(const uint8_t *rgba32_buf, int width, int height) {
    uint32_t id = sBoundTexture[sCurrentTile];
    if (id == UINT32_MAX || id >= sTextureCount) {
        return;
    }
    GfxVulkanTextureEntry *tex = &sTextures[id];

    if (tex->image.image != VK_NULL_HANDLE) {
        // Re-upload (e.g. a texture slot got reused): the old image might
        // still be referenced by an in-flight command buffer, so wait it out
        // before freeing. Simple and correct, not optimized - revisit if this
        // path ever becomes hot.
        vkDeviceWaitIdle(gfxVkDevice);
        gfx_vulkan_memory_destroy_image(&tex->image);
    }

    VkDeviceSize size = (VkDeviceSize)width * (VkDeviceSize)height * 4;
    GfxVulkanBuffer staging = { 0 };
    void *mapped = NULL;
    if (!gfx_vulkan_memory_create_streaming_buffer(size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, &staging, &mapped)) {
        return;
    }
    memcpy(mapped, rgba32_buf, size);

    if (!gfx_vulkan_memory_create_image((uint32_t)width, (uint32_t)height, VK_FORMAT_R8G8B8A8_UNORM,
                                         VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
                                         VK_IMAGE_ASPECT_COLOR_BIT, &tex->image)) {
        gfx_vulkan_memory_destroy_buffer(&staging);
        return;
    }

    VkCommandBuffer cmd = begin_immediate_commands();
    if (cmd != VK_NULL_HANDLE) {
        VkImageMemoryBarrier2 toTransferDst = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
            .srcStageMask = VK_PIPELINE_STAGE_2_TOP_OF_PIPE_BIT,
            .srcAccessMask = VK_ACCESS_2_NONE,
            .dstStageMask = VK_PIPELINE_STAGE_2_TRANSFER_BIT,
            .dstAccessMask = VK_ACCESS_2_TRANSFER_WRITE_BIT,
            .oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
            .newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
            .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
            .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
            .image = tex->image.image,
            .subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 },
        };
        VkDependencyInfo dep1 = {
            .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
            .imageMemoryBarrierCount = 1,
            .pImageMemoryBarriers = &toTransferDst,
        };
        vkCmdPipelineBarrier2(cmd, &dep1);

        VkBufferImageCopy2 region = {
            .sType = VK_STRUCTURE_TYPE_BUFFER_IMAGE_COPY_2,
            .imageSubresource = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1 },
            .imageExtent = { (uint32_t)width, (uint32_t)height, 1 },
        };
        VkCopyBufferToImageInfo2 copyInfo = {
            .sType = VK_STRUCTURE_TYPE_COPY_BUFFER_TO_IMAGE_INFO_2,
            .srcBuffer = staging.buffer,
            .dstImage = tex->image.image,
            .dstImageLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
            .regionCount = 1,
            .pRegions = &region,
        };
        vkCmdCopyBufferToImage2(cmd, &copyInfo);

        VkImageMemoryBarrier2 toShaderRead = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
            .srcStageMask = VK_PIPELINE_STAGE_2_TRANSFER_BIT,
            .srcAccessMask = VK_ACCESS_2_TRANSFER_WRITE_BIT,
            .dstStageMask = VK_PIPELINE_STAGE_2_FRAGMENT_SHADER_BIT,
            .dstAccessMask = VK_ACCESS_2_SHADER_READ_BIT,
            .oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
            .newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
            .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
            .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
            .image = tex->image.image,
            .subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 },
        };
        VkDependencyInfo dep2 = {
            .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
            .imageMemoryBarrierCount = 1,
            .pImageMemoryBarriers = &toShaderRead,
        };
        vkCmdPipelineBarrier2(cmd, &dep2);

        end_immediate_commands(cmd);
    }

    gfx_vulkan_memory_destroy_buffer(&staging);

    tex->width = (uint32_t)width;
    tex->height = (uint32_t)height;
}

// Maps an RDP texture-tile wrap mode (G_TX_CLAMP/G_TX_MIRROR bits) to its
// closest VkSamplerAddressMode.
static VkSamplerAddressMode cm_to_vk_address_mode(uint32_t val) {
    if (val & G_TX_CLAMP) {
        return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    }
    return (val & G_TX_MIRROR) ? VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT : VK_SAMPLER_ADDRESS_MODE_REPEAT;
}

// Returns a cached VkSampler for this exact (filter, wrap) combination,
// creating and caching one if this is the first time it's requested.
static VkSampler get_or_create_sampler(bool linearFilter, uint32_t cms, uint32_t cmt) {
    for (uint32_t i = 0; i < sSamplerCacheCount; i++) {
        GfxVulkanSamplerCacheEntry *entry = &sSamplerCache[i];
        if (entry->linearFilter == linearFilter && entry->cms == cms && entry->cmt == cmt) {
            return entry->sampler;
        }
    }

    VkFilter filter = linearFilter ? VK_FILTER_LINEAR : VK_FILTER_NEAREST;
    VkSamplerCreateInfo samplerInfo = {
        .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
        .magFilter = filter,
        .minFilter = filter,
        .addressModeU = cm_to_vk_address_mode(cms),
        .addressModeV = cm_to_vk_address_mode(cmt),
        .addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT,
        .maxLod = VK_LOD_CLAMP_NONE,
    };

    VkSampler sampler = VK_NULL_HANDLE;
    if (vkCreateSampler(gfxVkDevice, &samplerInfo, NULL, &sampler) != VK_SUCCESS) {
        return VK_NULL_HANDLE;
    }

    if (sSamplerCacheCount < GFX_VULKAN_SAMPLER_CACHE_MAX) {
        sSamplerCache[sSamplerCacheCount++] = (GfxVulkanSamplerCacheEntry){ linearFilter, cms, cmt, sampler };
    }
    return sampler;
}

// Assigns a (cached) sampler matching these filter/wrap settings to the
// texture currently bound on `tile`.
static void gfx_vulkan_texture_set_sampler_parameters(int tile, bool linear_filter, uint32_t cms, uint32_t cmt) {
    uint32_t id = sBoundTexture[tile];
    if (id == UINT32_MAX || id >= sTextureCount) {
        return;
    }
    sTextures[id].sampler = get_or_create_sampler(linear_filter, cms, cmt);
    sTextures[id].linearFilter = linear_filter;
}

// Read-only lookup for the Pipeline section below to bind whatever texture is
// currently selected on a tile.
static bool gfx_vulkan_texture_get_bound(int tile, VkImageView *outView, VkSampler *outSampler) {
    uint32_t id = sBoundTexture[tile];
    if (id == UINT32_MAX || id >= sTextureCount) {
        return false;
    }
    GfxVulkanTextureEntry *tex = &sTextures[id];
    if (tex->image.view == VK_NULL_HANDLE || tex->sampler == VK_NULL_HANDLE) {
        return false;
    }
    *outView = tex->image.view;
    *outSampler = tex->sampler;
    return true;
}

// Size (in texels) and linear-filter flag of whatever texture is currently
// selected on a tile, fed to the Color Combiner shader as push constants.
// linear_filter is the flag set_sampler_parameters was last called with for
// this texture (not the VkSampler's own filter mode) - it only gates the
// shader's 3-point-filter codepath, mirroring gfx_opengl.c's uTexNFilter
// uniform.
static bool gfx_vulkan_texture_get_bound_info(int tile, float outSize[2], bool *outLinearFilter) {
    uint32_t id = sBoundTexture[tile];
    if (id == UINT32_MAX || id >= sTextureCount) {
        return false;
    }
    GfxVulkanTextureEntry *tex = &sTextures[id];
    outSize[0] = (float)tex->width;
    outSize[1] = (float)tex->height;
    *outLinearFilter = tex->linearFilter;
    return true;
}

//////////////////////////////////////////////////////////////////////////////
// Frame - frame-in-flight sync (timeline semaphore + per-slot command
// pool/buffer/imageAvailable semaphore) and the acquire/rendering-begin/
// submit/present sequence.
//////////////////////////////////////////////////////////////////////////////

typedef struct {
    VkCommandPool commandPool;
    VkCommandBuffer commandBuffer;
    VkSemaphore imageAvailable;
    uint64_t signalValue; // timeline value this slot's last submission signals; 0 = never submitted
    bool pendingAcquire; // true between a successful acquire and its matching present
} GfxVulkanFrameSlot;

static GfxVulkanFrameSlot sFrames[GFX_VULKAN_FRAMES_IN_FLIGHT];
static VkSemaphore sTimeline = VK_NULL_HANDLE;
static uint64_t sTimelineCounter = 0;
static uint32_t sCurrentFrame = 0;
static uint32_t sCurrentImageIndex = 0;
static struct SDL_Window *sWindow = NULL;
static bool sSwapchainDirty = false;

// Indexed by *acquired swapchain image*, not by frame-in-flight slot: the
// presentation engine (not us) decides when a given image's semaphore is
// safe to reuse, and image count doesn't necessarily match
// GFX_VULKAN_FRAMES_IN_FLIGHT. Indexing by frame slot instead could make
// vkQueueSubmit2 re-signal a semaphore the presentation engine is still
// waiting on, which is undefined behavior.
static VkSemaphore *sRenderFinished = NULL;
static uint32_t sRenderFinishedCount = 0;

static VkCommandBuffer gfxVkCurrentCommandBuffer = VK_NULL_HANDLE;

// Allocates one renderFinished semaphore per current swapchain image.
static bool create_render_finished_semaphores(void) {
    sRenderFinishedCount = gfxVkSwapchainImageCount;
    sRenderFinished = malloc(sRenderFinishedCount * sizeof(VkSemaphore));
    if (!sRenderFinished) {
        return false;
    }

    for (uint32_t i = 0; i < sRenderFinishedCount; i++) {
        VkSemaphoreCreateInfo semInfo = { .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO };
        if (vkCreateSemaphore(gfxVkDevice, &semInfo, NULL, &sRenderFinished[i]) != VK_SUCCESS) {
            return false;
        }
    }
    return true;
}

// Safe to call when sRenderFinished is already NULL (no-op).
static void destroy_render_finished_semaphores(void) {
    if (!sRenderFinished) {
        return;
    }
    for (uint32_t i = 0; i < sRenderFinishedCount; i++) {
        if (sRenderFinished[i] != VK_NULL_HANDLE) {
            vkDestroySemaphore(gfxVkDevice, sRenderFinished[i], NULL);
        }
    }
    free(sRenderFinished);
    sRenderFinished = NULL;
    sRenderFinishedCount = 0;
}

// Creates the timeline semaphore plus, per frame-in-flight slot, a command
// pool/buffer and an imageAvailable semaphore.
static bool gfx_vulkan_frame_init(struct SDL_Window *window) {
    sWindow = window;

    VkSemaphoreTypeCreateInfo timelineInfo = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
        .semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE,
        .initialValue = 0,
    };
    VkSemaphoreCreateInfo timelineSemInfo = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
        .pNext = &timelineInfo,
    };
    if (vkCreateSemaphore(gfxVkDevice, &timelineSemInfo, NULL, &sTimeline) != VK_SUCCESS) {
        return false;
    }

    for (int i = 0; i < GFX_VULKAN_FRAMES_IN_FLIGHT; i++) {
        VkCommandPoolCreateInfo poolInfo = {
            .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
            .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
            .queueFamilyIndex = gfxVkQueueFamily,
        };
        if (vkCreateCommandPool(gfxVkDevice, &poolInfo, NULL, &sFrames[i].commandPool) != VK_SUCCESS) {
            return false;
        }

        VkCommandBufferAllocateInfo allocInfo = {
            .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
            .commandPool = sFrames[i].commandPool,
            .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
            .commandBufferCount = 1,
        };
        if (vkAllocateCommandBuffers(gfxVkDevice, &allocInfo, &sFrames[i].commandBuffer) != VK_SUCCESS) {
            return false;
        }

        VkSemaphoreCreateInfo plainSemInfo = { .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO };
        if (vkCreateSemaphore(gfxVkDevice, &plainSemInfo, NULL, &sFrames[i].imageAvailable) != VK_SUCCESS) {
            return false;
        }
    }

    if (!create_render_finished_semaphores()) {
        return false;
    }

    return true;
}

// Waits for the device to go idle, then frees every frame-in-flight
// resource (semaphores, command pools) and the timeline semaphore.
static void gfx_vulkan_frame_destroy(void) {
    if (gfxVkDevice != VK_NULL_HANDLE) {
        vkDeviceWaitIdle(gfxVkDevice);
    }

    destroy_render_finished_semaphores();

    for (int i = 0; i < GFX_VULKAN_FRAMES_IN_FLIGHT; i++) {
        if (sFrames[i].imageAvailable != VK_NULL_HANDLE) {
            vkDestroySemaphore(gfxVkDevice, sFrames[i].imageAvailable, NULL);
        }
        if (sFrames[i].commandPool != VK_NULL_HANDLE) {
            vkDestroyCommandPool(gfxVkDevice, sFrames[i].commandPool, NULL);
        }
    }
    memset(sFrames, 0, sizeof(sFrames));

    if (sTimeline != VK_NULL_HANDLE) {
        vkDestroySemaphore(gfxVkDevice, sTimeline, NULL);
        sTimeline = VK_NULL_HANDLE;
    }

    sCurrentFrame = 0;
    sTimelineCounter = 0;
    sSwapchainDirty = false;
    gfxVkCurrentCommandBuffer = VK_NULL_HANDLE;
}

// Called on SDL_WINDOWEVENT_SIZE_CHANGED: defers the actual swapchain rebuild
// to the next gfx_vulkan_frame_start, since resizing mid-frame would need a
// device-idle wait that shouldn't happen on the event thread.
static void gfx_vulkan_frame_notify_resize(void) {
#ifdef VULKAN_DEBUG
    log_to_terminal("[vulkan] notify_resize called\n");
#endif
    sSwapchainDirty = true;
}

// Rebuilds the swapchain and its renderFinished semaphores (image count can
// change across a resize). Both failure branches re-arm sSwapchainDirty
// instead of leaving it cleared: either step can fail after already
// destroying/freeing the previous working state (not just on the common
// 0x0/minimized-window case), which would otherwise leave the next
// gfx_vulkan_frame_start() acquiring from - or indexing into - broken state.
// Re-arming costs one extra vkDeviceWaitIdle + retry per frame while
// genuinely minimized, which is harmless since nothing renders then anyway.
static bool recreate_swapchain(void) {
    vkDeviceWaitIdle(gfxVkDevice);
    sSwapchainDirty = false;

    if (!gfx_vulkan_swapchain_create(sWindow)) {
        sSwapchainDirty = true;
        return false;
    }

    // Image count can change across a resize (different present mode/surface
    // capabilities), so the renderFinished semaphores must be rebuilt too.
    destroy_render_finished_semaphores();
    if (!create_render_finished_semaphores()) {
        sSwapchainDirty = true;
        return false;
    }
    return true;
}

// Pre-VK_EXT_swapchain_maintenance1 (not required by this backend's Vulkan
// 1.3 floor, so not assumed present), the base spec leaves the signal state
// of the wait semaphore undefined when vkAcquireNextImageKHR fails. Mesa has
// been observed to sometimes signal it anyway on that path. Recreating the
// semaphore after every failed acquire guarantees a clean, unsignaled
// semaphore for the next attempt regardless of what the driver actually did.
static void recreate_image_available_semaphore(GfxVulkanFrameSlot *slot) {
    if (slot->imageAvailable != VK_NULL_HANDLE) {
        vkDestroySemaphore(gfxVkDevice, slot->imageAvailable, NULL);
    }
    VkSemaphoreCreateInfo semInfo = { .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO };
    if (vkCreateSemaphore(gfxVkDevice, &semInfo, NULL, &slot->imageAvailable) != VK_SUCCESS) {
        slot->imageAvailable = VK_NULL_HANDLE;
        log_to_terminal("[vulkan] failed to recreate imageAvailable semaphore after a failed acquire\n");
    }
}

// Begins a new frame: rebuilds the swapchain if it was marked dirty, waits
// for this slot's previous submission to finish, resets its command pool,
// and acquires the next swapchain image.
static bool gfx_vulkan_frame_start(void) {
    if (sSwapchainDirty) {
        if (!recreate_swapchain()) {
            return false; // e.g. window minimized to a 0x0 extent - try again next frame
        }
    }

    GfxVulkanFrameSlot *slot = &sFrames[sCurrentFrame];

    // Nothing presented this slot's previous acquire (e.g. a caller that opens
    // a frame via GfxRenderingAPI::start_frame without a matching end_frame,
    // such as the loading-screen-to-gameplay transition) - imageAvailable is
    // still signaled with nothing waiting on it, so a fresh acquire on it
    // would violate VUID-vkAcquireNextImageKHR-semaphore-01286. Recreate it
    // before reusing this slot, same remedy as the failed-acquire path below.
    if (slot->pendingAcquire) {
        recreate_image_available_semaphore(slot);
        slot->pendingAcquire = false;
    }

    if (slot->signalValue > 0) {
        VkSemaphoreWaitInfo waitInfo = {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
            .semaphoreCount = 1,
            .pSemaphores = &sTimeline,
            .pValues = &slot->signalValue,
        };
        VkResult waitRes = vkWaitSemaphores(gfxVkDevice, &waitInfo, UINT64_MAX);
        if (waitRes != VK_SUCCESS) {
            log_to_terminal("[vulkan] vkWaitSemaphores failed: %d\n", waitRes);
            return false;
        }
    }

    vkResetCommandPool(gfxVkDevice, slot->commandPool, 0);

    VkResult res = vkAcquireNextImageKHR(gfxVkDevice, gfxVkSwapchain, UINT64_MAX,
                                          slot->imageAvailable, VK_NULL_HANDLE, &sCurrentImageIndex);
    if (res == VK_ERROR_OUT_OF_DATE_KHR) {
        sSwapchainDirty = true;
        recreate_image_available_semaphore(slot);
        return false;
    }
    if (res != VK_SUCCESS && res != VK_SUBOPTIMAL_KHR) {
        log_to_terminal("[vulkan] vkAcquireNextImageKHR failed: %d\n", res);
        recreate_image_available_semaphore(slot);
        return false;
    }

    gfxVkCurrentCommandBuffer = slot->commandBuffer;
    slot->pendingAcquire = true;
    return true;
}

// Begins recording the current frame's command buffer: transitions the
// acquired color image and the depth image into their attachment layouts,
// then opens the dynamic-rendering pass (clear color + clear depth 1.0).
static void gfx_vulkan_frame_begin_rendering(void) {
    VkCommandBufferBeginInfo beginInfo = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
    };
    vkBeginCommandBuffer(gfxVkCurrentCommandBuffer, &beginInfo);

    VkImageMemoryBarrier2 toColorAttachment = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
        .srcStageMask = VK_PIPELINE_STAGE_2_TOP_OF_PIPE_BIT,
        .srcAccessMask = VK_ACCESS_2_NONE,
        .dstStageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT,
        .dstAccessMask = VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT,
        .oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
        .newLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
        .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
        .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
        .image = gfxVkSwapchainImages[sCurrentImageIndex],
        .subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 },
    };
    // The depth image is recreated fresh every time the swapchain is (built
    // for this frame, only read/written within it), so UNDEFINED ->
    // DEPTH_ATTACHMENT_OPTIMAL (discarding whatever was there) is correct
    // every frame, not just "good enough".
    VkImageMemoryBarrier2 toDepthAttachment = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
        .srcStageMask = VK_PIPELINE_STAGE_2_TOP_OF_PIPE_BIT,
        .srcAccessMask = VK_ACCESS_2_NONE,
        .dstStageMask = VK_PIPELINE_STAGE_2_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_2_LATE_FRAGMENT_TESTS_BIT,
        .dstAccessMask = VK_ACCESS_2_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT | VK_ACCESS_2_DEPTH_STENCIL_ATTACHMENT_READ_BIT,
        .oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
        .newLayout = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL,
        .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
        .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
        .image = gfxVkDepthImage,
        .subresourceRange = { VK_IMAGE_ASPECT_DEPTH_BIT, 0, 1, 0, 1 },
    };
    VkImageMemoryBarrier2 barriers[2] = { toColorAttachment, toDepthAttachment };
    VkDependencyInfo depInfo = {
        .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
        .imageMemoryBarrierCount = 2,
        .pImageMemoryBarriers = barriers,
    };
    vkCmdPipelineBarrier2(gfxVkCurrentCommandBuffer, &depInfo);

    VkRenderingAttachmentInfo colorAttachment = {
        .sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO,
        .imageView = gfxVkSwapchainImageViews[sCurrentImageIndex],
        .imageLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
        .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
        .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
        .clearValue = { .color = { { 0.0f, 0.0f, 0.0f, 1.0f } } },
    };
    // z_is_from_0_to_1() is true (see the bottom of this file) so 1.0 is
    // "farthest", matching depthCompareOp = LESS_OR_EQUAL (Pipeline section).
    VkRenderingAttachmentInfo depthAttachment = {
        .sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO,
        .imageView = gfxVkDepthImageView,
        .imageLayout = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL,
        .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
        .storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
        .clearValue = { .depthStencil = { 1.0f, 0 } },
    };
    VkRenderingInfo renderingInfo = {
        .sType = VK_STRUCTURE_TYPE_RENDERING_INFO,
        .renderArea = { { 0, 0 }, gfxVkSwapchainExtent },
        .layerCount = 1,
        .colorAttachmentCount = 1,
        .pColorAttachments = &colorAttachment,
        .pDepthAttachment = &depthAttachment,
    };
    vkCmdBeginRendering(gfxVkCurrentCommandBuffer, &renderingInfo);
    gfx_vulkan_debug_begin_label(gfxVkCurrentCommandBuffer, "Vulkan Pass");
}

// Ends the rendering pass, transitions the color image to PRESENT_SRC, ends
// and submits the command buffer (signaling this slot's timeline value and
// this image's renderFinished semaphore).
static void gfx_vulkan_frame_end_and_submit(void) {
    gfx_vulkan_debug_end_label(gfxVkCurrentCommandBuffer);
    vkCmdEndRendering(gfxVkCurrentCommandBuffer);

    VkImageMemoryBarrier2 toPresent = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
        .srcStageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT,
        .srcAccessMask = VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT,
        .dstStageMask = VK_PIPELINE_STAGE_2_BOTTOM_OF_PIPE_BIT,
        .dstAccessMask = VK_ACCESS_2_NONE,
        .oldLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
        .newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
        .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
        .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
        .image = gfxVkSwapchainImages[sCurrentImageIndex],
        .subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 },
    };
    VkDependencyInfo depInfo = {
        .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
        .imageMemoryBarrierCount = 1,
        .pImageMemoryBarriers = &toPresent,
    };
    vkCmdPipelineBarrier2(gfxVkCurrentCommandBuffer, &depInfo);

    VkResult endRes = vkEndCommandBuffer(gfxVkCurrentCommandBuffer);
    if (endRes != VK_SUCCESS) {
        log_to_terminal("[vulkan] vkEndCommandBuffer failed: %d\n", endRes);
    }

    GfxVulkanFrameSlot *slot = &sFrames[sCurrentFrame];
    sTimelineCounter++;
    slot->signalValue = sTimelineCounter;

    VkSemaphoreSubmitInfo waitSemInfo = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = slot->imageAvailable,
        .stageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT,
    };
    VkSemaphoreSubmitInfo signalSemInfos[2] = {
        {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
            .semaphore = sRenderFinished[sCurrentImageIndex],
            .stageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT,
        },
        {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
            .semaphore = sTimeline,
            .value = sTimelineCounter,
            .stageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT,
        },
    };
    VkCommandBufferSubmitInfo cmdSubmitInfo = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO,
        .commandBuffer = gfxVkCurrentCommandBuffer,
    };
    VkSubmitInfo2 submitInfo = {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2,
        .waitSemaphoreInfoCount = 1,
        .pWaitSemaphoreInfos = &waitSemInfo,
        .commandBufferInfoCount = 1,
        .pCommandBufferInfos = &cmdSubmitInfo,
        .signalSemaphoreInfoCount = 2,
        .pSignalSemaphoreInfos = signalSemInfos,
    };
    VkResult submitRes = vkQueueSubmit2(gfxVkQueue, 1, &submitInfo, VK_NULL_HANDLE);
    if (submitRes != VK_SUCCESS) {
        log_to_terminal("[vulkan] vkQueueSubmit2 failed: %d\n", submitRes);
    }
}

// Presents the acquired image and advances to the next frame-in-flight slot.
static bool gfx_vulkan_frame_present(void) {
    VkPresentInfoKHR presentInfo = {
        .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = &sRenderFinished[sCurrentImageIndex],
        .swapchainCount = 1,
        .pSwapchains = &gfxVkSwapchain,
        .pImageIndices = &sCurrentImageIndex,
    };
    VkResult res = vkQueuePresentKHR(gfxVkQueue, &presentInfo);

    sFrames[sCurrentFrame].pendingAcquire = false;
    sCurrentFrame = (sCurrentFrame + 1) % GFX_VULKAN_FRAMES_IN_FLIGHT;

    if (res == VK_ERROR_OUT_OF_DATE_KHR || res == VK_SUBOPTIMAL_KHR) {
        sSwapchainDirty = true;
        return false;
    }
    if (res != VK_SUCCESS) {
        log_to_terminal("[vulkan] vkQueuePresentKHR failed: %d\n", res);
    }
    return res == VK_SUCCESS;
}

// Index in [0, GFX_VULKAN_FRAMES_IN_FLIGHT) of the slot currently being
// recorded (valid between gfx_vulkan_frame_start() and the matching
// gfx_vulkan_frame_present()).
static uint32_t gfx_vulkan_frame_get_current_slot(void) {
    return sCurrentFrame;
}

//////////////////////////////////////////////////////////////////////////////
// Pipeline - owns the state shared by every Color Combiner pipeline: the one
// VkPipelineLayout, its two descriptor set layouts (set 0 = per-frame UBO,
// regular/dynamic-offset; set 1 = up to 2 textures, push descriptor), the
// frame UBO's backing buffer, and the VkPipelineCache every
// gfx_vulkan_pipeline_create() call feeds into. Only the vertex input layout
// and the two shader modules differ between pipelines - cull mode, MSAA
// (always off), and the blend equation are fixed for all of them, to avoid a
// combinatorial explosion of pipeline variants; the only real per-draw toggle
// the game needs (alpha blending on/off) is dynamic state instead
// (VK_EXT_extended_dynamic_state3's colorBlendEnable).
//////////////////////////////////////////////////////////////////////////////

// Mirrors the `FrameUBO` block the Shader section below emits into every
// fragment shader (layout(std140, set = 0, binding = 0)). std140 rounds vec3
// up to a 16-byte slot and gives every array element its own 16-byte slot
// regardless of the element's own size - hence the explicit padding/[4]
// arrays below; only index [i][0] of the array members is ever written.
typedef struct {
    float uFrameCount;
    float _pad0[3];
    float uLightmapColor[3];
    float _pad1;
    int32_t uShaderFlags[SHADER_FLAG_MAX][4];
    float uShaderFlagValues[SHADER_FLAG_MAX][4];
    int32_t uFilter;
    float _pad2[3];
} GfxVulkanFrameUBO;

static VkDescriptorSetLayout sFrameSetLayout = VK_NULL_HANDLE;   // set 0: UBO, dynamic offset
static VkDescriptorSetLayout sTextureSetLayout = VK_NULL_HANDLE; // set 1: push descriptor, 2 samplers
static VkDescriptorPool sDescriptorPool = VK_NULL_HANDLE;
static VkDescriptorSet sFrameDescriptorSet = VK_NULL_HANDLE;
static VkPipelineLayout gfxVkPipelineLayout = VK_NULL_HANDLE;
static VkPipelineCache sPipelineCache = VK_NULL_HANDLE;

static GfxVulkanBuffer sFrameUboBuffer;
static uint8_t *sFrameUboMapped = NULL;
static VkDeviceSize sFrameUboSliceStride = 0; // sizeof(GfxVulkanFrameUBO) rounded up to minUniformBufferOffsetAlignment

// Creates the two shared descriptor set layouts: set 0 (frame UBO) and set 1
// (push-descriptor textures).
static bool create_set_layouts(void) {
    VkDescriptorSetLayoutBinding frameBinding = {
        .binding = 0,
        .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC,
        .descriptorCount = 1,
        .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
    };
    VkDescriptorSetLayoutCreateInfo frameInfo = {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        .bindingCount = 1,
        .pBindings = &frameBinding,
    };
    if (vkCreateDescriptorSetLayout(gfxVkDevice, &frameInfo, NULL, &sFrameSetLayout) != VK_SUCCESS) {
        return false;
    }

    VkDescriptorSetLayoutBinding texBindings[2] = {
        { .binding = 0, .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, .descriptorCount = 1, .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT },
        { .binding = 1, .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, .descriptorCount = 1, .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT },
    };
    VkDescriptorSetLayoutCreateInfo texInfo = {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        .flags = VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR,
        .bindingCount = 2,
        .pBindings = texBindings,
    };
    return vkCreateDescriptorSetLayout(gfxVkDevice, &texInfo, NULL, &sTextureSetLayout) == VK_SUCCESS;
}

// Creates gfxVkPipelineLayout from the two set layouts plus the draw push constant range.
static bool create_pipeline_layout(void) {
    VkDescriptorSetLayout setLayouts[2] = { sFrameSetLayout, sTextureSetLayout };
    VkPushConstantRange pushRange = {
        .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
        .offset = 0,
        .size = sizeof(GfxVulkanDrawPushConstants),
    };
    VkPipelineLayoutCreateInfo layoutInfo = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .setLayoutCount = 2,
        .pSetLayouts = setLayouts,
        .pushConstantRangeCount = 1,
        .pPushConstantRanges = &pushRange,
    };
    return vkCreatePipelineLayout(gfxVkDevice, &layoutInfo, NULL, &gfxVkPipelineLayout) == VK_SUCCESS;
}

// Rounds value up to the next multiple of alignment (alignment must be a power of two).
static VkDeviceSize align_up(VkDeviceSize value, VkDeviceSize alignment) {
    return (value + alignment - 1) & ~(alignment - 1);
}

// Allocates the persistently-mapped frame UBO buffer: one slice per
// frame-in-flight slot, each padded to the device's uniform buffer offset
// alignment.
static bool create_frame_ubo(void) {
    VkPhysicalDeviceProperties props;
    vkGetPhysicalDeviceProperties(gfxVkPhysicalDevice, &props);
    VkDeviceSize alignment = props.limits.minUniformBufferOffsetAlignment;
    if (alignment == 0) { alignment = 1; }

    sFrameUboSliceStride = align_up(sizeof(GfxVulkanFrameUBO), alignment);

    void *mapped = NULL;
    if (!gfx_vulkan_memory_create_streaming_buffer(sFrameUboSliceStride * GFX_VULKAN_FRAMES_IN_FLIGHT,
                                                    VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, &sFrameUboBuffer, &mapped)) {
        return false;
    }
    sFrameUboMapped = (uint8_t *)mapped;
    return true;
}

// Allocates the single descriptor set for the frame UBO (set 0) and points
// it at sFrameUboBuffer.
static bool create_descriptor_set(void) {
    VkDescriptorPoolSize poolSize = {
        .type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC,
        .descriptorCount = 1,
    };
    VkDescriptorPoolCreateInfo poolInfo = {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
        .maxSets = 1,
        .poolSizeCount = 1,
        .pPoolSizes = &poolSize,
    };
    if (vkCreateDescriptorPool(gfxVkDevice, &poolInfo, NULL, &sDescriptorPool) != VK_SUCCESS) {
        return false;
    }

    VkDescriptorSetAllocateInfo allocInfo = {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        .descriptorPool = sDescriptorPool,
        .descriptorSetCount = 1,
        .pSetLayouts = &sFrameSetLayout,
    };
    if (vkAllocateDescriptorSets(gfxVkDevice, &allocInfo, &sFrameDescriptorSet) != VK_SUCCESS) {
        return false;
    }

    VkDescriptorBufferInfo bufferInfo = {
        .buffer = sFrameUboBuffer.buffer,
        .offset = 0,
        .range = sizeof(GfxVulkanFrameUBO),
    };
    VkWriteDescriptorSet write = {
        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
        .dstSet = sFrameDescriptorSet,
        .dstBinding = 0,
        .descriptorCount = 1,
        .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC,
        .pBufferInfo = &bufferInfo,
    };
    vkUpdateDescriptorSets(gfxVkDevice, 1, &write, 0, NULL);
    return true;
}

#define GFX_VULKAN_PIPELINE_CACHE_FILE "vulkan_pipeline_cache.bin"

// Same convention configfile.c uses for sm64config.txt: fopen() directly on
// fs_get_write_path(), bypassing the read-only virtual/mounted asset
// filesystem in fs.c (that one is for mods/dynos packs, not per-install
// cache blobs). A stale/incompatible blob (different GPU, driver version,
// etc.) is safe to hand to vkCreatePipelineCache unconditionally: the spec
// requires the driver to silently discard initial data whose header doesn't
// match the current device instead of failing, so no manual validation of
// vendorID/deviceID/pipelineCacheUUID is needed here.
static void *load_pipeline_cache_blob(size_t *outSize) {
    FILE *f = fopen(fs_get_write_path(GFX_VULKAN_PIPELINE_CACHE_FILE), "rb");
    if (!f) {
        return NULL;
    }
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    if (size <= 0) {
        fclose(f);
        return NULL;
    }
    fseek(f, 0, SEEK_SET);

    void *buf = malloc((size_t)size);
    if (!buf) {
        fclose(f);
        return NULL;
    }
    size_t rd = fread(buf, 1, (size_t)size, f);
    fclose(f);
    if (rd != (size_t)size) {
        free(buf);
        return NULL;
    }

    *outSize = (size_t)size;
    return buf;
}

// Writes the current VkPipelineCache contents to disk; a no-op if the cache is empty.
static void save_pipeline_cache_blob(void) {
    size_t size = 0;
    if (vkGetPipelineCacheData(gfxVkDevice, sPipelineCache, &size, NULL) != VK_SUCCESS || size == 0) {
        return;
    }
    void *data = malloc(size);
    if (!data) {
        return;
    }
    if (vkGetPipelineCacheData(gfxVkDevice, sPipelineCache, &size, data) == VK_SUCCESS) {
        FILE *f = fopen(fs_get_write_path(GFX_VULKAN_PIPELINE_CACHE_FILE), "wb");
        if (f) {
            fwrite(data, 1, size, f);
            fclose(f);
        }
    }
    free(data);
}

// Loads the on-disk pipeline cache (if any), then creates the shared
// descriptor set layouts, pipeline layout, frame UBO, and descriptor set.
static bool gfx_vulkan_pipeline_init(void) {
    size_t blobSize = 0;
    void *blob = load_pipeline_cache_blob(&blobSize);

    VkPipelineCacheCreateInfo cacheInfo = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO,
        .initialDataSize = blobSize,
        .pInitialData = blob,
    };
    VkResult res = vkCreatePipelineCache(gfxVkDevice, &cacheInfo, NULL, &sPipelineCache);
    free(blob);
    if (res != VK_SUCCESS) {
        return false;
    }

    return create_set_layouts() && create_pipeline_layout() && create_frame_ubo() && create_descriptor_set();
}

// Persists the pipeline cache to disk, then frees every resource this section owns.
static void gfx_vulkan_pipeline_destroy(void) {
    if (sDescriptorPool != VK_NULL_HANDLE) {
        vkDestroyDescriptorPool(gfxVkDevice, sDescriptorPool, NULL);
        sDescriptorPool = VK_NULL_HANDLE;
        sFrameDescriptorSet = VK_NULL_HANDLE;
    }
    gfx_vulkan_memory_destroy_buffer(&sFrameUboBuffer);
    sFrameUboMapped = NULL;

    if (gfxVkPipelineLayout != VK_NULL_HANDLE) {
        vkDestroyPipelineLayout(gfxVkDevice, gfxVkPipelineLayout, NULL);
        gfxVkPipelineLayout = VK_NULL_HANDLE;
    }
    if (sTextureSetLayout != VK_NULL_HANDLE) {
        vkDestroyDescriptorSetLayout(gfxVkDevice, sTextureSetLayout, NULL);
        sTextureSetLayout = VK_NULL_HANDLE;
    }
    if (sFrameSetLayout != VK_NULL_HANDLE) {
        vkDestroyDescriptorSetLayout(gfxVkDevice, sFrameSetLayout, NULL);
        sFrameSetLayout = VK_NULL_HANDLE;
    }
    if (sPipelineCache != VK_NULL_HANDLE) {
        save_pipeline_cache_blob();
        vkDestroyPipelineCache(gfxVkDevice, sPipelineCache, NULL);
        sPipelineCache = VK_NULL_HANDLE;
    }
}

// Maps a vertex attribute's width (in floats) to the matching VkFormat.
static VkFormat vk_format_for_attrib_size(uint8_t sizeInFloats) {
    switch (sizeInFloats) {
        case 2: return VK_FORMAT_R32G32_SFLOAT;
        case 3: return VK_FORMAT_R32G32B32_SFLOAT;
        default: return VK_FORMAT_R32G32B32A32_SFLOAT;
    }
}

// Builds one VkPipeline: vertex input derived from prg's baked attribute
// layout, fixed rasterization/blend state, and viewport/scissor/depth-test/
// depth-write/depth-bias/blend-enable left as dynamic state (set per-frame by
// the Draw section below, not baked per pipeline). Caller destroys the shader
// modules once this returns - a VkPipeline doesn't keep them alive.
static VkPipeline gfx_vulkan_pipeline_create(VkShaderModule vertModule, VkShaderModule fragModule, const struct ShaderProgram *prg) {
    VkVertexInputBindingDescription binding = {
        .binding = 0,
        .stride = (uint32_t)prg->num_floats * sizeof(float),
        .inputRate = VK_VERTEX_INPUT_RATE_VERTEX,
    };
    VkVertexInputAttributeDescription attrs[GFX_VULKAN_MAX_ATTRIBS];
    uint32_t offsetFloats = 0;
    for (uint8_t i = 0; i < prg->num_attribs; i++) {
        attrs[i] = (VkVertexInputAttributeDescription){
            .location = i,
            .binding = 0,
            .format = vk_format_for_attrib_size(prg->attrib_sizes[i]),
            .offset = offsetFloats * (uint32_t)sizeof(float),
        };
        offsetFloats += prg->attrib_sizes[i];
    }
    VkPipelineVertexInputStateCreateInfo vertexInput = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
        .vertexBindingDescriptionCount = 1,
        .pVertexBindingDescriptions = &binding,
        .vertexAttributeDescriptionCount = prg->num_attribs,
        .pVertexAttributeDescriptions = attrs,
    };

    VkPipelineInputAssemblyStateCreateInfo inputAssembly = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
        .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, // batched, non-indexed
    };
    VkPipelineViewportStateCreateInfo viewportState = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
        .viewportCount = 1,
        .scissorCount = 1,
    };
    VkPipelineRasterizationStateCreateInfo rasterization = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
        .polygonMode = VK_POLYGON_MODE_FILL,
        .cullMode = VK_CULL_MODE_NONE, // culling always happens on CPU
        .lineWidth = 1.0f,
    };
    VkPipelineMultisampleStateCreateInfo multisample = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
        .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT, // no MSAA, same precedent as the D3D11 backend
    };
    // depthCompareOp matches gfx_opengl_init's glDepthFunc(GL_LEQUAL); test/
    // write/bias-enable are dynamic state (see set_depth_test/set_depth_mask/
    // set_zmode_decal in the Draw section below).
    VkPipelineDepthStencilStateCreateInfo depthStencil = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
        .depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL,
    };
    // Fixed blend equation - only the enable bit is dynamic
    // (VK_DYNAMIC_STATE_COLOR_BLEND_ENABLE_EXT, set_use_alpha).
    VkPipelineColorBlendAttachmentState blendAttachment = {
        .srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA,
        .dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
        .colorBlendOp = VK_BLEND_OP_ADD,
        .srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
        .dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,
        .alphaBlendOp = VK_BLEND_OP_ADD,
        .colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                           VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,
    };
    VkPipelineColorBlendStateCreateInfo colorBlend = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
        .attachmentCount = 1,
        .pAttachments = &blendAttachment,
    };

    VkDynamicState dynamicStates[] = {
        VK_DYNAMIC_STATE_VIEWPORT,
        VK_DYNAMIC_STATE_SCISSOR,
        VK_DYNAMIC_STATE_DEPTH_TEST_ENABLE,
        VK_DYNAMIC_STATE_DEPTH_WRITE_ENABLE,
        VK_DYNAMIC_STATE_DEPTH_BIAS_ENABLE,
        VK_DYNAMIC_STATE_DEPTH_BIAS,
        VK_DYNAMIC_STATE_COLOR_BLEND_ENABLE_EXT,
    };
    VkPipelineDynamicStateCreateInfo dynamicState = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
        .dynamicStateCount = (uint32_t)(sizeof(dynamicStates) / sizeof(dynamicStates[0])),
        .pDynamicStates = dynamicStates,
    };

    VkPipelineShaderStageCreateInfo stages[2] = {
        { .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO, .stage = VK_SHADER_STAGE_VERTEX_BIT, .module = vertModule, .pName = "main" },
        { .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO, .stage = VK_SHADER_STAGE_FRAGMENT_BIT, .module = fragModule, .pName = "main" },
    };
    VkPipelineRenderingCreateInfo renderingInfo = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO,
        .colorAttachmentCount = 1,
        .pColorAttachmentFormats = &gfxVkSwapchainFormat,
        .depthAttachmentFormat = gfxVkDepthFormat,
    };
    VkGraphicsPipelineCreateInfo pipelineInfo = {
        .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        .pNext = &renderingInfo,
        .stageCount = 2,
        .pStages = stages,
        .pVertexInputState = &vertexInput,
        .pInputAssemblyState = &inputAssembly,
        .pViewportState = &viewportState,
        .pRasterizationState = &rasterization,
        .pMultisampleState = &multisample,
        .pDepthStencilState = &depthStencil,
        .pColorBlendState = &colorBlend,
        .pDynamicState = &dynamicState,
        .layout = gfxVkPipelineLayout,
    };

    VkPipeline pipeline = VK_NULL_HANDLE;
    VkResult res = vkCreateGraphicsPipelines(gfxVkDevice, sPipelineCache, 1, &pipelineInfo, NULL, &pipeline);
    if (res != VK_SUCCESS) {
        log_to_terminal("[vulkan] vkCreateGraphicsPipelines failed: %d\n", res);
        return VK_NULL_HANDLE;
    }
    return pipeline;
}

// Writes this frame's UBO slice (frame count/lightmap color/shader flags/
// filter) into the current frame-in-flight's region of the persistently-
// mapped frame UBO buffer, and binds descriptor set 0 (dynamic offset into
// that region) on the current command buffer. Call once per frame, before
// any draw_triangles.
static void gfx_vulkan_pipeline_update_frame_ubo(uint32_t frameCount) {
    uint32_t slot = gfx_vulkan_frame_get_current_slot();
    uint8_t *dst = sFrameUboMapped + slot * sFrameUboSliceStride;

    GfxVulkanFrameUBO ubo = { 0 };
    ubo.uFrameCount = (float)frameCount;
    ubo.uLightmapColor[0] = gVertexColor[0] / 255.0f;
    ubo.uLightmapColor[1] = gVertexColor[1] / 255.0f;
    ubo.uLightmapColor[2] = gVertexColor[2] / 255.0f;
    for (int i = 0; i < SHADER_FLAG_MAX; i++) {
        ubo.uShaderFlags[i][0] = gShaderFlags[i];
        ubo.uShaderFlagValues[i][0] = gShaderFlagValues[i];
    }
    ubo.uFilter = (int32_t)configFiltering;

    memcpy(dst, &ubo, sizeof(ubo));

    uint32_t dynamicOffset = slot * (uint32_t)sFrameUboSliceStride;
    vkCmdBindDescriptorSets(gfxVkCurrentCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, gfxVkPipelineLayout,
                             0, 1, &sFrameDescriptorSet, 1, &dynamicOffset);
}

// Pushes descriptor set 1 for whatever textures the Texture section above
// currently has bound on tiles 0/1 (only the tiles `usedTextures` marks
// true), against the shared layout, on the current command buffer.
static void gfx_vulkan_pipeline_bind_textures(const bool usedTextures[2]) {
    VkWriteDescriptorSet writes[2];
    VkDescriptorImageInfo imageInfos[2];
    uint32_t writeCount = 0;

    for (int tile = 0; tile < 2; tile++) {
        if (!usedTextures[tile]) { continue; }
        VkImageView view;
        VkSampler sampler;
        if (!gfx_vulkan_texture_get_bound(tile, &view, &sampler)) { continue; }

        imageInfos[writeCount] = (VkDescriptorImageInfo){
            .sampler = sampler,
            .imageView = view,
            .imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
        };
        writes[writeCount] = (VkWriteDescriptorSet){
            .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
            .dstBinding = (uint32_t)tile,
            .descriptorCount = 1,
            .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
            .pImageInfo = &imageInfos[writeCount],
        };
        writeCount++;
    }

    if (writeCount > 0) {
        vkCmdPushDescriptorSetKHR(gfxVkCurrentCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, gfxVkPipelineLayout,
                                   1, writeCount, writes);
    }
}

// Pushes the per-draw push constants against the shared layout, on the current command buffer.
static void gfx_vulkan_pipeline_push_draw_constants(const GfxVulkanDrawPushConstants *pc) {
    vkCmdPushConstants(gfxVkCurrentCommandBuffer, gfxVkPipelineLayout, VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(*pc), pc);
}

//////////////////////////////////////////////////////////////////////////////
// Shader - runtime GLSL generator (ported formula-for-formula from
// gfx_opengl.c's own generator) + glslang-to-SPIR-V compilation + the
// ShaderProgram pool (mirrors gfx_opengl.c's shader_program_pool[CC_MAX_SHADERS],
// same ring-buffer reuse policy - see gfx_cc.h's CC_MAX_SHADERS). This whole
// path runs lazily, the first time a given ColorCombiner hash is seen
// (gfx_vulkan_shader_create_and_load, called from gfx_pc.c via
// GfxRenderingAPI::create_and_load_new_shader); every later use of the same
// CC is a cache hit (gfx_vulkan_shader_lookup) - no shader/pipeline work at
// all, just picking the cached struct ShaderProgram*.
//////////////////////////////////////////////////////////////////////////////

// Same pool/reuse policy as gfx_opengl.c's shader_program_pool - one CC/shader
// combination is retired (its VkPipeline destroyed) whenever the ring buffer
// wraps around and reclaims its slot.
static struct ShaderProgram sShaderPool[CC_MAX_SHADERS];
static uint8_t sShaderPoolSize = 0;
static uint8_t sShaderPoolIndex = 0;

static bool gfx_vulkan_shader_init(void) {
    return glslang_initialize_process() != 0;
}

// Destroys every pooled pipeline, then matches gfx_vulkan_shader_init()'s
// glslang_initialize_process() with glslang_finalize_process().
static void gfx_vulkan_shader_destroy(void) {
    for (uint8_t i = 0; i < sShaderPoolSize; i++) {
        if (sShaderPool[i].pipeline != VK_NULL_HANDLE) {
            vkDestroyPipeline(gfxVkDevice, sShaderPool[i].pipeline, NULL);
        }
    }
    memset(sShaderPool, 0, sizeof(sShaderPool));
    sShaderPoolSize = 0;
    sShaderPoolIndex = 0;

    glslang_finalize_process();
}

// Finds an already-compiled pipeline for cc's exact hash, if any.
static struct ShaderProgram *gfx_vulkan_shader_lookup(struct ColorCombiner *cc) {
    for (uint8_t i = 0; i < sShaderPoolSize; i++) {
        if (sShaderPool[i].hash == cc->hash) {
            return &sShaderPool[i];
        }
    }
    return NULL;
}

// GfxRenderingAPI::shader_get_info glue.
static void gfx_vulkan_shader_get_info(struct ShaderProgram *prg, uint8_t *num_inputs, bool used_textures[2]) {
    *num_inputs = prg->num_inputs;
    used_textures[0] = prg->used_textures[0];
    used_textures[1] = prg->used_textures[1];
}

//////////////////////////////////////////////////////////////////////////////
// GLSL generator - ported from gfx_opengl.c's shader generator. Same
// algorithm/formula logic (shader_item_to_str/append_formula operate on the
// same cc->shader_commands the GL backend reads), adapted to explicit
// layout(location=)/layout(set=,binding=) qualifiers, an in/out varying
// interface instead of attribute/varying, and moving GL's loose per-shader
// uniforms into the shared FrameUBO (set 0) and push-constant blocks the
// Pipeline section above binds identically for every ColorCombiner pipeline.
//////////////////////////////////////////////////////////////////////////////

// Appends str to buf without a trailing newline, advancing *len.
static void append_str(char *buf, size_t *len, const char *str) {
    while (*str != '\0') buf[(*len)++] = *str++;
}

// Appends str to buf followed by a newline, advancing *len.
static void append_line(char *buf, size_t *len, const char *str) {
    while (*str != '\0') buf[(*len)++] = *str++;
    buf[(*len)++] = '\n';
}

// Maps one Color Combiner formula operand to its GLSL expression.
static const char *shader_item_to_str(uint32_t item, bool with_alpha, bool only_alpha, bool inputs_have_alpha, bool hint_single_element) {
    if (!only_alpha) {
        switch (item) {
            case SHADER_0:
                return with_alpha ? "vec4(0.0, 0.0, 0.0, 0.0)" : "vec3(0.0, 0.0, 0.0)";
            case SHADER_1:
                return with_alpha ? "vec4(1.0, 1.0, 1.0, 1.0)" : "vec3(1.0, 1.0, 1.0)";
            case SHADER_INPUT_1:
                return with_alpha || !inputs_have_alpha ? "vInput1" : "vInput1.rgb";
            case SHADER_INPUT_2:
                return with_alpha || !inputs_have_alpha ? "vInput2" : "vInput2.rgb";
            case SHADER_INPUT_3:
                return with_alpha || !inputs_have_alpha ? "vInput3" : "vInput3.rgb";
            case SHADER_INPUT_4:
                return with_alpha || !inputs_have_alpha ? "vInput4" : "vInput4.rgb";
            case SHADER_INPUT_5:
                return with_alpha || !inputs_have_alpha ? "vInput5" : "vInput5.rgb";
            case SHADER_INPUT_6:
                return with_alpha || !inputs_have_alpha ? "vInput6" : "vInput6.rgb";
            case SHADER_INPUT_7:
                return with_alpha || !inputs_have_alpha ? "vInput7" : "vInput7.rgb";
            case SHADER_INPUT_8:
                return with_alpha || !inputs_have_alpha ? "vInput8" : "vInput8.rgb";
            case SHADER_TEXEL0:
                return with_alpha ? "texVal0" : "texVal0.rgb";
            case SHADER_TEXEL0A:
                return hint_single_element ? "texVal0.a" :
                    (with_alpha ? "vec4(texVal0.a, texVal0.a, texVal0.a, texVal0.a)" : "vec3(texVal0.a, texVal0.a, texVal0.a)");
            case SHADER_TEXEL1:
                return with_alpha ? "texVal1" : "texVal1.rgb";
            case SHADER_TEXEL1A:
                return hint_single_element ? "texVal1.a" :
                    (with_alpha ? "vec4(texVal1.a, texVal1.a, texVal1.a, texVal1.a)" : "vec3(texVal1.a, texVal1.a, texVal1.a)");
            case SHADER_COMBINED:
                return with_alpha ? "texel" : "texel.rgb";
            case SHADER_COMBINEDA:
                return hint_single_element ? "texel.a" :
                    (with_alpha ? "vec4(texel.a, texel.a, texel.a, texel.a)" : "vec3(texel.a, texel.a, texel.a)");
            case SHADER_NOISE:
                return with_alpha ? "vec4(noise)" : "vec3(noise)";
        }
    } else {
        switch (item) {
            case SHADER_0: return "0.0";
            case SHADER_1: return "1.0";
            case SHADER_INPUT_1: return "vInput1.a";
            case SHADER_INPUT_2: return "vInput2.a";
            case SHADER_INPUT_3: return "vInput3.a";
            case SHADER_INPUT_4: return "vInput4.a";
            case SHADER_INPUT_5: return "vInput5.a";
            case SHADER_INPUT_6: return "vInput6.a";
            case SHADER_INPUT_7: return "vInput7.a";
            case SHADER_INPUT_8: return "vInput8.a";
            case SHADER_TEXEL0: return "texVal0.a";
            case SHADER_TEXEL0A: return "texVal0.a";
            case SHADER_TEXEL1: return "texVal1.a";
            case SHADER_TEXEL1A: return "texVal1.a";
            case SHADER_COMBINED: return "texel.a";
            case SHADER_COMBINEDA: return "texel.a";
            case SHADER_NOISE: return "noise";
        }
    }
    return "unknown";
}

// Emits one RDP Color Combiner formula (single/multiply/mix/general form) as
// a GLSL expression.
static void append_formula(char *buf, size_t *len, uint8_t *cmd, bool do_single, bool do_multiply, bool do_mix, bool with_alpha, bool only_alpha, bool opt_alpha) {
    if (do_single) {
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 3], with_alpha, only_alpha, opt_alpha, false));
    } else if (do_multiply) {
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 0], with_alpha, only_alpha, opt_alpha, false));
        append_str(buf, len, " * ");
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 2], with_alpha, only_alpha, opt_alpha, true));
    } else if (do_mix) {
        append_str(buf, len, "mix(");
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 1], with_alpha, only_alpha, opt_alpha, false));
        append_str(buf, len, ", ");
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 0], with_alpha, only_alpha, opt_alpha, false));
        append_str(buf, len, ", ");
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 2], with_alpha, only_alpha, opt_alpha, true));
        append_str(buf, len, ")");
    } else {
        append_str(buf, len, "(");
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 0], with_alpha, only_alpha, opt_alpha, false));
        append_str(buf, len, " - ");
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 1], with_alpha, only_alpha, opt_alpha, false));
        append_str(buf, len, ") * ");
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 2], with_alpha, only_alpha, opt_alpha, true));
        append_str(buf, len, " + ");
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 3], with_alpha, only_alpha, opt_alpha, false));
    }
}

// Identical text in every fragment shader variant - matches the single
// shared pipeline layout the Pipeline section above binds for every CC.
// std140/std430 layouts are spelled out explicitly since SPIR-V, unlike
// desktop GL, has no implicit default.
static const char *kFrameUboBlock =
    "layout(std140, set = 0, binding = 0) uniform FrameUBO {\n"
    "    float uFrameCount;\n"
    "    vec3 uLightmapColor;\n"
    "    int uShaderFlags[8];\n"
    "    float uShaderFlagValues[8];\n"
    "    int uFilter;\n"
    "} frameUbo;\n";

static const char *kPushConstantBlock =
    "layout(push_constant, std430) uniform PushConstants {\n"
    "    vec2 uTex0Size;\n"
    "    int uTex0Filter;\n"
    "    vec2 uTex1Size;\n"
    "    int uTex1Filter;\n"
    "} pc;\n";

// Builds the vertex shader source for one Color Combiner: a passthrough that
// forwards position/texcoords/fog/lightmap/CC-input attributes to varyings.
static void generate_vertex_shader(char *vs_buf, size_t *vs_len, struct CCFeatures *ccf, bool opt_fog, bool opt_light_map, bool opt_alpha) {
    int loc = 0;

    append_line(vs_buf, vs_len, "#version 450");
    *vs_len += sprintf(vs_buf + *vs_len, "layout(location = %d) in vec4 aVtxPos;\n", loc++);

    int varying = 0;
    for (int t = 0; t < 2; t++) {
        if (ccf->used_textures[t]) {
            *vs_len += sprintf(vs_buf + *vs_len, "layout(location = %d) in vec2 aTexCoord%d;\n", loc++, t);
            *vs_len += sprintf(vs_buf + *vs_len, "layout(location = %d) out vec2 vTexCoord%d;\n", varying++, t);
        }
    }
    if (opt_fog) {
        *vs_len += sprintf(vs_buf + *vs_len, "layout(location = %d) in vec4 aFog;\n", loc++);
        *vs_len += sprintf(vs_buf + *vs_len, "layout(location = %d) out vec4 vFog;\n", varying++);
    }
    if (opt_light_map) {
        *vs_len += sprintf(vs_buf + *vs_len, "layout(location = %d) in vec2 aLightMap;\n", loc++);
        *vs_len += sprintf(vs_buf + *vs_len, "layout(location = %d) out vec2 vLightMap;\n", varying++);
    }
    for (int i = 0; i < ccf->num_inputs; i++) {
        *vs_len += sprintf(vs_buf + *vs_len, "layout(location = %d) in vec%d aInput%d;\n", loc++, opt_alpha ? 4 : 3, i + 1);
        *vs_len += sprintf(vs_buf + *vs_len, "layout(location = %d) out vec%d vInput%d;\n", varying++, opt_alpha ? 4 : 3, i + 1);
    }

    append_line(vs_buf, vs_len, "void main() {");
    for (int t = 0; t < 2; t++) {
        if (ccf->used_textures[t]) {
            *vs_len += sprintf(vs_buf + *vs_len, "vTexCoord%d = aTexCoord%d;\n", t, t);
        }
    }
    if (opt_fog) { append_line(vs_buf, vs_len, "vFog = aFog;"); }
    if (opt_light_map) { append_line(vs_buf, vs_len, "vLightMap = aLightMap;"); }
    for (int i = 0; i < ccf->num_inputs; i++) {
        *vs_len += sprintf(vs_buf + *vs_len, "vInput%d = aInput%d;\n", i + 1, i + 1);
    }
    append_line(vs_buf, vs_len, "gl_Position = aVtxPos;");
    append_line(vs_buf, vs_len, "}");
}

// Builds the fragment shader source for one Color Combiner: samples up to 2
// textures, evaluates the CC formula stages, then applies optional fog/
// dither/world-geometry post-processing.
static void generate_fragment_shader(char *fs_buf, size_t *fs_len, struct ColorCombiner *cc, struct CCFeatures *ccf,
                                      bool opt_alpha, bool opt_fog, bool opt_texture_edge, bool opt_2cycle,
                                      bool opt_light_map, bool opt_dither, bool world_geometry) {
    append_line(fs_buf, fs_len, "#version 450");

    int varying = 0;
    for (int t = 0; t < 2; t++) {
        if (ccf->used_textures[t]) {
            *fs_len += sprintf(fs_buf + *fs_len, "layout(location = %d) in vec2 vTexCoord%d;\n", varying++, t);
        }
    }
    if (opt_fog) {
        *fs_len += sprintf(fs_buf + *fs_len, "layout(location = %d) in vec4 vFog;\n", varying++);
    }
    if (opt_light_map) {
        *fs_len += sprintf(fs_buf + *fs_len, "layout(location = %d) in vec2 vLightMap;\n", varying++);
    }
    for (int i = 0; i < ccf->num_inputs; i++) {
        *fs_len += sprintf(fs_buf + *fs_len, "layout(location = %d) in vec%d vInput%d;\n", varying++, opt_alpha ? 4 : 3, i + 1);
    }

    append_line(fs_buf, fs_len, "layout(location = 0) out vec4 fragColor;");

    for (int t = 0; t < 2; t++) {
        if (ccf->used_textures[t]) {
            *fs_len += sprintf(fs_buf + *fs_len, "layout(set = 1, binding = %d) uniform sampler2D uTex%d;\n", t, t);
        }
    }

    // 3-point texture filtering (ArthurCarvalho / twinaphex, mupen64plus-libretro) -
    // ported from gfx_opengl.c, texture2D() -> texture() for GLSL 450/SPIR-V.
    if (ccf->used_textures[0] || ccf->used_textures[1]) {
        append_line(fs_buf, fs_len, "#define TEX_OFFSET(off) texture(tex, texCoord - (off)/texSize)");
        append_line(fs_buf, fs_len, "vec4 filter3point(in sampler2D tex, in vec2 texCoord, in vec2 texSize) {");
        append_line(fs_buf, fs_len, "    vec2 offset = fract(texCoord*texSize - vec2(0.5));");
        append_line(fs_buf, fs_len, "    offset -= step(1.0, offset.x + offset.y);");
        append_line(fs_buf, fs_len, "    vec4 c0 = TEX_OFFSET(offset);");
        append_line(fs_buf, fs_len, "    vec4 c1 = TEX_OFFSET(vec2(offset.x - sign(offset.x), offset.y));");
        append_line(fs_buf, fs_len, "    vec4 c2 = TEX_OFFSET(vec2(offset.x, offset.y - sign(offset.y)));");
        append_line(fs_buf, fs_len, "    return c0 + abs(offset.x)*(c1-c0) + abs(offset.y)*(c2-c0);");
        append_line(fs_buf, fs_len, "}");
        // `filter` is a GLSL reserved word for SPIR-V targets (unlike desktop
        // GL/GLSL ES, where gfx_opengl.c's identical parameter name compiles
        // fine) - renamed to filterMode here to avoid glslang rejecting it.
        append_line(fs_buf, fs_len, "vec4 sampleTex(in sampler2D tex, in vec2 uv, in vec2 texSize, in bool dofilter, in int filterMode) {");
        append_line(fs_buf, fs_len, "    if (dofilter && filterMode == 2)");
        append_line(fs_buf, fs_len, "        return filter3point(tex, uv, texSize);");
        append_line(fs_buf, fs_len, "    else");
        append_line(fs_buf, fs_len, "        return texture(tex, uv);");
        append_line(fs_buf, fs_len, "}");
    }

    // world_geometry post-process helpers - ported from gfx_opengl.c (pure
    // math, no GL-specific calls). gl_FragCoord's origin is top-left in
    // Vulkan vs. bottom-left in GL, so dither4x4/scanlines end up mirrored
    // vertically relative to the OpenGL backend - both are periodic patterns
    // so this isn't visually distinguishable.
    if (world_geometry) {
        append_line(fs_buf, fs_len, "float dither4x4(vec2 position, float brightness) {");
        append_line(fs_buf, fs_len, "    int x = int(mod(position.x, 4.0));");
        append_line(fs_buf, fs_len, "    int y = int(mod(position.y, 4.0));");
        append_line(fs_buf, fs_len, "    int index = x + y * 4;");
        append_line(fs_buf, fs_len, "    float limit = 0.0;");
        append_line(fs_buf, fs_len, "    if (x < 8) {");
        append_line(fs_buf, fs_len, "        if (index == 0) limit = 0.0625;");
        append_line(fs_buf, fs_len, "        if (index == 1) limit = 0.5625;");
        append_line(fs_buf, fs_len, "        if (index == 2) limit = 0.1875;");
        append_line(fs_buf, fs_len, "        if (index == 3) limit = 0.6875;");
        append_line(fs_buf, fs_len, "        if (index == 4) limit = 0.8125;");
        append_line(fs_buf, fs_len, "        if (index == 5) limit = 0.3125;");
        append_line(fs_buf, fs_len, "        if (index == 6) limit = 0.9375;");
        append_line(fs_buf, fs_len, "        if (index == 7) limit = 0.4375;");
        append_line(fs_buf, fs_len, "        if (index == 8) limit = 0.25;");
        append_line(fs_buf, fs_len, "        if (index == 9) limit = 0.75;");
        append_line(fs_buf, fs_len, "        if (index == 10) limit = 0.125;");
        append_line(fs_buf, fs_len, "        if (index == 11) limit = 0.625;");
        append_line(fs_buf, fs_len, "        if (index == 12) limit = 1.0;");
        append_line(fs_buf, fs_len, "        if (index == 13) limit = 0.5;");
        append_line(fs_buf, fs_len, "        if (index == 14) limit = 0.875;");
        append_line(fs_buf, fs_len, "        if (index == 15) limit = 0.375;");
        append_line(fs_buf, fs_len, "    }");
        append_line(fs_buf, fs_len, "    return brightness < limit ? 0.0 : 1.0;");
        append_line(fs_buf, fs_len, "}");

        append_line(fs_buf, fs_len, "vec3 rgb2hsv(vec3 c) {");
        append_line(fs_buf, fs_len, "    vec4 K = vec4(0.0, -1.0/3.0, 2.0/3.0, -1.0);");
        append_line(fs_buf, fs_len, "    vec4 p = mix(vec4(c.bg, K.wz),");
        append_line(fs_buf, fs_len, "                 vec4(c.gb, K.xy),");
        append_line(fs_buf, fs_len, "                 step(c.b, c.g));");
        append_line(fs_buf, fs_len, "    vec4 q = mix(vec4(p.xyw, c.r),");
        append_line(fs_buf, fs_len, "                 vec4(c.r, p.yzx),");
        append_line(fs_buf, fs_len, "                 step(p.x, c.r));");
        append_line(fs_buf, fs_len, "    float d = q.x - min(q.w, q.y);");
        append_line(fs_buf, fs_len, "    float e = 1.0e-10;");
        append_line(fs_buf, fs_len, "    return vec3(");
        append_line(fs_buf, fs_len, "        abs(q.z + (q.w - q.y) / (6.0 * d + e)),");
        append_line(fs_buf, fs_len, "        d / (q.x + e),");
        append_line(fs_buf, fs_len, "        q.x");
        append_line(fs_buf, fs_len, "    );");
        append_line(fs_buf, fs_len, "}");
        append_line(fs_buf, fs_len, "");
        append_line(fs_buf, fs_len, "vec3 hsv2rgb(vec3 c) {");
        append_line(fs_buf, fs_len, "    vec3 p = abs(fract(c.xxx + vec3(0.0, 2.0/3.0, 1.0/3.0)) * 6.0 - 3.0);");
        append_line(fs_buf, fs_len, "    return c.z * mix(vec3(1.0), clamp(p - 1.0, 0.0, 1.0), c.y);");
        append_line(fs_buf, fs_len, "}");
    }

    if ((opt_alpha && opt_dither) || ccf->do_noise) {
        append_line(fs_buf, fs_len, "float random(in vec3 value) {");
        append_line(fs_buf, fs_len, "    float random = dot(sin(value), vec3(12.9898, 78.233, 37.719));");
        append_line(fs_buf, fs_len, "    return fract(sin(random) * 143758.5453);");
        append_line(fs_buf, fs_len, "}");
    }

    append_line(fs_buf, fs_len, kFrameUboBlock);
    append_line(fs_buf, fs_len, kPushConstantBlock);

    append_line(fs_buf, fs_len, "void main() {");

    if ((opt_alpha && opt_dither) || ccf->do_noise) {
        append_line(fs_buf, fs_len, "float noise = random(floor(vec3(gl_FragCoord.xy, frameUbo.uFrameCount)));");
    }

    if (ccf->used_textures[0]) {
        append_line(fs_buf, fs_len, "vec4 texVal0 = sampleTex(uTex0, vTexCoord0, pc.uTex0Size, pc.uTex0Filter != 0, frameUbo.uFilter);");
    }
    if (ccf->used_textures[1]) {
        if (opt_light_map) {
            append_line(fs_buf, fs_len, "vec4 texVal1 = sampleTex(uTex1, vLightMap, pc.uTex1Size, pc.uTex1Filter != 0, frameUbo.uFilter);");
            append_line(fs_buf, fs_len, "texVal0.rgb *= frameUbo.uLightmapColor.rgb;");
            append_line(fs_buf, fs_len, "texVal1.rgb = texVal1.rgb * texVal1.rgb + texVal1.rgb;");
        } else {
            append_line(fs_buf, fs_len, "vec4 texVal1 = sampleTex(uTex1, vTexCoord1, pc.uTex1Size, pc.uTex1Filter != 0, frameUbo.uFilter);");
        }
    }

    append_line(fs_buf, fs_len, opt_alpha ? "vec4 texel = vec4(0.0, 0.0, 0.0, 0.0);" : "vec3 texel = vec3(0.0, 0.0, 0.0);");

    for (int i = 0; i < (opt_2cycle + 1); i++) {
        uint8_t *cmd = &cc->shader_commands[i * 8];
        append_str(fs_buf, fs_len, "texel = ");
        if (!ccf->color_alpha_same[i] && opt_alpha) {
            append_str(fs_buf, fs_len, "vec4(");
            append_formula(fs_buf, fs_len, cmd, ccf->do_single[i*2+0], ccf->do_multiply[i*2+0], ccf->do_mix[i*2+0], false, false, true);
            append_str(fs_buf, fs_len, ", ");
            append_formula(fs_buf, fs_len, cmd, ccf->do_single[i*2+1], ccf->do_multiply[i*2+1], ccf->do_mix[i*2+1], true, true, true);
            append_str(fs_buf, fs_len, ")");
        } else {
            append_formula(fs_buf, fs_len, cmd, ccf->do_single[i*2+0], ccf->do_multiply[i*2+0], ccf->do_mix[i*2+0], opt_alpha, false, opt_alpha);
        }
        append_line(fs_buf, fs_len, ";");

        if (i == 0) {
            append_line(fs_buf, fs_len, "texel = mod(texel + 0.5, 2.0) - 0.5;");
        }
    }

    append_line(fs_buf, fs_len, "texel = clamp(mod(texel + 0.5, 2.0) - 0.5, 0.0, 1.0);");

    if (opt_texture_edge && opt_alpha) {
        append_line(fs_buf, fs_len, "if (texel.a > 0.3) texel.a = 1.0; else discard;");
    }

    if (world_geometry) {
        append_line(fs_buf, fs_len, "if (frameUbo.uShaderFlags[0] == 1) {");
        append_line(fs_buf, fs_len, "vec3 hsv = rgb2hsv(texel.rgb);");
        append_line(fs_buf, fs_len, "hsv.x = fract(hsv.x + frameUbo.uShaderFlagValues[0]);");
        append_line(fs_buf, fs_len, "vec3 finalColor = hsv2rgb(hsv);");
        append_line(fs_buf, fs_len, "texel.rgb = finalColor;");
        append_line(fs_buf, fs_len, "}");

        append_line(fs_buf, fs_len, "if (frameUbo.uShaderFlags[1] == 1) {");
        append_line(fs_buf, fs_len, "const vec3 w = vec3(0.2125, 0.7154, 0.0721);");
        append_line(fs_buf, fs_len, "vec3 intensity = vec3(dot(texel.rgb, w));");
        append_line(fs_buf, fs_len, "texel.rgb = mix(intensity, texel.rgb, frameUbo.uShaderFlagValues[1]);");
        append_line(fs_buf, fs_len, "}");

        append_line(fs_buf, fs_len, "if (frameUbo.uShaderFlags[2] == 1) {");
        append_line(fs_buf, fs_len, "texel.rgb *= frameUbo.uShaderFlagValues[2];");
        append_line(fs_buf, fs_len, "}");

        append_line(fs_buf, fs_len, "if (frameUbo.uShaderFlags[3] == 1) {");
        append_line(fs_buf, fs_len, "texel.rgb = 0.5 + frameUbo.uShaderFlagValues[3] * (texel.rgb - 0.5);");
        append_line(fs_buf, fs_len, "}");

        append_line(fs_buf, fs_len, "if (frameUbo.uShaderFlags[4] == 1) {");
        append_line(fs_buf, fs_len, "texel.rgb = texel.rgb + (frameUbo.uShaderFlagValues[4] - 2) * texel.rgb + texel.rgb;");
        append_line(fs_buf, fs_len, "}");

        append_line(fs_buf, fs_len, "if (frameUbo.uShaderFlags[5] == 1) {");
        append_line(fs_buf, fs_len, "texel.rgb *= dither4x4(gl_FragCoord.xy, dot(texel.rgb, vec3(0.299, 0.587, 0.114)));");
        append_line(fs_buf, fs_len, "}");

        append_line(fs_buf, fs_len, "if (frameUbo.uShaderFlags[6] == 1) {");
        append_line(fs_buf, fs_len, "int levels = int(max(1.0, frameUbo.uShaderFlagValues[6]));");
        append_line(fs_buf, fs_len, "texel.rgb = floor(texel.rgb * levels) / levels;");
        append_line(fs_buf, fs_len, "}");

        append_line(fs_buf, fs_len, "if (frameUbo.uShaderFlags[7] == 1) {");
        append_line(fs_buf, fs_len, "float scan = sin(gl_FragCoord.y * 1.5) * 0.04;");
        append_line(fs_buf, fs_len, "texel.rgb -= scan * frameUbo.uShaderFlagValues[7];");
        append_line(fs_buf, fs_len, "}");
    }

    if (opt_fog) {
        if (opt_alpha) {
            append_line(fs_buf, fs_len, "texel = vec4(mix(texel.rgb, vFog.rgb, vFog.a), texel.a);");
        } else {
            append_line(fs_buf, fs_len, "texel = mix(texel, vFog.rgb, vFog.a);");
        }
    }

    if (opt_alpha && opt_dither) {
        append_line(fs_buf, fs_len, "texel.a = noise < texel.a ? 1.0 : 0.0;");
    }

    append_line(fs_buf, fs_len, opt_alpha ? "fragColor = texel;" : "fragColor = vec4(texel, 1.0);");
    append_line(fs_buf, fs_len, "}");
}

// Preprocesses/parses/links `source` and generates SPIR-V; *outWords is
// caller-owned (malloc'd).
static bool compile_stage(const char *source, glslang_stage_t stage, const char *stageName, uint32_t **outWords, size_t *outWordCount) {
    glslang_input_t input = {
        .language = GLSLANG_SOURCE_GLSL,
        .stage = stage,
        .client = GLSLANG_CLIENT_VULKAN,
        .client_version = GLSLANG_TARGET_VULKAN_1_3,
        .target_language = GLSLANG_TARGET_SPV,
        .target_language_version = GLSLANG_TARGET_SPV_1_6,
        .code = source,
        .default_version = 450,
        .default_profile = GLSLANG_NO_PROFILE,
        .messages = GLSLANG_MSG_DEFAULT_BIT,
        .resource = glslang_default_resource(),
    };

    glslang_shader_t *shader = glslang_shader_create(&input);
    if (!glslang_shader_preprocess(shader, &input)) {
        log_to_terminal("[vulkan] %s shader preprocess failed:\n%s\n--- source ---\n%s\n", stageName, glslang_shader_get_info_log(shader), source);
        glslang_shader_delete(shader);
        return false;
    }
    if (!glslang_shader_parse(shader, &input)) {
        log_to_terminal("[vulkan] %s shader parse failed:\n%s\n--- source ---\n%s\n", stageName, glslang_shader_get_info_log(shader), source);
        glslang_shader_delete(shader);
        return false;
    }

    glslang_program_t *program = glslang_program_create();
    glslang_program_add_shader(program, shader);
    if (!glslang_program_link(program, GLSLANG_MSG_SPV_RULES_BIT | GLSLANG_MSG_VULKAN_RULES_BIT)) {
        log_to_terminal("[vulkan] %s shader link failed:\n%s\n", stageName, glslang_program_get_info_log(program));
        glslang_program_delete(program);
        glslang_shader_delete(shader);
        return false;
    }

    glslang_program_SPIRV_generate(program, stage);
    size_t wordCount = glslang_program_SPIRV_get_size(program);
    uint32_t *words = malloc(wordCount * sizeof(uint32_t));
    if (words) {
        memcpy(words, glslang_program_SPIRV_get_ptr(program), wordCount * sizeof(uint32_t));
    }

    glslang_program_delete(program);
    glslang_shader_delete(shader);

    if (!words) { return false; }
    *outWords = words;
    *outWordCount = wordCount;
    return true;
}

// Wraps a SPIR-V word array in a VkShaderModule.
static VkShaderModule create_shader_module(const uint32_t *words, size_t wordCount) {
    VkShaderModuleCreateInfo createInfo = {
        .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .codeSize = wordCount * sizeof(uint32_t),
        .pCode = words,
    };
    VkShaderModule module = VK_NULL_HANDLE;
    vkCreateShaderModule(gfxVkDevice, &createInfo, NULL, &module);
    return module;
}

// Generates GLSL, compiles it to SPIR-V, builds a VkPipeline for this Color
// Combiner, and stores it in the ring-buffer shader pool. This is the one
// point in the frame where the CPU can stall - compiling GLSL->SPIR-V plus
// vkCreateGraphicsPipelines for a CC combination never seen before - the
// Pipeline section's disk-persisted VkPipelineCache makes repeat runs cheap
// once a combination has been compiled once anywhere on this machine, but a
// first encounter within a single run still pays the full cost (measured
// under VULKAN_DEBUG, not yet mitigated).
static struct ShaderProgram *gfx_vulkan_shader_create_and_load(struct ColorCombiner *cc) {
#if defined(VULKAN_DEBUG)
    uint64_t perfFreq = SDL_GetPerformanceFrequency();
    uint64_t tStart = SDL_GetPerformanceCounter();
#endif

    struct CCFeatures ccf = { 0 };
    gfx_cc_get_features(cc, &ccf);

    bool opt_alpha = cc->cm.use_alpha;
    bool opt_fog = cc->cm.use_fog;
    bool opt_texture_edge = cc->cm.texture_edge;
    bool opt_2cycle = cc->cm.use_2cycle;
    bool opt_light_map = cc->cm.light_map;
    bool world_geometry = cc->cm.world_geometry;
    bool opt_dither = cc->cm.use_dither;

    // Fixed-size scratch buffers for the generated GLSL text - same pattern
    // gfx_opengl.c uses (8192 bytes there; doubled here since explicit
    // layout()/set qualifiers make the Vulkan variant longer). Not bounds-
    // checked against overflow, matching the existing GL backend's risk
    // tolerance for this code path.
    char *vs_buf = malloc(16384);
    char *fs_buf = malloc(16384);
    size_t vs_len = 0, fs_len = 0;
    if (!vs_buf || !fs_buf) {
        free(vs_buf);
        free(fs_buf);
        return NULL;
    }

    generate_vertex_shader(vs_buf, &vs_len, &ccf, opt_fog, opt_light_map, opt_alpha);
    generate_fragment_shader(fs_buf, &fs_len, cc, &ccf, opt_alpha, opt_fog, opt_texture_edge, opt_2cycle, opt_light_map, opt_dither, world_geometry);
    vs_buf[vs_len] = '\0';
    fs_buf[fs_len] = '\0';

#if defined(VULKAN_DEBUG)
    uint64_t tAfterGen = SDL_GetPerformanceCounter();
#endif

    uint32_t *vsWords = NULL, *fsWords = NULL;
    size_t vsWordCount = 0, fsWordCount = 0;
    bool ok = compile_stage(vs_buf, GLSLANG_STAGE_VERTEX, "vertex", &vsWords, &vsWordCount) &&
              compile_stage(fs_buf, GLSLANG_STAGE_FRAGMENT, "fragment", &fsWords, &fsWordCount);
    free(vs_buf);
    free(fs_buf);
    if (!ok) {
        free(vsWords);
        free(fsWords);
        return NULL;
    }

#if defined(VULKAN_DEBUG)
    uint64_t tAfterSpirv = SDL_GetPerformanceCounter();
#endif

    VkShaderModule vertModule = create_shader_module(vsWords, vsWordCount);
    VkShaderModule fragModule = create_shader_module(fsWords, fsWordCount);
    free(vsWords);
    free(fsWords);
    if (vertModule == VK_NULL_HANDLE || fragModule == VK_NULL_HANDLE) {
        vkDestroyShaderModule(gfxVkDevice, vertModule, NULL);
        vkDestroyShaderModule(gfxVkDevice, fragModule, NULL);
        return NULL;
    }

    struct ShaderProgram *prg = &sShaderPool[sShaderPoolIndex];
    if (prg->pipeline != VK_NULL_HANDLE) {
        // Ring buffer wrapped around - this slot's old pipeline is being
        // retired. Safe without a device-idle wait: gfx_pc.c only reaches
        // here after a gfx_flush() of anything using the previous
        // occupant's pipeline, and gfx_vulkan_frame_start() already waited
        // out the frame-in-flight slot whose command buffer might reference it.
        vkDestroyPipeline(gfxVkDevice, prg->pipeline, NULL);
    }
    sShaderPoolIndex = (sShaderPoolIndex + 1) % CC_MAX_SHADERS;
    if (sShaderPoolSize < CC_MAX_SHADERS) { sShaderPoolSize++; }

    memset(prg, 0, sizeof(*prg));
    prg->hash = cc->hash;
    prg->num_inputs = (uint8_t)ccf.num_inputs;
    prg->used_textures[0] = ccf.used_textures[0];
    prg->used_textures[1] = ccf.used_textures[1];
    prg->opt_alpha = opt_alpha;
    prg->used_noise = (opt_alpha && opt_dither) || ccf.do_noise;
    prg->used_lightmap = opt_light_map;
    prg->world_geometry = world_geometry;

    // Vertex layout, baked as fixed pipeline state - same incremental
    // computation as gfx_opengl.c's equivalent loop.
    size_t cnt = 0;
    size_t num_floats = 4;
    prg->attrib_sizes[cnt++] = 4; // aVtxPos
    for (int t = 0; t < 2; t++) {
        if (ccf.used_textures[t]) {
            prg->attrib_sizes[cnt++] = 2;
            num_floats += 2;
        }
    }
    if (opt_fog) {
        prg->attrib_sizes[cnt++] = 4;
        num_floats += 4;
    }
    if (opt_light_map) {
        prg->attrib_sizes[cnt++] = 2;
        num_floats += 2;
    }
    for (int i = 0; i < ccf.num_inputs; i++) {
        prg->attrib_sizes[cnt++] = opt_alpha ? 4 : 3;
        num_floats += opt_alpha ? 4 : 3;
    }
    prg->num_attribs = (uint8_t)cnt;
    prg->num_floats = (uint8_t)num_floats;

    prg->pipeline = gfx_vulkan_pipeline_create(vertModule, fragModule, prg);

    vkDestroyShaderModule(gfxVkDevice, vertModule, NULL);
    vkDestroyShaderModule(gfxVkDevice, fragModule, NULL);

#if defined(VULKAN_DEBUG)
    uint64_t tEnd = SDL_GetPerformanceCounter();
    double toMs = 1000.0 / (double)perfFreq;
    log_to_terminal("[vulkan] new pipeline for CC 0x%016llx: %.2fms total (glsl=%.2fms spirv=%.2fms pipeline=%.2fms)\n",
            (unsigned long long)cc->hash, (double)(tEnd - tStart) * toMs,
            (double)(tAfterGen - tStart) * toMs, (double)(tAfterSpirv - tAfterGen) * toMs,
            (double)(tEnd - tAfterSpirv) * toMs);
#endif

    if (prg->pipeline == VK_NULL_HANDLE) {
        memset(prg, 0, sizeof(*prg));
        return NULL;
    }

    return prg;
}

//////////////////////////////////////////////////////////////////////////////
// Draw - vertex streaming (one persistently-mapped, host-visible arena per
// frame-in-flight slot; gfx_vulkan_frame_start() already waits out a slot's
// previous submission before it's reused, so by the time a slot's arena is
// written again the GPU is guaranteed done reading the previous frame's
// contents from it - no ring-buffer wraparound bookkeeping needed within a
// single frame) and all per-frame dynamic-state replay.
//////////////////////////////////////////////////////////////////////////////

// One batch is MAX_BUFFERED (256, gfx.h) triangles * 3 verts * up to 26
// floats = ~80KB. 16MB/slot covers ~200 flushes in a single frame,
// comfortably more than a real level needs; gfx_vulkan_draw_triangles clamps
// and warns instead of overrunning if a scene ever exceeds it.
#define GFX_VULKAN_ARENA_SIZE (16u * 1024u * 1024u)

typedef struct {
    GfxVulkanBuffer buffer;
    uint8_t *mapped;
    VkDeviceSize offset;
} GfxVulkanVertexArena;

static GfxVulkanVertexArena sArenas[GFX_VULKAN_FRAMES_IN_FLIGHT];
static bool sOverflowWarned = false;

// gfx_pc.c's rendering_state cache only calls set_viewport/set_scissor/
// set_depth_*/set_use_alpha again when the *value* changes from the previous
// frame (correct for GL/D3D11, where that state lives on a persistent
// context). Vulkan dynamic state doesn't survive across command buffers -
// vkResetCommandPool wipes it, and a fresh vkBeginCommandBuffer starts with
// it undefined - so a frame where nothing changes would otherwise submit a
// command buffer that never sets viewport/scissor/depth/blend at all. Fix:
// cache our own copy of the last value passed to each setter and
// unconditionally replay all of them once per frame
// (gfx_vulkan_draw_begin_frame, before any draw), instead of relying on
// gfx_pc.c to tell us again.
typedef struct { int x, y, width, height; } GfxVulkanRect;
static GfxVulkanRect sViewport = { 0, 0, 0, 0 };
static GfxVulkanRect sScissor = { 0, 0, 0, 0 };
static bool sDepthTest = false;
static bool sDepthMask = true;
static bool sZmodeDecal = false;
static bool sUseAlpha = false;

static void apply_viewport(void) {
    // Unlike GL *and* D3D11, Vulkan's clip space has +Y pointing down (not
    // just a differently-placed viewport origin - the NDC-to-viewport mapping
    // itself is flipped). gfx_pc.c writes clip-space positions on the CPU
    // assuming the GL/D3D convention (gl_Position is a passthrough), so
    // reusing gfx_direct3d11.cpp's rectangle-repositioning alone (flip the
    // origin, keep height positive) isn't enough here. A negative viewport
    // height cancels Vulkan's inherent Y flip (core since 1.1/
    // VK_KHR_maintenance1, unconditionally available at this backend's 1.3
    // floor) without having to patch every generated vertex shader.
    //
    // sViewport starts zeroed until the first real set_viewport call. Unlike
    // scissor, a 0-sized viewport is invalid to *set* (VUID-VkViewport-width-01770
    // requires width > 0), so skip the call entirely rather than submit a
    // degenerate one.
    if (sViewport.width <= 0 || sViewport.height <= 0) {
        return;
    }
    VkViewport viewport = {
        .x = (float)sViewport.x,
        .y = (float)((int)gfxVkSwapchainExtent.height - sViewport.y),
        .width = (float)sViewport.width,
        .height = -(float)sViewport.height,
        .minDepth = 0.0f,
        .maxDepth = 1.0f,
    };
    vkCmdSetViewport(gfxVkCurrentCommandBuffer, 0, 1, &viewport);
}

// Vulkan scissor rects are top-left origin like viewport, so the same Y flip
// as apply_viewport applies (a negative/degenerate result is clamped to 0,
// unlike viewport, since a 0-sized scissor rect is valid to set).
static void apply_scissor(void) {
    int flippedY = (int)gfxVkSwapchainExtent.height - sScissor.y - sScissor.height;
    VkRect2D scissor = {
        .offset = { sScissor.x, flippedY < 0 ? 0 : flippedY },
        .extent = { (uint32_t)sScissor.width, (uint32_t)sScissor.height },
    };
    vkCmdSetScissor(gfxVkCurrentCommandBuffer, 0, 1, &scissor);
}

// Replays the cached depth test/write/bias-enable state onto the current command buffer.
static void apply_depth_state(void) {
    VkCommandBuffer cmd = gfxVkCurrentCommandBuffer;
    vkCmdSetDepthTestEnable(cmd, sDepthTest);
    vkCmdSetDepthWriteEnable(cmd, sDepthMask);
    vkCmdSetDepthBiasEnable(cmd, sZmodeDecal);
    if (sZmodeDecal) {
        // Matches gfx_opengl.c's glPolygonOffset(-2, -2); GL/Vulkan define the
        // constant/slope factor units differently (implementation-dependent
        // multiples of the format's minimum resolvable depth step in both
        // cases), so this is a same-ballpark port, not a bit-exact one -
        // revisit only if z-fighting becomes visible.
        vkCmdSetDepthBias(cmd, -2.0f, 0.0f, -2.0f);
    }
}

// Replays the cached blend-enable state onto the current command buffer.
static void apply_blend_state(void) {
    VkBool32 enable = sUseAlpha ? VK_TRUE : VK_FALSE;
    vkCmdSetColorBlendEnableEXT(gfxVkCurrentCommandBuffer, 0, 1, &enable);
}

// Allocates one vertex-streaming arena per frame-in-flight slot.
static bool gfx_vulkan_draw_init(void) {
    for (int i = 0; i < GFX_VULKAN_FRAMES_IN_FLIGHT; i++) {
        void *mapped = NULL;
        if (!gfx_vulkan_memory_create_streaming_buffer(GFX_VULKAN_ARENA_SIZE, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                                                         &sArenas[i].buffer, &mapped)) {
            return false;
        }
        sArenas[i].mapped = (uint8_t *)mapped;
        sArenas[i].offset = 0;
    }
    return true;
}

// Frees every vertex-streaming arena.
static void gfx_vulkan_draw_destroy(void) {
    for (int i = 0; i < GFX_VULKAN_FRAMES_IN_FLIGHT; i++) {
        gfx_vulkan_memory_destroy_buffer(&sArenas[i].buffer);
        sArenas[i].mapped = NULL;
        sArenas[i].offset = 0;
    }
    sOverflowWarned = false;
}

// Rewinds this frame's vertex arena and reapplies all cached dynamic state.
static void gfx_vulkan_draw_begin_frame(void) {
    sArenas[gfx_vulkan_frame_get_current_slot()].offset = 0;

    // Must run before the first draw of the frame - see the comment above
    // sViewport for why this can't be left to gfx_pc.c's change-detection.
    apply_viewport();
    apply_scissor();
    apply_depth_state();
    apply_blend_state();
}

// Copies buf_vbo into the current frame's vertex arena, binds the CC's
// pipeline/textures/push constants, and issues a non-indexed triangle-list
// draw. Takes the currently-loaded ShaderProgram explicitly (the glue section
// at the bottom of this file tracks it across load_shader calls) rather than
// querying it itself, to keep this section independent of the Shader
// section's shader-selection bookkeeping.
static void gfx_vulkan_draw_triangles(const struct ShaderProgram *prg, float buf_vbo[], size_t buf_vbo_len, size_t buf_vbo_num_tris) {
    if (!prg || prg->pipeline == VK_NULL_HANDLE) {
        return;
    }

    GfxVulkanVertexArena *arena = &sArenas[gfx_vulkan_frame_get_current_slot()];
    VkDeviceSize byteSize = (VkDeviceSize)buf_vbo_len * sizeof(float);
    if (arena->offset + byteSize > GFX_VULKAN_ARENA_SIZE) {
        if (!sOverflowWarned) {
            log_to_terminal("[vulkan] vertex arena exhausted this frame, dropping draw (increase GFX_VULKAN_ARENA_SIZE)\n");
            sOverflowWarned = true;
        }
        return;
    }

    memcpy(arena->mapped + arena->offset, buf_vbo, byteSize);

    VkCommandBuffer cmd = gfxVkCurrentCommandBuffer;
    vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, prg->pipeline);

    VkDeviceSize bindOffset = arena->offset;
    vkCmdBindVertexBuffers(cmd, 0, 1, &arena->buffer.buffer, &bindOffset);

    gfx_vulkan_pipeline_bind_textures(prg->used_textures);

    GfxVulkanDrawPushConstants pc = { 0 };
    float size[2];
    bool linearFilter;
    if (prg->used_textures[0] && gfx_vulkan_texture_get_bound_info(0, size, &linearFilter)) {
        pc.tex0Size[0] = size[0];
        pc.tex0Size[1] = size[1];
        pc.tex0Filter = linearFilter ? 1 : 0;
    }
    if (prg->used_textures[1] && gfx_vulkan_texture_get_bound_info(1, size, &linearFilter)) {
        pc.tex1Size[0] = size[0];
        pc.tex1Size[1] = size[1];
        pc.tex1Filter = linearFilter ? 1 : 0;
    }
    gfx_vulkan_pipeline_push_draw_constants(&pc);

#if defined(DEVELOPMENT)
    char label[32];
    snprintf(label, sizeof(label), "CC 0x%016llx", (unsigned long long)prg->hash);
    gfx_vulkan_debug_begin_label(cmd, label);
#endif
    vkCmdDraw(cmd, (uint32_t)(3 * buf_vbo_num_tris), 1, 0, 0);
#if defined(DEVELOPMENT)
    gfx_vulkan_debug_end_label(cmd);
#endif

    arena->offset += byteSize;
}

// Caches the new value and reapplies it immediately (see the sViewport
// comment above apply_viewport for why this can't wait for begin_frame).
static void gfx_vulkan_draw_set_depth_test(bool depth_test) {
    sDepthTest = depth_test;
    apply_depth_state();
}

// See gfx_vulkan_draw_set_depth_test above.
static void gfx_vulkan_draw_set_depth_mask(bool z_upd) {
    sDepthMask = z_upd;
    apply_depth_state();
}

// See gfx_vulkan_draw_set_depth_test above.
static void gfx_vulkan_draw_set_zmode_decal(bool zmode_decal) {
    sZmodeDecal = zmode_decal;
    apply_depth_state();
}

// See gfx_vulkan_draw_set_depth_test above.
static void gfx_vulkan_draw_set_viewport(int x, int y, int width, int height) {
    sViewport = (GfxVulkanRect){ x, y, width, height };
    apply_viewport();
}

// See gfx_vulkan_draw_set_depth_test above.
static void gfx_vulkan_draw_set_scissor(int x, int y, int width, int height) {
    sScissor = (GfxVulkanRect){ x, y, width, height };
    apply_scissor();
}

// See gfx_vulkan_draw_set_depth_test above.
static void gfx_vulkan_draw_set_use_alpha(bool use_alpha) {
    sUseAlpha = use_alpha;
    apply_blend_state();
}

//////////////////////////////////////////////////////////////////////////////
// GfxRenderingAPI / GfxWindowBackendAPI glue - ties every section above
// together into the two structs gfx_pc.c and gfx_window_vulkan.c consume.
//////////////////////////////////////////////////////////////////////////////

// Same suitability rules as pick_physical_device() above (device_has_extension
// is shared with it), kept in sync even though this probe isn't invoked from
// Vulkan-enabled builds today.
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
// created. Dormant today (see the top-of-file comment): ENABLE_VULKAN=1
// builds force this backend on unconditionally, since switching Vulkan's
// swapchain/frame-sync state at runtime turned out to be a real hazard, not
// just an unfinished feature - this probe is what a real fallback-on-
// unsupported-hardware design would build on, if that ever gets wired into
// select_graphics_backend() in pc_main.c.
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
        VkPhysicalDevice *devices = malloc(deviceCount * sizeof(VkPhysicalDevice));
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
        // Shader compile failure (see gfx_vulkan_shader_create_and_load above) -
        // degrade to "no textures, no inputs" instead of dereferencing NULL.
        // gfx_opengl.c can't hit this path (it sys_fatal()s on compile failure instead).
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
        log_to_terminal("[vulkan] failed to initialize instance/device\n");
        return;
    }
    // VMA must exist before the first swapchain_create call: the swapchain
    // also allocates a depth image through it.
    if (!gfx_vulkan_memory_init()) {
        log_to_terminal("[vulkan] failed to initialize VMA\n");
        goto fail_memory;
    }
    if (!gfx_vulkan_swapchain_create(window)) {
        log_to_terminal("[vulkan] failed to create swapchain\n");
        goto fail_swapchain;
    }
    if (!gfx_vulkan_frame_init(window)) {
        log_to_terminal("[vulkan] failed to initialize frame resources\n");
        goto fail_frame;
    }
    if (!gfx_vulkan_texture_init()) {
        log_to_terminal("[vulkan] failed to initialize texture subsystem\n");
        goto fail_texture;
    }
    if (!gfx_vulkan_shader_init()) {
        log_to_terminal("[vulkan] failed to initialize glslang\n");
        goto fail_shader;
    }
    if (!gfx_vulkan_pipeline_init()) {
        log_to_terminal("[vulkan] failed to initialize shared pipeline layout/frame UBO\n");
        goto fail_pipeline;
    }
    if (!gfx_vulkan_draw_init()) {
        log_to_terminal("[vulkan] failed to initialize vertex streaming arenas\n");
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
