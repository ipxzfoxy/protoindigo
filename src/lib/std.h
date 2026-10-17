#include <string>
#include <format>

#include "src/codegen/wave/compiler.h"

namespace bre::internal::brestdlib
{
    void installArgs(codegen::WaveCoder& WC, std::vector<std::string>& args);
    void installVersion(codegen::WaveCoder& WC);
} // namespace bre::internal
