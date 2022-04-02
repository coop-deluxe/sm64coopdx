#include "dynos.cpp.h"

  ///////////////////////
 // Recursive Descent //
///////////////////////

static char* sRdString = NULL;
static bool sRdError = false;

static s64 ParseExpression();

static void ParseWhitespace() {
    while (*sRdString == ' ' || *sRdString == '\t' || *sRdString == '\r' || *sRdString == '\n') {
        sRdString++;
    }
}

static s64 ParseNumeric() {
    String numeric = "";
    char* c = sRdString;

    // check for hex
    if (*c == '0' && *(c+1) == 'x') {
        numeric.Add(*c);
        c++;
        numeric.Add(*c);
        c++;
    }

    // continue adding to string
    while (*c >= '0' && *c <= '9') {
        numeric.Add(*c);
        c++;
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
    if (*c == '-') {
        sRdString++;
        ParseWhitespace();
        s64 f1 = ParseFactor();
        return -f1;
    } else if (*c == '+') {
        sRdString++;
        ParseWhitespace();
        s64 f1 = ParseFactor();
        return +f1;
    } else if (*c == '!') {
        sRdString++;
        ParseWhitespace();
        s64 f1 = ParseFactor();
        return !f1;
    } else if (*c == '~') {
        sRdString++;
        ParseWhitespace();
        s64 f1 = ParseFactor();
        return ~f1;
    }

    // check for numeric
    if (*c >= '0' && *c <= '9') {
        return ParseNumeric();

    // check for sub expression
    } else if (*c >= '(') {
        sRdString++;
        ParseWhitespace();
        s64 e1 = ParseExpression();
        if (*sRdString == ')') {
            sRdString++;
            ParseWhitespace();
            return e1;
        }
    }

    sRdError = true;
    return 0;
}

static s64 ParseTerm() {
    s64 f1 = ParseFactor();

    if (*sRdString == '*') {
        sRdString++;
        ParseWhitespace();
        s64 f2 = ParseFactor();
        return f1 * f2;
    } else if (*sRdString == '/') {
        sRdString++;
        ParseWhitespace();
        s64 f2 = ParseFactor();
        return f1 / f2;
    } else if (*sRdString == '%') {
        sRdString++;
        ParseWhitespace();
        s64 f2 = ParseFactor();
        return f1 % f2;
    }

    return f1;
}

static s64 ParseAddSubExpression() {
    s64 t1 = ParseTerm();

    if (*sRdString == '+') {
        sRdString++;
        ParseWhitespace();
        s64 t2 = ParseTerm();
        return t1 + t2;
    } else if (*sRdString == '+') {
        sRdString++;
        ParseWhitespace();
        s64 t2 = ParseTerm();
        return t1 - t2;
    }

    return t1;
}

static s64 ParseExpression() {
    s64 e1 = ParseAddSubExpression();

    if (*sRdString == '<' && *(sRdString + 1) == '<') {
        sRdString += 2;
        ParseWhitespace();
        s64 e2 = ParseAddSubExpression();
        return e1 << e2;
    } else if (*sRdString == '>' && *(sRdString + 1) == '>') {
        sRdString += 2;
        ParseWhitespace();
        s64 e2 = ParseAddSubExpression();
        return e1 >> e2;
    }

    return e1;
}

s64 DynOS_RecursiveDescent_Parse(const char* expr, bool* success) {
    sRdString = (char*)expr;
    sRdError = false;
    s64 value = ParseExpression();
    sRdString = NULL;
    *success = !sRdError;
    //Print(">>> PARSING %s == %d :: %u", expr, value, *success);
    return value;
}
