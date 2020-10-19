#ifndef CUSTOM_MENU_SYSTEM_H
#define CUSTOM_MENU_SYSTEM_H
#include "file_select.h"

struct CustomMenuButton {
    struct Object* object;
    char* label;
    void (*on_click)(void);
    u32 clickSound;
    struct CustomMenu* menu;
    struct CustomMenuButton* next;
};

struct CustomMenu {
    struct CustomMenu* parent;
    struct CustomMenuButton* me;
    struct CustomMenuButton* buttons;
    u16 headerY;
    u16 depth;
    void (*draw_strings)(void);
    void (*on_close)(void);
};

struct CustomMenuButtonScale {
    f32 small;
    f32 medium;
    f32 large;
};
extern struct CustomMenuButtonScale gButtonScale;

extern u8 gMenuStringAlpha;

void custom_menu_system_init(void);
struct CustomMenu* custom_menu_create(struct CustomMenu* parent, char* label, u16 x, u16 y, f32 scale);
struct CustomMenuButton* custom_menu_create_button(struct CustomMenu* parent, char* label, u16 x, u16 y, f32 scale, s32 clickSound, void (*on_click)(void));

void custom_menu_system_loop(void);
void custom_menu_print_strings(void);
void custom_menu_render_top(void);
void custom_menu_cursor_click(f32 x, f32 y);

void custom_menu_open(struct CustomMenu* menu);
void custom_menu_close(void);
void custom_menu_close_system(void);

void bhv_menu_button_growing_from_custom(struct Object* button);
void bhv_menu_button_shrinking_to_custom(struct Object* button);

void custom_menu_error(char* message);

#endif // CUSTOM_MENU_SYSTEM_H
