#include "dynos.cpp.h"

  ////////////////////////////////
 // Should-generate-pack logic //
////////////////////////////////

static bool DynOS_PathHasExtension(const char *aPath, const char *aExtension) {
    size_t _LenStr    = strlen(aPath);
    size_t _LenSuffix = strlen(aExtension);

    if (_LenSuffix > _LenStr) {
        return false;
    }

    return strcmp(aPath + (_LenStr - _LenSuffix), aExtension) == 0;
}

static bool DynOS_PathHasExtensions(const char *aPath, std::initializer_list<const char*> aExtensions) {
    for (auto _Ext : aExtensions) {
        if (DynOS_PathHasExtension(aPath, _Ext)) {
            return true;
        }
    }

    return false;
}

static void DynOS_GetMTimeInFolderSplitByExtensions(const SysPath &aPath, std::initializer_list<const char*> aExtensions, u64 *aLatestMTimeExt, u64 *aLatestMTimeNonExt) {
    DIR *_DirPath = opendir(aPath.c_str());
    if (_DirPath) {
        struct dirent *_DirEnt = NULL;
        while ((_DirEnt = readdir(_DirPath)) != NULL) {

            // Skip . and ..
            if (SysPath(_DirEnt->d_name) == ".")  { continue; }
            if (SysPath(_DirEnt->d_name) == "..") { continue; }

            SysPath _Path = fstring("%s/%s", aPath.c_str(), _DirEnt->d_name);

            // Recursively accumulate maximum mtimes
            if (fs_sys_dir_exists(_Path.c_str())) {
                DynOS_GetMTimeInFolderSplitByExtensions(_Path, aExtensions, aLatestMTimeExt, aLatestMTimeNonExt);
                continue;
            }

            // Accumulate max mtime in the correct slot
            u64 _PathMTime = fs_sys_get_modified_time(_Path.c_str());
            if (DynOS_PathHasExtensions(_Path.c_str(), aExtensions)) {
                *aLatestMTimeExt = MAX(*aLatestMTimeExt, _PathMTime);
            } else {
                *aLatestMTimeNonExt = MAX(*aLatestMTimeNonExt, _PathMTime);
            }
        }
        closedir(_DirPath);
    }
}

static void DynOS_GetMTimeInFolderSplitBy2Extensions(const SysPath &aPath, const char * aExt1, const char *aExt2, u64 *aLatestMTimeExt1, u64 *aLatestMTimeExt2) {
    DIR *_DirPath = opendir(aPath.c_str());
    if (_DirPath) {
        struct dirent *_DirEnt = NULL;
        while ((_DirEnt = readdir(_DirPath)) != NULL) {

            // Skip . and ..
            if (SysPath(_DirEnt->d_name) == ".")  { continue; }
            if (SysPath(_DirEnt->d_name) == "..") { continue; }

            SysPath _Path = fstring("%s/%s", aPath.c_str(), _DirEnt->d_name);

            // Recursively accumulate maximum mtimes
            if (fs_sys_dir_exists(_Path.c_str())) {
                DynOS_GetMTimeInFolderSplitBy2Extensions(_Path, aExt1, aExt2, aLatestMTimeExt1, aLatestMTimeExt2);
                continue;
            }

            // Accumulate max mtime in the correct slot
            u64 _PathMTime = fs_sys_get_modified_time(_Path.c_str());
            if (DynOS_PathHasExtension(_Path.c_str(), aExt1)) {
                *aLatestMTimeExt1 = MAX(*aLatestMTimeExt1, _PathMTime);
            } else if (DynOS_PathHasExtension(_Path.c_str(), aExt2)) {
                *aLatestMTimeExt2 = MAX(*aLatestMTimeExt2, _PathMTime);
            }
        }
        closedir(_DirPath);
    }
}

