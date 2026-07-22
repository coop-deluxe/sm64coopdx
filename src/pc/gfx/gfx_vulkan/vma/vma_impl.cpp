// Single translation unit compiling the VMA (Vulkan Memory Allocator)
// implementation. Function loading is delegated to volk (VMA_DYNAMIC_VULKAN_FUNCTIONS,
// seeded with volk's vkGetInstanceProcAddr/vkGetDeviceProcAddr in
// src/pc/gfx/gfx_vulkan_memory.c) so this never links against libvulkan
// directly - same loading style as the rest of the backend
// (special_ai/VULKAN_BACKEND_PLAN.md §2, "Carga de símbolos vía volk").
#include <volk.h>

#define VMA_IMPLEMENTATION
#define VMA_STATIC_VULKAN_FUNCTIONS 0
#define VMA_DYNAMIC_VULKAN_FUNCTIONS 1
#include "vk_mem_alloc.h"
