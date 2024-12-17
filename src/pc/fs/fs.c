#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifndef DOCKERBUILD
#include <dirent.h>
#endif
#include <ctype.h>
#ifdef _WIN32
#include <direct.h>
#include <fileapi.h>
#endif

#include "macros.h"
#include "../platform.h"
#include "fs.h"

char fs_writepath[SYS_MAX_PATH] = "";

struct fs_dir_s {
    void *pack;
    const char *realpath;
    fs_packtype_t *packer;
    struct fs_dir_s *prev, *next;
};

extern fs_packtype_t fs_packtype_dir;

static fs_packtype_t *fs_packers[] = {
    &fs_packtype_dir
};

static fs_dir_t *fs_searchpaths = NULL;

static inline fs_dir_t *fs_find_dir(const char *realpath) {
    for (fs_dir_t *dir = fs_searchpaths; dir; dir = dir->next)
        if (!sys_strcasecmp(realpath, dir->realpath))
            return dir;
    return NULL;
}

bool fs_init(const char *writepath) {
    char buf[SYS_MAX_PATH];

    // expand and remember the write path
    strncpy(fs_writepath, fs_convert_path(buf, sizeof(buf), writepath), sizeof(fs_writepath));
    fs_writepath[sizeof(fs_writepath)-1] = 0;
#ifdef DEVELOPMENT
    printf("FS: writepath set to `%s`\n", fs_writepath);
#endif

    // we shall not progress any further if the path is inaccessible
    if (('\0' == fs_writepath[0]) || !fs_sys_dir_exists(fs_writepath)) {
        sys_fatal("Could not access the User Preferences directory.");
    }

    fs_mount(fs_writepath);

    return true;
}

bool fs_mount(const char *realpath) {
    if (fs_find_dir(realpath))
        return false; // already mounted

    const char *ext = sys_file_extension(realpath);
    void *pack = NULL;
    fs_packtype_t *packer = NULL;
    bool tried = false;
    for (uint32_t i = 0; i < sizeof(fs_packers) / sizeof(fs_packers[0]); ++i) {
        if (ext && sys_strcasecmp(ext, fs_packers[i]->extension))
            continue;
        tried = true;
        pack = fs_packers[i]->mount(realpath);
        if (pack) {
            packer = fs_packers[i];
            break;
        }
    }

    if (!pack || !packer) {
        if (tried)
            fprintf(stderr, "FS: could not mount '%s'\n", realpath);
        return false;
    }

    fs_dir_t *dir = calloc(1, sizeof(fs_dir_t));
    if (!dir) {
        packer->unmount(pack);
        return false;
    }

    dir->pack = pack;
    dir->realpath = sys_strdup(realpath);
    dir->packer = packer;
    dir->prev = NULL;
    dir->next = fs_searchpaths;
    if (fs_searchpaths)
        fs_searchpaths->prev = dir;
    fs_searchpaths = dir;

#ifdef DEVELOPMENT
    printf("FS: mounting '%s'\n", realpath);
#endif

    return true;
}

fs_walk_result_t fs_walk(const char *base, walk_fn_t walkfn, void *user, const bool recur) {
    bool found = false;
    for (fs_dir_t *dir = fs_searchpaths; dir; dir = dir->next) {
        fs_walk_result_t res = dir->packer->walk(dir->pack, base, walkfn, user, recur);
        if (res == FS_WALK_INTERRUPTED)
            return res;
        if (res != FS_WALK_NOTFOUND)
            found = true;
    }
    return found ? FS_WALK_SUCCESS : FS_WALK_NOTFOUND;
}

fs_file_t *fs_open(const char *vpath) {
    for (fs_dir_t *dir = fs_searchpaths; dir; dir = dir->next) {
        fs_file_t *f = dir->packer->open(dir->pack, vpath);
        if (f) {
            f->parent = dir;
            return f;
        }
    }
    return NULL;
}

void fs_close(fs_file_t *file) {
    if (!file) return;
    file->parent->packer->close(file->parent->pack, file);
}

int64_t fs_read(fs_file_t *file, void *buf, const uint64_t size) {
    if (!file) return -1;
    return file->parent->packer->read(file->parent->pack, file, buf, size);
}

int64_t fs_size(fs_file_t *file) {
    if (!file) return -1;
    return file->parent->packer->size(file->parent->pack, file);
}

bool fs_eof(fs_file_t *file) {
    if (!file) return true;
    return file->parent->packer->eof(file->parent->pack, file);
}

struct matchdata_s {
    const char *prefix;
    size_t prefix_len;
    char *dst;
    size_t dst_len;
};

static bool enumerate_walk(void *user, const char *path) {
    fs_pathlist_t *data = (fs_pathlist_t *)user;

    if (data->listcap == data->numpaths) {
        data->listcap *= 2;
        char **newpaths = realloc(data->paths, data->listcap * sizeof(char *));
        if (!newpaths) return false;
        data->paths = newpaths;
    }

    data->paths[data->numpaths++] = sys_strdup(path);
    return true;
}

fs_pathlist_t fs_enumerate(const char *base, const bool recur) {
    char **paths = malloc(sizeof(char *) * 32);
    fs_pathlist_t pathlist = { paths, 0, 32 };

    if (!paths) return pathlist;

    if (fs_walk(base, enumerate_walk, &pathlist, recur) == FS_WALK_INTERRUPTED)
        fs_pathlist_free(&pathlist);

    return pathlist;
}

