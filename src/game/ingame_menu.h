#ifndef INGAME_MENU_H
#define INGAME_MENU_H

#include <PR/ultratypes.h>

#define ASCII_TO_DIALOG(asc)                                       \
    (((asc) >= '0' && (asc) <= '9') ? ((asc) - '0') :              \
     ((asc) >= 'A' && (asc) <= 'Z') ? ((asc) - 'A' + 0x0A) :       \
     ((asc) >= 'a' && (asc) <= 'z') ? ((asc) - 'a' + 0x24) : 0xF4)

#define MENU_MTX_PUSH   1
#define MENU_MTX_NOPUSH 2

#define MENU_SCROLL_VERTICAL   1
#define MENU_SCROLL_HORIZONTAL 2

// Japanese File Select uses an unique table
// to print specific Japanese HUD chars
#define HUD_LUT_JPMENU 1
#define HUD_LUT_GLOBAL 2

// For file select JP HUD difference
#if defined(VERSION_JP) || defined(VERSION_SH)
#define HUD_LUT_DIFF HUD_LUT_JPMENU
#else
#define HUD_LUT_DIFF HUD_LUT_GLOBAL
#endif

#define RENDER_PAUSE_SCREEN       1
#define RENDER_COURSE_DONE_SCREEN 2


#if !defined(VERSION_JP) && !defined(VERSION_SH)
extern u8 gDialogCharWidths[];
#endif

extern s8 gDialogCourseActNum;
extern s8 gHudFlash;

struct DialogEntry
{
 /*0x00*/ u32 unused;
 /*0x04*/ s8 linesPerBox;
 /*0x06*/ s16 leftOffset;
 /*0x08*/ s16 width;
 /*0x0C*/ const u8 *str;
};

// EU only
enum HudSpecialHUDChars {
    HUD_CHAR_A_UMLAUT = 0x3A,
    HUD_CHAR_O_UMLAUT = 0x3B,
    HUD_CHAR_U_UMLAUT = 0x3C
};

enum SpecialFontChars {
    GLOBAL_CHAR_SPACE = 0x9E,
    GLOBAR_CHAR_TERMINATOR = 0xFF
};

// definitions for some of the special characters defined in charmap.txt
enum DialogSpecialChars {
#ifdef VERSION_EU
    DIALOG_CHAR_LOWER_A_GRAVE = 0x60,      // 'a' grave
    DIALOG_CHAR_LOWER_A_CIRCUMFLEX = 0x61, // 'a' circumflex
    DIALOG_CHAR_LOWER_A_UMLAUT = 0x62,     // 'a' umlaut
    DIALOG_CHAR_UPPER_A_GRAVE = 0x64,      // 'A' grave
    DIALOG_CHAR_UPPER_A_CIRCUMFLEX = 0x65, // 'A' circumflex
    DIALOG_CHAR_UPPER_A_UMLAUT = 0x66,     // 'A' umlaut
    DIALOG_CHAR_LOWER_E_GRAVE = 0x70,      // 'e' grave
    DIALOG_CHAR_LOWER_E_CIRCUMFLEX = 0x71, // 'e' circumflex
    DIALOG_CHAR_LOWER_E_UMLAUT = 0x72,     // 'e' umlaut
    DIALOG_CHAR_LOWER_E_ACUTE = 0x73,      // 'e' acute
    DIALOG_CHAR_UPPER_E_GRAVE = 0x74,      // 'E' grave
    DIALOG_CHAR_UPPER_E_CIRCUMFLEX = 0x75, // 'E' circumflex
    DIALOG_CHAR_UPPER_E_UMLAUT = 0x76,     // 'E' umlaut
    DIALOG_CHAR_UPPER_E_ACUTE = 0x77,      // 'E' acute
    DIALOG_CHAR_LOWER_U_GRAVE = 0x80,      // 'u' grave
    DIALOG_CHAR_LOWER_U_CIRCUMFLEX = 0x81, // 'u' circumflex
    DIALOG_CHAR_LOWER_U_UMLAUT = 0x82,     // 'u' umlaut
    DIALOG_CHAR_UPPER_U_GRAVE = 0x84,      // 'U' grave
    DIALOG_CHAR_UPPER_U_CIRCUMFLEX = 0x85, // 'U' circumflex
    DIALOG_CHAR_UPPER_U_UMLAUT = 0x86,     // 'U' umlaut
    DIALOG_CHAR_LOWER_O_CIRCUMFLEX = 0x91, // 'o' circumflex
    DIALOG_CHAR_LOWER_O_UMLAUT = 0x92,     // 'o' umlaut
    DIALOG_CHAR_UPPER_O_CIRCUMFLEX = 0x95, // 'O' circumflex
    DIALOG_CHAR_UPPER_O_UMLAUT = 0x96,     // 'O' umlaut
    DIALOG_CHAR_LOWER_I_CIRCUMFLEX = 0xA1, // 'i' circumflex
    DIALOG_CHAR_LOWER_I_UMLAUT = 0xA2,     // 'i' umlaut
    DIALOG_CHAR_I_NO_DIA = 0xEB,           // 'i' without diacritic
    DIALOG_CHAR_DOUBLE_LOW_QUOTE = 0xF0,   // German opening quotation mark
#endif
#if defined(VERSION_US) || defined(VERSION_EU)
    DIALOG_CHAR_SLASH = 0xD0,
    DIALOG_CHAR_MULTI_THE = 0xD1, // 'the'
    DIALOG_CHAR_MULTI_YOU = 0xD2, // 'you'
#endif
    DIALOG_CHAR_PERIOD = 0x6E,
    DIALOG_CHAR_COMMA = 0x6F,
    DIALOG_CHAR_SPACE = 0x9E,
    DIALOG_CHAR_STAR_COUNT = 0xE0, // number of stars
    DIALOG_CHAR_UMLAUT = 0xE9,
    DIALOG_CHAR_DAKUTEN = 0xF0,
    DIALOG_CHAR_PERIOD_OR_HANDAKUTEN = 0xF1,
    DIALOG_CHAR_STAR_FILLED = 0xFA,
    DIALOG_CHAR_STAR_OPEN = 0xFD,
    DIALOG_CHAR_NEWLINE = 0xFE,
    DIALOG_CHAR_TERMINATOR = 0xFF
};

