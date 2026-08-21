#pragma once
#include <string>
#include <fstream>
#include <format>
#include "utils/readBreFile.h"
#include "operation/w_operation.h"

namespace wave::cli
{
    std::string vm_version();
    std::string version();
    std::string platform();

    bool init();
    void help();
    void startREPL();
} // namespace wave::cli

// copyright (c) 2026 Victor Botelho Anunciação
