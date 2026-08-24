// Literal Proto Node - proto.h

#pragma once
#include <variant>
#include <string>
#include <memory>
#include "node.h"

namespace wave::internal {
		class ProtoNode : public Node {
		public:
			std::unique_ptr<Node> value;
			ProtoNode(std::unique_ptr<Node> value) : Node(NodeType::Proto), value(std::move(value)) {};
		};
	
} // namespace wave::internal

// copyright (c) 2026 Victor Botelho Anunciação