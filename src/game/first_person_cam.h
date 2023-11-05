#ifndef FIRST_PERSON_CAM_H
#define FIRST_PERSON_CAM_H

#include <stdbool.h>
#include <PR/ultratypes.h>

#define FIRST_PERSON_FOV 70

extern bool gFirstPersonEnabled;
extern s16 gFirstPersonYaw;

bool update_first_person(void);

#endif