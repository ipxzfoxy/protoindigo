/**
 * Implements of BreVM loop (vm.h)
 * loop.cpp
 */

#include "include/vm.h"
#include "depends/brevm-spec/opcode.h"

namespace brevm
{
    // Executes a bytecode vector
    int VM::execute(spec::bytecodePool bc)
    {
        using namespace spec;

        size_t ip = 0;
        

        while (ip < bc.size())
        {
            uint8_t current = bc[ip];
            switch (static_cast<spec::OPC>(current))
            {
                
                case OPC::LDC:
                {
                    std::cout << "LoadConst\n";
                    ip++; current = bc[ip];
                    const std::shared_ptr<RuntimeValue> constant = memory.getConstant(current);
                    ip++; current = bc[ip];
                    registers[current] = constant;
                    ip++;
                    break;
                }
                case OPC::ADD:
                {
                    std::cout << "Add\n";
                    ip++; current = bc[ip];
                    const spec::reg arg1 = registers[current];
                    ip++; current = bc[ip];
                    const spec::reg arg2 = registers[current];
                    ip++; current = bc[ip];
                    const std::shared_ptr<spec::RuntimeValue> res = add(arg1, arg2);
                    registers[current] = std::move(res);
                    ip++;
                    break;
                }
                case OPC::SUB:
                {
                    std::cout << "Sub\n";
                    ip++; current = bc[ip];
                    const spec::reg arg1 = registers[current];
                    ip++; current = bc[ip];
                    const spec::reg arg2 = registers[current];
                    ip++; current = bc[ip];
                    const std::shared_ptr<spec::RuntimeValue> res = sub(arg1, arg2);
                    registers[current] = std::move(res);
                    ip++;
                    break;
                }
                case OPC::MUL:
                {
                    std::cout << "Mul\n";
                    ip++; current = bc[ip];
                    const spec::reg arg1 = registers[current];
                    ip++; current = bc[ip];
                    const spec::reg arg2 = registers[current];
                    ip++; current = bc[ip];
                    const std::shared_ptr<spec::RuntimeValue> res = mul(arg1, arg2);
                    registers[current] = std::move(res);
                    ip++;
                    break;
                }
                case OPC::DIV:
                {
                    std::cout << "Div\n";
                    ip++; current = bc[ip];
                    const spec::reg arg1 = registers[current];
                    ip++; current = bc[ip];
                    const spec::reg arg2 = registers[current];
                    ip++; current = bc[ip];
                    const std::shared_ptr<spec::RuntimeValue> res = div(arg1, arg2);
                    registers[current] = std::move(res);
                    ip++;
                    break;
                }
                case OPC::MOD:
                {
                    std::cout << "Mod\n";
                    ip++; current = bc[ip];
                    const spec::reg arg1 = registers[current];
                    ip++; current = bc[ip];
                    const spec::reg arg2 = registers[current];
                    ip++; current = bc[ip];
                    const std::shared_ptr<spec::RuntimeValue> res = mod(arg1, arg2);
                    registers[current] = std::move(res);
                    ip++;
                    break;
                }
                case OPC::WRITE:
                {
                    std::cout << "Write\n";
                    ip++; current = bc[ip];
                    std::shared_ptr<RuntimeValue> reg = registers[current];

                    std::cout << reg.get()->toString() << std::endl;
                    ip++;
                    break;
                }
                case OPC::MOV:
                {
                    std::cout << "Mov\n";
                    ip++; current = bc[ip];
                    std::shared_ptr<RuntimeValue> arg = registers[current];
                    ip++; current = bc[ip];
                    registers[current] = arg;
                    ip++;
                    break;
                }
                case OPC::HALT:
                {
                    std::cout << "Halt\n";
                    return 0;
                }
                default:
                {
                    throw error::Error(std::format(
                        "InvalidOpcode: Unknown opcode {} at bytecode offset 0",
                        current
                    ));
                }
            }
        }

        return 0;
    }
} // namespace brevm
