#include "dynos.cpp.h"

// Free data pointers, but keep nodes and tokens intact
// Delete nodes generated from GfxDynCmds
template <typename T>
void ClearGfxDataNodes(DataNodes<T> &aDataNodes) {
    for (s32 i = aDataNodes.Count(); i != 0; --i) {
        Delete(aDataNodes[i - 1]->mData);
    }
}

  /////////////
 // Parsing //
/////////////

#define ANIMATION_SIZE_PER_TOKEN 4

static s32 ParseAnimBufferIndex(GfxData* aGfxData, DataNode<AnimData>* aNode, const String& aToken) {
    s32 _BufferIdx = aGfxData->mAnimBuffers.FindIf([&aToken](const AnimBuffer<u16> *aAnimBuffer) { return aAnimBuffer->first == aToken; });
    return _BufferIdx;
}

static s32 ParseAnimSymbolArg(GfxData* aGfxData, DataNode<AnimData>* aNode, u64& aTokenIndex) {
    const String& _Arg = aNode->mTokens[aTokenIndex++];

    // Buffers
    s32 bufferIdx = ParseAnimBufferIndex(aGfxData, aNode, _Arg);
    if (bufferIdx != -1) {
        return bufferIdx;
    }

    // Unknown
    PrintDataError("  ERROR: Unknown anim arg: %s", _Arg.begin());
    return 0;
}

#define anim_symbol_1(symb)                                                \
    if (_Symbol == #symb) {                                                \
        s32 _BufferIdx = ParseAnimSymbolArg(aGfxData, aNode, aTokenIndex); \
        AnimBuffer<u16> *_Cl = aGfxData->mAnimBuffers[_BufferIdx];          \
        memcpy(aHead, _Cl, sizeof(_Cl));                                   \
        aHead += (sizeof(_Cl) / sizeof(_Cl[0]));                           \
        return;                                                            \
    }

static void ParseAnimationSymbol(GfxData* aGfxData, DataNode<AnimData>* aNode, AnimData*& aHead, u64& aTokenIndex) {
    const String& _Symbol = aNode->mTokens[aTokenIndex++];

    anim_symbol_1(ANIMINDEX_NUMPARTS);
    anim_symbol_1(ANIM_FIELD_LENGTH);

    bool integerFound = false;
    u16 integerValue = (u16)DynOS_Misc_ParseInteger(_Symbol, &integerFound);
    if (integerFound) {
        u16 _C0[] = { integerValue };
        memcpy(aHead, _C0, sizeof(_C0));
        aHead += (sizeof(_C0) / sizeof(_C0[0]));
        return;
    }

    s32 bufferIdx = ParseAnimBufferIndex(aGfxData, aNode, _Symbol);
    if (bufferIdx != -1) {
        memcpy(aHead, aGfxData->mAnimBuffers[bufferIdx], sizeof(aGfxData->mAnimBuffers[bufferIdx]));
        aHead += (sizeof(aGfxData->mAnimBuffers[bufferIdx]) / sizeof(aGfxData->mAnimBuffers[bufferIdx][0]));
        return;
    }

    // Unknown
    PrintDataError("  ERROR: Unknown anim symbol: %s", _Symbol.begin());
}

