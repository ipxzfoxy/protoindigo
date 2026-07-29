#pragma once
#include <memory>
#include <string>
#include <utility>
#include "node.h"

namespace wave::internal {
    class VariableNode : public Node {
    public:
        bool is_const;
        std::string typing;
        std::string id;
        std::unique_ptr<Node> value;

        VariableNode(
            bool isConst,
            std::string typing,
            std::string id,
            std::unique_ptr<Node> value
        ) :
            Node(NodeType::Variable),
            is_const(isConst),
            typing(std::move(typing)),
            id(std::move(id)),
            value(std::move(value)) {}
    };

} // namespace wave::internal

// (c) 2026 Victor Botelho Anunciação