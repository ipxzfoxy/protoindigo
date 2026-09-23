#include "parser.h"

namespace wave::internal
{
    std::unique_ptr<Node> Parser::parentheses_exp()
    {
        expect(TokenType::LPAREN);
        if (current().getType() == TokenType::RPAREN)
            throw std::runtime_error("Expected a expression inside parentheses.");
        
        std::unique_ptr<Node> exp = expression();
        expect(TokenType::RPAREN);
        return std::move(exp);
    }

} // namespace wave::internal
