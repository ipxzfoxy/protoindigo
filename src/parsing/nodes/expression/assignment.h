// Assignment expression Node - assignment.h
#pragma once
#include <variant>
#include <memory>
#include <string>
#include "../node.h"
#include "../identifier.h"

namespace wave::internal
{
	class AssignmentExpressionNode : public Node {
	public:
        std::string targetVariable;
		std::unique_ptr<Node> value;
        AssignmentExpressionNode(std::string t, std::unique_ptr<Node> v)
            : Node(NodeType::AssignmentExpression), targetVariable(t), value(std::move(v)) {};
	};
} // namespace wave::internal

// (c) 2026 Victor Botelho Anunciação