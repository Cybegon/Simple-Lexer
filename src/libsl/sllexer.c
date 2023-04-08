#include "sllexer.h"

#include "slconfig.h"
#include "slreader.h"

SLToken lex(SLLexerContext* ctx);

SLLexerContext* sl_createLexerContext(const SLLexList lexList[], const SLLexStage lexStageList[])
{
    SLLexerContext* ctx = (SLLexerContext*)SL_MALLOC(sizeof(SLLexerContext));
    SL_BZERO(ctx, sizeof(SLLexerContext));

    ctx->LastChar       = ' ';
    ctx->lex            = lex;
    ctx->lexemeList     = lexList;
    ctx->lexStageList   = lexStageList;

    return ctx;
}

void sl_freeLexerContext(SLLexerContext* ctx)
{
    sl_closeFile(ctx);

    SL_FREE(ctx);
}

SLString sl_getTokenType(SLLexerContext* ctx, SLToken token)
{
    if (token.type < SL_ENUM_START) {
        SLString string;
        string.len = 0;

        string.data[0] = (char)token.type;
        string.data[1] = 0;
        ++string.len;

        return string;
    }

    if (token.type == EOF) {
        return (SLString){"EOF", 3};
    }

    return token.typeName;
}

SLToken sl_getNextToken(SLLexerContext* ctx)
{
    return ctx->lex(ctx);
}

SLToken lex(SLLexerContext* ctx)
{
    SLToken token;
    SL_BZERO(&token, sizeof(SLToken));

    if (ctx->lexemeList == NULL) {
        ctx->lastError = -1;

        return (SLToken){T_ERR, SL_SET_STRING(SL_TOSTRING(T_ERR)), SL_TOKEN_INFO_NONE, 0, ctx->CurLoc};
    }

    for (dint i = 0; ctx->lexStageList != NULL; ++i) {
        switch (ctx->lexStageList[i](ctx, &token)) {
            case SL_LEX_NEXT_RULE:
                break;
            case SL_LEX_RET_TOK:
                return token;
            case SL_LEX_FAIL:
            default:
                return (SLToken){T_ERR, SL_SET_STRING(SL_TOSTRING(T_ERR)), SL_TOKEN_INFO_NONE, 0, ctx->CurLoc};
        }
    }

    return token;
}
