## [:rewind: Lua Reference](../lua.md)

# The Mod Menu

The mod menu is a panel in DJUI dedicated to your mod. It can be used for configuring your mod, and has a variety of elements to use.

## Using the Mod Menu

### Hooking elements

For each element, the mod menu contains functions to add an element. All `hook_mod_menu_x` functions are for creating elements.

A list of these functions, along with example usages, can be found in [the hooks documentation](hooks.md#hook_mod_menu_text).

As a general rule, each of these functions have the name of the elements, the options in the middle are params required for the specific element, and the last argument is an optional panel ID, which will be explained later. They return an index to the hooked element, which can be used for updating elements.

### Updating elements

Updating elements can be accomplished with the `update_mod_menu_x` functions. A list of these functions along with example usages can be found in the [hooks documentation](hooks.md#update_mod_menu_element_name).

As a general rule, each of these functions take in an index returned by the appropriate `hook_mod_menu_x` function. It then takes in the appropriate params for that element.

### Pushing and popping panels

For each element created, a panel ID may be specified. A blank panel id is the root panel. When passing in a panel ID during creation of a element, it links that element to that panel.

To navigate to a submenu, or "push" a panel, you can use the `mod_menu_push_panel` function. This function takes in a `panelID`, and optionally `headerText` and `hideBackButton` arguments.

By default, the header text is the name of your mod, and the back button is shown. In the event you hide the back button to replace it for say a Cancel button, you'll want a way to go back a panel, or "pop" the panel. Use `mod_menu_pop_panel` to pop the last opened panel.

As an example, we can create a button to reset all saved data. When pressed, we can go to a warning page asking the user if they really want to do the action:

```lua
local PANEL_RESET_SAVE_DATA_ALERT = "panel_reset_save_data_alert"

-- create button to reset save data, which goes into an alert view
hook_mod_menu_button("Reset Save Data", function (index)
    mod_menu_push_panel(PANEL_RESET_SAVE_DATA_ALERT, "RESET SAVE DATA", true)
end)

-- create text and buttons that goes into the reset save data panel
hook_mod_menu_text("Are you sure you want to reset your save data?", PANEL_RESET_SAVE_DATA_ALERT)

hook_mod_menu_button("Yes", function (index)
    djui_popup_create("Your save file has been erased", 2)
    mod_menu_pop_panel() -- go back to the previous panel
end, PANEL_RESET_SAVE_DATA_ALERT)

hook_mod_menu_button("No", function (index)
    mod_menu_pop_panel() -- go back to the previous panel
end, PANEL_RESET_SAVE_DATA_ALERT)
```

## Limitations

- Not all updates done on an element will be reflected instantly in the mod menu
- Currently, you cannot remove a mod menu element. Part of the reason for this is due to elements being unable to instantly be reflected.
