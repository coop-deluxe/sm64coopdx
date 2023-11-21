-- name: Cheats
-- description: The Official Cheats have been Recreated into a Single Mod, Due to the Removal of Cheats as a Settings Option \n\nMod By JairoThePlumber, Coolio and Blocky \n\nSyncing fixed by Blocky and Coolio\n\nBLJ Anywhere and Rapid Fire made by Sunk\n\nAlways Triple Jump made by Bread\n\nMenu made also by Blocky
-- incompatible: cheats

--localise function for performance

local approach_s32, collision_find_surface_on_ray, disable_time_stop_including_mario, enable_time_stop_including_mario, djui_hud_get_screen_width, djui_hud_measure_text,
djui_hud_set_color, djui_hud_set_font, djui_hud_print_text, djui_hud_render_rect, djui_hud_get_mouse_x, djui_hud_get_mouse_y, djui_hud_render_texture, play_sound,
djui_hud_set_resolution, hook_chat_command, hook_event =

approach_s32, collision_find_surface_on_ray, disable_time_stop_including_mario, enable_time_stop_including_mario, djui_hud_get_screen_width, djui_hud_measure_text,
djui_hud_set_color, djui_hud_set_font, djui_hud_print_text, djui_hud_render_rect, djui_hud_get_mouse_x, djui_hud_get_mouse_y, djui_hud_render_texture, play_sound,
djui_hud_set_resolution, hook_chat_command, hook_event

-- Cheats in Order --
for i = 0, MAX_PLAYERS - 1 do
    gPlayerSyncTable[i].Moon_Jump = false
    gPlayerSyncTable[i].God_Mode = false
    gPlayerSyncTable[i].Infinite_lives = false
    gPlayerSyncTable[i].Super_Speed = false
    gPlayerSyncTable[i].Responsive_Controls = false
    gPlayerSyncTable[i].Rapid_Fire = false
    gPlayerSyncTable[i].BLJ_Anywhere = false
    gPlayerSyncTable[i].Always_Triple_Jump = false
end

local function lang()
	local l = gLang[smlua_text_utils_get_language()]
	return l == nil and gLang["English"] or l
end

