#include "dynos.cpp.h"
extern "C" {
#include "object_fields.h"
#include "engine/level_script.h"
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
#include "game/skybox.h"

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
// Geo
//

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
