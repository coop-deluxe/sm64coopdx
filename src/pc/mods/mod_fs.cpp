extern "C" {
#include "mod_fs.h"
#include "src/pc/fs/fs.h"
#include "src/pc/mods/mods_utils.h"
}
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>

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
static char sModFsErrorFunction[256];

#define mod_fs_reset_last_error() { \
    memset(sModFsLastError, 0, sizeof(sModFsLastError)); \
    snprintf(sModFsErrorFunction, sizeof(sModFsErrorFunction), "%s", __FUNCTION__); \
}

#define mod_fs_raise_error(fmt, ...) { \
    snprintf(sModFsLastError, sizeof(sModFsLastError), "%s: " fmt, sModFsErrorFunction, __VA_ARGS__); \
    if (!sModFsHideErrors) { \
        LOG_LUA_LINE("%s", sModFsLastError); \
    } \
}

//
// Pointers
//

// Pointers to ModFs and ModFsFile must be referenced and checked
// to avoid mods keeping and accessing dangling pointers

template <typename T>
static std::set<T *> &mod_fs_get_pointers() {
    static std::set<T *> sPointers = {};
    return sPointers;
}

template <typename T>
static bool mod_fs_is_valid_pointer(T *ptr) {
    std::set<T *> &pointers = mod_fs_get_pointers<T>();
    return pointers.find(ptr) != pointers.end();
}

template <typename T>
static T *mod_fs_alloc() {
    T *ptr = (T *) calloc(1, sizeof(T));
    if (ptr) {
        std::set<T *> &pointers = mod_fs_get_pointers<T>();
        pointers.insert(ptr);
    }
    return ptr;
}

template <typename T>
static bool mod_fs_free(T *ptr) {
    if (mod_fs_is_valid_pointer(ptr)) {
        std::set<T *> &pointers = mod_fs_get_pointers<T>();
        pointers.erase(ptr);
        free(ptr);
        return true;
    }
    return false;
}

//
// Utils
//

