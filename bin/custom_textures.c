#include <ultra64.h>
#include "sm64.h"
#include "game/ingame_menu.h"
#include "make_const_nonconst.h"

ALIGNED8 const Texture texture_hud_char_luigi_head[] = {
#include "textures/segment2/custom_luigi_head.rgba16.inc.c"
};

ALIGNED8 const Texture texture_hud_char_toad_head[] = {
#include "textures/segment2/custom_toad_head.rgba16.inc.c"
};

ALIGNED8 const Texture texture_hud_char_waluigi_head[] = {
#include "textures/segment2/custom_waluigi_head.rgba16.inc.c"
};

ALIGNED8 const Texture texture_hud_char_wario_head[] = {
#include "textures/segment2/custom_wario_head.rgba16.inc.c"
};

ALIGNED8 const Texture texture_shadow_spike_ext[] = {
#include "textures/segment2/shadow_spike_custom.ia8.inc.c"
};

ALIGNED8 const Texture texture_selectionbox_back_icon[] = {
#include "textures/segment2/custom_selectionbox_back_icon.rgba16.inc.c"
};

ALIGNED8 const Texture texture_selectionbox_forward_icon[] = {
#include "textures/segment2/custom_selectionbox_forward_icon.rgba16.inc.c"
};

ALIGNED8 const Texture texture_coopdx_logo[] = {
#include "textures/segment2/custom_coopdx_logo.rgba32.inc.c"
};
