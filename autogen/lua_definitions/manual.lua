--------------------------------
-- manually written functions --
--------------------------------

--- @param objFieldTable table<any, "u32"|"s32"|"f32"|table> Table of object field names and types
--- Defines a custom set of overlapping object fields.
--- 
--- - The `fieldTable` table's keys must start with the letter `o` and the values must be either `"u32"`, `"s32"`, `"f32"` or a table with fields `type` and `global`, for example `{ type = "u32", global = true }`.
--- - If, for a field, `global` is `true`, the field will be defined for all mods.
---
--- ### Lua Example
--- ```lua
--- define_custom_obj_fields({
---     oCustomField1 = 'u32',
---     oCustomField2 = 's32',
---     oCustomField3 = 'f32',
---     oCustomField4 = { type = 'u32', global = true },
---     oCustomField5 = { type = 's32', global = true },
---     oCustomField6 = { type = 'f32', global = true },
--- })
--- ```
function define_custom_obj_fields(objFieldTable)
    -- ...
end

--- @param object Object Object to sync
--- @param standardSync boolean Automatically syncs common fields and syncs with distance. If `false`, all syncing must be done with `network_send_object`
--- @param fieldTable table<string> The fields to sync
--- Enables synchronization on an object.
--- 
--- - Setting `standardSync` to `true` will automatically synchronize the object at a rate that is determined based on player distance. The commonly used object fields will be automatically synchronized.
--- - Setting `standardSync` to `false` will not automatically synchronize the object, or add commonly used object fields. The mod must manually call `network_send_object()` when fields have changed.
--- - The `fieldTable` parameter can be `nil`, or a list of object fields.
---
--- ### Lua Example
--- ```lua
--- network_init_object(obj, true, { 'oCustomField1', 'oCustomField2', 'oCustomField3' })
--- ```
function network_init_object(object, standardSync, fieldTable)
    -- ...
end

--- @param object Object Object to sync
--- @param reliable boolean Whether or not the game should try to resend the packet in case it gets lost, good for important packets
--- Sends a packet that synchronizes an object. This does not need to be called when `standardSync` is enabled.
---
--- - The `reliable` field will ensure that the packet arrives, but should be used sparingly and only when missing a packet would cause a desync.
---
--- ### Lua Example
--- ```lua
--- network_send_object(obj, false)
--- ```
function network_send_object(object, reliable)
    -- ...
end

--- @param reliable boolean Whether or not the game should try to resend the packet in case its lost, good for important packets
--- @param dataTable table<string, number|boolean|string|nil> Table of values to be included in the packet
--- Sends a global Lua packet with the values of `dataTable`. Received with the `HOOK_ON_PACKET_RECEIVE` hook.
---
--- - `dataTable` can only contain strings, integers, numbers, booleans, and nil.
--- - The `reliable` field will ensure that the packet arrives, but should be used sparingly and only when missing a packet would cause a desync.
---
--- ### Lua Example
--- ```lua
--- network_send(reliable, { data1 = 'hello', data2 = 10 })
--- ```
function network_send(reliable, dataTable)
    -- ...
end

--- @param toLocalIndex integer The local index to send the packet to
--- @param reliable boolean Whether or not the game should try to resend the packet in case its lost, good for important packets
--- @param dataTable table Table of values to be included in the packet
--- Sends a Lua packet with the values of `dataTable` to a specific client through local indices. Received with the `HOOK_ON_PACKET_RECEIVE` hook.
---
--- - `dataTable` can only contain strings, integers, numbers, booleans, and nil.
--- - The `reliable` field will ensure that the packet arrives, but should be used sparingly and only when missing a packet would cause a desync.
---
--- ### Lua Example
--- ```lua
--- network_send_to(localPlayerIndex, reliable, { data1 = 'hello', data2 = 10 })
--- ```
function network_send_to(toLocalIndex, reliable, dataTable)
    -- ...
end

--- @param reliable boolean Whether or not the game should try to resend the packet in case its lost, good for important packets
--- @param bytestring string The bytestring to be included in the packet
--- Sends a global Lua packet with the bytestring of `bytestring`. Received with the `HOOK_ON_PACKET_BYTESTRING_RECEIVE` hook.
---
--- - The `reliable` field will ensure that the packet arrives, but should be used sparingly and only when missing a packet would cause a desync.
---
--- ### Lua Example
--- ```lua
--- local bytestring = ''
---     -------------- PACKET ID --------------
---     .. string.pack("<B", PACKET_EXAMPLE_ID)
---     ---------------------------------------
---     .. string.pack("<l",  long_param)
---     .. string.pack("<s2", string_param)
---     ---------------------------------------
---
--- network_send_bytestring(reliable, bytestring)
--- ```
function network_send_bytestring(reliable, bytestring)
    -- ...
end

