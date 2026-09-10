#include "dynos.cpp.h"
extern "C" {
#include "include/surface_terrains.h"
#include "include/special_presets.h"
#include "src/game/macro_special_objects.h"
#include "src/engine/surface_load.h"
}

#define COL_SECTION_UNKNOWN   0
#define COL_SECTION_VTX       1
#define COL_SECTION_TRI       2
#define COL_SECTION_SPECIAL   3
#define COL_SECTION_WATER_BOX 4
#define COL_SECTION_END       5

struct CollisionValidationData {
    u8 section;
    const char *lastSymbol;
    u32 vtxAlloc;
    u32 vtxCount;
    u32 triAlloc;
    u32 triCount;
    s16 surfaceType;
    u32 specialAlloc;
    u32 specialCount;
    u32 waterBoxAlloc;
    u32 waterBoxCount;
};

static struct CollisionValidationData sColValData;

static u8 DynOS_Col_GetSpecialObjectType(u8 preset) {
    s32 index = get_special_object_preset_index(preset);
    if (index != -1) {
        return SpecialObjectPresets[index].type;
    }
    return SPTYPE_UNKNOWN;
}

static const char *DynOS_Col_GetCorrectSpecialObjectCommand(u8 presetType) {
    switch (presetType) {
        case SPTYPE_NO_YROT_OR_PARAMS: return "SPECIAL_OBJECT";
        case SPTYPE_YROT_NO_PARAMS: return "SPECIAL_OBJECT_WITH_YAW";
        case SPTYPE_PARAMS_AND_YROT: return "SPECIAL_OBJECT_WITH_YAW_AND_PARAM";
        case SPTYPE_DEF_PARAM_AND_YROT: return "SPECIAL_OBJECT_WITH_YAW";
        default: return "";
    }
}

void DynOS_Col_Validate_SectionChange(GfxData *aGfxData, u8 section) {
    if (sColValData.section == COL_SECTION_END) {
        PrintDataError("  ERROR: Found new col section after COL_END");
    }

    if (sColValData.section != section) {
        if (sColValData.vtxAlloc != sColValData.vtxCount) {
            PrintDataError("  ERROR: Improper vtx count found in section. Allocated: %u, Defined: %u", sColValData.vtxAlloc, sColValData.vtxCount);
        }
        if (sColValData.triAlloc != sColValData.triCount) {
            PrintDataError("  ERROR: Improper triangle count found in section. Allocated: %u, Defined: %u", sColValData.triAlloc, sColValData.triCount);
        }
        if (sColValData.specialAlloc != sColValData.specialCount) {
            PrintDataError("  ERROR: Improper special count found in section. Allocated: %u, Defined: %u", sColValData.specialAlloc, sColValData.specialCount);
        }
        if (sColValData.waterBoxAlloc != sColValData.waterBoxCount) {
            PrintDataError("  ERROR: Improper water box count found in section. Allocated: %u, Defined: %u", sColValData.waterBoxAlloc, sColValData.waterBoxCount);
        }
    }

    sColValData.section = section;
}

void DynOS_Col_Validate_Init(GfxData *aGfxData) {
    DynOS_Col_Validate_SectionChange(aGfxData, COL_SECTION_VTX);
}

void DynOS_Col_Validate_VertexInit(GfxData *aGfxData, s16 vertexCount) {
    if (!sColValData.lastSymbol) {
        PrintDataError("  ERROR: Missing COL_INIT command");
    } else if (strcmp(sColValData.lastSymbol, "COL_INIT") != 0) {
        PrintDataError("  ERROR: COL_VERTEX_INIT found outside of vertex section");
    }
    if (vertexCount < 0) {
        PrintDataError("  ERROR: COL_VERTEX_INIT with a negative count: %d", vertexCount);
    }
    sColValData.vtxAlloc = vertexCount;
    sColValData.vtxCount = 0;
}

void DynOS_Col_Validate_Vertex(GfxData *aGfxData, s16 x, s16 y, s16 z) {
    if (sColValData.section != COL_SECTION_VTX) {
        PrintDataError("  ERROR: COL_VERTEX found outside of vertex section");
    }
    sColValData.vtxCount++;
}

