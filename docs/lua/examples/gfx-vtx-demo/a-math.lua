--
-- Math stuff
-- Don't mind this file, it's not relevant to the purpose of this demo.
--

local SHAPE_SIZE = 100
local SHAPE_TEXTURE_SIZE = 512

----------
-- Cube --
----------

local CUBE_ROTATIONS = {
    { x = 0x0000, y = 0x0000, z = 0 },
    { x = 0x0000, y = 0x4000, z = 0 },
    { x = 0x0000, y = 0x8000, z = 0 },
    { x = 0x0000, y = 0xC000, z = 0 },
    { x = 0x4000, y = 0x0000, z = 0 },
    { x = 0xC000, y = 0x0000, z = 0 },
}

local CUBE_POINTS = {
    { x = -0.75, y = -0.75, z = -0.75, tu = 0, tv = (SHAPE_TEXTURE_SIZE - 1) << 5 },
    { x =  0.75, y = -0.75, z = -0.75, tu = 0, tv = 0 },
    { x = -0.75, y =  0.75, z = -0.75, tu = (SHAPE_TEXTURE_SIZE - 1) << 5, tv = (SHAPE_TEXTURE_SIZE - 1) << 5 },
    { x =  0.75, y =  0.75, z = -0.75, tu = (SHAPE_TEXTURE_SIZE - 1) << 5, tv = 0 },
}

function get_cube_vertices()
    vertices = {}
    for _, r in ipairs(CUBE_ROTATIONS) do
        for _, p in ipairs(CUBE_POINTS) do
            local v = { x = p.x * SHAPE_SIZE, y = p.y * SHAPE_SIZE, z = p.z * SHAPE_SIZE }
            vec3f_rotate_zxy(v, r)
            table.insert(vertices, { x = v.x, y = v.y, z = v.z, tu = p.tu, tv = p.tv, r = 0xFF, g = 0xFF, b = 0xFF })
        end
    end
    return vertices
end

function get_cube_triangles()
    local triangles = {}
    for i = 0, 5 do
        local offset = 4 * i
        table.insert(triangles, {
            offset + 0, offset + 1, offset + 2,
            offset + 2, offset + 1, offset + 3
        })
    end
    return triangles
end

function get_cube_geometry_mode()
    return "G_TEXTURE_GEN | G_CULL_BOTH | G_LIGHTING", "0"
end

function get_cube_texture_scaling()
    return 0xFFFF
end

----------------
-- Octahedron --
----------------

function get_octahedron_vertices()
    local vertices = {}
    table.insert(vertices, { x = 0, y = -SHAPE_SIZE, z = 0, tu = 0, tv = (SHAPE_TEXTURE_SIZE / 2) << 5, r = 0xFF, g = 0xFF, b = 0xFF })
    table.insert(vertices, { x = 0, y =  SHAPE_SIZE, z = 0, tu = (SHAPE_TEXTURE_SIZE - 1) << 5, tv = (SHAPE_TEXTURE_SIZE / 2) << 5, r = 0xFF, g = 0xFF, b = 0xFF })
    for i = 0, 3 do
        local sina = sins(0x4000 * i) * SHAPE_SIZE
        local cosa = coss(0x4000 * i) * SHAPE_SIZE
        table.insert(vertices, { x = sina, y = 0, z = cosa, tu = (SHAPE_TEXTURE_SIZE - 1) << 5, tv = (SHAPE_TEXTURE_SIZE - 1) << 5, r = 0xFF, g = 0xFF, b = 0xFF })
        table.insert(vertices, { x = sina, y = 0, z = cosa, tu = (SHAPE_TEXTURE_SIZE - 1) << 5, tv = 0, r = 0xFF, g = 0xFF, b = 0xFF })
        table.insert(vertices, { x = sina, y = 0, z = cosa, tu = 0, tv = (SHAPE_TEXTURE_SIZE - 1) << 5, r = 0xFF, g = 0xFF, b = 0xFF })
        table.insert(vertices, { x = sina, y = 0, z = cosa, tu = 0, tv = 0, r = 0xFF, g = 0xFF, b = 0xFF })
    end
    return vertices
end

function get_octahedron_triangles()
    local triangles = {}
    for i = 0, 3 do
        table.insert(triangles, {
            0, 2 + i * 4 + 0, 2 + ((i + 1) % 4) * 4 + 1,
            1, 2 + i * 4 + 2, 2 + ((i + 1) % 4) * 4 + 3
        })
    end
    return triangles
end

function get_octahedron_geometry_mode()
    return "G_TEXTURE_GEN | G_CULL_BOTH | G_LIGHTING", "0"
end

function get_octahedron_texture_scaling()
    return 0xFFFF
end

----------
-- Star --
----------

local STAR_POINTS = {
    { x =    0, y =    8, z = -90, r = 0x00, g = 0x07, b = 0x82 },
    { x =  190, y = -201, z =   0, r = 0x55, g = 0xa3, b = 0x00 },
    { x =    0, y = -129, z =   0, r = 0x00, g = 0x82, b = 0x00 },
    { x =  146, y =  -42, z =   0, r = 0x7c, g = 0xe7, b = 0x00 },
    { x =    0, y =    8, z =  90, r = 0x00, g = 0x07, b = 0x7e },
    { x =  256, y =   84, z =   0, r = 0x68, g = 0x47, b = 0x00 },
    { x = -146, y =  -42, z =   0, r = 0x84, g = 0xe7, b = 0x00 },
    { x = -190, y = -201, z =   0, r = 0xaa, g = 0xa3, b = 0x00 },
    { x = -256, y =   84, z =   0, r = 0x97, g = 0x47, b = 0x00 },
    { x =    0, y =  246, z =   0, r = 0x00, g = 0x7e, b = 0x00 },
    { x =   96, y =   99, z =   0, r = 0x3d, g = 0x6f, b = 0x00 },
    { x =  -96, y =   99, z =   0, r = 0xc3, g = 0x6f, b = 0x00 },
}

local STAR_TRIANGLES = {
    {  0,  1,  2,  0,  3,  1 },
    {  2,  1,  4,  1,  3,  4 },
    {  5,  3,  0,  4,  3,  5 },
    {  6,  7,  4,  7,  2,  4 },
    {  8,  6,  4,  9,  4, 10 },
    {  9, 11,  4,  4,  5, 10 },
    { 11,  8,  4,  0,  2,  7 },
    {  0,  7,  6,  0,  6,  8 },
    {  0,  8, 11,  0, 11,  9 },
    { 10,  5,  0, 10,  0,  9 },
}

function get_star_vertices()
    local vertices = {}
    for _, p in ipairs(STAR_POINTS) do
        table.insert(vertices, {
            x = p.x * SHAPE_SIZE / 256,
            y = p.y * SHAPE_SIZE / 256,
            z = p.z * SHAPE_SIZE / 256,
            tu = 0, tv = 0,
            r = p.r, g = p.g, b = p.b
        })
    end
    return vertices
end

function get_star_triangles()
    return STAR_TRIANGLES
end

function get_star_geometry_mode()
    return "G_CULL_BOTH", "G_LIGHTING | G_TEXTURE_GEN"
end

function get_star_texture_scaling()
    return 0x7FC0
end
