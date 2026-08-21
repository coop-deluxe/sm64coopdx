/*
Both define_geo_symbol and define_geo_symbol_manual have the same parameters.
1 - Geo Layout command name
2 - The number of parameters the command should take
3 - The offset to an internal pointer that DynOS should use.
4 - The number of words the command uses.
5 - The mask to apply to the first two command bytes when matching, interpreted as a big-endian 16-bit value.
6 - The expected value after applying the mask to the first two command bytes.
*/

define_geo_symbol(GEO_BRANCH_AND_LINK, 1, 1, 2, 0xFF00, 0x0000);
define_geo_symbol(GEO_END, 0, 0, 1, 0xFF00, 0x0100);
define_geo_symbol(GEO_BRANCH, 2, 1, 2, 0xFF00, 0x0200);
define_geo_symbol(GEO_RETURN, 0, 0, 1, 0xFF00, 0x0300);
define_geo_symbol(GEO_NODE_SCREEN_AREA, 5, 0, 3, 0xFF00, 0x0800);
define_geo_symbol(GEO_NODE_ORTHO, 1, 0, 1, 0xFF00, 0x0900);
define_geo_symbol(GEO_CAMERA_FRUSTUM, 3, 0, 2, 0xFFFF, 0x0A00);
define_geo_symbol(GEO_CAMERA_FRUSTUM_WITH_FUNC, 4, 2, 3, 0xFFFF, 0x0A01);
define_geo_symbol(GEO_NODE_START, 0, 0, 1, 0xFF00, 0x0B00);
define_geo_symbol(GEO_ZBUFFER, 1, 0, 1, 0xFF00, 0x0C00);
define_geo_symbol(GEO_RENDER_RANGE, 2, 0, 2, 0xFF00, 0x0D00);
define_geo_symbol(GEO_CAMERA, 8, 4, 5, 0xFF00, 0x0F00);
define_geo_symbol(GEO_TRANSLATE_ROTATE, 7, 0, 4, 0xFFF0, 0x1000);
define_geo_symbol(GEO_TRANSLATE_ROTATE_WITH_DL, 8, 4, 5, 0xFFF0, 0x1080);
define_geo_symbol(GEO_TRANSLATE, 4, 0, 2, 0xFFF0, 0x1010);
define_geo_symbol(GEO_TRANSLATE_WITH_DL, 5, 2, 3, 0xFFF0, 0x1090);
define_geo_symbol(GEO_ROTATE, 4, 0, 2, 0xFFF0, 0x1020);
define_geo_symbol(GEO_ROTATE_WITH_DL, 5, 2, 3, 0xFFF0, 0x10A0);
define_geo_symbol(GEO_ROTATE_Y, 2, 0, 1, 0xFFF0, 0x1030);
define_geo_symbol(GEO_ROTATE_Y_WITH_DL, 3, 1, 2, 0xFFF0, 0x10B0);
define_geo_symbol(GEO_TRANSLATE_NODE, 4, 0, 2, 0xFF80, 0x1100);
define_geo_symbol(GEO_TRANSLATE_NODE_WITH_DL, 5, 2, 3, 0xFF80, 0x1180);
define_geo_symbol(GEO_ROTATION_NODE, 4, 0, 2, 0xFF80, 0x1200);
define_geo_symbol(GEO_ROTATION_NODE_WITH_DL, 5, 2, 3, 0xFF80, 0x1280);
define_geo_symbol(GEO_ANIMATED_PART, 5, 2, 3, 0xFF00, 0x1300);
define_geo_symbol(GEO_BILLBOARD_WITH_PARAMS, 4, 0, 2, 0xFF80, 0x1400);
define_geo_symbol(GEO_BILLBOARD_WITH_PARAMS_AND_DL, 5, 2, 3, 0xFF80, 0x1480);
define_geo_symbol(GEO_BILLBOARD, 0, 0, 2, 0xFF80, 0x1400);
define_geo_symbol(GEO_DISPLAY_LIST, 2, 1, 2, 0xFF00, 0x1500);
define_geo_symbol(GEO_SHADOW, 3, 0, 2, 0xFF00, 0x1600);
define_geo_symbol(GEO_RENDER_OBJ, 0, 0, 1, 0xFF00, 0x1700);
define_geo_symbol(GEO_BACKGROUND_COLOR, 1, 0, 2, 0xFFFF, 0x1900);
define_geo_symbol(GEO_NOP_1A, 0, 0, 3, 0xFF00, 0x1A00);
define_geo_symbol(GEO_HELD_OBJECT, 5, 2, 3, 0xFF00, 0x1C00);
define_geo_symbol(GEO_SCALE, 2, 0, 2, 0xFFC0, 0x1D00);
define_geo_symbol(GEO_SCALE_WITH_DL, 3, 2, 3, 0xFFC0, 0x1D80);
define_geo_symbol(GEO_SCALE_XYZ, 4, 0, 4, 0xFFC0, 0x1D40);
define_geo_symbol(GEO_SCALE_XYZ_WITH_DL, 5, 4, 5, 0xFFC0, 0x1DC0);
define_geo_symbol(GEO_NOP_1E, 0, 0, 3, 0xFF00, 0x1E00);
define_geo_symbol(GEO_NOP_1F, 0, 0, 4, 0xFF00, 0x1F00);
define_geo_symbol(GEO_CULLING_RADIUS, 1, 0, 1, 0xFF00, 0x2000);
define_geo_symbol(GEO_BONE, 8, 4, 5, 0xFF80, 0x2400);
define_geo_symbol(GEO_BONE_WITH_SCALE, 11, 7, 8, 0xFF80, 0x2480);

define_geo_symbol_manual(GEO_ASSIGN_AS_VIEW, 1, 0, 1, 0xFF00, 0x0600);
define_geo_symbol_manual(GEO_UPDATE_NODE_FLAGS, 2, 0, 1, 0xFF00, 0x0700);
define_geo_symbol_manual(GEO_COPY_VIEW, 1, 0, 1, 0xFF00, 0x1B00);

define_geo_symbol_manual(GEO_ASM, 2, 1, 2, 0xFF00, 0x1800);
define_geo_symbol_manual(GEO_SWITCH_CASE, 2, 1, 2, 0xFF00, 0x0E00);
define_geo_symbol_manual(GEO_OPEN_NODE, 0, 0, 1, 0xFF00, 0x0400);
define_geo_symbol_manual(GEO_CLOSE_NODE, 0, 0, 1, 0xFF00, 0x0500);
define_geo_symbol_manual(GEO_BACKGROUND, 2, 1, 2, 0xFFFF, 0x1900);
define_geo_symbol_manual(GEO_BACKGROUND_EXT, 2, 2, 3, 0xFF00, 0x2100);
define_geo_symbol_manual(GEO_SWITCH_CASE_EXT, 2, 1, 2, 0xFF00, 0x2200);
define_geo_symbol_manual(GEO_ASM_EXT, 2, 0, 2, 0xFF00, 0x2300);
