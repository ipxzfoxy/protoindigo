#include "token.h"

namespace wave::internal {
    const std::unordered_map<std::string, TokenType> keywords = {
       {"new", TokenType::NEW},
       {"now", TokenType::NOW},
       {"const", TokenType::CONST},
       {"true", TokenType::BOOLEAN},
       {"false", TokenType::BOOLEAN},
       {"proto", TokenType::PROTO},
       {"as", TokenType::AS},
    };

    const std::unordered_map<std::string, TokenType> symbols_operators = {
        {"=", TokenType::EQUAL},
        {"(", TokenType::LPAREN},
        {")", TokenType::RPAREN},
        {"{", TokenType::LBRACE},
        {"}", TokenType::RBRACE},
        {"<", TokenType::LT},
        {">", TokenType::GT},
        {":", TokenType::COLON},
        {";", TokenType::SEMICOLON},
        {"#", TokenType::HASH},
        {"+", TokenType::PLUS},
        {"-", TokenType::MINUS},
        {"*", TokenType::STAR},
        {"/", TokenType::SLASH},
        {".", TokenType::DOT},
        {",", TokenType::COMMA}
    };
}

// copyright (c) 2026 Victor Botelho Anunciação