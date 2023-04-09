#include "slreader.h"

dint sl_isSpace(dint c)
{
    switch(c)
    {
        case ' ':
        case 9:
        case '\r':
        case 11:
        case '\f':
            return TRUE;
        default:
            return FALSE;
    }
}

dint sl_isNextLine(dint c)
{
    switch(c)
    {
        case '\r':
        case '\n':
            return TRUE;
        default:
            return FALSE;
    }
}

void sl_openFile(SLLexerContext* ctx, const char* path)
{
    if (ctx->curFile != NULL) {
        SL_FCLOSE(ctx->curFile);
        ctx->curFile = NULL;
    }

    ctx->curFile = SL_FOPEN(path, "r+");
}

void sl_closeFile(SLLexerContext* ctx)
{
    if (ctx->curFile != NULL) {
        SL_FCLOSE(ctx->curFile);
        ctx->curFile = NULL;
    }
}

VOID sl_setPos(SLLexerContext* ctx, SLSourceLocation sourceLocation)
{

}

dint sl_getc(SLLexerContext* ctx)
{
    return SL_GETC(ctx->curFile);
}

dint sl_ungetc(SLLexerContext* ctx, dint c)
{
    return SL_UNGETC(c, ctx->curFile);
}

dint sl_advance(SLLexerContext* ctx)
{
    dint LastChar = sl_getc(ctx);

    ++ctx->LexLoc.pos;
    if (sl_isNextLine(LastChar)) {
        ++ctx->LexLoc.line;
        ctx->LexLoc.col = 0;
    } else {
        ++ctx->LexLoc.col;
    }
    return LastChar;
}
