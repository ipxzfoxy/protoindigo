/*
* BreVM - ProtoIndigo Virtual Machine
* vm.cpp
*/

#include "vm.h"

wave::internal::VM::VM(std::vector<double> bytecode, std::vector<RV> cp)
{
    constant_pool = cp;
    srb = bytecode;
    ip = 0; 
}
 
void wave::internal::VM::adv()
{
    ip++;
}

wave::internal::RV wave::internal::VM::pop()
{
    const RV v = stack.back();
    stack.pop_back();
    return v;
}

wave::internal::RV wave::internal::VM::add(const RV& a, const RV& b)
{
    if (std::holds_alternative<double>(a) && std::holds_alternative<double>(b))
    {
        return std::get<double>(a) + std::get<double>(b);
    }

    if (std::holds_alternative<std::shared_ptr<std::string>>(a) && std::holds_alternative<std::shared_ptr<std::string>>(b))
    {
        return std::make_shared<std::string>(*std::get<std::shared_ptr<std::string>>(a) + *std::get<std::shared_ptr<std::string>>(b));
    }

    if (std::holds_alternative<double>(a) && std::holds_alternative<std::shared_ptr<std::string>>(b))
    {
        return std::make_shared<std::string>(std::to_string(std::get<double>(a)) + *std::get<std::shared_ptr<std::string>>(b));
    }

    std::cerr << "RuntimeError: Cannot apply '+' to operands of the given types." << std::endl;
    exit(1);
    
}

double wave::internal::VM::sub(const RV& a, const RV& b)
{
    if (std::holds_alternative<double>(a) && std::holds_alternative<double>(b))
    {
        return std::get<double>(a) - std::get<double>(b);
    }

    std::cerr << "RuntimeError: Cannot apply '-' to operands of the given types." << std::endl;
    exit(1);
}

double wave::internal::VM::mul(const RV& a, const RV& b)
{
    if (std::holds_alternative<double>(a) && std::holds_alternative<double>(b))
    {
        return std::get<double>(a) * std::get<double>(b);
    }

    std::cerr << "RuntimeError: Cannot apply '*' to operands of the given types." << std::endl;
    exit(1);
}

double wave::internal::VM::div(const RV& a, const RV& b)
{
    if (std::holds_alternative<double>(a) && std::holds_alternative<double>(b))
    {
        return std::get<double>(a) / std::get<double>(b);
    }

    std::cerr << "RuntimeError: Cannot apply '/' to operands of the given types." << std::endl;
    exit(1);
}

double wave::internal::VM::mod(const RV& a, const RV& b)
{
    if (std::holds_alternative<double>(a) && std::holds_alternative<double>(b))
    {
        return std::fmod(std::get<double>(a), std::get<double>(b));
    }

    std::cerr << "RuntimeError: Cannot apply '%' to operands of the given types." << std::endl;
    exit(1);
}

void wave::internal::VM::store(uint8_t index)
{
    const RV arg = pop();
    if (index >= variables.size()) {
        variables.resize(index + 1);
    }
    variables[index] = arg;
    adv();
}

void wave::internal::VM::print()
{
    RV arg = pop();
    if (std::holds_alternative<std::shared_ptr<std::string>>(arg)) {
        std::cout << *std::get<std::shared_ptr<std::string>>(arg) << std::endl;
        return;
    }
    if (std::holds_alternative<double>(arg)) {
        std::cout << std::get<double>(arg) << std::endl;
        return;
    }
    if (std::holds_alternative<bool>(arg)) {
        std::cout << std::boolalpha << std::get<bool>(arg) << std::endl;
        return;
    }
}

void wave::internal::VM::load_const(double index)
{
    if (index > constant_pool.size())
    {
        std::cout << "Runtime Error: Constant pool access failed. The provided index does not reference an existing constant." << std::endl;
        exit(1);
    }

    stack.push_back(constant_pool.at(index));
    adv();
}

void wave::internal::VM::run()
{
    while (ip < srb.size())
    {
        uint8_t c = srb[ip];
        adv();

        switch (static_cast<OPC>(c))
        {
            case OPC::PUSH:
            {
                stack.push_back(srb[ip]);
                adv();
                break;
            }

            case OPC::ADD:
            {
                const RV arg2 = pop();
                const RV arg1 = pop();

                const RV result = add(arg1, arg2);
                stack.push_back(result);
                break;
            }

            case OPC::SUB:
            {
                const RV arg2 = pop();
                const RV arg1 = pop();

                const double result = sub(arg1, arg2);
                stack.push_back(result);
                break;
            }
            case OPC::MUL:
            {
                const RV arg2 = pop();
                const RV arg1 = pop();

                const double result = mul(arg1, arg2);
                stack.push_back(result);
                break;
            }
            case OPC::DIV:
            {
                const RV arg2 = pop();
                const RV arg1 = pop();

                const double result = div(arg1, arg2);
                stack.push_back(result);
                break;
            }
            case OPC::MOD:
            {
                const RV arg2 = pop();
                const RV arg1 = pop();

                const double result = mod(arg1, arg2);
                stack.push_back(result);
                break;
            }
            case OPC::STORE:
            {
                store(srb[ip]);
                break;
            }
            case OPC::LOAD:
            {
                stack.push_back(variables[srb[ip]]);
                adv();
                break;
            }
            case OPC::PRINT:
            {
                print();
                break;
            }
            case OPC::LOAD_CONST:
            {
                load_const(srb[ip]);
                break;
            }
            case OPC::POP:
            {
                pop();
            }
            case OPC::HALT:
            {
                exit(0);
                break;
            }
        }
    }
} // namespace wave::internal

// copyright (c) 2026 Victor Botelho Anunciação