/*
* ProtoIndigo Parser
* parser.cpp
*/

#include "parser.h"

namespace wave::internal{

    // ============== PUBLIC ==============

    Parser::Parser(Tokenizer& t)
        : tokenizer(t), ctk_index(0) {}

    void Parser::parse()
    {
        tokenizer.tokenize();
        tokens = tokenizer.getOutput();
        while (current().getType() != TokenType::T_EOF)
        {
            switch (current().getType())
            {
                case TokenType::NEW:
                {
                    ast.push_back(variable());
                    break;
                }
                case TokenType::NOW:
                {
                    ast.push_back(variable());
                    break;
                }
                case TokenType::PROTO:
                {
                    ast.push_back(proto());
                    break;
                }
                case TokenType::INCLUDE:
                {
                    std::vector<std::unique_ptr<Node>> included = include();
                    std::vector<std::unique_ptr<Node>> newAst;

                    for(auto& n : included)
                        newAst.push_back(std::move(n));
                    
                    for(auto& n : ast)
                        newAst.push_back(std::move(n));
                    
                    ast = std::move(newAst);
                    break;
                }
                case TokenType::IDENTIFIER:
                {
                    const Token& nextToken = peek();

                    switch (nextToken.getType())
                    {
                        case TokenType::EQUAL:
                        {
                            ast.push_back(assignment());
                            break;
                        }
                        
                        default:
                        {
                            std::cerr << "SyntaxError\nExpected a expression.";
                            exit(1);
                            break;
                        }
                    }
                    break;
                }
                default:
                {
                    std::cerr << "SyntaxError\nUnexpected token: " << (int)current().getType() << '\n';
                    exit(1);
                    break;
                }

            }
        }
    }

    // ============== PRIVATE ==============

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
			std::cout << "SyntaxError\nExpected " << (int)expected
				<< " but: " << (int)current().getType();
			exit(1);
		}
    }

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
        expect(TokenType::EQUAL);

        value = std::move(term());
        if (current().getType() == TokenType::SEMICOLON) consume();

        return std::make_unique<VariableNode>(
            constant,
            typing,
            identifier,
            std::move(value.value())
        );
    }

    std::unique_ptr<ProtoNode> Parser::proto()
    {
        expect(TokenType::PROTO);

        std::optional<std::unique_ptr<Node>> exp = term();

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

        std::unique_ptr<Node> value = term();
        if (current().getType() == TokenType::SEMICOLON) consume();
        return std::make_unique<AssignmentExpressionNode>(
            target,
            std::move(value)
        );
    }
    
    std::unique_ptr<Node> Parser::term()
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

    bool Parser::isOp_symbol(const Token& t) const
    {
        const TokenType& type = t.getType();
        if (
            type == TokenType::PLUS ||
            type == TokenType::MINUS ||
            type == TokenType::STAR ||
            type == TokenType::SLASH
        ) return true;
        return false;
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
} // namespace wave::internal

// copyright (c) 2026 Victor Botelho Anunciação