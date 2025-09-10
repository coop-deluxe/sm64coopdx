#pragma once
#include "djui.h"

struct DjuiImage {
    struct DjuiBase base;
    const Texture* texture;
    u16 textureWidth;
    u16 textureHeight;
    u16 textureBitSize;
};

void djui_image_set_image(struct DjuiImage* image, const Texture* texture, u16 textureWidth, u16 textureHeight, u16 textureBitSize);

struct DjuiImage* djui_image_create(struct DjuiBase* parent, const Texture* texture, u16 textureWidth, u16 textureHeight, u16 textureBitSize);
