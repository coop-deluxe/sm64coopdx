extern "C" {
#include "mod_fs.h"
#include "src/pc/lua/smlua.h"
#include "src/pc/fs/fs.h"
#include "src/pc/mods/mods_utils.h"
}
#include <algorithm>
#include <vector>
#include <string>
#include <map>

#define C_DEFINE extern "C"

static std::vector<struct ModFs *> sModFsList = {};
static char sModFsFileReadStringBuf[MOD_FS_MAX_SIZE + 1];

#define MOD_FS_MAGIC "MODFSSM64COOPDX"
#define MOD_FS_HEADER_SIZE 32

//
// Error handling
//

// Errors raised by `mod_fs` functions do not stop the code execution.
// When an error is raised:
// - the error message is printed to the console if `sModFsHideErrors` is false
// - `sModFsLastError` is filled with that error message
// - the function that raised it usually returns false or nil

static bool sModFsHideErrors = false;
static char sModFsLastError[1024];

#define mod_fs_reset_last_error() { \
    memset(sModFsLastError, 0, sizeof(sModFsLastError)); \
}

#define mod_fs_raise_error(fmt, ...) { \
    snprintf(sModFsLastError, sizeof(sModFsLastError), "%s: " fmt, __FUNCTION__, __VA_ARGS__); \
    if (!sModFsHideErrors) { \
        LOG_LUA_LINE("%s: " fmt, __FUNCTION__, __VA_ARGS__); \
    } \
}

//
// Utils
//

static bool mod_fs_is_active_mod(struct ModFs *modFs) {
    return gLuaActiveMod != NULL && modFs->mod == gLuaActiveMod;
}

static bool mod_fs_check_access(struct ModFs *modFs) {
    return mod_fs_is_active_mod(modFs) || modFs->isPublic;
}

static bool mod_fs_get_modpath(const char *modPath, char *dest) {
    if (modPath) {
        snprintf(dest, SYS_MAX_PATH, "%s", modPath);
    } else if (gLuaActiveMod) {
        snprintf(dest, SYS_MAX_PATH, "%s", gLuaActiveMod->relativePath);
    } else {
        return false;
    }
    char *ext = strstr(dest, ".lua");
    if (ext) *ext = 0;
    return true;
}

static FILE *mod_fs_get_file_handle(const char *modPath, const char *mode) {
    char realModPath[SYS_MAX_PATH];
    if (mod_fs_get_modpath(modPath, realModPath)) {
        const char *path = fs_get_write_path(MOD_FS_DIRECTORY);
        char filename[SYS_MAX_PATH];
        snprintf(filename, SYS_MAX_PATH, "%s/%s" MOD_FS_EXTENSION, path, realModPath);
        normalize_path(filename);
        return fopen(filename, mode);
    }
    return NULL;
}

//
// ctor, dtor
//

static struct ModFs *mod_fs_new() {
    if (gLuaActiveMod) {
        struct ModFs *modFs = (struct ModFs *) malloc(sizeof(struct ModFs));
        modFs->mod = gLuaActiveMod;
        mod_fs_get_modpath(NULL, modFs->modPath);
        modFs->files = NULL;
        modFs->numFiles = 0;
        modFs->totalSize = 0;
        modFs->isPublic = false;
        return modFs;
    }
    return NULL;
}

static void mod_fs_file_destroy(struct ModFsFile *file) {
    free(file->data.bin);
    memset(file, 0, sizeof(struct ModFsFile));
}

static void mod_fs_destroy(struct ModFs *modFs) {
    for (u16 i = 0; i != modFs->numFiles; ++i) {
        mod_fs_file_destroy(modFs->files[i]);
        free(modFs->files[i]);
    }
    free(modFs->files);
    memset(modFs, 0, sizeof(struct ModFs));
}

//
// Read
//

#define mod_fs_read_raise_error(modFs, f, ...) { \
    mod_fs_destroy(modFs); \
    fclose(f); \
    mod_fs_raise_error(__VA_ARGS__); \
    return false; \
}

#define mod_fs_read_fread_or_fail(modFs, f, buf, size, count, ...) { \
    if (fread(buf, size, count, f) < count) { \
        mod_fs_read_raise_error(modFs, f, __VA_ARGS__); \
    } \
}

