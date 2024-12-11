#ifndef DYNOS_CMAP_CPP_H
#define DYNOS_CMAP_CPP_H
#ifndef __cplusplus

void* hmap_create(bool useUnordered);
void* hmap_get(void* map, int64_t k);
void hmap_put(void* map, int64_t k, void* v);
void hmap_del(void* map, int64_t k);
void hmap_clear(void* map);
void hmap_destroy(void* map);
size_t hmap_len(void* map);

void* hmap_begin(void* map);
void* hmap_next(void* map);

#endif
#endif