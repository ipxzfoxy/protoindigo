#include "parser.h"

namespace bre::internal
{
    std::unique_ptr<Node> Parser::array()
    {
        expect(TokenType::LBRACKET);
        std::vector<std::unique_ptr<Node>> a = {};

        while (current().getType() != TokenType::RBRACKET)
        {
            if (current().getType() == TokenType::COMMA)
            {
                consume();
                continue;
            };
            std::optional<std::unique_ptr<Node>> litr = literal();
            if (!litr.has_value())
            {
                throw std::runtime_error("SyntaxError: Expected a literal value. but: " + tokenTypeName(current().getType()));
            }
            a.push_back(std::move(litr.value()));
        }

        expect(TokenType::RBRACKET);

        return std::make_unique<LiteralArrayNode>(std::move(a));
    }
}