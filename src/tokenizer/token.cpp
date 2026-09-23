#include "token.h"

namespace wave::internal {
    const std::unordered_map<std::string, TokenType> keywords = {
        {"new", TokenType::NEW},
        {"now", TokenType::NOW},
        {"const", TokenType::CONST},
        {"true", TokenType::BOOLEAN},
        {"false", TokenType::BOOLEAN},
        {"proto", TokenType::PROTO},
        {"include", TokenType::INCLUDE},
        {"label", TokenType::CTX_KW},
        {"go", TokenType::GO},
        {"to", TokenType::TO},

    };

    const std::unordered_map<std::string, TokenType> operators = {
        {"++", TokenType::INCREMENT},
        {"--", TokenType::DECREMENT},
    };

    const std::unordered_map<std::string, TokenType> symbols = {
        {"=", TokenType::EQUAL},
        {"(", TokenType::LPAREN},
        {")", TokenType::RPAREN},
        {"{", TokenType::LBRACE},
        {"}", TokenType::RBRACE},
        {"[", TokenType::LBRACKET},
        {"]", TokenType::RBRACKET},
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