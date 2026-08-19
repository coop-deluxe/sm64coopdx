#include "smlua_fs_utils.h"
#include "pc/mods/mods_utils.h"
#include "pc/lua/smlua.h"
#include "pc/lua/smlua_utils.h"
#include "pc/fs/fmem.h"

ByteString mod_file_read(struct Mod *mod, const char *fileName) {
    ByteString byteString = { NULL, 0 };
    if (!mod) {
        LOG_LUA_LINE("Attempted to read a nil mod");
        return byteString;
    }

    if (path_ends_with(fileName, PATH_SEPARATOR) || path_ends_with(fileName, PATH_SEPARATOR_ALT)) {
        LOG_LUA_LINE("Cannot read '%s' because it is a directory", fileName);
        return byteString;
    }

    bool activeFileInMod = gLuaActiveMod == mod && gLuaActiveModFile != NULL;

    char baseDir[SYS_MAX_PATH] = { 0 };
    if (activeFileInMod && strlen(gLuaActiveModFile->relativePath) > 0) {
        snprintf(baseDir, SYS_MAX_PATH, "%s", gLuaActiveModFile->relativePath);

        char* lastSeparator = strrchr(baseDir, *PATH_SEPARATOR);
        char* lastAltSeparator = strrchr(baseDir, *PATH_SEPARATOR_ALT);

        if (lastAltSeparator != NULL && (lastSeparator == NULL || lastAltSeparator > lastSeparator)) {
            lastSeparator = lastAltSeparator;
        }

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
        return byteString;
    }

    static char *sReadBuffer = NULL;
    static size_t sReadBufferSize = 0;
    FILE* fp = file->fp;

    size_t fileSize = file->size;
    if (sReadBufferSize < fileSize) {
        char *newBuffer = realloc(sReadBuffer, fileSize);
        if (newBuffer) {
            sReadBuffer = newBuffer;
            sReadBufferSize = fileSize;
        } else {
            LOG_LUA_LINE("Could not set read buffer for '%s'", file->relativePath)
            return byteString;
        }
    }

    bool needsClose = false;

    if (!fp && file->cachedPath) {
        fp = f_open_r(file->cachedPath);
        needsClose = true;
    }

    if (!fp) {
        LOG_LUA_LINE("Failed to open file '%s'", file->relativePath);
        return byteString;
    }

    if (!sReadBuffer) {
        if (needsClose) {
            f_close(fp);
        }
        LOG_LUA_LINE("Ran out of memory while reading '%s'", file->relativePath);
        return byteString;
    }

    f_rewind(fp);

    size_t bytesRead;
    bytesRead = f_read(sReadBuffer, 1, fileSize, fp);

    if (needsClose) {
        f_close(fp);
    }

    if (bytesRead != fileSize) {
        LOG_LUA_LINE("Filesize mismatched with the amount of bytes read for file '%s'", file->relativePath);
        return byteString;
    }

    byteString.bytes = sReadBuffer;
    byteString.length = bytesRead;

    return byteString;
}

bool mod_file_exists(const char *filename) {
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

LuaTable mod_files_get(struct Mod *mod, OPTIONAL const char *subDirectory, OPTIONAL bool relative) {
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
