#include "sm64.h"
#include "types.h"
#include "characters.h"
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

struct Character gCharacters[CT_MAX] = {
    [CT_MARIO] = {
        .type                  = CT_MARIO,
        .name                  = "Mario",
        .hudHead               = '(',
        .hudHeadTexture        = { .texture = (u8*)texture_hud_char_mario_head, .bitSize = 8, .width = 16, .height = 16, .name = "texture_hud_char_mario_head" },
        .cameraHudHead         = GLYPH_CAM_MARIO_HEAD,
        .modelId               = MODEL_MARIO,
        .capModelId            = MODEL_MARIOS_CAP,
        .capMetalModelId       = MODEL_MARIOS_METAL_CAP,
        .capWingModelId        = MODEL_MARIOS_WING_CAP,
        .capMetalWingModelId   = MODEL_MARIOS_WINGED_METAL_CAP,
        .capEnemyLayer         = LAYER_ALPHA,
        .capEnemyGfx           = mario_cap_seg3_dl_03022F48,
        .capEnemyDecalGfx      = mario_cap_m_logo_decal,
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
        .hudHead               = ')',
        .hudHeadTexture        = { .texture = (u8*)texture_hud_char_luigi_head, .bitSize = 8, .width = 16, .height = 16, .name = "texture_hud_char_luigi_head" },
        .cameraHudHead         = GLYPH_CAM_LUIGI_HEAD,
        .modelId               = MODEL_LUIGI,
        .capModelId            = MODEL_LUIGIS_CAP,
        .capMetalModelId       = MODEL_LUIGIS_METAL_CAP,
        .capWingModelId        = MODEL_LUIGIS_WING_CAP,
        .capMetalWingModelId   = MODEL_LUIGIS_WINGED_METAL_CAP,
        .capEnemyLayer         = LAYER_ALPHA,
        .capEnemyGfx           = luigi_cap_seg3_dl_03022F48,
        .capEnemyDecalGfx      = luigi_cap_l_logo_decal,
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
        .hudHead               = '|',
        .hudHeadTexture        = { .texture = (u8*)texture_hud_char_toad_head, .bitSize = 8, .width = 16, .height = 16, .name = "texture_hud_char_toad_head" },
        .cameraHudHead         = GLYPH_CAM_TOAD_HEAD,
        .modelId               = MODEL_TOAD_PLAYER,
        .capModelId            = MODEL_TOADS_CAP,
        .capMetalModelId       = MODEL_TOADS_METAL_CAP,
        .capWingModelId        = MODEL_TOADS_WING_CAP,
        .capMetalWingModelId   = MODEL_TOADS_WINGED_METAL_CAP,
        .capEnemyLayer         = LAYER_ALPHA,
        .capEnemyGfx           = toad_cap_mesh_layer_1,
        .capEnemyDecalGfx      = toad_cap_mesh_layer_5,
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
        .hudHead               = ']',
        .hudHeadTexture        = { .texture = (u8*)texture_hud_char_waluigi_head, .bitSize = 8, .width = 16, .height = 16, .name = "texture_hud_char_waluigi_head" },
        .cameraHudHead         = GLYPH_CAM_WALUIGI_HEAD,
        .modelId               = MODEL_WALUIGI,
        .capModelId            = MODEL_WALUIGIS_CAP,
        .capMetalModelId       = MODEL_WALUIGIS_METAL_CAP,
        .capWingModelId        = MODEL_WALUIGIS_WING_CAP,
        .capMetalWingModelId   = MODEL_WALUIGIS_WINGED_METAL_CAP,
        .capEnemyLayer         = LAYER_ALPHA,
        .capEnemyGfx           = waluigi_cap_seg3_dl_03022F48,
        .capEnemyDecalGfx      = waluigi_cap_r_logo_decal,
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
        .hudHead               = '[',
        .hudHeadTexture        = { .texture = (u8*)texture_hud_char_wario_head, .bitSize = 8, .width = 16, .height = 16, .name = "texture_hud_char_wario_head" },
        .cameraHudHead         = GLYPH_CAM_WARIO_HEAD,
        .modelId               = MODEL_WARIO,
        .capModelId            = MODEL_WARIOS_CAP,
        .capMetalModelId       = MODEL_WARIOS_METAL_CAP,
        .capWingModelId        = MODEL_WARIOS_WING_CAP,
        .capMetalWingModelId   = MODEL_WARIOS_WINGED_METAL_CAP,
        .capEnemyLayer         = LAYER_ALPHA,
        .capEnemyGfx           = wario_cap_seg3_dl_03022F48,
        .capEnemyDecalGfx      = wario_cap_w_logo_decal,
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

struct Character* get_character(struct MarioState* m) {
    return (m == NULL || m->character == NULL)
        ? &gCharacters[CT_MARIO]
        : m->character;
}

static s32 get_character_sound(struct MarioState* m, enum CharacterSound characterSound) {
    if (m == NULL || m->marioObj == NULL) { return 0; }

    s32 override = 0;
    if (smlua_call_event_hooks_mario_character_sound_param_ret_int(HOOK_CHARACTER_SOUND, m, characterSound, &override)) {
        return override;
    }

    struct Character* character = ((m == NULL || m->character == NULL) ? &gCharacters[CT_MARIO] : m->character);

    if (characterSound < 0 || characterSound >= CHAR_SOUND_MAX) { return 0; }
    return character->sounds[characterSound];
}

static void play_character_sound_internal(struct MarioState *m, enum CharacterSound characterSound, u32 offset, u32 flags) {
    if (m != NULL && (m->flags & flags) == 0) {
        s32 sound = get_character_sound(m, characterSound);
        if (sound != 0) {
            struct Character* character = get_character(m);
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

    struct Character* character = ((m->character == NULL) ? &gCharacters[CT_MARIO] : m->character);
    return ((characterAnim >= 0 && characterAnim < CHAR_ANIM_MAX && character->anims[characterAnim] >= CHAR_ANIM_MAX) ? character->anims[characterAnim] : (s32)characterAnim);
}
