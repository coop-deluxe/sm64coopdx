local E_MODEL_SKYBOX_BLIMPCITY = smlua_model_util_get_id("skybox_blimpcity_geo")

local function bhv_skybox_init(o)
    o.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    o.header.gfx.skipInViewCheck = true
    obj_scale(o, 10.0)
end

local function bhv_skybox_loop(o)
    vec3f_to_object_pos(o, gLakituState.pos)
end

id_bhvSkybox = hook_behavior(nil, OBJ_LIST_LEVEL, false, bhv_skybox_init, bhv_skybox_loop)

local function on_level_init()
    if gNetworkPlayers[0].currLevelNum == LEVEL_ARENA_CITY then
        spawn_non_sync_object(
            id_bhvSkybox,
            E_MODEL_SKYBOX_BLIMPCITY,
            gLakituState.pos.x, gLakituState.pos.y, gLakituState.pos.z,
            nil
        )
    end
end

hook_event(HOOK_ON_LEVEL_INIT, on_level_init)
