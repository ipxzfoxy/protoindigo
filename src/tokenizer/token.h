#pragma once
#include <cstdint>
#include <unordered_map>
#include <string>
#include <string_view>
#include <variant>

namespace wave::internal {

    enum class TokenType : uint8_t {
        NEW,
        NOW,
        CONST,
        PROTO,
        AS,
        INCLUDE,
        IDENTIFIER,
        T_EOF,
        TYPING,

        EQUAL,
        LPAREN,
        RPAREN,
        LBRACE,
        RBRACE,
        LT,
        GT,
        COLON,
        SEMICOLON,
        HASH,
        PLUS,
        MINUS,
        STAR,
        SLASH,
        DOT,
        COMMA,

        LITERAL_STRING,
        TEMPLATE_STRING,
        NUMBER,
        T_NULL,
        BOOLEAN,
        INCREMENT,
        DECREMENT,
        POW
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
    extern const std::unordered_map<std::string, TokenType> symbols;
    extern const std::unordered_map<std::string, TokenType> operators;
}

// copyright (c) 2026 Victor Botelho Anunciação