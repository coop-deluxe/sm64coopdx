#include "PR/ultratypes.h"
#include "types.h"
#include "pc/platform.h"
#include "pc/utils/miniz/miniz.h"
#include "pc/debuglog.h"
#include "data/dynos.c.h"
#include "pc/djui/djui_language.h"
#include "pc/djui/djui_popup.h"
#include "mods.h"
#include "mods_utils.h"

static bool mod_import_lua(char* src) {
    char dst[SYS_MAX_PATH] = { 0 };
    if (!concat_path(dst, (char*)fs_get_write_path(MOD_DIRECTORY), path_basename(src))) {
        LOG_ERROR("Failed to concat path for lua mod import");
        return false;
    }

    FILE* fin = fopen(src, "rb");
    if (fin == NULL) {
        LOG_ERROR("Failed to open src path for lua mod import");
        return false;
    }

    FILE* fout = fopen(dst, "wb");
    if (fout == NULL) {
        LOG_ERROR("Failed to open dst path for lua mod import");
        fclose(fin);
        return false;
    }

    size_t rbytes;
    size_t wbytes;
    unsigned char buff[8192];
    do {
        rbytes = fread(buff, 1, sizeof(buff), fin);
        if (rbytes > 0) {
            wbytes = fwrite(buff, 1, rbytes, fout);
        } else {
            wbytes = 0;
        }
    } while ((rbytes > 0) && (rbytes == wbytes));

    fclose(fout);
    fclose(fin);

    if (wbytes) {
        LOG_ERROR("Write error on lua mod import");
        return false;
    }

    LOG_INFO("Imported lua mod: '%s' -> '%s'", src, dst);

    return true;
}

static bool mod_import_palette(char* src) {
    const char* palettesDirectory = fs_get_write_path(PALETTES_DIRECTORY);
    fs_sys_mkdir(palettesDirectory);

    char dst[SYS_MAX_PATH] = { 0 };
    if (!concat_path(dst, (char*)palettesDirectory, path_basename(src))) {
        LOG_ERROR("Failed to concat path for palette ini import");
        return false;
    }

    FILE* fin = fopen(src, "rb");
    if (fin == NULL) {
        LOG_ERROR("Failed to open src path for palette ini import");
        return false;
    }

    FILE* fout = fopen(dst, "wb");
    if (fout == NULL) {
        LOG_ERROR("Failed to open dst path for palette ini import");
        fclose(fin);
        return false;
    }

    size_t rbytes;
    size_t wbytes;
    unsigned char buff[8192];
    do {
        rbytes = fread(buff, 1, sizeof(buff), fin);
        if (rbytes > 0) {
            wbytes = fwrite(buff, 1, rbytes, fout);
        } else {
            wbytes = 0;
        }
    } while ((rbytes > 0) && (rbytes == wbytes));

    fclose(fout);
    fclose(fin);

    if (wbytes) {
        LOG_ERROR("Write error on palette ini import");
        return false;
    }

    LOG_INFO("Imported palette ini: '%s' -> '%s'", src, dst);

    return true;
}

