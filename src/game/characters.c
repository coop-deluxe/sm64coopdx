#include "sm64.h"
#include "types.h"
#include "characters.h"
#include "player_palette.h"
#include "hud.h"
#include "model_ids.h"
#include "object_constants.h"
#include "sounds.h"
#include "luigi_sounds.h"
#include "wario_sounds.h"
#include "toad_sounds.h"
#include "pc/configfile.h"
#include "audio/external.h"
#include "engine/graph_node.h"
#include "pc/lua/smlua.h"
#include "pc/lua/utils/smlua_audio_utils.h"
#include "pc/lua/utils/smlua_anim_utils.h"
#include "pc/mods/mods.h"
#include "pc/mods/mods_utils.h"

extern Gfx mario_cap_seg3_dl_03022F48[];
extern Gfx mario_cap_m_logo_decal[];
extern Gfx luigi_cap_seg3_dl_03022F48[];
extern Gfx luigi_cap_l_logo_decal[];
extern Gfx toad_cap_mesh_layer_1[];
extern Gfx toad_cap_mesh_layer_5[];
extern Gfx waluigi_cap_seg3_dl_03022F48[];
extern Gfx waluigi_cap_r_logo_decal[];
extern Gfx wario_cap_seg3_dl_03022F48[];
extern Gfx wario_cap_w_logo_decal[];

extern ALIGNED8 const u8 texture_hud_char_mario_head[];
extern ALIGNED8 const u8 texture_hud_char_luigi_head[];
extern ALIGNED8 const u8 texture_hud_char_toad_head[];
extern ALIGNED8 const u8 texture_hud_char_waluigi_head[];
extern ALIGNED8 const u8 texture_hud_char_wario_head[];

struct Character gTemplateCharacter = {
    .type                  = CT_UNALLOCATED,
    .name                  = "",
    .hudHeadTexture        = { .texture = NULL, .width = 16, .height = 16, .format = G_IM_FMT_RGBA, .size = G_IM_SIZ_16b, .name = "" },
    .modelId               = E_MODEL_ERROR_MODEL,
    .capModelId            = E_MODEL_ERROR_MODEL,
    .capMetalModelId       = E_MODEL_ERROR_MODEL,
    .capWingModelId        = E_MODEL_ERROR_MODEL,
    .capMetalWingModelId   = E_MODEL_ERROR_MODEL,
    .capEnemyLayer         = LAYER_ALPHA,
    .capEnemyGfx           = "mario_cap_seg3_dl_03022F48",
    .capEnemyDecalGfx      = "mario_cap_m_logo_decal",
    .torsoRotMult          = 1.0f,
    // anim
    .animOffsetEnabled     = false,

