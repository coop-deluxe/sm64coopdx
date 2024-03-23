// == dialog ==
// (defines en_dialog_table etc.)

#define DEFINE_DIALOG(id, _1, _2, _3, _4, _len) \
    static u8 dialog_text_ ## id[_len] = { 0xFF };

#include "dialogs.h"

#undef DEFINE_DIALOG
#define DEFINE_DIALOG(id, _1, _2, _3, _4, _5) dialog_text_ ## id,

const u8* seg2_dialog_original[] = {
#include "dialogs.h"
    NULL
};

#undef DEFINE_DIALOG
#define DEFINE_DIALOG(id, unused, linesPerBox, leftOffset, width, _) \
    static struct DialogEntry dialog_entry_ ## id = { \
        unused, linesPerBox, leftOffset, width, dialog_text_ ## id \
    };

#include "dialogs.h"

#undef DEFINE_DIALOG
#define DEFINE_DIALOG(id, _1, _2, _3, _4, _5) &dialog_entry_ ## id,

const struct DialogEntry *const seg2_dialog_table[] = {
#include "dialogs.h"
    NULL
};

// == courses ==
// (defines en_course_name_table etc.)
// The game duplicates this in levels/menu/leveldata.c in EU, so we split
// it out into a separate include file.

#define COURSE_TABLE seg2_course_name_table
#include "define_courses.inc.c"

// == acts ==
// (defines en_act_name_table etc.)

#define COURSE_ACTS(id, name, a,b,c,d,e,f) \
    static u8 act_name_ ## id ## _1[a] = { 0xFF }; \
    static u8 act_name_ ## id ## _2[b] = { 0xFF }; \
    static u8 act_name_ ## id ## _3[c] = { 0xFF }; \
    static u8 act_name_ ## id ## _4[d] = { 0xFF }; \
    static u8 act_name_ ## id ## _5[e] = { 0xFF }; \
    static u8 act_name_ ## id ## _6[f] = { 0xFF };

#define SECRET_STAR(id, name)
#define CASTLE_SECRET_STARS(str)

#undef EXTRA_TEXT
#define EXTRA_TEXT(id, str) \
    static u8 extra_text_ ## id[str] = { 0xFF };

#include "courses.h"

#undef COURSE_ACTS
#undef EXTRA_TEXT

#define COURSE_ACTS(id, name, a,b,c,d,e,f) \
    act_name_ ## id ## _1, act_name_ ## id ## _2, act_name_ ## id ## _3, \
    act_name_ ## id ## _4, act_name_ ## id ## _5, act_name_ ## id ## _6,
#define EXTRA_TEXT(id, str) extra_text_ ## id,

const u8* seg2_act_name_table[] = {
#include "courses.h"
    NULL
};

const u8* seg2_act_name_table_original[] = {
#include "courses.h"
    NULL
};

#include "dialog_assets.inc.c"
#include "courses_assets.inc.c"
