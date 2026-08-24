#include "parser.h"

namespace wave::internal
{
    // Variables & Functions
    std::unique_ptr<VariableNode> Parser::variable()
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

        /*if (
            current().getType() == TokenType::LPAREN ||
            current().getType() == TokenType::IDENTIFIER 
        )
        {
            std::cout << "Declaração de função detectada." << std::endl;
            std::vector<FunctionParamNode> params;
            if (current().getType() == TokenType::LPAREN)
            {
                std::cout << "Declaração padrão" << std::endl;
                consume();
                while (!(current().getType() == TokenType::RPAREN))
                {
                    if (current().getType() == TokenType::COLON)
                    {
                        consume();
                        continue;
                    }
                    params.push_back(FunctionParamNode(std::get<std::string>(current().getValue())));
                    consume();
                }
                consume();
            } 
            else if (current().getType() == TokenType::IDENTIFIER)
            {
                std::cout << "Declaração simples" << std::endl;
                while (!(current().getType() == TokenType::LBRACE))
                {
                    expect(TokenType::IDENTIFIER);
                    params.push_back(FunctionParamNode(std::get<std::string>(current().getValue())));
                }
            }

            if (current().getType() == TokenType::LBRACE)
            {
                std::cout << "Entrando no escopo da função." << std::endl;
                std::vector<std::unique_ptr<Node>> childAst = std::move(parse_scope());
                std::cout << "Escopo analisado." << std::endl;
                value = std::move(std::make_unique<FunctionNode>(std::move(childAst), params));
                std::cout << "Node de função completo. Variável declarada." << std::endl;
                if (current().getType() == TokenType::SEMICOLON) consume();

                return std::make_unique<VariableNode>(
                    constant,
                    typing,
                    identifier,
                    std::move(value.value())
                );
            } else {
                std::cout << "Função sem implementação declarada. Não foi guardada." << std::endl;
            }

        }*/
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
    std::unique_ptr<ProtoNode> Parser::proto()
    {
        expect(TokenType::PROTO);

        std::optional<std::unique_ptr<Node>> exp = expression();

        if (!exp.has_value())
        {
            std::cout << "SyntaxError\nExpected a expression. <proto>" << std::endl;
            exit(1);
        }

        if (current().getType() == TokenType::SEMICOLON) consume();
        return std::make_unique<ProtoNode>(std::move(exp.value()));
    }

    std::unique_ptr<AssignmentExpressionNode> Parser::assignment()
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
} // namespace wave::internal
// copyright (c) 2026 Victor Botelho Anunciação