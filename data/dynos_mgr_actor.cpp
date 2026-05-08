#include <unordered_map>
#include "dynos.cpp.h"

extern "C" {
#include "game/object_list_processor.h"
#include "pc/configfile.h"
#include "pc/lua/smlua_hooks.h"
#include "pc/mods/mod_fs.h"
}

static ObjectList sObjectListsToOverride[] = {
    OBJ_LIST_PLAYER,
    OBJ_LIST_DESTRUCTIVE,
    OBJ_LIST_GENACTOR,
    OBJ_LIST_PUSHABLE,
    OBJ_LIST_LEVEL,
    OBJ_LIST_DEFAULT,
    OBJ_LIST_SURFACE,
    OBJ_LIST_POLELIKE,
    OBJ_LIST_UNIMPORTANT
};

// Static maps/arrays
static std::map<const void*, ActorGfx>& DynosValidActors() {
    static std::map<const void*, ActorGfx> sDynosValidActors;
    return sDynosValidActors;
}

static std::vector<std::pair<std::string, void *>> &DynosCustomActors() {
    static std::vector<std::pair<std::string, void *>> sDynosCustomActors;
    return sDynosCustomActors;
}

static std::map<struct GraphNode *, struct GraphNode *> sModifiedGraphNodes;

std::map<const void *, ActorGfx> &DynOS_Actor_GetValidActors() {
    return DynosValidActors();
}

