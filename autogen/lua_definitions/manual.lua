-------------
-- globals --
-------------

--- @type MarioState[]
--- Array of `MarioState`s, from 0 to `MAX_PLAYERS` - 1
--- - Uses the local index, which is different between every player
--- - Index 0 always refers to the local player
gMarioStates = {}

--- @type NetworkPlayer[]
--- Array of `NetworkPlayer`s, from 0 to `MAX_PLAYERS` - 1
--- - Uses the local index, which is different between every player
--- - Index 0 always refers to the local player
gNetworkPlayers = {}

--- @type Mod[]
--- Array of all mods loaded, starting from 0
--- - All mods are loaded in the same order for every player
--- - Index 0 is the first mod in the list (the top of the mod list)
gActiveMods = {}

--- @type Character[]
--- Array of every character, from 0 to `CT_MAX` - 1
--- - The contents or order of the characters can never change
gCharacters = {}

--- @type Controller[]
--- Array of every controller, from 0 to `MAX_PLAYERS` - 1
--- - Uses the local index, which is different between every player
--- - Index 0 always refers to the local player
gControllers = {}

--- @type Pointer_Mat4[]
--- Matrix stack used during geo process
--- - Only has an effect when used in a geo process hook
gMatStack = {}

--- @type Pointer_Mat4[]
--- Matrix stack used during geo process
--- - Only has an effect when used in a geo process hook
gMatStackPrev = {}

--- @type GlobalTextures
--- Struct containing HUD glyph textures
gTextures = {}

--- @type GlobalObjectAnimations
--- Struct containing every object animation
gObjectAnimations = {}

--- @type GlobalObjectCollisionData
--- Struct containing all object collision data
gGlobalObjectCollisionData = {}

--- @type PaintingValues
--- Struct containing all paintings and their fields
gPaintingValues = {}

--- @alias SyncTable table

--- @type SyncTable
--- Any keys added and modified to this table will be synced among everyone.
--- - This shouldn't be used to sync player-specific values; Use `gPlayerSyncTable` for that
--- - Note: Does not support tables as keys
gGlobalSyncTable = {}

--- @type SyncTable[]
--- Array of sync tables. Any change to any sync tables will be synced to everyone else.
--- - This array takes in a local index, however it automatically translates to the global index
--- - Note: Does not support tables as keys
gPlayerSyncTable = {}

--- @type LevelValues
--- Struct containing fields that modify specific gameplay or level properties
gLevelValues = {}

--- @type BehaviorValues
--- Struct containing fields that modify specific object behavior properties
gBehaviorValues = {}

--- @type FirstPersonCamera
--- Struct that contains the fields for the first person camera
gFirstPersonCamera = {}

--- @type LakituState
--- The primary struct that controls the camera
--- - Local player only
gLakituState = {}

--- @type ServerSettings
--- Struct containing the settings for the server
--- - enablePlayersInLevelDisplay and enablePlayerList are not synced
gServerSettings = {}

--- @type NametagsSettings
--- Struct containing the settings for Nametags
gNametagsSettings = {}

--- @type Camera
--- Struct contaning camera fields
--- - This camera is the same as `gMarioStates[i].area.camera` or `gCurrentArea.camera`
gCamera = {}

-----------
-- hooks --
-----------

--- @param behaviorId BehaviorId | integer?  The behavior id of the object to modify. Pass in as `nil` to create a custom object
--- @param objectList ObjectList | integer Object list
--- @param replaceBehavior boolean Whether or not to completely replace the behavior
--- @param initFunction? fun(obj:Object) Run on object creation
--- @param loopFunction? fun(obj:Object) Run every frame
--- @param behaviorName? string Optional
--- @return BehaviorId BehaviorId Use if creating a custom object, otherwise can be ignored
--- Modify an object's behavior or create a new custom object
function hook_behavior(behaviorId, objectList, replaceBehavior, initFunction, loopFunction, behaviorName)
    -- ...
end

--- @param command string The command to run. Should be easy to type
--- @param description string Should describe what the command does and how to use it
--- @param func fun(msg:string): boolean Run upon activating the command. Return `true` to confirm the command has succeeded
function hook_chat_command(command, description, func)
    -- ...
end

--- @param command string The command to change the description of
--- @param description string The description to change to
function update_chat_command_description(command, description)
    -- ...
end

--- @param hookEventType LuaHookedEventType When a function should run
--- @param func fun(...: any): any The function to run
--- Different hooks can pass in different parameters and have different return values. Be sure to read the hooks guide for more information.
function hook_event(hookEventType, func)
    -- ...
end

