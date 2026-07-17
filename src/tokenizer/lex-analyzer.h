/*
* Lex Analizer Prototype Header - C++ / C header
* This document is in the testing phase. The lexical analyzer may not be fully functional at this time.
*/

#pragma once

#include "token.h"
#include <string>

namespace indigo::internal {

    class LexAttributes {
    public:
        int pos;
        char current;
        std::string src;

        LexAttributes(std::string_view source)
            : pos(0), current(source[0]), src(source) {
        };
    };

    class LexFunctions {
        LexAttributes& attr;
    public:
        LexFunctions(LexAttributes& attributes) :attr(attributes) {};

        void move_adv();

        void ignore_ws();

        Token keyword();

        Token number();

        Token string();

        Token boolean();

        Token symbol_operator();

        Token nextToken();

        Token typing();

        

    };

    class Lexer {
        LexAttributes attr;
        LexFunctions func;
    public:
        const std::string getSrc();
        Lexer(std::string_view source) : attr(source), func(attr) {};
        Token next();
    };
}

// (c) 2026 Victor Botelho Anunciação