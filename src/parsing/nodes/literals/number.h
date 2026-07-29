// Literal Number Node - number.h
#pragma once
#include <vector>
#include "../node.h"

namespace wave::internal {
	
		class LiteralNumberNode : public Node {
		public:
			double num;
			LiteralNumberNode(double num) : Node(NodeType::LiteralNumber), num(num) {}
		};
	
} // namespace wave::internal

// copyright (c) 2026 Victor Botelho Anunciação