// Only used for mods with custom actors.
bool DynOS_Actor_AddCustom(s32 aModIndex, s32 aModFileIndex, const SysPath &aFilename, const char *aActorName) {
    const void* georef = DynOS_Builtin_Actor_GetFromName(aActorName);

    std::string actorName = aActorName;

    GfxData *_GfxData = DynOS_Actor_LoadFromBinary(aFilename, actorName.c_str(), aFilename, false);
    if (!_GfxData) {
        PrintError("  ERROR: Couldn't load Actor Binary \"%s\" from \"%s\"", actorName.c_str(), aFilename.c_str());
        return false;
    }
    _GfxData->mModIndex = aModIndex;
    _GfxData->mModFileIndex = aModFileIndex;

    void* geoLayout = (*(_GfxData->mGeoLayouts.end() - 1))->mData;
    if (!geoLayout) {
        PrintError("  ERROR: Couldn't load geo layout for \"%s\"", actorName.c_str());
        return false;
    }

    // Load the graph node
    u32 id = 0;
    GraphNode *graphNode = (GraphNode *) DynOS_Model_LoadGeo(&id, MODEL_POOL_SESSION, geoLayout, true);
    if (!graphNode) {
        PrintError("  ERROR: Couldn't load graph node for \"%s\"", actorName.c_str());
        return false;
    }
    graphNode->georef = georef;

    // Add to custom actors
    if (georef == NULL) {
        DynosCustomActors().emplace_back(actorName, geoLayout);
        georef = geoLayout;
    }

    // Alloc and init the actors gfx list
    ActorGfx actorGfx = {
        .mGfxData   = _GfxData,
        .mGraphNode = graphNode,
        .mPackIndex = MOD_PACK_INDEX,
    };

    // Add to list
    DynOS_Actor_Valid(georef, actorGfx);
    return true;
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
        if (pair.first == aActorName) {
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

    // check modfs file
    if (is_mod_fs_file(aActorName)) {
        if (DynOS_Actor_AddCustom(gLuaActiveMod->index, -1, aActorName, aActorName)) {
            return DynOS_Actor_GetLayoutFromName(aActorName);
        }
    }

    return NULL;
}

bool DynOS_Actor_GetModIndexAndTokenFromGfxData(const GfxData *aGfxData, u32 aTokenIndex, s32 *outModIndex, s32 *outModFileIndex, const char **outToken) {
    if (aGfxData) {
        if (outModIndex) { *outModIndex = aGfxData->mModIndex; }
        if (outModFileIndex) { *outModFileIndex = aGfxData->mModFileIndex; }
        if (outToken) {
            if (!aTokenIndex || aTokenIndex > aGfxData->mLuaTokenList.Count()) {
                return false;
            }
            *outToken = aGfxData->mLuaTokenList[aTokenIndex - 1].begin(); // token index is 1-indexed
        }
        return true;
    }
    return false;
}

bool DynOS_Actor_GetModIndexAndToken(const GraphNode *aGraphNode, u32 aTokenIndex, s32 *outModIndex, s32 *outModFileIndex, const char **outToken) {
    ActorGfx *_ActorGfx = DynOS_Actor_GetActorGfx(aGraphNode);
    if (_ActorGfx) {
        return DynOS_Actor_GetModIndexAndTokenFromGfxData(_ActorGfx->mGfxData, aTokenIndex, outModIndex, outModFileIndex, outToken);
    } else { // try the active level
        return DynOS_Actor_GetModIndexAndTokenFromGfxData(DynOS_Lvl_GetActiveGfx(), aTokenIndex, outModIndex, outModFileIndex, outToken);
    }
}

ActorGfx* DynOS_Actor_GetActorGfx(const GraphNode* aGraphNode) {
    if (aGraphNode == NULL) { return NULL; }
    auto& _ValidActors = DynosValidActors();

    // If georef is not NULL, check georef
    if (aGraphNode->georef != NULL) {
        auto it = _ValidActors.find(aGraphNode->georef);
        if (it != _ValidActors.end()) {
            return &it->second;
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
    auto it = _ValidActors.find(aGeoref);
    if (it == _ValidActors.end()) { return; }
    if (it->second.mPackIndex != aPackIndex) { return; }

    DynOS_Tex_Invalid(it->second.mGfxData);
    _ValidActors.erase(aGeoref);
}

void DynOS_Actor_Override(struct Object* obj, void** aSharedChild) {
    if ((aSharedChild == NULL) || (*aSharedChild == NULL)) { return; }

    const void* georef = (*(GraphNode**)aSharedChild)->georef;
    if (georef == NULL) { return; }

    auto& _ValidActors = DynosValidActors();
    auto it = _ValidActors.find(georef);
    if (it == _ValidActors.end()) { return; }

    // Check if the behavior uses a character specific model
    if (obj && (
        obj->behavior == smlua_override_behavior(bhvMario)     ||
        obj->behavior == smlua_override_behavior(bhvNormalCap) ||
        obj->behavior == smlua_override_behavior(bhvWingCap)   ||
        obj->behavior == smlua_override_behavior(bhvMetalCap)  ||
        obj->behavior == smlua_override_behavior(bhvVanishCap)
    )) {
        struct NetworkPlayer* np = network_player_from_global_index(obj->globalPlayerIndex);
        if (np != NULL && np->localIndex > 0 && configDynosLocalPlayerModelOnly && it->second.mPackIndex != MOD_PACK_INDEX) {
            return;
        }
    }

    *aSharedChild = (void*)it->second.mGraphNode;
}

// Used for both DynOS packs and actors from mods, only overrides existing actors
void DynOS_Actor_Override_All(void) {
    if (!gObjectLists) { return; }

    // Loop through all object lists
    for (ObjectList list : sObjectListsToOverride) {
        struct Object *_Head = (struct Object *) &gObjectLists[list];
        for (struct Object *_Object = (struct Object *) _Head->header.next; _Object != _Head; _Object = (struct Object *) _Object->header.next) {
            if (_Object->activeFlags && _Object->header.gfx.sharedChild != NULL) {
                if (_Object->header.gfx.sharedChild->georef != NULL) {
                    GraphNode* georef = (GraphNode*)_Object->header.gfx.sharedChild->georef;
                    u32 id = 0;
                    _Object->header.gfx.sharedChild = DynOS_Model_LoadGeo(&id, MODEL_POOL_PERMANENT, georef, true);
                }
                DynOS_Actor_Override(_Object, (void**)&_Object->header.gfx.sharedChild);
            }
        }
    }
}

static std::unordered_map<s16, size_t> sGraphNodeSizeMap = {
    { GRAPH_NODE_TYPE_ROOT,                 sizeof(GraphNodeRoot) },
    { GRAPH_NODE_TYPE_ORTHO_PROJECTION,     sizeof(GraphNodeOrthoProjection) },
    { GRAPH_NODE_TYPE_PERSPECTIVE,          sizeof(GraphNodePerspective) },
    { GRAPH_NODE_TYPE_START,                sizeof(GraphNodeStart) },
    { GRAPH_NODE_TYPE_MASTER_LIST,          sizeof(GraphNodeMasterList) },
    { GRAPH_NODE_TYPE_LEVEL_OF_DETAIL,      sizeof(GraphNodeLevelOfDetail) },
    { GRAPH_NODE_TYPE_SWITCH_CASE,          sizeof(GraphNodeSwitchCase) },
    { GRAPH_NODE_TYPE_CAMERA,               sizeof(GraphNodeCamera) },
    { GRAPH_NODE_TYPE_TRANSLATION_ROTATION, sizeof(GraphNodeTranslationRotation) },
    { GRAPH_NODE_TYPE_TRANSLATION,          sizeof(GraphNodeTranslation) },
    { GRAPH_NODE_TYPE_ROTATION,             sizeof(GraphNodeRotation) },
    { GRAPH_NODE_TYPE_SCALE,                sizeof(GraphNodeScale) },
    { GRAPH_NODE_TYPE_SCALE_XYZ,            sizeof(GraphNodeScaleXYZ) },
    { GRAPH_NODE_TYPE_OBJECT,               sizeof(GraphNodeObject) },
    { GRAPH_NODE_TYPE_CULLING_RADIUS,       sizeof(GraphNodeCullingRadius) },
    { GRAPH_NODE_TYPE_ANIMATED_PART,        sizeof(GraphNodeAnimatedPart) },
    { GRAPH_NODE_TYPE_BILLBOARD,            sizeof(GraphNodeBillboard) },
    { GRAPH_NODE_TYPE_DISPLAY_LIST,         sizeof(GraphNodeDisplayList) },
    { GRAPH_NODE_TYPE_SHADOW,               sizeof(GraphNodeShadow) },
    { GRAPH_NODE_TYPE_OBJECT_PARENT,        sizeof(GraphNodeObjectParent) },
    { GRAPH_NODE_TYPE_GENERATED_LIST,       sizeof(GraphNodeGenerated) },
    { GRAPH_NODE_TYPE_BACKGROUND,           sizeof(GraphNodeBackground) },
    { GRAPH_NODE_TYPE_HELD_OBJ,             sizeof(GraphNodeHeldObject) },
};

size_t get_graph_node_size(s16 nodeType) {
    auto it = sGraphNodeSizeMap.find(nodeType);
    return it != sGraphNodeSizeMap.end() ? it->second : 0;
}

void DynOS_Actor_RegisterModifiedGraphNode(GraphNode *aNode) {
    if (sModifiedGraphNodes.find(aNode) == sModifiedGraphNodes.end()) {
        struct GraphNode *sharedChild = geo_find_shared_child(aNode);
        if (DynOS_Model_GetModelPoolFromGraphNode(sharedChild) != MODEL_POOL_PERMANENT) { return; } // Only need to reset permanent models
        size_t size = get_graph_node_size(aNode->type);
        if (size == 0) { return; } // Unexpected
        GraphNode *graphNodeCopy = (GraphNode *) malloc(size);
        memcpy(graphNodeCopy, aNode, size);
        sModifiedGraphNodes[aNode] = graphNodeCopy;
    }
}

void DynOS_Actor_ModShutdown() {
    auto& _DynosCustomActors = DynosCustomActors();
    for (auto &pair : _DynosCustomActors) {
        DynOS_Actor_Invalid(pair.second, MOD_PACK_INDEX);
    }
    _DynosCustomActors.clear();

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

    // Reset modified graph nodes
    for (auto& node : sModifiedGraphNodes) {
        size_t size = get_graph_node_size(node.second->type);
        if (size == 0) { continue; } // Unexpected
        memcpy(node.first, node.second, size);
        free(node.second);
    }
    sModifiedGraphNodes.clear();
}
