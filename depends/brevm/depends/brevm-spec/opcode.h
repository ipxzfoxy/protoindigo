/*
* BreVM - Opcodes
* opcodes.h
*/
#pragma once

namespace brevm::spec
{
    enum class OPC : uint8_t {
        // ======= arithmetic =======
        ADD = 0x01,
        SUB = 0x02,
        MUL = 0x03,
        DIV = 0x04,
        MOD = 0x05,
        // ======= operands =======
        WRITE = 0x08,
        LDC = 0x09,
        MOV = 0x0A,
        HALT = 0xFF
    };
} // namespace brevm_spec 

// copyright (c) 2026 Victor Botelho Anunciação