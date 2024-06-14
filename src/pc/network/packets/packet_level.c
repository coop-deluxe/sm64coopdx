#include <stdio.h>
#include "../network.h"
#include "game/object_list_processor.h"
#include "game/interaction.h"
#include "game/level_update.h"
#include "game/ingame_menu.h"
#include "behavior_table.h"
#include "object_constants.h"
#include "object_fields.h"
//#define DISABLE_MODULE_LOG 1
#include "pc/debuglog.h"
#include "pc/lua/smlua.h"
#include "pc/lua/smlua_utils.h"
#include "pc/lua/utils/smlua_obj_utils.h"

void network_send_level(struct NetworkPlayer* toNp, bool sendArea) {
    extern s16 gCurrCourseNum, gCurrActStarNum, gCurrLevelNum;

    packet_ordered_begin();
    {
        struct Packet p = { 0 };
        packet_init(&p, PACKET_LEVEL, true, PLMT_NONE);

        // level location
        packet_write(&p, &gCurrCourseNum,  sizeof(s16));
        packet_write(&p, &gCurrActStarNum, sizeof(s16));
        packet_write(&p, &gCurrLevelNum,   sizeof(s16));

        // level variables
        packet_write(&p, &gMarioStates[0].numCoins, sizeof(s16));
        packet_write(&p, &gPssSlideStarted,         sizeof(u8));
        packet_write(&p, &gTTCSpeedSetting,         sizeof(s16));

        // send level packet
        network_send_to(toNp->localIndex, &p);

        // send macro deletions
        network_send_level_macro(toNp);

        // send spawn info
        network_send_level_spawn_info(toNp);

        if (sendArea) {
            // send the area
            network_send_area(toNp);
        } else {
            // send sync valid
            network_send_sync_valid(toNp, gCurrCourseNum, gCurrActStarNum, gCurrLevelNum, -1);
        }
    }
    packet_ordered_end();

    LOG_INFO("tx level");
}

extern s16 gTTC2DRotatorSpeeds[];
extern s16 gTTC2DRotatorTimeBetweenTurns[][4];
extern s16 gTTCMovingBarDelays[];
extern f32 gTTCPendulumInitialAccels[];
extern u8 gTTCRotatingSolidInitialDelays[];
extern s16 gTTCTreadmillSpeeds[];
void network_receive_level(struct Packet* p) {
    LOG_INFO("rx level");

    // read level location
    s16 courseNum, actNum, levelNum;
    packet_read(p, &courseNum,   sizeof(s16));
    packet_read(p, &actNum,      sizeof(s16));
    packet_read(p, &levelNum,    sizeof(s16));

    extern s16 gCurrCourseNum, gCurrActStarNum, gCurrLevelNum;
    if (courseNum != gCurrCourseNum || actNum != gCurrActStarNum || levelNum != gCurrLevelNum) {
        LOG_ERROR("rx level: received an improper location");
        return;
    }

    // read level variables
    s16 oldTTCSpeedSetting = gTTCSpeedSetting;
    packet_read(p, &gMarioStates[0].numCoins, sizeof(s16));
    packet_read(p, &gPssSlideStarted,         sizeof(u8));
    packet_read(p, &gTTCSpeedSetting,         sizeof(s16));
    gHudDisplay.coins = gMarioStates[0].numCoins;

    // fix TTC objects by reinitializing values pertaining to speed
    if (levelNum == LEVEL_TTC) {
        u32 sanityDepth = 0;
        for (struct Object *obj = obj_get_first(OBJ_LIST_SURFACE); obj != NULL; obj = obj_get_next(obj)) {
            if (++sanityDepth > 10000) { break; }
            if (obj_has_behavior_id(obj, id_bhvTTC2DRotator)) {
                if (obj->oBehParams2ndByte >= 0 && obj->oBehParams2ndByte < 2 && gTTCSpeedSetting >= 0 && gTTCSpeedSetting < 4) {
                    obj->oTTC2DRotatorMinTimeUntilNextTurn = gTTC2DRotatorTimeBetweenTurns[obj->oBehParams2ndByte][gTTCSpeedSetting];
                    obj->oTTC2DRotatorIncrement = obj->oTTC2DRotatorSpeed = gTTC2DRotatorSpeeds[obj->oBehParams2ndByte];
                }
            } else if (obj_has_behavior_id(obj, id_bhvTTCMovingBar)) {
                if ((obj->oTTCMovingBarDelay = gTTCMovingBarDelays[gTTCSpeedSetting]) == 0) {
                    obj->oTTCMovingBarOffset = 250.0f;
                }
            } else if (obj_has_behavior_id(obj, id_bhvTTCPendulum)) {
                if (gTTCSpeedSetting != TTC_SPEED_STOPPED && gTTCSpeedSetting > 0 && gTTCSpeedSetting < 4) {
                    obj->oTTCPendulumAngleAccel = gTTCPendulumInitialAccels[gTTCSpeedSetting];
                    obj->oTTCPendulumAngle = 6500.0f;
                } else {
                    obj->oTTCPendulumAngle = 6371.5557f;
                }
            } else if (obj_has_behavior_id(obj, id_bhvTTCPitBlock) && oldTTCSpeedSetting == TTC_SPEED_STOPPED && gTTCSpeedSetting != TTC_SPEED_STOPPED) {
                obj->oPosY -= 330.0f;
            } else if (obj_has_behavior_id(obj, id_bhvTTCRotatingSolid)) {
                obj->oTTCRotatingSolidRotationDelay = gTTCRotatingSolidInitialDelays[gTTCSpeedSetting];
            } else if (obj_has_behavior_id(obj, id_bhvTTCTreadmill)) {
                *obj->oTTCTreadmillBigSurface = *obj->oTTCTreadmillSmallSurface = gTTCTreadmillSpeeds[gTTCSpeedSetting];
            }
        }
    }
}
