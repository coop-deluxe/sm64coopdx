extern "C" {
#include "mod_fs.h"
#include "src/pc/fs/fs.h"
#include "src/pc/mods/mods_utils.h"
#include "pc/utils/miniz/miniz.h"
}
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
#include "pc/utils/json.hpp"

#define C_DEFINE extern "C"

using json = nlohmann::json;
static const json sEmptyJson = {};

static std::vector<struct ModFs *> sModFsList = {};

#define MOD_FS_DIRECTORY    "sav"
#define MOD_FS_EXTENSION    ".modfs"
#define MOD_FS_PROPERTIES   "properties.json"

#define MOD_FS_IS_PUBLIC_DEFAULT        false
#define MOD_FS_FILE_IS_PUBLIC_DEFAULT   false

static const char *MOD_FS_FILE_ALLOWED_EXTENSIONS[] = {
    ".txt", ".json", ".ini", ".sav",    // text
    ".bin", ".col",                     // actors
    ".bhv",                             // behaviors
    ".tex", ".png",                     // textures
    ".lvl",                             // levels
    ".m64", ".aiff", ".mp3", ".ogg",    // audio
    NULL
};

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
    snprintf(sModFsLastError, sizeof(sModFsLastError), "%s: " fmt, sModFsErrorFunction, ##__VA_ARGS__); \
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

static int mod_fs_compare_filepaths(const void *l, const void *r) {
    const struct ModFsFile *lfile = *((const struct ModFsFile **) l);
    const struct ModFsFile *rfile = *((const struct ModFsFile **) r);
    return strcmp(lfile->filepath, rfile->filepath);
}

static bool mod_fs_check_filepath(struct ModFs *modFs, const char *filepath) {

    // check length
    u32 filepathLength = strlen(filepath);
    if (filepathLength == 0) {
        mod_fs_raise_error(
            "modPath: %s, filepath: %s - filepath length cannot be 0", modFs->modPath, filepath
        );
        return false;
    }
    if (filepathLength > MOD_FS_MAX_PATH - 1) {
        mod_fs_raise_error(
            "modPath: %s, filepath: %s - exceeded filepath length: %u (max is: %u)", modFs->modPath, filepath, filepathLength, MOD_FS_MAX_PATH - 1
        );
        return false;
    }

    // cannot be called properties.json
    if (strcmp(filepath, MOD_FS_PROPERTIES) == 0) {
        mod_fs_raise_error(
            "modPath: %s, filepath: %s - forbidden filepath: \"" MOD_FS_PROPERTIES "\" is reserved", modFs->modPath, filepath
        );
        return false;
    }

    // check character validity
    // only ascii chars, no control chars, no star, no backslash
    for (u32 i = 0; i != filepathLength; ++i) {
        char c = filepath[i];
        if (!isascii(c) || iscntrl(c) || c == '*' || c == '\\') {
            mod_fs_raise_error(
                "modPath: %s, filepath: %s - invalid character at position %d: '%c' (%02X)", modFs->modPath, filepath, i, c, (u8) c
            );
            return false;
        }
    }

    // cannot start with a slash
    if (filepath[0] == '/') {
        mod_fs_raise_error(
            "modPath: %s, filepath: %s - filepath cannot start with a slash '/'", modFs->modPath, filepath
        );
        return false;
    }

    // cannot end with a slash
    if (filepath[filepathLength - 1] == '/') {
        mod_fs_raise_error(
            "modPath: %s, filepath: %s - filepath cannot end with a slash '/'", modFs->modPath, filepath
        );
        return false;
    }

    // no two consecutive slashes
    if (strstr(filepath, "//")) {
        mod_fs_raise_error(
            "modPath: %s, filepath: %s - two or more consecutive slashes '/' are not allowed", modFs->modPath, filepath
        );
        return false;
    }

    // check extension
    const char *lastSlash = strrchr(filepath, '/');
    const char *lastDot = strrchr(filepath, '.');
    if (lastDot > lastSlash) {
        bool allowedExtension = false;
        for (const char **ext = MOD_FS_FILE_ALLOWED_EXTENSIONS; *ext; ext++) {
            if (strcasecmp(lastDot, *ext) == 0) {
                allowedExtension = true;
                break;
            }
        }
        if (!allowedExtension) {
            mod_fs_raise_error(
                "modPath: %s, filepath: %s - file extension not allowed: %s", modFs->modPath, filepath, lastDot
            );
            return false;
        }
    }

    return true;
}

static bool mod_fs_check_file_content(struct ModFs *modFs, struct ModFsFile *file) {
    if (!file->data.bin || file->size < 4) {
        return true;
    }

    // Reject Windows executable files
    if (memcmp(file->data.bin, "MZ", 2) == 0) {
        mod_fs_raise_error(
            "modPath: %s, filepath: %s - Binary file cannot start with \"MZ\" bytes", modFs->modPath, file->filepath
        );
        return false;
    }

    // Reject ELF files
    if (memcmp(file->data.bin, "\177ELF", 4) == 0) {
        mod_fs_raise_error(
            "modPath: %s, filepath: %s - Binary file cannot start with \"\\x7fELF\" bytes", modFs->modPath, file->filepath
        );
        return false;
    }

    return true;
}

//
// ctor, dtor
//

static struct ModFs *mod_fs_new() {
    if (gLuaActiveMod) {
        struct ModFs *modFs = mod_fs_alloc<struct ModFs>();
        if (!modFs) {
            mod_fs_raise_error(
                "failed to allocate modfs object"
            );
            return NULL;
        }
        modFs->mod = gLuaActiveMod;
        mod_fs_get_modpath(NULL, modFs->modPath);
        modFs->files = NULL;
        modFs->numFiles = 0;
        modFs->totalSize = 0;
        modFs->isPublic = MOD_FS_IS_PUBLIC_DEFAULT;
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
// Properties
//

template <typename T>
T mod_fs_get_property_value(const json &property, const T &defaultValue);

template <>
bool mod_fs_get_property_value(const json &property, const bool &defaultValue) {
    if (property.is_boolean()) {
        return (bool) property;
    }
    return defaultValue;
}

const json &mod_fs_get_properties_at(const json &properties, const std::vector<const char *> &propertyPath) {
    const json *current = &properties;
    for (const auto &key : propertyPath) {
        if (!current->is_object() || !current->contains(key)) {
            return sEmptyJson;
        }
        current = &(*current)[key];
    }
    return *current;
}

template <typename T>
static T mod_fs_read_property(const json &properties, const std::vector<const char *> &propertyPath, const T &defaultValue) {
    return mod_fs_get_property_value<T>(
        mod_fs_get_properties_at(properties, propertyPath),
        defaultValue
    );
}

static bool mod_fs_get_wildcard_tokens(const char *path, char *prefix, char *suffix) {
    const char *wildcard = strchr(path, '*');
    if (!wildcard) {
        return false;
    }

    // Multiple wildcards are not supported
    if (strchr(wildcard + 1, '*') != NULL) {
        return false;
    }

    snprintf(prefix, SYS_MAX_PATH, "%.*s", (s32) (wildcard - path), path);
    snprintf(suffix, SYS_MAX_PATH, "%s", wildcard + 1);
    return true;
}

static const json &mod_fs_read_properties_for_filepath(const json &properties, const char *filepath) {

    // Get all files properties
    const json &filesProperties = mod_fs_get_properties_at(properties, { "files" });
    if (filesProperties.empty()) {
        return sEmptyJson;
    }

    // First, check for the exact path
    const json &fileProperties = mod_fs_get_properties_at(filesProperties, { filepath });
    if (!fileProperties.empty()) {
        return fileProperties;
    }

    // If not found, look for wildcards
    for (auto it = filesProperties.begin(); it != filesProperties.end(); it++) {
        char prefix[SYS_MAX_PATH];
        char suffix[SYS_MAX_PATH];
        if (!mod_fs_get_wildcard_tokens(it.key().c_str(), prefix, suffix)) {
            continue;
        }
        if (str_starts_with(filepath, prefix) && str_ends_with(filepath, suffix)) {
            return it.value();
        }
    }

    return sEmptyJson;
}

static json mod_fs_get_properties_json(struct ModFs *modFs) {
    json properties;
    properties["isPublic"] = modFs->isPublic;
    for (u16 i = 0; i != modFs->numFiles; ++i) {
        struct ModFsFile *file = modFs->files[i];
        properties["files"][file->filepath] = {
            { "isText", file->isText },
            { "isPublic", file->isPublic }
        };
    }
    return properties;
}

static bool mod_fs_file_detect_text_mode(struct ModFsFile *file) {
    for (u32 i = 0; i != file->size; ++i) {
        u8 c = file->data.bin[i];
        if (iscntrl(c) && !isspace(c)) {
            return false;
        }
    }
    return true;
}

//
// Read
//

#define mod_fs_read_return(ret) { \
    if (zipBuf) { free(zipBuf); } \
    if (f) { fclose(f); } \
    mz_zip_reader_end(zip); \
    if (!ret) { mod_fs_destroy(modFs); } \
    return ret; \
}

#define mod_fs_read_raise_error(...) { \
    mod_fs_raise_error(__VA_ARGS__); \
    mod_fs_read_return(false); \
}

#define mod_fs_read_raise_error_zip() { \
    mod_fs_read_raise_error("modPath: %s - cannot read zip file: %s", modFs->modPath, mz_zip_get_error_string(mz_zip_get_last_error(zip))); \
}

