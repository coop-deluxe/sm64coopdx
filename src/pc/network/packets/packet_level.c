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
    packet_read(p, &gMarioStates[0].numCoins, sizeof(s16));
    packet_read(p, &gPssSlideStarted,         sizeof(u8));
    packet_read(p, &gTTCSpeedSetting,         sizeof(s16)); // likely doesn't work after level load.. but it could
    gHudDisplay.coins = gMarioStates[0].numCoins;
}
