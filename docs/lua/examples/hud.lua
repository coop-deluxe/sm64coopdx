-- This file is an example of how to render to the screen

rainbow = 0

function test_text()
    -- set text and scale
    local text = "This is example text in the bottom right."
    local scale = 1

    -- render to native screen space, with the MENU font
    djui_hud_set_resolution(RESOLUTION_DJUI);
    djui_hud_set_font(FONT_MENU);

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
    djui_hud_set_color(255, 0, 255, 255);
    djui_hud_print_text(text, x, y, scale);
end

function test_texture()
    -- render to N64's screen space
    djui_hud_set_resolution(RESOLUTION_N64)

    -- get player's character texture
    local tex = gMarioStates[0].character.hudHeadTexture

    -- set scale
    local wscale = 1
    local hscale = 1

    -- set position
    local x = 256
    local y = 64

    -- set color and render
    djui_hud_set_color(255, 0, 255, 255)
    djui_hud_render_texture(tex, x, y, wscale, hscale)
end

function test_rect()
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

function test_rainbow_text()
    -- this function is incredibly silly
    -- don't do anything like this
    local res = RESOLUTION_DJUI
    local text = "HELLO WORLD"
    local scale = 3

    djui_hud_set_resolution(res);
    djui_hud_set_font(FONT_NORMAL);

    for i=0,255 do
        j = rainbow / 50
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
        djui_hud_set_color(r, g, b, i);
        djui_hud_print_text(text, x, y, scale);
    end
    rainbow = rainbow + 1
end

function on_hud_render()
    test_text()
    test_rect()
    test_texture()
    test_rainbow_text()
end

hook_event(HOOK_ON_HUD_RENDER, on_hud_render)
