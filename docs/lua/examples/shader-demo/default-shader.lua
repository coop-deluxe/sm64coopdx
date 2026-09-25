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
            return "noise"
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
local function on_vertex_shader_create(cc)
    local opt_fog = cc.cm.flags & CM_FLAG_USE_FOG ~= 0
    local opt_tex_persp = cc.cm.flags & CM_FLAG_TEX_PERSP ~= 0

    local vs = {}

    table.insert(vs, "in vec4 aVtxPos;")
    table.insert(vs, "in vec4 aLocalPos;")

    for t = 0, 1 do
        table.insert(vs, string.format("in vec2 aTexCoord%d;", t))

        if not opt_tex_persp then
            table.insert(vs, string.format("noperspective out vec2 vTexCoord%d;", t))
        else
            table.insert(vs, string.format("out vec2 vTexCoord%d;", t))
        end
    end

    table.insert(vs, "in vec2 aLightMap;")
    table.insert(vs, "out vec2 vLightMap;")

    for i = 1, CC_MAX_INPUTS do
        table.insert(vs, string.format("in vec4 aInput%d;", i))
        table.insert(vs, string.format("out vec4 vInput%d;", i))
    end

    table.insert(vs, "in vec3 aNormal;")
    table.insert(vs, "in vec3 aBarycentric;")

    if opt_fog then
        table.insert(vs, "out float vFogZ;")
        table.insert(vs, "uniform float uFogMul;")
        table.insert(vs, "uniform float uFogIntensity;")
        table.insert(vs, "uniform float uFogOffset;")
        table.insert(vs, "uniform float uDepthZSub;")
        table.insert(vs, "uniform float uDepthZMult;")
        table.insert(vs, "uniform float uDepthZAdd;")
    end

    table.insert(vs, "void main() {")

    for t = 0, 1 do
        table.insert(vs, string.format("vTexCoord%d = aTexCoord%d;", t, t))
    end

    table.insert(vs, "vLightMap = aLightMap;")

    for i = 1, CC_MAX_INPUTS do
        table.insert(vs, string.format("vInput%d = aInput%d;", i, i))
    end

    table.insert(vs, "gl_Position = aVtxPos;")

    if opt_fog then
        table.insert(vs, "float w = max(abs(aVtxPos.w), 0.001);")
        table.insert(vs, "float winv = 1.0 / w;")

        table.insert(vs, "float adjClipZ = aVtxPos.z;")
        table.insert(vs, "adjClipZ -= uDepthZSub;")
        table.insert(vs, "adjClipZ *= uDepthZMult;")
        table.insert(vs, "adjClipZ += uDepthZAdd;")

        table.insert(vs, "float fog_z = (adjClipZ * winv * uFogMul * uFogIntensity) + uFogOffset;")
        table.insert(vs, "vFogZ = clamp(fog_z / 255.0, 0.0, 1.0);")
    end

    table.insert(vs, "}")

    return table.concat(vs, "\n")
end

