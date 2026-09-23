#include "parser.h"

namespace wave::internal
{
    // * & /
    std::unique_ptr<Node> Parser::factor()
    {
        NodeUniquePtr left = literal();

        

        // Implicit Multiplication
        if (auto nodeNumber = dynamic_cast<LiteralNumberNode*>(left.get()))
        {

            if (current().getType() == TokenType::IDENTIFIER || current().getType() == TokenType::LPAREN)
            {
                left = std::make_unique<BinaryExpressionNode>(std::move(left), std::move(literal()), BinaryOperation::MUL);
            }
        }

        while (
            current().getType() == TokenType::STAR
            || current().getType() == TokenType::SLASH
        )
        {
            BinaryOperation op = (current().getType() == TokenType::STAR)
                ? BinaryOperation::MUL
                : BinaryOperation::DIV;

            consume();

            left = std::make_unique<BinaryExpressionNode>(BinaryExpressionNode(std::move(left), literal(), op));
        }

        return left;
    }

    // + & -
    std::unique_ptr<Node> Parser::term()
    {
        NodeUniquePtr left = factor();

        // Increment & Decrement
        if (auto nodeString = dynamic_cast<LiteralStringNode*>(left.get()))
        {
            std::cout << "INDEC";
            if (peek().getType() == TokenType::INCREMENT || peek().getType() == TokenType::DECREMENT)
            {
                left = std::move(increment_decrement());
            }
        }

        while (
            current().getType() == TokenType::PLUS
            || current().getType() == TokenType::MINUS
        )
        {
            BinaryOperation op = (current().getType() == TokenType::PLUS)
                ? BinaryOperation::ADD
                : BinaryOperation::SUB;

            consume();

            left = std::make_unique<BinaryExpressionNode>(BinaryExpressionNode(std::move(left), expression(), op));
        }

        return left;
    }

    std::unique_ptr<Node> Parser::expression()
    {
        return std::move(term());
    }

    // Increment (++) & Decrement (--).
    std::unique_ptr<Node> Parser::increment_decrement()
    {
        std::string identifier = std::get<std::string>(current().getValue());
        expect(TokenType::IDENTIFIER);
        BinaryOperation operation = (current().getType() == TokenType::INCREMENT) 
            ? BinaryOperation::ADD 
            : BinaryOperation::SUB;
        consume();

        skipSemicolon();
        
        return std::make_unique<AssignmentExpressionNode>(
            identifier,
            std::make_unique<BinaryExpressionNode>(
                std::make_unique<IdentifierNode>(identifier), std::make_unique<LiteralNumberNode>(1), operation
            )
        );
    }

    std::unique_ptr<Node> Parser::implicit_mul()
    {
        double num = std::get<double>(current().getValue());
        consume();


        if (!(
            current().getType() == TokenType::NUMBER
        )) {
            std::cerr << "SyntaxError: Expected a expression. <impmul>";
            exit(0);
        }

        if (current().getType() == TokenType::LPAREN)
        {
            return std::make_unique<BinaryExpressionNode>(std::make_unique<LiteralNumberNode>(num), std::move(parentheses_exp()), BinaryOperation::MUL);
        }

        if (current().getType() == TokenType::IDENTIFIER)
        {
            return std::make_unique<BinaryExpressionNode>(std::make_unique<LiteralNumberNode>(num), std::move(parentheses_exp()), BinaryOperation::MUL);
        }
        

        std::cerr << "SyntaxError: Expected a expression. <impmul>";
        exit(0);
    }



} // namespace wave::internal
