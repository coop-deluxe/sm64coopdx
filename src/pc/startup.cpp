#include <fstream>
#include <iostream>
#include <vector>
#include <filesystem>

extern "C" {
#include "platform.h"
#include "mods/mods_utils.h" // for str_ends_with
#include "mods/mod_cache.h"  // for md5 hashing
#include "loading.h"
}

namespace fs = std::filesystem;

bool gUserFolderCopied = false;
bool gRomIsValid = false;
char gRomFilename[255] = "";

struct VanillaMD5 {
    const char *localizationName;
    const char *md5;
};

// lookup table for vanilla sm64 roms
static struct VanillaMD5 sVanillaMD5[] = {
    // { "eu", "45676429ef6b90e65b517129b700308e" },
    // { "jp", "85d61f5525af708c9f1e84dce6dc10e9" },
    // { "sh", "2d727c3278aa232d94f2fb45aec4d303" },
    { "us", "20b854b239203baf6c961b850a4a51a2" },
    { NULL, NULL },
};

static void copy_old_user_folder() {
    char* oldpath = (char*)sys_old_user_path();
    char* newpath = (char*)sys_user_path();

    if (fs::exists(oldpath) && (fs::is_empty(newpath) || !fs::exists(newpath))) {
        fs::copy(oldpath, newpath);
        gUserFolderCopied = true;
    }
}

static bool is_rom_valid(const std::string romPath) {
    u8 dataHash[16] = { 0 };
    mod_cache_md5(romPath.c_str(), dataHash);

    std::stringstream ss;
    for (int i = 0; i < 16; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(dataHash[i]);
    }

    bool foundHash = false;
    for (struct VanillaMD5 *md5 = sVanillaMD5; md5->localizationName != NULL; md5++) {
        if (md5->md5 == ss.str()) {
            std::string destPath = sys_user_path() + std::string("/baserom.") + md5->localizationName + ".z64";

            // Copy the rom to the user path
            if (romPath != destPath && !std::filesystem::exists(std::filesystem::path(destPath))) {
                std::filesystem::copy_file(
                    std::filesystem::path(romPath),
                    std::filesystem::path(destPath)
                );
            }

            snprintf(gRomFilename, 255, "%s", destPath.c_str()); // Load the copied rom
            gRomIsValid = true;
            foundHash = true;
            break;
        }
    }

    return foundHash;
}

inline static bool scan_path_for_rom(const char *dir) {
    for (const auto &entry: std::filesystem::directory_iterator(dir)) {
        std::string path = entry.path().generic_string();
        if (str_ends_with(path.c_str(), ".z64")) {
            if (is_rom_valid(path)) { return true; }
        }
    }
    return false;
}

extern "C" {
void old_user_folder_handler(void) {
    copy_old_user_folder();
}

bool main_rom_handler(void) {
    if (scan_path_for_rom(sys_user_path())) { return true; }
    scan_path_for_rom(sys_exe_path());
    return gRomIsValid;
}

void rom_on_drop_file(const char *path) {
    static bool hasDroppedInvalidFile = false;
    if (strlen(path) > 0) {
        if (!is_rom_valid(path) && !hasDroppedInvalidFile) {
            hasDroppedInvalidFile = true;
            strcat(gCurrLoadingSegment.str, "\n\\#ffc000\\The file you last dropped was not a valid, vanilla SM64 rom.");
        }
    }
}
}
