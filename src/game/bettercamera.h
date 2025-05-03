#ifndef BETTERCAMERA_H
#define BETTERCAMERA_H

#include "types.h"

typedef struct {

    // Status
    bool isActive; // basically the thing that governs if newcam is on.
    bool isSlide;
    Vec3f pos; // Position the camera is in the world
    Vec3f posTarget; // The position the camera is basing calculations off. *Usually* Mario.
    Vec3f lookAt; // Position the camera is looking at
    f32 distance; // The distance the camera stays from the player
    s32 distanceTargetIndex;
    s16 yaw; // Z axis rotation
    s16 yawTarget; // The yaw value the camera tries to set itself to when the centre flag is active. Is set to Mario's face angle.
    f32 yawAccel;
    s16 tilt; // Y axis rotation
    f32 tiltAccel;
    f32 panX;
    f32 panZ;
    s32 framesSinceCButtons[2];
    bool centering; // The flag that depicts wether the camera's going to try centering.
    bool directionLocked;
    s32 turnWait; // The amount of time to wait after landing before allowing the camera to turn again
    s16 extStick[2];
    u8 savedMode;
    u8 savedDefMode;

    // Settings
    s16 sensitivityX; // How quick the camera works.
    s16 sensitivityY;
    s16 panLevel; // How much the camera sticks out a bit in the direction you're looking.
    s16 aggression; // How much the camera tries to centre itself to Mario's facing and movement.
    f32 deceleration;
    bool invertX; // Reverses movement of the camera axis.
    bool invertY;
    bool isMouse;
    bool isAnalogue; // Weither to accept inputs from a player 2 joystick, and then disables C button input.
    bool useDPad;
    bool hasCollision;
    bool LCentering;

} NewCamera;

extern NewCamera gNewCamera;

void newcam_init_settings(void);

#endif // BETTERCAMERA_H
