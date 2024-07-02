#include <map>
#include <set>
#include "dynos.cpp.h"
extern "C" {
#include "pc/gfx/gfx_rendering_api.h"
}

struct OverrideTexture {
    DataNode<TexData>* node;
    bool customTexture;
};

static std::map<const Texture*, struct OverrideTexture*>& DynosOverrideTextures() {
    static std::map<const Texture*, struct OverrideTexture*> sDynosOverrideTextures;
    return sDynosOverrideTextures;
}

static std::map<const Texture*, struct OverrideTexture*>& DynosOverrideLuaTextures() {
    static std::map<const Texture*, struct OverrideTexture*> sDynosOverrideLuaTextures;
    return sDynosOverrideLuaTextures;
}
static std::map<DataNode<TexData>*, struct OverrideTexture*>& DynosOverrideLuaTexData() {
    static std::map<DataNode<TexData>*, struct OverrideTexture*> sDynosOverrideLuaTexData;
    return sDynosOverrideLuaTexData;
}

// static set
static std::set<DataNode<TexData> *>& DynosValidTextures() {
    static std::set<DataNode<TexData> *> sDynosValidTextures;
    return sDynosValidTextures;
}

static Array<DataNode<TexData> *>& DynosScheduledInvalidTextures() {
    static Array<DataNode<TexData> *> sDynosScheduledInvalidTextures;
    return sDynosScheduledInvalidTextures;
}

static bool sDynosDumpTextureCache = false;

//
// Conversion
//

#define SCALE_5_8(VAL_) (((VAL_) * 0xFF) / 0x1F)
#define SCALE_8_5(VAL_) ((((VAL_) + 4) * 0x1F) / 0xFF)
#define SCALE_4_8(VAL_) ((VAL_) * 0x11)
#define SCALE_8_4(VAL_) ((VAL_) / 0x11)
#define SCALE_3_8(VAL_) ((VAL_) * 0x24)
#define SCALE_8_3(VAL_) ((VAL_) / 0x24)

static u8 *RGBA16_RGBA32(const u8 *aData, u64 aLength) {
    u8 *_Buffer = New<u8>(aLength * 2);
    u8 *pBuffer = _Buffer;
    for (u64 i = 0; i != aLength; i += 2) {
        u16 _Col  = (aData[i + 0] << 8) | aData[i + 1];
        u8  _Red  = (_Col >> 11) & 0x1F;
        u8  _Grn  = (_Col >>  6) & 0x1F;
        u8  _Blu  = (_Col >>  1) & 0x1F;
        u8  _Alp  = (_Col >>  0) & 0x01;
        *(pBuffer++) = (SCALE_5_8(_Red));
        *(pBuffer++) = (SCALE_5_8(_Grn));
        *(pBuffer++) = (SCALE_5_8(_Blu));
        *(pBuffer++) = (0xFF  *  (_Alp));
    }
    return _Buffer;
}

static u8 *RGBA32_RGBA32(const u8 *aData, u64 aLength) {
    u8 *_Buffer = New<u8>(aLength * 1);
    memcpy(_Buffer, aData, aLength);
    return _Buffer;
}

static u8 *IA4_RGBA32(const u8 *aData, u64 aLength) {
    u8 *_Buffer = New<u8>(aLength * 8);
    u8 *pBuffer = _Buffer;
    for (u64 i = 0; i != aLength; ++i) {
        u8 _Half0 = (aData[i] >> 4) & 0xF;
        *(pBuffer++) = (SCALE_3_8(_Half0 >> 1));
        *(pBuffer++) = (SCALE_3_8(_Half0 >> 1));
        *(pBuffer++) = (SCALE_3_8(_Half0 >> 1));
        *(pBuffer++) = (0xFF  *  (_Half0 &  1));

        u8 _Half1 = (aData[i] >> 0) & 0xF;
        *(pBuffer++) = (SCALE_3_8(_Half1 >> 1));
        *(pBuffer++) = (SCALE_3_8(_Half1 >> 1));
        *(pBuffer++) = (SCALE_3_8(_Half1 >> 1));
        *(pBuffer++) = (0xFF  *  (_Half1 &  1));
    }
    return _Buffer;
}

