#ifndef DYNOS_CPP_H
#define DYNOS_CPP_H
#ifdef __cplusplus

#include "dynos.h"

extern "C" {
#include "engine/behavior_script.h"
#include "engine/math_util.h"
#include "game/moving_texture.h"
#include "pc/djui/djui_console.h"
#include "pc/fs/fmem.h"
}

#define FUNCTION_CODE   (u32) 0x434E5546
#define POINTER_CODE    (u32) 0x52544E50
#define LUA_VAR_CODE    (u32) 0x5641554C
#define TEX_REF_CODE    (u32) 0x52584554

#define MOD_PACK_INDEX 99

//
// Enums
//

enum {
    DATA_TYPE_NONE = 0,
    DATA_TYPE_LIGHT,
    DATA_TYPE_TEXTURE,
    DATA_TYPE_VERTEX,
    DATA_TYPE_DISPLAY_LIST,
    DATA_TYPE_GEO_LAYOUT,
    DATA_TYPE_ANIMATION_VALUE,
    DATA_TYPE_ANIMATION_INDEX,
    DATA_TYPE_ANIMATION,
    DATA_TYPE_ANIMATION_TABLE,
    DATA_TYPE_GFXDYNCMD,
    DATA_TYPE_COLLISION,
    DATA_TYPE_LEVEL_SCRIPT,
    DATA_TYPE_MACRO_OBJECT,
    DATA_TYPE_TRAJECTORY,
    DATA_TYPE_MOVTEX,
    DATA_TYPE_MOVTEXQC,
    DATA_TYPE_ROOMS,
    DATA_TYPE_LIGHT_T,
    DATA_TYPE_AMBIENT_T,
    DATA_TYPE_TEXTURE_LIST,
    DATA_TYPE_TEXTURE_RAW,
    DATA_TYPE_BEHAVIOR_SCRIPT,
    DATA_TYPE_UNUSED,
    DATA_TYPE_LIGHT_0,
};

enum {
    DOPT_NONE = 0,

    DOPT_TOGGLE,
    DOPT_CHOICE,
    DOPT_SCROLL,
    DOPT_BIND,
    DOPT_BUTTON,
    DOPT_SUBMENU,

    // These ones are used by the Warp to Level built-in submenu
    DOPT_CHOICELEVEL,
    DOPT_CHOICEAREA,
    DOPT_CHOICESTAR,
    DOPT_CHOICEPARAM,
};

//
// DynOS Binary file struct
//

class BinFile {
private:
    void Grow(s32 newSize) {
        if (newSize >= mCapacity) {
            mCapacity = MAX(newSize, MAX(256, mCapacity * 2));
            u8 *newBuffer = (u8 *) calloc(mCapacity, 1);
            if (mData) {
                memcpy(newBuffer, mData, mSize);
                free(mData);
            }
            mData = newBuffer;
        }
        mSize = MAX(mSize, newSize);
    }

public:
    inline s32 Size() const { return mSize; }
    inline s32 Offset() const { return mOffset; }
    inline bool EoF() const { return mOffset >= mSize; }
    inline void SetOffset(s32 aOffset) const { mOffset = aOffset; }
    inline const char *GetFilename() const { return mFilename; }

public:
    static BinFile *OpenR(const char *aFilename) {
        FILE *f = f_open_r(aFilename);
        if (f) {
            f_seek(f, 0, SEEK_END);
            BinFile *_BinFile = (BinFile *) calloc(1, sizeof(BinFile));
            _BinFile->mFilename = (const char *) memcpy(calloc(strlen(aFilename) + 1, 1), aFilename, strlen(aFilename));
            _BinFile->mReadOnly = true;
            _BinFile->Grow(f_tell(f));
            f_rewind(f);
            f_read(_BinFile->mData, 1, _BinFile->mSize, f);
            f_close(f);
            return _BinFile;
        }
        return NULL;
    }

    static BinFile *OpenW(const char *aFilename) {
        BinFile *_BinFile = (BinFile *) calloc(1, sizeof(BinFile));
        _BinFile->mFilename = (const char *) memcpy(calloc(strlen(aFilename) + 1, 1), aFilename, strlen(aFilename));
        _BinFile->mReadOnly = false;
        return _BinFile;
    }

    static BinFile *OpenB(const u8 *aBuffer, s32 aSize) {
        BinFile *_BinFile = (BinFile *) calloc(1, sizeof(BinFile));
        _BinFile->mReadOnly = true;
        _BinFile->Grow(aSize);
        memcpy(_BinFile->mData, aBuffer, aSize);
        return _BinFile;
    }

    static void Close(BinFile *&aBinFile) {
        if (aBinFile) {
            if (!aBinFile->mReadOnly && aBinFile->mFilename && aBinFile->mData && aBinFile->mSize) {
                FILE *f = fopen(aBinFile->mFilename, "wb");
                if (f) {
                    fwrite(aBinFile->mData, 1, aBinFile->mSize, f);
                    fclose(f);
                }
            }
            if (aBinFile->mFilename) free((void *) aBinFile->mFilename);
            if (aBinFile->mData) free(aBinFile->mData);
            free(aBinFile);
        }
    }

public:
    template <typename T>
    T Read() const {
        T _Item = { 0 };
        if (mOffset + sizeof(T) <= mSize) {
            memcpy(&_Item, mData + mOffset, sizeof(T));
            mOffset += sizeof(T);
        }
        return _Item;
    }

