#include "sm64.h"
#include "types.h"
#include "smlua_level_utils.h"
#include "pc/lua/smlua.h"
#include "game/area.h"
#include "game/level_update.h"
#include "game/object_helpers.h"
#include "data/dynos_cmap.cpp.h"
#include "level_commands.h"

extern void area_check_red_coin_or_secret(void *arg, bool isMacroObject);

#define MIN_AREA_INDEX 0
#define MAX_WARP_NODES_PER_AREA 0x100

struct CustomLevelInfo* sCustomLevelHead = NULL;
static s16 sCustomLevelNumNext = CUSTOM_LEVEL_NUM_START;

struct LevelWarpNodes {
    struct CustomWarpNode warpNodes[MAX_AREAS][MAX_WARP_NODES_PER_AREA];
};

static void *sCustomWarpNodes = NULL;

void smlua_level_util_reset(void) {
    struct CustomLevelInfo* node = sCustomLevelHead;

    while (node != NULL) {
        struct CustomLevelInfo* next = node->next;
        if (node->scriptEntryName) {
            free(node->scriptEntryName);
            node->scriptEntryName = NULL;
        }
        if (node->fullName) {
            free(node->fullName);
            node->fullName = NULL;
        }
        if (node->shortName) {
            free(node->shortName);
            node->shortName = NULL;
        }
        free(node);
        node = next;
    }

    sCustomLevelHead = NULL;
    sCustomLevelNumNext = CUSTOM_LEVEL_NUM_START;

    // Clear all custom warps
    for (void *warps = hmap_begin(sCustomWarpNodes); warps; warps = hmap_next(sCustomWarpNodes)) {
        free(warps);
    }
    hmap_destroy(sCustomWarpNodes);
    sCustomWarpNodes = NULL;
}

void smlua_level_util_change_area(s32 areaIndex) {
    if (areaIndex >= MIN_AREA_INDEX && areaIndex < MAX_AREAS && gAreas[areaIndex].root != NULL) {
        change_area(areaIndex);
    }
}

