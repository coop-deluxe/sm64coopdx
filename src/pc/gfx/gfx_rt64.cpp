#ifdef RAPI_RT64

#if defined(_WIN32) || defined(_WIN64)

#if !defined(EXTERNAL_DATA) && !defined(DYNOS)
#error "RT64 requires EXTERNAL_DATA to be enabled."
#endif

extern "C" {
#	include "../configfile.h"
#	include "../../game/area.h"
#	include "../../game/level_update.h"
#	include "../fs/fs.h"
#	include "../pc_main.h"
#	include "../../goddard/gd_math.h"
#	include "gfx_cc.h"
}

#include <cassert>
#include <stdint.h>

#include <stb/stb_image.h>
#include "xxhash/xxhash64.h"

#include "gfx_rt64.h"
#include "gfx_rt64_context.h"
#include "gfx_rt64_serialization.h"
#include "gfx_rt64_geo_map.h"

const unsigned short MouseButtonFlags[MAX_MOUSE_BUTTONS][2] = {
	{ RI_MOUSE_BUTTON_1_DOWN, RI_MOUSE_BUTTON_1_UP },
	{ RI_MOUSE_BUTTON_2_DOWN, RI_MOUSE_BUTTON_2_UP },
	{ RI_MOUSE_BUTTON_3_DOWN, RI_MOUSE_BUTTON_3_UP },
	{ RI_MOUSE_BUTTON_4_DOWN, RI_MOUSE_BUTTON_4_UP },
	{ RI_MOUSE_BUTTON_5_DOWN, RI_MOUSE_BUTTON_5_UP },
};

void gfx_rt64_render_thread();

uint16_t shaderVariantKey(bool raytrace, int filter, int hAddr, int vAddr, bool normalMap, bool specularMap) {
	uint16_t key = 0, fact = 1;
	key += raytrace ? fact : 0; fact *= 2;
	key += filter * fact; fact *= 2;
	key += hAddr * fact; fact *= 3;
	key += vAddr * fact; fact *= 3;
	key += normalMap ? fact : 0; fact *= 2;
	key += specularMap ? fact : 0; fact *= 2;
	return key;
}

inline RT64_VECTOR3 transform_position_affine(RT64_MATRIX4 m, RT64_VECTOR3 v) {
	RT64_VECTOR3 o;
	o.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + m.m[3][0];
	o.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + m.m[3][1];
	o.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + m.m[3][2];
	return o;
}

inline RT64_VECTOR3 transform_direction_affine(RT64_MATRIX4 m, RT64_VECTOR3 v) {
	RT64_VECTOR3 o;
	o.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0];
	o.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1];
	o.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2];
	return o;
}

inline float vector_length(RT64_VECTOR3 v) {
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline RT64_VECTOR3 normalize_vector(RT64_VECTOR3 v) {
	float length = vector_length(v);
	if (length > 0.0f) {
		return { v.x / length, v.y / length, v.z / length };
	}
	else {
		return { 0.0f, 0.0f, 0.0f };
	}
}

inline float vector_dot_product(RT64_VECTOR3 a, RT64_VECTOR3 b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

static void gfx_matrix_mul(float res[4][4], const float a[4][4], const float b[4][4]) {
    float tmp[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            tmp[i][j] = a[i][0] * b[0][j] +
                        a[i][1] * b[1][j] +
                        a[i][2] * b[2][j] +
                        a[i][3] * b[3][j];
        }
    }
    memcpy(res, tmp, sizeof(tmp));
}

static inline LARGE_INTEGER gfx_rt64_profile_marker() {
	LARGE_INTEGER marker;
	QueryPerformanceCounter(&marker);
	return marker;
}

static inline LARGE_INTEGER gfx_rt64_profile_delta(LARGE_INTEGER start, LARGE_INTEGER end) {
	LARGE_INTEGER Delta;
	Delta.QuadPart = end.QuadPart - start.QuadPart;
	Delta.QuadPart *= 1000000;
	Delta.QuadPart /= RT64.Frequency.QuadPart;
	return Delta;
}

static void gfx_rt64_rapi_unload_shader(struct ShaderProgram *old_prg) {
	
}

static void gfx_rt64_rapi_load_shader(struct ShaderProgram *new_prg) {
	RT64.shaderProgram = new_prg;
}

static struct ShaderProgram *gfx_rt64_rapi_create_and_load_new_shader(uint32_t shader_id) {
	ShaderProgram *shaderProgram = new ShaderProgram();
    int c[2][4];
    for (int i = 0; i < 4; i++) {
        c[0][i] = (shader_id >> (i * 3)) & 7;
        c[1][i] = (shader_id >> (12 + i * 3)) & 7;
    }

	shaderProgram->shaderId = shader_id;
    shaderProgram->usedTextures[0] = false;
    shaderProgram->usedTextures[1] = false;
    shaderProgram->numInputs = 0;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            if (c[i][j] >= SHADER_INPUT_1 && c[i][j] <= SHADER_INPUT_4) {
                if (c[i][j] > shaderProgram->numInputs) {
                    shaderProgram->numInputs = c[i][j];
                }
            }
            if (c[i][j] == SHADER_TEXEL0 || c[i][j] == SHADER_TEXEL0A) {
                shaderProgram->usedTextures[0] = true;
            }
            if (c[i][j] == SHADER_TEXEL1) {
                shaderProgram->usedTextures[1] = true;
            }
        }
    }

	{
		const std::lock_guard<std::mutex> lock(RT64.shaderProgramsMutex);
		RT64.shaderPrograms[shader_id] = shaderProgram;
	}

	gfx_rt64_rapi_load_shader(shaderProgram);

	return shaderProgram;
}

static struct ShaderProgram *gfx_rt64_rapi_lookup_shader(uint32_t shader_id) {
	const std::lock_guard<std::mutex> lock(RT64.shaderProgramsMutex);
	auto it = RT64.shaderPrograms.find(shader_id);
    return (it != RT64.shaderPrograms.end()) ? it->second : nullptr;
}

static void gfx_rt64_rapi_shader_get_info(struct ShaderProgram *prg, uint8_t *num_inputs, bool used_textures[2]) {
    *num_inputs = prg->numInputs;
    used_textures[0] = prg->usedTextures[0];
    used_textures[1] = prg->usedTextures[1];
}

RT64_SHADER *gfx_rt64_render_thread_load_shader_variant(ShaderProgram *shaderProgram, bool raytrace, int filter, int hAddr, int vAddr, bool normalMap, bool specularMap) {
	uint16_t variantKey = shaderVariantKey(raytrace, filter, hAddr, vAddr, normalMap, specularMap);
	if (shaderProgram->shaderVariantMap[variantKey] == nullptr) {
		int flags = raytrace ? RT64_SHADER_RAYTRACE_ENABLED : RT64_SHADER_RASTER_ENABLED;
		if (normalMap) {
			flags |= RT64_SHADER_NORMAL_MAP_ENABLED;
		}

		if (specularMap) {
			flags |= RT64_SHADER_SPECULAR_MAP_ENABLED;
		}

		shaderProgram->shaderVariantMap[variantKey] = RT64.lib.CreateShader(RT64.device, shaderProgram->shaderId, filter, hAddr, vAddr, flags);

		// Print shader discovery to reduce stutters when playing through the game.
		printf("gfx_rt64_render_thread_preload_shader(0x%X, %d, %d, %d, %d, %s, %s);\n", shaderProgram->shaderId, raytrace, filter, hAddr, vAddr, normalMap ? "true" : "false", specularMap ? "true" : "false");
	}

	return shaderProgram->shaderVariantMap[variantKey];
}

void gfx_rt64_render_thread_preload_shader(unsigned int shader_id, bool raytrace, int filter, int hAddr, int vAddr, bool normalMap, bool specularMap) {
	ShaderProgram *shaderProgram = gfx_rt64_rapi_lookup_shader(shader_id);
	if (shaderProgram == nullptr) {
		shaderProgram = gfx_rt64_rapi_create_and_load_new_shader(shader_id);
	}

	gfx_rt64_render_thread_load_shader_variant(shaderProgram, raytrace, filter, hAddr, vAddr, normalMap, specularMap);
};

void gfx_rt64_render_thread_preload_shaders() {
	gfx_rt64_render_thread_preload_shader(0x45, 1, 1, 0, 0, true, false);
	gfx_rt64_render_thread_preload_shader(0x45, 1, 1, 2, 2, true, false);
	gfx_rt64_render_thread_preload_shader(0x45, 1, 1, 0, 0, false, false);
	gfx_rt64_render_thread_preload_shader(0x45, 1, 1, 2, 2, false, false);
	gfx_rt64_render_thread_preload_shader(0x45, 1, 1, 0, 2, false, false);
	gfx_rt64_render_thread_preload_shader(0x45, 1, 1, 2, 0, false, false);
	gfx_rt64_render_thread_preload_shader(0x200, 0, 0, 0, 0, false, false);
	gfx_rt64_render_thread_preload_shader(0x200, 1, 0, 0, 0, false, false);
	gfx_rt64_render_thread_preload_shader(0x38D, 1, 1, 2, 2, false, false);
	gfx_rt64_render_thread_preload_shader(0x38D, 1, 1, 0, 0, false, false);
	gfx_rt64_render_thread_preload_shader(0x551, 1, 1, 0, 0, false, false);
	gfx_rt64_render_thread_preload_shader(0xA00, 0, 1, 2, 2, false, false);
	gfx_rt64_render_thread_preload_shader(0xA00, 1, 1, 0, 0, false, false);
	gfx_rt64_render_thread_preload_shader(0xA00, 1, 1, 2, 2, false, false);
	gfx_rt64_render_thread_preload_shader(0xA00, 1, 1, 0, 0, true, false);
	gfx_rt64_render_thread_preload_shader(0x1045045, 1, 1, 2, 2, true, false);
	gfx_rt64_render_thread_preload_shader(0x1045045, 1, 1, 2, 2, false, false);
	gfx_rt64_render_thread_preload_shader(0x1045045, 1, 1, 1, 1, false, false);
	gfx_rt64_render_thread_preload_shader(0x1045045, 1, 1, 2, 0, false, false);
	gfx_rt64_render_thread_preload_shader(0x1045045, 1, 1, 0, 0, false, false);
	gfx_rt64_render_thread_preload_shader(0x1045045, 0, 0, 2, 2, false, false);
	gfx_rt64_render_thread_preload_shader(0x1045045, 0, 0, 0, 0, false, false);
	gfx_rt64_render_thread_preload_shader(0x1045045, 1, 1, 0, 0, true, false);
	gfx_rt64_render_thread_preload_shader(0x1045045, 1, 1, 0, 2, false, false);
	gfx_rt64_render_thread_preload_shader(0x1045A00, 0, 1, 0, 0, false, false);
	gfx_rt64_render_thread_preload_shader(0x1045A00, 1, 1, 2, 2, false, false);
	gfx_rt64_render_thread_preload_shader(0x1081081, 0, 0, 0, 0, false, false);
	gfx_rt64_render_thread_preload_shader(0x1200045, 1, 1, 2, 2, false, false);
	gfx_rt64_render_thread_preload_shader(0x1200045, 0, 1, 2, 2, false, false);
	gfx_rt64_render_thread_preload_shader(0x1200200, 0, 0, 0, 0, false, false);
	gfx_rt64_render_thread_preload_shader(0x1200200, 1, 0, 0, 0, false, false);
	gfx_rt64_render_thread_preload_shader(0x1200A00, 1, 1, 2, 2, false, false);
	gfx_rt64_render_thread_preload_shader(0x1200A00, 0, 1, 2, 2, false, false);
	gfx_rt64_render_thread_preload_shader(0x1200A00, 1, 1, 0, 0, true, false);
	gfx_rt64_render_thread_preload_shader(0x120038D, 1, 1, 2, 2, false, false);
	gfx_rt64_render_thread_preload_shader(0x1200A00, 1, 1, 0, 0, false, false);
	gfx_rt64_render_thread_preload_shader(0x1A00045, 0, 1, 1, 1, false, false);
	gfx_rt64_render_thread_preload_shader(0x1A00045, 0, 1, 2, 2, false, false);
	gfx_rt64_render_thread_preload_shader(0x1A00A00, 0, 0, 2, 2, false, false);
	gfx_rt64_render_thread_preload_shader(0x1A00A6F, 1, 1, 2, 2, false, false);
	gfx_rt64_render_thread_preload_shader(0x3200045, 1, 1, 0, 2, false, false);
	gfx_rt64_render_thread_preload_shader(0x3200045, 1, 1, 2, 2, false, false);
	gfx_rt64_render_thread_preload_shader(0x3200045, 1, 1, 0, 0, false, false);
	gfx_rt64_render_thread_preload_shader(0x3200045, 1, 1, 2, 0, false, false);
	gfx_rt64_render_thread_preload_shader(0x3200200, 1, 0, 0, 0, false, false);
	gfx_rt64_render_thread_preload_shader(0x3200A00, 1, 1, 2, 2, false, false);
	gfx_rt64_render_thread_preload_shader(0x3200A00, 1, 1, 0, 0, true, false);
	gfx_rt64_render_thread_preload_shader(0x5045045, 1, 1, 0, 0, false, false);
	gfx_rt64_render_thread_preload_shader(0x5045045, 1, 1, 0, 2, false, false);
	gfx_rt64_render_thread_preload_shader(0x5045045, 1, 1, 2, 2, false, false);
	gfx_rt64_render_thread_preload_shader(0x5045045, 1, 1, 1, 1, false, false);
	gfx_rt64_render_thread_preload_shader(0x5045045, 0, 1, 2, 2, false, false);
	gfx_rt64_render_thread_preload_shader(0x5045045, 1, 1, 2, 2, true, false);
	gfx_rt64_render_thread_preload_shader(0x5045045, 1, 1, 0, 0, true, false);
	gfx_rt64_render_thread_preload_shader(0x5200200, 1, 0, 0, 0, false, false);
	gfx_rt64_render_thread_preload_shader(0x5200045, 1, 1, 0, 0, false, false);
	gfx_rt64_render_thread_preload_shader(0x5200A00, 1, 1, 0, 0, true, false);
	gfx_rt64_render_thread_preload_shader(0x5200A00, 1, 1, 0, 0, false, false);
	gfx_rt64_render_thread_preload_shader(0x5A00A00, 1, 1, 2, 0, false, false);
	gfx_rt64_render_thread_preload_shader(0x5A00A00, 0, 1, 0, 0, false, false);
	gfx_rt64_render_thread_preload_shader(0x5A00A00, 1, 1, 2, 2, false, false);
	gfx_rt64_render_thread_preload_shader(0x5A00A00, 1, 1, 0, 0, false, false);
	gfx_rt64_render_thread_preload_shader(0x5A00A00, 0, 0, 2, 2, false, false);
	gfx_rt64_render_thread_preload_shader(0x5A00A00, 1, 1, 0, 2, false, false);
	gfx_rt64_render_thread_preload_shader(0x7A00A00, 1, 1, 0, 0, false, false);
	gfx_rt64_render_thread_preload_shader(0x7A00A00, 1, 1, 0, 2, false, false);
	gfx_rt64_render_thread_preload_shader(0x7A00A00, 1, 1, 2, 2, false, false);
	gfx_rt64_render_thread_preload_shader(0x1200045, 1, 1, 0, 0, false, false);
	gfx_rt64_render_thread_preload_shader(0x1141045, 1, 1, 2, 2, false, false);
	gfx_rt64_render_thread_preload_shader(0x1200045, 1, 1, 0, 2, false, false);
	gfx_rt64_render_thread_preload_shader(0x3200A00, 1, 1, 0, 0, false, false);
	gfx_rt64_render_thread_preload_shader(0x9200200, 1, 0, 0, 0, false, false);
	gfx_rt64_render_thread_preload_shader(0x920038D, 1, 1, 2, 2, false, false);
	gfx_rt64_render_thread_preload_shader(0x9200A00, 1, 1, 0, 0, false, false);
	gfx_rt64_render_thread_preload_shader(0x9200045, 1, 1, 0, 0, false, false);
}

