# SSGI/AO Integration Notes for sm64coopdx

These are the bugs, gotchas, and hacks encountered while integrating the AO-only pass into the emscripten/WebGL build. Some of these may be WebGL-specific; others are fundamental to coopdx's rendering architecture. The original shader author should evaluate which apply to the native GL build and which need different solutions.

## 1. The N64 Projection Matrix is Non-Standard

**Problem:** The `rsp.P_matrix` captured from `gfx_sp_matrix()` when `G_MTX_PROJECTION` is set is NOT a standard OpenGL perspective matrix. It's a combined projection + viewport transform:

```
P_row = | 0.00625   0         0       0 |    ← 1/160, viewport X scale
        | 0         0.00833   0       0 |    ← 1/120, viewport Y scale
        | 0         0        -0.1     0 |    ← depth scale
        |-1        -1         0       1 |    ← viewport offset, w=1
```

This means:
- `w_clip = 1` always (no perspective divide through P alone)
- Near/far/FOV cannot be extracted from P — they're baked into the full `MP_matrix` which changes per object
- `P[0][0]` and `P[1][1]` are viewport scales, not projection focal lengths
- Standard inverse-projection reconstruction (`invP * clipPos`) does NOT work

**Current hack:** Hardcoded SM64's known camera defaults:
- near = 100, far = 12800
- FOV = 45 degrees
- `proj_x = cot(fov/2) / aspect`, `proj_y = cot(fov/2)`

**What the original author should evaluate:**
- These values may change per area (some areas use different far planes or FOVs)
- A proper fix would capture the actual `guPerspective()` parameters from the game code, or intercept them at the N64 GBI command level before they get baked into the viewport transform
- On native GL (non-web), the projection matrix layout might differ if the rendering API is different

## 2. Inverse Projection Matrix Approach Failed

**Problem:** We tried multiple approaches to use the inverse projection matrix:
1. Captured `rsp.P_matrix`, inverted it, passed to shader as `uProjMatrixInverse`
2. The `invert_matrix()` function treats flat float[16] as column-major, but coopdx stores matrices as row-major `float[4][4]` — this implicit transpose was confusing
3. Tried both `GL_TRUE` and `GL_FALSE` for the transpose parameter
4. All approaches produced incorrect view-space positions (flat normals, diagonal color bands)

**Root cause:** The P_matrix isn't a perspective projection at all (see #1), so its inverse can't reconstruct view-space positions regardless of transpose.

**Current solution:** Bypassed the matrix entirely. View-space reconstruction uses:
```glsl
float z = -linearizeDepth(depth, near, far);  // standard near/far formula
float x = ndc.x * (-z) / proj_x;              // from FOV + aspect
float y = ndc.y * (-z) / proj_y;
```

## 3. WebGL Shader Version

**Problem:** The original shaders use `#version 120` (desktop GL 2.1). WebGL doesn't support this — it needs:
- WebGL 1: `#version 100` with `precision mediump float;`
- WebGL 2: `#version 300 es` (or `#version 100` for backward compat)

**Current solution:** Conditional define:
```c
#ifdef USE_GLES
#define SHADER_VERSION "#version 100\n" "precision mediump float;\n"
#else
#define SHADER_VERSION "#version 120\n"
#endif
```

WebGL 2 accepts `#version 100` shaders (backward compatible). The shaders use `attribute`/`varying`/`gl_FragColor` which are GLSL ES 1.00 syntax.

**For native GL:** `#version 120` should work fine on desktop GL 2.1+.

## 4. WebGL Depth Texture Format

**Problem:** `GL_DEPTH_COMPONENT24` is invalid in WebGL 1. In WebGL 2, it's valid but requires the correct type.

**Current solution:**
```c
#ifdef USE_GLES
#define GL_DEPTH_COMPONENT24 0x81A6  // may not be in GLES headers
glTexImage2D(..., GL_DEPTH_COMPONENT24, w, h, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);
#else
glTexImage2D(..., GL_DEPTH_COMPONENT24, w, h, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);
#endif
```

