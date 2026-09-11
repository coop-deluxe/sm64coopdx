#include <deque>
#include <regex>
#include <charconv>
#include "dynos.cpp.h"
extern "C" {
#include "engine/graph_node.h"
}

static std::deque<PackData>& DynosPacks() {
    static std::deque<PackData> sDynosPacks;
    return sDynosPacks;
}

static bool ParseU8(const std::string& s, u8& out) {
    unsigned int value = 0;
    auto [ptr, ec] = std::from_chars(s.data(), s.data() + s.size(), value);

    // Reject:
    // - parse errors
    // - overflow
    // - trailing junk
    // - values outside u8 range
    if (ec != std::errc() || ptr != s.data() + s.size() || value > 0xFF) {
        return false;
    }

    out = static_cast<u8>(value);
    return true;
}

static void ScanPackBins(struct PackData* aPack) {
    DIR *_PackDir = opendir(aPack->mPath.c_str());
    if (!_PackDir) { return; }

    struct dirent *_PackEnt = NULL;
    while ((_PackEnt = readdir(_PackDir)) != NULL) {
        // Skip . and ..
        if (SysPath(_PackEnt->d_name) == ".") continue;
        if (SysPath(_PackEnt->d_name) == "..") continue;

        SysPath _FileName = fstring("%s/%s", aPack->mPath.c_str(), _PackEnt->d_name);
        s32 length = strlen(_PackEnt->d_name);

        // check for actors
        if (length > 4 && !strncmp(&_PackEnt->d_name[length - 4], ".bin", 4)) {
            String _ActorName = _PackEnt->d_name;
            _ActorName[length - 4] = '\0';
            DynOS_Actor_LoadFromBinary(aPack->mPath, _ActorName.begin(), _FileName, true);
        }

        // check for textures
        if (length > 4 && !strncmp(&_PackEnt->d_name[length - 4], ".tex", 4)) {
            String _TexName = _PackEnt->d_name;
            _TexName[length - 4] = '\0';
            DynOS_Tex_LoadFromBinary(aPack->mPath, _FileName, _TexName.begin(), true);
        }

        // check for sequences
        if (length > 4 && !strncmp(&_PackEnt->d_name[length - 4], ".m64", 4)) {
            String _SeqName = _PackEnt->d_name;
            _SeqName[length - 4] = '\0';
            std::string seqName = _SeqName.begin();
            std::regex re(".*\\.(\\d+)\\.(\\d+)\\.(\\d+)$");
            std::smatch match;
            bool success = false;
            if (std::regex_match(seqName, match, re) && match.size() == 4) {
                u8 sequenceId, bankId, defaultVolume;
                if (ParseU8(match[1].str(), sequenceId) &&
                    ParseU8(match[2].str(), bankId) &&
                    ParseU8(match[3].str(), defaultVolume)
                ) {
                    AudioOverrideEntry* audioOverride = DynOS_Audio_CreateOverride(
                        sequenceId, bankId, defaultVolume, _FileName.c_str(), true
                    );
                    if (audioOverride) {
                        aPack->mAudioOverrides.push_back(audioOverride);
                    }
                    success = true; // Not a formatting error
                }
            }
            if (!success) {
                PrintError(
                    "  ERROR! Invalid sequence override filename (expected format: <name>.<sequenceId>.<bankId>.<defaultVolume>.m64): '%s.m64'",
                    _SeqName.begin()
                );
            }
        }
    }
}

static void DynOS_Pack_ActivateActor(s32 aPackIndex, std::pair<std::string, GfxData *> &pair) {
    const char* aActorName = pair.first.c_str();
    GfxData* aGfxData = pair.second;

    auto& geoNode = *(aGfxData->mGeoLayouts.end() - 1);
    u32 id = 0;
    GraphNode* graphNode = DynOS_Model_LoadGeo(&id, MODEL_POOL_PERMANENT, geoNode->mData, true);
    if (graphNode == NULL) { return; }

    const void* georef = DynOS_Builtin_Actor_GetFromName(aActorName);
    graphNode->georef = georef;

    ActorGfx actorGfx;
    actorGfx.mGfxData   = aGfxData;
    actorGfx.mGraphNode = graphNode;
    actorGfx.mPackIndex = aPackIndex;

    for (const auto &vtxNode : aGfxData->mVertices) {
        if (vtxNode->mFlags & GRAPH_EXTRA_FORCE_3D) {
            actorGfx.mGraphNode->extraFlags |= GRAPH_EXTRA_FORCE_3D;
            break;
        }
    }

    DynOS_Actor_Valid(georef, actorGfx);
}

static void DynOS_Pack_DeactivateActor(s32 aPackIndex, std::pair<std::string, GfxData *> &pair) {
    const char* aActorName = pair.first.c_str();
    const void* georef = DynOS_Builtin_Actor_GetFromName(aActorName);
    DynOS_Actor_Invalid(georef, aPackIndex);

    // figure out which actor to replace it with
    std::pair<std::string, GfxData *> *_Replacement = NULL;
    s32 _ReplacementPackIndex = 0;
    for (auto& _Pack : DynosPacks()) {
        if (!_Pack.mEnabled) { continue; }
        auto _Tmp = DynOS_Pack_GetActor(&_Pack, aActorName);
        if (_Tmp != NULL) {
            _Replacement = _Tmp;
            _ReplacementPackIndex = _Pack.mIndex;
        }
    }
    if (_Replacement != NULL) {
        DynOS_Pack_ActivateActor(_ReplacementPackIndex, *_Replacement);
    }
}

