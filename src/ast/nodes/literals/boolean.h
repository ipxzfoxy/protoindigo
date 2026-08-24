// Literal Boolean Node - boolean.h
#pragma once
#include <vector>
#include "../node.h"

namespace wave::internal {
		class LiteralBoolNode : public Node {
		public:
			bool condition;
			LiteralBoolNode(bool condition) : Node(NodeType::LiteralBoolean), condition(condition) {}
		};
	
} // namespace wave::internal

// copyright (c) 2026 Victor Botelho Anunciação