-- Text For Languages --
gLang = {
	["English"] = {
		MJ = "Moon Jump",
		GM = "God Mode",
		IL = "Infinite Lives",
		SS = "Super Speed",
		RC = "Responsive Controls",
		RF = "Rapid Fire",
		BLJA = "BLJ Anywhere",
		ATJ = "Always Triple Jump",
		CHEATS = 'cheats',
		EXIT = 'Exit',
		DESC = '- Opens the Cheats menu.',
		EXIT_DESC = "Exit the cheat menu.",
		MJ_DESC = "Allows Mario to jump very high.",
		GM_DESC = "Makes Mario invincible.",
		IL_DESC = "Gives Mario infinite lives.",
		SS_DESC = "Increases Mario's movement speed.",
		RC_DESC = "Improves control responsiveness.",
		RF_DESC = "Enables rapid fire for Mario's A button.",
		BLJA_DESC = "Allows Backwards Long Jumps anywhere.",
		ATJ_DESC = "Allows Mario to always perform a triple jump.",
	},

	["Spanish"] = {
		MJ = "Salto Lunar",
		GM = "Modo Dios",
		IL = "Vidas Infinitas",
		SS = "Super Velocidad",
		RC = "Controles Responsivos",
		RF = "Pulsación Rápida",
		BLJA = "BLJ Donde Sea",
		ATJ = "Siempre Hacer Salto Triple",
		CHEATS = 'trucos',
		EXIT = 'Dejar',
		DESC = '- Abre el menú Trucos.',
		EXIT_DESC = "Sal del menú de trucos.",
		MJ_DESC = "Permite a Mario saltar muy alto.",
		GM_DESC = "Hace que Mario sea invencible.",
		IL_DESC = "Le da a Mario vidas infinitas.",
		SS_DESC = "Aumenta la velocidad de movimiento de Mario.",
		RC_DESC = "Mejora la capacidad de respuesta del control.",
		RF_DESC = "Permite disparar rápidamente el botón A de Mario.",
		BLJA_DESC = "Permite saltos largos hacia atrás en cualquier lugar.",
		ATJ_DESC = "Permite a Mario realizar siempre un Salto Triple.",
	},

	["French"] = {
		MJ = "Saut Antigravité",
		GM = "Mode Invincible",
		IL = "Vies Infinies",
		SS = "Super Vitesse",
		RC = "Contrôles Réactifs",
		RF = "Tir Rapide",
		BLJA = "BLJ N'importe Où",
		ATJ = "Triple Sauts Infinis",
		CHEATS = 'triche',
        EXIT = 'Partir',
		DESC = '- Ouvrez le menu Astuces.',
		EXIT_DESC = "Quittez le menu de triche.",
		MJ_DESC = "Permet à Mario de sauter très haut.",
		GM_DESC = "Rend Mario invincible.",
		IL_DESC = "Donne à Mario des vies infinies.",
		SS_DESC = "Augmente la vitesse de déplacement de Mario.",
		RC_DESC = "Améliore la réactivité du contrôle.",
		RF_DESC = "Permet un tir rapide pour le bouton A de Mario.",
		BLJA_DESC = "PPermet des sauts longs en arrière n'importe où.",
		ATJ_DESC = "Permet à Mario de toujours effectuer un triple saut.",
	},

	["Portuguese"] = {
		MJ = "Pulo da Lua",
		GM = "Modo Deus",
		IL = "Vidas Infinitas",
		SS = "Super Velocidade",
		RC = "Controle Responsivos",
		RF = "Fogo Rápido",
		BLJA = "BLJ Em Qualquer Lugar",
		ATJ = "Sempre Fazer Triple Jump",
		CHEATS = 'trapaças',
        EXIT = 'Deixar',
		DESC = '- Abra o menu Truques.',
		EXIT_DESC = "Saia do menu de truques.",
		MJ_DESC = "Permite que Mario salte muito alto.",
		GM_DESC = "Makes Mario invincible.",
		IL_DESC = "Torna Mario invencível.",
		SS_DESC = "Aumenta a velocidade de movimento de Mario.",
		RC_DESC = "Melhora a capacidade de resposta do controle.",
		RF_DESC = "Ativa o disparo rápido para o botão A de Mario.",
		BLJA_DESC = "Permite saltos longos para trás em qualquer lugar.",
		ATJ_DESC = "Permite que Mario sempre execute um salto triplo.",
	},

	["German"] = {
		MJ = "Mond-Sprung",
		GM = "Gott Modus",
		IL = "Unbegrenzte Leben",
		SS = "Supergeschwindigkeit",
		RC = "Reaktionsschnelle Steuerung",
		RF = "Schnellfeuer",
		BLJA = "Überall Rückwertsweitspringen",
		ATJ = "Immer Dreisprung",
		CHEATS = 'betrugt',
        EXIT = 'Verlassen',
		DESC = '- Öffnet das Cheats-Menü.',
		EXIT_DESC = "Verlassen Sie das Cheat-Menü.",
		MJ_DESC = "Ermöglicht Mario, sehr hoch zu springen.",
		GM_DESC = "Macht Mario unbesiegbar.",
		IL_DESC = "Gibt Mario unendlich viele Leben.",
		SS_DESC = "Erhöht Marios Bewegungsgeschwindigkeit.",
		RC_DESC = "Verbessert die Reaktionsfähigkeit der Steuerung.",
		RF_DESC = "Enables rapid fire for Mario's A button.",
		BLJA_DESC = "Ermöglicht Schnellfeuer für Marios A-Taste.",
		ATJ_DESC = "Ermöglicht Mario, immer einen Dreisprung auszuführen.",
	},

	["Russian"] = {
		MJ = "Супер прыжок",
		GM = "Режим бога",
		IL = "Бесконечные жизни",
		SS = "Супер cкорость",
		RC = "Отзывчивое управление",
		RF = "Быстрый огонь",
		BLJA = "BLJ в любом месте",
		ATJ = "Всегда тройной прыжок",
		CHEATS = 'cheats',
		EXIT = 'Покинуть',
		DESC = '- Открывает меню читов.',
		EXIT_DESC = "Выйдите из чит-меню.",
		MJ_DESC = "Позволяет Марио прыгать очень высоко.",
		GM_DESC = "Делает Марио непобедимым.",
		IL_DESC = "Дает Марио бесконечное количество жизней.",
		SS_DESC = "Увеличивает скорость передвижения Марио.",
		RC_DESC = "Улучшает оперативность управления.",
		RF_DESC = "Включает быстрый огонь для кнопки A Марио.",
		BLJA_DESC = "Позволяет совершать прыжки назад в длину в любом месте.",
		ATJ_DESC = "Позволяет Марио всегда выполнять тройной прыжок.",
	},

	["Italian"] = {
		MJ = "Salto della Luna",
		GM = "Modalità Dio",
		IL = "Vite Infinite",
		SS = "Super Velocità",
		RC = "Controlli Reattivi",
		RF = "Fuoco Rapido",
		BLJA = "BLJ Ovunque",
		ATJ = "Sempre Salto Triplo",
		CHEATS = 'trucchi',
		EXIT = 'lasciare',
		DESC = '- Apre il menu Trucchi.',
		EXIT_DESC = "Esci dal menu dei trucchi.",
		MJ_DESC = "Permette a Mario di saltare molto in alto.",
		GM_DESC = "Rende Mario invincibile.",
		IL_DESC = "Dà a Mario vite infinite.",
		SS_DESC = "Aumenta la velocità di movimento di Mario.",
		RC_DESC = "Migliora la reattività del controllo.",
		RF_DESC = "Abilita il fuoco rapido per il pulsante A di Mario.",
		BLJA_DESC = "Permette salti in lungo all'indietro ovunque.",
		ATJ_DESC = "Permette a Mario di eseguire sempre un triplo salto.",
	},

	["Czech"] = {
		MJ = "Nekonečný Skok",
		GM = "Nenech Se Zranit",
		IL = "Nekonečné Životy",
		SS = "Super Rychlost",
		RC = "Citlivé Ovládání",
		RF = "Rychle Mačkat Tlačítko",
		BLJA = "BLJ Všude",
		ATJ = "Vždy Trojitý Skok",
		CHEATS = 'cheaty',
		EXIT = 'opustit',
		DESC = '- Otevře nabídku Cheatů.',
		EXIT_DESC = "Opusťte cheat menu.",
		MJ_DESC = "Umožňuje Mariovi skákat velmi vysoko.",
		GM_DESC = "Učiní Maria neporazitelným.",
		IL_DESC = "Dává Mariovi nekonečné životy.",
		SS_DESC = "Zvyšuje Mariovu rychlost pohybu.",
		RC_DESC = "Zlepšuje odezvu ovládání.",
		RF_DESC = "Umožňuje rychlou střelbu pro Mariovo tlačítko A.",
		BLJA_DESC = "Umožňuje dlouhé skoky vzad kdekoli.",
		ATJ_DESC = "Umožňuje Mariovi vždy provést trojitý skok.",
	},

	["Dutch"] = {
		MJ = "Maan Sprong",
		GM = "God Modus",
		IL = "Oneindige Levens",
		SS = "Super Snelheid",
		RC = "Snel Reagerende Controles",
		RF = "Snel Vuur",
		BLJA = "BLJ Overal",
		ATJ = "Altijd Drievoudige Sprong",
		CHEATS = 'cheats',
        EXIT = 'Verlaten',
		DESC = '- Opent het Cheats-menu.',
		EXIT_DESC = "Verlaat het cheatmenu.",
		MJ_DESC = "Hiermee kan Mario heel hoog springen.",
		GM_DESC = "Maakt Mario onoverwinnelijk.",
		IL_DESC = "Geeft Mario oneindige levens.",
		SS_DESC = "Verhoogt de bewegingssnelheid van Mario.",
		RC_DESC = "Verbetert het reactievermogen van de besturing.",
		RF_DESC = "Maakt snel vuren voor Mario's A-knop mogelijk.",
		BLJA_DESC = "Maakt achteruit lange sprongen overal mogelijk.",
		ATJ_DESC = "Hiermee kan Mario altijd een hinkstapsprong uitvoeren."
	},
	
	["Polish"] = {
		MJ = "Skok Ksiezycowy",
		GM = "Tryb Boga",
		IL = "Nieskonczone Zycia",
		SS = "Super Szybkosc",
		RC = "Responsywne Sterowanie",
		RF = "Szybkostrzelnosc",
		BLJA = "BLJ Gdziekolwiek",
		ATJ = "Potrojny Skok Zawsze",
		CHEATS = 'oszustwa',
        EXIT = 'Wyjście',
		DESC = '- Otwiera menu Kody.',
		EXIT_DESC = "Wyjdź z menu cheatów.",
		MJ_DESC = "Pozwala Mario skakać bardzo wysoko.",
		GM_DESC = "Uczyń Mario niepokonanym.",
		IL_DESC = "Daje Mario nieskończone życie.",
		SS_DESC = "Zwiększa prędkość ruchu Mario.",
		RC_DESC = "Poprawia responsywność sterowania.",
		RF_DESC = "Umożliwia szybkie strzelanie przyciskiem A Mario.",
		BLJA_DESC = "Umożliwia dalekie skoki do tyłu w dowolnym miejscu.",
		ATJ_DESC = "Pozwala Mario zawsze wykonać potrójny skok.",
	}
}

