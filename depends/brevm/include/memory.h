#pragma once
#include <memory>
#include <vector>
#include <format>
#include <utility>
#include "depends/brevm-spec/bytecode.h"
#include "depends/brevm-spec/constant_pool.h"
#include "depends/brevm-spec/runtime_value.h"
#include "diagnostics/error.h"

namespace brevm
{
    class Memory 
    {
        spec::constantPool constantPool = {};
        std::vector<std::shared_ptr<spec::RuntimeValue>> heap = {};
    public:
        ~Memory() = default;
        Memory(spec::constantPool cp) : constantPool(std::move(cp)) {};
        
        // METHODS
        const std::shared_ptr<spec::RuntimeValue>& getConstant(size_t i) const;

        const spec::constantPool& getCP() const { return constantPool; };

        void halloc(std::shared_ptr<spec::RuntimeValue>);
    };
} // namespace brevm
