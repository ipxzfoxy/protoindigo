/*
* ProtoIndigo Operation - Header
* Manages the interpreter's core components, processing source code and compiled instructions.
*/ 
#pragma once

#include <memory>
#include <string>
#include <vector>
#include <filesystem>
#include "src/utils/filesys.h"
#include "src/tokenizer/tokenizer.h"
#include "src/parsing/parser.h"
#include "src/lib/std.h"

#include "src/codegen/wave/compiler.h"
#include "depends/brevm/include/vm.h"
#include "depends/brevmr/include/runtime_value.hpp"

namespace bre {

class Operation {
public:
    Operation() {};

    int executeString(const std::string& source);
    int executeString(const std::string& source, std::vector<std::string> args);
    int inputFile(const std::string& path);
    int inputFile(const std::string& path, std::vector<std::string> args);
    std::vector<internal::Token> tokenizeString(const std::string& source);
    std::vector<std::unique_ptr<internal::Node>> parseString(const std::string& source);
};

Operation create_operation();

} // namespace wave

// copyright (c) 2026 Victor Botelho Anunciação