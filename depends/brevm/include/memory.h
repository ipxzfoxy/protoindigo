#pragma once
#include <memory>
#include <vector>
#include <format>
#include <utility>
#include "depends/brevmr/include/bytecode.hpp"
#include "depends/brevmr/include/constant_pool.hpp"
#include "depends/brevmr/include/runtime_value.hpp"
#include "diagnostics/error.h"

namespace brevm
{
    class Memory 
    {
        constantPool cp = {};
        std::vector<std::shared_ptr<RuntimeValue>> heap = {};
        std::vector<std::shared_ptr<RuntimeValue>> slots = {};
    public:
        ~Memory() = default;
        Memory(constantPool cp) : cp(std::move(cp)) {};
        const std::shared_ptr<RuntimeValue>& getConstant(size_t i) const;
        const constantPool& getCP() const { return cp; };
        void halloc(std::shared_ptr<RuntimeValue> v);
        void store_slot(size_t index, std::shared_ptr<RuntimeValue> v);
        std::shared_ptr<RuntimeValue> ld_slot(size_t index);
    };
} // namespace brevm

// Copyright (c) 2026 Victor Botelho Anunciação.
// All rights reserved.