//
// Created by IPXZFOXY on 06/09/2026.
//

#include "labeltable.h"
#include <iostream>
#include <string>

namespace wave::internal::codegen
{
    size_t LabelTable::exists(std::string& name)
    {
        auto it = table.find(name);

        if (it == table.end()) {
                std::cerr
                    << "ReferenceError: The label "
                    << "\""
                    << name
                    << "\""
                    << " is not defined.\n";
                exit(0);
        };

        return it->second;
    }

    void LabelTable::set(std::string& name, size_t pos)
    {
        auto it = table.find(name);
        if (it != table.end())
        {
            std::cerr
                    << "ReferenceError: The label "
                    << "\""
                    << name
                    << "\""
                    << " is already defined.\n";
            exit(0);
        }

        table[name] = pos;
    }
}
