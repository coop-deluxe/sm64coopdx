#include "dynos.cpp.h"
extern "C" {
#include "object_fields.h"
#include "game/object_helpers.h"
#include "game/segment2.h"
#include "game/level_geo.h"
#include "game/level_update.h"
#include "game/moving_texture.h"
#include "game/paintings.h"
#include "game/geo_misc.h"
#include "game/mario_misc.h"
#include "game/mario_actions_cutscene.h"
#include "game/screen_transition.h"
#include "game/object_list_processor.h"
#include "game/behavior_actions.h"
#include "game/rendering_graph_node.h"
#include "actors/common0.h"
#include "actors/common1.h"
#include "actors/group0.h"
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
#include "actors/custom0.h"
#include "actors/zcustom0.h"
#include "levels/bbh/header.h"
#include "levels/bitdw/header.h"
#include "levels/bitfs/header.h"
#include "levels/bits/header.h"
#include "levels/bob/header.h"
#include "levels/bowser_2/header.h"
#include "levels/bowser_3/header.h"
#include "levels/castle_grounds/header.h"
#include "levels/castle_inside/header.h"
#include "levels/ccm/header.h"
#include "levels/ddd/header.h"
#include "levels/hmc/header.h"
#include "levels/jrb/header.h"
#include "levels/lll/header.h"
#include "levels/rr/header.h"
#include "levels/sl/header.h"
#include "levels/ssl/header.h"
#include "levels/thi/header.h"
#include "levels/ttc/header.h"
#include "levels/ttm/header.h"
#include "levels/wdw/header.h"
#include "levels/wf/header.h"
}

//
// String
//

static const struct { const char *mStr; u8 mChar64; s32 mWidth; } sSm64CharMap[] = {
    { "0",   0x00, 7 }, { "1",  0x01,  7 }, { "2",   0x02, 7 }, { "3",   0x03, 7 }, { "4",   0x04,  7 }, { "5",   0x05,  7 },
    { "6",   0x06, 7 }, { "7",  0x07,  7 }, { "8",   0x08, 7 }, { "9",   0x09, 7 }, { "A",   0x0A,  6 }, { "B",   0x0B,  6 },
    { "C",   0x0C, 6 }, { "D",  0x0D,  6 }, { "E",   0x0E, 6 }, { "F",   0x0F, 6 }, { "G",   0x10,  6 }, { "H",   0x11,  6 },
    { "I",   0x12, 5 }, { "J",  0x13,  6 }, { "K",   0x14, 6 }, { "L",   0x15, 5 }, { "M",   0x16,  8 }, { "N",   0x17,  8 },
    { "O",   0x18, 6 }, { "P",  0x19,  6 }, { "Q",   0x1A, 6 }, { "R",   0x1B, 6 }, { "S",   0x1C,  6 }, { "T",   0x1D,  5 },
    { "U",   0x1E, 6 }, { "V",  0x1F,  6 }, { "W",   0x20, 8 }, { "X",   0x21, 7 }, { "Y",   0x22,  6 }, { "Z",   0x23,  6 },
    { "a",   0x24, 6 }, { "b",  0x25,  5 }, { "c",   0x26, 5 }, { "d",   0x27, 6 }, { "e",   0x28,  5 }, { "f",   0x29,  5 },
    { "g",   0x2A, 6 }, { "h",  0x2B,  5 }, { "i",   0x2C, 4 }, { "j",   0x2D, 5 }, { "k",   0x2E,  5 }, { "l",   0x2F,  3 },
    { "m",   0x30, 7 }, { "n",  0x31,  5 }, { "o",   0x32, 5 }, { "p",   0x33, 5 }, { "q",   0x34,  6 }, { "r",   0x35,  5 },
    { "s",   0x36, 5 }, { "t",  0x37,  5 }, { "u",   0x38, 5 }, { "v",   0x39, 5 }, { "w",   0x3A,  7 }, { "x",   0x3B,  7 },
    { "y",   0x3C, 5 }, { "z",  0x3D,  5 }, { "\'",  0x3E, 4 }, { ".",   0x3F, 4 }, { "^",   0x50,  8 }, { "|",   0x51,  8 },
    { "<",   0x52, 8 }, { ">",  0x53,  8 }, { "[A]", 0x54, 7 }, { "[B]", 0x55, 7 }, { "[C]", 0x56,  6 }, { "[Z]", 0x57,  7 },
    { "[R]", 0x58, 7 }, { ",",  0x6F,  4 }, { " ",   0x9E, 5 }, { "-",   0x9F, 6 }, { "/",   0xD0, 10 }, { "[%]", 0xE0,  7 },
    { "(",   0xE1, 5 }, { ")(", 0xE2, 10 }, { ")",   0xE3, 5 }, { "+",   0xE4, 9 }, { "&",   0xE5,  8 }, { ":",   0xE6,  4 },
    { "!",   0xF2, 5 }, { "%",  0xF3,  7 }, { "?",   0xF4, 7 }, { "~",   0xF7, 8 }, { "$",   0xF9,  8 }, { "@",   0xFA, 10 },
    { "*",   0xFB, 6 }, { "=",  0xFD, 10 }, { "\n",  0xFE, 0 },
};

static const char *DynOS_String_AddChar64(u8 *aStr64, const char *pStr, s32 &aIndex) {
    for (const auto &c : sSm64CharMap) {
        if (strstr(pStr, c.mStr) == pStr) {
            aStr64[aIndex++] = c.mChar64;
            return pStr + strlen(c.mStr);
        }
    }

    // Put a space by default
    aStr64[aIndex++] = 0x9E;
    return pStr + 1;
}

u8 *DynOS_String_Convert(const char *aString, bool aHeapAlloc) {

    // Allocation
    static u8 sStringBuffer[8][2048];
    static u32 sStringBufferIndex = 0;
    u8 *_Str64;
    if (aHeapAlloc) {
        _Str64 = New<u8>(2048);
    } else {
        _Str64 = sStringBuffer[sStringBufferIndex];
        sStringBufferIndex = (sStringBufferIndex + 1) % 8;
    }

    // Conversion
    memset(_Str64, 0xFF, 2048);
    const char *pStr = aString;
    for (s32 i = 0; *pStr != 0 && i < 2047;) {
        pStr = DynOS_String_AddChar64(_Str64, pStr, i);
    }
    return _Str64;
}

u8 *DynOS_String_Decapitalize(u8 *aStr64) {
    bool _WasSpace = true;
    for (u8 *pStr64 = aStr64; *pStr64 != 0xFF; pStr64++) {
        if (*pStr64 >= 10 && *pStr64 <= 35) {
            if (_WasSpace) _WasSpace = false;
            else *pStr64 += 26;
        } else if (*pStr64 >= 63) {
            _WasSpace = true;
        }
    }
    return aStr64;
}

