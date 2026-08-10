#include "smlua_fs_utils.h"
#include "pc/mods/mods_utils.h"
#include "pc/lua/smlua.h"
#include "pc/fs/fmem.h"

static char *sReadBuffer = NULL;
static size_t sReadBufferSize = 0;

const char *smlua_fs_utils_mod_file_read(struct Mod *mod, const char *fileName) {
    if (path_ends_with(fileName, PATH_SEPARATOR) || path_ends_with(fileName, PATH_SEPARATOR_ALT)) {
        LOG_LUA_LINE("Cannot read '%s' because it is a directory", fileName);
        return NULL;
    }

    bool activeFileInMod = (gLuaActiveModFile >= &mod->files[0] && gLuaActiveModFile < &mod->files[mod->fileCount]);

    
    char baseDir[SYS_MAX_PATH] = { 0 };
    if (activeFileInMod && strlen(gLuaActiveModFile->relativePath) > 0) {
        snprintf(baseDir, SYS_MAX_PATH, "%s", gLuaActiveModFile->relativePath);

        char* lastSeparator = strrchr(baseDir, *PATH_SEPARATOR);
        char* lastAltSeparator = strrchr(baseDir, *PATH_SEPARATOR_ALT);
        if (lastAltSeparator > lastSeparator) lastSeparator = lastAltSeparator;

        if (lastSeparator) {
            *lastSeparator = '\0';
        } else {
            baseDir[0] = '\0';
        }
    }
    
    char targetPath[SYS_MAX_PATH] = { 0 };
    resolve_relative_path(baseDir, fileName, targetPath);

    struct ModFile* file = NULL;
    for (int i = 0; i < mod->fileCount; i++) {
        char normalizedModPath[SYS_MAX_PATH] = { 0 };
        snprintf(normalizedModPath, SYS_MAX_PATH, "%s", mod->files[i].relativePath);
        normalize_path(normalizedModPath);

        if (!strcmp(normalizedModPath, targetPath) || !strcmp(normalizedModPath, fileName)) {
            file = &mod->files[i];
            break;
        }
    }

    if (!file) {
        LOG_LUA_LINE("File '%s' not found in '%s'", fileName, mod->name);
        return NULL;
    }

    FILE* fp = file->fp;
    bool inMemory = false;
    bool needsClose = false;

    if (!fp && file->cachedPath) {
        fp = fopen(file->cachedPath, "rb");
        if (!fp) {
            fp = f_open_r(file->cachedPath);
            inMemory = true;
        }
        needsClose = true;
    }

    if (!fp) {
        LOG_LUA_LINE("Failed to open file '%s'", file->relativePath);
        return NULL;
    }

    size_t fileSize = file->size;
    if (sReadBufferSize < fileSize + 1) {
        sReadBufferSize = fileSize + 1;
        sReadBuffer = realloc(sReadBuffer, sReadBufferSize);
    }

    if (!sReadBuffer) {
        if (needsClose) {
            if (!inMemory) {
                fclose(fp);
            } else {
                f_close(fp);
            }
        }
        LOG_LUA_LINE("Ran out of memory while reading '%s'", file->relativePath);
        return NULL;
    }

    if (needsClose) {
        if (!inMemory) {
            fseek(fp, 0, SEEK_SET);
        } else {
            f_seek(fp, 0, SEEK_SET);
        }
    }

    size_t bytesRead;
    if (!inMemory) {
        bytesRead = fread(sReadBuffer, 1, fileSize, fp);
    } else {
        bytesRead = f_read(sReadBuffer, 1, fileSize, fp);
    }
    sReadBuffer[bytesRead] = '\0';

    if (needsClose) {
        if (!inMemory) {
            fclose(fp);
        } else {
            f_close(fp);
        }
    }

    return sReadBuffer;
}

bool smlua_fs_utils_mod_file_exists(const char *filename) {
    if (gLuaActiveMod == NULL) { return false; }

    char normPath[SYS_MAX_PATH] = { 0 };
    char normRelative[SYS_MAX_PATH] = { 0 };

    if (snprintf(normPath, sizeof(normPath), "%s", filename) < 0) {
        LOG_ERROR("Failed to copy filename for normalization: %s", filename);
    }

    normalize_path(normPath);

    for (s32 i = 0; i < gLuaActiveMod->fileCount; i++) {
        struct ModFile *file = &gLuaActiveMod->files[i];
        strcpy(normRelative, file->relativePath);
        normalize_path(normRelative);
        if (!strcmp(normRelative, normPath)) {
            return true;
        }
    }

    return false;
}

LuaTable smlua_fs_utils_mod_files_get(struct Mod *mod, OPTIONAL const char *subDirectory, OPTIONAL bool relative) {
    if (!mod) {
        struct lua_State *L = gLuaState;
        if (L) {
            lua_newtable(L);
            return smlua_to_lua_table(L, -1);
        }
        return 0;
    }

    char normalizedSubDir[SYS_MAX_PATH] = { 0 };
    snprintf(normalizedSubDir, SYS_MAX_PATH, "%s", subDirectory ? subDirectory : "");
    normalize_path(normalizedSubDir);

    size_t subDirLen = strlen(normalizedSubDir);
    if (subDirLen > 0 && subDirLen + 1 < SYS_MAX_PATH && normalizedSubDir[subDirLen - 1] != *PATH_SEPARATOR) {
        strcat(normalizedSubDir, PATH_SEPARATOR);
        subDirLen = strlen(normalizedSubDir);
    }

    struct lua_State *L = gLuaState;
    if (!L) { return 0; }

    LUA_STACK_CHECK_BEGIN_NUM(L, 1);

    lua_newtable(L);

    int luaTableIndex = 1;
    for (int i = 0; i < mod->fileCount; i++) {
        struct ModFile *file = &mod->files[i];
        char normalizedPath[SYS_MAX_PATH] = { 0 };
        if (snprintf(normalizedPath, SYS_MAX_PATH, "%s", file->relativePath) < 0) {
            LOG_ERROR("Failed to copy relativePath for normalization: %s", file->relativePath);
            continue;
        }
        normalize_path(normalizedPath);

        if (strncmp(normalizedPath, normalizedSubDir, subDirLen) == 0) {
            const char *path = relative ? (normalizedPath + subDirLen) : normalizedPath;
            lua_pushstring(L, path);
            lua_rawseti(L, -2, luaTableIndex++);
        }
    }

    LUA_STACK_CHECK_END(L);

    return smlua_to_lua_table(L, -1);
}
