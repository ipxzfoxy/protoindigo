
#include "tokenTypeName.h"

namespace bre::internal {
	std::string tokenTypeName(TokenType t)
    {
    switch (t)
    {
        case TokenType::NEW: return "new";
        case TokenType::NOW: return "now";
        case TokenType::PROTO: return "proto";
        case TokenType::AS: return "as";
        case TokenType::INCLUDE: return "include";

        case TokenType::IDENTIFIER: return "identifier";
        case TokenType::NUMBER: return "number";
        case TokenType::LITERAL_STRING: return "number";
        case TokenType::TYPING: return "#Type";
        case TokenType::INCREMENT: return "++";
        case TokenType::DECREMENT: return "--";
        case TokenType::EQUAL: return "=";
        case TokenType::LPAREN: return "(";
        case TokenType::RPAREN: return ")";
        case TokenType::LBRACE: return "{";
        case TokenType::RBRACE: return "}";
        case TokenType::PLUS: return "+";
        case TokenType::MINUS: return "-";
        case TokenType::STAR: return "*";
        case TokenType::SLASH: return "/";
        case TokenType::SEMICOLON: return ";";

        case TokenType::T_EOF: return "end_of_file";

        default: return "unknown token";
    }
        
    }
} // namespace wave::internal

// Copyright (c) 2026 Victor Botelho Anunciação