    template <typename T>
    T *Read(T *aBuffer, s32 aCount) const {
        if (mOffset + aCount * sizeof(T) <= mSize) {
            memcpy(aBuffer, mData + mOffset, aCount * sizeof(T));
            mOffset += aCount * sizeof(T);
        }
        return aBuffer;
    }

    template <typename T>
    void Write(const T& aItem) {
        if (!mReadOnly) {
            Grow(mOffset + sizeof(T));
            memcpy(mData + mOffset, &aItem, sizeof(T));
            mOffset += sizeof(T);
        }
    }

    template <typename T>
    void Write(const T *aBuffer, s32 aCount) {
        if (!mReadOnly) {
            Grow(mOffset + aCount * sizeof(T));
            memcpy(mData + mOffset, aBuffer, aCount * sizeof(T));
            mOffset += aCount * sizeof(T);
        }
    }

    void Skip(s32 aAmount) const {
        mOffset += aAmount;
    }

private:
    const char *mFilename;
    u8 *mData;
    s32 mSize;
    s32 mCapacity;
    mutable s32 mOffset;
    bool mReadOnly;
};

//
// DynOS Array
// A vector-like array, implemented to be processed really fast, but cannot handle C++ complex classes like std::string
//

template <typename T>
class Array {
public:
    inline Array() : mBuffer(NULL), mCount(0), mCapacity(0) {
    }

    inline Array(const std::initializer_list<T> &aList) : mBuffer(NULL), mCount(0), mCapacity(0) {
        Resize(aList.size());
        memcpy(mBuffer, aList.begin(), mCount * sizeof(T));
    }

    inline Array(const T *aBegin, const T *aEnd) : mBuffer(NULL), mCount(0), mCapacity(0) {
        Resize(aEnd - aBegin);
        memcpy(mBuffer, aBegin, mCount * sizeof(T));
    }

    inline Array(const Array &aOther) : mBuffer(NULL), mCount(0), mCapacity(0) {
        Resize(aOther.mCount);
        memcpy(mBuffer, aOther.mBuffer, mCount * sizeof(T));
    }

    inline void operator=(const Array &aOther) {
        Resize(aOther.mCount);
        memcpy(mBuffer, aOther.mBuffer, mCount * sizeof(T));
    }

    inline ~Array() {
        Clear();
    }

public:
    void Resize(s32 aCount) {
        if (aCount > mCapacity) {
            mCapacity = MAX(aCount, MAX(16, mCapacity * 2));
            T *_Buffer = (T *) calloc(mCapacity, sizeof(T));
            if (mBuffer) {
                memcpy(_Buffer, mBuffer, mCount * sizeof(T));
                free(mBuffer);
            }
            mBuffer = _Buffer;
        }
        mCount = aCount;
    }

    void Add(const T& aItem) {
        Resize(mCount + 1);
        mBuffer[mCount - 1] = aItem;
    }

    void Remove(s32 aIndex) {
        memmove(mBuffer + aIndex, mBuffer + aIndex + 1, (mCount - aIndex - 1) * sizeof(T));
        mCount--;
    }

    void Pop() {
        mCount--;
    }

    void RemoveAll() {
        mCount = 0;
    }

    void Clear() {
        if (mBuffer) free(mBuffer);
        mBuffer   = NULL;
        mCount    = 0;
        mCapacity = 0;
    }

    s32 Find(const T& aItem) const {
        for (s32 i = 0; i != mCount; ++i) {
            if (mBuffer[i] == aItem) {
                return i;
            }
        }
        return -1;
    }

    template <typename Predicate>
    s32 FindIf(Predicate aPredicate) const {
        for (s32 i = 0; i != mCount; ++i) {
            if (aPredicate(mBuffer[i])) {
                return i;
            }
        }
        return -1;
    }

public:
    inline const T *begin() const { return mBuffer; }
    inline const T *end() const { return mBuffer + mCount; }
    inline T *begin() { return mBuffer; }
    inline T *end() { return mBuffer + mCount; }

    inline const T &operator[](s32 aIndex) const { return mBuffer[aIndex]; }
    inline T &operator[](s32 aIndex) { return mBuffer[aIndex]; }

    inline s32 Count() const { return mCount; }
    inline bool Empty() const { return mCount == 0; }

public:
    void Read(BinFile *aFile) {
        s32 _Length = aFile->Read<s32>();
        Resize(_Length);
        aFile->Read<T>(mBuffer, _Length);
    }

    void Write(BinFile *aFile) const {
        aFile->Write<s32>(mCount);
        aFile->Write<T>(mBuffer, mCount);
    }

private:
    T *mBuffer;
    s32 mCount;
    s32 mCapacity;
};

//
// DynOS String
// A fixed-size string that doesn't require heap memory allocation
//

#define STRING_SIZE 255
class String {
public:
    inline String() : mCount(0) {
        mBuffer[0] = 0;
    }

    inline String(const char *aString) : mCount(0) {
        if (aString) {
            u64 _Length = strlen(aString);
            mCount = MIN(_Length, STRING_SIZE - 1);
            memcpy(mBuffer, aString, _Length);
        }
        mBuffer[mCount] = 0;
    }

    template <typename... Args>
    inline String(const char *aFmt, Args... aArgs) : mCount(0) {
        snprintf(mBuffer, STRING_SIZE, aFmt, aArgs...);
        mCount = (u8) strlen(mBuffer);
        mBuffer[mCount] = 0;
    }

