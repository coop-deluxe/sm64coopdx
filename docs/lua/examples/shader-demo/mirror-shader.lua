-- name: Mirror Shader
-- description: This is an example of a post process vertex shader!

local function on_post_process_vertex_shader_create()
    local vertexShader = {}

    table.insert(vertexShader, "#version 410 core")
    table.insert(vertexShader, "in vec4 aVtxPos;")
    table.insert(vertexShader, "out vec4 vVtxPos;")
    table.insert(vertexShader, "in vec2 aTexCoord;")
    table.insert(vertexShader, "out vec2 vTexCoord;")
    table.insert(vertexShader, "void main() {")
    table.insert(vertexShader, "vVtxPos = aVtxPos;")
    table.insert(vertexShader, "vTexCoord = aTexCoord;")
    table.insert(vertexShader, "gl_Position = vec4(aVtxPos.x * -1.0, aVtxPos.yzw);")
    table.insert(vertexShader, "}")

    return table.concat(vertexShader, "\n")
end

hook_event(HOOK_ON_POST_PROCESS_VERTEX_SHADER_CREATE, on_post_process_vertex_shader_create)

gfx_reload_shaders()
