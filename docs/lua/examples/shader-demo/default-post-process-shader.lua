local function on_post_process_vertex_shader_create()
    local vertexShader = {}

    table.insert(vertexShader, "in vec4 aVtxPos;")
    table.insert(vertexShader, "in vec2 aTexCoord;")
    table.insert(vertexShader, "out vec4 vVtxPos;")
    table.insert(vertexShader, "out vec2 vTexCoord;")
    table.insert(vertexShader, "void main() {")
    table.insert(vertexShader, "vVtxPos = aVtxPos;")
    table.insert(vertexShader, "vTexCoord = aTexCoord;")
    table.insert(vertexShader, "gl_Position = aVtxPos;")
    table.insert(vertexShader, "}")

    return table.concat(vertexShader, "\n")
end

local function on_post_process_fragment_shader_create(cc)
    local fragmentShader = {}

    table.insert(fragmentShader, "uniform sampler2D uPassTex;")
    table.insert(fragmentShader, "in vec4 vVtxPos;")
    table.insert(fragmentShader, "in vec2 vTexCoord;")
    table.insert(fragmentShader, "out vec4 fragColor;")
    table.insert(fragmentShader, "void main() {")
    table.insert(fragmentShader, "fragColor = texture(uPassTex, vTexCoord);")
    table.insert(fragmentShader, "}")

    return table.concat(fragmentShader, "\n")
end

hook_event(HOOK_ON_POST_PROCESS_VERTEX_SHADER_CREATE, on_post_process_vertex_shader_create)
hook_event(HOOK_ON_POST_PROCESS_FRAGMENT_SHADER_CREATE, on_post_process_fragment_shader_create)
