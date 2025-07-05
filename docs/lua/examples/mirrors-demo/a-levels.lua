hook_mod_menu_button("Test mirror room 1", function (index)
    warp_to_level(LEVEL_SL, 1, 1)
end)

hook_mod_menu_button("Test mirror room 2", function (index)
    warp_to_level(LEVEL_SL, 2, 1)
end)

hook_mod_menu_button("Vanilla mirror room", function (index)
    warp_to_warpnode(LEVEL_CASTLE, 2, 1, 0x68)
end)