static u8 *IA8_RGBA32(const u8 *aData, u64 aLength) {
    u8 *_Buffer = New<u8>(aLength * 4);
    u8 *pBuffer = _Buffer;
    for (u64 i = 0; i != aLength; ++i) {
        u8 _Col   = (aData[i] >> 4) & 0xF;
        u8 _Alp   = (aData[i] >> 0) & 0xF;
        *(pBuffer++) = (SCALE_4_8(_Col));
        *(pBuffer++) = (SCALE_4_8(_Col));
        *(pBuffer++) = (SCALE_4_8(_Col));
        *(pBuffer++) = (SCALE_4_8(_Alp));
    }
    return _Buffer;
}

static u8 *IA16_RGBA32(const u8 *aData, u64 aLength) {
    u8 *_Buffer = New<u8>(aLength * 2);
    u8 *pBuffer = _Buffer;
    for (u64 i = 0; i != aLength; i += 2) {
        u8 _Col   = aData[i + 0];
        u8 _Alp   = aData[i + 1];
        *(pBuffer++) = (_Col);
        *(pBuffer++) = (_Col);
        *(pBuffer++) = (_Col);
        *(pBuffer++) = (_Alp);
    }
    return _Buffer;
}

static u8 *CI4_RGBA32(const u8 *aData, u64 aLength, const u8 *aPalette) {
    if (!aPalette) { return NULL; }
    u8 *_Buffer = New<u8>(aLength * 8);
    u8 *pBuffer = _Buffer;
    for (u64 i = 0; i != aLength; ++i) {
        u8  _Idx0 = (aData[i] >> 4) & 0xF;
        u16 _Col0 = (aPalette[_Idx0 * 2 + 0] << 8) | aPalette[_Idx0 * 2 + 1];
        u8  _Red0 = (_Col0 >> 11) & 0x1F;
        u8  _Grn0 = (_Col0 >>  6) & 0x1F;
        u8  _Blu0 = (_Col0 >>  1) & 0x1F;
        u8  _Alp0 = (_Col0 >>  0) & 0x01;
        *(pBuffer++) = (SCALE_5_8(_Red0));
        *(pBuffer++) = (SCALE_5_8(_Grn0));
        *(pBuffer++) = (SCALE_5_8(_Blu0));
        *(pBuffer++) = (0xFF  *  (_Alp0));

        u8  _Idx1 = (aData[i] >> 0) & 0xF;
        u16 _Col1 = (aPalette[_Idx1 * 2 + 0] << 8) | aPalette[_Idx1 * 2 + 1];
        u8  _Red1 = (_Col1 >> 11) & 0x1F;
        u8  _Grn1 = (_Col1 >>  6) & 0x1F;
        u8  _Blu1 = (_Col1 >>  1) & 0x1F;
        u8  _Alp1 = (_Col1 >>  0) & 0x01;
        *(pBuffer++) = (SCALE_5_8(_Red1));
        *(pBuffer++) = (SCALE_5_8(_Grn1));
        *(pBuffer++) = (SCALE_5_8(_Blu1));
        *(pBuffer++) = (0xFF  *  (_Alp1));
    }
    return _Buffer;
}

static u8 *CI8_RGBA32(const u8 *aData, u64 aLength, const u8 *aPalette) {
    if (!aPalette) { return NULL; }
    u8 *_Buffer = New<u8>(aLength * 4);
    u8 *pBuffer = _Buffer;
    for (u64 i = 0; i != aLength; ++i) {
        u8  _Idx  = aData[i];
        u16 _Col  = (aPalette[_Idx * 2 + 0] << 8) | aPalette[_Idx * 2 + 1];
        u8  _Red  = (_Col >> 11) & 0x1F;
        u8  _Grn  = (_Col >>  6) & 0x1F;
        u8  _Blu  = (_Col >>  1) & 0x1F;
        u8  _Alp  = (_Col >>  0) & 0x01;
        *(pBuffer++) = (SCALE_5_8(_Red));
        *(pBuffer++) = (SCALE_5_8(_Grn));
        *(pBuffer++) = (SCALE_5_8(_Blu));
        *(pBuffer++) = (0xFF  *  (_Alp));
    }
    return _Buffer;
}