static void DynOS_Anim_GetBuffers(GfxData *aGfxData, const SysPath &aFilename) {
    FILE *_File = fopen(aFilename.c_str(), "rb");
    if (!_File) {
        PrintDataError("  ERROR: Unable to open file \"%s\"", aFilename.c_str());
    }

    // Load file into a buffer while removing all comments
    char *_FileBuffer = DynOS_Read_Buffer(_File, NULL);
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
            if (_Token == "s16" || _Token == "u16") {
                _DataType = DATA_TYPE_ANIMATION_VALUE;
            } else if (_Token == "Animation") {
                _DataType = DATA_TYPE_ANIMATION;
            }
        }

        // Data name
        else if (_DataName.Empty()) {
            _DataName = _Token;
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
                        AnimBuffer<u16> *_AnimBuffer = New<AnimBuffer<u16>>();
                        _AnimBuffer->first = _DataName;
                        for (const auto &_Value : _Data) {
                            _AnimBuffer->second.Add(_Value.ParseInt());
                        }
                        aGfxData->mAnimBuffers.Add(_AnimBuffer);
                        break;
                    }
                    case DATA_TYPE_ANIMATION: {
                        if (_Data.Count() < 10) {
                            PrintDataError("  ERROR: %s: Not enough data", _DataName.begin());
                            break;
                        }

                        DataNode<AnimData> *_Node        = aGfxData->mAnimations.Find(_DataName);
                        if (!_Node) { break; }
                        _Node->mData                     = New<AnimData>();
                        _Node->mData->mFlags             = (s16) _Data[0].ParseInt();
                        _Node->mData->mAnimYTransDivisor = (s16) _Data[1].ParseInt();
                        _Node->mData->mStartFrame        = (s16) _Data[2].ParseInt();
                        _Node->mData->mLoopStart         = (s16) _Data[3].ParseInt();
                        _Node->mData->mLoopEnd           = (s16) _Data[4].ParseInt();
                        _Node->mData->mNumParts.first    = _Data[6];
                        _Node->mData->mValues.first      = _Data[7];
                        _Node->mData->mIndex.first       = _Data[8];
                        _Node->mData->mLength            = (u32) _Data[9].ParseInt();
                        break;
                    }
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

DataNode<AnimData>* DynOS_Anim_Parse(GfxData* aGfxData, DataNode<AnimData>* aNode, bool aDisplayPercent) {
    if (aNode->mData) return aNode;

    // Animation data
    aNode->mData = New<AnimData>(aNode->mTokens.Count() * ANIMATION_SIZE_PER_TOKEN);
    AnimData* _Head = aNode->mData;

    for (u64 _TokenIndex = 0; _TokenIndex < aNode->mTokens.Count();) {
        ParseAnimationSymbol(aGfxData, aNode, _Head, _TokenIndex);
        if (aDisplayPercent && aGfxData->mErrorCount == 0) { PrintNoNewLine("%3d%%\b\b\b\b", (s32) (_TokenIndex * 100) / aNode->mTokens.Count()); }
    }

    aNode->mSize = (u32)(_Head - aNode->mData);
    aNode->mLoadIndex = aGfxData->mLoadIndex++;

    if (aGfxData->mErrorCount > 0) {
        PrintDataError("  ERROR: Failed to parse animation: '%s'", aNode->mName.begin());
    }

    if (aDisplayPercent && aGfxData->mErrorCount == 0) { Print("100%%"); }
    return aNode;
}

static void DynOS_Anim_Table_Parse(GfxData *aGfxData, const SysPath &aFilename) {
    FILE *_File = fopen(aFilename.c_str(), "rb");
    if (!_File) {
        PrintDataError("  ERROR: Unable to open file \"%s\"", aFilename.c_str());
        return;
    }

    // Load file into a buffer while removing all comments
    char *_FileBuffer = DynOS_Read_Buffer(_File, NULL);
    fclose(_File);

    Array<String> _Tokens = Split(_FileBuffer, " =&,;\t\r\n\b()[]");

    bool _InAnimList = false;
    bool _TargetingAnims = false;
    bool _ExpectsName = false;
    
    String _TableName = "";

    for (const auto &_Token : _Tokens) {
        if (_Token == "AnimationTable" || _Token == "Animation") {
            _ExpectsName = true;
            continue;
        }

        if (_ExpectsName) {
            if (_Token == "const" || _Token == "struct" || _Token == "*") { continue; }
            DataNode<AnimTableData> *_Node = aGfxData->mAnimationTables.Find(_Token);
            if (_Node) {
                _Node->mData = New<AnimTableData>();
            }
            _TableName = _Token;
            _ExpectsName = false;
            continue;
        }

        if (_Token == ".anims") {
            _TargetingAnims = true;
            continue;
        }

        if (_Token == "{") {
            if (_TargetingAnims || !_InAnimList) {
                _InAnimList = true;
                _TargetingAnims = false;
            }
            continue;
        }

        if (_Token == "}") {
            _InAnimList = false;
            _TableName = "";
            continue;
        }

        if (_InAnimList && !_TableName.Empty()) {
            if (_Token != "NULL" && _Token != "null" && _Token != "0" && _Token[0] != '.') {
                DataNode<AnimTableData> *_Node = aGfxData->mAnimationTables.Find(_TableName);
                if (!_Node) { continue; }
                _Node->mData->mAnimations.Add({ _Token, NULL });
            }
        }
    }

    Delete(_FileBuffer);
}


