#include "types.h"

#include "engine/math_util.h"
#include "engine/surface_collision.h"
#include "include/surface_terrains.h"
#include "game/mario_step.h"
#include "game/area.h"
#include "engine/surface_load.h"
#include "game/game_init.h"

#include "pc/lua/smlua.h"
#include "smlua_collision_utils.h"
#include "pc/debuglog.h"

// actors
#include "actors/common0.h"
#include "actors/common1.h"
#include "actors/custom0.h"
#include "actors/group1.h"
#include "actors/group2.h"
#include "actors/group3.h"
#include "actors/group4.h"
#include "actors/group5.h"
#include "actors/group6.h"
#include "actors/group7.h"
#include "actors/group8.h"
#include "actors/group9.h"
#include "actors/group10.h"
#include "actors/group11.h"
#include "actors/group12.h"
#include "actors/group13.h"
#include "actors/group14.h"
#include "actors/group15.h"
#include "actors/group16.h"
#include "actors/group17.h"
#include "actors/zcustom0.h"

// levels
#include "levels/bbh/header.h"
#include "levels/castle_inside/header.h"
#include "levels/hmc/header.h"
#include "levels/ssl/header.h"
#include "levels/bob/header.h"
#include "levels/sl/header.h"
#include "levels/wdw/header.h"
#include "levels/jrb/header.h"
#include "levels/thi/header.h"
#include "levels/ttc/header.h"
#include "levels/rr/header.h"
#include "levels/castle_grounds/header.h"
#include "levels/bitdw/header.h"
#include "levels/lll/header.h"
#include "levels/sa/header.h"
#include "levels/bitfs/header.h"
#include "levels/ddd/header.h"
#include "levels/wf/header.h"
#include "levels/bowser_2/header.h"
#include "levels/ttm/header.h"