static bool mod_fs_read(const char *modPath, struct ModFs *modFs, bool readHeaderOnly) {
    FILE *f = mod_fs_get_file_handle(modPath, "rb");
    if (f) {

        // get true modPath and mod
        if (!mod_fs_get_modpath(modPath, modFs->modPath)) {
            mod_fs_read_raise_error(modFs, f,
                "unable to retrieve modPath from %s", modPath
            );
        }
        char activeModPath[SYS_MAX_PATH];
        if (mod_fs_get_modpath(NULL, activeModPath) && strcmp(modFs->modPath, activeModPath) == 0) {
            modFs->mod = gLuaActiveMod;
        } else {
            modFs->mod = NULL;
        }

        // read magic (last byte is version)
        char magic[sizeof(MOD_FS_MAGIC)] = {0};
        mod_fs_read_fread_or_fail(modFs, f, magic, 1, sizeof(magic),
            "modPath: %s - cannot read file magic", modFs->modPath
        );
        if (memcmp(magic, MOD_FS_MAGIC, sizeof(MOD_FS_MAGIC) - 1) != 0) {
            mod_fs_read_raise_error(modFs, f,
                "modPath: %s - not a modfs file", modFs->modPath
            );
        }
        u8 version = (u8) magic[sizeof(MOD_FS_MAGIC) - 1];
        if (version == 0 || version > MOD_FS_VERSION) {
            mod_fs_read_raise_error(modFs, f,
                "modPath: %s - invalid version: %u (must be between 1 and %u)", modFs->modPath, version, MOD_FS_VERSION
            );
        }

        // read header
        mod_fs_read_fread_or_fail(modFs, f, &modFs->numFiles, sizeof(modFs->numFiles), 1,
            "modPath: %s - cannot read number of files", modFs->modPath
        );
        mod_fs_read_fread_or_fail(modFs, f, &modFs->isPublic, sizeof(modFs->isPublic), 1,
            "modPath: %s - cannot read public flag", modFs->modPath
        );

        // check validity
        if (modFs->numFiles > MOD_FS_MAX_FILES) {
            mod_fs_read_raise_error(modFs, f,
                "modPath: %s - exceeded number of files: %u (max is: %u)", modFs->modPath, modFs->numFiles, MOD_FS_MAX_FILES
            );
        }

        // check access
        if (!mod_fs_check_access(modFs)) {
            // don't raise an error, user should not know if a private modfs file exists
            mod_fs_destroy(modFs);
            fclose(f);
            return false;
        }
        if (readHeaderOnly) {
            fclose(f);
            return true;
        }

        // padding (empty space for future versions)
        if (fseek(f, MOD_FS_HEADER_SIZE, SEEK_SET) != 0) {
            mod_fs_read_raise_error(modFs, f,
                "modPath: %s - cannot read header", modFs->modPath
            );
        }

        // read files and compute total size
        if (modFs->numFiles) {
            modFs->files = (struct ModFsFile **) calloc(modFs->numFiles, sizeof(struct ModFsFile *));
        } else {
            modFs->files = NULL;
        }
        modFs->totalSize = 0;
        for (u16 i = 0; i != modFs->numFiles; ++i) {

            // check filepath length
            u16 filepathLength;
            mod_fs_read_fread_or_fail(modFs, f, &filepathLength, sizeof(filepathLength), 1,
                "modPath: %s - cannot read filepath length", modFs->modPath
            );
            if (filepathLength == 0) {
                mod_fs_read_raise_error(modFs, f,
                    "modPath: %s - filepath length cannot be 0", modFs->modPath
                );
            }
            if (filepathLength > MOD_FS_MAX_PATH - 1) {
                mod_fs_read_raise_error(modFs, f,
                    "modPath: %s - exceeded filepath length: %u (max is: %u)", modFs->modPath, filepathLength, MOD_FS_MAX_PATH - 1
                );
            }

            // get filename
            char filepath[MOD_FS_MAX_PATH];
            mod_fs_read_fread_or_fail(modFs, f, filepath, sizeof(char), filepathLength,
                "modPath: %s - cannot read filepath", modFs->modPath
            );

            // read file
            struct ModFsFile *file = modFs->files[i] = (struct ModFsFile *) calloc(1, sizeof(struct ModFsFile));
            snprintf(file->filepath, MOD_FS_MAX_PATH, "%s", filepath);
            mod_fs_read_fread_or_fail(modFs, f, &file->size, sizeof(file->size), 1,
                "modPath: %s, filepath: %s - cannot read file size", modFs->modPath, file->filepath
            );
            mod_fs_read_fread_or_fail(modFs, f, &file->isPublic, sizeof(file->isPublic), 1,
                "modPath: %s, filepath: %s - cannot read file public flag", modFs->modPath, file->filepath
            );
            mod_fs_read_fread_or_fail(modFs, f, &file->isText, sizeof(file->isText), 1,
                "modPath: %s, filepath: %s - cannot read file text flag", modFs->modPath, file->filepath
            );
            modFs->totalSize += file->size;
            if (modFs->totalSize > MOD_FS_MAX_SIZE) {
                mod_fs_read_raise_error(modFs, f,
                    "modPath: %s - exceeded total size: %u (max is: %u)", modFs->modPath, modFs->totalSize, MOD_FS_MAX_SIZE
                );
            }
            file->offset = 0;

            // read file data
            file->capacity = file->size;
            file->data.bin = (u8 *) malloc(file->capacity);
            mod_fs_read_fread_or_fail(modFs, f, file->data.bin, 1, file->size,
                "modPath: %s, filepath: %s - cannot read file data", modFs->modPath, file->filepath
            );
        }

        fclose(f);
        return true;
    }
    return false;
}

