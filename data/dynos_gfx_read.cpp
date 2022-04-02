#include "dynos.cpp.h"
extern "C" {
}

//
// Model files
//

enum {
    COMMENT_NONE = 0,
    COMMENT_START,       // first slash
    COMMENT_SINGLE_LINE, // double slash, reset to COMMENT_NONE if \\n is hit
    COMMENT_BLOCK,       // slash-star, set to comment block end if * is hit
    COMMENT_BLOCK_END,   // slash-star-star, set to comment none if / is hit, else return to COMMENT_BLOCK
};

struct IfDefPtr { const char *mPtr; u64 mSize; bool mErase; };
static IfDefPtr GetNearestIfDefPointer(char *pFileBuffer) {
    static const IfDefPtr sIfDefs[] = {
        { "#ifdef VERSION_JP",  17, true  },
        { "#ifndef VERSION_JP", 18, false },
        { "#ifdef VERSION_EU",  17, true  },
        { "#ifdef TEXTURE_FIX", 18, false },
    };
    IfDefPtr _Nearest = { NULL, 0, false };
    for (const auto &_IfDef : sIfDefs) {
        const char *_Ptr = strstr(pFileBuffer, _IfDef.mPtr);
        if (_Ptr != NULL && (_Nearest.mPtr == NULL || _Nearest.mPtr > _Ptr)) {
            _Nearest.mPtr = _Ptr;
            _Nearest.mSize = _IfDef.mSize;
            _Nearest.mErase = _IfDef.mErase;
        }
    }
    return _Nearest;
}

static char *LoadFileBuffer(FILE* aFile, GfxData* aGfxData) {
    fseek(aFile, 0, SEEK_END);
    s32 _Length = ftell(aFile);
    if (aGfxData && aGfxData->mModelIdentifier == 0) {
        aGfxData->mModelIdentifier = (u32) _Length;
    }

    // Remove comments
    rewind(aFile);
    char *_FileBuffer = New<char>(_Length + 1);
    char *pFileBuffer = _FileBuffer;
    char _Previous = 0;
    char _Current = 0;
    s32 _CommentType = 0;
    while (fread(&_Current, 1, 1, aFile)) {
        if (_CommentType == COMMENT_NONE) {
            if (_Current == '/') {
                _CommentType = COMMENT_START;
            } else {
                *(pFileBuffer++) = _Current;
            }
        } else if (_CommentType == COMMENT_START) {
            if (_Current == '/') {
                _CommentType = COMMENT_SINGLE_LINE;
            } else if (_Current == '*') {
                _CommentType = COMMENT_BLOCK;
            } else {
                _CommentType = COMMENT_NONE;
                *(pFileBuffer++) = _Previous;
                *(pFileBuffer++) = _Current;
            }
        } else if (_CommentType == COMMENT_SINGLE_LINE) {
            if (_Current == '\n') {
                _CommentType = COMMENT_NONE;
                *(pFileBuffer++) = _Current;
            }
        } else if (_CommentType == COMMENT_BLOCK) {
            if (_Current == '*') {
                _CommentType = COMMENT_BLOCK_END;
            }
        } else if (_CommentType == COMMENT_BLOCK_END) {
            if (_Current == '/') {
                _CommentType = COMMENT_NONE;
            } else {
                _CommentType = COMMENT_BLOCK;
            }
        }
        _Previous = _Current;
    }
    *(pFileBuffer++) = 0;

    // Remove ifdef blocks
    // Doesn't support nested blocks
    for (pFileBuffer = _FileBuffer; pFileBuffer != NULL;) {
        IfDefPtr _IfDefPtr = GetNearestIfDefPointer(pFileBuffer);
        if (_IfDefPtr.mPtr) {
            char *pIfDef = (char *) _IfDefPtr.mPtr;
            char *pElse  = (char *) strstr(_IfDefPtr.mPtr, "#else");
            char *pEndIf = (char *) strstr(_IfDefPtr.mPtr, "#endif");

            if (pElse && pElse < pEndIf) {
                if (_IfDefPtr.mErase) memset(pIfDef, ' ', pElse + 5 - pIfDef);
                else                  memset(pElse,  ' ', pEndIf - pElse);
            } else {
                if (_IfDefPtr.mErase) memset(pIfDef, ' ', pEndIf - pIfDef);
            }

            memset(pIfDef, ' ', _IfDefPtr.mSize);
            memset(pEndIf, ' ', 6);
            pFileBuffer = pEndIf;
        } else {
            pFileBuffer = NULL;
        }
    }

    return _FileBuffer;
}

