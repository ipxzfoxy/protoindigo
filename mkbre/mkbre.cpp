/*
 * ============================================================
 * ============ Mkbre - Build Tool for ProtoIndigo ============
 * ============================================================
 *
 * This file contains the main implementation of the Mkbre tool,
 * used to automate the Breeze interpreter build process.
 *
 * Responsibilities:
 *  - Manage interpreter compilation;
 *  - Execute build processes through the CLI;
 *  - Generate the pit.exe executable (ProtoIndigo Test);
 *  - Simplify runtime development and testing.
 *
 * mkbre.cpp
 */

#include <iostream>
#include <cstdlib>
#include <filesystem>

int main()
{
    std::cout << "[Mkbre] Starting build process..." << std::endl;

    int result = std::system("cmake --build build");

    if (result != 0)
    {
        std::cout << "[Mkbre] Build failed." << std::endl;
        return 1;
    }

    std::cout << "[Mkbre] Installing pit executable..." << std::endl;

    try
    {
        std::filesystem::create_directories("C:/Breeze");

        std::filesystem::copy_file(
            "build/indigo.exe",
            "C:/Breeze/pit.exe",
            std::filesystem::copy_options::overwrite_existing
        );

        std::cout << "[Mkbre] Installed successfully." << std::endl;
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        std::cerr << "[Mkbre] Install failed: "
                << e.what() << std::endl;
    }
}