#define COURSE_ACTS(id, name, a,b,c,d,e,f) \
    static u8 GLUE2(COURSE_TABLE, _ ## id)[name] = { 0xFF };

#define SECRET_STAR(id, name) \
    static u8 GLUE2(COURSE_TABLE, _ ## id)[name] = { 0xFF };

#define CASTLE_SECRET_STARS(str) \
    static u8 GLUE2(COURSE_TABLE, _castle_secret_stars)[str] = { 0xFF };

#define EXTRA_TEXT(id, str)

#include "courses.h"

#undef COURSE_ACTS
#undef SECRET_STAR
#undef CASTLE_SECRET_STARS

#define COURSE_ACTS(id, name, a,b,c,d,e,f) GLUE2(COURSE_TABLE, _ ## id),
#define SECRET_STAR(id, name) GLUE2(COURSE_TABLE, _ ## id),
#define CASTLE_SECRET_STARS(str) GLUE2(COURSE_TABLE, _castle_secret_stars),

const u8* COURSE_TABLE[] = {
#include "courses.h"
    NULL
};

const u8* GLUE2(COURSE_TABLE, _original)[] = {
#include "courses.h"
    NULL
};

#undef COURSE_ACTS
#undef SECRET_STAR
#undef CASTLE_SECRET_STARS

