#include "smlua_texture_utils.h"
#include "sm64.h"
#include "pc/lua/smlua.h"
#include "types.h"

extern void gfx_texture_cache_delete(const uint8_t *orig_addr);

static struct DynamicPool *sTextureInfoPool;
static struct DynamicPool *sDynosTextureInfoPool;

static void smlua_texture_util_free_info(struct TextureInfo *texInfo) {
    if (!texInfo) { return; }

    if (texInfo->pixels) {
        free(texInfo->pixels);
        texInfo->pixels = NULL;
    }

    if (texInfo->name) {
        free((void *)texInfo->name);
        texInfo->name = NULL;
    }
}

void smlua_texture_util_clear(void) {
    if (!sTextureInfoPool) { return; }
    struct DynamicPoolNode *node = sTextureInfoPool->tail;
    while (node) {
        struct TextureInfo *texInfo = (struct TextureInfo *)node->ptr;
        smlua_texture_util_free_info(texInfo);
        node = node->prev;
    }
    dynamic_pool_free_pool(sTextureInfoPool);
    free(sTextureInfoPool);
    sTextureInfoPool = NULL;
    if (!sDynosTextureInfoPool) { return; }
    dynamic_pool_free_pool(sDynosTextureInfoPool);
    free(sDynosTextureInfoPool);
    sDynosTextureInfoPool = NULL;
}

static u8 smlua_texture_util_color_from_key(lua_State *L, int subtable_idx, int key_stack_idx) {
    lua_pushvalue(L, key_stack_idx);
    lua_gettable(L, subtable_idx);
    
    u8 value = 0;
    if (lua_isinteger(L, -1)) {
        value = (u8)smlua_to_integer(L, -1);
    } else if (lua_isnumber(L, -1)) {
        value = (u8)(smlua_to_number(L, -1) * 255.0f + 0.5f);
    }
    
    lua_pop(L, 1);
    return value;
}

struct TextureInfo *smlua_texture_util_get_info(const char *textureName) {
    struct TextureInfo dynosTexInfo = { 0 };
    if (sDynosTextureInfoPool) {
        struct DynamicPoolNode *node = sDynosTextureInfoPool->tail;
        while (node) {
            struct TextureInfo *texInfo = (struct TextureInfo *)node->ptr;
            if (!strcmp(textureName, texInfo->name)) {
                return texInfo;
            }
            node = node->prev;
        }
    }

    if (dynos_texture_get(textureName, &dynosTexInfo)) {
        if (!sDynosTextureInfoPool) {
            sDynosTextureInfoPool = dynamic_pool_init();
        }
        struct TextureInfo *texInfo = (struct TextureInfo *)dynamic_pool_alloc(sDynosTextureInfoPool, sizeof(struct TextureInfo));
        if (!texInfo) {
            LOG_LUA_LINE("smlua_texture_util_get_info: Failed to allocate texture info for '%s'", textureName);
            return NULL;
        }

        texInfo->texture = dynosTexInfo.texture;
        texInfo->name    = dynosTexInfo.name;
        texInfo->width   = dynosTexInfo.width;
        texInfo->height  = dynosTexInfo.height;
        texInfo->format  = dynosTexInfo.format;
        texInfo->size    = dynosTexInfo.size;
        return texInfo;
    }

    if (!sTextureInfoPool) { return NULL; }
    struct DynamicPoolNode *node = sTextureInfoPool->tail;
    while (node) {
        struct TextureInfo *texInfo = (struct TextureInfo *)node->ptr;
        if (!strcmp(textureName, texInfo->name)) {
            return texInfo;
        }
        node = node->prev;
    }

    LOG_LUA_LINE("smlua_texture_util_get_info: Could not find texture info for '%s'", textureName);
    return NULL;
}

// Formats and Sizes aren't implemented so always fallback to rgba and ignore user input, this is just in case someone wants to do it
static void smlua_texture_util_validate_format_and_size(const u8 *format, const u8 *size, u8 origFmt, u8 origSiz, u8 *outFmt, u8 *outSiz) {
    u8 fmt = format ? *format : origFmt;
    u8 siz = size   ? *size   : origSiz;

    u8 mask = (fmt == G_IM_FMT_RGBA) ? 0x0C : (fmt == G_IM_FMT_IA) ? 0x07 : 0x03;

    if (!(mask & (1 << siz))) {
        if (format) {
            siz = (fmt == G_IM_FMT_RGBA || fmt == G_IM_FMT_IA) ? G_IM_SIZ_16b : G_IM_SIZ_8b;
        } else {
            fmt = (siz == G_IM_SIZ_32b) ? G_IM_FMT_RGBA :
                  (siz == G_IM_SIZ_16b) ? (origFmt == G_IM_FMT_IA ? G_IM_FMT_IA : G_IM_FMT_RGBA) :
                  (origFmt == G_IM_FMT_CI || origFmt == G_IM_FMT_IA) ? origFmt : G_IM_FMT_I;
        }
    }

    *outFmt = G_IM_FMT_RGBA;
    *outSiz = G_IM_SIZ_32b;
}

