if not dynamicHudAPI then return end

function setup_recolor_icons()
    local FEATURE = dynamicHudAPI.FEATURE
    local NONE = dynamicHudAPI.NONE
    dynamicHudAPI.add_head_for_cs(CT_TOADETTE, nil, get_texture_info("recolor_icon_toadette"),
        { SKIN, CAP, GLOVES, FEATURE, NONE, NONE },
        { SKIN, NONE, NONE, FEATURE, NONE, HAIR },
        nil, nil, {metal_sheet_x = 5, metal_capless_sheet_x = 7} -- legacy
    )
    dynamicHudAPI.add_head_for_cs(CT_PEACH, nil, get_texture_info("recolor_icon_peach"),
        { SKIN, HAIR, CAP, FEATURE, SHOES, FEATURE },
        { SKIN, HAIR, NONE, FEATURE, SHOES, NONE },
        nil, nil, {metal_sheet_x = 5, metal_capless_sheet_x = 7} -- legacy
    )
    dynamicHudAPI.add_head_for_cs(CT_DAISY, nil, get_texture_info("recolor_icon_daisy"),
        { SKIN, GLOVES, CAP, FEATURE, FEATURE, SHOES, HAIR },
        { SKIN, GLOVES, NONE, FEATURE, NONE, SHOES, HAIR }
    )
    dynamicHudAPI.add_head_for_cs(CT_YOSHI, nil, get_texture_info("recolor_icon_yoshi"),
        { GLOVES, HAIR, CAP, FEATURE, NONE, NONE},
        { GLOVES, HAIR, CAP, FEATURE, NONE, FEATURE}
    )
    dynamicHudAPI.add_head_for_cs(CT_BIRDO, nil, get_texture_info("recolor_icon_birdo"),
        { NONE, PANTS, CAP, FEATURE, NONE, NONE},
        { NONE, NONE, CAP, FEATURE, NONE, NONE}
    )
    dynamicHudAPI.add_head_for_cs(CT_FOREMANSPIKE, nil, get_texture_info("recolor_icon_foremanspike"),
        { SKIN, HAIR, CAP, HAIR, EMBLEM, NONE, NONE},
        { SKIN, HAIR, NONE, NONE, NONE, HAIR, FEATURE}
    )
    dynamicHudAPI.add_head_for_cs(CT_PAULINE, nil, get_texture_info("recolor_icon_pauline"),
        { SKIN, HAIR, CAP, FEATURE, EMBLEM, NONE},
        { SKIN, NONE, NONE, FEATURE, EMBLEM, HAIR}
    )
    dynamicHudAPI.add_head_for_cs(CT_ROSALINA, nil, get_texture_info("recolor_icon_rosalina"),
        { SKIN, HAIR, CAP, FEATURE, EMBLEM, FEATURE},
        { SKIN, HAIR, NONE, FEATURE, EMBLEM, NONE}
    )
    -- Wapeach: the skin on the icon appears darker with the default palette than the normal icon- not sure if this should be adjusted
    dynamicHudAPI.add_head_for_cs(CT_WAPEACH, nil, get_texture_info("recolor_icon_wapeach"),
        { SKIN, HAIR, CAP, FEATURE, SHIRT, FEATURE},
        { SKIN, HAIR, NONE, FEATURE, SHIRT, NONE}
    )
    dynamicHudAPI.add_head_for_cs(CT_DONKEY_KONG, nil, get_texture_info("recolor_icon_dk"),
        { SKIN, NONE, CAP, FEATURE, NONE, NONE},
        { SKIN, NONE, CAP, FEATURE, NONE, FEATURE}
    )
    dynamicHudAPI.add_head_for_cs(CT_SONIC, nil, get_texture_info("recolor_icon_segasonic"),
        { SKIN, PANTS, CAP, FEATURE, EMBLEM, NONE},
        { SKIN, PANTS, CAP, FEATURE, EMBLEM, FEATURE}
    )
end

hook_event(HOOK_ON_MODS_LOADED, setup_recolor_icons)