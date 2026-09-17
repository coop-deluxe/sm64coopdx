#pragma once

#include "pc/lua/smlua.h"
#include "types.h"

void smlua_texture_util_clear(void);

/* |description|Gets the `TextureInfo` of a texture by name. Works with vanilla textures|descriptionEnd| */
struct TextureInfo *smlua_texture_util_get_info(const char *textureName);
/* |description|Creates a new custom TextureInfo from the provided data and RGBA texture table|descriptionEnd| */
struct TextureInfo *smlua_texture_util_create_info(LuaTable pixelTable, const char *name, u32 width, u32 height, u8 format, u8 size);
/* |description|Modifies a custom TextureInfo using the provided data and RGBA texture table|descriptionEnd| */
void smlua_texture_util_modify_info(struct TextureInfo *texInfo, OPTIONAL LuaTable pixelTable, OPTIONAL const char *name, OPTIONAL u32 width, OPTIONAL u32 height, OPTIONAL u8 *format, OPTIONAL u8 *size);
/* |description|Deletes a custom TextureInfo|descriptionEnd| */
void smlua_texture_util_delete_info(struct TextureInfo *texInfo);
/* |description|Copies the data from a TextureInfo from `src` to `dst`, `dst` must be a custom texture|descriptionEnd| */
void smlua_texture_util_copy_info(struct TextureInfo *dst, const struct TextureInfo *src);
/* |description|Duplicates a TextureInfo with an optional different `name`|descriptionEnd| */
struct TextureInfo *smlua_texture_util_duplicate_info(const struct TextureInfo *src, OPTIONAL const char *name);
/* |description|Overrides a vanilla texture with a custom `TextureInfo`|descriptionEnd| */
void smlua_texture_util_override_set(const char *textureName, struct TextureInfo *overrideTexInfo);
/* |description|Resets an overridden texture|descriptionEnd| */
void smlua_texture_util_override_reset(const char *textureName);
/* |description|Converts a texture's pixels to a Lua table. Returns nil if failed. Otherwise, returns a 1-indexed table of RGBA pixels|descriptionEnd| */
LuaTable smlua_texture_util_to_table(const Texture *texture);
/* |description|Gets the name of the provided texture pointer `texture`|descriptionEnd| */
const char *smlua_texture_util_get_name(const Texture *texture);
