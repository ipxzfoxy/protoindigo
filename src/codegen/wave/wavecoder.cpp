#include "wavecoder.h"

namespace wave::internal
{

    void WaveCoder::compile()
    {

    }
    int WaveCoder::compile_literal(Node& node)
    {
        switch (node.getType())
        {
        case NodeType::LiteralString:
        {
            LiteralStringNode n = *dynamic_cast<LiteralStringNode*>(&node);
            output.cp.push_back(std::make_shared<brevm::spec::String>(n.cppcontent));
            return cp_count++;
        }
        case NodeType::LiteralNumber:
        {
            LiteralNumberNode n = *dynamic_cast<LiteralNumberNode*>(&node);
            output.cp.push_back(std::make_shared<brevm::spec::Double>(n.num));
            return cp_count++;
        }
        case NodeType::LiteralBoolean:
        {
            LiteralBoolNode n = *dynamic_cast<LiteralBoolNode*>(&node);
            output.cp.push_back(std::make_shared<brevm::spec::Boolean>(n.condition));
            return cp_count++;
        }
        default:
            break;
        }
    }
    
}