int gfx_rt64_get_level_index() {
    return (gPlayerSpawnInfos[0].areaIndex >= 0) ? gCurrLevelNum : 0;
}

int gfx_rt64_get_area_index() {
    return (gPlayerSpawnInfos[0].areaIndex >= 0) ? gCurrAreaIndex : 0;
}

void gfx_rt64_toggle_inspector() {
	RT64.renderInspectorActive = !RT64.renderInspectorActive;
}

static void onkeydown(WPARAM w_param, LPARAM l_param) {
    int key = ((l_param >> 16) & 0x1ff);
    if (RT64.on_key_down != nullptr) {
        RT64.on_key_down(key);
    }
}

static void onkeyup(WPARAM w_param, LPARAM l_param) {
    int key = ((l_param >> 16) & 0x1ff);
    if (RT64.on_key_up != nullptr) {
        RT64.on_key_up(key);
    }
}

// Adapted from gfx_dxgi.cpp
static void gfx_rt64_toggle_full_screen(bool enable) {
    // Windows 7 + flip mode + waitable object can't go to exclusive fullscreen,
    // so do borderless instead. If DWM is enabled, this means we get one monitor
    // sync interval of latency extra. On Win 10 however (maybe Win 8 too), due to
    // "fullscreen optimizations" the latency is eliminated.
    if (enable == RT64.isFullScreen) {
        return;
    }

    if (!enable) {
        RECT r = RT64.lastWindowRect;

        // Set in window mode with the last saved position and size
        SetWindowLongPtr(RT64.hwnd, GWL_STYLE, WS_VISIBLE | WS_OVERLAPPEDWINDOW);

        if (RT64.lastMaximizedState) {
            SetWindowPos(RT64.hwnd, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);
            ShowWindow(RT64.hwnd, SW_MAXIMIZE);
        } else {
            SetWindowPos(RT64.hwnd, NULL, r.left, r.top, r.right - r.left, r.bottom - r.top, SWP_FRAMECHANGED);
            ShowWindow(RT64.hwnd, SW_RESTORE);
        }
    } else {
        // Save if window is maximized or not
        WINDOWPLACEMENT windowPlacement;
        windowPlacement.length = sizeof(WINDOWPLACEMENT);
        GetWindowPlacement(RT64.hwnd, &windowPlacement);
        RT64.lastMaximizedState = windowPlacement.showCmd == SW_SHOWMAXIMIZED;

        // Save window position and size if the window is not maximized
        GetWindowRect(RT64.hwnd, &RT64.lastWindowRect);
        configWindow.x = RT64.lastWindowRect.left;
        configWindow.y = RT64.lastWindowRect.top;
        configWindow.w = RT64.lastWindowRect.right - RT64.lastWindowRect.left;
        configWindow.h = RT64.lastWindowRect.bottom - RT64.lastWindowRect.top;

        // Get in which monitor the window is
        HMONITOR hmonitor = MonitorFromWindow(RT64.hwnd, MONITOR_DEFAULTTONEAREST);

        // Get info from that monitor
        MONITORINFOEX monitorInfo;
        monitorInfo.cbSize = sizeof(MONITORINFOEX);
        GetMonitorInfo(hmonitor, &monitorInfo);
        RECT r = monitorInfo.rcMonitor;

        // Set borderless full screen to that monitor
        SetWindowLongPtr(RT64.hwnd, GWL_STYLE, WS_VISIBLE | WS_POPUP);
        SetWindowPos(RT64.hwnd, HWND_TOP, r.left, r.top, r.right - r.left, r.bottom - r.top, SWP_FRAMECHANGED);
    }

    RT64.isFullScreen = enable;
}

void gfx_rt64_apply_config() {
	{
    	const std::lock_guard<std::mutex> lock(RT64.renderViewDescMutex);
		RT64.renderViewDesc.resolutionScale = configRT64ResScale / 100.0f;
		RT64.renderViewDesc.maxLights = configRT64MaxLights;
		RT64.renderViewDesc.diSamples = configRT64SphereLights ? 1 : 0;
		RT64.renderViewDesc.giSamples = configRT64GI ? 1 : 0;
		RT64.renderViewDesc.denoiserEnabled = configRT64Denoiser;
		RT64.renderViewDesc.motionBlurStrength = configRT64MotionBlurStrength / 100.0f;
		RT64.renderViewDesc.upscaler = configRT64Upscaler;
		RT64.renderViewDesc.upscalerMode = configRT64UpscalerMode;
		RT64.renderViewDesc.upscalerSharpness = configRT64UpscalerSharpness / 100.0f;
		RT64.useVsync = configWindow.vsync;
		RT64.targetFPS = configRT64TargetFPS;
		RT64.renderViewDescChanged = true;
	}

	// Adapted from gfx_dxgi.cpp
	if (configWindow.fullscreen != RT64.isFullScreen) {
        gfx_rt64_toggle_full_screen(configWindow.fullscreen);
	}

	if (!RT64.isFullScreen) {
		const int screenWidth = GetSystemMetrics(SM_CXSCREEN);
        const int screenHeight = GetSystemMetrics(SM_CYSCREEN);
        const int xpos = (configWindow.x == WAPI_WIN_CENTERPOS) ? (screenWidth - configWindow.w) * 0.5 : configWindow.x;
        const int ypos = (configWindow.y == WAPI_WIN_CENTERPOS) ? (screenHeight - configWindow.h) * 0.5 : configWindow.y;
        RECT wr = { xpos, ypos, xpos + (int)configWindow.w, ypos + (int)configWindow.h };
        AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
        SetWindowPos(RT64.hwnd, NULL, wr.left, wr.top, wr.right - wr.left, wr.bottom - wr.top, SWP_NOACTIVATE | SWP_NOZORDER);
	}
}

static bool gfx_rt64_use_vsync() {
	return RT64.useVsync && !RT64.turboMode;
}

