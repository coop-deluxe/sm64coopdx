#ifndef FIRST_PERSON_CAM_H
#define FIRST_PERSON_CAM_H

#include "types.h"

#define FIRST_PERSON_DEFAULT_FOV 70

struct FirstPersonCamera {
    bool enabled;
    bool forceRoll;
    s16 pitch;
    s16 yaw;
    f32 crouch;
    f32 fov;
};

extern struct FirstPersonCamera gFirstPersonCamera;

bool first_person_check_cancels(struct MarioState *m);

bool get_first_person_enabled(void);
void set_first_person_enabled(bool enable);

void first_person_update(void);
void first_person_reset(void);

#endif // FIRST_PERSON_CAM_H