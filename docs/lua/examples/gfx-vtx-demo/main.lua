-- name: Gfx and Vtx manipulation demo
-- description: Press X to spawn three different shapes orbiting around Mario.

local SHAPE_TEXTURES = {}
for i = 0, 10 do
    SHAPE_TEXTURES[i] = get_texture_info("matrix_" .. i)
end

SHAPES = {
    {
        get_vertices = get_cube_vertices,
        get_triangles = get_cube_triangles,
        get_geometry_mode = get_cube_geometry_mode,
        get_texture_scaling = get_cube_texture_scaling,
    },
    {
        get_vertices = get_octahedron_vertices,
        get_triangles = get_octahedron_triangles,
        get_geometry_mode = get_octahedron_geometry_mode,
        get_texture_scaling = get_octahedron_texture_scaling,
    },
    {
        get_vertices = get_star_vertices,
        get_triangles = get_star_triangles,
        get_geometry_mode = get_star_geometry_mode,
        get_texture_scaling = get_star_texture_scaling,
    }
}


--- @param obj Object
--- Get a unique identifier for gfx and vtx allocation.
local function get_obj_identifier(obj)
    return tostring(obj._pointer)
end

--- @param obj Object
--- @param gfx Gfx
--- Set the geometry mode of the current shape.
local function set_geometry_mode(obj, gfx)
    local clear, set = SHAPES[obj.oAction].get_geometry_mode()
    gfx_set_command(gfx, "gsSPGeometryMode(%s, %s)", clear, set)
end

--- @param obj Object
--- @param gfx Gfx
--- @param on integer
--- Toggle on/off the texture rendering and set the texture scaling.
local function set_texture_scaling(obj, gfx, on)
    local scaling = SHAPES[obj.oAction].get_texture_scaling()
    gfx_set_command(gfx, "gsSPTexture(%i, %i, 0, G_TX_RENDERTILE, %i)", scaling, scaling, on)
end

--- @param obj Object
--- @param gfx Gfx
--- Update the texture of the current shape.
local function update_texture(obj, gfx)
    local texture = SHAPE_TEXTURES[obj.oAnimState].texture
    gfx_set_command(gfx, "gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_32b, 1, %t)", texture)
end

--- @param obj Object
--- @param gfx Gfx
--- Compute the vertices of the current shape and fill the vertex buffer.
local function compute_vertices(obj, gfx)
    local vertices = SHAPES[obj.oAction].get_vertices()
    local num_vertices = #vertices

    -- Create a new or retrieve an existing vertex buffer for the shape
    -- Use the object pointer to form a unique identifier
    local vtx_name = "shape_vertices_" .. get_obj_identifier(obj)
    local vtx = vtx_get_from_name(vtx_name)
    if vtx == nil then
        vtx = vtx_create(vtx_name, num_vertices)
    else
        vtx_resize(vtx, num_vertices)
    end

    -- Update the vertex command
    gfx_set_command(gfx, "gsSPVertex(%v, %i, 0)", vtx, num_vertices)

    -- Fill the vertex buffer
    for _, vertex in ipairs(vertices) do
        vtx.x = vertex.x
        vtx.y = vertex.y
        vtx.z = vertex.z
        vtx.tu = vertex.tu
        vtx.tv = vertex.tv
        vtx.r = vertex.r
        vtx.g = vertex.g
        vtx.b = vertex.b
        vtx.a = 0xFF
        vtx = vtx_get_next_vertex(vtx)
    end
end

