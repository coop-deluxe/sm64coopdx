#include <PR/ultratypes.h>
#include "rom_assets.h"
#include "pc/debuglog.h"
#include "rom_checker.h"

struct RomAsset {
    void* ptr;
    enum RomAssetType assetType;
    u32 physicalAddress;
    u32 physicalSize;
    u32 segmentedAddress;
    u32 segmentedSize;
    u32 cursor;
    struct RomAsset* next;
};

static FILE* sRomFile = NULL;
static struct RomAsset* sRomAssets = NULL;

static u32 sCurrentPhysicalAddress = 0;
static u32 sCurrentPhysicalSize = 0;
static u8* sCurrentSegmentMemory = NULL;
static u32 sCurrentSegmentSize = 0;

static s32 READ32(struct RomAsset* asset) {
    s64 index = (asset->segmentedAddress + asset->cursor);
    if (index < 0 || index >= sCurrentSegmentSize) { return 0; }
    u8* ptr = &sCurrentSegmentMemory[index];
    s32 value = BSWAP32(*((s32*)ptr));
    asset->cursor += sizeof(s32);
    return value;
}
static s16 READ16(struct RomAsset* asset) {
    s64 index = (asset->segmentedAddress + asset->cursor);
    if (index < 0 || index >= sCurrentSegmentSize) { return 0; }
    u8* ptr = &sCurrentSegmentMemory[index];
    s16 value = BSWAP16(*((s16*)ptr));
    asset->cursor += sizeof(s16);
    return value;
}

static s8 READ8(struct RomAsset* asset) {
    s64 index = (asset->segmentedAddress + asset->cursor);
    if (index < 0 || index >= sCurrentSegmentSize) { return 0; }
    u8* ptr = &sCurrentSegmentMemory[index];
    s8 value = *ptr;
    asset->cursor += sizeof(s8);
    return value;
}

static bool rom_asset_load_segment(u32 physicalAddress, u32 physicalSize) {
    if (physicalAddress == sCurrentPhysicalAddress && physicalSize == sCurrentPhysicalSize) {
        return true;
    }

    sCurrentPhysicalAddress = physicalAddress;
    sCurrentPhysicalSize = physicalSize;

    if (sCurrentSegmentMemory) {
        free(sCurrentSegmentMemory);
    }

    sCurrentSegmentMemory = malloc(physicalSize);
    sCurrentSegmentSize = physicalSize;
    if (!sCurrentSegmentMemory) {
        LOG_ERROR("Could not allocate segment memory!");
        sCurrentSegmentMemory = NULL;
        return false;
    }

    fseek(sRomFile, physicalAddress, SEEK_SET);
    fread(sCurrentSegmentMemory, sizeof(u8), physicalSize, sRomFile);

    u8* decompressed = rom_assets_decompress((u32*)sCurrentSegmentMemory, &sCurrentSegmentSize);
    if (decompressed != NULL) {
        free(sCurrentSegmentMemory);
        sCurrentSegmentMemory = decompressed;
        if (!sCurrentSegmentMemory) {
            LOG_ERROR("Could not decompress segment memory!");
        }
    }
    return (sCurrentSegmentMemory != NULL);
}

// Some Vtx arrays have been manually modified to use white opaque vertex colors
// so they can be shaded by Lua and not stand out as being unlit
static inline bool rom_asset_override_vertex_colors(void* ptr) {
    extern Vtx hoot_seg5_vertex_05002E50[];
    extern Vtx hoot_seg5_vertex_05002F78[];
    extern Vtx hoot_seg5_vertex_050030A0[];
    extern Vtx hoot_seg5_vertex_050031C8[];
    extern Vtx hoot_seg5_vertex_050032F0[];
    extern Vtx hoot_seg5_vertex_05003418[];
    extern Vtx hoot_seg5_vertex_05003540[];
    extern Vtx hoot_seg5_vertex_05003668[];
    extern Vtx yellow_sphere_seg5_vertex_05000000[];
    extern Vtx castle_courtyard_seg7_vertex_070021C0[];
    extern Vtx castle_courtyard_seg7_vertex_070022A0[];
    extern Vtx bbh_seg7_vertex_070076C0[];
    extern Vtx bbh_seg7_vertex_070077B0[];
    extern Vtx lll_seg7_vertex_07013830[];
    extern Vtx ttc_seg7_vertex_0700B238[];
    extern Vtx dirt_seg3_vertex_0302BDC8[];
    return ptr == hoot_seg5_vertex_05002E50 ||
           ptr == hoot_seg5_vertex_05002F78 ||
           ptr == hoot_seg5_vertex_050030A0 ||
           ptr == hoot_seg5_vertex_050031C8 ||
           ptr == hoot_seg5_vertex_050032F0 ||
           ptr == hoot_seg5_vertex_05003418 ||
           ptr == hoot_seg5_vertex_05003540 ||
           ptr == hoot_seg5_vertex_05003668 ||
           ptr == yellow_sphere_seg5_vertex_05000000 ||
           ptr == castle_courtyard_seg7_vertex_070021C0 ||
           ptr == castle_courtyard_seg7_vertex_070022A0 ||
           ptr == bbh_seg7_vertex_070076C0 ||
           ptr == bbh_seg7_vertex_070077B0 ||
           ptr == lll_seg7_vertex_07013830 ||
           ptr == ttc_seg7_vertex_0700B238 ||
           ptr == dirt_seg3_vertex_0302BDC8;
}

