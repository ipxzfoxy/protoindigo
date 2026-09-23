/*
* BreVM - Registers
* registers.h
*/
#pragma once
#include <array>
#include <memory>
#include "runtime_value.hpp"

namespace brevm 
{
    using reg = std::shared_ptr<RuntimeValue>;
    using registers = std::array<reg, 256>;
} // namespace brevm

// Copyright (c) 2026 Victor Botelho Anunciação.
// All rights reserved.