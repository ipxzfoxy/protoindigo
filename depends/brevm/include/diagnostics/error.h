#pragma once
#include <string>
#include <stdexcept>

namespace brevm::error
{
    class Error : public std::runtime_error
    {
    public:
        explicit Error(const std::string& message)
        : std::runtime_error(message) {}
    };
} // namespace brevm::errors
