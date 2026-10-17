/*
* ProtoIndigo Operation - Header
* Manages the interpreter's core components, processing source code and compiled instructions.
*/ 
#include "w_operation.h"

namespace bre
{
    Operation create_operation()
    {
        return Operation();
    }

    int Operation::executeString(const std::string& source, std::vector<std::string> args)
    {
        internal::Tokenizer tokenizer(source);

        internal::Parser parser(tokenizer);
        parser.parse();

        internal::codegen::WaveCoder WC(parser.getAST());

        internal::brestdlib::installArgs(WC, args);

        WC.compile();

        brevm::VM engine(WC.getCP(), WC.getOutput());
        engine.execute();

        return 0;
    }

    int Operation::executeString(const std::string& source)
    {
        return executeString(source, {});
    }


    int Operation::inputFile(const std::string& path, std::vector<std::string> args)
    {
        std::filesystem::path filePath = std::filesystem::current_path() / path;
        auto [e, s] = bre::internal::readFile(path);
        if (e == 1)
        {
            throw std::runtime_error(std::format("[InitError] Module not found:\n{}", filePath.string()));
        } else if (e == 2) {
             throw std::runtime_error(std::format("[InitError] Error to read module.\n{}", filePath.string()));
        }

        internal::Tokenizer tokenizer(s);
        
        internal::Parser parser(tokenizer);
        parser.parse();
        internal::codegen::WaveCoder WC(parser.getAST());

        internal::brestdlib::installArgs(WC, args);
        WC.compile();

        brevm::VM engine(WC.getCP(), WC.getOutput());
        engine.execute();

        return 0;
    }

    int Operation::inputFile(const std::string& path)
    {
        return inputFile(path, {});
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