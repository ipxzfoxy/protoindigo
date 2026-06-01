#pragma once
#include "../tokenizer/lex-analyzer.h"
#include <memory>
#include <iostream>
#include <vector>
#include <string>

namespace indigo::internal {
	namespace parser {

		class Node {
		public:
			virtual ~Node() = default;
		};

		class Parser {
			Lexer lex;
			Token ctk;
			std::vector<std::unique_ptr<Node>> ast;
 
			void consume();
			void literalAdv(std::string identifier);
			void functionAdv(std::string identifier);
			void analyzer(TokenType et);
			
		public:
			Parser(Lexer& lex);
			void parse();
		};
	}
}

// (c) 2026 Victor Botelho Anunciação