    inline String(const String &aOther) : mCount(0) {
        mCount = aOther.mCount;
        memcpy(mBuffer, aOther.mBuffer, mCount);
        mBuffer[mCount] = 0;
    }

    inline void operator=(const String &aOther) {
        mCount = aOther.mCount;
        memcpy(mBuffer, aOther.mBuffer, mCount);
        mBuffer[mCount] = 0;
    }

public:
    void Add(char aChar) {
        if (mCount == STRING_SIZE - 1) return;
        mBuffer[mCount++] = aChar;
        mBuffer[mCount] = 0;
    }

    void Remove(s32 aIndex) {
        memmove(mBuffer + aIndex, mBuffer + aIndex + 1, (mCount-- - aIndex - 1));
        mBuffer[mCount] = 0;
    }

    void RemoveAll() {
        mCount = 0;
        mBuffer[0] = 0;
    }

    void Clear() {
        mCount = 0;
        mBuffer[0] = 0;
    }

    s32 Find(char aChar, s32 aStart = 0) const {
        for (u8 i = (u8) aStart; i < mCount; ++i) {
            if (mBuffer[i] == aChar) {
                return (s32) i;
            }
        }
        return -1;
    }

    s32 Find(const char *aString, s32 aStart = 0) const {
        const char *_Ptr = strstr(mBuffer + aStart, aString);
        if (_Ptr) return (s32) (_Ptr - mBuffer);
        return -1;
    }

    s32 FindLast(char aChar) const {
        for (u8 i = mCount; i != 0; --i) {
            if (mBuffer[i - 1] == aChar) {
                return (s32) (i - 1);
            }
        }
        return -1;
    }

    String SubString(s32 aStart, s32 aCount = STRING_SIZE - 1) const {
        if (aStart >= mCount) return String();
        if (aCount < 0) aCount = STRING_SIZE - 1;
        aCount = MIN(aCount, mCount - aStart);
        String _String;
        _String.mCount = aCount;
        memcpy(_String.mBuffer, mBuffer + aStart, aCount);
        _String.mBuffer[aCount] = 0;
        return _String;
    }

public:
    inline const char *begin() const { return mBuffer; }
    inline const char *end() const { return mBuffer + mCount; }
    inline char *begin() { return mBuffer; }
    inline char *end() { return mBuffer + mCount; }

    inline const char &operator[](s32 aIndex) const { return mBuffer[aIndex]; }
    inline char &operator[](s32 aIndex) { return mBuffer[aIndex]; }

    inline s32 Length() const { return (s32) mCount; }
    inline bool Empty() const { return mCount == 0; }

public:
    bool OPTIMIZE_O3 operator==(const char *aString) const {
        return !strcmp(mBuffer, aString);
    }

    bool OPTIMIZE_O3 operator==(const String &aOther) const {
        return !strcmp(mBuffer, aOther.mBuffer);
    }

    bool OPTIMIZE_O3 operator!=(const char *aString) const {
        return strcmp(mBuffer, aString);
    }

    bool OPTIMIZE_O3 operator!=(const String &aOther) const {
        return strcmp(mBuffer, aOther.mBuffer);
    }

public:
    void Read(BinFile *aFile) {
        mCount = aFile->Read<u8>();
        aFile->Read<char>(mBuffer, mCount);
        mBuffer[mCount] = 0;
    }

    void Write(BinFile *aFile) const {
        aFile->Write<u8>(mCount);
        aFile->Write<char>(mBuffer, mCount);
    }

    s32 ParseInt() const {
        s32 i = 0;
        if (mBuffer[1] == 'x') {
            sscanf(mBuffer + 2, "%x", &i);
        } else {
            sscanf(mBuffer, "%d", &i);
        }
        return i;
    }

    f32 ParseFloat() const {
        f32 f = 0.f;
        sscanf(mBuffer, "%f", &f);
        return f;
    }

private:
    char mBuffer[STRING_SIZE];
    u8 mCount;
};
static_assert(sizeof(String) == (STRING_SIZE + 1), "sizeof(String) must be (STRING_SIZE + 1)");

//
// Types
//

template <typename U, typename V>
using Pair = std::pair<U, V>;

typedef std::string SysPath;
typedef struct MovtexQuadCollection MovtexQC;

class NoCopy {
  protected:
    NoCopy() {}
    ~NoCopy() {}
  private:
    NoCopy(const NoCopy &) = delete;
    void operator=(const NoCopy &) = delete;
};

struct TexData : NoCopy {
    Array<u8> mPngData;
    Array<u8> mRawData;
    s32 mRawWidth  = -1;
    s32 mRawHeight = -1;
    s32 mRawFormat = -1;
    s32 mRawSize   = -1;
    bool mUploaded = false;
};

struct AnimData : NoCopy {
    s16 mFlags = 0;
    s16 mUnk02 = 0;
    s16 mUnk04 = 0;
    s16 mUnk06 = 0;
    s16 mUnk08 = 0;
    Pair<String, s16> mUnk0A;
    Pair<String, Array<u16>> mValues;
    Pair<String, Array<u16>> mIndex;
    u32 mLength = 0;
};

template <typename T>
struct DataNode : NoCopy {
    String mName;
    T* mData = NULL;
    u32 mSize = 0;
    Array<String> mTokens;
    u64 mModelIdentifier = 0;
    u64 mLoadIndex = 0;
    u8 mFlags = 0;
};
template <typename T>
using DataNodes = Array<DataNode<T>*>;

