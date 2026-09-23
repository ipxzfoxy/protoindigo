#include "parser.h"

namespace wave::internal
{
    std::unique_ptr<Node> Parser::literal()
    {
        const PV v = current().getValue();
        std::unique_ptr<Node> n;

        switch (current().getType())
        {
            case TokenType::LITERAL_STRING:
            {
                n = std::make_unique<LiteralStringNode>(
                    Delimiter::DoubleQuote,
                    std::get<std::string>(current().getValue())
                );
                break;
            }

            case TokenType::TEMPLATE_STRING:
            {
                n = std::make_unique<LiteralStringNode>(
                    Delimiter::Template,
                    std::get<std::string>(current().getValue())
                );
                break;
            }

            case TokenType::NUMBER:
            {
                n = std::make_unique<LiteralNumberNode>(
                    std::get<double>(current().getValue())
                );
                break;
            }

            case TokenType::BOOLEAN:
            {
                n = std::make_unique<LiteralBoolNode>(
                    std::get<bool>(current().getValue())
                );
                break;
            }

            case TokenType::IDENTIFIER:
            {
                n = std::make_unique<IdentifierNode>(std::get<std::string>(current().getValue()));
                break;
            }
            
            case TokenType::LPAREN:
            {
                n = parentheses_exp();
                return n;
                break;
            }

            case TokenType::LBRACKET:
            {
                return array();
                break;
            }

            default:
                throw std::runtime_error("Expected a expression. but: " + tokenTypeName(current().getType()));
        }

        consume();
        return n;
    }
} // namespace name
