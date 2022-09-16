#include <stdio.h>

#include "libsl/reader.h"
#include "libsl/lexer.h"

const SLLexList lexList[] = {
        SL_SET_LEXEME("import", T_KEYWORD, NULL),
        SL_SET_LEXEME("i32", T_KEYWORD, NULL),
        SL_SET_LEXEME("f32", T_KEYWORD, NULL),
        SL_SET_LEXEME("if", T_KEYWORD, NULL),
        SL_SET_LEXEME("while", T_KEYWORD, NULL),
        SL_SET_LEXEME("for", T_KEYWORD, NULL),
        SL_END_LEXEME(T_EOF)
};

const SLLexStage lexStageLst[] = {
        sl_skipAnyWhitespace,
        sl_setLocation,
        sl_lexemeHandler,
        sl_matchNumber,
        sl_checkEOF,
        sl_retASCII,
        NULL
};

int main() {

    SLLexerContext* ctx = sl_createLexerContext(lexList, lexStageLst);
    sl_openFile(ctx, "G:/dcode.txt");

    for (SLToken token = sl_getNextToken(ctx); token.type != T_EOF; token = sl_getNextToken(ctx)) {
        switch (token.type) {
            case T_IDENTIFIER:
            case T_KEYWORD: {
                printf("%s name: %s\n", sl_getTokenType(ctx, token).data, token.identString);
                break;
            }
            case T_NUMBER: {
                printf("%s value: %f\n", sl_getTokenType(ctx, token).data, token.value);
                break;
            }
            default: {
                printf("%s\n", sl_getTokenType(ctx, token).data);
                break;
            }
        }
    }

    sl_closeFile(ctx);

    return 0;
}
