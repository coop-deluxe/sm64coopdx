// whirlpool.c.inc

static struct ObjectHitbox sWhirlpoolHitbox = {
    .interactType = INTERACT_WHIRLPOOL,
    .downOffset = 0,
    .damageOrCoinValue = 0,
    .health = 0,
    .numLootCoins = 0,
    .radius = 200,
    .height = 500,
    .hurtboxRadius = 0,
    .hurtboxHeight = 0,
};

void bhv_whirlpool_init(void) {
    o->oWhirlpoolInitFacePitch = o->oFaceAnglePitch;
    o->oWhirlpoolInitFaceRoll = o->oFaceAngleRoll;
    o->oFaceAnglePitch = 0;
    o->oFaceAngleRoll = 0;
}

void whirlpool_set_hitbox(void) {
    obj_set_hitbox(o, &sWhirlpoolHitbox);
}

void whirpool_orient_graph(void) {
    f32 cosPitch = coss(o->oFaceAnglePitch);
    f32 sinPitch = sins(o->oFaceAnglePitch);
    f32 cosRoll = coss(o->oFaceAngleRoll);
    f32 sinRoll = sins(o->oFaceAngleRoll);
    f32 normalX = sinRoll * cosPitch;
    f32 normalY = cosPitch * cosRoll;
    f32 normalZ = sinPitch;
    obj_orient_graph(o, normalX, normalY, normalZ);
}

void bhv_whirlpool_loop(void) {
    if (o->oWhirlpoolTimeout > 0) {
        o->oWhirlpoolTimeout--;
        if (o->oWhirlpoolTimeout <= 0) {
            o->oInteractStatus = 0;
        }
    } else if (o->oInteractStatus == INT_STATUS_INTERACTED) {
        o->oWhirlpoolTimeout = 30;
    }

    f32 marioDist = dist_between_objects(o, gMarioStates[0].marioObj);
    if (marioDist < 5000.0f * draw_distance_scalar()) {
        o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
    } else {
        o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
    }

    // not sure if actually an array
    gEnvFxBubbleConfig[ENVFX_STATE_PARTICLECOUNT] = 60;
    gEnvFxBubbleConfig[ENVFX_STATE_SRC_X] = o->oPosX;
    gEnvFxBubbleConfig[ENVFX_STATE_SRC_Z] = o->oPosZ;
    gEnvFxBubbleConfig[ENVFX_STATE_DEST_X] = o->oPosX;
    gEnvFxBubbleConfig[ENVFX_STATE_DEST_Y] = o->oPosY;
    gEnvFxBubbleConfig[ENVFX_STATE_DEST_Z] = o->oPosZ;
    gEnvFxBubbleConfig[ENVFX_STATE_SRC_Y] = o->oPosY + 800.0f;
    gEnvFxBubbleConfig[ENVFX_STATE_PITCH] = o->oWhirlpoolInitFacePitch;
    gEnvFxBubbleConfig[ENVFX_STATE_YAW] = o->oWhirlpoolInitFaceRoll;

    whirpool_orient_graph();

    o->oFaceAngleYaw += 0x1F40;

    cur_obj_play_sound_1(SOUND_ENV_WATER);

    whirlpool_set_hitbox();
}

void bhv_jet_stream_loop(void) {
    f32 marioDist = dist_between_objects(o, gMarioStates[0].marioObj);
    if (marioDist < 5000.0f) {
        gEnvFxBubbleConfig[ENVFX_STATE_PARTICLECOUNT] = 60;
        gEnvFxBubbleConfig[ENVFX_STATE_SRC_X] = o->oPosX;
        gEnvFxBubbleConfig[ENVFX_STATE_SRC_Y] = o->oPosY;
        gEnvFxBubbleConfig[ENVFX_STATE_SRC_Z] = o->oPosZ;
    } else
        gEnvFxBubbleConfig[ENVFX_STATE_PARTICLECOUNT] = 0;

    cur_obj_play_sound_1(SOUND_ENV_WATER);
}
