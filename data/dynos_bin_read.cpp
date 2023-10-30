#include "dynos.cpp.h"

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
        { "#if defined(VERSION_JP) || defined(VERSION_SH)", 47, false },
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

char *DynOS_Read_Buffer(FILE* aFile, GfxData* aGfxData) {
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

    // Make sure it's NULL terminated
    _FileBuffer[_Length] = '\0';

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

void DynOS_Read_Source(GfxData *aGfxData, const SysPath &aFilename) {
    FILE *_File = fopen(aFilename.c_str(), "rb");
    if (!_File) return;

    // Load file into a buffer while removing all comments
    char *_FileBuffer = DynOS_Read_Buffer(_File, aGfxData);
    fclose(_File);

    // Scanning the loaded data
    u32 _LineNumber = 1;
    u32 pDataLineNumber = 1;
    s32 _DataType = DATA_TYPE_NONE;
    String* pDataName = NULL;
    Array<String> *pDataTokens = NULL;
    char *pDataStart = NULL;
    bool _DataIgnore = false; // Needed to ignore the '#include "file.h"' strings
    String _Buffer = "";
    for (char *c = _FileBuffer; *c != 0; ++c) {

        // Scanning data type
        if (_DataType == DATA_TYPE_NONE) {

            // skip entire line of includes and externs
            if (!strncmp(c, "#include", 8) || !strncmp(c, "extern ", 7)) {
                while (*c != '\n' && *c != '\0') {
                    c++;
                }
                if (*c == '\0') {
                    break;
                }
            }

            // Reading data type name
            if ((*c >= 'A' && *c <= 'Z') || (*c >= 'a' && *c <= 'z') || (*c >= '0' && *c <= '9') || (*c == '_') || (*c == '\"')) {
                if (*c == '\"') {
                    _DataIgnore = !_DataIgnore;
                } else if (!_DataIgnore) {
                    _Buffer.Add(*c);
                }
            } else if (*c == '<' || *c == '>') {
                _DataIgnore = !_DataIgnore;
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
                } else if (_Buffer == "struct") {
                    // Ignore struct keyword
                } else if (_Buffer == "u64") {
                    _DataType = DATA_TYPE_UNUSED;
                } else if (_Buffer == "Lights0") {
                    _DataType = DATA_TYPE_LIGHT_0;
                } else if (_Buffer == "Lights1") {
                    _DataType = DATA_TYPE_LIGHT;
                } else if (_Buffer == "Light_t") {
                    _DataType = DATA_TYPE_LIGHT_T;
                } else if (_Buffer == "Ambient_t") {
                    _DataType = DATA_TYPE_AMBIENT_T;
                } else if (_Buffer == "u8") {
                    _DataType = strstr(aFilename.c_str(), "room.inc")
                              ? DATA_TYPE_ROOMS
                              : DATA_TYPE_TEXTURE;
                } else if (_Buffer == "Texture") {
                    // check if this is a 'Texture*' or a 'Texture'
                    char* peek = c;
                    while(*peek == ' ') { peek++; }
                    _DataType = (*peek == '*')
                              ? DATA_TYPE_TEXTURE_LIST
                              : DATA_TYPE_TEXTURE;
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
                } else if (_Buffer == "Trajectory") {
                    _DataType = DATA_TYPE_TRAJECTORY;
                } else if (_Buffer == "Movtex") {
                    _DataType = DATA_TYPE_MOVTEX;
                } else if (_Buffer == "MovtexQuadCollection") {
                    _DataType = DATA_TYPE_MOVTEXQC;
                } else if (_Buffer == "BehaviorScript") {
                    _DataType = DATA_TYPE_BEHAVIOR_SCRIPT;
                } else {
                    PrintDataError("  ERROR: Unknown type name: %s", _Buffer.begin());
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

            // Skip const
            else if (_Buffer == "const") {
                _Buffer.Clear();
            }

            // Adding new data node
            else if (_Buffer.Length() != 0) {
                switch (_DataType) {
                    case DATA_TYPE_LIGHT:           AppendNewNode(aGfxData, aGfxData->mLights,       _Buffer, pDataName, pDataTokens);    break;
                    case DATA_TYPE_LIGHT_0:         AppendNewNode(aGfxData, aGfxData->mLight0s,      _Buffer, pDataName, pDataTokens);    break;
                    case DATA_TYPE_LIGHT_T:         AppendNewNode(aGfxData, aGfxData->mLightTs,      _Buffer, pDataName, pDataTokens);    break;
                    case DATA_TYPE_AMBIENT_T:       AppendNewNode(aGfxData, aGfxData->mAmbientTs,    _Buffer, pDataName, pDataTokens);    break;
                    case DATA_TYPE_TEXTURE:         AppendNewNode(aGfxData, aGfxData->mTextures,     _Buffer, pDataName, pDataTokens);    break;
                    case DATA_TYPE_TEXTURE_LIST:    AppendNewNode(aGfxData, aGfxData->mTextureLists, _Buffer, pDataName, pDataTokens);    break;
                    case DATA_TYPE_VERTEX:          AppendNewNode(aGfxData, aGfxData->mVertices,     _Buffer, pDataName, pDataTokens);    break;
                    case DATA_TYPE_DISPLAY_LIST:    AppendNewNode(aGfxData, aGfxData->mDisplayLists, _Buffer, pDataName, pDataTokens);    break;
                    case DATA_TYPE_GEO_LAYOUT:      AppendNewNode(aGfxData, aGfxData->mGeoLayouts,   _Buffer, pDataName, pDataTokens);    break;
                    case DATA_TYPE_COLLISION:       AppendNewNode(aGfxData, aGfxData->mCollisions,   _Buffer, pDataName, pDataTokens);    break;
                    case DATA_TYPE_LEVEL_SCRIPT:    AppendNewNode(aGfxData, aGfxData->mLevelScripts, _Buffer, pDataName, pDataTokens);    break;
                    case DATA_TYPE_MACRO_OBJECT:    AppendNewNode(aGfxData, aGfxData->mMacroObjects, _Buffer, pDataName, pDataTokens);    break;
                    case DATA_TYPE_TRAJECTORY:      AppendNewNode(aGfxData, aGfxData->mTrajectories, _Buffer, pDataName, pDataTokens);    break;
                    case DATA_TYPE_MOVTEX:          AppendNewNode(aGfxData, aGfxData->mMovtexs,      _Buffer, pDataName, pDataTokens);    break;
                    case DATA_TYPE_MOVTEXQC:        AppendNewNode(aGfxData, aGfxData->mMovtexQCs,    _Buffer, pDataName, pDataTokens);    break;
                    case DATA_TYPE_ROOMS:           AppendNewNode(aGfxData, aGfxData->mRooms,        _Buffer, pDataName, pDataTokens);    break;
                    case DATA_TYPE_BEHAVIOR_SCRIPT: AppendNewNode(aGfxData, aGfxData->mBehaviorScripts, _Buffer, pDataName, pDataTokens); break;
                    case DATA_TYPE_UNUSED:          pDataTokens = (Array<String> *) 1;                                                    break;
                }
                _Buffer.Clear();
            }
        }

        // Looking for data
        else if (pDataStart == 0) {
            pDataLineNumber = _LineNumber;
            if (*c == '=') {
                pDataStart = c + 1;
            } else if (*c == ';') {
                PrintDataError("  ERROR: %s: Unexpected end of data", pDataName->begin());
            }
        }

        // Data end
        else if (*c == ';') {
            if (_DataType != DATA_TYPE_UNUSED) {
                char* pDataEnd = &*c;
                String _Token = "";
                for (u8 _Bracket = 0; pDataStart <= pDataEnd; pDataStart++) {
                    if (*pDataStart == '(') _Bracket++;
                    if (*pDataStart == '\n') pDataLineNumber++;
                    if (*pDataStart == ' ' || *pDataStart == '\t' || *pDataStart == '\r' || *pDataStart == '\n') continue;
                    if (_Bracket <= 1 && (*pDataStart == '(' || *pDataStart == ')' || *pDataStart == ',' || *pDataStart == '{' || *pDataStart == '}' || *pDataStart == ';')) {
                        if (_Token.Length() != 0) {
                            pDataTokens->Add(_Token);
                            // TODO: store pDataLineNumber in the node or something
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

        // increase line number
        if (c && *c == '\n') {
            _LineNumber++;
        }
    }

    Delete(_FileBuffer);
#ifdef DEVELOPMENT
    Print("Data read from file \"%s\"", aFilename.c_str());
#endif
}
