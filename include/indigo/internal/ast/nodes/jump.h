// Label Node - label.h

#pragma once
#include <variant>
#include <memory>
#include "node.h"
#include "identifier.h"

namespace bre::internal {
    class JumpNode : public Node {
    public:
        std::unique_ptr<IdentifierNode> target;
        bool declare;
        JumpNode(std::unique_ptr<IdentifierNode> target, bool declare)
            : Node(NodeType::Jump), target(std::move(target)), declare(declare) {};
    };

} // namespace wave::internal

// copyright (c) 2026 Victor Botelho Anunciação