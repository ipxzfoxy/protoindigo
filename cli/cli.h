#pragma once
#include <string>
#include <format>
#include <vector>
#include <functional>
#include <unordered_map>
#include <stdexcept>
#include "operation/w_operation.h"
#include "src/utils/filesys.h"
#include "indigo/internal/diagnostics/error.h"
namespace bre::cli
{
    std::string vm_version();
    void version();
    void platform();
    void tokenizefile(std::string& filepath);
    void parsefile(std::string& filepath);
    bool init();
    void help();
    void startREPL();
    int run(std::vector<std::string> args);
} // namespace bre::cli

// copyright (c) 2026 Victor Botelho Anunciação
