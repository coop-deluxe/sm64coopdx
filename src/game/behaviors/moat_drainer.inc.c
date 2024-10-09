// moat_drainer.c.inc

void bhv_invisible_objects_under_bridge_init(void) {
    if (save_file_get_flags() & SAVE_FLAG_MOAT_DRAINED) {
        if (gEnvironmentRegions && gEnvironmentRegionsLength > 12) {
            gEnvironmentRegions[6] = -800;
            gEnvironmentRegions[12] = -800;
        }
        o->oAction = 2;
    } else {
        o->oAction = 0;
    }
}

void bhv_invisible_objects_under_bridge_loop(void) {
    switch (o->oAction) {
        case 0:
            // wait for moat drained flag to get set
            if (save_file_get_flags() & SAVE_FLAG_MOAT_DRAINED) { o->oAction = 1; }
            break;
        case 1:
            // approach -800
            if (gEnvironmentRegions && gEnvironmentRegionsLength > 12) {
                gEnvironmentRegions[6]  = (s16)approach_f32_symmetric(gEnvironmentRegions[6],  -800, 5.0f);
                gEnvironmentRegions[12] = (s16)approach_f32_symmetric(gEnvironmentRegions[12], -800, 5.0f);
                if (gEnvironmentRegions[6] <= -795 && gEnvironmentRegions[12] <= -795) {
                    gEnvironmentRegions[6]  = -800;
                    gEnvironmentRegions[12] = -800;
                    o->oAction = 2;
                }
            }
            break;
        case 2:
            // clean up
            o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            break;
    }
}
