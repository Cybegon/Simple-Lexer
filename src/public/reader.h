#ifndef SMALLMOUSE_READER_H
#define SMALLMOUSE_READER_H

#include "config.h"
#include "lexer.h"

dint sl_isSpace(dint c);

void sl_openFile    (SLLexerContext* ctx, const char* path);
void sl_closeFile   (SLLexerContext* ctx);

dint sl_getc    (SLLexerContext* ctx);
dint sl_advance (SLLexerContext* ctx);

#endif //SMALLMOUSE_READER_H
