#if defined(ENABLE_VULKAN)

#include <stdio.h>
#include <string.h>

#include "gfx_vulkan_context.h"
#include "gfx_vulkan_swapchain.h"
#include "gfx_vulkan_frame.h"
#include "gfx_vulkan_memory.h"
#include "gfx_vulkan_pipeline.h"
#include "gfx_vulkan_shader.h"
#include "gfx_vulkan_texture.h"
#include "gfx_vulkan_debug.h"
#include "gfx_vulkan_draw.h"

#include <volk.h>

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
bool gfx_vulkan_draw_init(void) {
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
void gfx_vulkan_draw_destroy(void) {
    for (int i = 0; i < GFX_VULKAN_FRAMES_IN_FLIGHT; i++) {
        gfx_vulkan_memory_destroy_buffer(&sArenas[i].buffer);
        sArenas[i].mapped = NULL;
        sArenas[i].offset = 0;
    }
    sOverflowWarned = false;
}

// Rewinds this frame's vertex arena and reapplies all cached dynamic state.
void gfx_vulkan_draw_begin_frame(void) {
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
// draw.
void gfx_vulkan_draw_triangles(const struct ShaderProgram *prg, float buf_vbo[], size_t buf_vbo_len, size_t buf_vbo_num_tris) {
    if (!prg || prg->pipeline == VK_NULL_HANDLE) {
        return;
    }

    GfxVulkanVertexArena *arena = &sArenas[gfx_vulkan_frame_get_current_slot()];
    VkDeviceSize byteSize = (VkDeviceSize)buf_vbo_len * sizeof(float);
    if (arena->offset + byteSize > GFX_VULKAN_ARENA_SIZE) {
        if (!sOverflowWarned) {
            fprintf(stderr, "[vulkan] vertex arena exhausted this frame, dropping draw (increase GFX_VULKAN_ARENA_SIZE)\n");
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
void gfx_vulkan_draw_set_depth_test(bool depth_test) {
    sDepthTest = depth_test;
    apply_depth_state();
}

// See gfx_vulkan_draw_set_depth_test above.
void gfx_vulkan_draw_set_depth_mask(bool z_upd) {
    sDepthMask = z_upd;
    apply_depth_state();
}

// See gfx_vulkan_draw_set_depth_test above.
void gfx_vulkan_draw_set_zmode_decal(bool zmode_decal) {
    sZmodeDecal = zmode_decal;
    apply_depth_state();
}

// See gfx_vulkan_draw_set_depth_test above.
void gfx_vulkan_draw_set_viewport(int x, int y, int width, int height) {
    sViewport = (GfxVulkanRect){ x, y, width, height };
    apply_viewport();
}

// See gfx_vulkan_draw_set_depth_test above.
void gfx_vulkan_draw_set_scissor(int x, int y, int width, int height) {
    sScissor = (GfxVulkanRect){ x, y, width, height };
    apply_scissor();
}

// See gfx_vulkan_draw_set_depth_test above.
void gfx_vulkan_draw_set_use_alpha(bool use_alpha) {
    sUseAlpha = use_alpha;
    apply_blend_state();
}

#endif // ENABLE_VULKAN
