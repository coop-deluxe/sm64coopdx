--------------------------------
-- manually written functions --
--------------------------------

--- @param objFieldTable table<any, "u32"|"s32"|"f32"|table>
--- Keys must start with `o` and values must be `"u32"`, `"s32"`, `"f32"` or a table with fields `type` and `global`, for example `{ type = "u32", global = true }`
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
--- Sends a global Lua packet with the values of `dataTable`. Received with the `HOOK_ON_PACKET_RECEIVE` hook.
function network_send(reliable, dataTable)
    -- ...
end

--- @param toLocalIndex integer The local index to send the packet to
--- @param reliable boolean Whether or not the game should try to resend the packet in case its lost, good for important packets
--- @param dataTable table Table of values to be included in the packet
--- Sends a Lua packet with the values of `dataTable` to a specific client through local indices. Received with the `HOOK_ON_PACKET_RECEIVE` hook.
function network_send_to(toLocalIndex, reliable, dataTable)
    -- ...
end

--- @param reliable boolean Whether or not the game should try to resend the packet in case its lost, good for important packets
--- @param bytestring string The bytestring to be included in the packet
--- Sends a global Lua packet with the bytestring of `bytestring`. Received with the `HOOK_ON_PACKET_BYTESTRING_RECEIVE` hook.
function network_send_bytestring(reliable, bytestring)
    -- ...
end

--- @param toLocalIndex integer The local index to send the packet to
--- @param reliable boolean Whether or not the game should try to resend the packet in case its lost, good for important packets
--- @param bytestring string The bytestring to be included in the packet
--- Sends a Lua packet with the bytestring of `bytestring` to a specific client through local indices. Received with the `HOOK_ON_PACKET_BYTESTRING_RECEIVE` hook.
function network_send_bytestring_to(toLocalIndex, reliable, bytestring)
    -- ...
end

--- @param textureName string The texture name
--- @return TextureInfo
--- Gets the `TextureInfo` of a texture by name
--- - Note: This also works with vanilla textures
function get_texture_info(textureName)
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
--- @return GraphNode | GraphNodeAnimatedPart | GraphNodeBackground | GraphNodeBillboard | GraphNodeCamera | GraphNodeCullingRadius | GraphNodeDisplayList | GraphNodeGenerated | GraphNodeHeldObject | GraphNodeLevelOfDetail | GraphNodeMasterList | GraphNodeObject | GraphNodeObjectParent | GraphNodeOrthoProjection | GraphNodePerspective | GraphNodeRotation | GraphNodeScale | GraphNodeShadow | GraphNodeStart | GraphNodeSwitchCase | GraphNodeTranslation | GraphNodeTranslationRotation | GraphNodeBone
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
--- @vararg integer | string | Gfx | Texture | Vtx Parameters for the command
--- Sets a display list command on the display list given.
---
--- If `command` includes parameter specifiers (subsequences beginning with `%`), the additional arguments
--- following `command` are converted and inserted in `command` replacing their respective specifiers.
---
--- The number of provided parameters must be equal to the number of specifiers in `command`,
--- and the order of parameters must be the same as the specifiers.
---
--- The following specifiers are allowed:
--- - `%i` for an `integer` parameter
--- - `%s` for a `string` parameter
--- - `%v` for a `Vtx` parameter
--- - `%t` for a `Texture` parameter
--- - `%g` for a `Gfx` parameter
function gfx_set_command(gfx, command, ...)
    -- ...
end

--- @param name string
--- @return Pointer_Gfx
--- @return integer
--- Gets a display list of the current mod from its name.
--- Returns a pointer to the display list and its length
function gfx_get_from_name(name)
    -- ...
end

--- @param name string
--- @return Pointer_Vtx
--- @return integer
--- Gets a vertex buffer of the current mod from its name.
--- Returns a pointer to the vertex buffering and its vertex count
function vtx_get_from_name(name)
    -- ...
end