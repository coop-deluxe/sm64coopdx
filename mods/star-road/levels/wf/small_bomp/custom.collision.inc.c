const Collision wf_seg7_collision_small_bomp[] = {
    COL_INIT(),
    COL_VERTEX_INIT(4),
    COL_VERTEX(0,  192, -193),
    COL_VERTEX(0, -192,  193),
    COL_VERTEX(0,  192,  193),
    COL_VERTEX(0, -192, -193),
    COL_TRI_INIT(SURFACE_NO_CAM_COLLISION, 2),
    COL_TRI(0, 1, 2),
    COL_TRI(1, 0, 3),
    COL_TRI_STOP(),
    COL_END(),
};
