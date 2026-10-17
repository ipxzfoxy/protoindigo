// ProtoIndigo WaveCoder
#define RED     "\033[31m"
#define RESET   "\033[0m"

#include "compiler.h"

namespace bre::internal::codegen {
    // ======================== PUBLIC ========================
    WaveCoder::WaveCoder(std::vector<std::unique_ptr<Node>> nodes)
        : label_table()
    {
        ast = std::move(nodes);
    }

    void WaveCoder::compile()
    {
        for (const auto& unp : ast)
        {
           compile_node(*unp.get());
        }

        if (!(static_cast<brevm::OPC>(output.back()) == brevm::OPC::HALT))
        {
            push(brevm::OPC::HALT);
        }
    }

    // ======================== PRIVATE ========================
    void WaveCoder::push(brevm::OPC opcode)
    {
        output.push_back(static_cast<double>(opcode));
    }

    void WaveCoder::push_const(std::shared_ptr<brevm::RuntimeValue> v)
    {
        constant_pool.push_back(v);
        cp_count++;
    }

    void WaveCoder::store(std::string& identifier, bool isconst)
    {
        push(brevm::OPC::SSTS);
        output.push_back(v_count);
        Symbol s;
        s.isConst = isconst;
        s.varCount = v_count;
        symbol_table[identifier] = s;
        v_count++;
    }

    void WaveCoder::compile_exp(Node& node)
    {
        if (auto n = dynamic_cast<LiteralStringNode*>(&node))
        {
           push_const(std::make_shared<brevm::String>(n->cppcontent));
           push(brevm::OPC::SLDC);
           output.push_back(cp_count - 1);
        }
        if (auto n = dynamic_cast<LiteralNumberNode*>(&node))
        {
            push_const(std::make_shared<brevm::Integer>(n->num));
            push(brevm::OPC::SLDC);
            output.push_back(cp_count - 1);
        }
        if (auto n = dynamic_cast<LiteralBoolNode*>(&node))
        {
            push_const(std::make_shared<brevm::Boolean>(n->condition));
            push(brevm::OPC::SLDC);
            output.push_back(cp_count - 1);
        }
    }
    void WaveCoder::compile_binexp(Node& node)
    {
        BinaryExpressionNode* binexp = static_cast<BinaryExpressionNode*>(&node);

        compile_node(*binexp->left_arg);
        compile_node(*binexp->right_arg);
        
        

        switch (binexp->op)
        {
        case BinaryOperation::ADD:
            push(brevm::OPC::SADD);
            break;
        case BinaryOperation::SUB:
            push(brevm::OPC::SSUB);
            break;
        case BinaryOperation::DIV:
            push(brevm::OPC::SDIV);
            break;
        case BinaryOperation::MUL:
            push(brevm::OPC::SMUL);
            break;
        default:
            break;
        }
    }
    void WaveCoder::compile_node(Node& node)
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
            store(n.id, n.is_const);
            break;
        }
        case NodeType::Proto:
        {
            ProtoNode& n = *static_cast<ProtoNode*>(&node);
            compile_node(*n.value);
            push(brevm::OPC::SWR);
            break;
        }
        case NodeType::Jump:
        {
            JumpNode& n = *static_cast<JumpNode*>(&node);
            if (n.declare)
                label_table.set(n.target.get()->value, output.size());
            if (!n.declare)
            {
                push(brevm::OPC::JMP);
                output.push_back(label_table.exists(n.target.get()->value));
            }

            break;
        }
        case NodeType::Identifier:
        { 
            IdentifierNode& n = *static_cast<IdentifierNode*>(&node);
            isdef(n.value);
            push(brevm::OPC::SLDS);
            output.push_back(symbol_table[n.value].varCount);
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
            isdef(n.targetVariable);
            compile_node(*n.value);
            auto it = symbol_table.find(n.targetVariable);
            if (it->second.isConst)
            {
                std::cout << RED << "TypeError: Cannot assign to constant '"
                    << n.targetVariable
                    << "'." << RESET;
            }
            store(n.targetVariable, false);
            break;
        }
        default:
        {
            std::cout << "Warning: Unexpected or unknown node.\n";
            
        }
        }
    }

    void WaveCoder::isdef(std::string& identifier)
    {
        auto it = symbol_table.find(identifier);
            if (it == symbol_table.end())
            {
                std::cerr
                    << RED
                    << "ReferenceError: "
                    << "\""
                    << identifier
                    << "\""
                    << " is not defined.\n"
                    << RESET;
                exit(0);
            };
    }
    // Ejeta um símbolo na constantPool, e no bytecode. garantindo que o valor será alocado em um slot.
    void WaveCoder::eject_symbol(const std::string& symbol, const brevm::RuntimeValue& value, bool isConst)
    {
        Symbol s;
        s.isConst = isConst;

        push_const(std::move(value.clone()));
        push(brevm::OPC::SLDC);
        output.push_back(cp_count - 1);
        push(brevm::OPC::SSTS);
        output.push_back(v_count);
        s.varCount = v_count;
        v_count++;
        symbol_table[symbol] = s;


    }

} // namespace wave::internal

// copyright (c) 2026 Victor Botelho Anunciação