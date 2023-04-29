-------------
-- globals --
-------------

--- @type MarioState[]
gMarioStates = {}

--- @type NetworkPlayer[]
gNetworkPlayers = {}

--- @type Mod[]
gActiveMods = {}

--- @type Character[]
gCharacter = {}

--- @type GlobalTextures
gTextures = {}

--- @type GlobalObjectAnimations
gObjectAnimations = {}

--- @type GlobalObjectCollisionData
gGlobalObjectCollisionData = {}

--- @alias SyncTable table

--- @type SyncTable
gGlobalSyncTable = {}

--- @type SyncTable[]
gPlayerSyncTable = {}

--- @type LevelValues
gLevelValues = {}

--- @type BehaviorValues
gBehaviorValues = {}

--- @type BehaviorValues
gBehaviorValues = {}

--- @type PlayerPalette[]
gPalettePresets = {}

--- @type LakituState
gLakituState = {}

--- @type PaintingValues
gPaintingValues = {}

--- @type ServerSettings
gServerSettings = {}

-----------
-- hooks --
-----------

--- @param behaviorId BehaviorId
--- @param objectList ObjectList
--- @param replaceBehavior boolean
--- @param initFunction fun(obj:Object)
--- @param loopFunction fun(obj:Object)
--- @param behaviorName string
--- @return BehaviorId
function hook_behavior(behaviorId, objectList, replaceBehavior, initFunction, loopFunction, behaviorName)
    -- ...
end

--- @param command string
--- @param description string
--- @param func fun(msg:string)
function hook_chat_command(command, description, func)
    -- ...
end

--- @param hookEventType LuaHookedEventType
--- @param func function
function hook_event(hookEventType, func)
    -- ...
end

--- @param actionId integer
--- @param funcOrFuncTable fun(m:MarioState):integer | table(fun(m:MarioState):integer)
--- @param interactionType InteractionFlag
function hook_mario_action(actionId, funcOrFuncTable, interactionType)
    -- ...
end

--- @param syncTable SyncTable
--- @param field any
--- @param tag any
--- @param func fun(tag:any, oldVal:any, newVal:any)
function hook_on_sync_table_change(syncTable, field, tag, func)
    -- ...
end

---------------
-- functions --
---------------

--- @param t number
--- @return number
function sins(t)
    -- ...
end

--- @param t number
--- @return number
function coss(t)
    -- ...
end

--- @param y number
--- @param x number
--- @return integer
function atan2s(y, x)
    -- ...
end

--- @param objFieldTable table
--- @return nil
function define_custom_obj_fields(objFieldTable)
    -- ...
end

--- @param object Object
--- @param standardSync boolean
--- @param fieldTable table
--- @return nil
function network_init_object(object, standardSync, fieldTable)
    -- ...
end

--- @param object Object
--- @param reliable boolean
--- @return nil
function network_send_object(object, reliable)
    -- ...
end

--- @param reliable boolean
--- @param dataTable table
--- @return nil
function network_send(reliable, dataTable)
    -- ...
end

--- @param toLocalIndex integer
--- @param reliable boolean
--- @param dataTable table
--- @return nil
function network_send_to(toLocalIndex, reliable, dataTable)
    -- ...
end

--- @param textureName string
--- @return TextureInfo
function get_texture_info(textureName)
    -- ...
end

--- @param textureName string
--- @return TextureInfo
function get_texture_info(textureName)
    -- ...
end

--- @param texInfo TextureInfo
--- @param x number
--- @param y number
--- @param scaleW number
--- @param scaleH number
--- @return nil
function djui_hud_render_texture(texInfo, x, y, scaleW, scaleH)
    -- ...
end

--- @param texInfo TextureInfo
--- @param x number
--- @param y number
--- @param scaleW number
--- @param scaleH number
--- @param tileX number
--- @param tileY number
--- @param tileW number
--- @param tileH number
--- @return nil
function djui_hud_render_texture_tile(texInfo, x, y, scaleW, scaleH, tileX, tileY, tileW, tileH)
    -- ...
end

--- @param texInfo TextureInfo
--- @param prevX number
--- @param prevY number
--- @param prevScaleW number
--- @param prevScaleH number
--- @param x number
--- @param y number
--- @param scaleW number
--- @param scaleH number
--- @return nil
function djui_hud_render_texture_interpolated(texInfo, prevX, prevY, prevScaleW, prevScaleH, x, y, scaleW, scaleH)
    -- ...
end

--- @param texInfo TextureInfo
--- @param prevX number
--- @param prevY number
--- @param prevScaleW number
--- @param prevScaleH number
--- @param x number
--- @param y number
--- @param scaleW number
--- @param scaleH number
--- @param tileX number
--- @param tileY number
--- @param tileW number
--- @param tileH number
--- @return nil
function djui_hud_render_texture_tile_interpolated(texInfo, prevX, prevY, prevScaleW, prevScaleH, x, y, scaleW, scaleH, tileX, tileY, tileW, tileH)
    -- ...
end

--- @param name string
--- @param flags integer
--- @param animYTransDivisor integer
--- @param startFrame integer
--- @param loopStart integer
--- @param loopEnd integer
--- @param values table
--- @param index table
--- @return nil
function smlua_anim_util_register_animation(name, flags, animYTransDivisor, startFrame, loopStart, loopEnd, values, index)
    -- ...
end

--- @param levelNum number
--- @param func fun(areaIndex:number, bhvData:table, macroBhvIds:table, macroBhvArgs:table)
--- @return nil
--- When `func` is called, arguments are filled depending on the level command:
--- - `AREA` command: only `areaIndex` is filled. It's a number.
--- - `OBJECT` command: only `bhvData` is filled. `bhvData` is a table with two fields: `behavior` and `behaviorArg`.
--- - `MACRO` command: only `macroBhvIds` and `macroBhvArgs` are filled. `macrobhvIds` is a list of behavior ids. `macroBhvArgs` is a list of behavior params. Both lists have the same size and start at index 0.
function level_script_parse(levelNum, func)
    -- ...
end
