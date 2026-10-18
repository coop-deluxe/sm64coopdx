-- name: Custom Level Example
-- description: This is an example of a custom level that replaces BOB.\nIt has a custom object with a custom behavior.\nIt also has a custom skybox.
-- incompatible: romhack

teleport = true

function on_update()
    if teleport == true then
        teleport = false
        warp_to_level(LEVEL_BOB, 1, 0)
    end
end

hook_event(HOOK_MARIO_UPDATE, on_update)
