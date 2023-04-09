#include "slrules.h"

#include "slreader.h"

dint sl_skipAnyWhitespace(SLLexerContext* ctx, SLToken* token)
{
    while (sl_isSpace(ctx->LastChar)) // Skip any whitespace
        ctx->LastChar = sl_advance(ctx);

    return SL_LEX_NEXT_RULE;
}

dint sl_skipAnyWhitespaceAndReturn(SLLexerContext* ctx, SLToken* token) // TODO: Rename
{
    if (!sl_isSpace(ctx->LastChar))
        return SL_LEX_NEXT_RULE;

    while (sl_isSpace(ctx->LastChar)) // Skip any whitespace
        ctx->LastChar = sl_advance(ctx);

    token->type         = T_WHITESPACE;
    token->typeName     = SL_SET_STRING(SL_TOSTRING(T_WHITESPACE));
    token->tokenInfo    = SL_TOKEN_INFO_NONE;
    token->value        = 0;

    return SL_LEX_RET_TOK;


}

dint sl_retNextLine(SLLexerContext* ctx, SLToken* token)
{
    if (!sl_isNextLine(ctx->LastChar))
        return SL_LEX_NEXT_RULE;

    token->type         = T_ENDL;
    token->typeName     = SL_SET_STRING(SL_TOSTRING(T_ENDL));
    token->tokenInfo    = SL_TOKEN_INFO_NONE;
    token->value        = 0;

    ctx->LastChar = sl_advance(ctx);

    return SL_LEX_RET_TOK;
}

dint sl_setLocation(SLLexerContext* ctx, SLToken* token)
{
    ctx->CurLoc = ctx->LexLoc;
    token->sourceLocation = ctx->CurLoc;

    return SL_LEX_NEXT_RULE;
}

dint sl_lexemeHandler(SLLexerContext* ctx, SLToken* token)
{
    if (isalpha(ctx->LastChar) || ctx->LastChar == '_') { // [a-zA-Z][a-zA-Z0-9_.:]*
        memset(ctx->IdentifierStr.data, 0, ctx->IdentifierStr.len);
        ctx->IdentifierStr.len = 0;

        ctx->IdentifierStr.data[ctx->IdentifierStr.len++] = (char)ctx->LastChar;

        while (isalnum((ctx->LastChar = sl_advance(ctx))) || ctx->LastChar == '.' || ctx->LastChar == '_')
            ctx->IdentifierStr.data[ctx->IdentifierStr.len++] = (char)ctx->LastChar;

        if (ctx->LastChar == ':') { // match label
            ctx->IdentifierStr.data[ctx->IdentifierStr.len++] = (char)ctx->LastChar;
            ctx->LastChar = sl_advance(ctx);

            goto TO_LABEL;
        }

        for (dint i = 0; ctx->lexemeList[i].tokenType != T_EOF; ++i) {
            if (ctx->IdentifierStr.len == ctx->lexemeList[i].lexeme.len && ctx->lexemeList[i].lexeme.len != 0) {
                if (strncmp(ctx->IdentifierStr.data, ctx->lexemeList[i].lexeme.data, ctx->lexemeList[i].lexeme.len) == 0) {
                    token->type         = ctx->lexemeList[i].tokenType;
                    token->typeName     = ctx->lexemeList[i].tokenName;
                    token->tokenInfo    = ctx->lexemeList[i].tokenInfo;
                    token->identString  = (char*)ctx->lexemeList[i].lexeme.data;

                    return SL_LEX_RET_TOK;
                }
            }
        }

TO_LABEL:
        if (ctx->IdentifierStr.data[ctx->IdentifierStr.len - 1] == ':')
        {
            token->type             = T_LABEL;
            token->typeName         = SL_SET_STRING(SL_TOSTRING(T_LABEL));
        }
        else
        {
            token->type             = T_IDENTIFIER;
            token->typeName         = SL_SET_STRING(SL_TOSTRING(T_IDENTIFIER));
        }

        token->tokenInfo        = SL_TOKEN_INFO_NONE;
        token->identString      = SL_STRDUP(ctx->IdentifierStr.data);

        return SL_LEX_RET_TOK;
    }

    return SL_LEX_NEXT_RULE;
}