struct CustomLevelInfo* smlua_level_util_get_info(s16 levelNum) {
    struct CustomLevelInfo* node = sCustomLevelHead;
    while (node != NULL) {
        if (node->levelNum == levelNum) {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

struct CustomLevelInfo* smlua_level_util_get_info_from_short_name(const char* shortName) {
    struct CustomLevelInfo* node = sCustomLevelHead;
    while (node != NULL) {
        if (!strcmp(node->shortName, shortName)) {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

static struct CustomLevelInfo* smlua_level_util_get_info_from_script(const char* scriptEntryName) {
    struct CustomLevelInfo* node = sCustomLevelHead;
    while (node != NULL) {
        if (!strcmp(node->scriptEntryName, scriptEntryName)) {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

struct CustomLevelInfo* smlua_level_util_get_info_from_course_num(u8 courseNum) {
    struct CustomLevelInfo* node = sCustomLevelHead;
    while (node != NULL) {
        if (node->courseNum == courseNum) {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

s16 level_register(const char* scriptEntryName, s16 courseNum, const char* fullName, const char* shortName, u32 acousticReach, u32 echoLevel1, u32 echoLevel2, u32 echoLevel3) {
    // validate params
    if (scriptEntryName == NULL) {
        LOG_LUA("Provided nil scriptEntryName");
        return 0;
    }

    if (fullName == NULL) {
        LOG_LUA("Provided nil fullName");
        return 0;
    }

    if (shortName == NULL) {
        LOG_LUA("Provided nil shortName");
        return 0;
    }

    // find duplicate
    struct CustomLevelInfo* info = smlua_level_util_get_info_from_script(scriptEntryName);
    if (info != NULL) {
        return info->levelNum;
    }

    // find script
    LevelScript* script = dynos_get_level_script(scriptEntryName);
    if (script == NULL) {
        LOG_LUA("Failed to find script: %s", scriptEntryName);
        return 0;
    }

    // allocate and fill
    info = calloc(1, sizeof(struct CustomLevelInfo));
    info->script = script;
    info->scriptEntryName = strdup(scriptEntryName);
    info->courseNum = courseNum;
    info->levelNum = sCustomLevelNumNext++;
    info->fullName = strdup(fullName);
    info->shortName = strdup(shortName);
    info->acousticReach = acousticReach;
    info->echoLevel1 = echoLevel1;
    info->echoLevel2 = echoLevel2;
    info->echoLevel3 = echoLevel3;
    if (gLuaLoadingMod) {
        info->modIndex = gLuaLoadingMod->index;
    } else if (gLuaActiveMod) {
        info->modIndex = gLuaActiveMod->index;
    } else {
        if (info->scriptEntryName) {
            free(info->scriptEntryName);
            info->scriptEntryName = NULL;
        }
        if (info->fullName) {
            free(info->fullName);
            info->fullName = NULL;
        }
        if (info->shortName) {
            free(info->shortName);
            info->shortName = NULL;
        }
        free(info);
        LOG_LUA("Failed to find mod index for level: %s", scriptEntryName);
        return 0;
    }

    // add to list
    if (!sCustomLevelHead) {
        sCustomLevelHead = info;
        return info->levelNum;
    }

    struct CustomLevelInfo* node = sCustomLevelHead;
    while (node) {
        if (!node->next) {
            node->next = info;
            return info->levelNum;
        }
        node = node->next;
    }

    // just in case, should never trigger
    return 0;
}

bool level_is_vanilla_level(s16 levelNum) {
    return dynos_level_is_vanilla_level(levelNum);
}

bool warp_to_warpnode(s32 aLevel, s32 aArea, s32 aAct, s32 aWarpId) {
    return dynos_warp_to_warpnode(aLevel, aArea, aAct, aWarpId);
}

bool warp_to_level(s32 aLevel, s32 aArea, s32 aAct) {
    return dynos_warp_to_level(aLevel, aArea, aAct);
}

bool warp_to_start_level(void) {
    return dynos_warp_to_start_level();
}

bool warp_restart_level(void) {
    return dynos_warp_restart_level();
}

bool warp_exit_level(s32 aDelay) {
    return dynos_warp_exit_level(aDelay);
}

bool warp_to_castle(s32 aLevel) {
    return dynos_warp_to_castle(aLevel);
}

static struct LevelWarpNodes *level_get_warp_nodes(u8 levelNum, bool create) {
    struct LevelWarpNodes *warpNodes = hmap_get(sCustomWarpNodes, levelNum);
    if (!warpNodes && create) {
        if (!sCustomWarpNodes) {
            sCustomWarpNodes = hmap_create(true);
            if (!sCustomWarpNodes) {
                LOG_ERROR("Cannot allocate memory for custom warp nodes!");
                return NULL;
            }
        }
        warpNodes = calloc(1, sizeof(struct LevelWarpNodes));
        if (warpNodes) {
            hmap_put(sCustomWarpNodes, levelNum, warpNodes);
        }
    }
    return warpNodes;
}

static bool level_find_warp_node_in_current_level(struct CustomWarpNode *warpNode, u8 areaIndex,
    struct ObjectWarpNode **prevWarpNode, struct SpawnInfo **prevSpawnInfo
) {
    if (!warpNode || warpNode->node.node.id == 0) { return false; }

    struct Area *area = &gAreas[areaIndex];
    bool found = false;

    // Warp node
    if (prevWarpNode) { *prevWarpNode = NULL; }
    for (struct ObjectWarpNode *node = area->warpNodes, *prev = NULL; node != NULL; node = node->next) {
        if (node == &warpNode->node) {
            found = true;
            if (prevWarpNode) { *prevWarpNode = prev; }
            break;
        }
        prev = node;
    }

    // Spawn info
    if (found && prevSpawnInfo) {
        *prevSpawnInfo = NULL;
        for (struct SpawnInfo *spawnInfo = area->objectSpawnInfos, *prev = NULL; spawnInfo != NULL; spawnInfo = spawnInfo->next) {
            if (spawnInfo == &warpNode->spawnInfo) {
                *prevSpawnInfo = prev;
                break;
            }
            prev = spawnInfo;
        }
    }

    return found;
}

static void level_clear_warp_node(struct CustomWarpNode *warpNode, u8 areaIndex) {
    if (!warpNode) { return; }

    struct ObjectWarpNode *prevWarpNode = NULL;
    struct SpawnInfo *prevSpawnInfo = NULL;

    // Remove node from current area
    if (level_find_warp_node_in_current_level(warpNode, areaIndex, &prevWarpNode, &prevSpawnInfo)) {
        struct Area *area = &gAreas[areaIndex];

        // Unlink warp node
        if (prevWarpNode != NULL) {
            prevWarpNode->next = warpNode->node.next;
        } else if (area->warpNodes == &warpNode->node) {
            area->warpNodes = warpNode->node.next;
        }

        // Unlink warp object spawn info
        if (prevSpawnInfo != NULL) {
            prevSpawnInfo->next = warpNode->spawnInfo.next;
        } else if (area->objectSpawnInfos == &warpNode->spawnInfo) {
            area->objectSpawnInfos = warpNode->spawnInfo.next;
        }

        // Delete the corresponding object if current area
        if (areaIndex == gCurrAreaIndex && warpNode->node.object) {
            obj_mark_for_deletion(warpNode->node.object);
        }
    }

    // Clear node
    memset(warpNode, 0, sizeof(*warpNode));
}

struct CustomWarpNode *level_create_warp_node(u8 levelNum, u8 areaIndex, u8 id, enum MarioSpawnType marioSpawnType, u8 destLevel, u8 destArea, u8 destNode, bool checkpoint) {
    if (levelNum == LEVEL_NONE || (levelNum & WARP_CHECKPOINT) != 0 || (destLevel & WARP_CHECKPOINT) != 0 ||
        areaIndex >= MAX_AREAS || destArea >= MAX_AREAS || id == 0 || destNode == 0) {
        return NULL;
    }

    // Find level warp nodes
    struct LevelWarpNodes *levelWarps = level_get_warp_nodes(levelNum, true);
    if (!levelWarps) {
        return NULL;
    }

    struct CustomWarpNode *warpNode = &levelWarps->warpNodes[areaIndex][id];

    // If the node already exists in the current level, abort
    if (level_find_warp_node_in_current_level(warpNode, areaIndex, NULL, NULL)) {
        LOG_LUA_WARNING("Node %u already exists in the current level. To modify it, retrieve it with `level_get_warp_node` first.", id);
        return NULL;
    }

    level_clear_warp_node(warpNode, areaIndex);

    warpNode->node.node.id = id;
    warpNode->node.node.destLevel = destLevel | (checkpoint ? WARP_CHECKPOINT : WARP_NO_CHECKPOINT);
    warpNode->node.node.destArea = destArea;
    warpNode->node.node.destNode = destNode;

    warpNode->marioSpawnType = marioSpawnType;

    return warpNode;
}

struct CustomWarpNode *level_create_warp_node_with_object(u8 levelNum, u8 areaIndex, u8 id, enum MarioSpawnType marioSpawnType, u8 destLevel, u8 destArea, u8 destNode, bool checkpoint, Vec3f pos, Vec3s angle, enum ModelExtendedId modelId, enum BehaviorId behaviorId, u32 behParams) {
    struct CustomWarpNode *warpNode = level_create_warp_node(levelNum, areaIndex, id, marioSpawnType, destLevel, destArea, destNode, checkpoint);
    if (!warpNode) {
        return NULL;
    }

    // Remember warp node object parameters
    warpNode->spawnInfo.startPos[0] = pos[0];
    warpNode->spawnInfo.startPos[1] = pos[1];
    warpNode->spawnInfo.startPos[2] = pos[2];
    warpNode->spawnInfo.startAngle[0] = angle[0];
    warpNode->spawnInfo.startAngle[1] = angle[1];
    warpNode->spawnInfo.startAngle[2] = angle[2];
    warpNode->spawnInfo.areaIndex = areaIndex;
    warpNode->spawnInfo.activeAreaIndex = areaIndex;
    warpNode->spawnInfo.behaviorScript = (void *) get_behavior_from_id(behaviorId);
    warpNode->spawnInfo.behaviorArg = (behParams & 0xFF00FFFF) | (id << 16);
    warpNode->spawnInfo.unk18 = dynos_model_get_geo(smlua_model_util_load(modelId));

    return warpNode;
}

struct CustomWarpNode *level_get_warp_node(u8 levelNum, u8 areaIndex, u8 id) {
    if (levelNum == LEVEL_NONE || (levelNum & WARP_CHECKPOINT) != 0 || areaIndex >= MAX_AREAS || id == 0) {
        return NULL;
    }

    // Find level warp nodes
    struct LevelWarpNodes *levelWarps = level_get_warp_nodes(levelNum, false);
    if (!levelWarps) {
        return NULL;
    }

    struct CustomWarpNode *warpNode = &levelWarps->warpNodes[areaIndex][id];
    if (warpNode->node.node.id != id) {
        return NULL;
    }

    return warpNode;
}

void level_delete_warp_node(u8 levelNum, u8 areaIndex, u8 id) {
    if (levelNum == LEVEL_NONE || (levelNum & WARP_CHECKPOINT) != 0 || areaIndex >= MAX_AREAS || id == 0) {
        return;
    }

    // Find level warp nodes
    struct LevelWarpNodes *levelWarps = level_get_warp_nodes(levelNum, false);
    if (!levelWarps) {
        return;
    }

    struct CustomWarpNode *warpNode = &levelWarps->warpNodes[areaIndex][id];
    level_clear_warp_node(warpNode, areaIndex);
}

void level_clear_warp_nodes(u8 levelNum) {
    if (levelNum == LEVEL_NONE || (levelNum & WARP_CHECKPOINT) != 0) {
        return;
    }

    // Find level warp nodes
    struct LevelWarpNodes *levelWarps = level_get_warp_nodes(levelNum, false);
    if (!levelWarps) {
        return;
    }

    for (u8 areaIndex = 0; areaIndex < MAX_AREAS; areaIndex++) {
        struct CustomWarpNode *warpNodes = levelWarps->warpNodes[areaIndex];
        for (u16 id = 1; id < MAX_WARP_NODES_PER_AREA; ++id) {
            struct CustomWarpNode *warpNode = &warpNodes[id];
            level_clear_warp_node(warpNode, areaIndex);
        }
    }
}

void level_register_custom_warp_nodes(u8 levelNum, u8 areaIndex) {
    if (levelNum == LEVEL_NONE || (levelNum & WARP_CHECKPOINT) != 0 || areaIndex >= MAX_AREAS) {
        return;
    }

    // Find level warp nodes
    struct LevelWarpNodes *levelWarps = level_get_warp_nodes(levelNum, false);
    if (!levelWarps) {
        return;
    }

    struct CustomWarpNode *warpNodes = levelWarps->warpNodes[areaIndex];
    for (u16 id = 1; id < MAX_WARP_NODES_PER_AREA; ++id) {
        struct CustomWarpNode *warpNode = &warpNodes[id];
        if (warpNode->node.node.id == id) {

            // Register warp node
            warpNode->node.next = gAreas[areaIndex].warpNodes;
            gAreas[areaIndex].warpNodes = &warpNode->node;

            // Register warp node object
            if (warpNode->spawnInfo.behaviorScript) {
                warpNode->spawnInfo.next = gAreas[areaIndex].objectSpawnInfos;

                warpNode->spawnInfo.syncID = gAreas[areaIndex].nextSyncID;
                gAreas[areaIndex].nextSyncID += 10;

                gAreas[areaIndex].objectSpawnInfos = &warpNode->spawnInfo;
                area_check_red_coin_or_secret(warpNode->spawnInfo.behaviorScript, false);
            }
        }
    }
}

void level_clear_warp_node_objects(u8 levelNum, u8 areaIndex) {
    if (levelNum == LEVEL_NONE || (levelNum & WARP_CHECKPOINT) != 0 || areaIndex >= MAX_AREAS) {
        return;
    }

    // Find level warp nodes
    struct LevelWarpNodes *levelWarps = level_get_warp_nodes(levelNum, false);
    if (!levelWarps) {
        return;
    }

    struct CustomWarpNode *warpNodes = levelWarps->warpNodes[areaIndex];
    for (u16 id = 1; id < MAX_WARP_NODES_PER_AREA; ++id) {
        struct CustomWarpNode *warpNode = &warpNodes[id];
        warpNode->node.object = NULL;
    }
}

enum MarioSpawnType level_get_warp_spawn_type_from_object(u8 levelNum, u8 areaIndex, struct Object *obj) {
    u8 id = (u8) (obj->oBehParams >> 16);

    struct CustomWarpNode *warpNode = level_get_warp_node(levelNum, areaIndex, id);
    if (!warpNode) {
        return MARIO_SPAWN_NONE;
    }

    // Identify by spawn info
    if (obj->respawnInfo == (void *) &warpNode->spawnInfo.behaviorArg) {
        return warpNode->marioSpawnType;
    }

    // Identify by object
    if (warpNode->node.object == obj) {
        return warpNode->marioSpawnType;
    }

    return MARIO_SPAWN_NONE;
}