struct GfxContext {
    DataNode<TexData>* mCurrentTexture = NULL;
    DataNode<TexData>* mCurrentPalette = NULL;
};

template <typename T>
using AnimBuffer = Pair<String, Array<T>>;
struct GfxData : NoCopy {

    // Model data
    DataNodes<Lights1> mLights;
    DataNodes<Lights0> mLight0s;
    DataNodes<Light_t> mLightTs;
    DataNodes<Ambient_t> mAmbientTs;
    DataNodes<TexData> mTextures;
    DataNodes<TexData*> mTextureLists;
    DataNodes<Vtx> mVertices;
    DataNodes<Gfx> mDisplayLists;
    DataNodes<GeoLayout> mGeoLayouts;
    DataNodes<Collision> mCollisions;
    DataNodes<BehaviorScript> mBehaviorScripts;
    DataNodes<LevelScript> mLevelScripts;
    DataNodes<MacroObject> mMacroObjects;
    DataNodes<Trajectory> mTrajectories;
    DataNodes<Movtex> mMovtexs;
    DataNodes<MovtexQC> mMovtexQCs;
    DataNodes<u8> mRooms;

    // Animation data
    Array<AnimBuffer<s16> *> mAnimValues;
    Array<AnimBuffer<u16> *> mAnimIndices;
    DataNodes<AnimData> mAnimations;
    Array<Pair<String, void *>> mAnimationTable;

    // Skip bin output of children
    Array<DataNode<GeoLayout> *> mChildGeoLayouts;

    // Current
    u64 mLoadIndex = 0;
    s32 mErrorCount = 0;
    u32 mModelIdentifier = 0;
    s32 mModIndex = 0;
    SysPath mPackFolder;
    Array<void *> mPointerList;
    Array<Pair<const void*, const void*>> mPointerOffsetList;
    Array<void *> mLuaPointerList;
    Array<String> mLuaTokenList;
    GfxContext mGfxContext;
    Array<GfxContext> mGeoNodeStack;
};

struct ActorGfx {
    GfxData *mGfxData = NULL;
    GraphNode *mGraphNode = NULL;
    s32 mPackIndex = 0;
};

struct PackData {
    s32 mIndex;
    bool mEnabled;
    SysPath mPath;
    String mDisplayName;
    Array<Pair<const char *, GfxData *>> mGfxData;
    Array<DataNode<TexData>*> mTextures;
    bool mLoaded;
};

typedef Pair<String, const u8 *> Label;
struct DynosOption : NoCopy {
    String mName;
    String mConfigName; // Name used in the config file
    Label mLabel;
    Label mTitle; // Full caps label, displayed with colored font
    DynosOption *mPrev;
    DynosOption *mNext;
    DynosOption *mParent;
    bool mDynos; // true from create, false from convert
    u8 mType;

    // TOGGLE
    struct Toggle : NoCopy {
        bool *mTog;
    } mToggle;

    // CHOICE
    struct Choice : NoCopy {
        Array<Label> mChoices;
        s32 *mIndex;
    } mChoice;

    // SCROLL
    struct Scroll : NoCopy {
        s32 mMin;
        s32 mMax;
        s32 mStep;
        s32 *mValue;
    } mScroll;

    // BIND
    struct Bind : NoCopy {
        u32 mMask;
        u32 *mBinds;
        s32 mIndex;
    } mBind;

    // BUTTON
    struct Button : NoCopy {
        String mFuncName;
    } mButton;

    // SUBMENU
    struct Submenu : NoCopy {
        DynosOption *mChild;
        bool mEmpty;
    } mSubMenu;
};
typedef bool (*DynosLoopFunc)(DynosOption *, void *);

struct BuiltinTexInfo {
    const char* identifier;
    const void* pointer;
    const char* path;
    s32 width;
    s32 height;
    s32 bitSize;
};

struct LvlCmd {
    u8 mType;
    u8 mSize;
};

//
// Utils
//

template <typename T>
T* New(u64 aCount = 1llu) {
    T *_Ptr = (T *) calloc(aCount, sizeof(T));
    for (u64 i = 0; i != aCount; ++i) {
        new (_Ptr + i) T(); // Calls the constructor of type T at address (_Ptr + i)
    }
    return _Ptr;
}

template <typename T>
void Delete(T *& aPtr) {
    if (aPtr) {
        aPtr->~T();
        free(aPtr);
    }
    aPtr = NULL;
}

template <typename T = void>
Array<String> Split(const char *aBuffer, const String &aDelimiters, const String &aEndCharacters = {}, bool aHandleDoubleQuotedStrings = false) {
    Array<String> _Tokens;
    String _Token;
    bool _TreatSpaceAsChar = false;
    u64 _Length = strlen(aBuffer);
    for (u64 i = 0; i <= _Length; ++i) {
        if (i == _Length || aDelimiters.Find(aBuffer[i]) != -1) {
            if (aBuffer[i] == ' ' && _TreatSpaceAsChar) {
                _Token.Add(aBuffer[i]);
            } else {
                if (!_Token.Empty()) {
                    _Tokens.Add(_Token);
                    _Token.Clear();
                }
                if (aEndCharacters.Find(aBuffer[i]) != -1) {
                    break;
                }
            }
        } else {
            if (aBuffer[i] == '\"' && aHandleDoubleQuotedStrings) {
                _TreatSpaceAsChar = !_TreatSpaceAsChar;
            } else {
                _Token.Add(aBuffer[i]);
            }
        }
    }
    return _Tokens;
}

