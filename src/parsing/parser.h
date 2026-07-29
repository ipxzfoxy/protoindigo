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
#include "../tokenizer/tokenizer.h"
#include "nodes/node.h"
#include "nodes/proto.h"
#include "nodes/variable.h"
#include "nodes/identifier.h"
#include "nodes/literals/string.h"
#include "nodes/literals/number.h"
#include "nodes/literals/boolean.h"
#include "nodes/expression/assignment.h"
#include "nodes/expression/binary.h"

namespace wave::internal
{   
    using PV = std::variant<std::string, double, bool>;
    class Parser {
    private:
        int ctk_index;
        Tokenizer tokenizer;
        std::vector<Token> tokens;
        std::vector<std::unique_ptr<Node>> ast;
        std::optional<std::unique_ptr<Node>> primary();
        std::unique_ptr<VariableNode> variable();
        std::unique_ptr<ProtoNode> proto();
        std::unique_ptr<AssignmentExpressionNode> assignment();
        std::unique_ptr<Node> term();
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
    };
} // namespace wave::internal

// copyright (c) 2026 Victor Botelho Anunciação