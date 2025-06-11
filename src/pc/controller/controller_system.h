struct ControllerInfo {
    u8 index;
    u32 type;
    bool connected;
    SDL_GameController *sdl_cntrl;
    SDL_Joystick *sdl_joystick;
    SDL_Haptic *sdl_haptic;
};

extern char *gGamepadChoices[];
extern bool gSuppressConnectedPopup;
extern int gNumJoys;
extern struct ControllerInfo *gReadingController;
extern struct ControllerInfo gPlayerControllerInfos[];

void controller_update_gamepad_choices();
void controller_update_controller_count();
void controller_update_connected_controllers();
