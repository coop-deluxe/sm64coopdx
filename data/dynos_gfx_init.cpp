#include "dynos.cpp.h"
#include "pc/loading.h"

void DynOS_Gfx_GeneratePacks(const char* directory) {
    LOADING_SCREEN_MUTEX(snprintf(gCurrLoadingSegment.str, 256, "Generating DynOS Packs In Path:\n\\#808080\\%s", directory));

    DIR *modsDir = opendir(directory);
    if (!modsDir) { return; }

    struct dirent *dir = NULL;
    DIR* d = opendir(directory);
    u32 pathCount = 0;
    while ((dir = readdir(d)) != NULL) pathCount++;
    closedir(d);

    for (u32 i = 0; (dir = readdir(modsDir)) != NULL; ++i) {
        // Skip . and ..
        if (SysPath(dir->d_name) == ".") continue;
        if (SysPath(dir->d_name) == "..") continue;

        // If pack folder exists, generate bins
        SysPath _LevelPackFolder = fstring("%s/%s/levels", directory, dir->d_name);
        if (fs_sys_dir_exists(_LevelPackFolder.c_str())) {
            DynOS_Lvl_GeneratePack(_LevelPackFolder);
        }

        SysPath _ActorPackFolder = fstring("%s/%s/actors", directory, dir->d_name);
        if (fs_sys_dir_exists(_ActorPackFolder.c_str())) {
            DynOS_Actor_GeneratePack(_ActorPackFolder);
        }

        SysPath _BehaviorPackFolder = fstring("%s/%s/data", directory, dir->d_name);
        if (fs_sys_dir_exists(_BehaviorPackFolder.c_str())) {
            DynOS_Bhv_GeneratePack(_BehaviorPackFolder);
        }

        SysPath _TexturePackFolder = fstring("%s/%s", directory, dir->d_name);
        SysPath _TexturePackOutputFolder = fstring("%s/%s/textures", directory, dir->d_name);
        if (fs_sys_dir_exists(_TexturePackFolder.c_str())) {
            DynOS_Tex_GeneratePack(_TexturePackFolder, _TexturePackOutputFolder, true);
        }

        LOADING_SCREEN_MUTEX(gCurrLoadingSegment.percentage = (f32) i / (f32) pathCount);
    }

    closedir(modsDir);
}

static void ScanPacksFolder(SysPath _DynosPacksFolder) {
    DIR *_DynosPacksDir = opendir(_DynosPacksFolder.c_str());
    if (_DynosPacksDir) {
        struct dirent *_DynosPacksEnt = NULL;
        while ((_DynosPacksEnt = readdir(_DynosPacksDir)) != NULL) {

            // Skip . and ..
            if (SysPath(_DynosPacksEnt->d_name) == ".") continue;
            if (SysPath(_DynosPacksEnt->d_name) == "..") continue;

            // If pack folder exists, add it to the pack list
            SysPath _PackFolder = fstring("%s/%s", _DynosPacksFolder.c_str(), _DynosPacksEnt->d_name);
            if (fs_sys_dir_exists(_PackFolder.c_str())) {
                LOADING_SCREEN_MUTEX(snprintf(gCurrLoadingSegment.str, 256, "Generating DynOS Pack:\n\\#808080\\%s", _PackFolder.c_str()));
                DynOS_Pack_Add(_PackFolder);
                DynOS_Actor_GeneratePack(_PackFolder);
                DynOS_Tex_GeneratePack(_PackFolder, _PackFolder, false);
            }
        }
        closedir(_DynosPacksDir);
    }
}

void DynOS_Gfx_Init() {
    // Scan the DynOS packs folder
    SysPath _DynosPacksFolder = fstring("%s/%s", DYNOS_EXE_FOLDER, DYNOS_PACKS_FOLDER);
    ScanPacksFolder(_DynosPacksFolder);

    // Scan the user path folder
    SysPath _DynosPacksUserFolder = fstring("%s%s", DYNOS_USER_FOLDER, DYNOS_PACKS_FOLDER);
    ScanPacksFolder(_DynosPacksUserFolder);
}