LRESULT CALLBACK gfx_rt64_wnd_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	if (RT64.renderInspectorActive && (RT64.renderInspector != nullptr) && RT64.lib.HandleMessageInspector(RT64.renderInspector, message, wParam, lParam)) {
		return true;
	}

	switch (message) {
	case WM_SYSKEYDOWN:
		// Alt + Enter.
		if ((wParam == VK_RETURN) && ((lParam & 1 << 30) == 0)) {
			gfx_rt64_toggle_full_screen(!RT64.isFullScreen);
			break;
		} else {
			return DefWindowProcW(hWnd, message, wParam, lParam);
		}
	case WM_CLOSE:
		PostQuitMessage(0);
		game_exit();
		break;
	case WM_ACTIVATEAPP:
		RT64.windowActive = (wParam == TRUE);

        if (RT64.on_all_keys_up != nullptr) {
        	RT64.on_all_keys_up();
		}

        break;
	case WM_RBUTTONDOWN:
		if (RT64.renderInspectorActive) {
			const std::lock_guard<std::mutex> pickLock(RT64.pickTextureMutex);
			RT64.pickTextureHash = 0;
			RT64.pickTexture = true;
			RT64.pickTextureHighlight = true;
		}

		break;
	case WM_RBUTTONUP:
		if (RT64.renderInspectorActive) {
			const std::lock_guard<std::mutex> pickLock(RT64.pickTextureMutex);
			RT64.pickTextureHighlight = false;
		}

		break;
	case WM_KEYDOWN:
		if (wParam == VK_F1) {
			gfx_rt64_toggle_inspector();
		}

		if (wParam == VK_F2) {
			RT64.pauseMode = !RT64.pauseMode;
		}

		if (wParam == VK_F4) {
			RT64.turboMode = !RT64.turboMode;
		}
		
		if (RT64.renderInspectorActive) {
			if (wParam == VK_F5) {
				const std::lock_guard<std::mutex> lightingLock(RT64.levelAreaLightingMutex);
				const std::lock_guard<std::mutex> texModsLock(RT64.texModsMutex);
				gfx_rt64_save_geo_layout_mods();
				gfx_rt64_save_texture_mods();
				gfx_rt64_save_level_lights();
			}
		}

		onkeydown(wParam, lParam);
		break;
	case WM_KEYUP:
		onkeyup(wParam, lParam);
		break;
	case WM_INPUT: {
		// Skip mouselook events if inspector is active.
		if (RT64.renderInspectorActive) {
			break;
		}
		
		UINT dwSize = sizeof(RAWINPUT);
		static BYTE lpb[sizeof(RAWINPUT)];
		GetRawInputData((HRAWINPUT)(lParam), RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));
		RAWINPUT* raw = (RAWINPUT*)(lpb);
		if (raw->header.dwType == RIM_TYPEMOUSE) {
			RT64.deltaMouseX += raw->data.mouse.lLastX;
			RT64.deltaMouseY += raw->data.mouse.lLastY;

			// Detect mouse button states if any of them were enabled.
			if (raw->data.mouse.usButtonFlags & 0x3FF) {
				for (unsigned short b = 0; b < MAX_MOUSE_BUTTONS; b++) {
					if (raw->data.mouse.usButtonFlags & MouseButtonFlags[b][0]) {
						RT64.mouseButtons |= (1 << b);
					}
					else if (raw->data.mouse.usButtonFlags & MouseButtonFlags[b][1]) {
						RT64.mouseButtons &= ~(1 << b);
					}
				}
			}
    	}

		break;
	}
	case WM_PAINT: {
		LARGE_INTEGER ElapsedMicroseconds;

		// Apply configuration changes.
		if (configWindow.settings_changed) {
			gfx_rt64_apply_config();
			configWindow.settings_changed = false;
		}

		if (!RT64.pauseMode && (RT64.run_one_game_iter != nullptr)) {
			// Run one game iteration.
			LARGE_INTEGER GameStartTime, GameEndTime;
			GameStartTime = gfx_rt64_profile_marker();
			RT64.run_one_game_iter();
			GameEndTime = gfx_rt64_profile_marker();
			ElapsedMicroseconds = gfx_rt64_profile_delta(GameStartTime, GameEndTime);

			// Print the time it took to process the frame.
			if (RT64.renderInspectorActive) {
				const std::lock_guard<std::mutex> lock(RT64.renderInspectorMutex);
				char gameDeltaTimeMsg[64];
				sprintf(gameDeltaTimeMsg, "GAME: %.3f ms\n", ElapsedMicroseconds.QuadPart / 1000.0);
				RT64.renderInspectorMessages.clear();
				RT64.renderInspectorMessages.push_back(std::string(gameDeltaTimeMsg));

				char marioMessage[256] = "";
				char levelMessage[256] = "";
				int levelIndex = gfx_rt64_get_level_index();
				int areaIndex = gfx_rt64_get_area_index();
				sprintf(marioMessage, "Mario pos: %.1f %.1f %.1f", gMarioState->pos[0], gMarioState->pos[1], gMarioState->pos[2]);
				sprintf(levelMessage, "Level #%d Area #%d", levelIndex, areaIndex);
				RT64.renderInspectorMessages.push_back(std::string(marioMessage));
				RT64.renderInspectorMessages.push_back(std::string(levelMessage));
				RT64.renderInspectorMessages.push_back(std::string("F1: Toggle inspectors"));
				RT64.renderInspectorMessages.push_back(std::string("F5: Save all configuration"));
			}
		}

		if (!RT64.turboMode) {
			// Try to maintain the fixed framerate.
			const int FixedFramerate = 30;
			const int FramerateMicroseconds = 1000000 / FixedFramerate;
			int cyclesWaited = 0;

			// Sleep if possible to avoid busy waiting too much.
			RT64.EndingTime = gfx_rt64_profile_marker();
			ElapsedMicroseconds = gfx_rt64_profile_delta(RT64.StartingTime, RT64.EndingTime);
			int SleepMs = ((FramerateMicroseconds - ElapsedMicroseconds.QuadPart) - 500) / 1000;
			if (SleepMs > 0) {
				Sleep(SleepMs);
				cyclesWaited++;
			}

			// Busy wait to reach the desired framerate.
			do {
				RT64.EndingTime = gfx_rt64_profile_marker();
				ElapsedMicroseconds = gfx_rt64_profile_delta(RT64.StartingTime, RT64.EndingTime);
				cyclesWaited++;
			} while (ElapsedMicroseconds.QuadPart < FramerateMicroseconds);

			RT64.StartingTime = RT64.EndingTime;

			// Drop the next frame if we didn't wait any cycles.
			RT64.dropNextFrame = (cyclesWaited == 1);
		}

		return 0;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

static void gfx_rt64_error_message(const char *window_title, const char *error_message) {
	MessageBox(NULL, error_message, window_title, MB_OK | MB_ICONEXCLAMATION);
}

static void gfx_rt64_wapi_init(const char *window_title) {
	// Setup library.
	RT64.lib = RT64_LoadLibrary();
	if (RT64.lib.handle == 0) {
		gfx_rt64_error_message(window_title, "Failed to load library. Please make sure rt64lib.dll and dxil.dll are placed next to the game's executable and are up to date.");
		abort();
	}

	// Register window class.
	WNDCLASS wc;
	memset(&wc, 0, sizeof(WNDCLASS));
	wc.lpfnWndProc = gfx_rt64_wnd_proc;
	wc.hInstance = GetModuleHandle(0);
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
	wc.lpszClassName = "RT64";
	RegisterClass(&wc);

	// Create window.
	const int Width = 1280;
	const int Height = 720;
	RECT rect;
	UINT dwStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	rect.left = (GetSystemMetrics(SM_CXSCREEN) - Width) / 2;
	rect.top = (GetSystemMetrics(SM_CYSCREEN) - Height) / 2;
	rect.right = rect.left + Width;
	rect.bottom = rect.top + Height;
	AdjustWindowRectEx(&rect, dwStyle, 0, 0);
	RT64.hwnd = CreateWindow(wc.lpszClassName, window_title, dwStyle, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, wc.hInstance, NULL);

	// Start timers.
	QueryPerformanceFrequency(&RT64.Frequency);
	RT64.StartingTime = gfx_rt64_profile_marker();
	RT64.dropNextFrame = false;
	RT64.turboMode = false;
	
	// Start the game paused. Let the render thread unpause it once it's ready.
	RT64.pauseMode = true;

	// Load the default global lights and the ones from a file afterwards.
	gfx_rt64_default_level_lights();
	gfx_rt64_load_level_lights();
	
	// Load the texture mods from a file.
	gfx_rt64_load_texture_mods();

	// Initialize other attributes.
	RT64.scissorRect = { 0, 0, 0, 0 };
	RT64.viewportRect = { 0, 0, 0, 0 };
	RT64.fogColor.x = 0.0f;
	RT64.fogColor.y = 0.0f;
	RT64.fogColor.z = 0.0f;
	RT64.skyDiffuseMultiplier = { 1.0f, 1.0f, 1.0f };
	RT64.fogMul = RT64.fogOffset = 0;
	RT64.skyTextureId = 0;
	RT64.dlssSupport = false;
	RT64.fsrSupport = false;
	RT64.xessSupport = false;

	// Initialize the triangle list index array used by all meshes.
	unsigned int index = 0;
	while (index < GFX_MAX_BUFFERED) {
		RT64.indexTriangleList[index] = index;
		index++;
	}

	// Build identity matrix.
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			RT64.identityTransform.m[i][j] = (i == j) ? 1.0f : 0.0f;
		}
	}

	// Build a default material.
	RT64.defaultMaterial.ignoreNormalFactor = 0.0f;
    RT64.defaultMaterial.uvDetailScale = 1.0f;
	RT64.defaultMaterial.reflectionFactor = 0.0f;
	RT64.defaultMaterial.reflectionFresnelFactor = 1.0f;
    RT64.defaultMaterial.reflectionShineFactor = 0.0f;
	RT64.defaultMaterial.refractionFactor = 0.0f;
	RT64.defaultMaterial.specularColor = { 1.0f, 1.0f, 1.0f };
	RT64.defaultMaterial.specularExponent = 5.0f;
	RT64.defaultMaterial.solidAlphaMultiplier = 1.0f;
	RT64.defaultMaterial.shadowAlphaMultiplier = 1.0f;
	RT64.defaultMaterial.diffuseColorMix.x = 0.0f;
    RT64.defaultMaterial.diffuseColorMix.y = 0.0f;
    RT64.defaultMaterial.diffuseColorMix.z = 0.0f;
    RT64.defaultMaterial.diffuseColorMix.w = 0.0f;
	RT64.defaultMaterial.depthBias = 0.0f;
	RT64.defaultMaterial.shadowRayBias = 0.0f;
	RT64.defaultMaterial.selfLight.x = 0.0f;
    RT64.defaultMaterial.selfLight.y = 0.0f;
    RT64.defaultMaterial.selfLight.z = 0.0f;
	RT64.defaultMaterial.lightGroupMaskBits = RT64_LIGHT_GROUP_MASK_ALL;
	RT64.defaultMaterial.fogColor.x = 1.0f;
    RT64.defaultMaterial.fogColor.y = 1.0f;
    RT64.defaultMaterial.fogColor.z = 1.0f;
	RT64.defaultMaterial.fogMul = 0.0f;
	RT64.defaultMaterial.fogOffset = 0.0f;
	RT64.defaultMaterial.fogEnabled = false;
	RT64.defaultMaterial.lockMask = 0.0f;

	// Initialize camera.
	GameFrame *CPUFrame = &RT64.frames[RT64.CPUFrameIndex];
	CPUFrame->viewMatrix = RT64.identityTransform;
    CPUFrame->nearDist = 1.0f;
    CPUFrame->farDist = 1000.0f;
    CPUFrame->fovRadians = 0.75f;
	
	// Apply loaded configuration.
	gfx_rt64_apply_config();

	// Setup device.
	RT64.device = RT64.lib.CreateDevice(RT64.hwnd);
	if (RT64.device == nullptr) {
		gfx_rt64_error_message(window_title, RT64.lib.GetLastError());
		gfx_rt64_error_message(window_title, 
			"Failed to initialize RT64.\n\n"
			"Please make sure your GPU drivers are up to date and the Direct3D 12.1 feature level is supported.\n\n"
			"Windows 10 version 2004 or newer is also required for this feature level to work properly.\n\n"
			"If you're a mobile user, make sure that the high performance device is selected for this application on your system's settings.");
		
		abort();
	}

	// Create the render thread.
	RT64.renderThreadRunning = true;
	RT64.renderInspectorActive = false;
	RT64.renderThread = new std::thread(gfx_rt64_render_thread);
}

static void gfx_rt64_wapi_shutdown(void) {
	RT64.renderThreadRunning = false;
	RT64.renderThread->join();
	delete RT64.renderThread;
}

static void gfx_rt64_wapi_set_keyboard_callbacks(bool (*on_key_down)(int scancode), bool (*on_key_up)(int scancode), void (*on_all_keys_up)(void)) {
	RT64.on_key_down = on_key_down;
    RT64.on_key_up = on_key_up;
    RT64.on_all_keys_up = on_all_keys_up;
}

