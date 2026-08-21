/*
* ProtoIndigo Operation - Header
* Manages the interpreter's core components, processing source code and compiled instructions.
*/ 
#include "w_operation.h"

namespace wave
{
    Operation create_operation()
    {
        return Operation();
    }

    int Operation::executeString(const std::string& source)
    {
        internal::Tokenizer tokenizer(source);
        internal::Parser parser(tokenizer);
        parser.parse();
        internal::Compiler compiler(parser.getAST());
        compiler.compile();
        internal::VM vm(compiler.getOutput(), compiler.getCP());
        vm.run();
        return 0;
    }

    int Operation::execute(
        internal::compiler_output bytecode,
        internal::compiler_constant_pool constantPool
    )
    {
        internal::VM vm(bytecode, constantPool);
        vm.run();
        return 0;
    }

    std::vector<internal::Token> Operation::tokenizeString(const std::string& source)
    {
        internal::Tokenizer tokenizer(source);
        tokenizer.tokenize();
        return tokenizer.getOutput();
    }

    std::vector<std::unique_ptr<internal::Node>> Operation::parseString(const std::string& source)
    {
        internal::Tokenizer tokenizer(source);
        internal::Parser parser(tokenizer);
        parser.parse();
        return parser.getAST();
    }
} // namespace wave

// copyright (c) 2026 Victor Botelho Anunciação