dint sl_mathString(SLLexerContext* ctx, SLToken* token)
{
    char* ltok = "\"\'";

    while ( *ltok ) {
        if (ctx->LastChar == *ltok) {
            memset(ctx->IdentifierStr.data, 0, ctx->IdentifierStr.len);
            ctx->IdentifierStr.len = 0;

            while ((ctx->LastChar = sl_advance(ctx)) != *ltok) // TODO: Match \n\r etc...
                ctx->IdentifierStr.data[ctx->IdentifierStr.len++] = (char)ctx->LastChar;
            ctx->LastChar = sl_advance(ctx); // Skip "

            token->type         = T_STRING;
            token->typeName     = SL_SET_STRING(SL_TOSTRING(T_STRING));
            token->tokenInfo    = SL_TOKEN_INFO_NONE;
            token->identString  = strdup(ctx->IdentifierStr.data);

            return SL_LEX_RET_TOK;
        }

        ++ltok;
    }

    return SL_LEX_NEXT_RULE;
}

dint sl_matchNumber(SLLexerContext* ctx, SLToken* token)
{
    if (ctx->LastChar == '0') { // 0[xX][0-9a-fA-F]+
        ctx->LastChar = sl_advance(ctx);
        if (ctx->LastChar == 'x' || ctx->LastChar == 'X') {
            SLString hexNumStr = {"", 0};

            ctx->LastChar = sl_advance(ctx);

            do {
                hexNumStr.data[hexNumStr.len++] = (char)ctx->LastChar;
                ctx->LastChar = sl_advance(ctx);
            } while (isxdigit(ctx->LastChar));

            token->type         = T_CONSTANT;
            token->typeName     = SL_SET_STRING(SL_TOSTRING(T_CONSTANT));
            token->tokenInfo    = SL_TOKEN_INFO_NONE;
            token->value        = (double)strtoul(hexNumStr.data, NULL, 16);

            return SL_LEX_RET_TOK;
        }
    }

    if (isdigit(ctx->LastChar) || ctx->LastChar == '.') { // Number: [0-9.]+
        memset(ctx->IdentifierStr.data, 0, ctx->IdentifierStr.len);
        ctx->IdentifierStr.len = 0;

        SLString numStr = {"", 0};

        numStr.data[numStr.len++] = (char)ctx->LastChar;
        ctx->LastChar = sl_advance(ctx);

        if (!isdigit(ctx->LastChar)) { // ret ASCII
            token->type         = '.';
            token->tokenInfo    = 0;

            return SL_LEX_RET_TOK;
        }

        do {
            numStr.data[numStr.len++] = (char)ctx->LastChar;
            ctx->LastChar = sl_advance(ctx);
        } while (isdigit(ctx->LastChar) || ctx->LastChar == '.');

        token->type     = T_CONSTANT;
        token->typeName = SL_SET_STRING(SL_TOSTRING(T_CONSTANT));
        token->value    = (double)strtod(numStr.data, NULL);

        return SL_LEX_RET_TOK;
    }

    return SL_LEX_NEXT_RULE;
}

dint sl_checkEOF(SLLexerContext* ctx, SLToken* token)
{
    // Check for end of file.  Don't eat the EOF.
    if (ctx->LastChar == EOF) {
        token->type = T_EOF;
        ctx->LastChar = ' ';

        return SL_LEX_RET_TOK;
    }

    return SL_LEX_NEXT_RULE;
}

dint sl_retASCII(SLLexerContext* ctx, SLToken* token)
{
    token->type = ctx->LastChar;
    ctx->LastChar = sl_advance(ctx);

    return SL_LEX_RET_TOK;
}
