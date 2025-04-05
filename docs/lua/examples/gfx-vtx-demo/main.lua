-- name: Gfx and Vtx manipulation demo
-- description: Press X to move the shape in front of Mario.\nPress Y to change the shape.

local SHAPE_TEXTURES = {}
for i = 0, 10 do
    SHAPE_TEXTURES[i] = get_texture_info("matrix_" .. i)
end

SHAPES = {
    {
        name = "Cube",
        get_vertices = get_cube_vertices,
        get_triangles = get_cube_triangles,
        get_geometry_mode = get_cube_geometry_mode,
        get_texture_scaling = get_cube_texture_scaling,
    },
    {
        name = "Octahedron",
        get_vertices = get_octahedron_vertices,
        get_triangles = get_octahedron_triangles,
        get_geometry_mode = get_octahedron_geometry_mode,
        get_texture_scaling = get_octahedron_texture_scaling,
    },
    {
        name = "Star",
        get_vertices = get_star_vertices,
        get_triangles = get_star_triangles,
        get_geometry_mode = get_star_geometry_mode,
        get_texture_scaling = get_star_texture_scaling,
    }
}

local triangle_index = 0

--- @param x integer
--- @param shift integer
--- @param width integer
--- Reverse of _SHIFTL(x, shift, width). Return the `width` bits at position `shift`.
local function unshiftl(x, shift, width)
    return (x >> shift) & ((1 << width) - 1)
end

--- @param gfx Gfx
--- Set the geometry mode of the current shape.
local function set_geometry_mode(gfx)
    local clear, set = SHAPES[current_shape + 1].get_geometry_mode()
    gfx_set_command(gfx, "gsSPGeometryMode(%s, %s)", clear, set)
end

--- @param gfx Gfx
--- Compute the vertices of the current shape and fill the vertex buffer.
local function compute_vertices(gfx)
    local vertices = SHAPES[current_shape + 1].get_vertices()
    for i, v in ipairs(vertices) do
        local vtx = gfx_get_vtx(gfx, i - 1)
        gfx_set_vtx_v(vtx, v.x, v.y, v.z, v.tu, v.tv, v.r, v.g, v.b, 0xFF)
    end
end

--- @param gfx Gfx
--- @param i integer
--- Build the triangles for the current shape.
--- Since there can be only 2 triangles per command, we need to call this function multiple times.
local function build_triangles(gfx, i)
    local triangles = SHAPES[current_shape + 1].get_triangles(i)
    if #triangles == 6 then
        gfx_set_command(gfx, "gsSP2Triangles(%i, %i, %i, 0, %i, %i, %i, 0)",
            triangles[1], triangles[2], triangles[3],
            triangles[4], triangles[5], triangles[6]
        )
    elseif #triangles == 3 then
        gfx_set_command(gfx, "gsSP1Triangle(%i, %i, %i, 0)",
            triangles[1], triangles[2], triangles[3]
        )
    else
        -- We can't replace the unused triangle commands by "gsSPEndDisplayList()", because
        -- it will permanently shorten the display list for future gfx_parse calls.
        -- Instead we can fill them with the command below, which is equivalent to a NoOp.
        gfx_set_command(gfx, "gsSP1Triangle(0,0,0,0)")
    end
end

--- @param gfx Gfx
--- Update the texture of the current shape.
local function update_texture(gfx)
    local obj = geo_get_current_object()
    gfx_set_command(gfx, "gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_32b, 1, %t)", SHAPE_TEXTURES[obj.oAnimState].texture)
end

--- @param gfx Gfx
--- @param on integer
--- Toggle on/off the texture rendering and set the texture scaling.
local function toggle_texture(gfx, on)
    local scaling = SHAPES[current_shape + 1].get_texture_scaling()
    gfx_set_command(gfx, "gsSPTexture(%i, %i, 0, G_TX_RENDERTILE, %i)", scaling, scaling, on)
end

--- @param gfx Gfx
--- @param op integer
--- Update the shape display list.
local function update_shape(gfx, op)

    -- gsSPGeometryMode: change the geometry mode
    if op == G_GEOMETRYMODE then
        set_geometry_mode(gfx)

    -- gsSPVertex: compute and fill the vertex buffer
    elseif op == G_VTX then
        compute_vertices(gfx)

    -- gsSP1Triangle/gsSP2Triangles: build up to 2 triangles per call
    -- We need to keep track of the command index to know which triangles to build
    elseif op == G_TRI1 or op == G_TRI2 then
        build_triangles(gfx, triangle_index)
        triangle_index = triangle_index + 1

    -- gsDPSetTextureImage: change the texture
    elseif op == G_SETTIMG then
        update_texture(gfx)

    -- gsSPTexture: toggle the texture rendering and set scaling
    -- Read the toggle of the current command by directly accessing the words fields
    elseif op == G_TEXTURE then
        toggle_texture(gfx, unshiftl(gfx.w0, 1, 7))
    end
end

--- @param node GraphNode
--- @param matStackIndex integer
--- The custom GEO ASM function.
function geo_update_shape(node, matStackIndex)
    local gfx = cast_graph_node(node.next).displayList
    triangle_index = 0
    gfx_parse(gfx, update_shape)
end
