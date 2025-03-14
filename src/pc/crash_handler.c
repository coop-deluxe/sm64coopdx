// Adapted from PeachyPeach's sm64pc-omm (now sm64ex-omm)
#include "crash_handler.h"

char gLastRemoteBhv[256] = "";

#if (defined(_WIN32) || defined(__linux__)) && !defined(WAPI_DUMMY)

#ifdef HAVE_SDL2
#include <SDL2/SDL.h>
#endif

#include <PR/ultratypes.h>
#include <PR/gbi.h>
#include "config.h"
#include "pc/gfx/gfx_window_manager_api.h"
#include "pc/gfx/gfx_dxgi.h"
#include "pc/gfx/gfx_sdl.h"
#include "pc/gfx/gfx_pc.h"
#include "game/game_init.h"
#include "game/ingame_menu.h"
#include "game/segment2.h"
#include "game/mario.h"
#include "gfx_dimensions.h"
#include "pc/djui/djui.h"
#include "pc/djui/djui_unicode.h"
#include "pc/network/network.h"
#include "pc/gfx/gfx_rendering_api.h"
#include "pc/mods/mods.h"
#include "pc/debuglog.h"
#include "pc/pc_main.h"
#include "controller/controller_keyboard.h"

typedef struct {
    s32 x, y;
    u8 r, g, b;
    char s[128];
} CrashHandlerText;
static CrashHandlerText sCrashHandlerText[128 + 256 + 4];

#define PTR long long unsigned int)(uintptr_t

#define ARRAY_SIZE(a)               (sizeof(a) / sizeof(a[0]))
#define MEMNEW(typ, cnt)            calloc(cnt, sizeof(typ))
#define STRING(str, size, fmt, ...) char str[size]; snprintf(str, size, fmt, __VA_ARGS__);

#define BACK_TRACE_SIZE 15

#ifdef _WIN32

#define OS_NAME "Windows"

#if IS_64_BIT
    #define CRASH_HANDLER_TYPE LONG
    #define SYMBOL_INCREMENT 16
    #define SYMBOL_SCAN_FORMAT "%016llX"
    #define MACHINE_TYPE IMAGE_FILE_MACHINE_AMD64
    #define ARCHITECTURE_STR "64-bit"
#else
    #define CRASH_HANDLER_TYPE LONG WINAPI
    #define SYMBOL_INCREMENT 9
    #define SYMBOL_SCAN_FORMAT "%08X"
    #define MACHINE_TYPE IMAGE_FILE_MACHINE_I386
    #define ARCHITECTURE_STR "32-bit"
#endif

#include <stdio.h>
#include <windows.h>
#include <dbghelp.h>
#include <crtdbg.h>
#include "dbghelp.h"

static struct {
    u32 code;
    const char *error;
    const char *message;
} sCrashHandlerErrors[] = {
    { EXCEPTION_ACCESS_VIOLATION,       "Segmentation Fault",       "The game tried to %s at address 0x%016llX." },
    { EXCEPTION_ARRAY_BOUNDS_EXCEEDED,  "Array Out Of Bounds",      "The game tried to access an element out of the array bounds." },
    { EXCEPTION_DATATYPE_MISALIGNMENT,  "Data Misalignment",        "The game tried to access misaligned data." },
    { EXCEPTION_BREAKPOINT,             "Breakpoint",               "The game reached a breakpoint." },
    { EXCEPTION_FLT_DENORMAL_OPERAND,   "Float Denormal Operand",   "The game tried to perform a floating point operation with a denormal operand." },
    { EXCEPTION_FLT_DIVIDE_BY_ZERO,     "Float Division By Zero",   "The game tried to divide a floating point number by zero." },
    { EXCEPTION_FLT_INEXACT_RESULT,     "Float Inexact Result",     "The game couldn't represent the result of a floating point operation as a decimal fraction." },
    { EXCEPTION_FLT_INVALID_OPERATION,  "Float Invalid Operation",  "The game tried to perform an invalid floating point operation." },
    { EXCEPTION_FLT_OVERFLOW,           "Float Overflow",           "An overflow occurred with a floating point number." },
    { EXCEPTION_FLT_STACK_CHECK,        "Float Stack Overflow",     "The game performed a floating point operation resulting in a stack overflow." },
    { EXCEPTION_FLT_UNDERFLOW,          "Float Underflow",          "An underflow occurred with a floating point number." },
    { EXCEPTION_ILLEGAL_INSTRUCTION,    "Illegal Instruction",      "The game tried to execute an invalid instruction." },
    { EXCEPTION_IN_PAGE_ERROR,          "Page Error",               "The game tried to %s at address 0x%016llX." },
    { EXCEPTION_INT_DIVIDE_BY_ZERO,     "Integer Division By Zero", "The game tried to divide an integer by zero." },
    { EXCEPTION_INT_OVERFLOW,           "Integer Overflow",         "An overflow occurred with an integer." },
    { EXCEPTION_PRIV_INSTRUCTION,       "Instruction Not Allowed",  "The game tried to execute an invalid instruction." },
    { EXCEPTION_STACK_OVERFLOW,         "Stack Overflow",           "The game performed an operation resulting in a stack overflow." },
    { 0,                                "Unknown Exception",        "An unknown exception occurred." },
};


