#ifndef SIMPLE_LEXER_LRULES_H
#define SIMPLE_LEXER_LRULES_H

#include "datatypes.h"

#include "lexer.h"

// Default stages
dint sl_skipAnyWhitespace   (SLLexerContext* ctx, SLToken* token);
dint sl_setLocation         (SLLexerContext* ctx, SLToken* token);
dint sl_lexemeHandler       (SLLexerContext* ctx, SLToken* token);
dint sl_mathString          (SLLexerContext* ctx, SLToken* token);
dint sl_matchNumber         (SLLexerContext* ctx, SLToken* token);
dint sl_checkEOF            (SLLexerContext* ctx, SLToken* token);
dint sl_retASCII            (SLLexerContext* ctx, SLToken* token);

#endif //SIMPLE_LEXER_LRULES_H