local menu = false

-- Moon Jump --

local function limit_angle(a)
	return (a + 0x8000) % 0x10000 - 0x8000
end

local function moon_jump_update(m)
    if gPlayerSyncTable[m.playerIndex].Moon_Jump then
	    if (m.controller.buttonDown & L_TRIG) ~= 0 then
		    m.faceAngle.y = m.intendedYaw - approach_s32(limit_angle(m.intendedYaw - m.faceAngle.y), 0, 0x800, 0x800)
		    m.vel.y = 40

		    if (m.action == ACT_FORWARD_GROUND_KB or
		    	m.action == ACT_BACKWARD_GROUND_KB or
		    	m.action == ACT_SOFT_FORWARD_GROUND_KB or
		    	m.action == ACT_HARD_BACKWARD_GROUND_KB or
		    	m.action == ACT_FORWARD_AIR_KB or
		    	m.action == ACT_BACKWARD_AIR_KB or
		    	m.action == ACT_HARD_FORWARD_AIR_KB or
		    	m.action == ACT_HARD_BACKWARD_AIR_KB or
		    	m.action == ACT_AIR_HIT_WALL) then
		    	set_mario_action(m, ACT_FREEFALL, 0)
			end
		end
	end
end

local function moon_jump_command()
	gPlayerSyncTable[0].Moon_Jump = not gPlayerSyncTable[0].Moon_Jump
	--djui_popup_create("Moon Jump is now " .. (gPlayerSyncTable[0].Moon_Jump and "Enabled" or "Disabled"), 1)
	return true
