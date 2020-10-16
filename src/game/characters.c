#include "characters.h"
#include "hud.h"
#include "model_ids.h"
#include "object_constants.h"

struct Character gCharacters[CT_MAX] = {
    [CT_MARIO] = {
        .hudHead = ',',
        .cameraHudHead = GLYPH_CAM_MARIO_HEAD,
        .modelId = MODEL_MARIO,
        .capModelId = MODEL_MARIOS_CAP,
        .capKleptoAnimState = KLEPTO_ANIM_STATE_HOLDING_CAP,
        .capUkikiAnimState = UKIKI_ANIM_STATE_HAT_ON,
    },
    [CT_LUIGI] = {
        .hudHead = '.',
        .cameraHudHead = GLYPH_CAM_LUIGI_HEAD,
        .modelId = MODEL_LUIGI,
        .capModelId = MODEL_LUIGIS_CAP,
        .capKleptoAnimState = KLEPTO_ANIM_STATE_HOLDING_CAP_LUIGI,
        .capUkikiAnimState = UKIKI_ANIM_STATE_HAT_ON_LUIGI,
    },
};