--- @param toLocalIndex integer The local index to send the packet to
--- @param reliable boolean Whether or not the game should try to resend the packet in case its lost, good for important packets
--- @param bytestring string The bytestring to be included in the packet
--- Sends a Lua packet with the bytestring of `bytestring` to a specific client through local indices. Received with the `HOOK_ON_PACKET_BYTESTRING_RECEIVE` hook.
---
--- - The `reliable` field will ensure that the packet arrives, but should be used sparingly and only when missing a packet would cause a desync.
---
--- ### Lua Example
--- ```lua
--- local bytestring = ''
---     -------------- PACKET ID --------------
---     .. string.pack("<B", PACKET_EXAMPLE_ID)
---     ---------------------------------------
---     .. string.pack("<l",  long_param)
---     .. string.pack("<s2", string_param)
---     ---------------------------------------
---
--- network_send_bytestring_to(localPlayerIndex, reliable, bytestring)
--- ```
function network_send_bytestring_to(toLocalIndex, reliable, bytestring)
    -- ...
end

--- @param textureName string The texture name
--- @return TextureInfo
--- Gets the `TextureInfo` of a texture by name.
--- - Note: This also works with vanilla textures.
---
--- ### Lua Example
--- ```lua
--- local texinfo = get_texture_info(textureName)
--- ```
function get_texture_info(textureName)
    -- ...
end

--- @param textureName string The name of the texture
--- @param overrideTexInfo TextureInfo The texture to override with
--- Overrides a texture with a custom `TextureInfo`.
--- - `textureName` must be the codename of a vanilla texture, you can find these in `data/dynos_mgr_builtin_tex.cpp`
--- - `overrideTexInfo` can be any `TextureInfo`
---
--- ### Lua Example
--- ```lua
--- texture_override_set("outside_09004000", overrideTexInfo)
--- ```
function texture_override_set(textureName, overrideTexInfo)
    -- ...
end

--- @param textureName string The name of the texture
--- Resets an overridden texture.
---
--- ### Lua Example
--- ```lua
--- texture_override_reset("outside_09004000")
--- ```
function texture_override_reset(textureName)
    -- ...
end

--- @class BehaviorData
--- @field behavior BehaviorId
--- @field behaviorArg integer

--- @param levelNum LevelNum | integer The level number (ex: `LEVEL_BOB`)
--- @param func fun(areaIndex:number, bhvData:BehaviorData, macroBhvIds:BehaviorId[], macroBhvArgs:integer[]) Function to process parsed data
--- Parses a level script and passes area index, behavior data, macro behavior IDs and macro behavior arguments to a function.
--- When `func` is called, arguments are filled depending on the level command:
--- - `AREA` command: only `areaIndex` is filled. It's a number
--- - `OBJECT` command: only `bhvData` is filled. `bhvData` is a table with nine fields: 'behavior', 'behaviorArg', 'model', 'posX', 'posY', 'posZ', 'pitch', 'yaw' and 'roll'
--- - `MACRO` command: only `macroBhvIds`, `macroBhvArgs` and 'macroBhvModels' are filled. `macroBhvIds` is a list of behavior ids. `macroBhvArgs` is a list of behavior params. 'macroBhvModels' is a list of model ids. All lists have the same size and start at index 0
---
--- ### Lua Example
--- ```lua
--- level_script_parse(LEVEL_BOB, func)
--- ```
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
--- Registers an animation that can be used in objects if `smlua_anim_util_set_animation` is called.
--- 
--- ### Lua Example
--- ```lua
--- smlua_anim_util_register_animation("apparition_idle", 0, 189, 0, 0, 0x5A, values, index)
--- ```
function smlua_anim_util_register_animation(name, flags, animYTransDivisor, startFrame, loopStart, loopEnd, values, index)
    -- ...
end

--- @param message string The message to log
--- @param level? ConsoleMessageLevel Optional; Determines whether the message should appear as info, a warning or an error.
--- Logs a message to the in-game console.
---
--- ### Lua Example
--- ```lua
--- log_to_console("sm64coopdx FTW", CONSOLE_MESSAGE_INFO)
--- ```
function log_to_console(message, level)
    -- ...
end

--- @param index integer The index of the scroll target, should match up with the behavior param of `RM_Scroll_Texture` or `editor_Scroll_Texture`
--- @param name string The name of the vertex buffer that should be used while scrolling the texture
--- Registers a vertex buffer to be used for a scrolling texture. Should be used with `RM_Scroll_Texture` or `editor_Scroll_Texture`.
---
--- ### Lua Example
--- ```lua
--- add_scroll_target(0, "arena_rainbow_dl_StarRoad_mesh_layer_5_vtx_0")
--- ```
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
--- Shoots a raycast from `startX`, `startY`, and `startZ` in the direction of `dirX`, `dirY`, and `dirZ`.
---
--- ### Lua Example
--- ```lua
--- local hit = collision_find_surface_on_ray(0, 0, 0, 50, 100, 50, 3.0)
--- ```
function collision_find_surface_on_ray(startX, startY, startZ, dirX, dirY, dirZ, precision)
    -- ...
end