static void DynOS_Anim_ScanFile(GfxData *aGfxData, const SysPath &aFilename) {
    FILE *_File = fopen(aFilename.c_str(), "rb");
    if (!_File) {
        PrintDataError("  ERROR: Unable to open file \"%s\"", aFilename.c_str());
    }

    // Load file into a buffer while removing all comments
    char *_FileBuffer = DynOS_Read_Buffer(_File, NULL);
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
            if (_Token == "s16" || _Token == "u16") {
                _DataType = DATA_TYPE_ANIMATION_VALUE;
            } else if (_Token == "Animation") {
                _DataType = DATA_TYPE_ANIMATION;
            }
        }

        // Data name
        else if (_DataName.Empty()) {
            _DataName = _Token;
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
                        AnimBuffer<u16> *_AnimBuffer = New<AnimBuffer<u16>>();
                        _AnimBuffer->first = _DataName;
                        for (const auto &_Value : _Data) {
                            _AnimBuffer->second.Add(_Value.ParseInt());
                        }
                        aGfxData->mAnimBuffers.Add(_AnimBuffer);
                        break;
                    }
                    case DATA_TYPE_ANIMATION: {
                        if (_Data.Count() < 10) {
                            PrintDataError("  ERROR: %s: Not enough data", _DataName.begin());
                            break;
                        }

                        DataNode<AnimData> *_Node        = New<DataNode<AnimData>>();
                        _Node->mName                     = _DataName;
                        _Node->mData                     = New<AnimData>();
                        _Node->mData->mFlags             = (s16) _Data[0].ParseInt();
                        _Node->mData->mAnimYTransDivisor = (s16) _Data[1].ParseInt();
                        _Node->mData->mStartFrame        = (s16) _Data[2].ParseInt();
                        _Node->mData->mLoopStart         = (s16) _Data[3].ParseInt();
                        _Node->mData->mLoopEnd           = (s16) _Data[4].ParseInt();
                        _Node->mData->mNumParts.first    = _Data[6];
                        _Node->mData->mValues.first      = _Data[7];
                        _Node->mData->mIndex.first       = _Data[8];
                        _Node->mData->mLength            = (u32) _Data[9].ParseInt();
                        aGfxData->mAnimations.Add(_Node);
                        break;
                    }
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

static void DynOS_Anim_Table_ScanFile(GfxData *aGfxData, const SysPath &aFilename) {
    FILE *_File = fopen(aFilename.c_str(), "rb");
    if (!_File) {
        PrintDataError("  ERROR: Unable to open file \"%s\"", aFilename.c_str());
    }

    // Load file into a buffer while removing all comments
    char *_FileBuffer = DynOS_Read_Buffer(_File, NULL);
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

void DynOS_Anim_ScanFolder(GfxData *aGfxData, const SysPath &aAnimsFolder) {
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
                DynOS_Anim_Table_ScanFile(aGfxData, _AnimsFilename);
            }

            // Data file
            else {
                DynOS_Anim_ScanFile(aGfxData, _AnimsFilename);
            }
        }
    }
    closedir(_AnimsDir);
}

  /////////////
 // Writing //
/////////////

