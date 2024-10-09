#include "dynos.cpp.h"

extern "C" {
#include "include/level_misc_macros.h"
#include "include/macro_preset_names.h"
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnarrowing"

  /////////////
 // Parsing //
/////////////

#define MACRO_OBJECT_SIZE_PER_TOKEN 4

#define macro_object_constant(x) if (_Arg == #x) { return (s64) (x); }
static s64 ParseMacroObjectSymbolArg(GfxData* aGfxData, DataNode<MacroObject>* aNode, u64& aTokenIndex) {
    const String& _Arg = aNode->mTokens[aTokenIndex++];

    // Integers
    bool integerFound = false;
    s64 integerValue = DynOS_Misc_ParseInteger(_Arg, &integerFound);
    if (integerFound) {
        return integerValue;
    }

    // Surface constants
    macro_object_constant(macro_yellow_coin);
    macro_object_constant(macro_yellow_coin_2);
    macro_object_constant(macro_moving_blue_coin);
    macro_object_constant(macro_sliding_blue_coin);
    macro_object_constant(macro_red_coin);
    macro_object_constant(macro_empty_5);
    macro_object_constant(macro_coin_line_horizontal);
    macro_object_constant(macro_coin_ring_horizontal);
    macro_object_constant(macro_coin_arrow);
    macro_object_constant(macro_coin_line_horizontal_flying);
    macro_object_constant(macro_coin_line_vertical);
    macro_object_constant(macro_coin_ring_horizontal_flying);
    macro_object_constant(macro_coin_ring_vertical);
    macro_object_constant(macro_coin_arrow_flying);
    macro_object_constant(macro_hidden_star_trigger);
    macro_object_constant(macro_empty_15);
    macro_object_constant(macro_empty_16);
    macro_object_constant(macro_empty_17);
    macro_object_constant(macro_empty_18);
    macro_object_constant(macro_empty_19);
    macro_object_constant(macro_fake_star);
    macro_object_constant(macro_wooden_signpost);
    macro_object_constant(macro_cannon_closed);
    macro_object_constant(macro_bobomb_buddy_opens_cannon);
    macro_object_constant(macro_butterfly);
    macro_object_constant(macro_bouncing_fireball_copy);
    macro_object_constant(macro_fish_group_3);
    macro_object_constant(macro_fish_group);
    macro_object_constant(macro_unknown_28);
    macro_object_constant(macro_hidden_1up_in_pole);
    macro_object_constant(macro_huge_goomba);
    macro_object_constant(macro_tiny_goomba);
    macro_object_constant(macro_goomba_triplet_spawner);
    macro_object_constant(macro_goomba_quintuplet_spawner);
    macro_object_constant(macro_sign_on_wall);
    macro_object_constant(macro_chuckya);
    macro_object_constant(macro_cannon_open);
    macro_object_constant(macro_goomba);
    macro_object_constant(macro_homing_amp);
    macro_object_constant(macro_circling_amp);
    macro_object_constant(macro_unknown_40);
    macro_object_constant(macro_unknown_41);
    macro_object_constant(macro_free_bowling_ball);
    macro_object_constant(macro_snufit);
    macro_object_constant(macro_recovery_heart);
    macro_object_constant(macro_1up_sliding);
    macro_object_constant(macro_1up);
    macro_object_constant(macro_1up_jump_on_approach);
    macro_object_constant(macro_hidden_1up);
    macro_object_constant(macro_hidden_1up_trigger);
    macro_object_constant(macro_1up_2);
    macro_object_constant(macro_1up_3);
    macro_object_constant(macro_empty_52);
    macro_object_constant(macro_blue_coin_switch);
    macro_object_constant(macro_hidden_blue_coin);
    macro_object_constant(macro_wing_cap_switch);
    macro_object_constant(macro_metal_cap_switch);
    macro_object_constant(macro_vanish_cap_switch);
    macro_object_constant(macro_yellow_cap_switch);
    macro_object_constant(macro_unknown_59);
    macro_object_constant(macro_box_wing_cap);
    macro_object_constant(macro_box_metal_cap);
    macro_object_constant(macro_box_vanish_cap);
    macro_object_constant(macro_box_koopa_shell);
    macro_object_constant(macro_box_one_coin);
    macro_object_constant(macro_box_three_coins);
    macro_object_constant(macro_box_ten_coins);
    macro_object_constant(macro_box_1up);
    macro_object_constant(macro_box_star_1);
    macro_object_constant(macro_breakable_box_no_coins);
    macro_object_constant(macro_breakable_box_three_coins);
    macro_object_constant(macro_pushable_metal_box);
    macro_object_constant(macro_breakable_box_small);
    macro_object_constant(macro_floor_switch_hidden_objects);
    macro_object_constant(macro_hidden_box);
    macro_object_constant(macro_hidden_object_2);
    macro_object_constant(macro_hidden_object_3);
    macro_object_constant(macro_breakable_box_giant);
    macro_object_constant(macro_koopa_shell_underwater);
    macro_object_constant(macro_box_1up_running_away);
    macro_object_constant(macro_empty_80);
    macro_object_constant(macro_bullet_bill_cannon);
    macro_object_constant(macro_heave_ho);
    macro_object_constant(macro_empty_83);
    macro_object_constant(macro_thwomp);
    macro_object_constant(macro_fire_spitter);
    macro_object_constant(macro_fire_fly_guy);
    macro_object_constant(macro_jumping_box);
    macro_object_constant(macro_butterfly_triplet);
    macro_object_constant(macro_butterfly_triplet_2);
    macro_object_constant(macro_empty_90);
    macro_object_constant(macro_empty_91);
    macro_object_constant(macro_empty_92);
    macro_object_constant(macro_bully);
    macro_object_constant(macro_bully_2);
    macro_object_constant(macro_empty_95);
    macro_object_constant(macro_unknown_96);
    macro_object_constant(macro_bouncing_fireball);
    macro_object_constant(macro_flamethrower);
    macro_object_constant(macro_empty_99);
    macro_object_constant(macro_empty_100);
    macro_object_constant(macro_empty_101);
    macro_object_constant(macro_empty_102);
    macro_object_constant(macro_empty_103);
    macro_object_constant(macro_empty_104);
    macro_object_constant(macro_empty_105);
    macro_object_constant(macro_wooden_post);
    macro_object_constant(macro_water_bomb_spawner);
    macro_object_constant(macro_enemy_lakitu);
    macro_object_constant(macro_bob_koopa_the_quick);
    macro_object_constant(macro_koopa_race_endpoint);
    macro_object_constant(macro_bobomb);
    macro_object_constant(macro_water_bomb_cannon_copy);
    macro_object_constant(macro_bobomb_buddy_opens_cannon_copy);
    macro_object_constant(macro_water_bomb_cannon);
    macro_object_constant(macro_bobomb_still);
    macro_object_constant(macro_empty_116);
    macro_object_constant(macro_empty_117);
    macro_object_constant(macro_empty_118);
    macro_object_constant(macro_empty_119);
    macro_object_constant(macro_empty_120);
    macro_object_constant(macro_empty_121);
    macro_object_constant(macro_empty_122);
    macro_object_constant(macro_unknown_123);
    macro_object_constant(macro_empty_124);
    macro_object_constant(macro_unagi);
    macro_object_constant(macro_sushi);
    macro_object_constant(macro_empty_127);
    macro_object_constant(macro_empty_128);
    macro_object_constant(macro_empty_129);
    macro_object_constant(macro_empty_130);
    macro_object_constant(macro_empty_131);
    macro_object_constant(macro_empty_132);
    macro_object_constant(macro_empty_133);
    macro_object_constant(macro_empty_134);
    macro_object_constant(macro_empty_135);
    macro_object_constant(macro_empty_136);
    macro_object_constant(macro_unknown_137);
    macro_object_constant(macro_tornado);
    macro_object_constant(macro_pokey);
    macro_object_constant(macro_pokey_copy);
    macro_object_constant(macro_tox_box);
    macro_object_constant(macro_empty_142);
    macro_object_constant(macro_empty_143);
    macro_object_constant(macro_empty_144);
    macro_object_constant(macro_empty_145);
    macro_object_constant(macro_empty_146);
    macro_object_constant(macro_empty_147);
    macro_object_constant(macro_empty_148);
    macro_object_constant(macro_empty_149);
    macro_object_constant(macro_empty_150);
    macro_object_constant(macro_monty_mole_2);
    macro_object_constant(macro_monty_mole);
    macro_object_constant(macro_monty_mole_hole);
    macro_object_constant(macro_fly_guy);
    macro_object_constant(macro_empty_155);
    macro_object_constant(macro_wiggler);
    macro_object_constant(macro_empty_157);
    macro_object_constant(macro_empty_158);
    macro_object_constant(macro_empty_159);
    macro_object_constant(macro_empty_160);
    macro_object_constant(macro_empty_161);
    macro_object_constant(macro_empty_162);
    macro_object_constant(macro_empty_163);
    macro_object_constant(macro_empty_164);
    macro_object_constant(macro_spindrift);
    macro_object_constant(macro_mr_blizzard);
    macro_object_constant(macro_mr_blizzard_copy);
    macro_object_constant(macro_empty_168);
    macro_object_constant(macro_small_penguin);
    macro_object_constant(macro_tuxies_mother);
    macro_object_constant(macro_tuxies_mother_copy);
    macro_object_constant(macro_mr_blizzard_2);
    macro_object_constant(macro_empty_173);
    macro_object_constant(macro_empty_174);
    macro_object_constant(macro_empty_175);
    macro_object_constant(macro_empty_176);
    macro_object_constant(macro_empty_177);
    macro_object_constant(macro_empty_178);
    macro_object_constant(macro_empty_179);
    macro_object_constant(macro_empty_180);
    macro_object_constant(macro_empty_181);
    macro_object_constant(macro_empty_182);
    macro_object_constant(macro_empty_183);
    macro_object_constant(macro_empty_184);
    macro_object_constant(macro_empty_185);
    macro_object_constant(macro_empty_186);
    macro_object_constant(macro_empty_187);
    macro_object_constant(macro_empty_188);
    macro_object_constant(macro_haunted_chair_copy);
    macro_object_constant(macro_haunted_chair);
    macro_object_constant(macro_haunted_chair_copy2);
    macro_object_constant(macro_boo);
    macro_object_constant(macro_boo_copy);
    macro_object_constant(macro_boo_group);
    macro_object_constant(macro_boo_with_cage);
    macro_object_constant(macro_beta_key);
    macro_object_constant(macro_empty_197);
    macro_object_constant(macro_empty_198);
    macro_object_constant(macro_empty_199);
    macro_object_constant(macro_empty_200);
    macro_object_constant(macro_empty_201);
    macro_object_constant(macro_empty_202);
    macro_object_constant(macro_empty_203);
    macro_object_constant(macro_empty_204);
    macro_object_constant(macro_empty_205);
    macro_object_constant(macro_empty_206);
    macro_object_constant(macro_empty_207);
    macro_object_constant(macro_empty_208);
    macro_object_constant(macro_empty_209);
    macro_object_constant(macro_empty_210);
    macro_object_constant(macro_empty_211);
    macro_object_constant(macro_empty_212);
    macro_object_constant(macro_empty_213);
    macro_object_constant(macro_empty_214);
    macro_object_constant(macro_empty_215);
    macro_object_constant(macro_empty_216);
    macro_object_constant(macro_empty_217);
    macro_object_constant(macro_empty_218);
    macro_object_constant(macro_empty_219);
    macro_object_constant(macro_empty_220);
    macro_object_constant(macro_empty_221);
    macro_object_constant(macro_empty_222);
    macro_object_constant(macro_empty_223);
    macro_object_constant(macro_empty_224);
    macro_object_constant(macro_empty_225);
    macro_object_constant(macro_empty_226);
    macro_object_constant(macro_empty_227);
    macro_object_constant(macro_empty_228);
    macro_object_constant(macro_empty_229);
    macro_object_constant(macro_empty_230);
    macro_object_constant(macro_empty_231);
    macro_object_constant(macro_empty_232);
    macro_object_constant(macro_empty_233);
    macro_object_constant(macro_chirp_chirp);
    macro_object_constant(macro_seaweed_bundle);
    macro_object_constant(macro_beta_chest);
    macro_object_constant(macro_water_mine);
    macro_object_constant(macro_fish_group_4);
    macro_object_constant(macro_fish_group_2);
    macro_object_constant(macro_jet_stream_ring_spawner);
    macro_object_constant(macro_jet_stream_ring_spawner_copy);
    macro_object_constant(macro_skeeter);
    macro_object_constant(macro_clam_shell);
    macro_object_constant(macro_empty_244);
    macro_object_constant(macro_empty_245);
    macro_object_constant(macro_empty_246);
    macro_object_constant(macro_empty_247);
    macro_object_constant(macro_empty_248);
    macro_object_constant(macro_empty_249);
    macro_object_constant(macro_empty_250);
    macro_object_constant(macro_ukiki);
    macro_object_constant(macro_ukiki_2);
    macro_object_constant(macro_piranha_plant);
    macro_object_constant(macro_empty_254);
    macro_object_constant(macro_whomp);
    macro_object_constant(macro_chain_chomp);
    macro_object_constant(macro_empty_257);
    macro_object_constant(macro_koopa);
    macro_object_constant(macro_koopa_shellless);
    macro_object_constant(macro_wooden_post_copy);
    macro_object_constant(macro_fire_piranha_plant);
    macro_object_constant(macro_fire_piranha_plant_2);
    macro_object_constant(macro_thi_koopa_the_quick);
    macro_object_constant(macro_empty_264);
    macro_object_constant(macro_empty_265);
    macro_object_constant(macro_empty_266);
    macro_object_constant(macro_empty_267);
    macro_object_constant(macro_empty_268);
    macro_object_constant(macro_empty_269);
    macro_object_constant(macro_empty_270);
    macro_object_constant(macro_empty_271);
    macro_object_constant(macro_empty_272);
    macro_object_constant(macro_empty_273);
    macro_object_constant(macro_empty_274);
    macro_object_constant(macro_empty_275);
    macro_object_constant(macro_empty_276);
    macro_object_constant(macro_empty_277);
    macro_object_constant(macro_empty_278);
    macro_object_constant(macro_empty_279);
    macro_object_constant(macro_empty_280);
    macro_object_constant(macro_moneybag);
    macro_object_constant(macro_empty_282);
    macro_object_constant(macro_empty_283);
    macro_object_constant(macro_empty_284);
    macro_object_constant(macro_empty_285);
    macro_object_constant(macro_empty_286);
    macro_object_constant(macro_empty_287);
    macro_object_constant(macro_empty_288);
    macro_object_constant(macro_swoop);
    macro_object_constant(macro_swoop_2);
    macro_object_constant(macro_mr_i);
    macro_object_constant(macro_scuttlebug_spawner);
    macro_object_constant(macro_scuttlebug);
    macro_object_constant(macro_empty_294);
    macro_object_constant(macro_empty_295);
    macro_object_constant(macro_empty_296);
    macro_object_constant(macro_empty_297);
    macro_object_constant(macro_empty_298);
    macro_object_constant(macro_empty_299);
    macro_object_constant(macro_empty_300);
    macro_object_constant(macro_empty_301);
    macro_object_constant(macro_empty_302);
    macro_object_constant(macro_unknown_303);
    macro_object_constant(macro_empty_304);
    macro_object_constant(macro_empty_305);
    macro_object_constant(macro_empty_306);
    macro_object_constant(macro_empty_307);
    macro_object_constant(macro_empty_308);
    macro_object_constant(macro_empty_309);
    macro_object_constant(macro_empty_310);
    macro_object_constant(macro_empty_311);
    macro_object_constant(macro_empty_312);
    macro_object_constant(macro_ttc_rotating_cube);
    macro_object_constant(macro_ttc_rotating_prism);
    macro_object_constant(macro_ttc_pendulum);
    macro_object_constant(macro_ttc_large_treadmill);
    macro_object_constant(macro_ttc_small_treadmill);
    macro_object_constant(macro_ttc_push_block);
    macro_object_constant(macro_ttc_rotating_hexagon);
    macro_object_constant(macro_ttc_rotating_triangle);
    macro_object_constant(macro_ttc_pit_block);
    macro_object_constant(macro_ttc_pit_block_2);
    macro_object_constant(macro_ttc_elevator_platform);
    macro_object_constant(macro_ttc_clock_hand);
    macro_object_constant(macro_ttc_spinner);
    macro_object_constant(macro_ttc_small_gear);
    macro_object_constant(macro_ttc_large_gear);
    macro_object_constant(macro_ttc_large_treadmill_2);
    macro_object_constant(macro_ttc_small_treadmill_2);
    macro_object_constant(macro_empty_330);
    macro_object_constant(macro_empty_331);
    macro_object_constant(macro_empty_332);
    macro_object_constant(macro_empty_333);
    macro_object_constant(macro_empty_334);
    macro_object_constant(macro_empty_335);
    macro_object_constant(macro_empty_336);
    macro_object_constant(macro_empty_337);
    macro_object_constant(macro_empty_338);
    macro_object_constant(macro_box_star_2);
    macro_object_constant(macro_box_star_3);
    macro_object_constant(macro_box_star_4);
    macro_object_constant(macro_box_star_5);
    macro_object_constant(macro_box_star_6);
    macro_object_constant(macro_empty_344);
    macro_object_constant(macro_empty_345);
    macro_object_constant(macro_empty_346);
    macro_object_constant(macro_empty_347);
    macro_object_constant(macro_empty_348);
    macro_object_constant(macro_empty_349);
    macro_object_constant(macro_bits_sliding_platform);
    macro_object_constant(macro_bits_twin_sliding_platforms);
    macro_object_constant(macro_bits_unknown_352);
    macro_object_constant(macro_bits_octagonal_platform);
    macro_object_constant(macro_bits_staircase);
    macro_object_constant(macro_empty_355);
    macro_object_constant(macro_empty_356);
    macro_object_constant(macro_bits_ferris_wheel_axle);
    macro_object_constant(macro_bits_arrow_platform);
    macro_object_constant(macro_bits_seesaw_platform);
    macro_object_constant(macro_bits_tilting_w_platform);
    macro_object_constant(macro_empty_361);
    macro_object_constant(macro_empty_362);
    macro_object_constant(macro_empty_363);
    macro_object_constant(macro_empty_364);
    macro_object_constant(macro_empty_365);

    // Other constants
    macro_object_constant(NULL);

    // Check level constants
    bool constantFound = false;
    s64 constantValue = DynOS_Lvl_ParseLevelScriptConstants(_Arg, &constantFound);
    if (constantFound) {
        return (LevelScript) constantValue;
    }

    // Unknown
    PrintDataError("  ERROR: Unknown macro object arg: %s", _Arg.begin());
    return 0;
}

#define macro_object_symbol_0(symb)              \
    if (_Symbol == #symb) {                      \
        MacroObject _Mo[] = { symb() };          \
        memcpy(aHead, _Mo, sizeof(_Mo));         \
        aHead += (sizeof(_Mo) / sizeof(_Mo[0])); \
        return;                                  \
    }

#define macro_object_symbol_5(symb)                                          \
    if (_Symbol == #symb) {                                                  \
        s64 _Arg0 = ParseMacroObjectSymbolArg(aGfxData, aNode, aTokenIndex); \
        s64 _Arg1 = ParseMacroObjectSymbolArg(aGfxData, aNode, aTokenIndex); \
        s64 _Arg2 = ParseMacroObjectSymbolArg(aGfxData, aNode, aTokenIndex); \
        s64 _Arg3 = ParseMacroObjectSymbolArg(aGfxData, aNode, aTokenIndex); \
        s64 _Arg4 = ParseMacroObjectSymbolArg(aGfxData, aNode, aTokenIndex); \
        MacroObject _Mo[] = { symb(_Arg0, _Arg1, _Arg2, _Arg3, _Arg4) };     \
        memcpy(aHead, _Mo, sizeof(_Mo));                                     \
        aHead += (sizeof(_Mo) / sizeof(_Mo[0]));                             \
        return;                                                              \
    }

#define macro_object_symbol_6(symb)                                             \
    if (_Symbol == #symb) {                                                     \
        s64 _Arg0 = ParseMacroObjectSymbolArg(aGfxData, aNode, aTokenIndex);    \
        s64 _Arg1 = ParseMacroObjectSymbolArg(aGfxData, aNode, aTokenIndex);    \
        s64 _Arg2 = ParseMacroObjectSymbolArg(aGfxData, aNode, aTokenIndex);    \
        s64 _Arg3 = ParseMacroObjectSymbolArg(aGfxData, aNode, aTokenIndex);    \
        s64 _Arg4 = ParseMacroObjectSymbolArg(aGfxData, aNode, aTokenIndex);    \
        s64 _Arg5 = ParseMacroObjectSymbolArg(aGfxData, aNode, aTokenIndex);    \
        MacroObject _Mo[] = { symb(_Arg0, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5) }; \
        memcpy(aHead, _Mo, sizeof(_Mo));                                        \
        aHead += (sizeof(_Mo) / sizeof(_Mo[0]));                                \
        return;                                                                 \
    }

static void ParseMacroObjectSymbol(GfxData* aGfxData, DataNode<MacroObject>* aNode, MacroObject*& aHead, u64& aTokenIndex, Array<u64>& aSwitchNodes) {
    const String& _Symbol = aNode->mTokens[aTokenIndex++];

    macro_object_symbol_5(MACRO_OBJECT);
    macro_object_symbol_6(MACRO_OBJECT_WITH_BEH_PARAM);
    macro_object_symbol_0(MACRO_OBJECT_END);

    // Unknown
    PrintDataError("  ERROR: Unknown macro object symbol: %s", _Symbol.begin());
}

DataNode<MacroObject>* DynOS_MacroObject_Parse(GfxData* aGfxData, DataNode<MacroObject>* aNode, bool aDisplayPercent) {
    if (aNode->mData) return aNode;

    // MacroObject data
    aNode->mData = New<MacroObject>(aNode->mTokens.Count() * MACRO_OBJECT_SIZE_PER_TOKEN);
    MacroObject* _Head = aNode->mData;
    Array<u64> _SwitchNodes;
    for (u64 _TokenIndex = 0; _TokenIndex < aNode->mTokens.Count();) { // Don't increment _TokenIndex here!
        ParseMacroObjectSymbol(aGfxData, aNode, _Head, _TokenIndex, _SwitchNodes);
        if (aDisplayPercent && aGfxData->mErrorCount == 0) { PrintNoNewLine("%3d%%\b\b\b\b", (s32) (_TokenIndex * 100) / aNode->mTokens.Count()); }
    }
    if (aDisplayPercent && aGfxData->mErrorCount == 0) { Print("100%%"); }
    aNode->mSize = (u32)(_Head - aNode->mData);
    aNode->mLoadIndex = aGfxData->mLoadIndex++;
    return aNode;
}

#pragma GCC diagnostic pop

  /////////////
 // Writing //
/////////////

void DynOS_MacroObject_Write(BinFile* aFile, GfxData* aGfxData, DataNode<MacroObject> *aNode) {
    if (!aNode->mData) return;

    // Name
    aFile->Write<u8>(DATA_TYPE_MACRO_OBJECT);
    aNode->mName.Write(aFile);

    // Data
    aFile->Write<u32>(aNode->mSize);
    for (u32 i = 0; i != aNode->mSize; ++i) {
        aFile->Write<MacroObject>(aNode->mData[i]);
    }
}

  /////////////
 // Reading //
/////////////

DataNode<MacroObject>* DynOS_MacroObject_Load(BinFile *aFile, GfxData *aGfxData) {
    DataNode<MacroObject> *_Node = New<DataNode<MacroObject>>();

    // Name
    _Node->mName.Read(aFile);

    // Data
    _Node->mSize = aFile->Read<u32>();
    _Node->mData = New<MacroObject>(_Node->mSize);
    for (u32 i = 0; i != _Node->mSize; ++i) {
        _Node->mData[i] = aFile->Read<MacroObject>();
    }

    // Add it
    if (aGfxData != NULL) {
        aGfxData->mMacroObjects.Add(_Node);
    }

    return _Node;
}