end

-- God Mode --

local function god_mode_update(m)
    if gPlayerSyncTable[m.playerIndex].God_Mode then
	    m.health = 0x880
	    m.healCounter = 0
	    m.hurtCounter = 0
	end
end

local function god_mode_fall_update(m, type)
    if gPlayerSyncTable[m.playerIndex].God_Mode then
        if type == STEP_TYPE_AIR and m.vel.y < 0 then
            ray = collision_find_surface_on_ray(m.pos.x, m.pos.y, m.pos.z, m.vel.x, m.vel.y, m.vel.z)
            if ray.surface ~= nil then
                if ray.surface.normal.y ~= 0 then
                    m.peakHeight = m.pos.y
			    end
            end
		end
	end
end

local function god_mode_command()
	gPlayerSyncTable[0].God_Mode = not gPlayerSyncTable[0].God_Mode
	--djui_popup_create("God Mode is now " .. (gPlayerSyncTable[0].God_Mode and "Enabled" or "Disabled"), 1)
	return true
end

-- Infinite Lives --

local function infinite_lives_update(m)
    if gPlayerSyncTable[0].Infinite_lives then
	    m.numLives = 100
	end
end

local function infinite_lives_command()
	gPlayerSyncTable[0].Infinite_lives = not gPlayerSyncTable[0].Infinite_lives
	--djui_popup_create("Infinite Lives is now " .. (Infinite_lives and "Enabled" or "Disabled"), 1)
	return true
