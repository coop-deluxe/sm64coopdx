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
    local vtx = gfx_get_vertex_buffer(gfx)
    for i, vertex in ipairs(vertices) do
        local v = vtx_get_vertex(vtx, i - 1)
        v.x = vertex.x
        v.y = vertex.y
        v.z = vertex.z
        v.tu = vertex.tu
        v.tv = vertex.tv
        v.r = vertex.r
        v.g = vertex.g
        v.b = vertex.b
        v.a = 0xFF
    end
end

--- @param gfx Gfx
--- Build the triangles for the current shape.
local function build_triangles(gfx)
    local triangles = SHAPES[current_shape + 1].get_triangles()
    for i, indices in ipairs(triangles) do
        local cmd = gfx_get_command(gfx, i - 1)
        if #indices == 6 then
            gfx_set_command(cmd, "gsSP2Triangles(%i, %i, %i, 0, %i, %i, %i, 0)",
                indices[1], indices[2], indices[3],
                indices[4], indices[5], indices[6]
            )
        elseif #indices == 3 then
            gfx_set_command(cmd, "gsSP1Triangle(%i, %i, %i, 0)",
                indices[1], indices[2], indices[3]
            )
        end
    end
    local cmd_end = gfx_get_command(gfx, #triangles)
    gfx_set_command(cmd_end, "gsSPEndDisplayList()")
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
local function set_texture_scaling(gfx, on)
    local scaling = SHAPES[current_shape + 1].get_texture_scaling()
    gfx_set_command(gfx, "gsSPTexture(%i, %i, 0, G_TX_RENDERTILE, %i)", scaling, scaling, on)
end

--- @param node GraphNode
--- @param matStackIndex integer
--- The custom GEO ASM function.
function geo_update_shape(node, matStackIndex)
    local gfx = cast_graph_node(node.next).displayList

    -- Since the layout of the node display list is known, no need to parse it
    -- We can retrieve the commands directly with `gfx_get_command`
    -- Index | Command              | Goal
    -- ------|----------------------|----------------------------------------
    --   [0] | gsSPGeometryMode     | Change the geometry mode
    --   [2] | gsSPTexture          | Change the texture scaling
    --   [3] | gsDPLoadTextureBlock | Update the texture
    --  [10] | gsSPVertex           | Compute vertices
    --  [11] | gsSPDisplayList      | Build triangles
    --  [12] | gsSPTexture          | Change the texture scaling

    -- Change the geometry mode
    local cmd_geometry_mode = gfx_get_command(gfx, 0)
    set_geometry_mode(cmd_geometry_mode)

    -- Change the texture scaling
    local cmd_texture_scaling_1 = gfx_get_command(gfx, 2)
    set_texture_scaling(cmd_texture_scaling_1, 1)
    local cmd_texture_scaling_2 = gfx_get_command(gfx, 12)
    set_texture_scaling(cmd_texture_scaling_2, 0)

    -- Compute vertices
    local cmd_vertices = gfx_get_command(gfx, 10)
    compute_vertices(cmd_vertices)

    -- Build triangles
    local cmd_triangles = gfx_get_command(gfx, 11)
    local gfx_triangles = gfx_get_display_list(cmd_triangles)
    build_triangles(gfx_triangles)

    -- Update texture
    local cmd_texture = gfx_get_command(gfx, 3)
    update_texture(cmd_texture)
end