//
// Write
//

#define mod_fs_write_fwrite_or_fail(f, buf, size, count) { \
    if (fwrite(buf, size, count, f) < count) { \
        fclose(f); \
        return false; \
    } \
}

static bool mod_fs_write(struct ModFs *modFs) {
    FILE *f = mod_fs_get_file_handle(modFs->modPath, "wb");
    if (f) {

        // magic + version
        const u8 version = MOD_FS_VERSION;
        mod_fs_write_fwrite_or_fail(f, MOD_FS_MAGIC, 1, sizeof(MOD_FS_MAGIC) - 1);
        mod_fs_write_fwrite_or_fail(f, &version, sizeof(u8), 1);

        // header
        mod_fs_write_fwrite_or_fail(f, &modFs->numFiles, sizeof(modFs->numFiles), 1);
        mod_fs_write_fwrite_or_fail(f, &modFs->isPublic, sizeof(modFs->isPublic), 1);

        // padding (empty space for future versions)
        const u8 padding[MOD_FS_HEADER_SIZE] = {0};
        u32 paddingLength = MOD_FS_HEADER_SIZE - ftell(f);
        mod_fs_write_fwrite_or_fail(f, padding, 1, paddingLength);

        // files
        for (u16 i = 0; i != modFs->numFiles; ++i) {
            struct ModFsFile *file = modFs->files[i];

            // filepath
            u16 filepathLength = strlen(file->filepath);
            mod_fs_write_fwrite_or_fail(f, &filepathLength, sizeof(filepathLength), 1);
            mod_fs_write_fwrite_or_fail(f, file->filepath, sizeof(char), filepathLength);

            // data
            mod_fs_write_fwrite_or_fail(f, &file->size, sizeof(file->size), 1);
            mod_fs_write_fwrite_or_fail(f, &file->isPublic, sizeof(file->isPublic), 1);
            mod_fs_write_fwrite_or_fail(f, &file->isText, sizeof(file->isText), 1);
            if (file->data.bin) {
                mod_fs_write_fwrite_or_fail(f, file->data.bin, 1, file->size);
            }
        }

        fclose(f);
        return true;
    }
    return false;
}

//
// FS management
//

C_DEFINE bool mod_fs_exists(OPTIONAL const char *modPath) {
    mod_fs_reset_last_error();

    struct ModFs *modFs = mod_fs_get(modPath);
    if (modFs) {
        return true;
    }

    struct ModFs header = {0};
    if (!mod_fs_read(modPath, &header, true)) {
        return false;
    }

    return true;
}

C_DEFINE struct ModFs *mod_fs_get(OPTIONAL const char *modPath) {
    mod_fs_reset_last_error();

    for (auto &item : sModFsList) {

        // active mod fs
        if (!modPath && mod_fs_is_active_mod(item)) {
            return item;
        }

        if (modPath && strcmp(modPath, item->modPath) == 0) {
            return item;
        }
    }

    // try to load it
    struct ModFs temp = {0};
    if (mod_fs_read(modPath, &temp, false)) {
        struct ModFs *modFs = (struct ModFs *) memcpy(malloc(sizeof(struct ModFs)), &temp, sizeof(struct ModFs));
        for (u16 i = 0; i != modFs->numFiles; ++i) {
            modFs->files[i]->modFs = modFs;
        }
        sModFsList.push_back(modFs);
        return modFs;
    }

    return NULL;
}

C_DEFINE struct ModFs *mod_fs_create() {
    mod_fs_reset_last_error();

    struct ModFs *modFs = mod_fs_get(NULL);
    if (!modFs) {
        modFs = mod_fs_new();
        if (!modFs) {
            mod_fs_raise_error(
                "cannot create modfs for the active mod", NULL
            );
            return NULL;
        }

        sModFsList.push_back(modFs);
        return modFs;
    }

    mod_fs_raise_error(
        "a modfs already exists for the active mod; use `mod_fs_get()` instead", NULL
    );
    return NULL;
}

C_DEFINE bool mod_fs_delete() {
    mod_fs_reset_last_error();

    struct ModFs *modFs = mod_fs_get(NULL);
    if (modFs) {
        sModFsList.erase(std::find(sModFsList.begin(), sModFsList.end(), modFs));
        mod_fs_destroy(modFs);
        free(modFs);
        return true;
    }

    mod_fs_raise_error(
        "there is no modfs for the active mod", NULL
    );
    return false;
}

