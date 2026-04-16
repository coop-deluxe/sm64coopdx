---@param item number
---@param with_alpha boolean
---@param only_alpha boolean
---@param hint_single_element boolean
---@return string
local function shader_item_to_str(item, with_alpha, only_alpha, hint_single_element)
    if not only_alpha then
        if item == SHADER_0 then
            return with_alpha and "vec4(0.0, 0.0, 0.0, 0.0)" or "vec3(0.0, 0.0, 0.0)"
        elseif item == SHADER_1 then
            return with_alpha and "vec4(1.0, 1.0, 1.0, 1.0)" or "vec3(1.0, 1.0, 1.0)"
        elseif item >= SHADER_INPUT_1 and item <= SHADER_INPUT_8 then
            local idx = item - SHADER_INPUT_1 + 1
            local name = "vInput" .. idx
            return with_alpha and name or (name .. ".rgb")
        elseif item == SHADER_TEXEL0 then
            return with_alpha and "texVal0" or "texVal0.rgb"
        elseif item == SHADER_TEXEL0A then
            if hint_single_element then return "texVal0.a" end
            return with_alpha and
                "vec4(texVal0.a, texVal0.a, texVal0.a, texVal0.a)" or
                "vec3(texVal0.a, texVal0.a, texVal0.a)"
        elseif item == SHADER_TEXEL1 then
            return with_alpha and "texVal1" or "texVal1.rgb"
        elseif item == SHADER_TEXEL1A then
            if hint_single_element then return "texVal1.a" end
            return with_alpha and
                "vec4(texVal1.a, texVal1.a, texVal1.a, texVal1.a)" or
                "vec3(texVal1.a, texVal1.a, texVal1.a)"
        elseif item == SHADER_COMBINED then
            return with_alpha and "texel" or "texel.rgb"
        elseif item == SHADER_COMBINEDA then
            if hint_single_element then return "texel.a" end
            return with_alpha and
                "vec4(texel.a, texel.a, texel.a, texel.a)" or
                "vec3(texel.a, texel.a, texel.a)"
        elseif item == SHADER_NOISE then
            return with_alpha and "vec4(noise)" or "vec3(noise)"
        end
    else
        if item == SHADER_0 then
            return "0.0"
        elseif item == SHADER_1 then
            return "1.0"
        elseif item >= SHADER_INPUT_1 and item <= SHADER_INPUT_8 then
            local idx = item - SHADER_INPUT_1 + 1
            return "vInput" .. idx .. ".a"
        elseif item == SHADER_TEXEL0 or item == SHADER_TEXEL0A then
            return "texVal0.a"
        elseif item == SHADER_TEXEL1 or item == SHADER_TEXEL1A then
            return "texVal1.a"
        elseif item == SHADER_COMBINED or item == SHADER_COMBINEDA then
            return "texel.a"
        elseif item == SHADER_NOISE then
            return "noise.a"
        end
    end
    return "unknown"
end

---@param cmd number[]
---@param do_single boolean
---@param do_multiply boolean
---@param do_mix boolean
---@param with_alpha boolean
---@param only_alpha boolean
---@return string
local function append_formula(cmd, do_single, do_multiply, do_mix, with_alpha, only_alpha)
    local base = (only_alpha and 4 or 0)

    if do_single then
        return shader_item_to_str(cmd[base + 4], with_alpha, only_alpha, false)
    elseif do_multiply then
        local a = shader_item_to_str(cmd[base + 1], with_alpha, only_alpha, false)
        local c = shader_item_to_str(cmd[base + 3], with_alpha, only_alpha, true)
        return a .. " * " .. c
    elseif do_mix then
        local b = shader_item_to_str(cmd[base + 2], with_alpha, only_alpha, false)
        local a = shader_item_to_str(cmd[base + 1], with_alpha, only_alpha, false)
        local c = shader_item_to_str(cmd[base + 3], with_alpha, only_alpha, true)
        return "mix(" .. b .. ", " .. a .. ", " .. c .. ")"
    else
        local a = shader_item_to_str(cmd[base + 1], with_alpha, only_alpha, false)
        local b = shader_item_to_str(cmd[base + 2], with_alpha, only_alpha, false)
        local c = shader_item_to_str(cmd[base + 3], with_alpha, only_alpha, true)
        local d = shader_item_to_str(cmd[base + 4], with_alpha, only_alpha, false)
        return "(" .. a .. " - " .. b .. ") * " .. c .. " + " .. d
    end
