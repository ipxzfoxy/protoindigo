/*
* BreVM - Constant Pool
* constant_pool.h
*/
#pragma once
#include <vector>
#include <memory>
#include "runtime_value.hpp"

namespace brevm
{
    using constantPool = std::vector<std::shared_ptr<RuntimeValue>>;
} // namespace brevm

// Copyright (c) 2026 Victor Botelho Anunciação.
// All rights reserved.