C_DEFINE bool mod_fs_save() {
    mod_fs_reset_last_error();

    struct ModFs *modFs = mod_fs_get(NULL);
    if (modFs) {
        if (!mod_fs_write(modFs)) {
            mod_fs_raise_error(
                "cannot save modfs for the active mod", NULL
            );
            return false;
        }
        return true;
    }

    mod_fs_raise_error(
        "there is no modfs for the active mod; use `mod_fs_create()` to create one", NULL
    );
    return false;
}

C_DEFINE bool mod_fs_set_public(bool pub) {
    mod_fs_reset_last_error();

    struct ModFs *modFs = mod_fs_get(NULL);
    if (modFs) {
        modFs->isPublic = pub;
        return true;
    }

    mod_fs_raise_error(
        "there is no modfs for the active mod; use `mod_fs_create()` to create one", NULL
    );
    return false;
}

//
// File management
//

static int mod_fs_compare_filepaths(const void *l, const void *r) {
    const struct ModFsFile *lfile = (const struct ModFsFile *) l;
    const struct ModFsFile *rfile = (const struct ModFsFile *) r;
    return strcmp(lfile->filepath, rfile->filepath);
}

C_DEFINE const char *mod_fs_get_filename(struct ModFs *modFs, u16 index) {
    return index < modFs->numFiles ? modFs->files[index]->filepath : NULL;
}

C_DEFINE struct ModFsFile *mod_fs_get_file(struct ModFs *modFs, const char *filepath) {
    for (u16 i = 0; i != modFs->numFiles; ++i) {
        struct ModFsFile *file = modFs->files[i];
        if (strcmp(file->filepath, filepath) == 0) {
            if (mod_fs_is_active_mod(modFs) || file->isPublic) {
                return file;
            }
            return NULL;
        }
    }
    return NULL;
}

C_DEFINE struct ModFsFile *mod_fs_create_file(struct ModFs *modFs, const char *filepath, bool text) {
    mod_fs_reset_last_error();

    // cannot create new files in other mods modfs
    if (!mod_fs_is_active_mod(modFs)) {
        mod_fs_raise_error(
            "modPath: %s - creating files in other mods modfs is not allowed", modFs->modPath
        );
        return NULL;
    }

    // check number of files
    if (modFs->numFiles == MOD_FS_MAX_FILES) {
        mod_fs_raise_error(
            "modPath: %s - reached max number of files: %u", modFs->modPath, MOD_FS_MAX_FILES
        );
        return NULL;
    }

    // check filepath
    u32 filepathLength = strlen(filepath);
    if (filepathLength == 0) {
        mod_fs_raise_error(
            "modPath: %s - filepath length cannot be 0", modFs->modPath
        );
        return NULL;
    }
    if (filepathLength > MOD_FS_MAX_PATH - 1) {
        mod_fs_raise_error(
            "modPath: %s - exceeded filepath length: %u (max is: %u)", modFs->modPath, filepathLength, MOD_FS_MAX_PATH - 1
        );
        return NULL;
    }

    // create file
    struct ModFsFile *file = (struct ModFsFile *) malloc(sizeof(struct ModFsFile));
    snprintf(file->filepath, MOD_FS_MAX_PATH, "%s", filepath);
    file->data.bin = NULL;
    file->size = 0;
    file->capacity = 0;
    file->offset = 0;
    file->isText = text;
    file->isPublic = false;
    file->modFs = modFs;

    // add file and sort by filename
    modFs->files = (struct ModFsFile **) realloc(modFs->files, (modFs->numFiles + 1) * sizeof(struct ModFsFile *));
    modFs->files[modFs->numFiles] = file;
    modFs->numFiles++;
    qsort(modFs->files, modFs->numFiles, sizeof(struct ModFsFile *), mod_fs_compare_filepaths);

    return file;
}

C_DEFINE bool mod_fs_move_file(struct ModFs *modFs, const char *oldpath, const char *newpath, bool overwriteExisting) {
    mod_fs_reset_last_error();

    // cannot move files in other mods modfs
    if (!mod_fs_is_active_mod(modFs)) {
        mod_fs_raise_error(
            "modPath: %s - moving files in other mods modfs is not allowed", modFs->modPath
        );
        return false;
    }

    // check new filepath
    u32 newpathLength = strlen(newpath);
    if (newpathLength == 0) {
        mod_fs_raise_error(
            "modPath: %s - filepath length cannot be 0", modFs->modPath
        );
        return false;
    }
    if (newpathLength > MOD_FS_MAX_PATH - 1) {
        mod_fs_raise_error(
            "modPath: %s - exceeded filepath length: %u (max is: %u)", modFs->modPath, newpathLength, MOD_FS_MAX_PATH - 1
        );
        return false;
    }

    // get file
    struct ModFsFile *oldfile = mod_fs_get_file(modFs, oldpath);
    if (!oldfile) {
        mod_fs_raise_error(
            "modPath: %s - file %s doesn't exist", modFs->modPath, oldpath
        );
        return false;
    }

    // if overwriteExisting is not set, check if the newpath points to an existing file
    struct ModFsFile *newfile = mod_fs_get_file(modFs, newpath);
    if (newfile && !overwriteExisting) {
        mod_fs_raise_error(
            "modPath: %s - file %s already exists; set `overwriteExisting` to true to replace this file", modFs->modPath, newpath
        );
        return false;
    }

    // rename file
    if (newfile && !mod_fs_delete_file(modFs, newpath)) {
        return false;
    }
    snprintf(oldfile->filepath, MOD_FS_MAX_PATH, "%s", newpath);
    return true;
}

