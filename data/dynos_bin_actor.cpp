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
 // Writing //
/////////////

static bool DynOS_Actor_WriteBinary(const SysPath &aOutputFilename, GfxData *aGfxData) {
    BinFile *_File = BinFile::OpenW(aOutputFilename.c_str());
    if (!_File) {
        PrintDataError("  ERROR: Unable to create file \"%s\"", aOutputFilename.c_str());
        return false;
    }

    for (u64 i = 0; i != aGfxData->mLoadIndex; ++i) {
        for (auto &_Node : aGfxData->mLights) {
            if (_Node->mLoadIndex == i) {
                DynOS_Lights_Write(_File, aGfxData, _Node);
            }
        }
        for (auto &_Node : aGfxData->mLight0s) {
            if (_Node->mLoadIndex == i) {
                DynOS_Light0_Write(_File, aGfxData, _Node);
            }
        }
        for (auto &_Node : aGfxData->mLightTs) {
            if (_Node->mLoadIndex == i) {
                DynOS_LightT_Write(_File, aGfxData, _Node);
            }
        }
        for (auto &_Node : aGfxData->mAmbientTs) {
            if (_Node->mLoadIndex == i) {
                DynOS_AmbientT_Write(_File, aGfxData, _Node);
            }
        }
        for (auto &_Node : aGfxData->mTextures) {
            if (_Node->mLoadIndex == i) {
                DynOS_Tex_Write(_File, aGfxData, _Node);
            }
        }
        for (auto &_Node : aGfxData->mTextureLists) {
            if (_Node->mLoadIndex == i) {
                DynOS_TexList_Write(_File, aGfxData, _Node);
            }
        }
        for (auto &_Node : aGfxData->mVertices) {
            if (_Node->mLoadIndex == i) {
                DynOS_Vtx_Write(_File, aGfxData, _Node);
            }
        }
        for (auto &_Node : aGfxData->mDisplayLists) {
            if (_Node->mLoadIndex == i) {
                DynOS_Gfx_Write(_File, aGfxData, _Node);
            }
        }
        for (auto &_Node : aGfxData->mGeoLayouts) {
            if (_Node->mLoadIndex == i) {
                DynOS_Geo_Write(_File, aGfxData, _Node);
            }
        }
    }
    DynOS_Anim_Write(_File, aGfxData);
    DynOS_Anim_Table_Write(_File, aGfxData);
    BinFile::Close(_File);
    return DynOS_Bin_Compress(aOutputFilename);
}

  /////////////
 // Reading //
/////////////

GfxData *DynOS_Actor_LoadFromBinary(const SysPath &aPackFolder, const char *aActorName, const SysPath &aFilename, bool aAddToPack) {
    // Look for pack in cache
    PackData* _Pack = DynOS_Pack_GetFromPath(aPackFolder);

    // Look for actor in pack
    if (_Pack) {
        auto _ActorPair = DynOS_Pack_GetActor(_Pack, aActorName);
        if (_ActorPair != NULL) {
            return _ActorPair->second;
        }
    }

    // Load data from binary file
    GfxData *_GfxData = NULL;
    BinFile *_File = DynOS_Bin_Decompress(aFilename);
    if (_File) {
        _GfxData = New<GfxData>();
        for (bool _Done = false; !_Done;) {
            switch (_File->Read<u8>()) {
                case DATA_TYPE_LIGHT:           DynOS_Lights_Load    (_File, _GfxData); break;
                case DATA_TYPE_LIGHT_0:         DynOS_Light0_Load    (_File, _GfxData); break;
                case DATA_TYPE_LIGHT_T:         DynOS_LightT_Load    (_File, _GfxData); break;
                case DATA_TYPE_AMBIENT_T:       DynOS_AmbientT_Load  (_File, _GfxData); break;
                case DATA_TYPE_TEXTURE:         DynOS_Tex_Load       (_File, _GfxData); break;
                case DATA_TYPE_TEXTURE_LIST:    DynOS_TexList_Load   (_File, _GfxData); break;
                case DATA_TYPE_VERTEX:          DynOS_Vtx_Load       (_File, _GfxData); break;
                case DATA_TYPE_DISPLAY_LIST:    DynOS_Gfx_Load       (_File, _GfxData); break;
                case DATA_TYPE_GEO_LAYOUT:      DynOS_Geo_Load       (_File, _GfxData); break;
                case DATA_TYPE_ANIMATION:       DynOS_Anim_Load      (_File, _GfxData); break;
                case DATA_TYPE_ANIMATION_TABLE: DynOS_Anim_Table_Load(_File, _GfxData); break;
                case DATA_TYPE_GFXDYNCMD:       DynOS_GfxDynCmd_Load (_File, _GfxData); break;
                default:                        _Done = true;                           break;
            }
        }
        BinFile::Close(_File);
    }

    // Add data to cache, even if not loaded
    if (aAddToPack) {
        if (_Pack) {
            DynOS_Pack_AddActor(_Pack, aActorName, _GfxData);
        } else {
            _Pack = DynOS_Pack_Add(aPackFolder);
            DynOS_Pack_AddActor(_Pack, aActorName, _GfxData);
        }
    }

    return _GfxData;
}

  //////////////
 // Generate //
//////////////

static String GetActorFolder(const Array<Pair<u64, String>> &aActorsFolders, u64 aModelIdentifier) {
    for (const auto &_Pair : aActorsFolders) {
        if (_Pair.first == aModelIdentifier) {
            return _Pair.second;
        }
    }
    return String();
}