    // sounds
    .soundFreqScale        = 1.0f,
    .soundYahWahHoo        = SOUND_MARIO_YAH_WAH_HOO,
    .soundHoohoo           = SOUND_MARIO_HOOHOO,
    .soundYahoo            = SOUND_MARIO_YAHOO,
    .soundUh               = SOUND_MARIO_UH,
    .soundHrmm             = SOUND_MARIO_HRMM,
    .soundWah2             = SOUND_MARIO_WAH2,
    .soundWhoa             = SOUND_MARIO_WHOA,
    .soundEeuh             = SOUND_MARIO_EEUH,
    .soundAttacked         = SOUND_MARIO_ATTACKED,
    .soundOoof             = SOUND_MARIO_OOOF,
    .soundOoof2            = SOUND_MARIO_OOOF2,
    .soundHereWeGo         = SOUND_MARIO_HERE_WE_GO,
    .soundYawning          = SOUND_MARIO_YAWNING,
    .soundSnoring1         = SOUND_MARIO_SNORING1,
    .soundSnoring2         = SOUND_MARIO_SNORING2,
    .soundWaaaooow         = SOUND_MARIO_WAAAOOOW,
    .soundHaha             = SOUND_MARIO_HAHA,
    .soundHaha_2           = SOUND_MARIO_HAHA_2,
    .soundUh2              = SOUND_MARIO_UH2,
    .soundUh2_2            = SOUND_MARIO_UH2_2,
    .soundOnFire           = SOUND_MARIO_ON_FIRE,
    .soundDying            = SOUND_MARIO_DYING,
    .soundPantingCold      = SOUND_MARIO_PANTING_COLD,
    .soundPanting          = SOUND_MARIO_PANTING,
    .soundCoughing1        = SOUND_MARIO_COUGHING1,
    .soundCoughing2        = SOUND_MARIO_COUGHING2,
    .soundCoughing3        = SOUND_MARIO_COUGHING3,
    .soundPunchYah         = SOUND_MARIO_PUNCH_YAH,
    .soundPunchHoo         = SOUND_MARIO_PUNCH_HOO,
    .soundMamaMia          = SOUND_MARIO_MAMA_MIA,
    .soundGroundPoundWah   = SOUND_MARIO_GROUND_POUND_WAH,
    .soundDrowning         = SOUND_MARIO_DROWNING,
    .soundPunchWah         = SOUND_MARIO_PUNCH_WAH,
    .soundYahooWahaYippee  = SOUND_MARIO_YAHOO_WAHA_YIPPEE,
    .soundDoh              = SOUND_MARIO_DOH,
    .soundGameOver         = SOUND_MARIO_GAME_OVER,
    .soundHello            = SOUND_MARIO_HELLO,
    .soundPressStartToPlay = SOUND_MARIO_PRESS_START_TO_PLAY,
    .soundTwirlBounce      = SOUND_MARIO_TWIRL_BOUNCE,
    .soundSnoring3         = SOUND_MARIO_SNORING3,
    .soundSoLongaBowser    = SOUND_MARIO_SO_LONGA_BOWSER,
    .soundImaTired         = SOUND_MARIO_IMA_TIRED,
    .soundLetsAGo          = SOUND_MARIO_LETS_A_GO,
    .soundOkeyDokey        = SOUND_MARIO_OKEY_DOKEY,
};
struct Character gOriginalCharacters[CT_MAX] = {
    [CT_MARIO] = {
        .type                  = CT_MARIO,
        .name                  = "Mario",
        .hudHeadTexture        = { .texture = texture_hud_char_mario_head, .width = 16, .height = 16, .format = G_IM_FMT_RGBA, .size = G_IM_SIZ_16b, .name = "texture_hud_char_mario_head" },
        .modelId               = E_MODEL_MARIO,
        .capModelId            = E_MODEL_MARIOS_CAP,
        .capMetalModelId       = E_MODEL_MARIOS_METAL_CAP,
        .capWingModelId        = E_MODEL_MARIOS_WING_CAP,
        .capMetalWingModelId   = E_MODEL_MARIOS_WINGED_METAL_CAP,
        .capEnemyLayer         = LAYER_ALPHA,
        .capEnemyGfx           = "mario_cap_seg3_dl_03022F48",
        .capEnemyDecalGfx      = "mario_cap_m_logo_decal",
        .torsoRotMult          = 1.0f,
        // anim
        .animOffsetEnabled     = false,

        // sounds
        .soundFreqScale        = 1.0f,
        .soundYahWahHoo        = SOUND_MARIO_YAH_WAH_HOO,
        .soundHoohoo           = SOUND_MARIO_HOOHOO,
        .soundYahoo            = SOUND_MARIO_YAHOO,
        .soundUh               = SOUND_MARIO_UH,
        .soundHrmm             = SOUND_MARIO_HRMM,
        .soundWah2             = SOUND_MARIO_WAH2,
        .soundWhoa             = SOUND_MARIO_WHOA,
        .soundEeuh             = SOUND_MARIO_EEUH,
        .soundAttacked         = SOUND_MARIO_ATTACKED,
        .soundOoof             = SOUND_MARIO_OOOF,
        .soundOoof2            = SOUND_MARIO_OOOF2,
        .soundHereWeGo         = SOUND_MARIO_HERE_WE_GO,
        .soundYawning          = SOUND_MARIO_YAWNING,
        .soundSnoring1         = SOUND_MARIO_SNORING1,
        .soundSnoring2         = SOUND_MARIO_SNORING2,
        .soundWaaaooow         = SOUND_MARIO_WAAAOOOW,
        .soundHaha             = SOUND_MARIO_HAHA,
        .soundHaha_2           = SOUND_MARIO_HAHA_2,
        .soundUh2              = SOUND_MARIO_UH2,
        .soundUh2_2            = SOUND_MARIO_UH2_2,
        .soundOnFire           = SOUND_MARIO_ON_FIRE,
        .soundDying            = SOUND_MARIO_DYING,
        .soundPantingCold      = SOUND_MARIO_PANTING_COLD,
        .soundPanting          = SOUND_MARIO_PANTING,
        .soundCoughing1        = SOUND_MARIO_COUGHING1,
        .soundCoughing2        = SOUND_MARIO_COUGHING2,
        .soundCoughing3        = SOUND_MARIO_COUGHING3,
        .soundPunchYah         = SOUND_MARIO_PUNCH_YAH,
        .soundPunchHoo         = SOUND_MARIO_PUNCH_HOO,
        .soundMamaMia          = SOUND_MARIO_MAMA_MIA,
        .soundGroundPoundWah   = SOUND_MARIO_GROUND_POUND_WAH,
        .soundDrowning         = SOUND_MARIO_DROWNING,
        .soundPunchWah         = SOUND_MARIO_PUNCH_WAH,
        .soundYahooWahaYippee  = SOUND_MARIO_YAHOO_WAHA_YIPPEE,
        .soundDoh              = SOUND_MARIO_DOH,
        .soundGameOver         = SOUND_MARIO_GAME_OVER,
        .soundHello            = SOUND_MARIO_HELLO,
        .soundPressStartToPlay = SOUND_MARIO_PRESS_START_TO_PLAY,
        .soundTwirlBounce      = SOUND_MARIO_TWIRL_BOUNCE,
        .soundSnoring3         = SOUND_MARIO_SNORING3,
        .soundSoLongaBowser    = SOUND_MARIO_SO_LONGA_BOWSER,
        .soundImaTired         = SOUND_MARIO_IMA_TIRED,
        .soundLetsAGo          = SOUND_MARIO_LETS_A_GO,
        .soundOkeyDokey        = SOUND_MARIO_OKEY_DOKEY,
    },

