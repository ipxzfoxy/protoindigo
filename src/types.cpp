#include "types.h"
#include <unordered_map>

namespace indigo::internal {
	const std::unordered_map<std::string, Type> types {
		{"string", Type::STRING},
		{"boolean", Type::BOOLEAN},
		{"number", Type::NUMBER},
		{"double", Type::TDOUBLE},
		{"null", Type::TNULL},
		{"struct", Type::STRUCTURE},
		{"class", Type::TCLASS},
		{"flag", Type::FLAG},
		{"auto", Type::TAUTO},
		{"function", Type::FUNCTION},
	};
}