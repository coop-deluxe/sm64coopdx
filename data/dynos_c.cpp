#include "dynos.cpp.h"
extern "C" {
#include "src/game/moving_texture.h"

// -- built in -- //

void *dynos_update_cmd(void *cmd) {
    return DynOS_UpdateCmd(cmd);
}

void dynos_update_gfx() {
    return DynOS_UpdateGfx();
}

void dynos_update_opt(void *pad) {
    return DynOS_UpdateOpt(pad);
}

s32 dynos_gfx_import_texture(void **output, void *ptr, s32 tile, void *grapi, void **hashmap, void *pool, s32 *poolpos, s32 poolsize) {
    return DynOS_Gfx_ImportTexture(output, ptr, tile, grapi, hashmap, pool, (u32 *) poolpos, (u32) poolsize);
}

void dynos_gfx_swap_animations(void *ptr) {
    return DynOS_Gfx_SwapAnimations(ptr);
}

// -- warps -- //

bool dynos_warp_to_level(s32 aLevel, s32 aArea, s32 aAct) {
    return DynOS_Warp_ToLevel(aLevel, aArea, aAct);
}

bool dynos_warp_restart_level(void) {
    return DynOS_Warp_RestartLevel();
}

bool dynos_warp_exit_level(s32 aDelay) {
    return DynOS_Warp_ExitLevel(aDelay);
}

bool dynos_warp_to_castle(s32 aLevel) {
    return DynOS_Warp_ToCastle(aLevel);
}

// -- dynos packs -- //

int dynos_packs_get_count(void) {
    return DynOS_Gfx_GetPacks().Count();
}

const char* dynos_packs_get(s32 index) {
    const char* path = DynOS_Gfx_GetPacks()[index]->mPath.c_str();

    // extract basename
    const char* cpath = path;
    const char* ctoken = cpath;
    while (*ctoken != '\0') {
        if (*ctoken == '/' || *ctoken == '\\') {
            if (*(ctoken + 1) != '\0') {
                cpath = (ctoken + 1);
            }
        }
        ctoken++;
    }

    return cpath;
}

bool dynos_packs_get_enabled(s32 index) {
    return DynOS_Gfx_GetPacksEnabled()[index];
}

void dynos_packs_set_enabled(s32 index, bool value) {
    DynOS_Gfx_GetPacksEnabled()[index] = value;
}

void dynos_generate_packs(const char* directory) {
    DynOS_Gfx_GeneratePacks(directory);
}

// -- geos -- //

void dynos_add_actor_custom(const char *modPath, const char* geoName) {
    DynOS_Actor_AddCustom(modPath, geoName);
}

const void* dynos_geolayout_get(const char *name) {
    return DynOS_Actor_GetLayoutFromName(name);
}

// -- collisions -- //

void dynos_add_collision(const char *modPath, const char* collisionName) {
    DynOS_Col_Activate(modPath, collisionName);
}

Collision* dynos_collision_get(const char* collisionName) {
    return DynOS_Col_Get(collisionName);
}

// -- levels -- //

void dynos_add_level(s32 modIndex, const char *modPath, const char* levelName) {
    DynOS_Lvl_Activate(modIndex, modPath, levelName);
}

LevelScript* dynos_level_get(const char* levelName) {
    return DynOS_Lvl_GetScript(levelName);
}

const char* dynos_level_get_token(u32 index) {
    return DynOS_Lvl_GetToken(index);
}

struct MovtexQuadCollection *dynos_level_get_movtexqc(s32 index) {
    DataNode<MovtexQC> *node = DynOS_Lvl_GetMovtexQuadCollection(index);
    if (node == NULL) { return NULL; }
    
    return node->mData;
}

void dynos_level_load_background(void *ptr) {
    DynOS_Lvl_LoadBackground(ptr);
}

}