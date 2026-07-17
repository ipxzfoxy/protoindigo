#pragma once
#include "node.h"
#include "../../types.h"

#include <vector>

namespace indigo::internal {
	namespace parser {
		class FunctionNode : public Node {
			class Node;
		public:
			bool is_const;
			std::optional<Type> typing;
			std::string id;
			std::string src;

			
			std::vector<std::string> params;
			
			FunctionNode(bool is_const, std::optional<Type> typing, std::string id, std::vector<std::string> params, std::string src)
				: is_const(is_const), typing(typing), id(id), params(params), src(src) {};
		};
	}
}

// (c) 2026 Victor Botelho Anunciação