static u64 DynOS_GetMTimeInFolder(const SysPath &aPath) {
    u64 _LatestMTimeSubDir = 0;

    DIR *_DirPath = opendir(aPath.c_str());
    if (_DirPath) {
        struct dirent *_DirEnt = NULL;
        while ((_DirEnt = readdir(_DirPath)) != NULL) {

            // Skip . and ..
            if (SysPath(_DirEnt->d_name) == ".")  { continue; }
            if (SysPath(_DirEnt->d_name) == "..") { continue; }

            // Check get the mtime of the file and store the max mtime
            SysPath _Path = fstring("%s/%s", aPath.c_str(), _DirEnt->d_name);
            if (fs_sys_dir_exists(_Path.c_str())) {
                u64 _PathMTime = DynOS_GetMTimeInFolder(_Path);
                _LatestMTimeSubDir = MAX(_LatestMTimeSubDir, _PathMTime);
            } else {
                u64 _PathMTime = fs_sys_get_modified_time(_Path.c_str());
                _LatestMTimeSubDir = MAX(_LatestMTimeSubDir, _PathMTime);
            }
        }
        closedir(_DirPath);
    }

    return _LatestMTimeSubDir;
}

bool DynOS_ShouldGeneratePack(const SysPath &aPackFolder, std::initializer_list<const char*> aExtensions) {
    u64 _LatestMTimeExt = 0;
    u64 _LatestMTimeNonExt = 0;

    DynOS_GetMTimeInFolderSplitByExtensions(aPackFolder, aExtensions, &_LatestMTimeExt, &_LatestMTimeNonExt);

    return _LatestMTimeExt < _LatestMTimeNonExt;
}

bool DynOS_ShouldGeneratePack2Ext(const SysPath &aPackFolder, const char *aGenExtension, const char *aSrcExtension) {
    u64 _LatestMTimeGenExt = 0;
    u64 _LatestMTimeSrcExt = 0;

    DynOS_GetMTimeInFolderSplitBy2Extensions(aPackFolder, aGenExtension, aSrcExtension, &_LatestMTimeGenExt, &_LatestMTimeSrcExt);

    return _LatestMTimeGenExt < _LatestMTimeSrcExt;
}


bool DynOS_GenFileExistsAndIsNewerThanFile(const SysPath &aGenFile, const SysPath &aSrcFile) {
    if (fs_sys_file_exists(aGenFile.c_str())) {
        // compare modified times
        u64 _MTimeGenFile    = fs_sys_get_modified_time(aGenFile.c_str());
        u64 _MTimeSourceFile = fs_sys_get_modified_time(aSrcFile.c_str());
        return (_MTimeGenFile >= _MTimeSourceFile);
    }
    return false;
}

bool DynOS_GenFileExistsAndIsNewerThanFolder(const SysPath &aGenFile, const SysPath &aSrcFolder) {
    if (fs_sys_file_exists(aGenFile.c_str())) {
        // compare modified times
        u64 _MTimeGenFile      = fs_sys_get_modified_time(aGenFile.c_str());
        u64 _MTimeSourceFolder = DynOS_GetMTimeInFolder(aSrcFolder);
        return (_MTimeGenFile >= _MTimeSourceFolder);
    }
    return false;
}

String DynOS_GetActorFolder(const Array<Pair<u64, String>> &aActorsFolders, u64 aModelIdentifier) {
    for (const auto &_Pair : aActorsFolders) {
        if (_Pair.first == aModelIdentifier) {
            return _Pair.second;
        }
    }
    return String();
}

  //////////
 // Misc //
//////////

s64 DynOS_Misc_ParseInteger(const String& _Arg, bool* found) {
    const char* argStr = _Arg.begin();
    if (argStr[0] == '0' && argStr[1] == 'x') {
        // is a hex number
        argStr += 2;
        while(*argStr != '\0') {
            if (*argStr >= '0' && *argStr <= '9') {
                // good
            } else if (*argStr >= 'a' && *argStr <= 'f') {
                // good
            } else if (*argStr >= 'A' && *argStr <= 'F') {
                // good
            } else {
                // bad character
                *found = false;
                return 0;
            }
            argStr++;
        }
    } else {
        // is a decimal number
        if (*argStr == '-' || *argStr == '+') {
            // good
            argStr++;
        }
        while(*argStr != '\0') {
            if (*argStr >= '0' && *argStr <= '9') {
                // good
            } else if (*argStr == '.') {
                // good
            } else {
                // bad character
                *found = false;
                return 0;
            }
            argStr++;
        }
    }

    *found = true;
    return _Arg.ParseInt();
}

