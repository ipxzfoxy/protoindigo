#include "parser.h"

namespace wave::internal
{
        std::optional<std::unique_ptr<Node>> Parser::primary()
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
            

            default:
            {
                consume();
                return std::nullopt;
                break;
            }
        }

        consume();
        return n;
    }

    std::unique_ptr<Node> Parser::expression()
    {
        std::unique_ptr<Node> left = std::move(primary().value()); // Primary uses consume()
        while (isOp_symbol(current()))
        {
            BinaryOperation sym = op_symbol();
            std::unique_ptr<Node> right = std::move(primary().value()); // Primary uses consume()
            left = std::make_unique<BinaryExpressionNode>(std::move(left), std::move(right), sym);
            
        }

        return std::move(left);
    }

    // Increment (++) & Decrement (--).
    std::unique_ptr<AssignmentExpressionNode> Parser::indec()
    {
        std::string identifier = std::get<std::string>(current().getValue());
        expect(TokenType::IDENTIFIER);
        BinaryOperation operation = current().getType()
            == TokenType::INCREMENT ? BinaryOperation::ADD : BinaryOperation::SUB;
        consume();
        if (current().getType() == TokenType::SEMICOLON) consume();
        return std::make_unique<AssignmentExpressionNode>(
            identifier,
            std::make_unique<BinaryExpressionNode>(
                std::make_unique<IdentifierNode>(identifier), std::make_unique<LiteralNumberNode>(1), operation
            )
        );
    }

} // namespace wave::internal