static u8 *I4_RGBA32(const u8 *aData, u64 aLength) {
    u8 *_Buffer = New<u8>(aLength * 8);
    u8 *pBuffer = _Buffer;
    for (u64 i = 0; i != aLength; ++i) {
        u8 _Half0 = (aData[i] >> 4) & 0xF;
        *(pBuffer++) = (SCALE_4_8(_Half0));
        *(pBuffer++) = (SCALE_4_8(_Half0));
        *(pBuffer++) = (SCALE_4_8(_Half0));
        *(pBuffer++) = (255);

        u8 _Half1 = (aData[i] >> 0) & 0xF;
        *(pBuffer++) = (SCALE_4_8(_Half1));
        *(pBuffer++) = (SCALE_4_8(_Half1));
        *(pBuffer++) = (SCALE_4_8(_Half1));
        *(pBuffer++) = (255);
    }
    return _Buffer;
}

static u8 *I8_RGBA32(const u8 *aData, u64 aLength) {
    u8 *_Buffer = New<u8>(aLength * 4);
    u8 *pBuffer = _Buffer;
    for (u64 i = 0; i != aLength; ++i) {
        *(pBuffer++) = (aData[i]);
        *(pBuffer++) = (aData[i]);
        *(pBuffer++) = (aData[i]);
        *(pBuffer++) = (255);
    }
    return _Buffer;
}

u8 *DynOS_Tex_ConvertToRGBA32(const u8 *aData, u64 aLength, s32 aFormat, s32 aSize, const u8 *aPalette) {
    switch   ((aFormat       << 8) | aSize       ) {
        case ((G_IM_FMT_RGBA << 8) | G_IM_SIZ_16b): return RGBA16_RGBA32(aData, aLength);
        case ((G_IM_FMT_RGBA << 8) | G_IM_SIZ_32b): return RGBA32_RGBA32(aData, aLength);
        case ((G_IM_FMT_IA   << 8) | G_IM_SIZ_4b ): return IA4_RGBA32   (aData, aLength);
        case ((G_IM_FMT_IA   << 8) | G_IM_SIZ_8b ): return IA8_RGBA32   (aData, aLength);
        case ((G_IM_FMT_IA   << 8) | G_IM_SIZ_16b): return IA16_RGBA32  (aData, aLength);
        case ((G_IM_FMT_CI   << 8) | G_IM_SIZ_4b ): return CI4_RGBA32   (aData, aLength, aPalette);
        case ((G_IM_FMT_CI   << 8) | G_IM_SIZ_8b ): return CI8_RGBA32   (aData, aLength, aPalette);
        case ((G_IM_FMT_I    << 8) | G_IM_SIZ_4b ): return I4_RGBA32    (aData, aLength);
        case ((G_IM_FMT_I    << 8) | G_IM_SIZ_8b ): return I8_RGBA32    (aData, aLength);
    }
    return NULL;
}

//
// Upload
//

typedef struct GfxRenderingAPI GRAPI;
static void DynOS_Tex_Upload(DataNode<TexData> *aNode, GRAPI *aGfxRApi, s32 aTile, s32 aTexId) {
    aGfxRApi->select_texture(aTile, aTexId);
    aGfxRApi->upload_texture(aNode->mData->mRawData.begin(), aNode->mData->mRawWidth, aNode->mData->mRawHeight);
    aNode->mData->mUploaded = true;
}

//
// Cache
//

struct THN {
    struct THN *mNext;
    const void *mAddr; // Contains the pointer to the DataNode<TexData> struct, NOT the actual texture data
    u8 mFmt, mSiz;
    s32 mTexId;
    u8 mCms, mCmt;
    bool mLInf;
};

