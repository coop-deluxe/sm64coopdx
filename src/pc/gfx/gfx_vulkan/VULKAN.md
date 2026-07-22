# Vulkan Backend — Technical Fact Sheet

This document describes how the Vulkan graphics backend fits into sm64coopdx's
existing rendering architecture. It's the "what is this and how does it plug
in" reference; for how the render pipeline itself works see
[`PIPELINE.md`](PIPELINE.md), and for the startup/shutdown sequence see
[`INIT.md`](INIT.md).

## Status

| | |
|---|---|
| Build flag | `ENABLE_VULKAN=1` (default `0`) |
| Stability | Functional, feature-complete relative to the OpenGL backend |
| Platforms tested | Linux (Mesa/ANV, Intel) |
| Vulkan floor | 1.3 |

Vulkan is **opt-in**. A normal `make` build never touches this directory,
never links Vulkan, and never even compiles these files — everything in
`gfx_vulkan/` and `gfx_vulkan.c`/`gfx_vulkan.h`/`gfx_window_vulkan.c`/
`gfx_window_vulkan.h` is wrapped in `#if defined(ENABLE_VULKAN)`.

## How it plugs into the engine

sm64coopdx's PC port separates "what talks to the GPU" from "what talks to
the OS/windowing system" through two small function-pointer contracts:

- **`GfxRenderingAPI`** (`gfx_rendering_api.h`) — shaders, textures, draw
  calls, frame lifecycle. Implemented by `gfx_opengl.c`, `gfx_direct3d11.cpp`,
  `gfx_dummy.c`, and now `gfx_vulkan.c`.
- **`GfxWindowBackendAPI`** (`gfx_window_manager.h`) — window creation, event
  pumping, present/swap. Implemented by `gfx_window_opengl.c`,
  `gfx_window_dxgi.cpp`, `gfx_dummy.c`, and now `gfx_window_vulkan.c`.

Both structs are plain arrays of function pointers assigned once in
`pc_main.c::select_graphics_backend()`. Vulkan slots into the existing
`GFX_WINDOW_BACKEND_VULKAN` enum value (`gfx_window_manager.h`) next to
`GFX_WINDOW_BACKEND_OPENGL`/`_DIRECTX`/`_DUMMY` — no new selection mechanism
was invented.

