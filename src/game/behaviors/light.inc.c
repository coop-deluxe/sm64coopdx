struct Object* spawn_ambient_light(f32 x, f32 y, f32 z, u8 r, u8 g, u8 b) {
    struct Object* obj = spawn_object(NULL, MODEL_NONE, bhvAmbientLight);

    obj->oPosX = x;
    obj->oPosY = y;
    obj->oPosZ = z;
    obj->oBehParams = (r << 24) | (g << 16) | (b << 8) | (0x00);
    return obj;
}

struct Object* spawn_point_light(f32 x, f32 y, f32 z, u8 r, u8 g, u8 b, f32 radius) {
    struct Object* obj = spawn_object(NULL, MODEL_NONE, bhvPointLight);

    obj->oPosX = x;
    obj->oPosY = y;
    obj->oPosZ = z;
    obj->oBehParams = (r << 24) | (g << 16) | (b << 8) | (0x00);
    obj->oLightRadius = radius;
    return obj;
}

void bhv_ambient_light_update(void) {
    le_set_ambient_color(
        (o->oBehParams >> 24) & 0xFF,
        (o->oBehParams >> 16) & 0xFF,
        (o->oBehParams >> 8)  & 0xFF
    );
}


void bhv_point_light_init(void) {
    // assign oLightRadius
    f32 radius = (o->oBehParams & 0xFF) * 10.0f;
    if (o->oLightRadius != 0.0f) {
        radius = o->oLightRadius;
    } else if (radius != 0) {
        o->oLightRadius = radius;
    }

    o->oLightID = le_add_light(
        // position
        o->oPosX, o->oPosY, o->oPosZ,
        // color
        (o->oBehParams >> 24) & 0xFF, (o->oBehParams >> 16) & 0xFF, (o->oBehParams >> 8) & 0xFF,
        // radius
        radius,
        // intensity (2 by default)
        2.0f
    );
}

void bhv_point_light_loop(void) {
    if (o->parentObj != NULL) {
        if (o->parentObj->activeFlags == ACTIVE_FLAG_DEACTIVATED) {
            le_remove_light(o->oLightID);
            obj_mark_for_deletion(o);
            return;
        }

        obj_copy_pos(o, o->parentObj);
    }

    // update these values every frame
    le_set_light_pos(o->oLightID, o->oPosX, o->oPosY, o->oPosZ);
    le_set_light_color(o->oLightID, (o->oBehParams >> 24) & 0xFF, (o->oBehParams >> 16) & 0xFF, (o->oBehParams >> 8) & 0xFF);
    le_set_light_radius(o->oLightID, o->oLightRadius);
}
