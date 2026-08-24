// Literal String Node - string.h
#pragma once
#include <vector>
#include <string>
#include "../node.h"

namespace wave::internal {

    enum class Delimiter {
        SingleQuote,
        DoubleQuote,
        Template
    };

    class LiteralStringNode : public Node {
    public:
        Delimiter delimiter;
        std::string cppcontent;

        LiteralStringNode(Delimiter delimiter, std::string cppcontent)
            : Node(NodeType::LiteralString), delimiter(delimiter), cppcontent(cppcontent) {}
    };

} // namespace wave::internal

// copyright (c) 2026 Victor Botelho Anunciação