struct TextureInfo *smlua_texture_util_create_info(LuaTable pixelTable, const char *name, u32 width, u32 height, u8 format, u8 size) {
    if (!name) {
        LOG_LUA_LINE("smlua_texture_util_create_info: Attempted to create a texture with an invalid name");
        return NULL;
    }

    if (!width || !height) {
        if (!width) {
            LOG_LUA_LINE("smlua_texture_util_create_info: Attempted to create a texture with a width of 0");
        }
        if (!height) {
            LOG_LUA_LINE("smlua_texture_util_create_info: Attempted to create a texture with a height of 0");
        }
        return NULL;
    }
    
    smlua_texture_util_validate_format_and_size(NULL, NULL, format, size, &format, &size);

    lua_State *L = gLuaState;
    lua_rawgeti(L, LUA_REGISTRYINDEX, pixelTable);
    pixelTable = lua_gettop(L);

    if (!lua_istable(L, pixelTable)) {
        LOG_LUA_LINE("smlua_texture_util_create_info: pixelTable is not a table");
        lua_pop(L, 1);
        return NULL;
    }

    if (!sTextureInfoPool) {
        sTextureInfoPool = dynamic_pool_init();
        if (!sTextureInfoPool) {
            LOG_LUA_LINE("smlua_texture_util_create_info: Failed to initialize texture info pool");
            lua_pop(L, 1);
            return NULL;
        }
    }

    struct TextureInfo *texInfo = (struct TextureInfo *)dynamic_pool_alloc(sTextureInfoPool, sizeof(struct TextureInfo));
    if (!texInfo) {
        LOG_LUA_LINE("smlua_texture_util_create_info: Failed to allocate texture info in pool");
        lua_pop(L, 1);
        return NULL;
    }

    size_t textureSize = width * height;

    texInfo->pixels = malloc(textureSize * 4);
    if (!texInfo->pixels) {
        LOG_LUA_LINE("smlua_texture_util_create_info: Failed to allocate pixel buffer for texture info");
        smlua_texture_util_free_info(texInfo);
        dynamic_pool_free(sTextureInfoPool, texInfo);
        lua_pop(L, 1);
        return NULL;
    }

    texInfo->name   = strdup(name);
    texInfo->width  = width;
    texInfo->height = height;
    texInfo->format = format;
    texInfo->size   = size;

    lua_pushliteral(L, "r");
    s32 r_key = lua_gettop(L);
    lua_pushliteral(L, "g");
    s32 g_key = lua_gettop(L);
    lua_pushliteral(L, "b");
    s32 b_key = lua_gettop(L);
    lua_pushliteral(L, "a");
    s32 a_key = lua_gettop(L);

    Texture *out = texInfo->pixels;

    for (size_t pixelIndex = 0; pixelIndex < textureSize; pixelIndex++, out += 4) {
        lua_geti(L, pixelTable, pixelIndex + 1);

        if (lua_istable(L, -1)) {
            s32 subtable_idx = lua_gettop(L);

            out[0] = smlua_texture_util_color_from_key(L, subtable_idx, r_key);
            out[1] = smlua_texture_util_color_from_key(L, subtable_idx, g_key);
            out[2] = smlua_texture_util_color_from_key(L, subtable_idx, b_key);
            out[3] = smlua_texture_util_color_from_key(L, subtable_idx, a_key);
        } else if (lua_isinteger(L, -1)) {
            u32 rgba = (u32)smlua_to_integer(L, -1);
            out[0] = (rgba >> 24) & 0xFF;
            out[1] = (rgba >> 16) & 0xFF;
            out[2] = (rgba >>  8) & 0xFF;
            out[3] = (rgba      ) & 0xFF;
        } else {
            out[0] = 0;
            out[1] = 0;
            out[2] = 0;
            out[3] = 0;
        }
        lua_pop(L, 1);
    }

    lua_pop(L, 5);
    return texInfo;
}