static void gfx_rt64_wapi_main_loop(void (*run_one_game_iter)(void)) {
	RT64.run_one_game_iter = run_one_game_iter;

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

static void gfx_rt64_wapi_get_dimensions(uint32_t *width, uint32_t *height) {
	RECT rect;
	GetClientRect(RT64.hwnd, &rect);
	*width = rect.right - rect.left;
	*height = rect.bottom - rect.top;
}

static void gfx_rt64_wapi_handle_events(void) {
}

static bool gfx_rt64_wapi_start_frame(void) {
	if (RT64.dropNextFrame) {
		RT64.dropNextFrame = false;
		return false;
	}
	else {
		return true;
	}
}

static void gfx_rt64_wapi_swap_buffers_begin(void) {
}

static void gfx_rt64_wapi_swap_buffers_end(void) {
}

double gfx_rt64_wapi_get_time(void) {
    return 0.0;
}

static bool gfx_rt64_rapi_z_is_from_0_to_1(void) {
    return true;
}

static uint32_t gfx_rt64_rapi_new_texture(const char *name) {
	// We reserve 0 for unassigned textures.
	uint32_t textureKey = 1 + RT64.textures.size();
	auto &recordedTexture = RT64.textures[textureKey];
	recordedTexture.linearFilter = 0;
	recordedTexture.cms = 0;
	recordedTexture.cmt = 0;
	recordedTexture.hash = gfx_rt64_get_texture_name_hash(name);
	RT64.textureHashIdMap[recordedTexture.hash] = textureKey;
    return textureKey;
}

static void gfx_rt64_rapi_select_texture(int tile, uint32_t texture_id) {
	assert(tile < 2);
	RT64.currentTile = tile;
    RT64.currentTextureIds[tile] = texture_id;
}

static void gfx_rt64_rapi_upload_texture(const uint8_t *rgba32_buf, int width, int height) {
	uint32_t textureKey = RT64.currentTextureIds[RT64.currentTile];
	UploadTexture uploadTexture;
	uploadTexture.hash = RT64.textures[textureKey].hash;
	uploadTexture.key = textureKey;
	
	RT64_TEXTURE_DESC &texDesc = uploadTexture.desc;
	texDesc.width = width;
	texDesc.height = height;
	texDesc.rowPitch = texDesc.width * 4;
	texDesc.format = RT64_TEXTURE_FORMAT_RGBA8;
	texDesc.byteCount = texDesc.height * texDesc.rowPitch;
	texDesc.bytes = malloc(texDesc.byteCount);
	memcpy(texDesc.bytes, rgba32_buf, texDesc.byteCount);

	RT64.textureUploadQueueMutex.lock();
	RT64.textureUploadQueue.push(uploadTexture);
	RT64.textureUploadQueueMutex.unlock();
}

static void gfx_rt64_rapi_upload_texture_file(const char *file_path, const uint8_t *file_buf, uint64_t file_buf_size) {
	uint32_t textureKey = RT64.currentTextureIds[RT64.currentTile];
	UploadTexture uploadTexture;
	uploadTexture.hash = RT64.textures[textureKey].hash;
	uploadTexture.key = textureKey;

	RT64_TEXTURE_DESC &texDesc = uploadTexture.desc;

	// Use special case for loading DDS directly.
	if (strstr(file_path, ".dds") || strstr(file_path, ".DDS")) {
		texDesc.byteCount = (int)(file_buf_size);
		texDesc.bytes = malloc(texDesc.byteCount);
		memcpy(texDesc.bytes, file_buf, texDesc.byteCount);
		texDesc.width =  texDesc.height = texDesc.rowPitch = -1;
		texDesc.format = RT64_TEXTURE_FORMAT_DDS;

		RT64.textureUploadQueueMutex.lock();
		RT64.textureUploadQueue.push(uploadTexture);
		RT64.textureUploadQueueMutex.unlock();
	}
	// Use stb image to load the file from memory instead if possible.
	else {
		int width, height;
		stbi_uc *data = stbi_load_from_memory(file_buf, file_buf_size, &width, &height, NULL, 4);
        if (data != nullptr) {
			texDesc.bytes = data;
			texDesc.width = width;
			texDesc.height = height;
			texDesc.rowPitch = texDesc.width * 4;
			texDesc.byteCount = texDesc.height * texDesc.rowPitch;
			texDesc.format = RT64_TEXTURE_FORMAT_RGBA8;
			
            RT64.textureUploadQueueMutex.lock();
			RT64.textureUploadQueue.push(uploadTexture);
			RT64.textureUploadQueueMutex.unlock();
		}
		else {
			fprintf(stderr, "stb_image was unable to load the texture file.\n");
		}
	}
}

static void gfx_rt64_rapi_set_sampler_parameters(int tile, bool linear_filter, uint32_t cms, uint32_t cmt) {
	uint32_t textureKey = RT64.currentTextureIds[tile];
	auto &recordedTexture = RT64.textures[textureKey];
	recordedTexture.linearFilter = linear_filter;
	recordedTexture.cms = cms;
	recordedTexture.cmt = cmt;
}

static void gfx_rt64_rapi_set_depth_test(bool depth_test) {
}

static void gfx_rt64_rapi_set_depth_mask(bool depth_mask) {
}

static void gfx_rt64_rapi_set_zmode_decal(bool zmode_decal) {
}

static void gfx_rt64_rapi_set_viewport(int x, int y, int width, int height) {
	RT64.viewportRect = { x, y, width, height };
}

static void gfx_rt64_rapi_set_scissor(int x, int y, int width, int height) {
	RT64.scissorRect = { x, y, width, height };
}

static void gfx_rt64_rapi_set_use_alpha(bool use_alpha) {
}

static inline float gfx_rt64_norm_texcoord(float s, uint8_t address_mode) {
	return s - long(s);
}

static void gfx_rt64_rapi_process_mesh(float buf_vbo[], size_t buf_vbo_len, size_t buf_vbo_num_tris, bool raytrace, GameDisplayList &displayList) {
	// Calculate the required size for each vertex based on the shader.
	const bool useTexture = RT64.shaderProgram->usedTextures[0] || RT64.shaderProgram->usedTextures[1];
	const int numInputs = RT64.shaderProgram->numInputs;
	const bool useAlpha = RT64.shaderProgram->shaderId & SHADER_OPT_ALPHA;
	unsigned int vertexCount = 0;
	unsigned int vertexStride = 0;
	unsigned int indexCount = buf_vbo_num_tris * 3;
	void *vertexBuffer = buf_vbo;
	const unsigned int vertexFixedStride = 16 + 12;
	vertexStride = vertexFixedStride + (useTexture ? 8 : 0) + numInputs * (useAlpha ? 16 : 12);
	assert(((buf_vbo_len * 4) % vertexStride) == 0);

	vertexCount = (buf_vbo_len * 4) / vertexStride;
	assert(buf_vbo_num_tris == (vertexCount / 3));

	// Calculate hash and use it as key.
    XXHash64 hashStream(0);
	size_t vertexBufferSize = buf_vbo_len * sizeof(float);
	hashStream.add(buf_vbo, vertexBufferSize);
    uint64_t hash = hashStream.hash();

	// Make the vector large enough to fit the required meshes.
	if (displayList.meshes.size() < (displayList.drawCount + 1)) {
		displayList.meshes.resize(displayList.drawCount + 1);
	}

	// Try reusing the mesh that was stored in this index first.
	auto &dynMesh = displayList.meshes[displayList.drawCount];
	if (hash != dynMesh.vertexBufferHash) {
		// Free the previous vertex buffer if it's too small to fit the new vertex buffer.
		if ((dynMesh.vertexBuffer != nullptr) && ((dynMesh.vertexCount * dynMesh.vertexStride) < (vertexCount * vertexStride))) {
			free(dynMesh.vertexBuffer);
			dynMesh.vertexBuffer = nullptr;
		}

		// Only create the vertex buffer if it hasn't been assigned yet.
		if (dynMesh.vertexBuffer == nullptr) {
			dynMesh.vertexBuffer = (float *)(malloc(vertexBufferSize));
		}

		memcpy(dynMesh.vertexBuffer, vertexBuffer, vertexBufferSize);
		dynMesh.vertexCount = vertexCount;
		dynMesh.vertexStride = vertexStride;
		dynMesh.indexCount = indexCount;
		dynMesh.useTexture = useTexture;
		dynMesh.raytrace = raytrace;
		dynMesh.vertexBufferHash = hash;
	}
}

static void gfx_rt64_rapi_apply_mod(RT64_MATERIAL *material, uint32_t *normal, uint32_t *specular, bool *interpolate, RecordedMod *mod, RT64_MATRIX4 transform) {
	if (!mod->interpolationEnabled) {
		*interpolate = false;
	}
	
	if (mod->materialMod != NULL) {
		RT64_ApplyMaterialAttributes(material, mod->materialMod);
	}

	if (mod->normalMapHash != 0) {
		auto hashIt = RT64.textureHashIdMap.find(mod->normalMapHash);
		if (hashIt != RT64.textureHashIdMap.end()) {
			if (RT64.textures.find(hashIt->second) != RT64.textures.end()) {
				*normal = hashIt->second;
			}
		}
	}

	if (mod->specularMapHash != 0) {
		auto hashIt = RT64.textureHashIdMap.find(mod->specularMapHash);
		if (hashIt != RT64.textureHashIdMap.end()) {
			if (RT64.textures.find(hashIt->second) != RT64.textures.end()) {
				*specular = hashIt->second;
			}
		}
	}
}

static void gfx_rt64_rapi_draw_triangles_common(RT64_MATRIX4 transform, float buf_vbo[], size_t buf_vbo_len, size_t buf_vbo_num_tris, bool double_sided, bool raytrace, uint32_t uid) {
	assert(RT64.shaderProgram != nullptr);

	// Retrieve the previous transform for the display list with this UID and store the current one.
	GameFrame *CPUFrame = &RT64.frames[RT64.CPUFrameIndex];
	auto &displayList = CPUFrame->displayLists[uid];
	RecordedMod *textureMod = nullptr;
	bool linearFilter = false;
	bool interpolate = (uid != 0);
	uint32_t cms = 0, cmt = 0;

	// Make the vector large enough to fit the required instances.
	if (displayList.instances.size() < (displayList.drawCount + 1)) {
		displayList.instances.resize(displayList.drawCount + 1);
	}

	auto &displayListInstance = displayList.instances[displayList.drawCount];
	displayListInstance.light.groupBits = 0;
	
	RT64_INSTANCE_DESC &instDesc = displayListInstance.desc;
	instDesc.scissorRect = RT64.scissorRect;
	instDesc.viewportRect = RT64.viewportRect;
	instDesc.transform = transform;
	instDesc.material = RT64.defaultMaterial;

	// Find all parameters associated to the texture if it's used.
	bool highlightMaterial = false;
	if (RT64.shaderProgram->usedTextures[0]) {
		uint32_t diffuseKey = RT64.currentTextureIds[RT64.currentTile];
		RecordedTexture &recordedTexture = RT64.textures[diffuseKey];
		linearFilter = recordedTexture.linearFilter; 
		cms = recordedTexture.cms; 
		cmt = recordedTexture.cmt;
		displayListInstance.textures.diffuse = diffuseKey;

		// Use the hash from the texture alias if it exists.
		uint64_t textureHash = recordedTexture.hash;
		auto texAliasIt = RT64.texHashAliasMap.find(textureHash);
		if (texAliasIt != RT64.texHashAliasMap.end()) {
			textureHash = texAliasIt->second;
		}

		// Only use mutex access if the inspector is active.
		bool threadSafeAccess = RT64.renderInspectorActive;
		if (threadSafeAccess) {
			RT64.texModsMutex.lock();
			RT64.pickTextureMutex.lock();
		}

		// Use the texture mod for the matching texture hash.
		auto texModIt = RT64.texMods.find(textureHash);
		if (texModIt != RT64.texMods.end()) {
			textureMod = texModIt->second;
		}

		if (threadSafeAccess) {
			// Update data for ray picking.
			if (RT64.pickTextureHighlight && (textureHash == RT64.pickTextureHash)) {
				highlightMaterial = true;
			}

			RT64.texModsMutex.unlock();
			RT64.pickTextureMutex.unlock();
		}
	}

	// Build material with applied mods.
	if (RT64.graphNodeMod != nullptr) {
		gfx_rt64_rapi_apply_mod(
			&instDesc.material,
			&displayListInstance.textures.normal,
			&displayListInstance.textures.specular,
			&interpolate,
			RT64.graphNodeMod,
			transform);
	}

	if (textureMod != nullptr) {
		gfx_rt64_rapi_apply_mod(
			&instDesc.material,
			&displayListInstance.textures.normal,
			&displayListInstance.textures.specular,
			&interpolate,
			textureMod,
			transform);
		
		if (textureMod->lightMod != nullptr) {
			displayListInstance.light = *textureMod->lightMod;
		}
	}

	// Apply a higlight color if the material is selected.
	if (highlightMaterial) {
		instDesc.material.diffuseColorMix = { 1.0f, 0.0f, 1.0f, 0.5f };
		instDesc.material.selfLight = { 1.0f, 1.0f, 1.0f };
		instDesc.material.lightGroupMaskBits = 0;
	}

	// Copy the fog to the material.
	instDesc.material.fogColor = RT64.fogColor;
	instDesc.material.fogMul = RT64.fogMul;
	instDesc.material.fogOffset = RT64.fogOffset;
	instDesc.material.fogEnabled = (RT64.shaderProgram->shaderId & SHADER_OPT_FOG) != 0;

	// HACK: Add a depth bias based on how many instances have been drawn so far to push
	// coplanar stuff above other meshes on the anyhit sorting.
	instDesc.material.depthBias += RT64.instancesDrawn * 0.001f;

	unsigned int filter = linearFilter ? RT64_SHADER_FILTER_LINEAR : RT64_SHADER_FILTER_POINT;
	unsigned int hAddr = (cms & G_TX_CLAMP) ? RT64_SHADER_ADDRESSING_CLAMP : (cms & G_TX_MIRROR) ? RT64_SHADER_ADDRESSING_MIRROR : RT64_SHADER_ADDRESSING_WRAP;
	unsigned int vAddr = (cmt & G_TX_CLAMP) ? RT64_SHADER_ADDRESSING_CLAMP : (cmt & G_TX_MIRROR) ? RT64_SHADER_ADDRESSING_MIRROR : RT64_SHADER_ADDRESSING_WRAP;
	bool normalMap = (displayListInstance.textures.normal > 0);
	bool specularMap = (displayListInstance.textures.specular > 0);
	displayListInstance.shader.program = RT64.shaderProgram;
	displayListInstance.shader.raytrace = raytrace;
	displayListInstance.shader.filter = filter;
	displayListInstance.shader.hAddr = hAddr;
	displayListInstance.shader.vAddr = vAddr;
	displayListInstance.shader.normalMap = normalMap;
	displayListInstance.shader.specularMap = specularMap;
	displayListInstance.interpolate = interpolate;

	// Mark the right instance flags.
	instDesc.flags = 0;
	if (RT64.background) {
		instDesc.flags |= RT64_INSTANCE_RASTER_BACKGROUND;
	}

	if (double_sided) {
		instDesc.flags |= RT64_INSTANCE_DISABLE_BACKFACE_CULLING;
	}

	gfx_rt64_rapi_process_mesh(buf_vbo, buf_vbo_len, buf_vbo_num_tris, raytrace, displayList);
	
	// Increase the counters.
	displayList.drawCount++;
	RT64.instancesDrawn++;
}

void gfx_rt64_rapi_set_fog(uint8_t fog_r, uint8_t fog_g, uint8_t fog_b, int16_t fog_mul, int16_t fog_offset) {
	RT64.fogColor.x = fog_r / 255.0f;
	RT64.fogColor.y = fog_g / 255.0f;
	RT64.fogColor.z = fog_b / 255.0f;
	RT64.fogMul = fog_mul;
	RT64.fogOffset = fog_offset;
}

static void gfx_rt64_rapi_draw_triangles_ortho(float buf_vbo[], size_t buf_vbo_len, size_t buf_vbo_num_tris, bool double_sided, uint32_t uid) {
	gfx_rt64_rapi_draw_triangles_common(RT64.identityTransform, buf_vbo, buf_vbo_len, buf_vbo_num_tris, double_sided, false, uid);
}

static void gfx_rt64_rapi_draw_triangles_persp(float buf_vbo[], size_t buf_vbo_len, size_t buf_vbo_num_tris, float transform_affine[4][4], bool double_sided, uint32_t uid) {
	// Stop considering the orthographic projection triangles as background as soon as perspective triangles are drawn.
	if (RT64.background) {
		RT64.background = false;
	}

	RT64_MATRIX4 transform;
	memcpy(transform.m, transform_affine, sizeof(float) * 16);
	gfx_rt64_rapi_draw_triangles_common(transform, buf_vbo, buf_vbo_len, buf_vbo_num_tris, double_sided, true, uid);
}

static void gfx_rt64_rapi_init(void) {
}

static void gfx_rt64_rapi_on_resize(void) {
	if (!RT64.isFullScreen) {
		uint32_t w = 0, h = 0;
		gfx_rt64_wapi_get_dimensions(&w, &h);
		configWindow.w = w;
		configWindow.h = h;
	}
}

static void gfx_rt64_rapi_shutdown(void) {
}

static void gfx_rt64_rapi_start_frame(void) {
	GameFrame *CPUFrame = &RT64.frames[RT64.CPUFrameIndex];

	// Reset frame view interpolation.
	CPUFrame->interpolateView = true;

	// Determine cursor visibility base on the current camera mouselook support and the inspector.
	bool newCursorVisible = (!RT64.isFullScreen && !RT64.mouselookEnabled) || (RT64.renderInspectorActive);
	if (RT64.cursorVisible != newCursorVisible) {
		ShowCursor(newCursorVisible);
		RT64.cursorVisible = newCursorVisible;
	}
	
	RT64.instancesDrawn = 0;
	RT64.background = true;
    RT64.graphNodeMod = nullptr;
}

static inline int gfx_rt64_lerp_int(int a, int b, float t) {
	return a + lround(t * (b - a));
}

static inline float gfx_rt64_lerp_float(float a, float b, float t) {
	return a + t * (b - a);
}

static inline RT64_VECTOR3 gfx_rt64_lerp_vector3(RT64_VECTOR3 a, RT64_VECTOR3 b, float t) {
	return {
		gfx_rt64_lerp_float(a.x, b.x, t),
		gfx_rt64_lerp_float(a.y, b.y, t),
		gfx_rt64_lerp_float(a.z, b.z, t)
	};
}

static inline RT64_RECT gfx_rt64_lerp_rect(RT64_RECT a, RT64_RECT b, float t) {
	return {
		gfx_rt64_lerp_int(a.x, b.x, t),
		gfx_rt64_lerp_int(a.y, b.y, t),
		gfx_rt64_lerp_int(a.w, b.w, t),
		gfx_rt64_lerp_int(a.h, b.h, t)
	};
}

static inline RT64_MATRIX4 gfx_rt64_lerp_matrix(const RT64_MATRIX4 &a, const RT64_MATRIX4 &b, float t) {
	// TODO: This is just a hacky way to see some interpolated values, but it is NOT the proper way
	// to interpolate a transformation matrix. That will likely require decomposition of both the matrices.
	RT64_MATRIX4 c;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			c.m[i][j] = gfx_rt64_lerp_float(a.m[i][j], b.m[i][j], t);
		}
	}
	return c;
}

