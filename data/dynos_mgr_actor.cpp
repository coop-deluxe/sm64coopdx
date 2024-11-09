#include <map>
#include <algorithm>
#include "dynos.cpp.h"

extern "C" {
#include "object_fields.h"
#include "game/level_update.h"
#include "game/object_list_processor.h"
#include "pc/configfile.h"
#include "pc/lua/smlua_hooks.h"
}

// Static maps/arrays
static std::map<const void*, ActorGfx>& DynosValidActors() {
    static std::map<const void*, ActorGfx> sDynosValidActors;
    return sDynosValidActors;
}

static Array<Pair<const char*, void *>>& DynosCustomActors() {
    static Array<Pair<const char*, void *>> sDynosCustomActors;
    return sDynosCustomActors;
}

// TODO: the cleanup/refactor didn't really go as planned.
//       clean up the actor management code more

void DynOS_Actor_AddCustom(const SysPath &aFilename, const char *aActorName) {
    const void* georef = DynOS_Builtin_Actor_GetFromName(aActorName);

    u16 actorLen = strlen(aActorName);
    char* actorName = (char*)calloc(1, sizeof(char) * (actorLen + 1));
    strcpy(actorName, aActorName);

    GfxData *_GfxData = DynOS_Actor_LoadFromBinary(aFilename, actorName, aFilename, false);
    if (!_GfxData) {
        PrintError("  ERROR: Couldn't load Actor Binary \"%s\" from \"%s\"", actorName, aFilename.c_str());
        free(actorName);
        return;
    }

    void* geoLayout = (*(_GfxData->mGeoLayouts.end() - 1))->mData;
    if (!geoLayout) {
        PrintError("  ERROR: Couldn't load geo layout for \"%s\"", actorName);
        free(actorName);
        return;
    }

    // Alloc and init the actors gfx list
    u32 id = 0;
    ActorGfx actorGfx   = {  };
    actorGfx.mGfxData   = _GfxData;
    actorGfx.mPackIndex = MOD_PACK_INDEX;
    actorGfx.mGraphNode = (GraphNode *) DynOS_Model_LoadGeo(&id, MODEL_POOL_SESSION, geoLayout, true);
    if (!actorGfx.mGraphNode) {
        PrintError("  ERROR: Couldn't load graph node for \"%s\"", actorName);
        free(actorName);
        return;
    }
    actorGfx.mGraphNode->georef = georef;

    // Add to custom actors
    if (georef == NULL) {
        DynosCustomActors().Add({ strdup(actorName), geoLayout });
        georef = geoLayout;
    }

    // Add to list
    DynOS_Actor_Valid(georef, actorGfx);
    free(actorName);
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

    // check custom actors
    for (auto& pair : DynosCustomActors()) {
        if (!strcmp(aActorName, pair.first)) {
            return pair.second;
        }
    }

    // check loaded actors
    for (auto& pair : DynosValidActors()) {
        for (auto& geo : pair.second.mGfxData->mGeoLayouts) {
            if (!strcmp(aActorName, geo->mName.begin())) {
                return geo->mData;
            }
        }
    }

    // check built in actors
    for (s32 i = 0; i < DynOS_Builtin_Actor_GetCount(); ++i) {
        auto name = DynOS_Builtin_Actor_GetNameFromIndex(i);
        if (!strcmp(aActorName, name)) {
            return DynOS_Builtin_Actor_GetFromIndex(i);
        }
    }

    return NULL;
}

ActorGfx* DynOS_Actor_GetActorGfx(const GraphNode* aGraphNode) {
    if (aGraphNode == NULL) { return NULL; }
    auto& _ValidActors = DynosValidActors();

    // If georef is not NULL, check georef
    if (aGraphNode->georef != NULL) {
        if (_ValidActors.count(aGraphNode->georef) != 0) {
            return &_ValidActors[aGraphNode->georef];
        }
        return NULL;
    }

    // Check graph node
    for (const auto& _Actor : _ValidActors) {
        if (_Actor.second.mGraphNode == aGraphNode) {
            return (ActorGfx*)&_Actor.second;
        }
    }

    // No actor found
    return NULL;
}

