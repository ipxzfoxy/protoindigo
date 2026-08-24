#pragma once
#include <variant>
#include <string>
#include "node.h"

namespace wave::internal {
		class IdentifierNode : public Node {
		public:
			std::string value;
            IdentifierNode(std::string v) : Node(NodeType::Identifier), value(v) {}
		};
} // namespace wave::internal

// (c) 2026 Victor Botelho Anunciação