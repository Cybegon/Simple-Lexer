#include <stdio.h>

#include "libsl/reader.h"
#include "libsl/lexer.h"

const SLLexList lexList[] = {
        SL_SET_LEXEME("import", T_KEYWORD, SL_TOKEN_INFO_NONE, NULL),
        SL_SET_LEXEME("i32", T_KEYWORD, SL_TOKEN_INFO_NONE, NULL),
        SL_SET_LEXEME("f32", T_KEYWORD, SL_TOKEN_INFO_NONE, NULL),
        SL_SET_LEXEME("if", T_KEYWORD, SL_TOKEN_INFO_NONE, NULL),
        SL_SET_LEXEME("while", T_KEYWORD, SL_TOKEN_INFO_NONE, NULL),
        SL_SET_LEXEME("for", T_KEYWORD, SL_TOKEN_INFO_NONE, NULL),
        SL_END_LEXEME
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
    sl_openFile(ctx, "dcode.txt");

    for (SLToken token = sl_getNextToken(ctx); token.type != T_EOF; token = sl_getNextToken(ctx)) {
        switch (token.type) {
            case T_IDENTIFIER:
            case T_KEYWORD: {
                printf("%s name: %s\n", sl_getTokenType(ctx, token).data, token.identString);
                break;
            }
            case T_CONSTANT: {
                printf("%s value: %f\n", sl_getTokenType(ctx, token).data, token.value);
                break;
            }
            default: {
                printf("%s\n", sl_getTokenType(ctx, token).data);
                break;
            }
        }

        if (token.type == T_IDENTIFIER)
            free(token.identString);
    }

    sl_closeFile(ctx);

    return 0;
}