struct GlobalObjectCollisionData gGlobalObjectCollisionData = {
    .bbh_seg7_collision_coffin                       = (Collision*) bbh_seg7_collision_coffin,
    .bbh_seg7_collision_haunted_bookshelf            = (Collision*) bbh_seg7_collision_haunted_bookshelf,
    .bbh_seg7_collision_merry_go_round               = (Collision*) bbh_seg7_collision_merry_go_round,
    .bbh_seg7_collision_mesh_elevator                = (Collision*) bbh_seg7_collision_mesh_elevator,
    .bbh_seg7_collision_staircase_step               = (Collision*) bbh_seg7_collision_staircase_step,
    .bbh_seg7_collision_tilt_floor_platform          = (Collision*) bbh_seg7_collision_tilt_floor_platform,
    .bitdw_seg7_collision_moving_pyramid             = (Collision*) bitdw_seg7_collision_moving_pyramid,
    .bitfs_seg7_collision_inverted_pyramid           = (Collision*) bitfs_seg7_collision_inverted_pyramid,
    .bitfs_seg7_collision_sinking_cage_platform      = (Collision*) bitfs_seg7_collision_sinking_cage_platform,
    .bitfs_seg7_collision_sinking_platform           = (Collision*) bitfs_seg7_collision_sinking_platform,
    .bitfs_seg7_collision_squishable_platform        = (Collision*) bitfs_seg7_collision_squishable_platform,
    .blue_coin_switch_seg8_collision_08000E98        = (Collision*) blue_coin_switch_seg8_collision_08000E98,
    .bob_seg7_collision_chain_chomp_gate             = (Collision*) bob_seg7_collision_chain_chomp_gate,
    .bowser_2_seg7_collision_tilting_platform        = (Collision*) bowser_2_seg7_collision_tilting_platform,
    .breakable_box_seg8_collision_08012D70           = (Collision*) breakable_box_seg8_collision_08012D70,
    .cannon_lid_seg8_collision_08004950              = (Collision*) cannon_lid_seg8_collision_08004950,
    .capswitch_collision_050033D0                    = (Collision*) capswitch_collision_050033D0,
    .capswitch_collision_05003448                    = (Collision*) capswitch_collision_05003448,
    .castle_grounds_seg7_collision_cannon_grill      = (Collision*) castle_grounds_seg7_collision_cannon_grill,
    .castle_grounds_seg7_collision_moat_grills       = (Collision*) castle_grounds_seg7_collision_moat_grills,
    .checkerboard_platform_seg8_collision_0800D710   = (Collision*) checkerboard_platform_seg8_collision_0800D710,
    .ddd_seg7_collision_bowser_sub_door              = (Collision*) ddd_seg7_collision_bowser_sub_door,
    .ddd_seg7_collision_submarine                    = (Collision*) ddd_seg7_collision_submarine,
    .door_seg3_collision_0301CE78                    = (Collision*) door_seg3_collision_0301CE78,
    .dorrie_seg6_collision_0600F644                  = (Collision*) dorrie_seg6_collision_0600F644,
    .dorrie_seg6_collision_0600FBB8                  = (Collision*) dorrie_seg6_collision_0600FBB8,
    .exclamation_box_outline_seg8_collision_08025F78 = (Collision*) exclamation_box_outline_seg8_collision_08025F78,
    .hmc_seg7_collision_controllable_platform        = (Collision*) hmc_seg7_collision_controllable_platform,
    .hmc_seg7_collision_controllable_platform_sub    = (Collision*) hmc_seg7_collision_controllable_platform_sub,
    .hmc_seg7_collision_elevator                     = (Collision*) hmc_seg7_collision_elevator,
    .inside_castle_seg7_collision_floor_trap         = (Collision*) inside_castle_seg7_collision_floor_trap,
    .inside_castle_seg7_collision_star_door          = (Collision*) inside_castle_seg7_collision_star_door,
    .inside_castle_seg7_collision_water_level_pillar = (Collision*) inside_castle_seg7_collision_water_level_pillar,
    .jrb_seg7_collision_floating_box                 = (Collision*) jrb_seg7_collision_floating_box,
    .jrb_seg7_collision_floating_platform            = (Collision*) jrb_seg7_collision_floating_platform,
    .jrb_seg7_collision_in_sunken_ship_2             = (Collision*) jrb_seg7_collision_in_sunken_ship_2,
    .jrb_seg7_collision_in_sunken_ship_3             = (Collision*) jrb_seg7_collision_in_sunken_ship_3,
    .jrb_seg7_collision_in_sunken_ship               = (Collision*) jrb_seg7_collision_in_sunken_ship,
    .jrb_seg7_collision_pillar_base                  = (Collision*) jrb_seg7_collision_pillar_base,
    .jrb_seg7_collision_rock_solid                   = (Collision*) jrb_seg7_collision_rock_solid,
    .lll_hexagonal_mesh_seg3_collision_0301CECC      = (Collision*) lll_hexagonal_mesh_seg3_collision_0301CECC,
    .lll_seg7_collision_drawbridge                   = (Collision*) lll_seg7_collision_drawbridge,
    .lll_seg7_collision_falling_wall                 = (Collision*) lll_seg7_collision_falling_wall,
    .lll_seg7_collision_floating_block               = (Collision*) lll_seg7_collision_floating_block,
    .lll_seg7_collision_hexagonal_platform           = (Collision*) lll_seg7_collision_hexagonal_platform,
    .lll_seg7_collision_inverted_pyramid             = (Collision*) lll_seg7_collision_inverted_pyramid,
    .lll_seg7_collision_octagonal_moving_platform    = (Collision*) lll_seg7_collision_octagonal_moving_platform,
    .lll_seg7_collision_pitoune                      = (Collision*) lll_seg7_collision_pitoune,
    .lll_seg7_collision_puzzle_piece                 = (Collision*) lll_seg7_collision_puzzle_piece,
    .lll_seg7_collision_rotating_fire_bars           = (Collision*) lll_seg7_collision_rotating_fire_bars,
    .lll_seg7_collision_rotating_platform            = (Collision*) lll_seg7_collision_rotating_platform,
    .lll_seg7_collision_sinking_pyramids             = (Collision*) lll_seg7_collision_sinking_pyramids,
    .lll_seg7_collision_slow_tilting_platform        = (Collision*) lll_seg7_collision_slow_tilting_platform,
    .lll_seg7_collision_wood_piece                   = (Collision*) lll_seg7_collision_wood_piece,
    .metal_box_seg8_collision_08024C28               = (Collision*) metal_box_seg8_collision_08024C28,
    .penguin_seg5_collision_05008B88                 = (Collision*) penguin_seg5_collision_05008B88,
    .poundable_pole_collision_06002490               = (Collision*) poundable_pole_collision_06002490,
    .purple_switch_seg8_collision_0800C7A8           = (Collision*) purple_switch_seg8_collision_0800C7A8,
    .rr_seg7_collision_donut_platform                = (Collision*) rr_seg7_collision_donut_platform,
    .rr_seg7_collision_elevator_platform             = (Collision*) rr_seg7_collision_elevator_platform,
    .rr_seg7_collision_pendulum                      = (Collision*) rr_seg7_collision_pendulum,
    .rr_seg7_collision_rotating_platform_with_fire   = (Collision*) rr_seg7_collision_rotating_platform_with_fire,
    .sl_seg7_collision_pound_explodes                = (Collision*) sl_seg7_collision_pound_explodes,
    .sl_seg7_collision_sliding_snow_mound            = (Collision*) sl_seg7_collision_sliding_snow_mound,
    .springboard_collision_05001A28                  = (Collision*) springboard_collision_05001A28,
    .ssl_seg7_collision_0702808C                     = (Collision*) ssl_seg7_collision_0702808C,
    .ssl_seg7_collision_grindel                      = (Collision*) ssl_seg7_collision_grindel,
    .ssl_seg7_collision_pyramid_elevator             = (Collision*) ssl_seg7_collision_pyramid_elevator,
    .ssl_seg7_collision_pyramid_top                  = (Collision*) ssl_seg7_collision_pyramid_top,
    .ssl_seg7_collision_spindel                      = (Collision*) ssl_seg7_collision_spindel,
    .ssl_seg7_collision_tox_box                      = (Collision*) ssl_seg7_collision_tox_box,
    .thi_seg7_collision_top_trap                     = (Collision*) thi_seg7_collision_top_trap,
    .thwomp_seg5_collision_0500B7D0                  = (Collision*) thwomp_seg5_collision_0500B7D0,
    .thwomp_seg5_collision_0500B92C                  = (Collision*) thwomp_seg5_collision_0500B92C,
    .ttc_seg7_collision_clock_main_rotation          = (Collision*) ttc_seg7_collision_clock_main_rotation,
    .ttc_seg7_collision_clock_pendulum               = (Collision*) ttc_seg7_collision_clock_pendulum,
    .ttc_seg7_collision_clock_platform               = (Collision*) ttc_seg7_collision_clock_platform,
    .ttc_seg7_collision_rotating_clock_platform2     = (Collision*) ttc_seg7_collision_rotating_clock_platform2,
    .ttc_seg7_collision_sliding_surface              = (Collision*) ttc_seg7_collision_sliding_surface,
    .ttm_seg7_collision_pitoune_2                    = (Collision*) ttm_seg7_collision_pitoune_2,
    .ttm_seg7_collision_podium_warp                  = (Collision*) ttm_seg7_collision_podium_warp,
    .ttm_seg7_collision_ukiki_cage                   = (Collision*) ttm_seg7_collision_ukiki_cage,
    .unknown_seg8_collision_080262F8                 = (Collision*) unknown_seg8_collision_080262F8,
    .warp_pipe_seg3_collision_03009AC8               = (Collision*) warp_pipe_seg3_collision_03009AC8,
    .wdw_seg7_collision_arrow_lift                   = (Collision*) wdw_seg7_collision_arrow_lift,
    .wdw_seg7_collision_express_elevator_platform    = (Collision*) wdw_seg7_collision_express_elevator_platform,
    .wdw_seg7_collision_rect_floating_platform       = (Collision*) wdw_seg7_collision_rect_floating_platform,
    .wdw_seg7_collision_square_floating_platform     = (Collision*) wdw_seg7_collision_square_floating_platform,
    .wf_seg7_collision_breakable_wall_2              = (Collision*) wf_seg7_collision_breakable_wall_2,
    .wf_seg7_collision_breakable_wall                = (Collision*) wf_seg7_collision_breakable_wall,
    .wf_seg7_collision_bullet_bill_cannon            = (Collision*) wf_seg7_collision_bullet_bill_cannon,
    .wf_seg7_collision_clocklike_rotation            = (Collision*) wf_seg7_collision_clocklike_rotation,
    .wf_seg7_collision_kickable_board                = (Collision*) wf_seg7_collision_kickable_board,
    .wf_seg7_collision_large_bomp                    = (Collision*) wf_seg7_collision_large_bomp,
    .wf_seg7_collision_platform                      = (Collision*) wf_seg7_collision_platform,
    .wf_seg7_collision_sliding_brick_platform        = (Collision*) wf_seg7_collision_sliding_brick_platform,
    .wf_seg7_collision_small_bomp                    = (Collision*) wf_seg7_collision_small_bomp,
    .wf_seg7_collision_tower                         = (Collision*) wf_seg7_collision_tower,
    .wf_seg7_collision_tower_door                    = (Collision*) wf_seg7_collision_tower_door,
    .whomp_seg6_collision_06020A0C                   = (Collision*) whomp_seg6_collision_06020A0C,
    .wooden_signpost_seg3_collision_0302DD80         = (Collision*) wooden_signpost_seg3_collision_0302DD80,
};

