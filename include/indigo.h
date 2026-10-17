#include <memory>
#include <string>
#include <vector>
#include "src/tokenizer/tokenizer.h"
#include "src/parsing/parser.h"

#include "src/codegen/wave/compiler.h"
#include "depends/brevm/include/vm.h"
#include "depends/brevmr/include/runtime_value.hpp"
#include "depends/brevmr/include/wave.hpp"
#include "operation/w_operation.h"

namespace bre
{
    brevm::WIMG compile(std::string content);
} // namespace bre
