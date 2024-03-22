local function sv_get_gravity() return gGlobalSyncTable.Convar_Gravity end
local function sv_get_air_accel() return gGlobalSyncTable.Convar_AirAccelerate end
local function sv_get_air_clamp() return gGlobalSyncTable.Convar_AirClamp end
local function sv_get_ground_accel() return gGlobalSyncTable.Convar_Accelerate end
local function sv_get_speed() return gGlobalSyncTable.Convar_PlayerSpeed end
local function sv_get_friction() return gGlobalSyncTable.Convar_PlayerFriction end
local function sv_get_jump_height() return gGlobalSyncTable.Convar_PlayerJumpHeight end
local function sv_get_allow_groundpound() return gGlobalSyncTable.Convar_PlayerAllow_GroundPound end
local function sv_get_allow_walljump() return gGlobalSyncTable.Convar_PlayerAllow_WallJump end
local function sv_get_allow_interact() return gGlobalSyncTable.Convar_PlayerAllow_Interact end

local function sv_set_gravity(v) gGlobalSyncTable.Convar_Gravity = v end
local function sv_set_air_accel(v) gGlobalSyncTable.Convar_AirAccelerate = v end
local function sv_set_air_clamp(v) gGlobalSyncTable.Convar_AirClamp = v end
local function sv_set_ground_accel(v) gGlobalSyncTable.Convar_Accelerate = v end
local function sv_set_speed(v) gGlobalSyncTable.Convar_PlayerSpeed = v end
local function sv_set_friction(v) gGlobalSyncTable.Convar_PlayerFriction = v end
local function sv_set_jump_height(v) gGlobalSyncTable.Convar_PlayerJumpHeight = v end
local function sv_set_allow_groundpound(v) gGlobalSyncTable.Convar_PlayerAllow_GroundPound = v end
local function sv_set_allow_walljump(v) gGlobalSyncTable.Convar_PlayerAllow_WallJump = v end
local function sv_set_allow_interact(v) gGlobalSyncTable.Convar_PlayerAllow_Interact = v end

local function cl_set_allow_action(a,o) 
	DM_ACTIONS[tonumber(a)] = o
end

local function cl_set_action_crouchair(a,o)  
	DM_ACTIONS_CROUCHAIR[tonumber(a)] = o
end

local function cl_set_action_allowgrab(a,o)  
	DM_ACTIONS_ALLOWGRAB[tonumber(a)] = o
end

local function cl_set_action_uses_qphys(a,o)  
	DM_ACTION_QPHYS[tonumber(a)] = o
end

local function cl_set_action_forceangle(a,o)  
	DM_ACTION_FORCEANGLE[tonumber(a)] = o
end

local function cl_set_action_transfer_to_qphys(a,o)  
	DM_ACTION_TRANSFERS[tonumber(a)] = o
end

local function cl_set_action_prerun_func(a,o) 
	DM_ACTION_PREFUNCS[tonumber(a)] = o
end

local function cl_set_action_postrun_func(a,o) 
	DM_ACTION_FUNCTIONS[tonumber(a)] = o
end

local function cl_set_action_ignore_fp(a,o) 
	DM_ACTION_DONT_OVERRIDE_FP[tonumber(a)] = o
end

local function cl_set_interaction_func(a,o) 
	interactOverrides[tonumber(a)] = o
end

local function cl_set_throw_func(a,o) 
	throwOverrides[tonumber(a)]=o
end

local function cl_set_drop_func(a,o) 
	dropOverrides[tonumber(a)]=o
end

local api = {
	version = 1,
	hotfix = 0,
	server = {
		get = {  -- Allows modders to get server convars
			stickyslope = sv_get_stickyslope,
			gravity = sv_get_gravity,
			airaccelerate = sv_get_air_accel,
			airclamp = sv_get_air_clamp,
			accelerate = sv_get_ground_accel,
			speed = sv_get_speed,
			friction = sv_get_friction,
			jumpheight = sv_get_jump_height,
			groundpound = sv_get_allow_groundpound,
			walljump = sv_get_allow_walljump,
			interact = sv_get_allow_interact
		},
		set = {  -- Allows modders to override server convars
			stickyslope = sv_set_stickyslope,
			gravity = sv_set_gravity,
			airaccelerate = sv_set_air_accel,
			airclamp = sv_set_air_clamp,
			accelerate = sv_set_ground_accel,
			speed = sv_set_speed,
			friction = sv_set_friction,
			jumpheight = sv_set_jump_height,
			groundpound = sv_set_allow_groundpound,
			walljump = sv_set_allow_walljump,
			interact = sv_set_allow_interact
		}
	},
	physics = {  -- Allows modders to access mQuakes physics functions
		update = local_update,
		airaccelerate = SV_AirAccelerate,
		accelerate = SV_Accelerate,
		playermovement = SV_PlayerMovement,
		watermovement = SV_WaterMovement,
		gravity = SV_UserGravityEx,
		friction = SV_UserFriction,
		getplayerangles = GetAngleVectors,
		handlefloors = SV_HandleSpecialFloors,
		addrelativevelocity = SV_PlayerMovement_Relative,
		storeplayerposvel = SV_PlayerMovement_Store,
		velcollide = PHYS_CollideWithNormal
	},
	actions = {  -- Allows modders to access mQuakes action override tables
		set_allow_action = cl_set_allow_action,
		set_action_crouchair = cl_set_action_crouchair,
		set_action_allowgrab = cl_set_action_allowgrab,
		set_action_uses_qphys = cl_set_action_uses_qphys,
		set_action_forceangle = cl_set_action_forceangle,
		set_action_transfer_to_qphys = cl_set_action_transfer_to_qphys,
		set_action_prerun_func = cl_set_action_prerun_func,
		set_action_postrun_func = cl_set_action_postrun_func,
		set_action_ignore_fp = cl_set_action_ignore_fp,
		get_allowed_action_list = function() return DM_ACTIONS end,
		get_crouchair_action_list = function() return DM_ACTIONS_CROUCHAIR end,
		get_allowgrab_action_list = function() return DM_ACTIONS_ALLOWGRAB end,
		get_qphys_action_list = function() return DM_ACTION_QPHYS end,
		get_nofp_action_list = function() return DM_ACTION_DONT_OVERRIDE_FP end,
		get_forceangle_action_list = function() return DM_ACTION_FORCEANGLE end,
		get_transfer_action_list = function() return DM_ACTION_TRANSFERS end,
		get_prefunc_action_list = function() return DM_ACTION_PREFUNCS end,
		get_postfunc_action_list = function() return DM_ACTION_FUNCTIONS end
	},
	interactions = {  -- Allows modders to override interactions
		set_interaction_override = cl_set_interaction_func,
		set_throw_override = cl_set_throw_func,
		set_drop_override = cl_set_drop_func
	}
}

_G.mQuake_API = api