---@param cc ColorCombiner
local function on_fragment_shader_create(cc)
    local ccf = gfx_color_combiner_get_features(cc)

    local opt_alpha = cc.cm.flags & CM_FLAG_USE_ALPHA ~= 0
    local opt_fog = cc.cm.flags & CM_FLAG_USE_FOG ~= 0
    local opt_texture_edge = cc.cm.flags & CM_FLAG_TEXTURE_EDGE ~= 0
    local opt_2cycle = cc.cm.flags & CM_FLAG_USE_2CYCLE ~= 0
    local opt_light_map = cc.cm.flags & CM_FLAG_LIGHT_MAP ~= 0
    local opt_dither = cc.cm.flags & CM_FLAG_USE_DITHER ~= 0
    local world_geometry = cc.cm.flags & CM_FLAG_WORLD_GEOMETRY ~= 0
    local opt_tex_persp = cc.cm.flags & CM_FLAG_TEX_PERSP ~= 0

    local fs = {}

    table.insert(fs, "out vec4 fragColor;")

    for t = 0, 1 do
        if not opt_tex_persp then
            table.insert(fs, string.format("noperspective in vec2 vTexCoord%d;", t))
        else
            table.insert(fs, string.format("in vec2 vTexCoord%d;", t))
        end
    end

    table.insert(fs, "in vec2 vLightMap;")

    for i = 1, CC_MAX_INPUTS do
        table.insert(fs, string.format("in vec4 vInput%d;", i))
    end

    if opt_fog then
        table.insert(fs, "in float vFogZ;")
    end

    if ccf.used_textures[1] then
        table.insert(fs, "uniform sampler2D uTex0;")
        table.insert(fs, "uniform vec2 uTex0Size;")
        table.insert(fs, "uniform bool uTex0Filter;")
    end

    if ccf.used_textures[2] then
        table.insert(fs, "uniform sampler2D uTex1;")
        table.insert(fs, "uniform vec2 uTex1Size;")
        table.insert(fs, "uniform bool uTex1Filter;")
    end

    -- 3-point filtering
    if ccf.used_textures[1] or ccf.used_textures[2] then
        table.insert(fs, "#define TEX_OFFSET(off) texture(tex, texCoord - (off)/texSize)")
        table.insert(fs, "vec4 filter3point(in sampler2D tex, in vec2 texCoord, in vec2 texSize) {")
        table.insert(fs, "    vec2 offset = fract(texCoord * texSize - vec2(0.5));")
        table.insert(fs, "    offset -= step(1.0, offset.x + offset.y);")
        table.insert(fs, "    vec4 c0 = TEX_OFFSET(offset);")
        table.insert(fs, "    vec4 c1 = TEX_OFFSET(vec2(offset.x - sign(offset.x), offset.y));")
        table.insert(fs, "    vec4 c2 = TEX_OFFSET(vec2(offset.x, offset.y - sign(offset.y)));")
        table.insert(fs, "    return c0 + abs(offset.x)*(c1-c0) + abs(offset.y)*(c2-c0);")
        table.insert(fs, "}")

        table.insert(fs, "vec4 sampleTex(in sampler2D tex, in vec2 uv, in vec2 texSize, in bool dofilter, in int filterType) {")
        table.insert(fs, "    if (dofilter && filterType == 2) {")
        table.insert(fs, "        return filter3point(tex, uv, texSize);")
        table.insert(fs, "    }")
        table.insert(fs, "    return texture(tex, uv);")
        table.insert(fs, "}")
    end

    if world_geometry then
        table.insert(fs, "float dither4x4(vec2 position, float brightness) {")
        table.insert(fs, "    int x = int(mod(position.x, 4.0));")
        table.insert(fs, "    int y = int(mod(position.y, 4.0));")
        table.insert(fs, "    int index = x + y * 4;")
        table.insert(fs, "    float limit = 0.0;")
        table.insert(fs, "    if (x < 8) {")
        table.insert(fs, "        if (index == 0) limit = 0.0625;")
        table.insert(fs, "        if (index == 1) limit = 0.5625;")
        table.insert(fs, "        if (index == 2) limit = 0.1875;")
        table.insert(fs, "        if (index == 3) limit = 0.6875;")
        table.insert(fs, "        if (index == 4) limit = 0.8125;")
        table.insert(fs, "        if (index == 5) limit = 0.3125;")
        table.insert(fs, "        if (index == 6) limit = 0.9375;")
        table.insert(fs, "        if (index == 7) limit = 0.4375;")
        table.insert(fs, "        if (index == 8) limit = 0.25;")
        table.insert(fs, "        if (index == 9) limit = 0.75;")
        table.insert(fs, "        if (index == 10) limit = 0.125;")
        table.insert(fs, "        if (index == 11) limit = 0.625;")
        table.insert(fs, "        if (index == 12) limit = 1.0;")
        table.insert(fs, "        if (index == 13) limit = 0.5;")
        table.insert(fs, "        if (index == 14) limit = 0.875;")
        table.insert(fs, "        if (index == 15) limit = 0.375;")
        table.insert(fs, "    }")
        table.insert(fs, "    return brightness < limit ? 0.0 : 1.0;")
        table.insert(fs, "}")

        table.insert(fs, "vec3 rgb2hsv(vec3 c) {")
        table.insert(fs, "    vec4 K = vec4(0.0, -1.0/3.0, 2.0/3.0, -1.0);")
        table.insert(fs, "    vec4 p = mix(vec4(c.bg, K.wz),")
        table.insert(fs, "                 vec4(c.gb, K.xy),")
        table.insert(fs, "                 step(c.b, c.g));")
        table.insert(fs, "    vec4 q = mix(vec4(p.xyw, c.r),")
        table.insert(fs, "                 vec4(c.r, p.yzx),")
        table.insert(fs, "                 step(p.x, c.r));")
        table.insert(fs, "    float d = q.x - min(q.w, q.y);")
        table.insert(fs, "    float e = 1.0e-10;")
        table.insert(fs, "    return vec3(")
        table.insert(fs, "        abs(q.z + (q.w - q.y) / (6.0 * d + e)),")
        table.insert(fs, "        d / (q.x + e),")
        table.insert(fs, "        q.x")
        table.insert(fs, "    );")
        table.insert(fs, "}")

        table.insert(fs, "")

        table.insert(fs, "vec3 hsv2rgb(vec3 c) {")
        table.insert(fs, "    vec3 p = abs(fract(c.xxx + vec3(0.0, 2.0/3.0, 1.0/3.0)) * 6.0 - 3.0);")
        table.insert(fs, "    return c.z * mix(vec3(1.0), clamp(p - 1.0, 0.0, 1.0), c.y);")
        table.insert(fs, "}")
    end

    if (opt_alpha and opt_dither) or ccf.do_noise then
        table.insert(fs, "uniform uint uFrameCount;")
        table.insert(fs, "float random(in vec3 v) {")
        table.insert(fs, "    float r = dot(sin(v), vec3(12.9898, 78.233, 37.719));")
        table.insert(fs, "    return fract(sin(r) * 143758.5453);")
        table.insert(fs, "}")
    end

    if opt_light_map then
        table.insert(fs, "uniform vec3 uLightmapColor;")
    end

    if world_geometry then
        table.insert(fs, "uniform bool uShaderFlagsEnabled;")
        table.insert(fs, "uniform int uShaderFlags[" .. SHADER_FLAG_MAX .. "];")
        table.insert(fs, "uniform float uShaderFlagValues[" .. SHADER_FLAG_MAX .. "];")
    end

    if opt_fog then
        table.insert(fs, "uniform vec3 uFogColor;")
    end

    table.insert(fs, "uniform int uFilter;")

    table.insert(fs, "void main() {")

    if (opt_alpha and opt_dither) or ccf.do_noise then
        table.insert(fs, "float noise = floor(random(floor(vec3(gl_FragCoord.xy, uFrameCount))) + 0.5);")
    end

    if ccf.used_textures[1] then
        table.insert(fs, "vec4 texVal0 = sampleTex(uTex0, vTexCoord0, uTex0Size, uTex0Filter, uFilter);")
    end

    if ccf.used_textures[2] then
        if opt_light_map then
            table.insert(fs, "vec4 texVal1 = sampleTex(uTex1, vLightMap, uTex1Size, uTex1Filter, uFilter);")
            table.insert(fs, "texVal0.rgb *= uLightmapColor.rgb;")
            table.insert(fs, "texVal1.rgb = texVal1.rgb * texVal1.rgb + texVal1.rgb;")
        else
            table.insert(fs, "vec4 texVal1 = sampleTex(uTex1, vTexCoord1, uTex1Size, uTex1Filter, uFilter);")
        end
    end

    if opt_alpha then
        table.insert(fs, "vec4 texel = vec4(0.0);")
    else
        table.insert(fs, "vec3 texel = vec3(0.0);")
    end

    -- combine passes
    for i = 0, (opt_2cycle and 1 or 0) do
        local cmd = {}
        for j = 0, CC_MAX_INPUTS - 1 do
            cmd[j + 1] = cc.shader_commands[i * CC_MAX_INPUTS + j + 1]
        end

        local idx = i * 2

        table.insert(fs, "texel = ")

        if not ccf.color_alpha_same[i + 1] and opt_alpha then
            table.insert(fs, "vec4(")
            table.insert(fs, append_formula(cmd, ccf.do_single[idx + 1], ccf.do_multiply[idx + 1], ccf.do_mix[idx + 1], false, false))
            table.insert(fs, ", ")
            table.insert(fs, append_formula(cmd, ccf.do_single[idx + 2], ccf.do_multiply[idx + 2], ccf.do_mix[idx + 2], true, true))

            table.insert(fs, ")")
        else
            table.insert(fs,
                append_formula(cmd,
                    ccf.do_single[idx + 1],
                    ccf.do_multiply[idx + 1],
                    ccf.do_mix[idx + 1],
                    opt_alpha,
                    false
                )
            )
        end

        table.insert(fs, ";")

        if i == 0 then
            table.insert(fs, "texel = mod(texel + 0.5, 2.0) - 0.5;")
        end
    end

    table.insert(fs, "texel = clamp(mod(texel + 0.5, 2.0) - 0.5, 0.0, 1.0);")

    if opt_texture_edge and opt_alpha then
        table.insert(fs, "if (texel.a > 0.3) texel.a = 1.0; else discard;")
    end

    if world_geometry then
        table.insert(fs, "if (uShaderFlagsEnabled) {")

        table.insert(fs, "if (uShaderFlags[0] == 1) {")
        table.insert(fs, "vec3 hsv = rgb2hsv(texel.rgb);")
        table.insert(fs, "hsv.x = fract(hsv.x + uShaderFlagValues[0]);")
        table.insert(fs, "vec3 finalColor = hsv2rgb(hsv);")
        table.insert(fs, "texel.rgb = finalColor;")
        table.insert(fs, "}")

        table.insert(fs, "if (uShaderFlags[1] == 1) {")
        table.insert(fs, "const vec3 w = vec3(0.2125, 0.7154, 0.0721);")
        table.insert(fs, "vec3 intensity = vec3(dot(texel.rgb, w));")
        table.insert(fs, "texel.rgb = mix(intensity, texel.rgb, uShaderFlagValues[1]);")
        table.insert(fs, "}")

        table.insert(fs, "if (uShaderFlags[2] == 1) {")
        table.insert(fs, "texel.rgb *= uShaderFlagValues[2];")
        table.insert(fs, "}")

        table.insert(fs, "if (uShaderFlags[3] == 1) {")
        table.insert(fs, "texel.rgb = 0.5 + uShaderFlagValues[3] * (texel.rgb - 0.5);")
        table.insert(fs, "}")

        table.insert(fs, "if (uShaderFlags[4] == 1) {")
        table.insert(fs, "texel.rgb = texel.rgb + (uShaderFlagValues[4] - 2) * texel.rgb + texel.rgb;")
        table.insert(fs, "}")

        table.insert(fs, "if (uShaderFlags[5] == 1) {")
        table.insert(fs, "texel.rgb *= dither4x4(gl_FragCoord.xy, dot(texel.rgb, vec3(0.299, 0.587, 0.114)));")
        table.insert(fs, "}")

        table.insert(fs, "if (uShaderFlags[6] == 1) {")
        table.insert(fs, "int levels = int(max(1.0, uShaderFlagValues[6]));")
        table.insert(fs, "texel.rgb = floor(texel.rgb * levels) / levels;")
        table.insert(fs, "}")

        table.insert(fs, "if (uShaderFlags[7] == 1) {")
        table.insert(fs, "float scan = sin(gl_FragCoord.y * 1.5) * 0.04;")
        table.insert(fs, "texel.rgb -= scan * uShaderFlagValues[7];")
        table.insert(fs, "}")

        table.insert(fs, "}")
    end

    if opt_fog then
        if opt_alpha then
            table.insert(fs, "texel = vec4(mix(texel.rgb, uFogColor, vFogZ), texel.a);")
        else
            table.insert(fs, "texel = mix(texel, uFogColor, vFogZ);")
        end
    end

    if opt_alpha and opt_dither then
        table.insert(fs, "texel.a *= noise;")
    end

    if opt_alpha then
        table.insert(fs, "fragColor = texel;")
    else
        table.insert(fs, "fragColor = vec4(texel, 1.0);")
    end

    table.insert(fs, "}")

    return table.concat(fs, "\n")
end

hook_event(HOOK_ON_VERTEX_SHADER_CREATE, on_vertex_shader_create)
hook_event(HOOK_ON_FRAGMENT_SHADER_CREATE, on_fragment_shader_create)