template <typename T>
T *CopyBytes(const T *aPtr, u64 aSize) {
    T *_Ptr = (T *) calloc(1, aSize);
    memcpy(_Ptr, aPtr, aSize);
    return _Ptr;
}

template <typename... Args>
void PrintNoNewLine(const char *aFmt, Args... aArgs) {
    printf(aFmt, aArgs...);
    fflush(stdout);
}

template <typename... Args>
void Print(const char *aFmt, Args... aArgs) {
    printf(aFmt, aArgs...);
    printf("\r\n");
    fflush(stdout);
}

template <typename... Args>
void PrintConsole(enum ConsoleMessageLevel level, const char *aFmt, Args... aArgs) {
    snprintf(gDjuiConsoleTmpBuffer, CONSOLE_MAX_TMP_BUFFER, aFmt, aArgs...);
    sys_swap_backslashes(gDjuiConsoleTmpBuffer);
    djui_console_message_create(gDjuiConsoleTmpBuffer, level);
}

template <typename... Args>
void PrintError(const char *aFmt, Args... aArgs) {
    printf(aFmt, aArgs...);
    printf("\r\n");
    fflush(stdout);
    PrintConsole(CONSOLE_MESSAGE_ERROR, aFmt, aArgs...);
}
#define PrintDataError(...) { \
    if (aGfxData->mErrorCount == 0) Print("  ERROR!"); \
    Print(__VA_ARGS__); \
    PrintConsole(CONSOLE_MESSAGE_ERROR, __VA_ARGS__); \
    aGfxData->mErrorCount++; \
}

#if DEBUG
#define PrintDebug(...) { Print(__VA_ARGS__); }
#define PrintDebugNoNewLine(...) { PrintNoNewLine(__VA_ARGS__); }
#else
#define PrintDebug(...)
#define PrintDebugNoNewLine(...)
#endif

template <typename... Args>
SysPath fstring(const char *aFmt, Args... aArgs) {
    char buffer[1024];
    snprintf(buffer, 1024, aFmt, aArgs...);
    return SysPath(buffer);
}

// Wraps the static into a function, to call the constructor on first use
#define STATIC_STORAGE(type, name)  \
static type &__##name() {           \
    static type s##name;            \
    return s##name;                 \
}

//
// Main
//

void *DynOS_SwapCmd(void *aCmd);
void *DynOS_UpdateCmd(void *aCmd);
void DynOS_UpdateGfx();
bool DynOS_IsTransitionActive();
void DynOS_Mod_Update();
void DynOS_Mod_Shutdown();

//
// Gfx
//

void DynOS_Gfx_Init();
void DynOS_Gfx_Free(GfxData *aGfxData);

//
// String
//

u8 *DynOS_String_Convert(const char *aString, bool aHeapAlloc);
u8 *DynOS_String_Decapitalize(u8 *aStr64);
s32 DynOS_String_Length(const u8 *aStr64);
s32 DynOS_String_WidthChar64(u8 aChar64);
s32 DynOS_String_Width(const u8 *aStr64);

//
// Geo
//

//
// Levels
//

void DynOS_Level_Init();
s8 DynOS_Level_GetCourse(s32 aLevel);
void DynOS_Level_Override(void* originalScript, void* newScript, s32 modIndex);
void DynOS_Level_Unoverride();
const void *DynOS_Level_GetScript(s32 aLevel);
s32 DynOS_Level_GetModIndex(s32 aLevel);
bool DynOS_Level_IsVanillaLevel(s32 aLevel);
s16 *DynOS_Level_GetWarp(s32 aLevel, s32 aArea, u8 aWarpId);
s16 *DynOS_Level_GetWarpEntry(s32 aLevel, s32 aArea);
s16 *DynOS_Level_GetWarpDeath(s32 aLevel, s32 aArea);
u64 DynOS_Level_CmdGet(void *aCmd, u64 aOffset);
LvlCmd *DynOS_Level_CmdNext(LvlCmd *aCmd);
void DynOS_Level_ParseScript(const void *aScript, s32 (*aPreprocessFunction)(u8, void *));

//
// Warps
//

void *DynOS_Warp_Update(void *aCmd, bool aIsLevelInitDone);
bool DynOS_Warp_ToWarpNode(s32 aLevel, s32 aArea, s32 aAct, s32 aWarpId);
bool DynOS_Warp_ToLevel(s32 aLevel, s32 aArea, s32 aAct);
bool DynOS_Warp_RestartLevel();
bool DynOS_Warp_ExitLevel(s32 aDelay);
bool DynOS_Warp_ToCastle(s32 aLevel);

//
// Builtin
//

