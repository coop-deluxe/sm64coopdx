require "vanilla-chars"
require "anims/wario"

return {
    { HOOK_MARIO_UPDATE, char_update },
    { HOOK_BEFORE_PHYS_STEP, char_before_phys_step },
    { HOOK_ON_SET_MARIO_ACTION, char_on_set_action },
    { HOOK_ON_INTERACT, char_on_interact },
    { HOOK_ON_PVP_ATTACK, char_on_pvp_attack }
}