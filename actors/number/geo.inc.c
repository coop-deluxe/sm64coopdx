// 0x16000E14
// const GeoLayout number_geo[] = {
//    GEO_NODE_START(),
//    GEO_OPEN_NODE(),
//       GEO_SWITCH_CASE(10, geo_switch_anim_state),
//       GEO_OPEN_NODE(),
//          GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num_0),
//          GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num_1),
//          GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num_2),
//          GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num_3),
//          GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num_4),
//          GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num_5),
//          GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num_6),
//          GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num_7),
//          GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num_8),
//          GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num_9),
//       GEO_CLOSE_NODE(),
//    GEO_CLOSE_NODE(),
//    GEO_END(),
// };

//
// Three-digits orange number
//

#include "types.h"
#include "object_fields.h"
#include "engine/graph_node.h"
#include "game/rendering_graph_node.h"

Gfx *geo_num3_switch(s32 callContext, struct GraphNode *node, UNUSED void *context) {
    if (gCurGraphNodeObject != NULL && callContext == GEO_CONTEXT_RENDER) {
        s32 number = ((struct Object *) gCurGraphNodeObject)->oBehParams2ndByte;
        struct GraphNodeSwitchCase *switchCase = (struct GraphNodeSwitchCase *) node;
        s32 numMin, numMax, numDiv;
        switch (switchCase->parameter) {
            case 0: numMin =   0; numMax =   9; numDiv =   1; break;
            case 1: numMin =  10; numMax =  99; numDiv =  10; break;
            case 2: numMin =  10; numMax =  99; numDiv =   1; break;
            case 3: numMin = 100; numMax = 999; numDiv = 100; break;
            case 4: numMin = 100; numMax = 999; numDiv =  10; break;
            case 5: numMin = 100; numMax = 999; numDiv =   1; break;
        }
        if (number >= numMin && number <= numMax) {
            switchCase->selectedCase = (number / numDiv) % 10;
        } else {
            switchCase->selectedCase = 10;
        }
    }
    return NULL;
}

extern const Gfx dl_billboard_num3_0[];
extern const Gfx dl_billboard_num3_1[];
extern const Gfx dl_billboard_num3_2[];
extern const Gfx dl_billboard_num3_3[];
extern const Gfx dl_billboard_num3_4[];
extern const Gfx dl_billboard_num3_5[];
extern const Gfx dl_billboard_num3_6[];
extern const Gfx dl_billboard_num3_7[];
extern const Gfx dl_billboard_num3_8[];
extern const Gfx dl_billboard_num3_9[];
extern const Gfx dl_billboard_num3_0x[];
extern const Gfx dl_billboard_num3_1x[];
extern const Gfx dl_billboard_num3_2x[];
extern const Gfx dl_billboard_num3_3x[];
extern const Gfx dl_billboard_num3_4x[];
extern const Gfx dl_billboard_num3_5x[];
extern const Gfx dl_billboard_num3_6x[];
extern const Gfx dl_billboard_num3_7x[];
extern const Gfx dl_billboard_num3_8x[];
extern const Gfx dl_billboard_num3_9x[];
extern const Gfx dl_billboard_num3_x0[];
extern const Gfx dl_billboard_num3_x1[];
extern const Gfx dl_billboard_num3_x2[];
extern const Gfx dl_billboard_num3_x3[];
extern const Gfx dl_billboard_num3_x4[];
extern const Gfx dl_billboard_num3_x5[];
extern const Gfx dl_billboard_num3_x6[];
extern const Gfx dl_billboard_num3_x7[];
extern const Gfx dl_billboard_num3_x8[];
extern const Gfx dl_billboard_num3_x9[];
extern const Gfx dl_billboard_num3_0xx[];
extern const Gfx dl_billboard_num3_1xx[];
extern const Gfx dl_billboard_num3_2xx[];
extern const Gfx dl_billboard_num3_3xx[];
extern const Gfx dl_billboard_num3_4xx[];
extern const Gfx dl_billboard_num3_5xx[];
extern const Gfx dl_billboard_num3_6xx[];
extern const Gfx dl_billboard_num3_7xx[];
extern const Gfx dl_billboard_num3_8xx[];
extern const Gfx dl_billboard_num3_9xx[];
extern const Gfx dl_billboard_num3_x0x[];
extern const Gfx dl_billboard_num3_x1x[];
extern const Gfx dl_billboard_num3_x2x[];
extern const Gfx dl_billboard_num3_x3x[];
extern const Gfx dl_billboard_num3_x4x[];
extern const Gfx dl_billboard_num3_x5x[];
extern const Gfx dl_billboard_num3_x6x[];
extern const Gfx dl_billboard_num3_x7x[];
extern const Gfx dl_billboard_num3_x8x[];
extern const Gfx dl_billboard_num3_x9x[];
extern const Gfx dl_billboard_num3_xx0[];
extern const Gfx dl_billboard_num3_xx1[];
extern const Gfx dl_billboard_num3_xx2[];
extern const Gfx dl_billboard_num3_xx3[];
extern const Gfx dl_billboard_num3_xx4[];
extern const Gfx dl_billboard_num3_xx5[];
extern const Gfx dl_billboard_num3_xx6[];
extern const Gfx dl_billboard_num3_xx7[];
extern const Gfx dl_billboard_num3_xx8[];
extern const Gfx dl_billboard_num3_xx9[];

