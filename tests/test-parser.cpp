
#include "../src/indigo.h"
#include <iostream>
#include <string>
#include <fstream>

int main() {

	std::cout << "ProtoIndigo (c) 2026 Victor Botelho Anunciacao" << std::endl;
	std::cout << "**********************************" << std::endl;

	std::ifstream file("tests/index.txt");

	if (!file.is_open()) {
		std::cerr << "Error to read the file." << std::endl;
		return 1;
	}

	std::string code;
	std::string line;

	while (std::getline(file, line)) code += line + "\n";

	indigo::internal::Lexer lexer(code);
	indigo::internal::parser::Parser parser(lexer);

	parser.parse();

	return 0;
}

// (c) 2026 Victor Botelho Anunciacao