#if !IS_64_BIT
static ULONG CaptureStackWalkBackTrace(CONTEXT* ctx, DWORD FramesToSkip, DWORD FramesToCapture, void* BackTrace[]) {

    HANDLE process = GetCurrentProcess();
    HANDLE thread = GetCurrentThread();

    STACKFRAME64 stack;
    memset(&stack, 0, sizeof(STACKFRAME64));
#if IS_64_BIT
    stack.AddrPC.Offset = (*ctx).Rip;
    stack.AddrPC.Mode = AddrModeFlat;
    stack.AddrStack.Offset = (*ctx).Rsp;
    stack.AddrStack.Mode = AddrModeFlat;
    stack.AddrFrame.Offset = (*ctx).Rbp;
    stack.AddrFrame.Mode = AddrModeFlat;
#else
    stack.AddrPC.Offset = (*ctx).Eip;
    stack.AddrPC.Mode = AddrModeFlat;
    stack.AddrStack.Offset = (*ctx).Esp;
    stack.AddrStack.Mode = AddrModeFlat;
    stack.AddrFrame.Offset = (*ctx).Ebp;
    stack.AddrFrame.Mode = AddrModeFlat;
#endif

    ULONG frame = 0;
    for (frame = 0; ; frame++)
    {
        if (!StackWalk64(MACHINE_TYPE, process, thread, &stack, ctx, NULL, NULL, NULL, NULL)) { break; }
        if (frame < FramesToSkip || frame >= FramesToCapture) { continue; }
        BackTrace[frame+1] = (void*)(intptr_t)stack.AddrPC.Offset;
    }
    return frame;
}
#endif

#elif __linux__

#define OS_NAME "Linux"

#if IS_64_BIT
    #define CRASH_HANDLER_TYPE LONG
    #define SYMBOL_INCREMENT 16
    #define SYMBOL_SCAN_FORMAT "%ld"
    #define MACHINE_TYPE IMAGE_FILE_MACHINE_AMD64
    #define ARCHITECTURE_STR "64-bit"
#else
    #define CRASH_HANDLER_TYPE LONG WINAPI
    #define SYMBOL_INCREMENT 9
    #define SYMBOL_SCAN_FORMAT "%ld"
    #define MACHINE_TYPE IMAGE_FILE_MACHINE_I386
    #define ARCHITECTURE_STR "32-bit"
#endif

#define __USE_GNU

#include <signal.h>
#include <execinfo.h>
#include <ucontext.h>
#include <dlfcn.h>

static struct {
    u32 code;
    const char *error;
    const char *message;
} sCrashHandlerErrors[] = {
    { SIGBUS,       "Bad Memory Access",        "The game tried to access memory out of bounds." },
    { SIGFPE,       "Floating Point Exception", "The game tried to perform illegal arithmetic on a floating point." },
    { SIGILL,       "Illegal Instruction",      "The game tried to execute an invalid instruction." },
    { SIGSEGV,      "Segmentation Fault",       "The game tried to %s at address 0x%016llX." },
};

#endif

#define crash_handler_set_text(_x_, _y_, _r_, _g_, _b_, _fmt_, ...)     \
{                                                                       \
    if (_x_ == -1) {                                                    \
        pText->x = ((pText - 1)->x + strlen((pText - 1)->s) * 4);       \
    } else {                                                            \
        pText->x = _x_;                                                 \
    }                                                                   \
    pText->y = _y_;                                                     \
    pText->r = _r_;                                                     \
    pText->g = _g_;                                                     \
    pText->b = _b_;                                                     \
    snprintf(pText->s, 128, _fmt_, __VA_ARGS__);                        \
    pText++;                                                            \
}

