// Assignment expression Node - assignment.h
#pragma once
#include <variant>
#include <memory>
#include <string>
#include <utility>
#include "../node.h"
#include "../identifier.h"

namespace wave::internal
{
    enum class BinaryOperation {
        ADD, SUB, MUL, DIV, MOD
    };
	class BinaryExpressionNode : public Node {
	public:
        BinaryOperation op;
		std::unique_ptr<Node> left_arg;
        std::unique_ptr<Node> right_arg;
        BinaryExpressionNode(std::unique_ptr<Node> left_arg, std::unique_ptr<Node> right_arg, BinaryOperation op)
            : Node(NodeType::BinaryExpression), op(op), left_arg(std::move(left_arg)), right_arg(std::move(right_arg)) {};
	};
} // namespace wave::internal

// (c) 2026 Victor Botelho Anunciação