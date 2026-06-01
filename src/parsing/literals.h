#pragma once
#include "parser.h"

namespace indigo::internal {
	namespace parser {
		class Literals : public Node {
		public:
			std::string id;
			std::string value;

			Literals(std::string id, std::string value)
				: id(id), value(value) {
			};
		};
	}
}

// (c) 2026 Victor Botelho Anunciação