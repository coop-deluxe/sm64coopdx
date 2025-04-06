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

Gfx *gfx_get_display_list(Gfx *cmd) {
    if (!cmd) { return NULL; }
    u32 op = cmd->words.w0 >> 24;
    if (op != G_DL) { return NULL; }
    if (cmd->words.w1 == 0) { return NULL; }

    return (Gfx *) cmd->words.w1;
}

Vtx *gfx_get_vertex_buffer(Gfx *cmd) {
    if (!cmd) { return NULL; }
    u32 op = cmd->words.w0 >> 24;
    if (op != G_VTX) { return NULL; }
    if (cmd->words.w1 == 0) { return NULL; }

    return (Vtx *) cmd->words.w1;
}

u16 gfx_get_vertex_count(Gfx *cmd) {
    if (!cmd) { return 0; }
    u32 op = cmd->words.w0 >> 24;
    if (op != G_VTX) { return 0; }
    if (cmd->words.w1 == 0) { return 0; }

    return C0(cmd, 12, 8);
}

Gfx *gfx_get_command(Gfx *gfx, u32 offset) {
    if (!gfx) { return NULL; }
    return &gfx[offset];
}

Vtx *vtx_get_vertex(Vtx *vtx, u32 offset) {
    if (!vtx) { return NULL; }
    return &vtx[offset];
}
