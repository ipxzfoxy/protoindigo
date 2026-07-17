#pragma once
#include "../../types.h"
#include "node.h"
#include <optional>

namespace indigo::internal {
	namespace parser {
		class VariableNode : public Node {
			class Node;
		public:
			bool is_const;
			std::string typing;
			std::string id;
			PV value;
			
			VariableNode(bool isConst, std::string typing, std::string id, PV value)
				: is_const(isConst), typing(typing), id(id), value(value) {
			};
		};
	}
}

// (c) 2026 Victor Botelho Anunciação