s32 DynOS_Pack_GetCount() {
    return DynosPacks().size();
}

void DynOS_Pack_SetEnabled(PackData* aPack, bool aEnabled) {
    if (aPack == NULL) { return; }
    aPack->mEnabled = aEnabled;

    if (aEnabled && !aPack->mLoaded) {
        ScanPackBins(aPack);
        aPack->mLoaded = true;
    }

    if (aEnabled) {
        for (auto& pair : aPack->mGfxData) {
            DynOS_Pack_ActivateActor(aPack->mIndex, pair);
        }
        for (auto& _Tex : aPack->mTextures) {
            DynOS_Tex_Activate(_Tex, false);
        }
        for (auto& audioOverride : aPack->mAudioOverrides) {
            DynOS_Audio_ActivatePackOverride(audioOverride);
        }
    } else {
        for (auto& pair : aPack->mGfxData) {
            DynOS_Pack_DeactivateActor(aPack->mIndex, pair);
        }
        for (auto& _Tex : aPack->mTextures) {
            DynOS_Tex_Deactivate(_Tex);
        }
        for (auto& audioOverride : aPack->mAudioOverrides) {
            DynOS_Audio_DeactivatePackOverride(audioOverride);
        }
    }
    DynOS_Actor_Override_All();
}

PackData* DynOS_Pack_GetFromIndex(s32 aIndex) {
    auto& _DynosPacks = DynosPacks();
    if (aIndex < 0 || aIndex >= _DynosPacks.size()) {
        return NULL;
    }
    return &_DynosPacks[aIndex];
}

PackData* DynOS_Pack_GetFromPath(const SysPath& aPath) {
    for (auto& packData : DynosPacks()) {
        if (packData.mPath == aPath) {
            return &packData;
        }
    }
    return NULL;
}

PackData* DynOS_Pack_GetFromDisplayName(const char* aDisplayName) {
    for (auto& packData : DynosPacks()) {
        if (!strcmp(packData.mDisplayName.begin(), aDisplayName)) {
            return &packData;
        }
    }
    return NULL;
}

PackData* DynOS_Pack_Add(const SysPath& aPath) {
    PackData* existing = DynOS_Pack_GetFromPath(aPath);
    if (existing != NULL) { return existing; }

    // extract basename
    const char* displayName = aPath.c_str();
    const char* ctoken = displayName;
    while (*ctoken != '\0') {
        if (*ctoken == *PATH_SEPARATOR || *ctoken == *PATH_SEPARATOR_ALT) {
            if (*(ctoken + 1) != '\0') {
                displayName = (ctoken + 1);
            }
        }
        ctoken++;
    }

    existing = DynOS_Pack_GetFromDisplayName(displayName);
    if (existing != NULL) { return existing; }


    auto& _DynosPacks = DynosPacks();
    s32 index = _DynosPacks.size();
    const PackData packData = {
        .mIndex = index,
        .mEnabled = false,
        .mPath = aPath,
        .mDisplayName = "",
        .mGfxData = {},
        .mTextures = {},
        .mLoaded = false,
    };
    _DynosPacks.push_back(packData);

    PackData* _Pack = &_DynosPacks.back();

    _Pack->mDisplayName = displayName;

    return _Pack;
}

std::pair<std::string, GfxData *>* DynOS_Pack_GetActor(PackData* aPackData, const char* aActorName) {
    if (aPackData == NULL || aActorName == NULL) {
        return NULL;
    }
    for (auto& pair : aPackData->mGfxData) {
        if (pair.first == aActorName) {
            return &pair;
        }
    }
    return NULL;
}

void DynOS_Pack_AddActor(PackData* aPackData, const char* aActorName, GfxData* aGfxData) {
    if (aPackData == NULL || aActorName == NULL || aGfxData == NULL) {
        return;
    }

    s32 index = aPackData->mGfxData.size();
    aPackData->mGfxData.emplace_back(aActorName, aGfxData);

    if (aPackData->mEnabled) {
        DynOS_Pack_ActivateActor(aPackData->mIndex, aPackData->mGfxData[index]);
    }
}

DataNode<TexData>* DynOS_Pack_GetTex(PackData* aPackData, const char* aTexName) {
    if (aPackData == NULL || aTexName == NULL) {
        return NULL;
    }

    for (auto& _Tex : aPackData->mTextures) {
        if (!strcmp(_Tex->mName.begin(), aTexName)) {
            return _Tex;
        }
    }
    return NULL;
}

void DynOS_Pack_AddTex(PackData* aPackData, DataNode<TexData>* aTexData) {
    if (aPackData == NULL || aTexData == NULL) {
        return;
    }

    aPackData->mTextures.push_back(aTexData);

    if (aPackData->mEnabled) {
        DynOS_Tex_Activate(aTexData, false);
    }
}
