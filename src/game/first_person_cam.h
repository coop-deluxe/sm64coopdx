#ifndef FIRST_PERSON_CAM_H
#define FIRST_PERSON_CAM_H

#include "types.h"

#define FIRST_PERSON_DEFAULT_FOV 70

#define FIRST_PERSON_MARIO_HEAD_POS 120
#define FIRST_PERSON_MARIO_HEAD_POS_SHORT 60

struct FirstPersonCamera {
    bool enabled;
    bool forceRoll;
    bool centerL;
    s16 pitch;
    s16 yaw;
    f32 crouch;
    Vec3f offset;
};

extern struct FirstPersonCamera gFirstPersonCamera;

bool first_person_check_cancels(struct MarioState *m);

bool get_first_person_enabled(void);

f32 get_dest_fov(f32 fov);
f32 get_dest_near(f32 near);

void first_person_update(void);
void first_person_reset(void);

#endif // FIRST_PERSON_CAM_H