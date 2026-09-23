/**
 * Implements of BreVM loop (vm.h)
 * loop.cpp
 */

#include "include/vm.h"

namespace brevm
{
    // Executes a bytecode vector
    int VM::execute()
    {
        while (ip < bytecode.size())
        {
            switch (static_cast<OPC>(current))
            {
                case OPC::LDC:
                {
                    const std::shared_ptr<RuntimeValue> constant = memory.getConstant(adv());
                    registers[adv()] = constant;
                    adv();
                    break;
                }
                case OPC::ADD:
                {
                    const reg arg1 = registers[adv()];
                    const reg arg2 = registers[adv()];
                    const std::shared_ptr<RuntimeValue> res = add(arg1, arg2);
                    registers[adv()] = std::move(res);
                    adv();
                    break;
                }
                case OPC::SUB:
                {
                    const reg arg1 = registers[adv()];
                    const reg arg2 = registers[adv()];
                    const std::shared_ptr<RuntimeValue> res = sub(arg1, arg2);
                    registers[adv()] = std::move(res);
                    adv();
                    break;
                }
                case OPC::MUL:
                {
                    const reg arg2 = registers[adv()];
                    const reg arg1 = registers[adv()];                    
                    const std::shared_ptr<RuntimeValue> res = mul(arg1, arg2);
                    registers[adv()] = std::move(res);
                    adv();
                    break;
                }
                case OPC::DIV:
                {
                    const reg arg2 = registers[adv()];
                    const reg arg1 = registers[adv()];                   
                    const std::shared_ptr<RuntimeValue> res = div(arg1, arg2);
                    registers[adv()] = std::move(res);
                    adv();
                    break;
                }
                case OPC::MOD:
                {
                    const reg arg2 = registers[adv()];
                    const reg arg1 = registers[adv()];                   
                    const std::shared_ptr<RuntimeValue> res = mod(arg1, arg2);
                    registers[adv()] = std::move(res);
                    adv();
                    break;
                }
                case OPC::WR:
                {
                    std::shared_ptr<RuntimeValue> reg = registers[adv()];
                    std::cout << reg.get()->toString() << "\n";
                    adv();
                    break;
                }
                case OPC::MOV:
                {
                    std::shared_ptr<RuntimeValue> arg = registers[adv()];
                    registers[adv()] = arg;
                    adv();
                    break;
                }
                case OPC::SADD:
                {
                    const std::shared_ptr<RuntimeValue> arg2 = spop();
                    const std::shared_ptr<RuntimeValue> arg1 = spop();
                    const std::shared_ptr<RuntimeValue> res = add(arg1, arg2);
                    stack.push_back(res);
                    adv();
                    break;
                }
                case OPC::SSUB:
                {
                    const std::shared_ptr<RuntimeValue> arg2 = spop();
                    const std::shared_ptr<RuntimeValue> arg1 = spop();
                    const std::shared_ptr<RuntimeValue> res = sub(arg1, arg2);
                    stack.push_back(res);
                    adv();
                    break;
                }
                case OPC::SMUL:
                {
                    const std::shared_ptr<RuntimeValue> arg2 = spop();
                    const std::shared_ptr<RuntimeValue> arg1 = spop();
                    const std::shared_ptr<RuntimeValue> res = mul(arg1, arg2);
                    stack.push_back(res);
                    adv();
                    break;
                }
                case OPC::SDIV:
                {
                    const std::shared_ptr<RuntimeValue> arg2 = spop();
                    const std::shared_ptr<RuntimeValue> arg1 = spop();
                    const std::shared_ptr<RuntimeValue> res = div(arg1, arg2);
                    stack.push_back(res);
                    adv();
                    break;
                }
                case OPC::SMOD:
                {
                    const std::shared_ptr<RuntimeValue> arg2 = spop();
                    const std::shared_ptr<RuntimeValue> arg1 = spop();
                    const std::shared_ptr<RuntimeValue> res = mod(arg1, arg2);
                    stack.push_back(res);
                    adv();
                    break;
                }
                case OPC::SWR:
                {
                    std::shared_ptr<RuntimeValue> v = spop();
                    std::cout << v.get()->toString() << "\n";
                    adv();
                    break;
                }
                case OPC::SLDC:
                {
                    stack.push_back(memory.getConstant(adv()));
                    adv();
                    break;
                }
                case OPC::JMP:
                {
                    ip = adv();
                    current = bytecode[ip];
                    break;;
                }
                case OPC::LDS:
                {
                    std::shared_ptr<RuntimeValue> slot = memory.ld_slot(adv());
                    registers[adv()] = std::move(slot);
                    adv();
                    break;
                }
                case OPC::STS:
                {
                    size_t i = adv();
                    memory.store_slot(i, registers[adv()]);
                    adv();
                    break;
                }
                case OPC::SLDS:
                {
                    stack.push_back(memory.ld_slot(adv()));
                    adv();
                    break;
                }
                case OPC::SSTS:
                {
                    ip++; current = bytecode[ip];
                    size_t index = current;
                    memory.store_slot(index, spop());
                    ip++; current = bytecode[ip];
                    break;
                }
                case OPC::MSR:
                {
                    ip++; current = bytecode[ip];
                    registers[current] = stack.back();
                    ip++; current = bytecode[ip];
                    break;
                }
                case OPC::PSR:
                {
                    ip++; current = bytecode[ip];
                    registers[current] = spop();
                    ip++; current = bytecode[ip];
                    break;
                }
                case OPC::MRS:
                {
                    ip++; current = bytecode[ip];
                    stack.push_back(registers[current]);
                    ip++; current = bytecode[ip];
                    break;
                }
                case OPC::HALT:
                {   
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

// Copyright (c) 2026 Victor Botelho Anunciação.
// All rights reserved.