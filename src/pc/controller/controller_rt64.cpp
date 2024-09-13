#ifdef RAPI_RT64

#include "controller_rt64.h"
#include "controller_mouse.h"
#include "pc/gfx/gfx_rt64_context.h"

#include "../configfile.h"

#include <cassert>

#ifndef HID_USAGE_PAGE_GENERIC
#   define HID_USAGE_PAGE_GENERIC         ((unsigned short) 0x01)
#endif
#ifndef HID_USAGE_GENERIC_MOUSE
#   define HID_USAGE_GENERIC_MOUSE        ((unsigned short) 0x02)
#endif

#if !defined(CAPI_SDL2) && !defined(CAPI_SDL1)
int mouse_x = 0;
int mouse_y = 0;
#endif

#ifdef BETTERCAMERA
extern u8 newcam_mouse;
#endif

#define MAX_MOUSEBINDS  32

static u32 num_mouse_binds = 0;
static u32 mouse_binds[MAX_MOUSEBINDS][2];

static void controller_rt64_api_read(OSContPad *pad) {
#ifdef BETTERCAMERA
    // Mouselook support.
    RT64.mouselookEnabled = (newcam_mouse == 1);

    if (RT64.mouselookEnabled && RT64.windowActive) {
        mouse_x = RT64.deltaMouseX;
        mouse_y = RT64.deltaMouseY;

        // Clip the cursor to the window rectangle.
        RECT windowRect;
        GetWindowRect(RT64.hwnd, &windowRect);
        ClipCursor(&windowRect);
    }
    else {
        mouse_x = 0;
        mouse_y = 0;
        ClipCursor(NULL);
    }
#endif

    // Return current state of mouse buttons. Mouse buttons should only be detected if window is active.
    if (RT64.windowActive) {
        for (u32 i = 0; i < num_mouse_binds; ++i) {
            if (RT64.mouseButtons & (1 << mouse_binds[i][0])) {
                pad->button |= mouse_binds[i][1];
            }
        }
    }

    // Clear delta mouse movement.
    RT64.deltaMouseX = RT64.deltaMouseY = 0;
}

static void controller_rt64_api_shutdown(void) {
    ClipCursor(NULL);
}

static u32 controller_rt64_api_rawkey(void) {
    for (unsigned short b = 0; b < MAX_MOUSE_BUTTONS; b++) {
       if (RT64.mouseButtons & (1 << b)) {
           return b;
       }
    }

    return VK_INVALID;
}

static inline void bind_buttons(const u32 mask, const u32 *btns) {
    for (u32 i = 0; (i < MAX_BINDS) && (num_mouse_binds < MAX_MOUSEBINDS); ++i) {
        if ((btns[i] >= VK_BASE_RT64) && (btns[i] <= (VK_BASE_RT64 + VK_SIZE))) {
            mouse_binds[num_mouse_binds][0] = btns[i] - VK_BASE_RT64;
            mouse_binds[num_mouse_binds][1] = mask;
            num_mouse_binds++;
        }
    }
}

static void controller_rt64_api_bind(void) {
    memset(mouse_binds, 0, sizeof(mouse_binds));
    num_mouse_binds = 0;

    bind_buttons(A_BUTTON,     configKeyA);
    bind_buttons(B_BUTTON,     configKeyB);
    bind_buttons(Z_TRIG,       configKeyZ);
    bind_buttons(STICK_UP,     configKeyStickUp);
    bind_buttons(STICK_LEFT,   configKeyStickLeft);
    bind_buttons(STICK_DOWN,   configKeyStickDown);
    bind_buttons(STICK_RIGHT,  configKeyStickRight);
    bind_buttons(U_CBUTTONS,   configKeyCUp);
    bind_buttons(L_CBUTTONS,   configKeyCLeft);
    bind_buttons(D_CBUTTONS,   configKeyCDown);
    bind_buttons(R_CBUTTONS,   configKeyCRight);
    bind_buttons(L_TRIG,       configKeyL);
    bind_buttons(R_TRIG,       configKeyR);
    bind_buttons(START_BUTTON, configKeyStart);
}

static void controller_rt64_api_init(void) {
    assert(RT64.hwnd != NULL);

    // Register mouse as raw device for WM_INPUT.
    RAWINPUTDEVICE Rid[1];
	Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC; 
	Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE; 
	Rid[0].dwFlags = RIDEV_INPUTSINK;   
	Rid[0].hwndTarget = RT64.hwnd;
	RegisterRawInputDevices(Rid, 1, sizeof(Rid[0]));

    controller_rt64_api_bind();
}

// Barebones controller API to handle mouse movement.
struct ControllerAPI controller_rt64_api = {
    VK_BASE_RT64,
    controller_rt64_api_init,
    controller_rt64_api_read,
    controller_rt64_api_rawkey,
    NULL,
    NULL,
    controller_rt64_api_bind,
    controller_rt64_api_shutdown
};

#endif