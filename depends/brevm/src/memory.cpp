/**
 * Implements of BreVM Memory (memory.h)
 * Component responsible for managing the BreVM memory subsystems, including Slots, Constant Pool, and Heap
 * memory.cpp
 */
#include "include/memory.h"

namespace brevm
{
    /**
     * @brief Retrieves a constant from the constant pool.
     * @param index Index o the constant.
     * @return The constant from constant pool
     * @throws brevm::error::Error If the constant pool index is invalid.
     */
    const std::shared_ptr<RuntimeValue>& Memory::getConstant(size_t i) const {
        if (i > cp.size())
            throw error::Error(std::format(
                "InternalError: Failed to load constant: index {} is out of bounds for ConstantPool.",
                i
            ))
        ;
        return std::move(cp.at(i));
    }

    /**
     * @brief Alloc a Runtime Value in Memory heap
     * @param v value to halloc
     */
    void Memory::halloc(std::shared_ptr<RuntimeValue> v)
    {
        heap.push_back(std::move(v));
    }

    void Memory::store_slot(size_t index, std::shared_ptr<RuntimeValue> v)
    {
        if (index >= slots.size())
        {
            slots.resize(slots.size() + 1);
        }
        slots[index] = std::move(v);
    }

    std::shared_ptr<RuntimeValue> Memory::ld_slot(size_t index)
    {
        if (index > slots.size())
        {
            throw error::Error(std::format(
                "InternalError: Failed to load slot: index {} is out of bounds for Memory -> Slots.",
                index
            ));
        }

        return slots.at(index);
    }
} // namespace brevm

// Copyright (c) 2026 Victor Botelho Anunciação.
// All rights reserved.