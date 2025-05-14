extern u32 gDynosModDataLastError;


template <typename T>
struct ModDataItem {
    T *mBuffer;
    u32 mSize;
    bool mAvailable;
};

template <typename T>
using ModDataPool = ModDataItem<T> *;

template <typename T>
using ModDataMap = std::map<std::string, ModDataItem<T> *>;

template <typename T>
using ModDataResult = std::pair<T, u32>;


template <typename T, size_t MaxPoolSize, u32 MaxItemSize, typename ItemAllocator, typename ItemResize, typename ItemDeallocator>
class ModData : NoCopy {
public:
    inline ModData(ItemAllocator *itemAllocator, ItemResize *itemResize, ItemDeallocator *itemDeallocator) :
        mMapNameToItem(), mItems(), mItemAllocator(itemAllocator), mItemResize(itemResize), mItemDeallocator(itemDeallocator) {
    }

    inline ~ModData() {
        Clear();
    }

public:
    ModDataResult<ModDataItem<T> *> Get(const char *aName) {
        if (!aName) {
            return { NULL, DYNOS_MOD_DATA_ERROR_NAME_IS_NULL };
        }
        if (!*aName) {
            return { NULL, DYNOS_MOD_DATA_ERROR_NAME_IS_EMPTY };
        }

        auto itItem = mMapNameToItem.find(aName);
        if (itItem == mMapNameToItem.end()) {
            return { NULL, DYNOS_MOD_DATA_ERROR_NAME_NOT_FOUND };
        }

        return { itItem->second, 0 };
    }

    ModDataResult<ModDataItem<T> *> Create(const char *aName, u32 aSize) {
        if (!aName) {
            return { NULL, DYNOS_MOD_DATA_ERROR_NAME_IS_NULL };
        }
        if (!*aName) {
            return { NULL, DYNOS_MOD_DATA_ERROR_NAME_IS_EMPTY };
        }
        if (!aSize) {
            return { NULL, DYNOS_MOD_DATA_ERROR_SIZE_IS_ZERO };
        }
        if (aSize > MaxItemSize) {
            return { NULL, DYNOS_MOD_DATA_ERROR_SIZE_IS_ABOVE_MAX };
        }

        auto getResult = Get(aName);
        if (getResult.first) {
            return { NULL, DYNOS_MOD_DATA_ERROR_ALREADY_EXISTS };
        }

        auto findAvailableResult = FindAvailableItem();
        ModDataItem<T> *item = findAvailableResult.first;
        if (!item) {
            return { NULL, findAvailableResult.second ? findAvailableResult.second : DYNOS_MOD_DATA_ERROR_POOL_IS_FULL };
        }

        mItemResize(item->mBuffer, 0, aSize);
        item->mSize = aSize;
        item->mAvailable = false;
        mMapNameToItem[aName] = item;
        return { item, 0 };
    }

    ModDataResult<bool> Resize(T *aPointer, u32 aNewSize) {
        if (!aPointer) {
            return { false, DYNOS_MOD_DATA_ERROR_POINTER_IS_NULL };
        }
        if (!aNewSize) {
            return { false, DYNOS_MOD_DATA_ERROR_SIZE_IS_ZERO };
        }
        if (aNewSize > MaxItemSize) {
            return { false, DYNOS_MOD_DATA_ERROR_SIZE_IS_ABOVE_MAX };
        }

        std::string name;
        auto findResult = Find(aPointer, name);
        ModDataItem<T> *item = findResult.first;
        if (!item) {
            return { false, findResult.second ? findResult.second : DYNOS_MOD_DATA_ERROR_POINTER_NOT_FOUND };
        }

        mItemResize(item->mBuffer, item->mSize, aNewSize);
        item->mSize = aNewSize;
        return { true, 0 };
    }

    ModDataResult<bool> Delete(T *aPointer) {
        if (!aPointer) {
            return { false, DYNOS_MOD_DATA_ERROR_POINTER_IS_NULL };
        }

        std::string name;
        auto findResult = Find(aPointer, name);
        ModDataItem<T> *item = findResult.first;
        if (!item) {
            return { false, findResult.second ? findResult.second : DYNOS_MOD_DATA_ERROR_POINTER_NOT_FOUND };
        }

        // Mark the item as available, but don't free its content yet
        // It will be reused by the next call to Create
        // Also prevents use-after-free issues
        item->mAvailable = true;
        mMapNameToItem.erase(name);
        return { true, 0 };
    }

    void Clear() {
        if (mItems) {
            for (size_t i = 0; i != MaxPoolSize; ++i) {
                ModDataItem<T> *item = mItems + i;
                if (item->mBuffer) {
                    mItemDeallocator(item->mBuffer, item->mSize);
                }
            }
            free(mItems);
            mItems = NULL;
        }
        mMapNameToItem.clear();
    }

private:
    ModDataResult<ModDataItem<T> *> Find(T *aPointer, std::string &outName) {
        if (!aPointer) {
            return { NULL, DYNOS_MOD_DATA_ERROR_POINTER_IS_NULL };
        }

        for (auto &nameItem : mMapNameToItem) {
            if (nameItem.second->mBuffer == aPointer) {
                outName = nameItem.first;
                return { nameItem.second, 0 };
            }
        }

        return { NULL, 0 };
    }

