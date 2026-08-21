# ProtoIndigo 2.0.1

This release focuses directly on improvements, bug fixes, and optimizations, providing a better overall experience.

- REPL bug fixed: In the previous version, instructions entered in the REPL would always end with a syntax error.
- VM and data flow optimizations.
- New runtime structure: ProtoIndigo now uses its own directory structure containing files and resources required for full execution, no longer relying exclusively on the `indigo` executable.
- Implementations using `.bre` files: Parts of ProtoIndigo, such as the `help` CLI command, are now implemented using Bre code.

2.0.1: 2026-08-21

# ProtoIndigo 2.0.0

Welcome to ProtoIndigo 2! ProtoIndigo is now getting closer to becoming a usable programming language. Now, you can perform mathematical operations, variable reassignments, and take advantage of the maximum performance of the new BreVM virtual machine.

Check out what's new:

- Added Virtual Machine (BreVM)
- Added Bytecode Compilation
- Removed the classic interpreter
- Added new expression Nodes
- Added variable reassignment
- Added Mathematical Expressions
- Removed the requirement of using `;` at the end of every line
- Added a new syntax for creating constants: `now a = 10`, which does not replace `new const a = 10`, but provides a less verbose alternative
- Added new keyword `now`
- Added new string delimiters: `"HelloWorld!"`, `` `HelloWorld!` ``, `'HelloWorld!'`
- Reorganized internal structure
- Redesigned Tokenizer
- Redesigned Parser
- Added new internal utilities for development
- Added CLI command: `indigo compile <file>`
- Added CLI command: `indigo platform`
- Added CLI command: `indigo --tokenize <file>`
- Added CLI command: `indigo --parse <file>`
- Unexpected tokens are now prohibited
- Added new Nodes and expressions
- Added Runtime Operation - A class responsible for managing all interpreter components
- Several internal optimizations to improve execution speed
- Initial Embedding - ProtoIndigo is beginning to become embeddable into C++ applications
- Exclusive build tool for the interpreter currently under development
- Automatic `.bre` file detection, allowing execution without specifying the extension. Example: `indigo run tests/scripts/noextension` executes `noextension.bre`.

2.0.0 - 2026/07/28

# ProtoIndigo 1.0.1

ProtoIndigo 1.0.1 is here! New CLI commands have been added, along with a new way to execute files, preparing the interpreter for its next phase. CMake support has also been added for building the interpreter, along with an internal cleanup that removed unnecessary files.

- Added CLI command: `indigo run <file>`
- Added REPL using `indigo`
- Added CLI command: `indigo help`
- Added CLI command: `indigo -v`
- Added CMake support to build the interpreter
- Removed unnecessary files
- Reorganized releases, making interpreter files available correctly
- ProtoIndigo is now available for Windows, Linux, and macOS.

# ProtoIndigo 1.0.0

Welcome to ProtoIndigo 1.0.0! Initial version released on 2026/07/06.

- Added the ProtoIndigo interpreter.
- Added the `proto` instruction to display values in the output.
- Added type support and a new type syntax.
- Added constants.

## ProtoIndigo 0.0.4

- Added function parsing.

## ProtoIndigo 0.0.3

Internal development milestones before the first public release.

## ProtoIndigo 0.0.2

- Added function parsing.

## ProtoIndigo 0.0.1

- Added variable parsing.
- Defined the language syntax.
- Added parsing for strings, numbers, and booleans.