extern s32 gDialogResponse;
extern u16 gDialogColorFadeTimer;
extern s8 gLastDialogLineNum;
extern s32 gDialogVariable;
extern u16 gDialogTextAlpha;
extern s16 gCutsceneMsgXOffset;
extern s16 gCutsceneMsgYOffset;
extern s16 gDialogMinWidth;
extern s16 gDialogMinHeight;
extern s16 gDialogOverrideX;
extern s16 gDialogOverrideY;
extern u8 gOverrideDialogPos;
extern u8 gOverrideDialogColor;
extern u8 gDialogBgColorR;
extern u8 gDialogBgColorG;
extern u8 gDialogBgColorB;
extern u8 gDialogBgColorA;
extern u8 gDialogTextColorR;
extern u8 gDialogTextColorG;
extern u8 gDialogTextColorB;
extern u8 gDialogTextColorA;

void create_dl_identity_matrix(void);
void create_dl_translation_matrix(s8 pushOp, f32 x, f32 y, f32 z);
void create_dl_rotation_matrix(s8 pushOp, f32 a, f32 x, f32 y, f32 z);
void create_dl_ortho_matrix(void);
void render_generic_char(u8 c);
u8 str_ascii_char_to_dialog(char c);
void str_ascii_to_dialog(const char* string, u8* dialog, u16 length);
f32 get_generic_dialog_width(u8* dialog);
f32 get_generic_ascii_string_width(const char* ascii);
f32 get_generic_dialog_height(u8* dialog);
f32 get_generic_ascii_string_height(const char* ascii);
void print_generic_ascii_string(s16 x, s16 y, const char* ascii);
void print_generic_string(s16 x, s16 y, const u8 *str);
void print_hud_lut_string(s8 hudLUT, s16 x, s16 y, const u8 *str);
void print_menu_generic_string(s16 x, s16 y, const u8 *str);
void handle_menu_scrolling(s8 scrollDirection, s8 *currentIndex, s8 minIndex, s8 maxIndex);
#if defined(VERSION_US) || defined(VERSION_EU)
s16 get_str_x_pos_from_center(s16 centerPos, u8 *str, f32 scale);
#endif
#if defined(VERSION_JP) || defined(VERSION_SH)
#define get_str_x_pos_from_center get_str_x_pos_from_center_scale
#endif
#if defined(VERSION_JP) || defined(VERSION_EU) || defined(VERSION_SH)
s16 get_str_x_pos_from_center_scale(s16 centerPos, u8 *str, f32 scale);
#endif
void print_hud_my_score_coins(s32 useCourseCoinScore, s8 fileNum, s8 courseNum, s16 x, s16 y);
void int_to_str(s32 num, u8 *dst);
s16 get_dialog_id(void);
/* |description|Creates a dialog box with a dialog ID that rotates into view|descriptionEnd| */
void create_dialog_box(s16 dialog);
/* |description|Creates a dialog box with a dialog variable|descriptionEnd| */
void create_dialog_box_with_var(s16 dialog, s32 dialogVar);
/* |description|Creates a dialog box with a dialog ID that zooms into view|descriptionEnd| */
void create_dialog_inverted_box(s16 dialog);
/* |description|Creates a dialog box with a response|descriptionEnd| */
void create_dialog_box_with_response(s16 dialog);
/* |description|Resets the dialog box's state including dialog ID and open state|descriptionEnd| */
void reset_dialog_render_state(void);
/* |description|
Sets the in-game menu state. 0-1 is the courses box with the castle secret stars and 2-3 is the course completion screen.
|descriptionEnd| */
void set_menu_mode(s16 mode);
void reset_cutscene_msg_fade(void);
void dl_rgba16_begin_cutscene_msg_fade(void);
void dl_rgba16_stop_cutscene_msg_fade(void);
void print_credits_str_ascii(s16 x, s16 y, const char *str);
void set_cutscene_message(s16 xOffset, s16 yOffset, s16 msgIndex, s16 msgDuration);
void do_cutscene_handler(void);
void render_hud_cannon_reticle(void);
void reset_red_coins_collected(void);
s16 render_menus_and_dialogs(void);
void create_dl_scale_matrix(s8 pushOp, f32 x, f32 y, f32 z);
/* |description|Dialog box customization: Sets the minimum width for a dialog box|descriptionEnd| */
void set_min_dialog_width(s16 width);
/* |description|Dialog box customization: Sets the override position for a dialog box|descriptionEnd| */
void set_dialog_override_pos(s16 x, s16 y);
/* |description|Dialog box customization: Resets the override position for a dialog box|descriptionEnd| */
void reset_dialog_override_pos();
/* |description|Dialog box customization: Sets the override color for a dialog box|descriptionEnd| */
void set_dialog_override_color(u8 bgR, u8 bgG, u8 bgB, u8 bgA, u8 textR, u8 textG, u8 textB, u8 textA);
/* |description|Dialog box customization: Resets the override color for a dialog box|descriptionEnd| */
void reset_dialog_override_color();
/* |description|Sets the state for a dialog box (`DIALOG_STATE_*`)|descriptionEnd| */
void set_dialog_box_state(u8 state);

#endif // INGAME_MENU_H
