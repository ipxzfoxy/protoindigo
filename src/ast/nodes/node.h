#pragma once

namespace wave::internal {
    enum class NodeType
    {
        Identifier,
        Proto,
        Variable,
        Jump,
        LiteralBoolean,
        LiteralString,
        LiteralNumber,
        LiteralArray,
        AssignmentExpression,
        BinaryExpression,
        ScopeExpression,
        ParExpression,
        IndexExpression
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
    using NodeUniquePtr = std::unique_ptr<Node>;
} // namespace wave::internal