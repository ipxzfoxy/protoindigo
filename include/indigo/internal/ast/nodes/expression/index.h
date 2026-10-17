// Literal Proto Node - proto.h

#pragma once
#include <vector>
#include <memory>
#include "../node.h"

namespace bre::internal {
		class IndexExpressionNode : public Node {
		public:
			size_t index;
            NodeUniquePtr target;
			IndexExpressionNode(size_t i, NodeUniquePtr t) : Node(NodeType::IndexExpression), index(i), target(std::move(t)) {};
		};
	
} // namespace wave::internal

// copyright (c) 2026 Victor Botelho Anunciação