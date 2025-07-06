-----------------
-- Dbg Library --
-----------------

---------------------------------------------------------------------
--
--    A tiny, immediate-mode debug-drawing library for Lua that
--    lets you quickly visualize things in your game world or on
--    the HUD.
--
--    Use the following functions at any time:
--       Dbg.point(pos, color, size)          to draw 3D points
--       Dbg.line(a, b, color, thickness)     to draw 3D lines
--       Dbg.text(str, pos, color, scale)     for world-space labels
--
--    The rendered points/lines/text automatically disappear on the
--    next frame unless you set Dbg.clear_automatically to false
--
--    Credits for the original line rendering code go to Isaac
--
---------------------------------------------------------------------

---@class Dbg
local Dbg = {
    clear_automatically = true,
    alter_position_function = nil
}

Dbg.colors = {
    red     = { 1, 0, 0 },
    green   = { 0, 1, 0 },
    blue    = { 0, 0, 1 },

    cyan    = { 0, 1, 1 },
    magenta = { 1, 0, 1 },
    yellow  = { 1, 1, 0 },

    white   = { 1, 1, 1 },
    grey    = { 0.2, 0.2, 0.2 },
    black   = { 0, 0, 0 },
}

Dbg.htext = nil

---------------------------------------------------------------------
-- FRAME-LOCAL BUFFERS (auto-cleared each world_step)
---------------------------------------------------------------------
local _debug_points      = { points = {}, count = 0 }
local _debug_lines       = { lines  = {}, count = 0 }
local _debug_texts       = { texts  = {}, count = 0 }
local _debug_game_tick   = 0

local function point_new()
    return {
        position = { 0, 0, 0 },
        color    = { 0, 0, 0 },
        scale    = 1
    }
end

local function line_new()
    return {
        p1        = { 0, 0, 0 },
        p2        = { 0, 0, 0 },
        color     = { 0, 0, 0 },
        thickness = 1
    }
end

local function text_new()
    return {
        string = '',
        position = { 0, 0, 0 },
        color    = { 0, 0, 0 },
        scale    = 1
    }
end

local function clear_check()
    if not Dbg.clear_automatically then return end

    local tick = get_global_timer()
    if _debug_game_tick ~= tick then
        _debug_game_tick = tick
        Dbg.clear()
    end

end

---------------------------------------------------------------------
-- LINES - CLIPPING
---------------------------------------------------------------------

local tmp_out1 = { x = 0, y = 0, z = 0}
local tmp_out2 = { x = 0, y = 0, z = 0}

-- scratch buffers (create once, reuse every call)
local low_pt    = { 0, 0, 0 }
local high_pt   = { 0, 0, 0 }
local mid_pt    = { 0, 0, 0 }
local screen    = { x=0, y=0, z=0 }
local tmp_world = { x=0, y=0, z=0 }

local MAX_ITERS = 8   -- tweak for precision vs cost

--- try to clip the line so that it fits in the camera
local function clip_segment_against_camera(out_a, out_b, p1, p2)
    -- test both endpoints
    tmp_world.x, tmp_world.y, tmp_world.z = p1[1], p1[2], p1[3]
    djui_hud_world_pos_to_screen_pos(tmp_world, screen)
    local ok1 = screen.z < -260

    tmp_world.x, tmp_world.y, tmp_world.z = p2[1], p2[2], p2[3]
    djui_hud_world_pos_to_screen_pos(tmp_world, screen)
    local ok2 = screen.z < -260

    -- trivial accept / reject
    if ok1 and ok2 then
        out_a[1], out_a[2], out_a[3] = p1[1], p1[2], p1[3]
        out_b[1], out_b[2], out_b[3] = p2[1], p2[2], p2[3]
        return true
    end
    if not ok1 and not ok2 then
        return false
    end

    -- decide which end is inside, which is outside
    local inside, outside
    local p1Inside = ok1
    if p1Inside then
        inside, outside = p1, p2
    else
        inside, outside = p2, p1
    end

    -- seed the binary-search bracket
    low_pt[1], low_pt[2], low_pt[3] = inside[1], inside[2], inside[3]
    high_pt[1], high_pt[2], high_pt[3] = outside[1], outside[2], outside[3]

    -- binary-search edge of the frustum in MAX_ITERS steps
    for i = 1, MAX_ITERS do
        mid_pt[1], mid_pt[2], mid_pt[3] =
            low_pt[1] + (high_pt[1] - low_pt[1]) * 0.5,
            low_pt[2] + (high_pt[2] - low_pt[2]) * 0.5,
            low_pt[3] + (high_pt[3] - low_pt[3]) * 0.5

        -- test mid_pt
        tmp_world.x, tmp_world.y, tmp_world.z = mid_pt[1], mid_pt[2], mid_pt[3]
        djui_hud_world_pos_to_screen_pos(tmp_world, screen)
        if screen.z < -260 then
            -- mid is still in front -> push low_pt up
            low_pt[1], low_pt[2], low_pt[3] = mid_pt[1], mid_pt[2], mid_pt[3]
        else
            -- mid went behind -> pull high_pt down
            high_pt[1], high_pt[2], high_pt[3] = mid_pt[1], mid_pt[2], mid_pt[3]
        end
    end

    -- assign outputs in the original p1->p2 order
    if p1Inside then
        -- segment is p1 (inside) -> boundary near p2
        out_a[1], out_a[2], out_a[3] = p1[1], p1[2], p1[3]
        out_b[1], out_b[2], out_b[3] = low_pt[1], low_pt[2], low_pt[3]
    else
        -- segment is boundary near p1 -> p2 (inside)
        out_a[1], out_a[2], out_a[3] = low_pt[1], low_pt[2], low_pt[3]
        out_b[1], out_b[2], out_b[3] = p2[1], p2[2], p2[3]
    end

    return true