    ModDataResult<ModDataItem<T> *> FindAvailableItem() {

        // Create pool if it doesn't exist yet
        if (!mItems) {
            mItems = (ModDataPool<T>) calloc(MaxPoolSize, sizeof(ModDataItem<T>));
        }

        for (size_t i = 0; i != MaxPoolSize; ++i) {
            ModDataItem<T> *item = mItems + i;

            // Fresh new item
            if (!item->mBuffer) {
                item->mBuffer = mItemAllocator(MaxItemSize);
                item->mSize = 0;
                item->mAvailable = true;
                return { item, 0 };
            }

            // Available item
            if (item->mAvailable) {
                return { item, 0 };
            }
        }

        return { NULL, DYNOS_MOD_DATA_ERROR_POOL_IS_FULL };
    }

private:
    ModDataMap<T> mMapNameToItem;
    ModDataPool<T> mItems;
    ItemAllocator *mItemAllocator;
    ItemResize *mItemResize;
    ItemDeallocator *mItemDeallocator;
};


template <typename T, size_t MaxPoolSize, u32 MaxItemSize, typename ItemAllocator, typename ItemResize, typename ItemDeallocator>
class ModsData : NoCopy {
    typedef ModData<T, MaxPoolSize, MaxItemSize, ItemAllocator, ItemResize, ItemDeallocator> ModDataT;

public:
    inline ModsData(ItemAllocator *itemAllocator, ItemResize *itemResize, ItemDeallocator *itemDeallocator) :
        mMods(), mItemAllocator(itemAllocator), mItemResize(itemResize), mItemDeallocator(itemDeallocator) {
    }

    inline ~ModsData() {
        Clear();
    }

public:
    T *Get(s32 aModIndex, const char *aName, u32 *outSize) {
        ModDataT *modData = GetModData(aModIndex);
        auto getResult = modData->Get(aName);
        if (!getResult.first) {
            gDynosModDataLastError = getResult.second;
            return NULL;
        }
        *outSize = getResult.first->mSize;
        return getResult.first->mBuffer;
    }

    T *Create(s32 aModIndex, const char *aName, u32 aSize) {
        ModDataT *modData = GetModData(aModIndex);
        auto createResult = modData->Create(aName, aSize);
        if (!createResult.first) {
            gDynosModDataLastError = createResult.second;
            return NULL;
        }
        return createResult.first->mBuffer;
    }

    bool Resize(s32 aModIndex, T *aPointer, u32 aNewSize) {
        ModDataT *modData = GetModData(aModIndex);
        auto resizeResult = modData->Resize(aPointer, aNewSize);
        if (!resizeResult.first) {
            gDynosModDataLastError = resizeResult.second;
            return false;
        }
        return true;
    }

    bool Delete(s32 aModIndex, T *aPointer) {
        ModDataT *modData = GetModData(aModIndex);
        auto deleteResult = modData->Delete(aPointer);
        if (!deleteResult.first) {
            gDynosModDataLastError = deleteResult.second;
            return false;
        }
        return true;
    }

    void DeleteAll(s32 aModIndex) {
        ModDataT *modData = GetModData(aModIndex);
        modData->Clear();
    }

    void Clear() {
        for (auto &indexData : mMods) {
            indexData.second->Clear();
            delete indexData.second;
        }
        mMods.clear();
    }

private:
    ModDataT *GetModData(s32 aModIndex) {
        gDynosModDataLastError = 0;
        auto itModData = mMods.find(aModIndex);
        if (itModData == mMods.end()) {
            ModDataT *modData = new ModDataT(mItemAllocator, mItemResize, mItemDeallocator);
            mMods[aModIndex] = modData;
            return modData;
        }
        return itModData->second;
    }

private:
    std::map<s32, ModDataT *> mMods;
    ItemAllocator *mItemAllocator;
    ItemResize *mItemResize;
    ItemDeallocator *mItemDeallocator;
};

// - `_ItemAllocator_` should be a function of signature: `T *_ItemAllocator_(u32 size)`
//   allocates buffer of size `_MaxItemSize_`, but does not edit its contents (internal size is 0)
// - `_ItemResize_` should be a function of signature: `void _ItemResize_(T *ptr, u32 oldSize, u32 newSize)`
//   updates the contents of `ptr`, but does not allocate nor free memory
// - `_ItemDeallocator_` should be a function of signature: `void _ItemDeallocator_(T *ptr, u32 size)`
//   frees buffer of size `size`
#define DEFINE_MODS_DATA(_Name_, _Type_, _MaxPoolSize_, _MaxItemSize_, _ItemAllocator_, _ItemResize_, _ItemDeallocator_) \
static ModsData<_Type_, _MaxPoolSize_, _MaxItemSize_, decltype(_ItemAllocator_), decltype(_ItemResize_), decltype(_ItemDeallocator_)> _Name_(_ItemAllocator_, _ItemResize_, _ItemDeallocator_)