const void*      DynOS_Builtin_ScriptPtr_GetFromName(const char* aDataName);
const char*      DynOS_Builtin_ScriptPtr_GetFromData(const void* aData);
const GeoLayout* DynOS_Builtin_Actor_GetFromName(const char* aDataName);
const char*      DynOS_Builtin_Actor_GetFromData(const GeoLayout* aData);
const GeoLayout* DynOS_Builtin_Actor_GetFromIndex(s32 aIndex);
const char*      DynOS_Builtin_Actor_GetNameFromIndex(s32 aIndex);
s32              DynOS_Builtin_Actor_GetCount();
const GeoLayout* DynOS_Builtin_LvlGeo_GetFromName(const char* aDataName);
const char*      DynOS_Builtin_LvlGeo_GetFromData(const GeoLayout* aData);
const Collision* DynOS_Builtin_Col_GetFromName(const char* aDataName);
const char*      DynOS_Builtin_Col_GetFromData(const Collision* aData);
const Animation *DynOS_Builtin_Anim_GetFromName(const char *aDataName);
const char *     DynOS_Builtin_Anim_GetFromData(const Animation *aData);
const Texture*   DynOS_Builtin_Tex_GetFromName(const char* aDataName);
const char*      DynOS_Builtin_Tex_GetFromData(const Texture* aData);
const char*      DynOS_Builtin_Tex_GetNameFromFileName(const char* aDataName);
const struct BuiltinTexInfo* DynOS_Builtin_Tex_GetInfoFromName(const char* aDataName);
const void*      DynOS_Builtin_Func_GetFromName(const char* aDataName);
const void*      DynOS_Builtin_Func_GetFromIndex(s32 aIndex);
const char *     DynOS_Builtin_Func_GetNameFromIndex(s64 aIndex);
s32              DynOS_Builtin_Func_GetIndexFromData(const void* aData);

//
// Pack Manager
//

s32 DynOS_Pack_GetCount();
void DynOS_Pack_SetEnabled(PackData* aPack, bool aEnabled);
PackData* DynOS_Pack_GetFromIndex(s32 aIndex);
PackData* DynOS_Pack_GetFromPath(const SysPath& aPath);
PackData* DynOS_Pack_Add(const SysPath& aPath);
Pair<const char *, GfxData *>* DynOS_Pack_GetActor(PackData* aPackData, const char* aActorName);
void DynOS_Pack_AddActor(PackData* aPackData, const char* aActorName, GfxData* aGfxData);
DataNode<TexData>* DynOS_Pack_GetTex(PackData* aPackData, const char* aTexName);
void DynOS_Pack_AddTex(PackData* aPackData, DataNode<TexData>* aTexData);

//
// Actor Manager
//

void DynOS_Actor_AddCustom(const SysPath &aFilename, const char *aActorName);
const void *DynOS_Actor_GetLayoutFromName(const char *aActorName);
ActorGfx* DynOS_Actor_GetActorGfx(const GraphNode* aGraphNode);
void DynOS_Actor_Valid(const void* aGeoref, ActorGfx& aActorGfx);
void DynOS_Actor_Invalid(const void* aGeoref, s32 aPackIndex);
void DynOS_Actor_Override(struct Object* obj, void** aSharedChild);
void DynOS_Actor_Override_All(void);
void DynOS_Actor_ModShutdown();

//
// Anim Manager
//

void DynOS_Anim_Swap(void *aPtr);

//
// Tex Manager
//

void DynOS_Tex_Valid(GfxData* aGfxData);
void DynOS_Tex_Invalid(GfxData* aGfxData);
void DynOS_Tex_Update();
u8 *DynOS_Tex_ConvertToRGBA32(const u8 *aData, u64 aLength, s32 aFormat, s32 aSize, const u8 *aPalette);
bool DynOS_Tex_Import(void **aOutput, void *aPtr, s32 aTile, void *aGfxRApi, void **aHashMap, void *aPool, u32 *aPoolPos, u32 aPoolSize);
void DynOS_Tex_Activate(DataNode<TexData>* aNode, bool aCustomTexture);
void DynOS_Tex_Deactivate(DataNode<TexData>* aNode);
void DynOS_Tex_AddCustom(const SysPath &aFilename, const char *aTexName);
bool DynOS_Tex_Get(const char* aTexName, struct TextureInfo* aOutTexInfo);
void DynOS_Tex_Override_Set(const char* textureName, struct TextureInfo* aOverrideTexInfo);
void DynOS_Tex_Override_Reset(const char* textureName);
void DynOS_Tex_ModShutdown();

//
// Lvl Manager
//

Array<Pair<const char*, GfxData*>> &DynOS_Lvl_GetArray();
LevelScript* DynOS_Lvl_GetScript(const char* aScriptEntryName);
void  DynOS_Lvl_Activate(s32 modIndex, const SysPath &aFilePath, const char *aLevelName);
GfxData* DynOS_Lvl_GetActiveGfx(void);
const char* DynOS_Lvl_GetToken(u32 index);
DataNode<MovtexQC>* DynOS_Lvl_GetMovtexQuadCollection(s32 index);
Trajectory* DynOS_Lvl_GetTrajectory(const char* aName);
void DynOS_Lvl_LoadBackground(void *aPtr);
void* DynOS_Lvl_Override(void *aCmd);
void DynOS_Lvl_ModShutdown();

//
// Bhv Manager
//

Array<Pair<const char *, GfxData *>> &DynOS_Bhv_GetArray();
void DynOS_Bhv_Activate(s32 modIndex, const SysPath &aFilename, const char *aBehaviorName);
GfxData *DynOS_Bhv_GetActiveGfx(BehaviorScript *bhvScript);
s32 DynOS_Bhv_GetActiveModIndex(BehaviorScript *bhvScript);
const char *DynOS_Bhv_GetToken(BehaviorScript *bhvScript, u32 index);
void DynOS_Bhv_HookAllCustomBehaviors();
void DynOS_Bhv_ModShutdown();

//
// Col Manager
//

void DynOS_Col_Activate(const SysPath &aFilePath, const char *aCollisionName);
Collision* DynOS_Col_Get(const char* collisionName);
void DynOS_Col_ModShutdown();

//
// Movtexqc Manager
//