static void DynOS_Actor_Generate(const SysPath &aPackFolder, Array<Pair<u64, String>> _ActorsFolders, GfxData *_GfxData) {
    // do not regen this folder if we find any existing bins
    for (s32 geoIndex = _GfxData->mGeoLayouts.Count() - 1; geoIndex >= 0; geoIndex--) {
        auto &_GeoNode = _GfxData->mGeoLayouts[geoIndex];
        String _GeoRootName = _GeoNode->mName;

        // If there is an existing binary file for this layout, skip and go to the next actor
        SysPath _BinFilename = fstring("%s/%s.bin", aPackFolder.c_str(), _GeoRootName.begin());
        if (fs_sys_file_exists(_BinFilename.c_str())) {
#ifdef DEVELOPMENT
            // Compress file to gain some space
            if (!DynOS_Bin_IsCompressed(_BinFilename)) {
                DynOS_Bin_Compress(_BinFilename);
            }
#endif
            return;
        }
    }

    // generate in reverse order to detect children
    for (s32 geoIndex = _GfxData->mGeoLayouts.Count() - 1; geoIndex >= 0; geoIndex--) {
        auto &_GeoNode = _GfxData->mGeoLayouts[geoIndex];

        // if this is a child geo layout, don't save it as a bin
        if (_GfxData->mChildGeoLayouts.Find(_GeoNode) != -1) {
            continue;
        }

        String _GeoRootName = _GeoNode->mName;

        // If there is an existing binary file for this layout, skip and go to the next actor
        SysPath _BinFilename = fstring("%s/%s.bin", aPackFolder.c_str(), _GeoRootName.begin());

        // Init
        _GfxData->mLoadIndex                  = 0;
        _GfxData->mErrorCount                 = 0;
        _GfxData->mModelIdentifier            = _GeoNode->mModelIdentifier;
        _GfxData->mPackFolder                 = aPackFolder;
        _GfxData->mPointerList                = { NULL }; // The NULL pointer is needed, so we add it here
        _GfxData->mPointerOffsetList          = { };
        _GfxData->mLuaPointerList             = { };
        _GfxData->mLuaTokenList               = { };
        _GfxData->mGfxContext.mCurrentTexture = NULL;
        _GfxData->mGfxContext.mCurrentPalette = NULL;
        _GfxData->mGeoNodeStack.Clear();

        // Parse data
        PrintNoNewLine("%s.bin: Model identifier: %X - Processing... ", _GeoRootName.begin(), _GfxData->mModelIdentifier);
        PrintConsole(CONSOLE_MESSAGE_INFO, "%s.bin: Model identifier: %X - Processing... ", _GeoRootName.begin(), _GfxData->mModelIdentifier);
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
        DynOS_Anim_ScanFolder(_GfxData, _AnimsFolder);

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
            DynOS_Actor_WriteBinary(_BinFilename, _GfxData);
        } else {
            PrintError("  %u error(s): Unable to parse data", _GfxData->mErrorCount);
        }
        // Clear data pointers
        ClearGfxDataNodes(_GfxData->mLights);
        ClearGfxDataNodes(_GfxData->mLight0s);
        ClearGfxDataNodes(_GfxData->mLightTs);
        ClearGfxDataNodes(_GfxData->mAmbientTs);
        ClearGfxDataNodes(_GfxData->mTextures);
        ClearGfxDataNodes(_GfxData->mTextureLists);
        ClearGfxDataNodes(_GfxData->mVertices);
        ClearGfxDataNodes(_GfxData->mDisplayLists);
        ClearGfxDataNodes(_GfxData->mGeoLayouts);
        ClearGfxDataNodes(_GfxData->mCollisions);
        _GfxData->mPointerList.Clear();
        _GfxData->mPointerOffsetList.Clear();
        _GfxData->mLuaPointerList.Clear();
        _GfxData->mLuaTokenList.Clear();
    }

    _GfxData->mChildGeoLayouts.Clear();
}

void DynOS_Actor_GeneratePack(const SysPath &aPackFolder) {
    Print("Processing actors: \"%s\"", aPackFolder.c_str());
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

#ifdef DEVELOPMENT
            // Compress .bin files to gain some space
            SysPath _Filename = fstring("%s/%s", aPackFolder.c_str(), _PackEnt->d_name);
            if (SysPath(_PackEnt->d_name).find(".bin") != SysPath::npos && !DynOS_Bin_IsCompressed(_Filename)) {
                DynOS_Bin_Compress(_Filename);
                continue;
            }
#endif

            // For each subfolder, read tokens from model.inc.c and geo.inc.c
            SysPath _Folder = fstring("%s/%s", aPackFolder.c_str(), _PackEnt->d_name);
            if (fs_sys_dir_exists(_Folder.c_str())) {
                _GfxData->mModelIdentifier = 0;

                // Remember the geo layout count
                s32 prevGeoLayoutCount = _GfxData->mGeoLayouts.Count();

                DynOS_Read_Source(_GfxData, fstring("%s/texture.inc.c", _Folder.c_str()));
                DynOS_Read_Source(_GfxData, fstring("%s/model.inc.c", _Folder.c_str()));
                DynOS_Read_Source(_GfxData, fstring("%s/geo.inc.c", _Folder.c_str()));
                DynOS_Read_Source(_GfxData, fstring("%s/collision.inc.c", _Folder.c_str()));

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
