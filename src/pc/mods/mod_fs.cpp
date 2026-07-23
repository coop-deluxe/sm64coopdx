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

namespace modfs {

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
static enum ModFsErrorCode sModFsLastErrorCode;
static char sModFsLastError[1024];
static char sModFsErrorFunction[256];

#define mod_fs_reset_last_error() { \
    *err = modfs::sModFsLastErrorCode = MOD_FS_ERR_NONE; \
    memset(modfs::sModFsLastError, 0, sizeof(modfs::sModFsLastError)); \
    snprintf(modfs::sModFsErrorFunction, sizeof(modfs::sModFsErrorFunction), "%s", __FUNCTION__); \
}

#define mod_fs_raise_error(errcode, fmt, ...) { \
    if (!*err) { \
        sModFsLastErrorCode = *err = errcode; \
        snprintf(sModFsLastError, sizeof(sModFsLastError), "%s: " fmt, sModFsErrorFunction, ##__VA_ARGS__); \
        if (!sModFsHideErrors) { \
            LOG_LUA_LINE("%s", sModFsLastError); \
        } \
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

static bool mod_fs_check_filepath(struct ModFs *modFs, const char *filepath, enum ModFsErrorCode *err) {

    // check length
    u32 filepathLength = strlen(filepath);
    if (filepathLength == 0) {
        mod_fs_raise_error(
            MOD_FS_ERR_FILEPATH_EMPTY,
            "modPath: %s, filepath: %s - Filepath cannot be empty", modFs->modPath, filepath
        );
        return false;
    }
    if (filepathLength > MOD_FS_MAX_PATH - 1) {
        mod_fs_raise_error(
            MOD_FS_ERR_FILEPATH_LEN_EXCEEDED,
            "modPath: %s, filepath: %s - Exceeded filepath length: %u (max is: %u)", modFs->modPath, filepath, filepathLength, MOD_FS_MAX_PATH - 1
        );
        return false;
    }

    // cannot be called properties.json
    if (strcmp(filepath, MOD_FS_PROPERTIES) == 0) {
        mod_fs_raise_error(
            MOD_FS_ERR_FILEPATH_RESERVED,
            "modPath: %s, filepath: %s - Forbidden filepath: \"" MOD_FS_PROPERTIES "\" is reserved", modFs->modPath, filepath
        );
        return false;
    }

    // check character validity
    // only ascii chars, no control chars, no asterisk, no backslash
    for (u32 i = 0; i != filepathLength; ++i) {
        char c = filepath[i];
        if (!isascii(c) || iscntrl(c) || c == '*' || c == '\\') {
            mod_fs_raise_error(
                MOD_FS_ERR_FILEPATH_INVALID_CHAR,
                "modPath: %s, filepath: %s - Invalid character at position %d: '%c' (%02X)", modFs->modPath, filepath, i, c, (u8) c
            );
            return false;
        }
    }

    // cannot start with a whitespace
    if (isspace(filepath[0])) {
        mod_fs_raise_error(
            MOD_FS_ERR_FILEPATH_MALFORMED,
            "modPath: %s, filepath: %s - Filepath cannot start with a whitespace", modFs->modPath, filepath
        );
        return false;
    }

    // cannot end with a whitespace
    if (isspace(filepath[filepathLength - 1])) {
        mod_fs_raise_error(
            MOD_FS_ERR_FILEPATH_MALFORMED,
            "modPath: %s, filepath: %s - Filepath cannot end with a whitespace", modFs->modPath, filepath
        );
        return false;
    }

    // cannot start with a slash
    if (filepath[0] == '/') {
        mod_fs_raise_error(
            MOD_FS_ERR_FILEPATH_MALFORMED,
            "modPath: %s, filepath: %s - Filepath cannot start with a slash '/'", modFs->modPath, filepath
        );
        return false;
    }

    // cannot end with a slash
    if (filepath[filepathLength - 1] == '/') {
        mod_fs_raise_error(
            MOD_FS_ERR_FILEPATH_MALFORMED,
            "modPath: %s, filepath: %s - Filepath cannot end with a slash '/'", modFs->modPath, filepath
        );
        return false;
    }

    // no two consecutive slashes
    if (strstr(filepath, "//")) {
        mod_fs_raise_error(
            MOD_FS_ERR_FILEPATH_MALFORMED,
            "modPath: %s, filepath: %s - Two or more consecutive slashes '/' are not allowed", modFs->modPath, filepath
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
                MOD_FS_ERR_FILEPATH_INVALID_EXTENSION,
                "modPath: %s, filepath: %s - file extension not allowed: %s", modFs->modPath, filepath, lastDot
            );
            return false;
        }
    }

    return true;
}

//
// ctor, dtor
//

static struct ModFs *mod_fs_new(enum ModFsErrorCode *err) {
    if (gLuaActiveMod) {
        struct ModFs *modFs = mod_fs_alloc<struct ModFs>();
        if (!modFs) {
            mod_fs_raise_error(
                MOD_FS_ERR_ALLOC_FAILED,
                "Failed to allocate ModFS object"
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

template<>
s32 mod_fs_get_property_value(const json &property, const s32 &defaultValue) {
    if (property.is_number_integer()) {
        return (s32) property;
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
            { "isPublic", file->isPublic },
            { "compressionLevel", file->compressionLevel }
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
    mod_fs_read_raise_error( \
        MOD_FS_ERR_READ_ZIP, \
        "modPath: %s - Cannot read zip file: %s", modFs->modPath, mz_zip_get_error_string(mz_zip_get_last_error(zip)) \
    ); \
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
        error = "Cannot read file \"" MOD_FS_PROPERTIES "\": " + std::string(mz_zip_get_error_string(mz_zip_get_last_error(zip)));
        return false;
    }
    std::string textBuf((const char *) fileBuf, fileSize);
    mz_free(fileBuf);

    // parse json
    try {
        properties = json::parse(textBuf);
    } catch (const json::parse_error& e) {
        error = "Cannot read file \"" MOD_FS_PROPERTIES "\": " + std::string(e.what());
        return false;
    }

    // properties found
    return true;
}

static bool mod_fs_read(const char *modPath, struct ModFs *modFs, bool checkExistenceOnly, enum ModFsErrorCode *err) {
    FILE *f = mod_fs_get_file_handle(modPath, "rb");
    if (f) {
        mz_zip_archive zip[1] = {0};
        void *zipBuf = NULL;

        // get true modPath and mod
        if (!mod_fs_get_modpath(modPath, modFs->modPath)) {
            mod_fs_read_raise_error(
                MOD_FS_ERR_READ_INVALID_MODPATH,
                "Unable to retrieve modPath from: %s", modPath
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
                MOD_FS_ERR_READ_ZIP,
                "modPath: %s - Cannot read zip file", modFs->modPath
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
                MOD_FS_ERR_READ_PROPERTIES,
                "modPath: %s - %s", modFs->modPath, error.c_str()
            );
        }

        // check if ModFS is public
        modFs->isPublic = mod_fs_read_property<bool>(properties, { "isPublic" }, MOD_FS_IS_PUBLIC_DEFAULT);
        if (!mod_fs_is_active_mod(modFs) && !modFs->isPublic) {
            // don't raise an error, user should not know if a private ModFS file exists
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
                if (!mod_fs_check_filepath(modFs, filepath, err)) {
                    // mod_fs_check_filepath already sets the error
                    mod_fs_read_return (false);
                }
                memcpy(file.filepath, filepath, strlen(filepath));

                // check file size
                if (fileStat.m_uncomp_size > MOD_FS_MAX_SIZE) {
                    mod_fs_read_raise_error(
                        MOD_FS_ERR_TOTAL_SIZE_EXCEEDED,
                        "modPath: %s, filepath: %s - Exceeded file size: %llu (max is: %u)", modFs->modPath, file.filepath, (u64) fileStat.m_uncomp_size, MOD_FS_MAX_SIZE
                    );
                }
                file.size = file.capacity = fileStat.m_uncomp_size;

                // check total size
                modFs->totalSize += file.size;
                if (modFs->totalSize > MOD_FS_MAX_SIZE) {
                    mod_fs_read_raise_error(
                        MOD_FS_ERR_TOTAL_SIZE_EXCEEDED,
                        "modPath: %s - Exceeded total size: %u (max is: %u)", modFs->modPath, modFs->totalSize, MOD_FS_MAX_SIZE
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
                        MOD_FS_ERR_NUM_FILES_EXCEEDED,
                        "modPath: %s - Exceeded number of files: %u (max is: %u)", modFs->modPath, numFiles, MOD_FS_MAX_FILES
                    );
                }
            }
        }

        // read files data
        if (modFs->numFiles) {
            modFs->files = (struct ModFsFile **) calloc(modFs->numFiles, sizeof(struct ModFsFile *));
            if (!modFs->files) {
                mod_fs_read_raise_error(
                    MOD_FS_ERR_ALLOC_FAILED,
                    "modPath: %s - Failed to allocate buffer for ModFS files", modFs->modPath
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
                    MOD_FS_ERR_READ_FILE_TRUNCATED,
                    "modPath: %s, filepath: %s - Truncated data: read size is %llu (expected: %u)", modFs->modPath, fileRef.filepath, (u64) fileSize, fileRef.size
                );
            }

            // create ModFS file
            struct ModFsFile *file = modFs->files[i] = mod_fs_alloc<struct ModFsFile>();
            if (!file) {
                mod_fs_read_raise_error(
                    MOD_FS_ERR_ALLOC_FAILED,
                    "modPath: %s, filepath: %s - Failed to allocate ModFS file object", modFs->modPath, fileRef.filepath
                );
            }
            memcpy(file, &fileRef, sizeof(struct ModFsFile));
            file->offset = 0;
            if (file->size > 0) {
                file->data.bin = (u8 *) malloc(file->capacity);
                if (!file->data.bin) {
                    mod_fs_read_raise_error(
                        MOD_FS_ERR_ALLOC_FAILED,
                        "modPath: %s, filepath: %s - Failed to allocate buffer for ModFS file data", modFs->modPath, file->filepath
                    );
                }
                memcpy(file->data.bin, fileBuf, file->size);
            }
            mz_free(fileBuf);

            // read isText property
            const bool isText = mod_fs_file_detect_text_mode(file);
            const json &fileProperties = mod_fs_read_properties_for_filepath(properties, file->filepath);
            file->isText = mod_fs_read_property<bool>(fileProperties, { "isText" }, isText);

            // read compressionLevel property
            file->compressionLevel = mod_fs_read_property<s32>(fileProperties, { "compressionLevel" }, MOD_FS_COMPRESSION_DEFAULT);
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

#define mod_fs_write_raise_error(errcode, ...) { \
    mod_fs_raise_error(errcode, "Cannot save ModFS for the active mod: " __VA_ARGS__); \
    mz_zip_writer_end(zip); \
    fclose(f); \
    return false; \
}

#define mod_fs_write_raise_error_zip() { \
    mod_fs_write_raise_error( \
        MOD_FS_ERR_WRITE_ZIP, \
        "%s", mz_zip_get_error_string(mz_zip_get_last_error(zip)) \
    ); \
}

static bool mod_fs_write(struct ModFs *modFs, enum ModFsErrorCode *err) {
    FILE *f = mod_fs_get_file_handle(modFs->modPath, "wb");
    if (f) {
        mz_zip_archive zip[1] = {0};

        // initialize zip
        if (!mz_zip_writer_init_heap(zip, 0, 0)) {
            mod_fs_write_raise_error_zip();
        }

        // add each ModFS file to the zip archive
        for (u16 i = 0; i != modFs->numFiles; ++i) {
            struct ModFsFile *file = modFs->files[i];
            if (!mz_zip_writer_add_mem(zip, file->filepath, file->data.bin, file->size, file->compressionLevel)) {
                mod_fs_write_raise_error_zip();
            }
        }

        // write properties file
        std::string properties = mod_fs_get_properties_json(modFs).dump(4, ' ', true);
        if (!mz_zip_writer_add_mem(zip, MOD_FS_PROPERTIES, properties.c_str(), properties.length(), MZ_BEST_SPEED)) {
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
static bool mod_fs_check_pointer(T *ptr, const char *typeName, enum ModFsErrorCode *err) {
    if (!mod_fs_is_valid_pointer(ptr)) {
        mod_fs_raise_error(
            MOD_FS_ERR_INVALID_POINTER,
            "Pointer is not a valid %s object", typeName
        );
        return false;
    }
    return true;
}

static bool mod_fs_check_write(struct ModFs *modFs, const char *action, enum ModFsErrorCode *err) {
    if (!mod_fs_is_active_mod(modFs)) {
        mod_fs_raise_error(
            MOD_FS_ERR_WRITE_NOT_ACTIVE_MOD,
            "modPath: %s - %s other mods ModFS is not allowed", modFs->modPath, action
        );
        return false;
    }
    return true;
}

static bool mod_fs_file_check_write(struct ModFsFile *file, enum ModFsErrorCode *err) {
    if (!mod_fs_is_active_mod(file->modFs)) {
        mod_fs_raise_error(
            MOD_FS_ERR_WRITE_NOT_ACTIVE_MOD,
            "modPath: %s, filepath: %s - Writing to files in other mods ModFS is not allowed", file->modFs->modPath, file->filepath
        );
        return false;
    }
    return true;
}

static bool mod_fs_file_check_file_type(struct ModFsFile *file, bool isText, bool write, const char *dataName, enum ModFsErrorCode *err) {
    if (file->isText != isText) {
        mod_fs_raise_error(
            MOD_FS_ERR_FILE_TYPE_NOT_ALLOWED,
            "modPath: %s, filepath: %s - Cannot %s %s %s a %s file", file->modFs->modPath, file->filepath,
            (write ? "write" : "read"),
            dataName,
            (write ? "to" : "from"),
            (file->isText ? "text" : "binary")
        );
        return false;
    }
    return true;
}

static bool mod_fs_file_check_parameter(struct ModFsFile *file, int parameter, int parameterMin, int parameterMax, const char *parameterName, enum ModFsErrorCode *err) {
    if (parameter < parameterMin || parameter > parameterMax) {
        mod_fs_raise_error(
            MOD_FS_ERR_INVALID_PARAMETER,
            "modPath: %s, filepath: %s - Invalid %s: %d (must be between %d and %d inclusive)", file->modFs->modPath, file->filepath,
            parameterName,
            parameter,
            parameterMin,
            parameterMax
        );
        return false;
    }
    return true;
}

//
// FS management
//

static struct ModFs *mod_fs_get_or_load(const char *modPath, bool loadIfNotFound, enum ModFsErrorCode *err) {
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
        if (mod_fs_read(modPath, &temp, false, err)) {
            struct ModFs *modFs = mod_fs_alloc<struct ModFs>();
            if (!modFs) {
                mod_fs_raise_error(
                    MOD_FS_ERR_ALLOC_FAILED,
                    "Failed to allocate ModFS object"
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

static bool mod_fs_exists(const char *modPath, enum ModFsErrorCode *err) {
    struct ModFs *modFs = mod_fs_get_or_load(modPath, false, err);
    if (modFs) {
        return true;
    }

    struct ModFs header = {0};
    if (!mod_fs_read(modPath, &header, true, err)) {
        return false;
    }

    return true;
}

static struct ModFs *mod_fs_get(const char *modPath, enum ModFsErrorCode *err) {
    return mod_fs_get_or_load(modPath, true, err);
}

static struct ModFs *mod_fs_reload(const char *modPath, enum ModFsErrorCode *err) {

    // remove ModFS object if already loaded
    struct ModFs *modFs = mod_fs_get_or_load(modPath, false, err);
    if (modFs) {
        sModFsList.erase(std::find(sModFsList.begin(), sModFsList.end(), modFs));
        mod_fs_destroy(modFs);
        mod_fs_free<struct ModFs>(modFs);
    }

    // reload
    return modfs::mod_fs_get(modPath, err);
}

static struct ModFs *mod_fs_create(enum ModFsErrorCode *err) {
    if (!modfs::mod_fs_exists(NULL, err)) {
        struct ModFs *modFs = mod_fs_new(err);
        if (!modFs) {
            mod_fs_raise_error(
                MOD_FS_ERR_ALLOC_FAILED,
                "Cannot create ModFS for the active mod"
            );
            return NULL;
        }

        sModFsList.push_back(modFs);
        return modFs;
    }

    mod_fs_raise_error(
        MOD_FS_ERR_ALREADY_EXISTS,
        "A ModFS already exists for the active mod; use `mod_fs_get()` instead"
    );
    return NULL;
}

//
// File management
//

static const char *mod_fs_get_filename(struct ModFs *modFs, u16 index, enum ModFsErrorCode *err) {
    if (!mod_fs_check_pointer(modFs, "ModFS", err)) {
        return NULL;
    }

    if (index >= modFs->numFiles) {
        mod_fs_raise_error(
            MOD_FS_ERR_FILE_INVALID_INDEX,
            "modPath: %s - File index out of bounds: %u (num files: %u)", modFs->modPath, index, modFs->numFiles
        );
        return NULL;
    }

    return modFs->files[index]->filepath;
}

static struct ModFsFile *mod_fs_get_file(struct ModFs *modFs, const char *filepath, enum ModFsErrorCode *err) {
    if (!mod_fs_check_pointer(modFs, "ModFS", err)) {
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

static struct ModFsFile *mod_fs_create_file(struct ModFs *modFs, const char *filepath, bool text, enum ModFsErrorCode *err) {
    if (!mod_fs_check_pointer(modFs, "ModFS", err)) {
        return NULL;
    }

    // cannot create new files in other mods ModFS
    if (!mod_fs_check_write(modFs, "Creating files in", err)) {
        return NULL;
    }

    // check number of files
    if (modFs->numFiles == MOD_FS_MAX_FILES) {
        mod_fs_raise_error(
            MOD_FS_ERR_NUM_FILES_EXCEEDED,
            "modPath: %s - Reached max number of files: %u", modFs->modPath, MOD_FS_MAX_FILES
        );
        return NULL;
    }

    // check filepath
    if (!mod_fs_check_filepath(modFs, filepath, err)) {
        return NULL;
    }

    // check existing file
    if (modfs::mod_fs_get_file(modFs, filepath, err)) {
        mod_fs_raise_error(
            MOD_FS_ERR_ALREADY_EXISTS,
            "modPath: %s - File %s already exists; use `mod_fs_get_file` instead", modFs->modPath, filepath
        );
        return NULL;
    }

    // create file
    struct ModFsFile *file = mod_fs_alloc<struct ModFsFile>();
    if (!file) {
        mod_fs_raise_error(
            MOD_FS_ERR_ALLOC_FAILED,
            "modPath: %s, filepath: %s - Failed to allocate ModFS file object", modFs->modPath, filepath
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
    file->compressionLevel = MOD_FS_COMPRESSION_DEFAULT;
    file->modFs = modFs;

    // add file and sort by filename
    struct ModFsFile **files = (struct ModFsFile **) realloc(modFs->files, (modFs->numFiles + 1) * sizeof(struct ModFsFile *));
    if (!files) {
        mod_fs_raise_error(
            MOD_FS_ERR_ALLOC_FAILED,
            "modPath: %s, filepath: %s - Failed to reallocate buffer of ModFS files", modFs->modPath, filepath
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

static bool mod_fs_delete_file(struct ModFs *modFs, const char *filepath, enum ModFsErrorCode *err) {
    if (!mod_fs_check_pointer(modFs, "ModFS", err)) {
        return false;
    }

    // cannot delete files in other mods ModFS
    if (!mod_fs_check_write(modFs, "Deleting files in", err)) {
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
        MOD_FS_ERR_NOT_FOUND,
        "modPath: %s - File %s doesn't exist", modFs->modPath, filepath
    );
    return false;
}

static bool mod_fs_move_file(struct ModFs *modFs, const char *oldpath, const char *newpath, bool overwriteExisting, enum ModFsErrorCode *err) {
    if (!mod_fs_check_pointer(modFs, "ModFS", err)) {
        return false;
    }

    // cannot move files in other mods ModFS
    if (!mod_fs_check_write(modFs, "Moving files in", err)) {
        return false;
    }

    // check new filepath
    if (!mod_fs_check_filepath(modFs, newpath, err)) {
        return false;
    }

    // Do nothing if old and new paths are the same
    if (strcmp(oldpath, newpath) == 0) {
        return true;
    }

    // get file
    struct ModFsFile *oldfile = modfs::mod_fs_get_file(modFs, oldpath, err);
    if (!oldfile) {
        mod_fs_raise_error(
            MOD_FS_ERR_NOT_FOUND,
            "modPath: %s - File %s doesn't exist", modFs->modPath, oldpath
        );
        return false;
    }

    // if overwriteExisting is not set, check if the newpath points to an existing file
    struct ModFsFile *newfile = modfs::mod_fs_get_file(modFs, newpath, err);
    if (newfile && !overwriteExisting) {
        mod_fs_raise_error(
            MOD_FS_ERR_ALREADY_EXISTS,
            "modPath: %s - File %s already exists; set `overwriteExisting` to true to replace this file", modFs->modPath, newpath
        );
        return false;
    }

    // rename file
    if (newfile && !modfs::mod_fs_delete_file(modFs, newpath, err)) {
        return false;
    }
    snprintf(oldfile->filepath, MOD_FS_MAX_PATH, "%s", newpath);
    return true;
}

static bool mod_fs_copy_file(struct ModFs *modFs, const char *srcpath, const char *dstpath, bool overwriteExisting, enum ModFsErrorCode *err) {
    if (!mod_fs_check_pointer(modFs, "ModFS", err)) {
        return false;
    }

    // cannot copy files in other mods ModFS
    if (!mod_fs_check_write(modFs, "copying files in", err)) {
        return false;
    }

    // check dest filepath
    if (!mod_fs_check_filepath(modFs, dstpath, err)) {
        return false;
    }

    // Do nothing if src and dst paths are the same
    if (strcmp(srcpath, dstpath) == 0) {
        return true;
    }

    // get file
    struct ModFsFile *srcfile = modfs::mod_fs_get_file(modFs, srcpath, err);
    if (!srcfile) {
        mod_fs_raise_error(
            MOD_FS_ERR_NOT_FOUND,
            "modPath: %s - File %s doesn't exist", modFs->modPath, srcpath
        );
        return false;
    }

    // if overwriteExisting is not set, check if the newpath points to an existing file
    struct ModFsFile *dstfile = modfs::mod_fs_get_file(modFs, dstpath, err);
    if (dstfile && !overwriteExisting) {
        mod_fs_raise_error(
            MOD_FS_ERR_ALREADY_EXISTS,
            "modPath: %s - File %s already exists; set `overwriteExisting` to true to replace this file", modFs->modPath, dstpath
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
            MOD_FS_ERR_TOTAL_SIZE_EXCEEDED,
            "modPath: %s - Cannot copy file %s: exceeding total size: %u (max is: %u)", modFs->modPath, srcpath, newTotalSize, MOD_FS_MAX_SIZE
        );
        return false;
    }

    // copy file
    u8 *buffer = (u8 *) malloc(srcfile->size);
    if (!buffer) {
        mod_fs_raise_error(
            MOD_FS_ERR_ALLOC_FAILED,
            "modPath: %s, filepath: %s - Failed to allocate buffer for ModFS file data", modFs->modPath, dstpath
        );
        return false;
    }
    if (dstfile) {
        free(dstfile->data.bin);
    } else {
        dstfile = modfs::mod_fs_create_file(modFs, dstpath, srcfile->isText, err);
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
    modFs->totalSize = newTotalSize;
    return true;
}

static bool mod_fs_clear(struct ModFs *modFs, enum ModFsErrorCode *err) {
    if (!mod_fs_check_pointer(modFs, "ModFS", err)) {
        return false;
    }

    // cannot delete files in other mods ModFS
    if (!mod_fs_check_write(modFs, "Deleting files in", err)) {
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

static bool mod_fs_save(struct ModFs *modFs, enum ModFsErrorCode *err) {
    if (!mod_fs_check_pointer(modFs, "ModFS", err)) {
        return false;
    }

    // cannot save other mods ModFS
    if (!mod_fs_check_write(modFs, "Saving over", err)) {
        return false;
    }

    return mod_fs_write(modFs, err);
}

static bool mod_fs_delete(struct ModFs *modFs, enum ModFsErrorCode *err) {
    if (!mod_fs_check_pointer(modFs, "ModFS", err)) {
        return false;
    }

    // cannot delete other mods ModFS
    if (!mod_fs_check_write(modFs, "Deleting", err)) {
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

static bool mod_fs_set_public(struct ModFs *modFs, bool pub, enum ModFsErrorCode *err) {
    if (!mod_fs_check_pointer(modFs, "ModFS", err)) {
        return false;
    }

    // cannot change public flag of other mods ModFS
    if (!mod_fs_check_write(modFs, "Changing public flag of", err)) {
        return false;
    }

    modFs->isPublic = pub;
    return true;
}

//
// Read data
//

static bool mod_fs_file_read_check_eof(struct ModFsFile *file, u32 size, enum ModFsErrorCode *err) {
    if (file->offset + size > file->size) {
        file->offset = file->size;
        mod_fs_raise_error(
            MOD_FS_ERR_READ_EOF,
            "modPath: %s, filepath: %s - Reached end of file", file->modFs->modPath, file->filepath
        );
        return true;
    }
    return false;
}

template <typename T>
static T mod_fs_file_read_data(struct ModFsFile *file, T defaultValue, enum ModFsErrorCode *err) {
    if (mod_fs_file_read_check_eof(file, sizeof(T), err)) {
        return defaultValue;
    }
    T value;
    memcpy(&value, file->data.bin + file->offset, sizeof(T));
    file->offset += sizeof(T);
    return value;
}

static const char *mod_fs_file_read_string_buffer(struct ModFsFile *file, u32 length, bool skipNextChar, enum ModFsErrorCode *err) {
    static char *sModFsFileReadStringBuf = NULL;
    static u32 sModFsFileReadStringBufLength = 0;

    // grow buffer if needed
    if (length > sModFsFileReadStringBufLength) {
        free(sModFsFileReadStringBuf);
        sModFsFileReadStringBuf = (char *) malloc(length + 1);
        if (!sModFsFileReadStringBuf) {
            sModFsFileReadStringBufLength = 0;
            mod_fs_raise_error(
                MOD_FS_ERR_ALLOC_FAILED,
                "modPath: %s, filepath: %s - Unable to allocate temporary buffer of length: %u",
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

static bool mod_fs_file_read_bool(struct ModFsFile *file, enum ModFsErrorCode *err) {
    if (!mod_fs_check_pointer(file, "ModFS file", err)) {
        return false;
    }

    // binary only
    if (!mod_fs_file_check_file_type(file, false, false, "bool", err)) {
        return false;
    }

    return mod_fs_file_read_data<bool>(file, false, err);
}

static lua_Integer mod_fs_file_read_integer(struct ModFsFile *file, enum ModFsFileIntType intType, enum ModFsErrorCode *err) {
    if (!mod_fs_check_pointer(file, "ModFS file", err)) {
        return 0;
    }

    // binary only
    if (!mod_fs_file_check_file_type(file, false, false, "integer", err)) {
        return 0;
    }

    // check intType
    if (!mod_fs_file_check_parameter(file, intType, 0, INT_TYPE_MAX - 1, "intType", err)) {
        return 0;
    }

    switch (intType) {
        case INT_TYPE_U8:  return mod_fs_file_read_data<u8>(file, 0, err);
        case INT_TYPE_U16: return mod_fs_file_read_data<u16>(file, 0, err);
        case INT_TYPE_U32: return mod_fs_file_read_data<u32>(file, 0, err);
        case INT_TYPE_U64: return mod_fs_file_read_data<u64>(file, 0, err);
        case INT_TYPE_S8:  return mod_fs_file_read_data<s8>(file, 0, err);
        case INT_TYPE_S16: return mod_fs_file_read_data<s16>(file, 0, err);
        case INT_TYPE_S32: return mod_fs_file_read_data<s32>(file, 0, err);
        case INT_TYPE_S64: return mod_fs_file_read_data<s64>(file, 0, err);
        default:           return 0;
    }
}

static lua_Number mod_fs_file_read_number(struct ModFsFile *file, enum ModFsFileFloatType floatType, enum ModFsErrorCode *err) {
    if (!mod_fs_check_pointer(file, "ModFS file", err)) {
        return 0;
    }

    // binary only
    if (!mod_fs_file_check_file_type(file, false, false, "number", err)) {
        return 0;
    }

    // check intType
    if (!mod_fs_file_check_parameter(file, floatType, 0, FLOAT_TYPE_MAX - 1, "floatType", err)) {
        return 0;
    }

    switch (floatType) {
        case FLOAT_TYPE_F32: return mod_fs_file_read_data<f32>(file, 0, err);
        case FLOAT_TYPE_F64: return mod_fs_file_read_data<f64>(file, 0, err);
        default:             return 0;
    }
}

static ByteString mod_fs_file_read_bytes(struct ModFsFile *file, u32 length, enum ModFsErrorCode *err) {
    ByteString bytestring = { NULL, 0 };

    if (!mod_fs_check_pointer(file, "ModFS file", err)) {
        return bytestring;
    }

    // binary only
    if (!mod_fs_file_check_file_type(file, false, false, "bytes", err)) {
        return bytestring;
    }

    // check eof
    if (mod_fs_file_read_check_eof(file, length, err)) {
        return bytestring;
    }

    bytestring.bytes = (const char *) (file->data.bin + file->offset);
    bytestring.length = length;
    file->offset += length;
    return bytestring;
}

static const char *mod_fs_file_read_string(struct ModFsFile *file, enum ModFsErrorCode *err) {
    if (!mod_fs_check_pointer(file, "ModFS file", err)) {
        return NULL;
    }

    if (mod_fs_file_read_check_eof(file, 1, err)) {
        return NULL;
    }

    // for text files, returns the whole content from offset
    if (file->isText) {
        return mod_fs_file_read_string_buffer(file, file->size - file->offset, false, err);
    }

    // for binary, stops at the first NUL char or at the end of the file
    u32 length = 0;
    const char *start = (const char *) (file->data.bin + file->offset);
    const char *end = (const char *) (file->data.bin + file->size);
    for (const char *c = start; *c && c < end; c++) {
        length++;
    }
    return mod_fs_file_read_string_buffer(file, length, true, err);
}

static const char *mod_fs_file_read_line(struct ModFsFile *file, enum ModFsErrorCode *err) {
    if (!mod_fs_check_pointer(file, "ModFS file", err)) {
        return NULL;
    }

    // text only
    if (!mod_fs_file_check_file_type(file, true, false, "line", err)) {
        return 0;
    }

    if (mod_fs_file_read_check_eof(file, 1, err)) {
        return NULL;
    }

    // stops at the first newline or at the end of the file
    u32 length = 0;
    const char *start = (const char *) (file->data.text + file->offset);
    const char *end = (const char *) (file->data.text + file->size);
    for (const char *c = start; *c != '\n' && c < end; c++) {
        length++;
    }
    return mod_fs_file_read_string_buffer(file, length, true, err);
}

//
// Write data
//

static bool mod_fs_file_write_resize_buffer(struct ModFsFile *file, u32 size, enum ModFsErrorCode *err) {

    // compute and check new sizes
    file->offset = MIN(file->offset, file->size);
    u32 newFileSize = MAX(file->offset + size, file->size);
    u32 newTotalSize = file->modFs->totalSize + (newFileSize - file->size);
    if (newTotalSize > MOD_FS_MAX_SIZE) {
        mod_fs_raise_error(
            MOD_FS_ERR_TOTAL_SIZE_EXCEEDED,
            "modPath: %s, filepath: %s - Cannot write to file: exceeding total size: %u (max is: %u)", file->modFs->modPath, file->filepath, newTotalSize, MOD_FS_MAX_SIZE
        );
        return false;
    }

    // resize data buffer
    if (file->offset + size > file->capacity) {
        u32 newCapacity = MAX(file->capacity * 2, file->offset + size);
        u8 *buffer = (u8 *) realloc(file->data.bin, newCapacity);
        if (!buffer) {
            mod_fs_raise_error(
                MOD_FS_ERR_ALLOC_FAILED,
                "modPath: %s, filepath: %s - Failed to reallocate buffer of ModFS file data", file->modFs->modPath, file->filepath
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
static bool mod_fs_file_write_data(struct ModFsFile *file, T value, enum ModFsErrorCode *err) {
    if (mod_fs_file_write_resize_buffer(file, sizeof(T), err)) {
        memcpy(file->data.bin + file->offset, &value, sizeof(T));
        file->offset += sizeof(T);
        return true;
    }
    return false;
}

static bool mod_fs_file_write_bool(struct ModFsFile *file, bool value, enum ModFsErrorCode *err) {
    if (!mod_fs_check_pointer(file, "ModFS file", err)) {
        return false;
    }

    // cannot write to files in other mods ModFS
    if (!mod_fs_file_check_write(file, err)) {
        return false;
    }

    // binary only
    if (!mod_fs_file_check_file_type(file, false, true, "bool", err)) {
        return false;
    }

    return mod_fs_file_write_data<bool>(file, value, err);
}

static bool mod_fs_file_write_integer(struct ModFsFile *file, lua_Integer value, enum ModFsFileIntType intType, enum ModFsErrorCode *err) {
    if (!mod_fs_check_pointer(file, "ModFS file", err)) {
        return false;
    }

    // cannot write to files in other mods ModFS
    if (!mod_fs_file_check_write(file, err)) {
        return false;
    }

    // binary only
    if (!mod_fs_file_check_file_type(file, false, true, "integer", err)) {
        return false;
    }

    // check intType
    if (!mod_fs_file_check_parameter(file, intType, 0, INT_TYPE_MAX - 1, "intType", err)) {
        return false;
    }

    switch (intType) {
        case INT_TYPE_U8:  return mod_fs_file_write_data<u8>(file, value, err);
        case INT_TYPE_U16: return mod_fs_file_write_data<u16>(file, value, err);
        case INT_TYPE_U32: return mod_fs_file_write_data<u32>(file, value, err);
        case INT_TYPE_U64: return mod_fs_file_write_data<u64>(file, value, err);
        case INT_TYPE_S8:  return mod_fs_file_write_data<s8>(file, value, err);
        case INT_TYPE_S16: return mod_fs_file_write_data<s16>(file, value, err);
        case INT_TYPE_S32: return mod_fs_file_write_data<s32>(file, value, err);
        case INT_TYPE_S64: return mod_fs_file_write_data<s64>(file, value, err);
        default:           return false;
    }
}

static bool mod_fs_file_write_number(struct ModFsFile *file, lua_Number value, enum ModFsFileFloatType floatType, enum ModFsErrorCode *err) {
    if (!mod_fs_check_pointer(file, "ModFS file", err)) {
        return false;
    }

    // cannot write to files in other mods ModFS
    if (!mod_fs_file_check_write(file, err)) {
        return false;
    }

    // binary only
    if (!mod_fs_file_check_file_type(file, false, true, "number", err)) {
        return false;
    }

    // check floatType
    if (!mod_fs_file_check_parameter(file, floatType, 0, FLOAT_TYPE_MAX - 1, "floatType", err)) {
        return false;
    }

    switch (floatType) {
        case FLOAT_TYPE_F32: return mod_fs_file_write_data<f32>(file, value, err);
        case FLOAT_TYPE_F64: return mod_fs_file_write_data<f64>(file, value, err);
        default:             return false;
    }
}

static bool mod_fs_file_write_bytes(struct ModFsFile *file, ByteString bytestring, enum ModFsErrorCode *err) {
    if (!mod_fs_check_pointer(file, "ModFS file", err)) {
        return false;
    }

    // cannot write to files in other mods ModFS
    if (!mod_fs_file_check_write(file, err)) {
        return false;
    }

    // binary only
    if (!mod_fs_file_check_file_type(file, false, true, "bytes", err)) {
        return false;
    }

    u32 length = bytestring.length;
    if (mod_fs_file_write_resize_buffer(file, length, err)) {
        memcpy(file->data.bin + file->offset, bytestring.bytes, length);
        file->offset += length;
        return true;
    }
    return false;
}

static bool mod_fs_file_write_string(struct ModFsFile *file, const char *str, enum ModFsErrorCode *err) {
    if (!mod_fs_check_pointer(file, "ModFS file", err)) {
        return false;
    }

    // cannot write to files in other mods ModFS
    if (!mod_fs_file_check_write(file, err)) {
        return false;
    }

    u32 length = strlen(str) + (file->isText ? 0 : 1); // binary writes the NULL char
    if (mod_fs_file_write_resize_buffer(file, length, err)) {
        memcpy(file->data.bin + file->offset, str, length);
        file->offset += length;
        return true;
    }
    return false;
}

static bool mod_fs_file_write_line(struct ModFsFile *file, const char *str, enum ModFsErrorCode *err) {
    if (!mod_fs_check_pointer(file, "ModFS file", err)) {
        return false;
    }

    // cannot write to files in other mods ModFS
    if (!mod_fs_file_check_write(file, err)) {
        return false;
    }

    // text only
    if (!mod_fs_file_check_file_type(file, true, true, "line", err)) {
        return false;
    }

    u32 length = strlen(str);
    if (mod_fs_file_write_resize_buffer(file, length + 1, err)) { // '\n'
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

static bool mod_fs_file_seek(struct ModFsFile *file, s32 offset, enum ModFsFileSeek origin, enum ModFsErrorCode *err) {
    if (!mod_fs_check_pointer(file, "ModFS file", err)) {
        return false;
    }

    // check origin
    if (!mod_fs_file_check_parameter(file, origin, 0, FILE_SEEK_MAX - 1, "origin", err)) {
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

static bool mod_fs_file_rewind(struct ModFsFile *file, enum ModFsErrorCode *err) {
    if (!mod_fs_check_pointer(file, "ModFS file", err)) {
        return false;
    }

    file->offset = 0;
    return true;
}

static bool mod_fs_file_is_eof(struct ModFsFile *file, enum ModFsErrorCode *err) {
    if (!mod_fs_check_pointer(file, "ModFS file", err)) {
        return false;
    }

    return file->offset >= file->size;
}

static bool mod_fs_file_fill(struct ModFsFile *file, u8 byte, u32 length, enum ModFsErrorCode *err) {
    if (!mod_fs_check_pointer(file, "ModFS file", err)) {
        return false;
    }

    // cannot write to files in other mods ModFS
    if (!mod_fs_file_check_write(file, err)) {
        return false;
    }

    if (mod_fs_file_write_resize_buffer(file, length, err)) {
        memset(file->data.bin + file->offset, byte, length);
        file->offset += length;
        return true;
    }
    return false;
}

static bool mod_fs_file_erase(struct ModFsFile *file, u32 length, enum ModFsErrorCode *err) {
    if (!mod_fs_check_pointer(file, "ModFS file", err)) {
        return false;
    }

    // cannot erase data from files in other mods ModFS
    if (!mod_fs_file_check_write(file, err)) {
        return false;
    }

    length = MIN(length, file->size - file->offset);
    memmove(file->data.bin + file->offset, file->data.bin + file->offset + length, file->size - (file->offset + length));
    file->size -= length;
    file->modFs->totalSize -= length;
    return true;
}

static bool mod_fs_file_set_text_mode(struct ModFsFile *file, bool text, enum ModFsErrorCode *err) {
    if (!mod_fs_check_pointer(file, "ModFS file", err)) {
        return false;
    }

    file->isText = text;
    return true;
}

static bool mod_fs_file_set_public(struct ModFsFile *file, bool pub, enum ModFsErrorCode *err) {
    if (!mod_fs_check_pointer(file, "ModFS file", err)) {
        return false;
    }

    // cannot change public flag to files in other mods ModFS
    if (!mod_fs_file_check_write(file, err)) {
        return false;
    }

    file->isPublic = pub;
    return true;
}

static bool mod_fs_file_set_compression(struct ModFsFile *file, s32 level, enum ModFsErrorCode *err) {
    if (!mod_fs_check_pointer(file, "ModFS file", err)) {
        return false;
    }

    // cannot change compress level to files in other mods ModFS
    if (!mod_fs_file_check_write(file, err)) {
        return false;
    }

    // check level
    if (!mod_fs_file_check_parameter(file, level, MOD_FS_COMPRESSION_MIN, MOD_FS_COMPRESSION_MAX, "level", err)) {
        return false;
    }

    file->compressionLevel = level;
    return true;
}

//
// Errors
//

static void mod_fs_hide_errors(bool hide) {
    sModFsHideErrors = hide;
}

static enum ModFsErrorCode mod_fs_get_last_error_code() {
    return sModFsLastErrorCode;
}

static const char *mod_fs_get_last_error() {
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

static bool mod_fs_read_file_from_uri(const char *uri, void **buffer, u32 *length) {
    char modPath[SYS_MAX_PATH];
    char filepath[MOD_FS_MAX_PATH];
    if (!mod_fs_extract_modpath_and_filepath(uri, modPath, filepath)) {
        return false;
    }

    enum ModFsErrorCode err = MOD_FS_ERR_NONE;
    struct ModFs *modFs = modfs::mod_fs_get(modPath, &err);
    if (!modFs) {
        return false;
    }

    struct ModFsFile *file = modfs::mod_fs_get_file(modFs, filepath, &err);
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

static void mod_fs_shutdown() {

    // Close all ModFS
    for (auto &modFs : sModFsList) {
        mod_fs_destroy(modFs);
        mod_fs_free<struct ModFs>(modFs);
    }
    sModFsList.clear();

    // Reset error state
    sModFsLastErrorCode = MOD_FS_ERR_NONE;
    memset(sModFsLastError, 0, sizeof(sModFsLastError));
    sModFsHideErrors = false;
}

}

//
// C API
//

extern "C" {

bool mod_fs_exists(OPTIONAL const char *modPath, RET enum ModFsErrorCode *err) {
    mod_fs_reset_last_error();
    return modfs::mod_fs_exists(modPath, err);
}

struct ModFs *mod_fs_get(OPTIONAL const char *modPath, RET enum ModFsErrorCode *err) {
    mod_fs_reset_last_error();
    return modfs::mod_fs_get(modPath, err);
}

struct ModFs *mod_fs_reload(OPTIONAL const char *modPath, RET enum ModFsErrorCode *err) {
    mod_fs_reset_last_error();
    return modfs::mod_fs_reload(modPath, err);
}

struct ModFs *mod_fs_create(RET enum ModFsErrorCode *err) {
    mod_fs_reset_last_error();
    return modfs::mod_fs_create(err);
}

const char *mod_fs_get_filename(struct ModFs *modFs, u16 index, RET enum ModFsErrorCode *err) {
    mod_fs_reset_last_error();
    return modfs::mod_fs_get_filename(modFs, index, err);
}

struct ModFsFile *mod_fs_get_file(struct ModFs *modFs, const char *filepath, RET enum ModFsErrorCode *err) {
    mod_fs_reset_last_error();
    return modfs::mod_fs_get_file(modFs, filepath, err);
}

struct ModFsFile *mod_fs_create_file(struct ModFs *modFs, const char *filepath, bool text, RET enum ModFsErrorCode *err) {
    mod_fs_reset_last_error();
    return modfs::mod_fs_create_file(modFs, filepath, text, err);
}

bool mod_fs_move_file(struct ModFs *modFs, const char *oldpath, const char *newpath, bool overwriteExisting, RET enum ModFsErrorCode *err) {
    mod_fs_reset_last_error();
    return modfs::mod_fs_move_file(modFs, oldpath, newpath, overwriteExisting, err);
}

bool mod_fs_copy_file(struct ModFs *modFs, const char *srcpath, const char *dstpath, bool overwriteExisting, RET enum ModFsErrorCode *err) {
    mod_fs_reset_last_error();
    return modfs::mod_fs_copy_file(modFs, srcpath, dstpath, overwriteExisting, err);
}

bool mod_fs_delete_file(struct ModFs *modFs, const char *filepath, RET enum ModFsErrorCode *err) {
    mod_fs_reset_last_error();
    return modfs::mod_fs_delete_file(modFs, filepath, err);
}

bool mod_fs_clear(struct ModFs *modFs, RET enum ModFsErrorCode *err) {
    mod_fs_reset_last_error();
    return modfs::mod_fs_clear(modFs, err);
}

bool mod_fs_save(struct ModFs *modFs, RET enum ModFsErrorCode *err) {
    mod_fs_reset_last_error();
    return modfs::mod_fs_save(modFs, err);
}

bool mod_fs_delete(struct ModFs *modFs, RET enum ModFsErrorCode *err) {
    mod_fs_reset_last_error();
    return modfs::mod_fs_delete(modFs, err);
}

bool mod_fs_set_public(struct ModFs *modFs, bool pub, RET enum ModFsErrorCode *err) {
    mod_fs_reset_last_error();
    return modfs::mod_fs_set_public(modFs, pub, err);
}

bool mod_fs_file_read_bool(struct ModFsFile *file, RET enum ModFsErrorCode *err) {
    mod_fs_reset_last_error();
    return modfs::mod_fs_file_read_bool(file, err);
}

lua_Integer mod_fs_file_read_integer(struct ModFsFile *file, enum ModFsFileIntType intType, RET enum ModFsErrorCode *err) {
    mod_fs_reset_last_error();
    return modfs::mod_fs_file_read_integer(file, intType, err);
}

lua_Number mod_fs_file_read_number(struct ModFsFile *file, enum ModFsFileFloatType floatType, RET enum ModFsErrorCode *err) {
    mod_fs_reset_last_error();
    return modfs::mod_fs_file_read_number(file, floatType, err);
}

ByteString mod_fs_file_read_bytes(struct ModFsFile *file, u32 length, RET enum ModFsErrorCode *err) {
    mod_fs_reset_last_error();
    return modfs::mod_fs_file_read_bytes(file, length, err);
}

const char *mod_fs_file_read_string(struct ModFsFile *file, RET enum ModFsErrorCode *err) {
    mod_fs_reset_last_error();
    return modfs::mod_fs_file_read_string(file, err);
}

const char *mod_fs_file_read_line(struct ModFsFile *file, RET enum ModFsErrorCode *err) {
    mod_fs_reset_last_error();
    return modfs::mod_fs_file_read_line(file, err);
}

bool mod_fs_file_write_bool(struct ModFsFile *file, bool value, RET enum ModFsErrorCode *err) {
    mod_fs_reset_last_error();
    return modfs::mod_fs_file_write_bool(file, value, err);
}

bool mod_fs_file_write_integer(struct ModFsFile *file, lua_Integer value, enum ModFsFileIntType intType, RET enum ModFsErrorCode *err) {
    mod_fs_reset_last_error();
    return modfs::mod_fs_file_write_integer(file, value, intType, err);
}

bool mod_fs_file_write_number(struct ModFsFile *file, lua_Number value, enum ModFsFileFloatType floatType, RET enum ModFsErrorCode *err) {
    mod_fs_reset_last_error();
    return modfs::mod_fs_file_write_number(file, value, floatType, err);
}

bool mod_fs_file_write_bytes(struct ModFsFile *file, ByteString bytestring, RET enum ModFsErrorCode *err) {
    mod_fs_reset_last_error();
    return modfs::mod_fs_file_write_bytes(file, bytestring, err);
}

bool mod_fs_file_write_string(struct ModFsFile *file, const char *str, RET enum ModFsErrorCode *err) {
    mod_fs_reset_last_error();
    return modfs::mod_fs_file_write_string(file, str, err);
}

bool mod_fs_file_write_line(struct ModFsFile *file, const char *str, RET enum ModFsErrorCode *err) {
    mod_fs_reset_last_error();
    return modfs::mod_fs_file_write_line(file, str, err);
}

bool mod_fs_file_seek(struct ModFsFile *file, s32 offset, enum ModFsFileSeek origin, RET enum ModFsErrorCode *err) {
    mod_fs_reset_last_error();
    return modfs::mod_fs_file_seek(file, offset, origin, err);
}

bool mod_fs_file_rewind(struct ModFsFile *file, RET enum ModFsErrorCode *err) {
    mod_fs_reset_last_error();
    return modfs::mod_fs_file_rewind(file, err);
}

bool mod_fs_file_is_eof(struct ModFsFile *file, RET enum ModFsErrorCode *err) {
    mod_fs_reset_last_error();
    return modfs::mod_fs_file_is_eof(file, err);
}

bool mod_fs_file_fill(struct ModFsFile *file, u8 byte, u32 length, RET enum ModFsErrorCode *err) {
    mod_fs_reset_last_error();
    return modfs::mod_fs_file_fill(file, byte, length, err);
}

bool mod_fs_file_erase(struct ModFsFile *file, u32 length, RET enum ModFsErrorCode *err) {
    mod_fs_reset_last_error();
    return modfs::mod_fs_file_erase(file, length, err);
}

bool mod_fs_file_set_text_mode(struct ModFsFile *file, bool text, RET enum ModFsErrorCode *err) {
    mod_fs_reset_last_error();
    return modfs::mod_fs_file_set_text_mode(file, text, err);
}

bool mod_fs_file_set_public(struct ModFsFile *file, bool pub, RET enum ModFsErrorCode *err) {
    mod_fs_reset_last_error();
    return modfs::mod_fs_file_set_public(file, pub, err);
}

bool mod_fs_file_set_compression(struct ModFsFile *file, s32 level, RET enum ModFsErrorCode *err) {
    mod_fs_reset_last_error();
    return modfs::mod_fs_file_set_compression(file, level, err);
}

void mod_fs_hide_errors(bool hide) {
    return modfs::mod_fs_hide_errors(hide);
}

enum ModFsErrorCode mod_fs_get_last_error_code() {
    return modfs::mod_fs_get_last_error_code();
}

const char *mod_fs_get_last_error() {
    return modfs::mod_fs_get_last_error();
}

bool mod_fs_read_file_from_uri(const char *uri, void **buffer, u32 *length) {
    return modfs::mod_fs_read_file_from_uri(uri, buffer, length);
}

void mod_fs_shutdown() {
    return modfs::mod_fs_shutdown();
}

}