C_DEFINE bool mod_fs_copy_file(struct ModFs *modFs, const char *srcpath, const char *dstpath, bool overwriteExisting) {
    mod_fs_reset_last_error();

    // cannot copy files in other mods modfs
    if (!mod_fs_is_active_mod(modFs)) {
        mod_fs_raise_error(
            "modPath: %s - copying files in other mods modfs is not allowed", modFs->modPath
        );
        return false;
    }

    // check dest filepath
    u32 dstpathLength = strlen(dstpath);
    if (dstpathLength == 0) {
        mod_fs_raise_error(
            "modPath: %s - filepath length cannot be 0", modFs->modPath
        );
        return false;
    }
    if (dstpathLength > MOD_FS_MAX_PATH - 1) {
        mod_fs_raise_error(
            "modPath: %s - exceeded filepath length: %u (max is: %u)", modFs->modPath, dstpathLength, MOD_FS_MAX_PATH - 1
        );
        return false;
    }

    // get file
    struct ModFsFile *srcfile = mod_fs_get_file(modFs, srcpath);
    if (!srcfile) {
        mod_fs_raise_error(
            "modPath: %s - file %s doesn't exist", modFs->modPath, srcpath
        );
        return false;
    }

    // if overwriteExisting is not set, check if the newpath points to an existing file
    struct ModFsFile *dstfile = mod_fs_get_file(modFs, dstpath);
    if (dstfile && !overwriteExisting) {
        mod_fs_raise_error(
            "modPath: %s - file %s already exists; set `overwriteExisting` to true to replace this file", modFs->modPath, dstpath
        );
        return false;
    }

    // compute new total size
    u32 newTotalSize = modFs->totalSize + srcfile->size;
    if (dstfile) {
        newTotalSize -= dstfile->size;
    }
    if (newTotalSize > MOD_FS_MAX_SIZE) {
        mod_fs_raise_error(
            "modPath: %s - cannot copy file %s: exceeding total size: %u (max is: %u)", modFs->modPath, srcpath, newTotalSize, MOD_FS_MAX_SIZE
        );
        return false;
    }
    modFs->totalSize = newTotalSize;

    // copy file
    if (dstfile) {
        free(dstfile->data.bin);
    } else {
        dstfile = mod_fs_create_file(modFs, dstpath, srcfile->isText);
        if (!dstfile) {
            return false;
        }
    }
    memcpy(dstfile, srcfile, sizeof(struct ModFsFile));
    snprintf(dstfile->filepath, MOD_FS_MAX_PATH, "%s", dstpath);
    dstfile->data.bin = (u8 *) memcpy(malloc(srcfile->capacity), srcfile->data.bin, srcfile->size);
    dstfile->offset = 0;
    return true;
}

C_DEFINE bool mod_fs_delete_file(struct ModFs *modFs, const char *filepath) {
    mod_fs_reset_last_error();

    // cannot delete files in other mods modfs
    if (!mod_fs_is_active_mod(modFs)) {
        mod_fs_raise_error(
            "modPath: %s - deleting files in other mods modfs is not allowed", modFs->modPath
        );
        return false;
    }

    // get file
    for (u16 i = 0; i != modFs->numFiles; ++i) {
        struct ModFsFile *file = modFs->files[i];
        if (strcmp(file->filepath, filepath) == 0) {

            // delete file
            modFs->totalSize -= file->size;
            mod_fs_file_destroy(file);
            free(file);

            // remove file from list
            memmove(modFs->files + i, modFs->files + (i + 1), (modFs->numFiles - i - 1) * sizeof(struct ModFsFile *));
            modFs->numFiles--;
            return true;
        }
    }

    mod_fs_raise_error(
        "modPath: %s - file %s doesn't exist", modFs->modPath, filepath
    );
    return false;
}

