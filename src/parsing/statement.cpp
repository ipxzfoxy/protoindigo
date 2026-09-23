#include "parser.h"

namespace wave::internal
{
    // Variables & Functions
    std::unique_ptr<Node> Parser::variable()
    {
        bool constant = false;
        std::string typing = "auto";
        std::string identifier;
        std::optional<std::unique_ptr<Node>> value;

        if (current().getType() == TokenType::NOW)
        {
            constant = true;
            consume();

            if (current().getType() == TokenType::CONST)
            {
                std::cerr << std::format(
                    "SyntaxError\ninconsistent constant declaration using `{} >{}<`.\n"
                    "Did you mean `now x = value` or `new const x = value`?\n",
                    "now",
                    "const"
                );
                exit(1);
            }
        } else {
            expect(TokenType::NEW);
        }

        if (current().getType() == TokenType::CONST)
        {
            constant = true;
            consume();
        }

        if (current().getType() == TokenType::TYPING)
        {
            typing = std::get<std::string>(current().getValue());
            consume();
        }

        identifier = std::get<std::string>(current().getValue());

        expect(TokenType::IDENTIFIER);
        expect(TokenType::EQUAL);

        value = std::move(expression());
        if (current().getType() == TokenType::SEMICOLON) consume();

        return std::make_unique<VariableNode>(
            constant,
            typing,
            identifier,
            std::move(value.value())
        );
    }
    // Proto statement
    std::unique_ptr<Node> Parser::proto()
    {
        expect(TokenType::PROTO);

        std::optional<std::unique_ptr<Node>> exp = expression();

        if (!exp.has_value())
        {
            std::cout << "SyntaxError: Expected a expression." << std::endl;
            exit(1);
        }
        
        skipSemicolon();
        return std::make_unique<ProtoNode>(std::move(exp.value()));
    }

    std::unique_ptr<Node> Parser::assignment()
    {
        const std::string target = std::get<std::string>(current().getValue());

        expect(TokenType::IDENTIFIER);
        expect(TokenType::EQUAL);

        std::unique_ptr<Node> value = expression();
        if (current().getType() == TokenType::SEMICOLON) consume();
        return std::make_unique<AssignmentExpressionNode>(
            target,
            std::move(value)
        );
    }

    std::vector<std::unique_ptr<Node>> Parser::include()
    {
        expect(TokenType::INCLUDE);
        std::string target = std::get<std::string>(current().getValue());
        expect(TokenType::LITERAL_STRING);
        Tokenizer tkz(readBreFile(target));
        Parser parser(tkz);
        parser.parse();

        return std::move(parser.takeAST());
    }

    std::unique_ptr<Node> Parser::label()
    {
        consume();
        std::string identifier = std::get<std::string>(current().getValue());
        expect(TokenType::IDENTIFIER);
        skipSemicolon();

        return std::make_unique<JumpNode>(std::make_unique<IdentifierNode>(identifier), true);
    }

    std::unique_ptr<Node> Parser::go_to()
    {
        expect(TokenType::GO);
        expect(TokenType::TO);

        std::string target = std::get<std::string>(current().getValue());
        expect(TokenType::IDENTIFIER);

        return std::make_unique<JumpNode>(std::make_unique<IdentifierNode>(target), false);
    }
} // namespace wave::internal
// copyright (c) 2026 Victor Botelho Anunciação