static bool mod_import_zip(char* path, bool* isLua, bool* isDynos) {
    LOG_INFO("Importing zip mod: %s", path);

    char luaPath[SYS_MAX_PATH] = { 0 };
    mz_zip_archive zip_archive = { 0 };
    mz_bool status = mz_zip_reader_init_file(&zip_archive, path, 0);
    if (!status) {
        LOG_ERROR("mz_zip_reader_init_file() failed!");
        return false;
    }

    // Figure out if its a dynos pack or a mod
    *isLua = false;
    *isDynos = false;
    for (int i = 0; i < (int)mz_zip_reader_get_num_files(&zip_archive); i++) {
        mz_zip_archive_file_stat file_stat;
        if (!mz_zip_reader_file_stat(&zip_archive, i, &file_stat)) {
            LOG_ERROR("mz_zip_reader_file_stat() failed!");
            mz_zip_reader_end(&zip_archive);
            return false;
        }

        if (str_ends_with(file_stat.m_filename, ".lua") || str_ends_with(file_stat.m_filename, ".luac")) {
            path_get_folder(file_stat.m_filename, luaPath);
            *isLua = true;
            break;
        } else if (str_ends_with(file_stat.m_filename, ".tex")) {
            *isDynos = true;
        } else if (str_ends_with(file_stat.m_filename, ".png")) {
            *isDynos = true;
        } else if (str_ends_with(file_stat.m_filename, ".bin")) {
            *isDynos = true;
        }
    }

    // Figure out dst directory
    char dstDirectory[SYS_MAX_PATH] = { 0 };
    char dst[SYS_MAX_PATH] = { 0 };
    if (*isLua) {
        snprintf(dstDirectory, SYS_MAX_PATH, "%s", (char*)fs_get_write_path(MOD_DIRECTORY));
    } else if (*isDynos) {
        char* dynosPath = (char*)fs_get_write_path(DYNOS_RES_FOLDER);
        if (!fs_sys_dir_exists(dynosPath)) {
            fs_sys_mkdir(dynosPath);
        }
        snprintf(dstDirectory, SYS_MAX_PATH, "%s", (char*)fs_get_write_path(DYNOS_PACKS_FOLDER));
    } else {
        LOG_ERROR("Could not figure out what type of mod this is");
        mz_zip_reader_end(&zip_archive);
        return false;
    }

    // create mod/dynos path if it doesn't exist
    if (!fs_sys_dir_exists(dstDirectory)) {
        fs_sys_mkdir(dstDirectory);
    }

    // erase and create lua path
    if (*isLua && strlen(luaPath) > 0) {
        if (!concat_path(dst, dstDirectory, luaPath)) {
            LOG_ERROR("Failed to concat path for base lua directory");
            mz_zip_reader_end(&zip_archive);
            return false;
        }
        if (fs_sys_dir_exists(dst)) {
            mods_delete_folder(dst);
        }
        if (!fs_sys_mkdir(dst)) {
            LOG_ERROR("Failed to mkdir for base lua directory");
            mz_zip_reader_end(&zip_archive);
            return false;
        }
    }

    // Extract the archive
    for (int i = 0; i < (int)mz_zip_reader_get_num_files(&zip_archive); i++) {
        mz_zip_archive_file_stat file_stat;
        if (!mz_zip_reader_file_stat(&zip_archive, i, &file_stat)) {
            LOG_ERROR("mz_zip_reader_file_stat() failed!");
            mz_zip_reader_end(&zip_archive);
            return false;
        }

        // Build dst path
        if (!concat_path(dst, dstDirectory, file_stat.m_filename)) {
            LOG_ERROR("Failed to concat path for zip mod import");
            mz_zip_reader_end(&zip_archive);
            return false;
        }

        LOG_INFO("Filename: \"%s\", Comment: \"%s\", Uncompressed size: %u, Compressed size: %u, Is Dir: %u", file_stat.m_filename, file_stat.m_comment, (u32)file_stat.m_uncomp_size, (u32)file_stat.m_comp_size, mz_zip_reader_is_file_a_directory(&zip_archive, i));

        // If it's a directory, make it
        if (mz_zip_reader_is_file_a_directory(&zip_archive, i)) {
            // Remove the directory
            if (fs_sys_dir_exists(dst)) {
                mods_delete_folder(dst);
            }

            if (!fs_sys_mkdir(dst)) {
                LOG_ERROR("Failed to mkdir for zip mod import");
                mz_zip_reader_end(&zip_archive);
                return false;
            }
            continue;
        }

        // Try to extract all the files to the heap.
        size_t uncompSize = 0;
        const char* p = mz_zip_reader_extract_file_to_heap(&zip_archive, file_stat.m_filename, &uncompSize, 0);
        if (!p) {
            LOG_ERROR("mz_zip_reader_extract_file_to_heap() failed!");
            mz_zip_reader_end(&zip_archive);
            return false;
        }

        // Make sure the extraction really succeeded.
        if (uncompSize != file_stat.m_uncomp_size) {
            LOG_ERROR("mz_zip_reader_extract_file_to_heap() failed to extract the proper data");
            mz_free((void*)p);
            mz_zip_reader_end(&zip_archive);
            return false;
        }

        // Write the data
        FILE* fout = fopen(dst, "wb");
        if (fout == NULL) {
            LOG_ERROR("Failed to open dst path for zip mod import");
            mz_free((void*)p);
            mz_zip_reader_end(&zip_archive);
            return false;
        }

        size_t wbytes = fwrite(p, 1, uncompSize, fout);
        fclose(fout);

        if (wbytes != uncompSize) {
            LOG_ERROR("Write error on zip mod import: %u != %u", (u32)wbytes, (u32)uncompSize);
        }

        LOG_INFO("Successfully extracted file \"%s\", size %u", file_stat.m_filename, (u32)uncompSize);

        // We're done.
        mz_free((void*)p);
    }
    // Close the archive, freeing any resources it was using
    mz_zip_reader_end(&zip_archive);
    return true;
}

bool mod_import_file(char* path) {
    bool isLua = false;
    bool isDynos = false;
    bool isPalette = false;
    bool ret = false;

    if (gNetworkType != NT_NONE && !str_ends_with(path, ".ini")) {
        djui_popup_create(DLANG(NOTIF, IMPORT_FAIL_INGAME), 2);
        return false;
    }

    if (str_ends_with(path, ".lua") || str_ends_with(path, ".luac")) {
        isLua = true;
        ret = mod_import_lua(path);
    } else if (str_ends_with(path, ".ini")) {
        isPalette = true;
        ret = mod_import_palette(path);
    } else if (str_ends_with(path, ".zip")) {
        ret = mod_import_zip(path, &isLua, &isDynos);
    }

    char msg[SYS_MAX_PATH] = { 0 };
    char* basename = path_basename(path);

    if (ret) {
        if (isLua) {
            mods_refresh_local();
            djui_language_replace(DLANG(NOTIF, IMPORT_MOD_SUCCESS), msg, SYS_MAX_PATH, '@', basename);
            djui_popup_create(msg, 2);
        } else if (isDynos) {
            dynos_gfx_init();
            djui_language_replace(DLANG(NOTIF, IMPORT_DYNOS_SUCCESS), msg, SYS_MAX_PATH, '@', basename);
            djui_popup_create(msg, 2);
        } else if (isPalette) {
            djui_language_replace(DLANG(NOTIF, IMPORT_PALETTE_SUCCESS), msg, SYS_MAX_PATH, '@', basename);
            djui_popup_create(msg, 2);
        }
    } else {
        djui_language_replace(DLANG(NOTIF, IMPORT_FAIL), msg, SYS_MAX_PATH, '@', basename);
        djui_popup_create(msg, 2);
    }

    return ret;
}