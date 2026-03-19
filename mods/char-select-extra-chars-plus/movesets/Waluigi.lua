require "vanilla-chars"
require "anims/waluigi"

return {
    { HOOK_MARIO_UPDATE, char_update },
    { HOOK_BEFORE_PHYS_STEP, char_before_phys_step },
    { HOOK_ON_SET_MARIO_ACTION, char_on_set_action }
}