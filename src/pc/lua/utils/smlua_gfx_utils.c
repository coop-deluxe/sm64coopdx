#include "smlua_gfx_utils.h"
#include "pc/gfx/gfx_pc.h"
#include "game/rendering_graph_node.h"
#include "game/skybox.h"
#include "geo_commands.h"

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

  ///////////////////
 // Display lists //
///////////////////

//
// Sentinel values for dynamically allocated Gfx and Vtx buffers
// It will prevent out-of-bounds accesses and buffer overflows
//
// SENTINEL_GFX is a gsSPEndDisplayList() with all other bits set
// SENTINEL_VTX bits are all set, which results in a bunch of NaN when treated as a Vtx
//

static const Gfx SENTINEL_GFX[1] = {{{ _SHIFTL(G_ENDDL, 24, 8) | _SHIFTL(UINT32_MAX, 0, 24), UINT32_MAX }}};
static const u8  SENTINEL_VTX[sizeof(Vtx)] = {[0 ... sizeof(Vtx) - 1] = UINT8_MAX};

Gfx *gfx_allocate_internal(u32 length) {
    if (!length) { return NULL; }
    Gfx *gfx = calloc(length + 1, sizeof(Gfx));
    memcpy(gfx + length, SENTINEL_GFX, sizeof(Gfx));
    return gfx;
}

Vtx *vtx_allocate_internal(u32 count) {
    if (!count) { return NULL; }
    Vtx *vtx = calloc(count + 1, sizeof(Vtx));
    memcpy(vtx + count, SENTINEL_VTX, sizeof(Vtx));
    return vtx;
}

// Get the size of a display list by iterating
// until gsSPEndDisplayList or gsSPBranchList is found
u32 gfx_get_length_no_sentinel(const Gfx *gfx) {
    if (!gfx) { return 0; }
    for (u32 i = 0;;) {
        u32 op = (gfx + i)->words.w0 >> 24;
        u32 cmdSize = 1;
        switch (op) {
            case G_DL:
                if (C0(gfx + i, 16, 1) == G_DL_NOPUSH) { return i + 1; } // For displaylists that end with branches (jumps)
                break;
            case G_ENDDL:
                return i + 1;
            case G_TEXRECT:
            case G_TEXRECTFLIP:
                cmdSize = 3;
                break;
            case G_FILLRECT:
                cmdSize = 2;
                break;
        }
        i += cmdSize;
    }
}

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
                switch (op) {
                    case G_TEXRECT:
                    case G_TEXRECTFLIP:
                        ++cmd;
                        ++cmd;
                        break;
                    case G_FILLRECT:
                        ++cmd;
                        break;
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

u32 gfx_get_length(Gfx *gfx) {
    u32 length = 0;
    for (; memcmp(gfx, SENTINEL_GFX, sizeof(Gfx)) != 0; ++length, gfx++);
    return length;
}

Gfx *gfx_get_command(Gfx *gfx, u32 offset) {
    if (!gfx) { return NULL; }
    if (offset >= gfx_get_length(gfx)) { return NULL; }

    return &gfx[offset];
}

void gfx_copy(Gfx *dest, Gfx *src, u32 length) {
    if (!src || !dest || !length) { return; }

    u32 srcLength = gfx_get_length(src);
    if (length > srcLength) {
        LOG_LUA_LINE("gfx_copy: Cannot copy %u commands from a display list of size: %u", length, srcLength);
        return;
    }

    u32 destLength = gfx_get_length(dest);
    if (length > destLength) {
        LOG_LUA_LINE("gfx_copy: Cannot copy %u commands to a display list of size: %u", length, srcLength);
        return;
    }

    memcpy(dest, src, length * sizeof(Gfx));
}

Gfx *gfx_new(const char *name, u32 length) {
    if (!name || !length) { return NULL; }

    Gfx *gfx = dynos_gfx_new(name, length);
    if (!gfx) {
        LOG_LUA_LINE("gfx_new: Display list `%s` already exists", name);
        return NULL;
    }

    return gfx;
}

Gfx *gfx_realloc(Gfx *gfx, u32 newLength) {
    if (!gfx || !newLength) { return NULL; }

    Gfx *newGfx = dynos_gfx_realloc(gfx, newLength);
    if (!newGfx) {
        LOG_LUA_LINE("gfx_realloc: Display list was not allocated by `gfx_new`");
        return NULL;
    }

    return newGfx;
}

void gfx_delete(Gfx *gfx) {
    if (!gfx) { return; }

    if (!dynos_gfx_delete(gfx)) {
        LOG_LUA_LINE("gfx_delete: Display list was not allocated by `gfx_new`");
    }
}

u32 vtx_get_count(Vtx *vtx) {
    u32 count = 0;
    for (; memcmp(vtx, SENTINEL_VTX, sizeof(Vtx)) != 0; ++count, vtx++);
    return count;
}

Vtx *vtx_get_vertex(Vtx *vtx, u32 offset) {
    if (!vtx) { return NULL; }
    if (offset >= vtx_get_count(vtx)) { return NULL; }

    return &vtx[offset];
}

void vtx_copy(Vtx *dest, Vtx *src, u32 count) {
    if (!src || !dest || !count) { return; }

    u32 srcLength = vtx_get_count(src);
    if (count > srcLength) {
        LOG_LUA_LINE("vtx_copy: Cannot copy %u vertices from a vertex buffer of size: %u", count, srcLength);
        return;
    }

    u32 destLength = vtx_get_count(dest);
    if (count > destLength) {
        LOG_LUA_LINE("vtx_copy: Cannot copy %u vertices to a vertex buffer of size: %u", count, srcLength);
        return;
    }

    memcpy(dest, src, count * sizeof(Vtx));
}

Vtx *vtx_new(const char *name, u32 count) {
    if (!name || !count) { return NULL; }

    Vtx *vtx = dynos_vtx_new(name, count);
    if (!vtx) {
        LOG_LUA_LINE("vtx_new: Vertex buffer `%s` already exists", name);
        return NULL;
    }

    return vtx;
}

Vtx *vtx_realloc(Vtx *vtx, u32 newCount) {
    if (!vtx || !newCount) { return NULL; }

    Vtx *newVtx = dynos_vtx_realloc(vtx, newCount);
    if (!newVtx) {
        LOG_LUA_LINE("vtx_realloc: Vertex buffer was not allocated by `vtx_new`");
        return NULL;
    }

    return newVtx;
}

void vtx_delete(Vtx *vtx) {
    if (!vtx) { return; }

    if (!dynos_vtx_delete(vtx)) {
        LOG_LUA_LINE("vtx_delete: Vertex buffer was not allocated by `vtx_new`");
    }
}