void DynOS_Col_Validate_TriInit(GfxData *aGfxData, s16 surfaceType, s16 triangleCount) {
    if (triangleCount < 0) {
        PrintDataError("  ERROR: COL_TRI_INIT with a negative count: %d", triangleCount);
    }
    DynOS_Col_Validate_SectionChange(aGfxData, COL_SECTION_TRI);
    sColValData.triAlloc = triangleCount;
    sColValData.triCount = 0;
    sColValData.surfaceType = surfaceType;
}

void DynOS_Col_Validate_Tri(GfxData *aGfxData, s16 vertex0, s16 vertex1, s16 vertex2) {
    if (sColValData.section != COL_SECTION_TRI) {
        PrintDataError("  ERROR: COL_TRI found outside of triangle section");
    }
    if (surface_has_force(sColValData.surfaceType)) {
        PrintDataError("  ERROR: COL_TRI cannot be used by surface types with a force parameter: %d (use COL_TRI_SPECIAL instead)", sColValData.surfaceType);
    }
    if (vertex0 < 0 || vertex0 >= sColValData.vtxCount) {
        PrintDataError("  ERROR: COL_TRI used vertex outside of known range for first param: %d", vertex0);
    }
    if (vertex1 < 0 || vertex1 >= sColValData.vtxCount) {
        PrintDataError("  ERROR: COL_TRI used vertex outside of known range for second param: %d", vertex1);
    }
    if (vertex2 < 0 || vertex2 >= sColValData.vtxCount) {
        PrintDataError("  ERROR: COL_TRI used vertex outside of known range for third param: %d", vertex2);
    }
    sColValData.triCount++;
}

void DynOS_Col_Validate_TriSpecial(GfxData *aGfxData, s16 vertex0, s16 vertex1, s16 vertex2, s16 force) {
    if (sColValData.section != COL_SECTION_TRI) {
        PrintDataError("  ERROR: COL_TRI_SPECIAL found outside of triangle section");
    }
    if (!surface_has_force(sColValData.surfaceType)) {
        PrintDataError("  ERROR: COL_TRI_SPECIAL cannot be used by surface types with no force parameter: %d (use COL_TRI instead)", sColValData.surfaceType);
    }
    if (vertex0 < 0 || vertex0 >= sColValData.vtxCount) {
        PrintDataError("  ERROR: COL_TRI_SPECIAL used vertex outside of known range for first param: %d", vertex0);
    }
    if (vertex1 < 0 || vertex1 >= sColValData.vtxCount) {
        PrintDataError("  ERROR: COL_TRI_SPECIAL used vertex outside of known range for second param: %d", vertex1);
    }
    if (vertex2 < 0 || vertex2 >= sColValData.vtxCount) {
        PrintDataError("  ERROR: COL_TRI_SPECIAL used vertex outside of known range for third param: %d", vertex2);
    }
    sColValData.triCount++;
}

void DynOS_Col_Validate_Stop(GfxData *aGfxData) {
    DynOS_Col_Validate_SectionChange(aGfxData, COL_SECTION_UNKNOWN);
}

void DynOS_Col_Validate_End(GfxData *aGfxData) {
    DynOS_Col_Validate_SectionChange(aGfxData, COL_SECTION_END);
}

void DynOS_Col_Validate_SpecialInit(GfxData *aGfxData, s16 specialCount) {
    if (specialCount < 0) {
        PrintDataError("  ERROR: COL_SPECIAL_INIT with a negative count: %d", specialCount);
    }
    DynOS_Col_Validate_SectionChange(aGfxData, COL_SECTION_SPECIAL);
    sColValData.specialAlloc = specialCount;
    sColValData.specialCount = 0;
}

void DynOS_Col_Validate_WaterBoxInit(GfxData *aGfxData, s16 waterBoxCount) {
    if (waterBoxCount < 0) {
        PrintDataError("  ERROR: COL_WATER_BOX_INIT with a negative count: %d", waterBoxCount);
    }
    DynOS_Col_Validate_SectionChange(aGfxData, COL_SECTION_WATER_BOX);
    sColValData.waterBoxAlloc = waterBoxCount;
    sColValData.waterBoxCount = 0;
}

void DynOS_Col_Validate_WaterBox(GfxData *aGfxData, s16 id, s16 x1, s16 z1, s16 x2, s16 z2, s16 y) {
    if (sColValData.section != COL_SECTION_WATER_BOX) {
        PrintDataError("  ERROR: COL_WATER_BOX found outside of water box section");
    }
    sColValData.waterBoxCount++;
}

