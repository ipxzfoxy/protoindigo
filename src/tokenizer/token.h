#pragma once
#include <unordered_map>
#include <string>
#include <string_view>

namespace indigo::internal {
    // RESERVED
    enum class TokenType {
        // Keywords
        USE, CAN, DENY, NEW, CONST, VAR, CLASS,
        STRUCT, IF, ELSE, FOR, CONTINUE, RETURN, BREAK,
        IMPORT, EXPORT, SELF, ENUM, TYPE, PROTO,

        // Special
        IDENTIFIER, T_EOF, TYPING,

        // Symbols
        EQUAL, LPAREN, RPAREN, LBRACE, RBRACE, LT, GT, COLON, SEMICOLON,
        HASH, PLUS, MINUS, STAR, SLASH, DOT, COMMA,

        // Literal
        STRING, NUMBER, T_NULL, BOOLEAN
    };

    class Token {
        TokenType type;
        std::string value;

    public:
        Token(TokenType t, std::string_view val) : type(t), value(val) {}
        TokenType getType() const { return type; }
        std::string getValue() const { return value; }
    };

    extern const std::unordered_map<std::string, TokenType> keywords;
    extern const std::unordered_map<std::string, TokenType> symbols_operators;
}

// (c) 2026 Victor Botelho Anunciação