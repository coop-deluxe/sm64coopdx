------------------------------------------------------
-- Custom HUD Rendering by Agent X and xLuigiGamerx --
------------------------------------------------------

--- @param localIndex integer
--- @return TextureInfo|nil
--- This assumes multiple characters will not have the same model
function life_icon_from_local_index(localIndex)
    for i = 1, #characterTable do
        if characterTable[i].model == gPlayerSyncTable[localIndex].modelId then
            return characterTable[i].lifeIcon
        end
    end
end

local function render_hud_mario_lives()
    hud_set_value(HUD_DISPLAY_FLAGS, hud_get_value(HUD_DISPLAY_FLAGS) & ~HUD_DISPLAY_FLAG_LIVES)

    local x = 22
    local y = 15 -- SCREEN_HEIGHT - 209 - 16
    local lifeIcon = characterTable[currChar].lifeIcon

    if lifeIcon == nil then
        djui_hud_print_text("?", x, y, 1)
    else
        djui_hud_render_texture(lifeIcon, x, y, 1 / (lifeIcon.width * 0.0625), 1 / (lifeIcon.height * 0.0625)) -- 0.0625 is 1/16
    end
    djui_hud_print_text("@", x + 16, y, 1)
    djui_hud_print_text(tostring(hud_get_value(HUD_DISPLAY_LIVES)):gsub("-", "M"), x + 32, y, 1)
end

local function render_hud_stars()
    hud_set_value(HUD_DISPLAY_FLAGS, hud_get_value(HUD_DISPLAY_FLAGS) & ~HUD_DISPLAY_FLAG_STAR_COUNT)

    -- the flashing when you exit a painting, uses sm64coopdx exclusive functionality
    -- v0.1.5
    --[[
    if IS_COOPDX then
        -- prevent star count from flashing outside of castle
        if gNetworkPlayers[0].currCourseNum ~= COURSE_NONE then hud_set_flash(0) end

        if hud_get_flash() == 1 and (get_global_timer() & 0x08) == 0 then
            return
        end
    end
    ]]

    local x = djui_hud_get_screen_width() - 78
    local y = 15 -- SCREEN_HEIGHT - 209 - 16
    local starIcon = characterTable[currChar].starIcon and characterTable[currChar].starIcon or gTextures.star

    local showX = 0
    local hudDisplayStars = hud_get_value(HUD_DISPLAY_STARS)
    if hudDisplayStars < 100 then showX = 1 end

    djui_hud_render_texture(starIcon, x, y, 1 / (starIcon.width * 0.0625), 1 / (starIcon.height * 0.0625)) -- 0.0625 is 1/16
    if showX == 1 then
        djui_hud_print_text("@", x + 16, y, 1)
    end
    djui_hud_print_text(tostring(hudDisplayStars):gsub("-", "M"), (showX * 14) + x + 16, y, 1)
end

local function render_hud_camera_status()
    if not IS_COOPDX or not HUD_DISPLAY_CAMERA_STATUS then return end

    hud_set_value(HUD_DISPLAY_FLAGS, hud_get_value(HUD_DISPLAY_FLAGS) & ~HUD_DISPLAY_FLAG_CAMERA)

    local x = djui_hud_get_screen_width() - 54
    local y = 205
    local cameraHudStatus = hud_get_value(HUD_DISPLAY_CAMERA_STATUS)

    if cameraHudStatus == CAM_STATUS_NONE then return end

    djui_hud_render_texture(gTextures.camera, x, y, 1, 1)

    switch(cameraHudStatus & CAM_STATUS_MODE_GROUP, {
        [CAM_STATUS_MARIO] = function()
            local lifeIcon = characterTable[currChar].lifeIcon
            if lifeIcon == nil then
                djui_hud_print_text("?", x + 16, y, 1)
            else
                djui_hud_render_texture(lifeIcon, x + 16, y, 1 / (lifeIcon.width * 0.0625), 1 / (lifeIcon.height * 0.0625)) -- 0.0625 is 1/16
            end
        end,
        [CAM_STATUS_LAKITU] = function()
            djui_hud_render_texture(gTextures.lakitu, x + 16, y, 1, 1)
        end,
        [CAM_STATUS_FIXED] = function()
            djui_hud_render_texture(gTextures.no_camera, x + 16, y, 1, 1)
        end
    })

    switch(cameraHudStatus & CAM_STATUS_C_MODE_GROUP, {
        [CAM_STATUS_C_DOWN] = function()
            djui_hud_render_texture(gTextures.arrow_down, x + 4, y + 16, 1, 1)
        end,
        [CAM_STATUS_C_UP] = function()
            djui_hud_render_texture(gTextures.arrow_up, x + 4, y - 8, 1, 1)
        end
    })
end

local function render_act_select_hud()
    local course = gNetworkPlayers[0].currCourseNum
    if gServerSettings.enablePlayersInLevelDisplay == 0 or course == 0 or obj_get_first_with_behavior_id(id_bhvActSelector) == nil then return end

    local stars = save_file_get_star_flags(get_current_save_file_num() - 1, course - 1)
    local maxStar = 0

    for i = 5, 0, -1 do
        if stars & 2 ^ i ~= 0 then
            maxStar = i
            break
        end
    end

    for a = 1, maxStar + 1 do
        local x = (38 - maxStar * 17 + a * 34) + djui_hud_get_screen_width() * 0.5 - 75
        for j = 0, MAX_PLAYERS - 1 do
            local np = gNetworkPlayers[j]
            if np and np.connected and np.currCourseNum == course and np.currActNum == a then
                djui_hud_render_rect(x - 4, 17, 16, 16)
                local displayHead = life_icon_from_local_index(j)
                if displayHead == nil then
                    djui_hud_print_text("?", x - 4, 17, 1)
                else
                    djui_hud_render_texture(displayHead, x - 4, 17, 1 / (displayHead.width * 0.0625), 1 / (displayHead.height * 0.0625)) -- 0.0625 is 1/16
                end
            end
        end
    end
end

local function on_hud_render_behind()
    djui_hud_set_resolution(RESOLUTION_N64)
    djui_hud_set_font(FONT_HUD)
    djui_hud_set_color(255, 255, 255, 255)

    if obj_get_first_with_behavior_id(id_bhvActSelector) ~= nil then
        render_act_select_hud()
        return
    elseif gNetworkPlayers[0].currActNum == 99 or gMarioStates[0].action == ACT_INTRO_CUTSCENE or hud_is_hidden() then
        return
    end

    render_hud_mario_lives()
    render_hud_stars()
    render_hud_camera_status()
end


hook_event(HOOK_ON_HUD_RENDER_BEHIND, on_hud_render_behind)