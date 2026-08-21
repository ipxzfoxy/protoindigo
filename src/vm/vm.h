/*
* BreVM - ProtoIndigo Virtual Machine
* vm.h
*/

#pragma once
#include <memory>
#include <vector>
#include <variant>
#include <iostream>
#include <string>
#include <cmath>
#include "../shared/opcode.h"

namespace wave::internal {
    using RV = std::variant<std::monostate, double, bool, std::shared_ptr<std::string>>;
    class VM {
        std::vector<RV> stack;         
        std::vector<RV> variables;     
        std::vector<RV> constant_pool; 
        std::vector<double> srb;
        size_t ip;
    public:
        void adv();
        void run();
        RV pop();
        RV add(const RV& arg1, const RV& arg2);
        double sub(const RV& a, const RV& b);
        double mul(const RV& a, const RV& b);
        double div(const RV& a, const RV& b);
        double mod(const RV& a, const RV& b);
        void store(uint8_t index);
        void print();
        void load_const(double index);
        VM(std::vector<double> source, std::vector<RV> cp);
    };
}; // namespace wave::internal

// copyright (c) 2026 Victor Botelho Anunciação