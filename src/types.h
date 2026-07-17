#pragma once
#include <unordered_map>
#include <variant>
#include <string>

namespace indigo::internal {
	enum class Type {
		STRING, BOOLEAN, NUMBER, TDOUBLE, TNULL, STRUCTURE, TCLASS, FLAG, TAUTO, FUNCTION
	};

	using PV = std::variant<std::string, bool, int, double>;
}