// Literal Array Node - array.h
#pragma once
#include <vector>
#include <memory>
#include <utility>
#include "../node.h"

namespace wave::internal {
		class LiteralArrayNode : public Node {
		public:
			std::vector<std::unique_ptr<Node>> value;
			LiteralArrayNode(std::vector<std::unique_ptr<Node>> value) : Node(NodeType::LiteralArray), value(std::move(value)) {}
		};
	
} // namespace wave::internal

// copyright (c) 2026 Victor Botelho Anunciação