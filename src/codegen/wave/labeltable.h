//
// Created by IPXZFOXY on 06/09/2026.
//

#pragma once
#include <string>
#include <unordered_map>

namespace wave::internal::codegen
{
    class LabelTable
    {
        std::unordered_map<std::string, size_t> table;
        public:
            LabelTable() : table() {};
            ~LabelTable() = default;
            size_t exists(std::string& name);
            void set(std::string& name, size_t pos);
    };
}

