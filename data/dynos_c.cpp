#include "dynos.cpp.h"
extern "C" {
#include "src/game/moving_texture.h"

void *dynos_swap_cmd(void *cmd) {
    return DynOS_SwapCmd(cmd);
}

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

s32 dynos_tex_import(void **output, void *ptr, s32 tile, void *grapi, void **hashmap, void *pool, s32 *poolpos, s32 poolsize) {
    return DynOS_Tex_Import(output, ptr, tile, grapi, hashmap, pool, (u32 *) poolpos, (u32) poolsize);
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

void dynos_add_actor_custom(const char *filePath, const char* geoName) {
    DynOS_Actor_AddCustom(filePath, geoName);
}

const void* dynos_geolayout_get(const char *name) {
    return DynOS_Actor_GetLayoutFromName(name);
}

// -- collisions -- //

void dynos_add_collision(const char *filePath, const char* collisionName) {
    DynOS_Col_Activate(filePath, collisionName);
}

Collision* dynos_collision_get(const char* collisionName) {
    return DynOS_Col_Get(collisionName);
}

// -- movtexqcs -- //

void dynos_movtexqc_register(const char* name, s16 level, s16 area, s16 type) {
    DynOS_MovtexQC_Register(name, level, area, type);
}

struct MovtexQuadCollection* dynos_movtexqc_get_from_id(u32 id) {
    DataNode<MovtexQC> *node = DynOS_MovtexQC_GetFromId(id);
    if (node == NULL) { return NULL; }

    return node->mData;
}

struct MovtexQuadCollection* dynos_movtexqc_get_from_index(s32 index) {
    DataNode<MovtexQC> *node = DynOS_MovtexQC_GetFromIndex(index);
    if (node == NULL) { return NULL; }

    return node->mData;
}

// -- levels -- //

void dynos_add_level(s32 modIndex, const char *filePath, const char* levelName) {
    DynOS_Lvl_Activate(modIndex, filePath, levelName);
}

const char* dynos_level_get_token(u32 index) {
    return DynOS_Lvl_GetToken(index);
}

Trajectory* dynos_level_get_trajectory(const char* name) {
    return DynOS_Lvl_GetTrajectory(name);
}

void dynos_level_load_background(void *ptr) {
    DynOS_Lvl_LoadBackground(ptr);
}

}