static inline bool gfx_rt64_skip_matrix_lerp(const RT64_MATRIX4 &a, const RT64_MATRIX4 &b, const float minDot) {
	RT64_VECTOR3 prevX, prevY, prevZ;
	RT64_VECTOR3 newX, newY, newZ;
	float dotX, dotY, dotZ;
	prevX = normalize_vector(transform_direction_affine(a, { 1.0f, 0.0f, 0.0f } ));
	prevY = normalize_vector(transform_direction_affine(a, { 0.0f, 1.0f, 0.0f } ));
	prevZ = normalize_vector(transform_direction_affine(a, { 0.0f, 0.0f, 1.0f } ));
	newX = normalize_vector(transform_direction_affine(b, { 1.0f, 0.0f, 0.0f } ));
	newY = normalize_vector(transform_direction_affine(b, { 0.0f, 1.0f, 0.0f } ));
	newZ = normalize_vector(transform_direction_affine(b, { 0.0f, 0.0f, 1.0f } ));
	dotX = vector_dot_product(prevX, newX);
	dotY = vector_dot_product(prevY, newY);
	dotZ = vector_dot_product(prevZ, newZ);
	return (dotX < minDot) || (dotY < minDot) || (dotZ < minDot);
}

static void gfx_rt64_rapi_set_special_stage_lights(int levelIndex, int areaIndex) {
	GameFrame *CPUFrame = &RT64.frames[RT64.CPUFrameIndex];

	// Dynamic Lakitu camera light for Shifting Sand Land Pyramid.
	if ((levelIndex == 8) && (areaIndex == 2)) {
		auto &dl = CPUFrame->displayLists[0];
		RT64_VECTOR3 viewPos = { CPUFrame->invViewMatrix.m[3][0], CPUFrame->invViewMatrix.m[3][1], CPUFrame->invViewMatrix.m[3][2] };
		RT64_VECTOR3 marioPos = { gMarioState->pos[0], gMarioState->pos[1], gMarioState->pos[2] };

		// Set the transform towards the back of the camera facing away from Mario.
		dl.transform = RT64.identityTransform;
		dl.transform.m[3][0] = viewPos.x + (viewPos.x - marioPos.x);
		dl.transform.m[3][1] = viewPos.y + 150.0f;
		dl.transform.m[3][2] = viewPos.z + (viewPos.z - marioPos.z);
		
		// Configure the rest of the light.
		auto &light = dl.light;
		light.position.x = 0.0f;
		light.position.y = 0.0f;
		light.position.z = 0.0f;
		light.diffuseColor.x = 1.0f;
		light.diffuseColor.y = 0.9f;
		light.diffuseColor.z = 0.5f;
		light.attenuationRadius = 4000.0f;
		light.attenuationExponent = 1.0f;
		light.pointRadius = 25.0f;
		light.specularColor = { 0.65f, 0.585f, 0.325f };
		light.shadowOffset = 1000.0f;
		light.groupBits = RT64_LIGHT_GROUP_DEFAULT;
	}
}

static void gfx_rt64_rapi_end_frame(void) {
	GameFrame *CPUFrame = &RT64.frames[RT64.CPUFrameIndex];

	// Add the special stage lights.
	int levelIndex = gfx_rt64_get_level_index();
	int areaIndex = gfx_rt64_get_area_index();
	gfx_rt64_rapi_set_special_stage_lights(levelIndex, areaIndex);

	{
		const std::lock_guard<std::mutex> lightingLock(RT64.levelAreaLightingMutex);
		
		// Update the scene's description.
		const auto &areaLighting = RT64.levelAreaLighting[levelIndex][areaIndex];
		CPUFrame->sceneDesc = areaLighting.sceneDesc;
		CPUFrame->sceneDesc.skyDiffuseMultiplier.x *= RT64.skyDiffuseMultiplier.x;
		CPUFrame->sceneDesc.skyDiffuseMultiplier.y *= RT64.skyDiffuseMultiplier.y;
		CPUFrame->sceneDesc.skyDiffuseMultiplier.z *= RT64.skyDiffuseMultiplier.z;
		CPUFrame->skyTextureId = RT64.skyTextureId;

		// Assign the area's lights to this frame.
		CPUFrame->areaLights = areaLighting.lights;
		CPUFrame->areaLightCount = areaLighting.lightCount;
	}

	// Clean up any unused instances or meshes from the display lists.
	auto dlIt = CPUFrame->displayLists.begin();
	while (dlIt != CPUFrame->displayLists.end()) {
		auto &dl = dlIt->second;
		
		// Destroy all unused instances.
		while (dl.instances.size() > dl.drawCount) {
			auto &dynInst = dl.instances.back();
			dl.instances.pop_back();
		}

		// Destroy all unused meshes.
		while (dl.meshes.size() > dl.drawCount) {
			auto &dynMesh = dl.meshes.back();
			free(dynMesh.vertexBuffer);
			dl.meshes.pop_back();
		}

		// Keep the display list if it's not empty. Erase it otherwise.
		if (!dl.instances.empty() || !dl.meshes.empty() || (dl.light.groupBits > 0)) {
			dlIt++;
		}
		else {
			dlIt = CPUFrame->displayLists.erase(dlIt);
		}
	}

	// Submit the current CPU frame as the next frame to draw and start writing on the next CPU frame.
	bool waitForBarrier = false;
	{
		const std::lock_guard<std::mutex> lock(RT64.renderFrameIndexMutex);
		RT64.GPUFrameIndex = RT64.CPUFrameIndex;
		RT64.CPUFrameIndex = (RT64.CPUFrameIndex + 1) % MAX_RENDER_FRAMES;
		waitForBarrier = (RT64.CPUFrameIndex == RT64.BarrierFrameIndex);
	}

	// Stall the thread until the barrier is lifted if we're trying to write on a frame being used by the GPU.
	while (waitForBarrier) {
		const std::lock_guard<std::mutex> lock(RT64.renderFrameIndexMutex);
		waitForBarrier = (RT64.CPUFrameIndex == RT64.BarrierFrameIndex);
	}

	// Reset display lists for the next CPU frame.
	CPUFrame = &RT64.frames[RT64.CPUFrameIndex];
	dlIt = CPUFrame->displayLists.begin();
	while (dlIt != CPUFrame->displayLists.end()) {
		auto &dl = dlIt->second;
		dl.light.groupBits = 0;
		dl.drawCount = 0;
		dlIt++;
	}

	// Clear variables for next frame.
	RT64.skyTextureId = 0;
}

static void gfx_rt64_rapi_finish_render(void) {

}

static void gfx_rt64_rapi_set_camera_perspective(float fov_degrees, float near_dist, float far_dist, bool can_interpolate) {
	GameFrame *CPUFrame = &RT64.frames[RT64.CPUFrameIndex];
    CPUFrame->fovRadians = (fov_degrees / 180.0f) * M_PI;
	CPUFrame->nearDist = near_dist;
    CPUFrame->farDist = far_dist;
	CPUFrame->interpolateView = CPUFrame->interpolateView && can_interpolate;
}

static void gfx_rt64_rapi_set_camera_matrix(float matrix[4][4]) {
	GameFrame *CPUFrame = &RT64.frames[RT64.CPUFrameIndex];
	memcpy(&CPUFrame->viewMatrix.m, matrix, sizeof(float) * 16);
    gd_inverse_mat4f(&CPUFrame->viewMatrix.m, &CPUFrame->invViewMatrix.m);
}

static void gfx_rt64_rapi_register_layout_graph_node(void *geoLayout, void *graphNode) {
    if (graphNode != nullptr) {
        // Delete the previous graph node mod if it exists already.
        // Graph node addresses can be reused, so it's important to remove any previous mods
        // and only keep the most up to date version of them.
        auto graphNodeIt = RT64.graphNodeMods.find(graphNode);
        if (graphNodeIt != RT64.graphNodeMods.end()) {
            delete graphNodeIt->second;
            RT64.graphNodeMods.erase(graphNodeIt);
        }
    }

	if ((geoLayout != nullptr) && (graphNode != nullptr)) {
        // Find the mod for the specified geoLayout.
        auto it = RT64.geoLayoutMods.find(geoLayout);
		RecordedMod *geoMod = (it != RT64.geoLayoutMods.end()) ? it->second : nullptr;
		if (geoMod != nullptr) {
			RecordedMod *graphMod = RT64.graphNodeMods[graphNode];
			if (graphMod == nullptr) {
				graphMod = new RecordedMod();
				RT64.graphNodeMods[graphNode] = graphMod;
			}

			if (geoMod->materialMod != nullptr) {
				if (graphMod->materialMod == nullptr) {
					graphMod->materialMod = new RT64_MATERIAL();
					graphMod->materialMod->enabledAttributes = RT64_ATTRIBUTE_NONE;
				}

				RT64_ApplyMaterialAttributes(graphMod->materialMod, geoMod->materialMod);
				graphMod->materialMod->enabledAttributes |= geoMod->materialMod->enabledAttributes;
			}

			if (geoMod->lightMod != nullptr) {
				if (graphMod->lightMod == nullptr) {
					graphMod->lightMod = new RT64_LIGHT();
				}

				memcpy(graphMod->lightMod, geoMod->lightMod, sizeof(RT64_LIGHT));
			}

			if (geoMod->normalMapHash != 0) {
				graphMod->normalMapHash = geoMod->normalMapHash;
			}

			if (geoMod->specularMapHash != 0) {
				graphMod->specularMapHash = geoMod->specularMapHash;
			}

			if (!geoMod->interpolationEnabled) {
				graphMod->interpolationEnabled = geoMod->interpolationEnabled;
			}
		}
	}
}