s32 DynOS_String_Length(const u8 *aStr64) {
    s32 _Length = 0;
    for (; aStr64 && *aStr64 != 255; aStr64++, _Length++);
    return _Length;
}

s32 DynOS_String_WidthChar64(u8 aChar64) {
    for (const auto &c : sSm64CharMap) {
        if (c.mChar64 == aChar64) {
            return c.mWidth;
        }
    }
    return 0;
}

s32 DynOS_String_Width(const u8 *aStr64) {
    s32 _Width = 0;
    for (; *aStr64 != 0xFF; aStr64++) {
        _Width += DynOS_String_WidthChar64(*aStr64);
    }
    return _Width;
}

//
// Geo
//

static void *geo_rotate_3d_coin(s32 callContext, void *node, UNUSED void *c) {
    if (callContext == GEO_CONTEXT_RENDER) {
        struct Object *obj = (struct Object *) gCurGraphNodeObject;
        struct GraphNodeRotation *rotNode = (struct GraphNodeRotation *) ((struct GraphNode *) node)->next;
        rotNode->rotation[0] = 0;
        rotNode->rotation[1] = obj->oAnimState;
        rotNode->rotation[2] = 0;
        obj->oAnimState += 0x0800;
    }
    return NULL;
}

//
// Actors
//

// &__Actors()
#define define_actor(geo) (const void *) #geo, (const void *) geo
static const void *sDynosActors[] = {
define_actor(amp_geo),
define_actor(birds_geo),
define_actor(blargg_geo),
define_actor(blue_coin_switch_geo),
define_actor(black_bobomb_geo),
define_actor(bobomb_buddy_geo),
define_actor(boo_geo),
define_actor(boo_castle_geo),
define_actor(bookend_geo),
define_actor(bookend_part_geo),
define_actor(bowling_ball_geo),
define_actor(bowling_ball_track_geo),
define_actor(bowser_geo),
define_actor(bowser2_geo),
define_actor(bowser_bomb_geo),
define_actor(bowser_flames_geo),
define_actor(bowser_impact_smoke_geo),
define_actor(bowser_1_yellow_sphere_geo),
define_actor(invisible_bowser_accessory_geo),
define_actor(bowser_key_geo),
define_actor(bowser_key_cutscene_geo),
define_actor(breakable_box_geo),
define_actor(breakable_box_small_geo),
define_actor(bub_geo),
define_actor(bubba_geo),
define_actor(bubble_geo),
define_actor(bullet_bill_geo),
define_actor(bully_geo),
define_actor(bully_boss_geo),
define_actor(burn_smoke_geo),
define_actor(butterfly_geo),
define_actor(cannon_barrel_geo),
define_actor(cannon_base_geo),
define_actor(cap_switch_geo),
define_actor(cartoon_star_geo),
define_actor(chain_chomp_geo),
define_actor(checkerboard_platform_geo),
define_actor(chilly_chief_geo),
define_actor(chilly_chief_big_geo),
define_actor(chuckya_geo),
define_actor(clam_shell_geo),
define_actor(yellow_coin_geo),
define_actor(yellow_coin_no_shadow_geo),
define_actor(blue_coin_geo),
define_actor(blue_coin_no_shadow_geo),
define_actor(red_coin_geo),
define_actor(red_coin_no_shadow_geo),
define_actor(dirt_animation_geo),
define_actor(dorrie_geo),
define_actor(cabin_door_geo),
define_actor(castle_door_geo),
define_actor(castle_door_0_star_geo),
define_actor(castle_door_1_star_geo),
define_actor(castle_door_3_stars_geo),
define_actor(haunted_door_geo),
define_actor(hazy_maze_door_geo),
define_actor(metal_door_geo),
define_actor(key_door_geo),
define_actor(wooden_door_geo),
define_actor(enemy_lakitu_geo),
define_actor(exclamation_box_geo),
define_actor(exclamation_box_outline_geo),
define_actor(explosion_geo),
define_actor(eyerok_left_hand_geo),
define_actor(eyerok_right_hand_geo),
define_actor(fish_geo),
define_actor(cyan_fish_geo),
define_actor(flyguy_geo),
define_actor(red_flame_geo),
define_actor(red_flame_shadow_geo),
define_actor(blue_flame_geo),
define_actor(fwoosh_geo),
define_actor(goomba_geo),
define_actor(haunted_cage_geo),
define_actor(haunted_chair_geo),
define_actor(heart_geo),
define_actor(heave_ho_geo),
define_actor(hoot_geo),
define_actor(king_bobomb_geo),
define_actor(klepto_geo),
define_actor(koopa_with_shell_geo),
define_actor(koopa_without_shell_geo),
define_actor(koopa_flag_geo),
define_actor(koopa_shell_geo),
define_actor(lakitu_geo),
define_actor(mad_piano_geo),
define_actor(manta_seg5_geo_05008D14),
define_actor(mario_geo),
define_actor(marios_cap_geo),
define_actor(marios_metal_cap_geo),
define_actor(marios_wing_cap_geo),
define_actor(marios_winged_metal_cap_geo),
define_actor(metal_box_geo),
define_actor(metallic_ball_geo),
define_actor(mips_geo),
define_actor(mist_geo),
define_actor(moneybag_geo),
define_actor(monty_mole_geo),
define_actor(mr_blizzard_geo),
define_actor(mr_blizzard_hidden_geo),
define_actor(mr_i_geo),
define_actor(mr_i_iris_geo),
define_actor(mushroom_1up_geo),
define_actor(number_geo),
define_actor(peach_geo),
define_actor(penguin_geo),
define_actor(piranha_plant_geo),
define_actor(pokey_head_geo),
define_actor(pokey_body_part_geo),
define_actor(purple_marble_geo),
define_actor(purple_switch_geo),
define_actor(scuttlebug_geo),
define_actor(seaweed_geo),
define_actor(skeeter_geo),
define_actor(small_key_geo),
define_actor(small_water_splash_geo),
define_actor(smoke_geo),
define_actor(snufit_geo),
define_actor(sparkles_geo),
define_actor(sparkles_animation_geo),
define_actor(spindrift_geo),
define_actor(spiny_geo),
define_actor(spiny_ball_geo),
define_actor(star_geo),
define_actor(transparent_star_geo),
define_actor(sushi_geo),
define_actor(swoop_geo),
define_actor(thwomp_geo),
define_actor(toad_geo),
define_actor(treasure_chest_base_geo),
define_actor(treasure_chest_lid_geo),
define_actor(bubbly_tree_geo),
define_actor(spiky_tree_geo),
define_actor(snow_tree_geo),
define_actor(palm_tree_geo),
define_actor(leaves_geo),
define_actor(tweester_geo),
define_actor(ukiki_geo),
define_actor(unagi_geo),
define_actor(warp_pipe_geo),
define_actor(water_bomb_geo),
define_actor(water_bomb_shadow_geo),
define_actor(water_ring_geo),
define_actor(water_splash_geo),
define_actor(idle_water_wave_geo),
define_actor(wave_trail_geo),
define_actor(white_particle_geo),
define_actor(white_puff_geo),
define_actor(whomp_geo),
define_actor(wiggler_head_geo),
define_actor(wiggler_body_geo),
define_actor(wooden_post_geo),
define_actor(wooden_signpost_geo),
define_actor(yellow_sphere_geo),
define_actor(yoshi_geo),
define_actor(yoshi_egg_geo),
// coop models
define_actor(error_model_geo),
define_actor(luigi_geo),
define_actor(luigis_cap_geo),
define_actor(luigis_metal_cap_geo),
define_actor(luigis_wing_cap_geo),
define_actor(luigis_winged_metal_cap_geo),
define_actor(toad_player_geo),
define_actor(toads_cap_geo),
define_actor(toads_metal_cap_geo),
define_actor(toads_wing_cap_geo),
define_actor(waluigi_geo),
define_actor(waluigis_cap_geo),
define_actor(waluigis_metal_cap_geo),
define_actor(waluigis_wing_cap_geo),
define_actor(waluigis_winged_metal_cap_geo),
define_actor(wario_geo),
define_actor(warios_cap_geo),
define_actor(warios_metal_cap_geo),
define_actor(warios_wing_cap_geo),
define_actor(warios_winged_metal_cap_geo),
};

