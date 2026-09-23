// Scope.cpp
#include "parser.h"

namespace wave::internal
{
    std::vector<std::unique_ptr<Node>> Parser::scope()
    {
        expect(TokenType::LBRACE);
        std::vector<std::unique_ptr<Node>> child_ast;
        while (current().getType() != TokenType::RBRACE)
            child_ast.push_back(next());
        expect(TokenType::RBRACE);
        return child_ast;
    }
} // namespace wave:internal
// copyright (c) 2026 Victor Botelho Anunciação