template <typename T>
static void AppendNewNode(GfxData *aGfxData, DataNodes<T> &aNodes, const String &aName, String *&aDataName, Array<String> *&aDataTokens) {
    DataNode<T> *_Node = New<DataNode<T>>();
    _Node->mName = aName;
    _Node->mModelIdentifier = aGfxData->mModelIdentifier;
    aNodes.Add(_Node);
    aDataName = &_Node->mName;
    aDataTokens = &_Node->mTokens;
}

static void ScanModelFile(GfxData *aGfxData, const SysPath &aFilename) {
    FILE *_File = fopen(aFilename.c_str(), "rb");
    if (!_File) return;

    // Remember the geo layout count
    s32 prevGeoLayoutCount = aGfxData->mGeoLayouts.Count();

    // Load file into a buffer while removing all comments
    char *_FileBuffer = LoadFileBuffer(_File, aGfxData);
    fclose(_File);

    // Scanning the loaded data
    s32 _DataType = DATA_TYPE_NONE;
    String* pDataName = NULL;
    Array<String> *pDataTokens = NULL;
    char *pDataStart = NULL;
    bool _DataIgnore = false; // Needed to ignore the '#include "file.h"' strings
    String _Buffer = "";
    for (char *c = _FileBuffer; *c != 0; ++c) {

        // Scanning data type
        if (_DataType == DATA_TYPE_NONE) {

            // Reading data type name
            if ((*c >= 'A' && *c <= 'Z') || (*c >= 'a' && *c <= 'z') || (*c >= '0' && *c <= '9') || (*c == '_') || (*c == '\"')) {
                if (*c == '\"') {
                    _DataIgnore = !_DataIgnore;
                } else if (!_DataIgnore) {
                    _Buffer.Add(*c);
                }
            }

            // Retrieving data type
            else if (_Buffer.Length() != 0) {
                if (_Buffer == "static") {
                    // Ignore static keyword
                } else if (_Buffer == "const") {
                    // Ignore const keyword
                } else if (_Buffer == "inline") {
                    // Ignore inline keyword
                } else if (_Buffer == "include") {
                    // Ignore include keyword
                } else if (_Buffer == "ALIGNED8") {
                    // Ignore ALIGNED8 keyword
                } else if (_Buffer == "UNUSED") {
                    // Ignore UNUSED keyword
                } else if (_Buffer == "u64") {
                    _DataType = DATA_TYPE_UNUSED;
                } else if (_Buffer == "Lights1") {
                    _DataType = DATA_TYPE_LIGHT;
                } else if (_Buffer == "u8") {
                    _DataType = DATA_TYPE_TEXTURE;
                } else if (_Buffer == "Texture") {
                    _DataType = DATA_TYPE_TEXTURE;
                } else if (_Buffer == "Vtx") {
                    _DataType = DATA_TYPE_VERTEX;
                } else if (_Buffer == "Gfx") {
                    _DataType = DATA_TYPE_DISPLAY_LIST;
                } else if (_Buffer == "GeoLayout") {
                    _DataType = DATA_TYPE_GEO_LAYOUT;
                } else if (_Buffer == "Collision") {
                    _DataType = DATA_TYPE_COLLISION;
                } else if (_Buffer == "LevelScript") {
                    _DataType = DATA_TYPE_LEVEL_SCRIPT;
                } else if (_Buffer == "MacroObject") {
                    _DataType = DATA_TYPE_MACRO_OBJECT;
                } else {
                    PrintError("  ERROR: Unknown type name: %s", _Buffer.begin());
                }
                _Buffer.Clear();
            }
        }

        // Scanning data identifier
        else if (!pDataTokens) {

            // Reading data identifier name
            if ((*c >= 'A' && *c <= 'Z') || (*c >= 'a' && *c <= 'z') || (*c >= '0' && *c <= '9') || (*c == '_')) {
                _Buffer.Add(*c);
            }

            // Adding new data node
            else if (_Buffer.Length() != 0) {
                switch (_DataType) {
                    case DATA_TYPE_LIGHT:        AppendNewNode(aGfxData, aGfxData->mLights,       _Buffer, pDataName, pDataTokens); break;
                    case DATA_TYPE_TEXTURE:      AppendNewNode(aGfxData, aGfxData->mTextures,     _Buffer, pDataName, pDataTokens); break;
                    case DATA_TYPE_VERTEX:       AppendNewNode(aGfxData, aGfxData->mVertices,     _Buffer, pDataName, pDataTokens); break;
                    case DATA_TYPE_DISPLAY_LIST: AppendNewNode(aGfxData, aGfxData->mDisplayLists, _Buffer, pDataName, pDataTokens); break;
                    case DATA_TYPE_GEO_LAYOUT:   AppendNewNode(aGfxData, aGfxData->mGeoLayouts,   _Buffer, pDataName, pDataTokens); break;
                    case DATA_TYPE_COLLISION:    AppendNewNode(aGfxData, aGfxData->mCollisions,   _Buffer, pDataName, pDataTokens); break;
                    case DATA_TYPE_LEVEL_SCRIPT: AppendNewNode(aGfxData, aGfxData->mLevelScripts, _Buffer, pDataName, pDataTokens); break;
                    case DATA_TYPE_MACRO_OBJECT: AppendNewNode(aGfxData, aGfxData->mMacroObjects, _Buffer, pDataName, pDataTokens); break;
                    case DATA_TYPE_UNUSED:       pDataTokens = (Array<String> *) 1;                                                 break;
                }
                _Buffer.Clear();
            }
        }

        // Looking for data
        else if (pDataStart == 0) {
            if (*c == '=') {
                pDataStart = c + 1;
            } else if (*c == ';') {
                PrintError("  ERROR: %s: Unexpected end of data", pDataName->begin());
            }
        }

        // Data end
        else if (*c == ';') {
            if (_DataType != DATA_TYPE_UNUSED) {
                char* pDataEnd = &*c;
                String _Token = "";
                for (u8 _Bracket = 0; pDataStart <= pDataEnd; pDataStart++) {
                    if (*pDataStart == '(') _Bracket++;
                    if (*pDataStart == ' ' || *pDataStart == '\t' || *pDataStart == '\r' || *pDataStart == '\n') continue;
                    if (_Bracket <= 1 && (*pDataStart == '(' || *pDataStart == ')' || *pDataStart == ',' || *pDataStart == '{' || *pDataStart == '}' || *pDataStart == ';')) {
                        if (_Token.Length() != 0) {
                            pDataTokens->Add(_Token);
                            _Token.Clear();
                        }
                    } else {
                        _Token.Add(*pDataStart);
                    }
                    if (*pDataStart == ')') _Bracket--;
                }
            }
            _DataType   = DATA_TYPE_NONE;
            pDataName   = NULL;
            pDataTokens = NULL;
            pDataStart  = NULL;
            _DataIgnore = false;
            _Buffer     = "";
        }
    }

    // Figure out which geo layouts to generate
    s32 geoLayoutCount = aGfxData->mGeoLayouts.Count();
    if (geoLayoutCount > prevGeoLayoutCount) {
        // find actors to generate
        bool foundActor = false;
        for (s32 i = prevGeoLayoutCount; i < geoLayoutCount; i++) {
            String _GeoRootName = aGfxData->mGeoLayouts[i]->mName;
            const void* actor = DynOS_Geo_GetActorLayoutFromName(_GeoRootName.begin());
            if (actor != NULL) {
                foundActor = true;
                aGfxData->mGenerateGeoLayouts.Add(aGfxData->mGeoLayouts[i]);
            }
        }

        // if we haven't found an actor, just add the last geo layout found
        if (!foundActor) {
            aGfxData->mGenerateGeoLayouts.Add(aGfxData->mGeoLayouts[geoLayoutCount - 1]);
        }
    }

    Delete(_FileBuffer);
    Print("Data read from file \"%s\"", aFilename.c_str());
}