end

-- Super Speed --

local SUPER_SPEED_MULTIPLIER = 4

local function super_speed_update(m)
    if gPlayerSyncTable[m.playerIndex].Super_Speed and m.action ~= ACT_BUBBLED then
    	m.vel.x = m.vel.x * SUPER_SPEED_MULTIPLIER
    	m.vel.z = m.vel.z * SUPER_SPEED_MULTIPLIER
    end
end

local function super_speed_command()
	gPlayerSyncTable[0].Super_Speed = not gPlayerSyncTable[0].Super_Speed
	--djui_popup_create("Super Speed is now " .. (gPlayerSyncTable[0].Super_Speed and "Enabled" or "Disabled"), 1)
	return true
end

-- Responsive Controls -- 

local function responsive_controls_update(m)
    if gPlayerSyncTable[m.playerIndex].Responsive_Controls then
    	if m.action == ACT_WALKING or
    	    m.action == ACT_HOLD_WALKING or
    	    m.action == ACT_HOLD_HEAVY_WALKING or
    	    m.action == ACT_FINISH_TURNING_AROUND or
    	    m.action == ACT_CRAWLING then
    	    m.faceAngle.y = m.intendedYaw
		end
	end
end

local function responsive_controls_command()
	gPlayerSyncTable[0].Responsive_Controls = not gPlayerSyncTable[0].Responsive_Controls
	--djui_popup_create("Responsive Controls is now " .. (gPlayerSyncTable[0].Responsive_Controls and "Enabled" or "Disabled"), 1)
	return true
end

-- Rapid Fire --

local function rapid_fire_update(m)
    if gPlayerSyncTable[m.playerIndex].Rapid_Fire then
    	if (m.controller.buttonDown & A_BUTTON) ~= 0 then
    		m.controller.buttonPressed = m.controller.buttonPressed | A_BUTTON
		end
	end
end

local function rapid_fire_command()
	gPlayerSyncTable[0].Rapid_Fire = not gPlayerSyncTable[0].Rapid_Fire
	--djui_popup_create("Rapid Fire is now " .. (gPlayerSyncTable[0].Rapid_Fire and "Enabled" or "Disabled"), 1)
	return true
end

-- BLJ Anywhere --

local function blj_anywhere_update(m)
    if gPlayerSyncTable[m.playerIndex].BLJ_Anywhere then
    	if (m.action == ACT_LONG_JUMP) and
    	   (m.controller.buttonDown & Z_TRIG) ~= 0 and
    	    m.forwardVel < -15 then
    		m.vel.y = -30
		end
	end
end

local function blj_anywhere_command()
	gPlayerSyncTable[0].BLJ_Anywhere = not gPlayerSyncTable[0].BLJ_Anywhere
	--djui_popup_create("BLJ Anywhere is now " .. (gPlayerSyncTable[0].BLJ_Anywhere and "Enabled" or "Disabled"), 1)
	return true
end

-- Always Triple Jump --

---@param m MarioState
local function always_triple_jump_update(m, action)
    if gPlayerSyncTable[m.playerIndex].Always_Triple_Jump then
    	if m.forwardVel < 20 and m.action == ACT_DOUBLE_JUMP_LAND and action == ACT_JUMP then
    		return ACT_TRIPLE_JUMP
		end
	end