void smlua_texture_util_modify_info(struct TextureInfo *texInfo, OPTIONAL LuaTable pixelTable, OPTIONAL const char *name, OPTIONAL u32 width, OPTIONAL u32 height, OPTIONAL u8 *format, OPTIONAL u8 *size) {
    if (!sTextureInfoPool) {
        LOG_LUA_LINE("smlua_texture_util_modify_info: Cannot modify DynOS texture");
        return;
    }

    if (!dynamic_pool_contains(sTextureInfoPool, texInfo)) {
        LOG_LUA_LINE("smlua_texture_util_modify_info: Cannot modify DynOS or deleted texture");
        return;
    }

    if (name) {
        char *newName = strdup(name);
        if (newName) {
            if (texInfo->name) {
                free((void *)texInfo->name);
            }
            texInfo->name = newName;
        }
    }

    u8 newFormat = texInfo->format;
    u8 newSize = texInfo->size;

    smlua_texture_util_validate_format_and_size(format, size, newFormat, newSize, &newFormat, &newSize);

    texInfo->width  = width ? width : texInfo->width;
    texInfo->height = height ? height : texInfo->height;
    texInfo->format = newFormat;
    texInfo->size   = newSize;
    
    if (!pixelTable) { return; }

    lua_State *L = gLuaState;
    lua_rawgeti(L, LUA_REGISTRYINDEX, pixelTable);
    pixelTable = lua_gettop(L);

    size_t textureSize = texInfo->width * texInfo->height;
    Texture *pixels = (Texture *)realloc(texInfo->pixels, textureSize * 4);
    
    if (!pixels) {
        LOG_LUA_LINE("smlua_texture_util_modify_info: Failed to resize pixel buffer for texture '%s'", texInfo->name);
        lua_pop(L, 1);
        return;
    }
    texInfo->pixels = pixels;
    gfx_texture_cache_delete(texInfo->pixels);

    lua_pushliteral(L, "r");
    s32 r_key = lua_gettop(L);
    lua_pushliteral(L, "g");
    s32 g_key = lua_gettop(L);
    lua_pushliteral(L, "b");
    s32 b_key = lua_gettop(L);
    lua_pushliteral(L, "a");
    s32 a_key = lua_gettop(L);

    Texture *out = texInfo->pixels;

    for (size_t pixelIndex = 0; pixelIndex < textureSize; pixelIndex++, out += 4) {
        lua_geti(L, pixelTable, pixelIndex + 1);

        if (lua_istable(L, -1)) {
            s32 subtable_idx = lua_gettop(L);

            out[0] = smlua_texture_util_color_from_key(L, subtable_idx, r_key);
            out[1] = smlua_texture_util_color_from_key(L, subtable_idx, g_key);
            out[2] = smlua_texture_util_color_from_key(L, subtable_idx, b_key);
            out[3] = smlua_texture_util_color_from_key(L, subtable_idx, a_key);
        } else if (lua_isinteger(L, -1)) {
            u32 rgba = (u32)smlua_to_integer(L, -1);
            out[0] = (rgba >> 24) & 0xFF;
            out[1] = (rgba >> 16) & 0xFF;
            out[2] = (rgba >>  8) & 0xFF;
            out[3] = (rgba      ) & 0xFF;
        } else {
            out[0] = 0;
            out[1] = 0;
            out[2] = 0;
            out[3] = 0;
        }
        lua_pop(L, 1);
    }
    lua_pop(L, 5);
}

void smlua_texture_util_delete_info(struct TextureInfo *texInfo) {
    if (!sTextureInfoPool) {
        LOG_LUA_LINE("smlua_texture_util_delete_info: Cannot delete DynOS texture");
        return;
    }
    
    if (!dynamic_pool_contains(sTextureInfoPool, texInfo)) {
        LOG_LUA_LINE("smlua_texture_util_delete_info: Cannot delete DynOS or already deleted texture");
        return;
    }

    smlua_texture_util_free_info(texInfo);
    dynamic_pool_free(sTextureInfoPool, texInfo);
}

void smlua_texture_util_copy_info(struct TextureInfo *dst, const struct TextureInfo *src) {
    if (!sTextureInfoPool) {
        LOG_LUA_LINE("smlua_texture_util_copy_info: Cannot copy to a DynOS texture");
        return;
    }

    if (!dynamic_pool_contains(sTextureInfoPool, dst)) {
        LOG_LUA_LINE("smlua_texture_util_copy_info: Cannot copy to a DynOS or deleted texture");
        return;
    }

    size_t srcSize = src->width * src->height * 4;

    Texture *pixels = (Texture *)realloc(dst->pixels, srcSize);
    if (!pixels) {
        LOG_LUA_LINE("smlua_texture_util_copy_info: Failed to resize buffer for destination texture");
        return;
    }

    char *newName = src->name ? strdup(src->name) : NULL;
    if (dst->name) {
        free((void *)dst->name);
    }

    dst->pixels = pixels;
    dst->name   = newName;
    dst->width  = src->width;
    dst->height = src->height;
    dst->format = src->format;
    dst->size   = src->size;

    gfx_texture_cache_delete(dst->pixels);
    memcpy(dst->pixels, src->pixels, srcSize);
}