void DynOS_MovtexQC_Register(const char* name, s16 level, s16 area, s16 type);
DataNode<MovtexQC>* DynOS_MovtexQC_GetFromId(u32 id);
DataNode<MovtexQC>* DynOS_MovtexQC_GetFromIndex(s32 index);
void DynOS_MovtexQC_ModShutdown();

//
// Model Manager
//

struct GraphNode* DynOS_Model_LoadGeo(u32* aId, enum ModelPool aModelPool, void* aAsset, bool aDeDuplicate);
struct GraphNode* DynOS_Model_LoadDl(u32* aId, enum ModelPool aModelPool, u8 aLayer, void* aAsset);
struct GraphNode* DynOS_Model_StoreGeo(u32* aId, enum ModelPool aModelPool, void* aAsset, struct GraphNode* aGraphNode);
struct GraphNode* DynOS_Model_GetGeo(u32 aId);
u32 DynOS_Model_GetIdFromAsset(void* asset);
u32 DynOS_Model_GetIdFromGraphNode(struct GraphNode* aNode);
void DynOS_Model_OverwriteSlot(u32 srcSlot, u32 dstSlot);
void DynOS_Model_ClearPool(enum ModelPool aModelPool);

//
// Bin
//

typedef s64 (*RDConstantFunc)(const String& _Arg, bool* found);

u32 DynOS_Lua_RememberVariable(GfxData* aGfxData, void* aPtr, String& token);
void DynOS_Gfx_GeneratePacks(const char* directory);
s64 DynOS_RecursiveDescent_Parse(const char* expr, bool* success, RDConstantFunc func);
void DynOS_Read_Source(GfxData *aGfxData, const SysPath &aFilename);
char *DynOS_Read_Buffer(FILE* aFile, GfxData* aGfxData);

s64 DynOS_Misc_ParseInteger(const String& _Arg, bool* found);

void DynOS_Anim_ScanFolder(GfxData *aGfxData, const SysPath &aAnimsFolder);
void DynOS_Anim_Table_Write(BinFile* aFile, GfxData* aGfxData);
void DynOS_Anim_Write(BinFile* aFile, GfxData* aGfxData);
void DynOS_Anim_Load(BinFile *aFile, GfxData *aGfxData);
void DynOS_Anim_Table_Load(BinFile *aFile, GfxData *aGfxData);

DataNode<Collision>* DynOS_Col_Parse(GfxData* aGfxData, DataNode<Collision>* aNode, bool aDisplayPercent);
void DynOS_Col_Write(BinFile* aFile, GfxData* aGfxData, DataNode<Collision> *aNode);
DataNode<Collision>* DynOS_Col_Load(BinFile *aFile, GfxData *aGfxData);
DataNode<Collision>* DynOS_Col_LoadFromBinary(const SysPath &aFilename, const char *aCollisionName);
void DynOS_Col_Generate(const SysPath &aPackFolder, Array<Pair<u64, String>> _ActorsFolders, GfxData *_GfxData);

DataNode<GeoLayout>* DynOS_Geo_Parse(GfxData* aGfxData, DataNode<GeoLayout>* aNode, bool aDisplayPercent);
void DynOS_Geo_Write(BinFile *aFile, GfxData *aGfxData, DataNode<GeoLayout> *aNode);
void DynOS_Geo_Load(BinFile *aFile, GfxData *aGfxData);

DataNode<Gfx>* DynOS_Gfx_Parse(GfxData* aGfxData, DataNode<Gfx>* aNode);
void DynOS_Gfx_Write(BinFile *aFile, GfxData *aGfxData, DataNode<Gfx> *aNode);
void DynOS_Gfx_Load(BinFile *aFile, GfxData *aGfxData);
s64 DynOS_Gfx_ParseGfxConstants(const String& _Arg, bool* found);

DataNode<Lights1>* DynOS_Lights_Parse(GfxData* aGfxData, DataNode<Lights1>* aNode);
void DynOS_Lights_Write(BinFile* aFile, GfxData* aGfxData, DataNode<Lights1> *aNode);
void DynOS_Lights_Load(BinFile *aFile, GfxData *aGfxData);

DataNode<Lights0>* DynOS_Light0_Parse(GfxData* aGfxData, DataNode<Lights0>* aNode);
void DynOS_Light0_Write(BinFile* aFile, GfxData* aGfxData, DataNode<Lights0> *aNode);
void DynOS_Light0_Load(BinFile *aFile, GfxData *aGfxData);

DataNode<Light_t>* DynOS_LightT_Parse(GfxData* aGfxData, DataNode<Light_t>* aNode);
void DynOS_LightT_Write(BinFile* aFile, GfxData* aGfxData, DataNode<Light_t> *aNode);
void DynOS_LightT_Load(BinFile *aFile, GfxData *aGfxData);

DataNode<Ambient_t>* DynOS_AmbientT_Parse(GfxData* aGfxData, DataNode<Ambient_t>* aNode);
void DynOS_AmbientT_Write(BinFile* aFile, GfxData* aGfxData, DataNode<Ambient_t> *aNode);
void DynOS_AmbientT_Load(BinFile *aFile, GfxData *aGfxData);

DataNode<MacroObject>* DynOS_MacroObject_Parse(GfxData* aGfxData, DataNode<MacroObject>* aNode, bool aDisplayPercent);
void DynOS_MacroObject_Write(BinFile* aFile, GfxData* aGfxData, DataNode<MacroObject> *aNode);
DataNode<MacroObject>* DynOS_MacroObject_Load(BinFile *aFile, GfxData *aGfxData);

