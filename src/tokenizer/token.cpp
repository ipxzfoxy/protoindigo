#include "token.h"

namespace indigo::internal {
    const std::unordered_map<std::string, TokenType> keywords = {
       {"use", TokenType::USE},
       {"can", TokenType::CAN},
       {"deny", TokenType::DENY},
       {"new", TokenType::NEW},
       {"lock", TokenType::LOCK},
       {"var", TokenType::VAR},
       {"class", TokenType::CLASS},
       {"struct", TokenType::STRUCT},
       {"if", TokenType::IF},
       {"else", TokenType::ELSE},
       {"for", TokenType::FOR},
       {"continue", TokenType::CONTINUE},
       {"return", TokenType::RETURN},
       {"break", TokenType::BREAK},
       {"import", TokenType::IMPORT},
       {"export", TokenType::EXPORT},
       {"self", TokenType::SELF},
       {"enum", TokenType::ENUM},
       {"type", TokenType::TYPE},
       {"true", TokenType::BOOLEAN},
       {"false", TokenType::BOOLEAN},
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

// (c) 2026 Victor Botelho Anunciação