    [CT_LUIGI] = {
        .type                  = CT_LUIGI,
        .name                  = "Luigi",
        .hudHeadTexture        = { .texture = texture_hud_char_luigi_head, .width = 16, .height = 16, .format = G_IM_FMT_RGBA, .size = G_IM_SIZ_16b, .name = "texture_hud_char_luigi_head" },
        .modelId               = E_MODEL_LUIGI,
        .capModelId            = E_MODEL_LUIGIS_CAP,
        .capMetalModelId       = E_MODEL_LUIGIS_METAL_CAP,
        .capWingModelId        = E_MODEL_LUIGIS_WING_CAP,
        .capMetalWingModelId   = E_MODEL_LUIGIS_WINGED_METAL_CAP,
        .capEnemyLayer         = LAYER_ALPHA,
        .capEnemyGfx           = "luigi_cap_seg3_dl_03022F48",
        .capEnemyDecalGfx      = "luigi_cap_l_logo_decal",
        .torsoRotMult          = 1.0f,
        // anim
        .animOffsetEnabled     = false,

        // sounds
        .soundFreqScale        = 1.0f,
        .soundYahWahHoo        = SOUND_LUIGI_YAH_WAH_HOO,
        .soundHoohoo           = SOUND_LUIGI_HOOHOO,
        .soundYahoo            = SOUND_LUIGI_YAHOO,
        .soundUh               = SOUND_LUIGI_UH,
        .soundHrmm             = SOUND_LUIGI_HRMM,
        .soundWah2             = SOUND_LUIGI_WAH2,
        .soundWhoa             = SOUND_LUIGI_WHOA,
        .soundEeuh             = SOUND_LUIGI_EEUH,
        .soundAttacked         = SOUND_LUIGI_ATTACKED,
        .soundOoof             = SOUND_LUIGI_OOOF,
        .soundOoof2            = SOUND_LUIGI_OOOF2,
        .soundHereWeGo         = SOUND_LUIGI_HERE_WE_GO,
        .soundYawning          = SOUND_LUIGI_YAWNING,
        .soundSnoring1         = SOUND_LUIGI_SNORING1,
        .soundSnoring2         = SOUND_LUIGI_SNORING2,
        .soundWaaaooow         = SOUND_LUIGI_WAAAOOOW,
        .soundHaha             = SOUND_LUIGI_HAHA,
        .soundHaha_2           = SOUND_LUIGI_HAHA_2,
        .soundUh2              = SOUND_LUIGI_UH2,
        .soundUh2_2            = SOUND_LUIGI_UH2_2,
        .soundOnFire           = SOUND_LUIGI_ON_FIRE,
        .soundDying            = SOUND_LUIGI_DYING,
        .soundPantingCold      = SOUND_LUIGI_PANTING_COLD,
        .soundPanting          = SOUND_LUIGI_PANTING,
        .soundCoughing1        = SOUND_LUIGI_COUGHING1,
        .soundCoughing2        = SOUND_LUIGI_COUGHING2,
        .soundCoughing3        = SOUND_LUIGI_COUGHING3,
        .soundPunchYah         = SOUND_LUIGI_PUNCH_YAH,
        .soundPunchHoo         = SOUND_LUIGI_PUNCH_HOO,
        .soundMamaMia          = SOUND_LUIGI_MAMA_MIA,
        .soundGroundPoundWah   = SOUND_LUIGI_GROUND_POUND_WAH,
        .soundDrowning         = SOUND_LUIGI_DROWNING,
        .soundPunchWah         = SOUND_LUIGI_PUNCH_WAH,
        .soundYahooWahaYippee  = SOUND_LUIGI_YAHOO_WAHA_YIPPEE,
        .soundDoh              = SOUND_LUIGI_DOH,
        .soundGameOver         = SOUND_LUIGI_GAME_OVER,
        .soundHello            = SOUND_LUIGI_HELLO,
        .soundPressStartToPlay = SOUND_LUIGI_PRESS_START_TO_PLAY,
        .soundTwirlBounce      = SOUND_LUIGI_TWIRL_BOUNCE,
        .soundSnoring3         = SOUND_LUIGI_SNORING3,
        .soundSoLongaBowser    = SOUND_LUIGI_SO_LONGA_BOWSER,
        .soundImaTired         = SOUND_LUIGI_IMA_TIRED,
        .soundLetsAGo          = SOUND_LUIGI_LETS_A_GO,
        .soundOkeyDokey        = SOUND_LUIGI_OKEY_DOKEY,
    },

    [CT_TOAD] = {
        .type                  = CT_TOAD,
        .name                  = "Toad",
        .hudHeadTexture        = { .texture = texture_hud_char_toad_head, .width = 16, .height = 16, .format = G_IM_FMT_RGBA, .size = G_IM_SIZ_16b, .name = "texture_hud_char_toad_head" },
        .modelId               = E_MODEL_TOAD_PLAYER,
        .capModelId            = E_MODEL_TOADS_CAP,
        .capMetalModelId       = E_MODEL_TOADS_METAL_CAP,
        .capWingModelId        = E_MODEL_TOADS_WING_CAP,
        .capMetalWingModelId   = E_MODEL_TOADS_WINGED_METAL_CAP,
        .capEnemyLayer         = LAYER_ALPHA,
        .capEnemyGfx           = "toad_cap_mesh_layer_1",
        .capEnemyDecalGfx      = "toad_cap_mesh_layer_5",
        .torsoRotMult          = 1.0f,
        // anim
        .animOffsetEnabled     = false,

        // sounds
        .soundFreqScale        = 1.0f,
        .soundYahWahHoo        = SOUND_TOAD_YAH_WAH_HOO,
        .soundHoohoo           = SOUND_TOAD_HOOHOO,
        .soundYahoo            = SOUND_TOAD_YAHOO,
        .soundUh               = SOUND_TOAD_UH,
        .soundHrmm             = SOUND_TOAD_HRMM,
        .soundWah2             = SOUND_TOAD_WAH2,
        .soundWhoa             = SOUND_TOAD_WHOA,
        .soundEeuh             = SOUND_TOAD_EEUH,
        .soundAttacked         = SOUND_TOAD_ATTACKED,
        .soundOoof             = SOUND_TOAD_OOOF,
        .soundOoof2            = SOUND_TOAD_OOOF2,
        .soundHereWeGo         = SOUND_TOAD_HERE_WE_GO,
        .soundYawning          = SOUND_TOAD_YAWNING,
        .soundSnoring1         = SOUND_TOAD_SNORING1,
        .soundSnoring2         = SOUND_TOAD_SNORING2,
        .soundWaaaooow         = SOUND_TOAD_WAAAOOOW,
        .soundHaha             = SOUND_TOAD_HAHA,
        .soundHaha_2           = SOUND_TOAD_HAHA_2,
        .soundUh2              = SOUND_TOAD_UH2,
        .soundUh2_2            = SOUND_TOAD_UH2_2,
        .soundOnFire           = SOUND_TOAD_ON_FIRE,
        .soundDying            = SOUND_TOAD_DYING,
        .soundPantingCold      = SOUND_TOAD_PANTING_COLD,
        .soundPanting          = SOUND_TOAD_PANTING,
        .soundCoughing1        = SOUND_TOAD_COUGHING1,
        .soundCoughing2        = SOUND_TOAD_COUGHING2,
        .soundCoughing3        = SOUND_TOAD_COUGHING3,
        .soundPunchYah         = SOUND_TOAD_PUNCH_YAH,
        .soundPunchHoo         = SOUND_TOAD_PUNCH_HOO,
        .soundMamaMia          = SOUND_TOAD_MAMA_MIA,
        .soundGroundPoundWah   = SOUND_TOAD_GROUND_POUND_WAH,
        .soundDrowning         = SOUND_TOAD_DROWNING,
        .soundPunchWah         = SOUND_TOAD_PUNCH_WAH,
        .soundYahooWahaYippee  = SOUND_TOAD_YAHOO_WAHA_YIPPEE,
        .soundDoh              = SOUND_TOAD_DOH,
        .soundGameOver         = SOUND_TOAD_GAME_OVER,
        .soundHello            = SOUND_TOAD_HELLO,
        .soundPressStartToPlay = SOUND_TOAD_PRESS_START_TO_PLAY,
        .soundTwirlBounce      = SOUND_TOAD_TWIRL_BOUNCE,
        .soundSnoring3         = SOUND_TOAD_SNORING3,
        .soundSoLongaBowser    = SOUND_TOAD_SO_LONGA_BOWSER,
        .soundImaTired         = SOUND_TOAD_IMA_TIRED,
        .soundLetsAGo          = SOUND_TOAD_LETS_A_GO,
        .soundOkeyDokey        = SOUND_TOAD_OKEY_DOKEY,
    },