//
// Animation files
//

static void ScanAnimationDataFile(GfxData *aGfxData, const SysPath &aFilename) {
    FILE *_File = fopen(aFilename.c_str(), "rb");
    if (!_File) {
        PrintError("  ERROR: Unable to open file \"%s\"", aFilename.c_str());
    }

    // Load file into a buffer while removing all comments
    char *_FileBuffer = LoadFileBuffer(_File, NULL);
    fclose(_File);

    // Parse animation data
    u8 _DataType = DATA_TYPE_NONE;
    String _DataName;
    bool _IsData = false;
    Array<String> _Data;
    Array<String> _Tokens = Split(_FileBuffer, " []()=&,;\t\r\n\b");
    for (const auto &_Token : _Tokens) {

        // Data type
        if (_DataType == DATA_TYPE_NONE) {
            if (_Token == "s16" || _Token == "u16" || _Token == "s16") {
                _DataType = DATA_TYPE_ANIMATION_VALUE;
            } else if (_Token == "Animation") {
                _DataType = DATA_TYPE_ANIMATION;
            }
        }

        // Data name
        else if (_DataName.Empty()) {
            _DataName = _Token;
            if (_DataType == DATA_TYPE_ANIMATION_VALUE && (_DataName.Find("index") != -1 || _DataName.Find("indices") != -1)) {
                _DataType = DATA_TYPE_ANIMATION_INDEX;
            }
        }

        // Is data?
        else if (!_IsData) {
            if (_Token == "{") {
                _IsData = true;
            }
        }

        // Data
        else {
            if (_Token == "}") {
                switch (_DataType) {
                    case DATA_TYPE_ANIMATION_VALUE: {
                        AnimBuffer<s16> *_AnimValues = New<AnimBuffer<s16>>();
                        _AnimValues->first = _DataName;
                        for (const auto &_Value : _Data) {
                            _AnimValues->second.Add(_Value.ParseInt());
                        }
                        aGfxData->mAnimValues.Add(_AnimValues);
                    } break;

                    case DATA_TYPE_ANIMATION_INDEX: {
                        AnimBuffer<u16> *_AnimIndices = New<AnimBuffer<u16>>();
                        _AnimIndices->first = _DataName;
                        for (const auto &_Index : _Data) {
                            _AnimIndices->second.Add(_Index.ParseInt());
                        }
                        aGfxData->mAnimIndices.Add(_AnimIndices);
                    } break;

                    case DATA_TYPE_ANIMATION: {
                        if (_Data.Count() < 10) {
                            PrintError("  ERROR: %s: Not enough data", _DataName.begin());
                            break;
                        }

                        DataNode<AnimData> *_Node = New<DataNode<AnimData>>();
                        _Node->mName = _DataName;
                        _Node->mData = New<AnimData>();
                        _Node->mData->mFlags = (s16) _Data[0].ParseInt();
                        _Node->mData->mUnk02 = (s16) _Data[1].ParseInt();
                        _Node->mData->mUnk04 = (s16) _Data[2].ParseInt();
                        _Node->mData->mUnk06 = (s16) _Data[3].ParseInt();
                        _Node->mData->mUnk08 = (s16) _Data[4].ParseInt();
                        _Node->mData->mUnk0A.first = _Data[6]; // 5 is "ANIMINDEX_NUMPARTS"
                        _Node->mData->mValues.first = _Data[7];
                        _Node->mData->mIndex.first = _Data[8];
                        _Node->mData->mLength = (u32) _Data[9].ParseInt();
                        aGfxData->mAnimations.Add(_Node);
                    } break;
                }
                _DataType = DATA_TYPE_NONE;
                _DataName.Clear();
                _IsData = false;
                _Data.Clear();
            } else {
                _Data.Add(_Token);
            }
        }
    }
    Delete(_FileBuffer);
}

