#include <map>
#include <cstdint>
#include <cstddef>

typedef std::map<int64_t, void*> Map;

struct MapIter {
    Map* map;
    Map::iterator itr;
};

extern "C" {

void* hmap_create() {
    return reinterpret_cast<void*> (new Map());
}

void* hmap_get(void* map, int64_t k) {
    if (!map) { return NULL; }
    Map* m = reinterpret_cast<Map*> (map);
    Map::iterator pos = m->find(k);
    if (pos == m->end()) {
        return NULL;
    } else {
        return pos->second;
    }
}

void hmap_put(void* map, int64_t k, void* v) {
    if (!map) { return; }
    Map* m = reinterpret_cast<Map*> (map);
    if (m->count(k) > 0) {
        m->erase(k);
    }
    m->insert(std::pair<int64_t, void*>(k, v));
}

void hmap_del(void* map, int64_t k) {
    if (!map) { return; }
    Map* m = reinterpret_cast<Map*> (map);
    m->erase(k);
}

void hmap_clear(void* map) {
    if (!map) { return; }
    Map* m = reinterpret_cast<Map*> (map);
    m->clear();
}

size_t hmap_len(void* map) {
    if (!map) { return 0; }
    Map* m = reinterpret_cast<Map*> (map);
    return m->size();
}

void* hmap_iter(void* map) {
    if (!map) { return nullptr; }
    auto iter = new MapIter();
    Map* m = reinterpret_cast<Map*> (map);
    iter->map = m;
    return reinterpret_cast<void*> (iter);
}

void* hmap_begin(void* iter) {
    if (!iter) { return nullptr; }
    MapIter* i = reinterpret_cast<MapIter*> (iter);
    i->itr = i->map->begin();
    if (i->itr == i->map->end()) {
        return NULL;
    }
    return i->itr->second;
}

void* hmap_next(void* iter) {
    if (!iter) { return nullptr; }
    MapIter* i = reinterpret_cast<MapIter*> (iter);
    i->itr++;
    if (i->itr == i->map->end()) {
        return NULL;
    }
    return i->itr->second;
}

} // extern "C"