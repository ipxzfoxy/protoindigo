#pragma once
#include "parser.h"
#include <vector>


namespace indigo::internal {
	namespace parser {
		class Function : public Node {
		public:
			std::string id;
			std::vector<std::unique_ptr<Node>> body;
			std::vector<std::string> params;
			
			Function(std::string id, std::vector<std::string> params, std::vector<std::unique_ptr<Node>> body)
				: id(id), params(params), body(std::move(body)) {};
		};
	}
}

// (c) 2026 Victor Botelho Anunciação