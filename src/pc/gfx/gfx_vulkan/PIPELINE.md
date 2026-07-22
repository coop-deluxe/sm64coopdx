# The Vulkan Pipeline — Internals

This document explains how a `VkPipeline` gets built for this game
specifically, and what happens every frame to use it. For the broader "how
does Vulkan fit into the engine" picture, see [`VULKAN.md`](VULKAN.md); for
the startup sequence, see [`INIT.md`](INIT.md).

## The core problem: one pipeline per Color Combiner

The N64's RDP has a programmable-ish "Color Combiner" (CC) that blends up to
two texture samples and several other inputs through a small formula
language. sm64coopdx's PC ports don't emulate the CC in a shader interpreter
— each backend *compiles* every distinct CC configuration it encounters into
real shader code, once, and caches the result. `gfx_opengl.c` does this by
generating GLSL text and compiling a `GLuint` program; this backend does the
Vulkan equivalent: generate GLSL text, compile it to SPIR-V, and bake a whole
`VkPipeline` around it.

```
ColorCombiner (hash, shader_commands, flags)
        │
        ▼
gfx_vulkan_shader.c: generate_vertex_shader() / generate_fragment_shader()
        │  (GLSL text, ported formula-for-formula from gfx_opengl.c's generator)
        ▼
gfx_vulkan_shader.c: compile_stage() × 2         (glslang → SPIR-V)
        │
        ▼
gfx_vulkan_pipeline.c: gfx_vulkan_pipeline_create()
        │  (shared layout + this CC's baked vertex input/shader stages)
        ▼
VkPipeline, cached in gfx_vulkan_shader.c's ring buffer (ShaderProgram pool)
```

This whole path runs lazily, the first time a given `ColorCombiner` hash is
seen (`gfx_vulkan_shader_create_and_load`, called from `gfx_pc.c` via
`GfxRenderingAPI::create_and_load_new_shader`). Every later use of the same
CC is a cache hit (`gfx_vulkan_shader_lookup`) — no shader/pipeline work at
all, just picking the cached `struct ShaderProgram*`.

## Shader cache

`sShaderPool[CC_MAX_SHADERS]` (64 slots) is a ring buffer, identical in
spirit to `gfx_opengl.c`'s own `shader_program_pool`. Once full, creating a
new pipeline destroys the oldest one's `VkPipeline` to reuse its slot. This
is safe without a device-idle wait — by the time a slot gets reused, the
game has already flushed anything that used its previous occupant, and the
current frame-in-flight slot's fence/semaphore wait has already happened in
`gfx_vulkan_frame_start()`.

## What's shared vs. what's per-pipeline

Every `VkPipeline` this backend ever creates shares **one**
`VkPipelineLayout` (`gfx_vulkan_pipeline.c`). Only the vertex input layout
and the two shader modules differ between pipelines.

