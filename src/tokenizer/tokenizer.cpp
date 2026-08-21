/*
* ProtoIndigo Tokenizer
* tokenizer.cpp
* 
* ---------------TOKEN BODY ----------------
* |   Type - TokenType   |  String - Value |
* ------------------------------------------
*/

#include "tokenizer.h"

namespace wave::internal {
    
    // ============== PUBLIC ==============

    void Tokenizer::tokenize()
    {
        while (current_char != '\0')
        {
            Token token = next();
            if (token.getType() == TokenType::T_EOF) {
                out.push_back(Token(TokenType::T_EOF, ""));
                return;
            }
            out.push_back(token);
        };
    }

    // ============== PRIVATE ==============

    void Tokenizer::skipws() {
        while (current_char != '\0' && std::isspace(current_char)) {
            adv();
        }
    }
    void Tokenizer::adv()
    {
        src_index++;
        if (src_index < source.size())
        {
            current_char = source[src_index];
        }
        else
        {
            current_char = '\0';
        }
    }
    // Keyword and Identifiers
    Token Tokenizer::keyword()
    {
        std::string result;

        while (
            current_char != '\0' &&
            (std::isalnum(current_char) || current_char == '_')
        )
        {
            result += current_char;
            adv();
        }

        if (result == "true" || result == "false")
            return {TokenType::BOOLEAN, toBool(result)};
        auto it = keywords.find(result);
        if (it != keywords.end())
            return Token(it->second, it->first);

        return { TokenType::IDENTIFIER, result };
    }
    // Numbers
    Token Tokenizer::number()
    {
        double res = 0;

        while (current_char != '\0' && std::isdigit(current_char))
        {
            res = (res * 10) + (current_char - '0');
            adv();
        }

        return Token(TokenType::NUMBER, res);
    }
    // Strings
    Token Tokenizer::string()
    {
        std::string res;
        const char quote_char = current_char;

        adv();

        while (current_char != quote_char)
        {
            if (current_char == '\0')
            {
                std::cout << "Syntax Error: String scope not closed correctly." << std::endl;
                exit(1);
            }

            res += current_char;
            adv();
        }

        adv();

        if (quote_char == '`')
            return { TokenType::TEMPLATE_STRING, res };

        return { TokenType::LITERAL_STRING, res };
    }
    // Typing identifier
    Token Tokenizer::typing()
    {
        std::string res;

        adv();

        while (current_char != '\0' && std::isalnum(current_char))
        {
            res += current_char;
            adv();
        }

        return Token(TokenType::TYPING, res);
    }
    // Symbols or Operators
    Token Tokenizer::sym_op()
    {
        std::string res;
        while (current_char != '\0' && std::ispunct(current_char)) {
            res += current_char;
            adv();
            auto it = symbols_operators.find(res);
            if (it != symbols_operators.end()) return Token(it->second, it->first);
        }
        return Token(TokenType::T_NULL, res);
    }

    Token Tokenizer::next()
    {
        skipws();
        if (current_char == '\0') return Token(TokenType::T_EOF, "");
        if (std::isalpha(current_char) || current_char == '_') return keyword();
        if (current_char == '"' || current_char == '\'' || current_char == '`') {
            return string();
        }
        if (current_char == '#') return typing();
        if (std::isdigit(current_char)) return number();
        if (std::ispunct(current_char)) return sym_op();
        adv();
        return Token(TokenType::T_NULL, "");
    }

    bool Tokenizer::toBool(std::string& str)
    {
        return str == "true";
    }
}

// copyright (c) 2026 Victor Botelho Anunciação