C_DEFINE bool mod_fs_clear(struct ModFs *modFs) {
    mod_fs_reset_last_error();

    // cannot delete files in other mods modfs
    if (!mod_fs_is_active_mod(modFs)) {
        mod_fs_raise_error(
            "modPath: %s - deleting files in other mods modfs is not allowed", modFs->modPath
        );
        return false;
    }

    // delete all files
    for (u16 i = 0; i != modFs->numFiles; ++i) {
        struct ModFsFile *file = modFs->files[i];
        mod_fs_file_destroy(file);
        free(file);
    }
    free(modFs->files);
    modFs->files = NULL;
    modFs->numFiles = 0;
    modFs->totalSize = 0;
    return true;
}

//
// Read data
//

static bool mod_fs_file_read_check_eof(struct ModFsFile *file, u32 size) {
    if (file->offset + size > file->size) {
        file->offset = file->size;
        return true;
    }
    return false;
}

template <typename T>
static T mod_fs_file_read_data(struct ModFsFile *file, T defaultValue) {
    if (mod_fs_file_read_check_eof(file, sizeof(T))) {
        return defaultValue;
    }
    T value;
    memcpy(&value, file->data.bin + file->offset, sizeof(T));
    file->offset += sizeof(T);
    return value;
}

C_DEFINE bool mod_fs_file_read_bool(struct ModFsFile *file) {
    mod_fs_reset_last_error();

    // binary only
    if (file->isText) {
        mod_fs_raise_error(
            "modPath: %s, filepath: %s - cannot read bool from a text file", file->modFs->modPath, file->filepath
        );
        return false;
    }

    return mod_fs_file_read_data<bool>(file, false);
}

C_DEFINE lua_Integer mod_fs_file_read_integer(struct ModFsFile *file, enum ModFsFileIntType intType) {
    mod_fs_reset_last_error();

    // binary only
    if (file->isText) {
        mod_fs_raise_error(
            "modPath: %s, filepath: %s - cannot read integer from a text file", file->modFs->modPath, file->filepath
        );
        return 0;
    }

    // check intType
    if (intType >= INT_TYPE_MAX) {
        mod_fs_raise_error(
            "modPath: %s, filepath: %s - invalid intType: %u", file->modFs->modPath, file->filepath, intType
        );
        return 0;
    }

    switch (intType) {
        case INT_TYPE_U8:  return mod_fs_file_read_data<u8>(file, 0);
        case INT_TYPE_U16: return mod_fs_file_read_data<u16>(file, 0);
        case INT_TYPE_U32: return mod_fs_file_read_data<u32>(file, 0);
        case INT_TYPE_U64: return mod_fs_file_read_data<u64>(file, 0);
        case INT_TYPE_S8:  return mod_fs_file_read_data<s8>(file, 0);
        case INT_TYPE_S16: return mod_fs_file_read_data<s16>(file, 0);
        case INT_TYPE_S32: return mod_fs_file_read_data<s32>(file, 0);
        case INT_TYPE_S64: return mod_fs_file_read_data<s64>(file, 0);
    }
    return 0;
}

C_DEFINE lua_Number mod_fs_file_read_number(struct ModFsFile *file, enum ModFsFileFloatType floatType) {
    mod_fs_reset_last_error();

    // binary only
    if (file->isText) {
        mod_fs_raise_error(
            "modPath: %s, filepath: %s - cannot read number from a text file", file->modFs->modPath, file->filepath
        );
        return 0;
    }

    // check floatType
    if (floatType >= FLOAT_TYPE_MAX) {
        mod_fs_raise_error(
            "modPath: %s, filepath: %s - invalid floatType: %u", file->modFs->modPath, file->filepath, floatType
        );
        return 0;
    }

    switch (floatType) {
        case FLOAT_TYPE_F32: return mod_fs_file_read_data<f32>(file, 0);
        case FLOAT_TYPE_F64: return mod_fs_file_read_data<f64>(file, 0);
    }
    return 0;
}

C_DEFINE const char *mod_fs_file_read_string(struct ModFsFile *file) {
    mod_fs_reset_last_error();

    memset(sModFsFileReadStringBuf, 0, sizeof(sModFsFileReadStringBuf));
    mod_fs_file_read_check_eof(file, 0);

    // for text files, returns the whole content from offset
    if (file->isText) {
        memcpy(sModFsFileReadStringBuf, file->data.text + file->offset, file->size - file->offset);
        file->offset = file->size;
        return sModFsFileReadStringBuf;
    }

    // for binary, stops at the first NULL char or at the end of the file
    char *buf = sModFsFileReadStringBuf;
    for (char *c = (char *) (file->data.bin + file->offset); *c && file->offset < file->size; c++, file->offset++, buf++) {
        *buf = *c;
    }
    *buf = 0;
    return sModFsFileReadStringBuf;
}