| Shared across all pipelines | Baked per-pipeline (fixed at creation) | Dynamic (set per-frame/per-draw) |
|---|---|---|
| Pipeline layout (2 descriptor sets + push constants) | Vertex input layout (from this CC's attributes) | Viewport / scissor |
| Descriptor set 0 (frame UBO) | Vertex + fragment shader modules | Depth test enable / write enable / bias enable / bias values |
| Descriptor set 1 layout (2 push-descriptor samplers) | Blend *equation* (fixed: `SRC_ALPHA` / `ONE_MINUS_SRC_ALPHA`) | Blend *enable* (`VK_EXT_extended_dynamic_state3`) |
| `VkPipelineCache` (persisted to disk) | Cull mode (always `NONE` — culling happens on the CPU, not the GPU) | |
| | Multisampling (always 1 sample — no MSAA) | |
| | `VkPipelineRenderingCreateInfo` (swapchain color format + depth format) | |

Keeping cull mode, MSAA, and the blend equation fixed avoids a combinatorial
explosion of pipeline variants — the only real per-draw toggle the game
needs is "is alpha blending on for this draw", which is exactly what
`VK_EXT_extended_dynamic_state3`'s `colorBlendEnable` dynamic state buys us
without extra pipeline permutations.

## Descriptor layout

| Set | Binding(s) | Type | Update model |
|---|---|---|---|
| 0 | 0 | `UNIFORM_BUFFER_DYNAMIC` | Bound once per frame with a dynamic offset into a double-buffered UBO (`gfx_vulkan_pipeline_update_frame_ubo`) |
| 1 | 0, 1 | `COMBINED_IMAGE_SAMPLER` × 2 | Pushed per draw call via `vkCmdPushDescriptorSetKHR` (`gfx_vulkan_pipeline_bind_textures`) — no descriptor pool, no allocation, no per-texture descriptor set lifetime to manage |

Push constants (28 bytes, fragment stage only) carry the size and filter
mode of whichever of the two textures the active CC actually samples
(`GfxVulkanDrawPushConstants`), matching the `PushConstants` block the
generated fragment shader declares.

The frame UBO (`GfxVulkanFrameUBO`, 304 bytes after `std140` padding) carries
frame count, lightmap color, and the 8 post-processing `gShaderFlags`/
`gShaderFlagValues` pairs (hue/saturation/brightness/contrast/exposure/
dithering/posterization/scanlines) — one slice per frame-in-flight slot, so
the CPU can start writing next frame's UBO data while the GPU is still
reading the previous one.

## Vertex layout

Unlike GL (which enables/disables vertex attrib arrays per draw), Vulkan
bakes the entire vertex input state into the pipeline. `gfx_vulkan_shader.c`
computes the same incremental attribute layout `gfx_opengl.c` does — position,
up to 2 texcoords, fog, light map, up to 2 CC inputs — and stores it on
`struct ShaderProgram` (`num_floats`, `attrib_sizes[]`). `gfx_vulkan_pipeline_create()`
turns that into a `VkVertexInputBindingDescription` + `VkVertexInputAttributeDescription[]`
pair at pipeline-creation time.

## The render loop

```
gfx_vulkan_renderer_start_frame()          gfx_vulkan.c
  → gfx_vulkan_frame_begin_rendering()     opens the command buffer, transitions
                                            color+depth images, vkCmdBeginRendering
  → gfx_vulkan_draw_begin_frame()          rewinds this frame's vertex arena,
                                            reapplies cached viewport/scissor/
                                            depth/blend state (*)
  → gfx_vulkan_pipeline_update_frame_ubo() writes + binds set 0

... gfx_pc.c calls draw_triangles/set_* any number of times ...

gfx_vulkan_renderer_end_frame()
  → gfx_vulkan_frame_end_and_submit()      vkCmdEndRendering, transitions color
                                            image to PRESENT_SRC, submits

gfx_vulkan_renderer_finish_render()
  → gfx_vulkan_frame_present()             vkQueuePresentKHR
```

(*) Dynamic state doesn't survive across command buffers — a fresh
`vkBeginCommandBuffer` starts with viewport/scissor/depth/blend all
*undefined*. `gfx_pc.c`'s state cache only calls `set_viewport`/etc. again
when the value actually *changes* from the previous frame (correct for
GL/D3D11, where that state lives on a persistent context). `gfx_vulkan_draw.c`
works around this by caching its own copy of the last value passed to each
setter and unconditionally replaying all four once per frame, before any
draw — see the comment above `apply_viewport` in `gfx_vulkan_draw.c` for the
full story, including why this only became visible once the window stopped
being resized every frame.

Each individual `draw_triangles` call (`gfx_vulkan_draw_triangles`) does, in
order: bump-allocate its vertex data into this frame's streaming arena, bind
the CC's pipeline, bind the vertex buffer at the arena offset, push the
texture descriptor set, push the size/filter push constants, and issue one
non-indexed `vkCmdDraw` (`TRIANGLE_LIST`, 3 vertices per triangle — the
engine batches up to `MAX_BUFFERED` (256) triangles per flush and never uses
an index buffer).

## Vertex streaming

One persistently-mapped, host-visible arena per frame-in-flight slot
(`GFX_VULKAN_FRAMES_IN_FLIGHT`, 2 slots), each 16 MiB — comfortably more than
a real scene needs (one full batch is ~80 KiB; the arena covers roughly 200
flushes per frame before `gfx_vulkan_draw_triangles` starts clamping and
warning instead of overrunning). Because `gfx_vulkan_frame_start()` already
waits out a slot's previous submission before reusing it, simply rewinding
the arena's offset to 0 at the start of each frame is enough — no
ring-buffer wraparound bookkeeping is needed within a single frame.

## Depth buffer & dynamic rendering

This backend never creates a `VkRenderPass` or `VkFramebuffer` — it uses core
1.3 dynamic rendering (`vkCmdBeginRendering`/`vkCmdEndRendering`) directly.
The depth image is recreated alongside the swapchain's color images on every
resize (`gfx_vulkan_swapchain.c`), in a spec-guaranteed-supported pure-depth
format (`D32_SFLOAT` or `X8_D24_UNORM_PACK32`), cleared to `1.0` every frame
(matching `z_is_from_0_to_1() == true` and `depthCompareOp = LESS_OR_EQUAL`).

## Gotchas worth knowing before touching this code

- **Vulkan's clip space flips Y relative to GL and D3D11.** Since vertex
  positions are computed on the CPU assuming the GL/D3D convention (there's
  no MVP matrix in the vertex shader — `gl_Position` is a pure passthrough),
  the fix lives entirely in `gfx_vulkan_draw.c::apply_viewport`: a
  **negative viewport height** cancels the flip without touching any
  generated shader.
- **`filter` is a GLSL reserved word under the Vulkan/SPIR-V rules**, even
  though it compiles fine under desktop GL/GLSL ES. The generated fragment
  shader's helper function parameter is named `filterMode` instead (see
  `sampleTex()` in `gfx_vulkan_shader.c`).
- **The GLSL text buffers are fixed-size (16 KiB) with no bounds checking**,
  same risk profile as `gfx_opengl.c`'s own 8 KiB buffers for the same
  generator — not something introduced by this backend, just inherited.
- **Pipeline compilation can stall a frame.** The first time a new CC
  combination is seen, GLSL generation + SPIR-V compilation +
  `vkCreateGraphicsPipelines` all happen synchronously on that frame. The
  on-disk `VkPipelineCache` (persisted in `gfx_vulkan_pipeline_destroy`,
  loaded in `gfx_vulkan_pipeline_init`) makes *repeat* runs cheap once a
  combination has been compiled once on this machine, but a first encounter
  within a single run still pays full price. Timing is logged under
  `VULKAN_DEBUG` but no mitigation (background thread, pre-warming) is
  implemented yet.
