#include "dynos.cpp.h"
extern "C" {
#include "engine/graph_node.h"
}

static Array<PackData>& DynosPacks() {
    static Array<PackData> sDynosPacks;
    return sDynosPacks;
}

static void DynOS_Pack_ActivateActor(s32 aPackIndex, Pair<const char *, GfxData *>& pair) {
    const char* aActorName = pair.first;
    GfxData* aGfxData = pair.second;
    
    GraphNode* graphNode = (GraphNode *) DynOS_Geo_GetGraphNode((*(aGfxData->mGeoLayouts.end() - 1))->mData, false);
    if (graphNode == NULL) { return; }

    const void* georef = DynOS_Builtin_Actor_GetFromName(aActorName);
    graphNode->georef = georef;

    ActorGfx actorGfx;
    actorGfx.mGfxData   = aGfxData;
    actorGfx.mGraphNode = graphNode;
    actorGfx.mPackIndex = aPackIndex;

    // Check if we should disable billboards
    // TODO: make this smarter
    /*u32 vertices = 0;
    for (auto& vtx : aGfxData->mVertices) {
        vertices += vtx->mSize;
    }
    if (vertices > 6) {
        actorGfx.mGraphNode->extraFlags |= GRAPH_EXTRA_FORCE_3D;
    }*/

    DynOS_Actor_Valid(georef, actorGfx);
}

static void DynOS_Pack_DeactivateActor(s32 aPackIndex, Pair<const char *, GfxData *>& pair) {
    const char* aActorName = pair.first;
    const void* georef = DynOS_Builtin_Actor_GetFromName(aActorName);
    DynOS_Actor_Invalid(georef, aPackIndex);

    // figure out which actor to replace it with
    Pair<const char *, GfxData *>* _Replacement = NULL;
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
    return DynosPacks().Count();
}

void DynOS_Pack_SetEnabled(PackData* aPack, bool aEnabled) {
    if (aPack == NULL) { return; }
    aPack->mEnabled = aEnabled;
    aPack->mEnabledSet = true;

    if (aEnabled) {
        for (auto& pair : aPack->mGfxData) {
            DynOS_Pack_ActivateActor(aPack->mIndex, pair);
        }
    } else {
        for (auto& pair : aPack->mGfxData) {
            DynOS_Pack_DeactivateActor(aPack->mIndex, pair);
        }
    }
    DynOS_Actor_Override_All();
}

PackData* DynOS_Pack_GetFromIndex(s32 aIndex) {
    auto& _DynosPacks = DynosPacks();
    if (aIndex < 0 || aIndex >= _DynosPacks.Count()) {
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

PackData* DynOS_Pack_Add(const SysPath& aPath) {
    PackData* existing = DynOS_Pack_GetFromPath(aPath);
    if (existing != NULL) { return existing; }

    auto& _DynosPacks = DynosPacks();
    s32 index = _DynosPacks.Count();
    _DynosPacks.Add({
        .mIndex = index,
        .mPath = aPath,
        .mGfxData = {},
    });

    PackData* _Pack = &_DynosPacks[index];

    // extract basename
    const char* cpath = aPath.c_str();
    const char* ctoken = cpath;
    while (*ctoken != '\0') {
        if (*ctoken == '/' || *ctoken == '\\') {
            if (*(ctoken + 1) != '\0') {
                cpath = (ctoken + 1);
            }
        }
        ctoken++;
    }
    _Pack->mDisplayName = cpath;

    _Pack->mEnabled = true;
    _Pack->mEnabledSet = false;

    return _Pack;
}

void DynOS_Pack_Init() {
    for (auto& pack : DynosPacks()) {
        if (!pack.mEnabledSet) {
            DynOS_Pack_SetEnabled(&pack, pack.mEnabled);
        }
    }
}

Pair<const char *, GfxData *>* DynOS_Pack_GetActor(PackData* aPackData, const char* aActorName) {
    if (aPackData == NULL || aActorName == NULL) {
        return NULL;
    }
    for (auto& pair : aPackData->mGfxData) {
        if (!strcmp(pair.first, aActorName)) {
            return &pair;
        }
    }
    return NULL;
}

void DynOS_Pack_AddActor(PackData* aPackData, const char* aActorName, GfxData* aGfxData) {
    if (aPackData == NULL || aActorName == NULL || aGfxData == NULL) {
        return;
    }

    s32 index = aPackData->mGfxData.Count();
    aPackData->mGfxData.Add({ aActorName, aGfxData });

    if (aPackData->mEnabled) {
        DynOS_Pack_ActivateActor(aPackData->mIndex, aPackData->mGfxData[index]);
    }
}