static void *gfx_rt64_rapi_build_graph_node_mod(void *graphNode, float modelview_matrix[4][4], uint32_t uid) {
    auto graphNodeIt = RT64.graphNodeMods.find(graphNode);
    if (graphNodeIt != RT64.graphNodeMods.end()) {
        RecordedMod *graphNodeMod = (RecordedMod *) (graphNodeIt->second);
        if (graphNodeMod != nullptr) {
            if (graphNodeMod->lightMod != nullptr) {
				GameFrame *CPUFrame = &RT64.frames[RT64.CPUFrameIndex];
				auto &displayList = CPUFrame->displayLists[uid];
				RT64_MATRIX4 transform;
                gfx_matrix_mul(transform.m, modelview_matrix, CPUFrame->invViewMatrix.m);
				displayList.light = *graphNodeMod->lightMod;
				displayList.transform = transform;
				displayList.interpolateTransform = (uid != 0) && graphNodeMod->interpolationEnabled;
            }

            return graphNodeMod;
        }
    }

    return nullptr;
}

static void gfx_rt64_rapi_set_graph_node_mod(void *graph_node_mod) {
	RT64.graphNodeMod = (RecordedMod *)(graph_node_mod);
}

static void gfx_rt64_rapi_set_skybox(uint32_t texture_id, float diffuse_color[3]) {
	RT64.skyTextureId = texture_id;
	RT64.skyDiffuseMultiplier = { diffuse_color[0], diffuse_color[1], diffuse_color[2] };
}

extern "C" bool gfx_rt64_dlss_supported() {
	return RT64.dlssSupport;
}

extern "C" bool gfx_rt64_fsr_supported() {
	return RT64.fsrSupport;
}

extern "C" bool gfx_rt64_xess_supported() {
	return RT64.xessSupport;
}

extern "C" void gfx_register_layout_graph_node(void *geoLayout, void *graphNode) {
	static bool loadedLayoutMods = false;
	if (!loadedLayoutMods) {
		gfx_rt64_load_geo_layout_mods();
		loadedLayoutMods = true;
	}

    gfx_rt64_rapi_register_layout_graph_node(geoLayout, graphNode);
}

extern "C" void *gfx_build_graph_node_mod(void *graphNode, float modelview_matrix[4][4], uint32_t uid) {
    return gfx_rt64_rapi_build_graph_node_mod(graphNode, modelview_matrix, uid);
}

RT64_TEXTURE *gfx_rt64_render_thread_find_texture(uint32_t textureKey) {
	auto texIt = RT64.GPUTextures.find(textureKey);
	if ((texIt != RT64.GPUTextures.end()) && (texIt->second.texture != nullptr)) {
		return texIt->second.texture;
	}
	else {
		return RT64.blankTexture;
	}
}

inline void gfx_rt64_render_thread_interpolate_mesh(GPUMesh &dstMesh, const GameMesh &curMesh, const GameMesh &prevMesh, float curFrameWeight) {
	static float *tempVertexBuffer = nullptr;
	static size_t tempVertexBufferSize = 0;

	// Create the delta vertex buffer if it hasn't been created yet or recreate it if it's too small.
	uint64_t requiredVertexBufferSize = curMesh.vertexCount * curMesh.vertexStride;
	if ((dstMesh.deltaVertexBuffer == nullptr) || (requiredVertexBufferSize > dstMesh.deltaVertexBufferSize)) {
		free(dstMesh.deltaVertexBuffer);
		dstMesh.deltaVertexBuffer = (float *)(malloc(requiredVertexBufferSize));
		memset(dstMesh.deltaVertexBuffer, 0, requiredVertexBufferSize);
		dstMesh.deltaVertexBufferSize = requiredVertexBufferSize;
	}

	// Recreate the temporal buffer if required.
	if (requiredVertexBufferSize > tempVertexBufferSize) {
		free(tempVertexBuffer);
		tempVertexBuffer = (float *)(malloc(requiredVertexBufferSize));
		tempVertexBufferSize = requiredVertexBufferSize;
	}

	// FIXME: Since this was ported from the single-threaded code, the delta vertex buffer computations and 
	// comparisons are repeated unnecessarily for every single frame that is drawn. There's not exactly a 
	// good equivalent spot to place this on the main thread yet, but it might be better to just parallelize
	// this at some point or move it to a compute shader anyway.
	const float *prevPtr = prevMesh.vertexBuffer;
	const float *curPtr = curMesh.vertexBuffer;
	float *deltaPtr = dstMesh.deltaVertexBuffer;
	float *tempPtr = tempVertexBuffer;
	size_t f = 0, i = 0;
	size_t imax = curMesh.vertexStride / sizeof(float);
	size_t floatCount = curMesh.vertexCount * imax;
	float deltaValue = 0.0f;
	const float Epsilon = 1e-6f;
	const float MagnitudeThreshold = 10.0f;
	while (f < floatCount) {
		deltaValue = *curPtr - *prevPtr;
		
		switch (i) {
		// Position interpolation.
		case 0:
		case 1:
		case 2:
			// Skip interpolating objects that suddenly teleport the vertices around.
			// This helps with effects like lava bubbles, snow, and other types of effects without
			// having to generate UIDs for each individual particle.
			// Since this relies on an arbitrary value to detect the magnitude difference, it might
			// break depending on the game. The minimum value of 1.0 is also reliant on the fact
			// the game never sends vertices with non-integer values when untransformed, making it
			// the smallest possible value that isn't zero.
			if ((fabsf(deltaValue) / std::max(fabsf(*deltaPtr), 1.0f)) >= MagnitudeThreshold) {
				*tempPtr = *curPtr;
			}
			else {
				*tempPtr = gfx_rt64_lerp_float(*prevPtr, *curPtr, curFrameWeight);
			}

			break;
		// Texture coordinate interpolation.
		case 7:
		case 8:
			if (curMesh.useTexture) {
				// Reuse previous delta if the delta values have different signs.
				// This helps with textures that scroll and eventually reset to their starting
				// position. Since the intended effect is usually to continue the scrolling motion,
				// just reusing the previously known delta value that actually worked is usually a
				// good enough strategy. This might break depending on the game if the UVs are used
				// for anything that doesn't resemble this type of effect.
				if ((deltaValue * (*deltaPtr)) < 0.0f) {
					deltaValue = *deltaPtr;
					*tempPtr = *curPtr - deltaValue;
					break;
				}
			}
			
			*tempPtr = gfx_rt64_lerp_float(*prevPtr, *curPtr, curFrameWeight);
			break;
		// Any other vertex element.
		default:
			*tempPtr = gfx_rt64_lerp_float(*prevPtr, *curPtr, curFrameWeight);
			break;
		}

		*deltaPtr = deltaValue;
		prevPtr++;
		curPtr++;
		tempPtr++;
		deltaPtr++;
		f++;
		i = (i + 1) % imax;
	}

	// Update the mesh using the temporal vertex buffer.
	RT64.lib.SetMesh(dstMesh.mesh, tempVertexBuffer, curMesh.vertexCount, curMesh.vertexStride, RT64.indexTriangleList, curMesh.indexCount);
	dstMesh.vertexBufferHash = curMesh.vertexBufferHash;
}

inline void gfx_rt64_render_thread_add_light(const RT64_LIGHT &srcLight, const RT64_MATRIX4 &transform) {
	assert(RT64.renderLightCount < MAX_LIGHTS);
	auto &dstLight = RT64.renderLights[RT64.renderLightCount++];
	dstLight = srcLight;
	dstLight.position = transform_position_affine(transform, srcLight.position);
	
	// Use a vector that points in all three axes in case the node uses non-uniform scaling to get an estimate.
	RT64_VECTOR3 scaleVector = transform_direction_affine(transform, { 1.0f, 1.0f, 1.0f });
	float scale = vector_length(scaleVector) / sqrtf(3.0f);
	dstLight.attenuationRadius *= scale;
	dstLight.pointRadius *= scale;
	dstLight.shadowOffset *= scale;
}

inline void gfx_rt64_render_thread_draw_display_list(uint32_t uid, GameFrame *curFrame, GameFrame *prevFrame, float curFrameWeight) {
	auto &gpuDl = RT64.GPUDisplayLists[uid];
	const auto &curDisplayList = curFrame->displayLists[uid];
	const auto &prevDisplayList = prevFrame->displayLists[uid];

	for (int i = 0; i < curDisplayList.drawCount; i++) {
		auto &dstInstance = gpuDl.instances[i];
		const auto &curMesh = curDisplayList.meshes[i];
		const auto &prevMesh = (i < prevDisplayList.meshes.size()) ? prevDisplayList.meshes[i] : curDisplayList.meshes[i];
		const auto &curInstance = curDisplayList.instances[i];
		const auto &prevInstance = (i < prevDisplayList.instances.size()) ? prevDisplayList.instances[i] : curDisplayList.instances[i];

		// Check if there's a mesh we can use from the static cache first.
		RT64_MESH *usedMesh = nullptr;
		if (curMesh.raytrace && (curMesh.vertexBufferHash == prevMesh.vertexBufferHash)) {
			const auto &staticMesh = RT64.GPUStaticMeshes[curMesh.vertexBufferHash];
			if (staticMesh.mesh != nullptr) {
				usedMesh = staticMesh.mesh;
				RT64.staticMeshesDrawn++;
			}
		}

		if (usedMesh == nullptr) {
			// Check if current and previous meshes are different.
			if (curInstance.interpolate) {
				auto &dstMesh = gpuDl.meshes[i];

				// Destroy the existing mesh if the raytracing mode is different.
				if ((dstMesh.mesh != nullptr) && (dstMesh.raytrace != curMesh.raytrace)) {
					free(dstMesh.deltaVertexBuffer);
					RT64.lib.DestroyMesh(dstMesh.mesh);
					dstMesh.deltaVertexBuffer = nullptr;
					dstMesh.mesh = nullptr;
					dstMesh.vertexBufferHash = 0;
					RT64.meshesDestroyed++;
				}

				// Create the mesh if it doesn't exist yet.
				if (dstMesh.mesh == nullptr) {
					dstMesh.mesh = RT64.lib.CreateMesh(RT64.device, curMesh.raytrace ? (RT64_MESH_RAYTRACE_ENABLED | RT64_MESH_RAYTRACE_UPDATABLE) : 0);
					dstMesh.raytrace = curMesh.raytrace;
					RT64.meshesCreated++;
				}
				
				if (curMesh.vertexBufferHash != prevMesh.vertexBufferHash) {
					bool meshesCompatible = 
						(curMesh.vertexCount == prevMesh.vertexCount) &&
						(curMesh.vertexStride == prevMesh.vertexStride) &&
						(curMesh.indexCount == prevMesh.indexCount) &&
						(curMesh.raytrace == prevMesh.raytrace);

					// If the meshes are compatible, we interpolate using the delta buffer instead.
					if (meshesCompatible) {
						gfx_rt64_render_thread_interpolate_mesh(dstMesh, curMesh, prevMesh, curFrameWeight);
					}
				}

				// Update the mesh altogether if the vertex buffer hashes are different.
				if (dstMesh.vertexBufferHash != curMesh.vertexBufferHash) {
					RT64.lib.SetMesh(dstMesh.mesh, curMesh.vertexBuffer, curMesh.vertexCount, curMesh.vertexStride, RT64.indexTriangleList, curMesh.indexCount);
					dstMesh.vertexCount = curMesh.vertexCount;
					dstMesh.vertexStride = curMesh.vertexStride;
					dstMesh.indexCount = curMesh.indexCount;
					dstMesh.vertexBufferHash = curMesh.vertexBufferHash;
				}
				
				usedMesh = dstMesh.mesh;
			}
			else {
				// Search for a dynamic mesh that has the same hash.
				auto &dynamicMeshPool = curMesh.raytrace ? RT64.GPUDynamicRtMeshes : RT64.GPUDynamicRasterMeshes;
				auto dynamicMeshIt = dynamicMeshPool.find(curMesh.vertexBufferHash);
				if ((dynamicMeshIt != dynamicMeshPool.end()) && (dynamicMeshIt->second.raytrace == curMesh.raytrace)) {
					dynamicMeshIt->second.inUse = true;
					usedMesh = dynamicMeshIt->second.mesh;
				}

				if (usedMesh == nullptr) {
					// Search linearly for a compatible dynamic mesh.
					uint64_t foundHash = 0;
					for (auto dynamicMeshIt : dynamicMeshPool) {
						if (
							!dynamicMeshIt.second.inUse &&
							(dynamicMeshIt.second.vertexCount == curMesh.vertexCount) &&
							(dynamicMeshIt.second.vertexStride == curMesh.vertexStride) &&
							(dynamicMeshIt.second.indexCount == curMesh.indexCount) &&
							(dynamicMeshIt.second.raytrace == curMesh.raytrace)
						)
						{
							foundHash = dynamicMeshIt.first;
							break;
						}
					}

					// If we found a valid hash, change the hash where the mesh is stored.
					if (foundHash != 0) {
						dynamicMeshPool[curMesh.vertexBufferHash] = dynamicMeshPool[foundHash];
						dynamicMeshPool.erase(foundHash);
					}

					auto &dynamicMesh = dynamicMeshPool[curMesh.vertexBufferHash];

					// Create the mesh if it hasn't been created yet.
					if (dynamicMesh.mesh == nullptr) {
						dynamicMesh.mesh = RT64.lib.CreateMesh(RT64.device, curMesh.raytrace ? (RT64_MESH_RAYTRACE_ENABLED | RT64_MESH_RAYTRACE_UPDATABLE) : 0);
					}

					RT64.lib.SetMesh(dynamicMesh.mesh, curMesh.vertexBuffer, curMesh.vertexCount, curMesh.vertexStride, RT64.indexTriangleList, curMesh.indexCount);

					dynamicMesh.vertexBufferHash = curMesh.vertexBufferHash;
					dynamicMesh.vertexCount = curMesh.vertexCount;
					dynamicMesh.vertexStride = curMesh.vertexStride;
					dynamicMesh.indexCount = curMesh.indexCount;
					dynamicMesh.raytrace = curMesh.raytrace;
					dynamicMesh.inUse = true;

					usedMesh = dynamicMesh.mesh;
				}
			}

			RT64.dynamicMeshesDrawn++;
		}

		assert(usedMesh != nullptr);
		
		// Create the instance if it doesn't exist yet.
		if (dstInstance.instance == nullptr) {
			dstInstance.instance = RT64.lib.CreateInstance(RT64.scene);
			dstInstance.transform = curInstance.desc.transform;
		}

		// Update the instance.
		RT64_INSTANCE_DESC instDesc = curInstance.desc;
		instDesc.scissorRect = gfx_rt64_lerp_rect(prevInstance.desc.scissorRect, curInstance.desc.scissorRect, curFrameWeight);
		instDesc.viewportRect = gfx_rt64_lerp_rect(prevInstance.desc.viewportRect, curInstance.desc.viewportRect, curFrameWeight);
		instDesc.diffuseTexture = gfx_rt64_render_thread_find_texture(curInstance.textures.diffuse);
		instDesc.normalTexture = gfx_rt64_render_thread_find_texture(curInstance.textures.normal);
		instDesc.specularTexture = gfx_rt64_render_thread_find_texture(curInstance.textures.specular);
		instDesc.mesh = usedMesh;

		const bool animatedTexture = (curInstance.textures.diffuse != prevInstance.textures.diffuse);
		instDesc.material.lockMask = animatedTexture ? 1.0f : 0.0f;

		// Assign the shader to the instance. Create if necessary.
		const auto &shader = curInstance.shader;
		instDesc.shader = gfx_rt64_render_thread_load_shader_variant(shader.program, shader.raytrace, shader.filter, shader.hAddr, shader.vAddr, shader.normalMap, shader.specularMap);

		// Detect sudden transformation changes and skip interpolation if necessary.
		const float MinDot = sqrt(2.0f) / -2.0f;
		if (!curInstance.interpolate || gfx_rt64_skip_matrix_lerp(prevInstance.desc.transform, curInstance.desc.transform, MinDot)) {
			instDesc.previousTransform = curInstance.desc.transform;
			instDesc.transform = curInstance.desc.transform;
		}
		else {
			instDesc.previousTransform = dstInstance.transform;
			instDesc.transform = gfx_rt64_lerp_matrix(prevInstance.desc.transform, curInstance.desc.transform, curFrameWeight);
		}

		// Update the instance.
		RT64.lib.SetInstanceDescription(dstInstance.instance, instDesc);
		dstInstance.transform = instDesc.transform;

		// Apply the display list instance light (if applicable).
		if (curInstance.light.groupBits > 0) {
			gfx_rt64_render_thread_add_light(curInstance.light, instDesc.transform);
		}

		gpuDl.drawCount++;
	}
	
	// Apply the display list light (if applicable).
	if (curDisplayList.light.groupBits > 0) {
		RT64_MATRIX4 transform = curDisplayList.interpolateTransform ? gfx_rt64_lerp_matrix(prevDisplayList.transform, curDisplayList.transform, curFrameWeight) : curDisplayList.transform;
		gfx_rt64_render_thread_add_light(curDisplayList.light, transform);
	}
}