static bool DynOS_Tex_Cache(THN **aOutput, DataNode<TexData> *aNode, s32 aTile, GRAPI *aGfxRApi, THN **aHashMap, THN *aPool, u32 *aPoolPos, u32 aPoolSize) {

    // Find texture in cache
    uintptr_t _Hash = ((uintptr_t) aNode) & ((aPoolSize * 2) - 1);
    THN **_Node = &(aHashMap[_Hash]);
    while ((*_Node) != NULL && ((*_Node) - aPool) < (*aPoolPos)) {
        if ((*_Node)->mAddr == (const void *) aNode) {
            aGfxRApi->select_texture(aTile, (*_Node)->mTexId);
            if (!aNode->mData->mUploaded) {
                DynOS_Tex_Upload(aNode, aGfxRApi, aTile, (*_Node)->mTexId);
            }
            (*aOutput) = (*_Node);
            return true;
        }
        _Node = &(*_Node)->mNext;
    }

    // If cache is full, clear cache
    if ((*aPoolPos) == aPoolSize) {
        (*aPoolPos) = 0;
        _Node = &aHashMap[_Hash];
    }

    // Add new texture to cache
    (*_Node) = &aPool[(*aPoolPos)++];
    if (!(*_Node)->mAddr) {
        (*_Node)->mTexId = aGfxRApi->new_texture();
    }
    aGfxRApi->select_texture(aTile, (*_Node)->mTexId);
    aGfxRApi->set_sampler_parameters(aTile, false, 0, 0);
    (*_Node)->mCms  = 0;
    (*_Node)->mCmt  = 0;
    (*_Node)->mLInf = false;
    (*_Node)->mNext = NULL;
    (*_Node)->mAddr = aNode;
    (*_Node)->mFmt  = G_IM_FMT_RGBA;
    (*_Node)->mSiz  = G_IM_SIZ_32b;
    (*aOutput)      = (*_Node);
    return false;
}

//
// Make textures valid/invalid
//

void DynOS_Tex_Valid(GfxData* aGfxData) {
    for (auto &_Texture : aGfxData->mTextures) {
        DynosValidTextures().insert(_Texture);
    }
}

void DynOS_Tex_Invalid(GfxData* aGfxData) {
    auto& schedule = DynosScheduledInvalidTextures();
    for (auto &_Texture : aGfxData->mTextures) {
        schedule.Add(_Texture);
    }
}

void DynOS_Tex_Update() {
    auto& schedule = DynosScheduledInvalidTextures();
    if (schedule.Count() == 0) { return; }
    for (auto &_Texture : schedule) {
        DynosValidTextures().erase(_Texture);
    }
    schedule.Clear();
}

//
// Import
//

static DataNode<TexData> *DynOS_Tex_RetrieveNode(void *aPtr) {
    {
        auto _LuaOverrideTexture = DynosOverrideLuaTextures()[(const Texture*)aPtr];
        if (_LuaOverrideTexture && _LuaOverrideTexture->node) {
            return _LuaOverrideTexture->node;
        }
        auto _LuaOverrideTexData = DynosOverrideLuaTexData()[(DataNode<TexData>*)aPtr];
        if (_LuaOverrideTexData && _LuaOverrideTexData->node) {
            return _LuaOverrideTexData->node;
        }
    }

    auto _Override = DynosOverrideTextures()[(const Texture*)aPtr];
    if (_Override && _Override->node) {
        return _Override->node;
    }

    auto& _ValidTextures = DynosValidTextures();
    if (_ValidTextures.find((DataNode<TexData>*)aPtr) != _ValidTextures.end()) {
        return (DataNode<TexData>*)aPtr;
    }
    return NULL;
}

static bool DynOS_Tex_Import_Typed(THN **aOutput, void *aPtr, s32 aTile, GRAPI *aGfxRApi, THN **aHashMap, THN *aPool, u32 *aPoolPos, u32 aPoolSize) {
    DataNode<TexData> *_Node = DynOS_Tex_RetrieveNode(aPtr);
    if (_Node) {
        if (!DynOS_Tex_Cache(aOutput, _Node, aTile, aGfxRApi, aHashMap, aPool, aPoolPos, aPoolSize)) {
            DynOS_Tex_Upload(_Node, aGfxRApi, aTile, (*aOutput)->mTexId);
        }
        return true;
    }
    return false;
}

bool DynOS_Tex_Import(void **aOutput, void *aPtr, s32 aTile, void *aGfxRApi, void **aHashMap, void *aPool, u32 *aPoolPos, u32 aPoolSize) {
    return DynOS_Tex_Import_Typed(
        (THN **)  aOutput,
        (void *)  aPtr,
        (s32)     aTile,
        (GRAPI *) aGfxRApi,
        (THN **)  aHashMap,
        (THN *)   aPool,
        (u32 *)   aPoolPos,
        (u32)     aPoolSize
    );
}

  /////////////////////
 // Custom Textures //
/////////////////////

static Array<Pair<const char*, DataNode<TexData>*>>& DynosCustomTexs() {
    static Array<Pair<const char*, DataNode<TexData>*>> sDynosCustomTexs;
    return sDynosCustomTexs;
}