    [CT_WALUIGI] = {
        .type                  = CT_WALUIGI,
        .name                  = "Waluigi",
        .hudHeadTexture        = { .texture = texture_hud_char_waluigi_head, .width = 16, .height = 16, .format = G_IM_FMT_RGBA, .size = G_IM_SIZ_16b, .name = "texture_hud_char_waluigi_head" },
        .modelId               = E_MODEL_WALUIGI,
        .capModelId            = E_MODEL_WALUIGIS_CAP,
        .capMetalModelId       = E_MODEL_WALUIGIS_METAL_CAP,
        .capWingModelId        = E_MODEL_WALUIGIS_WING_CAP,
        .capMetalWingModelId   = E_MODEL_WALUIGIS_WINGED_METAL_CAP,
        .capEnemyLayer         = LAYER_ALPHA,
        .capEnemyGfx           = "waluigi_cap_seg3_dl_03022F48",
        .capEnemyDecalGfx      = "waluigi_cap_r_logo_decal",
        .torsoRotMult          = 1.0f,
        // anim
        .animOffsetEnabled     = false,

        // sounds
        .soundFreqScale        = 0.99f,
        .soundYahWahHoo        = SOUND_LUIGI_YAH_WAH_HOO,
        .soundHoohoo           = SOUND_LUIGI_HOOHOO,
        .soundYahoo            = SOUND_LUIGI_YAHOO,
        .soundUh               = SOUND_LUIGI_UH,
        .soundHrmm             = SOUND_LUIGI_HRMM,
        .soundWah2             = SOUND_LUIGI_WAH2,
        .soundWhoa             = SOUND_LUIGI_WHOA,
        .soundEeuh             = SOUND_LUIGI_EEUH,
        .soundAttacked         = SOUND_LUIGI_ATTACKED,
        .soundOoof             = SOUND_LUIGI_OOOF,
        .soundOoof2            = SOUND_LUIGI_OOOF2,
        .soundHereWeGo         = SOUND_LUIGI_HERE_WE_GO,
        .soundYawning          = SOUND_LUIGI_YAWNING,
        .soundSnoring1         = SOUND_LUIGI_SNORING1,
        .soundSnoring2         = SOUND_LUIGI_SNORING2,
        .soundWaaaooow         = SOUND_LUIGI_WAAAOOOW,
        .soundHaha             = SOUND_LUIGI_HAHA,
        .soundHaha_2           = SOUND_LUIGI_HAHA_2,
        .soundUh2              = SOUND_LUIGI_UH2,
        .soundUh2_2            = SOUND_LUIGI_UH2_2,
        .soundOnFire           = SOUND_LUIGI_ON_FIRE,
        .soundDying            = SOUND_LUIGI_DYING,
        .soundPantingCold      = SOUND_LUIGI_PANTING_COLD,
        .soundPanting          = SOUND_LUIGI_PANTING,
        .soundCoughing1        = SOUND_LUIGI_COUGHING1,
        .soundCoughing2        = SOUND_LUIGI_COUGHING2,
        .soundCoughing3        = SOUND_LUIGI_COUGHING3,
        .soundPunchYah         = SOUND_LUIGI_PUNCH_YAH,
        .soundPunchHoo         = SOUND_LUIGI_PUNCH_HOO,
        .soundMamaMia          = SOUND_LUIGI_MAMA_MIA,
        .soundGroundPoundWah   = SOUND_LUIGI_GROUND_POUND_WAH,
        .soundDrowning         = SOUND_LUIGI_DROWNING,
        .soundPunchWah         = SOUND_LUIGI_PUNCH_WAH,
        .soundYahooWahaYippee  = SOUND_LUIGI_YAHOO_WAHA_YIPPEE,
        .soundDoh              = SOUND_LUIGI_DOH,
        .soundGameOver         = SOUND_LUIGI_GAME_OVER,
        .soundHello            = SOUND_LUIGI_HELLO,
        .soundPressStartToPlay = SOUND_LUIGI_PRESS_START_TO_PLAY,
        .soundTwirlBounce      = SOUND_LUIGI_TWIRL_BOUNCE,
        .soundSnoring3         = SOUND_LUIGI_SNORING3,
        .soundSoLongaBowser    = SOUND_LUIGI_SO_LONGA_BOWSER,
        .soundImaTired         = SOUND_LUIGI_IMA_TIRED,
        .soundLetsAGo          = SOUND_LUIGI_LETS_A_GO,
        .soundOkeyDokey        = SOUND_LUIGI_OKEY_DOKEY,
    },

