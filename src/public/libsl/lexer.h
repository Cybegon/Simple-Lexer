#ifndef SMALLMOUSE_LEXER_H
#define SMALLMOUSE_LEXER_H

#include "config.h"

#define SL_LEX_FAIL         FALSE
#define SL_LEX_SUCCESS      TRUE
#define SL_LEX_RET_TOK      3

typedef struct SLString SLString;
typedef struct SLSourceLocation SLSourceLocation;
typedef struct SLLexerContext SLLexerContext;
typedef struct SLLexList SLLexList;
typedef struct SLPunctuatorList SLPunctuatorList;
typedef struct SLToken SLToken;
typedef struct SLUserData SLUserData;

typedef SLToken(*SLLexer)(SLLexerContext* ctx);
typedef dint(*SLLexStage)(SLLexerContext* ctx, dint* LastChar, SLToken* token);

typedef void(*SLUserHandler)(SLLexerContext* ctx, void* userData);

struct SLSourceLocation {
    duint64 line;
    duint64 col;
    duint64 pos;
};

struct SLString {
    char    data[2048];
    duint64 len;
};

struct SLUserData {
    SLUserHandler handler;
    void* userData;
};

struct SLLexList {
    SLTokenType tokenType;
    SLString    tokenName;
    dint32      tokenInfo;
    SLString    lexeme;

    SLUserData  userData;
};

struct SLLexerContext {
    SL_FILE*           curFile;
    const SLLexList*   lexemeList;
    const SLLexStage*  lexStageList;

    SLSourceLocation   CurLoc;// = { 0 };
    SLSourceLocation   LexLoc;// = { 1, 0 };
    SLString           IdentifierStr;// = { 0 };

    SLLexer lex;

    duint32 lastError;
};

struct SLToken {
    SLTokenType type;
    SLString    typeName;
    dint32      tokenInfo;

    union {
        double  value;
        char*   identString;
    };

    SLSourceLocation sourceLocation;
};

SLLexerContext* sl_createLexerContext(const SLLexList lexList[], const SLLexStage lexStageList[]);
void sl_freeLexerContext(SLLexerContext* ctx);
SLLexerContext* sl_initContext();

SLString sl_getTokenType  (SLLexerContext* ctx, SLToken token);
SLToken sl_getNextToken   (SLLexerContext* ctx);

// Default stages
dint sl_skipAnyWhitespace   (SLLexerContext* ctx, dint* LastChar, SLToken* token);
dint sl_setLocation         (SLLexerContext* ctx, dint* LastChar, SLToken* token);
dint sl_lexemeHandler       (SLLexerContext* ctx, dint* LastChar, SLToken* token);
dint sl_mathString          (SLLexerContext* ctx, dint* LastChar, SLToken* token);
dint sl_matchNumber         (SLLexerContext* ctx, dint* LastChar, SLToken* token);
dint sl_checkEOF            (SLLexerContext* ctx, dint* LastChar, SLToken* token);
dint sl_retASCII            (SLLexerContext* ctx, dint* LastChar, SLToken* token);

#endif //SMALLMOUSE_LEXER_H
