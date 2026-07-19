-----------
-- hooks --
-----------

--- @param behaviorId BehaviorId | integer?  The behavior id of the object to modify. Pass in as `nil` to create a custom object
--- @param objectList ObjectList | integer | nil Object list. Pass in as `nil` to use the vanilla object list or the already assigned object list in case of multiple hooks
--- @param replaceBehavior boolean Whether or not to completely replace the behavior (ignored for non-vanilla behaviors, which are always replaced)
--- @param initFunction? fun(obj:Object) Run on object creation
--- @param loopFunction? fun(obj:Object) Run every frame
--- @param behaviorName? string Optional, name to give to the behavior to be able to retrieve it with `get_id_from_behavior_name`
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
--- @param func fun(...: any): any?, any? The function to run
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
