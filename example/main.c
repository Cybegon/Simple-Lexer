#include <stdio.h>

#include "slreader.h"
#include "sllexer.h"

#include "slrules.h"

const SLLexList lexList[] = {
        SL_SET_LEXEME("import", T_KEYWORD, SL_TOKEN_INFO_NONE, NULL),
        SL_SET_LEXEME("i32", T_KEYWORD, SL_TOKEN_INFO_NONE, NULL),
        SL_SET_LEXEME("f32", T_KEYWORD, SL_TOKEN_INFO_NONE, NULL),
        SL_SET_LEXEME("if", T_KEYWORD, SL_TOKEN_INFO_NONE, NULL),
        SL_SET_LEXEME("while", T_KEYWORD, SL_TOKEN_INFO_NONE, NULL),
        SL_SET_LEXEME("for", T_KEYWORD, SL_TOKEN_INFO_NONE, NULL),
        SL_END_LEXEME
};

const SLLexList lexList_rb[] = {
        SL_SET_LEXEME("require", T_KEYWORD, SL_TOKEN_INFO_NONE, NULL),
        SL_SET_LEXEME("if", T_KEYWORD, SL_TOKEN_INFO_NONE, NULL),
        SL_SET_LEXEME("not", T_KEYWORD, SL_TOKEN_INFO_NONE, NULL),
        SL_SET_LEXEME("else", T_KEYWORD, SL_TOKEN_INFO_NONE, NULL),
        SL_SET_LEXEME("case ", T_KEYWORD, SL_TOKEN_INFO_NONE, NULL),
        SL_SET_LEXEME("when", T_KEYWORD, SL_TOKEN_INFO_NONE, NULL),
        SL_SET_LEXEME("while", T_KEYWORD, SL_TOKEN_INFO_NONE, NULL),
        SL_SET_LEXEME("for", T_KEYWORD, SL_TOKEN_INFO_NONE, NULL),
        SL_SET_LEXEME("OWN_DIR", T_CONSTANT, 1, NULL),
        SL_END_LEXEME
};

const SLLexStage lexStageLst[] = {
        sl_skipAnyWhitespace,
        sl_setLocation,
        sl_retNextLine,
        sl_lexemeHandler,
        sl_mathString,
        sl_matchNumber,
        sl_checkEOF,
        sl_retASCII,
        NULL
};

const char* const paths[] = {
        "dcode.txt",
        "test.rb",
        NULL
};

int main() {
    printf("\n========================dcode.txt========================\n");
    SLLexerContext* ctx;
    ctx = sl_createLexerContext(lexList, lexStageLst);

    sl_openFile(ctx, "dcode.txt");

    for (SLToken token = sl_getNextToken(ctx); token.type != T_EOF; token = sl_getNextToken(ctx)) {
        switch (token.type) {
            case T_LABEL:
            case T_IDENTIFIER:
            case T_KEYWORD:
            case T_REGISTER:
            case T_STRING: {
                printf("%s name: %s\n", sl_getTokenType(ctx, token).data, token.identString);
                break;
            }
            case T_CONSTANT: {
                if (token.tokenInfo == 1)
                    printf("%s name: %s\n", sl_getTokenType(ctx, token).data, token.identString);
                else
                    printf("%s value: %f\n", sl_getTokenType(ctx, token).data, token.value);
                break;
            }
            case T_ENDL:
                break;
            default: {
                printf("%s\n", sl_getTokenType(ctx, token).data);
                break;
            }
        }

        if (token.type == T_IDENTIFIER || token.type == T_STRING)
            free(token.identString);
    }

    sl_closeFile(ctx);
    sl_freeLexerContext(ctx);
    printf("========================dcode.txt========================\n");

    printf("\n========================test.rb========================\n");
    SLLexerContext* ctx2 = sl_createLexerContext(lexList, lexStageLst);

    sl_openFile(ctx2, "test.rb");

    for (SLToken token = sl_getNextToken(ctx2); token.type != T_EOF; token = sl_getNextToken(ctx2)) {
        switch (token.type) {
            case T_LABEL:
            case T_IDENTIFIER:
            case T_KEYWORD:
            case T_REGISTER:
            case T_STRING: {
                printf("%s name: %s\n", sl_getTokenType(ctx, token).data, token.identString);
                break;
            }
            case T_CONSTANT: {
                if (token.tokenInfo == 1)
                    printf("%s name: %s\n", sl_getTokenType(ctx2, token).data, token.identString);
                else
                    printf("%s value: %f\n", sl_getTokenType(ctx2, token).data, token.value);
                break;
            }
            case T_ENDL:
                break;
            default: {
                printf("%s\n", sl_getTokenType(ctx2, token).data);
                break;
            }
        }

        if (token.type == T_IDENTIFIER || token.type == T_STRING)
            free(token.identString);
    }

    sl_closeFile(ctx2);
    sl_freeLexerContext(ctx2);
    printf("========================test.rb========================\n");

    return 0;
}