void render_create_dl_ortho_matrix(void) {
    static const Mtx sIdentMatrix = { {
        { 1.f, 0.f, 0.f, 0.f },
        { 0.f, 1.f, 0.f, 0.f },
        { 0.f, 0.f, 1.f, 0.f },
        { 0.f, 0.f, 0.f, 1.f },
    } };
    static const Mtx sOrthoMatrix = { {
        { 2.f / SCREEN_WIDTH, 0.f, 0.f, 0.f },
        { 0.f, 2.f / SCREEN_HEIGHT, 0.f, 0.f },
        { 0.f, 0.f, -0.1f, 0.f },
        { -1.f, -1.f, 0.f, 1.f },
    } };
    gSPPerspNormalize(gDisplayListHead++, 0xFFFF);
    gSPMatrix(gDisplayListHead++, &sIdentMatrix, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(gDisplayListHead++, &sIdentMatrix, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(gDisplayListHead++, &sOrthoMatrix, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
}

static void crash_handler_produce_one_frame_callback(void) {
    float minAspectRatio = 1.743468f;
    float aspectScale = 1.0f;
    if (gfx_current_dimensions.aspect_ratio < minAspectRatio) {
        aspectScale = gfx_current_dimensions.aspect_ratio / minAspectRatio;
    }

    // Print text
    const struct DjuiFont* font = gDjuiFonts[0];
    if (font->textBeginDisplayList != NULL) {
        gSPDisplayList(gDisplayListHead++, font->textBeginDisplayList);
    }

    for (CrashHandlerText* text = sCrashHandlerText; text->s[0] != 0; ++text) {
        s32 x = GFX_DIMENSIONS_RECT_FROM_LEFT_EDGE(text->x * aspectScale);
        s32 y = SCREEN_HEIGHT - 8 - text->y * aspectScale;
        gDPPipeSync(gDisplayListHead++);
        gDPSetEnvColor(gDisplayListHead++, text->r, text->g, text->b, 0xFF);
        create_dl_translation_matrix(DJUI_MTX_PUSH, x, y, 0);

        // translate scale
        f32 fontSize = 10.0f * aspectScale;
        create_dl_scale_matrix(DJUI_MTX_NOPUSH, fontSize, fontSize, 1.0f);

        // set color
        gDPSetEnvColor(gDisplayListHead++, text->r, text->g, text->b, 0xFF);

        // render the line
        f32 addX = 0;
        char* c = text->s;
        while (*c != '\0') {
            f32 charWidth = 0.4f;

            if ((u8)*c <= 0x20 || (u8)*c >= 0x7F) {
                addX += charWidth;
                c = djui_unicode_next_char(c);
                continue;
            }

            if (addX != 0) {
                create_dl_translation_matrix(DJUI_MTX_NOPUSH, addX, 0, 0);
                addX = 0;
            }
            // render
            font->render_char(c);
            create_dl_translation_matrix(DJUI_MTX_NOPUSH, charWidth, 0, 0);
            c = djui_unicode_next_char(c);
        }

        // pop
        gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
    }
}

static void crash_handler_produce_one_frame(void) {
    extern u8 gRenderingInterpolated;
    gRenderingInterpolated = false;
    produce_one_dummy_frame(crash_handler_produce_one_frame_callback, 0x02, 0x06, 0x0F);
}

static void crash_handler_add_info_str(CrashHandlerText** pTextP, f32 x, f32 y, const char* title, const char* value) {
    CrashHandlerText* pText = *pTextP;
    crash_handler_set_text(x, y, 0xFF, 0xFF, 0x00, "%s", title);
    crash_handler_set_text(-1, y, 0xFF, 0xFF, 0xFF, "%s", ": ");
    crash_handler_set_text(-1, y, 0x00, 0xFF, 0xFF, "%s", value);
    *pTextP = pText;
}

static void crash_handler_add_version_str(CrashHandlerText** pTextP, f32 x, f32 y) {
    CrashHandlerText* pText = *pTextP;
    crash_handler_add_info_str(&pText, x, y, "Version", SM64COOPDX_VERSION);
    crash_handler_add_info_str(&pText, x, y + 8, "Renderer", RAPI_NAME);
    *pTextP = pText;
}

static void crash_handler_add_info_int(CrashHandlerText** pTextP, f32 x, f32 y, const char* title, int value) {
    CrashHandlerText* pText = *pTextP;
    crash_handler_set_text(x, y, 0xFF, 0xFF, 0x00, "%s", title);
    crash_handler_set_text(-1, y, 0xFF, 0xFF, 0xFF, "%s", ": ");
    crash_handler_set_text(-1, y, 0x00, 0xFF, 0xFF, "%d", value);
    *pTextP = pText;
}

#ifdef _WIN32
static CRASH_HANDLER_TYPE crash_handler(EXCEPTION_POINTERS *ExceptionInfo) {
#elif __linux__
static void crash_handler(const int signalNum, siginfo_t *info, UNUSED ucontext_t *context) {
#endif
    printf("Game crashed! preparing crash screen...\n");
    memset(sCrashHandlerText, 0, sizeof(sCrashHandlerText));
    CrashHandlerText *pText = &sCrashHandlerText[0];
    gDjuiDisabled = true;

    // Exception report
    crash_handler_set_text(8, -4, 0xFF, 0x80, 0x00, "%s", "Please report this crash with a consistent way to reproduce it.");

    // Exception address, code, type and info
#ifdef _WIN32
    if (ExceptionInfo && ExceptionInfo->ExceptionRecord) {
        PEXCEPTION_RECORD er = ExceptionInfo->ExceptionRecord;
        crash_handler_set_text( 8, 4, 0xFF, 0x00, 0x00, "%s", "Exception occurred at address ");
        crash_handler_set_text(-1, 4, 0xFF, 0xFF, 0x00, "0x%016llX", (PTR) er->ExceptionAddress);
        crash_handler_set_text(-1, 4, 0xFF, 0x00, 0x00, "%s", " with error code ");
        crash_handler_set_text(-1, 4, 0xFF, 0x00, 0xFF, "0x%08X", (u32) er->ExceptionCode);
        crash_handler_set_text(-1, 4, 0xFF, 0x00, 0x00, "%s", ":");
        for (s32 i = 0; i != ARRAY_SIZE(sCrashHandlerErrors); ++i) {
            if (sCrashHandlerErrors[i].code == (u32) er->ExceptionCode || sCrashHandlerErrors[i].code == 0) {
                crash_handler_set_text( 8, 12, 0xFF, 0x00, 0x00, "%s", sCrashHandlerErrors[i].error);
                crash_handler_set_text(-1, 12, 0xFF, 0xFF, 0xFF, "%s", " - ");
                if (er->ExceptionCode == EXCEPTION_ACCESS_VIOLATION || er->ExceptionCode == EXCEPTION_IN_PAGE_ERROR) {
                    crash_handler_set_text(-1, 12, 0xFF, 0xFF, 0xFF, sCrashHandlerErrors[i].message, (er->ExceptionInformation[0] ? "write" : "read"), (PTR)er->ExceptionInformation[1]);
                } else {
                    crash_handler_set_text(-1, 12, 0xFF, 0xFF, 0xFF, "%s", sCrashHandlerErrors[i].message);
                }
                break;
            }
        }
#elif __linux__
    if (signalNum != 0 && info != NULL) {
        crash_handler_set_text( 8, 4, 0xFF, 0x00, 0x00, "%s", "Exception occurred at address ");
        crash_handler_set_text(-1, 4, 0xFF, 0xFF, 0x00, "0x%016llX", (u64) info->si_addr);
        crash_handler_set_text(-1, 4, 0xFF, 0x00, 0x00, "%s", " with error code ");
        crash_handler_set_text(-1, 4, 0xFF, 0x00, 0xFF, "0x%08X", (u32) signalNum);
        crash_handler_set_text(-1, 4, 0xFF, 0x00, 0x00, "%s", ":");
        for (s32 i = 0; i != ARRAY_SIZE(sCrashHandlerErrors); ++i) {
            if (sCrashHandlerErrors[i].code == (u32) signalNum || sCrashHandlerErrors[i].code == 0) {
                crash_handler_set_text( 8, 12, 0xFF, 0x00, 0x00, "%s", sCrashHandlerErrors[i].error);
                crash_handler_set_text(-1, 12, 0xFF, 0xFF, 0xFF, "%s", " - ");
                if (signalNum == SIGSEGV) {
                    char segFaultStr[255] = "";
                    if (info->si_code == SEGV_MAPERR) {
                        snprintf(segFaultStr, 255, "The game tried to read unmapped memory at address %p", info->si_addr);
#ifdef __x86_64__
                    } else if (info->si_code == SEGV_ACCERR) {
                        snprintf(segFaultStr, 255, "The game tried to %s at address %016llX", ((context->uc_mcontext.gregs[REG_ERR] & 0x2) != 0 ? "write" : "read"), (u64) info->si_addr);
#endif
                    } else {
                        snprintf(segFaultStr, 255, "Unknown segmentation fault at address %p", info->si_addr);
                    }

                    crash_handler_set_text(-1, 12, 0xFF, 0xFF, 0xFF, "%s", segFaultStr);
                } else {
                    crash_handler_set_text(-1, 12, 0xFF, 0xFF, 0xFF, "%s", sCrashHandlerErrors[i].message);
                }
                break;
            }
        }
#endif
    } else {
        crash_handler_set_text(8,  4, 0xFF, 0x00, 0x00, "%s", "An unknown exception occurred somewhere in the game's code.");
        crash_handler_set_text(8, 12, 0x80, 0x80, 0x80, "%s", "Unable to retrieve the exception info.");
    }

    // Registers
    crash_handler_set_text(8, 22, 0xFF, 0xFF, 0xFF, "%s", "Registers:");
#if defined(_WIN32) || (defined(__linux__) && defined(__x86_64__))
#ifdef _WIN32
    if (ExceptionInfo && ExceptionInfo->ContextRecord) {
        PCONTEXT cr = ExceptionInfo->ContextRecord;
#if IS_64_BIT
        crash_handler_set_text( 8, 30, 0xFF, 0xFF, 0xFF,   "RSP: 0x%016llX", (PTR)cr->Rsp);
        crash_handler_set_text(-1, 30, 0xFF, 0xFF, 0xFF, "  RBP: 0x%016llX", (PTR)cr->Rbp);
        crash_handler_set_text(-1, 30, 0xFF, 0xFF, 0xFF, "  RIP: 0x%016llX", (PTR)cr->Rip);
        crash_handler_set_text( 8, 38, 0xFF, 0xFF, 0xFF,   "RAX: 0x%016llX", (PTR)cr->Rax);
        crash_handler_set_text(-1, 38, 0xFF, 0xFF, 0xFF, "  RBX: 0x%016llX", (PTR)cr->Rbx);
        crash_handler_set_text(-1, 38, 0xFF, 0xFF, 0xFF, "  RCX: 0x%016llX", (PTR)cr->Rcx);
        crash_handler_set_text(-1, 38, 0xFF, 0xFF, 0xFF, "  RDX: 0x%016llX", (PTR)cr->Rdx);
        crash_handler_set_text( 8, 46, 0xFF, 0xFF, 0xFF,   "R08: 0x%016llX", (PTR)cr->R8);
        crash_handler_set_text(-1, 46, 0xFF, 0xFF, 0xFF, "  R09: 0x%016llX", (PTR)cr->R9);
        crash_handler_set_text(-1, 46, 0xFF, 0xFF, 0xFF, "  R10: 0x%016llX", (PTR)cr->R10);
        crash_handler_set_text(-1, 46, 0xFF, 0xFF, 0xFF, "  R11: 0x%016llX", (PTR)cr->R11);
        crash_handler_set_text( 8, 54, 0xFF, 0xFF, 0xFF,   "R12: 0x%016llX", (PTR)cr->R12);
        crash_handler_set_text(-1, 54, 0xFF, 0xFF, 0xFF, "  R13: 0x%016llX", (PTR)cr->R13);
        crash_handler_set_text(-1, 54, 0xFF, 0xFF, 0xFF, "  R14: 0x%016llX", (PTR)cr->R14);
        crash_handler_set_text(-1, 54, 0xFF, 0xFF, 0xFF, "  R15: 0x%016llX", (PTR)cr->R15);
        crash_handler_set_text( 8, 62, 0xFF, 0xFF, 0xFF,   "RSI: 0x%016llX", (PTR)cr->Rsi);
        crash_handler_set_text(-1, 62, 0xFF, 0xFF, 0xFF, "  RDI: 0x%016llX", (PTR)cr->Rdi);
#else
        crash_handler_set_text( 8, 30, 0xFF, 0xFF, 0xFF,   "EAX: 0x%016llX", (PTR)cr->Eax);
        crash_handler_set_text(-1, 30, 0xFF, 0xFF, 0xFF, "  EBX: 0x%016llX", (PTR)cr->Ebx);
        crash_handler_set_text(-1, 30, 0xFF, 0xFF, 0xFF, "  ECX: 0x%016llX", (PTR)cr->Ecx);
        crash_handler_set_text( 8, 38, 0xFF, 0xFF, 0xFF,   "EDX: 0x%016llX", (PTR)cr->Edx);
        crash_handler_set_text(-1, 38, 0xFF, 0xFF, 0xFF, "  ESI: 0x%016llX", (PTR)cr->Esi);
        crash_handler_set_text(-1, 38, 0xFF, 0xFF, 0xFF, "  EDI: 0x%016llX", (PTR)cr->Edi);
        crash_handler_set_text(-1, 38, 0xFF, 0xFF, 0xFF, "  EBP: 0x%016llX", (PTR)cr->Ebp);
        crash_handler_set_text( 8, 46, 0xFF, 0xFF, 0xFF,   "EIP: 0x%016llX", (PTR)cr->Eip);
        crash_handler_set_text(-1, 46, 0xFF, 0xFF, 0xFF, "  ESP: 0x%016llX", (PTR)cr->Esp);
        crash_handler_set_text(-1, 46, 0xFF, 0xFF, 0xFF, "   CS: 0x%016llX", (PTR)cr->SegCs);
        crash_handler_set_text(-1, 46, 0xFF, 0xFF, 0xFF, "   DS: 0x%016llX", (PTR)cr->SegDs);
        crash_handler_set_text( 8, 54, 0xFF, 0xFF, 0xFF,   " ES: 0x%016llX", (PTR)cr->SegEs);
        crash_handler_set_text(-1, 54, 0xFF, 0xFF, 0xFF, "   FS: 0x%016llX", (PTR)cr->SegFs);
        crash_handler_set_text(-1, 54, 0xFF, 0xFF, 0xFF, "   GS: 0x%016llX", (PTR)cr->SegGs);
        crash_handler_set_text(-1, 54, 0xFF, 0xFF, 0xFF, "   SS: 0x%016llX", (PTR)cr->SegSs);
        crash_handler_set_text( 8, 62, 0xFF, 0xFF, 0xFF,   "DR0: 0x%016llX", (PTR)cr->Dr0);
        crash_handler_set_text(-1, 62, 0xFF, 0xFF, 0xFF, "  DR1: 0x%016llX", (PTR)cr->Dr1);
#endif
#elif __linux__
    if (context->uc_mcontext.gregs[REG_RSP] != 0) {
#if IS_64_BIT
        crash_handler_set_text( 8, 30, 0xFF, 0xFF, 0xFF,   "RSP: 0x%016llX", context->uc_mcontext.gregs[REG_RSP]);
        crash_handler_set_text(-1, 30, 0xFF, 0xFF, 0xFF, "  RBP: 0x%016llX", context->uc_mcontext.gregs[REG_RBP]);
        crash_handler_set_text(-1, 30, 0xFF, 0xFF, 0xFF, "  RIP: 0x%016llX", context->uc_mcontext.gregs[REG_RIP]);
        crash_handler_set_text( 8, 38, 0xFF, 0xFF, 0xFF,   "RAX: 0x%016llX", context->uc_mcontext.gregs[REG_RAX]);
        crash_handler_set_text(-1, 38, 0xFF, 0xFF, 0xFF, "  RBX: 0x%016llX", context->uc_mcontext.gregs[REG_RBX]);
        crash_handler_set_text(-1, 38, 0xFF, 0xFF, 0xFF, "  RCX: 0x%016llX", context->uc_mcontext.gregs[REG_RCX]);
        crash_handler_set_text(-1, 38, 0xFF, 0xFF, 0xFF, "  RDX: 0x%016llX", context->uc_mcontext.gregs[REG_RDX]);
        crash_handler_set_text( 8, 46, 0xFF, 0xFF, 0xFF,   "R08: 0x%016llX", context->uc_mcontext.gregs[REG_R8]);
        crash_handler_set_text(-1, 46, 0xFF, 0xFF, 0xFF, "  R09: 0x%016llX", context->uc_mcontext.gregs[REG_R9]);
        crash_handler_set_text(-1, 46, 0xFF, 0xFF, 0xFF, "  R10: 0x%016llX", context->uc_mcontext.gregs[REG_R10]);
        crash_handler_set_text(-1, 46, 0xFF, 0xFF, 0xFF, "  R11: 0x%016llX", context->uc_mcontext.gregs[REG_R11]);
        crash_handler_set_text( 8, 54, 0xFF, 0xFF, 0xFF,   "R12: 0x%016llX", context->uc_mcontext.gregs[REG_R12]);
        crash_handler_set_text(-1, 54, 0xFF, 0xFF, 0xFF, "  R13: 0x%016llX", context->uc_mcontext.gregs[REG_R13]);
        crash_handler_set_text(-1, 54, 0xFF, 0xFF, 0xFF, "  R14: 0x%016llX", context->uc_mcontext.gregs[REG_R14]);
        crash_handler_set_text(-1, 54, 0xFF, 0xFF, 0xFF, "  R15: 0x%016llX", context->uc_mcontext.gregs[REG_R15]);
        crash_handler_set_text( 8, 62, 0xFF, 0xFF, 0xFF,   "RSI: 0x%016llX", context->uc_mcontext.gregs[REG_RSI]);
        crash_handler_set_text(-1, 62, 0xFF, 0xFF, 0xFF, "  RDI: 0x%016llX", context->uc_mcontext.gregs[REG_RDI]);
#else
        crash_handler_set_text( 8, 30, 0xFF, 0xFF, 0xFF,   "EAX: 0x%016llX", context->uc_mcontext.gregs[REG_EAX]);
        crash_handler_set_text(-1, 30, 0xFF, 0xFF, 0xFF, "  EBX: 0x%016llX", context->uc_mcontext.gregs[REG_EBX]);
        crash_handler_set_text(-1, 30, 0xFF, 0xFF, 0xFF, "  ECX: 0x%016llX", context->uc_mcontext.gregs[REG_ECX]);
        crash_handler_set_text( 8, 38, 0xFF, 0xFF, 0xFF,   "EDX: 0x%016llX", context->uc_mcontext.gregs[REG_EDX]);
        crash_handler_set_text(-1, 38, 0xFF, 0xFF, 0xFF, "  ESI: 0x%016llX", context->uc_mcontext.gregs[REG_ESI]);
        crash_handler_set_text(-1, 38, 0xFF, 0xFF, 0xFF, "  EDI: 0x%016llX", context->uc_mcontext.gregs[REG_EDI]);
        crash_handler_set_text(-1, 38, 0xFF, 0xFF, 0xFF, "  EBP: 0x%016llX", context->uc_mcontext.gregs[REG_EBP]);
        crash_handler_set_text( 8, 46, 0xFF, 0xFF, 0xFF,   "EIP: 0x%016llX", context->uc_mcontext.gregs[REG_EIP]);
        crash_handler_set_text(-1, 46, 0xFF, 0xFF, 0xFF, "  ESP: 0x%016llX", context->uc_mcontext.gregs[REG_ESP]);
        crash_handler_set_text(-1, 46, 0xFF, 0xFF, 0xFF, "   CS: 0x%016llX", context->uc_mcontext.gregs[REG_CS]);
        crash_handler_set_text(-1, 46, 0xFF, 0xFF, 0xFF, "   DS: 0x%016llX", context->uc_mcontext.gregs[REG_DS]);
        crash_handler_set_text( 8, 54, 0xFF, 0xFF, 0xFF,   " ES: 0x%016llX", context->uc_mcontext.gregs[REG_ES]);
        crash_handler_set_text(-1, 54, 0xFF, 0xFF, 0xFF, "   FS: 0x%016llX", context->uc_mcontext.gregs[REG_FS]);
        crash_handler_set_text(-1, 54, 0xFF, 0xFF, 0xFF, "   GS: 0x%016llX", context->uc_mcontext.gregs[REG_GS]);
        crash_handler_set_text(-1, 54, 0xFF, 0xFF, 0xFF, "   SS: 0x%016llX", context->uc_mcontext.gregs[REG_SS]);
        crash_handler_set_text( 8, 62, 0xFF, 0xFF, 0xFF,   "DR0: 0x%016llX", context->uc_mcontext.gregs[REG_RDI]);
        crash_handler_set_text(-1, 62, 0xFF, 0xFF, 0xFF, "  DR1: 0x%016llX", context->uc_mcontext.gregs[REG_RDX]);
#endif
#endif
    } else {
        crash_handler_set_text(8, 30, 0x80, 0x80, 0x80, "%s", "Unable to access the registers.");
    }
#else
    crash_handler_set_text(8, 30, 0x80, 0x80, 0x80, "%s", "Cannot access the registers on this system.");
#endif

    // Stack trace
    crash_handler_set_text(8, 72, 0xFF, 0xFF, 0xFF, "%s", "Stack trace:");
#ifdef _WIN32
    if (ExceptionInfo && ExceptionInfo->ContextRecord) {
        static const char sGlobalFunctionIdentifier[] = "(sec1)(fl0x00)(ty20)(scl2)(nx0)0x";
        static const char sStaticFunctionIdentifier[] = "(sec1)(fl0x00)(ty20)(scl3)(nx0)0x";
        typedef struct Symbol { uintptr_t offset; char name[128]; struct Symbol *next; } Symbol;
        Symbol *symbols = NULL;
        Symbol* symbol0 = NULL;

        // Load symbols
        char filename[256] = { 0 };
        const char *exe_path = sys_exe_path_dir();
        if (exe_path[0] != '\0') {
            snprintf(filename, 256, "%s/%s", exe_path, "coop.map");
        } else {
            snprintf(filename, 256, "%s", "coop.map");
        }

        FILE *f = fopen(filename, "r");
        if (f) {
            char buffer[1024];
            while (fgets(buffer, 1024, f)) {

                // Remove spaces
                char bufferNoSpace[1024] = { 0 };
                for (char *p0 = buffer, *p1 = bufferNoSpace; *p0 != 0; ++p0) {
                    if (*p0 > 0x20) {
                        *(p1++) = *p0;
                    }
                }

                // Try to find identifiers
                char *id0 = strstr(bufferNoSpace, sGlobalFunctionIdentifier);
                char *id1 = strstr(bufferNoSpace, sStaticFunctionIdentifier);
                if (id0 || id1) {
                    char *addr = (char *) max((uintptr_t) id0, (uintptr_t) id1) + sizeof(sGlobalFunctionIdentifier) - 1;
                    char* name = addr + SYMBOL_INCREMENT;

                    // New symbol
                    Symbol *newSymbol = MEMNEW(Symbol, 1);
                    snprintf(newSymbol->name, 128, "%s", name); *name = 0;
                    sscanf(addr, SYMBOL_SCAN_FORMAT, &newSymbol->offset);
                    newSymbol->next = NULL;

                    // Store symbol
                    if (symbols == NULL) {
                        symbols = newSymbol;
                    } else {
                        for (Symbol *symbol = symbols;; symbol = symbol->next) {
                            if (symbol->next == NULL) {
                                symbol->next = newSymbol;
                                break;
                            }
                            if (symbol->next->offset > newSymbol->offset) {
                                newSymbol->next = symbol->next;
                                symbol->next = newSymbol;
                                break;
                            }
                        }
                    }

                    // Reference
                    if (memcmp(newSymbol->name, "set_mario_action", sizeof("set_mario_action")) == 0) {
                        symbol0 = newSymbol;
                    }
                }
            }
            fclose(f);
        }
        uintptr_t addr0 = (symbol0 ? ((uintptr_t) set_mario_action - symbol0->offset) : 0);

        // Unwind and print call stack
        void *stack[64];
#if IS_64_BIT
        s32 frames = CaptureStackBackTrace(6, 64, stack, NULL);
#else
        s32 frames = CaptureStackWalkBackTrace(ExceptionInfo->ContextRecord, 0, 64, stack);
#endif
        for (s32 i = 1, j = 0; i < frames && j < BACK_TRACE_SIZE; ++i) {
            s32 y = 80 + j++ * 8;
            crash_handler_set_text( 8, y, 0xFF, 0xFF, 0x00, "0x%016llX", (PTR) stack[i]);
            crash_handler_set_text(-1, y, 0xFF, 0xFF, 0xFF, "%s", ": ");
            for (Symbol *symbol = symbols;; symbol = symbol->next) {
                if (symbol == NULL || symbol->next == NULL) {
                    if (j != 0) {
                        crash_handler_set_text(-1, y, 0x00, 0xFF, 0xFF, "%s", "????");
                    }
                    break;
                } else {
                    uintptr_t offset = (uintptr_t) stack[i] - addr0;
                    if (symbol->next->offset > offset) {
                        crash_handler_set_text(-1, y, 0x00, 0xFF, 0xFF, "%s", symbol->name);
                        crash_handler_set_text(-1, y, 0xFF, 0xFF, 0xFF, " + 0x%llX", (PTR)(offset - symbol->offset));
                        break;
                    }
                }
            }
        }
#elif __linux__
    void *trace[BACK_TRACE_SIZE];
    u8 traceSize = backtrace(trace, BACK_TRACE_SIZE);
    if (traceSize > 0) {
        // Unwind and print call stack
        char **messages = backtrace_symbols(trace, traceSize);
        for (s32 i = 1, j = 0; i < traceSize && j < BACK_TRACE_SIZE; ++i) {
            s32 y = 80 + j++ * 8;
            crash_handler_set_text( 8, y, 0xFF, 0xFF, 0x00, "0x%016llX", (u64) strtoul(strstr(messages[i], "[") + 1, NULL, 16));
            crash_handler_set_text(-1, y, 0xFF, 0xFF, 0xFF, "%s", ": ");

            // dladdr gives us function names if -rdynamic/-export-dynamic is set in compiler flags
            Dl_info info;
            if (dladdr(trace[i], &info) && info.dli_sname) {
                crash_handler_set_text(-1, y, 0x00, 0xFF, 0xFF, "%s", info.dli_sname);
                crash_handler_set_text(-1, y, 0xFF, 0xFF, 0xFF, " + 0x%lX", trace[i] - info.dli_saddr);
            } else {
                crash_handler_set_text(-1, y, 0x00, 0xFF, 0xFF, "%s", "????");
            }
        }
#endif
    } else {
        crash_handler_set_text(8, 116, 0x80, 0x80, 0x80, "%s", "Unable to unwind the call stack.");
    }

    // Info
    crash_handler_add_info_str(&pText, 315, -4 + (8 * 0), "Arch", ARCHITECTURE_STR);
    crash_handler_add_info_str(&pText, 315, -4 + (8 * 1), "Network", (gNetworkType == NT_SERVER) ? "Server" : "Client");
    crash_handler_add_info_str(&pText, 315, -4 + (8 * 2), "System", (gNetworkSystem == NULL) ? "null" : gNetworkSystem->name);
    crash_handler_add_info_int(&pText, 315, -4 + (8 * 3), "Players", network_player_connected_count());

    s32 syncObjects = 0;
    if (gGameInited) {
        for (struct SyncObject* so = sync_object_get_first(); so != NULL; so = sync_object_get_next()) {
            if (so->o != NULL) { syncObjects++; }
        }
    }
    crash_handler_add_info_int(&pText, 315, -4 + (8 * 4), "SyncObj", syncObjects);

    crash_handler_add_info_int(&pText, 380, -4 + (8 * 0), "Id", (int)gPcDebug.id & 0xFF);
    crash_handler_add_info_int(&pText, 380, -4 + (8 * 1), "Ofs", (int)gPcDebug.bhvOffset & 0xFF);
    extern s16 gPrevFrameObjectCount;
    crash_handler_add_info_int(&pText, 380, -4 + (8 * 4), "Objs", gPrevFrameObjectCount);

    crash_handler_add_info_int(&pText, 380, -4 + (8 * 2), "Mods", gActiveMods.entryCount);

    crash_handler_add_info_str(&pText, 380, -4 + (8 * 3), "OS", OS_NAME);

    // Mods
    crash_handler_set_text(245, 64, 0xFF, 0xFF, 0xFF, "%s", "Mods:");
    {
        s32 x = 245;
        s32 y = 72;
        for (s32 i = 0; i < gActiveMods.entryCount; i++) {
            struct Mod* mod = gActiveMods.entries[i];
            u8 g = (gPcDebug.lastModRun == mod) ? 0 : 0xFF;
            crash_handler_set_text(x, y, 0xFF, g, 200, "%.21s", mod->name);
            y += 8;
        }
    }

    // Packets
    crash_handler_set_text(335, 64, 0xFF, 0xFF, 0xFF, "%s", "Packets:");
    {
        s32 x = 335;
        s32 y = 72;
        u8 index = gDebugPacketOnBuffer;
        for (s32 i = 0; i < 128; i++) {
            u8 brightness = (gDebugPacketIdBuffer[index] * 5) % 200;
            if (gDebugPacketSentBuffer[index]) {
                crash_handler_set_text(x, y, 0xFF, 0xFF, brightness, "%02X", gDebugPacketIdBuffer[index]);
            } else {
                crash_handler_set_text(x, y, brightness, 0xFF, 0xFF, "%02X", gDebugPacketIdBuffer[index]);
            }
            index--;
            y += 8;
            if (y >= 72 + (16 * 8)) {
                y = 72;
                x += 10;
            }
        }
    }

    crash_handler_add_version_str(&pText, 335, 208);
    crash_handler_add_info_str(&pText, 8, 208, "RemoteBhv", gLastRemoteBhv);

    // sounds
#ifdef HAVE_SDL2
    if (SDL_WasInit(SDL_INIT_AUDIO) || SDL_InitSubSystem(SDL_INIT_AUDIO) == 0) {
        SDL_AudioSpec want, have;
        want.freq = 32000;
        want.format = AUDIO_S16SYS;
        want.channels = 1;
        want.samples = 0x200;
        want.callback = NULL;
        want.userdata = NULL;
        s32 device = SDL_OpenAudioDevice(NULL, 0, &want, &have, 0);
        if (device) {
            SDL_PauseAudioDevice(device, 0);
        }
    }
#endif

    // In case the game crashed before the game window opened
    if (!gGfxInited) {
        gfx_init(&WAPI, &RAPI, TITLE);
        WAPI.set_keyboard_callbacks(keyboard_on_key_down, keyboard_on_key_up, keyboard_on_all_keys_up,
            keyboard_on_text_input, keyboard_on_text_editing);
    }
    if (!gGameInited) djui_unicode_init();

    // Main loop
    while (true) {
        WAPI.main_loop(crash_handler_produce_one_frame);
    }
    exit(0);
}

AT_STARTUP static void init_crash_handler(void) {
#ifdef _WIN32
    // Windows
    SetUnhandledExceptionFilter(crash_handler);
#elif __linux__

    // Linux
    struct sigaction linuxCrashHandler;
    linuxCrashHandler.sa_handler = (void*) &crash_handler;
    sigemptyset(&linuxCrashHandler.sa_mask);
    linuxCrashHandler.sa_flags = SA_SIGINFO; // Get extra info about the crash

    sigaction(SIGBUS, &linuxCrashHandler, NULL);
    sigaction(SIGFPE, &linuxCrashHandler, NULL);
    sigaction(SIGILL, &linuxCrashHandler, NULL);
    sigaction(SIGSEGV, &linuxCrashHandler, NULL);
#endif
}

#endif

struct PcDebug gPcDebug = {
    .tags = {
        0x0000000000000000,
        0x000000000000FFFF,
        0x2D1D50FB02617949,
        0x8AEB7180FAE739EB,
        0x0CDB1A233CC71057,
        0x53D5D9880C8B278E,
        0xE8E307BE5802542E,
        0x8A3ACC4FDB4FFE45,
        0x09046C2BA3C5000D,
        0xF027964ADE989C29,
        0x076CF19655C70007,
        0x440C28A5CC404F11,
        0xE9A402C28144FD8B,
        0x9A2269E87B26BE68,
        0x0E76DE227D813019,
        0x12ABA8362D430002,
    },
    .id = DEFAULT_ID,
    .bhvOffset = /* 0x12 */ 0,
    .debugId = 0x4BE2,
    .lastModRun = NULL,
};

void crash_handler_init(void) {
    u64* first = gPcDebug.tags;
    *first = 0;
    u64* tag = gPcDebug.tags;
    u64* inner = NULL;
    u64 hash = 0;
    u64 id = gPcDebug.debugId ^ MIXER;
    while (*tag != DEFAULT_ID) {
        inner = tag;
        if (id == *tag) { gPcDebug.bhvOffset = 0x12; }
        while (*inner != DEFAULT_ID) {
            if (tag == inner) { inner++; continue; }
            hash |= (*tag < (*inner ^ MIXER) || *tag > (*inner ^ MIXER))
                 ? (*tag & *first)
                 : ((*tag & *(first+1))|3);
            inner++;
        }
        if (*(tag+1) == DEFAULT_ID) {
            *tag |= hash;
            break;
        }
        tag++;
    }
}
