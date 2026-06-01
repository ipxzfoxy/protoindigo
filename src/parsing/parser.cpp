#pragma 
#include <memory>
#include "parser.h"
#include "literals.h"
//#include "functions.h"

namespace indigo::internal {
	namespace parser {

		void Parser::consume() {
			ctk = lex.next();
		}
		void Parser::analyzer(TokenType et) {
			if (ctk.getType() == et) {
				consume();
			}
			else {
				std::cout << "Syntax Error! Expected: " << (int)et
					<< " but received: " << (int)ctk.getType()
					<< " = '" << ctk.getValue() << "'" << std::endl;
				exit(1);
			}
		}

		void Parser::literalAdv(std::string identifier) {
			std::cout << "Starting Literal parser" << std::endl;

			analyzer(TokenType::EQUAL);

			const std::string value = ctk.getValue();


			if (!(ctk.getType() == TokenType::NUMBER || ctk.getType() == TokenType::STRING || ctk.getType() == TokenType::BOOLEAN)) {
				std::cout << "Invalid Type on: " << identifier << std::endl;
				std::cout << "Received: " << value << std::endl;
				exit(1);
			}
			consume();

			analyzer(TokenType::SEMICOLON);

			std::cout
				<< "Identifier Detected: "
				<< "Name: "
				<< identifier
				<< " Value: "
				<< value
				<< std::endl;

			std::cout << "Saving..." << std::endl;

			Literals literal(identifier, value);
			ast.push_back(std::make_unique<Literals>(identifier, value));

			std::cout << "Saved!" << std::endl;
			std::cout << "----------------------" << std::endl;
		}
		void Parser::functionAdv(std::string identifier) {
			std::cout << "Starting Function parser" << std::endl;
			std::vector<std::string> params;
			std::vector<std::unique_ptr<Node>> body;

			consume();

			while (ctk.getType() != TokenType::RPAREN) {
				if (ctk.getType() == TokenType::IDENTIFIER) {
					std::cout
						<< "Parameter Detected: "
						<< "Name: "
						<< ctk.getValue()
					<< std::endl;
			
					params.push_back(ctk.getValue());
					consume();
				}
				if (ctk.getType() == TokenType::COMMA) consume();
			}
			consume();
			analyzer(TokenType::LBRACE);

			analyzer(TokenType::RBRACE);
			analyzer(TokenType::SEMICOLON);
			
		}

		void Parser::parse()
		{
			while (ctk.getType() != TokenType::T_EOF) {
				if (ctk.getType() == TokenType::NEW) {

					analyzer(TokenType::NEW);

					const std::string identifier = ctk.getValue();
					analyzer(TokenType::IDENTIFIER);

					if (ctk.getType() == TokenType::EQUAL) literalAdv(identifier);
					if (ctk.getType() == TokenType::LPAREN) functionAdv(identifier);

				}
			}
		}

		Parser::Parser(Lexer& lex) : lex(lex), ctk(TokenType::T_EOF, "") {
			consume();
		}



	}
}

// (c) 2026 Victor Botelho Anunciação