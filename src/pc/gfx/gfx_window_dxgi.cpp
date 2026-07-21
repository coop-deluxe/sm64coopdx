#if defined(_WIN32)

#include <stdint.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>

#include <map>
#include <set>
#include <string>

#include <windows.h>
#include <wrl/client.h>
#include <dxgi1_6.h>
#include <versionhelpers.h>

#include <shellscalingapi.h>

#ifndef _LANGUAGE_C
#define _LANGUAGE_C
#endif
#include <PR/gbi.h>

#define DECLARE_GFX_DXGI_FUNCTIONS
#include "gfx_window_dxgi.h"

extern "C" {
    #include "pc/mods/mod_import.h"
    #include "pc/rom_checker.h"
    #include "pc/network/version.h"
    #include "pc/configfile.h"
}

#include "pc/pc_main.h"

#include "gfx_window_manager.h"
#include "gfx_rendering_api.h"
#include "gfx_direct3d_common.h"
#include "gfx_screen_config.h"
#include "gfx_pc.h"

extern "C" f64 clock_elapsed_f64(void);

using namespace Microsoft::WRL; // For ComPtr

static SDL_Window *sSdlWindow;

static struct {
    HWND h_wnd;
    bool showing_error;
    std::string window_title;

    HMODULE dxgi_module;
    HRESULT (__stdcall *CreateDXGIFactory1)(REFIID riid, void **factory);
    HRESULT (__stdcall *CreateDXGIFactory2)(UINT flags, REFIID iid, void **factory);

    ComPtr<IDXGIFactory2> factory;
    ComPtr<IDXGISwapChain1> swap_chain;
    HANDLE waitable_object;
    uint64_t qpc_init, qpc_freq;
    bool allow_tearing;
} dxgi;

static void load_dxgi_library(void) {
    dxgi.dxgi_module = LoadLibraryW(L"dxgi.dll");
    *(FARPROC *)&dxgi.CreateDXGIFactory1 = GetProcAddress(dxgi.dxgi_module, "CreateDXGIFactory1");
    *(FARPROC *)&dxgi.CreateDXGIFactory2 = GetProcAddress(dxgi.dxgi_module, "CreateDXGIFactory2");
}

#define IS_FULLSCREEN() ((SDL_GetWindowFlags(sSdlWindow) & SDL_WINDOW_FULLSCREEN_DESKTOP) != 0)

static void gfx_window_dxgi_on_resize(void) {
    if (dxgi.swap_chain.Get() != nullptr) {
        gfx_get_current_rendering_api()->on_resize();

        DXGI_SWAP_CHAIN_DESC1 desc1;
        ThrowIfFailed(dxgi.swap_chain->GetDesc1(&desc1));
    }
}

static void gfx_window_dxgi_set_fullscreen(void) {
    gfx_window_dxgi_on_resize();
}

static void gfx_window_dxgi_init(const char *window_title) {
    LARGE_INTEGER qpc_init, qpc_freq;
    QueryPerformanceCounter(&qpc_init);
    QueryPerformanceFrequency(&qpc_freq);
    dxgi.qpc_init = qpc_init.QuadPart;
    dxgi.qpc_freq = qpc_freq.QuadPart;

    dxgi.window_title = window_title;

    int xpos = (configWindow.x == WAPI_WIN_CENTERPOS) ? SDL_WINDOWPOS_CENTERED : configWindow.x;
    int ypos = (configWindow.y == WAPI_WIN_CENTERPOS) ? SDL_WINDOWPOS_CENTERED : configWindow.y;

    sSdlWindow = SDL_CreateWindow(
        window_title,
        xpos, ypos, configWindow.w, configWindow.h,
        SDL_WINDOW_RESIZABLE
    );

    gfx_wm_set_window(sSdlWindow);

    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);

    SDL_GetWindowWMInfo(sSdlWindow, &wmInfo);

    dxgi.h_wnd = wmInfo.info.win.window;

    load_dxgi_library();
}

static void gfx_window_dxgi_handle_events(SDL_Event event) {
    if (event.type == SDL_WINDOWEVENT) {
        if (!IS_FULLSCREEN()) {
            if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                gfx_window_dxgi_on_resize();
            }
        }
    }
}

static bool gfx_window_dxgi_start_frame(void) {
    return true;
}

static void gfx_window_dxgi_swap_buffers_begin(void) {
    UINT syncInterval = configWindow.vsync;
    UINT presentFlags = 0;
    if (!syncInterval && dxgi.allow_tearing) {
        presentFlags |= DXGI_PRESENT_ALLOW_TEARING;
    }
    ThrowIfFailed(dxgi.swap_chain->Present(syncInterval, presentFlags));
}

static void gfx_window_dxgi_swap_buffers_end(void) {
}

static double gfx_window_dxgi_get_time(void) {
    LARGE_INTEGER t;
    QueryPerformanceCounter(&t);
    return (double)(t.QuadPart - dxgi.qpc_init) / dxgi.qpc_freq;
}

