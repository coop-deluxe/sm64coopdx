#include "dynos.cpp.h"

extern "C" {
#include "include/moving_texture_macros.h"
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnarrowing"

  /////////////
 // Parsing //
/////////////

#define MOVTEX_SIZE_PER_TOKEN 4

#define movtex_constant(x) if (_Arg == #x) { return (s64) (x); }
static s64 ParseMovtexSymbolArg(GfxData* aGfxData, DataNode<Movtex>* aNode, u64& aTokenIndex) {
    const String& _Arg = aNode->mTokens[aTokenIndex++];

    // Integers
    bool integerFound = false;
    s64 integerValue = DynOS_Misc_ParseInteger(_Arg, &integerFound);
    if (integerFound) {
        return integerValue;
    }

    // texture constants
    movtex_constant(TEXTURE_WATER);
    movtex_constant(TEXTURE_MIST);
    movtex_constant(TEXTURE_JRB_WATER);
    movtex_constant(TEXTURE_UNK_WATER);
    movtex_constant(TEXTURE_LAVA);
    movtex_constant(TEX_QUICKSAND_SSL);
    movtex_constant(TEX_PYRAMID_SAND_SSL);
    movtex_constant(TEX_YELLOW_TRI_TTC);
    movtex_constant(ROTATE_CLOCKWISE);
    movtex_constant(ROTATE_COUNTER_CLOCKWISE);

    // Other constants
    movtex_constant(NULL);

    // Unknown
    PrintDataError("  ERROR: Unknown movtex arg: %s", _Arg.begin());
    return 0;
}

#define movtex_symbol_0(symb)                    \
    if (_Symbol == #symb) {                      \
        Movtex _Mt[] = { symb() };               \
        memcpy(aHead, _Mt, sizeof(_Mt));         \
        aHead += (sizeof(_Mt) / sizeof(_Mt[0])); \
        return;                                  \
    }

#define movtex_symbol_1(symb)                                           \
    if (_Symbol == #symb) {                                             \
        s64 _Arg0 = ParseMovtexSymbolArg(aGfxData, aNode, aTokenIndex); \
        Movtex _Mt[] = { symb(_Arg0) };                                 \
        memcpy(aHead, _Mt, sizeof(_Mt));                                \
        aHead += (sizeof(_Mt) / sizeof(_Mt[0]));                        \
        return;                                                         \
    }

#define movtex_symbol_2(symb)                                           \
    if (_Symbol == #symb) {                                             \
        s64 _Arg0 = ParseMovtexSymbolArg(aGfxData, aNode, aTokenIndex); \
        s64 _Arg1 = ParseMovtexSymbolArg(aGfxData, aNode, aTokenIndex); \
        Movtex _Mt[] = { symb(_Arg0, _Arg1) };                          \
        memcpy(aHead, _Mt, sizeof(_Mt));                                \
        aHead += (sizeof(_Mt) / sizeof(_Mt[0]));                        \
        return;                                                         \
    }

#define movtex_symbol_5(symb)                                           \
    if (_Symbol == #symb) {                                             \
        s64 _Arg0 = ParseMovtexSymbolArg(aGfxData, aNode, aTokenIndex); \
        s64 _Arg1 = ParseMovtexSymbolArg(aGfxData, aNode, aTokenIndex); \
        s64 _Arg2 = ParseMovtexSymbolArg(aGfxData, aNode, aTokenIndex); \
        s64 _Arg3 = ParseMovtexSymbolArg(aGfxData, aNode, aTokenIndex); \
        s64 _Arg4 = ParseMovtexSymbolArg(aGfxData, aNode, aTokenIndex); \
        Movtex _Mt[] = { symb(_Arg0, _Arg1, _Arg2, _Arg3, _Arg4) };     \
        memcpy(aHead, _Mt, sizeof(_Mt));                                \
        aHead += (sizeof(_Mt) / sizeof(_Mt[0]));                        \
        return;                                                         \
    }

#define movtex_symbol_6(symb)                                           \
    if (_Symbol == #symb) {                                             \
        s64 _Arg0 = ParseMovtexSymbolArg(aGfxData, aNode, aTokenIndex); \
        s64 _Arg1 = ParseMovtexSymbolArg(aGfxData, aNode, aTokenIndex); \
        s64 _Arg2 = ParseMovtexSymbolArg(aGfxData, aNode, aTokenIndex); \
        s64 _Arg3 = ParseMovtexSymbolArg(aGfxData, aNode, aTokenIndex); \
        s64 _Arg4 = ParseMovtexSymbolArg(aGfxData, aNode, aTokenIndex); \
        s64 _Arg5 = ParseMovtexSymbolArg(aGfxData, aNode, aTokenIndex); \
        Movtex _Mt[] = { symb(_Arg0, _Arg1, _Arg2, _Arg3, _Arg4,        \
                              _Arg5) };                                 \
        memcpy(aHead, _Mt, sizeof(_Mt));                                \
        aHead += (sizeof(_Mt) / sizeof(_Mt[0]));                        \
        return;                                                         \
    }

#define movtex_symbol_8(symb)                                           \
    if (_Symbol == #symb) {                                             \
        s64 _Arg0 = ParseMovtexSymbolArg(aGfxData, aNode, aTokenIndex); \
        s64 _Arg1 = ParseMovtexSymbolArg(aGfxData, aNode, aTokenIndex); \
        s64 _Arg2 = ParseMovtexSymbolArg(aGfxData, aNode, aTokenIndex); \
        s64 _Arg3 = ParseMovtexSymbolArg(aGfxData, aNode, aTokenIndex); \
        s64 _Arg4 = ParseMovtexSymbolArg(aGfxData, aNode, aTokenIndex); \
        s64 _Arg5 = ParseMovtexSymbolArg(aGfxData, aNode, aTokenIndex); \
        s64 _Arg6 = ParseMovtexSymbolArg(aGfxData, aNode, aTokenIndex); \
        s64 _Arg7 = ParseMovtexSymbolArg(aGfxData, aNode, aTokenIndex); \
        Movtex _Mt[] = { symb(_Arg0, _Arg1, _Arg2, _Arg3, _Arg4,        \
                              _Arg5, _Arg6, _Arg7) };                   \
        memcpy(aHead, _Mt, sizeof(_Mt));                                \
        aHead += (sizeof(_Mt) / sizeof(_Mt[0]));                        \
        return;                                                         \
    }

static void ParseMovtexSymbol(GfxData* aGfxData, DataNode<Movtex>* aNode, Movtex*& aHead, u64& aTokenIndex, Array<u64>& aSwitchNodes) {
    const String& _Symbol = aNode->mTokens[aTokenIndex++];

    movtex_symbol_1(MOV_TEX_INIT_LOAD);
    movtex_symbol_2(MOV_TEX_4_BOX_TRIS);
    movtex_symbol_1(MOV_TEX_DEFINE);
    movtex_symbol_1(MOV_TEX_SPD);
    movtex_symbol_1(MOV_TEX_ROT_SPEED);
    movtex_symbol_1(MOV_TEX_ROT_SCALE);
    movtex_symbol_1(MOV_TEX_ROT);
    movtex_symbol_1(MOV_TEX_ALPHA);
    movtex_symbol_5(MOV_TEX_TRIS);
    movtex_symbol_8(MOV_TEX_ROT_TRIS);
    movtex_symbol_6(MOV_TEX_LIGHT_TRIS);
    movtex_symbol_0(MOV_TEX_END);
    movtex_symbol_0(MOV_TEX_ROT_END);

    // Integers
    s32 x;
    if ((_Symbol[1] == 'x' && sscanf(_Symbol.begin(), "%x", &x) == 1) || (sscanf(_Symbol.begin(), "%d", &x) == 1)) {
        Movtex _Mt[] = { (s16)x };
        memcpy(aHead, _Mt, sizeof(_Mt));
        aHead += (sizeof(_Mt) / sizeof(_Mt[0]));
        return;
    }

    // Unknown
    PrintDataError("  ERROR: Unknown movtex symbol: %s", _Symbol.begin());
}

DataNode<Movtex>* DynOS_Movtex_Parse(GfxData* aGfxData, DataNode<Movtex>* aNode, bool aDisplayPercent) {
    if (aNode->mData) return aNode;

    // Movtex data
    aNode->mData = New<Movtex>(aNode->mTokens.Count() * MOVTEX_SIZE_PER_TOKEN);
    Movtex* _Head = aNode->mData;
    Array<u64> _SwitchNodes;
    for (u64 _TokenIndex = 0; _TokenIndex < aNode->mTokens.Count();) { // Don't increment _TokenIndex here!
        ParseMovtexSymbol(aGfxData, aNode, _Head, _TokenIndex, _SwitchNodes);
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

void DynOS_Movtex_Write(BinFile* aFile, GfxData* aGfxData, DataNode<Movtex> *aNode) {
    if (!aNode->mData) return;

    // Name
    aFile->Write<u8>(DATA_TYPE_MOVTEX);
    aNode->mName.Write(aFile);

    // Data
    aFile->Write<u32>(aNode->mSize);
    for (u32 i = 0; i != aNode->mSize; ++i) {
        aFile->Write<Movtex>(aNode->mData[i]);
    }
}

  /////////////
 // Reading //
/////////////

DataNode<Movtex>* DynOS_Movtex_Load(BinFile *aFile, GfxData *aGfxData) {
    DataNode<Movtex> *_Node = New<DataNode<Movtex>>();

    // Name
    _Node->mName.Read(aFile);

    // Data
    _Node->mSize = aFile->Read<u32>();
    _Node->mData = New<Movtex>(_Node->mSize);
    for (u32 i = 0; i != _Node->mSize; ++i) {
        _Node->mData[i] = aFile->Read<Movtex>();
    }

    // Add it
    if (aGfxData != NULL) {
        aGfxData->mMovtexs.Add(_Node);
    }

    return _Node;
}