void DynOS_Tex_Activate(DataNode<TexData>* aNode, bool aCustomTexture) {
    if (!aNode) { return; }

    // check for duplicates
    auto& _DynosCustomTexs = DynosCustomTexs();
    bool _HasCustomTex = false;
    for (s32 i = 0; i < _DynosCustomTexs.Count(); ++i) {
        if (!strcmp(_DynosCustomTexs[i].first, aNode->mName.begin())) {
            _HasCustomTex = true;
            break;
        }
    }

    // Override texture
    const Texture* _BuiltinTex = DynOS_Builtin_Tex_GetFromName(aNode->mName.begin());
    if (_BuiltinTex) {
        auto& _DynosOverrideTextures = DynosOverrideTextures();
        if (_DynosOverrideTextures[_BuiltinTex] == NULL || !_DynosOverrideTextures[_BuiltinTex]->customTexture) {
            struct OverrideTexture* _Override = new OverrideTexture();
            _Override->customTexture = aCustomTexture;
            _Override->node = aNode;
            _DynosOverrideTextures[_BuiltinTex] = _Override;
        }
    }

    // Add to custom textures
    if (!_HasCustomTex && aCustomTexture) {
        _DynosCustomTexs.Add({ aNode->mName.begin(), aNode });
    }

    // Add to valid
    DynosValidTextures().insert(aNode);
}

void DynOS_Tex_Deactivate(DataNode<TexData>* aNode) {
    if (!aNode) { return; }
    aNode->mData->mUploaded = false;

    // remove from custom textures
    auto& _DynosCustomTexs = DynosCustomTexs();
    for (s32 i = 0; i < _DynosCustomTexs.Count(); ++i) {
        if (_DynosCustomTexs[i].second == aNode) {
            _DynosCustomTexs.Remove(i);
            i--;
        }
    }

    // un-override texture
    const Texture* _BuiltinTex = DynOS_Builtin_Tex_GetFromName(aNode->mName.begin());
    auto& _DynosOverrideTextures = DynosOverrideTextures();
    if (_BuiltinTex) {
        auto _Override = _DynosOverrideTextures[_BuiltinTex];
        if (_Override && _Override->node == aNode) {
            _DynosOverrideTextures.erase(_BuiltinTex);
        }
    }

    // Remove from valid
    auto& _Schedule = DynosScheduledInvalidTextures();
    _Schedule.Add(aNode);
}

void DynOS_Tex_AddCustom(const SysPath &aFilename, const char *aTexName) {
    auto& _DynosCustomTexs = DynosCustomTexs();

    // check for duplicates
    for (s32 i = 0; i < _DynosCustomTexs.Count(); ++i) {
        if (!strcmp(_DynosCustomTexs[i].first, aTexName)) {
            return;
        }
    }

    // Allocate name
    u16 texLen = strlen(aTexName);
    char* _TexName = (char*)calloc(1, sizeof(char) * (texLen + 1));
    strcpy(_TexName, aTexName);

    // Load
    SysPath _PackFolder = "";
    DataNode<TexData>* _Node = DynOS_Tex_LoadFromBinary(_PackFolder, aFilename, _TexName, false);
    free(_TexName);
    if (_Node) {
        DynOS_Tex_Activate(_Node, true);
    }
}

