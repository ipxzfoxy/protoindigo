
#include "std.h"

namespace bre::internal::brestdlib
{
    void installArgs(codegen::WaveCoder& WC, std::vector<std::string>& args)
    {
        for (int i = 0; i < args.size(); i++)
        {
            WC.eject_symbol(std::format("std_argv{}", i), brevm::String(args[i]), true);
        }
    }
} // namespace bre::internal
