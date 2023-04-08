#ifndef SIMPLE_LEXER_READER_H
#define SIMPLE_LEXER_READER_H

#include "slconfig.h"
#include "sllexer.h"

dint sl_isSpace     (dint c);
dint sl_isNextLine  (dint c);

void sl_openFile    (SLLexerContext* ctx, const char* path);
void sl_closeFile   (SLLexerContext* ctx);

dint sl_getc    (SLLexerContext* ctx);
dint sl_ungetc  (SLLexerContext* ctx, dint c);
dint sl_advance (SLLexerContext* ctx);

#endif //SIMPLE_LEXER_READER_H