DataNode<Trajectory>* DynOS_Trajectory_Parse(GfxData* aGfxData, DataNode<Trajectory>* aNode, bool aDisplayPercent);
void DynOS_Trajectory_Write(BinFile* aFile, GfxData* aGfxData, DataNode<Trajectory> *aNode);
DataNode<Trajectory>* DynOS_Trajectory_Load(BinFile *aFile, GfxData *aGfxData);

DataNode<Movtex>* DynOS_Movtex_Parse(GfxData* aGfxData, DataNode<Movtex>* aNode, bool aDisplayPercent);
void DynOS_Movtex_Write(BinFile* aFile, GfxData* aGfxData, DataNode<Movtex> *aNode);
DataNode<Movtex>* DynOS_Movtex_Load(BinFile *aFile, GfxData *aGfxData);

DataNode<MovtexQC>* DynOS_MovtexQC_Parse(GfxData* aGfxData, DataNode<MovtexQC>* aNode);
void DynOS_MovtexQC_Write(BinFile* aFile, GfxData* aGfxData, DataNode<MovtexQC> *aNode);
DataNode<MovtexQC>* DynOS_MovtexQC_Load(BinFile *aFile, GfxData *aGfxData);

DataNode<u8>* DynOS_Rooms_Parse(GfxData* aGfxData, DataNode<u8>* aNode);
void DynOS_Rooms_Write(BinFile* aFile, GfxData* aGfxData, DataNode<u8> *aNode);
DataNode<u8>* DynOS_Rooms_Load(BinFile *aFile, GfxData *aGfxData);

DataNode<TexData>* DynOS_Tex_Parse(GfxData* aGfxData, DataNode<TexData>* aNode);
void DynOS_Tex_Write(BinFile* aFile, GfxData* aGfxData, DataNode<TexData> *aNode);
DataNode<TexData>* DynOS_Tex_Load(BinFile *aFile, GfxData *aGfxData);
DataNode<TexData>* DynOS_Tex_LoadFromBinary(const SysPath &aPackFolder, const SysPath &aFilename, const char *aTexName, bool aAddToPack);
void DynOS_Tex_ConvertTextureDataToPng(GfxData *aGfxData, TexData* aTexture);
void DynOS_Tex_GeneratePack(const SysPath &aPackFolder, SysPath &aOutputFolder, bool aAllowCustomTextures);

DataNode<TexData*>* DynOS_TexList_Parse(GfxData* aGfxData, DataNode<TexData*>* aNode);
void DynOS_TexList_Write(BinFile* aFile, GfxData* aGfxData, DataNode<TexData*> *aNode);
DataNode<TexData*>* DynOS_TexList_Load(BinFile *aFile, GfxData *aGfxData);

DataNode<Vtx>* DynOS_Vtx_Parse(GfxData* aGfxData, DataNode<Vtx>* aNode);
void DynOS_Vtx_Write(BinFile* aFile, GfxData* aGfxData, DataNode<Vtx> *aNode);
void DynOS_Vtx_Load(BinFile *aFile, GfxData *aGfxData);

void DynOS_Pointer_Lua_Write(BinFile* aFile, u32 index, GfxData* aGfxData);
void DynOS_Pointer_Write(BinFile* aFile, const void* aPtr, GfxData* aGfxData);
void *DynOS_Pointer_Load(BinFile *aFile, GfxData *aGfxData, u32 aValue, u8* outFlags);

void DynOS_GfxDynCmd_Load(BinFile *aFile, GfxData *aGfxData);

GfxData *DynOS_Actor_LoadFromBinary(const SysPath &aPackFolder, const char *aActorName, const SysPath &aFilename, bool aAddToPack);
void DynOS_Actor_GeneratePack(const SysPath &aPackFolder);

DataNode<LevelScript>* DynOS_Lvl_Parse(GfxData* aGfxData, DataNode<LevelScript>* aNode, bool aDisplayPercent);
GfxData *DynOS_Lvl_LoadFromBinary(const SysPath &aFilename, const char *aLevelName);
void DynOS_Lvl_GeneratePack(const SysPath &aPackFolder);
s64 DynOS_Lvl_ParseLevelScriptConstants(const String& _Arg, bool* found);

void DynOS_Lvl_Validate_Begin();
bool DynOS_Lvl_Validate_RequirePointer(u32 value);

DataNode<BehaviorScript> *DynOS_Bhv_Parse(GfxData *aGfxData, DataNode<BehaviorScript> *aNode, bool aDisplayPercent);
GfxData *DynOS_Bhv_LoadFromBinary(const SysPath &aFilename, const char *aBehaviorName);
void DynOS_Bhv_GeneratePack(const SysPath &aPackFolder);
s64 DynOS_Bhv_ParseBehaviorScriptConstants(const String &_Arg, bool *found);
s64 DynOS_Bhv_ParseBehaviorIntegerScriptConstants(const String &_Arg, bool *found);

s64 DynOS_Common_ParseBhvConstants(const String &_Arg, bool *found);
s64 DynOS_Common_ParseModelConstants(const String &_Arg, bool *found);

bool DynOS_Bin_IsCompressed(const SysPath &aFilename);
bool DynOS_Bin_Compress(const SysPath &aFilename);
BinFile *DynOS_Bin_Decompress(const SysPath &aFilename);

void DynOS_Add_Scroll_Target(u32 index, const char *name, u32 offset, u32 size);

#endif
#endif