static Array<Pair<const char*, void *>> sDynosCustomActors;

void DynOS_Geo_AddActorCustom(const SysPath &aPackFolder, const char *aActorName) {
    // check for duplicates
    bool isUnique = true;
    s32 foundIndex = -1;
    for (s32 i = 0; i < DynOS_Geo_GetActorCount(); ++i) {
        if (!strcmp(DynOS_Geo_GetActorName(i), aActorName)) {
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
    s32 index = DynOS_Geo_GetActorCount();
    if (isUnique) {
        sDynosCustomActors.Add({ actorName, geoLayout });
    } else {
        index = foundIndex;
        free(actorName);
    }

    // Alloc and init the actors gfx list
    Array<ActorGfx> &pActorGfxList = DynOS_Gfx_GetActorList();
    pActorGfxList.Resize(DynOS_Geo_GetActorCount());
    pActorGfxList[index].mPackIndex = 99;
    pActorGfxList[index].mGfxData   = _GfxData;
    pActorGfxList[index].mGraphNode = (GraphNode *) DynOS_Geo_GetGraphNode(geoLayout, true);
}

s32 DynOS_Geo_GetActorCount() {
    s32 arrayCount = (s32) (sizeof(sDynosActors) / (2 * sizeof(sDynosActors[0])));
    return (s32) arrayCount + sDynosCustomActors.Count();
}

const char *DynOS_Geo_GetActorName(s32 aIndex) {
    s32 arrayCount = (s32) (sizeof(sDynosActors) / (2 * sizeof(sDynosActors[0])));
    if (aIndex < arrayCount) { return (const char *) sDynosActors[2 * aIndex]; }
    return sDynosCustomActors[aIndex - arrayCount].first;
}

const void *DynOS_Geo_GetActorLayout(s32 aIndex) {
    s32 arrayCount = (s32) (sizeof(sDynosActors) / (2 * sizeof(sDynosActors[0])));
    if (aIndex < arrayCount) { return (const void *) sDynosActors[2 * aIndex + 1]; }
    return sDynosCustomActors[aIndex - arrayCount].second;
}

const void *DynOS_Geo_GetActorLayoutFromName(const char *aActorName) {
    for (s32 i = 0; i < DynOS_Geo_GetActorCount(); ++i) {
        if (!strcmp(DynOS_Geo_GetActorName(i), aActorName)) {
            return DynOS_Geo_GetActorLayout(i);
        }
    }
    return NULL;
}

s32 DynOS_Geo_GetActorIndex(const void *aGeoLayout) {
    for (s32 i = 0; i < DynOS_Geo_GetActorCount(); ++i) {
        if (DynOS_Geo_GetActorLayout(i) == aGeoLayout) {
            return i;
        }
    }
    return -1;
}

bool DynOS_Geo_IsCustomActor(s32 aIndex) {
    s32 arrayCount = (s32) (sizeof(sDynosActors) / (2 * sizeof(sDynosActors[0])));
    return aIndex >= arrayCount;
}

//
// Geo Functions
//

static const Array<Pair<const char *, void *>> &__GeoFunctions() {
#define define_geo_function(name) { #name, (void *) name }
static const Array<Pair<const char *, void *>> sGeoFunctions = {
    define_geo_function(geo_mirror_mario_set_alpha),
    define_geo_function(geo_switch_mario_stand_run),
    define_geo_function(geo_switch_mario_eyes),
    define_geo_function(geo_mario_tilt_torso),
    define_geo_function(geo_mario_head_rotation),
    define_geo_function(geo_switch_mario_hand),
    define_geo_function(geo_mario_hand_foot_scaler),
    define_geo_function(geo_switch_mario_cap_effect),
    define_geo_function(geo_switch_mario_cap_on_off),
    define_geo_function(geo_mario_rotate_wing_cap_wings),
    define_geo_function(geo_switch_mario_hand_grab_pos),
    define_geo_function(geo_render_mirror_mario),
    define_geo_function(geo_mirror_mario_backface_culling),
    define_geo_function(geo_update_projectile_pos_from_parent),
    define_geo_function(geo_update_layer_transparency),
    define_geo_function(geo_switch_anim_state),
    define_geo_function(geo_switch_area),
    define_geo_function(geo_camera_main),
    define_geo_function(geo_camera_fov),
    define_geo_function(geo_envfx_main),
    define_geo_function(geo_skybox_main),
    define_geo_function(geo_wdw_set_initial_water_level),
    define_geo_function(geo_movtex_pause_control),
    define_geo_function(geo_movtex_draw_water_regions),
    define_geo_function(geo_movtex_draw_nocolor),
    define_geo_function(geo_movtex_draw_colored),
    define_geo_function(geo_movtex_draw_colored_no_update),
    define_geo_function(geo_movtex_draw_colored_2_no_update),
    define_geo_function(geo_movtex_update_horizontal),
    define_geo_function(geo_movtex_draw_colored_no_update),
    define_geo_function(geo_painting_draw),
    define_geo_function(geo_painting_update),
    define_geo_function(geo_exec_inside_castle_light),
    define_geo_function(geo_exec_flying_carpet_timer_update),
    define_geo_function(geo_exec_flying_carpet_create),
    define_geo_function(geo_exec_cake_end_screen),
    define_geo_function(geo_cannon_circle_base),
    define_geo_function(geo_move_mario_part_from_parent),
    define_geo_function(geo_bits_bowser_coloring),
    define_geo_function(geo_update_body_rot_from_parent),
    define_geo_function(geo_switch_bowser_eyes),
    define_geo_function(geo_switch_tuxie_mother_eyes),
    define_geo_function(geo_update_held_mario_pos),
    define_geo_function(geo_snufit_move_mask),
    define_geo_function(geo_snufit_scale_body),
    define_geo_function(geo_scale_bowser_key),
    { "geo_rotate_coin", (void *) geo_rotate_3d_coin },
    define_geo_function(geo_offset_klepto_held_object),
    define_geo_function(geo_switch_peach_eyes),
    // coop-specific
    define_geo_function(geo_mario_set_player_colors),
};
#undef define_geo_function
return sGeoFunctions;
}
#define sGeoFunctions __GeoFunctions()

void *DynOS_Geo_GetFunctionPointerFromName(const String &aName) {
    for (const auto &_GeoFunction : sGeoFunctions) {
        if (aName == _GeoFunction.first) {
            return _GeoFunction.second;
        }
    };
    return NULL;
}

void *DynOS_Geo_GetFunctionPointerFromIndex(s32 aIndex) {
    return sGeoFunctions[aIndex].second;
}

s32 DynOS_Geo_GetFunctionIndex(const void *aPtr) {
    for (const auto &_GeoFunction : sGeoFunctions) {
        if (_GeoFunction.second == aPtr) {
            return (s32) (&_GeoFunction - sGeoFunctions.begin());
        }
    }
    return -1;
}

static void _RelocateGraphNodePointers(struct GraphNode *aHead, u64 aOffset) {
    struct GraphNode *_Node = aHead;
    do {
        if (_Node->prev) {
            _Node->prev = (struct GraphNode *) ((u64) _Node->prev + aOffset);
        }
        if (_Node->next) {
            _Node->next = (struct GraphNode *) ((u64) _Node->next + aOffset);
        }
        if (_Node->parent) {
            _Node->parent = (struct GraphNode *) ((u64) _Node->parent + aOffset);
        }
        if (_Node->children) {
            _Node->children = (struct GraphNode *) ((u64) _Node->children + aOffset);
            _RelocateGraphNodePointers(_Node->children, aOffset);
        }
        _Node = _Node->next;
    } while (_Node != aHead);
}

void *DynOS_Geo_GetGraphNode(const void *aGeoLayout, bool aKeepInMemory) {
    static Array<Pair<void *, void *>> sLoadedGraphNodes;
    if (aKeepInMemory) {
        s32 _LoadedGraphNodeIndex = sLoadedGraphNodes.FindIf([&aGeoLayout](const Pair<void *, void *> &aLoadedGraphNode) { return aLoadedGraphNode.first == aGeoLayout; });
        if (_LoadedGraphNodeIndex != -1) {
            return sLoadedGraphNodes[_LoadedGraphNodeIndex].second;
        }
    }

    // Process the geo layout on a large pool of memory (16 MB)
    struct AllocOnlyPool *_Pool = (struct AllocOnlyPool *) calloc(1, 0x1000000);
    _Pool->totalSpace = 0x1000000    - sizeof(struct AllocOnlyPool);
    _Pool->usedSpace  = 0;
    _Pool->startPtr   = (u8 *) _Pool + sizeof(struct AllocOnlyPool);
    _Pool->freePtr    = (u8 *) _Pool + sizeof(struct AllocOnlyPool);
    void *_Processed  = process_geo_layout(_Pool, (void *) aGeoLayout);

    // Copy the graph node data to the minimum amount of memory needed
    if (_Processed && _Pool->usedSpace != 0) {
        struct GraphNode *_Node = (struct GraphNode *) calloc(1, _Pool->usedSpace);
        memcpy(_Node, _Pool->startPtr, _Pool->usedSpace);

        // Relocate all graph pointers
        u64 _Offset = (u64) _Node - (u64) _Pool->startPtr;
        _RelocateGraphNodePointers(_Node, _Offset);

        // Add it to loaded graph nodes
        if (aKeepInMemory) {
            sLoadedGraphNodes.Add({ (void *) aGeoLayout, (void *) _Node });
        }
        free(_Pool);
        return _Node;
    }
    free(_Pool);
    return NULL;
}

  ////////////////
 // Collisions //
////////////////

static Array<Pair<const char*, DataNode<Collision>*>> sDynosCollisions;

void DynOS_Col_Add(const SysPath &aPackFolder, const char *aCollisionName) {
    // check for duplicates
    for (s32 i = 0; i < sDynosCollisions.Count(); ++i) {
        if (!strcmp(sDynosCollisions[i].first, aCollisionName)) {
            return;
        }
    }

    u16 collisionLen = strlen(aCollisionName);
    char* collisionName = (char*)calloc(1, sizeof(char) * (collisionLen + 1));
    strcpy(collisionName, aCollisionName);

    DataNode<Collision>* _Node = DynOS_Col_LoadFromBinary(aPackFolder, collisionName);
    if (!_Node) {
        free(collisionName);
        return;
    }

    // Add to collisions
    sDynosCollisions.Add({ collisionName, _Node });
}

Collision* DynOS_Col_Get(const char* collisionName) {
    for (s32 i = 0; i < sDynosCollisions.Count(); ++i) {
        if (!strcmp(sDynosCollisions[i].first, collisionName)) {
            return sDynosCollisions[i].second->mData;
        }
    }
    return NULL;
}

  ////////////
 // Levels //
////////////

#define define_lvl_geo(geo) (const void *) #geo, (const void *) geo
static const void *sDynosLevelGeos[] = {
    define_lvl_geo(geo_bbh_0005B0),
    define_lvl_geo(geo_bbh_0005C8),
    define_lvl_geo(geo_bbh_0005E0),
    define_lvl_geo(geo_bbh_0005F8),
    define_lvl_geo(geo_bbh_000610),
    define_lvl_geo(geo_bbh_000628),
    define_lvl_geo(geo_bbh_000640),
    define_lvl_geo(geo_bbh_000658),
    define_lvl_geo(geo_bbh_000670),
    define_lvl_geo(geo_bbh_0006B0),
    define_lvl_geo(geo_bbh_0006E8),
    define_lvl_geo(geo_bbh_000730),
    define_lvl_geo(geo_bbh_000750),
    define_lvl_geo(geo_bbh_000768),
    define_lvl_geo(geo_bbh_0007B0),
    define_lvl_geo(geo_bbh_0007D0),
    define_lvl_geo(geo_bbh_000800),
    define_lvl_geo(geo_bbh_000828),
    define_lvl_geo(geo_bbh_000860),
    define_lvl_geo(geo_bbh_000888),
    define_lvl_geo(geo_bbh_0008B0),
    define_lvl_geo(geo_bbh_0008E8),
    define_lvl_geo(geo_bbh_000950),
    define_lvl_geo(geo_bbh_0009C8),
    define_lvl_geo(geo_bbh_000A18),
    define_lvl_geo(geo_bbh_000A60),
    define_lvl_geo(geo_bbh_000AD8),
    define_lvl_geo(geo_bbh_000B28),
    define_lvl_geo(geo_bbh_000B88),
    define_lvl_geo(geo_bbh_000BF0),
    define_lvl_geo(geo_bbh_000C38),
    define_lvl_geo(geo_bbh_000C88),
    define_lvl_geo(geo_bbh_000CE8),
    define_lvl_geo(geo_bbh_000D20),
    define_lvl_geo(geo_bbh_000D68),
    define_lvl_geo(geo_bbh_000DB0),
    define_lvl_geo(geo_bbh_000DF0),
    define_lvl_geo(geo_bbh_000E40),
    define_lvl_geo(geo_bbh_000E80),
    define_lvl_geo(geo_bbh_000EB0),
    define_lvl_geo(geo_bbh_000F00),
    define_lvl_geo(geo_bitdw_0003C0),
    define_lvl_geo(geo_bitdw_0003D8),
    define_lvl_geo(geo_bitdw_0003F0),
    define_lvl_geo(geo_bitdw_000408),
    define_lvl_geo(geo_bitdw_000420),
    define_lvl_geo(geo_bitdw_000438),
    define_lvl_geo(geo_bitdw_000450),
    define_lvl_geo(geo_bitdw_000468),
    define_lvl_geo(geo_bitdw_000480),
    define_lvl_geo(geo_bitdw_000498),
    define_lvl_geo(geo_bitdw_0004B0),
    define_lvl_geo(geo_bitdw_0004C8),
    define_lvl_geo(geo_bitdw_0004E0),
    define_lvl_geo(geo_bitdw_0004F8),
    define_lvl_geo(geo_bitdw_000510),
    define_lvl_geo(geo_bitdw_000528),
    define_lvl_geo(geo_bitdw_000540),
    define_lvl_geo(geo_bitdw_000558),
    define_lvl_geo(geo_bitdw_000570),
    define_lvl_geo(geo_bitdw_000588),
    define_lvl_geo(geo_bitdw_0005A0),
    define_lvl_geo(geo_bitdw_0005B8),
    define_lvl_geo(geo_bitdw_0005D0),
    define_lvl_geo(geo_bitdw_0005E8),
    define_lvl_geo(geo_bitdw_000600),
    define_lvl_geo(geo_bitdw_000618),
    define_lvl_geo(bitfs_geo_0004B0),
    define_lvl_geo(bitfs_geo_0004C8),
    define_lvl_geo(bitfs_geo_0004E0),
    define_lvl_geo(bitfs_geo_0004F8),
    define_lvl_geo(bitfs_geo_000510),
    define_lvl_geo(bitfs_geo_000528),
    define_lvl_geo(bitfs_geo_000540),
    define_lvl_geo(bitfs_geo_000558),
    define_lvl_geo(bitfs_geo_000570),
    define_lvl_geo(bitfs_geo_000588),
    define_lvl_geo(bitfs_geo_0005A0),
    define_lvl_geo(bitfs_geo_0005B8),
    define_lvl_geo(bitfs_geo_0005D0),
    define_lvl_geo(bitfs_geo_0005E8),
    define_lvl_geo(bitfs_geo_000600),
    define_lvl_geo(bitfs_geo_000618),
    define_lvl_geo(bitfs_geo_000630),
    define_lvl_geo(bitfs_geo_000648),
    define_lvl_geo(bitfs_geo_000660),
    define_lvl_geo(bitfs_geo_000678),
    define_lvl_geo(bitfs_geo_000690),
    define_lvl_geo(bitfs_geo_0006A8),
    define_lvl_geo(bitfs_geo_0006C0),
    define_lvl_geo(bitfs_geo_0006D8),
    define_lvl_geo(bitfs_geo_0006F0),
    define_lvl_geo(bitfs_geo_000708),
    define_lvl_geo(bitfs_geo_000728),
    define_lvl_geo(bitfs_geo_000740),
    define_lvl_geo(bitfs_geo_000758),
    define_lvl_geo(bitfs_geo_000770),
    define_lvl_geo(bitfs_geo_000788),
    define_lvl_geo(bitfs_geo_0007A0),
    define_lvl_geo(bits_geo_000430),
    define_lvl_geo(bits_geo_000448),
    define_lvl_geo(bits_geo_000460),
    define_lvl_geo(bits_geo_000478),
    define_lvl_geo(bits_geo_000490),
    define_lvl_geo(bits_geo_0004A8),
    define_lvl_geo(bits_geo_0004C0),
    define_lvl_geo(bits_geo_0004D8),
    define_lvl_geo(bits_geo_0004F0),
    define_lvl_geo(bits_geo_000508),
    define_lvl_geo(bits_geo_000520),
    define_lvl_geo(bits_geo_000538),
    define_lvl_geo(bits_geo_000550),
    define_lvl_geo(bits_geo_000568),
    define_lvl_geo(bits_geo_000580),
    define_lvl_geo(bits_geo_000598),
    define_lvl_geo(bits_geo_0005B0),
    define_lvl_geo(bits_geo_0005C8),
    define_lvl_geo(bits_geo_0005E0),
    define_lvl_geo(bits_geo_0005F8),
    define_lvl_geo(bits_geo_000610),
    define_lvl_geo(bits_geo_000628),
    define_lvl_geo(bits_geo_000640),
    define_lvl_geo(bits_geo_000658),
    define_lvl_geo(bits_geo_000670),
    define_lvl_geo(bits_geo_000688),
    define_lvl_geo(bits_geo_0006A0),
    define_lvl_geo(bits_geo_0006B8),
    define_lvl_geo(bits_geo_0006D0),
    define_lvl_geo(bits_geo_0006E8),
    define_lvl_geo(bits_geo_000700),
    define_lvl_geo(bits_geo_000718),
    define_lvl_geo(bob_geo_000440),
    define_lvl_geo(bob_geo_000458),
    define_lvl_geo(bob_geo_000470),
    define_lvl_geo(bob_geo_000488),
    define_lvl_geo(bowser_2_geo_000170),
    define_lvl_geo(bowser_2_geo_000188),
    define_lvl_geo(bowser_3_geo_000290),
    define_lvl_geo(bowser_3_geo_0002A8),
    define_lvl_geo(bowser_3_geo_0002C0),
    define_lvl_geo(bowser_3_geo_0002D8),
    define_lvl_geo(bowser_3_geo_0002F0),
    define_lvl_geo(bowser_3_geo_000308),
    define_lvl_geo(bowser_3_geo_000320),
    define_lvl_geo(bowser_3_geo_000338),
    define_lvl_geo(bowser_3_geo_000350),
    define_lvl_geo(bowser_3_geo_000368),
    define_lvl_geo(bowser_3_geo_000380),
    define_lvl_geo(bowser_3_geo_000398),
    define_lvl_geo(castle_grounds_geo_000660),
    define_lvl_geo(castle_grounds_geo_0006F4),
    define_lvl_geo(castle_grounds_geo_00070C),
    define_lvl_geo(castle_grounds_geo_000724),
    define_lvl_geo(castle_grounds_geo_00073C),
    define_lvl_geo(castle_geo_000F00),
    define_lvl_geo(castle_geo_000F18),
    define_lvl_geo(castle_geo_000F30),
    define_lvl_geo(castle_geo_000F70),
    define_lvl_geo(castle_geo_000F88),
    define_lvl_geo(castle_geo_000FA8),
    define_lvl_geo(castle_geo_000FD0),
    define_lvl_geo(castle_geo_001000),
    define_lvl_geo(castle_geo_001038),
    define_lvl_geo(castle_geo_001088),
    define_lvl_geo(castle_geo_0010C8),
    define_lvl_geo(castle_geo_001110),
    define_lvl_geo(castle_geo_001158),
    define_lvl_geo(castle_geo_0011A8),
    define_lvl_geo(castle_geo_001200),
    define_lvl_geo(castle_geo_001260),
    define_lvl_geo(castle_geo_0012C8),
    define_lvl_geo(castle_geo_001348),
    define_lvl_geo(castle_geo_0013B8),
    define_lvl_geo(castle_geo_001400),
    define_lvl_geo(castle_geo_001518),
    define_lvl_geo(castle_geo_001530),
    define_lvl_geo(castle_geo_001548),
    define_lvl_geo(castle_geo_001560),
    define_lvl_geo(castle_geo_001578),
    define_lvl_geo(castle_geo_0015B8),
    define_lvl_geo(castle_geo_0015F8),
    define_lvl_geo(castle_geo_001628),
    define_lvl_geo(castle_geo_001668),
    define_lvl_geo(castle_geo_001690),
    define_lvl_geo(castle_geo_0016D8),
    define_lvl_geo(castle_geo_001740),
    define_lvl_geo(castle_geo_001798),
    define_lvl_geo(castle_geo_001800),
    define_lvl_geo(castle_geo_001858),
    define_lvl_geo(castle_geo_001940),
    define_lvl_geo(castle_geo_001958),
    define_lvl_geo(castle_geo_001980),
    define_lvl_geo(castle_geo_0019C8),
    define_lvl_geo(castle_geo_0019F8),
    define_lvl_geo(castle_geo_001A30),
    define_lvl_geo(castle_geo_001A58),
    define_lvl_geo(castle_geo_001AB8),
    define_lvl_geo(castle_geo_001AF8),
    define_lvl_geo(castle_geo_001B48),
    define_lvl_geo(castle_geo_001BB0),
    define_lvl_geo(castle_geo_001C10),
    define_lvl_geo(ccm_geo_0003D0),
    define_lvl_geo(ccm_geo_0003F0),
    define_lvl_geo(ccm_geo_00040C),
    define_lvl_geo(ccm_geo_00042C),
    define_lvl_geo(ccm_geo_00045C),
    define_lvl_geo(ccm_geo_000494),
    define_lvl_geo(ccm_geo_0004BC),
    define_lvl_geo(ccm_geo_0004E4),
    define_lvl_geo(ccm_geo_00051C),
    define_lvl_geo(ccm_geo_0005E8),
    define_lvl_geo(ddd_geo_000450),
    define_lvl_geo(ddd_geo_000478),
    define_lvl_geo(ddd_geo_0004A0),
    define_lvl_geo(ddd_geo_0004C0),
    define_lvl_geo(ddd_geo_000570),
    define_lvl_geo(hmc_geo_000530),
    define_lvl_geo(hmc_geo_000548),
    define_lvl_geo(hmc_geo_000570),
    define_lvl_geo(hmc_geo_000588),
    define_lvl_geo(hmc_geo_0005A0),
    define_lvl_geo(hmc_geo_0005B8),
    define_lvl_geo(hmc_geo_0005D0),
    define_lvl_geo(hmc_geo_0005E8),
    define_lvl_geo(hmc_geo_000618),
    define_lvl_geo(hmc_geo_000658),
    define_lvl_geo(hmc_geo_0006A8),
    define_lvl_geo(hmc_geo_0006E0),
    define_lvl_geo(hmc_geo_000700),
    define_lvl_geo(hmc_geo_000748),
    define_lvl_geo(hmc_geo_000770),
    define_lvl_geo(hmc_geo_000798),
    define_lvl_geo(hmc_geo_0007F8),
    define_lvl_geo(hmc_geo_000850),
    define_lvl_geo(hmc_geo_0008D0),
    define_lvl_geo(hmc_geo_000938),
    define_lvl_geo(hmc_geo_000998),
    define_lvl_geo(hmc_geo_000A18),
    define_lvl_geo(hmc_geo_000A88),
    define_lvl_geo(hmc_geo_000AE8),
    define_lvl_geo(hmc_geo_000B48),
    define_lvl_geo(hmc_geo_000B90),
    define_lvl_geo(jrb_geo_000900),
    define_lvl_geo(jrb_geo_000918),
    define_lvl_geo(jrb_geo_000930),
    define_lvl_geo(jrb_geo_000948),
    define_lvl_geo(jrb_geo_000960),
    define_lvl_geo(jrb_geo_000978),
    define_lvl_geo(jrb_geo_000990),
    define_lvl_geo(jrb_geo_0009B0),
    define_lvl_geo(jrb_geo_0009C8),
    define_lvl_geo(jrb_geo_0009E8),
    define_lvl_geo(jrb_geo_000A00),
    define_lvl_geo(jrb_geo_000A18),
    define_lvl_geo(jrb_geo_000AFC),
    define_lvl_geo(lll_geo_0009E0),
    define_lvl_geo(lll_geo_0009F8),
    define_lvl_geo(lll_geo_000A10),
    define_lvl_geo(lll_geo_000A28),
    define_lvl_geo(lll_geo_000A40),
    define_lvl_geo(lll_geo_000A60),
    define_lvl_geo(lll_geo_000A78),
    define_lvl_geo(lll_geo_000A90),
    define_lvl_geo(lll_geo_000AA8),
    define_lvl_geo(lll_geo_000AC0),
    define_lvl_geo(lll_geo_000AD8),
    define_lvl_geo(lll_geo_000AF0),
    define_lvl_geo(lll_geo_000B08),
    define_lvl_geo(lll_geo_000B20),
    define_lvl_geo(lll_geo_000B38),
    define_lvl_geo(lll_geo_000B50),
    define_lvl_geo(lll_geo_000B68),
    define_lvl_geo(lll_geo_000B80),
    define_lvl_geo(lll_geo_000B98),
    define_lvl_geo(lll_geo_000BB0),
    define_lvl_geo(lll_geo_000BC8),
    define_lvl_geo(lll_geo_000BE0),
    define_lvl_geo(lll_geo_000BF8),
    define_lvl_geo(lll_geo_000C10),
    define_lvl_geo(lll_geo_000C30),
    define_lvl_geo(lll_geo_000C50),
    define_lvl_geo(lll_geo_000C70),
    define_lvl_geo(lll_geo_000C90),
    define_lvl_geo(lll_geo_000CB0),
    define_lvl_geo(lll_geo_000CD0),
    define_lvl_geo(lll_geo_000CF0),
    define_lvl_geo(lll_geo_000D10),
    define_lvl_geo(lll_geo_000D30),
    define_lvl_geo(lll_geo_000D50),
    define_lvl_geo(lll_geo_000D70),
    define_lvl_geo(lll_geo_000D90),
    define_lvl_geo(lll_geo_000DB0),
    define_lvl_geo(lll_geo_000DD0),
    define_lvl_geo(lll_geo_000DE8),
    define_lvl_geo(lll_geo_000E00),
    define_lvl_geo(lll_geo_000EA8),
    define_lvl_geo(lll_geo_000EC0),
    define_lvl_geo(rr_geo_000660),
    define_lvl_geo(rr_geo_000678),
    define_lvl_geo(rr_geo_000690),
    define_lvl_geo(rr_geo_0006A8),
    define_lvl_geo(rr_geo_0006C0),
    define_lvl_geo(rr_geo_0006D8),
    define_lvl_geo(rr_geo_0006F0),
    define_lvl_geo(rr_geo_000708),
    define_lvl_geo(rr_geo_000720),
    define_lvl_geo(rr_geo_000738),
    define_lvl_geo(rr_geo_000758),
    define_lvl_geo(rr_geo_000770),
    define_lvl_geo(rr_geo_000788),
    define_lvl_geo(rr_geo_0007A0),
    define_lvl_geo(rr_geo_0007B8),
    define_lvl_geo(rr_geo_0007D0),
    define_lvl_geo(rr_geo_0007E8),
    define_lvl_geo(rr_geo_000800),
    define_lvl_geo(rr_geo_000818),
    define_lvl_geo(rr_geo_000830),
    define_lvl_geo(rr_geo_000848),
    define_lvl_geo(rr_geo_000860),
    define_lvl_geo(rr_geo_000878),
    define_lvl_geo(rr_geo_000890),
    define_lvl_geo(rr_geo_0008A8),
    define_lvl_geo(rr_geo_0008C0),
    define_lvl_geo(rr_geo_0008D8),
    define_lvl_geo(rr_geo_0008F0),
    define_lvl_geo(rr_geo_000908),
    define_lvl_geo(rr_geo_000920),
    define_lvl_geo(rr_geo_000940),
    define_lvl_geo(rr_geo_000958),
    define_lvl_geo(rr_geo_000970),
    define_lvl_geo(rr_geo_000988),
    define_lvl_geo(rr_geo_0009A0),
    define_lvl_geo(rr_geo_0009B8),
    define_lvl_geo(rr_geo_0009D0),
    define_lvl_geo(sl_geo_000360),
    define_lvl_geo(sl_geo_000378),
    define_lvl_geo(sl_geo_000390),
    define_lvl_geo(sl_geo_0003A8),
    define_lvl_geo(sl_geo_000484),
    define_lvl_geo(ssl_geo_0005C0),
    define_lvl_geo(ssl_geo_0005D8),
    define_lvl_geo(ssl_geo_000618),
    define_lvl_geo(ssl_geo_000630),
    define_lvl_geo(ssl_geo_000648),
    define_lvl_geo(ssl_geo_000734),
    define_lvl_geo(ssl_geo_000764),
    define_lvl_geo(ssl_geo_000794),
    define_lvl_geo(ssl_geo_0007AC),
    define_lvl_geo(ssl_geo_0007CC),
    define_lvl_geo(ssl_geo_00088C),
    define_lvl_geo(thi_geo_0005B0),
    define_lvl_geo(thi_geo_0005C8),
    define_lvl_geo(thi_geo_0005F0),
    define_lvl_geo(thi_geo_000608),
    define_lvl_geo(thi_geo_0006D4),
    define_lvl_geo(thi_geo_00079C),
    define_lvl_geo(ttc_geo_000240),
    define_lvl_geo(ttc_geo_000258),
    define_lvl_geo(ttc_geo_000270),
    define_lvl_geo(ttc_geo_000288),
    define_lvl_geo(ttc_geo_0002A8),
    define_lvl_geo(ttc_geo_0002C8),
    define_lvl_geo(ttc_geo_0002E0),
    define_lvl_geo(ttc_geo_0002F8),
    define_lvl_geo(ttc_geo_000310),
    define_lvl_geo(ttc_geo_000328),
    define_lvl_geo(ttc_geo_000340),
    define_lvl_geo(ttc_geo_000358),
    define_lvl_geo(ttc_geo_000370),
    define_lvl_geo(ttc_geo_000388),
    define_lvl_geo(ttc_geo_0003A0),
    define_lvl_geo(ttc_geo_0003B8),
    define_lvl_geo(ttm_geo_000710),
    define_lvl_geo(ttm_geo_000730),
    define_lvl_geo(ttm_geo_000748),
    define_lvl_geo(ttm_geo_000778),
    define_lvl_geo(ttm_geo_0007A8),
    define_lvl_geo(ttm_geo_0007D8),
    define_lvl_geo(ttm_geo_000808),
    define_lvl_geo(ttm_geo_000830),
    define_lvl_geo(ttm_geo_000858),
    define_lvl_geo(ttm_geo_000880),
    define_lvl_geo(ttm_geo_0008A8),
    define_lvl_geo(ttm_geo_0008D0),
    define_lvl_geo(ttm_geo_0008F8),
    define_lvl_geo(ttm_geo_000920),
    define_lvl_geo(ttm_geo_000948),
    define_lvl_geo(ttm_geo_000970),
    define_lvl_geo(ttm_geo_000990),
    define_lvl_geo(ttm_geo_0009C0),
    define_lvl_geo(ttm_geo_0009F0),
    define_lvl_geo(ttm_geo_000A18),
    define_lvl_geo(ttm_geo_000A40),
    define_lvl_geo(ttm_geo_000A70),
    define_lvl_geo(ttm_geo_000B5C),
    define_lvl_geo(ttm_geo_000BEC),
    define_lvl_geo(ttm_geo_000C84),
    define_lvl_geo(ttm_geo_000D14),
    define_lvl_geo(ttm_geo_000D4C),
    define_lvl_geo(ttm_geo_000D84),
    define_lvl_geo(ttm_geo_000DBC),
    define_lvl_geo(ttm_geo_000DF4),
    define_lvl_geo(wdw_geo_000580),
    define_lvl_geo(wdw_geo_000598),
    define_lvl_geo(wdw_geo_0005C0),
    define_lvl_geo(wdw_geo_0005E8),
    define_lvl_geo(wdw_geo_000610),
    define_lvl_geo(wdw_geo_000628),
    define_lvl_geo(wdw_geo_000640),
    define_lvl_geo(wdw_geo_000658),
    define_lvl_geo(wdw_geo_000724),
    define_lvl_geo(wf_geo_0007E0),
    define_lvl_geo(wf_geo_000820),
    define_lvl_geo(wf_geo_000860),
    define_lvl_geo(wf_geo_000878),
    define_lvl_geo(wf_geo_000890),
    define_lvl_geo(wf_geo_0008A8),
    define_lvl_geo(wf_geo_0008E8),
    define_lvl_geo(wf_geo_000900),
    define_lvl_geo(wf_geo_000940),
    define_lvl_geo(wf_geo_000958),
    define_lvl_geo(wf_geo_0009A0),
    define_lvl_geo(wf_geo_0009B8),
    define_lvl_geo(wf_geo_0009D0),
    define_lvl_geo(wf_geo_0009E8),
    define_lvl_geo(wf_geo_000A00),
    define_lvl_geo(wf_geo_000A40),
    define_lvl_geo(wf_geo_000A58),
    define_lvl_geo(wf_geo_000A98),
    define_lvl_geo(wf_geo_000AB0),
    define_lvl_geo(wf_geo_000AC8),
    define_lvl_geo(wf_geo_000AE0),
    define_lvl_geo(wf_geo_000AF8),
    define_lvl_geo(wf_geo_000B10),
    define_lvl_geo(wf_geo_000B38),
    define_lvl_geo(wf_geo_000B60),
    define_lvl_geo(wf_geo_000B78),
    define_lvl_geo(wf_geo_000B90),
    define_lvl_geo(wf_geo_000BA8),
    define_lvl_geo(wf_geo_000BC8),
    define_lvl_geo(wf_geo_000BE0),
    define_lvl_geo(wf_geo_000BF8),
};

s32 DynOS_Lvl_GetGeoCount() {
    return (s32) (sizeof(sDynosLevelGeos) / (2 * sizeof(sDynosLevelGeos[0])));
}

const char *DynOS_Lvl_GetGeoName(s32 aIndex) {
     return (const char *) sDynosLevelGeos[2 * aIndex];
}

const void *DynOS_Lvl_GetGeoLayout(s32 aIndex) {
    return (const void *) sDynosLevelGeos[2 * aIndex + 1];
}

const void *DynOS_Lvl_GetGeoLayoutFromName(const char *aGeoName) {
    for (s32 i = 0; i < DynOS_Lvl_GetGeoCount(); ++i) {
        if (!strcmp(DynOS_Lvl_GetGeoName(i), aGeoName)) {
            return DynOS_Lvl_GetGeoLayout(i);
        }
    }
    return NULL;
}

s32 DynOS_Lvl_GetGeoIndex(const void *aGeoLayout) {
    for (s32 i = 0; i < DynOS_Lvl_GetGeoCount(); ++i) {
        if (DynOS_Lvl_GetGeoLayout(i) == aGeoLayout) {
            return i;
        }
    }
    return -1;
}

static Array<Pair<const char*, GfxData*>> sDynosCustomLevelScripts;

void DynOS_Lvl_Add(s32 modIndex, const SysPath &aPackFolder, const char *aLevelName) {
    // check for duplicates
    for (s32 i = 0; i < sDynosCustomLevelScripts.Count(); ++i) {
        if (!strcmp(sDynosCustomLevelScripts[i].first, aLevelName)) {
            return;
        }
    }

    u16 levelLen = strlen(aLevelName);
    char* levelName = (char*)calloc(1, sizeof(char) * (levelLen + 1));
    strcpy(levelName, aLevelName);

    GfxData* _Node = DynOS_Lvl_LoadFromBinary(aPackFolder, levelName);
    if (!_Node) {
        free(levelName);
        return;
    }

    // remember index
    _Node->mModIndex = modIndex;

    // Add to levels
    sDynosCustomLevelScripts.Add({ levelName, _Node });
}

LevelScript* DynOS_Lvl_Get(const char* levelName) {
    static u32 index = 0; // DO NOT COMMIT
    index = (index + 1) % sDynosCustomLevelScripts.Count();  // DO NOT COMMIT
    auto& scripts = sDynosCustomLevelScripts[index].second->mLevelScripts; // DO NOT COMMIT
    Print("Going to level: %s\n", scripts[scripts.Count() - 1]->mName); // DO NOT COMMIT
    return scripts[scripts.Count() - 1]->mData; // DO NOT COMMIT

    for (s32 i = 0; i < sDynosCustomLevelScripts.Count(); ++i) {
        if (!strcmp(sDynosCustomLevelScripts[i].first, levelName)) {
            auto& scripts = sDynosCustomLevelScripts[i].second->mLevelScripts;
            return scripts[scripts.Count() - 1]->mData;
        }
    }
    return NULL;
}

s32 DynOS_Lvl_GetModIndex(void* levelScript) {
    for (s32 i = 0; i < sDynosCustomLevelScripts.Count(); ++i) {
        auto& scripts = sDynosCustomLevelScripts[i].second->mLevelScripts;
        if (levelScript == scripts[scripts.Count() - 1]->mData) {
            return sDynosCustomLevelScripts[i].second->mModIndex;
        }
    }
    return -1;
}

DataNode<TexData> *DynOS_Lvl_Texture_Get(void *aPtr) {
    for (s32 i = 0; i < sDynosCustomLevelScripts.Count(); ++i) {
        auto &mTextures = sDynosCustomLevelScripts[i].second->mTextures;
        for (s32 j = 0; j < mTextures.Count(); j++) {
            auto &texture = mTextures[j];
            if (texture == aPtr) {
                return texture;
            }

        }
    }
    return NULL;
}