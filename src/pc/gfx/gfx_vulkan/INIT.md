# Engine Bring-Up — How Vulkan Loads Inside the Game

This document walks through what actually happens, in order, from process
start to a Vulkan frame appearing on screen — and back down on shutdown. For
the bigger architectural picture see [`VULKAN.md`](VULKAN.md); for what
happens *inside* a frame once things are running, see
[`PIPELINE.md`](PIPELINE.md).

## 1. Build time: is Vulkan even in this binary?

Everything in this backend is gated by the `ENABLE_VULKAN` Make flag
(default `0`). If it's off, none of `gfx_vulkan.c`, `gfx_window_vulkan.c`, or
anything under `gfx_vulkan/` is even compiled — the normal build every player
uses is untouched. Two optional flags layer on top when it's on:

| Flag | Effect |
|---|---|
| `ENABLE_VULKAN=1` | Compiles and links this backend; excludes the OpenGL backend (`gfx_opengl.c`/`gfx_window_opengl.c`) from the build entirely and skips `-lGL` |
| `DEVELOPMENT=1` | Enables the validation-layer debug messenger and GPU debugger labels (see `VULKAN.md`) |
| `VULKAN_DEBUG=1` | Enables extra `stderr` diagnostics (auto-enabled by `DEVELOPMENT=1`, see the Makefile) |

## 2. Backend selection — no fallback, no toggle

`pc_main.c::select_graphics_backend()` normally probes for OpenGL/D3D11
compatibility and lets the user pick a backend in-game. Under
`ENABLE_VULKAN=1`, that whole path is replaced with one unconditional line:

```c
configGraphicsBackend = GFX_WINDOW_BACKEND_VULKAN;
```

**Why exclusive, not a toggle:** early in development, the Display settings
panel listed "OpenGL" and "Vulkan" as interchangeable options in any
`ENABLE_VULKAN=1` build. Switching backends *at runtime* (via that selector)
turned out to be a real hazard for this backend specifically — Vulkan's
swapchain/frame-sync state doesn't tolerate being torn down and rebuilt
across a backend switch the way GL's context-based model does, and it was
the actual root cause of a resize bug that looked unrelated on the surface
(see `PIPELINE.md`'s dynamic-state gotcha for a similarly indirect bug in the
same family). The fix was a product decision, not just a technical one:
`ENABLE_VULKAN=1` builds are Vulkan-only, full stop — the selector is
compiled out (`djui_panel_display.c`), and there's no automatic fallback to
GL if Vulkan turns out to be unsupported on the machine. A lightweight
capability probe (`gfx_vulkan_probe_support()` in `gfx_vulkan.c`) exists and
would support a real fallback-on-unsupported-hardware design, but it isn't
wired into `select_graphics_backend()` today — see `VULKAN.md`'s non-goals.

## 3. Window creation

`gfx_window_vulkan_init()` creates a plain SDL2 window with the
`SDL_WINDOW_VULKAN` flag (no GL context, no attributes) and hands it to the
shared window-manager glue via `gfx_wm_set_window()`. Everything downstream
gets the `SDL_Window*` from there.

## 4. `GfxRenderingAPI::init` — the real bring-up

`gfx_vulkan_renderer_init()` (`gfx_vulkan.c`) brings up every subsystem in
strict dependency order, stopping at the first failure:

```
1. gfx_vulkan_context_init()    VkInstance → VkSurfaceKHR → (debug messenger)
                                  → VkPhysicalDevice → VkDevice → VkQueue
2. gfx_vulkan_memory_init()      VMA allocator (must exist before #3, which
                                  allocates a depth image through it)
3. gfx_vulkan_swapchain_create() VkSwapchainKHR + color image views + depth image
4. gfx_vulkan_frame_init()       timeline semaphore, per-frame-in-flight
                                  command pools/buffers/semaphores
5. gfx_vulkan_texture_init()     transient command pool for texture uploads
6. gfx_vulkan_shader_init()      glslang_initialize_process()
7. gfx_vulkan_pipeline_init()    shared descriptor layouts, pipeline layout,
                                  frame UBO, pipeline cache (loaded from disk)
8. gfx_vulkan_draw_init()        per-frame-in-flight vertex streaming arenas
```

Only after step 8 succeeds does `sInitOk` become `true`. Every other
lifecycle function (`on_resize`, `start_frame`, `end_frame`, `finish_render`,
`shutdown`) checks `sInitOk` first and no-ops if it's `false` — a failed init
degrades to a black, unresponsive Vulkan window instead of crashing on
half-initialized state. This is a direct consequence of
`GfxRenderingAPI::init()` returning `void`: there's no channel back to
`select_graphics_backend()` to request a fallback, so "fail safely and stay
dark" is the best this contract allows today.

**Cleanup on partial failure.** If any step above fails, `gfx_vulkan_renderer_init()`
doesn't just bail out — it unwinds through a chain of `goto fail_*` labels
that call the `destroy_*` function for every subsystem that *did* finish
initializing, in reverse order, before returning. Every `destroy_*` function
in this backend tolerates being called on an already-torn-down or
never-initialized subsystem (each checks its own handles against
`VK_NULL_HANDLE` first) — with one deliberate exception: `gfx_vulkan_shader_destroy()`
calls `glslang_finalize_process()`, which asserts if it's ever called without
a matching `glslang_initialize_process()`. The label chain is ordered so
that call is only reached when step 6 above is known to have succeeded.

## 5. Steady state: one frame

Once `sInitOk` is `true`, the per-frame calls are thin wrappers over
`gfx_vulkan_frame.c`/`gfx_vulkan_draw.c`/`gfx_vulkan_pipeline.c` — see
[`PIPELINE.md`](PIPELINE.md#the-render-loop) for that sequence in detail.

## 6. Resize

`gfx_window_vulkan_handle_events()` catches `SDL_WINDOWEVENT_SIZE_CHANGED`
and calls `on_resize()` → `gfx_vulkan_frame_notify_resize()`, which just sets
a dirty flag. The actual swapchain rebuild happens lazily, at the start of
the *next* `gfx_vulkan_frame_start()` — never on the event thread — because
rebuilding needs a `vkDeviceWaitIdle()`, which would stall event handling.
If the rebuild itself fails (not just the common "window is momentarily
0x0/minimized" case), the dirty flag is re-armed rather than left cleared, so
the next frame retries instead of running with a stale or half-built
swapchain.

## 7. The loading-screen-to-game transition

One easy-to-miss detail: `rendering_init()` (`src/game/game_init.c`, shared
by all three backends) calls `send_display_list()` once, right as the game
finishes its loading screen — which internally acquires a swapchain image
via `gfx_run()` — but historically never closed that frame with a matching
`gfx_end_frame()`. GL/D3D11 don't track acquire/present state, so a "swap"
that never happens is a harmless no-op for them. Vulkan does track it: an
acquired image that's never submitted+presented leaves its frame-in-flight
slot's semaphore signaled with nothing waiting on it, corrupting the *next*
real acquire on that same slot. The fix is a single added call
(`gfx_end_frame();` right after `send_display_list()`), safe for all three
backends since GL/D3D11's `end_frame()` are no-ops.

## 8. `GfxRenderingAPI::shutdown`

`gfx_vulkan_renderer_shutdown()` waits for the device to go idle, then tears
down every subsystem in the exact reverse order of step 4 above: draw →
pipeline → shader → texture → frame → swapchain → memory → context. The
swapchain is destroyed before the VMA allocator specifically because it owns
a VMA-backed depth image.
