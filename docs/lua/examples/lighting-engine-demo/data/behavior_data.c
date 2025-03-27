/* ================ New Behaviors ================  */

const BehaviorScript bhvFlashlight[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    ID(id_bhvNewId), // id_bhvNewId signifies a new behavior.
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    CALL_NATIVE(bhv_point_light_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bhv_flashlight_loop),
    END_LOOP(),
};
