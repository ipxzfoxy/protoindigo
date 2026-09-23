// Literal Proto Node - proto.h

#pragma once
#include <vector>
#include <memory>
#include "../node.h"

namespace wave::internal {
		class ParExpressionNode : public Node {
		public:
			std::unique_ptr<Node> exp;
			ParExpressionNode(std::unique_ptr<Node> e) : Node(NodeType::ParExpression), exp(std::move(e)) {};
		};
	
} // namespace wave::internal

// copyright (c) 2026 Victor Botelho Anunciação