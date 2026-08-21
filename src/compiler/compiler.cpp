// ProtoIndigo Compiler

#include "compiler.h"

namespace wave::internal {
    // ======================== PUBLIC ========================
    Compiler::Compiler(std::vector<std::unique_ptr<Node>> nodes)
    {
        ast = std::move(nodes);
    }

    void Compiler::compile()
    {
        for (const auto& unp : ast)
        {
           compile_node(*unp.get());
        }
    }

    // ======================== PRIVATE ========================
    void Compiler::push(OPC opcode)
    {
        output.push_back(static_cast<double>(opcode));
    }

    void Compiler::push_const(runtime_value v)
    {
        constant_pool.push_back(v);
        cp_count++;
    }

    void Compiler::store(std::string& identifier)
    {
        push(OPC::STORE);
        output.push_back(v_count);
        symbol_table[identifier] = v_count;
        v_count++;
    }

    void Compiler::compile_exp(Node& node)
    {
        if (auto n = dynamic_cast<LiteralStringNode*>(&node))
        {
           push_const(std::make_shared<std::string>(n->cppcontent));
           push(OPC::LOAD_CONST);
           output.push_back(cp_count - 1);
        }
        if (auto n = dynamic_cast<LiteralNumberNode*>(&node))
        {
            push_const(n->num);
            push(OPC::LOAD_CONST);
            output.push_back(cp_count - 1);
        }
        if (auto n = dynamic_cast<LiteralBoolNode*>(&node))
        {
            push_const(n->condition);
            push(OPC::LOAD_CONST);
            output.push_back(cp_count - 1);
        }
    }
    void Compiler::compile_binexp(Node& node)
    {
        BinaryExpressionNode* binexp = static_cast<BinaryExpressionNode*>(&node);

        compile_node(*binexp->left_arg);
        compile_node(*binexp->right_arg);

        switch (binexp->op)
        {
        case BinaryOperation::ADD:
            push(OPC::ADD);
            break;
        case BinaryOperation::SUB:
            push(OPC::SUB);
            break;
        case BinaryOperation::DIV:
            push(OPC::DIV);
            break;
        case BinaryOperation::MUL:
            push(OPC::MUL);
            break;
        default:
            break;
        }
    }
    void Compiler::compile_node(Node& node)
    {
        switch (node.getType())
        {
        case NodeType::BinaryExpression:
        {
            compile_binexp(node);
            break;
        }
        case NodeType::Variable:
        {
            VariableNode& n = *static_cast<VariableNode*>(&node);
            compile_node(*n.value);
            store(n.id);
            break;
        }
        case NodeType::Proto:
        {
            ProtoNode& n = *static_cast<ProtoNode*>(&node);
            compile_node(*n.value);
            push(OPC::PRINT);
            break;
        }
        case NodeType::Identifier:
        { 
            IdentifierNode& n = *static_cast<IdentifierNode*>(&node);
            isdefined(n.value);
            push(OPC::LOAD);
            output.push_back(symbol_table[n.value]);
            break;
        }
        case NodeType::LiteralString:
        {
            compile_exp(node);
            break;
        }
        case NodeType::LiteralNumber:
        {
            compile_exp(node);
            break;
        }
        case NodeType::LiteralBoolean:
        {
            compile_exp(node);
            break;
        }
        case NodeType::AssignmentExpression:
        { 
            AssignmentExpressionNode& n = *static_cast<AssignmentExpressionNode*>(&node);
            isdefined(n.targetVariable);
            compile_node(*n.value);
            
            store(n.targetVariable);
            break;
        }
        }
    }

    void Compiler::isdefined(std::string identifier)
    {
        auto it = symbol_table.find(identifier);
            if (it == symbol_table.end())
            {
                std::cerr
                    << "ReferenceError: "
                    << "\""
                    << identifier
                    << "\""
                    << " is not defined.\n";
                exit(0);
            };
    }

} // namespace wave::internal

// copyright (c) 2026 Victor Botelho Anunciação