static bool mod_fs_read_properties(mz_zip_archive *zip, json &properties, std::string &error) {
    properties.clear();

    // locate file in zip
    s32 fileIndex = mz_zip_reader_locate_file(zip, MOD_FS_PROPERTIES, NULL, 0);
    if (fileIndex < 0) {
        return true;
    }

    // read file
    size_t fileSize;
    void *fileBuf = mz_zip_reader_extract_to_heap(zip, fileIndex, &fileSize, 0);
    if (!fileBuf) {
        error = "cannot read file \"" MOD_FS_PROPERTIES "\": " + std::string(mz_zip_get_error_string(mz_zip_get_last_error(zip)));
        return false;
    }
    std::string textBuf((const char *) fileBuf, fileSize);
    mz_free(fileBuf);

    // parse json
    try {
        properties = json::parse(textBuf);
    } catch (const json::parse_error& e) {
        error = e.what();
        return false;
    }

    // properties found
    return true;
}

static bool mod_fs_read(const char *modPath, struct ModFs *modFs, bool checkExistenceOnly) {
    FILE *f = mod_fs_get_file_handle(modPath, "rb");
    if (f) {
        mz_zip_archive zip[1] = {0};
        void *zipBuf = NULL;

        // get true modPath and mod
        if (!mod_fs_get_modpath(modPath, modFs->modPath)) {
            mod_fs_read_raise_error(
                "unable to retrieve modPath from %s", modPath
            );
        }
        char activeModPath[SYS_MAX_PATH];
        if (mod_fs_get_modpath(NULL, activeModPath) && strcmp(modFs->modPath, activeModPath) == 0) {
            modFs->mod = gLuaActiveMod;
        } else {
            modFs->mod = NULL;
        }

        // read zip file
        fseek(f, 0, SEEK_END);
        size_t zipSize = ftell(f);
        rewind(f);
        zipBuf = malloc(zipSize);
        if (!zipBuf || fread(zipBuf, 1, zipSize, f) < zipSize) {
            mod_fs_read_raise_error(
                "modPath: %s - cannot read zip file", modFs->modPath
            );
        }
        fclose(f);
        f = NULL;

        // initialize zip
        if (!mz_zip_reader_init_mem(zip, zipBuf, zipSize, 0)) {
            mod_fs_read_raise_error_zip();
        }

        // find and read properties file
        json properties;
        std::string error;
        if (!mod_fs_read_properties(zip, properties, error)) {
            mod_fs_read_raise_error(
                "modPath: %s - %s", modFs->modPath, error.c_str()
            );
        }

        // check if modfs is public
        modFs->isPublic = mod_fs_read_property<bool>(properties, { "isPublic" }, MOD_FS_IS_PUBLIC_DEFAULT);
        if (!mod_fs_is_active_mod(modFs) && !modFs->isPublic) {
            // don't raise an error, user should not know if a private modfs file exists
            mod_fs_read_return (false);
        }
        if (checkExistenceOnly) {
            mod_fs_read_return (true);
        }

        modFs->numFiles = 0;
        modFs->totalSize = 0;
        u32 numFiles = mz_zip_reader_get_num_files(zip);
        std::vector<struct ModFsFile> files;

        // retrieve files and start building them
        // check filename, file size, total size and number of files here
        for (u32 i = 0; i != numFiles; ++i) {
            mz_zip_archive_file_stat fileStat;
            if (!mz_zip_reader_is_file_a_directory(zip, i) &&        // not a directory
                mz_zip_reader_file_stat(zip, i, &fileStat) &&        // valid file
                strcmp(fileStat.m_filename, MOD_FS_PROPERTIES) != 0  // not properties.json
            ) {
                struct ModFsFile file = {0};
                file.offset = i;

                // check filepath
                const char *filepath = fileStat.m_filename;
                if (!mod_fs_check_filepath(modFs, filepath)) {
                    mod_fs_read_raise_error(
                        "modPath: %s - invalid filepath: %s", modFs->modPath, filepath
                    );
                }
                memcpy(file.filepath, filepath, strlen(filepath));

                // check file size
                if (fileStat.m_uncomp_size > MOD_FS_MAX_SIZE) {
                    mod_fs_read_raise_error(
                        "modPath: %s, filepath: %s - exceeded file size: %llu (max is: %u)", modFs->modPath, file.filepath, (u64) fileStat.m_uncomp_size, MOD_FS_MAX_SIZE
                    );
                }
                file.size = file.capacity = fileStat.m_uncomp_size;

                // check total size
                modFs->totalSize += file.size;
                if (modFs->totalSize > MOD_FS_MAX_SIZE) {
                    mod_fs_read_raise_error(
                        "modPath: %s - exceeded total size: %u (max is: %u)", modFs->modPath, modFs->totalSize, MOD_FS_MAX_SIZE
                    );
                }

                // read isPublic property
                const json &fileProperties = mod_fs_read_properties_for_filepath(properties, file.filepath);
                file.isPublic = mod_fs_read_property<bool>(fileProperties, { "isPublic" }, MOD_FS_FILE_IS_PUBLIC_DEFAULT);

                // skip file if it's private
                if (!mod_fs_is_active_mod(modFs) && !file.isPublic) {
                    continue;
                }

                files.push_back(file);
                modFs->numFiles++;

                // check number of files
                if (modFs->numFiles > MOD_FS_MAX_FILES) {
                    mod_fs_read_raise_error(
                        "modPath: %s - exceeded number of files: %u (max is: %u)", modFs->modPath, numFiles, MOD_FS_MAX_FILES
                    );
                }
            }
        }

        // read files data
        if (modFs->numFiles) {
            modFs->files = (struct ModFsFile **) calloc(modFs->numFiles, sizeof(struct ModFsFile *));
            if (!modFs->files) {
                mod_fs_read_raise_error(
                    "modPath: %s - failed to allocate buffer for modfs files", modFs->modPath
                );
            }
        } else {
            modFs->files = NULL;
        }
        for (u16 i = 0, j = 0; i != modFs->numFiles; ++i) {
            const struct ModFsFile &fileRef = files[i];

            // read file
            size_t fileSize;
            void *fileBuf = mz_zip_reader_extract_to_heap(zip, fileRef.offset, &fileSize, 0);
            if (!fileBuf) {
                mod_fs_read_raise_error_zip();
            }

            // check file size
            if (fileSize != fileRef.size) {
                mod_fs_read_raise_error(
                    "modPath: %s, filepath: %s - truncated data: read size is %llu (expected: %u)", modFs->modPath, fileRef.filepath, (u64) fileSize, fileRef.size
                );
            }

            // create modfs file
            struct ModFsFile *file = modFs->files[i] = mod_fs_alloc<struct ModFsFile>();
            if (!file) {
                mod_fs_read_raise_error(
                    "modPath: %s, filepath: %s - failed to allocate modfs file object", modFs->modPath, file->filepath
                );
            }
            memcpy(file, &fileRef, sizeof(struct ModFsFile));
            file->offset = 0;
            if (file->size > 0) {
                file->data.bin = (u8 *) malloc(file->capacity);
                if (!file->data.bin) {
                    mod_fs_read_raise_error(
                        "modPath: %s, filepath: %s - failed to allocate buffer for modfs file data", modFs->modPath, file->filepath
                    );
                }
                memcpy(file->data.bin, fileBuf, file->size);
            }
            mz_free(fileBuf);

            // read isText property
            const bool isText = mod_fs_file_detect_text_mode(file);
            const json &fileProperties = mod_fs_read_properties_for_filepath(properties, file->filepath);
            file->isText = mod_fs_read_property<bool>(fileProperties, { "isText" }, isText);

            // check file content if binary
            if (!isText && !mod_fs_check_file_content(modFs, file)) {
                mod_fs_read_raise_error(
                    "modPath: %s, filepath: %s - Invalid file data", modFs->modPath, file->filepath
                );
            }
        }

        if (modFs->files) {
            qsort(modFs->files, modFs->numFiles, sizeof(struct ModFsFile *), mod_fs_compare_filepaths);
        }

        mod_fs_read_return (true);
    }
    return false;
}

