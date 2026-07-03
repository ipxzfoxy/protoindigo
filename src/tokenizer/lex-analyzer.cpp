#include <cctype>
#include <string>
#include <iostream>
#include <unordered_map>
#include "lex-analyzer.h"
#include "token.h"

namespace indigo::internal {

    void LexFunctions::move_adv() {
        attr.pos++;
        if (attr.pos < (int)attr.src.size()) {
            attr.current = attr.src[attr.pos];
        }
        else {
            attr.current = '\0';
        }
    }

    void LexFunctions::ignore_ws() {
        while (attr.current != '\0' && std::isspace(attr.current)) {
            move_adv();
        }
    }

    Token LexFunctions::keyword() {
        std::string res;
        while (attr.current != '\0' && (std::isalpha(attr.current) || attr.current == '_')) {
            res += attr.current;
            move_adv();
        }
        auto it = keywords.find(res);
        if (it != keywords.end()) return Token(it->second, it->first);
        return Token(TokenType::IDENTIFIER, res);
    }

    Token LexFunctions::number() {
        std::string res;
        while (attr.current != '\0' && std::isdigit(attr.current)) {
            res += attr.current;
            move_adv();
        }
        return Token(TokenType::NUMBER, res);
    }

    Token LexFunctions::string() {
        std::string res;

        while (attr.current != '"') {
            if (attr.current == '\0') {
                std::cout << "Syntax Error: String scope not closed correctly." << std::endl;
                exit(1);
            }

            res += attr.current;
            move_adv();
        }

        move_adv();
        return Token(TokenType::STRING, res);
    }

    Token LexFunctions::typing() {
        std::string res;
        move_adv();

        while (attr.current != '\0' && std::isalnum(attr.current)) {
            res += attr.current;
            move_adv();
        }

        return Token(TokenType::TYPING, res);
    }

    Token LexFunctions::symbol_operator() {
        std::string res;
        while (attr.current != '\0' && std::ispunct(attr.current)) {
            res += attr.current;
            move_adv();
            auto it = symbols_operators.find(res);
            if (it != symbols_operators.end()) return Token(it->second, it->first);
        }
        return Token(TokenType::T_NULL, res);
    }


    Token LexFunctions::nextToken() {
        ignore_ws();
        if (attr.current == '\0') return Token(TokenType::T_EOF, "");
        if (std::isalpha(attr.current) || attr.current == '_') return keyword();
        if (attr.current == '"') {
            move_adv();
            return string();
        }
        if (attr.current == '#') return typing();
        if (std::isdigit(attr.current)) return number();
        if (std::ispunct(attr.current)) return symbol_operator();
        
        move_adv();
        return Token(TokenType::T_NULL, "");
    }

    const std::string Lexer::getSrc() {
        return attr.src;
    }

    // Lexer

    Token Lexer::next() {
        return func.nextToken();
    }

}

// (c) 2026 Victor Botelho Anunciação