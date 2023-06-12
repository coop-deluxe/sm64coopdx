#include "dynos.cpp.h"

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

u32 DynOS_Lua_RememberVariable(GfxData* aGfxData, void* aPtr, String& token) {
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