    [CT_WARIO] = {
        .type                  = CT_WARIO,
        .name                  = "Wario",
        .hudHeadTexture        = { .texture = texture_hud_char_wario_head, .width = 16, .height = 16, .format = G_IM_FMT_RGBA, .size = G_IM_SIZ_16b, .name = "texture_hud_char_wario_head" },
        .modelId               = E_MODEL_WARIO,
        .capModelId            = E_MODEL_WARIOS_CAP,
        .capMetalModelId       = E_MODEL_WARIOS_METAL_CAP,
        .capWingModelId        = E_MODEL_WARIOS_WING_CAP,
        .capMetalWingModelId   = E_MODEL_WARIOS_WINGED_METAL_CAP,
        .capEnemyLayer         = LAYER_ALPHA,
        .capEnemyGfx           = "wario_cap_seg3_dl_03022F48",
        .capEnemyDecalGfx      = "wario_cap_w_logo_decal",
        .torsoRotMult          = 1.0f,
        // anim
        .animOffsetEnabled     = false,

        // sounds
        .soundFreqScale        = 1.0f,
        .soundYahWahHoo        = SOUND_WARIO_YAH_WAH_HOO,
        .soundHoohoo           = SOUND_WARIO_HOOHOO,
        .soundYahoo            = SOUND_WARIO_YAHOO,
        .soundUh               = SOUND_WARIO_UH,
        .soundHrmm             = SOUND_WARIO_HRMM,
        .soundWah2             = SOUND_WARIO_WAH2,
        .soundWhoa             = SOUND_WARIO_WHOA,
        .soundEeuh             = SOUND_WARIO_EEUH,
        .soundAttacked         = SOUND_WARIO_ATTACKED,
        .soundOoof             = SOUND_WARIO_OOOF,
        .soundOoof2            = SOUND_WARIO_OOOF2,
        .soundHereWeGo         = SOUND_WARIO_HERE_WE_GO,
        .soundYawning          = SOUND_WARIO_YAWNING,
        .soundSnoring1         = SOUND_WARIO_SNORING1,
        .soundSnoring2         = SOUND_WARIO_SNORING2,
        .soundWaaaooow         = SOUND_WARIO_WAAAOOOW,
        .soundHaha             = SOUND_WARIO_HAHA,
        .soundHaha_2           = SOUND_WARIO_HAHA_2,
        .soundUh2              = SOUND_WARIO_UH2,
        .soundUh2_2            = SOUND_WARIO_UH2_2,
        .soundOnFire           = SOUND_WARIO_ON_FIRE,
        .soundDying            = SOUND_WARIO_DYING,
        .soundPantingCold      = SOUND_WARIO_PANTING_COLD,
        .soundPanting          = SOUND_WARIO_PANTING,
        .soundCoughing1        = SOUND_WARIO_COUGHING1,
        .soundCoughing2        = SOUND_WARIO_COUGHING2,
        .soundCoughing3        = SOUND_WARIO_COUGHING3,
        .soundPunchYah         = SOUND_WARIO_PUNCH_YAH,
        .soundPunchHoo         = SOUND_WARIO_PUNCH_HOO,
        .soundMamaMia          = SOUND_WARIO_MAMA_MIA,
        .soundGroundPoundWah   = SOUND_WARIO_GROUND_POUND_WAH,
        .soundDrowning         = SOUND_WARIO_DROWNING,
        .soundPunchWah         = SOUND_WARIO_PUNCH_WAH,
        .soundYahooWahaYippee  = SOUND_WARIO_YAHOO_WAHA_YIPPEE,
        .soundDoh              = SOUND_WARIO_DOH,
        .soundGameOver         = SOUND_WARIO_GAME_OVER,
        .soundHello            = SOUND_WARIO_HELLO,
        .soundPressStartToPlay = SOUND_WARIO_PRESS_START_TO_PLAY,
        .soundTwirlBounce      = SOUND_WARIO_TWIRL_BOUNCE,
        .soundSnoring3         = SOUND_WARIO_SNORING3,
        .soundSoLongaBowser    = SOUND_WARIO_SO_LONGA_BOWSER,
        .soundImaTired         = SOUND_WARIO_IMA_TIRED,
        .soundLetsAGo          = SOUND_WARIO_LETS_A_GO,
        .soundOkeyDokey        = SOUND_WARIO_OKEY_DOKEY,
    },
};
struct Character gCharacters[MAX_CHARACTERS] = { 0 };

enum AnimType {
    ANIM_TYPE_NONE,
    ANIM_TYPE_LOWY,
    ANIM_TYPE_FEET,
    ANIM_TYPE_HAND,
};

