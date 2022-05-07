function on_hud_render()
    local texInfo = get_texture_info('test')
    djui_hud_set_resolution(RESOLUTION_N64);
    djui_hud_render_texture(texInfo, 0, 0, 1, 1)
end

hook_event(HOOK_ON_HUD_RENDER, on_hud_render)