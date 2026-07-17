#pragma once
#include <optional>
#include <string>

namespace indigo::internal {
	namespace parser {
		class Node {
			std::optional<std::string> identifier;
		public:
			virtual ~Node() = default;
		};
	}
}