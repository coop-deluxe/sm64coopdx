#include "characters.h"
#include "hud.h"
#include "model_ids.h"

struct Character gCharacters[CT_MAX] = {
    [CT_MARIO] = {
        .hudHead = ',',
        .cameraHudHead = GLYPH_CAM_MARIO_HEAD,
        .modelId = MODEL_MARIO,
    },
    [CT_LUIGI] = {
        .hudHead = '.',
        .cameraHudHead = GLYPH_CAM_LUIGI_HEAD,
        .modelId = MODEL_LUIGI,
    },
};