C_DEFINE const char *mod_fs_file_read_line(struct ModFsFile *file) {
    mod_fs_reset_last_error();

    memset(sModFsFileReadStringBuf, 0, sizeof(sModFsFileReadStringBuf));
    mod_fs_file_read_check_eof(file, 0);

    // text only
    if (!file->isText) {
        mod_fs_raise_error(
            "modPath: %s, filepath: %s - cannot read line from binary file", file->modFs->modPath, file->filepath
        );
        return sModFsFileReadStringBuf;
    }

    char *buf = sModFsFileReadStringBuf;
    for (char *c = file->data.text + file->offset; *c != '\n' && file->offset < file->size; c++, file->offset++, buf++) {
        *buf = *c;
    }
    *buf = 0;
    file->offset = MIN(file->offset + 1, file->size);
    return sModFsFileReadStringBuf;
}

//
// Write data
//

static bool mod_fs_file_write_resize_buffer(struct ModFsFile *file, u32 size) {

    // compute and check new sizes
    file->offset = MIN(file->offset, file->size);
    u32 newFileSize = MAX(file->offset + size, file->size);
    u32 newTotalSize = file->modFs->totalSize + (newFileSize - file->size);
    if (newTotalSize > MOD_FS_MAX_SIZE) {
        mod_fs_raise_error(
            "modPath: %s, filepath: %s - cannot write to file: exceeding total size: %u (max is: %u)", file->modFs->modPath, file->filepath, newTotalSize, MOD_FS_MAX_SIZE
        );
        return false;
    }
    file->size = newFileSize;
    file->modFs->totalSize = newTotalSize;

    // resize data buffer
    if (file->offset + size > file->capacity) {
        u32 newCapacity = MAX(file->capacity * 2, 32);
        file->data.bin = (u8 *) realloc(file->data.bin, newCapacity);
        file->capacity = newCapacity;
    }
    return true;
}

template <typename T>
static bool mod_fs_file_write_data(struct ModFsFile *file, T value) {
    if (mod_fs_file_write_resize_buffer(file, sizeof(T))) {
        memcpy(file->data.bin + file->offset, &value, sizeof(T));
        file->offset += sizeof(T);
        return true;
    }
    return false;
}

C_DEFINE bool mod_fs_file_write_bool(struct ModFsFile *file, bool value) {
    mod_fs_reset_last_error();

    // cannot write to files in other mods modfs
    if (!mod_fs_is_active_mod(file->modFs)) {
        mod_fs_raise_error(
            "modPath: %s, filepath: %s - writing to files in other mods modfs is not allowed", file->modFs->modPath, file->filepath
        );
        return false;
    }

    // binary only
    if (file->isText) {
        mod_fs_raise_error(
            "modPath: %s, filepath: %s - cannot write bool to a text file", file->modFs->modPath, file->filepath
        );
        return false;
    }

    return mod_fs_file_write_data<bool>(file, value);
}

C_DEFINE bool mod_fs_file_write_integer(struct ModFsFile *file, lua_Integer value, enum ModFsFileIntType intType) {
    mod_fs_reset_last_error();

    // cannot write to files in other mods modfs
    if (!mod_fs_is_active_mod(file->modFs)) {
        mod_fs_raise_error(
            "modPath: %s, filepath: %s - writing to files in other mods modfs is not allowed", file->modFs->modPath, file->filepath
        );
        return false;
    }

    // binary only
    if (file->isText) {
        mod_fs_raise_error(
            "modPath: %s, filepath: %s - cannot write integer to a text file", file->modFs->modPath, file->filepath
        );
        return false;
    }

    // check intType
    if (intType >= INT_TYPE_MAX) {
        mod_fs_raise_error(
            "modPath: %s, filepath: %s - invalid intType: %u", file->modFs->modPath, file->filepath, intType
        );
        return false;
    }

    switch (intType) {
        case INT_TYPE_U8:  return mod_fs_file_write_data<u8>(file, value);
        case INT_TYPE_U16: return mod_fs_file_write_data<u16>(file, value);
        case INT_TYPE_U32: return mod_fs_file_write_data<u32>(file, value);
        case INT_TYPE_U64: return mod_fs_file_write_data<u64>(file, value);
        case INT_TYPE_S8:  return mod_fs_file_write_data<s8>(file, value);
        case INT_TYPE_S16: return mod_fs_file_write_data<s16>(file, value);
        case INT_TYPE_S32: return mod_fs_file_write_data<s32>(file, value);
        case INT_TYPE_S64: return mod_fs_file_write_data<s64>(file, value);
    }
    return false;
}

