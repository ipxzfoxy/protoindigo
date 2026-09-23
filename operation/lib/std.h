#include <string>
#include <format>

#include "src/codegen/wave/compiler.h"

namespace wave::internal::brestdlib
{
    void installArgs(codegen::WaveCoder& WC, int argc, char* argv[]);
    void installVersion(codegen::WaveCoder& WC);
} // namespace wave::internal