--- @param contents ExclamationBoxContent[] The exclamation box contents to set
--- Sets the contents that the exclamation box spawns.
--- A single content has 5 keys: `id`, `unused`, `firstByte`, `model`, and `behavior`:
--- - `id`: Required; what value the box's oBehParams2ndByte needs to be to spawn this object.
--- - `unused`: Optional; unused by vanilla.
--- - `firstByte`: Optional; Overrides the 1st byte given to the spawned object.
--- - `model`: Required; The model that the object will spawn with. Uses `ModelExtendedId`.
--- - `behavior`: Required; The behavior ID that the object will spawn with. Uses `BehaviorId`.
---
--- ### Lua Example
--- ```lua
--- set_exclamation_box_contents({
---    {id = 0, unused = 0, firstByte = 0, model = E_MODEL_GOOMBA, behavior = id_bhvGoomba}, -- Uses both optional fields
---    {id = 1, unused = 0, model = E_MODEL_KOOPA_WITH_SHELL, behavior = id_bhvKoopa}, -- Only uses `unused` optional field
---    {id = 2, firstByte = 0, model = E_MODEL_BLACK_BOBOMB, behavior = id_bhvBobomb}, -- Only uses `firstByte` optional field
---    {id = 3, model = E_MODEL_BOO, behavior = id_bhvBoo}, -- Uses no optional fields
--- })
--- ```
function set_exclamation_box_contents(contents)
    -- ...
end

--- @return ExclamationBoxContent[]
--- Gets the contents that the exclamation box spawns.
--- A single content has 5 keys: `id`, `unused`, `firstByte`, `model`, and `behavior`:
--- - `id`: Required; what value the box's oBehParams2ndByte needs to be to spawn this object.
--- - `unused`: Optional; unused by vanilla.
--- - `firstByte`: Optional; Overrides the 1st byte given to the spawned object.
--- - `model`: Required; The model that the object will spawn with. Uses `ModelExtendedId`.
--- - `behavior`: Required; The behavior ID that the object will spawn with. Uses `BehaviorId`.
--- 
--- ### Lua Example
--- ```lua
--- local contents = get_exclamation_box_contents()
--- for index, content in pairs(contents) do -- Enter the main table
---     djui_chat_message_create("Table index " .. index) -- Print the current table index
---     for key, value in pairs(content) do
---        djui_chat_message_create(key .. ": " .. value) -- Print a key-value pair within this subtable
---     end
--- end
--- ```
function get_exclamation_box_contents()
    -- ...
end

--- @param node GraphNode | FnGraphNode A graph node
--- @return GraphNode | GraphNodeAnimatedPart | GraphNodeBackground | GraphNodeBillboard | GraphNodeCamera | GraphNodeCullingRadius | GraphNodeDisplayList | GraphNodeGenerated | GraphNodeHeldObject | GraphNodeLevelOfDetail | GraphNodeMasterList | GraphNodeObject | GraphNodeObjectParent | GraphNodeOrthoProjection | GraphNodePerspective | GraphNodeRotation | GraphNodeScale | GraphNodeShadow | GraphNodeStart | GraphNodeSwitchCase | GraphNodeTranslation | GraphNodeTranslationRotation | GraphNodeBone
--- Returns the specific GraphNode(...) the node is part of.
--- Basically the reverse of `.node` or `.fnNode`.
--- 
--- ### Lua Example
--- ```lua
--- local marioGfx = gMarioStates[0].marioObj.header.gfx -- GraphNodeObject
--- local node = marioGfx.node -- GraphNode
--- 
--- print(marioGfx == cast_graph_node(node)) -- true
--- ```
function cast_graph_node(node)
    -- ...
end

--- @param str string Any string
--- @return string
--- Removes color codes from a string.
---
--- ### Lua Example
--- ```lua
--- print(get_uncolored_string("\\#210059\\Colored \\#FF086F\\String")) -- "Colored String"
--- ```
function get_uncolored_string(str)
    -- ...
end

--- @param gfx Gfx A display list
--- @param command string A display list command
--- @vararg integer | string | Gfx | Texture | Vtx parameters
--- Sets a display list command on the display list given.
---
--- If `command` includes parameter specifiers (subsequences beginning with `%`), the additional arguments following `command` are converted and inserted in `command` replacing their respective specifiers.
---
--- The number of provided parameters must be equal to the number of specifiers in `command`, and the order of parameters must be the same as the specifiers.
---
--- The following specifiers are allowed:
--- - `%i` for an `integer` parameter
--- - `%s` for a `string` parameter
--- - `%v` for a `Vtx` parameter
--- - `%t` for a `Texture` parameter
--- - `%g` for a `Gfx` parameter
---
--- ### Lua Example
---
--- Plain string:
--- ```lua
--- gfx_set_command(gfx, "gsDPSetEnvColor(0x00, 0xFF, 0x00, 0xFF)")
--- ```
---
--- With parameter specifiers:
--- ```lua
--- local r, g, b, a = 0x00, 0xFF, 0x00, 0xFF
--- gfx_set_command(gfx, "gsDPSetEnvColor(%i, %i, %i, %i)", r, g, b, a)
--- ```
function gfx_set_command(gfx, command, ...)
    -- ...
end
