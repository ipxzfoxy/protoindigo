/*
* BreVM - Opcodes
* opcodes.h
*/
#pragma once

namespace wave::internal 
{
    enum class OPC : uint8_t {
        PUSH = 0x00,
        ADD = 0x01,
        SUB = 0x02,
        MUL = 0x03,
        DIV = 0x04,
        MOD = 0x05,
        STORE = 0x06,
        LOAD = 0x07,
        PRINT = 0x08,
        LOAD_CONST = 0x09,
        POP = 0x0A,
        HALT = 0xFF
    };
} // namespace wave::internal 

// copyright (c) 2026 Victor Botelho Anunciação