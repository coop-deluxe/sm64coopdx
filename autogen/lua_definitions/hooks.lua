-----------
-- hooks --
-----------

--- @param behaviorId BehaviorId | integer | nil The behavior id of the object to modify. Pass in as `nil` to create a custom object
--- @param objectList ObjectList | integer | nil Object list. Pass in as `nil` to use the vanilla object list or the already assigned object list in case of multiple hooks
--- @param replaceBehavior boolean Whether or not to completely replace the behavior (ignored for non-vanilla behaviors, which are always replaced)
--- @param initFunction? fun(obj:Object) Run on object creation
--- @param loopFunction? fun(obj:Object) Run every frame
--- @param behaviorName? string Optional, name to give to the behavior to be able to retrieve it with `get_id_from_behavior_name`
--- @return BehaviorId
--- Allows Lua mods to override existing behaviors or create new ones.
---
--- ### Lua Example
--- 
--- ```lua
--- function bhv_example_init(obj)
---     obj.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
---     network_init_object(obj, true, nil)
--- end
--- 
--- function bhv_example_loop(obj)
---     obj.oPosY = obj.oPosY + 1
--- end
--- 
--- id_bhvExample = hook_behavior(nil, OBJ_LIST_DEFAULT, true, bhv_example_init, bhv_example_loop, "bhvExample")
--- ```
function hook_behavior(behaviorId, objectList, replaceBehavior, initFunction, loopFunction, behaviorName)
    -- ...
end

--- @param command string The command to run. Should be easy to type
--- @param description string Should describe what the command does and how to use it
--- @param func fun(msg:string): boolean Run upon activating the command. Return `true` to confirm the command has succeeded
--- Allows Lua mods to react and respond to chat commands.
---
--- - To execute a chat command, type `/` followed by the command name.
--- - The function the mod passes to the hook should return `true` when the command is valid and `false` otherwise.
---
--- ### Lua Example
--- 
--- ```lua
--- function on_test_command(msg)
---     if msg == "on" then
---         djui_chat_message_create("Test: enabled")
---         return true
---     elseif msg == "off" then
---         djui_chat_message_create("Test: disabled")
---         return true
---     end
---     return false
--- end
--- 
--- hook_chat_command("test", "[on|off] turn test on or off", on_test_command)
--- ```
function hook_chat_command(command, description, func)
    -- ...
end

--- @param command string The command to change the description of
--- @param description string The description to change to
--- Updates the description of a chat command.
--- 
--- ### Lua Example
--- ```lua
--- update_chat_command_description("command", "description")
--- ```
function update_chat_command_description(command, description)
    -- ...
end

--- @param command string The command to run. Should be easy to type
--- @param description string Should describe what the command does and how to use it
--- @param func fun(msg:string): boolean Run upon activating the command. Return `true` to confirm the command has succeeded
--- Allows Lua mods to react and respond to console commands. The function the mod passes to the hook should return `true` when the command was valid and `false` otherwise. You should use `command_message_create` to show any messages to the user. Console messages only appear in the console and terminal.
---
--- ### Lua Example
--- 
--- ```lua
--- function on_test_command(msg)
---     if msg == "on" then
---         command_message_create("Test: enabled")
---         return true
---     elseif msg == "off" then
---         command_message_create("Test: disabled")
---         return true
---     end
---     return false
--- end
--- 
--- hook_console_command("test", "[on|off] turn test on or off", on_test_command)
--- ```
function hook_console_command(command, description, func)
    -- ...
end

--- @param command string The command to change the description of
--- @param description string The description to change to
--- Updates the description of a console command.
--- 
--- ### Lua Example
--- ```lua
--- update_console_command_description("command", "description")
--- ```
function update_console_command_description(command, description)
    -- ...
end

