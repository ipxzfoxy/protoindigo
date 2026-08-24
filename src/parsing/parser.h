/*
* ProtoIndigo Parser
* parser.cpp
*/

#pragma once
#include <memory>
#include <vector>
#include <optional>
#include <iostream>
#include <variant>
#include <format>
#include <utility>
#include "../../utils/readBreFile.h"
#include "../ast/nodes/node.h"
#include "../ast/nodes/proto.h"
#include "../ast/nodes/variable.h"
#include "../ast/nodes/identifier.h"
#include "../ast/nodes/literals/string.h"
#include "../ast/nodes/literals/number.h"
#include "../ast/nodes/literals/boolean.h"
#include "../ast/nodes/expression/assignment.h"
#include "../ast/nodes/expression/binary.h"
#include "../tokenizer/tokenizer.h"

namespace wave::internal
{   
    using PV = std::variant<std::string, double, bool>;
    class Parser {
    private:
        int ctk_index;
        Tokenizer tokenizer;
        std::vector<Token> tokens;
        std::vector<std::unique_ptr<Node>> ast;
        std::unique_ptr<Node> next();
        std::optional<std::unique_ptr<Node>> primary();
        std::unique_ptr<VariableNode> variable();
        std::unique_ptr<ProtoNode> proto();
        std::unique_ptr<AssignmentExpressionNode> assignment();
        std::vector<std::unique_ptr<Node>> include();
        std::unique_ptr<AssignmentExpressionNode> indec();
        std::unique_ptr<Node> expression();
        std::vector<std::unique_ptr<Node>> parse_scope();
        BinaryOperation op_symbol();
        bool isOp_symbol(const Token& t) const;
        const Token& consume();
        const Token& current();
        const Token& peek();
        const Token& previous();
        void expect(TokenType expected);
    public:
        Parser(Tokenizer& tokenizer);
        void parse();
        const std::vector<std::unique_ptr<Node>> getAST() { return std::move(ast); };
        std::vector<std::unique_ptr<Node>> takeAST() { return std::move(ast); };
    };
} // namespace wave::internal

// copyright (c) 2026 Victor Botelho Anunciação