#define ANIM_TYPE_MAX 211
u8 sAnimTypes[ANIM_TYPE_MAX] = {
    ANIM_TYPE_HAND, ANIM_TYPE_LOWY, ANIM_TYPE_NONE, ANIM_TYPE_NONE, ANIM_TYPE_NONE,
    ANIM_TYPE_NONE, ANIM_TYPE_NONE, ANIM_TYPE_NONE, ANIM_TYPE_NONE, ANIM_TYPE_NONE,
    ANIM_TYPE_NONE, ANIM_TYPE_NONE, ANIM_TYPE_NONE, ANIM_TYPE_NONE, ANIM_TYPE_NONE,
    ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_FEET,
    ANIM_TYPE_LOWY, ANIM_TYPE_NONE, ANIM_TYPE_FEET, ANIM_TYPE_FEET, ANIM_TYPE_FEET,
    ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_NONE, ANIM_TYPE_LOWY,
    ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY,
    ANIM_TYPE_FEET, ANIM_TYPE_FEET, ANIM_TYPE_FEET, ANIM_TYPE_NONE, ANIM_TYPE_LOWY,
    ANIM_TYPE_NONE, ANIM_TYPE_NONE, ANIM_TYPE_NONE, ANIM_TYPE_HAND, ANIM_TYPE_LOWY,
    ANIM_TYPE_NONE, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY,
    ANIM_TYPE_LOWY, ANIM_TYPE_HAND, ANIM_TYPE_FEET, ANIM_TYPE_HAND, ANIM_TYPE_LOWY,
    ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_FEET, ANIM_TYPE_NONE, ANIM_TYPE_NONE,
    ANIM_TYPE_NONE, ANIM_TYPE_NONE, ANIM_TYPE_NONE, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY,
    ANIM_TYPE_NONE, ANIM_TYPE_LOWY, ANIM_TYPE_NONE, ANIM_TYPE_NONE, ANIM_TYPE_NONE,
    ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_FEET, ANIM_TYPE_NONE, ANIM_TYPE_LOWY,
    ANIM_TYPE_LOWY, ANIM_TYPE_NONE, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_FEET,
    ANIM_TYPE_NONE, ANIM_TYPE_NONE, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY,
    ANIM_TYPE_FEET, ANIM_TYPE_NONE, ANIM_TYPE_LOWY, ANIM_TYPE_NONE, ANIM_TYPE_LOWY,
    ANIM_TYPE_LOWY, ANIM_TYPE_NONE, ANIM_TYPE_HAND, ANIM_TYPE_HAND, ANIM_TYPE_LOWY,
    ANIM_TYPE_FEET, ANIM_TYPE_FEET, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY,
    ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY,
    ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY,
    ANIM_TYPE_LOWY, ANIM_TYPE_NONE, ANIM_TYPE_NONE, ANIM_TYPE_LOWY, ANIM_TYPE_FEET,
    ANIM_TYPE_FEET, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_NONE, ANIM_TYPE_NONE,
    ANIM_TYPE_NONE, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY,
    ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY,
    ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_NONE, ANIM_TYPE_NONE,
    ANIM_TYPE_NONE, ANIM_TYPE_NONE, ANIM_TYPE_NONE, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY,
    ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_NONE, ANIM_TYPE_LOWY, ANIM_TYPE_NONE,
    ANIM_TYPE_NONE, ANIM_TYPE_FEET, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY,
    ANIM_TYPE_LOWY, ANIM_TYPE_FEET, ANIM_TYPE_LOWY, ANIM_TYPE_NONE, ANIM_TYPE_LOWY,
    ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_NONE, ANIM_TYPE_NONE,
    ANIM_TYPE_NONE, ANIM_TYPE_NONE, ANIM_TYPE_NONE, ANIM_TYPE_NONE, ANIM_TYPE_NONE,
    ANIM_TYPE_NONE, ANIM_TYPE_NONE, ANIM_TYPE_NONE, ANIM_TYPE_NONE, ANIM_TYPE_NONE,
    ANIM_TYPE_NONE, ANIM_TYPE_NONE, ANIM_TYPE_NONE, ANIM_TYPE_NONE, ANIM_TYPE_NONE,
    ANIM_TYPE_NONE, ANIM_TYPE_NONE, ANIM_TYPE_NONE, ANIM_TYPE_NONE, ANIM_TYPE_NONE,
    ANIM_TYPE_NONE, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY,
    ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY,
    ANIM_TYPE_LOWY, ANIM_TYPE_NONE, ANIM_TYPE_LOWY, ANIM_TYPE_NONE, ANIM_TYPE_LOWY,
    ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_HAND, ANIM_TYPE_HAND,
    ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_FEET, ANIM_TYPE_LOWY, ANIM_TYPE_LOWY,
    ANIM_TYPE_LOWY, ANIM_TYPE_LOWY, ANIM_TYPE_NONE, ANIM_TYPE_NONE, ANIM_TYPE_FEET,
    ANIM_TYPE_FEET,
};

int character_get_first_allocated_index() {
    for (int i = 0; i < MAX_CHARACTERS; i++) {
        if (gCharacters[i].type != CT_UNALLOCATED) {
            return i;
        }
    }
    return 0;
}

int character_get_first_unallocated_index() {
    for (int i = 0; i < MAX_CHARACTERS; i++) {
        if (gCharacters[i].type == CT_UNALLOCATED) {
            return i;
        }
    }
    return 0;
}

struct Character* character_get_first_allocated() {
    return &gCharacters[character_get_first_allocated_index()];
}

struct Character* character_get_first_unallocated() {
    return &gCharacters[character_get_first_unallocated_index()];
}

struct Character* get_allocated_character_from_index(int i) {
    if (i < 0 || i >= MAX_CHARACTERS) { return  &gCharacters[CT_MARIO]; }
    return (gCharacters[i].type == CT_UNALLOCATED) ? &gCharacters[CT_MARIO] : &gCharacters[i];
}

struct Character* get_character(struct MarioState* m) {
    return (m == NULL || m->character == NULL || m->character->type == CT_UNALLOCATED)
        ? &gCharacters[CT_MARIO]
        : m->character;
}