void DynOS_Anim_Write(BinFile *aFile, GfxData *aGfxData, DataNode<AnimData> *aNode) {
    if (!aNode->mData) { return; }

    // Value buffer
    s32 _ValueBufferIdx = aGfxData->mAnimBuffers.FindIf([&aNode](const AnimBuffer<u16> *aAnimBuffer) { return aAnimBuffer->first == aNode->mData->mValues.first; });
    if (_ValueBufferIdx == -1) { return; }

    // Index buffer
    s32 _IndexBufferIdx = aGfxData->mAnimBuffers.FindIf([&aNode](const AnimBuffer<u16> *aAnimBuffer) { return aAnimBuffer->first == aNode->mData->mIndex.first; });
    if (_IndexBufferIdx == -1) { return; }

    // NumParts buffer
    s32 _NumPartsBufferIdx = aGfxData->mAnimBuffers.FindIf([&aNode](const AnimBuffer<u16> *aAnimBuffer) { return aAnimBuffer->first == aNode->mData->mNumParts.first; });
    if (_NumPartsBufferIdx == -1) { return; }

    // Header
    aFile->Write<u8>(DATA_TYPE_ANIMATION);
    aNode->mName.Write(aFile);

    // Data
    aFile->Write<s16>(aNode->mData->mFlags);
    aFile->Write<s16>(aNode->mData->mAnimYTransDivisor);
    aFile->Write<s16>(aNode->mData->mStartFrame);
    aFile->Write<s16>(aNode->mData->mLoopStart);
    aFile->Write<s16>(aNode->mData->mLoopEnd);
    aFile->Write<s16>((aGfxData->mAnimBuffers[_NumPartsBufferIdx]->second.Count() / 6) - 1);
    aFile->Write<u32>(aNode->mData->mLength);
    aGfxData->mAnimBuffers[_ValueBufferIdx]->second.Write(aFile);
    aGfxData->mAnimBuffers[_IndexBufferIdx]->second.Write(aFile);
}

void DynOS_Anim_Table_Write(BinFile* aFile, DataNode<AnimTableData> *aNode) {
    if (!aNode->mData) { return; }

    // Header
    aFile->Write<u8>(DATA_TYPE_ANIMATION_TABLE);
    aNode->mName.Write(aFile);

    // Data
    aFile->Write<u32>((u32)aNode->mData->mAnimations.Count());
    for (auto& _AnimName : aNode->mData->mAnimations) {
        _AnimName.first.Write(aFile);
    }
}

static bool DynOS_Anim_WriteBinary(const SysPath &aOutputFilename, GfxData *aGfxData, DataNode<AnimData> *aNode) {
    BinFile *_File = BinFile::OpenW(aOutputFilename.c_str());
    if (!_File) {
        PrintDataError("  ERROR: Unable to create file \"%s\"", aOutputFilename.c_str());
        return false;
    }

    DynOS_Anim_Write(_File, aGfxData, aNode);

    BinFile::Close(_File);
    return DynOS_Bin_Compress(aOutputFilename);
}

static bool DynOS_Anim_Table_WriteBinary(const SysPath &aOutputFilename, GfxData *aGfxData, DataNode<AnimTableData> *aNode) {
    BinFile *_File = BinFile::OpenW(aOutputFilename.c_str());
    if (!_File) {
        PrintDataError("  ERROR: Unable to create file \"%s\"", aOutputFilename.c_str());
        return false;
    }

    DynOS_Anim_Table_Write(_File, aNode);

    BinFile::Close(_File);
    return DynOS_Bin_Compress(aOutputFilename);
}

  /////////////
 // Reading //
/////////////

DataNode<AnimData> *DynOS_Anim_Load(BinFile *aFile, GfxData *aGfxData) {
    DataNode<AnimData> *_Node = New<DataNode<AnimData>>();

    // Name
    _Node->mName.Read(aFile);

    // Data
    _Node->mData                     = New<AnimData>();
    _Node->mData->mFlags             = aFile->Read<s16>();
    _Node->mData->mAnimYTransDivisor = aFile->Read<s16>();
    _Node->mData->mStartFrame        = aFile->Read<s16>();
    _Node->mData->mLoopStart         = aFile->Read<s16>();
    _Node->mData->mLoopEnd           = aFile->Read<s16>();
    _Node->mData->mNumParts.second   = aFile->Read<s16>();
    _Node->mData->mLength            = aFile->Read<u32>();
    _Node->mData->mValues.second.Read(aFile);
    _Node->mData->mIndex.second.Read(aFile);

    // Append
    if (aGfxData != NULL) {
        aGfxData->mAnimations.Add(_Node);
    }
    
    return _Node;
}