void gfx_rt64_render_thread_draw_frame(GameFrame *curFrame, GameFrame *prevFrame, float curFrameWeight, float deltaTimeMs) {
	LARGE_INTEGER elapsedMicro;

	RT64.staticMeshesDrawn = 0;
	RT64.dynamicMeshesDrawn = 0;
	RT64.meshesCreated = 0;
	RT64.meshesDestroyed = 0;

	// Copy the frame's static lights.
	memcpy(RT64.renderLights, curFrame->areaLights, sizeof(RT64_LIGHT) * curFrame->areaLightCount);
	RT64.renderLightCount = curFrame->areaLightCount;

	// Reset the draw counter for all active display lists.
	LARGE_INTEGER dlStart = gfx_rt64_profile_marker();
	auto gpuDlIt = RT64.GPUDisplayLists.begin();
	while (gpuDlIt != RT64.GPUDisplayLists.end()) {
		auto &dl = gpuDlIt->second;
		dl.drawCount = 0;
		gpuDlIt++;
	}

	// Queue up all display lists first.
	auto dlIt = curFrame->displayLists.begin();
	while (dlIt != curFrame->displayLists.end()) {
		gfx_rt64_render_thread_draw_display_list(dlIt->first, curFrame, prevFrame, curFrameWeight);
		dlIt++;
	}

	// Clean up any unused instances or meshes from the GPU display lists.
	gpuDlIt = RT64.GPUDisplayLists.begin();
	while (gpuDlIt != RT64.GPUDisplayLists.end()) {
		auto &dl = gpuDlIt->second;
		
		// Destroy all unused instances.
		while (dl.instances.size() > dl.drawCount) {
			auto &dynInst = dl.instances.back();
			if (dynInst.instance != nullptr) {
				RT64.lib.DestroyInstance(dynInst.instance);
			}

			dl.instances.pop_back();
		}

		// Destroy all unused meshes.
		while (dl.meshes.size() > dl.drawCount) {
			auto &dynMesh = dl.meshes.back();
			free(dynMesh.deltaVertexBuffer);
			if (dynMesh.mesh != nullptr) {
				RT64.lib.DestroyMesh(dynMesh.mesh);
			}

			dl.meshes.pop_back();
		}
		
		gpuDlIt++;
	}

	LARGE_INTEGER dlEnd = gfx_rt64_profile_marker();
	elapsedMicro = gfx_rt64_profile_delta(dlStart, dlEnd);
	double dlMs = elapsedMicro.QuadPart / 1000.0;

	// Interpolate and update the view.
	RT64_MATRIX4 viewMatrix;
	float fovRadians;
	bool interpolateView = curFrame->interpolateView;

	// Detect if camera interpolation should be skipped.
	// Attempts to fix sudden camera changes like the ones in BBH.
	if (interpolateView && gfx_rt64_skip_matrix_lerp(prevFrame->viewMatrix, curFrame->viewMatrix, 0.0f)) {
		interpolateView = false;
	}

	if (interpolateView) {
		viewMatrix = gfx_rt64_lerp_matrix(prevFrame->viewMatrix, curFrame->viewMatrix, curFrameWeight);
		fovRadians = gfx_rt64_lerp_float(prevFrame->fovRadians, curFrame->fovRadians, curFrameWeight);
	}
	else {
		viewMatrix = curFrame->viewMatrix;
		fovRadians = curFrame->fovRadians;
	}

	RT64.lib.SetViewPerspective(RT64.view, viewMatrix, fovRadians, curFrame->nearDist, curFrame->farDist, curFrame->interpolateView);

	// Update the scene.
	RT64.lib.SetSceneLights(RT64.scene, RT64.renderLights, RT64.renderLightCount);
	RT64.lib.SetSceneDescription(RT64.scene, curFrame->sceneDesc);
	RT64.lib.SetViewSkyPlane(RT64.view, (curFrame->skyTextureId > 0) ? RT64.GPUTextures[curFrame->skyTextureId].texture : nullptr);

	// Additional information.
	if ((RT64.renderInspector != nullptr) && RT64.renderInspectorActive) {
		char dlMsMessage[128];
		sprintf(dlMsMessage, "RENDER DL: %.3f ms\n", dlMs);
		RT64.lib.PrintMessageInspector(RT64.renderInspector, dlMsMessage);

		char infoMessage[128];
		sprintf(infoMessage, "ST %d DYN %d CRE %d DTY %d\n", RT64.staticMeshesDrawn, RT64.dynamicMeshesDrawn, RT64.meshesCreated, RT64.meshesDestroyed);
		RT64.lib.PrintMessageInspector(RT64.renderInspector, infoMessage);
	}

	// Draw everything and update the window.
	RT64.lib.DrawDevice(RT64.device, gfx_rt64_use_vsync() ? 1 : 0, deltaTimeMs);

	// Dynamic mesh pool cleanup.
	auto dynamicMeshIt = RT64.GPUDynamicRasterMeshes.begin();
	while (dynamicMeshIt != RT64.GPUDynamicRasterMeshes.end()) {
		if (dynamicMeshIt->second.inUse) {
			dynamicMeshIt->second.inUse = false;
			dynamicMeshIt++;
        }
		else {
			RT64.lib.DestroyMesh(dynamicMeshIt->second.mesh);
			dynamicMeshIt = RT64.GPUDynamicRasterMeshes.erase(dynamicMeshIt);
		}
	}

	dynamicMeshIt = RT64.GPUDynamicRtMeshes.begin();
	while (dynamicMeshIt != RT64.GPUDynamicRtMeshes.end()) {
		if (dynamicMeshIt->second.inUse) {
			dynamicMeshIt->second.inUse = false;
			dynamicMeshIt++;
		}
		else {
			RT64.lib.DestroyMesh(dynamicMeshIt->second.mesh);
			dynamicMeshIt = RT64.GPUDynamicRtMeshes.erase(dynamicMeshIt);
		}
	}
}

void gfx_rt64_render_thread_preprocess_frames(GameFrame *curFrame, GameFrame *prevFrame) {
	// Left click allows to pick a texture for editing from the viewport.
	RT64_INSTANCE *pickSearchInstance = nullptr;
	if (RT64.renderInspectorActive) {
		const std::lock_guard<std::mutex> pickLock(RT64.pickTextureMutex);
		if (RT64.pickTexture) {
			POINT cursorPos = {};
			GetCursorPos(&cursorPos);
			ScreenToClient(RT64.hwnd, &cursorPos);
			RT64_INSTANCE *instance = RT64.lib.GetViewRaytracedInstanceAt(RT64.view, cursorPos.x, cursorPos.y);
			if (instance != nullptr) {
				pickSearchInstance = instance;
			}
			else {
				RT64.pickTextureHash = 0;
			}

			RT64.pickTexture = false;
		}
	}

	int remainingStaticMeshesForCache = CACHED_MESH_MAX_PER_FRAME;
	auto dlIt = curFrame->displayLists.begin();
	while (dlIt != curFrame->displayLists.end()) {
		auto &gpuDl = RT64.GPUDisplayLists[dlIt->first];
		const auto &curDisplayList = curFrame->displayLists[dlIt->first];
		const auto &prevDisplayList = prevFrame->displayLists[dlIt->first];

		// Make the vectors large enough to fit all the instances and meshes.
		if (gpuDl.instances.size() < curDisplayList.drawCount) {
			gpuDl.instances.resize(curDisplayList.drawCount);
		}

		if (gpuDl.meshes.size() < curDisplayList.drawCount) {
			gpuDl.meshes.resize(curDisplayList.drawCount);
		}

		// Search for the matching instance inside the DLs and find the hash corresponding to the diffuse texture.
		if (pickSearchInstance != nullptr) {
			for (int i = 0; (i < gpuDl.drawCount) && (i < gpuDl.instances.size()); i++) {
				if (gpuDl.instances[i].instance == pickSearchInstance) {
					const std::lock_guard<std::mutex> pickLock(RT64.pickTextureMutex);
					uint32_t diffuseId = curDisplayList.instances[i].textures.diffuse;
					auto texIt = RT64.GPUTextures.find(diffuseId);
					if ((diffuseId > 0) && (texIt != RT64.GPUTextures.end())) {
						RT64.pickTextureHash = texIt->second.hash;
					}
					else {
						RT64.pickTextureHash = 0;
					}

					pickSearchInstance = nullptr;
					break;
				}
			}
		}

		if (remainingStaticMeshesForCache > 0) {
			for (int i = 0; i < curDisplayList.drawCount; i++) {
				const auto &curMesh = curDisplayList.meshes[i];

				// Ignore meshes that have already been cached.
				auto &staticMesh = RT64.GPUStaticMeshes[curMesh.vertexBufferHash];
				if ((staticMesh.mesh == nullptr) && (i < prevDisplayList.meshes.size())) {
					// Check if the mesh is a candidate for being cached.
					const auto &prevMesh = prevDisplayList.meshes[i];
					if (curMesh.raytrace && (curMesh.vertexBufferHash == prevMesh.vertexBufferHash)) {
						if (staticMesh.staticFrames >= CACHED_MESH_REQUIRED_FRAMES) {
							if (staticMesh.mesh == nullptr) {
								staticMesh.mesh = RT64.lib.CreateMesh(RT64.device, RT64_MESH_RAYTRACE_ENABLED);
								staticMesh.vertexBufferHash = curMesh.vertexBufferHash;
								RT64.lib.SetMesh(staticMesh.mesh, curMesh.vertexBuffer, curMesh.vertexCount, curMesh.vertexStride, RT64.indexTriangleList, curMesh.indexCount);
								remainingStaticMeshesForCache--;
							}
						}
						else {
							staticMesh.staticFrames++;
						}
					}
				}
			}
		}

		dlIt++;
	}
}