struct TextureInfo *smlua_texture_util_duplicate_info(const struct TextureInfo *src, OPTIONAL const char *name) {
    if (!sTextureInfoPool) {
        sTextureInfoPool = dynamic_pool_init();
        if (!sTextureInfoPool) {
            LOG_LUA_LINE("smlua_texture_util_create_info: Failed to initialize texture info pool");
            return NULL;
        }
    }

    struct TextureInfo *dst = (struct TextureInfo *)dynamic_pool_alloc(sTextureInfoPool, sizeof(struct TextureInfo));
    size_t srcSize = src->width * src->height * 4;

    dst->pixels = (Texture *)malloc(srcSize);
    if (!dst->pixels) {
        LOG_LUA_LINE("smlua_texture_util_duplicate_info: Failed to allocate pixel buffer");
        smlua_texture_util_free_info(dst);
        dynamic_pool_free(sTextureInfoPool, dst);
        return NULL;
    }

    const char *newName = name ? name : src->name;
    dst->name   = newName ? strdup(newName) : NULL;
    dst->width  = src->width;
    dst->height = src->height;
    dst->format = src->format;
    dst->size   = src->size;

    memcpy(dst->pixels, src->pixels, srcSize);

    return dst;
}

void smlua_texture_util_override_set(const char *textureName, struct TextureInfo *overrideTexInfo) {
    dynos_texture_override_set(textureName, overrideTexInfo);
}

void smlua_texture_util_override_reset(const char *textureName) {
    dynos_texture_override_reset(textureName);
}

LuaTable smlua_texture_util_to_table(const Texture *texture) {
    lua_State *L = gLuaState;
    if (!L) { return 0; }

    if (!texture) {
        lua_pushnil(L);
        return 0;
    }

    struct TextureInfo tempTexInfo = { 0 };
    struct TextureInfo *texInfo = &tempTexInfo;

    if (!dynos_texture_get_from_data(texture, texInfo)) {
        bool validTexture = false;
        if (sTextureInfoPool) {
            struct DynamicPoolNode *node = sTextureInfoPool->tail;
            while (node) {
                struct TextureInfo *poolTex = (struct TextureInfo *)node->ptr;
                if (texture == poolTex->texture) {
                    texInfo = poolTex;
                    validTexture = true;
                    break;
                }
                node = node->prev;
            }
        }
        if (!validTexture) {
            lua_pushnil(L);
            return 0;
        }
    }

    u8 *rgba = dynos_texture_convert_to_rgba32(texInfo->texture, texInfo->width, texInfo->height, texInfo->format, texInfo->size);
    if (!rgba) {
        lua_pushnil(L);
        return 0;
    }

    LUA_STACK_CHECK_BEGIN_NUM(L, 1);

    lua_newtable(L);
    const u8 *pixel = rgba;
    for (u32 i = 0; i < texInfo->width * texInfo->height; ++i, pixel += 4) {
        lua_newtable(L);
        smlua_push_integer_field(-2, "r", pixel[0]);
        smlua_push_integer_field(-2, "g", pixel[1]);
        smlua_push_integer_field(-2, "b", pixel[2]);
        smlua_push_integer_field(-2, "a", pixel[3]);
        lua_rawseti(L, -2, i + 1);
    }
    free(rgba);

    LUA_STACK_CHECK_END(L);
    return smlua_to_lua_table(L, -1);
}

const char *smlua_texture_util_get_name(const Texture *texture) {
    struct TextureInfo dynosTexInfo;
    if (dynos_texture_get_from_data(texture, &dynosTexInfo)) {
        return dynosTexInfo.name;
    }

    if (!sTextureInfoPool) { return NULL; }
    struct DynamicPoolNode *node = sTextureInfoPool->tail;
    while (node) {
        struct TextureInfo *texInfo = (struct TextureInfo *)node->ptr;
        if (texture == texInfo->texture) {
            return texInfo->name;
        }
        node = node->prev;
    }
    return NULL;
}