--- @param obj Object
--- @param gfx Gfx
--- Build the triangles for the current shape.
local function build_triangles(obj, gfx)
    local triangles = SHAPES[obj.oAction].get_triangles()
    local num_triangles = #triangles

    -- Create a new or retrieve an existing triangles display list for the shape
    -- Use the object pointer to form a unique identifier
    local tris_name = "shape_triangles_" .. get_obj_identifier(obj)
    local tris = gfx_get_from_name(tris_name)
    if tris == nil then
        tris = gfx_create(tris_name, num_triangles + 1) -- +1 for the gsSPEndDisplayList command
    else
        gfx_resize(tris, num_triangles + 1)
    end

    -- Update the triangles command
    gfx_set_command(gfx, "gsSPDisplayList(%g)", tris)

    -- Fill the triangles display list
    for _, indices in ipairs(triangles) do
        if #indices == 6 then
            gfx_set_command(tris, "gsSP2Triangles(%i, %i, %i, 0, %i, %i, %i, 0)",
                indices[1], indices[2], indices[3],
                indices[4], indices[5], indices[6]
            )
        elseif #indices == 3 then
            gfx_set_command(tris, "gsSP1Triangle(%i, %i, %i, 0)",
                indices[1], indices[2], indices[3]
            )
        end
        tris = gfx_get_next_command(tris)
    end
    gfx_set_command(tris, "gsSPEndDisplayList()")
end

--- @param node GraphNode
--- @param matStackIndex integer
--- The custom GEO ASM function.
function geo_update_shape(node, matStackIndex)
    local obj = geo_get_current_object()

    -- Create a new display list that will be attached to the display list node
    -- To get a different display list for each object, we can use the object pointer to form a unique identifier
    local gfx_name = "shape_dl_" .. get_obj_identifier(obj)
    local gfx = gfx_get_from_name(gfx_name)
    if gfx == nil then

        -- Get and copy the template to the newly created display list
        local gfx_template = gfx_get_from_name("shape_template_dl")
        local gfx_template_length = gfx_get_length(gfx_template)
        gfx = gfx_create(gfx_name, gfx_template_length)
        gfx_copy(gfx, gfx_template, gfx_template_length)
    end

    -- Now fill the display list with the appropriate commands (see actors/shape/model.inc.c)
    -- We can retrieve the commands directly with `gfx_get_command`
    -- Index | Command              | What to do
    -- ------|----------------------|----------------------------------------
    --  [00] | gsSPGeometryMode     | Change the geometry mode
    --  [02] | gsSPTexture          | Change the texture scaling
    --  [03] | gsDPSetTextureImage  | Update the texture
    --  [10] | gsSPVertex           | Compute vertices
    --  [11] | gsSPDisplayList      | Build triangles
    --  [12] | gsSPTexture          | Change the texture scaling

    -- Change the geometry mode
    local cmd_geometry_mode = gfx_get_command(gfx, 0)
    set_geometry_mode(obj, cmd_geometry_mode)

    -- Change the texture scaling
    local cmd_texture_scaling_1 = gfx_get_command(gfx, 2)
    set_texture_scaling(obj, cmd_texture_scaling_1, 1)
    local cmd_texture_scaling_2 = gfx_get_command(gfx, 12)
    set_texture_scaling(obj, cmd_texture_scaling_2, 0)

    -- Update texture
    local cmd_texture = gfx_get_command(gfx, 3)
    update_texture(obj, cmd_texture)

    -- Compute vertices
    local cmd_vertices = gfx_get_command(gfx, 10)
    compute_vertices(obj, cmd_vertices)

    -- Build triangles
    local cmd_triangles = gfx_get_command(gfx, 11)
    build_triangles(obj, cmd_triangles)

    -- Update the graph node display list
    cast_graph_node(node.next).displayList = gfx
end

--- @param obj Object
--- Delete allocated gfx and vtx for this object.
local function on_object_unload(obj)

    local gfx = gfx_get_from_name("shape_dl_" .. get_obj_identifier(obj))
    if gfx then gfx_delete(gfx) end

    local tris = gfx_get_from_name("shape_triangles_" .. get_obj_identifier(obj))
    if tris then gfx_delete(tris) end

    local vtx = vtx_get_from_name("shape_vertices_" .. get_obj_identifier(obj))
    if vtx then vtx_delete(vtx) end
end

hook_event(HOOK_ON_OBJECT_UNLOAD, on_object_unload)
