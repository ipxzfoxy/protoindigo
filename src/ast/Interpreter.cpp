#include "interpreter.h"

#include "../parsing/parser.h"
#include "../types.h"

#include <memory>
#include <vector>
#include <unordered_map>
#include <variant>
#include <iostream>

namespace indigo::internal {
	namespace ast {
		void Cache::set(const std::string& i, RV v) {
			cache.insert_or_assign(i, std::move(v));
		}

		std::optional<RV> Cache::get(const std::string& i) {
			auto it = cache.find(i);

			if (it != cache.end()) {
				return it->second;
			}
			else {
				return std::nullopt;
			}
		}

		void Interpreter::run() {
			p.parse();

			for (const auto& u : p.getAST()) {
				parser::Node* node = u.get();
				

				if (!node) continue;

				if (auto vn = dynamic_cast<parser::VariableNode*>(node)) {
					
					Variable varCache(vn->is_const, vn->id, vn->value);
					cache.set(vn->id, varCache);
					std::optional<RV> va = cache.get(vn->id);

				}

				if (auto pn = dynamic_cast<parser::ProtoNode*>(node)) {

					if (pn->isID) {
						std::optional<RV> va = cache.get(pn->rawv);
						if (va.has_value()) {
							auto& realVar = std::get<Variable>(va.value());

							std::visit([](const auto& val) {
								std::cout << val;
								}, realVar.value);

							std::cout << std::endl;
						}
						else {
							std::cout << "[Error] Identifier <"
								<< pn->rawv
								<< "> is not defined."
								<< std::endl;
							exit(0);
						}
					}
					else {
						std::cout << pn->rawv << std::endl;
					}
					
					
					

					

				}

				
			}
		}
	}
}