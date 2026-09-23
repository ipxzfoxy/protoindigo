/*
* BreVM - Opcodes
* opcodes.h
*/
#pragma once

namespace brevm
{
    enum class OPC : uint8_t {
        // ======= Registers, Arithmetic =======
        ADD = 0x01,
        SUB = 0x02,
        MUL = 0x03,
        DIV = 0x04,
        MOD = 0x05,

        // ======= Registers, Operands =======
        WR  = 0x06,
        LDC = 0x07,
        MOV = 0x08,
        LDS = 0x09, // Load Slot: index, reg
        STS = 0x0A, // Store Slot: index, reg

        // ======= Operand Stack, Arithmetic =======
        SADD = 0x0B,
        SSUB = 0x0C,
        SMUL = 0x0D,
        SDIV = 0x0E,
        SMOD = 0x0F,

        // ======= Operand Stack, Operands =======
        SWR  = 0x10,
        SLDC = 0x11,
        SLDS = 0x12, // Stack Load Slot: index
        SSTS = 0x13, // Stack Store Slot: index

        // ======= Bridge =======
        MSR = 0x14, // Move Stack -> Register
        PSR = 0x15, // Pop Stack -> Register
        MRS = 0x16, // Move Register -> Stack

        // ======= Control Flow =======
        JMP  = 0x17,

        // ======= VM =======
        HALT = 0xFF
    };
} // namespace brevm

// Copyright (c) 2026 Victor Botelho Anunciação.
// All rights reserved.