//
// Write
//

#define mod_fs_write_raise_error(...) { \
    mod_fs_raise_error("cannot save modfs for the active mod: " __VA_ARGS__); \
    mz_zip_writer_end(zip); \
    fclose(f); \
    return false; \
}

#define mod_fs_write_raise_error_zip() { \
    mod_fs_write_raise_error("%s", mz_zip_get_error_string(mz_zip_get_last_error(zip))); \
}

static bool mod_fs_write(struct ModFs *modFs) {
    FILE *f = mod_fs_get_file_handle(modFs->modPath, "wb");
    if (f) {
        mz_zip_archive zip[1] = {0};

        // initialize zip
        if (!mz_zip_writer_init_heap(zip, 0, 0)) {
            mod_fs_write_raise_error_zip();
        }

        // add each modfs file to the zip archive
        for (u16 i = 0; i != modFs->numFiles; ++i) {
            struct ModFsFile *file = modFs->files[i];

            // check file content before writing if binary
            const bool isText = mod_fs_file_detect_text_mode(file);
            if (!isText && !mod_fs_check_file_content(modFs, file)) {
                mod_fs_write_raise_error(
                    "filepath: %s - Invalid file data", file->filepath
                );
            }

            if (!mz_zip_writer_add_mem(zip, file->filepath, file->data.bin, file->size, MZ_BEST_COMPRESSION)) {
                mod_fs_write_raise_error_zip();
            }
        }

        // write properties file
        std::string properties = mod_fs_get_properties_json(modFs).dump(4, ' ', true);
        if (!mz_zip_writer_add_mem(zip, MOD_FS_PROPERTIES, properties.c_str(), properties.length(), MZ_BEST_COMPRESSION)) {
            mod_fs_write_raise_error_zip();
        }

        // finalize and gets zip archive
        void *zipBuf = NULL;
        size_t zipSize = 0;
        if (!mz_zip_writer_finalize_heap_archive(zip, &zipBuf, &zipSize)) {
            mod_fs_write_raise_error_zip();
        }

        // write file and cleanup
        fwrite(zipBuf, 1, zipSize, f);
        mz_zip_writer_end(zip);
        mz_free(zipBuf);
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
            "modPath: %s - %s other mods modfs is not allowed", modFs->modPath, action
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
                    "failed to allocate modfs object"
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
    return mod_fs_get(modPath);
}

C_DEFINE struct ModFs *mod_fs_create() {
    mod_fs_reset_last_error();

    if (!mod_fs_exists(NULL)) {
        struct ModFs *modFs = mod_fs_new();
        if (!modFs) {
            mod_fs_raise_error(
                "cannot create modfs for the active mod"
            );
            return NULL;
        }

        sModFsList.push_back(modFs);
        return modFs;
    }

    mod_fs_raise_error(
        "a modfs already exists for the active mod; use `mod_fs_get()` instead"
    );
    return NULL;
}

//
// File management
//

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
    if (!mod_fs_check_write(modFs, "creating files in")) {
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
    if (!mod_fs_check_filepath(modFs, filepath)) {
        return NULL;
    }

    // check existing file
    if (mod_fs_get_file(modFs, filepath)) {
        mod_fs_raise_error(
            "modPath: %s - file %s already exists; use `mod_fs_get_file` instead", modFs->modPath, filepath
        );
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
    file->isPublic = MOD_FS_FILE_IS_PUBLIC_DEFAULT;
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
    if (!mod_fs_check_write(modFs, "moving files in")) {
        return false;
    }

    // check new filepath
    if (!mod_fs_check_filepath(modFs, newpath)) {
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
    if (!mod_fs_check_write(modFs, "copying files in")) {
        return false;
    }

    // check dest filepath
    if (!mod_fs_check_filepath(modFs, dstpath)) {
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
    u8 *buffer = (u8 *) malloc(srcfile->size);
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
    dstfile->size = dstfile->capacity = srcfile->size;
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
    if (!mod_fs_check_write(modFs, "deleting files in")) {
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
    if (!mod_fs_check_write(modFs, "deleting files in")) {
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

C_DEFINE bool mod_fs_save(struct ModFs *modFs) {
    mod_fs_reset_last_error();

    if (!mod_fs_check_pointer(modFs, "modfs")) {
        return false;
    }

    // cannot save other mods modfs
    if (!mod_fs_check_write(modFs, "saving over")) {
        return false;
    }

    return mod_fs_write(modFs);
}

C_DEFINE bool mod_fs_delete(struct ModFs *modFs) {
    mod_fs_reset_last_error();

    if (!mod_fs_check_pointer(modFs, "modfs")) {
        return false;
    }

    // cannot delete other mods modfs
    if (!mod_fs_check_write(modFs, "deleting")) {
        return false;
    }

    char filename[SYS_MAX_PATH];
    if (mod_fs_get_physical_filename(modFs->modPath, filename) && fs_sys_file_exists(filename)) {
        remove(filename);
    }

    sModFsList.erase(std::find(sModFsList.begin(), sModFsList.end(), modFs));
    mod_fs_destroy(modFs);
    mod_fs_free<struct ModFs>(modFs);
    return true;
}

C_DEFINE bool mod_fs_set_public(struct ModFs *modFs, bool pub) {
    mod_fs_reset_last_error();

    if (!mod_fs_check_pointer(modFs, "modfs")) {
        return false;
    }

    // cannot change public flag of other mods modfs
    if (!mod_fs_check_write(modFs, "changing public flag of")) {
        return false;
    }

    modFs->isPublic = pub;
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

static const char *mod_fs_file_read_string_buffer(struct ModFsFile *file, u32 length, bool skipNextChar) {
    static char *sModFsFileReadStringBuf = NULL;
    static u32 sModFsFileReadStringBufLength = 0;

    // grow buffer if needed
    if (length > sModFsFileReadStringBufLength) {
        free(sModFsFileReadStringBuf);
        sModFsFileReadStringBuf = (char *) malloc(length + 1);
        if (!sModFsFileReadStringBuf) {
            sModFsFileReadStringBufLength = 0;
            mod_fs_raise_error(
                "modPath: %s, filepath: %s - unable to allocate temporary buffer of length: %u",
                file->modFs->modPath, file->filepath, length
            );
            return NULL;
        }
        sModFsFileReadStringBufLength = length;
    }

    memcpy(sModFsFileReadStringBuf, file->data.bin + file->offset, length);
    sModFsFileReadStringBuf[length] = 0;
    file->offset = MIN(file->offset + length + skipNextChar, file->size);
    return sModFsFileReadStringBuf;
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

    if (mod_fs_file_read_check_eof(file, 1)) {
        return NULL;
    }

    // for text files, returns the whole content from offset
    if (file->isText) {
        return mod_fs_file_read_string_buffer(file, file->size - file->offset, false);
    }

    // for binary, stops at the first NUL char or at the end of the file
    u32 length = 0;
    const char *start = (const char *) (file->data.bin + file->offset);
    const char *end = (const char *) (file->data.bin + file->size);
    for (const char *c = start; *c && c < end; c++) {
        length++;
    }
    return mod_fs_file_read_string_buffer(file, length, true);
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

    if (mod_fs_file_read_check_eof(file, 1)) {
        return NULL;
    }

    // stops at the first newline or at the end of the file
    u32 length = 0;
    const char *start = (const char *) (file->data.text + file->offset);
    const char *end = (const char *) (file->data.text + file->size);
    for (const char *c = start; *c != '\n' && c < end; c++) {
        length++;
    }
    return mod_fs_file_read_string_buffer(file, length, true);
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
        u32 newCapacity = MAX(file->capacity * 2, file->offset + size);
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

C_DEFINE bool mod_fs_file_rewind(struct ModFsFile *file) {
    mod_fs_reset_last_error();

    if (!mod_fs_check_pointer(file, "modfs file")) {
        return false;
    }

    file->offset = 0;
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

C_DEFINE bool mod_fs_file_set_text_mode(struct ModFsFile *file, bool text) {
    mod_fs_reset_last_error();

    if (!mod_fs_check_pointer(file, "modfs file")) {
        return false;
    }

    file->isText = text;
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

C_DEFINE void mod_fs_hide_errors(bool hide) {
    sModFsHideErrors = hide;
}

C_DEFINE const char *mod_fs_get_last_error() {
    return *sModFsLastError ? sModFsLastError : NULL;
}

//
// Functions used by other C modules, not API
//

static bool mod_fs_extract_modpath_and_filepath(const char *uri, char *modPath, char *filepath) {

    // check prefix
    if (!is_mod_fs_file(uri)) {
        return false;
    }

    // get modPath
    const char *modPathBegin = uri + sizeof(MOD_FS_URI_PREFIX) - 1;
    const char *modPathEnd = strchr(modPathBegin, '/');
    if (!modPathEnd) {
        return false;
    }
    snprintf(modPath, SYS_MAX_PATH, "%.*s", (s32) (modPathEnd - modPathBegin), modPathBegin);

    // get filepath
    snprintf(filepath, MOD_FS_MAX_PATH, "%s", modPathEnd + 1);

    return true;
}

C_DEFINE bool mod_fs_read_file_from_uri(const char *uri, void **buffer, u32 *length) {
    char modPath[SYS_MAX_PATH];
    char filepath[MOD_FS_MAX_PATH];
    if (!mod_fs_extract_modpath_and_filepath(uri, modPath, filepath)) {
        return false;
    }

    struct ModFs *modFs = mod_fs_get(modPath);
    if (!modFs) {
        return false;
    }

    struct ModFsFile *file = mod_fs_get_file(modFs, filepath);
    if (!file || !file->data.bin || !file->size) {
        return false;
    }

    *buffer = malloc(file->size);
    if (!*buffer) {
        return false;
    }
    memcpy(*buffer, file->data.bin, file->size);
    *length = file->size;
    return true;
}

C_DEFINE void mod_fs_shutdown() {

    // Close all modfs
    for (auto &modFs : sModFsList) {
        mod_fs_destroy(modFs);
        mod_fs_free<struct ModFs>(modFs);
    }
    sModFsList.clear();

    // Reset error state
    mod_fs_reset_last_error();
    sModFsHideErrors = false;
}
