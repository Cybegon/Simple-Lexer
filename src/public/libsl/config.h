#ifndef SMALLMOUSE_CONFIG_H
#define SMALLMOUSE_CONFIG_H

#include "datatypes.h"
#include "configInternal.h"

enum TokenType {
    T_IDENTIFIER = SL_ENUM_START,
    T_KEYWORD,
    T_NUMBER,

    // Your tokens here...

    T_NULL,
    T_ERR,
    T_EOF = EOF
};

#define SL_TOSTRING(s) #s
#define SL_SET_STRING(s) (SLString){s, sizeof(s) - 1}

#define SL_SET_LEXEME(s, t, ud) { t, SL_SET_STRING(SL_TOSTRING(t)), SL_SET_STRING(s), ud }

#define SL_END_LEXEME(e)   SL_SET_LEXEME("", e, NULL)

#endif //SMALLMOUSE_CONFIG_H