Also explicitly enables `WEBGL_depth_texture` extension for WebGL 1 (not needed for WebGL 2, where it's core). Falls back gracefully if neither is available.

## 5. VBO State Corruption

**Problem:** Creating the fullscreen quad VBO during `ssgi_init()` left the game's VBO unbound, causing `bufferData: no buffer` spam on every subsequent draw call.

**Fix:** Save/restore `GL_ARRAY_BUFFER_BINDING` around VBO creation:
```c
GLint prev_vbo;
glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &prev_vbo);
// ... create quad VBO ...
glBindBuffer(GL_ARRAY_BUFFER, prev_vbo);
```

**Note:** All SSGI render functions also save/restore full GL state (FBO, program, VBO, depth test, scissor, blend).

## 6. FBO Binding When SSGI Disabled

**Problem:** When FBO creation failed (e.g., missing depth texture extension), `ssgi_enabled` was set to false, but `ssgi_start_frame()` was still called before the flag was rechecked after resize. This redirected rendering to the broken FBO, causing hundreds of `GL_INVALID_FRAMEBUFFER_OPERATION` errors per frame.

**Fix:** Multiple guard checks in `ssgi_start_frame()`:
```c
if (!ssgi_enabled || !ssgi_initialized || !gSSGI_Enabled) return;
// ... resize may disable ssgi_enabled ...
if (!ssgi_enabled) return;   // check again after resize
if (!ssgi_scene_fbo) return; // check FBO handle is valid
```

## 7. AO "50% Brightness" Baseline

**Problem:** Flat unoccluded surfaces (e.g., a floor with nothing nearby) produced AO = 0.5 instead of 1.0. This is mathematically correct — the ground plane occludes exactly half the hemisphere — but visually it darkens the entire scene uniformly.

**Current hack:** `ao = clamp(ao * 2.0, 0.0, 1.0)` after averaging slices. This remaps the flat-surface baseline (0.5) to 1.0, so only actual corners/crevices (where ao < 0.5) produce visible darkening.

**What the original author should evaluate:**
- The proper GTAO formula uses `0.25 * (-cos(2h-n) + cos(n) + 2h*sin(n))` which may already handle this
- The `ao * 2.0` remap effectively halves the dynamic range — fully occluded corners can only reach 0.0 if the raw AO is 0.0, but values between 0.0 and 0.5 get stretched
- A more principled fix would normalize by the theoretical maximum AO for the current normal angle

## 8. Thickness Check Inversion

**Problem:** The original thickness check was:
```glsl
float tc = clamp(horizonLen / uThickness, 0.0, 1.0);
hc = mix(hc, -1.0, 1.0 - tc);  // ORIGINAL from ssgi_ao_only_120.frag
```
This rejected CLOSE samples (tc small → mix factor large → push to -1.0) and kept FAR samples. The intent was the opposite — reject far samples that are behind thin geometry.

**First attempted fix:** `hc = mix(hc, -1.0, tc)` — this created bright halos around objects with far backgrounds because far samples were actively pushed to -1.0 (no occlusion), artificially brightening edges.

**Current solution:** Skip far samples entirely instead of mixing:
```glsl
if (hl > 0.001 && hl < uThickness) {
    float hc = dot(hd/hl, vd);
    mhc = max(mhc, hc);
}
```
Far samples are simply ignored, leaving `maxHorizonCos` at its initialized -1.0 naturally.

**What the original author should evaluate:**
- The original `1.0 - tc` in `ssgi_ao_only_120.frag` may have been correct in the context of Three.js/WebGL where depth values and view-space scales are different
- The simple skip approach loses the soft falloff that the mix provided
- A better solution might be: `if (hl < uThickness) { ... } else { /* falloff */ }`

## 9. Thickness Scale for N64 Units

**Problem:** The thickness uniform was originally in the range 0.1-2.0 (from the PLAN.md tuning suggestions), but view-space distances in N64 are in the hundreds/thousands of units. A thickness of 2.0 meant `clamp(horizonLen / 2.0, ...)` always saturated to 1.0 — making thickness a no-op.

**Current solution:** DJUI slider range 1-20, multiplied by 50 → 50-1000 world units. This gives meaningful thickness rejection in N64 scale.

**For the original author:** The PLAN.md suggested `uThickness: 0.5 - 2.0`, which is appropriate for normalized/metric-scale scenes but not for N64's large coordinate system.

## 10. Compositing Pipeline

**Current pipeline:**
```
gfx_opengl_start_frame()
  → ssgi_start_frame()           // Binds scene FBO (color + depth textures)
  → glClear(COLOR | DEPTH)

[N64 display list renders into scene FBO]

gfx_end_frame_render()            // Flushes VBO, scene is now in FBO textures

ssgi_render()                     // Reads depth texture → computes AO → writes to AO FBO
  → Binds AO FBO
  → Fullscreen quad with AO shader
  → Reads: ssgi_scene_depth_tex (depth)
  → Writes: ssgi_ao_tex (R channel = AO, 1.0 = no occlusion)

ssgi_composite()                  // Combines scene × AO → default framebuffer
  → Binds framebuffer 0
  → Fullscreen quad with composite shader
  → Reads: ssgi_scene_color_tex (scene), ssgi_ao_tex (AO)
  → Writes: default framebuffer
  → Output: scene.rgb * ao

gfx_display_frame()               // Swap buffers
```

**Important:** The composite currently also renders two debug thumbnails in the top-right corner (normals and AO-only) for tuning. These should be removed or made toggleable for production.

**Correctness concern:** The DJUI overlay (menus, FPS counter, player list, chat) renders as part of the N64 display list, so it goes into the scene FBO and gets AO applied to it. This means UI elements can have ambient occlusion artifacts (darkened corners where UI elements meet the 3D scene). A proper fix would render the 3D scene to FBO, apply AO, then render the DJUI overlay on top — but this requires separating the DJUI render from the display list execution, which is a deeper architectural change.

## 11. Integration Points (Files Modified)

| File | Change |
|------|--------|
| `src/pc/gfx/gfx_ssgi.c` | New file: FBOs, shaders, render passes |
| `src/pc/gfx/gfx_ssgi.h` | New file: public API + tunable globals |
| `src/pc/gfx/gfx_opengl.c` | `ssgi_init()` in init, `ssgi_start_frame()` in start_frame |
| `src/pc/gfx/gfx_pc.c` | Capture P_matrix on `G_MTX_PROJECTION` (currently unused but still there) |
| `src/pc/pc_main.c` | `ssgi_render()` + `ssgi_composite()` at 3 frame submission points |
| `src/pc/djui/djui_panel_display.c` | SSAO checkbox + 3 tuning sliders |

## 12. Tunable Parameters

| Parameter | DJUI Slider Range | Actual Range | Default | Effect |
|-----------|------------------|--------------|---------|--------|
| gSSGI_Enabled | 0-1 (checkbox) | bool | 1 (on) | Master on/off |
| gSSGI_AoIntensity | 1-50 | 0.1-5.0 (÷10) | 15 (1.5) | Power curve exponent. Higher = subtler |
| gSSGI_Radius | 1-50 | 0.1-5.0 (÷10) | 15 (1.5) | Sample search radius in screen-space |
| gSSGI_Thickness | 1-20 | 50-1000 (×50) | 3 (150) | Max distance for valid occluder |

Parameters are `unsigned int` for DJUI slider compatibility, converted to float in the shader uniform setting code.