void gfx_rt64_render_thread_upload_texture_queue() {
	// Upload all textures on the queue. Work with a copy of the queue so it's free to keep 
	// loading more textures during the next frame.
	RT64.textureUploadQueueMutex.lock();
	auto textureUploadQueue = RT64.textureUploadQueue;
	RT64.textureUploadQueue = { };
	RT64.textureUploadQueueMutex.unlock();

	while (!textureUploadQueue.empty()) {
		UploadTexture uploadTexture = textureUploadQueue.front();
		textureUploadQueue.pop();

		auto &gpuTexture = RT64.GPUTextures[uploadTexture.key];
		gpuTexture.texture = RT64.lib.CreateTexture(RT64.device, uploadTexture.desc);
		gpuTexture.hash = uploadTexture.hash;
		free(uploadTexture.desc.bytes);
	}
}

void gfx_rt64_render_thread() {
	LARGE_INTEGER frameStart, frameEnd, preprocessStart, preprocessEnd, elapsedMicro;

	// Setup scene and view.
	RT64.scene = RT64.lib.CreateScene(RT64.device);
	RT64.view = RT64.lib.CreateView(RT64.scene);
	RT64.dlssSupport = RT64.lib.GetViewUpscalerSupport(RT64.view, RT64_UPSCALER_DLSS);
	RT64.fsrSupport = RT64.lib.GetViewUpscalerSupport(RT64.view, RT64_UPSCALER_FSR);
	RT64.xessSupport = RT64.lib.GetViewUpscalerSupport(RT64.view, RT64_UPSCALER_XESS);
	
	// Draw at least one empty frame to fill the window.
	RT64.lib.DrawDevice(RT64.device, gfx_rt64_use_vsync() ? 1 : 0, 0.0f);

	// Preload shaders to avoid ingame stuttering.
	gfx_rt64_render_thread_preload_shaders();

	// Preload a blank texture.
	const int BlankTextureSize = 64;
	int blankBytesCount = BlankTextureSize * BlankTextureSize * 4;
	unsigned char *blankBytes = (unsigned char *)(malloc(blankBytesCount));
	memset(blankBytes, 0xFF, blankBytesCount);

	RT64_TEXTURE_DESC texDesc;
	texDesc.bytes = blankBytes;
	texDesc.byteCount = blankBytesCount;
	texDesc.format = RT64_TEXTURE_FORMAT_RGBA8;
	texDesc.width = BlankTextureSize;
	texDesc.height = BlankTextureSize;
	texDesc.rowPitch = texDesc.width * 4;
	RT64.blankTexture = RT64.lib.CreateTexture(RT64.device, texDesc);
	free(blankBytes);

	// Upload any pending textures that the game has already queued up.
	gfx_rt64_render_thread_upload_texture_queue();

	// Unpause the game once the render thread has finished loading.
	RT64.pauseMode = false;

	int curFrameIndex = -1;
	int prevFrameIndex = -1;
	int renderTargetFPS = 30;
	const double FrameSkippingMultiplier = 1.05;
	double targetDeltaTimeMs = (1000.0 / renderTargetFPS);
	double frameDeltaTimeMs = targetDeltaTimeMs;
	int framesSkipped = 0;
	while (RT64.renderThreadRunning) {
		// Create or destroy the inspector depending on the current state of the flag.
		if (RT64.renderInspectorActive && (RT64.renderInspector == nullptr)) {
			RT64.renderInspector = RT64.lib.CreateInspector(RT64.device);
		}
		else if (!RT64.renderInspectorActive && (RT64.renderInspector != nullptr)) {
			RT64.lib.DestroyInspector(RT64.renderInspector);
			RT64.renderInspector = nullptr;
		}

		// Update the view description if modified.
		{
			const std::lock_guard<std::mutex> lock(RT64.renderViewDescMutex);
			if (RT64.renderViewDescChanged) {
				renderTargetFPS = RT64.targetFPS;
				targetDeltaTimeMs = (1000.0 / renderTargetFPS);
				RT64.lib.SetViewDescription(RT64.view, RT64.renderViewDesc);
				RT64.renderViewDescChanged = false;
			}
		}

		// Update any textures if necessary.
		gfx_rt64_render_thread_upload_texture_queue();

		// Retrieve the frame to draw if there's any and clear the last submitted frame.
		// Indicate there's a barrier in the previous frame being used and the CPU should not write to it.
		{
			const std::lock_guard<std::mutex> lock(RT64.renderFrameIndexMutex);
			curFrameIndex = RT64.GPUFrameIndex;
			prevFrameIndex = (curFrameIndex == 0) ? (MAX_RENDER_FRAMES - 1) : (curFrameIndex - 1);
			RT64.BarrierFrameIndex = prevFrameIndex;
			RT64.GPUFrameIndex = -1;
		}

		if (curFrameIndex >= 0) {
			// Run any necessary preprocessing.
			preprocessStart = gfx_rt64_profile_marker();
			gfx_rt64_render_thread_preprocess_frames(&RT64.frames[curFrameIndex], &RT64.frames[prevFrameIndex]);
			preprocessEnd = gfx_rt64_profile_marker();
			elapsedMicro = gfx_rt64_profile_delta(preprocessStart, preprocessEnd);
			double preprocessTimeMs = elapsedMicro.QuadPart / 1000.0;

			// Draw as many frames as the target framerate indicates.
			const unsigned int framesPerUpdate = renderTargetFPS / 30;
			const float weightPerFrame = 1.0f / framesPerUpdate;
			for (int f = 0; f < framesPerUpdate; f++) {
				// Print to the inspector the previous time it took to draw a frame.
				if ((RT64.renderInspector != nullptr) && RT64.renderInspectorActive) {
					const std::lock_guard<std::mutex> lock(RT64.renderInspectorMutex);
					char preprocessTimeMsg[64], renderDeltaTimeMsg[64];
					sprintf(preprocessTimeMsg, "RENDER PREPROCESS: %.3f ms\n", preprocessTimeMs);
					sprintf(renderDeltaTimeMsg, "RENDER FRAME: %.3f ms\n", frameDeltaTimeMs);
					RT64.lib.PrintClearInspector(RT64.renderInspector);
					RT64.lib.PrintMessageInspector(RT64.renderInspector, preprocessTimeMsg);
					RT64.lib.PrintMessageInspector(RT64.renderInspector, renderDeltaTimeMsg);
					for (const std::string &message : RT64.renderInspectorMessages) {
						RT64.lib.PrintMessageInspector(RT64.renderInspector, message.c_str());
					}

					{
						const std::lock_guard<std::mutex> lightingLock(RT64.levelAreaLightingMutex);
						const std::lock_guard<std::mutex> pickLock(RT64.pickTextureMutex);
						int levelIndex = gfx_rt64_get_level_index();
						int areaIndex = gfx_rt64_get_area_index();

						// Inspect the current scene.
						RT64.lib.SetSceneInspector(RT64.renderInspector, &RT64.levelAreaLighting[levelIndex][areaIndex].sceneDesc);

						// Inspect the current level's lights.
						RT64_LIGHT *lights = RT64.levelAreaLighting[levelIndex][areaIndex].lights;
						int *lightCount = &RT64.levelAreaLighting[levelIndex][areaIndex].lightCount;
						RT64.lib.SetLightsInspector(RT64.renderInspector, lights, lightCount, MAX_LEVEL_LIGHTS);

						// Inspect the current picked material.
						if (RT64.pickTextureHash > 0) {
							const std::lock_guard<std::mutex> texModsLock(RT64.texModsMutex);
							auto texNameIt = RT64.texNameMap.find(RT64.pickTextureHash);
							const std::string textureName = (texNameIt != RT64.texNameMap.end()) ? texNameIt->second : std::string();
							RecordedMod *texMod = RT64.texMods[RT64.pickTextureHash];
							if (texMod == nullptr) {
								texMod = new RecordedMod();
								RT64.texMods[RT64.pickTextureHash] = texMod;
							}

							if (texMod->materialMod == nullptr) {
								texMod->materialMod = new RT64_MATERIAL();
								texMod->materialMod->enabledAttributes = RT64_ATTRIBUTE_NONE;
							}

							RT64.lib.SetMaterialInspector(RT64.renderInspector, texMod->materialMod, textureName.c_str());
						}
					}
				}

				// Draw the frame and measure the time right before and right after.
				frameStart = gfx_rt64_profile_marker();
				gfx_rt64_render_thread_draw_frame(&RT64.frames[curFrameIndex], &RT64.frames[prevFrameIndex], (f + 1) * weightPerFrame, targetDeltaTimeMs * (1 + framesSkipped));
				frameEnd = gfx_rt64_profile_marker();
				elapsedMicro = gfx_rt64_profile_delta(frameStart, frameEnd);
				frameDeltaTimeMs = elapsedMicro.QuadPart / 1000.0;

				// Start skipping frames if it took considerably longer than the target framerate to draw a frame.
				if (frameDeltaTimeMs > (targetDeltaTimeMs * FrameSkippingMultiplier)) {
					int framesToSkip = (int)(frameDeltaTimeMs / targetDeltaTimeMs);
					f += framesToSkip;
					framesSkipped += framesToSkip;
				}
				else {
					framesSkipped = 0;
				}
			}

			// Clear the barrier.
			{
				const std::lock_guard<std::mutex> lock(RT64.renderFrameIndexMutex);
				RT64.BarrierFrameIndex = -1;
			}
		}
	}
}

struct GfxWindowManagerAPI gfx_rt64_wapi = {
    gfx_rt64_wapi_init,
    gfx_rt64_wapi_set_keyboard_callbacks,
    gfx_rt64_wapi_main_loop,
    gfx_rt64_wapi_get_dimensions,
    gfx_rt64_wapi_handle_events,
    gfx_rt64_wapi_start_frame,
    gfx_rt64_wapi_swap_buffers_begin,
    gfx_rt64_wapi_swap_buffers_end,
    gfx_rt64_wapi_get_time,
    gfx_rt64_wapi_shutdown,
};

struct GfxRenderingAPI gfx_rt64_rapi = {
    gfx_rt64_rapi_z_is_from_0_to_1,
    gfx_rt64_rapi_unload_shader,
    gfx_rt64_rapi_load_shader,
    gfx_rt64_rapi_create_and_load_new_shader,
    gfx_rt64_rapi_lookup_shader,
    gfx_rt64_rapi_shader_get_info,
    gfx_rt64_rapi_new_texture,
    gfx_rt64_rapi_select_texture,
    gfx_rt64_rapi_upload_texture,
    gfx_rt64_rapi_upload_texture_file,
    gfx_rt64_rapi_set_sampler_parameters,
    gfx_rt64_rapi_set_depth_test,
    gfx_rt64_rapi_set_depth_mask,
    gfx_rt64_rapi_set_zmode_decal,
    gfx_rt64_rapi_set_viewport,
    gfx_rt64_rapi_set_scissor,
    gfx_rt64_rapi_set_use_alpha,
	gfx_rt64_rapi_set_fog,
	gfx_rt64_rapi_set_camera_perspective,
	gfx_rt64_rapi_set_camera_matrix,
	gfx_rt64_rapi_draw_triangles_ortho,
    gfx_rt64_rapi_draw_triangles_persp,
	gfx_rt64_rapi_set_graph_node_mod,
	gfx_rt64_rapi_set_skybox,
    gfx_rt64_rapi_init,
	gfx_rt64_rapi_on_resize,
    gfx_rt64_rapi_start_frame,
	gfx_rt64_rapi_end_frame,
	gfx_rt64_rapi_finish_render,
    gfx_rt64_rapi_shutdown
};

#else

#error "RT64 is only supported on Windows"

#endif // _WIN32

#endif
