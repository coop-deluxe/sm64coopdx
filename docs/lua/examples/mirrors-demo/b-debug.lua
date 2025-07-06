local dbg = require("dbg")
if not dbg then
    dbg = {
        colors = {},
        point = function (...) end,
        line = function (...) end,
    }
end

local debug_mirror = false
local mario_in_range = {}

local function get_mirror_coordinates(mirror)
    local n, e1, e2
    if mirror.oMirrorType == MIRROR_TYPE_VERTICAL then
        n = {
            x = 0,
            y = 1,
            z = 0,
        }
        e1 = {
            x = sins(mirror.oFaceAngleYaw),
            y = 0,
            z = coss(mirror.oFaceAngleYaw),
        }
        e2 = {
            x = sins(mirror.oFaceAngleYaw + 0x4000),
            y = 0,
            z = coss(mirror.oFaceAngleYaw + 0x4000),
        }
    elseif mirror.oMirrorType == MIRROR_TYPE_HORIZONTAL then
        n = {
            x = sins(mirror.oFaceAngleYaw),
            y = 0,
            z = coss(mirror.oFaceAngleYaw),
        }
        e1 = {
            x = 0,
            y = 1,
            z = 0,
        }
        e2 = {
            x = sins(mirror.oFaceAngleYaw + 0x4000),
            y = 0,
            z = coss(mirror.oFaceAngleYaw + 0x4000),
        }
    else
        return nil
    end
    local c = {
        x = mirror.oPosX,
        y = mirror.oPosY,
        z = mirror.oPosZ,
    }
    return c, n, e1, e2
end

local function render_mirror_hitbox(mirror)
    local c, n, e1, e2 = get_mirror_coordinates(mirror)
    if not c then return end

    -- normal
    dbg.point(c, dbg.colors.blue, 2)
    dbg.line(c, {
        x = c.x + 200 * n.x,
        y = c.y + 200 * n.y,
        z = c.z + 200 * n.z,
    }, dbg.colors.blue, 2)
    dbg.line(c, {
        x = c.x - 200 * n.x,
        y = c.y - 200 * n.y,
        z = c.z - 200 * n.z,
    }, dbg.colors.blue, 2)

    -- points
    local points = {}
    local coords = {{ 1, 1 }, { 1, -1 }, { -1, -1 }, { -1, 1 }}
    local N = #coords
    for i, uv in ipairs(coords) do
        local p = {
            x = c.x + e1.x * mirror.oMirrorHeight * 0.5 * uv[1] + e2.x * mirror.oMirrorWidth * 0.5 * uv[2],
            y = c.y + e1.y * mirror.oMirrorHeight * 0.5 * uv[1] + e2.y * mirror.oMirrorWidth * 0.5 * uv[2],
            z = c.z + e1.z * mirror.oMirrorHeight * 0.5 * uv[1] + e2.z * mirror.oMirrorWidth * 0.5 * uv[2],
        }
        local q0 = {
            x = p.x + n.x * mirror.oMirrorMaxDistance,
            y = p.y + n.y * mirror.oMirrorMaxDistance,
            z = p.z + n.z * mirror.oMirrorMaxDistance,
        }
        local q1 = {
            x = p.x - n.x * mirror.oMirrorMaxDistance,
            y = p.y - n.y * mirror.oMirrorMaxDistance,
            z = p.z - n.z * mirror.oMirrorMaxDistance,
        }
        points[i] = p
        points[i + N] = q0
        points[i + N * 2] = q1
    end

    -- mirror
    for i = 1, N do
        dbg.line(points[i], points[(i % N) + 1], dbg.colors.cyan, 3)
    end

    -- range
    local color = mario_in_range[mirror._pointer] and dbg.colors.green or dbg.colors.red
    for i = 1, N do
        dbg.line(points[i + N], points[(i % N) + N + 1], color, 2)
        dbg.line(points[i + N * 2], points[(i % N) + N * 2 + 1], color, 2)
        dbg.line(points[i], points[i + N], color, 2)
        dbg.line(points[i], points[i + N * 2], color, 2)
    end
end

hook_event(HOOK_MARIO_UPDATE, function (m)
    if m.playerIndex ~= 0 then return end
    if not debug_mirror then return end
    local mirror = obj_get_first_with_behavior_id(id_bhvMirror)
    while mirror do
        render_mirror_hitbox(mirror)
        mirror = obj_get_next_with_same_behavior_id(mirror)
    end
    mario_in_range = {}
    m.marioObj.hookRender = 1
end)

hook_event(HOOK_ON_MIRROR_OBJECT_RENDER, function (mirrorObj)
    local realObj = mirrorObj.oMirrorObjRealObj
    if realObj == gMarioStates[0].marioObj then
        mario_in_range[mirrorObj.oMirrorObjMirror._pointer] = true
    end
end)

hook_mod_menu_checkbox("Show mirror hitboxes", false, function (index, value)
    debug_mirror = value
end)
