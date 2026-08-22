#pragma once

namespace wave::internal {
    enum class NodeType
    {
        Identifier,
        Proto,
        Variable,
        LiteralBoolean,
        LiteralString,
        LiteralNumber,
        AssignmentExpression,
        BinaryExpression,
        Include
    };
    class Node {
    protected:
        NodeType type;
    public:
        NodeType getType() { return type; };
        virtual ~Node() = default;
    protected:
        Node(NodeType t) : type(t) {};
    };
} // namespace wave::internal