void DynOS_Col_Validate_SpecialObject(GfxData *aGfxData, s16 preset, s16 posX, s16 posY, s16 posZ) {
    if (sColValData.section != COL_SECTION_SPECIAL) {
        PrintDataError("  ERROR: SPECIAL_OBJECT found outside of special section");
    }
    u8 presetType = DynOS_Col_GetSpecialObjectType(preset);
    if (presetType == SPTYPE_UNKNOWN) {
        PrintDataError("  ERROR: SPECIAL_OBJECT has invalid preset: %d", preset);
    }
    if (presetType != SPTYPE_NO_YROT_OR_PARAMS) {
        PrintDataError("  ERROR: SPECIAL_OBJECT cannot be used with preset: %d (use %s instead)", preset, DynOS_Col_GetCorrectSpecialObjectCommand(presetType));
    }
    sColValData.specialCount++;
}

void DynOS_Col_Validate_SpecialObjectWithYaw(GfxData *aGfxData, s16 preset, s16 posX, s16 posY, s16 posZ, s16 yaw) {
    if (sColValData.section != COL_SECTION_SPECIAL) {
        PrintDataError("  ERROR: SPECIAL_OBJECT_WITH_YAW found outside of special section");
    }
    u8 presetType = DynOS_Col_GetSpecialObjectType(preset);
    if (presetType == SPTYPE_UNKNOWN) {
        PrintDataError("  ERROR: SPECIAL_OBJECT_WITH_YAW has invalid preset: %d", preset);
    }
    if (presetType != SPTYPE_YROT_NO_PARAMS && presetType != SPTYPE_DEF_PARAM_AND_YROT) {
        PrintDataError("  ERROR: SPECIAL_OBJECT_WITH_YAW cannot be used with preset: %d (use %s instead)", preset, DynOS_Col_GetCorrectSpecialObjectCommand(presetType));
    }
    sColValData.specialCount++;
}

void DynOS_Col_Validate_SpecialObjectWithYawAndParam(GfxData *aGfxData, s16 preset, s16 posX, s16 posY, s16 posZ, s16 yaw, s16 param) {
    if (sColValData.section != COL_SECTION_SPECIAL) {
        PrintDataError("  ERROR: SPECIAL_OBJECT_WITH_YAW_AND_PARAM found outside of special section");
    }
    u8 presetType = DynOS_Col_GetSpecialObjectType(preset);
    if (presetType == SPTYPE_UNKNOWN) {
        PrintDataError("  ERROR: SPECIAL_OBJECT_WITH_YAW_AND_PARAM has invalid preset: %d", preset);
    }
    if (presetType != SPTYPE_PARAMS_AND_YROT) {
        PrintDataError("  ERROR: SPECIAL_OBJECT_WITH_YAW_AND_PARAM cannot be used with preset: %d (use %s instead)", preset, DynOS_Col_GetCorrectSpecialObjectCommand(presetType));
    }
    sColValData.specialCount++;
}

void DynOS_Col_Validate_Begin() {
    sColValData = {0};
}

bool DynOS_Col_Validate_CheckSectionEnd() {
    return sColValData.section == COL_SECTION_END;
}

void DynOS_Col_Validate_SetLastSymbol(const char *aLastSymbol) {
    sColValData.lastSymbol = aLastSymbol;
}

static bool sColValidationAborted = false;
static Collision *sColBegin = NULL;
static Collision *sColEnd = NULL;
static Collision *sColData = NULL;
static s16 sColNumVertices = 0;

static void DynOS_Col_Validate_CheckVertices(GfxData *aGfxData, const DataNode<Collision> *aNode) {
    if (sColData >= sColEnd) {
        PrintDataError("  ERROR: Validation failed for collision %s: Cannot read vertex count", aNode->mName.begin());
        sColValidationAborted = true;
        return;
    }

    sColNumVertices = *sColData;
    if (sColNumVertices < 0) {
        PrintDataError("  ERROR: Validation failed for collision %s: Vertex count is negative (%d)", aNode->mName.begin(), sColNumVertices);
        sColValidationAborted = true;
        return;
    }

    sColData += (1 + 3 * sColNumVertices);
    if (sColData >= sColEnd) {
        PrintDataError("  ERROR: Validation failed for collision %s: Not enough data for vertices", aNode->mName.begin());
        sColValidationAborted = true;
        return;
    }
}

