/**
 * Implements of BreVM methods (vm.h)
 * vm.cpp
 */
#include "include/vm.h"

namespace brevm
{
    VM::VM(
        constantPool cp, bytecodePool b
    ) : memory(std::move(cp)), bytecode(std::move(b))
    {
        if (bytecode.empty())
        {
            throw error::Error(
                "EmptyBytecodePool: The received bytecode pool contains no instructions."
            );
        }
        if (!(static_cast<OPC>(bytecode.back()) == OPC::HALT))
        {
            throw error::Error(
                "InvalidBytecodeTermination: Bytecode does not end with a valid terminating instruction, such as HALT."
            );
        }

        ip = 0;
        registers = {};
        stack = {};
        current = bytecode[ip];
    };

    uint8_t VM::adv()
    {
        ip++;
        if (ip >= bytecode.size()) 
        {
            throw error::Error(
                "BytecodeOutOfBounds: Attempted to advance beyond the bytecode boundary."
            );
        };
        return current = bytecode[ip];
    }

    std::shared_ptr<RuntimeValue> VM::spop()
    {
        std::shared_ptr<RuntimeValue> back = stack.back();
        stack.pop_back();
        return std::move(back);
    }
} // namespace brevm

// Copyright (c) 2026 Victor Botelho Anunciação.
// All rights reserved.