--- @class ActionTable
--- @field every_frame fun(m:MarioState):integer?
--- @field gravity fun(m:MarioState):integer?

--- @param actionId integer The action to replace
--- @param funcOrFuncTable fun(m:MarioState):integer? | ActionTable The new behavior of the action
--- @param interactionType? InteractionFlag Optional; The flag that determines how the action interacts with other objects
--- If a function table is used, it must be in the form of `{ act_hook = [func], ... }`. Current action hooks include:
--- - every_frame
--- - gravity
function hook_mario_action(actionId, funcOrFuncTable, interactionType)
    -- ...
end

--- @param syncTable SyncTable Must be the gGlobalSyncTable or gPlayerSyncTable[] or one of their child tables
--- @param field string Field name
--- @param tag any An additional parameter
--- @param func fun(tag:any, oldVal:any, newVal:any) Run when the specified field has been changed
function hook_on_sync_table_change(syncTable, field, tag, func)
    -- ...
end

--- @param message string The message for the text to show
--- @return integer
--- Hooks DJUI text into the mod menu
function hook_mod_menu_text(message)
    -- ...
end

--- @param name string The text to show on the button
--- @param func fun(index:integer) The function that is called when the button is pressed
--- @return integer
--- Hooks a DJUI button into the mod menu
function hook_mod_menu_button(name, func)
    -- ...
end

--- @param name string The text to show on the left
--- @param defaultValue boolean The default state of the checkbox
--- @param func fun(index:integer, value:boolean) The function that is called when the checkbox is changed
--- @return integer
--- Hooks a DJUI checkbox into the mod menu
function hook_mod_menu_checkbox(name, defaultValue, func)
    -- ...
end

--- @param name string The text to show on the left
--- @param defaultValue integer The default value of the slider
--- @param min integer The lowest the slider can go
--- @param max integer The highest the slider can go
--- @param func fun(index:integer, value:integer) The function that is called when the value of the slider changes
--- @return integer
--- Hooks a DJUI slider into the mod menu
function hook_mod_menu_slider(name, defaultValue, min, max, func)
    -- ...
end

--- @param name string The text to show on the left
--- @param defaultValue string The default text in the inputbox
--- @param stringLength integer The max length of the inputbox
--- @param func fun(index:integer, value:string) The function that is called when the value of the inputbox changes
--- @return integer
--- Hooks a DJUI inputbox into the mod menu
function hook_mod_menu_inputbox(name, defaultValue, stringLength, func)
    -- ...
end

--- @param index integer The index of the element in the order in which they were hooked
--- @param name string The name to change to
--- Updates a mod menu element's text
--- - NOTE: `index` is zero-indexed
function update_mod_menu_element_name(index, name)
    -- ...
end

--- @param index integer The index of the element in the order in which they were hooked
--- @param value boolean The boolean value to change to
--- Updates a mod menu checkbox element's boolean value
--- - NOTE: `index` is zero-indexed
function update_mod_menu_element_checkbox(index, value)
    -- ...
end

--- @param index integer The index of the element in the order in which they were hooked
--- @param value number The number value to change to
--- Updates a mod menu slider element's numerical value
--- - NOTE: `index` is zero-indexed
function update_mod_menu_element_slider(index, value)
    -- ...
end

--- @param index integer The index of the element in the order in which they were hooked
--- @param value string The text to change to
--- Updates a mod menu inputbox element's string value
--- - NOTE: `index` is zero-indexed
function update_mod_menu_element_inputbox(index, value)
    -- ...
end

---------------
-- functions --
---------------

--- @param objFieldTable table<any, "u32"|"s32"|"f32">
--- Keys must start with `o` and values must be `"u32"`, `"s32"`, or `"f32"`
function define_custom_obj_fields(objFieldTable)
    -- ...
end

--- @param object Object Object to sync
--- @param standardSync boolean Automatically syncs common fields and syncs with distance. If `false`, all syncing must be done with `network_send_object`
--- @param fieldTable table<string> The fields to sync
--- All synced fields must start with `o` and there should not be any keys, just values
function network_init_object(object, standardSync, fieldTable)
    -- ...
end

--- @param object Object Object to sync
--- @param reliable boolean Whether or not the game should try to resend the packet in case it gets lost, good for important packets
--- Sends a sync packet to sync up the object with everyone else
function network_send_object(object, reliable)
    -- ...
end

--- @param reliable boolean Whether or not the game should try to resend the packet in case its lost, good for important packets
--- @param dataTable table<string, number|boolean|string|nil> Table of values to be included in the packet
--- Sends a global Lua packet with the values of `dataTable`
function network_send(reliable, dataTable)
    -- ...
