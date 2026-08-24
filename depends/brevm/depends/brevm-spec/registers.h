/*
* BreVM - Registers
* registers.h
*/
#pragma once
#include <array>
#include <memory>
#include "runtime_value.h"

namespace brevm::spec 
{
    using reg = std::shared_ptr<RuntimeValue>;
    using registers = std::array<reg, 256>;
} // namespace brevm_spec 

// copyright (c) 2026 Victor Botelho Anunciação