void gfx_window_dxgi_create_factory_and_device(bool debug, int d3d_version, bool (*create_device_fn)(IDXGIAdapter1 *adapter, bool test_only)) {
    if (dxgi.CreateDXGIFactory2 != nullptr) {
        ThrowIfFailed(dxgi.CreateDXGIFactory2(debug ? DXGI_CREATE_FACTORY_DEBUG : 0, __uuidof(IDXGIFactory2), &dxgi.factory));
    } else {
        ThrowIfFailed(dxgi.CreateDXGIFactory1(__uuidof(IDXGIFactory2), &dxgi.factory));
    }

    ComPtr<IDXGIAdapter1> adapter;
    for (UINT i = 0; dxgi.factory->EnumAdapters1(i, &adapter) != DXGI_ERROR_NOT_FOUND; i++) {
        DXGI_ADAPTER_DESC1 desc;
        adapter->GetDesc1(&desc);
        if (desc.Flags & 2/*DXGI_ADAPTER_FLAG_SOFTWARE*/) { // declaration missing in mingw headers
            continue;
        }
        if (create_device_fn(adapter.Get(), true)) {
            break;
        }
    }
    create_device_fn(adapter.Get(), false);

    SDL_SetWindowTitle(sSdlWindow, dxgi.window_title.c_str());
}

ComPtr<IDXGISwapChain1> gfx_window_dxgi_create_swap_chain(IUnknown *device) {
    bool win8 = IsWindows8OrGreater(); // DXGI_SCALING_NONE is only supported on Win8 and beyond
    bool dxgi_13 = dxgi.CreateDXGIFactory2 != nullptr; // DXGI 1.3 introduced waitable object

    dxgi.allow_tearing = false;
    ComPtr<IDXGIFactory5> factory5;
    if (SUCCEEDED(dxgi.factory.As(&factory5))) {
        BOOL allow = FALSE;
        if (SUCCEEDED(factory5->CheckFeatureSupport(DXGI_FEATURE_PRESENT_ALLOW_TEARING, &allow, sizeof(allow)))) {
            dxgi.allow_tearing = allow;
        }
    }

    DXGI_SWAP_CHAIN_DESC1 swap_chain_desc = {};
    swap_chain_desc.BufferCount = 2;
    swap_chain_desc.Width = 0;
    swap_chain_desc.Height = 0;
    swap_chain_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swap_chain_desc.Scaling = win8 ? DXGI_SCALING_NONE : DXGI_SCALING_STRETCH;
    swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL; // Apparently this was backported to Win 7 Platform Update
    swap_chain_desc.Flags = 0;
    swap_chain_desc.SampleDesc.Count = 1;

    if (dxgi_13) {
        swap_chain_desc.Flags |= DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT;
    }
    if (dxgi.allow_tearing) {
        swap_chain_desc.Flags |= DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;
    }

    ThrowIfFailed(dxgi.factory->CreateSwapChainForHwnd(device, dxgi.h_wnd, &swap_chain_desc, nullptr, nullptr, &dxgi.swap_chain));
    ThrowIfFailed(dxgi.factory->MakeWindowAssociation(dxgi.h_wnd, DXGI_MWA_NO_ALT_ENTER));

    ComPtr<IDXGISwapChain2> swap_chain2;
    if (dxgi.swap_chain->QueryInterface(__uuidof(IDXGISwapChain2), &swap_chain2) == S_OK) {
        ThrowIfFailed(swap_chain2->SetMaximumFrameLatency(1));
        dxgi.waitable_object = swap_chain2->GetFrameLatencyWaitableObject();
        WaitForSingleObject(dxgi.waitable_object, INFINITE);
    } else {
        ComPtr<IDXGIDevice1> device1;
        ThrowIfFailed(device->QueryInterface(IID_PPV_ARGS(&device1)));
        ThrowIfFailed(device1->SetMaximumFrameLatency(1));
    }

    ThrowIfFailed(dxgi.swap_chain->GetDesc1(&swap_chain_desc));

    return dxgi.swap_chain;
}

static int gfx_window_dxgi_get_max_msaa(void) {
    return 0;
}

extern "C" HWND gfx_window_dxgi_get_h_wnd(void) {
    return dxgi.h_wnd;
}

void ThrowIfFailed(HRESULT res) {
    if (FAILED(res)) {
        fprintf(stderr, "Error: 0x%08X\n", res);
        throw res;
    }
}

void ThrowIfFailed(HRESULT res, HWND h_wnd, const char *message) {
    if (FAILED(res)) {
        char full_message[256];
        sprintf(full_message, "%s\n\nHRESULT: 0x%08X", message, res);
        dxgi.showing_error = true;
        MessageBoxA(h_wnd, full_message, "Error", MB_OK | MB_ICONERROR);
        throw res;
    }
}

struct GfxWindowBackendAPI gfx_window_dxgi = {
    gfx_window_dxgi_init,
    gfx_window_dxgi_set_fullscreen,
    gfx_window_dxgi_handle_events,
    gfx_window_dxgi_start_frame,
    gfx_window_dxgi_swap_buffers_begin,
    gfx_window_dxgi_swap_buffers_end,
    gfx_window_dxgi_get_time,
    gfx_window_dxgi_get_max_msaa,
};

#endif
