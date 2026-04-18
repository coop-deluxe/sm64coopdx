// orange_number.c.inc

void bhv_orange_number_init(void) {
    o->oAnimState = o->oBehParams2ndByte;
    o->oVelY = 26.0f;
}

void bhv_orange_number_loop(void) {
    o->oPosY += o->oVelY;
    o->oVelY -= 2.0f;
    if (o->oVelY < -21.0f) {
        o->oVelY = 14.0;
    }

    if (o->oTimer == 35) {
        struct Object *coinSparkleObj = spawn_object(o, MODEL_SPARKLES, bhvGoldenCoinSparkles);
        if (coinSparkleObj != NULL) {
            coinSparkleObj->oPosY -= 30.f;
        }
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }
}
