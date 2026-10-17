#include <array>
#include "dynos.cpp.h"

extern "C" {
#include "pc/network/network_player.h"
}

static constexpr std::array<const char *, CT_MAX> sCharacterHeadNames = {
    "mario_head",
    "luigi_head",
    "toad_head",
    "waluigi_head",
    "wario_head",
};

static_assert(sCharacterHeadNames.back() != nullptr, "sCharacterHeadNames needs an entry for every character up to CT_MAX");

static std::vector<GoddardHeadEntry*> sGoddardPackHeads;
static std::vector<GoddardHeadEntry*> sGoddardModHeads;

// Head requested through goddard_set_head(), and is prioritized
// over the head belonging to the character the local player is using.
static std::string sGoddardHeadOverride = "";

static GoddardHeadEntry* DynOS_Goddard_GetActiveHeadFrom(std::vector<GoddardHeadEntry*> &aHeads, const char* aHeadName) {
    for (auto it = aHeads.rbegin(); it != aHeads.rend(); ++it) {
        if ((*it)->enabled && !strcmp((*it)->headName, aHeadName)) {
            return *it;
        }
    }
    return NULL;
}

static GoddardHeadEntry* DynOS_Goddard_GetActiveHead(const char* aHeadName) {
    if (aHeadName == NULL || *aHeadName == '\0') { return NULL; }
    GoddardHeadEntry* _Head = DynOS_Goddard_GetActiveHeadFrom(sGoddardModHeads, aHeadName);
    if (_Head != NULL) { return _Head; }
    return DynOS_Goddard_GetActiveHeadFrom(sGoddardPackHeads, aHeadName);
}

static GoddardHeadEntry* DynOS_Goddard_GetActiveCharacterHead() {
    u8 _CharacterIndex = gNetworkPlayers[0].overrideModelIndex;
    if (_CharacterIndex >= CT_MAX) { _CharacterIndex = CT_MARIO; }

    GoddardHeadEntry* _Head = DynOS_Goddard_GetActiveHead(sGoddardHeadOverride.c_str());
    if (_Head == NULL) { _Head = DynOS_Goddard_GetActiveHead(sCharacterHeadNames[_CharacterIndex]); }
    if (_Head == NULL) { _Head = DynOS_Goddard_GetActiveHead(sCharacterHeadNames[CT_MARIO]); }
    return _Head;
}

static void DynOS_Goddard_ResetModEntry(GoddardHeadEntry* aHead) {
    if (aHead == NULL) { return; }

    aHead->enabled = false;
    aHead->loaded = false;

    if (aHead->headName) {
        free(aHead->headName);
        aHead->headName = NULL;
    }

    if (aHead->filename) {
        free(aHead->filename);
        aHead->filename = NULL;
    }

    aHead->length = 0;

    if (aHead->buffer != NULL) {
        free(aHead->buffer);
        aHead->buffer = NULL;
    }
}

void DynOS_Goddard_ModShutdown() {
    for (auto& _Head : sGoddardModHeads) {
        DynOS_Goddard_ResetModEntry(_Head);
        free(_Head);
    }
    sGoddardModHeads.clear();
    sGoddardHeadOverride = "";
}

static bool DynOS_Goddard_LoadEntry(GoddardHeadEntry* aHead) {
    if (aHead == NULL || !aHead->enabled) { return false; }
    if (aHead->loaded) { return true; }

    BinFile* _File = BinFile::OpenR(aHead->filename);
    if (_File == NULL) {
        PrintError("  ERROR: Unable to open file \"%s\": Goddard head '%s' will not be enabled", aHead->filename, aHead->headName);
        return false;
    }

    PrintInfo("Loading goddard head '%s' from file: %s", aHead->headName, aHead->filename);

    s32 _Size = _File->Size();
    if (_Size <= 0) {
        BinFile::Close(_File);
        PrintError("  ERROR: File \"%s\" is empty: Goddard head '%s' will not be enabled", aHead->filename, aHead->headName);
        return false;
    }

    u8* _Data = (u8*) malloc(_Size);
    if (_Data == NULL) {
        BinFile::Close(_File);
        PrintError("  ERROR: Unable to allocate %d bytes for file \"%s\"", _Size, aHead->filename);
        return false;
    }

    _File->Read<u8>(_Data, _Size);
    BinFile::Close(_File);

    aHead->loaded = true;
    aHead->buffer = _Data;
    aHead->length = _Size;

    return true;
}

const u8* DynOS_Goddard_GetData() {
    GoddardHeadEntry* _Head = DynOS_Goddard_GetActiveCharacterHead();
    if (!DynOS_Goddard_LoadEntry(_Head)) { return NULL; }
    return _Head->buffer;
}

s32 DynOS_Goddard_GetSize() {
    GoddardHeadEntry* _Head = DynOS_Goddard_GetActiveCharacterHead();
    if (!DynOS_Goddard_LoadEntry(_Head)) { return 0; }
    return (s32) _Head->length;
}

void DynOS_Goddard_SetHead(const char* aHeadName) {
    sGoddardHeadOverride = (aHeadName != NULL) ? aHeadName : "";
}

void DynOS_Goddard_ActivatePackHead(GoddardHeadEntry* aHead) {
    if (aHead == NULL) { return; }
    aHead->enabled = true;
}

void DynOS_Goddard_DeactivatePackHead(GoddardHeadEntry* aHead) {
    if (aHead == NULL) { return; }
    aHead->enabled = false;
}

GoddardHeadEntry* DynOS_Goddard_AddHead(const char* aHeadName, const char* aFilepath, bool aIsPack) {
    if (aHeadName == NULL || *aHeadName == '\0') {
        PrintError("  ERROR: Missing head name for file \"%s\"", aFilepath);
        return NULL;
    }

    GoddardHeadEntry* _Head = (GoddardHeadEntry*) malloc(sizeof(GoddardHeadEntry));
    if (_Head == NULL) {
        PrintError("  ERROR: Unable to allocate entry: Goddard head '%s' will not be enabled", aHeadName);
        return NULL;
    }

    _Head->headName = strdup(aHeadName);
    _Head->filename = strdup(aFilepath);
    if (_Head->headName == NULL || _Head->filename == NULL) {
        PrintError("  ERROR: Unable to allocate name: Goddard head '%s' will not be enabled", aHeadName);
        free(_Head->headName);
        free(_Head->filename);
        free(_Head);
        return NULL;
    }
    _Head->enabled = !aIsPack;
    _Head->loaded = false;
    _Head->length = 0;
    _Head->buffer = NULL;

    if (aIsPack) {
        sGoddardPackHeads.push_back(_Head);
    } else {
        sGoddardModHeads.push_back(_Head);
    }

    return _Head;
}
