#ifndef SIMPLE_LEXER_CONFIGINTERNAL_HPP
#define SIMPLE_LEXER_CONFIGINTERNAL_HPP

// Do not edit after build SL library

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

#if !defined(EOF)
#   define EOF (-1)
#endif

#endif //SIMPLE_LEXER_CONFIGINTERNAL_HPP
