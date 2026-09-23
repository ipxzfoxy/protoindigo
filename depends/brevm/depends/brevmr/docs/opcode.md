# BreVM Opcodes

Target Version: BreVMR 1

This document define all BreVM opcodes.

Each of them have a numeric identifier, operands and a mandatory behavior for all compatibility implementation.

## Registers OPCODES

Opcode: ADD

Value: 0x01

Name: "Add"

Responsability: Somar 2 RuntimeValue em 2 registradores.

Format: `0x01 r0 r1 r2`

---

Opcode: SUB

Value: 0x02

Name: "Subtract"

Responsability: Subtrair 2 RuntimeValue em 2 registradores.

Format: `0x02 r0 r1 r2`

---

Opcode: MUL

Value: 0x03

Name: "Multiply"

Responsability: Multiplicar 2 RuntimeValue em 2 registradores.

Format: `0x03 r0 r1 r2`

---

Opcode: DIV

Value: 0x04

Name: "Divide"

Responsability: Dividir 2 RuntimeValue em 2 registradores.

Format: `0x04 r0 r1 r2`

---

Opcode: MOD

Value: 0x05

Name: "Modulo"

Responsability: Calcula restos de 2 RuntimeValue em 2 registradores.

Format: `0x05 r0 r1 r2`

---

Opcode: WR

Value: 0x06

Name: "Write"

Responsability: Jogar na saída um RuntimeValue de um registrador. Transformando-o em string primeiro.

Format: `0x06 r0`

---

Opcode: LDC

Value: 0x07

Name: "Load Const"

Responsability: Carregar um RuntimeValue da constant pool, e alocar em um registrador.

Format: `0x07 index r0`

---

Opcode: MOV

Value: 0x08

Name: "Move"

Responsability: Mover o valor de um registrador para outro. mas sem apagar ou liberar o primeiro registrador.

Format: `0x08 r0 r1`

---

Opcode: LDS

Value: 0x09

Name: "Load Slot"

Responsability: Carregar um RuntimeValue de um slot, e alocar em um registrador.

Format: `0x09 index r0`

---

Opcode: STS

Value: 0x0A

Name: "Store Slot"

Responsability: Armazena um RuntimeValue em um slot, a partir de um registrador.

Format: `0x0A index r0`

## Operand Stack (OS) OPCODES

Opcode: SADD

Value: 0x0B

Name: "Stack Add"

Responsability: Somar os 2 últimos RuntimeValue da Operand Stack e colocar o resultado na Operand Stack.

Format: `0x0B`

---

Opcode: SSUB

Value: 0x0C

Name: "Stack Subtract"

Responsability: Subtrair os 2 últimos RuntimeValue da Operand Stack e colocar o resultado na Operand Stack.

Format: `0x0C`

---

Opcode: SMUL

Value: 0x0D

Name: "Stack Multiply"

Responsability: Multiplicar os 2 últimos RuntimeValue da Operand Stack e colocar o resultado na Operand Stack.

Format: `0x0D`

---

Opcode: SDIV

Value: 0x0E

Name: "Stack Divide"

Responsability: Dividir os 2 últimos RuntimeValue da Operand Stack e colocar o resultado na Operand Stack.

Format: `0x0E`

---

Opcode: SMOD

Value: 0x0F

Name: "Stack Modulo"

Responsability: Calcula o resto dos 2 últimos RuntimeValue da Operand Stack e coloca o resultado na Operand Stack.

Format: `0x0F`

---

Opcode: SWR

Value: 0x10

Name: "Stack Write"

Responsability: Jogar na saída o último RuntimeValue da Operand Stack, removendo-o da stack. Transformando-o em string primeiro.

Format: `0x10`

---

Opcode: SLDC

Value: 0x11

Name: "Stack Load Const"

Responsability: Carregar um RuntimeValue da constant pool e colocar na Operand Stack.

Format: `0x11 index`

---

Opcode: SLDS

Value: 0x12

Name: "Stack Load Slot"

Responsability: Carregar um RuntimeValue de um slot e colocar na Operand Stack.

Format: `0x12 index`

---

Opcode: SSTS

Value: 0x13

Name: "Stack Store Slot"

Responsability: Armazena o último RuntimeValue da Operand Stack em um slot.

Format: `0x13 index`

## Bridge OPCODES

Opcode: MSR

Value: 0x14

Name: "Move Stack Register"

Responsability: Mover o último RuntimeValue da Operand Stack para um registrador, sem remover o valor da Operand Stack.

Format: `0x14 r0`

---

Opcode: PSR

Value: 0x15

Name: "Pop Stack Register"

Responsability: Remover o último RuntimeValue da Operand Stack e mover para um registrador.

Format: `0x15 r0`

---

Opcode: MRS

Value: 0x16

Name: "Move Register Stack"

Responsability: Mover um RuntimeValue de um registrador para a Operand Stack, sem apagar ou liberar o registrador.

Format: `0x16 r0`

## Control Flow OPCODES

Opcode: JMP

Value: 0x17

Name: "Jump"

Responsability: Alterar o fluxo de execução da BreVM, movendo o Instruction Pointer para outro endereço do bytecode.

Format: `0x17 address`

## VM OPCODES

Opcode: HALT

Value: 0xFF

Name: "Halt"

Responsability: Finalizar a execução da BreVM.

Format: `0xFF`

---

Copyright (c) 2026 Victor Botelho Anunciação.
All rights reserved.