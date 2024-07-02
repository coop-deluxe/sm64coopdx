#include "dynos.cpp.h"
extern "C" {
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
}

  ///////////
 // Utils //
///////////

static bool FileTypeExists(SysPath& aFolder, const char* fileType) {
    DIR *_Dir = opendir(aFolder.c_str());
    if (!_Dir) { return false; }

    int fileTypeLen = strlen(fileType);

    struct dirent *_Ent = NULL;
    while ((_Ent = readdir(_Dir)) != NULL) {
        int nameLen = strlen(_Ent->d_name);
        if (nameLen > fileTypeLen && !strcmp(&_Ent->d_name[nameLen - fileTypeLen], fileType)) {
            closedir(_Dir);
            return true;
        }
    }
    closedir(_Dir);
    return false;
}

static TexData* LoadTextureFromFile(GfxData *aGfxData, const char* aFile) {
    // Image file
    SysPath _Filename;
    int fileNameLen = strlen(aFile);
    if (aGfxData->mPackFolder.length() == 0) {
        _Filename = aFile;
    } else if (fileNameLen > 4 && !strcmp(&aFile[fileNameLen - 4], ".png")) {
        _Filename = fstring("%s/%s", aGfxData->mPackFolder.c_str(), aFile);
    } else {
        _Filename = fstring("%s/%s.png", aGfxData->mPackFolder.c_str(), aFile);
    }

    FILE *_File = fopen(_Filename.c_str(), "rb");

    // Check as if we're an Actor.
    if (!_File) {
        SysPath _ActorFilename = "";
        const char* _SubString = strchr(aFile, '/'); // Remove the "actors/"
        if (_SubString && *_SubString) {
            _SubString++;
            _ActorFilename = fstring("%s/%s.png", aGfxData->mPackFolder.c_str(), _SubString);
            _File = fopen(_ActorFilename.c_str(), "rb");
        }

        // The file does not exist in either spot!
        if (!_File) {
            PrintDataError("  ERROR: Unable to open file at \"%s\" or \"%s\"", _Filename.c_str(), _ActorFilename.c_str());
            return NULL;
        }
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
    u8 *_Buffer = DynOS_Tex_ConvertToRGBA32(aTexture->mRawData.begin(), aTexture->mRawData.Count(), aTexture->mRawFormat, aTexture->mRawSize, _Palette);
    if (_Buffer == NULL) {
        PrintDataError("  ERROR: Unknown texture format");
        return;
    }

    // Convert to PNG
    s32 _PngLength = 0;
    u8 *_PngData = stbi_write_png_to_mem(_Buffer, 0, aTexture->mRawWidth, aTexture->mRawHeight, 4, &_PngLength);
    if (!_PngData || !_PngLength) {
        PrintDataError("  ERROR: Cannot convert texture to PNG");
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
        PrintDataError("  ERROR: %s: not enough data", aNode->mName.begin());
        return aNode;
    }

    // #include"[texture].inc.c"
    s32 i0 = aNode->mTokens[0].Find("#include");
    if (i0 != -1) {
        s32 i1 = aNode->mTokens[0].Find(".inc.c");
        if (i1 == -1) {
            if (strstr(aNode->mName.begin(), "_pal_") == NULL) {
                PrintDataError("  ERROR: %s: missing .inc.c in String %s", aNode->mName.begin(), aNode->mTokens[0].begin());
            } else {
                // hack for pal textures to be "found"
                TexData* _Texture = New<TexData>();
                aNode->mData = _Texture;
                aNode->mLoadIndex = aGfxData->mLoadIndex++;
            }
            return aNode;
        }

        // Filename
        String _Filename  = aNode->mTokens[0].SubString(i0 + 9, i1 - i0 - 9);
        aNode->mData      = LoadTextureFromFile(aGfxData, _Filename.begin());
        aNode->mLoadIndex = aGfxData->mLoadIndex++;
        return aNode;
    }

    // double quoted String
    s32 dq0 = aNode->mTokens[0].Find('\"');
    if (dq0 != -1) {
        s32 dq1 = aNode->mTokens[0].Find('\"', dq0 + 1);
        if (dq1 == -1) {
            PrintDataError("  ERROR: %s: missing second quote in String %s", aNode->mName.begin(), aNode->mTokens[0].begin());
            return aNode;
        }

        // Filename
        String _Filename  = aNode->mTokens[0].SubString(dq0 + 1, dq1 - dq0 - 1);
        aNode->mData      = LoadTextureFromFile(aGfxData, _Filename.begin());
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

void DynOS_Tex_Write(BinFile* aFile, GfxData* aGfxData, DataNode<TexData> *aNode) {
    if (!aNode->mData) return;

    // Header
    aFile->Write<u8>(DATA_TYPE_TEXTURE);
    aNode->mName.Write(aFile);

    // Data
    // Look for texture duplicates
    // If that's the case, store the name of the texture node instead of the whole PNG data
    // (Don't bother to look for duplicates if there is no data to write)
    if (!aNode->mData->mPngData.Empty()) {
        for (const auto& _Node : aGfxData->mTextures) {
            if (_Node->mLoadIndex < aNode->mLoadIndex &&    // Check load order: duplicates should reference only an already loaded node
                _Node->mData != NULL &&                     // Check node data
                aNode->mData->mPngData.Count() == _Node->mData->mPngData.Count() &&     // Check PNG data lengths
                memcmp(aNode->mData->mPngData.begin(), _Node->mData->mPngData.begin(), aNode->mData->mPngData.Count()) == 0)    // Check PNG data content
            {
                aFile->Write<u32>(TEX_REF_CODE);
                _Node->mName.Write(aFile);
                return;
            }
        }
    }
    aNode->mData->mPngData.Write(aFile);
}

static bool DynOS_Tex_WriteBinary(GfxData* aGfxData, const SysPath &aOutputFilename, String& aName, TexData* aTexData, bool aRawTexture) {
    BinFile *_File = BinFile::OpenW(aOutputFilename.c_str());
    if (!_File) {
        PrintDataError("  ERROR: Unable to create file \"%s\"", aOutputFilename.c_str());
        return false;
    }

    if (!aRawTexture) {
        // Write png-texture

        // Header
        _File->Write<u8>(DATA_TYPE_TEXTURE);
        aName.Write(_File);

        // Data
        aTexData->mPngData.Write(_File);

        BinFile::Close(_File);
        return true;
    }

    // Write raw-texture

    // Header
    _File->Write<u8>(DATA_TYPE_TEXTURE_RAW);
    aName.Write(_File);

    // load
    u8 *_RawData = stbi_load_from_memory(aTexData->mPngData.begin(), aTexData->mPngData.Count(), &aTexData->mRawWidth, &aTexData->mRawHeight, NULL, 4);
    aTexData->mRawFormat = G_IM_FMT_RGBA;
    aTexData->mRawSize   = G_IM_SIZ_32b;
    aTexData->mRawData   = Array<u8>(_RawData, _RawData + (aTexData->mRawWidth * aTexData->mRawHeight * 4));
    free(_RawData);

    // Data
    _File->Write<s32>(aTexData->mRawFormat);
    _File->Write<s32>(aTexData->mRawSize);
    _File->Write<s32>(aTexData->mRawWidth);
    _File->Write<s32>(aTexData->mRawHeight);
    aTexData->mRawData.Write(_File);

    BinFile::Close(_File);
    return true;
}

  /////////////
 // Reading //
/////////////

DataNode<TexData>* DynOS_Tex_Load(BinFile *aFile, GfxData *aGfxData) {
    if (!aFile || !aGfxData) { return NULL; }

    DataNode<TexData> *_Node = New<DataNode<TexData>>();

    // Name
    _Node->mName.Read(aFile);

    // Data
    _Node->mData = New<TexData>();
    _Node->mData->mUploaded = false;

    // Check for the texture ref magic
    s32 _FileOffset = aFile->Offset();
    u32 _TexRefCode = aFile->Read<u32>();
    if (_TexRefCode == TEX_REF_CODE) {

        // That's a duplicate, find the original node and copy its content
        String _NodeName; _NodeName.Read(aFile);
        for (const auto& _LoadedNode : aGfxData->mTextures) {
            if (_LoadedNode->mName == _NodeName) {
                _Node->mData->mPngData   = _LoadedNode->mData->mPngData;
                _Node->mData->mRawData   = _LoadedNode->mData->mRawData;
                _Node->mData->mRawWidth  = _LoadedNode->mData->mRawWidth;
                _Node->mData->mRawHeight = _LoadedNode->mData->mRawHeight;
                _Node->mData->mRawFormat = _LoadedNode->mData->mRawFormat;
                _Node->mData->mRawSize   = _LoadedNode->mData->mRawSize;
                break;
            }
        }
    } else {
        aFile->SetOffset(_FileOffset);
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
    }

    // Append
    if (aGfxData) {
        aGfxData->mTextures.Add(_Node);
    }

    return _Node;
}

DataNode<TexData>* DynOS_Tex_LoadFromBinary(const SysPath &aPackFolder, const SysPath &aFilename, const char *aTexName, bool aAddToPack) {
    // Look for pack in cache
    PackData* _Pack = DynOS_Pack_GetFromPath(aPackFolder);

    // Look for tex in pack
    if (_Pack) {
        auto _Tex = DynOS_Pack_GetTex(_Pack, aTexName);
        if (_Tex != NULL) {
            return _Tex;
        }
    }

    // Load data from binary file
    DataNode<TexData>* _TexNode = NULL;
    BinFile *_File = BinFile::OpenR(aFilename.c_str());
    if (!_File) { return NULL; }

    u8 type = _File->Read<u8>();
    if (type == DATA_TYPE_TEXTURE) {
        // load png-texture
        _TexNode = New<DataNode<TexData>>();
        _TexNode->mData = New<TexData>();

        _TexNode->mName.Read(_File);
        _TexNode->mData->mPngData.Read(_File);
        BinFile::Close(_File);

        if (aAddToPack) {
            if (!_Pack) { _Pack = DynOS_Pack_Add(aPackFolder); }
            DynOS_Pack_AddTex(_Pack, _TexNode);
        }

        return _TexNode;
    } else if (type != DATA_TYPE_TEXTURE_RAW) {
        BinFile::Close(_File);
        return NULL;
    }

    // load raw-texture
    _TexNode = New<DataNode<TexData>>();
    _TexNode->mData = New<TexData>();

    _TexNode->mName.Read(_File);
    _TexNode->mData->mRawFormat = _File->Read<s32>();
    _TexNode->mData->mRawSize = _File->Read<s32>();
    _TexNode->mData->mRawWidth = _File->Read<s32>();
    _TexNode->mData->mRawHeight = _File->Read<s32>();
    _TexNode->mData->mRawData.Read(_File);

    BinFile::Close(_File);

    if (aAddToPack) {
        if (!_Pack) { _Pack = DynOS_Pack_Add(aPackFolder); }
        DynOS_Pack_AddTex(_Pack, _TexNode);
    }

    return _TexNode;
}

  //////////////
 // Generate //
//////////////

static bool is_level_number_png(SysPath& aPath) {
    // normalize
    String path = aPath.c_str();
    char* p = path.begin();
    while (*p != '\0') {
        if (*p == '\\') {
            *p = '/';
        }
        break;
    }
    p = path.begin();

    // compare 'levels/'
    s16 levelsLength = strlen("levels/");
    if (strncmp(p, "levels/", levelsLength)) {
        return false;
    }

    // skip past level name
    p += levelsLength;
    while (*p != '\0') {
        if (*p == '/') { break; }
        p++;
    }
    if (*p != '/') { return false; }
    p++;

    return (*p >= '0' && *p <= '9');
}

static void DynOS_Tex_GeneratePack_Recursive(const SysPath &aPackFolder, SysPath &aOutputFolder, SysPath& aRelativePath, SysPath& aPrefix, GfxData *aGfxData, bool aAllowCustomTextures) {
    SysPath _DirPath = fstring("%s/%s", aPackFolder.c_str(), aRelativePath.c_str());

    // skip generation if any .c files exist, and it isn't levels/xxx/NUMBER
    bool containsC = FileTypeExists(_DirPath, ".c");

    DIR *_PackDir = opendir(_DirPath.c_str());
    if (!_PackDir) { return; }

    struct dirent *_PackEnt = NULL;
    while ((_PackEnt = readdir(_PackDir)) != NULL) {

        // Skip . and ..
        if (SysPath(_PackEnt->d_name) == ".") continue;
        if (SysPath(_PackEnt->d_name) == "..") continue;

        SysPath _Path = fstring("%s%s", _DirPath.c_str(), _PackEnt->d_name);

        // Recurse through subfolders
        if (fs_sys_dir_exists(_Path.c_str())) {
            SysPath _NextPath = fstring("%s%s/", aRelativePath.c_str(), _PackEnt->d_name);
            SysPath _Prefix = fstring("%s.", _PackEnt->d_name);
            DynOS_Tex_GeneratePack_Recursive(aPackFolder, aOutputFolder, _NextPath, _Prefix, aGfxData, aAllowCustomTextures);
            continue;
        }


        size_t nameLen = strlen(_PackEnt->d_name);
        if (nameLen < 4) continue;

        // skip files that don't end in '.png'
        if (strcmp(&_PackEnt->d_name[nameLen - 4], ".png")) {
            continue;
        }

        // skip files that have already been generated
        char buffer[SYS_MAX_PATH];
        snprintf(buffer, SYS_MAX_PATH, "%s.tex", _Path.substr(0, _Path.size() - 4).c_str());
        if (fs_sys_file_exists(buffer)) {
            continue;
        }

        // read the file
        aGfxData->mModelIdentifier++;
        TexData* _TexData = LoadTextureFromFile(aGfxData, _Path.c_str());
        if (_TexData == NULL) {
            PrintDataError("Error reading texture from file: %s", _Path.c_str());
            continue;
        }

        SysPath _RelativePath = fstring("%s%s", aRelativePath.c_str(), _PackEnt->d_name);
        if (containsC && !is_level_number_png(_RelativePath)) {
            // Don't forgot to free the texture data we've read.
            Delete<TexData>(_TexData);
            continue;
        }

        // write the file
        String _BaseName;
        const char* _OverrideName = DynOS_Builtin_Tex_GetNameFromFileName(_RelativePath.c_str());
        if (_OverrideName) {
            _BaseName = _OverrideName;
        } else {
            _BaseName = _PackEnt->d_name;
            _BaseName = _BaseName.SubString(0, nameLen - 4);
        }

        // if we aren't overriding a texture, only generate textures in the output directory
        SysPath _OutputFolder = fstring("%s/", aOutputFolder.c_str());
        if (_OverrideName == NULL && (!aAllowCustomTextures || strcmp(_DirPath.c_str(), _OutputFolder.c_str()))) {
            // Don't forgot to free the texture data we've read.
            Delete<TexData>(_TexData);
            continue;
        }

        SysPath _OutputPath = fstring("%s/%s.tex", aOutputFolder.c_str(), _BaseName.begin());

        // create output dir if it doesn't exist
        if (!fs_sys_dir_exists(aOutputFolder.c_str())) {
            fs_sys_mkdir(aOutputFolder.c_str());
        }

        DynOS_Tex_WriteBinary(aGfxData, _OutputPath, _BaseName, _TexData, (_OverrideName != NULL));
        
        // Don't forgot to free the texture data we've read.
        Delete<TexData>(_TexData);
    }

    closedir(_PackDir);
}

void DynOS_Tex_GeneratePack(const SysPath &aPackFolder, SysPath &aOutputFolder, bool aAllowCustomTextures) {
    Print("Processing textures: \"%s\"", aPackFolder.c_str());

    GfxData *_GfxData = New<GfxData>();
    _GfxData->mModelIdentifier = 0;
    SysPath _Empty = "";
    DynOS_Tex_GeneratePack_Recursive(aPackFolder, aOutputFolder, _Empty, _Empty, _GfxData, aAllowCustomTextures);
    DynOS_Gfx_Free(_GfxData);
}