static bool mod_fs_is_active_mod(struct ModFs *modFs) {
    return gLuaActiveMod != NULL && modFs->mod == gLuaActiveMod;
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

static bool mod_fs_get_physical_filename(const char *modPath, char *dest) {
    char realModPath[SYS_MAX_PATH];
    if (mod_fs_get_modpath(modPath, realModPath)) {
        const char *path = fs_get_write_path(MOD_FS_DIRECTORY);
        snprintf(dest, SYS_MAX_PATH, "%s/%s" MOD_FS_EXTENSION, path, realModPath);
        normalize_path(dest);
        return true;
    }
    return false;
}

static FILE *mod_fs_get_file_handle(const char *modPath, const char *mode) {
    char filename[SYS_MAX_PATH];
    if (mod_fs_get_physical_filename(modPath, filename)) {
        return fopen(filename, mode);
    }
    return NULL;
}

//
// ctor, dtor
//

static struct ModFs *mod_fs_new() {
    if (gLuaActiveMod) {
        struct ModFs *modFs = mod_fs_alloc<struct ModFs>();
        if (!modFs) {
            mod_fs_raise_error(
                "failed to allocate modfs object", NULL
            );
            return NULL;
        }
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
    if (file) {
        free(file->data.bin);
        memset(file, 0, sizeof(struct ModFsFile));
    }
}

static void mod_fs_destroy(struct ModFs *modFs) {
    for (u16 i = 0; modFs->files && i != modFs->numFiles; ++i) {
        mod_fs_file_destroy(modFs->files[i]);
        mod_fs_free<struct ModFsFile>(modFs->files[i]);
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
        if (!mod_fs_is_active_mod(modFs) && !modFs->isPublic) {
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
            if (!modFs->files) {
                mod_fs_read_raise_error(modFs, f,
                    "modPath: %s - failed to allocate buffer for modfs files", modFs->modPath
                );
            }
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
            char filepath[MOD_FS_MAX_PATH] = {0};
            mod_fs_read_fread_or_fail(modFs, f, filepath, sizeof(char), filepathLength,
                "modPath: %s - cannot read filepath", modFs->modPath
            );

            // read file header
            struct ModFsFile fileHeader = {0};
            mod_fs_read_fread_or_fail(modFs, f, &fileHeader.size, sizeof(fileHeader.size), 1,
                "modPath: %s, filepath: %s - cannot read file size", modFs->modPath, filepath
            );
            mod_fs_read_fread_or_fail(modFs, f, &fileHeader.isPublic, sizeof(fileHeader.isPublic), 1,
                "modPath: %s, filepath: %s - cannot read file public flag", modFs->modPath, filepath
            );
            mod_fs_read_fread_or_fail(modFs, f, &fileHeader.isText, sizeof(fileHeader.isText), 1,
                "modPath: %s, filepath: %s - cannot read file text flag", modFs->modPath, filepath
            );

            // don't create file if it's private
            if (!mod_fs_is_active_mod(modFs) && !fileHeader.isPublic) {
                modFs->numFiles--;
                i--;
                fseek(f, fileHeader.size, SEEK_CUR);
                continue;
            }

            // create file
            struct ModFsFile *file = modFs->files[i] = mod_fs_alloc<struct ModFsFile>();
            if (!file) {
                mod_fs_read_raise_error(modFs, f,
                    "modPath: %s, filepath: %s - failed to allocate modfs file object", modFs->modPath, file->filepath
                );
            }
            memcpy(file, &fileHeader, sizeof(struct ModFsFile));
            snprintf(file->filepath, MOD_FS_MAX_PATH, "%s", filepath);
            modFs->totalSize += file->size;
            if (modFs->totalSize > MOD_FS_MAX_SIZE) {
                mod_fs_read_raise_error(modFs, f,
                    "modPath: %s - exceeded total size: %u (max is: %u)", modFs->modPath, modFs->totalSize, MOD_FS_MAX_SIZE
                );
            }
            file->offset = 0;

            // read file data
            file->capacity = file->size;
            if (file->size > 0) {
                file->data.bin = (u8 *) malloc(file->capacity);
                if (!file->data.bin) {
                    mod_fs_read_raise_error(modFs, f,
                        "modPath: %s, filepath: %s - failed to allocate buffer for modfs file data", modFs->modPath, file->filepath
                    );
                }
                mod_fs_read_fread_or_fail(modFs, f, file->data.bin, 1, file->size,
                    "modPath: %s, filepath: %s - cannot read file data", modFs->modPath, file->filepath
                );
            }
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
// Common checks
//

template <typename T>
static bool mod_fs_check_pointer(T *ptr, const char *typeName) {
    if (!mod_fs_is_valid_pointer(ptr)) {
        mod_fs_raise_error(
            "pointer is not a valid %s object", typeName
        );
        return false;
    }
    return true;
}

static bool mod_fs_check_write(struct ModFs *modFs, const char *action) {
    if (!mod_fs_is_active_mod(modFs)) {
        mod_fs_raise_error(
            "modPath: %s - %s files in other mods modfs is not allowed", modFs->modPath, action
        );
        return false;
    }
    return true;
}

static bool mod_fs_file_check_write(struct ModFsFile *file) {
    if (!mod_fs_is_active_mod(file->modFs)) {
        mod_fs_raise_error(
            "modPath: %s, filepath: %s - writing to files in other mods modfs is not allowed", file->modFs->modPath, file->filepath
        );
        return false;
    }
    return true;
}

static bool mod_fs_check_filepath_length(struct ModFs *modFs, u32 filepathLength) {
    if (filepathLength == 0) {
        mod_fs_raise_error(
            "modPath: %s - filepath length cannot be 0", modFs->modPath
        );
        return false;
    }
    if (filepathLength > MOD_FS_MAX_PATH - 1) {
        mod_fs_raise_error(
            "modPath: %s - exceeded filepath length: %u (max is: %u)", modFs->modPath, filepathLength, MOD_FS_MAX_PATH - 1
        );
        return false;
    }
    return true;
}

static bool mod_fs_file_check_file_type(struct ModFsFile *file, bool isText, bool write, const char *dataName) {
    if (file->isText != isText) {
        mod_fs_raise_error(
            "modPath: %s, filepath: %s - cannot %s %s %s a %s file", file->modFs->modPath, file->filepath,
            (write ? "write" : "read"),
            dataName,
            (write ? "to" : "from"),
            (file->isText ? "text" : "binary")
        );
        return false;
    }
    return true;
}

static bool mod_fs_file_check_parameter(struct ModFsFile *file, u8 parameter, u8 parameterMax, const char *parameterName) {
    if (parameter >= parameterMax) {
        mod_fs_raise_error(
            "modPath: %s, filepath: %s - invalid %s: %u", file->modFs->modPath, file->filepath,
            parameterName,
            parameter
        );
        return false;
    }
    return true;
}






//
// FS management
//

static struct ModFs *mod_fs_get_or_load(const char *modPath, bool loadIfNotFound) {
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
    if (loadIfNotFound) {
        struct ModFs temp = {0};
        if (mod_fs_read(modPath, &temp, false)) {
            struct ModFs *modFs = mod_fs_alloc<struct ModFs>();
            if (!modFs) {
                mod_fs_raise_error(
                    "failed to allocate modfs object", NULL
                );
                return NULL;
            }
            memcpy(modFs, &temp, sizeof(struct ModFs));
            for (u16 i = 0; i != modFs->numFiles; ++i) {
                modFs->files[i]->modFs = modFs;
            }
            sModFsList.push_back(modFs);
            return modFs;
        }
    }

    return NULL;
}

C_DEFINE bool mod_fs_exists(OPTIONAL const char *modPath) {
    mod_fs_reset_last_error();

    struct ModFs *modFs = mod_fs_get_or_load(modPath, false);
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

    return mod_fs_get_or_load(modPath, true);
}

C_DEFINE struct ModFs *mod_fs_reload(OPTIONAL const char *modPath) {
    mod_fs_reset_last_error();

    // remove modfs object if already loaded
    struct ModFs *modFs = mod_fs_get_or_load(modPath, false);
    if (modFs) {
        sModFsList.erase(std::find(sModFsList.begin(), sModFsList.end(), modFs));
        mod_fs_destroy(modFs);
        mod_fs_free<struct ModFs>(modFs);
    }

    // reload
    return mod_fs_get_or_load(modPath, true);
}

C_DEFINE struct ModFs *mod_fs_create() {
    mod_fs_reset_last_error();

    struct ModFs *modFs = mod_fs_get_or_load(NULL, false);
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

    struct ModFs *modFs = mod_fs_get_or_load(NULL, true);
    if (modFs) {
        char filename[SYS_MAX_PATH];
        if (mod_fs_get_physical_filename(modFs->modPath, filename) && fs_sys_file_exists(filename)) {
            remove(filename);
        }

        sModFsList.erase(std::find(sModFsList.begin(), sModFsList.end(), modFs));
        mod_fs_destroy(modFs);
        mod_fs_free<struct ModFs>(modFs);
        return true;
    }

    mod_fs_raise_error(
        "there is no modfs for the active mod", NULL
    );
    return false;
}

C_DEFINE bool mod_fs_save() {
    mod_fs_reset_last_error();

    struct ModFs *modFs = mod_fs_get_or_load(NULL, true);
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

    struct ModFs *modFs = mod_fs_get_or_load(NULL, true);
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
    mod_fs_reset_last_error();

    if (!mod_fs_check_pointer(modFs, "modfs")) {
        return NULL;
    }

    if (index >= modFs->numFiles) {
        mod_fs_raise_error(
            "modPath: %s - file index out of bounds: %u (num files: %u)", modFs->modPath, index, modFs->numFiles
        );
        return NULL;
    }

    return modFs->files[index]->filepath;
}

C_DEFINE struct ModFsFile *mod_fs_get_file(struct ModFs *modFs, const char *filepath) {
    mod_fs_reset_last_error();

    if (!mod_fs_check_pointer(modFs, "modfs")) {
        return NULL;
    }

    for (u16 i = 0; i != modFs->numFiles; ++i) {
        struct ModFsFile *file = modFs->files[i];
        if (strcmp(file->filepath, filepath) == 0) {
            return file;
        }
    }
    return NULL;
}

C_DEFINE struct ModFsFile *mod_fs_create_file(struct ModFs *modFs, const char *filepath, bool text) {
    mod_fs_reset_last_error();

    if (!mod_fs_check_pointer(modFs, "modfs")) {
        return NULL;
    }

    // cannot create new files in other mods modfs
    if (!mod_fs_check_write(modFs, "creating")) {
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
    if (!mod_fs_check_filepath_length(modFs, filepathLength)) {
        return NULL;
    }

    // create file
    struct ModFsFile *file = mod_fs_alloc<struct ModFsFile>();
    if (!file) {
        mod_fs_raise_error(
            "modPath: %s, filepath: %s - failed to allocate modfs file object", modFs->modPath, filepath
        );
        return NULL;
    }
    snprintf(file->filepath, MOD_FS_MAX_PATH, "%s", filepath);
    file->data.bin = NULL;
    file->size = 0;
    file->capacity = 0;
    file->offset = 0;
    file->isText = text;
    file->isPublic = false;
    file->modFs = modFs;

    // add file and sort by filename
    struct ModFsFile **files = (struct ModFsFile **) realloc(modFs->files, (modFs->numFiles + 1) * sizeof(struct ModFsFile *));
    if (!files) {
        mod_fs_raise_error(
            "modPath: %s, filepath: %s - failed to reallocate buffer of modfs files", modFs->modPath, filepath
        );
        mod_fs_free<struct ModFsFile>(file);
        return NULL;
    }
    modFs->files = files;
    modFs->files[modFs->numFiles] = file;
    modFs->numFiles++;
    qsort(modFs->files, modFs->numFiles, sizeof(struct ModFsFile *), mod_fs_compare_filepaths);

    return file;
}

C_DEFINE bool mod_fs_move_file(struct ModFs *modFs, const char *oldpath, const char *newpath, bool overwriteExisting) {
    mod_fs_reset_last_error();

    if (!mod_fs_check_pointer(modFs, "modfs")) {
        return false;
    }

    // cannot move files in other mods modfs
    if (!mod_fs_check_write(modFs, "moving")) {
        return false;
    }

    // check new filepath
    u32 newpathLength = strlen(newpath);
    if (!mod_fs_check_filepath_length(modFs, newpathLength)) {
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

    if (!mod_fs_check_pointer(modFs, "modfs")) {
        return false;
    }

    // cannot copy files in other mods modfs
    if (!mod_fs_check_write(modFs, "copying")) {
        return false;
    }

    // check dest filepath
    u32 dstpathLength = strlen(dstpath);
    if (!mod_fs_check_filepath_length(modFs, dstpathLength)) {
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
    u8 *buffer = (u8 *) malloc(srcfile->capacity);
    if (!buffer) {
        mod_fs_raise_error(
            "modPath: %s, filepath: %s - failed to allocate buffer for modfs file data", modFs->modPath, dstfile->filepath
        );
        return false;
    }
    if (dstfile) {
        free(dstfile->data.bin);
    } else {
        dstfile = mod_fs_create_file(modFs, dstpath, srcfile->isText);
        if (!dstfile) {
            free(buffer);
            return false;
        }
    }
    memcpy(dstfile, srcfile, sizeof(struct ModFsFile));
    snprintf(dstfile->filepath, MOD_FS_MAX_PATH, "%s", dstpath);
    memcpy(buffer, srcfile->data.bin, srcfile->size);
    dstfile->data.bin = buffer;
    dstfile->offset = 0;
    return true;
}

C_DEFINE bool mod_fs_delete_file(struct ModFs *modFs, const char *filepath) {
    mod_fs_reset_last_error();

    if (!mod_fs_check_pointer(modFs, "modfs")) {
        return false;
    }

    // cannot delete files in other mods modfs
    if (!mod_fs_check_write(modFs, "deleting")) {
        return false;
    }

    // get file
    for (u16 i = 0; i != modFs->numFiles; ++i) {
        struct ModFsFile *file = modFs->files[i];
        if (strcmp(file->filepath, filepath) == 0) {

            // delete file
            modFs->totalSize -= file->size;
            mod_fs_file_destroy(file);
            mod_fs_free<struct ModFsFile>(file);

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

    if (!mod_fs_check_pointer(modFs, "modfs")) {
        return false;
    }

    // cannot delete files in other mods modfs
    if (!mod_fs_check_write(modFs, "deleting")) {
        return false;
    }

    // delete all files
    for (u16 i = 0; i != modFs->numFiles; ++i) {
        struct ModFsFile *file = modFs->files[i];
        mod_fs_file_destroy(file);
        mod_fs_free<struct ModFsFile>(file);
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
        mod_fs_raise_error(
            "modPath: %s, filepath: %s - reached end of file", file->modFs->modPath, file->filepath
        );
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

    if (!mod_fs_check_pointer(file, "modfs file")) {
        return false;
    }

    // binary only
    if (!mod_fs_file_check_file_type(file, false, false, "bool")) {
        return false;
    }

    return mod_fs_file_read_data<bool>(file, false);
}

C_DEFINE lua_Integer mod_fs_file_read_integer(struct ModFsFile *file, enum ModFsFileIntType intType) {
    mod_fs_reset_last_error();

    if (!mod_fs_check_pointer(file, "modfs file")) {
        return 0;
    }

    // binary only
    if (!mod_fs_file_check_file_type(file, false, false, "integer")) {
        return 0;
    }

    // check intType
    if (!mod_fs_file_check_parameter(file, intType, INT_TYPE_MAX, "intType")) {
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
        default:           return 0;
    }
}

C_DEFINE lua_Number mod_fs_file_read_number(struct ModFsFile *file, enum ModFsFileFloatType floatType) {
    mod_fs_reset_last_error();

    if (!mod_fs_check_pointer(file, "modfs file")) {
        return 0;
    }

    // binary only
    if (!mod_fs_file_check_file_type(file, false, false, "number")) {
        return 0;
    }

    // check intType
    if (!mod_fs_file_check_parameter(file, floatType, FLOAT_TYPE_MAX, "floatType")) {
        return 0;
    }

    switch (floatType) {
        case FLOAT_TYPE_F32: return mod_fs_file_read_data<f32>(file, 0);
        case FLOAT_TYPE_F64: return mod_fs_file_read_data<f64>(file, 0);
        default:             return 0;
    }
}

C_DEFINE ByteString mod_fs_file_read_bytes(struct ModFsFile *file, u32 length) {
    mod_fs_reset_last_error();
    ByteString bytestring = { NULL, 0 };

    if (!mod_fs_check_pointer(file, "modfs file")) {
        return bytestring;
    }

    // binary only
    if (!mod_fs_file_check_file_type(file, false, false, "bytes")) {
        return bytestring;
    }

    // check eof
    if (mod_fs_file_read_check_eof(file, length)) {
        return bytestring;
    }

    bytestring.bytes = (const char *) (file->data.bin + file->offset);
    bytestring.length = length;
    file->offset += length;
    return bytestring;
}

C_DEFINE const char *mod_fs_file_read_string(struct ModFsFile *file) {
    mod_fs_reset_last_error();

    if (!mod_fs_check_pointer(file, "modfs file")) {
        return NULL;
    }

    memset(sModFsFileReadStringBuf, 0, sizeof(sModFsFileReadStringBuf));
    if (mod_fs_file_read_check_eof(file, 1)) {
        return NULL;
    }

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
    file->offset = MIN(file->offset + 1, file->size);
    return sModFsFileReadStringBuf;
}

C_DEFINE const char *mod_fs_file_read_line(struct ModFsFile *file) {
    mod_fs_reset_last_error();

    if (!mod_fs_check_pointer(file, "modfs file")) {
        return NULL;
    }

    // text only
    if (!mod_fs_file_check_file_type(file, true, false, "line")) {
        return 0;
    }

    memset(sModFsFileReadStringBuf, 0, sizeof(sModFsFileReadStringBuf));
    if (mod_fs_file_read_check_eof(file, 1)) {
        return NULL;
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

    // resize data buffer
    if (file->offset + size > file->capacity) {
        u32 newCapacity = MAX(file->capacity * 2, 32);
        u8 *buffer = (u8 *) realloc(file->data.bin, newCapacity);
        if (!buffer) {
            mod_fs_raise_error(
                "modPath: %s, filepath: %s - failed to reallocate buffer of modfs file data", file->modFs->modPath, file->filepath
            );
            return false;
        }
        file->data.bin = buffer;
        file->capacity = newCapacity;
    }
    file->size = newFileSize;
    file->modFs->totalSize = newTotalSize;
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

    if (!mod_fs_check_pointer(file, "modfs file")) {
        return false;
    }

    // cannot write to files in other mods modfs
    if (!mod_fs_file_check_write(file)) {
        return false;
    }

    // binary only
    if (!mod_fs_file_check_file_type(file, false, true, "bool")) {
        return false;
    }

    return mod_fs_file_write_data<bool>(file, value);
}

C_DEFINE bool mod_fs_file_write_integer(struct ModFsFile *file, lua_Integer value, enum ModFsFileIntType intType) {
    mod_fs_reset_last_error();

    if (!mod_fs_check_pointer(file, "modfs file")) {
        return false;
    }

    // cannot write to files in other mods modfs
    if (!mod_fs_file_check_write(file)) {
        return false;
    }

    // binary only
    if (!mod_fs_file_check_file_type(file, false, true, "integer")) {
        return false;
    }

    // check intType
    if (!mod_fs_file_check_parameter(file, intType, INT_TYPE_MAX, "intType")) {
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
        default:           return false;
    }
}

C_DEFINE bool mod_fs_file_write_number(struct ModFsFile *file, lua_Number value, enum ModFsFileFloatType floatType) {
    mod_fs_reset_last_error();

    if (!mod_fs_check_pointer(file, "modfs file")) {
        return false;
    }

    // cannot write to files in other mods modfs
    if (!mod_fs_file_check_write(file)) {
        return false;
    }

    // binary only
    if (!mod_fs_file_check_file_type(file, false, true, "number")) {
        return false;
    }

    // check floatType
    if (!mod_fs_file_check_parameter(file, floatType, FLOAT_TYPE_MAX, "floatType")) {
        return false;
    }

    switch (floatType) {
        case FLOAT_TYPE_F32: return mod_fs_file_write_data<f32>(file, value);
        case FLOAT_TYPE_F64: return mod_fs_file_write_data<f64>(file, value);
        default:             return false;
    }
}

C_DEFINE bool mod_fs_file_write_bytes(struct ModFsFile *file, ByteString bytestring) {
    mod_fs_reset_last_error();

    if (!mod_fs_check_pointer(file, "modfs file")) {
        return false;
    }

    // cannot write to files in other mods modfs
    if (!mod_fs_file_check_write(file)) {
        return false;
    }

    // binary only
    if (!mod_fs_file_check_file_type(file, false, true, "bytes")) {
        return false;
    }

    u32 length = bytestring.length;
    if (mod_fs_file_write_resize_buffer(file, length)) {
        memcpy(file->data.bin + file->offset, bytestring.bytes, length);
        file->offset += length;
        return true;
    }
    return false;
}

C_DEFINE bool mod_fs_file_write_string(struct ModFsFile *file, const char *str) {
    mod_fs_reset_last_error();

    if (!mod_fs_check_pointer(file, "modfs file")) {
        return false;
    }

    // cannot write to files in other mods modfs
    if (!mod_fs_file_check_write(file)) {
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

    if (!mod_fs_check_pointer(file, "modfs file")) {
        return false;
    }

    // cannot write to files in other mods modfs
    if (!mod_fs_file_check_write(file)) {
        return false;
    }

    // text only
    if (!mod_fs_file_check_file_type(file, true, true, "line")) {
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

    if (!mod_fs_check_pointer(file, "modfs file")) {
        return false;
    }

    // check origin
    if (!mod_fs_file_check_parameter(file, origin, FILE_SEEK_MAX, "origin")) {
        return false;
    }

    s32 start;
    switch (origin) {
        case FILE_SEEK_SET: start = 0; break;
        case FILE_SEEK_CUR: start = file->offset; break;
        case FILE_SEEK_END: start = file->size; break;
        default:            start = 0; break;
    }
    file->offset = MIN(MAX(start + offset, 0), (s32) file->size);
    return true;
}

C_DEFINE bool mod_fs_file_is_eof(struct ModFsFile *file) {
    mod_fs_reset_last_error();

    if (!mod_fs_check_pointer(file, "modfs file")) {
        return false;
    }

    return file->offset >= file->size;
}

C_DEFINE bool mod_fs_file_fill(struct ModFsFile *file, u8 byte, u32 length) {
    mod_fs_reset_last_error();

    if (!mod_fs_check_pointer(file, "modfs file")) {
        return false;
    }

    // cannot write to files in other mods modfs
    if (!mod_fs_file_check_write(file)) {
        return false;
    }

    if (mod_fs_file_write_resize_buffer(file, length)) {
        memset(file->data.bin + file->offset, byte, length);
        file->offset += length;
        return true;
    }
    return false;
}

C_DEFINE bool mod_fs_file_erase(struct ModFsFile *file, u32 length) {
    mod_fs_reset_last_error();

    if (!mod_fs_check_pointer(file, "modfs file")) {
        return false;
    }

    // cannot erase data from files in other mods modfs
    if (!mod_fs_file_check_write(file)) {
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

    if (!mod_fs_check_pointer(file, "modfs file")) {
        return false;
    }

    // cannot change public flag to files in other mods modfs
    if (!mod_fs_file_check_write(file)) {
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
    return *sModFsLastError ? sModFsLastError : NULL;
}
