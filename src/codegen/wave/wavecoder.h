#include <memory>
#include <vector>
#include <utility>
#include "depends/brevm/depends/brevm-spec/bytecode.h"
#include "depends/brevm/depends/brevm-spec/constant_pool.h"
#include "depends/brevm/depends/brevm-spec/wave.h"
#include "../../ast/ast.h"
#include "allocator.h"

namespace wave::internal
{
    class WaveCoder
    {
        std::vector<std::unique_ptr<Node>> ast;
        Allocator allocator;
        brevm::spec::WaveCode output;
        size_t cp_count;
        size_t var_count;
    public:
        void compile();
        int compile_literal(Node& node);
        brevm::spec::bytecodePool compile_exp(Node& node);
        WaveCoder(std::vector<std::unique_ptr<Node>> a) : ast(std::move(a)), allocator() {};
    };
   
}