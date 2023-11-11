#ifndef FIRST_PERSON_CAM_H
#define FIRST_PERSON_CAM_H

#include <stdbool.h>
#include <PR/ultratypes.h>

#define FIRST_PERSON_DEFAULT_FOV 70

struct FirstPersonCamera {
    bool enabled;
    s16 pitch;
    s16 yaw;
    f32 crouch;
    f32 fov;
};

extern struct FirstPersonCamera gFirstPersonCamera;

bool update_first_person(void);

#endif