#include "include/vm.h"
#include <vector>
#include <memory>

using namespace brevm;

constantPool cp({
    std::make_shared<Integer>(10),
    std::make_shared<Integer>(5),
    std::make_shared<Integer>(3),
    std::make_shared<Integer>(20),
    std::make_shared<String>("Hello,"),
    std::make_shared<String>(" World!"),
    std::make_shared<String>(" - This is BreVM 0.0.2, Stack and Register based!")
});

bytecodePool bp({
    0x07, 0, 2,
    0x07, 1, 1,
    0x01, 1, 2, 0,
    0x06, 0,
    0x11, 2,
    0x16, 0,
    0x0B,
    0x10,
    0x07, 4, 2,
    0x16, 2,
    0x11, 5,
    0x0B,
    0x15, 0,
    0x06, 0,
    0x0A, 0, 0,
    0x12, 0,
    0x11, 6,
    0x0B,
    0x10,
    0x17, 0,
    0xFF
});

int main()
{
    try
    {
        VM vm(cp, bp);
        vm.execute();
        return 0;
    } catch (const error::Error& e)
    {
        std::cerr << e.what() << "\n";
        return 1;
    }
}

// Copyright (c) 2026 Victor Botelho Anunciação.
// All rights reserved.