struct RayIntersectionInfo* collision_find_surface_on_ray(f32 startX, f32 startY, f32 startZ, f32 dirX, f32 dirY, f32 dirZ, f32 precision) {
    static struct RayIntersectionInfo info = { 0 };
    Vec3f orig = { startX, startY, startZ };
    Vec3f dir = { dirX, dirY, dirZ };
    find_surface_on_ray(orig, dir, &info.surface, info.hitPos, precision);
    return &info;
}

struct Surface* collision_find_floor(f32 x, f32 y, f32 z) {
    static struct Surface *surface;
    find_floor(x, y, z, &surface);
    return surface;
}

struct Surface* collision_find_ceil(f32 x, f32 y, f32 z) {
    static struct Surface *surface;
    find_ceil(x, y, z, &surface);
    return surface;
}

struct Surface* get_water_surface_pseudo_floor(void) {
    return &gWaterSurfacePseudoFloor;
}

Collision* smlua_collision_util_get(const char* name) {
    return dynos_collision_get(name);
}

struct WallCollisionData* collision_get_temp_wall_collision_data(void) {
    static struct WallCollisionData sTmpWcd = { 0 };
    memset(&sTmpWcd, 0, sizeof(struct WallCollisionData));
    return &sTmpWcd;
}

struct Surface* get_surface_from_wcd_index(struct WallCollisionData* wcd, s8 index) {
    if (index < 0 || index >= 4) { return NULL; }
    return wcd->walls[index];
}

