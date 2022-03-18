-- name: Custom Koopa Player Model
-- description: Press DPAD+DOWN to become a Koopa!\n(by Super Keeberghrh)

E_MODEL_KOOPA_PLAYER = smlua_model_util_get_id("koopa_player_geo")

function mario_update_local(m)
    if (m.controller.buttonPressed & D_JPAD) ~= 0 then
        gPlayerSyncTable[0].modelId = E_MODEL_KOOPA_PLAYER
    end
end

function mario_update(m)
    if m.playerIndex == 0 then
        mario_update_local(m)
    end

    if gPlayerSyncTable[m.playerIndex].modelId ~= nil then
        obj_set_model_extended(m.marioObj, gPlayerSyncTable[m.playerIndex].modelId)
    end
end

hook_event(HOOK_MARIO_UPDATE, mario_update)
