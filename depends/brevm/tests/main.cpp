#include "include/vm.h"
#include <vector>
#include <memory>

using namespace brevm;
using namespace spec;

constantPool cp({
    std::make_shared<Integer>(10),
    std::make_shared<Integer>(5),
    std::make_shared<Integer>(100),
});

bytecodePool bp({
    // 10 + 5 = 15
    0x09, 0, 3,     // LDC cp[0] -> reg3 = 10
    0x09, 1, 2,     // LDC cp[1] -> reg2 = 5
    0x01, 3, 2, 1,  // ADD reg3, reg2 -> reg1
    0x08, 1,        // WRITE reg1

    // 15 - 10 = 5
    0x09, 0, 3,     // LDC cp[0] -> reg3 = 10
    0x02, 1, 3, 1,  // SUB reg1, reg3 -> reg1
    0x08, 1,        // WRITE reg1

    // 100 * 5 = 500
    0x09, 2, 3,     // LDC cp[2] -> reg3 = 100
    0x03, 3, 1, 1,  // MUL reg3, reg1 -> reg1
    0x08, 1,        // WRITE reg1

    // 500 / 10 = 50
    0x09, 0, 3,     // LDC cp[0] -> reg3 = 10
    0x04, 1, 3, 1,  // DIV reg1, reg3 -> reg1
    0x08, 1,        // WRITE reg1

    // 50 % 5 = 0
    0x09, 1, 3,     // LDC cp[1] -> reg3 = 5
    0x05, 1, 3, 1,  // MOD reg1, reg3 -> reg1
    0x08, 1,        // WRITE reg1

    0xFF             // HALT
});

int main()
{
    VM vm(cp);
    vm.execute(bp);
}