end

---------------------------------------------------------------------
-- RENDER: LINES
---------------------------------------------------------------------

local function render_debug_lines()
    local cam = (gMarioStates[0].area or {}).camera
    if not cam then return end
    djui_hud_set_resolution(RESOLUTION_N64)     -- use default pixel grid

    for i = 1, _debug_lines.count do
        local l = _debug_lines.lines[i]
        local c = l.color
        djui_hud_set_color(c[1]*255, c[2]*255, c[3]*255, c[4] and c[4]*255 or 255)

        if not clip_segment_against_camera(tmp_out1, tmp_out2, l.p1, l.p2) then
            goto continue
        end

        djui_hud_world_pos_to_screen_pos({ x = tmp_out1[1], y = tmp_out1[2], z = tmp_out1[3] }, screen)
        local s1x, s1y = screen.x, screen.y

        djui_hud_world_pos_to_screen_pos({ x = tmp_out2[1], y = tmp_out2[2], z = tmp_out2[3] }, screen)
        local s2x, s2y = screen.x, screen.y

        if s1x and s2x then
            local dx, dy = s2x - s1x, s2y - s1y
            local angle  = atan2s(dy, dx) - 0x4000   -- rotate by -90 degree for Djui rects
            local len    = math.sqrt(dx * dx + dy * dy)
            djui_hud_set_rotation(angle, 0, 0.5)
            djui_hud_render_rect(s1x, s1y, len, l.thickness * 0.5)
        end
        ::continue::
    end
end

---------------------------------------------------------------------
-- RENDER: POINT ICONS
---------------------------------------------------------------------

local tmp_pos_in = { x = 0, y = 0, z = 0 }

local function render_debug_points()
    djui_hud_set_resolution(RESOLUTION_N64)     -- use default pixel grid

    tmp_out1.x, tmp_out1.y, tmp_out1.z = 0, 0, 0

    for i = 1, _debug_points.count do
        local p = _debug_points.points[i]
        tmp_pos_in.x, tmp_pos_in.y, tmp_pos_in.z = p.position[1], p.position[2], p.position[3]
        djui_hud_world_pos_to_screen_pos(tmp_pos_in, tmp_out1)
        if tmp_out1.z <= -260 then                   -- clip very near points
            local c = p.color

            local scale = p.scale * 2
            local x, y = tmp_out1.x - scale * 0.5, tmp_out1.y - scale * 0.5
            local padding = 0.3

            djui_hud_set_color(0, 0, 0, c[4] and c[4]*200 or 200)
            djui_hud_render_rect(x - padding, y - padding, scale + padding * 2, scale + padding * 2)

            djui_hud_set_color(c[1] * 255, c[2] * 255, c[3] * 255, c[4] and c[4]*255 or 255)
            djui_hud_render_rect(x, y, scale, scale)
        end
    end
end

---------------------------------------------------------------------
-- RENDER: TEXTS
---------------------------------------------------------------------

local function render_debug_texts()
    djui_hud_set_resolution(RESOLUTION_N64)     -- use default pixel grid

    tmp_out1.x, tmp_out1.y, tmp_out1.z = 0, 0, 0

    for i = 1, _debug_texts.count do
        local t = _debug_texts.texts[i]
        tmp_pos_in.x, tmp_pos_in.y, tmp_pos_in.z = t.position[1], t.position[2], t.position[3]
        djui_hud_world_pos_to_screen_pos(tmp_pos_in, tmp_out1)
        if tmp_out1.z <= -260 then                   -- clip very near points
            local c = t.color
            djui_hud_set_font(FONT_ALIASED)
            djui_hud_set_color(0, 0, 0, c[4] and c[4] * 200 or 200)
            djui_hud_print_text(t.string, tmp_out1.x + 0.4, tmp_out1.y + 0.4, t.scale * 0.3)
            djui_hud_set_color(c[1] * 255, c[2] * 255, c[3] * 255, c[4] and c[4] * 255 or 255)
            djui_hud_print_text(t.string, tmp_out1.x, tmp_out1.y, t.scale * 0.3)
        end
    end
