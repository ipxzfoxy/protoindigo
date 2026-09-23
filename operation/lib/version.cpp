
#include "std.h"

namespace wave::internal
{
    void installVersion(codegen::WaveCoder& WC)
    {
        std::string v = INDIGO_VERSION;
        std::string bv = "nodisp";
        WC.eject_symbol("std_version", brevm::String(v), true);
        WC.eject_symbol("std_vm_version", brevm::String(bv), true);
    }
} // namespace wave::internal
