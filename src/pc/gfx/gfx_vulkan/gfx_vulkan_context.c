#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

#include "macros.h"
#include "gfx_vulkan_context.h"

VkInstance gfxVkInstance = VK_NULL_HANDLE;
VkSurfaceKHR gfxVkSurface = VK_NULL_HANDLE;
VkPhysicalDevice gfxVkPhysicalDevice = VK_NULL_HANDLE;
VkDevice gfxVkDevice = VK_NULL_HANDLE;
VkQueue gfxVkQueue = VK_NULL_HANDLE;
uint32_t gfxVkQueueFamily = UINT32_MAX;

#ifdef DEVELOPMENT
static VkDebugUtilsMessengerEXT sDebugMessenger = VK_NULL_HANDLE;

// Forwards validation layer warnings/errors to stderr, prefixed "[vulkan]".
static VKAPI_ATTR VkBool32 VKAPI_CALL gfx_vulkan_debug_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT severity,
    UNUSED VkDebugUtilsMessageTypeFlagsEXT type,
    const VkDebugUtilsMessengerCallbackDataEXT *data,
    UNUSED void *userData) {
    if (severity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
        fprintf(stderr, "[vulkan] %s\n", data->pMessage);
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

// Checks whether `device` reports `extensionName` as a supported device extension.
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
        // bit. gfx_vulkan_frame.c relies on it for the frame timeline
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
bool gfx_vulkan_context_init(struct SDL_Window *window) {
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
void gfx_vulkan_context_destroy(void) {
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
