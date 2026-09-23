/*
* BreVM - Operand Stack
* ostack.h
*/
#pragma once
#include <vector>
#include <memory>
#include "runtime_value.hpp"

namespace brevm 
{
    using operandStack = std::vector<std::shared_ptr<RuntimeValue>>;

} // namespace brevm

// Copyright (c) 2026 Victor Botelho Anunciação.
// All rights reserved.