static s32 get_character_sound(struct MarioState* m, enum CharacterSound characterSound) {
    if (m == NULL || m->marioObj == NULL) { return 0; }

    s32 soundOverride = 0;
    if (smlua_call_event_hooks(HOOK_CHARACTER_SOUND, m, characterSound, &soundOverride)) {
        return soundOverride;
    }

    struct Character* character = get_character(m);

    if (characterSound < 0 || characterSound >= CHAR_SOUND_MAX) { return 0; }
    return character->sounds[characterSound];
}

static struct ModAudio* get_mod_audio_character_sound(struct MarioState* m, enum CharacterSound characterSound) {
    struct Character* character = get_character(m);

    int indices[MAX_CHARACTER_AUDIOS_PER_SOUND];
    int curIndex = 0;
    for (int i = 0; i < MAX_CHARACTER_AUDIOS_PER_SOUND; i++) {
        if (character->modAudioSounds[characterSound][i] >= 0) {
            indices[curIndex++] = i;
        }
    }
    int selectedAudioIndex = curIndex ? indices[rand() % curIndex] : -1;
    if (selectedAudioIndex == -1) { return NULL; }
    int modFileIndex = character->modAudioSounds[characterSound][selectedAudioIndex];
    int modIndex = character->modIndexForAudio[characterSound][selectedAudioIndex];
    if (modIndex < 0 || modIndex > gActiveMods.entryCount) {
        LOG_ERROR("get_mod_audio_character_sound: Could not find sound file, mod index is invalid. It is %d", modIndex);
        return NULL;
    }
    struct Mod* mod = gActiveMods.entries[modIndex];
    if (!mod) {
        LOG_ERROR("get_mod_audio_character_sound: Could not find sound file, mod is null");
    }

    return audio_sample_load_from_mod(mod, mod->files[modFileIndex].relativePath);
}

static void play_character_sound_internal(struct MarioState *m, enum CharacterSound characterSound, u32 offset, u32 flags) {
    if (m != NULL && (m->flags & flags) == 0) {
        struct Character* character = get_character(m);
        struct ModAudio* modAudio = get_mod_audio_character_sound(m, characterSound);
        s32 sound = get_character_sound(m, characterSound);
        if (modAudio) {
            audio_sample_play(modAudio, m->pos, 1);
        } else if (sound != 0) {
            f32 *pos = (m->marioObj != NULL ? m->marioObj->header.gfx.cameraToObject : gGlobalSoundSource);
            play_sound_with_freq_scale(sound + offset, pos, character->soundFreqScale);
        }
        m->flags |= flags;
    }
}

void play_character_sound(struct MarioState* m, enum CharacterSound characterSound) {
    play_character_sound_internal(m, characterSound, 0, 0);
}

void play_character_sound_offset(struct MarioState* m, enum CharacterSound characterSound, u32 offset) {
    play_character_sound_internal(m, characterSound, offset, 0);
}

void play_character_sound_if_no_flag(struct MarioState* m, enum CharacterSound characterSound, u32 flags) {
    play_character_sound_internal(m, characterSound, 0, flags);
}

f32 get_character_anim_offset(struct MarioState* m) {
    if (m == NULL || m->marioObj == NULL) { return 0; }
    struct Object* marioObj = m->marioObj;
    if (!marioObj) { return 0; }
    struct Character* c = get_character(m);
    if (!c || !c->animOffsetEnabled) { return 0; }
    s32 animID = marioObj->header.gfx.animInfo.animID;
    if (animID < 0 || animID >= ANIM_TYPE_MAX) { return 0; }

    switch (sAnimTypes[animID]) {
        case ANIM_TYPE_LOWY:
            if (m->minimumBoneY < c->animOffsetLowYPoint) {
                return c->animOffsetLowYPoint - m->minimumBoneY;
            }
            break;
        case ANIM_TYPE_FEET:
            return c->animOffsetFeet;
            break;
        case ANIM_TYPE_HAND:
            return c->animOffsetHand;
            break;
    }
    return 0;
}

void update_character_anim_offset(struct MarioState* m) {
    if (m == NULL || m->marioObj == NULL) { return; }
    struct Object* marioObj = m->marioObj;
    if (!marioObj) { return; }
    struct Character* c = get_character(m);
    if (!c || !c->animOffsetEnabled) { return; }

    f32 targetOffset = get_character_anim_offset(m);

    // smooth
    f32 alpha = (fabs(targetOffset - m->curAnimOffset) / 80.0f) + 0.5f;
    alpha = (alpha + 0.5f) / 2.0f;
    alpha *= alpha;
    m->curAnimOffset = (m->curAnimOffset * alpha) + (targetOffset * (1.0f - alpha));
    if (m->curAnimOffset > 40)  { m->curAnimOffset = 40; }
    if (m->curAnimOffset < -40) { m->curAnimOffset = -40; }

    marioObj->header.gfx.pos[1] = m->pos[1] + m->curAnimOffset;
    marioObj->header.gfx.node.flags |= GRAPH_RENDER_PLAYER;
}

s32 get_character_anim(struct MarioState* m, enum CharacterAnimID characterAnim) {
    if (m == NULL) { return 0; }

    struct Character* character = get_character(m);
    return ((characterAnim >= 0 && characterAnim < CHAR_ANIM_MAX && character->anims[characterAnim] >= CHAR_ANIM_MAX) ? character->anims[characterAnim] : (s32)characterAnim);
}

const char* get_modded_character_anim_string(struct MarioState* m, enum CharacterAnimID characterAnim) {
    if (m == NULL) { return NULL; }
    if (characterAnim < 0 || characterAnim >= CHAR_ANIM_MAX) { return NULL; }

    struct Character* character = get_character(m);
    if (character->moddedAnims[characterAnim] < 0) { return NULL; }

    return smlua_anim_util_animation_exists_using_index(character->moddedAnims[characterAnim]) ? smlua_anim_util_get_name_from_index(character->moddedAnims[characterAnim]) : NULL;
}

