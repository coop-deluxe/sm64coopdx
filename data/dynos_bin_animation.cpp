#include "dynos.cpp.h"

  /////////////
 // Parsing //
/////////////

static void ScanAnimationDataFile(GfxData *aGfxData, const SysPath &aFilename) {
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
                            PrintDataError("  ERROR: %s: Not enough data", _DataName.begin());
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

  /////////////
 // Writing //
/////////////

void DynOS_Anim_Write(BinFile* aFile, GfxData* aGfxData) {
    for (auto& _Node : aGfxData->mAnimations) {

        // Value buffer
        s32 _ValueBufferIdx = aGfxData->mAnimValues.FindIf([&_Node](const AnimBuffer<s16> *aAnimBuffer) { return aAnimBuffer->first == _Node->mData->mValues.first; });
        if (_ValueBufferIdx == -1) {
            continue;
        }

        // Index buffer
        s32 _IndexBufferIdx = aGfxData->mAnimIndices.FindIf([&_Node](const AnimBuffer<u16> *aAnimBuffer) { return aAnimBuffer->first == _Node->mData->mIndex.first; });
        if (_IndexBufferIdx == -1) {
            continue;
        }

        // Unk0A buffer
        s32 _Unk0ABufferIdx = aGfxData->mAnimIndices.FindIf([&_Node](const AnimBuffer<u16> *aAnimBuffer) { return aAnimBuffer->first == _Node->mData->mUnk0A.first; });
        if (_Unk0ABufferIdx == -1) {
            continue;
        }

        // Header
        aFile->Write<u8>(DATA_TYPE_ANIMATION);
        _Node->mName.Write(aFile);

        // Data
        aFile->Write<s16>(_Node->mData->mFlags);
        aFile->Write<s16>(_Node->mData->mUnk02);
        aFile->Write<s16>(_Node->mData->mUnk04);
        aFile->Write<s16>(_Node->mData->mUnk06);
        aFile->Write<s16>(_Node->mData->mUnk08);
        aFile->Write<s16>((aGfxData->mAnimIndices[_Unk0ABufferIdx]->second.Count() / 6) - 1);
        aFile->Write<u32>(_Node->mData->mLength);
        aGfxData->mAnimValues[_ValueBufferIdx]->second.Write(aFile);
        aGfxData->mAnimIndices[_IndexBufferIdx]->second.Write(aFile);
    }
}

void DynOS_Anim_Table_Write(BinFile* aFile, GfxData* aGfxData) {
    for (auto& _AnimName : aGfxData->mAnimationTable) {

        // Header
        aFile->Write<u8>(DATA_TYPE_ANIMATION_TABLE);

        // Data
        _AnimName.first.Write(aFile);
    }
}

  /////////////
 // Reading //
/////////////

void DynOS_Anim_Load(BinFile *aFile, GfxData *aGfxData) {
    DataNode<AnimData> *_Node = New<DataNode<AnimData>>();

    // Name
    _Node->mName.Read(aFile);

    // Data
    _Node->mData = New<AnimData>();
    _Node->mData->mFlags = aFile->Read<s16>();
    _Node->mData->mUnk02 = aFile->Read<s16>();
    _Node->mData->mUnk04 = aFile->Read<s16>();
    _Node->mData->mUnk06 = aFile->Read<s16>();
    _Node->mData->mUnk08 = aFile->Read<s16>();
    _Node->mData->mUnk0A.second = aFile->Read<s16>();
    _Node->mData->mLength = aFile->Read<u32>();
    _Node->mData->mValues.second.Read(aFile);
    _Node->mData->mIndex.second.Read(aFile);

    // Append
    aGfxData->mAnimations.Add(_Node);
}

void DynOS_Anim_Table_Load(BinFile *aFile, GfxData *aGfxData) {
    void *_AnimationPtr = NULL;

    // Data
    String _AnimationName; _AnimationName.Read(aFile);
    if (_AnimationName != "NULL") {
        for (auto &_AnimData : aGfxData->mAnimations) {
            if (_AnimData->mName == _AnimationName) {
                _AnimationPtr = (void *) _AnimData->mData;
                break;
            }
        }
        if (!_AnimationPtr) {
            sys_fatal("Animation not found: %s", _AnimationName.begin());
        }
    }

    // Append
    aGfxData->mAnimationTable.Add({ "", _AnimationPtr });
}