C_DEFINE bool mod_fs_file_write_number(struct ModFsFile *file, lua_Number value, enum ModFsFileFloatType floatType) {
    mod_fs_reset_last_error();

    // cannot write to files in other mods modfs
    if (!mod_fs_is_active_mod(file->modFs)) {
        mod_fs_raise_error(
            "modPath: %s, filepath: %s - writing to files in other mods modfs is not allowed", file->modFs->modPath, file->filepath
        );
        return false;
    }

    // binary only
    if (file->isText) {
        mod_fs_raise_error(
            "modPath: %s, filepath: %s - cannot write number to a text file", file->modFs->modPath, file->filepath
        );
        return false;
    }

    // check floatType
    if (floatType >= FLOAT_TYPE_MAX) {
        mod_fs_raise_error(
            "modPath: %s, filepath: %s - invalid floatType: %u", file->modFs->modPath, file->filepath, floatType
        );
        return false;
    }

    switch (floatType) {
        case FLOAT_TYPE_F32: return mod_fs_file_write_data<f32>(file, value);
        case FLOAT_TYPE_F64: return mod_fs_file_write_data<f64>(file, value);
    }
    return false;
}

C_DEFINE bool mod_fs_file_write_string(struct ModFsFile *file, const char *str) {
    mod_fs_reset_last_error();

    // cannot write to files in other mods modfs
    if (!mod_fs_is_active_mod(file->modFs)) {
        mod_fs_raise_error(
            "modPath: %s, filepath: %s - writing to files in other mods modfs is not allowed", file->modFs->modPath, file->filepath
        );
        return false;
    }

    u32 length = strlen(str) + (file->isText ? 0 : 1); // binary writes the NULL char
    if (mod_fs_file_write_resize_buffer(file, length)) {
        memcpy(file->data.bin + file->offset, str, length);
        file->offset += length;
        return true;
    }
    return false;
}

C_DEFINE bool mod_fs_file_write_line(struct ModFsFile *file, const char *str) {
    mod_fs_reset_last_error();

    // cannot write to files in other mods modfs
    if (!mod_fs_is_active_mod(file->modFs)) {
        mod_fs_raise_error(
            "modPath: %s, filepath: %s - writing to files in other mods modfs is not allowed", file->modFs->modPath, file->filepath
        );
        return false;
    }

    // text only
    if (!file->isText) {
        mod_fs_raise_error(
            "modPath: %s, filepath: %s - cannot write line to binary file", file->modFs->modPath, file->filepath
        );
        return false;
    }

    u32 length = strlen(str);
    if (mod_fs_file_write_resize_buffer(file, length + 1)) { // '\n'
        memcpy(file->data.text + file->offset, str, length);
        file->offset += length;
        file->data.text[file->offset++] = '\n';
        return true;
    }
    return false;
}

//
// File misc
//

C_DEFINE bool mod_fs_file_seek(struct ModFsFile *file, s32 offset, enum ModFsFileSeek origin) {
    mod_fs_reset_last_error();

    // check origin
    if (origin >= FILE_SEEK_MAX) {
        mod_fs_raise_error(
            "modPath: %s, filepath: %s - invalid origin: %u", file->modFs->modPath, file->filepath, origin
        );
        return false;
    }

    s32 start = 0;
    switch (origin) {
        case FILE_SEEK_SET: start = 0; break;
        case FILE_SEEK_CUR: start = file->offset; break;
        case FILE_SEEK_END: start = file->size; break;
    }
    file->offset = MIN(MAX(start + offset, 0), (s32) file->size);
    return true;
}

C_DEFINE bool mod_fs_file_is_eof(struct ModFsFile *file) {
    return file->offset >= file->size;
}

C_DEFINE bool mod_fs_file_erase(struct ModFsFile *file, u32 length) {
    mod_fs_reset_last_error();

    // cannot erase data from files in other mods modfs
    if (!mod_fs_is_active_mod(file->modFs)) {
        mod_fs_raise_error(
            "modPath: %s, filepath: %s - erasing data from files in other mods modfs is not allowed", file->modFs->modPath, file->filepath
        );
        return false;
    }

    length = MIN(length, file->size - file->offset);
    memmove(file->data.bin + file->offset, file->data.bin + file->offset + length, file->size - (file->offset + length));
    file->size -= length;
    file->modFs->totalSize -= length;
    return true;
}

C_DEFINE bool mod_fs_file_set_public(struct ModFsFile *file, bool pub) {
    mod_fs_reset_last_error();

    // cannot change public flag to files in other mods modfs
    if (!mod_fs_is_active_mod(file->modFs)) {
        mod_fs_raise_error(
            "modPath: %s, filepath: %s - changing public flag of files in other mods modfs is not allowed", file->modFs->modPath, file->filepath
        );
        return false;
    }

    file->isPublic = pub;
    return true;
}

//
// Errors
//

void mod_fs_hide_errors(bool hide) {
    sModFsHideErrors = hide;
}

const char *mod_fs_get_last_error() {
    return sModFsLastError;
}
