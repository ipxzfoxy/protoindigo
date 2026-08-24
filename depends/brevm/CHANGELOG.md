## 1.1.0

- New register-based architecture.
- Source code refactoring.
- Migration to a dedicated repository and decoupling from the ProtoIndigo ecosystem.
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
WRITE = 0x08,
LDC = 0x09,
MOV = 0x0A,
HALT = 0xFF
```

- Created the BreVM Reference.
- Added external dependencies.
- Tratamento de erros mais especializado. Deixando o uso de exit().

## 1.0.0

- Created BreVM.