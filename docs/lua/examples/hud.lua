-- This file is an example of how to render to the screen

local function test_text()
    -- set text and scale
    local text = "This is example text in the bottom right."
    local scale = 1

    -- render to native screen space, with the MENU font
    djui_hud_set_resolution(RESOLUTION_DJUI)
    djui_hud_set_font(FONT_MENU)

    -- get width of screen and text
    local screenWidth = djui_hud_get_screen_width()
    local width = djui_hud_measure_text(text) * scale

    -- get height of screen and text
    local screenHeight = djui_hud_get_screen_height()
    local height = 64 * scale

    -- set location
    local x = screenWidth - width
    local y = screenHeight - height

    -- set color and render
    djui_hud_set_color(255, 0, 255, 255)
    djui_hud_print_text(text, x, y, scale)
end

local function test_texture()
    -- render to the N64's screen space
    djui_hud_set_resolution(RESOLUTION_N64)

    local tex = gTextures.star

    -- color and render
    djui_hud_set_color(255, 0, 255, 255)
    djui_hud_render_texture(tex, 256, 64, 1, 1)

    -- render texture, but cut in half
    djui_hud_render_texture_tile(tex, 256, 84, 2, 1, 0, 0, 8, 16)
end

local function test_rect()
    -- render to native screen space
    djui_hud_set_resolution(RESOLUTION_DJUI)

    -- set location
    local x = 512
    local y = 512

    -- set width/height
    local w = 256
    local h = 256

    -- set color and render first rectangle
    djui_hud_set_color(255, 0, 0, 128)
    djui_hud_render_rect(x, y, w, h)

    -- adjust location and size
    x = x + 16
    y = y + 16
    w = w - 32
    h = h - 32

    -- set color and render second rectangle
    djui_hud_set_color(0, 255, 0, 128)
    djui_hud_render_rect(x, y, w, h)

    -- adjust location and size
    x = x + 16
    y = y + 16
    w = w - 32
    h = h - 32

    -- set color and render third rectangle
    djui_hud_set_color(0, 0, 255, 128)
    djui_hud_render_rect(x, y, w, h)
end

local function test_rainbow_text()
    -- this function is incredibly silly
    -- don't do anything like this
    local text = "HELLO WORLD"
    local scale = 3

    local gt = get_global_timer()

    djui_hud_set_resolution(RESOLUTION_DJUI)
    djui_hud_set_font(FONT_NORMAL)

    for i=0,255 do
        j = gt / 50
        local r = math.sin(0.00 + i / 15 + j) * 127 + 127
        local g = math.sin(0.33 + i / 33 + j) * 127 + 127
        local b = math.sin(0.66 + i / 77 + j) * 127 + 127
        local x = 64 + i
        local y = 64 + i + math.sin(i / 40 + j) * 64
        if i == 255 then
            r = 0
            g = 0
            b = 0
        end
        djui_hud_set_color(r, g, b, i)
        djui_hud_print_text(text, x, y, scale)
    end
end

local function test_rotation()
    -- render to native screen space
    djui_hud_set_resolution(RESOLUTION_DJUI)

    -- get SM64 global timer
    local gt = get_global_timer()

    -- rotate object around pivot (center)
    djui_hud_set_rotation(gt * 512, 0.5, 0.5)

    -- color and render
    djui_hud_set_color(255, 255, 0, 128)
    djui_hud_render_rect(1280, 512, 64, 64)

    -- rotate object around pivot (top-left); color and render
    djui_hud_set_rotation(gt * 512, 0, 0)
    djui_hud_set_color(0, 255, 255, 128)
    djui_hud_render_rect(1280, 512, 64, 64)

    -- rotate object around pivot (bottom-right); color and render
    djui_hud_set_rotation(gt * 512, 1, 1)
    djui_hud_set_color(255, 0, 255, 128)
    djui_hud_render_rect(1280, 512, 64, 64)
end

local function test_filtering()
    local scale = 1

    -- reset rotation from earlier
    djui_hud_set_rotation(0, 0, 0)
    
    -- render to the N64's screen space with the HUD font
    djui_hud_set_resolution(RESOLUTION_N64)
    djui_hud_set_font(FONT_HUD)

    djui_hud_reset_color()

    -- get height of screen and text
    local screenHeight = djui_hud_get_screen_height()
    local height = 16 * scale

    local y = screenHeight - height

    -- set filtering and render
    djui_hud_set_filter(FILTER_NEAREST)
    djui_hud_print_text("NEAREST", 0, y, scale)

    -- adjust position
    y = y - height

    -- set filtering and render
    djui_hud_set_filter(FILTER_LINEAR)
    djui_hud_print_text("LINEAR", 0, y, scale)
end

local function test_world_to_screen()
    -- render to the N64's screen space (recommended for this)
    djui_hud_set_resolution(RESOLUTION_N64)

    -- reset filtering from earlier
    djui_hud_set_filter(FILTER_NEAREST)

    -- project to mario's position
    local out = {x = 0, y = 0, z = 0}
    djui_hud_world_pos_to_screen_pos(gMarioStates[0].pos,out)

    -- get player's character texture
    local tex = gMarioStates[0].character.hudHeadTexture

    djui_hud_reset_color()
    djui_hud_render_texture(tex, out.x, out.y, 1, 1)
end

local function test_mouse()
    -- render to native screen space (recommended for this)
    djui_hud_set_resolution(RESOLUTION_DJUI)

    djui_hud_reset_color()

    -- get mouse position
    local mouseX = djui_hud_get_mouse_x()
    local mouseY = djui_hud_get_mouse_y()
    local scale = 4

    djui_hud_render_texture(gTextures.arrow_up, mouseX, mouseY, scale, scale)
end

local function test_pow_meter()
    djui_hud_set_resolution(RESOLUTION_N64)

    local hp = gMarioStates[0].health
    hud_render_power_meter(hp,16,128,24,24) -- health value ranges from 255 (0xFF in hex) to 2176 (0x880 in hex)
end

-- HOOK_ON_HUD_RENDER renders above SM64's hud
local function on_hud_render()
    test_text()
    test_rect()
    test_texture()
    test_rainbow_text()
    test_rotation()
    test_filtering()
    test_world_to_screen()
    test_pow_meter()
    test_mouse()
end

-- HOOK_ON_HUD_RENDER_BEHIND renders behind SM64's hud
local function on_hud_render_behind()

    local scale = 0.5
    local text = "This text renders behind SM64's HUD!"

    djui_hud_set_resolution(RESOLUTION_N64)
    djui_hud_set_font(FONT_RECOLOR_HUD)

    local screenWidth = djui_hud_get_screen_width()
    local width = djui_hud_measure_text(text) * scale

    local x = screenWidth - width

    djui_hud_set_color(0, 255, 255, 255)
    djui_hud_print_text(text, x, 22, scale)
end

-- hooks --
hook_event(HOOK_ON_HUD_RENDER, on_hud_render)
hook_event(HOOK_ON_HUD_RENDER_BEHIND, on_hud_render_behind)