static void ScanAnimationTableFile(GfxData *aGfxData, const SysPath &aFilename) {
    FILE *_File = fopen(aFilename.c_str(), "rb");
    if (!_File) {
        PrintError("  ERROR: Unable to open file \"%s\"", aFilename.c_str());
    }

    // Load file into a buffer while removing all comments
    char *_FileBuffer = LoadFileBuffer(_File, NULL);
    fclose(_File);

    // Retrieve animation names
    bool _IsAnimName = false;
    Array<String> _Tokens = Split(_FileBuffer, " =&,;\t\r\n\b");
    for (const auto &_Token : _Tokens) {
        if (_Token == "{") {
            _IsAnimName = true;
        } else if (_Token == "}") {
            _IsAnimName = false;
        } else if (_IsAnimName) {
            aGfxData->mAnimationTable.Add({ _Token, NULL });
        }
    }
    Delete(_FileBuffer);
}

static void ScanAnimationFolder(GfxData *aGfxData, const SysPath &aAnimsFolder) {
    DIR *_AnimsDir = opendir(aAnimsFolder.c_str());
    if (!_AnimsDir) return;

    struct dirent *_AnimsEnt = NULL;
    while ((_AnimsEnt = readdir(_AnimsDir)) != NULL) {

        // Skip
        if (SysPath(_AnimsEnt->d_name) == ".") continue;
        if (SysPath(_AnimsEnt->d_name) == "..") continue;
        if (SysPath(_AnimsEnt->d_name) == "data.inc.c") continue;

        // Animation file
        SysPath _AnimsFilename = fstring("%s/%s", aAnimsFolder.c_str(), _AnimsEnt->d_name);
        if (fs_sys_file_exists(_AnimsFilename.c_str())) {

            // Table file
            if (SysPath(_AnimsEnt->d_name) == "table.inc.c") {
                ScanAnimationTableFile(aGfxData, _AnimsFilename);
            }

            // Data file
            else {
                ScanAnimationDataFile(aGfxData, _AnimsFilename);
            }
        }
    }
    closedir(_AnimsDir);
}