void DynOS_Actor_Valid(const void* aGeoref, ActorGfx& aActorGfx) {
    if (aGeoref == NULL) { return; }
    auto& _ValidActors = DynosValidActors();
    _ValidActors[aGeoref] = aActorGfx;
    DynOS_Tex_Valid(aActorGfx.mGfxData);
}

void DynOS_Actor_Invalid(const void* aGeoref, s32 aPackIndex) {
    if (aGeoref == NULL) { return; }
    auto& _ValidActors = DynosValidActors();
    if (_ValidActors.count(aGeoref) == 0) { return; }
    if (_ValidActors[aGeoref].mPackIndex != aPackIndex) { return; }

    DynOS_Tex_Invalid(_ValidActors[aGeoref].mGfxData);
    _ValidActors.erase(aGeoref);
}

void DynOS_Actor_Override(struct Object* obj, void** aSharedChild) {
    if ((aSharedChild == NULL) || (*aSharedChild == NULL)) { return; }

    const void* georef = (*(GraphNode**)aSharedChild)->georef;
    if (georef == NULL) { return; }

    auto& _ValidActors = DynosValidActors();
    if (_ValidActors.count(georef) == 0) { return; }

    // Check if the behavior uses a character specific model
    if (obj && (obj->behavior == smlua_override_behavior(bhvMario) ||
            obj->behavior == smlua_override_behavior(bhvNormalCap) ||
            obj->behavior == smlua_override_behavior(bhvWingCap) ||
            obj->behavior == smlua_override_behavior(bhvMetalCap) ||
            obj->behavior == smlua_override_behavior(bhvVanishCap))) {
        struct NetworkPlayer* np = network_player_from_global_index(obj->globalPlayerIndex);
        if (np && np->localIndex > 0 && configDynosLocalPlayerModelOnly) {
            return;
        }
    }


    *aSharedChild = (void*)_ValidActors[georef].mGraphNode;
}

void DynOS_Actor_Override_All(void) {
    if (!gObjectLists) { return; }
    // Loop through all object lists
    for (s32 list : { OBJ_LIST_PLAYER, OBJ_LIST_DESTRUCTIVE, OBJ_LIST_GENACTOR, OBJ_LIST_PUSHABLE, OBJ_LIST_LEVEL, OBJ_LIST_DEFAULT, OBJ_LIST_SURFACE, OBJ_LIST_POLELIKE, OBJ_LIST_UNIMPORTANT }) {
        struct Object *_Head = (struct Object *) &gObjectLists[list];
        for (struct Object *_Object = (struct Object *) _Head->header.next; _Object != _Head; _Object = (struct Object *) _Object->header.next) {
            if (_Object->header.gfx.sharedChild != NULL && _Object->header.gfx.sharedChild->georef != NULL) {
                GraphNode* georef = (GraphNode*)_Object->header.gfx.sharedChild->georef;
                u32 id = 0;
                _Object->header.gfx.sharedChild = DynOS_Model_LoadGeo(&id, MODEL_POOL_PERMANENT, georef, true);
            }
            DynOS_Actor_Override(_Object, (void**)&_Object->header.gfx.sharedChild);
        }
    }
}

void DynOS_Actor_ModShutdown() {
    auto& _DynosCustomActors = DynosCustomActors();
    while (_DynosCustomActors.Count() > 0) {
        auto& pair = _DynosCustomActors[0];
        DynOS_Actor_Invalid(pair.second, MOD_PACK_INDEX);
        free((void*)pair.first);
        _DynosCustomActors.Remove(0);
    }

    auto& _ValidActors = DynosValidActors();
    for (auto it = _ValidActors.cbegin(); it != _ValidActors.cend();) {
        auto& actorGfx = it->second;
        if (actorGfx.mPackIndex == MOD_PACK_INDEX) {
            DynOS_Gfx_Free(actorGfx.mGfxData);
            _ValidActors.erase(it++);
        } else {
            ++it;
        }
    }

    DynOS_Actor_Override_All();
}
