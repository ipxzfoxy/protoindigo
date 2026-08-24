/*
* BreVM - Constant Pool
* constant_pool.h
*/
#pragma once
#include <vector>
#include <memory>
#include "runtime_value.h"

namespace brevm::spec 
{
    using constantPool = std::vector<std::shared_ptr<RuntimeValue>>;
} // namespace brevm_spec 

// copyright (c) 2026 Victor Botelho Anunciação