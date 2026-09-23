# BreVM

> [!WARNING]
> **BreVM is currently under development.** Features, APIs, instructions, and specifications may undergo significant changes during development.

BreVM is a lightweight virtual machine based on a **hybrid execution model**, following the **[BreVMR 1](https://github.com/ipxzfoxy/brevmr)** specification.

Its architecture combines both **register-based** and **stack-based** execution models within the same runtime. Instructions are separated according to their execution model, allowing operations to be performed using either **registers** or the **operand stack**, with consistent semantics and similar instruction naming.

This hybrid architecture allows bytecode to freely use either model—or combine both—depending on the needs of the program.

BreVM executes **Wave bytecode** with a focus on simplicity, performance, and low runtime overhead. It is designed to be lightweight and easy to embed into C/C++ applications, while also allowing integration with other programming languages.

BreVM is primarily used by the **[ProtoIndigo](https://github.com/ipxzfoxy/protoindigo)** project.