static void rom_asset_load_vtx(struct RomAsset* asset) {
    Vtx* vtx = asset->ptr;
    while (asset->cursor < asset->segmentedSize) {
        vtx->v.ob[0] = READ16(asset);
        vtx->v.ob[1] = READ16(asset);
        vtx->v.ob[2] = READ16(asset);
        vtx->v.flag  = READ16(asset);
        vtx->v.tc[0] = READ16(asset);
        vtx->v.tc[1] = READ16(asset);
        if (rom_asset_override_vertex_colors(asset->ptr)) {
            vtx->v.cn[0] = 0xFF;
            vtx->v.cn[1] = 0xFF;
            vtx->v.cn[2] = 0xFF;
            vtx->v.cn[3] = 0xFF;
            asset->cursor += sizeof(s8) * 4;
        } else {
            vtx->v.cn[0] = READ8(asset);
            vtx->v.cn[1] = READ8(asset);
            vtx->v.cn[2] = READ8(asset);
            vtx->v.cn[3] = READ8(asset);
        }
        vtx++;
    }
}

static void rom_asset_load_texture(struct RomAsset* asset) {
    Texture* texture = asset->ptr;
    while (asset->cursor < asset->segmentedSize) {
        *texture = READ8(asset);
        texture++;
    }
}

static void rom_asset_load_sample(struct RomAsset* asset) {
    u8* sample = asset->ptr;
    while (asset->cursor < asset->segmentedSize) {
        *sample = READ8(asset);
        sample++;
    }
}

static void rom_asset_load_collision(struct RomAsset* asset) {
    Collision* col = asset->ptr;
    while (asset->cursor < asset->segmentedSize) {
        *col = READ16(asset);
        col++;
    }
}

static void rom_asset_load_anim(struct RomAsset* asset) {
    u16* anim = asset->ptr;
    while (asset->cursor < asset->segmentedSize) {
        *anim = READ16(asset);
        anim++;
    }
}

static void rom_asset_load_dialog(struct RomAsset* asset) {
    u8* dialog = asset->ptr;
    while (asset->cursor < asset->segmentedSize) {
        *dialog = READ8(asset);
        dialog++;
    }
}

static void rom_asset_load_demo(struct RomAsset* asset) {
    u8* demo = asset->ptr;
    while (asset->cursor < asset->segmentedSize) {
        *demo = READ8(asset);
        demo++;
    }
}

static void rom_asset_load(struct RomAsset* asset) {
    if (!rom_asset_load_segment(asset->physicalAddress, asset->physicalSize)) {
        return;
    }
    switch (asset->assetType) {
        case ROM_ASSET_VTX: rom_asset_load_vtx(asset); break;
        case ROM_ASSET_TEXTURE: rom_asset_load_texture(asset); break;
        case ROM_ASSET_SAMPLE: rom_asset_load_sample(asset); break;
        case ROM_ASSET_COLLISION: rom_asset_load_collision(asset); break;
        case ROM_ASSET_ANIM: rom_asset_load_anim(asset); break;
        case ROM_ASSET_DIALOG: rom_asset_load_dialog(asset); break;
        case ROM_ASSET_DEMO: rom_asset_load_demo(asset); break;
        default:
            LOG_ERROR("Could not load unknown asset type %u!", asset->assetType);
    }
}

void rom_assets_load(void) {
    LOG_INFO("loading asset");

    assert(fs_sys_file_exists(gRomFilename)); // Should never be false

    sRomFile = fopen(gRomFilename, "rb");

    while (sRomAssets) {
        rom_asset_load(sRomAssets);

        struct RomAsset* next = sRomAssets->next;
        free(sRomAssets);
        sRomAssets = next;
    }

    if (sCurrentSegmentMemory) {
        free(sCurrentSegmentMemory);
        sCurrentSegmentMemory = NULL;
    }

    fclose(sRomFile);
}

void rom_assets_queue(void* ptr, enum RomAssetType assetType, u32 physicalAddress, u32 physicalSize, u32 segmentedAddress, u32 segmentedSize) {
    struct RomAsset* asset = (struct RomAsset*)calloc(1, sizeof(struct RomAsset));
    asset->ptr = ptr;
    asset->assetType = assetType;
    asset->physicalAddress = physicalAddress;
    asset->physicalSize = physicalSize;
    asset->segmentedAddress = segmentedAddress;
    asset->segmentedSize = segmentedSize;
    asset->cursor = 0;
    asset->next = sRomAssets;
    sRomAssets = asset;
    LOG_INFO("added asset");
}

u8* rom_assets_decompress(u32* data, u32* decompressedSize) {
    if (BSWAP32(data[0]) != 0x4d494f30) {
        return NULL;
    }

    // ripped from tools/gen_asset_list.cpp
    uint32_t* src = data;
    uint32_t size = BSWAP32(src[1]);
    u8* output = calloc(size, 1);
    char *dest = (char *)output;
    char *destEnd = (size + dest);
    uint16_t *cmpOffset = (uint16_t *)((char *)src + BSWAP32(src[2]));
    char *rawOffset = ((char *)src + BSWAP32(src[3]));
    int counter = 0;
    uint32_t controlBits;

    src += 4;

    while (dest != destEnd) {
        if (counter == 0) {
            controlBits = *src++;
            controlBits = BSWAP32(controlBits);
            counter = 32;
        }

        if (controlBits & 0x80000000) {
            *dest++ = *rawOffset++;
        }
        else {
            uint16_t dcmpParam = *cmpOffset++;
            dcmpParam = BSWAP16(dcmpParam);
            int dcmpCount = (dcmpParam >> 12) + 3;
            char* dcmpPtr = dest - (dcmpParam & 0x0FFF);

            while (dcmpCount) {
                *dest++ = dcmpPtr[-1];
                dcmpCount--;
                dcmpPtr++;
            }
        }

        counter--;
        controlBits <<= 1;
    }

    *decompressedSize = size;
    return output;
}
