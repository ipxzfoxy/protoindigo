#include "parser.h"

namespace wave::internal
{
    // Para keywords e statements que dependem de contexto.
    std::unique_ptr<Node> Parser::ctx_statement()
    {
        if (std::holds_alternative<std::string>(current().getValue())) {
            if (std::get<std::string>(current().getValue()) == "label")
                return std::move(label());
        }
    }
} // namespace wave::internal
// copyright (c) 2026 Victor Botelho Anunciação