void DynOS_Gfx_Free(GfxData* aGfxData) {
    if (aGfxData) {
        for (auto& _Node : aGfxData->mLights) {
            Delete(_Node->mData);
            Delete(_Node);
        }
        for (auto& _Node : aGfxData->mLight0s) {
            Delete(_Node->mData);
            Delete(_Node);
        }
        for (auto& _Node : aGfxData->mLightTs) {
            Delete(_Node->mData);
            Delete(_Node);
        }
        for (auto& _Node : aGfxData->mAmbientTs) {
            Delete(_Node->mData);
            Delete(_Node);
        }
        for (auto& _Node : aGfxData->mTextures) {
            Delete(_Node->mData);
            Delete(_Node);
        }
        for (auto& _Node : aGfxData->mTextureLists) {
            Delete(_Node->mData);
            Delete(_Node);
        }
        for (auto& _Node : aGfxData->mVertices) {
            Delete(_Node->mData);
            Delete(_Node);
        }
        for (auto& _Node : aGfxData->mDisplayLists) {
            Delete(_Node->mData);
            Delete(_Node);
        }
        for (auto& _Node : aGfxData->mGeoLayouts) {
            Delete(_Node->mData);
            Delete(_Node);
        }
        for (auto& _Node : aGfxData->mAnimations) {
            Delete(_Node->mData);
            Delete(_Node);
        }
        for (auto& _Node : aGfxData->mCollisions) {
            Delete(_Node->mData);
            Delete(_Node);
        }
        for (auto& _Node : aGfxData->mBehaviorScripts) {
            Delete(_Node->mData);
            Delete(_Node);
        }
        for (auto& _Node : aGfxData->mLevelScripts) {
            Delete(_Node->mData);
            Delete(_Node);
        }
        for (auto& _Node : aGfxData->mMacroObjects) {
            Delete(_Node->mData);
            Delete(_Node);
        }
        for (auto& _Node : aGfxData->mTrajectories) {
            Delete(_Node->mData);
            Delete(_Node);
        }
        for (auto& _Node : aGfxData->mMovtexs) {
            Delete(_Node->mData);
            Delete(_Node);
        }
        for (auto& _Node : aGfxData->mMovtexQCs) {
            Delete(_Node->mData);
            Delete(_Node);
        }
        for (auto& _Node : aGfxData->mRooms) {
            Delete(_Node->mData);
            Delete(_Node);
        }
        Delete(aGfxData);
    }
}

u32 DynOS_Lua_RememberVariable(GfxData* aGfxData, void* aPtr, const String& token) {
    // remember as lua pointer
    aGfxData->mLuaPointerList.Add(aPtr);

    // find existing token
    for (u32 i = 0; i < aGfxData->mLuaTokenList.Count(); i++) {
        if (aGfxData->mLuaTokenList[i] == token) {
            return i;
        }
    }

    // add token
    aGfxData->mLuaTokenList.Add(token);
    return aGfxData->mLuaTokenList.Count() - 1;
}

  ///////////////////////
 // Recursive Descent //
///////////////////////

static char* sRdString = NULL;
static bool sRdError = false;
static RDConstantFunc sRdConstantFunc = NULL;

static s64 ParseExpression();

static void ParseWhitespace() {
    while (*sRdString == ' ' || *sRdString == '\t' || *sRdString == '\r' || *sRdString == '\n') {
        sRdString++;
    }
}