//
// Read & Generate
//

// Free data pointers, but keep nodes and tokens intact
// Delete nodes generated from GfxDynCmds
template <typename T>
static void ClearGfxDataNodes(DataNodes<T> &aDataNodes) {
    for (s32 i = aDataNodes.Count(); i != 0; --i) {
        Delete(aDataNodes[i - 1]->mData);
    }
}

static String GetActorFolder(const Array<Pair<u64, String>> &aActorsFolders, u64 aModelIdentifier) {
    for (const auto &_Pair : aActorsFolders) {
        if (_Pair.first == aModelIdentifier) {
            return _Pair.second;
        }
    }
    return String();
}

static void DynOS_Col_Generate(const SysPath &aPackFolder, Array<Pair<u64, String>> _ActorsFolders, GfxData *_GfxData) {
    for (auto &_ColNode : _GfxData->mCollisions) {
        String _ColRootName = _ColNode->mName;

        // If there is an existing binary file for this collision, skip and go to the next actor
        SysPath _ColFilename = fstring("%s/%s.col", aPackFolder.c_str(), _ColRootName.begin());
        if (fs_sys_file_exists(_ColFilename.c_str())) {
            continue;
        }

        // Init
        _GfxData->mErrorCount = 0;
        _GfxData->mLoadIndex = 0;

        // Parse data
        PrintNoNewLine("%s.col: Model identifier: %X - Processing... ", _ColRootName.begin(), _GfxData->mModelIdentifier);
        DynOS_Col_Parse(_GfxData, _ColNode, true);

        // Write if no error
        if (_GfxData->mErrorCount == 0) {
            DynOS_Col_WriteBinary(_ColFilename, _GfxData, _ColNode);
        } else {
            Print("  %u error(s): Unable to parse data", _GfxData->mErrorCount);
        }

        // Clear data pointers
        ClearGfxDataNodes(_GfxData->mCollisions);
    }
}

