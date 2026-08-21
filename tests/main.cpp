#include <iostream>
#include <filesystem>
#include "operation/w_operation.h"

int main(int argc, char* argv[]) {
    if (argc < 2)
    {
        std::cout << "Welcome to ProtoIndigo!" << std::endl;
		std::cout << " type \"exit\" to exit." << std::endl;
        wave::cli::startREPL();
        return 0;
    };

    std::string cmd = argv[1];

    if (cmd == "run")
    {
        std::string code = wave::readBreFile(argv[2]);
        wave::Operation OP = wave::create_operation();
        OP.executeString(code);
        return 0;
    }
    if (cmd == "platform")
    {
        std::cout << wave::cli::platform() << std::endl;
    } else
    if (cmd == "-v")
    {
        std::cout << wave::cli::version() << std::endl;
    } else
    if (cmd == "--tokenize")
    {
        
        std::string code = wave::readBreFile(argv[2]);
        wave::Operation OP = wave::create_operation();
        std::cout << "Initialing Tokenizer..." << std::endl;
        std::vector<wave::internal::Token> t = OP.tokenizeString(code);
        std::cout << "Tokens: " << t.size() << '\n';
        std::cout << std::format("Tokens of {}", std::filesystem::path(argv[2]).filename().string()) << std::endl;
        for (auto& token : t)
        {
            std::cout << "Type: " << static_cast<int>(token.getType()) << " Value: ";
            std::visit([](const auto& value) {
                std::cout << value;
            }, token.getValue());

            std::cout << std::endl;
        }
        return 0;
    } else
    if (cmd == "--parse")
    {
        
        std::string code = wave::readBreFile(argv[2]);
        wave::Operation OP = wave::create_operation();
        std::cout << "Initialing Parser..." << std::endl;
        OP.parseString(code);
        std::cout << argv[2] << " parsed." << std::endl;
        return 0;
    } else
    if (cmd == "help")
    {
        wave::cli::help();
    } else 
    {
        wave::cli::help();
    }
}