DataNode<AnimTableData> *DynOS_Anim_Table_Load(BinFile *aFile, GfxData *aGfxData) {
    DataNode<AnimTableData> *_Node = New<DataNode<AnimTableData>>();

    // Name
    _Node->mName.Read(aFile);
    
    // Data
    _Node->mData = New<AnimTableData>();
    s32 _Count = aFile->Read<u32>();
    for (u32 i = 0; i < _Count; i++) {
        String _AnimationName;
        _AnimationName.Read(aFile);
        if (_AnimationName != "NULL") {
            _Node->mData->mAnimations.Add({ _AnimationName, NULL });
        }
    }

    // Append
    if (aGfxData != NULL) {
        aGfxData->mAnimationTables.Add(_Node);
    }

    return _Node;
}

DataNode<AnimData>* DynOS_Anim_LoadFromBinary(const SysPath &aFilename, const char *aAnimationName) {
    // Load data from binary file
    DataNode<AnimData>* animationNode = NULL;
    BinFile *_File = DynOS_Bin_Decompress(aFilename);
    if (_File) {
        PrintInfo("Loading animation '%s' from file: %s", aAnimationName, aFilename.c_str());
        u8 type = _File->Read<u8>();
        if (type == DATA_TYPE_ANIMATION) {
            animationNode = DynOS_Anim_Load(_File, NULL);
        }
        BinFile::Close(_File);
    }

    return animationNode;
}

DataNode<AnimTableData>* DynOS_Anim_Table_LoadFromBinary(const SysPath &aFilename, const char *aAnimationTableName) {
    // Load data from binary file
    DataNode<AnimTableData>* animationTableNode = NULL;
    BinFile *_File = DynOS_Bin_Decompress(aFilename);
    if (_File) {
        PrintInfo("Loading animation table '%s' from file: %s", aAnimationTableName, aFilename.c_str());
        u8 type = _File->Read<u8>();
        if (type == DATA_TYPE_ANIMATION_TABLE) {
            animationTableNode = DynOS_Anim_Table_Load(_File, NULL);
        }
        BinFile::Close(_File);
    }

    return animationTableNode;
}

  /////////////////////////////
 // Backwards Compatibility //
/////////////////////////////

void DynOS_Anim_WriteAll(BinFile* aFile, GfxData* aGfxData) {
    for (auto& _Node : aGfxData->mAnimations) {
        DynOS_Anim_Write(aFile, aGfxData, _Node);
    }
}

void DynOS_Anim_Table_WriteAll(BinFile* aFile, GfxData* aGfxData) {
    for (auto& _AnimName : aGfxData->mAnimationTable) {
        // Header
        aFile->Write<u8>(DATA_TYPE_ANIMATION_TABLE);

        // Data
        _AnimName.first.Write(aFile);
    }
}

void DynOS_Anim_Table_LoadSeparate(BinFile *aFile, GfxData *aGfxData) {
    void *_AnimationPtr = NULL;

    // Data
    String _AnimationName; _AnimationName.Read(aFile);
    if (_AnimationName != "NULL") {
        auto _AnimData = aGfxData->mAnimations.Find(_AnimationName);
        if (_AnimData) {
            _AnimationPtr = (void *) _AnimData->mData;
        }
        if (!_AnimationPtr) {
            sys_fatal("Animation not found: %s", _AnimationName.begin());
        }
    }

    // Append
    aGfxData->mAnimationTable.Add({ "", _AnimationPtr });
}

  //////////////
 // Generate //
//////////////