static void DynOS_Actor_Generate(const SysPath &aPackFolder, Array<Pair<u64, String>> _ActorsFolders, GfxData *_GfxData) {
    for (auto &_GeoNode : _GfxData->mGenerateGeoLayouts) {
        String _GeoRootName = _GeoNode->mName;

        // If there is an existing binary file for this layout, skip and go to the next actor
        SysPath _BinFilename = fstring("%s/%s.bin", aPackFolder.c_str(), _GeoRootName.begin());
        if (fs_sys_file_exists(_BinFilename.c_str())) {
            continue;
        }

        // Init
        _GfxData->mLoadIndex                  = 0;
        _GfxData->mErrorCount                 = 0;
        _GfxData->mModelIdentifier            = _GeoNode->mModelIdentifier;
        _GfxData->mPackFolder                 = aPackFolder;
        _GfxData->mPointerList                = { NULL }; // The NULL pointer is needed, so we add it here
        _GfxData->mGfxContext.mCurrentTexture = NULL;
        _GfxData->mGfxContext.mCurrentPalette = NULL;
        _GfxData->mGeoNodeStack.Clear();

        // Parse data
        PrintNoNewLine("%s.bin: Model identifier: %X - Processing... ", _GeoRootName.begin(), _GfxData->mModelIdentifier);
        DynOS_Geo_Parse(_GfxData, _GeoNode, true);

        // Init animation data
        for (auto &_AnimBuffer : _GfxData->mAnimValues) Delete(_AnimBuffer);
        for (auto &_AnimBuffer : _GfxData->mAnimIndices) Delete(_AnimBuffer);
        for (auto &_AnimNode : _GfxData->mAnimations) Delete(_AnimNode);
        _GfxData->mAnimValues.Clear();
        _GfxData->mAnimIndices.Clear();
        _GfxData->mAnimations.Clear();
        _GfxData->mAnimationTable.Clear();

        // Scan anims folder for animation data
        String _ActorFolder = GetActorFolder(_ActorsFolders, _GfxData->mModelIdentifier);
        SysPath _AnimsFolder = fstring("%s/%s/anims", aPackFolder.c_str(), _ActorFolder.begin());
        ScanAnimationFolder(_GfxData, _AnimsFolder);

        // Create table for player model animations
        if ((_GeoRootName == "mario_geo" || _GeoRootName == "luigi_geo" || _GeoRootName == "toad_player_geo" || _GeoRootName == "wario_geo" || _GeoRootName == "waluigi_geo") && !_GfxData->mAnimations.Empty()) {
            _GfxData->mAnimationTable.Resize(256);
            for (s32 i = 0; i != 256; ++i) {
                String _AnimName("anim_%02X", i);
                if (_GfxData->mAnimations.FindIf([&_AnimName](const DataNode<AnimData> *aNode) { return aNode->mName == _AnimName; }) != -1) {
                    _GfxData->mAnimationTable[i] = { _AnimName, NULL };
                } else {
                    _GfxData->mAnimationTable[i] = { "NULL", NULL };
                }
            }
        }

        // Write if no error
        if (_GfxData->mErrorCount == 0) {
            DynOS_Gfx_WriteBinary(_BinFilename, _GfxData);
        } else {
            Print("  %u error(s): Unable to parse data", _GfxData->mErrorCount);
        }
        // Clear data pointers
        ClearGfxDataNodes(_GfxData->mLights);
        ClearGfxDataNodes(_GfxData->mTextures);
        ClearGfxDataNodes(_GfxData->mVertices);
        ClearGfxDataNodes(_GfxData->mDisplayLists);
        ClearGfxDataNodes(_GfxData->mGeoLayouts);
        ClearGfxDataNodes(_GfxData->mCollisions);
    }
}

