#include <stdio.h>
#include "../network.h"
#include "game/object_list_processor.h"
#include "game/interaction.h"
#include "game/level_update.h"
#include "game/ingame_menu.h"
#include "course_table.h"
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

        // Level location
        packet_write_int16(&p, gCurrCourseNum);
        packet_write_int16(&p, gCurrActStarNum);
        packet_write_int16(&p, gCurrLevelNum);

        // Level variables
        packet_write_int16(&p, gMarioStates[0].numCoins);
        packet_write_uint8(&p, gPssSlideStarted);
        packet_write_int16(&p, gTTCSpeedSetting);

        // Send our level packet
        network_send_to(toNp->localIndex, &p);
        
        packet_clear(&p);

        // Send macro deletions
        network_send_level_macro(toNp);

        // Send spawn info
        network_send_level_spawn_info(toNp);

        if (sendArea) {
            // Send the area
            network_send_area(toNp);
        } else {
            // Send sync valid
            network_send_sync_valid(toNp, gCurrCourseNum, gCurrActStarNum, gCurrLevelNum, -1, false);
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
    
    // Sanity check for data contents. Read will throw an error anyways,
    // But it's better to catch malformed or maliciously formed packets here.
    SOFT_ASSERT(packet_get_remaining_size(p) >= sizeof(u8) + (sizeof(s16) * 5));

    // Read the level location
    s16 courseNum = packet_read_int16(p);
    s16 actNum = packet_read_int16(p);
    s16 levelNum = packet_read_int16(p);

    extern s16 gCurrCourseNum, gCurrActStarNum, gCurrLevelNum;
    if (courseNum != gCurrCourseNum || actNum != gCurrActStarNum || levelNum != gCurrLevelNum) {
        LOG_ERROR("rx level: received an improper location");
        return;
    }

    // Read level variables
    s16 oldTTCSpeedSetting = gTTCSpeedSetting;
    gMarioStates[0].numCoins = packet_read_int16(p);
    gPssSlideStarted = packet_read_uint8(p);
    gTTCSpeedSetting = packet_read_int16(p);
    gHudDisplay.coins = gMarioStates[0].numCoins;

    // Fix TTC objects by reinitializing values pertaining to speed
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
