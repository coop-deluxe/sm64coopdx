#include "dynos.cpp.h"
extern "C" {
#include "object_fields.h"
#include "engine/level_script.h"
#include "game/object_helpers.h"
#include "game/segment2.h"
#include "game/level_geo.h"
#include "game/level_update.h"
#include "game/moving_texture.h"
#include "game/paintings.h"
#include "game/geo_misc.h"
#include "game/mario_misc.h"
#include "game/mario_actions_cutscene.h"
#include "game/screen_transition.h"
#include "game/object_list_processor.h"
#include "game/behavior_actions.h"
#include "game/rendering_graph_node.h"
#include "game/skybox.h"
#include "game/scroll_targets.h"
}

//
// String
//

static const struct { const char *mStr; u8 mChar64; s32 mWidth; } sSm64CharMap[] = {
    { "0",   0x00, 7 }, { "1",  0x01,  7 }, { "2",   0x02, 7 }, { "3",   0x03, 7 }, { "4",   0x04,  7 }, { "5",   0x05,  7 },
    { "6",   0x06, 7 }, { "7",  0x07,  7 }, { "8",   0x08, 7 }, { "9",   0x09, 7 }, { "A",   0x0A,  6 }, { "B",   0x0B,  6 },
    { "C",   0x0C, 6 }, { "D",  0x0D,  6 }, { "E",   0x0E, 6 }, { "F",   0x0F, 6 }, { "G",   0x10,  6 }, { "H",   0x11,  6 },
    { "I",   0x12, 5 }, { "J",  0x13,  6 }, { "K",   0x14, 6 }, { "L",   0x15, 5 }, { "M",   0x16,  8 }, { "N",   0x17,  8 },
    { "O",   0x18, 6 }, { "P",  0x19,  6 }, { "Q",   0x1A, 6 }, { "R",   0x1B, 6 }, { "S",   0x1C,  6 }, { "T",   0x1D,  5 },
    { "U",   0x1E, 6 }, { "V",  0x1F,  6 }, { "W",   0x20, 8 }, { "X",   0x21, 7 }, { "Y",   0x22,  6 }, { "Z",   0x23,  6 },
    { "a",   0x24, 6 }, { "b",  0x25,  5 }, { "c",   0x26, 5 }, { "d",   0x27, 6 }, { "e",   0x28,  5 }, { "f",   0x29,  5 },
    { "g",   0x2A, 6 }, { "h",  0x2B,  5 }, { "i",   0x2C, 4 }, { "j",   0x2D, 5 }, { "k",   0x2E,  5 }, { "l",   0x2F,  3 },
    { "m",   0x30, 7 }, { "n",  0x31,  5 }, { "o",   0x32, 5 }, { "p",   0x33, 5 }, { "q",   0x34,  6 }, { "r",   0x35,  5 },
    { "s",   0x36, 5 }, { "t",  0x37,  5 }, { "u",   0x38, 5 }, { "v",   0x39, 5 }, { "w",   0x3A,  7 }, { "x",   0x3B,  7 },
    { "y",   0x3C, 5 }, { "z",  0x3D,  5 }, { "\'",  0x3E, 4 }, { ".",   0x3F, 4 }, { "^",   0x50,  8 }, { "|",   0x51,  8 },
    { "<",   0x52, 8 }, { ">",  0x53,  8 }, { "[A]", 0x54, 7 }, { "[B]", 0x55, 7 }, { "[C]", 0x56,  6 }, { "[Z]", 0x57,  7 },
    { "[R]", 0x58, 7 }, { ",",  0x6F,  4 }, { " ",   0x9E, 5 }, { "-",   0x9F, 6 }, { "/",   0xD0, 10 }, { "[%]", 0xE0,  7 },
    { "(",   0xE1, 5 }, { ")(", 0xE2, 10 }, { ")",   0xE3, 5 }, { "+",   0xE4, 9 }, { "&",   0xE5,  8 }, { ":",   0xE6,  4 },
    { "!",   0xF2, 5 }, { "%",  0xF3,  7 }, { "?",   0xF4, 7 }, { "~",   0xF7, 8 }, { "$",   0xF9,  8 }, { "@",   0xFA, 10 },
    { "*",   0xFB, 6 }, { "=",  0xFD, 10 }, { "\n",  0xFE, 0 },
};

static const char *DynOS_String_AddChar64(u8 *aStr64, const char *pStr, s32 &aIndex) {
    for (const auto &c : sSm64CharMap) {
        if (strstr(pStr, c.mStr) == pStr) {
            aStr64[aIndex++] = c.mChar64;
            return pStr + strlen(c.mStr);
        }
    }

    // Put a space by default
    aStr64[aIndex++] = 0x9E;
    return pStr + 1;
}

u8 *DynOS_String_Convert(const char *aString, bool aHeapAlloc) {

    // Allocation
    static u8 sStringBuffer[8][2048];
    static u32 sStringBufferIndex = 0;
    u8 *_Str64;
    if (aHeapAlloc) {
        _Str64 = New<u8>(2048);
    } else {
        _Str64 = sStringBuffer[sStringBufferIndex];
        sStringBufferIndex = (sStringBufferIndex + 1) % 8;
    }

    // Conversion
    memset(_Str64, 0xFF, 2048);
    const char *pStr = aString;
    for (s32 i = 0; *pStr != 0 && i < 2047;) {
        pStr = DynOS_String_AddChar64(_Str64, pStr, i);
    }
    return _Str64;
}

u8 *DynOS_String_Decapitalize(u8 *aStr64) {
    bool _WasSpace = true;
    for (u8 *pStr64 = aStr64; *pStr64 != 0xFF; pStr64++) {
        if (*pStr64 >= 10 && *pStr64 <= 35) {
            if (_WasSpace) _WasSpace = false;
            else *pStr64 += 26;
        } else if (*pStr64 >= 63) {
            _WasSpace = true;
        }
    }
    return aStr64;
}

s32 DynOS_String_Length(const u8 *aStr64) {
    s32 _Length = 0;
    for (; aStr64 && *aStr64 != 255; aStr64++, _Length++);
    return _Length;
}

s32 DynOS_String_WidthChar64(u8 aChar64) {
    for (const auto &c : sSm64CharMap) {
        if (c.mChar64 == aChar64) {
            return c.mWidth;
        }
    }
    return 0;
}

s32 DynOS_String_Width(const u8 *aStr64) {
    s32 _Width = 0;
    for (; *aStr64 != 0xFF; aStr64++) {
        _Width += DynOS_String_WidthChar64(*aStr64);
    }
    return _Width;
}

//
// Scroll Targets
//

void DynOS_Add_Scroll_Target(u32 index, const char* name, u32 offset, u32 size) {
    for (auto& lvlPair : DynOS_Lvl_GetArray()) {
        for (auto& node : lvlPair.second->mVertices) {
            if (node->mName.Find(name) >= 0) {
                add_vtx_scroll_target(
                    index,
                    offset > 0 ? &node->mData[offset] : node->mData,
                    size > 0 ? size : node->mSize,
                    offset > 0
                );
            }
        }
    }
}