void DynOS_Gfx_GeneratePack(const SysPath &aPackFolder) {
    Print("---------- Pack folder: \"%s\" ----------", aPackFolder.c_str());
    Array<Pair<u64, String>> _ActorsFolders;
    GfxData *_GfxData = New<GfxData>();

    // Read all the model.inc.c files and geo.inc.c files from the subfolders of the pack folder
    // Animations are processed separately
    DIR *aPackDir = opendir(aPackFolder.c_str());
    if (aPackDir) {
        struct dirent *_PackEnt = NULL;
        while ((_PackEnt = readdir(aPackDir)) != NULL) {

            // Skip . and ..
            if (SysPath(_PackEnt->d_name) == ".") continue;
            if (SysPath(_PackEnt->d_name) == "..") continue;

            // For each subfolder, read tokens from model.inc.c and geo.inc.c
            SysPath _Folder = fstring("%s/%s", aPackFolder.c_str(), _PackEnt->d_name);
            if (fs_sys_dir_exists(_Folder.c_str())) {
                _GfxData->mModelIdentifier = 0;
                ScanModelFile(_GfxData, fstring("%s/model.inc.c", _Folder.c_str()));
                ScanModelFile(_GfxData, fstring("%s/geo.inc.c", _Folder.c_str()));
                ScanModelFile(_GfxData, fstring("%s/collision.inc.c", _Folder.c_str()));
                if (_GfxData->mModelIdentifier != 0) {
                    _ActorsFolders.Add({ _GfxData->mModelIdentifier, String(_PackEnt->d_name) });
                }
            }
        }
        closedir(aPackDir);
    }

    // Generate a binary file for each actor found in the GfxData
    DynOS_Col_Generate(aPackFolder, _ActorsFolders, _GfxData);
    DynOS_Actor_Generate(aPackFolder, _ActorsFolders, _GfxData);

    DynOS_Gfx_Free(_GfxData);
}

void DynOS_Lvl_GeneratePack(const SysPath &aPackFolder) {
    Print("---------- Level pack folder: \"%s\" ----------", aPackFolder.c_str());
    Array<Pair<u64, String>> _ActorsFolders;
    GfxData *_GfxData = New<GfxData>();

    DIR *aPackDir = opendir(aPackFolder.c_str());
    if (aPackDir) {
        struct dirent *_PackEnt = NULL;
        while ((_PackEnt = readdir(aPackDir)) != NULL) {

            // Skip . and ..
            if (SysPath(_PackEnt->d_name) == ".") continue;
            if (SysPath(_PackEnt->d_name) == "..") continue;

            // For each subfolder, read tokens from script.c
            SysPath _Folder = fstring("%s/%s", aPackFolder.c_str(), _PackEnt->d_name);
            if (fs_sys_dir_exists(_Folder.c_str())) {
                _GfxData->mModelIdentifier = 0;
                ScanModelFile(_GfxData, fstring("%s/model.inc.c", _Folder.c_str()));
                ScanModelFile(_GfxData, fstring("%s/area_1/collision.inc.c", _Folder.c_str()));
                ScanModelFile(_GfxData, fstring("%s/area_1/geo.inc.c", _Folder.c_str()));
                ScanModelFile(_GfxData, fstring("%s/script.c", _Folder.c_str()));
                ScanModelFile(_GfxData, fstring("%s/area_1/macro.inc.c", _Folder.c_str()));
            }
        }
        closedir(aPackDir);
    }

    // Generate a binary file for each actor found in the GfxData
    DynOS_Lvl_GeneratePack_Internal(aPackFolder, _ActorsFolders, _GfxData);

    DynOS_Gfx_Free(_GfxData);
}