end


---------------------------------------------------------------------
-- RENDER: DEBUG TEXT
---------------------------------------------------------------------

local function render_debug_text()
    -- set text and scale
    local text = Dbg.htext
    local scale = 1

    -- render to native screen space, with the MENU font
    djui_hud_set_resolution(RESOLUTION_DJUI)
    djui_hud_set_font(FONT_MENU)

    -- get width of screen and text
    local screen_width = djui_hud_get_screen_width()
    local width = djui_hud_measure_text(text) * scale

    -- get height of screen and text
    local screen_height = djui_hud_get_screen_height()
    local height = 64 * scale

    -- set location
    local x = screen_width - width - 100
    local y = screen_height - height - 50

    -- set color and render
    djui_hud_set_color(255, 0, 255, 255)
    djui_hud_print_text(text, x, y, scale)
end

---------------------------------------------------------------------
-- ENTRY HOOK
---------------------------------------------------------------------

local function on_debug_hud_render()
    clear_check()
    render_debug_points()
    render_debug_lines()
    render_debug_texts()
    if Dbg.htext ~= nil then render_debug_text() end
end

hook_event(HOOK_ON_HUD_RENDER, on_debug_hud_render)

---------------------------------------------------------------------
-- UTILS
---------------------------------------------------------------------

local num_str = "number"

local function parse_vec3(dst, src)
    if type(src) ~= "table" then return nil end

    -- parse { x = ..., y = ..., z = ... }
    if src.x and src.y and src.z then
        if type(src.x) == num_str and type(src.y) == num_str and type(src.z) == num_str then
            dst[1], dst[2], dst[3] = src.x, src.y, src.z
        else
            return nil
        end

    -- parse { ..., ..., ... }
    elseif #src == 3 and type(src[1]) == num_str and type(src[2]) == num_str and type(src[3]) == num_str  then
        dst[1], dst[2], dst[3] = src[1], src[2], src[3]
    else
        return nil
    end

    -- alter if we want to
    if Dbg.alter_position_function then
        Dbg.alter_position_function(dst)
    end

    return dst
end

---------------------------------------------------------------------
-- PUBLIC API
---------------------------------------------------------------------

function Dbg.point(pos, color, scale)
    clear_check()
    color = color or Dbg.colors.white
    scale = scale or 1

    -- increment / allocate
    _debug_points.count = _debug_points.count + 1
    if not _debug_points.points[_debug_points.count] then
        _debug_points.points[_debug_points.count] = point_new()
    end
    local p = _debug_points.points[_debug_points.count]

    -- parse vec
    if not parse_vec3(p.position, pos) then
        _debug_points.count = _debug_points.count - 1
        return
    end

    p.color[1], p.color[2], p.color[3], p.color[4] = color[1], color[2], color[3], color[4] or 1
    p.scale = scale
end

function Dbg.line(p1, p2, color, thickness)
    clear_check()
    color = color or Dbg.colors.white
    thickness = thickness or 1

    if not p1 or not p2 then return end

    -- increment / allocate
    _debug_lines.count = _debug_lines.count + 1
    if not _debug_lines.lines[_debug_lines.count] then
        _debug_lines.lines[_debug_lines.count] = line_new()
    end
    local l = _debug_lines.lines[_debug_lines.count]

    -- parse vecs
    if not parse_vec3(l.p1, p1) or not parse_vec3(l.p2, p2) then
        _debug_lines.count = _debug_lines.count - 1
        return
    end

    l.color[1], l.color[2], l.color[3], l.color[4] = color[1], color[2], color[3], color[4] or 1
    l.thickness = thickness
end

function Dbg.text(string, pos, color, scale)
    clear_check()
    color = color or Dbg.colors.white
    scale = scale or 1

    -- increment / allocate
    _debug_texts.count = _debug_texts.count + 1
    if not _debug_texts.texts[_debug_texts.count] then
        _debug_texts.texts[_debug_texts.count] = text_new()
    end
    local t = _debug_texts.texts[_debug_texts.count]

    -- parse vec
    if not parse_vec3(t.position, pos) then
        _debug_texts.count = _debug_texts.count - 1
        return
    end

    t.string = string
    t.color[1], t.color[2], t.color[3], t.color[4] = color[1], color[2], color[3], color[4] or 1
    t.scale = scale
end

function Dbg.clear()
    _debug_points.count = 0
    _debug_lines.count  = 0
    _debug_texts.count = 0
end

return Dbg