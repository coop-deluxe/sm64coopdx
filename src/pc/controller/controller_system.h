struct ControllerPlace {
    u8 index;
    u32 type;
    bool connected;
};

extern char *gGamepadChoices[];
extern int gNumJoys;
extern struct ControllerPlace gPlayerControllerInfos[];

void controller_update_gamepad_choices();
void controller_update_controller_count();
void controller_update_connected_controllers();

