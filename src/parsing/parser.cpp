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
            auto n = next();
            if (n == nullptr) continue;
            ast.push_back(std::move(n));
        }
    }

    // ============== PRIVATE ==============

    std::unique_ptr<Node> Parser::next()
    {
        switch (current().getType())
            {
                case TokenType::INCLUDE:
                {
                    std::vector<std::unique_ptr<Node>> included = include();
                    std::vector<std::unique_ptr<Node>> newAst;

                    for(auto& n : included)
                        newAst.push_back(std::move(n));
                    
                    for(auto& n : ast)
                        newAst.push_back(std::move(n));
                    
                    ast = std::move(newAst);
                    return nullptr;
                }
                case TokenType::NEW:
                {
                    return variable();
                    break;
                }
                case TokenType::NOW:
                {
                    return variable();
                    break;
                }
                case TokenType::PROTO:
                {
                    return proto();
                    break;
                }
                case TokenType::IDENTIFIER:
                {
                    const Token& nextToken = peek();

                    switch (nextToken.getType())
                    {
                        case TokenType::EQUAL:
                        {
                            return assignment();
                            break;
                        }

                        case TokenType::INCREMENT:
                        {
                            return indec();
                            break;
                        }
                        case TokenType::DECREMENT:
                        {
                            return indec();
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
                return nullptr;
            }
    }
} // namespace wave::internal
// copyright (c) 2026 Victor Botelho Anunciação