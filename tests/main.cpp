#include "../src/indigo.h"
#include "../utils/readBreFile.h"

#include <iostream>
#include <string>

void showHelp()
{
    std::cout << "Welcome to ProtoIndigo 1.0.1\n";

    std::cout << "Usage:\n";
    std::cout << "  indigo              Start the Indigo REPL\n";
    std::cout << "  indigo run <file>   Execute an Indigo source file\n\n";

    std::cout << "Commands:\n";
    std::cout << "  help                Show this help message\n";
    std::cout << "  -v                  Show version information\n\n";

    std::cout << "Examples:\n";
    std::cout << "  indigo\n";
    std::cout << "  indigo run hello.bre\n\n";

	std::cout << "https://github.com/ipxzfoxy/protoindigo\n";
    std::cout << "(c) 2026 Victor Botelho Anunciacao\n";
}

int main(int argc, char* argv[])
{
	if (argc < 2) {
		std::cout << "Welcome to ProtoIndigo 1.0.1!" << std::endl;
		std::cout << " type \"exit\" to exit." << std::endl;

		while(true) {
			std::cout << ">> ";
			std::string line;
			std::getline(std::cin, line);
			if (line.empty()) continue;
			if (line == "exit") break;
			indigo::internal::ast::Interpreter interpreter(line);
			interpreter.run();
		}

		return 0;
	}

	std::string command = argv[1];

	if (command == "run") {
		std::string code = indigo::readBreFile(argv[2]);
		indigo::internal::ast::Interpreter interpreter(code);
		interpreter.run();
		
	} else if (command == "-v") {
		std::cout << "ProtoIndigo 1.0.1" << std::endl;
		
	} else if (command == "help") {
		showHelp();
	} else showHelp();

	return 0;
	
}

// (c) 2026 Victor Botelho Anunciacao