--- @param hookEventType LuaHookedEventType When a function should run
--- @param func fun(...: any): any?, any? The function to run
--- Assigns a callback function to a game hook [event](hook-events.md#Hook-Event-Types). This function will be automatically called by the game when this kind of event occurs.
---
--- ### Lua Example
--- The following example will print out a message 16 times per frame (once for every possible player).
--- ```lua
--- function mario_update(m)
---     print("Mario update was called for player index ", m.playerIndex)
--- end
--- 
--- hook_event(HOOK_MARIO_UPDATE, mario_update)
--- ```
function hook_event(hookEventType, func)
    -- ...
end

--- @class ActionTable
--- @field every_frame fun(m:MarioState):integer?
--- @field gravity fun(m:MarioState):integer?

--- @param actionId integer The action to replace
--- @param funcOrFuncTable fun(m:MarioState):integer? | ActionTable Action function or table with entries for action hooks
--- @param interactionType? InteractionFlag Optional; The flag that determines how the action interacts with other objects
--- Allows Lua mods to create new actions or override existing ones.
--- If a function table is used, it must be in the form of `{ action_hook = [func], ... }`.
--- Possible `action_hook`s include:
--- - `every_frame`: Main action code, called once per frame. Returns `true` if action cancelled, else `false`
--- - `gravity`: Called inside `apply_gravity` when in action
--- 
--- ### Lua Example
--- 
--- ```lua
--- ACT_WALL_SLIDE = (0x0BF | ACT_FLAG_AIR | ACT_FLAG_MOVING | ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION)
--- 
--- function act_wall_slide(m)
---     if (m.input & INPUT_A_PRESSED) ~= 0 then
---         local rc = set_mario_action(m, ACT_TRIPLE_JUMP, 0)
---         m.vel.y = 72.0
---         if m.forwardVel < 20.0 then
---             m.forwardVel = 20.0
---         end
---         m.wallKickTimer = 0
---         return rc
---     end
--- 
---     -- attempt to stick to the wall a bit. if it's 0, sometimes you'll get kicked off of slightly sloped walls
---     mario_set_forward_vel(m, -1.0)
--- 
---     m.particleFlags = m.particleFlags | PARTICLE_DUST
--- 
---     play_sound(SOUND_MOVING_TERRAIN_SLIDE + m.terrainSoundAddend, m.marioObj.header.gfx.cameraToObject)
---     set_mario_animation(m, MARIO_ANIM_START_WALLKICK)
--- 
---     if perform_air_step(m, 0) == AIR_STEP_LANDED then
---         mario_set_forward_vel(m, 0.0)
---         if check_fall_damage_or_get_stuck(m, ACT_HARD_BACKWARD_GROUND_KB) == 0 then
---             return set_mario_action(m, ACT_FREEFALL_LAND, 0)
---         end
---     end
--- 
---     m.actionTimer = m.actionTimer + 1
---     if m.wall == nil and m.actionTimer > 2 then
---         mario_set_forward_vel(m, 0.0)
---         return set_mario_action(m, ACT_FREEFALL, 0)
---     end
--- 
---     return 0
--- end
--- 
--- function act_wall_slide_gravity(m)
---     m.vel.y = m.vel.y - 2
--- 
---     if m.vel.y < -15 then
---         m.vel.y = -15
---     end
--- end
--- 
--- function mario_on_set_action(m)
---     -- wall slide
---     if m.action == ACT_SOFT_BONK then
---         m.faceAngle.y = m.faceAngle.y + 0x8000
---         set_mario_action(m, ACT_WALL_SLIDE, 0)
---     end
--- end
--- 
--- hook_event(HOOK_ON_SET_MARIO_ACTION, mario_on_set_action)
--- hook_mario_action(ACT_WALL_SLIDE, { every_frame = act_wall_slide, gravity = act_wall_slide_gravity } )
--- ```
function hook_mario_action(actionId, funcOrFuncTable, interactionType)
    -- ...
end

--- @param syncTable SyncTable Must be the gGlobalSyncTable or gPlayerSyncTable[] or one of their child tables
--- @param field string Field name
--- @param tag any An additional parameter
--- @param func fun(tag:any, oldVal:any, newVal:any) Run when the specified field has been changed
--- Allows Lua mods to react to sync table changes.
--- - `syncTable` parameter must be a sync table, e.g. [gGlobalSyncTable](../globals.md#gGlobalSyncTable), [gPlayerSyncTable[]](../globals.md#gPlayerSyncTable), or one of their child tables.
--- - `field` parameter must be one of the fields in the `SyncTable`.
--- - `tag` parameter can be any type, and is automatically passed to the callback.
--- - `func` parameter must be a function with three parameters: `tag`, `oldVal`, and `newVal`.
---   - `tag` will be the same `tag` passed into `hook_on_sync_table_change()`.
---   - `oldVal` will be the value before it was set.
---   - `newVal` will be the value that it was set to.
--- 
--- ### Lua Example
--- 
--- ```lua
--- function on_testing_field_changed(tag, oldVal, newVal)
---     print("testingField changed:", tag, ",", oldVal, "->", newVal)
--- end
--- 
--- hook_on_sync_table_change(gGlobalSyncTable, "testingField", "tag", on_testing_field_changed)
--- 
--- -- now, when testingField is set, either locally or over the network on_testing_field_changed() will be called
--- gGlobalSyncTable.testingField = "hello"
--- ```
function hook_on_sync_table_change(syncTable, field, tag, func)
    -- ...
end

--- @param message string The message for the text to show
--- @return integer
--- Allows Lua to add text labels to their designated mod menu submenu.
--- 
--- ### Lua Example
--- 
--- ```lua
--- indexText = hook_mod_menu_text("Rise and shine, Mr. Freeman.")
--- ```
function hook_mod_menu_text(message)
    -- ...
end

--- @param name string The text to show on the button
--- @param func fun(index:integer) The function that is called when the button is pressed
--- @return integer
--- Allows Lua to add buttons to their designated mod menu submenu.
--- 
--- ### Lua Example
--- 
--- ```lua
--- local menu1Open = false
--- local menu2Open = false
--- 
--- --- @param index integer
--- local function on_open_menu(index)
---     if index == indexButton1 then
---         menu1Open = true
---         menu2Open = false
---     elseif index == indexButton2 then
---         menu1Open = false
---         menu2Open = true
---     end
--- end
--- 
--- -- you can always do separate functions too!
--- indexButton1 = hook_mod_menu_button("Open Menu 1", on_open_menu)
--- indexButton2 = hook_mod_menu_button("Open Menu 2", on_open_menu)
--- ```
function hook_mod_menu_button(name, func)
    -- ...
end

--- @param name string The text to show on the left
--- @param defaultValue boolean The default state of the checkbox
--- @param func fun(index:integer, value:boolean) The function that is called when the checkbox is changed
--- @return integer
--- Allows Lua to add checkboxes to their designated mod menu submenu.
--- 
--- ### Lua Example
--- 
--- ```lua
--- local flyMode = false
--- local noclipMode = false
--- 
--- --- @param index integer
--- --- @param value boolean
--- local function on_set_player_mode(index, value)
---     if index == indexCheckbox1 then
---         flyMode = value
---     elseif index == indexCheckbox2 then
---         noclipMode = value
---     end
--- end
--- 
--- -- you can always do separate functions too!
--- indexCheckbox1 = hook_mod_menu_checkbox("Fly Mode", false, on_set_player_mode)
--- indexCheckbox2 = hook_mod_menu_checkbox("Noclip Mode", false, on_set_player_mode)
--- ```
function hook_mod_menu_checkbox(name, defaultValue, func)
    -- ...
end

--- @param name string The text to show on the left
--- @param defaultValue integer The default value of the slider
--- @param min integer The lowest the slider can go
--- @param max integer The highest the slider can go
--- @param func fun(index:integer, value:integer) The function that is called when the value of the slider changes
--- @return integer
--- Allows Lua to add sliders to their designated mod menu submenu.
--- 
--- ### Lua Example
--- 
--- ```lua
--- local timeScale = 0.0
--- 
--- local function on_set_time_scale(index, value)
---     timeScale = value
--- end
--- 
--- indexSlider = hook_mod_menu_slider("Time Scale", 1, 0, 10, on_set_time_scale)
--- ```
function hook_mod_menu_slider(name, defaultValue, min, max, func)
    -- ...
end

--- @param name string The text to show on the left
--- @param defaultValue string The default text in the inputbox
--- @param stringLength integer The max length of the inputbox
--- @param func fun(index:integer, value:string) The function that is called when the value of the inputbox changes
--- @return integer
--- Allows Lua to add textboxes to their designated mod menu submenu.
--- 
--- ### Lua Example
--- 
--- ```lua
--- --- @param index integer
--- --- @param value string
--- local function on_set_network_player_description(index, value)
---     network_player_set_description(gNetworkPlayers[0], value, 255, 255, 255, 255)
--- end
--- 
--- indexInputbox = hook_mod_menu_inputbox("Network Player Description", "", 100, on_set_network_player_description)
--- ```
function hook_mod_menu_inputbox(name, defaultValue, stringLength, func)
    -- ...
end

--- @param index integer The index of the element returned by `hook_mod_menu` functions
--- @param name string The name to change to
--- Updates a mod menu element's name.
--- 
--- ### Lua Example
---
--- ```lua
--- update_mod_menu_element_name(index, "new name")
--- ```
function update_mod_menu_element_name(index, name)
    -- ...
end

--- @param index integer The index of the element returned by `hook_mod_menu_checkbox`
--- @param value boolean The boolean value to change to
--- Updates a mod menu checkbox element's boolean value.
--- 
--- ### Lua Example
---
--- ```lua
--- update_mod_menu_element_checkbox(indexCheckbox, booleanValue)
--- ```
function update_mod_menu_element_checkbox(index, value)
    -- ...
end

--- @param index integer The index of the element returned by `hook_mod_menu_slider`
--- @param value number The number value to change to
--- Updates a mod menu slider element's numerical value.
--- 
--- ### Lua Example
---
--- ```lua
--- update_mod_menu_element_slider(indexSlider, numberValue)
--- ```
function update_mod_menu_element_slider(index, value)
    -- ...
end

--- @param index integer The index of the element returned by `hook_mod_menu_inputbox`
--- @param value string The text to change to
--- Updates a mod menu inputbox element's string value.
--- 
--- ### Lua Example
---
--- ```lua
--- update_mod_menu_element_inputbox(indexInputbox, stringValue)
--- ```
function update_mod_menu_element_inputbox(index, value)
    -- ...
end
