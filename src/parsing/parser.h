/*
* ProtoIndigo Parser
* parser.cpp
*/
#pragma once

#define RED     "\033[31m"
#define RESET   "\033[0m"

#include <memory>
#include <vector>
#include <optional>
#include <iostream>
#include <variant>
#include <format>
#include <utility>
#include <stdexcept>

#include "../../utils/readBreFile.h"

#include "../ast/nodes/node.h"
#include "../ast/nodes/proto.h"
#include "../ast/nodes/variable.h"
#include "../ast/nodes/identifier.h"
#include "../ast/nodes/jump.h"

#include "../ast/nodes/literals/string.h"
#include "../ast/nodes/literals/number.h"
#include "../ast/nodes/literals/boolean.h"
#include "../ast/nodes/literals/array.h"

#include "../ast/nodes/expression/assignment.h"
#include "../ast/nodes/expression/binary.h"
#include "../ast/nodes/expression/parenthesized.h"

#include "../tokenizer/tokenizer.h"
#include "../tokenizer/tokenTypeName.h"

namespace wave::internal
{   
    using PV = std::variant<std::string, double, bool>;
    class Parser {
    private:
        int ctk_index;
        Tokenizer tokenizer;
        std::vector<Token> tokens;
        std::vector<std::unique_ptr<Node>> ast;

    public:
        Parser(Tokenizer& tokenizer);

        void parse();

        const std::vector<std::unique_ptr<Node>> getAST() {
            return std::move(ast);
        }

        std::vector<std::unique_ptr<Node>> takeAST() {
            return std::move(ast);
        }

    private:
        const Token& consume();
        const Token& current();
        const Token& peek();
        const Token& previous();

        std::unique_ptr<Node> next();

        void expect(TokenType expected);
        void skipSemicolon();

        BinaryOperation op_symbol();
        bool isOp_symbol(const Token& t) const;

        // Expressions
        std::unique_ptr<Node> expression();
        std::unique_ptr<Node> term();
        std::unique_ptr<Node> factor();
        std::unique_ptr<Node> implicit_mul();
        std::unique_ptr<Node> parentheses_exp();
        std::unique_ptr<Node> literal();
        std::unique_ptr<Node> array();

        // Statements
        std::unique_ptr<Node> statement();
        std::unique_ptr<Node> ctx_statement();
        std::unique_ptr<Node> variable();
        std::unique_ptr<Node> assignment();
        std::unique_ptr<Node> proto();
        std::unique_ptr<Node> label();
        std::unique_ptr<Node> go_to();
        std::unique_ptr<Node> increment_decrement();

        // Blocks / external sources
        std::vector<std::unique_ptr<Node>> include();
        std::vector<std::unique_ptr<Node>> scope();
    };
} // namespace wave::internal

// copyright (c) 2026 Victor Botelho Anunciação