#include <iostream>
#include <filesystem>
#include <vector>
#include <indigo.h>
#include "cli.h"
#include "indigo/internal/diagnostics/error.h"

int main(int argc, char* argv[]) {

    std::vector<std::string> args;

    for (int i = 0; i < argc; i++)
        args.emplace_back(argv[i]);
    

    try {
        bre::cli::run(args);
    } catch (bre::internal::Error& err) {
        std::cerr << RED << err.name() << ": " << err.message();

        const auto detail = err.detail();
        if (!detail.empty())
            std::cerr << "\n" << detail;

        std::cerr << '\n' << RESET;
    } catch (const std::exception& err) {
        std::cerr << RED  << err.what() << '\n' << RESET;
    } catch (...) {
        std::cerr << RED << "UnknownError: An unknown exception occurred.\n" << RESET;
    }

}