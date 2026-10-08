## [:rewind: Lua Reference](../lua.md)

# Input Utilities

`Input Utilities` is a group of utils that allows you to grab and use certain raw user inputs that you usually wouldn't be able to using normal Super Mario 64 APIs.

## Globals

There are 2 arrays to keep in mind for accessing user input.

### `gGamepads`

An array of [`Gamepad`](../structs.md#gamepad) structs from 0-`MAX_GAMEPADS` each containing that specific controller's values. Use along with `smlua_input_util_get_current_gamepad()` to get the current user's controller.

### `gKeyboard`

An array of [`Key`](../structs.md#key) structs from 0-`SDL_SCANCODE_COUNT` each containing whether that specific key was just pressed, released, or is held down. Don't use this for typing except for modifiers or shortcuts, that will be explained below.

## Functions

This also includes a couple of functions that help you get user text and which controller they're using:

### [`smlua_input_util_get_current_gamepad()`](../functions-7.md#smlua_input_util_get_current_gamepad)

Gets the index of the current gamepad the player is using. Returns `MAX_GAMEPADS` if the controller is a joystick or if they aren't using one. For more info check the out [difference between SDL Game Controllers and SDL Joysticks.](#gamepad-vs-joystick)

### [`smlua_input_util_start_text_input()`](../functions-7.md#smlua_input_util_start_text_input)

Starts mod text input and grabs focus away from other input shortcuts of built-in menus. Must be run once for `HOOK_ON_TEXT_INPUT` and `HOOK_ON_TEXT_EDITING` to pickup user text input.

### [`smlua_input_util_stop_text_input()`](../functions-7.md#smlua_input_util_stop_text_input)

Stops mod text input and loses focus letting you access other input shortcuts of built-in menus. Run once after you grab all the text you need from `HOOK_ON_TEXT_INPUT` and `HOOK_ON_TEXT_EDITING` to restore normal input.

### [`smlua_input_util_text_input_active()`](../functions-7.md#smlua_input_util_text_input_active)

Checks if mod text input is currently active and returns `true`, otherwise it returns `false`. Use to check focus for your custom text fields. 

## Hooks

This system also offers text input in the form of two hooks.

### `HOOK_ON_TEXT_INPUT`

This hook receives the actual text the user is typing regardless of the keyboard layout. It has one parameter which is the text parameter containing the last character the user has typed. Store it in a buffer to construct a string.<br>
You MUST call [`smlua_input_util_start_text_input()`](#smlua_input_util_start_text_input) beforehand to receive input and [`smlua_input_util_stop_text_input()`](#smlua_input_util_stop_text_input) after grabbing all the text you need to restore normal input.

**Example Usage**

```lua
local stringBuffer = ""

--- @param text string
function on_text_input(text)
    stringBuffer = stringBuffer .. text -- Concatenates text into string buffer
    print(stringBuffer) -- Prints the entire string you just typed
end

hook_event(HOOK_ON_TEXT_INPUT, on_text_input)
```

### `HOOK_ON_TEXT_EDITING`
This hooks receives IME compositions and gives you the starting point of the edit and the string being edited. It has 2 parameters, `text` which is the substring currently being composed/edited, and `start` which is the position at which the edit is starting.<br>
Just like `HOOK_ON_TEXT_INPUT`, you MUST call [`smlua_input_util_start_text_input()`](#smlua_input_util_start_text_input) beforehand to receive input and [`smlua_input_util_stop_text_input()`](#smlua_input_util_stop_text_input) after grabbing all the text you need to restore normal input.

**Example Usage**

```lua
--- @param text string
--- @param start integer
function on_text_editing(text, start)
    print(text, start) -- Prints the section being edited and the start position of the edit
end

hook_event(HOOK_ON_TEXT_EDITING, on_text_editing)
```

## Gamepad VS Joystick

The difference between and SDL Gamepad and SDL Joystick isn't that difficult to understand.

### Gamepad

An SDL Gamepad is a controller that is mapped to the standardized SDL gamepad input system meaning that the gamepad inputs correspond to the same standard inputs in a way that makes sense for us through SDL. This makes reading its inputs less confusing and more consistent on a universal scale.

### Joystick

An SDL Joystick on the other hand is a controller that is NOT mapped to that standardized system meaning the commands/inputs that the controller sends aren't understood by us in a way that makes sense, this can be like the physical right joystick on the controller actually being the left joystick or vice versa, or even buttons and dpad inputs being mixed around or straight up not working sometimes.

### What's the point?

This makes using joysticks and registering them in a way that makes sense a hassle or unreasonable. However that doesn't mean that if a controller is a joystick that you can't use it.<br>
Basically a gamepad is a mapped joystick meaning that a joystick isn't actually doomed as long as you map it beforehand into a gamepad mapping file using the SDL Controller Mapping tool. You then insert that file into the `databases` folder in your temporary or permanent directories with the extension `.db` and then the game can read that mapping.<br>
When that's done, your joystick is no longer a joystick and the game can read its inputs as a standardized Gamepad, allowing you to use these modding features in your mods or play mods that use said features.