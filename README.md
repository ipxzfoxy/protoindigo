# ProtoIndigo

ProtoIndigo is the compiler and execution engine for the **[Bre](https://github.com/brelang)** programming language.

**Bre** is being designed to provide fine-grained control, safety, flexibility, modularity, and embedding capabilities.

Bre source code is compiled into **Wave** bytecode and executed by the [BreVM](https://github.com/ipxzfoxy/brevm) virtual machine, which is also under development.

Bre features its own syntax and architecture while retaining many fundamental concepts of programming languages.

It is also being designed with modern, developer-friendly embedding capabilities in mind.

# Embedding

## ProtoIndigo C++ API

```cpp
#include <indigo.h>

int main() {
    bre::Operation O;
    O.executeString("new #Number x = 10");
}
```

# Syntax

You can find all code examples **[here](https://github.com/ipxzfoxy/protoindigo/tree/main/tests/scripts)**.

## Installing

### Supported Platforms

ProtoIndigo currently supports the following operating systems:

- Windows
- Ubuntu
- macOS

**[Download ProtoIndigo](https://github.com/ipxzfoxy/protoindigo/releases)**

## Building ProtoIndigo

### Requirements

- C++20-compatible compiler
- CMake
- Ninja (recommended)
- Make (alternative)

Developed and tested with Clang and Ninja.

```bash
git clone https://github.com/ipxzfoxy/protoindigo
cd protoindigo

cmake -B build -G Ninja
cmake --build build
```

### Using the CLI

```bash
./indigo.exe run index.bre
```

Or, if the executable is already available in your system's `PATH`:

```bash
indigo run index.bre
```

The first argument must be the path to the Bre source file you want to execute.

To see all available commands, run:

```bash
indigo help
```

## License

**[ProtoIndigo License](https://github.com/ipxzfoxy/protoindigo/blob/main/LICENSE)**

## Developer

Developed by **Victor Botelho Anunciação** (xFoxyyy0).