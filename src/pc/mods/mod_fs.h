#ifndef MOD_FS_H
#define MOD_FS_H

#include "types.h"
#include "src/pc/lua/smlua.h"

#define MOD_FS_MAX_SIZE     0x2000000 // 32 MB
#define MOD_FS_MAX_FILES    0x200
#define MOD_FS_MAX_PATH     0x100
#define MOD_FS_URI_PREFIX   "modfs:/"
#define MOD_FS_URI_FORMAT   "modfs:/%s/%s" // modPath, filepath

#define is_mod_fs_file(filepath) (memcmp(filepath, MOD_FS_URI_PREFIX, sizeof(MOD_FS_URI_PREFIX) - 1) == 0)

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

    FUNCTION(read_bool, mod_fs_file_read_bool);
    FUNCTION(read_integer, mod_fs_file_read_integer);
    FUNCTION(read_number, mod_fs_file_read_number);
    FUNCTION(read_bytes, mod_fs_file_read_bytes);
    FUNCTION(read_string, mod_fs_file_read_string);
    FUNCTION(read_line, mod_fs_file_read_line);
    FUNCTION(write_bool, mod_fs_file_write_bool);
    FUNCTION(write_integer, mod_fs_file_write_integer);
    FUNCTION(write_number, mod_fs_file_write_number);
    FUNCTION(write_bytes, mod_fs_file_write_bytes);
    FUNCTION(write_string, mod_fs_file_write_string);
    FUNCTION(write_line, mod_fs_file_write_line);
    FUNCTION(seek, mod_fs_file_seek);
    FUNCTION(rewind, mod_fs_file_rewind);
    FUNCTION(is_eof, mod_fs_file_is_eof);
    FUNCTION(fill, mod_fs_file_fill);
    FUNCTION(erase, mod_fs_file_erase);
    FUNCTION(set_text_mode, mod_fs_file_set_text_mode);
    FUNCTION(set_public, mod_fs_file_set_public);
};

struct ModFs {
    struct Mod *mod;
    char modPath[SYS_MAX_PATH];
    struct ModFsFile **files;
    u16 numFiles;
    u32 totalSize;
    bool isPublic;

    FUNCTION(get_filename, mod_fs_get_filename);
    FUNCTION(get_file, mod_fs_get_file);
    FUNCTION(create_file, mod_fs_create_file);
    FUNCTION(move_file, mod_fs_move_file);
    FUNCTION(copy_file, mod_fs_copy_file);
    FUNCTION(delete_file, mod_fs_delete_file);
    FUNCTION(clear, mod_fs_clear);
    FUNCTION(save, mod_fs_save);
    FUNCTION(delete, mod_fs_delete);
    FUNCTION(set_public, mod_fs_set_public);
};

/* |description|
Checks the existence of a modfs at path `modPath` or for the active mod if not provided. Checking for the existence of a private modfs will return false, even if it exists
|descriptionEnd| */
bool mod_fs_exists(OPTIONAL const char *modPath);

/* |description|
Gets the modfs object at path `modPath` or the active mod one if not provided. This function will return nil for a private modfs, even if it exists
|descriptionEnd| */
struct ModFs *mod_fs_get(OPTIONAL const char *modPath);

/* |description|
Reloads the modfs object at path `modPath`. This function will return nil for a private modfs, even if it exists
|descriptionEnd| */
struct ModFs *mod_fs_reload(OPTIONAL const char *modPath);

/* |description|
Creates a modfs object for the active mod if it doesn't exist. Returns the modfs object on success
|descriptionEnd| */
struct ModFs *mod_fs_create();

/* |description|
Gets the filename at position `index` of the provided `modFs`
|descriptionEnd| */
const char *mod_fs_get_filename(struct ModFs *modFs, u16 index);

/* |description|
Gets the file object at path `filepath` of the provided `modFs`. This function will return nil for a private modfs file, even if it exists
|descriptionEnd| */
struct ModFsFile *mod_fs_get_file(struct ModFs *modFs, const char *filepath);

/* |description|
Creates a new file at path `filepath` for the provided `modFs`. Set `text` to true to treat the file as a pure text file, not a binary file. Returns the created file on success
|descriptionEnd| */
struct ModFsFile *mod_fs_create_file(struct ModFs *modFs, const char *filepath, bool text);

/* |description|
Moves the file at path `oldpath` to `newpath` of the provided `modFs`. Set `overwriteExisting` to true to overwrite the file at path `newpath` if it exists. Returns true on success
|descriptionEnd| */
bool mod_fs_move_file(struct ModFs *modFs, const char *oldpath, const char *newpath, bool overwriteExisting);

/* |description|
Copies the file at path `srcpath` to `dstpath` of the provided `modFs`. Set `overwriteExisting` to true to overwrite the file at path `dstpath` if it exists. Returns true on success
|descriptionEnd| */
bool mod_fs_copy_file(struct ModFs *modFs, const char *srcpath, const char *dstpath, bool overwriteExisting);

/* |description|
Deletes the file at path `filepath` of the provided `modFs`. Returns true on success
|descriptionEnd| */
bool mod_fs_delete_file(struct ModFs *modFs, const char *filepath);

/* |description|
Deletes all files of the provided `modFs`. Returns true on success
|descriptionEnd| */
bool mod_fs_clear(struct ModFs *modFs);

