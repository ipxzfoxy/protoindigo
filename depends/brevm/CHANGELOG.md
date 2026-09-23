## 0.0.2

Release: [2026-08-26]

- New hybrid architecture based on Registers and an Operand Stack.
- Source code refactoring.
- Migration to a dedicated repository and decoupling from the ProtoIndigo ecosystem.
- New components and improved component separation.
- New directory: `depends/`.
- Reworked opcodes:

### From:
```cpp
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
```

### To:
```cpp
ADD = 0x01,
SUB = 0x02,
MUL = 0x03,
DIV = 0x04,
MOD = 0x05,

WR = 0x06,
LDC = 0x07,
MOV = 0x08,
LDS = 0x09,
STS = 0x0A,

SADD = 0x0B,
SSUB = 0x0C,
SMUL = 0x0D,
SDIV = 0x0E,
SMOD = 0x0F,

SWR = 0x10,
SLDC = 0x11,
SLDS = 0x12,
SSTS = 0x13,

MSR = 0x14,
PSR = 0x15,
MRS = 0x16,

JMP = 0x17,

HALT = 0xFF
```

- Created the BreVM Reference.
- Added external dependencies.
- Tratamento de erros mais especializado. Deixando o uso de exit().

## 0.0.1

- Created BreVM.