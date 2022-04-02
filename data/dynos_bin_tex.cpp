#include "dynos.cpp.h"
extern "C" {
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
}

  ///////////
 // Utils //
///////////

static TexData* LoadTextureFromFile(GfxData *aGfxData, const String& aFile) {

    // Image file
    String _TexturePath = aFile.SubString(aFile.Find('/') + 1); // Remove the "actors/"
    SysPath _Filename = fstring("%s/%s.png", aGfxData->mPackFolder.c_str(), _TexturePath.begin());
    FILE *_File = fopen(_Filename.c_str(), "rb");
    if (!_File) {
        PrintError("  ERROR: Unable to open file \"%s\"", _Filename.c_str());
        return NULL;
    }

    // Texture data
    fseek(_File, 0, SEEK_END);
    TexData* _Texture = New<TexData>();
    _Texture->mPngData.Resize(ftell(_File)); rewind(_File);
    fread(_Texture->mPngData.begin(), sizeof(u8), _Texture->mPngData.Count(), _File);
    fclose(_File);
    return _Texture;
}

void DynOS_Tex_ConvertTextureDataToPng(GfxData *aGfxData, TexData* aTexture) {

    // Convert to RGBA32
    const u8 *_Palette = (aGfxData->mGfxContext.mCurrentPalette ? aGfxData->mGfxContext.mCurrentPalette->mData->mRawData.begin() : NULL);
    u8 *_Buffer = DynOS_Gfx_TextureConvertToRGBA32(aTexture->mRawData.begin(), aTexture->mRawData.Count(), aTexture->mRawFormat, aTexture->mRawSize, _Palette);
    if (_Buffer == NULL) {
        PrintError("  ERROR: Unknown texture format");
        return;
    }

    // Convert to PNG
    s32 _PngLength = 0;
    u8 *_PngData = stbi_write_png_to_mem(_Buffer, 0, aTexture->mRawWidth, aTexture->mRawHeight, 4, &_PngLength);
    if (!_PngData || !_PngLength) {
        PrintError("  ERROR: Cannot convert texture to PNG");
        return;
    }

    aTexture->mPngData = Array<u8>(_PngData, _PngData + _PngLength);
    Delete(_PngData);
}

  /////////////
 // Parsing //
/////////////

DataNode<TexData>* DynOS_Tex_Parse(GfxData* aGfxData, DataNode<TexData>* aNode) {
    if (aNode->mData) return aNode;

    // Check tokens Count
    if (aNode->mTokens.Count() < 1) {
        PrintError("  ERROR: %s: not enough data", aNode->mName.begin());
        return aNode;
    }

    // #include"[texture].inc.c"
    s32 i0 = aNode->mTokens[0].Find("#include");
    if (i0 != -1) {
        s32 i1 = aNode->mTokens[0].Find(".inc.c");
        if (i1 == -1) {
            PrintError("  ERROR: %s: missing .inc.c in String %s", aNode->mName.begin(), aNode->mTokens[0].begin());
            return aNode;
        }

        // Filename
        String _Filename  = aNode->mTokens[0].SubString(i0 + 9, i1 - i0 - 9);
        aNode->mData      = LoadTextureFromFile(aGfxData, _Filename);
        aNode->mLoadIndex = aGfxData->mLoadIndex++;
        return aNode;
    }

    // double quoted String
    s32 dq0 = aNode->mTokens[0].Find('\"');
    if (dq0 != -1) {
        s32 dq1 = aNode->mTokens[0].Find('\"', dq0 + 1);
        if (dq1 == -1) {
            PrintError("  ERROR: %s: missing second quote in String %s", aNode->mName.begin(), aNode->mTokens[0].begin());
            return aNode;
        }

        // Filename
        String _Filename  = aNode->mTokens[0].SubString(dq0 + 1, dq1 - dq0 - 1);
        aNode->mData      = LoadTextureFromFile(aGfxData, _Filename);
        aNode->mLoadIndex = aGfxData->mLoadIndex++;
        return aNode;
    }

    // Stream of bytes
    aNode->mData              = New<TexData>();
    aNode->mData->mRawWidth   = -1; // Unknown for now, will be set later
    aNode->mData->mRawHeight  = -1; // Unknown for now, will be set later
    aNode->mData->mRawFormat  = -1; // Unknown for now, will be set later
    aNode->mData->mRawSize    = -1; // Unknown for now, will be set later
    aNode->mData->mRawData.Resize(aNode->mTokens.Count());
    for (u64 j = 0; j != aNode->mTokens.Count(); ++j) {
    aNode->mData->mRawData[j] = aNode->mTokens[j].ParseInt();
    }
    aNode->mLoadIndex         = aGfxData->mLoadIndex++;
    return aNode;
}

  /////////////
 // Writing //
/////////////

void DynOS_Tex_Write(FILE* aFile, GfxData* aGfxData, DataNode<TexData> *aNode) {
    if (!aNode->mData) return;

    // Header
    WriteBytes<u8>(aFile, DATA_TYPE_TEXTURE);
    aNode->mName.Write(aFile);

    // Data
    aNode->mData->mPngData.Write(aFile);
}

  /////////////
 // Reading //
/////////////

void DynOS_Tex_Load(FILE *aFile, GfxData *aGfxData) {
    DataNode<TexData> *_Node = New<DataNode<TexData>>();

    // Name
    _Node->mName.Read(aFile);

    // Data
    _Node->mData = New<TexData>();
    _Node->mData->mUploaded = false;
    _Node->mData->mPngData.Read(aFile);
    if (!_Node->mData->mPngData.Empty()) {
        u8 *_RawData = stbi_load_from_memory(_Node->mData->mPngData.begin(), _Node->mData->mPngData.Count(), &_Node->mData->mRawWidth, &_Node->mData->mRawHeight, NULL, 4);
        _Node->mData->mRawFormat = G_IM_FMT_RGBA;
        _Node->mData->mRawSize   = G_IM_SIZ_32b;
        _Node->mData->mRawData   = Array<u8>(_RawData, _RawData + (_Node->mData->mRawWidth * _Node->mData->mRawHeight * 4));
        free(_RawData);
    } else { // Probably a palette
        _Node->mData->mRawData   = Array<u8>();
        _Node->mData->mRawWidth  = 0;
        _Node->mData->mRawHeight = 0;
        _Node->mData->mRawFormat = 0;
        _Node->mData->mRawSize   = 0;
    }

    // Append
    aGfxData->mTextures.Add(_Node);
}