Collision *smlua_collision_util_get_current_terrain_collision(void) {
    if (gCurrentArea && gCurrentArea->terrainData) {
        return (Collision*) gCurrentArea->terrainData;
    }
    return NULL;
}

Collision *smlua_collision_util_get_level_collision(u32 level, u16 area) {
    return dynos_level_get_collision(level, area);
}

void smlua_collision_util_find_surface_types(Collision* data) {
    lua_State* L = gLuaState;

    if (data && *data++ == COL_INIT()) {
        lua_newtable(L);
        s32 t = lua_gettop(gLuaState);

        // Skip collision vertices
        s32 numVertices = *data++;
        data += 3 * numVertices;

        // Process surface types
        for (u16 i = 0; true; ++i) {
            s16 surfaceType = *data++;
            if (surfaceType == COL_TRI_STOP()) { break; }
            s32 numTriangles = *data++;
            data += (3 + surface_has_force(surfaceType)) * numTriangles;

            lua_pushinteger(L, i);
            lua_pushinteger(L, surfaceType);
            lua_settable(L, t);
        }
        return;
    }

    // Couldn't find anything
    lua_pushnil(L);
}

/**
 * Compute the normal, plane equation, and Y bounds for a triangle.
 * Only writes to the surface on success. Returns false if the triangle
 * is degenerate, leaving the surface completely untouched.
 */
static bool calc_surface_fields(struct Surface *surface, Vec3s vertex1, Vec3s vertex2, Vec3s vertex3) {
    s32 x1 = vertex1[0], y1 = vertex1[1], z1 = vertex1[2];
    s32 x2 = vertex2[0], y2 = vertex2[1], z2 = vertex2[2];
    s32 x3 = vertex3[0], y3 = vertex3[1], z3 = vertex3[2];

    // Compute normal via cross product: (v2 - v1) x (v3 - v2)
    f32 nx = (y2 - y1) * (z3 - z2) - (z2 - z1) * (y3 - y2);
    f32 ny = (z2 - z1) * (x3 - x2) - (x2 - x1) * (z3 - z2);
    f32 nz = (x2 - x1) * (y3 - y2) - (y2 - y1) * (x3 - x2);
    f32 mag = sqrtf(nx * nx + ny * ny + nz * nz);

    // Reject degenerate triangles without touching the surface
    if (mag < 0.0001f) { return false; }

    mag = 1.0f / mag;

    // All checks passed; commit fields to the surface
    surface->normal.x = nx * mag;
    surface->normal.y = ny * mag;
    surface->normal.z = nz * mag;
    surface->originOffset = -(surface->normal.x * x1 + surface->normal.y * y1 + surface->normal.z * z1);

    surface->lowerY = MIN(MIN(y1, y2), y3) - 5;
    surface->upperY = MAX(MAX(y1, y2), y3) + 5;

    return true;
}

struct Surface* smlua_collision_add_surface(bool dynamic, s16 surfaceType, Vec3s vertex1, Vec3s vertex2, Vec3s vertex3) {
    s32 poolType = dynamic ? SURFACE_POOL_DYNAMIC : SURFACE_POOL_STATIC;

    // Allocate surface from the appropriate pool
    struct Surface *surface = alloc_surface(poolType);
    if (surface == NULL) { return NULL; }

