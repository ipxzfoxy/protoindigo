#pragma once
#include <vector>
#include <iostream>
#include <format>
#include <cmath>
#include "depends/brevm-spec/bytecode.h"
#include "depends/brevm-spec/constant_pool.h"
#include "depends/brevm-spec/registers.h"
#include "depends/brevm-spec/runtime_value.h"
#include "diagnostics/error.h"
#include "memory.h"

namespace brevm
{
    using namespace spec;
    class VM
    {
        spec::bytecodePool bytecode = {};
        spec::registers registers = {};
        Memory memory;
        void push();
    public:
        int execute(spec::bytecodePool bc);
        VM(spec::constantPool constantPool);

        std::shared_ptr<spec::RuntimeValue> add(
            const spec::reg& left,
            const spec::reg& right
        );
        std::shared_ptr<spec::RuntimeValue> VM::sub(
            const spec::reg& left,
            const spec::reg& right
        );
        std::shared_ptr<spec::RuntimeValue> VM::mul(
            const spec::reg& left,
            const spec::reg& right
        );
        std::shared_ptr<spec::RuntimeValue> VM::div(
            const spec::reg& left,
            const spec::reg& right
        );
        std::shared_ptr<spec::RuntimeValue> VM::mod(
            const spec::reg& left,
            const spec::reg& right
        );
    };
} // namespace brevm
 