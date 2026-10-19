/*
* cmds.cpp
* This program contains all CLI command implementations for ProtoIndigo.
*/
#define YELLOW "\033[93m"
#define CLI_RED "\033[91m"
#define RESET  "\033[0m"
#include "cli.h"
#include "src/utils/filesys.h"

namespace bre::cli
{
    void runfile(std::string& path, std::vector<std::string> args) {
        Operation O;
        O.inputFile(path, args);
    }
    void tokenizefile(std::string& filepath, bool showResult)
    {
        Operation O = create_operation();
        auto [code,  content] = internal::readFile(filepath);

        if (code == 1)
            throw internal::NFError(filepath);
        if (code == 2)
            throw internal::NFError(filepath);
        O.tokenizeString(content);

    }
    void parsefile(std::string& filepath)
    {
        Operation O = create_operation();
        auto [code,  content] = internal::readFile(filepath);

        if (code == 1)
            throw internal::NFError(filepath);
        if (code == 2)
            // ========= FIXXXXX =========
            throw internal::NFError(filepath);
        O.parseString(content);
        std::cout << 0;
    }
    void showv()
    {
        std::cout << INDIGO_VERSION << "\n";
    }
    void showvmv()
    {
        std::cout << BREVM_VERSION << "\n";
    }
    void platform()
    {
        showv();
        showvmv();
    }
    void help()
    {
       Operation O;
        auto path = std::filesystem::path(internal::getExecutablePath())
            / "scripts"
            / "Cli"
            / "help.bre";

        O.inputFile(path.string(), std::vector<std::string>{});
    }
    void startREPL()
    {
        std::cout << "Welcome to ProtoIndigo v" << INDIGO_VERSION <<"!\n";
        std::cout << " type \"exit\" to exit, \"help\" to help.\n";
        bre::Operation O = bre::create_operation();
        while(true) {
			std::cout << ">> ";
			std::string line;
            if (!std::getline(std::cin, line))
            {
                break;
            }
			if (line.empty()) continue;
			if (line == "exit") break;
            if (line == "help") help();
            O.executeString(line + "\n");
            
		}
    }
    int run(std::vector<std::string> args) {

        // =========== REPL ===========

        if (args.size() < 2 || args[1] == "repl") {
            cli::startREPL();
            return 0;
        }

        // =========== RunFile ===========

        if (args[1] == "run") {
            if (args.size() < 3) {
                throw std::runtime_error(
                    "[InitError] Missing required argument.\nUsage: indigo run <file>"
                );
            }

            runfile(args[2], args);
            return 0;
        }

        if (args[1].ends_with(".bre")) {
            runfile(args[1], args);
            return 0;
        }

        // =========== Help ===========

        if (args[1] == "help") {
            help();
            return 0;
        }


        // =========== Help ===========
        if (args[1] == "-v") {
            version();
            return 0;
        }

        if (args[1] == "platform") {
            version();
            return 0;
        }

        help();
        return 0;

    }
} // namespace bre::cli

// copyright (c) 2026 Victor Botelho Anunciação