    // Compute normal, plane equation, and Y bounds
    if (!calc_surface_fields(surface, vertex1, vertex2, vertex3)) {
        // Degenerate triangle: reclaim the pool slot that alloc_surface reserved.
        // Cannot use delete_surface() here because the surface was never added
        // to a partition or counter, so delete_surface's counter decrements
        // would cause drift.
        smlua_invalidate_surface(surface);
        swap_and_pop_surface_pool(poolType, surface);
        gSurfacesAllocated--;
        return NULL;
    }

    // Set vertices (prevVertex = vertex for first frame)
    vec3s_copy(surface->vertex1, vertex1);
    vec3s_copy(surface->vertex2, vertex2);
    vec3s_copy(surface->vertex3, vertex3);
    vec3s_copy(surface->prevVertex1, vertex1);
    vec3s_copy(surface->prevVertex2, vertex2);
    vec3s_copy(surface->prevVertex3, vertex3);
    surface->modifiedTimestamp = gGlobalTimer;

    // Set surface properties
    surface->type = surfaceType;
    surface->force = 0;
    surface->flags = dynamic ? SURFACE_FLAG_DYNAMIC : 0;
    surface->room = 0;
    surface->object = NULL;

    // Snapshot node count before add_surface allocates nodes
    s32 nodesBefore = gSurfaceNodesAllocated;

    // Add to spatial partition
    add_surface(surface);

    s32 nodesAdded = gSurfaceNodesAllocated - nodesBefore;

    // Update surface/node counters to stay in sync with load_area_terrain
    if (poolType == SURFACE_POOL_STATIC) {
        gNumStaticSurfaces++;
        gNumStaticSurfaceNodes += nodesAdded;
    }

    return surface;
}

void smlua_collision_move_surface(struct Surface *surface, Vec3s vertex1, Vec3s vertex2, Vec3s vertex3) {
    if (surface == NULL) { return; }

    s32 poolType = surface->poolType;

    // Snapshot node count before removal
    s32 nodesBefore = gSurfaceNodesAllocated;

    // Remove from old spatial partition cells
    remove_surface_from_partition(surface);

    // Compute normal, plane equation, and Y bounds (surface is untouched on failure)
    if (!calc_surface_fields(surface, vertex1, vertex2, vertex3)) {
        // Degenerate triangle: re-add at old position without firing the hook
        add_surface_without_hook(surface);

        // Fix node counter drift from the remove + re-add round-trip
        s32 nodeDelta = gSurfaceNodesAllocated - nodesBefore;
        if (poolType == SURFACE_POOL_STATIC) {
            gNumStaticSurfaceNodes += nodeDelta;
        } else if (poolType == SURFACE_POOL_SOC) {
            gNumSOCSurfaceNodes += nodeDelta;
        }
        return;
    }

    // Update previous vertices for interpolation
    vec3s_copy(surface->prevVertex1, surface->vertex1);
    vec3s_copy(surface->prevVertex2, surface->vertex2);
    vec3s_copy(surface->prevVertex3, surface->vertex3);

    // Set new vertices
    vec3s_copy(surface->vertex1, vertex1);
    vec3s_copy(surface->vertex2, vertex2);
    vec3s_copy(surface->vertex3, vertex3);
    surface->modifiedTimestamp = gGlobalTimer;

    // Clear X_PROJECTION flag so add_surface can re-evaluate it
    surface->flags &= ~SURFACE_FLAG_X_PROJECTION;

    // Re-add to spatial partition without firing the hook (this is a move, not a new insertion)
    add_surface_without_hook(surface);

    // Update gNum*SurfaceNodes to account for the net change;
    // cell range may differ after a move, so node count can change.
    s32 nodeDelta = gSurfaceNodesAllocated - nodesBefore;
    if (poolType == SURFACE_POOL_STATIC) {
        gNumStaticSurfaceNodes += nodeDelta;
    } else if (poolType == SURFACE_POOL_SOC) {
        gNumSOCSurfaceNodes += nodeDelta;
    }
    // Dynamic nodes are reset each frame, no tracking needed
}

void smlua_collision_delete_surface(struct Surface *surface) {
    if (surface == NULL) { return; }
    delete_surface(surface);
}

bool surface_is_quicksand(struct Surface* surf) {
    if (surf == NULL) { return FALSE; }
    return SURFACE_IS_QUICKSAND(surf->type);
}

bool surface_is_not_hard(struct Surface* surf) {
    if (surf == NULL) { return FALSE; }
    return SURFACE_IS_NOT_HARD(surf->type);
}

bool surface_is_painting_warp(struct Surface* surf) {
    if (surf == NULL) { return FALSE; }
    return SURFACE_IS_PAINTING_WARP(surf->type);
}