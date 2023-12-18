local seen = false

--- @param o Object
local function bhv_dialog_arrow_init(o)
    o.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE

    o.parentObj = obj_get_nearest_object_with_behavior_id(o, id_bhvMessagePanel)
    if o.parentObj == nil then
        obj_mark_for_deletion(o)
        return
    end

    o.oDrawingDistance = o.parentObj.oDrawingDistance
    o.oPosX = o.parentObj.oPosX
    o.oPosY = o.parentObj.oPosY + 150
    o.oPosZ = o.parentObj.oPosZ
end

--- @param o Object
local function bhv_dialog_arrow_loop(o)
    o.oGraphYOffset = math.sin(o.oTimer * 0.1) * 20

    if gMarioStates[0].interactObj == o.parentObj then
        seen = true
        obj_mark_for_deletion(o)
    elseif o.parentObj.oInteractType == 0 then
        obj_mark_for_deletion(o)
    end
end

local id_bhvDialogArrow = hook_behavior(nil, OBJ_LIST_UNIMPORTANT, true, bhv_dialog_arrow_init, bhv_dialog_arrow_loop)

function spawn_dialog_arrow()
    if gNetworkPlayers[0].currLevelNum ~= LEVEL_CASTLE_GROUNDS or not level_is_vanilla_level(LEVEL_CASTLE_GROUNDS) or seen then return end

    spawn_non_sync_object(
        id_bhvDialogArrow,
        E_MODEL_ARROW,
        -1567, 386, 3492,
        nil
    )
end