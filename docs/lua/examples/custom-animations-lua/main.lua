-- name: Custom animation (LUA)
-- description: No running allowed.\nReplace the running animation by Mario walking.

local function mario_update(m)
    if m.marioObj.header.gfx.animInfo.animID == MARIO_ANIM_RUNNING then
        smlua_anim_util_set_animation(m.marioObj, "mario_anim_walking")
    end
end

hook_event(HOOK_MARIO_UPDATE, mario_update)
