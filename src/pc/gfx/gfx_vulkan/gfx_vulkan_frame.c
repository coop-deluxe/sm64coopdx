#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "gfx_vulkan_context.h"
#include "gfx_vulkan_swapchain.h"
#include "gfx_vulkan_frame.h"
#include "gfx_vulkan_debug.h"

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

VkCommandBuffer gfxVkCurrentCommandBuffer = VK_NULL_HANDLE;

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
bool gfx_vulkan_frame_init(struct SDL_Window *window) {
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
void gfx_vulkan_frame_destroy(void) {
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

// Marks the swapchain for rebuild on the next gfx_vulkan_frame_start() call.
void gfx_vulkan_frame_notify_resize(void) {
#ifdef VULKAN_DEBUG
    fprintf(stderr, "[vulkan] notify_resize called\n");
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
        fprintf(stderr, "[vulkan] failed to recreate imageAvailable semaphore after a failed acquire\n");
    }
}

// Begins a new frame: rebuilds the swapchain if it was marked dirty, waits
// for this slot's previous submission to finish, resets its command pool,
// and acquires the next swapchain image.
bool gfx_vulkan_frame_start(void) {
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
            fprintf(stderr, "[vulkan] vkWaitSemaphores failed: %d\n", waitRes);
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
        fprintf(stderr, "[vulkan] vkAcquireNextImageKHR failed: %d\n", res);
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
void gfx_vulkan_frame_begin_rendering(void) {
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
    // z_is_from_0_to_1() is true (gfx_vulkan.c) so 1.0 is "farthest", matching
    // depthCompareOp = LESS_OR_EQUAL (gfx_vulkan_pipeline.c).
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
void gfx_vulkan_frame_end_and_submit(void) {
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
        fprintf(stderr, "[vulkan] vkEndCommandBuffer failed: %d\n", endRes);
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
        fprintf(stderr, "[vulkan] vkQueueSubmit2 failed: %d\n", submitRes);
    }
}

// Presents the acquired image and advances to the next frame-in-flight slot.
bool gfx_vulkan_frame_present(void) {
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
        fprintf(stderr, "[vulkan] vkQueuePresentKHR failed: %d\n", res);
    }
    return res == VK_SUCCESS;
}

// See gfx_vulkan_frame.h.
uint32_t gfx_vulkan_frame_get_current_slot(void) {
    return sCurrentFrame;
}
