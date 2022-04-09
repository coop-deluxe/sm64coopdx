#include "dynos.cpp.h"

static Array<Pair<const char*, void *>> sDynosCustomActors;

// TODO: the cleanup/refactor didn't really go as planned.
//       clean up the actor management code more

void DynOS_Actor_AddCustom(const SysPath &aPackFolder, const char *aActorName) {
    // check for duplicates
    bool isUnique = true;
    s32 foundIndex = -1;
    for (s32 i = 0; i < DynOS_Actor_GetCount(); ++i) {
        if (!strcmp(DynOS_Actor_GetName(i), aActorName)) {
            isUnique = false;
            foundIndex = i;
            break;
        }
    }

    u16 actorLen = strlen(aActorName);
    char* actorName = (char*)calloc(1, sizeof(char) * (actorLen + 1));
    strcpy(actorName, aActorName);

    GfxData *_GfxData = DynOS_Actor_LoadFromBinary(aPackFolder, actorName);
    if (!_GfxData) {
        free(actorName);
        return;
    }

    void* geoLayout = (*(_GfxData->mGeoLayouts.end() - 1))->mData;
    if (!geoLayout) {
        free(actorName);
        return;
    }

    // Add to custom actors
    s32 index = DynOS_Actor_GetCount();
    if (isUnique) {
        sDynosCustomActors.Add({ actorName, geoLayout });
    } else {
        index = foundIndex;
        free(actorName);
    }

    // Alloc and init the actors gfx list
    Array<ActorGfx> &pActorGfxList = DynOS_Gfx_GetActorList();
    pActorGfxList.Resize(DynOS_Actor_GetCount());
    pActorGfxList[index].mPackIndex = 99;
    pActorGfxList[index].mGfxData   = _GfxData;
    pActorGfxList[index].mGraphNode = (GraphNode *) DynOS_Geo_GetGraphNode(geoLayout, true);
}

s32 DynOS_Actor_GetCount() {
    return (s32) DynOS_Builtin_Actor_GetCount() + sDynosCustomActors.Count();
}

const char *DynOS_Actor_GetName(s32 aIndex) {
    s32 builtinCount = DynOS_Builtin_Actor_GetCount();
    if (aIndex < builtinCount) { return (const char *) DynOS_Builtin_Actor_GetNameFromIndex(aIndex); }
    return sDynosCustomActors[aIndex - builtinCount].first;
}

const void *DynOS_Actor_GetLayoutFromIndex(s32 aIndex) {
    s32 builtinCount = DynOS_Builtin_Actor_GetCount();
    if (aIndex < builtinCount) { return (const void *) DynOS_Builtin_Actor_GetFromIndex(aIndex); }
    return sDynosCustomActors[aIndex - builtinCount].second;
}

const void *DynOS_Actor_GetLayoutFromName(const char *aActorName) {
    if (aActorName == NULL) { return NULL; }

    // check levels
    auto& levelsArray = DynOS_Lvl_GetArray();
    for (auto& lvl : levelsArray) {
        for (auto& geo : lvl.second->mGeoLayouts) {
            if (geo->mName == aActorName) {
                return geo->mData;
            }
        }
    }

    // check actors
    for (s32 i = 0; i < DynOS_Actor_GetCount(); ++i) {
        if (!strcmp(DynOS_Actor_GetName(i), aActorName)) {
            return DynOS_Actor_GetLayoutFromIndex(i);
        }
    }

    return NULL;
}

s32 DynOS_Actor_GetIndex(const void *aGeoLayout) {
    for (s32 i = 0; i < DynOS_Actor_GetCount(); ++i) {
        if (DynOS_Actor_GetLayoutFromIndex(i) == aGeoLayout) {
            return i;
        }
    }
    return -1;
}

bool DynOS_Actor_IsCustom(s32 aIndex) {
    s32 builtinCount = DynOS_Builtin_Actor_GetCount();
    return aIndex >= builtinCount;
}