void fs_pathlist_free(fs_pathlist_t *pathlist) {
    if (!pathlist || !pathlist->paths) return;
    for (int32_t i = 0; i < pathlist->numpaths; ++i)
        free(pathlist->paths[i]);
    free(pathlist->paths);
    pathlist->paths = NULL;
    pathlist->numpaths = 0;
}

const char *fs_readline(fs_file_t *file, char *dst, uint64_t size) {
    int64_t rx = 0;
    char chr, *p;

    // assume we got buffered input
    for (p = dst, size--; size > 0; size--) {
        if ((rx = fs_read(file, &chr, 1)) <= 0)
            break;
        *p++ = chr;
        if (chr == '\n')
            break;
    }

    *p = 0;
    if (p == dst || rx <= 0)
        return NULL;

    return p;
}

void *fs_load_file(const char *vpath, uint64_t *outsize) {
    fs_file_t *f = fs_open(vpath);
    if (!f) return NULL;

    int64_t size = fs_size(f);
    if (size <= 0) {
        fs_close(f);
        return NULL;
    }

    void *buf = malloc(size);
    if (!buf) {
        fs_close(f);
        return NULL;
    }

    int64_t rx = fs_read(f, buf, size);
    fs_close(f);

    if (rx < size) {
        free(buf);
        return NULL;
    }

    if (outsize) *outsize = size;
    return buf;
}

const char *fs_get_write_path(const char *vpath) {
    static char path[SYS_MAX_PATH];
    if (snprintf(path, sizeof(path), "%s/%s", fs_writepath, vpath) < 0) {
        return NULL;
    }
    return path;
}

const char *fs_convert_path(char *buf, const size_t bufsiz, const char *path) {
    if (NULL == path) { return ""; }

    // ! means "executable directory"
    if (path[0] == '!') {
        if (snprintf(buf, bufsiz, "%s%s", sys_exe_path_dir(), path + 1) < 0) {
            return "";
        }
    } else {
        strncpy(buf, path, bufsiz);
        buf[bufsiz-1] = 0;
    }

    // change all backslashes
    for (char *p = buf; *p; ++p)
        if (*p == '\\') *p = '/';

    return buf;
}

bool fs_sys_filename_is_portable(char const *filename) {
    char c;
    while (0 != (c = *(filename++))) {

        if (c < ' ' || c > '~') {
            // character outside of printable range
            return false;
        }

        switch (c) {
            // characters unallowed in filenames
            case '/': case '\\': case '<': case '>':
            case ':': case '"': case '|': case '?': case '*':
                return false;
        }
    }

    return true;
}

/* these operate on the real file system */

bool fs_sys_path_exists(const char *name) {
#ifdef _WIN32
    return GetFileAttributesA(name) != INVALID_FILE_ATTRIBUTES;
#else
    struct stat st;
    return (stat(name, &st) == 0);
#endif
}

bool fs_sys_file_exists(const char *name) {
#ifdef _WIN32
    DWORD attribs = GetFileAttributesA(name);
    return attribs != INVALID_FILE_ATTRIBUTES && !(attribs & FILE_ATTRIBUTE_DIRECTORY);
#else
    struct stat st;
    return (stat(name, &st) == 0 && S_ISREG(st.st_mode));
#endif
}

bool fs_sys_dir_exists(const char *name) {
#ifdef _WIN32
    DWORD attribs = GetFileAttributesA(name);
    return attribs != INVALID_FILE_ATTRIBUTES && (attribs & FILE_ATTRIBUTE_DIRECTORY);
#else
    struct stat st;
    return (stat(name, &st) == 0 && S_ISDIR(st.st_mode));
#endif
}

bool fs_sys_dir_is_empty(const char *name) {
    DIR *dir;
    struct dirent *ent;

    if (!(dir = opendir(name))) {
        fprintf(stderr, "fs_sys_dir_is_empty(): could not open `%s`\n", name);
        return true;
    }

    bool ret = true;
    while ((ent = readdir(dir)) != NULL) {
        // skip "." and ".."
        if (ent->d_name[0] == '.' && (ent->d_name[1] == '\0' ||
           (ent->d_name[1] == '.' && ent->d_name[2] == '\0'))) {
            continue;
        }

        ret = false;
        break;
    }

    closedir(dir);
    return ret;
}

bool fs_sys_walk(const char *base, walk_fn_t walk, void *user, const bool recur) {
#ifdef DOCKERBUILD
    return false;
#else
    char fullpath[SYS_MAX_PATH];
    DIR *dir;
    struct dirent *ent;

    if (!(dir = opendir(base))) {
        fprintf(stderr, "fs_dir_walk(): could not open `%s`\n", base);
        return false;
    }

    bool ret = true;

    while ((ent = readdir(dir)) != NULL) {
        if (ent->d_name[0] == 0 || ent->d_name[0] == '.') continue; // skip ./.. and hidden files
        if (snprintf(fullpath, sizeof(fullpath), "%s/%s", base, ent->d_name) < 0) {
            continue;
        }
        if (fs_sys_dir_exists(fullpath)) {
            if (recur) {
                if (!fs_sys_walk(fullpath, walk, user, recur)) {
                    ret = false;
                    break;
                }
            }
        } else {
            if (!walk(user, fullpath)) {
                ret = false;
                break;
            }
        }
    }

    closedir(dir);
    return ret;
#endif
}

bool fs_sys_mkdir(const char *name) {
#ifdef _WIN32
    return _mkdir(name) == 0;
#else
    return mkdir(name, 0777) == 0;
#endif
}

bool fs_sys_rmdir(const char *name) {
#ifdef _WIN32
    return _rmdir(name) == 0;
#else
    return rmdir(name) == 0;
#endif
}
