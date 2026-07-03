#pragma once
#include "../tokenizer/lex-analyzer.h" 
#include "../types.h"
#include "./nodes/variable.h"
#include "./nodes/functions.h"
#include "./nodes/proto.h"

#include <memory>
#include <vector>
#include <optional>
#include <iostream>


namespace indigo::internal {
	namespace parser {
		class Parser {
			Lexer lex;
			Token ctk;
			std::vector<std::unique_ptr<Node>> ast;
			
			
			void consume();
			void protoAdv();
			void varAdv(bool isConst, std::string, std::string identifier);
			void functionAdv(std::string identifier);
			void analyzer(TokenType et);
			
		public:
			const std::vector<std::unique_ptr<Node>>& getAST() const;
			Parser(Lexer& lex);
			void parse();
		};
	}
}

// (c) 2026 Victor Botelho Anunciação