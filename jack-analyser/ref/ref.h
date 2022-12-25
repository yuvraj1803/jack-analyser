//
//  ref.h
//  jack-analyser
//
//  Created by Yuvraj Sakshith on 25/12/22.
//

#ifndef ref_h
#define ref_h

enum types{
    SYMBOL,
    INTEGER_CONSTANT,
    STRING_CONSTANT,
    IDENTIFIER,
    KEYWORD,
    CLASS,
    METHOD,
    FUNCTION,
    CONSTRUCTOR,
    INT,
    BOOLEAN,
    CHAR,
    VOID,
    VAR,
    STATIC,
    FIELD,
    LET,
    DO,
    IF,
    ELSE,
    WHILE,
    RETURN,
    __TRUE__,   // _'s have been added as these terms are already in use.
    __FALSE__,
    __NULL__,
    THIS,
    
    INVALID
};

#endif /* ref_h */
