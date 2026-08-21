#include "dynos.cpp.h"
extern "C" {
#include "macros.h"
#include "sm64.h"
#include "geo_commands.h"
#include "engine/geo_layout.h"
#include "game/camera.h"
#include "game/envfx_snow.h"
#include "game/paintings.h"
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnarrowing"

  /////////////
 // Parsing //
/////////////

#define GEO_LAYOUT_SIZE_PER_TOKEN 4

#define geo_constant(x) if (_Arg == #x) { return (s64) (x); }

static s64 DynOS_Geo_ParseConstants(const String& _Arg, bool* found) {
    *found = true;

    // Layer constants
    geo_constant(LAYER_FORCE);
    geo_constant(LAYER_OPAQUE);
    geo_constant(LAYER_OPAQUE_DECAL);
    geo_constant(LAYER_OPAQUE_INTER);
    geo_constant(LAYER_ALPHA);
    geo_constant(LAYER_TRANSPARENT);
    geo_constant(LAYER_TRANSPARENT_DECAL);
    geo_constant(LAYER_TRANSPARENT_INTER);

    // Background constants
    geo_constant(BACKGROUND_OCEAN_SKY);
    geo_constant(BACKGROUND_FLAMING_SKY);
    geo_constant(BACKGROUND_UNDERWATER_CITY);
    geo_constant(BACKGROUND_BELOW_CLOUDS);
    geo_constant(BACKGROUND_SNOW_MOUNTAINS);
    geo_constant(BACKGROUND_DESERT);
    geo_constant(BACKGROUND_HAUNTED);
    geo_constant(BACKGROUND_GREEN_SKY);
    geo_constant(BACKGROUND_ABOVE_CLOUDS);
    geo_constant(BACKGROUND_PURPLE_SKY);

    // Shadow constants
    geo_constant(SHADOW_CIRCLE_9_VERTS);
    geo_constant(SHADOW_CIRCLE_4_VERTS);
    geo_constant(SHADOW_CIRCLE_4_VERTS_FLAT_UNUSED);
    geo_constant(SHADOW_SQUARE_PERMANENT);
    geo_constant(SHADOW_SQUARE_SCALABLE);
    geo_constant(SHADOW_SQUARE_TOGGLABLE);
    geo_constant(SHADOW_RECTANGLE_HARDCODED_OFFSET);
    geo_constant(SHADOW_CIRCLE_PLAYER);
    geo_constant(SHADOW_SPIKE_EXT);

    // Envfx constants
    geo_constant(ENVFX_MODE_NONE);
    geo_constant(ENVFX_SNOW_NORMAL);
    geo_constant(ENVFX_SNOW_WATER);
    geo_constant(ENVFX_SNOW_BLIZZARD);
    geo_constant(ENVFX_BUBBLE_START);
    geo_constant(ENVFX_FLOWERS);
    geo_constant(ENVFX_LAVA_BUBBLES);
    geo_constant(ENVFX_WHIRLPOOL_BUBBLES);
    geo_constant(ENVFX_JETSTREAM_BUBBLES);


    // Camera constants
    geo_constant(CAMERA_MODE_NONE);
    geo_constant(CAMERA_MODE_RADIAL);
    geo_constant(CAMERA_MODE_OUTWARD_RADIAL);
    geo_constant(CAMERA_MODE_BEHIND_MARIO);
    geo_constant(CAMERA_MODE_CLOSE);
    geo_constant(CAMERA_MODE_C_UP);
    geo_constant(CAMERA_MODE_WATER_SURFACE);
    geo_constant(CAMERA_MODE_SLIDE_HOOT);
    geo_constant(CAMERA_MODE_INSIDE_CANNON);
    geo_constant(CAMERA_MODE_BOSS_FIGHT);
    geo_constant(CAMERA_MODE_PARALLEL_TRACKING);
    geo_constant(CAMERA_MODE_FIXED);
    geo_constant(CAMERA_MODE_8_DIRECTIONS);
    geo_constant(CAMERA_MODE_FREE_ROAM);
    geo_constant(CAMERA_MODE_SPIRAL_STAIRS);

    // Other constants
    geo_constant(NULL);
    geo_constant(SCREEN_WIDTH);
    geo_constant(SCREEN_HEIGHT);
    geo_constant(SCREEN_WIDTH/2);
    geo_constant(SCREEN_HEIGHT/2);

    *found = false;
    return 0;
}

static s64 ParseGeoSymbolArg(GfxData* aGfxData, DataNode<GeoLayout>* aNode, u64& aTokenIndex) {
    const String& _Arg = aNode->mTokens[aTokenIndex++];

    // Integers
    bool integerFound = false;
    s64 integerValue = DynOS_Misc_ParseInteger(_Arg, &integerFound);
    if (integerFound) {
        return integerValue;
    }

    // Built-in functions
    const void *_FunctionPtr = DynOS_Builtin_Func_GetFromName(_Arg.begin(), FUNCTION_GEO);
    if (_FunctionPtr != NULL) {
        return (s64) _FunctionPtr;
    }
    String error = DynOS_Builtin_Func_CheckMisuse(_Arg.begin(), FUNCTION_GEO);
    if (!error.Empty()) {
        PrintDataError("  ERROR: %s", error.begin());
        return 0;
    }

    // Constants
    bool constantFound = false;
    s64 constantValue = DynOS_Geo_ParseConstants(_Arg, &constantFound);
    if (constantFound) {
        return constantValue;
    }

    // Display lists
    {
        auto _Node = aGfxData->mDisplayLists.Find(_Arg, aGfxData->mDataIdentifier);
        if (_Node) {
            return (s64) DynOS_Gfx_Parse(aGfxData, _Node);
        }
    }

    // Geo layouts
    {
        auto _Node = aGfxData->mGeoLayouts.Find(_Arg, aGfxData->mDataIdentifier);
        if (_Node) {
            auto geoNode = DynOS_Geo_Parse(aGfxData, _Node, false);
            aGfxData->mChildGeoLayouts.Add(geoNode);
            return (s64) geoNode->mData;
        }
    }

    // Complex
    s32 a;
    s32 b;
    if (sscanf(_Arg.begin(), "PAINTING_ID(%d,%d)", &a, &b) == 2) {
        return PAINTING_ID(a, b);
    }

    // Recursive descent parsing
    bool rdSuccess = false;
    s64 rdValue = DynOS_RecursiveDescent_Parse(_Arg.begin(), &rdSuccess, DynOS_Geo_ParseConstants);
    if (rdSuccess) {
        return rdValue;
    }

    // Unknown
    PrintDataError("  ERROR: Unknown geo arg: %s", _Arg.begin());
    return 0;
}

static void ParseGeoSymbol(GfxData* aGfxData, DataNode<GeoLayout>* aNode, GeoLayout*& aHead, u64& aTokenIndex, Array<u64>& aSwitchNodes) {
    const String& _Symbol = aNode->mTokens[aTokenIndex++];

    // Restore context after each command if inside a switch
    if (!aSwitchNodes.Empty() && !aGfxData->mGeoNodeStack.Empty()) {
        aGfxData->mGfxContext = aGfxData->mGeoNodeStack[aGfxData->mGeoNodeStack.Count() - 1];
    }

    // Simple symbols
    // Uses macro iterators to dynamically handle the correct number of parameters
#define HANDLE_PARAM(paramNum) s64 _Arg##paramNum = ParseGeoSymbolArg(aGfxData, aNode, aTokenIndex);
#define GET_ARG(paramNum) _Arg##paramNum
#define CALL_SYMB(symb, ...) symb(__VA_ARGS__)
#define define_geo_symbol(symb, params, n, ...)                       \
if (_Symbol == #symb) {                                               \
    REPEAT(HANDLE_PARAM, params);                                     \
    if (n != 0) { aGfxData->mPointerList.Add(aHead + n); }            \
    GeoLayout _Gl[] = { CALL_SYMB(symb, LIST_ARGS(GET_ARG, params)) };\
    memcpy(aHead, _Gl, sizeof(_Gl));                                  \
    aHead += (sizeof(_Gl) / sizeof(_Gl[0]));                          \
    return;                                                           \
}
#define define_geo_symbol_manual(...)
#include "geo_symbols.h"
#undef HANDLE_PARAM
#undef GET_ARG
#undef CALL_SYMB
#undef define_geo_symbol
#undef define_geo_symbol_manual

    // Geo function node
    if (_Symbol == "GEO_ASM") {
        s64 _Arg0 = ParseGeoSymbolArg(aGfxData, aNode, aTokenIndex);
        const String& _Arg1 = aNode->mTokens[aTokenIndex++];

        const void *_FunctionPtr = DynOS_Builtin_Func_GetFromName(_Arg1.begin(), FUNCTION_GEO);
        if (_FunctionPtr != NULL) {
            aGfxData->mPointerList.Add(aHead + 1);
            GeoLayout _Gl[] = { GEO_ASM(_Arg0, _FunctionPtr) };
            memcpy(aHead, _Gl, sizeof(_Gl));
            aHead += (sizeof(_Gl) / sizeof(_Gl[0]));
        } else {
            String error = DynOS_Builtin_Func_CheckMisuse(_Arg1.begin(), FUNCTION_GEO);
            if (!error.Empty()) {
                PrintDataError("  ERROR: %s", error.begin());
                return;
            }
            u32 _FuncIndex = DynOS_Lua_RememberVariable(aGfxData, aHead + 1, _Arg1);
            GeoLayout _Gl[] = { GEO_ASM_EXT(_Arg0, _FuncIndex) };
            memcpy(aHead, _Gl, sizeof(_Gl));
            aHead += (sizeof(_Gl) / sizeof(_Gl[0]));
        }
        return;
    }

    // Switch node
    if (_Symbol == "GEO_SWITCH_CASE") {

        // Start a switch
        aSwitchNodes.Add(0);

        s64 _Arg0 = ParseGeoSymbolArg(aGfxData, aNode, aTokenIndex);
        const String& _Arg1 = aNode->mTokens[aTokenIndex++];

        const void *_FunctionPtr = DynOS_Builtin_Func_GetFromName(_Arg1.begin(), FUNCTION_GEO);
        if (_FunctionPtr != NULL) {
            aGfxData->mPointerList.Add(aHead + 1);
            GeoLayout _Gl[] = { GEO_SWITCH_CASE(_Arg0, _FunctionPtr) };
            memcpy(aHead, _Gl, sizeof(_Gl));
            aHead += (sizeof(_Gl) / sizeof(_Gl[0]));
        } else {
            String error = DynOS_Builtin_Func_CheckMisuse(_Arg1.begin(), FUNCTION_GEO);
            if (!error.Empty()) {
                PrintDataError("  ERROR: %s", error.begin());
                return;
            }
            u32 _FuncIndex = DynOS_Lua_RememberVariable(aGfxData, aHead + 1, _Arg1);
            GeoLayout _Gl[] = { GEO_SWITCH_CASE_EXT(_Arg0, _FuncIndex) };
            memcpy(aHead, _Gl, sizeof(_Gl));
            aHead += (sizeof(_Gl) / sizeof(_Gl[0]));
        }
        return;
    }

    // Open node
    if (_Symbol == "GEO_OPEN_NODE") {

        // We're inside a switch
        if (!aSwitchNodes.Empty()) {
            aSwitchNodes[aSwitchNodes.Count() - 1]++;
        }

        // Push context
        aGfxData->mGeoNodeStack.Add(aGfxData->mGfxContext);

        *(aHead++) = GEO_OPEN_NODE();
        return;
    }

    // Close node
    if (_Symbol == "GEO_CLOSE_NODE") {

        // Are we still inside a switch?
        if (!aSwitchNodes.Empty()) {
            aSwitchNodes[aSwitchNodes.Count() - 1]--;

            // We're not anymore
            if (aSwitchNodes[aSwitchNodes.Count() - 1] == 0) {
                aSwitchNodes.Pop();
            }
        }

        // Pop context
        if (!aGfxData->mGeoNodeStack.Empty()) {
            aGfxData->mGfxContext = aGfxData->mGeoNodeStack[aGfxData->mGeoNodeStack.Count() - 1];
            aGfxData->mGeoNodeStack.Pop();
        }

        *(aHead++) = GEO_CLOSE_NODE();
        return;
    }

    // Background
    if (_Symbol == "GEO_BACKGROUND") {
        // check if this is a custom background
        const String& backgroundName = aNode->mTokens[aTokenIndex];
        auto node = aGfxData->mTextureLists.Find(backgroundName, aGfxData->mDataIdentifier);
        if (node) {
            // custom background cmd
            node = DynOS_TexList_Parse(aGfxData, node);
            aTokenIndex++; // skip background name
            s64 func = ParseGeoSymbolArg(aGfxData, aNode, aTokenIndex);
            aGfxData->mPointerList.Add(aHead + 1);
            aGfxData->mPointerList.Add(aHead + 2);
            GeoLayout _Gl[] = { GEO_BACKGROUND_EXT(node, func) };
            memcpy(aHead, _Gl, sizeof(_Gl));
            aHead += (sizeof(_Gl) / sizeof(_Gl[0]));
        } else {
            // regular background cmd
            s64 background = ParseGeoSymbolArg(aGfxData, aNode, aTokenIndex);
            s64 func = ParseGeoSymbolArg(aGfxData, aNode, aTokenIndex);
            aGfxData->mPointerList.Add(aHead + 1);
            GeoLayout _Gl[] = { GEO_BACKGROUND(background, func) };
            memcpy(aHead, _Gl, sizeof(_Gl));
            aHead += (sizeof(_Gl) / sizeof(_Gl[0]));
        }
        return;
    }

    // Unknown
    PrintDataError("  ERROR: Unknown geo symbol: %s", _Symbol.begin());
}

DataNode<GeoLayout>* DynOS_Geo_Parse(GfxData* aGfxData, DataNode<GeoLayout>* aNode, bool aDisplayPercent) {
    if (aNode->mData) return aNode;

    // Geo layout data
    aNode->mData = New<GeoLayout>(aNode->mTokens.Count() * GEO_LAYOUT_SIZE_PER_TOKEN);
    GeoLayout* _Head = aNode->mData;
    Array<u64> _SwitchNodes;
    for (u64 _TokenIndex = 0; _TokenIndex < aNode->mTokens.Count();) { // Don't increment _TokenIndex here!
        ParseGeoSymbol(aGfxData, aNode, _Head, _TokenIndex, _SwitchNodes);
        if (aDisplayPercent && aGfxData->mErrorCount == 0) { PrintNoNewLine("%3d%%\b\b\b\b", (s32) (_TokenIndex * 100) / aNode->mTokens.Count()); }
    }
    if (aDisplayPercent && aGfxData->mErrorCount == 0) { Print("100%%"); }
    aNode->mSize = (u32)(_Head - aNode->mData);
    aNode->mLoadIndex = aGfxData->mLoadIndex++;
    return aNode;
}

#pragma GCC diagnostic pop

  /////////////
 // Writing //
/////////////

void DynOS_Geo_Write(BinFile *aFile, GfxData *aGfxData, DataNode<GeoLayout> *aNode) {
    if (!aNode->mData) return;

    // Header
    aFile->Write<u8>(DATA_TYPE_GEO_LAYOUT);
    aNode->mName.Write(aFile);

    // Data
    aFile->Write<u32>(aNode->mSize);
    for (u32 i = 0; i != aNode->mSize; ++i) {
        GeoLayout *_Head = &aNode->mData[i];
        if (aGfxData->mPointerList.Find((void *) _Head) != -1) {
            DynOS_Pointer_Write(aFile, (const void *) (*_Head), aGfxData, FUNCTION_GEO);
        } else if (aGfxData->mLuaPointerList.Find((void *) _Head) != -1) {
            DynOS_Pointer_Lua_Write(aFile, *(u32 *)_Head, aGfxData);
        } else {
            aFile->Write<u32>(*((u32 *) _Head));
        }
    }
}

  /////////////
 // Reading //
/////////////

static bool DynOS_Geo_Validate(DataNode<GeoLayout> *aNode) {
    for (u32 i = 0; i < aNode->mSize;) {

        // Check the command header and validate its length.
        u8 *commandBytes = (u8 *)&aNode->mData[i];
        if (commandBytes[0] >= GEO_CMD_COUNT) {
            return false;
        }
        u16 commandHeader = ((u16) commandBytes[0] << 8) | commandBytes[1];
        u32 cmdLengthWords = 0;
#define GET_ARG(paramNum) 0
#define CALL_SYMB(symb, ...) symb(__VA_ARGS__)
#define define_geo_symbol(symb, params, n, words, headerMask, headerValue)  \
if ((commandHeader & headerMask) == headerValue) {                          \
    cmdLengthWords = words;                                                 \
}
#define define_geo_symbol_manual(...) define_geo_symbol(__VA_ARGS__)
#include "geo_symbols.h"
#undef GET_ARG
#undef CALL_SYMB
#undef define_geo_symbol
#undef define_geo_symbol_manual

        assert(cmdLengthWords > 0);
        if (i + cmdLengthWords > aNode->mSize) {
            return false;
        }

        // Next command
        i += cmdLengthWords;
    }
    return true;
}

void DynOS_Geo_Load(BinFile *aFile, GfxData *aGfxData) {
    DataNode<GeoLayout> *_Node = New<DataNode<GeoLayout>>();

    // Name
    _Node->mName.Read(aFile);

    // Data
    _Node->mSize = aFile->Read<u32>();
    _Node->mData = New<GeoLayout>(_Node->mSize);
    for (u32 i = 0; i != _Node->mSize; ++i) {
        u32 _Value = aFile->Read<u32>();
        void *_Ptr = DynOS_Pointer_Load(aFile, aGfxData, _Value, FUNCTION_GEO, &_Node->mFlags);
        if (_Ptr) {
            _Node->mData[i] = (uintptr_t) _Ptr;
        } else {
            _Node->mData[i] = (uintptr_t) _Value;
        }
    }

    // Append if valid
    if (DynOS_Geo_Validate(_Node)) {
        aGfxData->mGeoLayouts.Add(_Node);
    }
}
