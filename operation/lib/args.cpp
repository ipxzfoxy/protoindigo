
#include "std.h"

namespace wave::internal
{
    void installArgs(codegen::WaveCoder& WC, int argc, char* argv[])
    {
        for (int i = 0; i < argc; i++)
        {
            WC.eject_symbol(std::format("argv{}", i), brevm::String(argv[i]), true);
        }
    }
} // namespace wave::internal
