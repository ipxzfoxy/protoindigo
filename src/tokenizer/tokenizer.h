/*
* ProtoIndigo Tokenizer
* tokenizer.h
*/

#pragma once
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include "token.h"

namespace wave::internal {
    class Tokenizer {
    private:
        std::string source;
        int src_index;
        char current_char;
        std::vector<Token> out;
        void skipws();
        void adv();
        Token keyword();
        Token string();
        Token number();
        Token boolean();
        Token sym_op();
        Token typing();
        Token next();
        bool toBool(std::string& str);
    public:
        void tokenize();
        std::vector<Token> getOutput() { return out; };
        Tokenizer(
            std::string sourceCode
        ) : source(sourceCode), src_index(0), current_char(source[src_index]) {}
    };
}

// copyright (c) 2026 Victor Botelho Anunciação