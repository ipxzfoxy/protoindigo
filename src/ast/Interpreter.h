#pragma once

#include "../parsing/parser.h"
#include "../types.h"
#include <memory>
#include <vector>
#include <unordered_map>
#include <variant>

namespace indigo::internal {
	namespace ast {

		class FunctionParam {
			std::string identifier;
			std::string docType;
		public:
			FunctionParam(std::string identifier, std::string docType)
				: identifier(identifier), docType(docType) {};
		};


		class CacheValue {
		public:
			bool isConst = false;
			Type typing;
			CacheValue(bool isConst, Type typing)
				: isConst(isConst), typing(typing) {};
		};

		class Variable : public CacheValue {
		public:
			std::string identifier;
			//Type type;
			PV value;

			//Variable(bool isConst, Type typing, std::string identifier, Type type, PV value)
				//: CacheValue(isConst, typing), identifier(identifier), type(type), value(value) {};

			Variable(bool isConst, std::string identifier, PV value)
				: CacheValue(isConst, typing), identifier(identifier), value(value) {};
		};

		class Function : public CacheValue {
		public:
			std::string identifier;
			std::vector<FunctionParam> parameters;
			Type typingReturns;
			std::vector<parser::Node> scope;
		public:
			Function(bool isConst, std::string identifier, std::vector<FunctionParam> parameters, Type typingReturns, std::vector<parser::Node> scope)
				: CacheValue(isConst, Type::FUNCTION), identifier(identifier), parameters(parameters), typingReturns(typingReturns), scope(scope) {}
		};

		using RV = std::variant<Variable, Function>;
		class Cache {
			std::unordered_map<std::string, RV> cache;

		public:
			std::optional<RV> get(const std::string& i);
			void set(const std::string& i,RV v);
		};

		class Interpreter {
			Lexer lex;
			parser::Parser p;
			std::vector<std::unique_ptr<parser::Node>> generatedAst;
			Cache cache;
			//void v(parser::VariableNode* varNode);
			//void f(parser::FunctionNode* funcNode);
		public:
			Interpreter(std::string src) : lex(src), p(lex) {};
			void run();


		};
	}
}