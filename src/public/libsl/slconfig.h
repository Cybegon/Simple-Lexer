#ifndef SIMPLE_LEXER_CONFIG_H
#define SIMPLE_LEXER_CONFIG_H

#include "datatypes.h"

#if !defined(EOF)
#   define EOF (-1)
#endif

#define SL_ENUM_START 256

#if !defined(NO_STDLIB)
#   include <stdio.h>
#   include <string.h>
#   include <stdlib.h>
#   include <ctype.h>

#   define SL_FILE             FILE
#   define SL_FOPEN(p, m)      fopen(p, m)
#   define SL_FREAD(b, s, f)   fread(b, s, 1, f)
#   define SL_FWRITE(b, s, f)  fwrite(b, s, 1, f)
#   define SL_FCLOSE(f)        fclose(f)
#   define SL_GETC(f)          getc(f)
#   define SL_GETPOS(f)        ftell(f)

#   define SL_STRDUP(s)  strdup(s)

#   define SL_BZERO(p, s) memset(p, 0, s)

#   define SL_MALLOC(s) malloc(s)
#   define SL_FREE(p) free(p)
#else
#   define SL_FILE
#   define SL_FOPEN(p, m)
#   define SL_FREAD(b, s, f)
#   define SL_FWRITE(b, s, f)
#   define SL_FCLOSE(f)
#   define SL_GETC(f)
#   define SL_GETPOS(f)

#   define SL_BZERO(p, s)

#   define SL_MALLOC(s)
#   define SL_FREE(p)
#endif

typedef enum SLTokenType SLTokenType;

enum SLTokenType {
    T_NONE = SL_ENUM_START,
    T_LABEL,
    T_REGISTER,
    T_DIRECTIVE,
    T_KEYWORD,
    T_IDENTIFIER,
    T_PUNCTUATOR,
    T_CONSTANT,
    T_STRING = 0xFF,

    // Your tokens here...

    T_NULL = 0x3FFFFFFF,
    T_ERR,
    T_EOF = EOF
};

#define SL_TOKEN_INFO_NONE 0

#define SL_TOSTRING(s) #s
#define SL_SET_STRING(s) (SLString){s, sizeof(s) - 1}

#define SL_SET_LEXEME(s, t, i, ud) { t, SL_SET_STRING(SL_TOSTRING(t)), i, SL_SET_STRING(s), ud }

#define SL_END_LEXEME  SL_SET_LEXEME("", T_EOF, SL_TOKEN_INFO_NONE, NULL)

#endif //SIMPLE_LEXER_CONFIG_H
