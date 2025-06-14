#ifndef MOD_FS_H
#define MOD_FS_H

#include "types.h"
#include "lib/lua/include/lua.h"

#define MOD_FS_MAX_SIZE     0x1000000 // 16 MB
#define MOD_FS_MAX_FILES    0x100
#define MOD_FS_MAX_PATH     0x100
#define MOD_FS_DIRECTORY    "sav"
#define MOD_FS_EXTENSION    ".modfs"
#define MOD_FS_VERSION      1

enum ModFsFileIntType {
    INT_TYPE_U8,
    INT_TYPE_U16,
    INT_TYPE_U32,
    INT_TYPE_U64,
    INT_TYPE_S8,
    INT_TYPE_S16,
    INT_TYPE_S32,
    INT_TYPE_S64,

    INT_TYPE_MAX
};

enum ModFsFileFloatType {
    FLOAT_TYPE_F32,
    FLOAT_TYPE_F64,

    FLOAT_TYPE_MAX
};

enum ModFsFileSeek {
    FILE_SEEK_SET,
    FILE_SEEK_CUR,
    FILE_SEEK_END,

    FILE_SEEK_MAX
};

struct Mod;

struct ModFsFile {
    struct ModFs *modFs;
    char filepath[MOD_FS_MAX_PATH];
    union {
        u8 *bin;
        char *text;
    } data;
    u32 size;
    u32 capacity;
    u32 offset;
    bool isText;
    bool isPublic;
};

struct ModFs {
    struct Mod *mod;
    char modPath[SYS_MAX_PATH];
    struct ModFsFile **files;
    u16 numFiles;
    u32 totalSize;
    bool isPublic;
};

/* |description|
Checks the existence of a modfs at path `modPath` or for the active mod if not provided
|descriptionEnd| */
bool mod_fs_exists(OPTIONAL const char *modPath);

/* |description|
Gets the modfs object at path `modPath` or the active mod one if not provided
|descriptionEnd| */
struct ModFs *mod_fs_get(OPTIONAL const char *modPath);

/* |description|
Creates a modfs object for the active mod if it doesn't exist
|descriptionEnd| */
struct ModFs *mod_fs_create();

/* |description|
Deletes the modfs object of the active mod if it exists
|descriptionEnd| */
void mod_fs_delete();

/* |description|
Saves the modfs object of the active mod if it exists
|descriptionEnd| */
void mod_fs_save();

/* |description|
Marks the modfs object of the active mod as public (i.e. readable by other mods) if it exists
|descriptionEnd| */
void mod_fs_set_public(bool pub);

const char *mod_fs_get_filename(struct ModFs *modFs, u16 index);
struct ModFsFile *mod_fs_get_file(struct ModFs *modFs, const char *filepath);
struct ModFsFile *mod_fs_create_file(struct ModFs *modFs, const char *filepath, bool text);
void mod_fs_move_file(struct ModFs *modFs, const char *oldpath, const char *newpath, bool overwriteExisting);
void mod_fs_copy_file(struct ModFs *modFs, const char *srcpath, const char *dstpath, bool overwriteExisting);
void mod_fs_delete_file(struct ModFs *modFs, const char *filepath);
void mod_fs_clear(struct ModFs *modFs);

bool mod_fs_file_read_bool(struct ModFsFile *file);
lua_Integer mod_fs_file_read_integer(struct ModFsFile *file, enum ModFsFileIntType intType);
lua_Number mod_fs_file_read_number(struct ModFsFile *file, enum ModFsFileFloatType floatType);
const char *mod_fs_file_read_string(struct ModFsFile *file);
const char *mod_fs_file_read_line(struct ModFsFile *file);

void mod_fs_file_write_bool(struct ModFsFile *file, bool value);
void mod_fs_file_write_integer(struct ModFsFile *file, lua_Integer value, enum ModFsFileIntType intType);
void mod_fs_file_write_number(struct ModFsFile *file, lua_Number value, enum ModFsFileFloatType floatType);
void mod_fs_file_write_string(struct ModFsFile *file, const char *str);
void mod_fs_file_write_line(struct ModFsFile *file, const char *str);

void mod_fs_file_seek(struct ModFsFile *file, s32 offset, enum ModFsFileSeek origin);
bool mod_fs_file_is_eof(struct ModFsFile *file);
void mod_fs_file_erase(struct ModFsFile *file, u32 length);
void mod_fs_file_set_public(struct ModFsFile *file, bool pub);

#endif // MOD_FS_H
