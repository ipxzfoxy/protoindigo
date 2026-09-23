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
        internal::codegen::WaveCoder compiler(parser.getAST());

        std::string space = "_BETA_STD";
        std::string v = INDIGO_VERSION;

        compiler.eject_symbol(space + "_VERSION", brevm::String(v), true);
        compiler.compile();




        compiler.compile();

   

        brevm::VM vm(compiler.getCP(), compiler.getOutput());

      

        vm.execute();

      
        return 0;
    }

    int Operation::inputFile(const std::string& path, int argc, char* argv[])
    {
        std::string source = wave::readBreFile(path);
        internal::Tokenizer tokenizer(source);
        internal::Parser parser(tokenizer);
        parser.parse();
        internal::codegen::WaveCoder compiler(parser.getAST());

        std::string space = "_BETA_STD";
        std::string v = INDIGO_VERSION;

        compiler.eject_symbol(space + "_VERSION", brevm::String(v), true);
        compiler.eject_symbol(space + "_FIRSTARG", brevm::String(argv[3]), true);
        compiler.compile();




        compiler.compile();

   

        brevm::VM vm(compiler.getCP(), compiler.getOutput());

      

        vm.execute();

      
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