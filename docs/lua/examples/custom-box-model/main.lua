-- name: Custom Box Model
-- description: Press DPAD+down to spawn a box

E_MODEL_CUSTOM_BOX = smlua_model_util_get_id("custom_box_geo")

function mario_update_local(m)
    if (m.controller.buttonPressed & D_JPAD) ~= 0 then
        print('spawning box: ', id_bhvBreakableBox, E_MODEL_CUSTOM_BOX)
        -- spawn breakable box
        spawn_sync_object(
            id_bhvBreakableBoxSmall,
            E_MODEL_CUSTOM_BOX,
            m.pos.x, m.pos.y, m.pos.z,
            nil)
    end
end

function mario_update(m)
    if m.playerIndex == 0 then
        mario_update_local(m)
    end
end

hook_event(HOOK_MARIO_UPDATE, mario_update)
