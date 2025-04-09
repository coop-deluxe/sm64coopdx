
template <typename T>
T *DynOS_ModData_Get(ModData<T> &aModData, s32 aModIndex, const char *aName, u32 *outCount) {
    if (!aName) { return NULL; }

    auto itMod = aModData.find(aModIndex);
    if (itMod == aModData.end()) {
        return NULL;
    }

    auto itItem = itMod->second.find(aName);
    if (itItem == itMod->second.end()) {
        return NULL;
    }

    if (outCount) {
        *outCount = itItem->second.second;
    }
    return itItem->second.first;
}

template <typename T>
bool DynOS_ModData_Find(ModData<T> &aModData, s32 aModIndex, T *aPointer, std::string &outName) {
    if (!aPointer) { return false; }

    auto itMod = aModData.find(aModIndex);
    if (itMod == aModData.end()) {
        return false;
    }

    for (auto &modItem : itMod->second) {
        if (modItem.second.first == aPointer) {
            outName = modItem.first;
            return true;
        }
    }

    return false;
}

template <typename T, typename Allocator>
T *DynOS_ModData_New(ModData<T> &aModData, s32 aModIndex, const char *aName, u32 aCount, Allocator aAllocator) {
    if (!aName || !aCount) { return NULL; }

    if (DynOS_ModData_Get(aModData, aModIndex, aName, NULL)) {
        return NULL;
    }

    auto itMod = aModData.find(aModIndex);
    if (itMod == aModData.end()) {
        aModData[aModIndex] = {};
    }

    T *newItem = aAllocator(aCount);
    aModData[aModIndex][aName] = { newItem, aCount };
    return newItem;
}

template <typename T, typename Allocator, typename Deallocator>
T *DynOS_ModData_Realloc(ModData<T> &aModData, s32 aModIndex, T *aPointer, u32 aNewCount, Allocator aAllocator, Deallocator aDeallocator) {
    if (!aPointer) { return NULL; }

    std::string itemName;
    if (!DynOS_ModData_Find(aModData, aModIndex, aPointer, itemName)) {
        return NULL;
    }

    // No need to shrink the existing buffer
    auto &modItem = aModData[aModIndex][itemName];
    u32 itemCount = modItem.second;
    if (aNewCount < itemCount) {
        return modItem.first;
    }

    T *newItem = aAllocator(aNewCount);
    memcpy(newItem, aPointer, itemCount * sizeof(T));
    aDeallocator(aPointer);
    aModData[aModIndex][itemName] = { newItem, aNewCount };
    return newItem;
}

template <typename T, typename Deallocator>
bool DynOS_ModData_Delete(ModData<T> &aModData, s32 aModIndex, T *aPointer, Deallocator aDeallocator) {
    if (!aPointer) { return false; }

    std::string itemName;
    if (!DynOS_ModData_Find(aModData, aModIndex, aPointer, itemName)) {
        return false;
    }

    aDeallocator(aPointer);
    aModData[aModIndex].erase(itemName);
    return true;
}

template <typename T, typename Deallocator>
void DynOS_ModData_DeleteAll(ModData<T> &aModData, Deallocator aDeallocator) {
    for (auto &modItems : aModData) {
        for (auto &modItem : modItems.second) {
            aDeallocator(modItem.second.first);
        }
    }
    aModData.clear();
}
