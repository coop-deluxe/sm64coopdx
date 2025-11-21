#pragma once
#include "djui.h"

struct DjuiImage {
    struct DjuiBase base;
    struct TextureInfo textureInfo;
};

struct DjuiImage* djui_image_create(struct DjuiBase* parent, const Texture* texture, u16 width, u16 height, u8 fmt, u8 siz);