static void DynOS_Col_Validate_CheckSurfaceData(GfxData *aGfxData, const DataNode<Collision> *aNode) {
    if (sColData + 2 >= sColEnd) {
        PrintDataError("  ERROR: Validation failed for collision %s: Cannot read triangle vertex indices", aNode->mName.begin());
        sColValidationAborted = true;
        return;
    }

    s16 index1 = sColData[0];
    if (index1 < 0) {
        PrintDataError("  ERROR: Validation failed for collision %s: Triangle vertex index 1 is negative (%d)", aNode->mName.begin(), index1);
        sColValidationAborted = true;
        return;
    }
    if (index1 >= sColNumVertices) {
        PrintDataError("  ERROR: Validation failed for collision %s: Triangle vertex index 1 is out of bounds (%d >= %d)", aNode->mName.begin(), index1, sColNumVertices);
        sColValidationAborted = true;
        return;
    }

    s16 index2 = sColData[1];
    if (index2 < 0) {
        PrintDataError("  ERROR: Validation failed for collision %s: Triangle vertex index 2 is negative (%d)", aNode->mName.begin(), index2);
        sColValidationAborted = true;
        return;
    }
    if (index2 >= sColNumVertices) {
        PrintDataError("  ERROR: Validation failed for collision %s: Triangle vertex index 2 is out of bounds (%d >= %d)", aNode->mName.begin(), index2, sColNumVertices);
        sColValidationAborted = true;
        return;
    }

    s16 index3 = sColData[2];
    if (index3 < 0) {
        PrintDataError("  ERROR: Validation failed for collision %s: Triangle vertex index 3 is negative (%d)", aNode->mName.begin(), index3);
        sColValidationAborted = true;
        return;
    }
    if (index3 >= sColNumVertices) {
        PrintDataError("  ERROR: Validation failed for collision %s: Triangle vertex index 3 is out of bounds (%d >= %d)", aNode->mName.begin(), index3, sColNumVertices);
        sColValidationAborted = true;
        return;
    }
}

static void DynOS_Col_Validate_CheckSurfaces(GfxData *aGfxData, const DataNode<Collision> *aNode, s16 surfaceType) {
    if (sColData >= sColEnd) {
        PrintDataError("  ERROR: Validation failed for collision %s: Cannot read surface count", aNode->mName.begin());
        sColValidationAborted = true;
        return;
    }

    bool hasForce = surface_has_force(surfaceType);
    s16 numSurfaces = *sColData;
    if (numSurfaces < 0) {
        PrintDataError("  ERROR: Validation failed for collision %s: Surface count is negative (%d)", aNode->mName.begin(), numSurfaces);
        sColValidationAborted = true;
        return;
    }

    sColData++;
    if (sColData >= sColEnd) {
        PrintDataError("  ERROR: Validation failed for collision %s: Not enough data for surfaces", aNode->mName.begin());
        sColValidationAborted = true;
        return;
    }

    for (s16 i = 0; i < numSurfaces; i++) {
        DynOS_Col_Validate_CheckSurfaceData(aGfxData, aNode);
        if (sColValidationAborted) {
            return;
        }

        sColData += (3 + (hasForce ? 1 : 0));
        if (sColData >= sColEnd) {
            PrintDataError("  ERROR: Validation failed for collision %s: Not enough data for surfaces", aNode->mName.begin());
            sColValidationAborted = true;
            return;
        }
    }
}

static void DynOS_Col_Validate_CheckEnvironmentalRegions(GfxData *aGfxData, const DataNode<Collision> *aNode) {
    if (sColData >= sColEnd) {
        PrintDataError("  ERROR: Validation failed for collision %s: Cannot read water regions count", aNode->mName.begin());
        sColValidationAborted = true;
        return;
    }

    s16 numRegions = *sColData;
    if (numRegions < 0) {
        PrintDataError("  ERROR: Validation failed for collision %s: Water regions count is negative (%d)", aNode->mName.begin(), numRegions);
        sColValidationAborted = true;
        return;
    }
    if (numRegions > 20) {
        PrintDataError("  ERROR: Validation failed for collision %s: 7.8/10 - Too much water", aNode->mName.begin());
        sColValidationAborted = true;
        return;
    }

    sColData += (1 + 6 * numRegions);
    if (sColData >= sColEnd) {
        PrintDataError("  ERROR: Validation failed for collision %s: Not enough data for water regions", aNode->mName.begin());
        sColValidationAborted = true;
        return;
    }
}

