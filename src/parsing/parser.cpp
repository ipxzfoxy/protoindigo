
#include "parser.h"
#include "./nodes/variable.h"
#include "./nodes/functions.h"
#include "./nodes/proto.h"
#include "../tokenizer/lex-analyzer.h"
#include "../types.h"

namespace indigo::internal {
	namespace parser {

		const std::vector<std::unique_ptr<Node>>& Parser::getAST() const {
			return ast;
		}
		void Parser::consume() {
			ctk = lex.next();
		}
		void Parser::analyzer(TokenType et) {
			if (ctk.getType() == et) {
				consume();
			}
			else {
				std::cout << "Syntax Error! Expected: " << (int)et
					<< " but: " << (int)ctk.getType()
					<< " = '" << ctk.getValue() << "'" << std::endl;
				exit(1);
			}
		}

		void Parser::protoAdv() {
			consume();
			TokenType t = ctk.getType();

			if (t == TokenType::STRING ||
				t == TokenType::BOOLEAN ||
				t == TokenType::NUMBER ||
				t == TokenType::IDENTIFIER)
			{
				bool isVar = false;
				if (t == TokenType::IDENTIFIER) isVar = true;
				ast.push_back(std::make_unique<ProtoNode>(ctk.getValue(), isVar));
			}
			else {
				std::cout << "[Syntax Error]: <proto> received a invalid input type. Expected: [\n"
					<< "<#string>\n"
					<< "<#number>\n"
					<< "<#boolean>\n"
					<< "<identifier>]"
					<< std::endl;
				exit(1);
			}

			
		}
		void Parser::varAdv(bool constant, std::string t, std::string identifier) {
			

			analyzer(TokenType::EQUAL);

			const PV value = ctk.getValue();


			if (!(ctk.getType() == TokenType::NUMBER ||
				ctk.getType() == TokenType::STRING ||
				ctk.getType() == TokenType::BOOLEAN)) {

				std::cout << "Invalid Type on: " << identifier << std::endl;

				std::cout << "Received: ";
				std::visit([](auto&& v) {
					std::cout << v;
					}, value);

				std::cout << std::endl;

				exit(1);
			}

			consume();

			analyzer(TokenType::SEMICOLON);

			/*std::cout
				<< "Variable Detected: \n"
				<< "Is constant: "
				<< std::boolalpha
				<< constant
				<< "\n"
				<< "Typing: #"

				<< t
				<< "\nName: "
				<< identifier
				<< " Value: ";

			std::visit([](auto&& v) {
				std::cout << v;
				}, value);

			std::cout << std::endl;

			std::cout << "Creating VariableNode..." << std::endl;
			*/

			VariableNode variable(constant, t, identifier, value);
			ast.push_back(std::make_unique<VariableNode>(constant, t, identifier, value));

		}
		void Parser::functionAdv(std::string identifier) {
			
			std::vector<std::string> params;
			std::vector<std::unique_ptr<Node>> body;

			consume();

			while (ctk.getType() != TokenType::RPAREN) {
				if (ctk.getType() == TokenType::IDENTIFIER) {
					/*std::cout
						<< "Parameter Detected: "
						<< "Name: "
						<< ctk.getValue()
					<< std::endl;*/
			
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
				if (ctk.getType() == TokenType::NEW)
				{
					bool constant = false;
					std::string type = "auto";

					analyzer(TokenType::NEW);

					if (ctk.getType() == TokenType::CONST)
					{
						constant = true;
						consume();
					}

					if (ctk.getType() == TokenType::TYPING)
					{
						type = ctk.getValue();
						consume();
					}
					
					const std::string identifier = ctk.getValue();
					analyzer(TokenType::IDENTIFIER);

					if (ctk.getType() == TokenType::EQUAL) varAdv(constant, type, identifier);
					if (ctk.getType() == TokenType::LPAREN) functionAdv(identifier);

				}
				else if (ctk.getType() == TokenType::PROTO) {
					protoAdv();
				}
				else consume();
			}
		}

		Parser::Parser(Lexer& lex) : lex(lex), ctk(TokenType::T_EOF, "") {
			consume();
		}



	}
}

// (c) 2026 Victor Botelho Anunciação