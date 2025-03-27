#include "smlua_gfx_utils.h"
#include "pc/gfx/gfx_pc.h"
#include "game/rendering_graph_node.h"
#include "game/skybox.h"
#include "geo_commands.h"
#include "engine/display_list.h"

void set_override_fov(f32 fov) {
    gOverrideFOV = fov;
}

///

void set_override_near(f32 nearClip) {
    gOverrideNear = nearClip;
}

///

void set_override_far(f32 farClip) {
    gOverrideFar = farClip;
}

///

f32 get_lighting_dir(u8 index) {
    if (index > 2) { return 0; }
    return gLightingDir[index];
}

void set_lighting_dir(u8 index, f32 value) {
    if (index > 2) { return; }
    gLightingDir[index] = value;
}

u8 get_lighting_color(u8 index) {
    if (index > 2) { return 0; }
    return gLightingColor[0][index];
}

u8 get_lighting_color_ambient(u8 index) {
    if (index > 2) { return 0; }
    return gLightingColor[1][index];
}

void set_lighting_color(u8 index, u8 value) {
    if (index > 2) { return; }
    gLightingColor[0][index] = value;
    gLightingColor[1][index] = value;
}

void set_lighting_color_ambient(u8 index, u8 value) {
    if (index > 2) { return; }
    gLightingColor[1][index] = value;
}

///

u8 get_vertex_color(u8 index) {
    if (index > 2) { return 0; }
    return gVertexColor[index];
}

void set_vertex_color(u8 index, u8 value) {
    if (index > 2) { return; }
    gVertexColor[index] = value;
}

///

u8 get_fog_color(u8 index) {
    if (index > 2) { return 0; }
    return gFogColor[index];
}

void set_fog_color(u8 index, u8 value) {
    if (index > 2) { return; }
    gFogColor[index] = value;
}

f32 get_fog_intensity(void) {
    return gFogIntensity;
}

void set_fog_intensity(f32 intensity) {
    gFogIntensity = intensity;
}

///

s8 get_skybox(void) {
    if (gOverrideBackground != -1) { return gOverrideBackground; }
    return gReadOnlyBackground;
}

void set_override_skybox(s8 background) {
    if (background < -1 || background > BACKGROUND_CUSTOM) { return; }
    gOverrideBackground = background;
}

u8 get_skybox_color(u8 index) {
    if (index > 2) { return 0; }
    return gSkyboxColor[index];
}

void set_skybox_color(u8 index, u8 value) {
    if (index > 2) { return; }
    gSkyboxColor[index] = value;
}

///

// Assumes the current microcode is Fast3DEX2 Extended (default for pc port)
void gfx_parse(Gfx* cmd, LuaFunction func) {
    if (!cmd) { return; }
    if (func == 0) { return; }

    lua_State* L = gLuaState;
    while (true) {
        u32 op = cmd->words.w0 >> 24;
        switch (op) {
            case G_DL:
                if (C0(cmd, 16, 1) == G_DL_PUSH) {
                    gfx_parse((Gfx *) cmd->words.w1, func);
                } else {
                    cmd = (Gfx *) cmd->words.w1;
                    --cmd;
                }
                break;
            case (uint8_t) G_ENDDL:
                return; // Reached end of display list
            case G_TEXRECT:
            case G_TEXRECTFLIP:
                ++cmd;
                ++cmd;
                break;
            case G_FILLRECT:
                ++cmd;
                break;
            default:
                lua_rawgeti(L, LUA_REGISTRYINDEX, func);
                smlua_push_object(L, LOT_GFX, cmd, NULL);
                lua_pushinteger(L, op);
                if (smlua_pcall(L, 2, 1, 0) != 0) {
                    LOG_LUA("Failed to call the gfx_parse callback: %u", func);
                }
                if (lua_type(L, -1) == LUA_TBOOLEAN && smlua_to_boolean(L, -1)) {
                    return;
                }
                break;
        }
        ++cmd;
    }
}

Vtx *gfx_get_vtx(Gfx* cmd, u16 offset) {
    if (!cmd) { return NULL; }
    u32 op = cmd->words.w0 >> 24;
    if (op != G_VTX) { return NULL; }
    if (cmd->words.w1 == 0) { return NULL; }

    u16 numVertices = C0(cmd, 12, 8);
    if (offset >= numVertices) { return NULL; }

    return &((Vtx *) cmd->words.w1)[offset];
}

u16 gfx_get_vtx_count(Gfx* cmd) {
    if (!cmd) { return 0; }
    u32 op = cmd->words.w0 >> 24;
    if (op != G_VTX) { return 0; }
    if (cmd->words.w1 == 0) { return 0; }

    return C0(cmd, 12, 8);
}

void gfx_set_combine_lerp(Gfx* gfx, u32 a0, u32 b0, u32 c0, u32 d0, u32 Aa0, u32 Ab0, u32 Ac0, u32 Ad0, u32 a1, u32 b1, u32 c1, u32 d1,	u32 Aa1, u32 Ab1, u32 Ac1, u32 Ad1) {
    if (!gfx) { return; }
    gDPSetCombineLERPNoString(gfx, a0, b0, c0, d0, Aa0, Ab0, Ac0, Ad0, a1, b1, c1, d1, Aa1, Ab1, Ac1, Ad1);
}

void gfx_set_texture_image(Gfx* gfx, u32 format, u32 size, u32 width, u8* texture) {
    if (!gfx) { return; }
    gDPSetTextureImage(gfx, format, size, width, texture);
}