end

--- @param toLocalIndex integer The local index to send the packet to
--- @param reliable boolean Whether or not the game should try to resend the packet in case its lost, good for important packets
--- @param dataTable table Table of values to be included in the packet
--- Sends a Lua packet with the values of `dataTable` to a specific client through local indices
function network_send_to(toLocalIndex, reliable, dataTable)
    -- ...
end

--- @param textureName string The texture name
--- @return TextureInfo
--- Gets the `TextureInfo` of a texture by name
--- - Note: This also works with vanilla textures
function get_texture_info(textureName)
    -- ...
end

--- @param texInfo TextureInfo The texture
--- @param x number Where the texture is horizontally (left anchored)
--- @param y number Where the texture is vertically (top anchored)
--- @param scaleW number The scaled width of the texture
--- @param scaleH number The scaled height of the texture
--- Renders a texture to the screen
function djui_hud_render_texture(texInfo, x, y, scaleW, scaleH)
    -- ...
end

--- @param texInfo TextureInfo The texture
--- @param x number Where the texture is horizontally (left anchored)
--- @param y number Where the texture is vertically (top anchored)
--- @param scaleW number The scaled width of the texture
--- @param scaleH number The scaled height of the texture
--- @param tileX number Where the tile is horizontally (left anchored)
--- @param tileY number Where the tile is vertically (top anchored)
--- @param tileW number The width of the tile
--- @param tileH number The height of the tile
--- Renders a tile of a texture to the screen
function djui_hud_render_texture_tile(texInfo, x, y, scaleW, scaleH, tileX, tileY, tileW, tileH)
    -- ...
end

--- @param texInfo TextureInfo The texture
--- @param prevX number Where the texture previously was horizontally (left anchored)
--- @param prevY number Where the texture previously was vertically (top anchored)
--- @param prevScaleW number The previous scaled width of the texture
--- @param prevScaleH number The previous scaled height of the texture
--- @param x number Where the texture is horizontally (left anchored)
--- @param y number Where the texture is vertically (top anchored)
--- @param scaleW number The scaled width of the texture
--- @param scaleH number The scaled height of the texture
--- Renders an interpolated texture to the screen
function djui_hud_render_texture_interpolated(texInfo, prevX, prevY, prevScaleW, prevScaleH, x, y, scaleW, scaleH)
    -- ...
end

--- @param texInfo TextureInfo The texture
--- @param prevX number Where the texture previously was horizontally (left anchored)
--- @param prevY number Where the texture previously was vertically (top anchored)
--- @param prevScaleW number The previous scaled width of the texture
--- @param prevScaleH number The previous scaled height of the texture
--- @param x number Where the texture is horizontally (left anchored)
--- @param y number Where the texture is vertically (top anchored)
--- @param scaleW number The scaled width of the texture
--- @param scaleH number The scaled height of the texture
--- @param tileX number Where the tile is horizontally (left anchored)
--- @param tileY number Where the tile is vertically (top anchored)
--- @param tileW number The width of the tile
--- @param tileH number The height of the tile
--- Renders an interpolated tile of a texture to the screen
function djui_hud_render_texture_tile_interpolated(texInfo, prevX, prevY, prevScaleW, prevScaleH, x, y, scaleW, scaleH, tileX, tileY, tileW, tileH)
    -- ...
end

--- @param textureName string The name of the texture
--- @param overrideTexInfo TextureInfo The texture to override with
--- Overrides a texture with a custom `TextureInfo`
--- - `textureName` must be the codename of a vanilla texture, you can find these in files such as `texture.inc.c`s
--- - `overrideTexInfo` can be any TextureInfo
function texture_override_set(textureName, overrideTexInfo)
    -- ...
end

--- @param textureName string The name of the texture
--- Resets an overridden texture
function texture_override_reset(textureName)
    -- ...
end

--- @class BehaviorData
--- @field behavior BehaviorId
--- @field behaviorArg integer

--- @param levelNum LevelNum | integer
--- @param func fun(areaIndex:number, bhvData:BehaviorData, macroBhvIds:BehaviorId[], macroBhvArgs:integer[])
--- When `func` is called, arguments are filled depending on the level command:
--- - `AREA` command: only `areaIndex` is filled. It's a number
--- - `OBJECT` command: only `bhvData` is filled. `bhvData` is a table with nine fields: 'behavior', 'behaviorArg', 'model', 'posX', 'posY', 'posZ', 'pitch', 'yaw' and 'roll'
--- - `MACRO` command: only `macroBhvIds`, `macroBhvArgs` and 'macroBhvModels' are filled. `macroBhvIds` is a list of behavior ids. `macroBhvArgs` is a list of behavior params. 'macroBhvModels' is a list of model ids. All lists have the same size and start at index 0
function level_script_parse(levelNum, func)
    -- ...
