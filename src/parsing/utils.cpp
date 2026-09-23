#include "parser.h"

namespace wave::internal
{
    const Token&Parser::current()
    {
        if (ctk_index >= tokens.size())
            return tokens.back();
        return tokens[ctk_index];
    }

    const Token& Parser::peek()
    {
        if (ctk_index + 1 >= tokens.size())
            return tokens.back();
        return tokens[ctk_index + 1];
    }

    const Token& Parser::previous()
    {
        if (ctk_index == 0)
            return tokens.front();
        return tokens[ctk_index - 1];
    }

    const Token& Parser::consume()
    {
        ctk_index++;
        return current();
    }

    void Parser::expect(TokenType expected)
    {
        if (current().getType() == expected) {
				consume();
		}
		else {

			std::cout
                << "SyntaxError: Expected '"
                << tokenTypeName(expected)
				<< "' but: <" << tokenTypeName(current().getType()) << ">";
			exit(1);
		}
    }
    
    BinaryOperation Parser::op_symbol()
    {
        switch (current().getType())
        {
        case TokenType::PLUS:
            consume();
            return BinaryOperation::ADD;
            break;
        case TokenType::MINUS:
        consume();
            return BinaryOperation::SUB;
            break;
        case TokenType::STAR:
        consume();
            return BinaryOperation::MUL;
            break;  
        case TokenType::SLASH:
        consume();
            return BinaryOperation::DIV;
            break;  
        default:
            break;
        }
    }

    bool Parser::isOp_symbol(const Token& t) const
    {
        const TokenType& type = t.getType();
        if (
            type == TokenType::PLUS     ||
            type == TokenType::MINUS    ||
            type == TokenType::STAR     ||
            type == TokenType::SLASH    //
        ) return true;
        return false;
    }

    void Parser::skipSemicolon()
    {
        if (current().getType() == TokenType::SEMICOLON)
            consume();
    }
} // namespace wave::internal
// copyright (c) 2026 Victor Botelho Anunciação