bool DynOS_Tex_Get(const char* aTexName, struct TextureInfo* aOutTexInfo) {
    #define CONVERT_TEXINFO() { \
        /* translate bit size */ \
        switch (_Data->mRawSize) { \
            case G_IM_SIZ_8b:  aOutTexInfo->bitSize = 8; break; \
            case G_IM_SIZ_16b: aOutTexInfo->bitSize = 16; break; \
            case G_IM_SIZ_32b: aOutTexInfo->bitSize = 32; break; \
            default: return false; \
        } \
        aOutTexInfo->width   = _Data->mRawWidth; \
        aOutTexInfo->height  = _Data->mRawHeight; \
        aOutTexInfo->texture = _Data->mRawData.begin(); \
        aOutTexInfo->name    = aTexName; \
    }

    auto& _DynosCustomTexs = DynosCustomTexs();

    // check custom textures
    for (s32 i = 0; i < _DynosCustomTexs.Count(); ++i) {
        if (!strcmp(_DynosCustomTexs[i].first, aTexName)) {
            auto& _Data = _DynosCustomTexs[i].second->mData;

            // load the texture if it hasn't been yet
            if (_Data->mRawData.begin() == NULL) {
                u8 *_RawData = stbi_load_from_memory(_Data->mPngData.begin(), _Data->mPngData.Count(), &_Data->mRawWidth, &_Data->mRawHeight, NULL, 4);
                // texture data is corrupted
                if (_RawData == NULL) {
                    PrintError("Attempted to load corrupted tex file: %s", aTexName);
                    return false;
                }
                _Data->mRawFormat = G_IM_FMT_RGBA;
                _Data->mRawSize   = G_IM_SIZ_32b;
                _Data->mRawData   = Array<u8>(_RawData, _RawData + (_Data->mRawWidth * _Data->mRawHeight * 4));
                free(_RawData);
            }

            CONVERT_TEXINFO();
            return true;
        }
    }

    // check builtin textures
    const struct BuiltinTexInfo* info = DynOS_Builtin_Tex_GetInfoFromName(aTexName);
    if (!info) {
        for (DataNode<TexData>* _Node : DynosValidTextures()) { // check valid textures
            if (_Node->mName == aTexName) {
                auto& _Data = _Node->mData;
                CONVERT_TEXINFO();
                return true;
            }
        }
        return false;
    }
    aOutTexInfo->bitSize = info->bitSize;
    aOutTexInfo->width   = info->width;
    aOutTexInfo->height  = info->height;
    aOutTexInfo->texture = (u8*)info->pointer;
    aOutTexInfo->name    = aTexName;
    return true;
}

static DataNode<TexData> *DynOS_Lua_Tex_RetrieveNode(const char* aName) {
    auto& _DynosCustomTexs = DynosCustomTexs();
    for (s32 i = 0; i < _DynosCustomTexs.Count(); ++i) {
        if (!strcmp(_DynosCustomTexs[i].first, aName)) {
            return _DynosCustomTexs[i].second;
        }
    }

    for (DataNode<TexData>* _Node : DynosValidTextures()) {
        if (_Node->mName == aName) { return _Node; }
    };

    return NULL;
}

void DynOS_Tex_Override_Set(const char* aTexName, struct TextureInfo* aOverrideTexInfo) {
    // Override texture
    const Texture* _BuiltinTexture = DynOS_Builtin_Tex_GetFromName(aTexName);
    DataNode<TexData>* _BuiltinTexData;
    if (!_BuiltinTexture) {
        _BuiltinTexData = DynOS_Lua_Tex_RetrieveNode(aTexName);
        if (!_BuiltinTexData) { return; }
    }
    DataNode<TexData>* _Node = DynOS_Lua_Tex_RetrieveNode(aOverrideTexInfo->name);
    if (!_Node) { return; }

    struct OverrideTexture* _Override = new OverrideTexture();
    _Override->customTexture = false;
    _Override->node = _Node;
    if (_BuiltinTexture) {
        auto& _DynosOverrideLuaTextures = DynosOverrideLuaTextures();
        _DynosOverrideLuaTextures[_BuiltinTexture] = _Override;
    } else {
        auto& _DynosOverrideLuaTexData = DynosOverrideLuaTexData();
        _DynosOverrideLuaTexData[_BuiltinTexData] = _Override;
    }
}

void DynOS_Tex_Override_Reset(const char* aTexName) {
    // Override texture
    const Texture* _BuiltinTex = DynOS_Builtin_Tex_GetFromName(aTexName);
    if (!_BuiltinTex) { return; }

    auto& _DynosOverrideLuaTextures = DynosOverrideLuaTextures();
    auto _Override = _DynosOverrideLuaTextures[_BuiltinTex];
    if (_Override) {
        _DynosOverrideLuaTextures.erase(_BuiltinTex);
    }
}

void DynOS_Tex_ModShutdown() {
    auto& _DynosOverrideLuaTextures = DynosOverrideLuaTextures();
    _DynosOverrideLuaTextures.clear();

    auto& _DynosCustomTexs = DynosCustomTexs();
    while (_DynosCustomTexs.Count() > 0) {
        auto& pair = _DynosCustomTexs[0];
        DynOS_Tex_Deactivate(pair.second);
    }
}