Under `ENABLE_VULKAN=1`, `select_graphics_backend()` forces
`GFX_WINDOW_BACKEND_VULKAN` unconditionally: there is no OpenGL/D3D11
fallback, and no in-game backend selector (the `GRAPHICS_BACKEND` option in
the Display settings panel is compiled out for these builds, see
`djui_panel_display.c`). This isn't a design limitation so much as a
deliberate simplification during development — see the "Why exclusive, not a
toggle" note in `INIT.md`. As a side effect, `gfx_opengl.c` and
`gfx_window_opengl.c` are excluded from the build entirely and `-lGL` is
never linked (see the Makefile's `ENABLE_VULKAN` branches).

## File map

```
src/pc/gfx/
├── gfx_vulkan.c / gfx_vulkan.h          GfxRenderingAPI implementation, support probe
├── gfx_window_vulkan.c / .h             GfxWindowBackendAPI implementation (SDL2 window)
└── gfx_vulkan/
    ├── gfx_vulkan_context.c / .h        VkInstance, VkSurfaceKHR, VkPhysicalDevice, VkDevice, VkQueue
    ├── gfx_vulkan_swapchain.c / .h      VkSwapchainKHR, color image views, depth image
    ├── gfx_vulkan_frame.c / .h          Frame-in-flight sync, acquire/submit/present loop
    ├── gfx_vulkan_memory.c / .h         VMA wrapper (buffers, images)
    ├── gfx_vulkan_texture.c / .h        Texture cache, samplers, uploads
    ├── gfx_vulkan_shader.c / .h         GLSL generator (per Color Combiner) + SPIR-V compilation
    ├── gfx_vulkan_pipeline.c / .h       Shared pipeline layout, frame UBO, VkPipeline creation
    ├── gfx_vulkan_draw.c / .h           Vertex streaming, dynamic state, draw calls
    ├── gfx_vulkan_debug.c / .h          DEVELOPMENT-only GPU debugger labels
    ├── volk/                            vendored: Vulkan function loader
    ├── vma/                             vendored: VulkanMemoryAllocator
    └── glslang/                         vendored: GLSL → SPIR-V compiler
```

Ownership is layered strictly bottom-up: `gfx_vulkan_context` owns nothing
above it, `gfx_vulkan_swapchain` depends on `context` and `memory`,
`gfx_vulkan_frame` depends on `context` and `swapchain`, and so on up to
`gfx_vulkan.c`, which only orchestrates the other modules and never touches a
`Vk*` handle directly.

## Vendored dependencies

None of these are modified from upstream; they live under `gfx_vulkan/` (not
`lib/`) because nothing outside this backend uses them.

| Library | Role | Why this one |
|---|---|---|
| [volk](https://github.com/zeux/volk) | Loads Vulkan entry points at runtime | No link-time dependency on `libvulkan` — works the same on Linux/Windows/macOS without per-platform loader code |
| [VMA](https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator) | Buffer/image memory allocation | Avoids hand-rolled sub-allocation and `maxMemoryAllocationCount` bookkeeping |
| [glslang](https://github.com/KhronosGroup/glslang) | GLSL → SPIR-V, at runtime | The Color Combiner shader text is only known once a level's materials are seen — needs a runtime compiler, not an offline one. Chosen over shaderc because shaderc is glslang + SPIRV-Tools + a wrapper this backend doesn't need. |

## Required Vulkan version & features

The backend targets a single, non-negotiable floor: **Vulkan 1.3** on both
the instance (`VkApplicationInfo.apiVersion`) and the physical device. Below
that, device selection simply skips the device (see
`gfx_vulkan_context.c::pick_physical_device`).

| Requirement | Why |
|---|---|
| Core 1.3: dynamic rendering | No `VkRenderPass`/`VkFramebuffer` objects anywhere in this backend |
| Core 1.3: `synchronization2` | `vkCmdPipelineBarrier2`/`vkQueueSubmit2` throughout |
| `VkPhysicalDeviceVulkan12Features.timelineSemaphore` | Frame-in-flight throttling (`gfx_vulkan_frame.c`) — opt-in even at 1.3, not folded into the 1.3 feature struct |
| `VK_EXT_extended_dynamic_state3` + `extendedDynamicState3ColorBlendEnable` | The only truly dynamic blend state this backend needs (enable/disable); not promoted to core as of 1.3 |
| `VK_KHR_swapchain` | Presentation |
| `VK_KHR_push_descriptor` | Per-draw texture binding without descriptor pools (see `PIPELINE.md`) |

A lightweight version of this same check runs as `gfx_vulkan_probe_support()`
in `gfx_vulkan.c` — it exists for a design that lets the engine fall back
from Vulkan to OpenGL if the GPU/driver doesn't qualify, but that fallback
path is currently dormant (see the `ENABLE_VULKAN`-forces-Vulkan note above).

## Platform notes

- **Linux**: `-ldl` is linked explicitly for volk's runtime loading (already
  part of libc on Windows/macOS).
- **Windows**: no `_WIN32`-specific Vulkan code is needed beyond what SDL2
  already handles for surface creation.
- **macOS**: requires `VK_KHR_portability_enumeration` +
  `VK_KHR_get_physical_device_properties2` (MoltenVK) and
  `VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR`; the vendored glslang
  needs `-std=c++17 -stdlib=libc++`.

## Explicit non-goals

- **MSAA** — not implemented, matching the existing D3D11 backend's
  precedent of omitting it. Left as a Fase 6 candidate if ever needed.
- **A GL/D3D11 fallback if Vulkan init fails partway** — `GfxRenderingAPI::init()`
  returns `void`, so a failure can't be reported back to
  `select_graphics_backend()`. A failed init degrades to a black,
  unresponsive Vulkan window instead of crashing (see `INIT.md`).
- **Runtime backend switching** — see the "exclusive, not a toggle" note above.

## Debugging

- Build with `DEVELOPMENT=1` to enable the debug messenger
  (`VK_EXT_debug_utils` + `VK_LAYER_KHRONOS_validation`, best-effort: silently
  skipped if the validation layer package isn't installed) and GPU debugger
  labels (`gfx_vulkan_debug.c`) around each render pass and each draw call
  (`"CC 0x<hash>"`), useful for tools like RenderDoc.
- Build with `VULKAN_DEBUG=1` (automatically implied by `DEVELOPMENT=1`, see
  the Makefile) for extra `stderr` logging: swapchain recreation, and
  per-pipeline shader-compile timing broken down into GLSL generation /
  SPIR-V compilation / `vkCreateGraphicsPipelines`.
- Recommended combo for real debugging sessions:
  `make ENABLE_VULKAN=1 DEVELOPMENT=1 -j$(nproc)` with
  `vulkan-validationlayers` installed on the system.
