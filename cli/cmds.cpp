/*
* cmds.cpp
* This program contains all CLI command implementations for ProtoIndigo.
*/

#include "cmds.h"

namespace wave::cli
{

    std::string version() {
        return "2.0.0";
    }
    std::string platform()
    {
        return std::format("ProtoIndigo {}", version());
    }
    bool init()
    {
        return false;
    }
    std::string help()
        {
            return std::format(
                "Welcome to ProtoIndigo {}\n"
                "\n"
                "Usage:\n"
                "  indigo              Start the Indigo REPL\n"
                "  indigo run <file>   Execute an Indigo source file\n"
                "\n"
                "Commands:\n"
                "  help                Show this help message\n"
                "  -v                  Show version information\n"
                "  platform            Show platform version\n"
                "  --tokenize          Tokenizes a .bre file and displays the result in the output.\n"
                "  --parse             Parser a .bre file.\n"
                "\n"
                "Examples:\n"
                "  indigo\n"
                "  indigo run hello.bre\n"
                "\n"
                "https://github.com/ipxzfoxy/protoindigo\n"
                "(c) 2026 Victor Botelho Anunciacao\n",
                version()
            );
    }
    void startREPL()
    {
        while(true) {
			std::cout << ">> ";
			std::string line;
			std::getline(std::cin, line);
			if (line.empty()) continue;
			if (line == "exit") break;

            wave::Operation OP = wave::create_operation();
            OP.executeString(line);
		}
    }
} // namespace wave::cli

// copyright (c) 2026 Victor Botelho Anunciação
