#ifndef FIRST_PERSON_CAM_H
#define FIRST_PERSON_CAM_H

#include "types.h"

#define FIRST_PERSON_DEFAULT_FOV 70

#define FIRST_PERSON_MARIO_HEAD_POS 120
#define FIRST_PERSON_MARIO_HEAD_POS_SHORT 60

struct FirstPersonCamera {
    bool enabled;
    bool forcePitch;
    bool forceYaw;
    bool forceRoll;
    bool centerL;
    s16 pitch;
    s16 yaw;
    f32 crouch;
    f32 fov;
    Vec3f offset;
};

extern struct FirstPersonCamera gFirstPersonCamera;

/* |description|Checks common cancels for first person|descriptionEnd| */
bool first_person_check_cancels(struct MarioState *m);

/* |description|Checks if first person is enabled|descriptionEnd| */
bool get_first_person_enabled(void);
/* |description|Sets if first person is enabled|descriptionEnd| */
void set_first_person_enabled(bool enable);

void first_person_update(void);
/* |description|Resets first person|descriptionEnd| */
void first_person_reset(void);

#endif // FIRST_PERSON_CAM_H