#include <map>
#include <unordered_map>
#include <cstdint>
#include <cstddef>
#include <memory>

enum class MapType {
    Ordered,
    Unordered
};

// Ordered maps can be iterated by key order
// Unordered maps have the fastest lookup times (also called a hash map)

class HMap {
public:
    HMap(MapType type = MapType::Ordered) : mMapType(type) {
        switch (mMapType) {
            case MapType::Ordered:
                mOrderedMap = std::make_unique<std::map<int64_t, void*>>();
                break;
            case MapType::Unordered:
                mUnorderedMap = std::make_unique<std::unordered_map<int64_t, void*>>();
                break;
        }
    }

    void* get(int64_t key) {
        switch (mMapType) {
            case MapType::Ordered:
                if (mOrderedMap->count(key)) {
                    return mOrderedMap->at(key);
                }
                break;
            case MapType::Unordered:
                if (mUnorderedMap->count(key)) {
                    return mUnorderedMap->at(key);
                }
                break;
        }
        return nullptr;
    }

    void put(int64_t key, void* value) {
        switch (mMapType) {
            case MapType::Ordered:
                mOrderedMap->insert_or_assign(key, value);
                break;
            case MapType::Unordered:
                mUnorderedMap->insert_or_assign(key, value);
                break;
        }
    }

    void erase(int64_t key) {
        switch (mMapType) {
            case MapType::Ordered:
                mOrderedMap->erase(key);
                break;
            case MapType::Unordered:
                mUnorderedMap->erase(key);
                break;
        }
    }

    void clear() {
        switch (mMapType) {
            case MapType::Ordered:
                mOrderedMap->clear();
                break;
            case MapType::Unordered:
                mUnorderedMap->clear();
                break;
        }
    }

    size_t size() const {
        switch (mMapType) {
            case MapType::Ordered:
                return mOrderedMap->size();
            case MapType::Unordered:
                return mUnorderedMap->size();
        }
        return 0;
    }

    void* begin() {
        switch (mMapType) {
            case MapType::Ordered: {
                auto& orderedMap = *mOrderedMap;
                if (orderedMap.empty()) { return nullptr; }
                mOrderedIterator = mOrderedMap->begin();
                return mOrderedIterator->second;
            }
            case MapType::Unordered: {
                auto& unorderedMap = *mUnorderedMap;
                if (unorderedMap.empty()) { return nullptr; }
                mUnorderedIterator = mUnorderedMap->begin();
                return mUnorderedIterator->second;
            }
        }
        return nullptr;
    }

    void* next() {
        switch (mMapType) {
            case MapType::Ordered: {
                if (++mOrderedIterator != mOrderedMap->end()) {
                    return mOrderedIterator->second;
                }
                break;
            }
            case MapType::Unordered: {
                if (++mUnorderedIterator != mUnorderedMap->end()) {
                    return mUnorderedIterator->second;
                }
                break;
            }
        }
        return nullptr;
    }

private:
    MapType mMapType;

    std::unique_ptr<std::map<int64_t, void*>> mOrderedMap;
    typename std::map<int64_t, void*>::iterator mOrderedIterator;

    std::unique_ptr<std::unordered_map<int64_t, void*>> mUnorderedMap;
    typename std::unordered_map<int64_t, void*>::iterator mUnorderedIterator;
};

extern "C" {
void* hmap_create(MapType type) {
    return new HMap(type);
}

void* hmap_get(void* map, int64_t key) {
    if (!map) { return NULL; }
    HMap* hmap = reinterpret_cast<HMap*>(map);
    return hmap->get(key);
}

void hmap_put(void* map, int64_t key, void* value) {
    if (!map) { return; }
    HMap* hmap = reinterpret_cast<HMap*>(map);
    hmap->put(key, value);
}

void hmap_del(void* map, int64_t key) {
    if (!map) { return; }
    HMap* hmap = reinterpret_cast<HMap*>(map);
    hmap->erase(key);
}

void hmap_clear(void* map) {
    if (!map) { return; }
    HMap* hmap = reinterpret_cast<HMap*>(map);
    hmap->clear();
}

void hmap_destroy(void* map) {
    if (!map) { return; }
    delete reinterpret_cast<HMap*>(map);
}

size_t hmap_len(void* map) {
    if (!map) { return 0; }
    HMap* hmap = reinterpret_cast<HMap*>(map);
    return hmap->size();
}

void* hmap_begin(void* map) {
    if (!map) { return NULL; }
    HMap* hmap = reinterpret_cast<HMap*>(map);
    return hmap->begin();
}

void* hmap_next(void* map) {
    if (!map) { return NULL; }
    HMap* hmap = reinterpret_cast<HMap*>(map);
    return hmap->next();
}
}
