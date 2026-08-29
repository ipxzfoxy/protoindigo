ProtoIndigo Interpreter

<div align="center">"C++20" (https://img.shields.io/badge/C%2B%2B-20-blue.svg)
"Platform" (https://img.shields.io/badge/platform-Windows%20%7C%20macOS%20%7C%20Linux%20%7C%20Wasm-lightgrey)

</div>

ProtoIndigo is a programming language compiled into bytecode and executed by its own virtual machine, BreVM.

Designed for executing programs with the ".bre" extension, the language uses an architecture based on modern interpretation models, featuring its own bytecode format and a dedicated runtime for its execution.

The language has a lightweight and declarative syntax, maintaining familiarity with modern programming language concepts while preserving its own identity. Currently, it supports mathematical operations, variable declaration and reassignment, and data output.

It is also possible to integrate ProtoIndigo into C++ applications through the embedding API currently under development.

See a .bre program!

now name = "xFoxyyy0"
new age = 90

age = 20 + age

proto name
proto age

This is an incomplete example. You can see the complete syntax "here." (https://github.com/ipxzfoxy/protoindigo/tree/main/tests/scripts)

Installing

"Install ProtoIndigo on your machine!" (https://github.com/ipxzfoxy/protoindigo/releases)

«Pre-compiled files are available for Windows, macOS, Ubuntu and WebAssembly.»

Embedding

Use the C++ API to create and control Operations:

#include "operation/w_operation.h"

int main(int argc, char* argv[])
{
    std::string code = wave::readBreFile(argv[2]);
    wave::Operation OP = wave::create_operation();
    OP.executeString(code);
    return 0;
}

Building ProtoIndigo

Requirements

- C++20
- CMake
- Ninja (recommended)
- Make (alternative)

Developed and tested using Clang + Ninja.

git clone https://github.com/ipxzfoxy/protoindigo
cd protoindigo

cmake -B build -G Ninja
cmake --build build

Using the CLI

./indigo.exe run index.bre

or if it has already been added to your PATH:

indigo run index.bre

* The first argument must be the path to the file you want to interpret.

See all available commands:

indigo help

LICENSE

"PROTOINDIGO LICENSE" (https://github.com/ipxzfoxy/protoindigo/blob/main/LICENSE)

Developer

Developed by Victor Botelho Anunciação (xFoxyyy0).