static bool IsAlphabetical(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

static bool IsAlphaNumeric(char c) {
    return IsAlphabetical(c) || (c >= '0' && c <= '9');
}

static bool IsIdentifierBeginning(char c) {
    return IsAlphabetical(c) || (c == '_');
}

static bool IsIdentifierCharacter(char c) {
    return IsAlphaNumeric(c) || (c == '_');
}

static bool ParseOperator(const char* op) {
    size_t opLen = strlen(op);
    if (!strncmp(sRdString, op, opLen)) {
        sRdString += opLen;
        ParseWhitespace();
        return true;
    }
    return false;
}

static bool PeekOperator(const char* op) {
    size_t opLen = strlen(op);
    return (!strncmp(sRdString, op, opLen));
}

static s64 ParseNumeric() {
    String numeric = "";
    char* c = sRdString;

    if (*c == '0' && *(c+1) == 'x') {
        // is hex
        numeric.Add(*c);
        c++;
        numeric.Add(*c);
        c++;
        while (true) {
            if (*c >= '0' && *c <= '9') {
                // good
            } else if (*c >= 'a' && *c <= 'f') {
                // good
            } else if (*c >= 'A' && *c <= 'F') {
                // good
            } else {
                // bad
                break;
            }
            numeric.Add(*c);
            c++;
        }
    } else {
        // is decimal
        while (*c >= '0' && *c <= '9') {
            numeric.Add(*c);
            c++;
        }
    }

    // advance parsing
    sRdString = c;
    ParseWhitespace();

    // parse
    return numeric.ParseInt();
}

static s64 ParseFactor() {
    char* c = sRdString;

    // check for unary op
    if (ParseOperator("-")) {
        return -ParseFactor();
    } else if (ParseOperator("+")) {
        return +ParseFactor();
    } else if (ParseOperator("!")) {
        return !ParseFactor();
    } else if (ParseOperator("~")) {
        return ~ParseFactor();
    }

    // check for numeric
    if (*c >= '0' && *c <= '9') {
        return ParseNumeric();
    }

    // check for sub expression
    if (ParseOperator("(")) {
        s64 e1 = ParseExpression();
        if (ParseOperator(")")) {
            return e1;
        } else {
            sRdError = true;
            return 0;
        }
    }

    // check for known identifier
    if (IsIdentifierBeginning(*c)) {
        String identifier = "";
        char* cTmp = c;
        while (IsIdentifierCharacter(*cTmp)) {
            identifier.Add(*cTmp);
            cTmp++;
        }

        if (sRdConstantFunc != NULL) {
            bool constantFound = false;
            s64 constantValue = sRdConstantFunc(identifier, &constantFound);
            if (constantFound) {
                sRdString = cTmp;
                return constantValue;
            }
        }
    }

    sRdError = true;
    return 0;
}

static s64 ParseTerm() {
    s64 f1 = ParseFactor();

    while (PeekOperator("*") || PeekOperator("/") || PeekOperator("%")) {
        if (ParseOperator("*")) {
            f1 *= ParseFactor();
        } else if (ParseOperator("/")) {
            f1 /= ParseFactor();
        } else if (ParseOperator("%")) {
            f1 %= ParseFactor();
        }
    }

    return f1;
}

static s64 ParseAddSubExpression() {
    s64 t1 = ParseTerm();

    while (PeekOperator("+") || PeekOperator("-")) {
        if (ParseOperator("+")) {
            t1 += ParseTerm();
        } else if (ParseOperator("-")) {
            t1 -= ParseTerm();
        }
    }

    return t1;
}

static s64 ParseShiftExpression() {
    s64 e1 = ParseAddSubExpression();

    while (PeekOperator("<<") || PeekOperator(">>")) {
        if (ParseOperator("<<")) {
            e1 = e1 << ParseAddSubExpression();
        } else if (ParseOperator(">>")) {
            e1 = e1 >> ParseAddSubExpression();
        }
    }

    return e1;
}

static s64 ParseBitAndExpression() {
    s64 e1 = ParseShiftExpression();

    while (PeekOperator("&")) {
        if (ParseOperator("&")) {
            e1 &= ParseShiftExpression();
        }
    }

    return e1;
}

static s64 ParseBitXorExpression() {
    s64 e1 = ParseBitAndExpression();

    while (PeekOperator("^")) {
        if (ParseOperator("^")) {
            e1 ^= ParseBitAndExpression();
        }
    }

    return e1;
}

static s64 ParseBitOrExpression() {
    s64 e1 = ParseBitXorExpression();

    while (PeekOperator("|")) {
        if (ParseOperator("|")) {
            e1 |= ParseBitXorExpression();
        }
    }

    return e1;
}

static s64 ParseExpression() {
    return ParseBitOrExpression();
}

s64 DynOS_RecursiveDescent_Parse(const char* expr, bool* success, RDConstantFunc func) {
    sRdString = (char*)expr;
    sRdError = false;
    sRdConstantFunc = func;
    s64 value = ParseExpression();
    if (strlen(sRdString) > 0) {
        sRdError = true;
    }
    sRdString = NULL;
    *success = !sRdError;
    return value;
}