end


local function always_triple_jump_command()
	gPlayerSyncTable[0].Always_Triple_Jump = not gPlayerSyncTable[0].Always_Triple_Jump
	--djui_popup_create("Always Triple Jump is now " .. (gPlayerSyncTable[0].Always_Triple_Jump and "Enabled" or "Disabled"), 1)
	return true
end

local function mario_update(m)
	if m.playerIndex ~= 0 then return end
	moon_jump_update(m)
	god_mode_update(m)
	infinite_lives_update(m)
	responsive_controls_update(m)
end

local function before_phys_step(m, type)
	god_mode_fall_update(m, type)
	super_speed_update(m)
end

local function before_mario_update(m)
	if m.playerIndex ~= 0 then return end
	blj_anywhere_update(m)
	rapid_fire_update(m)
end

local function close_menu()
    menu = false
    selectedOption = 1
    disable_time_stop_including_mario()
end

-- Define menu options
local menuOptions = {
    { label = lang().MJ,   action = moon_jump_command, status = gPlayerSyncTable[0].Moon_Jump, description = lang().MJ_DESC },
    { label = lang().GM,   action = god_mode_command, status = gPlayerSyncTable[0].God_Mode, description = lang().GM_DESC },
    { label = lang().IL,   action = infinite_lives_command, status = gPlayerSyncTable[0].Infinite_lives, description = lang().IL_DESC },
    { label = lang().SS,   action = super_speed_command, status = gPlayerSyncTable[0].Super_Speed, description = lang().SS_DESC },
    { label = lang().RC,   action = responsive_controls_command, status = gPlayerSyncTable[0].Responsive_Controls, description = lang().RC_DESC },
    { label = lang().RF,   action = rapid_fire_command, status = gPlayerSyncTable[0].Rapid_Fire, description = lang().RF_DESC },
	{ label = lang().BLJA, action = blj_anywhere_command, status = gPlayerSyncTable[0].BLJ_Anywhere, description = lang().BLJA_DESC },
    { label = lang().ATJ,  action = always_triple_jump_command, status = gPlayerSyncTable[0].Always_Triple_Jump, description = lang().ATJ_DESC },
    { label = lang().EXIT, action = function() close_menu() end, description = lang().EXIT_DESC },
}

-- Initialize the selected option
local selectedOption = 1

-- Set the scale factor for the menu
local menuScale = 2.0 -- Adjust this value as needed

-- Add a title for the menu
local menuTitle = lang().CHEATS
local titleY = 150

local function drawMenu()
    if not menu then return end
    enable_time_stop_including_mario()

    djui_hud_set_color(0, 0, 0, 200)
    djui_hud_render_rect(0, 0, 10000, 10000)

    -- Set text color and position for the title
    local titleX = ((djui_hud_get_screen_width() - djui_hud_measure_text(menuTitle) * menuScale * 2.5) / 2.1)

    -- Draw the title
    djui_hud_set_color(255, 255, 255, 255)
    djui_hud_set_font(FONT_HUD)
    djui_hud_print_text(menuTitle, titleX, titleY, menuScale * 2.5)
    djui_hud_set_font(FONT_NORMAL)

    -- Set text color and position for the menu options
    local textY = titleY + 100
    local textSpacing = 30 * menuScale
    local rectPadding = 5

    for i, option in ipairs(menuOptions) do
        local textWidth = djui_hud_measure_text(option.label)
        local textX = (djui_hud_get_screen_width() - textWidth * menuScale) / 2

        if i == selectedOption then
            -- Draw black rectangle behind the selected option
                    -- Draw the description with a smaller scale
            local descX = (djui_hud_get_screen_width() - djui_hud_measure_text(option.description) * (menuScale - 0.5)) / 2
            local descY = 850
            djui_hud_set_color(255, 255, 255, 255)
            djui_hud_set_font(FONT_NORMAL)
            djui_hud_print_text(option.description, descX, descY, menuScale - 0.5)
            local optionWidth = textWidth * menuScale + rectPadding * 2
            local optionHeight = 16 * menuScale + rectPadding * 2
            djui_hud_set_color(0, 255, 255, 150)
            djui_hud_render_rect(textX - rectPadding, (textY + (i - 1) * textSpacing - rectPadding) + 15, optionWidth, optionHeight + 5)
        end

        -- Set text color based on the status
        if option.status == nil then
            djui_hud_set_color(255, 255, 255, 255) -- Green for "On"
        elseif option.status then
            djui_hud_set_color(0, 255, 0, 255) -- Green for "On"
        else
            djui_hud_set_color(255, 0, 0, 255) -- Red for "Off"
        end

        -- Draw the menu option with scale
        djui_hud_print_text(option.label, textX, textY + (i - 1) * textSpacing, menuScale)
    end
