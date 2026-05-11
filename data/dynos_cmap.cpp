#include <map>
#include <unordered_map>
#include <cstdint>
#include <cstddef>
#include <memory>
#include <string>

// Ordered maps can be iterated by key order
// Unordered maps have the fastest lookup times (also called a hash map)

template <typename KeyType>
class IHMap {
public:
    virtual ~IHMap() = default;

    virtual void* get(const KeyType& key) = 0;
    virtual void put(const KeyType& key, void* value) = 0;
    virtual void erase(const KeyType& key) = 0;
    virtual void clear() = 0;
    virtual size_t size() const = 0;
    virtual void* begin() = 0;
    virtual void* next() = 0;
};

template <typename KeyType, bool UseUnordered>
class HMap final : public IHMap<KeyType> {
private:
    using MapType = typename std::conditional<
        UseUnordered,
        std::unordered_map<KeyType, void*>,
        std::map<KeyType, void*>
    >::type;

public:
    void* get(const KeyType& key) override {
        auto it = mMap.find(key);
        return (it != mMap.end()) ? it->second : nullptr;
    }

    void put(const KeyType& key, void* value) override {
        mMap.insert_or_assign(key, value);
    }

    void erase(const KeyType& key) override {
        mMap.erase(key);
    }

    void clear() override {
        mMap.clear();
    }

    size_t size() const override {
        return mMap.size();
    }

    void* begin() override {
        if (mMap.empty()) return nullptr;
        mIterator = mMap.begin();
        return mIterator->second;
    }

    void* next() override {
        if (++mIterator != mMap.end()) {
            return mIterator->second;
        }
        return nullptr;
    }

private:
    MapType mMap;
    typename MapType::iterator mIterator;
};

extern "C" {
void* hmap_create(bool useUnordered) {
    if (useUnordered) {
        return new HMap<int64_t, true>();
    }
    return new HMap<int64_t, false>();
}

void* hmap_get(void* map, int64_t key) {
    if (!map) { return NULL; }
    IHMap<int64_t>* hmap = static_cast<IHMap<int64_t>*>(map);
    return hmap->get(key);
}

void hmap_put(void* map, int64_t key, void* value) {
    if (!map) { return; }
    IHMap<int64_t>* hmap = static_cast<IHMap<int64_t>*>(map);
    hmap->put(key, value);
}

void hmap_del(void* map, int64_t key) {
    if (!map) { return; }
    IHMap<int64_t>* hmap = static_cast<IHMap<int64_t>*>(map);
    hmap->erase(key);
}

void hmap_clear(void* map) {
    if (!map) { return; }
    IHMap<int64_t>* hmap = static_cast<IHMap<int64_t>*>(map);
    hmap->clear();
}

void hmap_destroy(void* map) {
    if (!map) { return; }
    delete static_cast<IHMap<int64_t>*>(map);
}

size_t hmap_len(void* map) {
    if (!map) { return 0; }
    IHMap<int64_t>* hmap = static_cast<IHMap<int64_t>*>(map);
    return hmap->size();
}

void* hmap_begin(void* map) {
    if (!map) { return NULL; }
    IHMap<int64_t>* hmap = static_cast<IHMap<int64_t>*>(map);
    return hmap->begin();
}

void* hmap_next(void* map) {
    if (!map) { return NULL; }
    IHMap<int64_t>* hmap = static_cast<IHMap<int64_t>*>(map);
    return hmap->next();
}

// Data/String map (for larger keys)
void* hmap_data_create(void) {
    return new HMap<std::string, true>();
}

void* hmap_data_get(void* map, const char* key, size_t len) {
    if (!map) { return NULL; }
    std::string keyString(key, len);
    return static_cast<IHMap<std::string>*>(map)->get(keyString);
}

void hmap_data_put(void* map, const char* key, size_t len, void* value) {
    if (!map) { return; }
    std::string keyString(key, len);
    static_cast<IHMap<std::string>*>(map)->put(keyString, value);
}

void hmap_data_del(void* map, const char* key, size_t len) {
    if (!map) { return; }
    std::string keyString(key, len);
    static_cast<IHMap<std::string>*>(map)->erase(keyString);
}

void hmap_data_clear(void* map) {
    if (!map) { return; }
    static_cast<IHMap<std::string>*>(map)->clear();
}

void hmap_data_destroy(void* map) {
    if (!map) { return; }
    delete static_cast<IHMap<std::string>*>(map);
}

size_t hmap_data_len(void* map) {
    if (!map) { return 0; }
    return static_cast<IHMap<std::string>*>(map)->size();
}
}
