/*
* cmds.cpp
* This program contains all CLI command implementations for ProtoIndigo.
*/

#include "cmds.h"

namespace wave::cli
{

    std::string version() {
        return "2.0.2";
    }
    std::string vm_version() {
        return "0.0.1";
    }
    std::string platform()
    {
        return std::format("ProtoIndigo {}\nBreVM {}", version(), vm_version());
    }
    bool init()
    {
        return false;
    }
    void help()
    {
        wave::Operation operation;
        operation.executeString(wave::readBreFile("./scripts/Cli/help.bre"));
    }
    void startREPL()
    {
        wave::Operation OP = wave::create_operation();
        while(true) {
			std::cout << ">> ";
			std::string line;
            if (!std::getline(std::cin, line))
            {
                break;
            }
			if (line.empty()) continue;
			if (line == "exit") break;
            OP.executeString(line + "\n");
            
		}
    }
} // namespace wave::cli

// copyright (c) 2026 Victor Botelho Anunciação
