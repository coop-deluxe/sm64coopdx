-- name: Runtime Surface Examples
-- description: Shows how to create, move, and delete surfaces at runtime. Also shows how to load static object collision and draw debug visuals for surfaces.

local Dbg = require('/lib/dbg')

local moving_surface = nil

local function draw_surface(surface, color, thickness)
    thickness = thickness or 0.5
    Dbg.line(surface.vertex1, surface.vertex2, color, thickness)
    Dbg.line(surface.vertex2, surface.vertex3, color, thickness)
    Dbg.line(surface.vertex3, surface.vertex1, color, thickness)
end

local sSoc = nil
local sObject = nil
local id_bhvSOC = hook_behavior(nil, OBJ_LIST_SURFACE, false,
    function (obj)
        obj.collisionData = gGlobalObjectCollisionData.bbh_seg7_collision_coffin
        sSoc = load_static_object_collision()
    end,
    function (obj)
        if not sSoc then return end
        for i = 1, sSoc.length do
            local surf = get_static_object_surface(sSoc, i)
            if surf then
                draw_surface(surf, Dbg.colors.yellow)
            end
        end
    end
)

hook_event(HOOK_UPDATE, function ()
    local m = gMarioStates[0]
    local pressed = m.controller.buttonPressed

    -- D_JPAD: create a surface at Mario's position
    if (pressed & D_JPAD) ~= 0 then
        local v1 = { x = m.pos.x - 500, y = m.pos.y, z = m.pos.z - 500 }
        local v2 = { x = m.pos.x + 500, y = m.pos.y, z = m.pos.z - 500 }
        local v3 = { x = m.pos.x, y = m.pos.y, z = m.pos.z + 500 }
        moving_surface = smlua_collision_add_surface(false, SURFACE_DEFAULT, v3, v2, v1)
    end

    -- U_JPAD: move the last created surface to Mario's position
    if (pressed & U_JPAD) ~= 0 and moving_surface then
        local v1 = { x = m.pos.x - 500, y = m.pos.y - 100, z = m.pos.z - 500 }
        local v2 = { x = m.pos.x + 500, y = m.pos.y - 100, z = m.pos.z - 500 }
        local v3 = { x = m.pos.x, y = m.pos.y - 100, z = m.pos.z + 500 }
        smlua_collision_move_surface(moving_surface, v3, v2, v1)
    end

    -- L_JPAD: delete the floor
    if (pressed & L_JPAD) ~= 0 and m.floor then
        smlua_collision_delete_surface(m.floor)
    end

    -- R_JPAD: delete the wall
    if (pressed & R_JPAD) ~= 0 and m.wall then
        smlua_collision_delete_surface(m.wall)
    end

    -- X_BUTTON: load static object collision
    if (pressed & X_BUTTON) ~= 0 then
        if sSoc and not ~sSoc then
            remove_static_object_collision(sSoc)
            sSoc = nil
        end
        if sObject then
            sObject.activeFlags = ACTIVE_FLAG_DEACTIVATED
            sObject = nil
        end
        sObject = spawn_non_sync_object(id_bhvSOC, E_MODEL_BBH_WOODEN_TOMB, m.pos.x, m.pos.y, m.pos.z, nil)
    end

    -- draw debug visuals
    if m.floor then
        draw_surface(m.floor, Dbg.colors.blue, 1)
    end
    if m.wall then
        draw_surface(m.wall, Dbg.colors.green, 1)
    end
    if moving_surface and not ~moving_surface then
        draw_surface(moving_surface, Dbg.colors.red)
    end
end)

hook_event(HOOK_ON_HUD_RENDER, function ()
    djui_hud_set_resolution(RESOLUTION_N64)
    djui_hud_set_font(FONT_NORMAL)
    local scale  = 0.25
    local lineH  = 32 * scale
    local x      = 16
    local y      = 32

    local function row(label, desc)
        djui_hud_set_color(0, 0, 0, 255)
        djui_hud_print_text(label, x + 0.4, y + 0.4, scale)
        djui_hud_set_color(255, 220, 60, 255)
        djui_hud_print_text(label, x, y, scale)

        local desc_x = x + djui_hud_measure_text(label) * scale + 8
        djui_hud_set_color(0, 0, 0, 255)
        djui_hud_print_text(desc, desc_x + 0.4, y + 0.4, scale)
        djui_hud_set_color(255, 255, 255, 255)
        djui_hud_print_text(desc, desc_x, y, scale)
        y = y + lineH
    end

    row("D-pad Down: ", "create surface")
    row("D-pad Up:   ", moving_surface and not ~moving_surface and "move surface" or "move surface (none)")
    row("D-pad Left: ", "delete floor")
    row("D-pad Right:", "delete wall")
    row("X:          ", "reload static collision")
end)