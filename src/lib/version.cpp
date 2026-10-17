
#include "std.h"

namespace bre::internal::brestdlib
{
    void installVersion(codegen::WaveCoder& WC)
    {
        std::string v = INDIGO_VERSION;
        std::string bv = BREVM_VERSION;
        WC.eject_symbol("std_version", brevm::String(v), true);
        WC.eject_symbol("std_vm_version", brevm::String(bv), true);
    }
} // namespace bre::internal
