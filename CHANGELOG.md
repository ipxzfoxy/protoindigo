# ProtoIndigo 2.1.0
**Structural reorganization** for improved **code maintainability**, along with a few **additional utilities**.

## Mudanças internas específicas
- BreVM desaclopada do repositório protoindigo, transferindo-se para seu próprio repositório.
- compiler/ renomeado apra codegen/
- orquetrador de codegen renomeado de Compiler para WaveCoder
- Parser reorganized and split into multiple files.
- Codegen reformulado para seguir a BreVMR 1
- Mudanças no Tokenizer
- Novos tokens: `CTX_KW`, `GO`, `TO`

## Relevante
- Diversas mudanças no compilador
- Adicionado suporte para BreVM v0.0.2
- Adicionado suporte para BreVMR 1
- Tokenizer aprimorado
* CLI atualizada: Agora é possível executar arquivos `.bre` diretamente pela linha de comando, sem a necessidade de utilizar explicitamente o comando `run`.

  Por exemplo, em vez de:

  `indigo run file.bre`

  agora também é possível utilizar:

  `indigo file.bre`

  O uso de `indigo run file.bre` continua sendo recomendado por deixar a intenção do comando explícita. Além disso, o comando `run` é obrigatório para executar arquivos que não possuem a extensão `.bre`.

- New increment and decrement instructions
> Instruções para incrementar ou decrementar um dígito a uma variável do tipo number.

```bre
new x = 10;
x++ // Equivalente a x = x + 1;
x-- // Equivalente a x = x - 1;
```

- Added support for comments
> Comentários são ignorados pelo parser e não chegam na fase de code generation.

```bre
proto "Hello, World!";

// And still no functions... welp.
```

- Diagnósticos melhorados e padronizados. de:

```bash
SyntaxError
Expected 11 but: 7
```

para

```bash
SyntaxError: Expected ')' but: <end_of_file>
```

- Adicionado suporte para expressões dentro de parênteses:

```bre
new x = 10 + (10 / 2) // Retornando 15, com a expressão dentro dos parênteses send resolvida com prioridade.
```

- Adicionada Multiplicação implícita

```bre
new x = 10;

proto 2x
```

retorna `20`, que é equivalente a:

```bre
new x = 10;

proto 2 * x
```

E também com parenteses:

```bre
proto 2(10 / 2)
```

retorna `25`, que é equivalente a:

```bre
proto 2 * (10 / 2)
```

- Nova instrução: label
> Utilizada para marcar pontos específicos no código. permitindo que instruções como goto desviem o fluxo de execução da VM para determinado ponto.

```bre
label home // label <IDENTIFIER>
```

- Nova instrução: go/to
> A instrução go/to desvia o fluxo de execução para um determinado ponto, marcado por um label.

```bre
label home

proto "Hello, World!"

go to home
```

*Que a partir do ponto marcado por `home`, o compilador irá ejetar o opcode `JMP` para voltar ou avançar a partir do ponto marcado pelo label.*

- go/to com contatores
> Define um limite de quantas vezes tal go/to pode ser executado.

Que nesse caso, o pulo até home só poderia ser feito 2 vezes.

```bre
label home

proto "Hello, World!"

go 2 to home
```

- go/to explícitos
> Um forma de redirecionar a execução usando go/to com números no lugar de labels.

```
go to 1
```

- label proto
> Labels podem ser jogados na saída. que retornam um size_t indicando o ponto que o label aponta.

# Mudanças completas

- BreVM desaclopada do repositório protoindigo, transferindo-se para seu próprio repositório.
- compiler/ renomeado apra codegen/
- Diversas mudaças no compilador
- Codegen reformulado para seguir a BreVMR 1
- Adicionado suporte para BreVM v0.0.2
- Parser reorganized and split into multiple files.
- Tokenizer aprimorado
- New increment and decrement instructions
- Added support for comments
- Diagnósticos melhorados e padronizados.
- Adicionado suporte para expressões dentro de parênteses.
- Adicionada Multiplicação implícita.

*2026-09-02*

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