void DynOS_Anim_Generate(const SysPath &aPackFolder, Array<Pair<u64, String>> _AnimsFolders, GfxData *_GfxData) {
    for (auto &_AnimNode : _GfxData->mAnimations) {
        String _AnimRootName = _AnimNode->mName;
        SysPath _AnimFilename = fstring("%s/%s.anim", aPackFolder.c_str(), _AnimRootName.begin());

        // Init
        _GfxData->mErrorCount = 0;
        _GfxData->mLoadIndex = 0;

        // Parse data
        PrintInfoNoNewLine("%s.anim: Animation identifier: %llX - Processing... ", _AnimRootName.begin(), _AnimNode->mDataIdentifier);
        DynOS_Anim_Parse(_GfxData, _AnimNode, true);

        // Write if no error
        if (_GfxData->mErrorCount == 0) {
            DynOS_Anim_WriteBinary(_AnimFilename, _GfxData, _AnimNode);
        } else {
            PrintError("  %u error(s): Unable to parse data", _GfxData->mErrorCount);
        }

    }
    // Clear data pointers
    ClearGfxDataNodes(_GfxData->mAnimations);

    for (auto &_AnimTableNode : _GfxData->mAnimationTables) {
        String _AnimTableRootName = _AnimTableNode->mName;
        SysPath _AnimTableFilename = fstring("%s/%s.atbl", aPackFolder.c_str(), _AnimTableRootName.begin());

        // Init
        _GfxData->mErrorCount = 0;
        _GfxData->mLoadIndex = 0;

        // Parse data
        PrintInfoNoNewLine("%s.atbl: Animation identifier: %llX - Processing... ", _AnimTableRootName.begin(), _AnimTableNode->mDataIdentifier);

        // Write if no error
        if (_GfxData->mErrorCount == 0) {
            DynOS_Anim_Table_WriteBinary(_AnimTableFilename, _GfxData, _AnimTableNode);
        } else {
            PrintError("  %u error(s): Unable to parse data", _GfxData->mErrorCount);
        }

    }
    // Clear data pointers
    ClearGfxDataNodes(_GfxData->mAnimationTables);
}

void DynOS_Anim_GeneratePack(const SysPath &aPackFolder) {
    Print("Processing animations: \"%s\"", aPackFolder.c_str());

    if (!DynOS_ShouldGeneratePack(aPackFolder,  { ".anim", ".atbl" })) {
        return;
    }

    Array<Pair<u64, String>> _AnimsFolders;
    GfxData *_GfxData = New<GfxData>();

    DIR *aPackDir = opendir(aPackFolder.c_str());
    if (aPackDir) {
        struct dirent *_PackEnt = NULL;
        while ((_PackEnt = readdir(aPackDir)) != NULL) {

            // Skip . and ..
            if (SysPath(_PackEnt->d_name) == ".") continue;
            if (SysPath(_PackEnt->d_name) == "..") continue;

            // Compress .anim files to gain some space
            SysPath _Filename = fstring("%s/%s", aPackFolder.c_str(), _PackEnt->d_name);
            if ((SysPath(_PackEnt->d_name).find(".anim") != SysPath::npos || SysPath(_PackEnt->d_name).find(".atbl") != SysPath::npos) && !DynOS_Bin_IsCompressed(_Filename)) {
                if (configCompressOnStartup) { DynOS_Bin_Compress(_Filename); }
                continue;
            }

            SysPath _SrcFile = fstring("%s/%s", aPackFolder.c_str(), _PackEnt->d_name);
            if (fs_sys_file_exists(_SrcFile.c_str()) && (SysPath(_PackEnt->d_name).find(".c") != SysPath::npos)) {
                _GfxData->mDataIdentifier = 0;

                DynOS_Read_Source(_GfxData, _SrcFile.c_str());
                DynOS_Anim_GetBuffers(_GfxData, _SrcFile.c_str());
                DynOS_Anim_Table_Parse(_GfxData, _SrcFile.c_str());

                if (_GfxData->mDataIdentifier != 0) {
                    _AnimsFolders.Add({ _GfxData->mDataIdentifier, String(_PackEnt->d_name) });
                }
            }
        }
        closedir(aPackDir);
    }

    DynOS_Anim_Generate(aPackFolder, _AnimsFolders, _GfxData);
    DynOS_Gfx_Free(_GfxData);
}
