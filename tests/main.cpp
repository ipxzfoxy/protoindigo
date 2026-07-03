
#include "../src/indigo.h"
#include "../utils/readBreFile.h"

#include <iostream>
#include <string>


int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cout << "Welcome to ProtoIndigo! Use indigo.exe <filepath.bre> to read an Indigo program and interpret it!" << std::endl;
		std::cout << "(c) 2026 Victor Botelho Anunciacao" << std::endl;
		return 0;
	}

	std::string rawFile = argv[1];

	std::string code = indigo::readBreFile(rawFile);
	indigo::internal::ast::Interpreter interpreter(code);
	interpreter.run();
	return 0;
	
}

// (c) 2026 Victor Botelho Anunciacao