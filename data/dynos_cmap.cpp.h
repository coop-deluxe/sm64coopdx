#ifndef DYNOS_CMAP_CPP_H
#define DYNOS_CMAP_CPP_H
#ifndef __cplusplus

void* hmap_create();
void* hmap_get(void* map, int64_t k);
void hmap_put(void* map, int64_t k, void* v);
void hmap_del(void* map, int64_t k);
void hmap_clear(void* map);
size_t hmap_len(void* map);

void* hmap_iter(void* map);
void* hmap_begin(void* iter);
void* hmap_next(void* iter);

#endif
#endif