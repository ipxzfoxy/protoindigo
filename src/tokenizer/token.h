#pragma once
#include <cstdint>
#include <unordered_map>
#include <string>
#include <string_view>
#include <variant>

namespace wave::internal {
    // RESERVED
    enum class TokenType : uint8_t {
        // Keywords
        NEW, NOW, CONST, PROTO, AS,

        // Special
        IDENTIFIER, T_EOF, TYPING,

        // Symbols
        EQUAL, LPAREN, RPAREN, LBRACE, RBRACE, LT, GT, COLON, SEMICOLON,
        HASH, PLUS, MINUS, STAR, SLASH, DOT, COMMA,

        // Literal
        LITERAL_STRING, TEMPLATE_STRING, NUMBER, T_NULL, BOOLEAN
    };

    class Token {
        TokenType type;
        std::variant<std::string, double, bool> value;

    public:
        Token(TokenType t, std::variant<std::string, double, bool> val) : type(t), value(val) {}
        TokenType getType() const { return type; }
        std::variant<std::string, double, bool> getValue() const { return value; }
    };

    extern const std::unordered_map<std::string, TokenType> keywords;
    extern const std::unordered_map<std::string, TokenType> symbols_operators;
}

// copyright (c) 2026 Victor Botelho Anunciação