struct Character* character_allocate(RET int *characterIndex) {
    *characterIndex = character_get_first_unallocated_index();
    struct Character* character = &gCharacters[*characterIndex];
    character->type = CT_MARIO;
    return character;
}

void character_deallocate(struct Character* character) {
    *character = gTemplateCharacter;
}

void character_set_name(struct Character* character, const char* name) {
    if (character == NULL) { return; }
    if (strlen(name) >= MAX_CHARACTER_NAME_LEN) {
        LOG_LUA_LINE("character_set_name: Name %s exceeds %u character limit", name, MAX_CHARACTER_NAME_LEN)
        return;
    }
    strncpy(character->name, name, MAX_CHARACTER_NAME_LEN);
    character->name[MAX_CHARACTER_NAME_LEN - 1] = '\0';
}

void character_set_hud_head_texture(struct Character* character, struct TextureInfo* texInfo) {
    if (character == NULL) { return; }
    if (texInfo == NULL) { return; }
    character->hudHeadTexture.name = texInfo->name;
    character->hudHeadTexture.texture = texInfo->texture;
    character->hudHeadTexture.width = texInfo->width;
    character->hudHeadTexture.height = texInfo->height;
    character->hudHeadTexture.size = texInfo->size;
    character->hudHeadTexture.format = texInfo->format;
}

void character_set_cap_enemy_gfx_name(struct Character* character, const char* gfxName) {
    if (character == NULL) { return; }
    character->capEnemyGfx = strdup(gfxName);
}

void character_set_cap_enemy_decal_gfx_name(struct Character* character, const char* gfxName) {
    if (character == NULL) { return; }
    character->capEnemyDecalGfx = strdup(gfxName);
}

void character_add_sound(struct Character* character, enum CharacterSound characterSound, const char* audioName) {
    if (!character) return;
    if (!audioName) return;
    if (characterSound < 0 || characterSound >= CHAR_SOUND_MAX) return;

    bool validFileType = false;
    const char* fileTypes[] = { ".mp3", ".aiff", ".ogg", NULL };
    const char** ft = fileTypes;
    while (*ft != NULL) {
        if (path_ends_with(audioName, *ft)) {
            validFileType = true;
            break;
        }
        ft++;
    }
    if (!validFileType) {
        LOG_LUA_LINE("character_add_sound: Tried to set audio name to invalid file type: %s", audioName);
        return;
    }
    char normPath[SYS_MAX_PATH] = { 0 };
    snprintf(normPath, SYS_MAX_PATH, "%s", audioName);
    normalize_path(normPath);

    // find mod file in mod list
    int modFileIndex = -1;
    u16 fileCount = gLuaActiveMod->fileCount;
    for (u16 i = 0; i < fileCount; i++) {
        struct ModFile* file = &gLuaActiveMod->files[i];
        if(path_ends_with(file->relativePath, normPath)) {
            modFileIndex = i;
            break;
        }
    }
    if (modFileIndex < 0){
        LOG_LUA_LINE("character_add_sound: Could not find audio file: '%s'", audioName);
        return;
    }

    for (int i = 0; i < MAX_CHARACTER_AUDIOS_PER_SOUND; i++) {
        if (character->modAudioSounds[characterSound][i] < 0) {
            character->modAudioSounds[characterSound][i] = modFileIndex;
            character->modIndexForAudio[characterSound][i] = gLuaActiveMod->index;
            return;
        }
    }
    LOG_LUA_LINE("character_add_sound: Too many audio files in sound %d. %d audio files already exist", characterSound, MAX_CHARACTER_AUDIOS_PER_SOUND);
}

void character_remove_sounds(struct Character* character, enum CharacterSound characterSound) {
    if (!character) return;
    if (characterSound < 0 || characterSound >= CHAR_SOUND_MAX) return;

    for (int i = 0; i < MAX_CHARACTER_AUDIOS_PER_SOUND; i++) {
        character->modAudioSounds[characterSound][i] = -1;
        character->modIndexForAudio[characterSound][i] = -1;
    }
}

void character_set_animation(struct Character* character, enum CharacterAnimID animID, const char* animString) {
    if (!character) { return; }
    if (animID < 0 || animID >= CHAR_ANIM_MAX) { return; }
    if (!animString) { return; }

    if (!smlua_anim_util_animation_exists(animString)) {
        LOG_LUA_LINE("character_set_animation: Animation %s does not exist!", animString)
    }
    int index = smlua_anim_util_get_index_from_name(animString);
    character->moddedAnims[animID] = index;
}

void character_remove_animation(struct Character* character, enum CharacterAnimID animID) {
    if (!character) { return; }
    if (animID < 0 || animID >= CHAR_ANIM_MAX) { return; }

    character->moddedAnims[animID] = -1;
}

void reset_all_characters() {
    memcpy(gCharacters, gOriginalCharacters,
           sizeof(struct Character) * CT_MAX);

    for (int i = 0; i < MAX_CHARACTERS; i++) {
        if (i >= CT_MAX) {
            gCharacters[i] = gTemplateCharacter;
        }
        // set audio and anim indexes to -1 so they don't trigger, since 0 is a valid index
        for (int j = 0; j < CHAR_SOUND_MAX; j++) {
            for (int k = 0; k < MAX_CHARACTER_AUDIOS_PER_SOUND; k++) {
                gCharacters[i].modAudioSounds[j][k] = -1;
                gCharacters[i].modIndexForAudio[j][k] = -1;
            }
        }
        for (int j = 0; j < CHAR_ANIM_MAX; j++) {
            gCharacters[i].moddedAnims[j] = -1;
        }
    }

    if (configPlayerModel < 0 || configPlayerModel >= MAX_CHARACTERS) {
        configPlayerModel = CT_MARIO;
    }
}