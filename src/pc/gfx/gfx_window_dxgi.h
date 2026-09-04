#ifndef GFX_WINDOW_DXGI_H
#define GFX_WINDOW_DXGI_H

#include "gfx_rendering_api.h"

#ifdef DECLARE_GFX_DXGI_FUNCTIONS
void gfx_window_dxgi_create_factory_and_device(bool debug, int d3d_version, bool (*create_device_fn)(IDXGIAdapter1 *adapter, bool test_only));
Microsoft::WRL::ComPtr<IDXGISwapChain1> gfx_window_dxgi_create_swap_chain(IUnknown *device);
extern "C" HWND gfx_window_dxgi_get_h_wnd(void);
void ThrowIfFailed(HRESULT res);
void ThrowIfFailed(HRESULT res, HWND h_wnd, const char *message);
#endif

extern struct GfxWindowBackendAPI gfx_window_dxgi;

#endif