end

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
    table.insert(vertexShader, "gl_Position = aVtxPos;")
    table.insert(vertexShader, "}")

    return table.concat(vertexShader, "\n")
end

---@param cc ColorCombiner
---@param shaderIndex integer
local function on_fragment_shader_create(cc, shaderIndex)
    local ccf = gfx_color_combiner_get_features(cc)
    local opt_alpha = cc.cm.flags & USE_ALPHA ~= 0
    local opt_fog = cc.cm.flags & USE_FOG ~= 0
    local opt_texture_edge = cc.cm.flags & TEXTURE_EDGE ~= 0
    local opt_2cycle = cc.cm.flags & USE_2CYCLE ~= 0
    local opt_light_map = cc.cm.flags & LIGHT_MAP ~= 0
    local opt_dither = cc.cm.flags & USE_DITHER ~= 0

    local fragmentShader = {}
    table.insert(fragmentShader, "#version 150")

    table.insert(fragmentShader, "out vec4 fragColor;")
    table.insert(fragmentShader, "in vec2 vTexCoord;")
    table.insert(fragmentShader, "in vec4 vFog;")
    table.insert(fragmentShader, "in vec2 vLightMap;")

    for i = 1, CC_MAX_INPUTS do
        table.insert(fragmentShader, string.format("in vec4 vInput%d;", i))
    end

    table.insert(fragmentShader, "in vec3 vNormal;")
    table.insert(fragmentShader, "in vec3 vBarycentric;")

    if ccf.used_textures[1] then
        table.insert(fragmentShader, "uniform sampler2D uTex0;")
        table.insert(fragmentShader, "uniform vec2 uTex0Size;")
        table.insert(fragmentShader, "uniform bool uTex0Filter;")
    end
    if ccf.used_textures[2] then
        table.insert(fragmentShader, "uniform sampler2D uTex1;")
        table.insert(fragmentShader, "uniform vec2 uTex1Size;")
        table.insert(fragmentShader, "uniform bool uTex1Filter;")
    end

    if ccf.used_textures[1] or ccf.used_textures[2] then
        table.insert(fragmentShader, "#define TEX_OFFSET(off) texture(tex, texCoord - (off)/texSize)")
        table.insert(fragmentShader, "vec4 filter3point(in sampler2D tex, in vec2 texCoord, in vec2 texSize) {")
        table.insert(fragmentShader, "    vec2 offset = fract(texCoord*texSize - vec2(0.5));")
        table.insert(fragmentShader, "    offset -= step(1.0, offset.x + offset.y);")
        table.insert(fragmentShader, "    vec4 c0 = TEX_OFFSET(offset);")
        table.insert(fragmentShader, "    vec4 c1 = TEX_OFFSET(vec2(offset.x - sign(offset.x), offset.y));")
        table.insert(fragmentShader, "    vec4 c2 = TEX_OFFSET(vec2(offset.x, offset.y - sign(offset.y)));")
        table.insert(fragmentShader, "    return c0 + abs(offset.x)*(c1-c0) + abs(offset.y)*(c2-c0);")
        table.insert(fragmentShader, "}")
        table.insert(fragmentShader, "vec4 sampleTex(in sampler2D tex, in vec2 uv, in vec2 texSize, in bool dofilter, in int filterType) {")
        table.insert(fragmentShader, "    if (dofilter && filterType == 2) return filter3point(tex, uv, texSize);")
        table.insert(fragmentShader, "    else return texture(tex, uv);")
        table.insert(fragmentShader, "}")
    end

    if (opt_alpha and opt_dither) or ccf.do_noise then
        table.insert(fragmentShader, "uniform float uFrameCount;")
        table.insert(fragmentShader, "float random(in vec3 value) {")
        table.insert(fragmentShader, "    float random = dot(sin(value), vec3(12.9898, 78.233, 37.719));")
        table.insert(fragmentShader, "    return fract(sin(random) * 143758.5453);")
        table.insert(fragmentShader, "}")
    end

    if opt_light_map then
        table.insert(fragmentShader, "uniform vec3 uLightmapColor;")
    end
    table.insert(fragmentShader, "uniform int uFilter;")

    table.insert(fragmentShader, "void main() {")
    if (opt_alpha and opt_dither) or ccf.do_noise then
        table.insert(fragmentShader, "float noise = floor(random(floor(vec3(gl_FragCoord.xy, uFrameCount))) + 0.5);")
    end

    if ccf.used_textures[1] then
        table.insert(fragmentShader, "vec4 texVal0 = sampleTex(uTex0, vTexCoord, uTex0Size, uTex0Filter, uFilter);")
    end
    if ccf.used_textures[2] then
        if opt_light_map then
            table.insert(fragmentShader, "vec4 texVal1 = sampleTex(uTex1, vLightMap, uTex1Size, uTex1Filter, uFilter);")
            table.insert(fragmentShader, "texVal0.rgb *= uLightmapColor.rgb;")
            table.insert(fragmentShader, "texVal1.rgb = texVal1.rgb * texVal1.rgb + texVal1.rgb;")
        else
            table.insert(fragmentShader, "vec4 texVal1 = sampleTex(uTex1, vTexCoord, uTex1Size, uTex1Filter, uFilter);")
        end
    end

    table.insert(fragmentShader, (opt_alpha and "vec4 texel = " or "vec3 texel = "))

    for i = 0, (opt_2cycle and 1 or 0) do
        local cmd = {}
        for j = 0, CC_MAX_INPUTS - 1 do
            cmd[j + 1] = cc.shader_commands[i * CC_MAX_INPUTS + j + 1]
        end
        local idx = i * 2

        if not ccf.color_alpha_same[i + 1] and opt_alpha then
            local color = append_formula(cmd, ccf.do_single[idx + 1], ccf.do_multiply[idx + 1], ccf.do_mix[idx + 1], false, false)
            local alpha = append_formula(cmd, ccf.do_single[idx + 2], ccf.do_multiply[idx + 2], ccf.do_mix[idx + 2], true, true)
            table.insert(fragmentShader, "vec4(" .. color .. ", " .. alpha .. ")")
        else
            table.insert(fragmentShader, append_formula(cmd, ccf.do_single[idx + 1], ccf.do_multiply[idx + 1], ccf.do_mix[idx + 1], opt_alpha, false))
        end
        table.insert(fragmentShader, ";")
        if i == 0 and opt_2cycle then table.insert(fragmentShader, "texel = ") end
    end

    if opt_texture_edge and opt_alpha then
        table.insert(fragmentShader, "if (texel.a > 0.3) texel.a = 1.0; else discard;")
    end
    if opt_fog then
        if opt_alpha then
            table.insert(fragmentShader, "texel = vec4(mix(texel.rgb, vFog.rgb, vFog.a), texel.a);")
        else
            table.insert(fragmentShader, "texel = mix(texel, vFog.rgb, vFog.a);")
        end
    end
    if opt_alpha and opt_dither then
        table.insert(fragmentShader, "texel.a *= noise;")
    end

    if opt_alpha then
        table.insert(fragmentShader, "fragColor = texel;")
    else
        table.insert(fragmentShader, "fragColor = vec4(texel, 1.0);")
    end
    table.insert(fragmentShader, "}")

    return table.concat(fragmentShader, "\n")
end

hook_event(HOOK_ON_VERTEX_SHADER_CREATE, on_vertex_shader_create)
hook_event(HOOK_ON_FRAGMENT_SHADER_CREATE, on_fragment_shader_create)

gfx_reload_shaders()