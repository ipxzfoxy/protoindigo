# 2.1.0-beta
**2026-10-17**

> ⚠️ **Beta Release:** Unstable and incomplete build for testing.

This update focuses entirely on innovation, restructuring, and adaptation. **BreVM is now an independent project.**

ProtoIndigo continues to use BreVM's stack-based architecture, despite the hybrid architecture that also incorporates registers.

This update introduces several **new features**, including support for **mathematical expressions**. It also brings minor **optimizations**, **error standardization**, and new **toolchains** to ensure the best possible experience.

Enjoy the ProtoIndigo embedding releases! We are happy to announce the first prototype of the ProtoIndigo Standard Library.

**Have a great October! 🎃**

*(No functions for now...)*

**## Fix**

- Fixed a CLI bug that caused `help.bre` to be searched for in an incorrect directory instead of the installation directory relative to the executable's location.
- Added and fixed support for resolving the scripts directory across the following platforms: **Windows, Ubuntu, and macOS**.

## Changed

### C++ API

- Replaced the `indigo` namespace with `bre`.
- Added a new method for file input: `Operation::inputFile()`.
- Introduced a new standard for creating `Operation` instances and using the API.

> ProtoIndigo is now compiled as a library, while the CLI continues to be compiled as an executable.

```cpp
#include <indigo.h>

int main() {
    bre::Operation O;

    /**
     * @param path Expects a valid file path. Operation handles it automatically.
     * @param args A std::vector<std::string> containing arguments passed through the CLI. (OPTIONAL)
     */
    O.inputFile("FILE_PATH"); // Automatically executes the script

    /**
     * @param source The source code written in Bre.
     * @param args A std::vector<std::string> containing arguments passed through the CLI. (OPTIONAL)
     */
    O.executeString("new #Number x = 10"); // Automatically executes the string
}
```

> The `.pushSymbol()` method is planned for implementation in the stable release.

### CLI

- New command: `repl`
  > Explicitly starts the REPL.
- New behavior for the `--parse file.bre` command.
  > The `--parse <file>` command now returns only an exit code (`0`) upon success.

### Parsing

- Improved, cleaned up, and reorganized the parser.
- Added parsing support for new expressions.

### Codegen

- Added support for BreVM 0.0.2.
- Added support for BreVMR 1.
- Added support for new instructions and expressions.
- Added support for `RuntimeValue` types.

---

## Release

### Standard Library

A new Standard Library is now available in its early testing and development stage!

- `std_argv`

  > Returns the arguments passed through the CLI. For example:

  ```bash
  indigo run main.bre hello!
  ```

  ```bre
  proto std_argv0 // indigo
  proto std_argv3 // hello!
  ```

- `std_version`

  > Returns the ProtoIndigo version.

  ```bre
  proto std_version
  ```

- `std_vm_version`

  > Returns the BreVM version.

  ```bre
  proto std_vm_version
  ```

### Keywords

- Removed the `const` keyword.
- Added the contextual keyword `label`.
- Added the `go` keyword.
- Added the `to` keyword.
- Added the `pre` keyword.

### ProtoIndigo

- Added support for comments.

  ```bre
  // Hello! This is a comment. The Tokenizer ignores it.
  ```

---

- Added new instructions for incrementing and decrementing `Number` variables and constants.

  ```bre
  new x = 10;
  x++; // Equivalent to: x = x + 1
  x--; // Equivalent to: x = x - 1
  ```

  > **Note:** Increment and decrement are currently instructions, not expressions. This limitation is expected to be addressed in future updates.

---

- Added support for parenthesized expressions.

  > Expressions enclosed in parentheses are isolated and given higher evaluation priority by the interpreter.

  > Do not mistake `proto` for a function just because parentheses are involved. `proto` remains an instruction, and something like `proto(10, "Hello World!")` will result in an error.

  ```bre
  new x = 10 - 5 + (100 / 2); // The expression inside the parentheses is evaluated first.
  ```

  ```bre
  proto(10 / 2) // This is not a function call, but it is still parsed normally.
  ```

---

- Added implicit multiplication.

  > This feature, which is still experimental, allows numbers followed by identifiers or parenthesized expressions `()` to be interpreted as multiplication.

  ```bre
  new x = 10;
  proto 2x; // Equivalent to: proto 2 * x;
  ```

  ```bre
  proto 2(10 + 10); // Equivalent to: proto 2 * (10 + 10);
  ```

---

- Added the `label` instruction.

  > Used to mark specific locations in the code, allowing instructions such as `goto` to redirect the VM's execution flow to a designated point.

  ```bre
  label myhome
  ```

- Removed the `const` declaration syntax:

  ```bre
  new const x = 5;
  ```

  The `now` keyword remains available for constant declarations:

  ```bre
  now x = 5;
  ```

- Added a new instruction for pre-execution directives:

  ```bre
  pre <statement>
  ```

- Introduced a new syntax for including Bre scripts:

  ```bre
  pre include "file.bre"
  ```

  The `pre` keyword is now required before `include` to specify script inclusion as a pre-execution directive.
# ProtoIndigo 2.0.2
New features and amazing fixes have been added. *And still no functions... welp.*

- Constants now actually fulfill their purpose by preventing reassignment.
- `.bre` file inclusion has been added as an initial import system, currently in the testing and prototyping phase.

Module
```
now VERSION = "2.0.2"
```

Including
```bre
include "module.bre"

proto VERSION
```

2026-08-22

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