end

--- @param name string The name of the animation
--- @param flags integer The flags of the animation (`ANIM_FLAG_*`)
--- @param animYTransDivisor integer The vertical animation translation divisor
--- @param startFrame integer What frame the animation starts on
--- @param loopStart integer When the loop starts
--- @param loopEnd integer When the loop ends
--- @param values table The table containing animation values
--- @param index table The table containing animation indices
--- Registers an animation that can be used in objects if `smlua_anim_util_set_animation` is called
function smlua_anim_util_register_animation(name, flags, animYTransDivisor, startFrame, loopStart, loopEnd, values, index)
    -- ...
end

--- @param message string The message to log
--- @param level? ConsoleMessageLevel Optional; Determines whether the message should appear as info, a warning or an error.
--- Logs a message to the in-game console
function log_to_console(message, level)
    -- ...
end

--- @param index integer The index of the scroll target, should match up with the behavior param of `RM_Scroll_Texture` or `editor_Scroll_Texture`
--- @param name string The name of the vertex buffer that should be used while scrolling the texture
--- Registers a vertex buffer to be used for a scrolling texture. Should be used with `RM_Scroll_Texture` or `editor_Scroll_Texture`
function add_scroll_target(index, name)
    -- ...
end

--- @param startX number Start position X
--- @param startY number Start position Y
--- @param startZ number Start position Z
--- @param dirX number Direction X
--- @param dirY number Direction Y
--- @param dirZ number Direction Z
--- @param precision? number Optional; How precise the raycast should be. The default value is 3.0, the higher the number, the more precise.
--- @return RayIntersectionInfo
--- Shoots a raycast from `startX`, `startY`, and `startZ` in the direction of `dirX`, `dirY`, and `dirZ`
function collision_find_surface_on_ray(startX, startY, startZ, dirX, dirY, dirZ, precision)
    -- ...
end

--- @param contents ExclamationBoxContent[]
--- Sets the contents that the exclamation box spawns.
--- A single content has 5 keys: `id`, `unused`, `firstByte`, `model`, and `behavior`
--- * `id`: Required; what value the box's oBehParams2ndByte needs to be to spawn this object
--- * `unused`: Optional; unused by vanilla
--- * `firstByte`: Optional; Overrides the 1st byte given to the spawned object
--- * `model`: Required; The model that the object will spawn with. Uses `ModelExtendedId`
--- * `behavior`: Required; The behavior ID that the object will spawn with. Uses `BehaviorId`
function set_exclamation_box_contents(contents)
    -- ...
end

--- @return ExclamationBoxContent[]
--- Gets the contents that the exclamation box spawns
--- A single content has 5 keys: `id`, `unused`, `firstByte`, `model`, and `behavior`
--- * `id`: Required; what value the box's oBehParams2ndByte needs to be to spawn this object
--- * `unused`: Optional; unused by vanilla
--- * `firstByte`: Optional; Overrides the 1st byte given to the spawned object
--- * `model`: Required; The model that the object will spawn with. Uses `ModelExtendedId`
--- * `behavior`: Required; The behavior ID that the object will spawn with. Uses `BehaviorId`
function get_exclamation_box_contents()
    -- ...
end

--- @param node GraphNode | FnGraphNode
--- @return GraphNode | GraphNodeAnimatedPart | GraphNodeBackground | GraphNodeBillboard | GraphNodeCamera | GraphNodeCullingRadius | GraphNodeDisplayList | GraphNodeGenerated | GraphNodeHeldObject | GraphNodeLevelOfDetail | GraphNodeMasterList | GraphNodeObject | GraphNodeObjectParent | GraphNodeOrthoProjection | GraphNodePerspective | GraphNodeRotation | GraphNodeScale | GraphNodeShadow | GraphNodeStart | GraphNodeSwitchCase | GraphNodeTranslation | GraphNodeTranslationRotation
--- Returns the specific GraphNode(...) the node is part of.
--- Basically the reverse of `.node` or `.fnNode`
function cast_graph_node(node)
    -- ...
end

--- @param str string
--- @return string
--- Removes color codes from a string
function get_uncolored_string(str)
    -- ...
end

--- @param gfx Gfx
--- @param command string
--- @vararg integer Parameters for the command
--- Sets the specified display list command on the display list given
function gfx_set_command(gfx, command, ...)
    -- ...
end
