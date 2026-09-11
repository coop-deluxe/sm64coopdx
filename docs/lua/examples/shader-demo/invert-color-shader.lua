-- name: Inverted Color Shader
-- description: This is an example of a post process fragment shader!

local function on_post_process_fragment_shader_create(cc)
    local fragmentShader = {}

    table.insert(fragmentShader, "#version 410 core")
    table.insert(fragmentShader, "uniform sampler2D uPassTex;")
    table.insert(fragmentShader, "in vec4 vVtxPos;")
    table.insert(fragmentShader, "in vec2 vTexCoord;")
    table.insert(fragmentShader, "out vec4 fragColor;")
    table.insert(fragmentShader, "void main() {")
    table.insert(fragmentShader, "vec4 texColor = texture(uPassTex, vTexCoord);")
    table.insert(fragmentShader, "fragColor = vec4(1.0 - texColor.rgb, texColor.a);")
    table.insert(fragmentShader, "}")

    return table.concat(fragmentShader, "\n")
end

hook_event(HOOK_ON_POST_PROCESS_FRAGMENT_SHADER_CREATE, on_post_process_fragment_shader_create)

gfx_reload_shaders()