const GeoLayout number_geo[] = {
    GEO_NODE_START(),
    GEO_OPEN_NODE(),
        GEO_BILLBOARD(),
        GEO_OPEN_NODE(),
            GEO_SWITCH_CASE(0, geo_num3_switch),
            GEO_OPEN_NODE(),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_0),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_1),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_2),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_3),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_4),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_5),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_6),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_7),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_8),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_9),
                GEO_DISPLAY_LIST(LAYER_ALPHA, NULL),
            GEO_CLOSE_NODE(),
            GEO_SWITCH_CASE(1, geo_num3_switch),
            GEO_OPEN_NODE(),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_0x),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_1x),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_2x),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_3x),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_4x),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_5x),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_6x),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_7x),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_8x),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_9x),
                GEO_DISPLAY_LIST(LAYER_ALPHA, NULL),
            GEO_CLOSE_NODE(),
            GEO_SWITCH_CASE(2, geo_num3_switch),
            GEO_OPEN_NODE(),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_x0),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_x1),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_x2),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_x3),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_x4),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_x5),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_x6),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_x7),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_x8),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_x9),
                GEO_DISPLAY_LIST(LAYER_ALPHA, NULL),
            GEO_CLOSE_NODE(),
            GEO_SWITCH_CASE(3, geo_num3_switch),
            GEO_OPEN_NODE(),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_0xx),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_1xx),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_2xx),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_3xx),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_4xx),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_5xx),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_6xx),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_7xx),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_8xx),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_9xx),
                GEO_DISPLAY_LIST(LAYER_ALPHA, NULL),
            GEO_CLOSE_NODE(),
            GEO_SWITCH_CASE(4, geo_num3_switch),
            GEO_OPEN_NODE(),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_x0x),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_x1x),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_x2x),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_x3x),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_x4x),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_x5x),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_x6x),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_x7x),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_x8x),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_x9x),
                GEO_DISPLAY_LIST(LAYER_ALPHA, NULL),
            GEO_CLOSE_NODE(),
            GEO_SWITCH_CASE(5, geo_num3_switch),
            GEO_OPEN_NODE(),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_xx0),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_xx1),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_xx2),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_xx3),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_xx4),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_xx5),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_xx6),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_xx7),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_xx8),
                GEO_DISPLAY_LIST(LAYER_ALPHA, dl_billboard_num3_xx9),
                GEO_DISPLAY_LIST(LAYER_ALPHA, NULL),
            GEO_CLOSE_NODE(),
        GEO_CLOSE_NODE(),
    GEO_CLOSE_NODE(),
    GEO_END(),
};
