// Literal Proto Node - proto.h

#pragma once
#include <vector>
#include <memory>
#include "node.h"

namespace wave::internal {
		class ScopeExpressionNode : public Node {
		public:
			std::vector<std::unique_ptr<Node>> ast;
			ScopeExpressionNode(std::vector<std::unique_ptr<Node>> s) : Node(NodeType::Proto), ast(s) {};
		};
	
} // namespace wave::internal

// copyright (c) 2026 Victor Botelho Anunciação