/* |description|
Saves the provided `modFs` to persistent storage. Returns true on success
|descriptionEnd| */
bool mod_fs_save(struct ModFs *modFs);

/* |description|
Removes the provided `modFs` from persistent storage and deletes its object. Returns true on success
|descriptionEnd| */
bool mod_fs_delete(struct ModFs *modFs);

/* |description|
Marks the provided `modFs` as public (i.e. readable by other mods). Returns true on success
|descriptionEnd| */
bool mod_fs_set_public(struct ModFs *modFs, bool pub);

/* |description|
Reads a boolean from a binary modfs `file`
|descriptionEnd| */
bool mod_fs_file_read_bool(struct ModFsFile *file);

/* |description|
Reads an integer from a binary modfs `file`. `intType` must be one of the `INT_TYPE_*` constants
|descriptionEnd| */
lua_Integer mod_fs_file_read_integer(struct ModFsFile *file, enum ModFsFileIntType intType);

/* |description|
Reads an floating-point number from a binary modfs `file`. `floatType` must be one of the `FLOAT_TYPE_*` constants
|descriptionEnd| */
lua_Number mod_fs_file_read_number(struct ModFsFile *file, enum ModFsFileFloatType floatType);

/* |description|
Reads a bytestring of `length` bytes from a binary modfs `file`
|descriptionEnd| */
ByteString mod_fs_file_read_bytes(struct ModFsFile *file, u32 length);

/* |description|
Reads a string from a binary modfs `file`, or read the whole content of a text modfs `file`
|descriptionEnd| */
const char *mod_fs_file_read_string(struct ModFsFile *file);

/* |description|
Reads a line from a text modfs `file`
|descriptionEnd| */
const char *mod_fs_file_read_line(struct ModFsFile *file);

/* |description|
Writes a boolean to a binary modfs `file`. Returns true on success
|descriptionEnd| */
bool mod_fs_file_write_bool(struct ModFsFile *file, bool value);

/* |description|
Writes an integer to a binary modfs `file`. `intType` must be one of the `INT_TYPE_*` constants. Returns true on success
|descriptionEnd| */
bool mod_fs_file_write_integer(struct ModFsFile *file, lua_Integer value, enum ModFsFileIntType intType);

/* |description|
Writes an floating-point number to a binary modfs `file`. `floatType` must be one of the `FLOAT_TYPE_*` constants. Returns true on success
|descriptionEnd| */
bool mod_fs_file_write_number(struct ModFsFile *file, lua_Number value, enum ModFsFileFloatType floatType);

/* |description|
Writes a bytestring to a modfs `file`. Returns true on success
|descriptionEnd| */
bool mod_fs_file_write_bytes(struct ModFsFile *file, ByteString bytestring);

/* |description|
Writes a string to a modfs `file`. Returns true on success
|descriptionEnd| */
bool mod_fs_file_write_string(struct ModFsFile *file, const char *str);

/* |description|
Writes a line to a text modfs `file`. Returns true on success
|descriptionEnd| */
bool mod_fs_file_write_line(struct ModFsFile *file, const char *str);

/* |description|
Sets the current position of a modfs `file`.
If `origin` is `FILE_SEEK_SET`, file position is set to `offset`.
If `origin` is `FILE_SEEK_CUR`, `offset` is added to file current position.
If `origin` is `FILE_SEEK_END`, file position is set to `end of file + offset`.
Returns true on success
|descriptionEnd| */
bool mod_fs_file_seek(struct ModFsFile *file, s32 offset, enum ModFsFileSeek origin);

/* |description|
Sets the current position of a modfs `file` to its beginning.
Returns true on success
|descriptionEnd| */
bool mod_fs_file_rewind(struct ModFsFile *file);

/* |description|
Returns true if the provided modfs `file` has reached its end of file
|descriptionEnd| */
bool mod_fs_file_is_eof(struct ModFsFile *file);

/* |description|
Fills a modfs `file` with `byte` repeated `length` times. Returns true on success
|descriptionEnd| */
bool mod_fs_file_fill(struct ModFsFile *file, u8 byte, u32 length);

/* |description|
Erases `length` bytes or characters from a modfs `file`. Returns true on success
|descriptionEnd| */
bool mod_fs_file_erase(struct ModFsFile *file, u32 length);

/* |description|
Marks the provided modfs `file` as text. Returns true on success
|descriptionEnd| */
bool mod_fs_file_set_text_mode(struct ModFsFile *file, bool text);

/* |description|
Marks the provided modfs `file` as public (i.e. readable by other mods). Returns true on success
|descriptionEnd| */
bool mod_fs_file_set_public(struct ModFsFile *file, bool pub);

/* |description|
Hides script errors raised by `mod_fs` functions. Errors messages are still generated and can be retrieved with `mod_fs_get_last_error()`
|descriptionEnd| */
void mod_fs_hide_errors(bool hide);

/* |description|
Returns the last error message generated by `mod_fs` functions or nil if no error occurred
|descriptionEnd| */
const char *mod_fs_get_last_error();

// Functions used by other C modules, not API

bool mod_fs_read_file_from_uri(const char *uri, void **buffer, u32 *length);
void mod_fs_shutdown();

#endif // MOD_FS_H
