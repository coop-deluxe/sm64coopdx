void bhv_ambient_light_update(void) {
    le_set_ambient_color(
        (o->oBehParams >> 24) & 0xFF,
        (o->oBehParams >> 16) & 0xFF,
        (o->oBehParams >> 8)  & 0xFF
    );
}


void bhv_point_light_init(void) {
    o->oLightID = le_add_light(
        // position
        o->oPosX, o->oPosY, o->oPosZ,
        // color
        (o->oBehParams >> 24) & 0xFF, (o->oBehParams >> 16) & 0xFF, (o->oBehParams >> 8) & 0xFF,
        // radius
        (o->oBehParams & 0xFF) * 10.0f,
        // intensity (2 by default)
        2.0f
    );
}

void bhv_point_light_loop(void) {
    if (o->parentObj != NULL) {
        if (o->parentObj->activeFlags == ACTIVE_FLAG_DEACTIVATED) {
            o->parentObj = NULL;
            le_remove_light(o->oLightID);
            obj_mark_for_deletion(o);
            return;
        }

        obj_copy_pos(o, o->parentObj);
    }

    le_set_light_pos(o->oLightID, o->oPosX, o->oPosY, o->oPosZ);
}
