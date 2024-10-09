#include "fmem.h"
#include "pc/platform.h"
#include "engine/math_util.h"

typedef struct file_t {
    char filename[SYS_MAX_PATH];
    void *data;
    size_t size;
    size_t pos;
    bool readonly;
} file_t;

typedef struct file_node_t {
    file_t file;
    struct file_node_t *prev;
    struct file_node_t *next;
} file_node_t;

static file_node_t *sMemoryFiles = NULL;

static file_t *f_get_file_from_handle(FILE *f) {
    for (file_node_t *node = sMemoryFiles; node; node = node->prev) {
        if (node == (void *) f) {
            return &node->file;
        }
    }
    return NULL;
}

static file_t *f_get_file_from_name(const char *filename) {
    for (file_node_t *node = sMemoryFiles; node; node = node->prev) {
        if (strcmp(node->file.filename, filename) == 0) {
            return &node->file;
        }
    }
    return NULL;
}

static file_t *f_create_file(const char *filename) {
    file_node_t *node = calloc(1, sizeof(file_node_t));
    if (sMemoryFiles) {
        sMemoryFiles->next = node;
        node->prev = sMemoryFiles;
    }
    sMemoryFiles = node;
    strncpy(node->file.filename, filename, sizeof(node->file.filename) - 1);
    return &node->file;
}

static void f_remove_file(file_t *file) {
    file_node_t *node = (file_node_t *) file;
    if (node->prev) {
        node->prev->next = node->next;
    }
    if (node->next) {
        node->next->prev = node->prev;
    }
    if (node == sMemoryFiles) {
        sMemoryFiles = node->prev;
    }
    if (file->data) {
        free(file->data);
    }
    free(node);
}

FILE *f_open_r(const char *filename) {
    file_t *file = f_get_file_from_name(filename);
    if (!file) return fopen(filename, "rb");
    file->pos = 0;
    file->readonly = true;
    return (FILE *) file;
}

FILE *f_open_w(const char *filename) {
    file_t *file = f_create_file(filename);
    return (FILE *) file;
}

int f_close(FILE *f) {
    file_t *file = f_get_file_from_handle(f);
    if (!file) return fclose(f);
    return 0;
}

void f_delete(FILE *f) {
    file_t *file = f_get_file_from_handle(f);
    if (!file) return;
    f_remove_file(file);
}

size_t f_read(void *dst, size_t size, size_t count, FILE *f) {
    file_t *file = f_get_file_from_handle(f);
    if (!file) return fread(dst, size, count, f);
    if (file->pos >= file->size) return 0;
    count = min(count, ((file->size - file->pos) / size));
    memcpy(dst, file->data + file->pos, count * size);
    file->pos += count * size;
    return count;
}

size_t f_write(const void *str, size_t size, size_t count, FILE *f) {
    file_t *file = f_get_file_from_handle(f);
    if (!file) return fwrite(str, size, count, f);
    if (file->readonly) return 0;
    size_t newsize = file->pos + size * count;
    if (newsize > file->size) {
        void *buffer = malloc(newsize);
        if (!buffer) {
            return 0;
        }
        if (file->data) {
            memcpy(buffer, file->data, file->size);
            free(file->data);
        }
        file->data = buffer;
        file->size = newsize;
    }
    memcpy(file->data + file->pos, str, size * count);
    file->pos += size * count;
    return count;
}

int f_seek(FILE *f, long offset, int origin) {
    file_t *file = f_get_file_from_handle(f);
    if (!file) return fseek(f, offset, origin);
    switch (origin) {
        case SEEK_SET: file->pos = offset; break;
        case SEEK_CUR: file->pos += offset; break;
        case SEEK_END: file->pos = file->size + offset; break;
        default: return 1;
    }
    return 0;
}

long f_tell(FILE *f) {
    file_t *file = f_get_file_from_handle(f);
    if (!file) return ftell(f);
    return file->pos;
}

void f_rewind(FILE *f) {
    file_t *file = f_get_file_from_handle(f);
    if (!file) return rewind(f);
    file->pos = 0;
}

int f_flush(FILE *f) {
    file_t *file = f_get_file_from_handle(f);
    if (!file) return fflush(f);
    return 0;
}

void f_shutdown() {
    for (file_node_t *node = sMemoryFiles; node;) {
        if (node->file.data) {
            free(node->file.data);
        }
        file_node_t *prev = node->prev;
        free(node);
        node = prev;
    }
    sMemoryFiles = NULL;
}