static void DynOS_Col_Validate_CheckSpecialObjects(GfxData *aGfxData, const DataNode<Collision> *aNode) {
    if (sColData >= sColEnd) {
        PrintDataError("  ERROR: Validation failed for collision %s: Cannot read special objects count", aNode->mName.begin());
        sColValidationAborted = true;
        return;
    }

    s16 numSpecialObjects = *sColData;
    if (numSpecialObjects < 0) {
        PrintDataError("  ERROR: Validation failed for collision %s: Special objects count is negative (%d)", aNode->mName.begin(), numSpecialObjects);
        sColValidationAborted = true;
        return;
    }

    sColData++;
    if (sColData >= sColEnd) {
        PrintDataError("  ERROR: Validation failed for collision %s: Not enough data for special objects", aNode->mName.begin());
        sColValidationAborted = true;
        return;
    }

    for (s16 i = 0; i < numSpecialObjects; i++) {
        u8 presetID = (u8) *sColData;
        sColData += 4;

        s32 index = get_special_object_preset_index(presetID);
        if (index == -1) {
            PrintDataError("  ERROR: Validation failed for collision %s: Invalid special object preset ID: %d", aNode->mName.begin(), presetID);
            sColValidationAborted = true;
            return;
        }

        u8 type = SpecialObjectPresets[index].type;
        switch (type) {
            case SPTYPE_NO_YROT_OR_PARAMS: break;
            case SPTYPE_YROT_NO_PARAMS: sColData += 1; break;
            case SPTYPE_PARAMS_AND_YROT: sColData += 2; break;
            case SPTYPE_DEF_PARAM_AND_YROT: sColData += 1; break;
            case SPTYPE_UNKNOWN:
            default:
                PrintDataError("  ERROR: Validation failed for collision %s: Invalid special object preset type: %d", aNode->mName.begin(), type);
                sColValidationAborted = true;
                return;
        }

        if (sColData >= sColEnd) {
            PrintDataError("  ERROR: Validation failed for collision %s: Not enough data for special objects", aNode->mName.begin());
            sColValidationAborted = true;
            return;
        }
    }
}

bool DynOS_Col_Validate_CheckCommands(GfxData *aGfxData, const DataNode<Collision> *aNode) {
    if (aNode->mSize < 1) {
        PrintDataError("  ERROR: Validation failed for collision %s: Not enough commands (%d)", aNode->mName.begin(), aNode->mSize);
        return false;
    }

    sColBegin = aNode->mData;
    sColEnd = aNode->mData + aNode->mSize;
    sColData = sColBegin;
    sColNumVertices = 0;

    sColValidationAborted = false;
    while (!sColValidationAborted) {
        s16 command = *sColData;
        sColData++;

        if (TERRAIN_LOAD_IS_SURFACE_TYPE_LOW(command)) {
            DynOS_Col_Validate_CheckSurfaces(aGfxData, aNode, command);
        } else if (command == TERRAIN_LOAD_VERTICES) {
            DynOS_Col_Validate_CheckVertices(aGfxData, aNode);
        } else if (command == TERRAIN_LOAD_OBJECTS) {
            DynOS_Col_Validate_CheckSpecialObjects(aGfxData, aNode);
        } else if (command == TERRAIN_LOAD_ENVIRONMENT) {
            DynOS_Col_Validate_CheckEnvironmentalRegions(aGfxData, aNode);
        } else if (command == TERRAIN_LOAD_CONTINUE) {
            // continue, but check bounds at the end
        } else if (command == TERRAIN_LOAD_END) {
            break;
        } else if (TERRAIN_LOAD_IS_SURFACE_TYPE_HIGH(command)) {
            DynOS_Col_Validate_CheckSurfaces(aGfxData, aNode, command);
        } else {
            PrintDataError("  ERROR: Validation failed for collision %s: Invalid command: %04X", aNode->mName.begin(), (u16) command);
            return false;
        }

        if (sColData >= sColEnd) {
            PrintDataError("  ERROR: Validation failed for collision %s: Last command of the script must be COL_END", aNode->mName.begin());
            return false;
        }
    }

    return !sColValidationAborted;
}
