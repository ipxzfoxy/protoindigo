#pragma once
#include <vector>
#include <iostream>
#include <format>
#include <cmath>
#include <memory>
#include "depends/brevmr/include/bytecode.hpp"
#include "depends/brevmr/include/constant_pool.hpp"
#include "depends/brevmr/include/registers.hpp"
#include "depends/brevmr/include/ostack.hpp"
#include "depends/brevmr/include/runtime_value.hpp"
#include "depends/brevmr/include/opcode.hpp"
#include "diagnostics/error.h"
#include "memory.h"

namespace brevm
{
    class VM
    {
        bytecodePool bytecode;
        registers registers;
        operandStack stack;
        Memory memory;
        size_t ip;
        uint8_t current;
        uint8_t adv();
    public:
        int execute();
        VM(
            constantPool constantPool,
            bytecodePool bytecodePool
        );

        std::shared_ptr<RuntimeValue> add(
            const std::shared_ptr<RuntimeValue>& left,
            const std::shared_ptr<RuntimeValue>& right
        );
        std::shared_ptr<RuntimeValue> sub(
            const std::shared_ptr<RuntimeValue>& left,
            const std::shared_ptr<RuntimeValue>& right
        );
        std::shared_ptr<RuntimeValue> mul(
            const std::shared_ptr<RuntimeValue>& left,
            const std::shared_ptr<RuntimeValue>& right
        );
        std::shared_ptr<RuntimeValue> div(
            const std::shared_ptr<RuntimeValue>& left,
            const std::shared_ptr<RuntimeValue>& right
        );
        std::shared_ptr<RuntimeValue> mod(
            const std::shared_ptr<RuntimeValue>& left,
            const std::shared_ptr<RuntimeValue>& right
        );

        std::shared_ptr<RuntimeValue> spop();
    };
} // namespace brevm
 
// Copyright (c) 2026 Victor Botelho Anunciação.
// All rights reserved.