end

---comment
-----@param m MarioState
-- Add a cooldown for menu navigation
local cooldown = 5
local cooldownCounter = 0

local function updateMenu()
    if not menu then return end
    local m = gMarioStates[0]
    if m.playerIndex ~= 0 then return end

    local stickY = m.controller.stickY
    local mouseX = djui_hud_get_mouse_x()
    local mouseY = djui_hud_get_mouse_y()

    djui_hud_render_texture(gTextures.star, mouseX - 8, mouseY - 8, 2, 2)

    if selectedOption < 1 then
        selectedOption = #menuOptions
    elseif selectedOption > #menuOptions then
        selectedOption = 1
    end

    if cooldownCounter > 0 then
        cooldownCounter = cooldownCounter - 1
    else
        for i, option in ipairs(menuOptions) do
            local textWidth = djui_hud_measure_text(option.label)
            local textX = (djui_hud_get_screen_width() - textWidth * menuScale) / 2
            local textY = titleY + 100 + (i - 1) * (30 * menuScale)
            local optionWidth = textWidth * menuScale
            local optionHeight = 16 * menuScale

            -- Check if the mouse is within the bounds of the option
            if mouseX >= textX and mouseX <= textX + optionWidth and mouseY >= textY and mouseY <= textY + optionHeight then
                selectedOption = i
            end
        end

        if stickY > 0.5 then
            -- Move selection down
            selectedOption = selectedOption - 1
            play_sound(SOUND_MENU_CHANGE_SELECT, gMarioStates[0].pos)
            cooldownCounter = cooldown
        elseif stickY < -0.5 then
            -- Move selection up
            selectedOption = selectedOption + 1
            play_sound(SOUND_MENU_CHANGE_SELECT, gMarioStates[0].pos)
            cooldownCounter = cooldown
        elseif m.controller.buttonPressed & A_BUTTON ~= 0 or  m.controller.buttonPressed & B_BUTTON ~= 0 then
            play_sound(SOUND_MENU_CLICK_FILE_SELECT, gMarioStates[0].pos)
            -- Execute the selected menu option
            menuOptions[selectedOption].action()
            if menuOptions[selectedOption].status ~= nil then
                menuOptions[selectedOption].status = not menuOptions[selectedOption].status
            end
        elseif m.controller.buttonPressed & START_BUTTON ~= 0 then
            close_menu()
        end
    end
end

-- Main loop
local function hud_render()
    djui_hud_set_resolution(RESOLUTION_DJUI)
    drawMenu()
    updateMenu()
end

local function menu_command()
    menu = true
	return true
end

hook_chat_command(lang().CHEATS, lang().DESC, menu_command)
hook_event(HOOK_ON_HUD_RENDER,			hud_render)
hook_event(HOOK_MARIO_UPDATE,			mario_update)
hook_event(HOOK_ALLOW_HAZARD_SURFACE,	function (m) return not gPlayerSyncTable[m.playerIndex].God_Mode end)
hook_event(HOOK_BEFORE_PHYS_STEP,		before_phys_step)
hook_event(HOOK_BEFORE_MARIO_UPDATE,	before_mario_update)
hook_event(HOOK_BEFORE_SET_MARIO_ACTION,always_triple_jump_update)