
---@param cc ColorCombiner
---@param shaderIndex integer
local function on_vertex_shader_create(cc, shaderIndex)
    local vertexShader = {}
    table.insert(vertexShader, "#version 150")
    table.insert(vertexShader, "in vec4 aVtxPos;")
    table.insert(vertexShader, "in vec2 aTexCoord;")
    table.insert(vertexShader, "out vec2 vTexCoord;")
    table.insert(vertexShader, "in vec4 aFog;")
    table.insert(vertexShader, "out vec4 vFog;")
    table.insert(vertexShader, "in vec2 aLightMap;")
    table.insert(vertexShader, "out vec2 vLightMap;")

    for i = 1, CC_MAX_INPUTS do
        table.insert(vertexShader, string.format("in vec4 aInput%d;", i))
        table.insert(vertexShader, string.format("out vec4 vInput%d;", i))
    end

    table.insert(vertexShader, "in vec3 aNormal;")
    table.insert(vertexShader, "out vec3 vNormal;")
    table.insert(vertexShader, "in vec3 aBarycentric;")
    table.insert(vertexShader, "out vec3 vBarycentric;")

    table.insert(vertexShader, "void main() {")
    table.insert(vertexShader, "vTexCoord = aTexCoord;")
    table.insert(vertexShader, "vFog = aFog;")
    table.insert(vertexShader, "vLightMap = aLightMap;")
    for i = 1, CC_MAX_INPUTS do
        table.insert(vertexShader, string.format("vInput%d = aInput%d;", i, i))
    end
    table.insert(vertexShader, "vNormal = aNormal;")
    table.insert(vertexShader, "vBarycentric = aBarycentric;")
    table.insert(vertexShader, "gl_Position = vec4(aVtxPos.x * -1.0, aVtxPos.yzw);")
    table.insert(vertexShader, "}")

    return table.concat(vertexShader, "\n")
end

hook_event(HOOK_ON_VERTEX_SHADER_CREATE, on_vertex_shader_create)

gfx_reload_shaders()