#ifndef DYNOS_CMAP_CPP_H
#define DYNOS_CMAP_CPP_H
#endif

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

void* hmap_data_create(void);
void* hmap_data_get(void* map, const char* key, size_t len);
void hmap_data_put(void* map, const char* key, size_t len, void* value);
void hmap_data_del(void* map, const char* key, size_t len);
void hmap_data_clear(void* map);
void hmap_data_destroy(void* map);
size_t hmap_data_len(void* map);

#endif
