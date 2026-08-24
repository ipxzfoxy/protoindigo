#include "include/memory.h"

namespace brevm
{
    const std::shared_ptr<spec::RuntimeValue>& Memory::getConstant(size_t i) const {
        if (i > constantPool.size())
            throw error::Error(std::format(
                "InternalError: Failed to load constant: index {} is out of bounds for ConstantPool.",
                i
            ))
        ;
        return std::move(constantPool.at(i));
    }

    void Memory::halloc(std::shared_ptr<spec::RuntimeValue> v)
    {
        heap.push_back(std::move(v));
    }
} // namespace brevm
