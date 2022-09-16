#ifndef SMALLMOUSE_CONFIG_H
#define SMALLMOUSE_CONFIG_H

#include "datatypes.h"
#include "configInternal.h"

typedef enum SLTokenType SLTokenType;

enum SLTokenType {
    T_NONE = SL_ENUM_START,
    T_KEYWORD,
    T_IDENTIFIER,
    T_PUNCTUATOR,
    T_CONSTANT,
    T_STRING,

    // Your tokens here...

    T_NULL,
    T_ERR,
    T_EOF = EOF
};

#define SL_TOKEN_INFO_NONE 0

#define SL_TOSTRING(s) #s
#define SL_SET_STRING(s) (SLString){s, sizeof(s) - 1}

#define SL_SET_LEXEME(s, t, i, ud) { t, SL_SET_STRING(SL_TOSTRING(t)), i, SL_SET_STRING(s), ud }

#define SL_END_LEXEME  SL_SET_LEXEME("", T_EOF, SL_TOKEN_INFO_NONE, NULL)

#endif //SMALLMOUSE_CONFIG_H
