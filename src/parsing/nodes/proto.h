#pragma once
#include "../../types.h"
#include "node.h"
#include <variant>

namespace indigo::internal {
	namespace parser {
		class ProtoNode : public Node {
			class Node;
		public:
			std::string rawv;
			bool isID;
			ProtoNode(std::string val, bool isID) : rawv(val), isID(isID) {};
		};
	}
}

// (c) 2026 Victor Botelho Anunciação